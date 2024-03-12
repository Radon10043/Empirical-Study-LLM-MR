import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *

class TestingClass(unittest.TestCase):
    def add_weight_to_edges(self, graph: list, weight: int) -> list:
        """Add a weight to all edges in the graph.

        Parameters
        ----------
        graph : list
            The adjacency matrix of the graph
        weight : int
            The weight to add to all edges

        Returns
        -------
        list
            The new graph after adding the weight to all edges
        """
        n = len(graph)
        new_graph = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                if graph[i][j] != 0:
                    new_graph[i][j] = graph[i][j] + weight
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test14(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 14: If the graph is unweighted, adding a weight to all edges should not change the shortest path distances."""
        # Get source output
        source_out = shortest_path(graph, method=method, unweighted=True)[src][dst]

        follow_graph = self.add_weight_to_edges(graph, weight=1)

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method, unweighted=True)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()