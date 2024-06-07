import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test9(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 9: The shortest path using only a subset of nodes (indices) should be
        greater or equal to the shortest path using all nodes."""
        subset_indices = [src, dst]
        # Get shortest path using all nodes
        source_out = shortest_path(graph, method=method)[src][dst]

        # Get shortest path using only a subset of nodes including src and dst
        follow_out = shortest_path(graph, method=method, indices=subset_indices)[src][dst]

        # Verification
        self.assertGreaterEqual(follow_out, source_out)


if __name__ == "__main__":
    unittest.main()
