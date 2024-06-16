import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test40(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 40: Given the same graph, if the source and destination vertices are the same,
        the shortest path between them should always be 0, regardless of the algorithm used."""

        result = shortest_path(graph, method=method)
        self.assertEqual(result[src][dst], 0)


if __name__ == "__main__":
    unittest.main()
