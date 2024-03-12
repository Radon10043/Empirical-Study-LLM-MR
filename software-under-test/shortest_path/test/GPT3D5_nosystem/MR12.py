import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test12(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 12: For any two nodes, the shortest path from node A to node B passing through an intermediate node C should be greater than or equal to the shortest path from node A to C plus the shortest path from C to B."""
        dist_matrix, predecessors = shortest_path_A_to_B = shortest_path(graph, method=method, directed=False, return_predecessors=True)
        path = get_shortest_path(predecessors, src, dst)
        intermediate = random.choice(path)
        shortest_path_A_to_B = dist_matrix[src][dst]

        # Get source output
        shortest_path_A_to_C = shortest_path(graph, method=method, directed=False)[src][intermediate]
        shortest_path_C_to_B = shortest_path(graph, method=method, directed=False)[intermediate][dst]

        # Verification
        self.assertGreaterEqual(shortest_path_A_to_B, shortest_path_A_to_C + shortest_path_C_to_B)


if __name__ == "__main__":
    unittest.main()