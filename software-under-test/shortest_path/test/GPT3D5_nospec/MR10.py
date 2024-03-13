import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test10(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 10: Given the same graph, the same source and destination vertices,
        but with an additional edge added to the graph, the output should still satisfy the shortest path property."""
        modified_graph = [row[:] for row in graph]
        modified_graph[src][dst] = 1  # adding an additional edge

        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Get follow-up output
        follow_out = shortest_path(modified_graph, method=method)[src][dst]

        # Verification
        self.assertTrue(follow_out >= source_out)


if __name__ == "__main__":
    unittest.main()
