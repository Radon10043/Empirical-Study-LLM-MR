import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test37(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 37: Reversing the direction of every edge in a graph should not change the distances
        in the shortest path matrix when the graph is undirected."""
        csgraph = csr_matrix(graph)

        reversed_csgraph = csgraph.T  # Transpose to reverse edge directions

        # Get the original shortest path distances
        original_distances = shortest_path(csgraph, directed=False)

        # Get the distances after edges are reversed in the graph
        reversed_distances = shortest_path(reversed_csgraph, directed=False)

        # Distances in the shortest path matrix should remain unchanged because the graph is undirected
        np.testing.assert_array_almost_equal(original_distances, reversed_distances)


if __name__ == "__main__":
    unittest.main()
