import unittest
import os, sys

from copy import deepcopy
from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test7(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 7: Given the same graph, the same source and destination vertices,
        if we duplicate a vertex in the graph, the shortest path length should remain the same."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Duplicate a vertex in the graph for follow-up input
        duplicated_graph = deepcopy(graph)
        duplicated_graph.append(list(graph[src]))  # Duplicate the source vertex

        # Get the shortest path for the modified graph
        duplicated_shortest_path = shortest_path(duplicated_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path, duplicated_shortest_path)


if __name__ == "__main__":
    unittest.main()
