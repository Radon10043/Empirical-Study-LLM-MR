import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test35(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 35: Given the same graph, source and destination vertices,
        if we reverse all the edge weights and also reverse the graph structure,
        the shortest path should remain the same."""
        # Get source output
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by reversing all the edge weights and the graph structure
        reversed_weights_graph = [[-x for x in row] for row in graph]
        reversed_graph = [row[::-1] for row in reversed_weights_graph]

        # Get follow-up output
        modified_shortest_path = shortest_path(reversed_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path, modified_shortest_path)


if __name__ == "__main__":
    unittest.main()
