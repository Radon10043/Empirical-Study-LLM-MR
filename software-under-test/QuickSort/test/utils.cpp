#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "utils.h"

using namespace std;

vector<QuickSortInput> gen_tcs_randomly() {
    vector<QuickSortInput> tcs;
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist_size(1, 1000);
    uniform_int_distribution<int> dist_value(-1000, 1000);

    /* 构建测试用例 */
    for (int i = 0; i < TESTCASE_NUM; i++) {
        int size = dist_size(rng);
        vector<int> vec(size);
        for (auto &v : vec)
            v = dist_value(rng);
        tcs.push_back(vec);
    }

    /* 写入文件, 方便调试 */
    ofstream fout("testcases.txt");
    for (int i = 0; i < tcs.size(); i++) {
        fout << "Testcase " << i << ": " << endl;
        fout << "------------------------------" << endl;
        fout << "vec    : ";
        for (auto& v : tcs[i].vec)
            fout << v << ",";
        fout << endl << endl;
    }
    fout.close();

    return tcs;
}