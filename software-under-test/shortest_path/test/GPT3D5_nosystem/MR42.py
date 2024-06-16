import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test42(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 42: Given the same graph, if the source and the destination vertices are the same,
        and the graph has non-negative weights, the shortest path distance between them using Dijkstra's algorithm should be 0."""

        if method == "D":
            result = shortest_path(graph, method=method)
            self.assertEqual(result[src][src], 0)


if __name__ == "__main__":
    unittest.main()
