import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test9(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 9: Given the same graph with different edge weights, the output follows the triangle inequality."""
        # Get source outputs
        dist_a_b = shortest_path(graph, method=method)[src][dst]
        dist_a_c = shortest_path(graph, method=method)[src][1] # Example vertex
        dist_c_b = shortest_path(graph, method=method)[1][dst] # Example vertex

        # Verification - Triangle Inequality
        self.assertTrue(dist_a_b <= dist_a_c + dist_c_b)


if __name__ == "__main__":
    unittest.main()
