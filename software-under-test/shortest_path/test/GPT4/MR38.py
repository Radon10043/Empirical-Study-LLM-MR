import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test38(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 38: Reversing the direction of all edges in a weighted directed graph should 
        not change the shortest path if the graph was symmetrical. If it was not symmetrical, the shortest 
        path distance could change."""
        for i in range(len(graph)):
            for j in range(i, len(graph[i])):
                graph[i][j] = graph[i][j]
        graph = csr_matrix(graph)

        # Create a reverse graph by reversing the edge directions
        reverse_graph = graph.T

        # Calculate shortest path in the original graph
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Calculate shortest path in the reversed graph
        reversed_distance = shortest_path(reverse_graph, method=method)[dst][src]

        # Verification: if original graph is symmetrical, distances should be equal
        # If it is not symmetrical, no equality check is performed
        self.assertEqual(original_distance, reversed_distance)


if __name__ == "__main__":
    unittest.main()
