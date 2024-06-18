import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test27(self, graph: list, str: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 27: Inverting the direction of a directed graph should yield
        a transposed shortest path distance matrix."""
        # Assume that graph is directed and represented as a list of lists
        # Get original shortest path distances
        original_dist_matrix = shortest_path(graph, method=method, directed=True)

        # Invert direction of graph
        inverted_graph = [list(x) for x in zip(*graph)]  # Transpose the matrix

        # Get shortest path distances for inverted graph
        inverted_dist_matrix = shortest_path(inverted_graph, method=method, directed=True)

        # Verify that the inverted distance matrix is a transpose of the original
        for i in range(len(graph)):
            for j in range(len(graph)):
                self.assertEqual(original_dist_matrix[i][j], inverted_dist_matrix[j][i])


if __name__ == "__main__":
    unittest.main()
