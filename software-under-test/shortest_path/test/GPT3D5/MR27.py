import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test27(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 27: Given the same graph, the same source and destination vertices,
        if we connect the source vertex to all other vertices with zero-weight edges, the shortest path length should not increase."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Connect the source vertex to all other vertices with zero-weight edges for the follow-up input
        modified_graph = deepcopy(graph)
        modified_graph[src] = [0] * len(graph)

        # Get the shortest path for the modified graph
        modified_shortest_path = shortest_path(modified_graph, method=method)[src][dst]

        # Verification
        self.assertLessEqual(modified_shortest_path, original_shortest_path)


if __name__ == "__main__":
    unittest.main()
