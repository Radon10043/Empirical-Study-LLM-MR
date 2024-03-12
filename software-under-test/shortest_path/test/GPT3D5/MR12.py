import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test12(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 12: Given the same graph, the same source and destination vertices,
        but with a different scale for the edge weights, the output should have the property of monotonicity."""
        # Get source outputs
        source_out = shortest_path(graph, method=method)[src][dst]

        follow_graph = list()
        for row in graph:
            follow_graph.append([x * 2 for x in row])

        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification - Monotonicity
        self.assertTrue(source_out <= follow_out)


if __name__ == "__main__":
    unittest.main()
