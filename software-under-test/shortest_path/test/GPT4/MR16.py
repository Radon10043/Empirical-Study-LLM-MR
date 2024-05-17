import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test16(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 16: Doubling the weights of every edge in the graph should not change 
        the shortest path sequence of vertices, though the lengths will be doubled."""
        csgraph = csr_matrix(graph)

        # Double each edge weight
        doubled_csgraph = csgraph * 2
        doubled_csgraph = csr_matrix(doubled_csgraph)  # Sparse representation

        # Original shortest paths and predecessors
        original_dists, original_preds = shortest_path(csgraph, return_predecessors=True)

        # Shortest paths and predecessors after doubling
        doubled_dists, doubled_preds = shortest_path(doubled_csgraph, return_predecessors=True)

        num_vertices = original_dists.shape[0]

        # Verification
        for i in range(num_vertices):
            for j in range(num_vertices):
                # Compare the shortest path lengths
                self.assertEqual(doubled_dists[i, j], original_dists[i, j] * 2)

                # Compare the predecessor sequences
                orig_seq, double_seq = [], []

                orig_pred, double_pred = j, j
                while orig_pred != -9999 and double_pred != -9999:  # Assuming -9999 indicates no predecessor
                    orig_seq.append(orig_pred)
                    double_seq.append(double_pred)

                    orig_pred = original_preds[i, orig_pred]
                    double_pred = doubled_preds[i, double_pred]

                self.assertEqual(orig_seq, double_seq)


if __name__ == "__main__":
    unittest.main()
