import numpy as np

import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test21(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 21: Given the same graph, the same source and destination vertices,
        if we remove all edges from the graph, the shortest path length should remain unchanged."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Remove all edges from the graph for follow-up input
        empty_graph = [[np.inf for _ in row] for row in graph]

        # Get the shortest path for the empty graph
        empty_shortest_path = shortest_path(empty_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path, empty_shortest_path)


if __name__ == "__main__":
    unittest.main()
