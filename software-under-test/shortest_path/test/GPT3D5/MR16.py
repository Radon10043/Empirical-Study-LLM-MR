import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test16(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 16: Given the same graph, the same source and destination vertices,
        but with the graph modified to have redundant paths, the result should remain unchanged."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Modify the graph to introduce redundant paths
        follow_graph = graph.copy()
        for i in range(len(follow_graph)):
            for j in range(len(follow_graph)):
                if follow_graph[i][j] != 0:
                    follow_graph[i][j] = 1  # Introduce a path with weight 1

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()
