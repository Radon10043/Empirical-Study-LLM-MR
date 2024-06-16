import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test17(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 17: Given the same graph and source vertex,
        if the destination vertex is the same as the source vertex,
        the shortest path distance should be 0."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Verify that the distance from a node to itself is always 0
        self.assertEqual(source_out[src][src], 0)


if __name__ == "__main__":
    unittest.main()
