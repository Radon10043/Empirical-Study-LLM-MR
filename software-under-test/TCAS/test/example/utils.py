import unittest
import os, subprocess, sys

from parameterized import parameterized

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from generate import *

# ==================== GLOBAL VRAIABLES ====================
TCAS_PATH = os.path.join(os.path.dirname(__file__), "..", "..", "src", "tcas.out")

# fmt:off
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
# fmt:on
# ==========================================================


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
            lst = [int(x) for x in f.read().split()]
            tcs.append((lst,))

    return tcs


def run_tcas(vals: list) -> str:
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