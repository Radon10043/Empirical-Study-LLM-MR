#include <algorithm>
#include <iostream>
#include <random>
#include <fstream>

#include "utils.h"

using namespace std;

/**
 * @brief 随机生成一定数量的测试用例
 *
 * @return vector<GetRangeInput>
 */
vector<GetRangeInput> gen_tcs_randomly() {
    /* 存储测试用例用的数组 */
    vector<GetRangeInput> tcs;

    /* Create a random number generator and seed it with a value */
    mt19937 rng(std::random_device{}());

    /* clang-format off */
    /* Create a distribution, which determines the range of the numbers that generator creates. */
    uniform_int_distribution<int> dist_size(1, 1000),       /* Vector's sise, [1, 1000]     */
                                  dist_value(1, 10000),     /* Value's range, [1, 10000]    */
                                  dist_target(1, 10000);    /* Target's range, [1, 10000]   */
    /* clang-format on */

    /* 构建测试用例 */
    for (int i = 0; i < TESTCASE_NUM; i++) {
        /* 生成随机大小的数组, 数组中的值和目标值也随机决定 */
        vector<int> vec(dist_size(rng));
        for (int j = 0; j < vec.size(); j++)
            vec[j] = dist_value(rng);
        int target = dist_target(rng);

        /* 由于测试二分搜索算法, 因此数组需要升序排序 */
        sort(vec.begin(), vec.end());

        /* 将创建好的测试数据加入tcs */
        tcs.push_back(GetRangeInput(vec, target));
    }

    /* 将生成的测试用例写入文件, 方便调试用 */
    ofstream fout("testcases.txt");
    for (int i = 0; i < tcs.size(); i++) {
        fout << "Testcase " << i << ": " << endl;
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