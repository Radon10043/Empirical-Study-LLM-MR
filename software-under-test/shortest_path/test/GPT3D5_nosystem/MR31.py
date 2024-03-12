import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def add_constant_to_edge_weights(self, graph: list, constant: int) -> list:
        """Add a constant to all edge weights in the graph.

        Parameters
        ----------
        graph : list
            The adjacency matrix of the graph
        constant : int
            The constant to be added to all edge weights

        Returns
        -------
        list
            The new graph after adding the constant to all edge weights
        """
        n = len(graph)
        new_graph = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                if graph[i][j] != 0:
                    new_graph[i][j] = graph[i][j] + constant
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test31(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 31: If the graph contains negative weight edges, adding a constant to all edge weights should not change the shortest path distances."""
        # Make sure the graph contains negative weight edges
        for i in range(len(graph)):
            for j in range(len(graph[0])):
                if random.random() < 0.5:
                    graph[i][j] = -graph[i][j]

        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)

        new_graph = self.add_constant_to_edge_weights(graph, constant=5)

        # Get follow-up output
        follow_out = shortest_path(new_graph, method=method, directed=True)

        # Verify that all distances remain the same
        for i in range(len(source_out)):
            for j in range(len(source_out[0])):
                if i != j:
                    self.assertEqual(source_out[i][j], follow_out[i][j])


if __name__ == '__main__':
    unittest.main()