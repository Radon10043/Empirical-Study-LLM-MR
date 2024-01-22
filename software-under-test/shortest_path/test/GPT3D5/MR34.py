import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test34(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 34: Given the same graph, the same source and destination vertices,
        if we add a new edge that creates a cycle in the graph, the shortest path length should not increase."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Find an edge which, when added, creates a cycle in the graph
        for i in range(len(graph)):
            for j in range(len(graph[i])):
                if i != j and graph[i][j] != np.inf:
                    # Add a new edge that creates a cycle
                    modified_graph = deepcopy(graph)
                    modified_graph[j][src] = 1  # Add the new edge

                    # Get the shortest path for the modified graph
                    modified_shortest_path = shortest_path(modified_graph, method=method)[src][dst]

                    # Verification
                    self.assertLessEqual(modified_shortest_path, original_shortest_path)


if __name__ == "__main__":
    unittest.main()
