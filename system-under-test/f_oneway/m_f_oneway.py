import os
import time

import scipy.stats as stats
import random
from m_func import *

# 方差theta 、长度length、均值mean 的取值范围
theta = [[0, 10], [10, 30], [30, 50]]
length = [[1, 10], [11, 30], [31, 50]]
mean = [[-100, 0], [0, 100]]

# 路径
data_path = './data/f_oneway/'
result_path = './result/f_oneway/'
base_test_path = './wholeTest/f_oneway/'
test_methods = ['ART_Cons', 'ART_Cons_MR', 'Baseline']

ART_concrete_time = []
ART_run_time = []
ART_Cons_MR_concrete_time = []
ART_Cons_MR_run_time = []
Baseline_concrete_time = []
Baseline_run_time = []
Random_concrete_time = []
Random_run_time = []

def list2file(cases, f_result=None, f_test=None):
    source = matrix_format(cases[0])
    follow = matrix_format(cases[1])
    res1 = stats.f_oneway(*cases[0]).pvalue
    res2 = stats.f_oneway(*cases[1]).pvalue
    if f_result:
        f_result.write(source + '\t' + str(res1) + '\n')
        f_result.write(follow + '\t' + str(res2) + '\n' + str(int(res1 == res2)) + '\n\n')
    if f_test:
        f_test.write(source + '\t' + str(res1) + '\n')
        f_test.write(follow + '\t' + str(res2) + '\n')


def MR_real(abc_i, abc_j):
    """ 判断两条实测试用例是否满足MR关系
    因为 f_oneway 的结果和a b c中数据的顺序无关，所以先对其排序，然后直接比较即可

    :param abc_i: 第一条实测试用例
    :param abc_j: 第二条实测试用例
    :return:
    """
    for temp in abc_i:
        temp.sort()
    for temp in abc_j:
        temp.sort()

    # if any([judge_list_equal(abc_i[0], abc_j[1]) and judge_list_equal(abc_i[1], abc_j[0]) and judge_list_equal(abc_i[2], abc_j[2]),
    #         judge_list_equal(abc_i[0], abc_j[2]) and judge_list_equal(abc_i[2], abc_j[0]) and judge_list_equal(abc_i[1], abc_j[1]),
    #         judge_list_equal(abc_i[1], abc_j[2]) and judge_list_equal(abc_i[2], abc_j[1]) and judge_list_equal(abc_i[0], abc_j[0])]):
    #     return True
    if judge_list_equal(abc_i[0], abc_j[1]) and judge_list_equal(abc_i[1], abc_j[0]) and judge_list_equal(abc_i[2], abc_j[2]):
        return True
    else:
        return False


def MR_abstract(abc_i, abc_j):
    """ 判断两条抽象测试用例是否满足MR关系

    :param abc_i:
    :param abc_j:
    :return:
    """
    # if any([abc_i[0] == abc_j[1] and abc_i[1] == abc_j[0] and abc_i[2] == abc_j[2],
    #         abc_i[0] == abc_j[2] and abc_i[2] == abc_j[0] and abc_i[1] == abc_j[1],
    #         abc_i[1] == abc_j[2] and abc_i[2] == abc_j[1] and abc_i[0] == abc_j[0]]):
    #     return True
    if abc_i[0] == abc_j[1] and abc_i[1] == abc_j[0] and abc_i[2]==abc_j[2]:
        return True
    return False


def transfer(case):
    """ 将一条抽象测试用例转换成一条实测试用例

    :param case:
    :return:
    """
    th = random.uniform(theta[case[0]][0], theta[case[0]][1])
    mean_a = random.uniform(mean[case[1]][0], mean[case[1]][1])
    mean_b = random.uniform(mean[case[2]][0], mean[case[2]][1])
    mean_c = random.uniform(mean[case[3]][0], mean[case[3]][1])
    len_a = random.randint(length[case[4]][0], length[case[4]][1])
    len_b = random.randint(length[case[5]][0], length[case[5]][1])
    len_c = random.randint(length[case[6]][0], length[case[6]][1])
    a = stats.norm.rvs(loc=mean_a, scale=th, size=len_a)
    b = stats.norm.rvs(loc=mean_b, scale=th, size=len_b)
    c = stats.norm.rvs(loc=mean_c, scale=th, size=len_c)
    return [a, b, c]

def transferRandom():
    #随机生成一条实测试用例
    th = random.uniform(0, 50)
    mean_a = random.uniform(-100, 100)
    mean_b = random.uniform(-100, 100)
    mean_c = random.uniform(-100, 100)
    len_a = random.randint(1, 50)
    len_b = random.randint(1, 50)
    len_c = random.randint(1, 50)
    a = stats.norm.rvs(loc=mean_a, scale=th, size=len_a)
    b = stats.norm.rvs(loc=mean_b, scale=th, size=len_b)
    c = stats.norm.rvs(loc=mean_c, scale=th, size=len_c)
    return [a, b, c]

def transfer_ART(test_case: [int], result_path, test_path):
    """ ART 方法下的转换

    :param test_case: 抽象测试用例集
    :param result_path: 符合MR关系的测试用例的存储路径
    :param test_path: 所有测试用例的存储路径
    :return:
    """
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
            s = matrix_format(case)
            file.write(s + '\t')
            file.write(str(stats.f_oneway(*case).pvalue) + '\n\n')
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
            for list_case in cases_with_MR:
                list2file(list_case, f_result=f_result)
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
            s = matrix_format(case)
            file.write(s + '\t')
            file.write(str(stats.f_oneway(*case).pvalue) + '\n')
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
            for list_case in cases_with_MR:
                list2file(list_case, f_result=f_result)
        finally:
            f_result.close()
    Random_run_time.append((time.time() - start_time) / 60)


def transfer_ART_Cons_MR(test_case: [int], result_path, test_path):
    """ ART_Cons_MR 方法下的转换

    :param test_case: 抽象测试用例集
    :param result_path: 符合MR关系的测试用例的存储路径
    :param test_path: 所有测试用例的存储路径
    :return:
    """
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
            a, b, c = transfer(case)
            # 看满足哪条MR关系
            # if s[0][0] == s[1][1] and s[0][1] == s[1][0]:
            #     res.append([[a, b, c], [b, a, c]])
            # elif s[0][0] == s[1][2] and s[0][2] == s[1][0]:
            #     res.append([[a, b, c], [c, b, a]])
            # else:
            #     res.append([[a, b, c], [a, c, b]])
            res.append([[a, b, c], [b, a, c]])

        f_result = open(result_path, 'a')
        f_test = open(test_path, 'a')
        try:
            for list_case in res:
                list2file(list_case, f_result, f_test)
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
            s = matrix_format(case)
            f_test.write(s + '\t' + str(stats.f_oneway(*case).pvalue) + '\n\n')
            time2 = time2 + (time.time() - start_time2)
    finally:
        f_test.close()
    ART_Cons_MR_concrete_time.append(time1 * 1000)
    ART_Cons_MR_run_time.append(time2 / 60)


# Baseline 方法下的转换
def transfer_Baseline(test_case: [int], result_path, test_path):
    # 存满足 MR 的实际测试用例
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
            a, b, c = transfer(case)
            # 看满足哪条MR关系
            # if s[0][0] == s[1][1] and s[0][1] == s[1][0]:
            #     res.append([[a, b, c], [b, a, c]])
            # elif s[0][0] == s[1][2] and s[0][2] == s[1][0]:
            #     res.append([[a, b, c], [c, b, a]])
            # else:
            #     res.append([[a, b, c], [a, c, b]])
            res.append([[a, b, c], [b, a, c]])

        f_result = open(result_path, 'a')
        f_test = open(test_path, 'a')
        try:
            for list_case in res:
                list2file(list_case, f_result, f_test)
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
            s = matrix_format(case)
            f_test.write(s + '\t' + str(stats.f_oneway(*case).pvalue) + '\n\n')
            time2 = time2 + (time.time() - start_time2)
    finally:
        f_test.close()
    Baseline_concrete_time.append(time1 * 1000)
    Baseline_run_time.append(time2 / 60)


# 利用字典来调用不同接口函数
transfer_methods = {'ART_Cons': transfer_ART, 'ART_Cons_MR': transfer_ART_Cons_MR, 'Baseline': transfer_Baseline}


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


# 验证和输入顺序无关的例子
# a = [0.28865636, -1.47371801, -0.74615039, -0.8956755, 1.0428089, -0.28445148, -0.27224358, 0.06852419, 1.78770504,
#      -0.0472857]
# b = [1.95866329, 1.76770129, -0.09322308, -0.4419681, 0.10771382, 1.04902273, -1.40323904, 0.10392299, 0.01264551,
#      -2.00075058]
# c = [1.08886624, -0.85965024, 0.35828826, 0.10294662, -0.9196048, 1.0326629, -1.17716434, 0.52116222, 0.93825409,
#      1.42281138]
# p1 = stats.f_oneway(a[::-1], b, c).pvalue
# p2 = stats.f_oneway(a, c, b).pvalue
# p3 = stats.f_oneway(b, c, a).pvalue
# print(p1, p2, p3)
# 0.8138626875448547 0.8138626875448547 0.8138626875448547

if __name__ == '__main__':
    # randomNum = [15, 14, 27, 43, 40, 79, 107, 100, 203]
    # randomMethod(randomNum)
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

