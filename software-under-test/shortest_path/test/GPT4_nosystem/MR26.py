import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test26(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 26: Replacing all edges in the graph with a constant weight should not
        change the order of the nodes in the shortest path from any given source to all destinations."""
        # Replace all non-zero weights with a constant
        constant_weight = 5
        constant_weight_graph = [[constant_weight if x != 0 else 0 for x in row] for row in graph]

        # Get original shortest path distances
        original_dist_matrix = shortest_path(graph, method=method)

        # Get constant weight distances
        constant_dist_matrix = shortest_path(constant_weight_graph, method=method)

        # Verify that the order of the nodes by distance is preserved
        for i in range(len(graph)):
            original_order = sorted(range(len(graph)), key=lambda j: original_dist_matrix[i][j])
            constant_order = sorted(range(len(graph)), key=lambda j: constant_dist_matrix[j][i])
            self.assertEqual(original_order, constant_order)


if __name__ == "__main__":
    unittest.main()
