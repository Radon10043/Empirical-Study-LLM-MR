import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test13(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 13: If the graph is converted to an unweighted graph by setting all edge
        weights to 1, the shortest path lengths should equal the number of edges in each path."""
        csgraph = csr_matrix(graph)

        # Convert graph to unweighted by setting all weights to 1
        unweighted_csgraph = csgraph.copy()
        unweighted_csgraph.data = np.ones_like(csgraph.data)

        # Get source output from the original weighted graph
        source_out = shortest_path(csgraph)

        # Get follow-up output from the unweighted graph
        unweighted_out = shortest_path(unweighted_csgraph)

        # Verification for each pair of nodes
        num_vertices = unweighted_out.shape[0]
        for i in range(num_vertices):
            for j in range(num_vertices):
                # If the original graph had a finite path, check the unweighted path length
                if np.isfinite(source_out[i][j]):
                    self.assertAlmostEqual(unweighted_out[i][j], unweighted_csgraph[i].getnnz())


if __name__ == "__main__":
    unittest.main()
