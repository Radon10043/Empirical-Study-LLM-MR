import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test25(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 25: Given the same graph, the same source and destination vertices, 
        if an edge is disconnected in the follow-up graph, the shortest path should change."""
        modified_graph = [row[:] for row in graph]
        modified_graph[src][dst] = float('inf')  # Disconnecting an edge

        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Get follow-up output
        follow_out = shortest_path(modified_graph, method=method)[src][dst]

        # Verification
        self.assertNotEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
