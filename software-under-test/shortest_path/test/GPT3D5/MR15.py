import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test15(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 15: Given the same graph, the same source and destination vertices,
        but with the graph modified to have isolated vertices connected, the result should remain unchanged."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Modify the graph to connect isolated vertices
        follow_graph = graph.copy()
        for i in range(len(follow_graph)):
            follow_graph[i][i] = 0

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()
