import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test34(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 34: If the weight of every outgoing edge from a source node is increased
        by a constant amount, every shortest path from that source to any destination should
        increase by exactly the same amount or remain unchanged if the edge was not part of the path."""
        constant_increase = 10
        # Increase the weight of every edge from a selected source node
        increased_graph = deepcopy(graph)
        for i in range(len(graph)):
            if increased_graph[src][i] != 0:
                increased_graph[src][i] += constant_increase

        # Compute shortest paths for both original and increased-weight graph
        original_dist_matrix = shortest_path(graph, method=method)
        increased_dist_matrix = shortest_path(increased_graph, method=method)

        # Verify distances from the source have increased by the constant or remain unchanged
        for destination in range(len(graph)):
            original_distance = original_dist_matrix[src][destination]
            increased_distance = increased_dist_matrix[src][destination]
            if original_distance == np.inf:
                self.assertEqual(increased_distance, np.inf)
            else:
                self.assertTrue(increased_distance == original_distance + constant_increase or increased_distance == original_distance)


if __name__ == "__main__":
    unittest.main()
