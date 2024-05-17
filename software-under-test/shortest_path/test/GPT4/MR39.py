import os, sys

import scipy as sp

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test39(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 39: Removing a node that is not part of any shortest paths should not affect the shortest paths
        between the remaining nodes."""
        original_csgraph = csr_matrix(graph)

        # Select a node that is not part of any shortest paths
        node_to_remove = find_non_critical_node(original_csgraph)

        # Remove the selected node from the graph
        reduced_csgraph = sp.sparse.lil_matrix((original_csgraph.shape[0] - 1, original_csgraph.shape[1] - 1))
        reduced_csgraph[:, :] = np.delete(np.delete(original_csgraph.toarray(), node_to_remove, axis=0), node_to_remove, axis=1)
        reduced_csgraph = reduced_csgraph.tocsr()

        # Compute shortest paths before and after removal of the node
        original_paths = shortest_path(original_csgraph)
        reduced_paths = shortest_path(reduced_csgraph)

        # Reconstruct the original matrix without the removed node for comparison
        original_paths_reduced = np.delete(np.delete(original_paths, node_to_remove, axis=0), node_to_remove, axis=1)

        # Verify that the shortest paths remain unchanged after the removal of the non-critical node
        np.testing.assert_array_equal(reduced_paths, original_paths_reduced)


if __name__ == "__main__":
    unittest.main()
