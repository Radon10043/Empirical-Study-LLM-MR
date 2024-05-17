import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test40(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 40: Inverting the weight of all edges in an undirected graph (negating them and adding a
        constant to avoid negative weights) should not change the topology (the sequence of nodes) of the shortest paths."""
        csgraph = csr_matrix(graph)
        additive_inverse_offset = 100000

        # Negate all edge weights and add a constant to invert the weight without creating negative weights
        inverted_csgraph = csgraph.copy()
        inverted_csgraph.data = -inverted_csgraph.data + additive_inverse_offset

        # Calculate shortest path predecessors for the original and inverted graphs
        _, original_preds = shortest_path(csgraph, directed=False, return_predecessors=True)
        _, inverted_preds = shortest_path(inverted_csgraph, directed=False, return_predecessors=True)

        # Verify that the shortest path topology (the sequence of nodes) remains unchanged
        np.testing.assert_array_equal(original_preds, inverted_preds)


if __name__ == "__main__":
    unittest.main()
