import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test14(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 14: Given the same graph, the same source and destination vertices,
        but with the graph modified to have a single vertex removed, the result should remain unchanged or the path may be longer."""
        if src == len(graph) - 1 or dst == len(graph) - 1:
            self.skipTest("Source or destination is the removed vertex")

        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Remove a vertex from the graph
        follow_graph = graph[:-1]
        for i in range(len(follow_graph)):
            follow_graph[i] = follow_graph[i][:-1]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out) or np.all(follow_out >= source_out))


if __name__ == "__main__":
    unittest.main()
