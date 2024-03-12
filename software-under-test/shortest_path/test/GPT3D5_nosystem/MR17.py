import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def remove_vertex(self, graph: list, vertex_to_remove: int) -> list:
        """Remove a vertex from the graph.

        Parameters
        ----------
        graph : list
            The adjacency matrix of the graph
        vertex_to_remove : int
            The vertex to remove

        Returns
        -------
        list
            The new graph after removing the vertex
        """
        n = len(graph)
        new_graph = [[0] * (n - 1) for _ in range(n - 1)]
        for i in range(n):
            for j in range(n):
                if i < vertex_to_remove and j < vertex_to_remove:
                    new_graph[i][j] = graph[i][j]
                elif i < vertex_to_remove and j > vertex_to_remove:
                    new_graph[i][j - 1] = graph[i][j]
                elif i > vertex_to_remove and j < vertex_to_remove:
                    new_graph[i - 1][j] = graph[i][j]
                elif i > vertex_to_remove and j > vertex_to_remove:
                    new_graph[i - 1][j - 1] = graph[i][j]
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test17(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 17: If a vertex is removed from the graph, the shortest path distances between the remaining vertices should decrease or remain the same."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)

        vertex_to_remove = random.randint(0, len(graph) - 1)
        new_graph = self.remove_vertex(graph, vertex_to_remove)

        # Get follow-up output
        follow_out = shortest_path(new_graph, method=method, directed=True)

        # Verify that all distances have decreased or remained the same
        for i in range(len(source_out)):
            for j in range(len(source_out[0])):
                if i != j:
                    self.assertLessEqual(follow_out[i][j], source_out[i][j])


if __name__ == "__main__":
    unittest.main()