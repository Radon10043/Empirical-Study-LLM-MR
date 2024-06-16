import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test24(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 24: Given the same graph, source, and destination vertices,
        if we apply a positive linear transformation to the edge weights, 
        the shortest path from source to destination should be scaled accordingly."""
        constant = randint(2, 100)
        intercept = randint(2, 100)

        # Get source output
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by applying a positive linear transformation to the edge weights
        follow_graph = [[x * constant + intercept for x in row] for row in graph]

        # Get follow-up output
        modified_shortest_path = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(modified_shortest_path, constant * original_shortest_path + intercept)


if __name__ == "__main__":
    unittest.main()
