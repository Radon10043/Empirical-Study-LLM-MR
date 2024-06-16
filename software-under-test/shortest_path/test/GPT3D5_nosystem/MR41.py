import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test41(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 41: Given the same graph, if the source and the destination vertices are not connected in the graph,
        the shortest path between them should be infinity."""

        # Set the edge between source and destination vertices to infinity
        disconnected_graph = graph.copy()
        disconnected_graph[src][dst] = np.inf
        result = shortest_path(disconnected_graph, method=method)

        self.assertEqual(result[src][dst], np.inf)


if __name__ == "__main__":
    unittest.main()
