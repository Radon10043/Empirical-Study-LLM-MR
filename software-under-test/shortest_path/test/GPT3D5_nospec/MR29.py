import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test29(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 29: Given the same graph and vertices, the order of the vertices in the input should not affect the shortest path."""
        # Get the original shortest path
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Get the shortest path with the vertices swapped
        swapped_shortest_path = shortest_path(graph, method=method)[dst][src]

        # Verification
        self.assertEqual(original_shortest_path, swapped_shortest_path)


if __name__ == "__main__":
    unittest.main()
