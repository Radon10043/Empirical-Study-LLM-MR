import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test39(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 39: Given the same graph, source, and destination vertices,
        if all edge weights are multiplied by 0, the shortest path should be 0 for all vertices."""
        # Get source output
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by multiplying all edge weights by 0
        zero_weight_graph = [[0 for _ in row] for row in graph]

        # Get follow-up output
        modified_shortest_path = shortest_path(zero_weight_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(modified_shortest_path, 0)


if __name__ == "__main__":
    unittest.main()
