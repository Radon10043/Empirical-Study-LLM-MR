import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test41(self, graph: list, src: int, dist: int, method: str):  # Fixed
        """Metamorphic Relation 41: Translating all edge weights by a fixed constant (adding a constant to all
        weights) should not change the relative order of shortest paths but only increase the length of paths by
        a multiple of the constant times the number of edges in the path."""
        offset = 5
        translated_graph = deepcopy(graph)
        size = len(graph)

        # Add the constant to all edges
        for i in range(size):
            for j in range(size):
                if translated_graph[i][j] != 0:
                    translated_graph[i][j] += offset

        # Obtain shortest path distances
        original_dist_matrix = shortest_path(graph, method=method)
        translated_dist_matrix = shortest_path(translated_graph, method=method)

        # Check the order of vertices by comparing sorted orders based on path lengths
        for i in range(size):
            original_order = sorted(range(size), key=lambda x: original_dist_matrix[i][x])
            translated_order = sorted(range(size), key=lambda x: translated_dist_matrix[i][x])
            self.assertEqual(original_order, translated_order)


if __name__ == "__main__":
    unittest.main()
