import unittest
import os, sys
import random

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from parameterized import parameterized
from generate import *


# GLOBAL VARIABLES
GREP_PATH = os.path.join(os.path.dirname(__file__), "..", "..", "src", "grep-3.11", "obj-temp", "src", "grep")


def load_test_cases(num: int) -> list:
    """加载测试用例

    Parameters
    ----------
    num : int
        测试用例数量

    Returns
    -------
    list
        _description_
    """
    # 每次测试开始前先创建测试用例
    gen_tcs_randomly(num)

    tc_dir = os.path.join(os.path.dirname(__file__), "..", "..", "testcases")  # 文件系统中存储所有测试用例的根目录
    dirs = [os.path.join(tc_dir, dir) for dir in os.listdir(tc_dir)]  # 存储了测试用例文件路径的列表
    testcases = list()  # 用于存储所有测试用例的列表

    # 遍历存储了测试用例的文件夹, 读取测试用例的内容
    for dir in dirs:
        pattern_path = os.path.join(dir, "pattern.txt")
        text_path = os.path.join(dir, "text.txt")  # 获取要进行搜索的文本路径
        testcases.append((pattern_path, text_path))

    return testcases
