import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from copy import deepcopy

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test24(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 24: Given the same graph, the same source and destination vertices,
        if we add a new vertex with zero-weight edges to all existing vertices, the shortest path length should remain unchanged."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Add a new vertex with zero-weight edges to all existing vertices for follow-up input
        extended_graph = deepcopy(graph)
        extended_graph.append([0] * len(graph))  # Add a new vertex with zero-weight edges

        for i in range(len(extended_graph)):
            extended_graph[i].append(0)  # Connect the new vertex to all existing vertices with zero-weight edges

        # Get the shortest path for the extended graph
        extended_shortest_path = shortest_path(extended_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path, extended_shortest_path)


if __name__ == "__main__":
    unittest.main()
