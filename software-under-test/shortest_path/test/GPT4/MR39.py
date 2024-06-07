import os, sys

import scipy as sp

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test39(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 39: In an undirected graph, adding a new vertex and connecting it to all 
        other vertices with a zero weight should not change any shortest paths between existing nodes."""
        # Get source output for the original graph assuming it is undirected
        original_distance = shortest_path(graph, method=method, directed=False)[src][dst]

        # Add a new vertex and connect to all existing nodes with a zero weight
        extended_graph = graph.copy()
        extended_graph.append([0] * len(extended_graph))
        for i in range(len(extended_graph)):
            extended_graph[i].append(0)

        # Get follow-up output for the extended graph
        new_distance = shortest_path(extended_graph, method=method, directed=False)[src][dst]

        # Verification: The distance in the extended graph should be the same as the original
        self.assertEqual(original_distance, new_distance)


if __name__ == "__main__":
    unittest.main()
