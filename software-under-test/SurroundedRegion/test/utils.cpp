#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "utils.h"

using namespace std;

/**
 * @brief 将测试数据写入文件, 调试用
 *
 * @param input
 * @param filename
 */
void write_tcs(SurroundedRegionInput input, string filename) {
    ofstream fout(filename);
    for (auto &row : input.vec)
        fout << row << endl;
    fout << endl;
    fout.close();
}

/**
 * @brief 随机生成测试数据
 *
 * @return vector<SurroundedRegionInput>
 */
vector<SurroundedRegionInput> gen_tcs_randomly() {
    vector<SurroundedRegionInput> tcs;
    vector<char> chars = {'X', 'O'};
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist_size(1, 100);
    uniform_int_distribution<int> dist_char(0, chars.size() - 1);

    /* 构建测试用例 */
    for (int i = 0; i < TESTCASE_NUM; i++) {
        int num_r = dist_size(rng), num_c = dist_size(rng);
        vector<string> vec(num_r, string(num_c, '.'));
        for (auto &row : vec)
            for (auto &c : row)
                c = chars[dist_char(rng)];
        tcs.push_back(SurroundedRegionInput(vec));
    }

    return tcs;
}