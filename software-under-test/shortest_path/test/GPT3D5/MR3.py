import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test3(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 3: Given the same graph, the same source vertex,
        and a different destination vertex, the output path length should always be greater or equal."""
        # Get source output for the original destination
        source_out_original = shortest_path(graph, method=method)[src][dst]

        # Choose a different destination vertex
        new_dst = (dst + 1) % len(graph)  # Choose the next vertex cyclically

        # Get source output for the new destination
        source_out_new = shortest_path(graph, method=method)[src][new_dst]

        # Verification
        self.assertGreaterEqual(source_out_new, source_out_original)


if __name__ == "__main__":
    unittest.main()
