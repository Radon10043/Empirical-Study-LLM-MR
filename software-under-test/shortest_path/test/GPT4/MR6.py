import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test6(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 6: When directed is False, the shortest path from node i to j should be the same as
        the shortest path from node j to i."""
        csgraph = csr_matrix(graph)
        directed = True

        if directed:
            # Convert graph to undirected
            undirected_graph = csgraph + csgraph.T

            # Get source output
            source_out = shortest_path(undirected_graph, directed=False)

            # Verification
            num_vertices = len(source_out)
            for i in range(num_vertices):
                for j in range(num_vertices):
                    if i != j:
                        self.assertEqual(source_out[i][j], source_out[j][i])


if __name__ == "__main__":
    unittest.main()
