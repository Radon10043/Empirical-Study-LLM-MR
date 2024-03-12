import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test5(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 5: The shortest path from a vertex to itself should always be 0."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][src]

        # Verification
        self.assertEqual(source_out, 0)


if __name__ == "__main__":
    unittest.main()
