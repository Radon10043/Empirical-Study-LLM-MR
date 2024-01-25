import cv2 as cv
import numpy as np

# fmt:off
# ========== GLOBAL VARIABLES =========
TESTCASE_NUM = 1000     # 测试用例的数量
IMAGE_HEIGHT = 256      # 图像高度
IMAGE_WIDTH = 256       # 图像宽度
RANGE_ANGLE = (-360, 360)   # 旋转角度的范围
# =====================================
# fmt:on


def gen_tcs_randomly() -> list:
    """随机生成一定数量的测试用例

    Returns
    -------
    list
        存储测试用例的列表
    """
    testcases = list()
    for i in range(TESTCASE_NUM):
        print("\rGenerating testcases: {}/{}".format(i + 1, TESTCASE_NUM), end="")
        img = np.random.randint(0, 256, size=(IMAGE_HEIGHT, IMAGE_WIDTH, 3), dtype=np.uint8)
        angle = np.random.uniform(*RANGE_ANGLE)
        testcases.append((img, angle))
    print("\nDone!")
    return testcases