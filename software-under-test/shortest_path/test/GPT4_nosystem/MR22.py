import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test22(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 22: Applying the same permutation to the rows and columns of the
        graph (i.e., reordering the nodes) should yield a distance matrix that, when similarly
        permuted, is identical to the original shortest path matrix."""
        # Generate a permutation of node indices
        node_count = len(graph)
        permutation = np.random.permutation(node_count)

        # Apply the permutation to rows and columns of the graph
        permuted_graph = [[graph[i][j] for j in permutation] for i in permutation]

        graph = csr_matrix(graph)
        permuted_graph = csr_matrix(permuted_graph)

        # Compute original shortest path distances
        original_dist_matrix = shortest_path(graph)

        # Compute shortest path distances of the permuted graph
        permuted_dist_matrix = shortest_path(permuted_graph)

        # Apply the same permutation to the rows and columns of the result
        permuted_dist_matrix_reordered = [[permuted_dist_matrix[i][j] for j in permutation] for i in permutation]

        # Verify if the permuted distance matrix matches the original
        for i in range(node_count):
            for j in range(node_count):
                original_i, original_j = permutation[i], permutation[j]
                self.assertEqual(original_dist_matrix[original_i][original_j], permuted_dist_matrix_reordered[i][j])


if __name__ == "__main__":
    unittest.main()
