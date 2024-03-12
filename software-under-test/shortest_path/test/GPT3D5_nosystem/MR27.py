import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def reverse_edge_directions(self, graph: list) -> list:
        """Reverse all edge directions in the graph.

        Parameters
        ----------
        graph : list
            The adjacency matrix of the graph

        Returns
        -------
        list
            The new graph after reversing all edge directions
        """
        n = len(graph)
        new_graph = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                if graph[i][j] != 0:
                    new_graph[j][i] = graph[i][j]
        return new_graph


    @parameterized.expand(gen_tcs_randomly(1000))
    def test27(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 27: Reversing all the edge directions in the graph should change the shortest path distances."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)

        # Reverse all edge directions in the graph
        new_graph = self.reverse_edge_directions(graph)

        # Get follow-up output
        follow_out = shortest_path(new_graph, method=method, directed=True)

        # Verify that at least one distance has changed
        self.assertNotEqual(source_out[src][dst], follow_out[src][dst])


if __name__ == '__main__':
    unittest.main()