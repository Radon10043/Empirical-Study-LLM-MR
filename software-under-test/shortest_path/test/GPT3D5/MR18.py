import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from copy import deepcopy

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test18(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 18: Given the same graph, the same source and destination vertices,
        if we add a cycle with negative weight, the shortest path length should remain the same."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Add a cycle with negative weight to the graph
        graph_with_cycle = deepcopy(graph)
        for i in range(len(graph_with_cycle)):
            graph_with_cycle[i][i] = -1  # Add negative weight for self-loop for all vertices

        # Get the shortest path for the modified graph
        modified_shortest_path = shortest_path(graph_with_cycle, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path, modified_shortest_path)


if __name__ == "__main__":
    unittest.main()
