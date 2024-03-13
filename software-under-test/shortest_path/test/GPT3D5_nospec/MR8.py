import scipy
import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test8(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 8: Given the same graph, the same source and destination vertices,
        but with different sources and destinations, the output should still satisfy the shortest path property."""
        # Get source output for original source and destination
        original_out = shortest_path(graph, method=method)[src][dst]

        # Get follow-up outputs for all other combinations of source and destination
        for new_src in range(len(graph)):
            for new_dst in range(len(graph)):
                if new_src != src and new_dst != dst:  # avoid the original source and destination
                    follow_out = shortest_path(graph, method=method)[new_src][new_dst]

                    # Verification
                    self.assertTrue(follow_out >= original_out)

if __name__ == "__main__":
    unittest.main()
