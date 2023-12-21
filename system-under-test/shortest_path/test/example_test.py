import unittest
import os, json

import numpy as np

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix


def load_test_cases() -> list:
    """读取测试用例文件夹下所有测试用例的内容

    Returns
    -------
    list
        存储了所有测试用例的列表

    Notes
    -----
    _description_
    """
    # 存储测试用例文件夹的路径
    tc_dir = os.path.join(os.path.dirname(__file__), "..", "testcases")

    # 读取后缀名为json的文件
    files = os.listdir(tc_dir)
    json_files = [file for file in files if file.endswith(".json")]

    # 存储所有测试用例的列表
    tcs = list()

    # 读取测试用例的内容
    for json_file in json_files:
        with open(os.path.join(tc_dir, json_file), "r") as f:
            tc = json.loads(f.read())
            tc["graph"] = csr_matrix(tc["graph"])
            tcs.append((tc["graph"], tc["source"], tc["destination"], tc["method"]))

    return tcs


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test1(self, graph: csr_matrix, src: int, dst: int, method: str):
        """Metamorphic Relation 1: Given the same graph, the same source and destination vertices,
        but with different algorithms, the output should be the same.

        Parameters
        ----------
        graph : csr_matrix
            Directed graph.
        src : int
            Source vertex.
        dst : int
            Destination vertex.
        method : str
            The shortest path algorithm to be used.

        Notes
        -----
        _description_
        """
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
