import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test15(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 15: Given the same graph, the same source and destination vertices,
        but with the graph converted to its complement graph, the output should still satisfy the shortest path property."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Convert the graph to its complement graph
        complement_graph = [[0 if weight > 0 else 1 for weight in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(complement_graph, method=method)[src][dst]

        # Verification
        self.assertTrue(follow_out >= source_out)


if __name__ == "__main__":
    unittest.main()
