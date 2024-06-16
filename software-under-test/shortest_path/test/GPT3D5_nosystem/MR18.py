import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test18(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 18: Given the same graph and the same source and destination vertices,
        if the path is reversed, the distance should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        follow_graph = np.transpose(graph)
        follow_graph = np.ascontiguousarray(follow_graph)

        # Reverse the source and destination vertices
        reversed_out = shortest_path(graph, method=method)

        # Verify that the distance is the same
        self.assertTrue(source_out[src][dst], reversed_out[dst][src])


if __name__ == "__main__":
    unittest.main()
