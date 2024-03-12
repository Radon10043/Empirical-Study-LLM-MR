import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def get_transpose(self, graph: list) -> list:
        """Get the transpose of the graph.

        Parameters
        ----------
        graph : list
            The adjacency matrix of the graph

        Returns
        -------
        list
            The transpose of the graph
        """
        n = len(graph)
        transposed_graph = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                transposed_graph[i][j] = graph[j][i]
        return transposed_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test28(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 28: Converting the graph to its transpose should not change the shortest path distances."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)

        # Get the transpose of the graph
        transposed_graph = self.get_transpose(graph)

        # Get follow-up output
        follow_out = shortest_path(transposed_graph, method=method, directed=True)

        # Verify that all distances remain the same
        for i in range(len(source_out)):
            for j in range(len(source_out[0])):
                if i != j:
                    self.assertEqual(source_out[i][j], follow_out[i][j])


if __name__ == "__main__":
    unittest.main()
