import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test35(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 35: Concatenation of two shortest paths from node A to B and B to C,
        should always be greater than or equal to the direct shortest path from A to C."""
        # Compute shortest path distances
        dist_matrix = shortest_path(graph)

        node_count = len(graph)
        for a in range(node_count):
            for b in range(node_count):
                for c in range(node_count):
                    if a != b and b != c and a != c:
                        concatenated_path_dist = dist_matrix[a][b] + dist_matrix[b][c]
                        direct_path_dist = dist_matrix[a][c]
                        self.assertLessEqual(direct_path_dist, concatenated_path_dist)


if __name__ == "__main__":
    unittest.main()
