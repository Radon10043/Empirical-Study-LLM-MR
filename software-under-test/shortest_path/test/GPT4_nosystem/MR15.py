import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test15(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 15: If all edges in a directed graph are reversed, the shortest path
        from node i to node j should equal the shortest path from node j to node i in the original
        graph."""
        # Get original directed distance matrix
        original_dist_matrix = shortest_path(graph, method=method, directed=True)

        # Reverse all edges in the graph (transpose the adjacency matrix)
        reversed_graph = np.transpose(graph)
        reversed_graph = np.ascontiguousarray(reversed_graph)

        # Get new distance matrix after reversing edges
        reversed_dist_matrix = shortest_path(reversed_graph, method=method, directed=True)

        # Verify that distances are correctly reversed
        for i in range(len(graph)):
            for j in range(len(graph)):
                self.assertEqual(original_dist_matrix[i][j], reversed_dist_matrix[j][i])


if __name__ == "__main__":
    unittest.main()
