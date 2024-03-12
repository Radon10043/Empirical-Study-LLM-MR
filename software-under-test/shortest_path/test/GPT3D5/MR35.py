import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test35(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 35: Given the same graph, the same source and destination vertices, but with a single edge removed, 
        the shortest path length should either remain the same or be greater."""
        # Get the original shortest path length
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Remove a single edge
        follow_graph = [row[:] for row in graph]
        follow_graph[0][1] = 9999  # Remove the edge (0, 1)

        # Get the new shortest path length
        new_distance = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertGreaterEqual(new_distance, original_distance)


if __name__ == "__main__":
    unittest.main()
