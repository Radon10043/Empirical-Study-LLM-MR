import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test21(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 21: Adding an edge with a higher weight than the existing shortest path
        should not change the shortest path."""
        # Get the current shortest path and weight
        shortest_path_cost = shortest_path(graph, method=method)[src][dst]

        # Find the maximum edge weight in the current shortest path
        max_edge_weight = 0
        for i in range(len(graph)):
            for j in range(len(graph[0])):
                if graph[i][j] > max_edge_weight:
                    max_edge_weight = graph[i][j]

        # Add an edge with a higher weight than the maximum edge weight in the shortest path
        new_high_weight = max_edge_weight * 2

        for i in range(len(graph)):
            for j in range(len(graph[0])):
                if i != j and graph[i][j] == 0:
                    graph[i][j] = new_high_weight
                    break

        # Get the new shortest path and weight
        new_path_cost = shortest_path(graph, method=method)[src][dst]

        # The shortest path should remain unaffected
        self.assertEqual(shortest_path_cost, new_path_cost)


if __name__ == "__main__":
    unittest.main()
