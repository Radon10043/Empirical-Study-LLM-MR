import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test40(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 40: Given the same graph, the same source and destination vertices,
        but modifying the graph to have cycles removed, the result should remain unchanged."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Remove cycles from the graph
        follow_graph = graph.copy()
        for i in range(len(follow_graph)):
            follow_graph[i][i] = 0  # Remove self-loops

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()
