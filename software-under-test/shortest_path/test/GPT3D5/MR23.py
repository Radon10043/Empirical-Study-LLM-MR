import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test23(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 23: Given the same graph, the same source and destination vertices,
        but with one intermediate vertex removed, the result should remain unchanged or path may be longer."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Remove one intermediate vertex from the graph
        intermediate_vertex = 1

        if intermediate_vertex == src or intermediate_vertex == dst:
            self.skipTest("Intermediate vertex is the source or destination")

        follow_graph = graph.copy()
        for i in range(len(graph)):
            follow_graph[i][intermediate_vertex] = 0
            follow_graph[intermediate_vertex][i] = 0

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertGreaterEqual(follow_out, source_out)


if __name__ == "__main__":
    unittest.main()
