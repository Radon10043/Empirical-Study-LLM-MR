#include <random>
#include <vector>
#include <fstream>
#include <iostream>

#include "utils.h"

using namespace std;

/**
 * @brief 随机生成一定数量的测试用例
 *
 * @return vector<DistinctSubsequenceInput>
 */
vector<DistinctSubsequenceInput> gen_tcs_randomly() {
    vector<DistinctSubsequenceInput> tcs;
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist_len(1, 1000), dist_value(0, 25);

    /* 构建测试用例 */
    for (int i = 0; i < TESTCASE_NUM; i++) {
        int len_s = dist_len(rng), len_t = dist_len(rng);
        string s, t;
        for (int j = 0; j < len_s; j++) {
            s += 'a' + dist_value(rng);
        }
        for (int j = 0; j < len_t; j++) {
            t += 'a' + dist_value(rng);
        }
        tcs.push_back(DistinctSubsequenceInput(s, t));
    }

    /* 保存到文件, 方便调试 */
    ofstream fout("testcases.txt");
    for (int i = 0; i < TESTCASE_NUM; i++) {
        fout << "Testcase " << i << ": " << endl;
        fout << "------------------------------" << endl;
        fout << "s: " << tcs[i].s << endl;
        fout << "t: " << tcs[i].t << endl;
        fout << endl;
    }

    return tcs;
}