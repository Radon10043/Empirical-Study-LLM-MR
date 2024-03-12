import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def decrease_edge_weights(self, graph: list, factor: int) -> list:
        """Decreases the edge weights in the graph by the given factor."""
        new_graph = [row[:] for row in graph]
        for i in range(len(graph)):
            for j in range(len(graph[i])):
                if graph[i][j] != 0:
                    new_graph[i][j] *= factor
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test38(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 38: If all edge weights are decreased by a constant factor, the shortest path distances should also decrease by the same factor."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        decreased_weights_graph = self.decrease_edge_weights(graph, factor=0.5)

        # Get follow-up output
        follow_out = shortest_path(decreased_weights_graph, method=method)

        # Verify that the distances have decreased by a factor of 0.5
        for i in range(len(source_out)):
            for j in range(len(source_out[0])):
                if i != j:
                    self.assertEqual(source_out[i][j] * 0.5, follow_out[i][j])


if __name__ == "__main__":
    unittest.main()
