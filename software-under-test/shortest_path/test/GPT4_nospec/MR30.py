import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test30(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 30: For an undirected graph, adding a mirror image of the graph should not alter the shortest paths within the original graph."""
        # Get the current shortest paths matrix
        paths_matrix = shortest_path(graph, method=method)

        # Create a mirror of the graph and combine with the original to create a larger graph
        mirror_graph = [list(reversed(row)) for row in reversed(graph)]
        combined_graph = graph + mirror_graph

        # Get the new shortest paths matrix for the combined graph
        new_paths_matrix = shortest_path(combined_graph, method=method)

        # Verify that the shortest paths within the original graph's node space are unchanged
        for i in range(len(graph)):
            for j in range(len(graph)):
                self.assertEqual(paths_matrix[i][j], new_paths_matrix[i][j])


if __name__ == "__main__":
    unittest.main()
