import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test12(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 12: Given the same graph, the same source and destination vertices,
        but with the edge weights rounded to the nearest integer, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Round the edge weights in the graph to the nearest integer
        rounded_graph = [[round(weight) for weight in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(rounded_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
