import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from copy import deepcopy

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    # Fix by Radon, maybe not right?
    @parameterized.expand(gen_tcs_randomly)
    def test20(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 20: Given the same graph, the same source and destination vertices,
        if we introduce a new edge that creates a shorter path, the new shortest path should be the length of the introduced edge."""
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Find an intermediary node not in the shortest path
        sp = shortest_path(graph, method=method, return_predecessors=True)
        inter_node = sp[1][dst]
        if inter_node != -9999:
            # Create a new edge that creates a shorter path
            modified_graph = deepcopy(graph)
            modified_graph[src][dst] = modified_graph[src][inter_node] + modified_graph[inter_node][dst]

            # Get the shortest path for the modified graph
            modified_shortest_path = shortest_path(modified_graph, method=method)[src][dst]

            # Verification
            self.assertEqual(modified_shortest_path, modified_graph[src][dst])


if __name__ == "__main__":
    unittest.main()
