import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test37(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 37: Given the same graph, the same source and destination vertices, and the method is set to Bellman-Ford,
        the result should be the same as when using Dijkstra's algorithm."""

        bellman_ford_output = shortest_path(graph, method="BF")
        dijkstra_output = shortest_path(graph, method="D")

        np.testing.assert_array_almost_equal(bellman_ford_output, dijkstra_output, decimal=6)


if __name__ == "__main__":
    unittest.main()
