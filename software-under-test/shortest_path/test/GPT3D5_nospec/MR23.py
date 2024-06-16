import random
import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test23(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 23: Given the same graph, source, and destination vertices,
        if every edge weight is multiplied by a constant and additional constant weight is added to all edges,
        the shortest path should also include the effect of these transformations."""
        # Get source output
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by multiplying every edge weight and then adding a constant weight to all edges
        constant_multiplier = 2
        additional_constant = 10
        follow_graph = [[x * constant_multiplier + additional_constant for x in row] for row in graph]

        # Get follow-up output
        modified_shortest_path = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path * constant_multiplier + additional_constant, modified_shortest_path)


if __name__ == "__main__":
    unittest.main()
