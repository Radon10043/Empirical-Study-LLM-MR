import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test31(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 31: Reducing the weights of all edges by a constant amount down to a
        minimum of zero should not increase the length of any shortest path."""
        csgraph = csr_matrix(graph)

        # Calculate the minimum positive weight in the graph
        min_positive_weight = csgraph.data[csgraph.data > 0].min()

        # Reduce all weights by min_positive_weight down to a minimum of zero
        modified_csgraph = csgraph.copy()
        modified_csgraph.data -= min_positive_weight
        modified_csgraph.data[modified_csgraph.data < 0] = 0

        # Get the original and modified shortest path lengths
        original_dists = shortest_path(csgraph)
        modified_dists = shortest_path(modified_csgraph)

        n = original_dists.shape[0]
        for i in range(n):
            for j in range(n):
                # Verify that the modified shortest path distances are not greater than the original
                self.assertLessEqual(modified_dists[i, j], original_dists[i, j])


if __name__ == "__main__":
    unittest.main()
