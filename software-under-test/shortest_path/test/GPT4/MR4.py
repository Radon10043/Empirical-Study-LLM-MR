import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test4(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 4: The shortest path from a node to itself should always be zero, 
        regardless of the graph or method."""
        # Get source and follow-up output (should be the same)
        path_length = shortest_path(graph, method=method)[src][src]

        # Verification
        self.assertEqual(path_length, 0)


if __name__ == "__main__":
    unittest.main()
