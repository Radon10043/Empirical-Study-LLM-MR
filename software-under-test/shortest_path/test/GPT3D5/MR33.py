import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test33(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 33: Given the same graph, the same source and destination vertices, and the same algorithm,
        but with all weights decreased by a constant value, the resulting shortest path should remain the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Decrease all weights in the graph by a constant value
        follow_graph = [[weight - 3 for weight in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
