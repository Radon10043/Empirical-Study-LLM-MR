import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test41(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 41: Given the same graph, the same source and destination vertices,
        but modifying the graph to have multiple paths between the same pair of vertices, the result should remain unchanged."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Add multiple paths between the same pair of vertices
        follow_graph = graph.copy()
        follow_graph[src][dst] = follow_graph[dst][src] = 1  # Add a direct path between src and dst

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()
