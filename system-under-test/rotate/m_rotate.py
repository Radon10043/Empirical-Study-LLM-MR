import os
import random
import time

import numpy as np
from m_func import *
from scipy import ndimage

# 方阵大小 scale
scale = [[1, 10], [11, 20], [21, 30]]
scaleRandom = [1,30]

# 算法和比例映射
proportion = {0: 1, 1: 0.5, 2: 0.33, 3: 0.25, 4: 0.2, 5: 0}
angles = {0: 90, 1: 180, 2: 270, 3: -270, 4: -180, 5: -90}

# 路径
data_path = './data/rotate/'
result_path = './result/rotate/'
base_test_path = './wholeTest/rotate/'
test_methods = ['ART', 'ART_Cons_MR', 'Baseline']

ART_concrete_time = []
ART_run_time = []
ART_Cons_MR_concrete_time = []
ART_Cons_MR_run_time = []
Baseline_concrete_time = []
Baseline_run_time = []
Random_concrete_time = []
Random_run_time = []

Baseline_Num=[]

def transfer(case: [int]) -> [[int]]:
    m = random.randint(scale[case[0]][0], scale[case[0]][1])
    shape = case[1]
    # 初始化矩阵
    result = np.zeros(shape=(m, m))
    # 填充矩阵
    fill(result, shape, pro=case[2])
    return [result, angles[case[-1]]]

def transferRandom() -> [[int]]:
    m = random.randint(scaleRandom[0], scaleRandom[1])
    # 初始化矩阵
    result = np.zeros(shape=(m, m))
    # 填充矩阵
    for i in range(0, m):
        for j in range(0, m):
            result[i][j] = random.randint(0, 50)

    for i in range(0, m):
        result[i][i] = 0.0

    anglesRandom = random.randint(-360,360)
    return [result, anglesRandom]

def fill(result, shape: int, pro):
    """ 填矩阵
    :param result: 被填充的结果矩阵
    :param shape: 矩阵形状
    :param pro: 0 的占比
    :return:
    """
    m = len(result)

    if shape == 0:
        num_of_random = m * m
        # 填充矩阵
        filled_matrix = np.random.randint(-100, 100, size=num_of_random)
        # 0 填充的位置——这里可能有重复值，暂时不考虑
        zero_index = np.random.randint(0, num_of_random, int(num_of_random * proportion[pro]))

        # 将 0 填入填充矩阵的对应位置
        for index in zero_index:
            filled_matrix[index] = 0

        index = 0
        for i in range(m):
            for j in range(m):
                result[i][j] = filled_matrix[index]
                index += 1

    elif shape == 3:
        filled_matrix = np.random.randint(-100, 100, size=m)
        # 0 填充的位置——这里可能有重复值，暂时不考虑
        zero_index = np.random.randint(0, m, int(m * proportion[pro]))

        # 将 0 填入填充矩阵的对应位置
        for index in zero_index:
            filled_matrix[index] = 0

        for i in range(m):
            result[i][i] = filled_matrix[i]

    else:
        size = (m * m) // 2 + m
        filled_matrix = np.random.randint(-100, 100, size=size)
        zero_index = np.random.randint(0, size, int(m * proportion[pro]))

        # 将 0 填入填充矩阵的对应位置
        for index in zero_index:
            filled_matrix[index] = 0

        index = 0
        if shape == 1:
            for i in range(0, m):
                for j in range(i, m):
                    result[i][j] = filled_matrix[index]
                    index = index + 1

        else:
            for j in range(0, m):
                for i in range(j, m):
                    result[i][j] = filled_matrix[index]
                    index = index + 1


# 同时写入结果文件和MR文件
def write2file(cases, f_result, f_test=None):
    s1 = matrix_format(cases[0][0])
    s1 = s1 + '; rotate angle=\"' + str(cases[0][1]) + '\"\t'
    output1 = ndimage.rotate(cases[0][0], cases[0][1])
    s1 = s1 + matrix_format(output1)

    s2 = matrix_format(cases[1][0])
    s2 = s2 + '; rotate angle=\"' + str(cases[1][1]) + '\"\t'
    output2 = ndimage.rotate(cases[1][0], cases[1][1])
    s2 = s2 + matrix_format(output2)
    if f_result:
        f_result.write(s1 + '\n' + s2 + '\n' + str(int(judge_matrix_equal(output1, output2))) + '\n\n')
    if f_test:
        f_test.write(s1 + '\n' + s2 + '\n')


def MR_real(abc_i, abc_j):
    if judge_matrix_equal(abc_i[0], abc_j[0]) and abs(abc_i[1] - abc_j[1]) == 360:
        return True
    return False


# 判断两条抽象测试用例是否满足MR关系
def MR_abstract(abc_i, abc_j):
    # 抽象矩阵相等
    for i in range(len(abc_i) - 1):
        if abc_i[i] != abc_j[i]:
            return False
    # 最后一个参数相差3
    if abs(abc_i[-1] - abc_j[-1]) == 3:
        return True
    return False


# ART 方法下的转换
def transfer_ART(test_case: [int], result_path, test_path):
    cases_with_MR = []
    test_cases = []
    # 将抽象测试用例转换成实际的测试用例
    start_time = time.time()
    for s in test_case:
        # 将 str 型的抽象测试用例转换成 [int] 的类型
        case = s.strip().split()
        case = [int(x) for x in case]
        test_cases.append(transfer(case))

    ART_concrete_time.append((time.time() - start_time) * 1000)

    start_time = time.time()
    # 将所有测试用例保存
    file = open(test_path, 'a')
    try:
        for case in test_cases:
            s = matrix_format(case[0])
            s = s + '; rotate angle=\"' + str(case[1]) + '\"\t'
            s = s + matrix_format(ndimage.rotate(case[0], case[1])) + '\n'
            file.write(s)
    finally:
        file.close()

    # 判断是实测试用例两两之间否有MR关系
    for i in range(len(test_cases)):
        for j in range(i + 1, len(test_cases)):
            # 因为是对称的，所以只判断一次
            if MR_real(test_cases[i], test_cases[j]):
                cases_with_MR.append([test_cases[i], test_cases[j]])

    if cases_with_MR:
        f_result = open(result_path, 'a')
        try:
            for cases in cases_with_MR:
                write2file(cases, f_result)
        finally:
            f_result.close()
    ART_run_time.append((time.time() - start_time) / 60)

def transfer_random(result_path, test_path,number):
    cases_with_MR = []
    test_cases = []
    # 将抽象测试用例转换成实际的测试用例
    start_time = time.time()
    for i in range(0, int(number)):
        test_cases.append(transferRandom())
    Random_concrete_time.append((time.time() - start_time) * 1000)

    start_time = time.time()
    # 将所有测试用例保存
    file = open(test_path, 'a')
    try:
        for case in test_cases:
            s = matrix_format(case[0])
            s = s + '; rotate angle=\"' + str(case[1]) + '\"\t'
            s = s + matrix_format(ndimage.rotate(case[0], case[1])) + '\n'
            file.write(s)
    finally:
        file.close()

    # 判断是实测试用例两两之间否有MR关系
    for i in range(len(test_cases)):
        for j in range(i + 1, len(test_cases)):
            # 因为是对称的，所以只判断一次
            if MR_real(test_cases[i], test_cases[j]):
                cases_with_MR.append([test_cases[i], test_cases[j]])

    if cases_with_MR:
        f_result = open(result_path, 'a')
        try:
            for cases in cases_with_MR:
                write2file(cases, f_result)
        finally:
            f_result.close()
    Random_run_time.append((time.time() - start_time) / 60)

def transfer_ART_Cons_MR(test_case: [int], result_path, test_path):
    cases_with_MR = []
    test_omitted = set(range(len(test_case)))
    test_with_MR = set()
    time1 = 0
    time2 = 0
    start_time1 = time.time()
    for i in range(len(test_case)):
        # 将 str 类型的抽象测试用例转换成 [int] 的类型
        test_case[i] = test_case[i].strip().split()
        test_case[i] = [int(x) for x in test_case[i]]
    time1 = time1 + (time.time() - start_time1)

    start_time2 = time.time()
    # 判断抽象测试用例两两之间是否有MR关系
    for i in range(len(test_case)):
        for j in range(i + 1, len(test_case)):
            # 因为MR具有对称关系，只要判断一次即可
            if MR_abstract(test_case[i], test_case[j]):
                cases_with_MR.append([test_case[i], test_case[j]])
                test_with_MR.update([i, j])
    time2 = time2 + (time.time() - start_time2)

    if cases_with_MR:
        res = []
        # 将抽象测试用例转换成实际的测试用例
        start_time1 = time.time()
        for s in cases_with_MR:
            case = s[0]
            matrix = transfer(case)[0]
            res.append([[matrix, angles[case[-1]]], [matrix, angles[s[1][-1]]]])
        time1 = time1 + (time.time() - start_time1)
        start_time2 = time.time()
        f_result = open(result_path, 'a')
        f_test = open(test_path, 'a')
        try:
            for cases in res:
                write2file(cases, f_result, f_test)
        finally:
            f_result.close()
            f_test.close()
        time2 = time2 + (time.time() - start_time2)

    test_omitted = test_omitted.difference(test_with_MR)
    f_test = open(test_path, 'a')
    try:
        for x in test_omitted:
            start_time1 = time.time()
            case = transfer(test_case[x])
            time1 = time1 + (time.time() - start_time1)
            start_time2 = time.time()
            s = matrix_format(case[0])
            s = s + '; rotate angle=\"' + str(case[1]) + '\"\t'
            s = s + matrix_format(ndimage.rotate(case[0], case[1])) + '\n'
            f_test.write(s)
            time2 = time2 + (time.time() - start_time2)
    finally:
        f_test.close()
    ART_Cons_MR_concrete_time.append(time1 * 1000)
    ART_Cons_MR_run_time.append(time2 / 60)


def transfer_Baseline(test_case: [int], result_path, test_path):
    Baseline_Num.append(len(test_case))
    cases_with_MR = []
    test_omitted = set(range(len(test_case)))
    test_with_MR = set()
    time1 = 0
    start_time1 = time.time()
    for i in range(len(test_case)):
        # 将 str 类型的抽象测试用例转换成 [int] 的类型
        test_case[i] = test_case[i].strip().split()
        test_case[i] = [int(x) for x in test_case[i]]
    time1 = time1 + (time.time() - start_time1)
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

    if cases_with_MR:
        res = []
        # 将抽象测试用例转换成实际的测试用例
        start_time1 = time.time()
        for s in cases_with_MR:
            case = s[0]
            matrix = transfer(case)[0]
            res.append([[matrix, angles[case[-1]]], [matrix, angles[s[1][-1]]]])
        time1 = time1 + (time.time() - start_time1)
        start_time2 = time.time()
        f_result = open(result_path, 'a')
        f_test = open(test_path, 'a')
        try:
            for cases in res:
                write2file(cases, f_result, f_test)
        finally:
            f_result.close()
            f_test.close()
        time2 = time2 + (time.time() - start_time2)

    test_omitted = test_omitted.difference(test_with_MR)
    f_test = open(test_path, 'a')
    try:
        for x in test_omitted:
            start_time1 = time.time()
            case = transfer(test_case[x])
            time1 = time1 + (time.time() - start_time1)
            start_time2 = time.time()
            s = matrix_format(case[0])
            s = s + '; rotate angle=\"' + str(case[1]) + '\"\t'
            s = s + matrix_format(ndimage.rotate(case[0], case[1])) + '\n'
            f_test.write(s)
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

    # methodList = ["RandomVSCOM","RandomVSCT","RandomVSTRI"]
    methodList = ["RandomVSTRI"]
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
    # randomNum = [39, 37, 74, 151, 145, 291, 432, 432,864]
    # randomMethod(randomNum)
    main()
    print("ART")
    x1 = 0
    x2 = 0
    x3 = 0
    y1 = 0
    y2 = 0
    y3 = 0
    for i in range(0, 30):
        x1 = x1 + ART_concrete_time[i]
    for i in range(30, 60):
        x2 = x2 + ART_concrete_time[i]
    for i in range(60, 90):
        x3 = x3 + ART_concrete_time[i]
    for i in range(0, 30):
        y1 = y1 + ART_run_time[i]
    for i in range(30, 60):
        y2 = y2 + ART_run_time[i]
    for i in range(60, 90):
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
    randomNum = [432, 432,864]
    randomMethod(randomNum)
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
