import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test39(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 39: Given the same graph, the same source and destination vertices,
        but removing specific edges, the result should remain unchanged or path may be longer."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Remove specific edges from the graph
        follow_graph = graph.copy()
        follow_graph[src][dst] = 0
        follow_graph[dst][src] = 0

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out) or np.all(follow_out >= source_out))


if __name__ == "__main__":
    unittest.main()
