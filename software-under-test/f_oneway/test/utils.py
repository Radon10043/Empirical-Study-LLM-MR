from random import randint

# fmt:off
# ========== GLOBAL VARIABLES =========
RANGE_SIZE = [1, 1000]      # 数组长度范围
RANGE_VALUE = [-100, 100]   # 数组元素取值范围
# =====================================
# fmt:on


def gen_tcs_randomly(tcs_num: int) -> list:
    """随机生成一定数量的测试用例

    Parameters
    ----------
    tcs_num : int
        测试用例数量

    Returns
    -------
    list
        存储测试用例的列表
    """
    tcs = list()

    for _ in range(tcs_num):
        # Generate two random arrays
        size1 = randint(*RANGE_SIZE)
        size2 = randint(*RANGE_SIZE)
        g1 = [randint(*RANGE_VALUE) for _ in range(size1)]
        g2 = [randint(*RANGE_VALUE) for _ in range(size2)]

        # Append to test cases
        tcs.append((g1, g2))

    # 写入文件, 方便调试
    with open("testcases.txt", "w") as f:
        for i in range(tcs_num):
            f.write(f"Testcase {i}:\n------------------------------\n")
            f.write(f"g1: {tcs[i][0]}\n")
            f.write(f"g2: {tcs[i][1]}\n\n")

    return tcs
