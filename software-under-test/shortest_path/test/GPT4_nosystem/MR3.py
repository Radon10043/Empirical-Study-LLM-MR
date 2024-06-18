import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test3(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 3: If the graph is treated as undirected, the shortest path from
        source to destination should be the same as the shortest path from destination to source."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=False)[src][dst]

        # Get folllow-up output (reversing src and dst as the graph is undirected)
        follow_out = shortest_path(graph, method=method, directed=False)[dst][src]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
