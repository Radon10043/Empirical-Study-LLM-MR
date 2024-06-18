import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test28(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 28: If every edge weight in a graph is increased by the same constant
        amount, the order and structure of the shortest paths should remain unchanged."""
        # Increase the weight of every edge by a constant
        constant_increase = 10
        increased_weight_graph = [[x + constant_increase if x > 0 else 0 for x in row] for row in graph]

        # Get original shortest paths
        _, source_pred = shortest_path(graph, method=method, return_predecessors=True)

        # Get shortest paths after increasing edge weights
        _, follow_pred = shortest_path(increased_weight_graph, method=method, return_predecessors=True)

        # Verify that the path structure remains unchanged
        original_paths = get_shortest_path(source_pred, src, dst)
        increased_paths = get_shortest_path(follow_pred, src, dst)
        self.assertEqual(original_paths, increased_paths)


if __name__ == "__main__":
    unittest.main()
