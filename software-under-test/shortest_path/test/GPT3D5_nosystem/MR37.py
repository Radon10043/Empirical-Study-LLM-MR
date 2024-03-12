import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def multiply_edge_weights(self, graph: list, factor: int) -> list:
        """Multiplies the edge weights in the graph by the given factor."""
        new_graph = [row[:] for row in graph]
        for i in range(len(graph)):
            for j in range(len(graph[i])):
                if graph[i][j] != 0:
                    new_graph[i][j] *= factor
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test37(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 37: Multiplying the edge weights between all nodes by a constant factor should result in the squared distances between the nodes increasing by the square of the constant."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        increased_weights_graph = self.multiply_edge_weights(graph, factor=2)

        # Get follow-up output
        follow_out = shortest_path(increased_weights_graph, method=method)

        # Verify that the squared distances have increased by the square of 2
        for i in range(len(source_out)):
            for j in range(len(source_out[0])):
                if i != j:
                    self.assertEqual(source_out[i][j]**2 * 4, follow_out[i][j]**2)


if __name__ == "__main__":
    unittest.main()