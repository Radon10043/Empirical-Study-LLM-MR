"""
Author: Radon
Date: 2024-01-09 17:27:20
LastEditors: Radon
LastEditTime: 2024-02-13 18:09:40
Description: Hi, say something
"""

import os
import shutil
import string

from random import randint


# fmt:off
# ==================== GLOBAL BARIABLES ====================
RANGE_LINE   = (1, 100)
RANGE_SMALL  = (1, 5)
RANGE_LARGE  = (1, 100)
RANGE_COUNT  = (1, 10)
KEYWORDS     = ["lambda", "and", "or", "if", "xor"]
SPECIAL      = ["(", ")", "[", "]", "'", "`", ",", "=>"]
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
    candidate = string.ascii_letters + string.digits + " "
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
    """随机生成测试用例, 保存至testcases文件夹下

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
        for j in range(line_num):
            for _ in range(*RANGE_COUNT):
                op = operations[randint(0, len(operations) - 1)]
                f.write(op() + " ")
            if j == line_num - 1:
                break
            f.write("\n")
        f.close()

    print("\nDone!")


if __name__ == "__main__":
    gen_tcs_randomly(1000)
