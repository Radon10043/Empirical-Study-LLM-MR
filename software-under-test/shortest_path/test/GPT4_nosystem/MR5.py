import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test5(self, graph: list, src: int, dst: list, method: str):  # Fixed
        """Metamorphic Relation 5: When a set of indices is specified, their shortest paths
        distances should match those in the complete distance matrix."""
        indices = [x for x in range(len(graph) - 1)]

        # Get the full distance matrix
        full_dist_matrix = shortest_path(graph, method=method)

        # Get distance matrix only for specified nodes
        partial_dist_matrix = shortest_path(graph, indices=indices, method=method)

        # Verification
        for idx in indices:
            for j in range(len(graph) - 1):
                self.assertEqual(full_dist_matrix[idx][j], partial_dist_matrix[idx][j])
                self.assertEqual(full_dist_matrix[j][idx], partial_dist_matrix[idx][j])


if __name__ == "__main__":
    unittest.main()
