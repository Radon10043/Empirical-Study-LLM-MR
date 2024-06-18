import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test16(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 16: In an unweighted graph, the shortest path should be at least
        as long as the absolute difference between 'src' and 'dst'."""
        # Convert to unweighted graph
        unweighted_graph = [[1 if weight > 0 else 0 for weight in row] for row in graph]

        # Get source output
        source_out = shortest_path(unweighted_graph, method=method)[src][dst]

        # Expected minimum length is the absolute difference between src and dst
        expected_min_length = abs(src - dst)

        # Verification
        self.assertGreaterEqual(source_out, expected_min_length)


if __name__ == "__main__":
    unittest.main()
