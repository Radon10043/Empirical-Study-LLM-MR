import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test27(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 27: Given the same graph and the same source and destination vertices,
        if we negate all edge weights in the graph, the shortest path length should remain unchanged."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Create a new graph with negated edge weights
        negated_graph = [[x * -1 for x in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(negated_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == '__main__':
    unittest.main()