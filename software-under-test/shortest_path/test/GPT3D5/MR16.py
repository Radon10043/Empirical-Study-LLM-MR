import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from copy import deepcopy

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test16(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 16: Given the same graph, the same source and destination vertices,
        if we reverse the graph (treat edges as undirected), the shortest path length should remain the same."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Reverse the graph (treat edges as undirected)
        reversed_graph = deepcopy(graph)
        for i in range(len(graph)):
            for j in range(i, len(graph)):
                reversed_graph[i][j] = reversed_graph[j][i]

        # Get the shortest path for the reversed graph
        reversed_shortest_path = shortest_path(reversed_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path, reversed_shortest_path)


if __name__ == "__main__":
    unittest.main()
