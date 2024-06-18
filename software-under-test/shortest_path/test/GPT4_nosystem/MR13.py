import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test13(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 13: Removing an edge from the graph (changing its weight to infinity
        or a very large number) cannot make the shortest paths shorter, only longer or unchanged.
        For disconnected verticals, we may represent the lack of an edge with `numpy.inf`."""
        import numpy as np
        remove_i = 0
        remove_j = 1

        # Get original distances
        original_dist_matrix = shortest_path(graph, method=method)

        # Select an arbitrary edge to remove (set its distance to infinity)
        graph_with_removed_edge = [[np.inf if x != 0 and i == remove_i and j == remove_j else x
                                    for j, x in enumerate(row)] for i, row in enumerate(graph)]

        # Get distances with the edge removed
        new_dist_matrix = shortest_path(graph_with_removed_edge, method=method)

        # Verify that no path is shorter than the original path
        for i in range(len(graph)):
            for j in range(len(graph)):
                if original_dist_matrix[i][j] != np.inf:
                    self.assertLessEqual(original_dist_matrix[i][j], new_dist_matrix[i][j])

if __name__ == "__main__":
    unittest.main()
