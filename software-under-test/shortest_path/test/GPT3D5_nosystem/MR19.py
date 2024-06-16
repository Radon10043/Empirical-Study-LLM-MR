import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test19(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 19: Given the same graph, the same source and destination vertices,
        the distance should always be equal to or greater than 0"""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Verify that the distance is greater than or equal to 0
        self.assertTrue(source_out[src][dst] >= 0)


if __name__ == "__main__":
    unittest.main()
