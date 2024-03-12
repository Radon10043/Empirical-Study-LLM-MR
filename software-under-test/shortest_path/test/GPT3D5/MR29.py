import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test29(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 29: Given the same graph, the same source and destination vertices, reversing the direction of all edges 
        should maintain the shortest path."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Reverse the direction of all edges
        reversed_graph = [row[::-1] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(reversed_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
