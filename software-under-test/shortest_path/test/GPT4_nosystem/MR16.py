import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test16(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 16: The shortest path from any node to itself should always be zero,
        regardless of the weight or presence of any self-looping edge (i.e., edge from a node to
        itself)."""
        # Get distance matrix
        dist_matrix = shortest_path(graph, method=method)

        # Verify that each node-to-self distance is zero
        for i in range(len(graph)):
            self.assertEqual(dist_matrix[i][i], 0)


if __name__ == "__main__":
    unittest.main()
