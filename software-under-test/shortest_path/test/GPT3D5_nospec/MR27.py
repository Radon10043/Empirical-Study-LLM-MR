import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test27(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 27: Given the same graph and source and destination vertices,
        if the weights of all edges are transformed by log function, 
        the shortest path from source to destination should reflect the log transformation."""
        import math

        # Get source output
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by transforming the weights of all edges using log function
        follow_graph = [[math.log(x+1) for x in row] for row in graph]

        # Get follow-up output
        modified_shortest_path = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertAlmostEqual(modified_shortest_path, math.log(original_shortest_path+1), places=5)


if __name__ == "__main__":
    unittest.main()
