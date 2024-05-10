#include <fstream>
#include <iostream>
#include <random>

#include "utils.h"

// using namespace std;

/**
 * @brief 生成一定数量的测试用例
 *
 * @return vector<ClosestPairInput>
 */
vector<ClosestPairInput> gen_tcs_randomly() {
    vector<ClosestPairInput> tcs;
    mt19937 rng(random_device{}());

    /* clang-format off */
    uniform_int_distribution<int> dist_size(2, 100),   /* Range of vector's size */
                                  dist_value(-1000, 1000);  /* Range of value */
    /* clang-format on */

    /* 构建测试用例 */
    for (int i = 0; i < TESTCASE_NUM; i++) {
        int size = dist_size(rng);
        vector<pair<int, int>> vec;
        vec.reserve(size);
        for (int j = 0; j < size; j++) {
            int x = dist_value(rng), y = dist_value(rng);
            vec.emplace_back(dist_value(rng), dist_value(rng));
        }
        tcs.emplace_back(vec);
    }

    /* 将测试用例保存到文件, 方便调试 */
    ofstream fout("testcases.txt");
    for (int i = 0; i < TESTCASE_NUM; i++) {
        fout << "Testcase " << i << ": " << endl;
        fout << "------------------------------" << endl;
        fout << "vec: ";
        for (int j = 0; j < tcs[i].vec.size(); j++) {
            fout << "(" << tcs[i].vec[j].first << ", " << tcs[i].vec[j].second << "), ";
        }
        fout << endl << endl;
    }
    fout.close();

    return tcs;
}
