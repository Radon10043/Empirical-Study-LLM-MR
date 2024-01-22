import numpy as np

import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from copy import deepcopy

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test17(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 17: Given the same graph, the same source and destination vertices,
        if we add a bypass path that is shorter than the original shortest path, the new shortest path should be the length of the bypass path."""
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Find intermediary node
        inter_node = None
        for i in range(len(graph)):
            if i != src and i != dst and graph[src][i] != np.inf and graph[i][dst] != np.inf:
                inter_node = i
                break

        if inter_node is not None:
            # Create bypass path
            bypass_graph = deepcopy(graph)
            bypass_graph[src][dst] = bypass_graph[src][inter_node] + bypass_graph[inter_node][dst]

            # Get the shortest path for the bypass graph
            bypass_shortest_path = shortest_path(bypass_graph, method=method)[src][dst]

            # Verification
            self.assertEqual(bypass_shortest_path, bypass_graph[src][dst])


if __name__ == "__main__":
    unittest.main()
