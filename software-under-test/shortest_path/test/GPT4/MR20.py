import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test20(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 20: Permuting the labels of the vertices of the graph should not change 
        the distance of the shortest paths (only the vertices' identities in the path will change)."""
        graph = csr_matrix(graph)

        # Get source output for the original graph
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Create a mapping for vertex labels
        permutation = np.random.permutation(graph.shape[0])
        permuted_graph = self.permute_vertex_labels(graph, permutation)

        # Find new src and dst according to the permutation
        permuted_src = np.where(permutation == src)[0][0]
        permuted_dst = np.where(permutation == dst)[0][0]

        # Get follow-up output with permuted graph and new src, dst
        permuted_distance = shortest_path(permuted_graph, method=method)[permuted_src][permuted_dst]

        # Verification
        self.assertEqual(original_distance, permuted_distance)

    def permute_vertex_labels(self, graph, permutation):
        """Permute the labels of the vertices according to provided permutation"""
        # Apply permutation to both rows and columns of the graph
        return graph[permutation][:, permutation]

if __name__ == "__main__":
    unittest.main()
