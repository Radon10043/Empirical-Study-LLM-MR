#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "utils.h"

using namespace std;

vector<MultiMAXSUMInput> gen_tcs_randomly() {
    vector<MultiMAXSUMInput> tcs;
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist_size(2, 1000),
                                  dist_val(-1000, 1000);

    /* 构造测试用例 */
    for (int i = 0; i < TESTCASE_NUM; i++) {
        int size = dist_size(rng);
        vector<int> vec(size);
        for (int j = 0; j < size; j++)
            vec[j] = dist_val(rng);

        uniform_int_distribution<int> dist_m(1, size - 1);
        int m = dist_m(rng);

        tcs.push_back(MultiMAXSUMInput(vec, m));
    }

    /* 输出到文件, 方便调试 */
    ofstream fout("testcases.txt");
    for (int i = 0; i < TESTCASE_NUM; i++) {
        fout << "Testcase " << i << ": " << endl;
        fout << "------------------------------" << endl;
        fout << "vec: ";
        for (auto &val : tcs[i].vec)
            fout << val << ",";
        fout << endl;
        fout << "m  : " << tcs[i].m << endl << endl;
    }

    return tcs;
}