import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test21(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 21:  For a symmetric (undirected) graph, doubling the weight of all edges should
        keep the same shortest path, with doubled path length."""
        indices = [0, 1]
        csgraph = csr_matrix(graph)

        # Double the weight of all edges
        modified_csgraph = csgraph.copy()
        modified_csgraph.data *= 2

        # Get the shortest paths for the original and modified graphs
        original_path_lengths = shortest_path(csgraph, indices=indices)
        modified_path_lengths = shortest_path(modified_csgraph, indices=indices)

        # Verification: The modified shortest path lengths should be double the original lengths
        np.testing.assert_allclose(original_path_lengths * 2, modified_path_lengths)


if __name__ == "__main__":
    unittest.main()
