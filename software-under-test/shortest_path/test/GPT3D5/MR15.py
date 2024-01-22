import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test15(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 15: Given the same graph, the same source and destination vertices,
        if we change the source and destination vertices, the shortest path length should change accordingly."""
        # Get the shortest path for the original source and destination
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Choose different source and destination vertices
        new_src, new_dst = (src + 1) % len(graph), (dst + 1) % len(graph)

        # Get the shortest path for the new source and destination
        new_shortest_path = shortest_path(graph, method=method)[new_src][new_dst]

        # Verification
        self.assertNotEqual(original_shortest_path, new_shortest_path)


if __name__ == "__main__":
    unittest.main()
