import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test31(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 31: Given the same graph, the same source and destination vertices,
        if we add a new isolated vertex, the shortest path length should remain unchanged."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Add a new isolated vertex to the graph
        extended_graph = deepcopy(graph)
        extended_graph.append([np.inf] * len(graph) + [np.inf])  # Add a new isolated vertex with no connections

        # Get the shortest path for the extended graph
        extended_shortest_path = shortest_path(extended_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path, extended_shortest_path)


if __name__ == "__main__":
    unittest.main()
