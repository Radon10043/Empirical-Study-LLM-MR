import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def change_edge_weights_to_absolute(self, graph: list) -> list:
        """Change the edge weights to their absolute values.

        Parameters
        ----------
        graph : list
            The adjacency matrix of the graph

        Returns
        -------
        list
            The new graph after changing the edge weights to their absolute values
        """
        n = len(graph)
        new_graph = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                if graph[i][j] != 0:
                    new_graph[i][j] = abs(graph[i][j])
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test20(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 20: If the graph contains negative weight edges, changing all edge weights to their absolute values should not affect the shortest path distances."""
        # Make surenegative weight edges are exist
        for i in range(len(graph)):
            for j in range(len(graph[0])):
                if graph[i][j] > 0:
                    graph[i][j] = -graph[i][j]

        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)

        new_graph = self.change_edge_weights_to_absolute(graph)

        # Get follow-up output
        follow_out = shortest_path(new_graph, method=method, directed=True)

        # Verify that all distances remain the same
        for i in range(len(source_out)):
            for j in range(len(source_out[0])):
                if i != j:
                    self.assertEqual(source_out[i][j], follow_out[i][j])


if __name__ == "__main__":
    unittest.main()
