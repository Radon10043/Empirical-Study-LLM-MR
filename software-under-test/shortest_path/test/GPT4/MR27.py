import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test27(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 27: If the graph is updated so that the weight of a particular edge
        is reduced (and the edge is already part of some shortest paths), the lengths of those paths
        should be reduced correspondingly, or other shorter paths may emerge."""
        csgraph = csr_matrix(graph)

        # Find an edge that is part of a shortest path
        dist_matrix, predecessors = shortest_path(csgraph, return_predecessors=True)
        path = get_shortest_path(predecessors, src, dst)
        u, v = path[0], path[1]

        # Create a new csgraph with the selected edge weight reduced
        modified_csgraph = csgraph.copy()
        old_weight = modified_csgraph[u, v]
        new_weight = old_weight / 2  # Reduced weight
        modified_csgraph[u, v] = new_weight
        modified_csgraph[v, u] = new_weight  # For undirected graphs

        # Get new shortest path lengths
        modified_dist_matrix = shortest_path(modified_csgraph)

        # Check that the shortest paths have not increased
        np.testing.assert_array_less(modified_dist_matrix[src][dst], dist_matrix[src][dst])


if __name__ == "__main__":
    unittest.main()
