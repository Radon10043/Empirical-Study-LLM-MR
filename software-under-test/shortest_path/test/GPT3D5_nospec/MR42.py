import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test42(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 42: Given the same graph and vertices, if the weights are all set to 1, 
        the shortest path should still be the same as the original graph."""
        # Set all edge weights to 1
        modified_graph = [[1 for _ in range(len(graph))] for _ in range(len(graph))]

        # Verify that the shortest path remains unchanged
        np.testing.assert_array_equal(shortest_path(graph, method=method), shortest_path(modified_graph, method=method))


if __name__ == "__main__":
    unittest.main()
