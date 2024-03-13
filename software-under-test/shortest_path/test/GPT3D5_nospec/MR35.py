import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test35(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 35: Given the same graph and vertices, if the edge weights are sorted in non-decreasing order, 
        the shortest path should not change."""
        # Get the original shortest path
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Sort the edge weights in non-decreasing order
        sorted_graph = [sorted(row) for row in graph]

        # Get the shortest path in the sorted graph
        sorted_shortest_path = shortest_path(sorted_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path, sorted_shortest_path)


if __name__ == "__main__":
    unittest.main()
