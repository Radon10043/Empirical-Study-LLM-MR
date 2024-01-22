import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test39(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 39: Given the same graph, the same source and destination vertices,
        if we remove an edge on the shortest path, the shortest path length should increase or remain unchanged."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Find an edge on the shortest path
        path, _ = shortest_path(graph, method=method, return_predecessors=True)
        u, v = dst, path[1][dst]
        while v != src:
            # Remove the edge on the shortest path
            modified_graph = deepcopy(graph)
            modified_graph[u][v] = np.inf
            u, v = v, path[1][v]

        # Get the shortest path for the modified graph
        modified_shortest_path = shortest_path(modified_graph, method=method)[src][dst]

        # Verification
        self.assertGreaterEqual(modified_shortest_path, original_shortest_path)


if __name__ == "__main__":
    unittest.main()
