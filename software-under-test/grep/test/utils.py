"""
Author: Radon
Date: 2024-01-09 15:59:19
LastEditors: Radon
LastEditTime: 2024-05-27 14:49:21
Description: Hi, say something
"""
import os
import sys
import shutil
import unittest

from random import randint
from string import ascii_letters, digits
from parameterized import parameterized


# fmt:off
# ========== GLOBAL VARIABLES ==========
RANGE_TEXT_LINE     = (1, 1000)   # 文本文件行数范围
RANGE_TEXT_LEN      = (1, 100)    # 文本文件行长度范围
RANGE_PATTERN_LEN   = (1, 5)     # 搜索项长度范围
GREP_PATH           = os.path.join(os.path.dirname(__file__), "..", "src", "grep-3.11", "obj-temp", "src", "grep")
# ======================================
# fmt:on


def gen_str_randomly(length: int) -> str:
    """随机生成一定长度的字符串

    Parameters
    ----------
    length : int
        _description_

    Returns
    -------
    str
        _description_
    """
    s = str()
    candidate = ascii_letters + digits + " \t"
    for _ in range(length):
        s += candidate[randint(0, len(candidate) - 1)]
    return s


def gen_text_randomly(fp: str):
    """随机生成一定行数的text文件

    Parameters
    ----------
    fp : str
        _description_
    """
    line_num = randint(*RANGE_TEXT_LINE)
    lines = list()

    for _ in range(line_num):
        lines.append(gen_str_randomly(randint(*RANGE_TEXT_LEN)))

    with open(fp, mode="w") as f:
        f.write("\n".join(lines))


def gen_pattern_randomly(fp: str):
    """随机生成pattern文件

    Parameters
    ----------
    fp : str
        _description_
    """
    # 随机生成pattern, 避免出现空格
    pattern = gen_str_randomly(randint(*RANGE_PATTERN_LEN))
    while " " in pattern or "\t" in pattern:
        pattern = gen_str_randomly(randint(*RANGE_PATTERN_LEN))

    # 写入文件
    with open(fp, mode="w") as f:
        f.write(pattern)


def gen_tcs_randomly(num: int):
    """随机生成测试用例

    Parameters
    ----------
    num : int
        测试用例数量
    """
    tcs_dir = os.path.join(os.path.dirname(__file__), "..", "testcases")

    # 删除旧的测试用例, 新创建一个存储测试用例的文件夹
    shutil.rmtree(tcs_dir, ignore_errors=True)
    os.mkdir(tcs_dir)

    for i in range(num):
        print("Creating testcase " + str(i).zfill(3) + "...", end="\r")

        tc_dir = os.path.join(tcs_dir, "tc" + str(i).zfill(3))
        if not os.path.exists(tc_dir):
            os.mkdir(os.path.join(tc_dir))

        # 生成文本文件
        text_path = os.path.join(tc_dir, "text.txt")
        gen_text_randomly(text_path)

        pattern_path = os.path.join(tc_dir, "pattern.txt")
        gen_pattern_randomly(pattern_path)

    print(f"{num} testcases are created!")


def gen_tcs_randomly_combination(num: int):
    """随机生成测试用例 (combination)

    Parameters
    ----------
    num : int
        测试用例数量
    """
    tcs_dir = os.path.join(os.path.dirname(__file__), "..", "testcases")

    # 删除旧的测试用例, 新创建一个存储测试用例的文件夹
    shutil.rmtree(tcs_dir, ignore_errors=True)
    os.mkdir(tcs_dir)

    for i in range(num):
        print("Creating testcase " + str(i).zfill(3) + "...", end="\r")

        tc_dir = os.path.join(tcs_dir, "tc" + str(i).zfill(3))
        if not os.path.exists(tc_dir):
            os.mkdir(os.path.join(tc_dir))

        # 生成文本文件
        text1_path = os.path.join(tc_dir, "text1.txt")
        text2_path = os.path.join(tc_dir, "text2.txt")
        gen_text_randomly(text1_path)
        gen_text_randomly(text2_path)

        pattern_path = os.path.join(tc_dir, "pattern.txt")
        gen_pattern_randomly(pattern_path)

    print(f"{num} testcases are created!")


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

    tc_dir = os.path.join(os.path.dirname(__file__), "..", "testcases")  # 文件系统中存储所有测试用例的根目录
    dirs = [os.path.join(tc_dir, dir) for dir in os.listdir(tc_dir)]  # 存储了测试用例文件路径的列表
    testcases = list()  # 用于存储所有测试用例的列表

    # 遍历存储了测试用例的文件夹, 读取测试用例的内容
    for dir in dirs:
        pattern_path = os.path.join(dir, "pattern.txt")
        text_path = os.path.join(dir, "text.txt")  # 获取要进行搜索的文本路径
        testcases.append((pattern_path, text_path))

    return testcases


def load_test_cases_combinations(num: int) -> list:
    """加载测试用例

    Parameters
    ----------
    num : int
        测试用例数量

    Returns
    -------
    list
        text1, text2和pattern文件的地址
    """
    # 每次测试开始前先创建测试用例
    gen_tcs_randomly_combination(num)

    tc_dir = os.path.join(os.path.dirname(__file__), "..", "testcases")  # 文件系统中存储所有测试用例的根目录
    dirs = [os.path.join(tc_dir, dir) for dir in os.listdir(tc_dir)]  # 存储了测试用例文件路径的列表
    testcases = list()  # 用于存储所有测试用例的列表

    # 遍历存储了测试用例的文件夹, 读取测试用例的内容
    for dir in dirs:
        pattern_path = os.path.join(dir, "pattern.txt")
        text1_path = os.path.join(dir, "text1.txt")  # 获取要进行搜索的文本路径
        text2_path = os.path.join(dir, "text2.txt")  # 获取要进行搜索的文本路径
        testcases.append((pattern_path, text1_path, text2_path))

    return testcases