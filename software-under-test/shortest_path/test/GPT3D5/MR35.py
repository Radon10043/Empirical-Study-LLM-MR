import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test35(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 35: Given the same graph, the same source and destination vertices,
        if we add a new edge that creates a shorter path, the shortest path length should decrease."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        for i in range(len(graph)):
            for j in range(len(graph[i])):
                if i != j and graph[i][j] > original_shortest_path:
                    # Add a new edge that creates a shorter path
                    modified_graph = deepcopy(graph)
                    modified_graph[i][j] = graph[i][j] - 1  # Add the new edge

                    # Get the shortest path for the modified graph
                    modified_shortest_path = shortest_path(modified_graph, method=method)[src][dst]

                    # Verification
                    self.assertLess(modified_shortest_path, original_shortest_path)


if __name__ == "__main__":
    unittest.main()
