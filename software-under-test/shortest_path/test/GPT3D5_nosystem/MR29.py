import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def add_node_with_all_connections(self, graph: list) -> list:
        """Add a new node with connections to all existing nodes in the graph.

        Parameters
        ----------
        graph : list
            The adjacency matrix of the graph

        Returns
        -------
        list
            The new graph after adding a new node with connections to all existing nodes
        """
        n = len(graph)
        new_graph = [[0] * (n + 1) for _ in range(n + 1)]
        for i in range(n):
            for j in range(n):
                new_graph[i][j] = graph[i][j]
        for i in range(n):
            new_graph[i][n] = random.randint(1, 1000)
            new_graph[n][i] = random.randint(1, 1000)
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test29(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 29: Adding a new node with connections to all existing nodes should change the shortest path distances."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)

        # Add a new node with connections to all existing nodes
        new_graph = self.add_node_with_all_connections(graph)

        # Get follow-up output
        follow_out = shortest_path(new_graph, method=method, directed=True)

        # Verify that the distance has changed
        self.assertNotEqual(source_out[src][dst], follow_out[src][dst])


if __name__ == "__main__":
    unittest.main()