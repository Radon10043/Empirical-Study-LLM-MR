import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test29(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 29: Given the same graph and source and destination vertices,
        if the weights of all edges are transformed by the exponential function, 
        the shortest path from source to destination should be impacted by the exponential transformation."""
        import math

        # Get source output
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by transforming the weights of all edges using the exponential function
        follow_graph = [[math.exp(x) for x in row] for row in graph]

        # Get follow-up output
        modified_shortest_path = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertAlmostEqual(modified_shortest_path, math.exp(original_shortest_path), places=5)


if __name__ == "__main__":
    unittest.main()
