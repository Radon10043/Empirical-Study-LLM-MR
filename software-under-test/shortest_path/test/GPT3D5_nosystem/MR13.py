import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test13(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 13: Given the same graph, the same source and destination vertices,
        if the graph is replaced with its transpose, the shortest path lengths should remain the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Get the transpose of the graph
        transposed_graph = np.transpose(graph)

        # Get follow-up output
        follow_out = shortest_path(transposed_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()