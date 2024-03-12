import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *

class TestingClass(unittest.TestCase):
    def add_isolated_node(self, graph: list) -> list:
        """Add a new node without connections to the graph.

        Parameters
        ----------
        graph : list
            The adjacency matrix of the graph

        Returns
        -------
        list
            The new graph after adding a new node without connections
        """
        n = len(graph)
        new_graph = [[0] * (n + 1) for _ in range(n + 1)]
        inf = 99999
        for i in range(n + 1):
            for j in range(n + 1):
                if i < n and j < n:
                    new_graph[i][j] = graph[i][j]
                else:
                    new_graph[i][j] = inf
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test32(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 32: Adding a new node without connections to existing nodes should not change the shortest path distances."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)

        new_graph = self.add_isolated_node(graph)

        # Get follow-up output
        follow_out = shortest_path(new_graph, method=method, directed=True)

        # Verify that all distances remain the same
        for i in range(len(source_out)):
            for j in range(len(source_out[0])):
                if i != j:
                    self.assertEqual(source_out[i][j], follow_out[i][j])


if __name__ == "__main__":
    unittest.main()