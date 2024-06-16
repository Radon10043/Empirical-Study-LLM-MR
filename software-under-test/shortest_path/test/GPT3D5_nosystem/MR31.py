import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test31(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 31: Given the same graph, the same source and destination vertices, and method='auto',
        the result when using specific algorithm Dijkstra should be the same as using the 'auto' method."""
        graph = csr_matrix(graph)

        # Get source output when using the 'auto' method
        source_out_auto = shortest_path(graph, method="auto")

        # Get source output using Dijkstra
        source_out_dijkstra = shortest_path(graph, method="D")

        # Verification
        np.testing.assert_almost_equal(source_out_auto, source_out_dijkstra)


if __name__ == "__main__":
    unittest.main()
