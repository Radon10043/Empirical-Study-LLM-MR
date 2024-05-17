import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test23(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 23: Applying the same random permutation to the rows and columns of the graph
        adjacency matrix should not affect the shortest path lengths."""
        seed = 100
        csgraph = csr_matrix(graph)

        rng = np.random.default_rng(seed)  # Ensures reproducibility
        num_vertices = csgraph.shape[0]
        permutation = rng.permutation(num_vertices)

        # Apply the permutation to the rows and columns of the csgraph
        permuted_csgraph = csgraph[permutation, :][:, permutation]

        # Get the shortest path lengths for the original and permuted graphs
        original_path_lengths = shortest_path(csgraph)
        permuted_path_lengths = shortest_path(permuted_csgraph)

        # Verification: The permuted shortest path lengths should match the original
        for i in range(num_vertices):
            for j in range(num_vertices):
                self.assertEqual(original_path_lengths[i, j], permuted_path_lengths[permutation[i], permutation[j]])


if __name__ == "__main__":
    unittest.main()
