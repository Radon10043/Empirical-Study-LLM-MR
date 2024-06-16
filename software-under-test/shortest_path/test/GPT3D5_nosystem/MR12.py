import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test12(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 12: Given the same graph and the same source and destination vertices, 
        the shortest path results should remain the same when the graph is represented using different sparse matrix formats."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Convert the graph to a different sparse matrix format
        converted_graph = csr_matrix(graph)

        # Get follow-up output
        follow_out = shortest_path(converted_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()