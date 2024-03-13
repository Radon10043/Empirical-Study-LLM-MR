import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test20(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 20: Given the same graph, the same source and destination vertices, 
        and a subset of edges flipped (i.e., changing the direction), the output should still satisfy the shortest path property."""
        # Create a graph with a subset of edges flipped
        flipped_graph = [[graph[j][i] for j in range(len(graph))] for i in range(len(graph))]

        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Get follow-up output
        follow_out = shortest_path(flipped_graph, method=method)[src][dst]

        # Verification
        self.assertTrue(follow_out >= source_out)


if __name__ == "__main__":
    unittest.main()
