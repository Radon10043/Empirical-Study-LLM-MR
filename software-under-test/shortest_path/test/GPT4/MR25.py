import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test25(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 25: For an undirected graph, converting to a directed graph by duplicating 
        each edge should result in the same shortest path distances."""
        csgraph = csr_matrix(graph)

        # Ensure the graph is undirected by making it symmetric
        symmetric_csgraph = csgraph + csgraph.T

        # Get shortest path distances on the undirected graph
        undirected_distances = shortest_path(symmetric_csgraph, directed=False)

        # Get shortest path distances on the same graph but considered directed
        directed_distances = shortest_path(symmetric_csgraph, directed=True)

        # Shortest path distances should be the same regardless of directed or undirected representation
        np.testing.assert_array_equal(undirected_distances, directed_distances)


if __name__ == "__main__":
    unittest.main()
