import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test38(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 38: In a graph where every path from node A to node B passes through
        node C, increasing the weight of all outgoing edges from C should either increase the shortest
        path from A to B or leave it unchanged if C is not on the shortest path from A to B."""
        # This requires previous knowledge or another method to check if all paths from A to B pass through C
        source, via_node, destination = 0, 1, 2  # As an example, but should be determined based on the graph structure

        # Get original shortest paths
        original_dist_matrix = shortest_path(graph, method=method)

        # Increase the weight of all outgoing edges from via_node
        increased_graph = deepcopy(graph)
        for i in range(len(graph)):
            if increased_graph[via_node][i] > 0:  # Check for an existing edge
                increased_graph[via_node][i] += 10

        # Get new shortest path distances
        new_dist_matrix = shortest_path(increased_graph, method=method)

        # Verify that the shortest path from A to B has not decreased
        self.assertLessEqual(original_dist_matrix[source][destination], new_dist_matrix[source][destination])


if __name__ == "__main__":
    unittest.main()
