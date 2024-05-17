import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test34(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 34: For a connected undirected graph, removing edges should
        not decrease the shortest path lengths between nodes."""
        csgraph = csr_matrix(graph)

        # Start with an undirected graph by making the original_csgraph symmetric
        undirected_graph = csgraph + csgraph.T

        # Remove a random sample of edges, not disconnected the graph
        removal_indices = np.random.choice(undirected_graph.nnz, size=10, replace=False)
        undirected_graph.data[removal_indices] = 0  # Set selected edges to weight 0
        undirected_graph.eliminate_zeros()  # Remove zero-weight edges effectively

        # Get shortest path distances from the original and modified graphs
        original_dists = shortest_path(csgraph, directed=False)
        modified_dists = shortest_path(undirected_graph, directed=False)

        # Check that the shortest path distances are not decreased after edge removal
        n = original_dists.shape[0]
        for i in range(n):
            for j in range(n):
                self.assertGreaterEqual(modified_dists[i, j], original_dists[i, j])


if __name__ == "__main__":
    unittest.main()
