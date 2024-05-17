import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test1(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 11: If every edge weight in the graph is increased by a constant factor k,
        the shortest path from any node to any other node should also be increased by that factor k."""
        csgraph = csr_matrix(graph)

        k = 10

        # Add a constant factor k to every edge weight
        modified_csgraph = csgraph.copy()
        modified_csgraph.data = modified_csgraph.data + k

        # Get source output from the original graph
        source_out = shortest_path(csgraph)

        # Get follow-up output from the modified graph
        follow_out = shortest_path(modified_csgraph)

        # Verification for each pair of nodes
        # Assuming no negative weights and disconnected paths (inf)
        num_vertices = source_out.shape[0]
        for i in range(num_vertices):
            for j in range(num_vertices):
                if np.isfinite(source_out[i][j]):
                    expected_follow_out = source_out[i][j] + k * (len(csgraph.indices[csgraph.indptr[i] : csgraph.indptr[i + 1]]) - 1)
                    self.assertAlmostEqual(follow_out[i][j], expected_follow_out)


if __name__ == "__main__":
    unittest.main()
