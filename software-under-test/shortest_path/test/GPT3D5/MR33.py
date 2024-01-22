import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test33(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 33: Given the same graph, the same source and destination vertices,
        if we remove all paths from the source to the destination except for the shortest path, 
        the only existing path should be the shortest path."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Modify the graph to remove alternative paths from src to dst
        modified_graph = deepcopy(graph)
        for i in range(len(graph)):
            for j in range(len(graph[i])):
                if i != src and j != dst:
                    modified_graph[i][j] = np.inf

        # Get the shortest path for the modified graph
        modified_shortest_path = shortest_path(modified_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path, modified_shortest_path)


if __name__ == "__main__":
    unittest.main()
