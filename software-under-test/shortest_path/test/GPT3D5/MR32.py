import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test32(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 32: Given the same graph, the same source and destination vertices,
        if we add a new vertex with a direct edge to the destination, the shortest path length should decrease or remain unchanged."""
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Add a new vertex with a direct edge to the destination
        modified_graph = deepcopy(graph)
        modified_graph.append([np.inf] * len(graph) + [1])  # Add a new vertex with no connections except for the direct edge to the destination

        # Get the shortest path for the modified graph
        modified_shortest_path = shortest_path(modified_graph, method=method)[src][dst]

        # Verification
        self.assertLessEqual(modified_shortest_path, original_shortest_path)


if __name__ == "__main__":
    unittest.main()
