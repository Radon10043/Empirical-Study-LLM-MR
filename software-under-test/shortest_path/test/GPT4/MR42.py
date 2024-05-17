import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test42(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 42: In an undirected graph, making a copy of the graph and interchanging 
        two nodes should not affect the shortest path lengths between any other pair of nodes."""
        csgraph = csr_matrix(graph)
        
        # Create a copy of the original graph
        permuted_csgraph = csgraph.copy()

        # Select two nodes to interchange
        num_nodes = csgraph.shape[0]
        node_a, node_b = np.random.choice(num_nodes, size=2, replace=False)

        # Interchange the nodes in the graph's adjacency matrix
        permuted_csgraph[[node_a, node_b], :] = permuted_csgraph[[node_b, node_a], :]
        permuted_csgraph[:, [node_a, node_b]] = permuted_csgraph[:, [node_b, node_a]]

        # Compute shortest path lengths for both graphs
        original_distances = shortest_path(csgraph, directed=False)
        permuted_distances = shortest_path(permuted_csgraph, directed=False)

        # Verify that the shortest path lengths between other nodes remain the same
        mask = np.ones(num_nodes, dtype=bool)
        mask[[node_a, node_b]] = False
        np.testing.assert_array_equal(original_distances[mask][:, mask], permuted_distances[mask][:, mask])


if __name__ == "__main__":
    unittest.main()
