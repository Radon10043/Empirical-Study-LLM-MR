import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))   # Fixed
    def test41(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 41: Removing edges between non-adjacent nodes in the shortest path should not affect the shortest path length."""
        # Calculate the shortest path from src to dst
        matrix, predcessors = shortest_path(graph, method=method)
        shortest_path_length = matrix[src][dst]

        # Assume a function get_shortest_path_edges exists that returns the edges in the shortest path
        path_nodes = get_shortest_path(predcessors, src, dst)
        edges_on_path = [(path_nodes[i], path_nodes[i + 1]) for i in range(len(path_nodes) - 1)]

        # Remove edges between non-adjacent nodes in the graph
        for i in range(len(graph)):
            for j in range(len(graph)):
                if i != j and (i, j) not in edges_on_path and graph[i][j] != float('inf'):
                    graph[i][j] = float('inf')

        # Calculate the shortest path after removing non-adjacent edges
        new_shortest_path_length = shortest_path(graph, method=method)[src][dst]

        # Verify that removing edges not on the original shortest path doesn't affect its length
        self.assertEqual(shortest_path_length, new_shortest_path_length)


if __name__ == "__main__":
    unittest.main()
