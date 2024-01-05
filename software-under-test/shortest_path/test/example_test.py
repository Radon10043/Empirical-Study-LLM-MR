import unittest
import os, json

import numpy as np

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test1(self, graph: csr_matrix, src: int, dst: int, method: str):
        """Metamorphic Relation 1: Given the same graph, the same source and destination vertices,
        but with different algorithms, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input
        follow_method = "FW"
        if method == "FW":
            follow_method = "D"

        # Get folllow-up output
        follow_out = shortest_path(graph, method=follow_method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
