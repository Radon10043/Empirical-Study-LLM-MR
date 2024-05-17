import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test38(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 38: Scaling the weights of all edges by a positive factor should result in the shortest path 
        distances being scaled by that same factor."""
        scale_factor = np.random.randint(1, 11);
        csgraph = csr_matrix(graph)

        # Scale the graph by a positive factor
        scaled_csgraph = csgraph.copy()
        scaled_csgraph.data *= scale_factor

        # Get the original shortest path distances
        original_distances = shortest_path(csgraph)

        # Get the shortest path distances after scaling the graph
        scaled_distances = shortest_path(scaled_csgraph)

        # Shortest path distances should be scaled by the same factor
        np.testing.assert_array_almost_equal(scaled_distances, original_distances * scale_factor)


if __name__ == "__main__":
    unittest.main()
