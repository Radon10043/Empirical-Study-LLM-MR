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
    def test11(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 11: Given the same graph, the same source and destination vertices,
        if we remove all edges connected to the source vertex, the shortest path length should increase or remain the same."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        trimmed_graph = deepcopy(graph)
        for i in range(len(trimmed_graph)):
            trimmed_graph[src][i] = np.inf  # Remove all edges connected to the source vertex

        # Get the shortest path for the modified graph
        new_shortest_path = shortest_path(trimmed_graph, method=method)[src][dst]

        # Verification
        self.assertGreaterEqual(new_shortest_path, original_shortest_path)


if __name__ == "__main__":
    unittest.main()
