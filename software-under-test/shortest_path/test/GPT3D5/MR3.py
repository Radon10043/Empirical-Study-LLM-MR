import os, sys

sys.path.append(os.path.abspath(".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test3(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 3: Given the same graph, the same source and destination vertices,
        but with a cut-off threshold for Dijkstra's algorithm, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method, limit=None)[src][dst]

        # Construct follow-up input
        follow_out = shortest_path(graph, method=method, limit=10)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
