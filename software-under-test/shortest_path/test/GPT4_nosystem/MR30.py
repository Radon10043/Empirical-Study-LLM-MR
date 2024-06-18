import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test30(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 30: In a directed graph, disconnecting a node (removing all outgoing
        edges) should not affect the shortest path distances from any node to that node."""
        # Select a node to disconnect (remove all outgoing edges)
        disconnected_node = randint(0, len(graph) - 1)
        disconnected_graph = deepcopy(graph)  # Assume deepcopy is imported from the copy module
        for i in range(len(disconnected_graph)):
            disconnected_graph[disconnected_node][i] = 0

        # Get shortest paths for both original and disconnected graphs
        original_dist_matrix = shortest_path(graph, method=method, directed=True)
        disconnected_dist_matrix = shortest_path(disconnected_graph, method=method, directed=True)

        # Verify that distances to the disconnected node are unchanged
        for i in range(len(graph)):
            self.assertEqual(original_dist_matrix[i][disconnected_node], disconnected_dist_matrix[i][disconnected_node])


if __name__ == "__main__":
    unittest.main()
