import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test9(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 9: The shortest path in a graph should remain the same or become
        improved (shorter or equal in length) if the weights of edges are decreased."""
        # Get original distance matrix
        original_dist_matrix = shortest_path(graph, method=method)

        # Construct follow-up input with decreased weights
        follow_graph = [[max(0, x - 1) if x != 0 else 0 for x in row] for row in graph]

        # Get follow-up distance matrix
        follow_dist_matrix = shortest_path(follow_graph, method=method)

        # Verify that paths are the same or shorter
        for i in range(len(graph)):
            for j in range(len(graph)):
                self.assertLessEqual(follow_dist_matrix[i][j], original_dist_matrix[i][j])


if __name__ == "__main__":
    unittest.main()
