import os, sys

import scipy.sparse

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test36(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 36: Adding a new vertex that does not offer a shortcut for any existing paths
        should not change the shortest paths between the existing vertices.
        """
        original_csgraph = csr_matrix(graph)

        # Assume new_vertex_edges is a list of weights from the new vertex to all existing vertices,
        # and it is guaranteed not to provide any shortcuts.
        num_vertices = original_csgraph.shape[0]

        # Create an extended graph with one additional vertex
        extended_csgraph = scipy.sparse.lil_matrix((num_vertices+1, num_vertices+1))
        extended_csgraph[:num_vertices, :num_vertices] = original_csgraph
        extended_csgraph[-1, :] = new_vertex_edges
        extended_csgraph[:, -1] = new_vertex_edges
        extended_csgraph = extended_csgraph.tocsr()

        # Get the shortest paths from the original graph
        original_distances = shortest_path(original_csgraph)
        # Get the shortest paths from the extended graph
        extended_distances = shortest_path(extended_csgraph)

        # Shortest path distances among original nodes should remain unchanged
        np.testing.assert_array_almost_equal(
            original_distances, 
            extended_distances[:num_vertices, :num_vertices]
        )


if __name__ == "__main__":
    unittest.main()
