import random
import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test17(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 17: Given the same graph, source, and destination vertices,
        if the graph is modified by removing certain vertices and their associated edges, 
        the shortest path should remain the same."""
        n = len(graph)
        if src ==  n - 1 or dst == n - 1:
            self.skipTest("Skip test where source or destination is the removed vertex")

        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by removing certain vertices and their associated edges
        follow_graph = graph.copy()
        follow_graph.pop(n - 1)
        for i in range(n - 1):
            follow_graph[i] = follow_graph[i][:n - 1]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
