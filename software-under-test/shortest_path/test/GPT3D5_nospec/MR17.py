import random
import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test17(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 17: Given the same graph, the same source and destination vertices, 
        but with the source and destination vertices replaced with intermediate vertices, 
        the output should still satisfy the shortest path property."""
        # Get the intermediate node
        num_nodes = len(graph)
        mid_vertex = random.randint(0, num_nodes - 1)

        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Get follow-up output with the intermediate vertex
        follow_out = shortest_path(graph, method=method)[src][mid_vertex] + shortest_path(graph, method=method)[mid_vertex][dst]

        # Verification
        self.assertTrue(follow_out >= source_out)


if __name__ == "__main__":
    unittest.main()
