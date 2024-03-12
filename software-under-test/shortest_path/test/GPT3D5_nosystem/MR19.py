import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def change_edge_weight_to_infinity(self, graph: list, src: int, dst: int) -> list:
        """Change the weight of the edge between node A and node B to infinity.

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
            The new graph after changing the edge weight to infinity
        """
        n = len(graph)
        new_graph = [[0] * n for _ in range(n)]
        inf = 99999
        for i in range(n):
            for j in range(n):
                if i == src and j == dst:
                    new_graph[i][j] = inf
                else:
                    new_graph[i][j] = graph[i][j]
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test19(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 19: For any two nodes A and B, changing the edge weight between node A and node B to infinity should affect the shortest path distances."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)

        # Change the weight of the edge between node A and node B to infinity
        new_graph = self.change_edge_weight_to_infinity(graph, src, dst)

        # Get follow-up output
        follow_out = shortest_path(new_graph, method=method, directed=True)

        # Verify that the distance has changed
        self.assertNotEqual(source_out[src][dst], follow_out[src][dst])


if __name__ == "__main__":
    unittest.main()
