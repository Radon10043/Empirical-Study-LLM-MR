import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test25(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 25: Given the same graph, the same source and destination vertices,
        if we add a new vertex with a directed zero-weight edge from source and a directed edge to destination,
        the shortest path length should remain unchanged or decrease"""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Add a new vertex and connect it to the source and destination vertices with zero-weight and non-zero-weight edges
        extended_graph = deepcopy(graph)
        extended_graph.append([0 if i == src else np.inf for i in range(len(graph) - 1)] + [1])  # Connect the new vertex to the source
        extended_graph[src][len(graph)] = 0  # Connect the source to the new vertex
        extended_graph[len(graph)][dst] = 1  # Connect the new vertex to the destination

        # Get the shortest path for the extended graph
        extended_shortest_path = shortest_path(extended_graph, method=method)[src][dst]

        # Verification
        self.assertLessEqual(extended_shortest_path, original_shortest_path)


if __name__ == "__main__":
    unittest.main()
