"""
Author: Radon
Date: 2024-01-10 21:23:15
LastEditors: Radon
LastEditTime: 2024-05-27 11:09:07
Description: Hi, say something
"""
import os
import unittest
import subprocess
import sys
import shutil

from parameterized import parameterized

from random import randint


# fmt:off
# ==================== GLOBAL VRAIABLES ====================
TETSCASE_NUM           = 1000
RANGE_VALUE            = (0, 1000)
RANGE_ALT_LAYER_VALUE  = (0, 3)
RANGE_OTEHER_RAC       = (0, 2)
RANGE_OTHER_CAPABILITY = (1, 2)
RANGE_CLIMB_INHIBIT    = (0, 1)
TCAS_PATH              = os.path.join(os.path.dirname(__file__), "..", "..", "src", "tcas.out")

INDEX = {
    "Cur_Vertical_Sep"          : 0,
    "High_Confidence"           : 1,
    "Two_of_Three_Reports_Valid": 2,
    "Own_Tracked_Alt"           : 3,
    "Own_Tracked_Alt_Rate"      : 4,
    "Other_Tracked_Alt"         : 5,
    "Alt_Layer_Value"           : 6,
    "Up_Separation"             : 7,
    "Down_Separation"           : 8,
    "Other_RAC"                 : 9,
    "Other_Capability"          : 10,
    "Climb_Inhibit"             : 11
}

OTHER_RAC_VALUES = {
    "NO_INTENT"     : 0,
    "DO_NOT_CLIMB"  : 1,
    "DO_NOT_DESCEND": 2
}

OTHER_CAPABILITY_VALUES = {
    "TCAS_TA"       : 1,
    "OTHER"         : 2
}
# ==========================================================
# fmt:on


def gen_tcs_randomly(num: int):
    """随机生成一定数量的测试用例, 并存储到testcases目录下

    Parameters
    ----------
    num : int
        测试用例数量
    """
    tcs_dir = os.path.join(os.path.dirname(__file__), "..", "testcases")
    if os.path.exists(tcs_dir):
        shutil.rmtree(tcs_dir)
    os.mkdir(tcs_dir)

    for i in range(TETSCASE_NUM):
        print(f"\rGenerating testcase {i}", end="")
        Cur_Vertical_Sep = randint(*RANGE_VALUE)
        High_Confidence = randint(*RANGE_VALUE)
        Two_of_Three_Reports_Valid = randint(*RANGE_VALUE)
        Own_Tracked_Alt = randint(*RANGE_VALUE)
        Own_Tracked_Alt_Rate = randint(*RANGE_VALUE)
        Other_Tracked_Alt = randint(*RANGE_VALUE)
        Alt_Layer_Value = randint(*RANGE_ALT_LAYER_VALUE)
        Up_Separation = randint(*RANGE_VALUE)
        Down_Separation = randint(*RANGE_VALUE)
        Other_RAC = randint(*RANGE_OTEHER_RAC)
        Other_Capability = randint(*RANGE_OTHER_CAPABILITY)
        Climb_Inhibit = randint(*RANGE_CLIMB_INHIBIT)
        list_values = [Cur_Vertical_Sep, High_Confidence, Two_of_Three_Reports_Valid, Own_Tracked_Alt, Own_Tracked_Alt_Rate, Other_Tracked_Alt, Alt_Layer_Value, Up_Separation, Down_Separation, Other_RAC, Other_Capability, Climb_Inhibit]

        f = open(os.path.join(tcs_dir, "tc" + str(i).zfill(3) + ".txt"), mode="w")
        f.write("\n".join([str(x) for x in list_values]))
        f.close()

    print("\nDone!")


def load_test_cases(num: int) -> list:
    """读取所有测试用例

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
            lst = [int(x) for x in f.read().split()]
            tcs.append((lst,))

    return tcs


def run_TCAS(vals: list) -> str:
    """运行 tcas.out 并返回输出

    Parameters
    ----------
    vals : list
        测试用例

    Returns
    -------
    str
        tcas.out 的输出
    """
    cmd_list = [TCAS_PATH]
    tmp_list = [str(x) for x in vals]
    cmd_list.extend(tmp_list)
    output = subprocess.check_output(cmd_list, text=True).split("\n")
    return output


if __name__ == "__main__":
    gen_tcs_randomly()
