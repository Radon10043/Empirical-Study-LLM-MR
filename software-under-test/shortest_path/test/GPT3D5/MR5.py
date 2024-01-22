import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test5(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 5: Given the same graph, the same source and destination vertices,
        reversing the direction of edges in the graph should result in the same shortest path length."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Reverse the direction of edges in the graph for follow-up input
        reversed_graph = [[graph[j][i] for j in range(len(graph[0]))] for i in range(len(graph))]

        # Get the shortest path for the reversed graph
        reversed_shortest_path = shortest_path(reversed_graph, method=method)[dst][src]

        # Verification
        self.assertEqual(original_shortest_path, reversed_shortest_path)


if __name__ == "__main__":
    unittest.main()
