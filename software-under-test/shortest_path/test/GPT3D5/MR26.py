import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test26(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 26: Given the same graph, the same source and destination vertices,
        if we change all edge weights to 1, the shortest path length should not increase"""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Change all edge weights to 1 for follow-up input
        modified_graph = [[1 if weight != np.inf else np.inf for weight in row] for row in graph]

        # Get the shortest path for the modified graph
        modified_shortest_path = shortest_path(modified_graph, method=method)[src][dst]

        # Verification
        self.assertLessEqual(modified_shortest_path, original_shortest_path)


if __name__ == "__main__":
    unittest.main()
