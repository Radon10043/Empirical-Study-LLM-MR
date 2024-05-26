"""
Author: Radon
Date: 2024-01-10 20:21:28
LastEditors: Radon
LastEditTime: 2024-05-26 02:57:56
Description: Hi, say something
"""
import os
import shutil
import string
import unittest
import subprocess
import sys
import random
import re

from parameterized import parameterized

from random import randint


# fmt:off
# ==================== GLOBAL BARIABLES ====================
RANGE_LINE          = (1, 100)
RANGE_SMALL         = (1, 5)
RANGE_LARGE         = (1, 100)
RANGE_COUNT         = (1, 10)
KEYWORDS            = ["lambda", "and", "or", "if", "xor"]
SPECIAL             = ["(", ")", "[", "]", "'", "`", ",", "=>"]
PRINT_TOKENS2_PATH  = os.path.join(os.path.dirname(__file__), "..", "src", "print_tokens2.out")
# ==========================================================
# fmt:on


def gen_keyword() -> str:
    """生成一个随机的keyword

    Returns
    -------
    str
        keyword
    """
    return KEYWORDS[randint(0, len(KEYWORDS) - 1)]


def gen_special() -> str:
    """生成一个随机的特殊字符

    Returns
    -------
    str
        特殊字符
    """
    return SPECIAL[randint(0, len(SPECIAL) - 1)]


def gen_identifier() -> str:
    """生成一个随机的标识符

    Returns
    -------
    str
        标识符
    """
    candidate = string.ascii_letters
    s = str()
    length = randint(*RANGE_SMALL)

    for _ in range(length):
        s += candidate[randint(0, len(candidate) - 1)]

    return s


def gen_numeric() -> str:
    """生成一个随机的数字

    Returns
    -------
    str
        数字
    """
    candidate = string.digits
    s = str()
    length = randint(*RANGE_SMALL)

    for _ in range(length):
        s += candidate[randint(0, len(candidate) - 1)]

    return s


def gen_string() -> str:
    """生成一个随机的字符串

    Returns
    -------
    str
        字符串
    """
    candidate = string.ascii_letters + string.digits
    s = '"'
    length = randint(*RANGE_SMALL)

    for _ in range(length):
        s += candidate[randint(0, len(candidate) - 1)]
    s += '"'

    return s


def gen_comment() -> str:
    """生成一个随机的注释

    Returns
    -------
    str
        注释
    """
    candidate = string.ascii_letters + string.digits + " "
    s = ";"
    length = randint(*RANGE_LARGE)

    for _ in range(length):
        s += candidate[randint(0, len(candidate) - 1)]

    return s


def gen_tcs_randomly(num: int):
    """生成一定数量的测试用例

    Parameters
    ----------
    num : int
        测试用例数量
    """
    tcs_dir = os.path.join(os.path.dirname(__file__), "..", "testcases")
    if os.path.exists(tcs_dir):
        shutil.rmtree(tcs_dir)
    os.mkdir(tcs_dir)

    # 可选操作
    operations = [gen_keyword, gen_special, gen_identifier, gen_numeric, gen_string, gen_comment]

    for i in range(num):
        print("\rGenerating testcase " + str(i).zfill(3) + " ...", end="")
        tc_file = os.path.join(tcs_dir, "tc" + str(i).zfill(3) + ".txt")
        line_num = randint(*RANGE_LINE)

        f = open(tc_file, mode="w", encoding="utf-8")
        for _ in range(line_num):
            for _ in range(*RANGE_COUNT):
                op = operations[randint(0, len(operations) - 1)]
                f.write(op() + " ")
            f.write("\n")
        f.close()

    print("\nDone!")


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

    tcs_dir = os.path.join(os.path.dirname(__file__), "..", "testcases")
    tcs = list()

    # 遍历存储测试用例的根目录, 依次读取文件
    for file in os.listdir(tcs_dir):
        with open(os.path.join(tcs_dir, file), "r") as f:
            tcs.append(f.read() + "\n")

    return tcs


if __name__ == "__main__":
    gen_tcs_randomly(1000)