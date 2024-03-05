import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from generate import *


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

def get_shortest_path(predecessors: np.ndarray, src: int, dst: int) -> list:
    """获取从src到dst的最短路径

    Parameters
    ----------
    predecessors : np.ndarray
        前驱节点列表
    src : int
        起点
    dst : int
        终点

    Returns
    -------
    list
        最短路径的节点列表
    """
    path = [src]
    while path[-1] != dst:
        mid = path[-1]
        if predecessors[mid][dst] == mid:
            path.append(dst)
        else:
            path.append(predecessors[mid][dst])
    return path
