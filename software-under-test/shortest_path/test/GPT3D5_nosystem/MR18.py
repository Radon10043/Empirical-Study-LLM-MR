import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def change_edge_weights(self, graph: list, constant: int) -> list:
        """Change the weights of all edges in the graph by a constant value.

        Parameters
        ----------
        graph : list
            The adjacency matrix of the graph
        constant : int
            The constant value to add to all edge weights

        Returns
        -------
        list
            The new graph after changing the edge weights
        """
        n = len(graph)
        new_graph = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                if graph[i][j] != 0:
                    new_graph[i][j] = graph[i][j] + constant
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test18(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 18: If the graph contains negative weight edges, changing all edge weights by a constant value should not affect the shortest path distances."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)

        constant = random.randint(1, 1000)
        new_graph = self.change_edge_weights(graph, constant)

        # Get follow-up output
        follow_out = shortest_path(new_graph, method=method, directed=True)

        # Verify that all distances remain the same
        for i in range(len(source_out)):
            for j in range(len(source_out[0])):
                if i != j:
                    self.assertEqual(source_out[i][j], follow_out[i][j])


if __name__ == "__main__":
    unittest.main()
