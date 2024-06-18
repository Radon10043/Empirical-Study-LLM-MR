import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test11(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 11: The shortest path from src to src should always have a length of 0."""
        # Verification
        self.assertEqual(shortest_path(graph, method=method)[src][src], 0)


if __name__ == "__main__":
    unittest.main()
