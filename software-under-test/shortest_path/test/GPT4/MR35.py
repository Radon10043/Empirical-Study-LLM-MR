import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test35(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 35: If the weight of an edge (i, j) in a graph is the minimum weight 
        of all outgoing edges from i, then removing this edge should increase the shortest path 
        distance from i to j."""
        csgraph = csr_matrix(graph)

        # Find an edge (i, j) such that edge weight is the minimum of all outgoing edges from i
        i, min_weight_outgoing_edge_idx = self.find_min_outgoing_edge(csgraph)
        j = csgraph.indices[min_weight_outgoing_edge_idx]

        # Remove edge (i, j)
        modified_csgraph = csgraph.copy()
        modified_csgraph[i, j] = 0
        modified_csgraph.eliminate_zeros()  # Remove zero-weight edges effectively

        # Get shortest path distances from the original and modified graphs
        original_dist_i_to_j = shortest_path(csgraph, indices=[i])[0][j]
        modified_dist_i_to_j = shortest_path(modified_csgraph, indices=[i])[0][j]

        # Check that the shortest path distance from i to j is increased after edge removal
        self.assertGreater(modified_dist_i_to_j, original_dist_i_to_j)

    def find_min_outgoing_edge(self, csgraph):
        min_weight = np.inf
        min_weight_idx = -1
        node_idx = -1
        for i in range(csgraph.shape[0]):
            outgoing_edges = csgraph.indices[csgraph.indptr[i]:csgraph.indptr[i+1]]
            outgoing_weights = csgraph.data[csgraph.indptr[i]:csgraph.indptr[i+1]]
            if outgoing_weights.size > 0:
                min_outgoing_weight_idx = outgoing_weights.argmin()
                if outgoing_weights[min_outgoing_weight_idx] < min_weight:
                    min_weight = outgoing_weights[min_outgoing_weight_idx]
                    min_weight_idx = csgraph.indptr[i] + min_outgoing_weight_idx
                    node_idx = i
        return node_idx, min_weight_idx


if __name__ == "__main__":
    unittest.main()
