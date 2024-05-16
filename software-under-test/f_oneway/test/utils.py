from random import randint

# fmt:off
# ========== GLOBAL VARIABLES =========
RANGE_GROUPS = [2, 10]      # 数组数量范围
RANGE_SIZE = [1, 1000]      # 数组长度范围
RANGE_VALUE = [-100, 100]   # 数组元素取值范围
# =====================================
# fmt:on


def write_tcs(groups: tuple, filename: str) -> None:
    """将测试数据写入文件

    Parameters
    ----------
    groups : tuple
        测试数据
    filename : str
        文件名
    """
    with open(filename, "w") as f:
        for group in groups:
            f.write(" ".join(map(str, group)) + "\n")


def gen_tcs_randomly(tcs_num: int) -> list:
    """随机生成一定数量的测试数据

    Parameters
    ----------
    tcs_num : int
        测试数据数量

    Returns
    -------
    list
        存储测试数据的列表
    """
    tcs = list()

    for _ in range(tcs_num):
        # Generate multiple random arrays
        group_num = randint(*RANGE_GROUPS)
        groups = list()
        for _ in range(group_num):
            size = randint(*RANGE_SIZE)
            groups.append([randint(*RANGE_VALUE) for _ in range(size)])

        # Append to test cases
        tcs.append(tuple(groups))

    return tcs
