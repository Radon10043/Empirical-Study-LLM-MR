import unittest
import os, sys

from copy import deepcopy
from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test8(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 8: Given the same graph, the same source and destination vertices, and a shortest path,
        if we add a new vertex and connect it to the existing vertices in the graph, the shortest path length from
        source to destination should not decrease."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Add a new vertex and connect it to the existing vertices in the graph for follow-up input
        extended_graph = deepcopy(graph)
        for row in extended_graph:
            row.append(5)  # Add a new edge weight to the existing vertices
        extended_graph.append([5] * (len(graph) + 1))  # Connect the new vertex to the existing vertices

        # Get the shortest path for the extended graph
        extended_shortest_path = shortest_path(extended_graph, method=method)[src][dst]

        # Verification
        self.assertGreaterEqual(extended_shortest_path, original_shortest_path)

if __name__ == "__main__":
    unittest.main()
