import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test21(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 21: Identifying a node as an intermediary hub (adding 0-weight edges
        between the hub and all other nodes) should not increase the distance of any shortest path."""
        import random

        # Select a random node to be the "hub"
        hub = random.choice(range(len(graph)))

        # Modify the graph to include 0-weight edges to/from the hub
        hub_graph = [[0 if (i == hub or j == hub) else graph[i][j] for j in range(len(graph))] for i in range(len(graph))]

        # Compute shortest path with the modified "hub" graph
        hub_distances = shortest_path(hub_graph, method=method)

        # Compare the shortest paths with the original distances
        original_distances = shortest_path(graph, method=method)
        for i in range(len(graph)):
            for j in range(len(graph)):
                if i != hub and j != hub:  # Exclude the hub itself
                    self.assertLessEqual(hub_distances[i][j], original_distances[i][j])


if __name__ == "__main__":
    unittest.main()
