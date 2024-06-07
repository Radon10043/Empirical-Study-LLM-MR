import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test28(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 28: Removing the highest weight edge from the graph does not decrease
        the shortest path distance, unless the edge is part of the only shortest path."""
        # Get source output for the original graph
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Find the edge with the highest weight that is not a self-loop
        max_weight_edge = 0
        for i in range(len(graph)):
            for j in range(len(graph)):
                if i != j:
                    max_weight_edge = max(max_weight_edge, graph[i][j])
                    break

        # Remove the highest weight edge
        graph_without_max_edge = graph.copy()
        for i in range(len(graph)):
            for j in range(len(graph)):
                if graph[i][j] == max_weight_edge:
                    graph_without_max_edge[i][j] = 0

        # Get follow-up output after removing the highest weight edge
        new_distance = shortest_path(graph_without_max_edge, method=method)[src][dst]

        # Verification
        self.assertGreaterEqual(new_distance, original_distance)


if __name__ == "__main__":
    unittest.main()
