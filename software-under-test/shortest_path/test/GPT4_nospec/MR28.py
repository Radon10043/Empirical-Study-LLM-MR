import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test28(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 28: Removing all edges with weight greater than the current shortest path length should not
        change the shortest path between src and dst."""
        # Get the current shortest path weight
        shortest_path_cost = shortest_path(graph, method=method)[src][dst]

        # Remove all edges with a weight greater than the current shortest path length
        trimmed_graph = [[weight if weight <= shortest_path_cost else float("inf") for weight in row] for row in graph]

        # Verify the shortest path cost remains the same after the edge removal
        trimmed_shortest_path_cost = shortest_path(trimmed_graph, method=method)[src][dst]
        self.assertEqual(shortest_path_cost, trimmed_shortest_path_cost)


if __name__ == "__main__":
    unittest.main()
