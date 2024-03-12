import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def remove_loops(self, graph: list) -> list:
        """Remove loops from the graph.

        Parameters
        ----------
        graph : list
            The adjacency matrix of the graph

        Returns
        -------
        list
            The new graph after removing loops
        """
        n = len(graph)
        new_graph = [row[:] for row in graph]
        for i in range(n):
            new_graph[i][i] = 0
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test26(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 26: For a graph with loops, removing the loops should not change the shortest path distances."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)

        # Remove loops from the graph
        new_graph = self.remove_loops(graph)

        # Get follow-up output
        follow_out = shortest_path(new_graph, method=method, directed=True)

        # Verify that all distances remain the same
        for i in range(len(source_out)):
            for j in range(len(source_out[0])):
                if i != j:
                    self.assertEqual(source_out[i][j], follow_out[i][j])


if __name__ == "__main__":
    unittest.main()