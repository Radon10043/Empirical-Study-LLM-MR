import os, sys

import scipy as sp

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test41(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 41: Concatenating identical graphs along the diagonal (creating a block diagonal matrix)
        should result in shortest paths within each block that are identical to those of the original graph."""
        original_csgraph = csr_matrix(graph)

        # Concatenate the original graph with itself along the diagonal (creating a block diagonal matrix)
        block_diag_csgraph = sp.sparse.block_diag([original_csgraph, original_csgraph])

        # Calculate shortest paths within each block
        original_paths = shortest_path(original_csgraph)
        block_diag_paths = shortest_path(block_diag_csgraph)

        # Check that the shortest paths within each block are the same as the original
        num_vertices = original_csgraph.shape[0]
        np.testing.assert_array_equal(original_paths, block_diag_paths[:num_vertices, :num_vertices])
        np.testing.assert_array_equal(original_paths, block_diag_paths[num_vertices:, num_vertices:])


if __name__ == "__main__":
    unittest.main()
