import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test33(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 33: For a directed graph, if the shortest path from node A to B and from
        B to C exists, then removing the edge from A to B should either increase the length of the
        shortest path from A to C or result in no valid path."""
        # Ensure there is an edge from src to dst to start with
        if graph[src][dst] == 0:
            self.skipTest("No edge between src and dst to begin with. Choose different nodes.")

        # Original shortest paths from src to all nodes
        original_dist_matrix = shortest_path(graph, method=method)

        # Remove edge from src to dst
        graph_without_edge = deepcopy(graph)
        graph_without_edge[src][dst] = 0

        # Shortest paths after edge removal
        new_dist_matrix = shortest_path(graph_without_edge, method=method)

        # Verify that the shortest path from src to any node C via B is not shorter
        for c in range(len(graph)):
            if original_dist_matrix[dst][c] != np.inf and original_dist_matrix[src][dst] != np.inf:
                # Check if path from src to c via dst is not shorter
                self.assertGreaterEqual(new_dist_matrix[src][c], original_dist_matrix[src][c])


if __name__ == "__main__":
    unittest.main()
