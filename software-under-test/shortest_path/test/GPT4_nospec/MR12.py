import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test12(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 12: Concatenating a path from src to an intermediate node 'n'
        and a path from 'n' to dst should always be longer or equal to the direct shortest path from src to dst."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        for n in range(len(graph)):
            # Avoid using the same src, dst or a nonexistent node
            if n != src and n != dst:
                # Get the shortest paths
                src_to_n = shortest_path(graph, method=method)[src][n]
                n_to_dst = shortest_path(graph, method=method)[n][dst]

                # Concatenate the paths and check if the result is longer
                concatenated_path_length = src_to_n + n_to_dst
                self.assertGreaterEqual(concatenated_path_length, source_out)


if __name__ == "__main__":
    unittest.main()
