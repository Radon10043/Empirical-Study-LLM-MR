import os, sys

import scipy.sparse

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test36(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 36: The shortest path from a node to itself should always be zero, regardless of 
        the graph, its weights, and whether it is directed or not."""
        # Calculate shortest path from a node to itself
        zero_distance = shortest_path(graph, method=method, directed=True)[src][src]

        # Verification
        self.assertEqual(zero_distance, 0)


if __name__ == "__main__":
    unittest.main()
