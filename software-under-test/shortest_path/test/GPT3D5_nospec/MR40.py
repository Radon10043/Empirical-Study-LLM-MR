import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test40(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 40: Given the same graph and vertices, if the graph is transposed, 
        the shortest paths between vertices should remain unchanged."""
        import numpy as np

        # Transpose the graph
        transposed_graph = np.transpose(graph)

        # Verify that the shortest paths are unchanged
        np.testing.assert_array_equal(shortest_path(graph, method=method), shortest_path(transposed_graph, method=method))


if __name__ == "__main__":
    unittest.main()
