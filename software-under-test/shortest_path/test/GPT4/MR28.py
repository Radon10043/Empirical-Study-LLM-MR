import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test28(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 28: Replacing all non-zero weights with their negations should result 
        in the same shortest path topology, provided that there are no negative cycles."""
        csgraph = csr_matrix(graph)

        # Get original shortest paths
        original_path_lengths, original_predecessors = shortest_path(csgraph, return_predecessors=True)

        # Negate all weights
        negated_csgraph = csgraph.copy()
        negated_csgraph.data *= -1

        # Get shortest paths for the graph with negated weights
        negated_path_lengths, negated_predecessors = shortest_path(negated_csgraph, return_predecessors=True)

        # Verify that the topology of paths (sequence of nodes) remains the same, while distances will be negated
        np.testing.assert_array_equal(original_predecessors, negated_predecessors)
        np.testing.assert_allclose(original_path_lengths, -negated_path_lengths, atol=1e-6)


if __name__ == "__main__":
    unittest.main()
