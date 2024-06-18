import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test7(self, graph: list, src: int, dst: int, method: str):    # Fixed
        """Metamorphic Relation 7: Multiplying the weights of all edges by a positive constant
        should not change the structure/order of the shortest path but the total weights should
        be scaled accordingly."""
        weights_multiplier = 2

        # Get original distance output
        original_dist_matrix = shortest_path(graph, method=method)

        # Scale weights of the graph
        scaled_graph = [list(map(lambda edge: edge * weights_multiplier if edge != 0 else 0, row)) for row in graph]

        # Get scaled distance output
        scaled_dist_matrix = shortest_path(scaled_graph, method=method)

        # Verify that distances are scaled correctly
        for i in range(len(graph)):
            for j in range(len(graph)):
                self.assertAlmostEqual(original_dist_matrix[i][j] * weights_multiplier, scaled_dist_matrix[i][j])


if __name__ == "__main__":
    unittest.main()
