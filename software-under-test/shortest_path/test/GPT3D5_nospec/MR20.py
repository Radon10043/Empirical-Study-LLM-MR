import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test20(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 20: Given the same graph, source, and destination vertices,
        if the weights on the edges in a specific path are multiplied by a positive constant k, 
        the shortest path from source to destination should be multiplied by the same constant."""
        k = 3

        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by multiplying the weights on the edges in a specific path by a positive constant k
        follow_graph = [[x * k for x in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(follow_out, k * source_out)


if __name__ == "__main__":
    unittest.main()
