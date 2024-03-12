import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def reverse_edges(self, graph: list, src: int, dst: int) -> list:
        """Reverse the direction of one or more edges in the graph.

        Parameters
        ----------
        graph : list
            The adjacency matrix of the graph
        src : int
            The source vertex
        dst : int
            The destination vertex

        Returns
        -------
        list
            The new graph after reversing the direction of one or more edges
        """
        n = len(graph)
        new_graph = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                if graph[i][j] != 0:
                    new_graph[j][i] = graph[i][j]
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test15(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 15: Reversing the direction of one or more edges in the graph should change the shortest path distances."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)[src][dst]

        follow_graph = self.reverse_edges(graph, src, dst)

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method, directed=True)[src, dst]

        # Verification
        self.assertNotEqual(source_out, follow_out)


if __name__ == '__main__':
    unittest.main()