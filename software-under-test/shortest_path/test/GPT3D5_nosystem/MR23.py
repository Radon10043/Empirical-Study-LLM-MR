import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def remove_node_with_connections(self, graph: list) -> list:
        """Remove a node and its connections from the graph.

        Parameters
        ----------
        graph : list
            The adjacency matrix of the graph

        Returns
        -------
        list
            The new graph after removing a node and its connections
        """
        n = len(graph)
        new_graph = [[0] * (n - 1) for _ in range(n - 1)]
        for i in range(n - 1):
            for j in range(n - 1):
                new_graph[i][j] = graph[i][j]
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test23(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 23: If the graph represents a real-world network, removing a node and its connections should change the shortest path distances."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)

        # Remove a node and its connections
        new_graph = self.remove_node_with_connections(graph)

        # Get follow-up output
        follow_out = shortest_path(new_graph, method=method, directed=True)

        # Verify that the distance has changed
        self.assertNotEqual(source_out[src][dst], follow_out[src][dst])


if __name__ == "__main__":
    unittest.main()