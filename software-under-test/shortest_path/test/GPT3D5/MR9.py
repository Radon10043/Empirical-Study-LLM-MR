import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test9(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 9: Given the same graph, the same source and destination vertices,
        if we multiply all edge weights by a negative constant, the shortest path length should remain the same."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Multiply all edge weights by a negative constant for follow-up input
        negated_graph = [[weight * -1 for weight in row] for row in graph]

        # Get the shortest path for the modified graph
        negated_shortest_path = shortest_path(negated_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path, negated_shortest_path)


if __name__ == "__main__":
    unittest.main()
