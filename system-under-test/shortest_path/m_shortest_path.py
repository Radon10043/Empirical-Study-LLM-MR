import os
import time

from m_func import *
import random
import numpy as np
from scipy.sparse.csgraph import shortest_path

# 方阵大小 scale
scale = [[1, 10], [11, 30], [31, 50]]
scaleRandom = [1,50]

# 算法和比例映射
algos = {0: 'FW', 1: 'D', 2: 'BF', 3: 'J'}
proportion = {0: 1, 1: 0.5, 2: 0.33, 3: 0.25, 4: 0.2, 5: 0}

# 路径
data_path = './data/shortest_path/'
result_path = './result/shortest_path/'
base_test_path = './wholeTest/shortest_path/'
test_methods = ['ART', 'ART_Cons_MR', 'Baseline']
# test_methods = ['Baseline']
ART_concrete_time = []
ART_run_time = []
ART_Cons_MR_concrete_time = []
ART_Cons_MR_run_time = []
Baseline_concrete_time = []
Baseline_run_time = []
Random_concrete_time = []
Random_run_time = []

Baseline_Num=[]

def write2file(cases, f_result=None, f_test=None):
    s1 = matrix_format(cases[0][0])
    s1 = s1 + '; method=\"' + cases[0][1] + '\"; directed=\"' + str(cases[0][2]) + '\"\t'
    graph_masked = np.ma.masked_invalid(cases[0][0])
    res_matrix1 = shortest_path(graph_masked, method=cases[0][1], directed=cases[0][2])
    s1 = s1 + matrix_format(res_matrix1)

    s2 = matrix_format(cases[1][0])
    s2 = s2 + '; method=\"' + cases[1][1] + '\"; directed=\"' + str(cases[1][2]) + '\"\t'
    graph_masked = np.ma.masked_invalid(cases[1][0])
    res_matrix2 = shortest_path(graph_masked, method=cases[1][1], directed=cases[1][2])
    s2 = s2 + matrix_format(res_matrix2)
    if f_result:
        output = str(int(judge_matrix_equal(res_matrix1, res_matrix2)))
        f_result.write(s1 + '\n' + s2 + '\n' + output + '\n\n')
    if f_test:
        f_test.write(s1 + '\n' + s2 + '\n')


def fill(result, filled, upper: bool, lower: bool):
    """
    优先填充上三角的矩阵填充法

    :param result: 被填充的结果矩阵
    :param filled: 用来填充的矩阵
    :param upper: 是否填上三角阵
    :param lower: 是否填下三角阵
    :return:
    """
    n = len(result)
    index = 0
    # 是否需要填上三角阵
    if upper:
        for i in range(0, n):
            for j in range(i + 1, n):
                result[i][j] = filled[index]
                index = index + 1

    index = (n ** 2 - n) // 2
    # 是否需要填下三角阵
    if lower:
        for j in range(0, n):
            for i in range(j + 1, n):
                result[i][j] = filled[index]
                index = index + 1


def transfer(case: [int]) -> [[int]]:
    """
    这里只是转换成矩阵，算法选项没有加入

    :param case:
    :return:
    """
    n = random.randint(scale[case[0]][0], scale[case[0]][1])
    # 矩阵需要填充数的个数
    num_of_random = n ** 2 - n
    # 初始化矩阵
    result = np.zeros(shape=(n, n))
    # 填充矩阵
    filled_matrix = np.random.randint(1, 100, size=num_of_random)
    # 0 填充的位置——这里可能有重复值，暂时不考虑
    zero_index = np.random.randint(0, num_of_random, int(num_of_random * proportion[case[3]]))

    # 将 0 填入填充矩阵的对应位置
    for index in zero_index:
        filled_matrix[index] = 0

    # 如果是有向图
    if case[1] == 1:
        # normal
        if case[2] == 0:
            fill(result, filled_matrix, True, True)
        # 上三角
        elif case[2] == 2:
            fill(result, filled_matrix, True, False)
        # 下三角
        elif case[2] == 3:
            fill(result, filled_matrix, False, True)

    # 如果是无向图
    else:
        # normal or 上三角
        if case[2] in [0, 2]:
            fill(result, filled_matrix, True, False)
        # 下三角
        elif case[2] == 3:
            # 填完下三角后，对称一下
            fill(result, filled_matrix, False, True)
            for i in range(0, n):
                for j in range(i + 1, n):
                    result[i][j] = result[j][i]
    # 返回 [matrix, method, directed]
    return [result, algos[case[-1]], case[1]]

def transferRandom():
    n = random.randint(scaleRandom[0], scaleRandom[1])
    # 初始化矩阵
    result = np.zeros(shape=(n, n))
    for i in range(0, n):
        for j in range(0, n):
            result[i][j]=random.randint(0,50)

    for i in range(0, n):
        result[i][i] = 0.0

    case1=0
    for i in range(0, n):
        for j in range(i + 1, n):
            if result[i][j] != result[j][i]:
                case1=1
                break
        if case1==1:
            break

    rand_method = random.randint(0,3)

    # 返回 [matrix, method, directed]
    return [result, algos[rand_method], case1]

# 判断两条抽象测试用例是否满足MR关系
def MR_abstract(abc_i, abc_j):
    for i in range(len(abc_i) - 1):
        if abc_i[i] != abc_j[i]:
            return False
    return True


def transfer_ART(test_case: [int], result_path, test_path):
    """ ART 方法下的转换

    :param test_case: 抽象测试用例集
    :param result_path: 符合MR关系的测试用例的存储路径
    :param test_path: 所有测试用例的存储路径
    :return:
    """
    cases_with_MR = []
    test_cases = []
    start_time = time.time()
    # 将抽象测试用例转换成实际的测试用例
    for s in test_case:
        # 将 str 型的抽象测试用例转换成 [int] 的类型
        case = s.strip().split()
        case = [int(x) for x in case]
        test_cases.append(transfer(case))
    ART_concrete_time.append((time.time()-start_time)*1000)

    start_time = time.time()
    # 将所有测试用例保存
    file = open(test_path, 'a')
    try:
        for case in test_cases:
            s = matrix_format(case[0])
            s = s + '; method=\"' + case[1] + '\"; directed=\"' + str(case[2]) + '\"'
            graph_masked = np.ma.masked_invalid(case[0])
            res_matrix = shortest_path(graph_masked, method=case[1], directed=case[2])
            file.write(s + '\t' + matrix_format(res_matrix) + '\n')
    finally:
        file.close()

    # 判断是实测试用例两两之间否有MR关系
    for i in range(len(test_cases)):
        for j in range(i + 1, len(test_cases)):
            # 因为是对称的，所以只判断一次
            if judge_matrix_equal(test_cases[i][0], test_cases[j][0]):
                cases_with_MR.append([test_cases[i], test_cases[j]])

    if cases_with_MR:
        f_result = open(result_path, 'a')
        try:
            for cases in cases_with_MR:
                write2file(cases, f_result=f_result)
        finally:
            f_result.close()
    ART_run_time.append((time.time() - start_time) /60)

def transfer_random(result_path, test_path,number):
    cases_with_MR = []
    test_cases = []
    start_time = time.time()
    # 将抽象测试用例转换成实际的测试用例
    for i in range(0,int(number)):
        test_cases.append(transferRandom())
    Random_concrete_time.append((time.time()-start_time)*1000)

    start_time = time.time()
    # 将所有测试用例保存
    file = open(test_path, 'a')
    try:
        for case in test_cases:
            s = matrix_format(case[0])
            s = s + '; method=\"' + case[1] + '\"; directed=\"' + str(case[2]) + '\"'
            graph_masked = np.ma.masked_invalid(case[0])
            res_matrix = shortest_path(graph_masked, method=case[1], directed=case[2])
            file.write(s + '\t' + matrix_format(res_matrix) + '\n')
    finally:
        file.close()

    # 判断是实测试用例两两之间否有MR关系
    for i in range(len(test_cases)):
        for j in range(i + 1, len(test_cases)):
            # 因为是对称的，所以只判断一次
            if judge_matrix_equal(test_cases[i][0], test_cases[j][0]):
                cases_with_MR.append([test_cases[i], test_cases[j]])

    if cases_with_MR:
        f_result = open(result_path, 'a')
        try:
            for cases in cases_with_MR:
                write2file(cases, f_result=f_result)
        finally:
            f_result.close()
    Random_run_time.append((time.time() - start_time) /60)

def transfer_ART_Cons_MR(test_case: [int], result_path, test_path):
    cases_with_MR = []
    test_omitted = set(range(len(test_case)))
    test_with_MR = set()
    for i in range(len(test_case)):
        # 将 str 类型的抽象测试用例转换成 [int] 的类型
        test_case[i] = test_case[i].strip().split()
        test_case[i] = [int(x) for x in test_case[i]]
    time2 = 0
    start_time2 = time.time()
    # 判断抽象测试用例两两之间是否有MR关系
    for i in range(len(test_case)):
        for j in range(i + 1, len(test_case)):
            # 因为MR具有对称关系，只要判断一次即可
            if MR_abstract(test_case[i], test_case[j]):
                cases_with_MR.append([test_case[i], test_case[j]])
                test_with_MR.update([i, j])
    time2 = time2 + (time.time() - start_time2)

    time1 = 0
    start_time1 = time.time()
    if cases_with_MR:
        res = []
        # 将抽象测试用例转换成实际的测试用例
        for s in cases_with_MR:
            case = s[0]
            matrix = transfer(case)[0]
            res.append([[matrix, algos[case[-1]], case[2]], [matrix, algos[s[1][-1]], case[2]]])

        f_result = open(result_path, 'a')
        f_test = open(test_path, 'a')
        try:
            for cases in res:
                write2file(cases, f_result, f_test)
        finally:
            f_result.close()
            f_test.close()
    time1 = time1 + (time.time() - start_time1)

    # 将遗漏的不满足MR关系的测试用例加入 f_test
    test_omitted = test_omitted.difference(test_with_MR)
    f_test = open(test_path, 'a')
    try:
        for x in test_omitted:
            start_time1 = time.time()
            case = transfer(test_case[x])
            time1 = time1 + (time.time() - start_time1)
            start_time2 = time.time()
            s = matrix_format(case[0])
            s = s + '; method=\"' + case[1] + '\"; directed=\"' + str(case[2]) + '\"\t'
            graph_masked = np.ma.masked_invalid(case[0])
            res_matrix = shortest_path(graph_masked, method=case[1], directed=case[2])
            f_test.write(s + matrix_format(res_matrix) + '\n')
            time2 = time2 + (time.time() - start_time2)
    finally:
        f_test.close()
    ART_Cons_MR_concrete_time.append(time1*1000)
    ART_Cons_MR_run_time.append(time2/60)


def transfer_Baseline(test_case: [int], result_path, test_path):
    Baseline_Num.append(len(test_case))
    cases_with_MR = []
    test_omitted = set(range(len(test_case)))
    test_with_MR = set()
    for i in range(len(test_case)):
        # 将 str 类型的抽象测试用例转换成 [int] 的类型
        test_case[i] = test_case[i].strip().split()
        test_case[i] = [int(x) for x in test_case[i]]
    time2 = 0
    start_time2 = time.time()
    # 判断抽象测试用例两两之间是否有MR关系
    for i in range(len(test_case)):
        for j in range(i + 1, len(test_case)):
            # 因为MR具有对称关系，只要判断一次即可
            if MR_abstract(test_case[i], test_case[j]):
                cases_with_MR.append([test_case[i], test_case[j]])
                test_with_MR.update([i, j])
    time2 = time2 + (time.time() - start_time2)

    time1 = 0
    start_time1 = time.time()
    if cases_with_MR:
        res = []
        # 将抽象测试用例转换成实际的测试用例
        for s in cases_with_MR:
            case = s[0]
            matrix = transfer(case)[0]
            res.append([[matrix, algos[case[-1]], case[2]], [matrix, algos[s[1][-1]], case[2]]])

        f_result = open(result_path, 'a')
        f_test = open(test_path, 'a')
        try:
            for cases in res:
                write2file(cases, f_result, f_test)
        finally:
            f_result.close()
            f_test.close()
    time1 = time1 + (time.time() - start_time1)

    # 将遗漏的不满足MR关系的测试用例加入 f_test
    test_omitted = test_omitted.difference(test_with_MR)
    f_test = open(test_path, 'a')
    try:
        for x in test_omitted:
            start_time1 = time.time()
            case = transfer(test_case[x])
            time1 = time1 + (time.time() - start_time1)
            start_time2 = time.time()
            s = matrix_format(case[0])
            s = s + '; method=\"' + case[1] + '\"; directed=\"' + str(case[2]) + '\"\t'
            graph_masked = np.ma.masked_invalid(case[0])
            res_matrix = shortest_path(graph_masked, method=case[1], directed=case[2])
            f_test.write(s + matrix_format(res_matrix) + '\n')
            time2 = time2 + (time.time() - start_time2)
    finally:
        f_test.close()
    Baseline_concrete_time.append(time1 * 1000)
    Baseline_run_time.append(time2 / 60)


# 利用字典来调用不同接口函数
transfer_methods = {'ART': transfer_ART, 'ART_Cons_MR': transfer_ART_Cons_MR, 'Baseline': transfer_Baseline}


def main():
    for method in test_methods:
        # 每种测试方法下的目录
        folders = os.listdir(data_path + method)
        # 每种测试方法下的合法目录
        folders = list(filter(is_valid, folders))
        for folder in folders:
            # 当前维度下的测试组
            groups = list(filter(is_valid, os.listdir(data_path + method + '/' + folder)))
            for group in groups:
                # 打开某一组测试用例
                case_path = data_path + method + '/' + folder + '/' + group
                end_path = result_path + method + '/' + folder + '/' + group
                test_path = base_test_path + method + '/' + folder + '/' + group
                case_file = open(case_path)
                # 将原数据覆盖
                end_file = open(end_path, 'w')
                test_file = open(test_path, 'w')
                try:
                    # 将一组测试用例全部放入列表中
                    test_case = case_file.readlines()
                finally:
                    case_file.close()
                    end_file.close()
                    test_file.close()
                # 做相应的步骤
                transfer_methods[method](test_case, end_path, test_path)

def randomMethod(randomList):
    # random_num=[]
    # x1 = 0
    # for i in range(0,30):
    #     x1 = x1 + Baseline_Num[i]
    # random_num.append(x1/30)
    # x1 = 0
    # for i in range(30, 60):
    #     x1 = x1 + Baseline_Num[i]
    # random_num.append(x1 / 30)
    # x1 = 0
    # for i in range(60, 90):
    #     x1 = x1 + Baseline_Num[i]
    # random_num.append(x1 / 30)
    # print(random_num)
    methodList = ["RandomVSCOM","RandomVSCT","RandomVSTRI"]
    i=0
    for degree in range(2, 5):
        for method in methodList:
            for timeya in range(0, 30):
                # 打开某一组测试用例
                end_path = result_path + method + '/testcase' + str(degree) + '/' + str(timeya) + ".txt"
                test_path = base_test_path + method + '/testcase' + str(degree) + '/' + str(timeya) + ".txt"
                # 将原数据覆盖
                end_file = open(end_path, 'w')
                test_file = open(test_path, 'w')
                end_file.close()
                test_file.close()
                # 做相应的步骤
                transfer_random(end_path, test_path, randomList[i])
            i=i+1


if __name__ == '__main__':
    # randomNum = [34,27,52,120,102,206,311,291,581]
    # randomMethod(randomNum)
    main()
    print("ART")
    x1 = 0
    x2 = 0
    x3 = 0
    y1 = 0
    y2 = 0
    y3 = 0
    for i in range(0,30):
        x1 = x1 + ART_concrete_time[i]
    for i in range(30,60):
        x2 = x2 + ART_concrete_time[i]
    for i in range(60,90):
        x3 = x3 + ART_concrete_time[i]
    for i in range(0,30):
        y1 = y1 + ART_run_time[i]
    for i in range(30,60):
        y2 = y2 + ART_run_time[i]
    for i in range(60,90):
        y3 = y3 + ART_run_time[i]
    print(x1)
    print(y1)
    print(x2)
    print(y2)
    print(x3)
    print(y3)
    print("ART_Cons_MR")
    x1 = 0
    x2 = 0
    x3 = 0
    y1 = 0
    y2 = 0
    y3 = 0
    for i in range(0, 30):
        x1 = x1 + ART_Cons_MR_concrete_time[i]
    for i in range(30, 60):
        x2 = x2 + ART_Cons_MR_concrete_time[i]
    for i in range(60, 90):
        x3 = x3 + ART_Cons_MR_concrete_time[i]
    for i in range(0, 30):
        y1 = y1 + ART_Cons_MR_run_time[i]
    for i in range(30, 60):
        y2 = y2 + ART_Cons_MR_run_time[i]
    for i in range(60, 90):
        y3 = y3 + ART_Cons_MR_run_time[i]
    print(x1)
    print(y1)
    print(x2)
    print(y2)
    print(x3)
    print(y3)
    print("Baseline")
    x1 = 0
    x2 = 0
    x3 = 0
    y1 = 0
    y2 = 0
    y3 = 0
    for i in range(0, 30):
        x1 = x1 + Baseline_concrete_time[i]
    for i in range(30, 60):
        x2 = x2 + Baseline_concrete_time[i]
    for i in range(60, 90):
        x3 = x3 + Baseline_concrete_time[i]
    for i in range(0, 30):
        y1 = y1 + Baseline_run_time[i]
    for i in range(30, 60):
        y2 = y2 + Baseline_run_time[i]
    for i in range(60, 90):
        y3 = y3 + Baseline_run_time[i]
    print(x1)
    print(y1)
    print(x2)
    print(y2)
    print(x3)
    print(y3)
    randomMethod()
    print("Random")
    x1 = 0
    x2 = 0
    x3 = 0
    y1 = 0
    y2 = 0
    y3 = 0
    for i in range(0, 30):
        x1 = x1 + Random_concrete_time[i]
    for i in range(30, 60):
        x2 = x2 + Random_concrete_time[i]
    for i in range(60, 90):
        x3 = x3 + Random_concrete_time[i]
    for i in range(0, 30):
        y1 = y1 + Random_run_time[i]
    for i in range(30, 60):
        y2 = y2 + Random_run_time[i]
    for i in range(60, 90):
        y3 = y3 + Random_run_time[i]
    print(x1)
    print(y1)
    print(x2)
    print(y2)
    print(x3)
    print(y3)