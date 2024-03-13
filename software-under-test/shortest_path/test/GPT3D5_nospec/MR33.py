import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test33(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 33: Given the same graph and vertices, if a new edge with a weight greater than the shortest 
        path weight is added, the shortest path should remain unchanged."""
        # Get the original shortest path
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Add a new edge with weight greater than the shortest path weight
        modified_graph = [row[:] for row in graph]
        modified_graph[src][dst] = original_shortest_path + 1

        # Get the shortest path in the modified graph
        modified_shortest_path = shortest_path(modified_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path, modified_shortest_path)


if __name__ == "__main__":
    unittest.main()
