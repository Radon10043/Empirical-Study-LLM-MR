import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test20(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 20: If the same constant is added to all weights in the graph, the shortest path
        should remain the same, but its length should increase by the constant multiplied by the number of edges 
        in the path."""
        csgraph = csr_matrix(graph)

        # Constant to add
        constant = 5
        # Modified graph with the constant added to all weights
        modified_csgraph = csgraph.copy()
        modified_csgraph.data += constant

        # Get the original shortest paths and predecessors
        original_dists, original_preds = shortest_path(csgraph, return_predecessors=True)

        # Get the shortest paths and predecessors for the modified graph
        modified_dists, modified_preds = shortest_path(modified_csgraph, return_predecessors=True)

        # The shortest paths should not change, but the lengths should
        for v in range(original_dists.shape[0]):
            dest_pred = original_preds[:, v]
            path_length = np.where(dest_pred != -9999, 1, 0).sum() - 1
            np.testing.assert_array_equal(original_preds[:, v], modified_preds[:, v])
            expected_increase = path_length * constant
            np.testing.assert_allclose(modified_dists[:, v], original_dists[:, v] + expected_increase)


if __name__ == "__main__":
    unittest.main()
