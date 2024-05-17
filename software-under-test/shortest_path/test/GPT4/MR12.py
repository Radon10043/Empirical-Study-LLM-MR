import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test12(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 12: Multiplying all edge weights by a negative should not change the
        shortest path (in absolute terms) for undirected graphs or positively weighted directed graphs,
        although paths may change if there are multiple shortest paths."""
        csgraph = csr_matrix(graph)

        # Note: the relation assumes no negative cycles would be introduced by this transformation.

        # Multiply each edge weight by -1
        modified_csgraph = -1 * csgraph

        # Get source output from the original graph
        source_out = shortest_path(csgraph)

        # Get follow-up output from the modified graph with all negative weights
        follow_out = shortest_path(modified_csgraph, method='FW')

        # Verification for each pair of nodes
        num_vertices = source_out.shape[0]
        for i in range(num_vertices):
            for j in range(num_vertices):
                self.assertAlmostEqual(abs(source_out[i][j]), abs(follow_out[i][j]))


if __name__ == "__main__":
    unittest.main()
