import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test29(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 29: Given the same graph and the same source and destination vertices,
        if all weights are set to 1 and unweighted=True, the output should be the same as when unweighted=False."""
        # Get source output with unweighted=False
        source_out_weighted = shortest_path(graph, method=method, unweighted=False)

        # Get source output with unweighted=True
        source_out_unweighted = shortest_path(graph, method=method, unweighted=True)

        # Verification
        np.testing.assert_almost_equal(source_out_weighted, source_out_unweighted)


if __name__ == "__main__":
    unittest.main()