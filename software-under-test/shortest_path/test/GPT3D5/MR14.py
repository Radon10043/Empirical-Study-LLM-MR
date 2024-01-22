import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test14(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 14: Given the same graph, the same source and destination vertices,
        if we make all edge weights the same, the shortest path length should remain the same."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Make all edge weights the same for follow-up input
        uniform_weight_graph = [[1 for _ in row] for row in graph]

        # Get the shortest path for the uniform weight graph
        uniform_shortest_path = shortest_path(uniform_weight_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path, uniform_shortest_path)


if __name__ == "__main__":
    unittest.main()
