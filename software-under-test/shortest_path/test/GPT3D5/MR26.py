import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test26(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 26: Given the same graph and vertices, the output of the shortest path should remain the same if
        the same graph is represented using different sparse matrix formats."""
        from scipy.sparse import csr_matrix, csc_matrix
        import numpy as np

        # Create a csr_matrix from the original graph
        csr_graph = csr_matrix(np.array(graph))

        # Get source output using csr_matrix
        source_out_csr = shortest_path(csr_graph, method=method)[src][dst]

        # Create a csc_matrix from the original graph
        csc_graph = csc_matrix(np.array(graph))

        # Get follow-up output using csc_matrix
        follow_out_csc = shortest_path(csc_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out_csr, follow_out_csc)


if __name__ == "__main__":
    unittest.main()
