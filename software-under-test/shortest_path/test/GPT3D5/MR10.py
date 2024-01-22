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
    def test10(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 10: Given the same graph, the same source and destination vertices,
        if we add an isolated vertex to the graph, the shortest path length should remain the same."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Add an isolated vertex to the graph for follow-up input
        isolated_graph = deepcopy(graph)
        isolated_graph.append([np.inf] * (len(graph) + 1))  # Add a new vertex with no connections

        # Get the shortest path for the modified graph
        isolated_shortest_path = shortest_path(isolated_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path, isolated_shortest_path)


if __name__ == "__main__":
    unittest.main()
