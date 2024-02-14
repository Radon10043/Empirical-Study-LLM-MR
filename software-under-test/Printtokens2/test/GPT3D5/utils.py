import unittest
import os, subprocess, sys, random

from parameterized import parameterized

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from generate import *


# GLOBAL VRAIABLES
PRINT_TOKENS2_PATH = os.path.join(os.path.dirname(__file__), "..", "..", "src", "print_tokens2.out")


def load_test_cases(num: int) -> list:
    """读取测试用例

    Parameters
    ----------
    num : int
        测试用例数量

    Returns
    -------
    list
        存储测试用例的列表
    """
    gen_tcs_randomly(num)

    tcs_dir = os.path.join(os.path.dirname(__file__), "..", "..", "testcases")
    tcs = list()

    # 遍历存储测试用例的根目录, 依次读取文件
    for file in os.listdir(tcs_dir):
        with open(os.path.join(tcs_dir, file), "r") as f:
            tcs.append(f.read() + "\n")

    return tcs

