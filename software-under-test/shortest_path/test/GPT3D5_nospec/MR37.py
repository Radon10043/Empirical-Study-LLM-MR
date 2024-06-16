import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test37(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 37: Given the same graph, source and destination vertices,
        if we square the weights of all edges and then take the square root of the resulting weights, 
        the shortest path remains the same as the original shortest path."""
        import math

        # Get source output
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by applying the square root to the squared edge weights
        squared_weights_graph = [[x**2 for x in row] for row in graph]
        follow_graph = [[math.sqrt(x) for x in row] for row in squared_weights_graph]

        # Get follow-up output
        modified_shortest_path = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(modified_shortest_path, original_shortest_path)


if __name__ == "__main__":
    unittest.main()
