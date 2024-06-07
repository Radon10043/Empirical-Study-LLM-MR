import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test33(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 33: For a directed graph, adding a new edge that does not create a cycle and whose weight is
        higher than the existing shortest path does not change the shortest path."""
        # Get the shortest path for the original graph
        original_distance = shortest_path(graph, method=method, directed=True)[src][dst]

        # Add a new edge with a weight greater than the original shortest path
        graph_with_new_edge = graph.copy()
        for i in range(len(graph)):
            for j in range(len(graph)):
                if i != j and graph[i][j] == 0:
                    graph_with_new_edge[i][j] = original_distance + 1
                    break

        # Get the shortest path for the graph with the new edge
        new_edge_distance = shortest_path(graph_with_new_edge, method=method, directed=True)[src][dst]

        # The distance should not change since the new edge is heavier
        self.assertEqual(original_distance, new_edge_distance)


if __name__ == "__main__":
    unittest.main()
