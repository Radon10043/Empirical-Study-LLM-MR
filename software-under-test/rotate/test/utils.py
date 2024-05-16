import cv2 as cv
import numpy as np

# fmt:off
# ========== GLOBAL VARIABLES =========
RANGE_HEIGHT = (64, 128)    # 图像高度范围
RANGE_WIDTH  = (64, 128)    # 图像宽度范围
RANGE_ANGLE  = (-360, 360)  # 旋转角度的范围
# =====================================
# fmt:on


def gen_tcs_randomly(tcs_num: int) -> list:
    """随机生成一定数量的测试数据

    Parameters
    ----------
    tcs_num : int
        测试数据的数量

    Returns
    -------
    list
        存储测试数据的列表
    """
    testcases = list()
    for i in range(tcs_num):
        print("\rGenerating testcases: {}/{}".format(i + 1, tcs_num), end="")
        height = np.random.randint(*RANGE_HEIGHT)
        width = np.random.randint(*RANGE_WIDTH)
        angle = np.random.uniform(*RANGE_ANGLE)
        img = np.random.randint(0, 256, size=(height, width, 3), dtype=np.uint8)
        testcases.append((img, angle))
    print("\nDone!")
    return testcases
