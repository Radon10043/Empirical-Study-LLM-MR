"""
Author: Radon
Date: 2024-01-09 15:59:19
LastEditors: Radon
LastEditTime: 2024-01-19 15:34:58
Description: Hi, say something
"""
import os

from random import randint
from string import ascii_letters, digits


# fmt:off
# ========== GLOBAL VARIABLES ==========
TESTCASE_NUM      = 1000        # 测试用例数量
RANGE_TEXT_LINE   = (1, 1000)   # 文本文件行数范围
RANGE_TEXT_LEN    = (1, 100)    # 文本文件行长度范围
RANGE_PATTERN_LEN = (1, 10)     # 搜索项长度范围
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
    while " " in pattern:
        pattern = gen_str_randomly(randint(*RANGE_PATTERN_LEN))

    # 写入文件
    with open(fp, mode="w") as f:
        f.write(pattern)


def gen_tcs_randomly():
    """随机生成测试用例

    Returns
    -------
    list
        _description_
    """
    tcs_dir = os.path.join(os.path.dirname(__file__), "..", "testcases")

    # 创建存储测试用例的文件夹
    if not os.path.exists(tcs_dir):
        os.mkdir(tcs_dir)

    for i in range(TESTCASE_NUM):
        print("Creating testcase " + str(i).zfill(3) + "...", end="\r")

        tc_dir = os.path.join(tcs_dir, "tc" + str(i).zfill(3))
        if not os.path.exists(tc_dir):
            os.mkdir(os.path.join(tc_dir))

        # 生成文本文件
        text_path = os.path.join(tc_dir, "text.txt")
        gen_text_randomly(text_path)

        pattern_path = os.path.join(tc_dir, "pattern.txt")
        gen_pattern_randomly(pattern_path)

    print(f"{TESTCASE_NUM} testcases are created!")


if __name__ == "__main__":
    gen_tcs_randomly()
