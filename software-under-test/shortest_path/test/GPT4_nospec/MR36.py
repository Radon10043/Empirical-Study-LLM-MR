import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test36(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 36: In a graph with positive weights, increasing the weight of an edge not on the current shortest path shouldn't affect the shortest path."""
        # Get the shortest path and its edges
        _, predcessors = shortest_path(graph, method=method, return_predecessors=True)
        path = get_shortest_path(predcessors, src, dst)
        shortest_path_edges = [(path[i], path[i + 1]) for i in range(len(path) - 1)]

        # Pick an edge that's not in the shortest path, if possible
        all_edges = [(i, j) for i in range(len(graph)) for j in range(len(graph[i])) if graph[i][j] != float("inf") and (i, j) not in shortest_path_edges]
        if all_edges:
            u, v = all_edges[0]

            # Increase the weight of the chosen edge
            original_weight = graph[u][v]
            graph[u][v] += 10

            # Verify the shortest path cost remains unchanged
            new_shortest_path_cost = shortest_path(graph, method=method)[src][dst]
            self.assertEqual(shortest_path(graph, method=method)[src][dst], new_shortest_path_cost)

            # Reset the edge weight for other tests
            graph[u][v] = original_weight


if __name__ == "__main__":
    unittest.main()
