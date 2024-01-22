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
    def test13(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 13: Given the same graph, the same source and destination vertices,
        if we add a new vertex with a direct edge to the source and destination, the shortest path length should decrease or remain the same."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Add a new vertex with direct edges to the source and destination
        extended_graph = deepcopy(graph)
        extended_graph.append([np.inf] * (len(graph) + 1))  # Add a new vertex with no connections
        extended_graph[src][len(graph)] = 1  # Connect the new vertex to the source
        extended_graph[len(graph)][dst] = 1  # Connect the new vertex to the destination

        # Get the shortest path for the extended graph
        extended_shortest_path = shortest_path(extended_graph, method=method)[src][dst]

        # Verification
        self.assertLessEqual(extended_shortest_path, original_shortest_path)


if __name__ == "__main__":
    unittest.main()
