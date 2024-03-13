import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test37(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 37: Given the same graph and vertices, if the weights of all edges are replaced with their absolute values,
        the shortest path should remain the same."""
        # Get the original shortest path
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Replace the weights of all edges with their absolute values
        abs_graph = [[abs(weight) for weight in row] for row in graph]

        # Get the shortest path in the absolute graph
        abs_shortest_path = shortest_path(abs_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path, abs_shortest_path)


if __name__ == "__main__":
    unittest.main()
