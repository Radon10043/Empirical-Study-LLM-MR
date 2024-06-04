import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test19(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 19: Given the same graph, the same source and destination vertices,
        but duplicate edges added with the weight equal to the sum of the original edge weight and the added edge weight, 
        the result should remain unchanged or path may be shorter."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Add duplicate edges with the weight equal to the sum of the original edge weight and the added edge weight
        follow_graph = graph.copy()
        follow_graph[src][dst] = graph[src][dst] + 2
        follow_graph[dst][src] = graph[dst][src] + 2

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out) or np.all(follow_out <= source_out))


if __name__ == "__main__":
    unittest.main()
