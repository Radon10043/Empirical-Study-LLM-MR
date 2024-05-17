import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test24(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 24: Adding an edge with an extremely high weight between two nodes should not 
        change the shortest path between them."""
        csgraph = csr_matrix(graph)

        # Get original shortest path output
        original_output = shortest_path(csgraph)

        # Add new edge with high weight to the csgraph
        u, v, high_weight = 1, 2, 1000000
        modified_csgraph = csgraph.copy()
        modified_csgraph[u, v] = high_weight
        modified_csgraph[v, u] = high_weight

        # Get new shortest path output
        modified_output = shortest_path(modified_csgraph)

        # The shortest path should not change for any pair of nodes due to the high weight of the new edge
        np.testing.assert_array_equal(original_output, modified_output)


if __name__ == "__main__":
    unittest.main()
