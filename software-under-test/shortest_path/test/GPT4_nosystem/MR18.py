import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test18(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 18: Replacing all non-zero weights with 1 in a weighted graph
        should not affect the order of the shortest paths when using unweighted computation."""
        # Convert all non-zero edge weights to 1
        unweighted_graph = [[1 if x != 0 else 0 for x in row] for row in graph]

        # Get original distances with weighted computation
        weighted_distances = shortest_path(graph, method=method, unweighted=False)

        # Get distances using unweighted computation on the modified graph
        unweighted_distances = shortest_path(unweighted_graph, method=method, unweighted=True)

        # Verify that the order of paths is preserved
        for src in range(len(graph)):
            shortest_path_order_weighted = sorted(range(len(graph)), key=lambda dst: weighted_distances[src][dst])
            shortest_path_order_unweighted = sorted(range(len(graph)), key=lambda dst: unweighted_distances[src][dst])
            self.assertEqual(shortest_path_order_weighted, shortest_path_order_unweighted)


if __name__ == "__main__":
    unittest.main()
