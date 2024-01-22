import unittest
import os, json

import numpy as np

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

from utils import gen_tcs_randomly


def load_test_cases() -> list:
    """加载测试用例

    Returns
    -------
    list
        存储测试用例的列表

    Notes
    -----
    _description_
    """
    return gen_tcs_randomly()


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
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

    @parameterized.expand(load_test_cases)
    def test2(self, graph: csr_matrix, src: int, dst: int, method: str):
        """Metamorphic Relation 2: Given the same graph, the same source and destination vertices,
        but weights scaled 2 times, the output should also be scaled 2 times."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        follow_graph = list()
        for row in graph:
            follow_graph.append([x * 2 for x in row])

        # Get folllow-up output
        follow_out = shortest_path(follow_graph, method)[src][dst]

        # Verification
        self.assertEqual(source_out * 2, follow_out)


if __name__ == "__main__":
    unittest.main()
