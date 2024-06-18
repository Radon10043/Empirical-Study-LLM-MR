import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test32(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 32: Computing the shortest path between a smaller set of nodes (indices)
        should reflect a subset of the distances in the full distance matrix."""
        indices = [x for x in range(0, len(graph) - 1)]
        method = "D"

        # Get full distance matrix
        full_dist_matrix = shortest_path(graph, method=method)

        # Get distance matrix for the subset of nodes specified by indices
        subset_dist_matrix = shortest_path(graph, method=method, indices=indices)

        # Verify the subset distances match the corresponding distances in the full matrix
        for i in indices:
            for j in indices:
                self.assertEqual(full_dist_matrix[i][j], subset_dist_matrix[i][j])


if __name__ == "__main__":
    unittest.main()
