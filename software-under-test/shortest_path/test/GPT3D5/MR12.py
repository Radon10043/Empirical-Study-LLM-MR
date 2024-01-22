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
    def test12(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 12: Given the same graph, the same source and destination vertices,
        if we add a new edge that bypasses the original shortest path, the shortest path length should increase."""
        original_result = shortest_path(graph, method=method)[src][dst]

        # Find a node that is accessible from the source and can reach the destination
        new_node = -1
        for i in range(len(graph)):
            if i != src and i != dst and graph[src][i] != np.inf and graph[i][dst] != np.inf:
                new_node = i
                break

        if new_node != -1:
            # Add a new edge that bypasses the original shortest path
            modified_graph = deepcopy(graph)
            modified_graph[src][new_node] = 1  # Add a new edge weight
            modified_graph[new_node][dst] = 1  # Add a new edge weight

            modified_result = shortest_path(modified_graph, method=method)[src][dst]
            self.assertGreater(modified_result, original_result)


if __name__ == "__main__":
    unittest.main()
