import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test8(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 8: Adding a new vertex to the graph with edges that do not offer
        a shortcut for existing paths should not change the shortest paths among existing vertices."""
        # Add an additional vertex (no shortcut edges)
        new_graph = deepcopy(graph)
        for i in range(len(graph)):
            new_graph[i].append(1e6)
        new_graph.append([1e6] * (len(graph) + 1))

        graph = csr_matrix(graph)
        new_graph = csr_matrix(new_graph)

        # Get original distance matrix before adding the vertex
        original_dist_matrix = shortest_path(graph)

        # Get distance matrix after adding the vertex
        new_dist_matrix = shortest_path(new_graph)

        # Compare shortest paths among existing vertices
        for i in range(graph.shape[0]):
            for j in range(graph.shape[0]):
                self.assertEqual(original_dist_matrix[i][j], new_dist_matrix[i][j])


if __name__ == "__main__":
    unittest.main()
