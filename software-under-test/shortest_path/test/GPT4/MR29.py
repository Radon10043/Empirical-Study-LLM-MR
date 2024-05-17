import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test29(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 29: Removing an edge with an infinite weight (or a very large weight if infinity is 
        not used) should not change the shortest path lengths, as these edges are effectively non-edges."""
        csgraph = csr_matrix(graph)

        # Assume an edge with infinite weight exists in the graph
        i, j = find_infinite_weight_edge(csgraph)  # Assuming this function exists

        # Compute shortest paths before edge removal
        original_paths = shortest_path(csgraph)

        # Remove the edge by setting the weight to 0 or removing from the sparse matrix
        modified_csgraph = csgraph.copy()
        modified_csgraph[i, j] = 0
        modified_csgraph.eliminate_zeros()  # Removes zero entries from the sparse matrix

        # Compute shortest paths after edge removal
        modified_paths = shortest_path(modified_csgraph)

        # Verify shortest paths remain unchanged after removal of the infinite-weight edge
        np.testing.assert_array_equal(original_paths, modified_paths)


if __name__ == "__main__":
    unittest.main()
