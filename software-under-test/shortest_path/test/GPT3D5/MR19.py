import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from copy import deepcopy

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test19(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 19: Given the same graph, the same source and destination vertices,
        if we remove a vertex and its incident edges, the shortest path length should remain the same or increase."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        if len(graph) > 1:
            # Remove a vertex and its incident edges from the graph for follow-up input
            reduced_graph = deepcopy(graph)
            reduced_graph.pop(src)  # Remove the vertex
            for row in reduced_graph:
                row.pop(src)  # Remove the incident edges

            # Get the shortest path for the reduced graph
            reduced_shortest_path = shortest_path(reduced_graph, method=method)[src][dst]

            # Verification
            self.assertGreaterEqual(reduced_shortest_path, original_shortest_path)


if __name__ == "__main__":
    unittest.main()
