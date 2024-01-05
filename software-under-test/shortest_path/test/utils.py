from random import randint, choice
from time import time

# fmt:off
# ========== GLOBAL VARIABLES =========
TESTCASE_NUM = 1000     # 测试用例的数量
MAX_VERTICES = 100      # 图中节点的最大数量
MAX_WEIGHT = 1000       # 图中边的最大权重
# =====================================
# fmt:on


def gen_graph_randomly(num_v: int) -> list:
    """随机生成图

    Parameters
    ----------
    num_v : int
        图中节点的数量

    Returns
    -------
    list
        存储了图的邻接矩阵的列表

    Notes
    -----
    _description_
    """
    # 存储图的邻接矩阵的列表
    graph = [[0 for _ in range(num_v)] for _ in range(num_v)]

    # 为图中每个边随机赋值
    for i in range(num_v):
        for j in range(num_v):
            if i == j:
                graph[i][j] = 0
            else:
                graph[i][j] = randint(1, MAX_WEIGHT)

    return graph


def gen_tcs_randomly() -> list:
    """随机生成测试用例,包含图, 起点, 终点和方法

    Returns
    -------
    list
        存储了所有测试用例的列表

    Notes
    -----
    _description_
    """
    # 存储测试用例的列表
    tcs = list()

    for _ in range(TESTCASE_NUM):
        # 节点数量
        num_v = randint(1, MAX_VERTICES)
        graph = [[0 for _ in range(num_v)] for _ in range(num_v)]

        # 随机生成图
        graph = gen_graph_randomly(num_v)

        # 随机生成起点和终点
        src = randint(0, num_v - 1)
        dst = randint(0, num_v - 1)

        # 随机生成要使用的方法
        method = choice(["FW", "D"])

        tcs.append((graph, src, dst, method))

    # 将测试用例保存到文件, 方便调试用
    with open("testcases.txt", mode="w") as f:
        for i in range(len(tcs)):
            f.write(f"TESTCASE {i}:\n--------------------\nGRAPH: {tcs[i][0]}\nSRC: {tcs[i][1]}\nDST: {tcs[i][2]}\nMETHOD: {tcs[i][3]}\n\n")

    return tcs
