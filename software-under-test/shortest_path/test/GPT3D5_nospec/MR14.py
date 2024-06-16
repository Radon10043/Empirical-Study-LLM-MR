import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test14(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 14: Given the same graph, source, and destination vertices,
        if some edge weights are set to infinity, the shortest path should not change."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input with some edge weights set to infinity
        follow_graph = [[float('inf') if (i+j) % 2 == 0 else x for j, x in enumerate(row)] for i, row in enumerate(graph)]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
