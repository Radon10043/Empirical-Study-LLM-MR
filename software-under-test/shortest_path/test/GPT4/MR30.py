import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
import scipy as sp


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test30(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 30: Adding a new node connected to all existing nodes with very high weight edges 
        should not change the shortest paths between any of the original nodes."""
        csgraph = csr_matrix(graph)

        # Define a high weight that is practically impossible to be part of any shortest path
        high_weight = 1e6
        num_vertices = csgraph.shape[0]

        # Extend the csgraph with one additional node connected by high_weight edges
        modified_csgraph = sp.sparse.lil_matrix((num_vertices + 1, num_vertices + 1))
        modified_csgraph[:num_vertices, :num_vertices] = csgraph
        modified_csgraph[num_vertices, :] = high_weight
        modified_csgraph[:, num_vertices] = high_weight
        modified_csgraph = modified_csgraph.tocsr()

        # Get original and modified shortest path outputs
        original_output = shortest_path(csgraph)
        modified_output = shortest_path(modified_csgraph)

        # The shortest paths should remain the same for the original nodes
        np.testing.assert_array_equal(original_output, modified_output[:num_vertices, :num_vertices])


if __name__ == "__main__":
    unittest.main()
