import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test32(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 32: Adding a bypass (edge from src to dst) with a weight less than the current shortest path weight should result in the bypass edge weight as the new shortest path weight."""
        # Get the current shortest path weight
        current_shortest_weight = shortest_path(graph, src=src, dst=dst, method=method)

        # Add a bypass edge directly from src to dst with a weight less than the current shortest path weight
        bypass_weight = current_shortest_weight - 1
        graph[src][dst] = bypass_weight

        # Get the new shortest path weight
        new_shortmost_weight = shortest_path(graph, src=src, dst=dst, method=method)

        # Verify that the new shortest path weight is equal to the weight of the bypass
        self.assertEqual(bypass_weight, new_shortmost_weight)


if __name__ == "__main__":
    unittest.main()
