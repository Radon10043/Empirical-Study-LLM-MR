import numpy as np

import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(gen_tcs_randomly)
    def test6(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 6: Given the same graph, the same source and destination vertices,
        adding a constant value to all edge weights should result in updated shortest path lengths."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Add a constant value to all edge weights in the graph for follow-up input
        modified_graph = [[weight + 1 for weight in row] for row in graph]

        # Get the updated shortest path for the modified graph
        modified_shortest_path = shortest_path(modified_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path + 1, modified_shortest_path)


if __name__ == "__main__":
    unittest.main()
