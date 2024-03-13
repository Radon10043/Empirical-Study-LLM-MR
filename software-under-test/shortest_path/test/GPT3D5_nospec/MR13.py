import random
import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test13(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 13: Given the same graph, the same source and destination vertices,
        but with a subset of edges removed, the output should still satisfy the shortest path property."""
        
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Remove a subset of edges from the graph
        num_edges_to_remove = len(graph) // 2
        edges_to_remove = random.sample(range(len(graph)), num_edges_to_remove)
        filtered_graph = [row[:] for row in graph]
        for i in edges_to_remove:
            filtered_graph[i] = [float('inf')] * len(graph)

        # Get follow-up output
        follow_out = shortest_path(filtered_graph, method=method)[src][dst]

        # Verification
        self.assertTrue(follow_out >= source_out)


if __name__ == "__main__":
    unittest.main()
