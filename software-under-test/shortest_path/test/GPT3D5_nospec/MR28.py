import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test28(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 28: Given the same graph, the same source and destination vertices,
        but with the weights in the graph adjusted such that all weights are scaled by a constant factor,
        the shortest path between the vertices should also be scaled by the same constant factor."""
        factor = 2

        # Get the original shortest path
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Scale the weights in the graph by the constant factor
        scaled_graph = [[edge_weight * factor for edge_weight in row] for row in graph]

        # Get the shortest path in the scaled graph
        scaled_shortest_path = shortest_path(scaled_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path * factor, scaled_shortest_path)


if __name__ == "__main__":
    unittest.main()
