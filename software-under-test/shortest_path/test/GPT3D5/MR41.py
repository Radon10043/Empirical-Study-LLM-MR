import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test41(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 41: Given the same graph, the same source and destination vertices,
        if we duplicate all edges in the graph, the shortest path length should remain unchanged."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Duplicate all edges in the graph for follow-up input
        duplicated_graph = [[weight for weight in row] for row in graph]

        # Get the shortest path for the duplicated graph
        duplicated_shortest_path = shortest_path(duplicated_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path, duplicated_shortest_path)


if __name__ == "__main__":
    unittest.main()
