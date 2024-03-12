import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def add_vertex(self, graph: list) -> list:
        """Add a new vertex to the graph.

        Parameters
        ----------
        graph : list
            The adjacency matrix of the graph

        Returns
        -------
        list
            The new graph after adding a new vertex
        """
        n = len(graph)
        new_graph = [[0] * (n + 1) for _ in range(n + 1)]
        for i in range(n + 1):
            for j in range(n + 1):
                if i < n and j < n:
                    new_graph[i][j] = graph[i][j]
                else:
                    new_graph[i][j] = random.randint(1, 1000)
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test16(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 16: If a new vertex is added to the graph, the shortest path distances from all existing vertices to the new vertex should be greater than or equal to the shortest distances without the new vertex."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)

        new_graph = self.add_vertex(graph)

        # Get follow-up output
        follow_out = shortest_path(new_graph, method=method, directed=True)

        # Verify that all distances have increased or remained the same
        for i in range(len(source_out)):
            for j in range(len(source_out[0])):
                if i != j:
                    self.assertGreaterEqual(follow_out[i][j], source_out[i][j])


if __name__ == "__main__":
    unittest.main()
