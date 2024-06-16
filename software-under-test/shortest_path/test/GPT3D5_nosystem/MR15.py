import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test15(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 15: Given the same graph, the shortest path from a node to itself
        should always be 0, regardless of the algorithm or graph representation"""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Verify that the distance from a node to itself is always 0
        for i in range(len(graph)):
            self.assertEqual(source_out[i][i], 0)


if __name__ == "__main__":
    unittest.main()
