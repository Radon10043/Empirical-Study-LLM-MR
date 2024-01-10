"""
Author: Radon
Date: 2024-01-10 21:18:24
LastEditors: Radon
LastEditTime: 2024-01-10 21:20:24
Description: Hi, say something
"""
import os

from random import randint


# fmt:off
# ==================== GLOBAL BARIABLES ====================
TESTCASE_NUM = 1000
RANGE_JOBS   = (1, 100)
# ==========================================================
# fmt:on

def gen_tcs_randomly():
    """随机生成一定数量的测试用例, 并保存到testcases文件夹下"""
    tcs_dir = os.path.join(os.path.dirname(__file__), "..", "testcases")
    if not os.path.exists(tcs_dir):
        os.mkdir(tcs_dir)

    for i in range(TESTCASE_NUM):
        print("\rGenerating testcase " + str(i).zfill(3) + " ...", end="")
        tc_file = os.path.join(tcs_dir, "tc" + str(i).zfill(3) + ".txt")

        f = open(tc_file, mode="w", encoding="utf-8")
        f.write(str(randint(*RANGE_JOBS)) + " " + str(randint(*RANGE_JOBS)) + " " + str(randint(*RANGE_JOBS)))
        f.close()

    print("\nDone!")


if __name__ == "__main__":
    gen_tcs_randomly()