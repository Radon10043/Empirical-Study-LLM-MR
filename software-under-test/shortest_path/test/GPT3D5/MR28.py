import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test28(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 28: Given the same graph, the same source and destination vertices,
        if we remove all edges except for the direct edge from source to destination, the shortest path length should not increase."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Remove all edges except for the direct edge from source to destination for the follow-up input
        modified_graph = [[np.inf] * len(graph) for _ in range(len(graph))]
        modified_graph[src][dst] = graph[src][dst]

        # Get the shortest path for the modified graph
        modified_shortest_path = shortest_path(modified_graph, method=method)[src][dst]

        # Verification
        self.assertLessEqual(modified_shortest_path, original_shortest_path)


if __name__ == "__main__":
    unittest.main()
