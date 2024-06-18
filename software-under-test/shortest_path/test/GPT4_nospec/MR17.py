import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test17(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 17: Concatenating two paths should yield a longer path than either individually.
        For an unweighted graph, test a path from src to an intermediate node u, and from u to dst."""
        # Convert to unweighted graph (assuming positive weights)
        unweighted_graph = [[1 if weight > 0 else float("inf") for weight in row] for row in graph]

        for u in range(len(unweighted_graph)):
            if u != src and u != dst:
                # Get shortest path from src to u
                src_to_u = shortest_path(unweighted_graph, method=method)[src][u]

                # Get shortest path from u to dst
                u_to_dst = shortest_path(unweighted_graph, method=method)[u][dst]

                # Concatenated path length
                concatenated_path_length = src_to_u + u_to_dst

                # Get direct shortest path from src to dst
                direct_path_length = shortest_path(unweighted_graph, method=method)[src][dst]

                # The concatenated path should not be shorter than the direct path
                self.assertGreaterEqual(concatenated_path_length, direct_path_length)


if __name__ == "__main__":
    unittest.main()
