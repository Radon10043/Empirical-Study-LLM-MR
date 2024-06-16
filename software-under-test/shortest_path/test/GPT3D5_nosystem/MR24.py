import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test24(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 24: Given the same graph, the same source and destination vertices, 
        if we add a constant value to all edge weights, the shortest path length should be invariant"""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Create a new graph with all edge weights increased by a constant
        modified_graph = [[x + 2 for x in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(modified_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()