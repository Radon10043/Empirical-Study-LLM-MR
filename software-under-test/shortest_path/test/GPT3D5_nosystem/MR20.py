import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test20(self, graph: list, src: int, dst: int, method: str): # Fixed
        """ Metamorphic Relation 20: Given the same graph and the same source and destination vertices, 
        and with method='auto', the result should be the same as when using a specific algorithm."""
        graph = csr_matrix(graph)

        # Get source output with method='auto'
        source_out_auto = shortest_path(graph, method='auto')

        # Get source output with a specific algorithm
        source_out_specific = shortest_path(graph, method=method)

        # Verification
        np.testing.assert_almost_equal(source_out_auto, source_out_specific)


if __name__ == "__main__":
    unittest.main()
