"""
Author: Radon
Date: 2024-01-10 21:18:24
LastEditors: Radon
LastEditTime: 2024-05-27 10:12:46
Description: Hi, say something
"""

import unittest
import os
import subprocess
import sys

from parameterized import parameterized

from random import randint
import shutil


# fmt:off
# ==================== GLOBAL BARIABLES ====================
RANGE_JOBS   = (0, 100)
SCHEDULE_PATH = os.path.join(os.path.dirname(__file__), "..", "src", "schedule2.out")

SCHEDULE_OPERATIONS = {
    "NEW_JOB"       : "1",
    "UPGRADE_PRIO"  : "2",
    "BLOCK"         : "3",
    "UNBLOCK"       : "4",
    "QUANTUM_EXPIRE": "5",
    "FINISH"        : "6",
    "FLUSH"         : "7"
}

PRIORITY_LEVEL = {
    "HIGH"  : "3",
    "MEDIUM": "2",
    "LOW"   : "1"
}
# ==========================================================
# fmt:on


def gen_tcs_randomly(num: int):
    """随机生成一定数量的测试用例, 保存到testcases文件夹下

    Parameters
    ----------
    num : int
        测试用例数量
    """
    tcs_dir = os.path.join(os.path.dirname(__file__), "..", "testcases")
    if os.path.exists(tcs_dir):
        shutil.rmtree(tcs_dir)
    os.mkdir(tcs_dir)

    for i in range(num):
        print("\rGenerating testcase " + str(i).zfill(3) + " ...", end="")
        tc_file = os.path.join(tcs_dir, "tc" + str(i).zfill(3) + ".txt")

        f = open(tc_file, mode="w", encoding="utf-8")
        f.write(str(randint(*RANGE_JOBS)) + " " + str(randint(*RANGE_JOBS)) + " " + str(randint(*RANGE_JOBS)))
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
            tcs.append((f.read().split(),))

    return tcs


if __name__ == "__main__":
    gen_tcs_randomly(1000)
