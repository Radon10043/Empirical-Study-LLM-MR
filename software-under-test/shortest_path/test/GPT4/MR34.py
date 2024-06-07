import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test34(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 34: Connecting all nodes to a new node with infinite weight edges does 
        not change the shortest paths in the original graph."""
        # Get shortest paths for the original graph
        original_distances = shortest_path(graph, method=method)

        # Connect all existing nodes to a new node with infinite weight
        extended_graph = graph.copy()
        extended_graph.append([float("inf")] * len(extended_graph))
        for i in range(len(extended_graph)):
            extended_graph[i].append(float("inf"))

        # Get shortest paths for the extended graph
        extended_distances = shortest_path(extended_graph, method=method)

        # Verify that distances in the original graph are unchanged
        for i in range(original_distances.shape[0]):
            for j in range(original_distances.shape[1]):
                if i != j:  # Ignore self-distances, as a new node adds a 0-distance edge
                    self.assertEqual(original_distances[i][j], extended_distances[i][j])


if __name__ == "__main__":
    unittest.main()
