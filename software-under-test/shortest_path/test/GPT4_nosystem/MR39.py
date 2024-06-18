import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test39(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 39: If a negative edge weight is introduced between two nodes that were
        previously connected by a positive weight, the shortest path distances involving these two nodes
        might decrease, but not for paths that do not involve this edge."""
        # Identify two connected nodes i and j with a positive weight
        i, j = 0, 1  # Example index, should be determined based on actual graph weights and structure
        assert graph[i][j] > 0, "Initial edge weight must be positive for this test case."

        # Get original distances
        original_dist_matrix = shortest_path(graph, method=method)

        # Introduce a negative weight on the edge from i to j
        graph_with_negative_edge = deepcopy(graph)
        graph_with_negative_edge[i][j] = -10

        # Get new distances
        new_dist_matrix = shortest_path(graph_with_negative_edge, method=method)

        # Check non-involved paths remain unaffected
        for src in range(len(graph)):
            for dst in range(len(graph)):
                if src != i and dst != j:
                    self.assertEqual(original_dist_matrix[src][dst], new_dist_matrix[src][dst])


if __name__ == "__main__":
    unittest.main()
