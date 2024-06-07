import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test6(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 6: For an undirected graph, the shortest path from node A to B
        is the same as from B to A."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=False)[src][dst]

        # Get follow-up output (reverse query)
        follow_out = shortest_path(graph, method=method, directed=False)[dst][src]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
