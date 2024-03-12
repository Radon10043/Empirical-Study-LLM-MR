import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):

    def add_new_vertex(self, graph: list) -> list:
        """Add a new vertex and connecting it to all existing vertices.

        Parameters
        ----------
        graph : list
            The adjacency matrix of the graph

        Returns
        -------
        list
            Implemented by Radon
        """
        weight = randint(1, 1000)
        n = len(graph)
        for i in range(n):
            graph[i].append(weight)
        graph.append([weight] * (n + 1))
        return graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test7(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 7: Adding a new vertex and connecting it to all existing vertices
        with the same edge weight should not change the shortest path distances between the original vertices."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Add a new vertex and connect it to all existing vertices
        follow_graph = self.add_new_vertex(graph)

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
