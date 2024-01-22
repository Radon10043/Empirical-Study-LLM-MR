import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test23(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 23: Given the same graph, the same source and destination vertices,
        if we decrease all edge weights by a constant, the shortest path length should remain the same or increase."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Decrease all edge weights by a constant for follow-up input
        decreased_weight_graph = [[max(weight - 1, 0) for weight in row] for row in graph]

        # Get the shortest path for the modified graph
        decreased_shortest_path = shortest_path(decreased_weight_graph, method=method)[src][dst]

        # Verification
        self.assertGreaterEqual(decreased_shortest_path, original_shortest_path)


if __name__ == "__main__":
    unittest.main()
