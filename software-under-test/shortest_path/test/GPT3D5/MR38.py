import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test38(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 38: Given the same graph, the same source and destination vertices,
        if we create a graph with the reverse edge weights, the shortest path length should remain unchanged."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Create a graph with reverse edge weights for follow-up input
        modified_graph = [[weight for weight in reversed(row)] for row in graph]

        # Get the shortest path for the modified graph
        modified_shortest_path = shortest_path(modified_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path, modified_shortest_path)


if __name__ == "__main__":
    unittest.main()
