"""
Author: Radon
Date: 2024-01-10 21:23:15
LastEditors: Radon
LastEditTime: 2024-01-24 19:50:01
Description: Hi, say something
"""
import os

from random import randint


# fmt:off
# ==================== GLOBAL VRAIABLES ====================
TETSCASE_NUM           = 1000
RANGE_VALUE            = (0, 1000)
RANGE_ALT_LAYER_VALUE  = (0, 3)
RANGE_OTEHER_RAC       = (0, 2)
RANGE_OTHER_CAPABILITY = (1, 2)
RANGE_CLIMB_INHIBIT    = (0, 1)
# ==========================================================
# fmt:on


def gen_tcs_randomly():
    """随机生成一定数量的测试用例, 并保存到文件"""
    tcs_dir = os.path.join(os.path.dirname(__file__), "..", "testcases")
    if not os.path.exists(tcs_dir):
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


if __name__ == "__main__":
    gen_tcs_randomly()
