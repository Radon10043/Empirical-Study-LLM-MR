import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test18(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 18: Transposing the graph (inverting the direction of all edges) should not 
        change the shortest path distance in an undirected graph."""
        csgraph = csr_matrix(graph)

        # Get the original shortest path output
        original_output = shortest_path(csgraph, directed=False)

        # Transpose the csgraph
        transposed_csgraph = csgraph.transpose()

        # Get the shortest path for the transposed csgraph
        transposed_output = shortest_path(transposed_csgraph, directed=False)

        # The outputs should be equal for an undirected csgraph
        np.testing.assert_array_equal(original_output, transposed_output)


if __name__ == "__main__":
    unittest.main()
