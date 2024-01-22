import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test29(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 29: Given the same graph, the same source and destination vertices,
        if we add an edge with weight less than the shortest path, the shortest path length should decrease."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Add an edge with weight less than the original shortest path
        modified_graph = deepcopy(graph)
        modified_graph[src][dst] = original_shortest_path - 1

        # Get the shortest path for the modified graph
        modified_shortest_path = shortest_path(modified_graph, method=method)[src][dst]

        # Verification
        self.assertLess(modified_shortest_path, original_shortest_path)


if __name__ == "__main__":
    unittest.main()
