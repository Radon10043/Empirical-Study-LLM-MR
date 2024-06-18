import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test5(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 5: The shortest path from src to dst should be the same length
        as the path from dst to src in an undirected graph."""
        # Get source output for src to dst
        source_out = shortest_path(graph, method=method, directed=False)[src][dst]

        # Get follow-up output for dst to src
        follow_out = shortest_path(graph, method=method, directed=False)[dst][src]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
