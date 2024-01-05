#include <iostream>
#include <random>
#include <algorithm>
#include <fstream>

#include "utils.h"

using namespace std;

vector<BSearch2Input> get_tcs_randomly() {
    /* 存储测试用例的数组 */
    vector<BSearch2Input> tcs;

    /* 创建一个随机数生成器 */
    mt19937 rng(std::random_device{}());

    /* clang-format off */
    /* 各个数值的取值范围 */
    uniform_int_distribution<int> dist_size(1, 100),        /* Vector's size, [1, 1000] */
                                  dist_value(1, 1000),      /* Value's size, [1, 1000]  */
                                  dist_target(1, 1000);     /* Target's size, [1, 1000] */
    /* clang-format on */

    /* 构建测试用例 */
    for (int i = 0; i < TESTCASE_NUM; i++) {
        /* 随机生成测试用例 */
        int size = dist_size(rng);
        vector<int> vec(size);
        for (int j = 0; j < size; j++)
            vec[j] = dist_value(rng);
        int target = dist_target(rng);

        /* 测的是二分搜索算法, 需要数组升序排序 */
        sort(vec.begin(), vec.end());

        /* 将测试用例加入数组 */
        tcs.push_back(BSearch2Input(vec, target));
    }

    /* 将生成的测试用例写入文件, 方便调试用 */
    ofstream fout("testcases.txt");
    for (int i = 0; i < TESTCASE_NUM; i++) {
        fout << "Testcase " << i << ":" << endl;
        fout << "------------------------------" << endl;
        fout << "vec    : ";
        for (int j = 0; j < tcs[i].vec.size(); j++)
            fout << tcs[i].vec[j] << ",";
        fout << endl;
        fout << "target : " << tcs[i].target << endl << endl;;
    }
    fout.close();

    return tcs;
}