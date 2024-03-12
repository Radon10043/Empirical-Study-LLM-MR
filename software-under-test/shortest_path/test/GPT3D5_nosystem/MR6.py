import os, sys

from random import shuffle

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def shuffle_vertices(self, graph: list) -> list:
        """Shuffle the vertices of the graph.

        Parameters
        ----------
        graph : list
            The adjacency matrix of the graph

        Returns
        -------
        list
            Implemented by Radon
        """
        n = len(graph)
        vertices = list(range(n))
        shuffle(vertices)
        new_graph = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                new_graph[vertices[i]][vertices[j]] = graph[i][j]
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test6(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 6: Reordering the vertices should not change the shortest path distances."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Shuffle the vertices
        follow_graph = self.shuffle_vertices(graph)

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
