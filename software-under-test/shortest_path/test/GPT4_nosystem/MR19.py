import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test19(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 19: The shortest path from any source node to a set of selected nodes
        should match the paths obtained when the shortest paths algorithm is run for the subset of
        these nodes specified by indices."""
        indices = [i for i in range(0, len(graph) - 1)]

        # Get distance matrix for all nodes
        full_dist_matrix = shortest_path(graph, method=method)

        # Get distance matrix for a subset of nodes
        subset_dist_matrix = shortest_path(graph, method=method, indices=indices)

        # Verify that the distances to selected nodes are the same
        for i in indices:
            for j in indices:
                subset_index_i = indices.index(i)
                subset_index_j = indices.index(j)
                self.assertEqual(full_dist_matrix[i][j], subset_dist_matrix[subset_index_i][subset_index_j])


if __name__ == "__main__":
    unittest.main()
