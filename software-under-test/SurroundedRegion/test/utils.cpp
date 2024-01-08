#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "utils.h"

using namespace std;

vector<SurroundedRegionInput> gen_tcs_randomly() {
    vector<SurroundedRegionInput> tcs;
    vector<char> chars = {'X', 'O'};
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist_size(3, 100);
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

    /* 写入文件, 方便调试 */
    ofstream fout("testcases.txt");
    for (int i = 0; i < TESTCASE_NUM; i++) {
        fout << "Testcase " << i << ": " << endl;
        fout << "------------------------------" << endl;
        for (auto &row : tcs[i].vec)
            fout << row << endl;
        fout << endl;
    }

    return tcs;
}