import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test8(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 8: If edges of a graph are made twice as costly, the shortest path cost should
        also double, assuming no negative weights which could reroute paths."""
        csgraph = csr_matrix(graph)

        doubled_csgraph = 2 * csgraph

        # Source output: original weights
        source_out = shortest_path(csgraph)

        # Follow-up output: doubled weights
        follow_out = shortest_path(doubled_csgraph)

        # Verification for each pair of nodes
        num_vertices = source_out.shape[0]
        for i in range(num_vertices):
            for j in range(num_vertices):
                self.assertEqual(source_out[i][j] * 2, follow_out[i][j])


if __name__ == "__main__":
    unittest.main()
