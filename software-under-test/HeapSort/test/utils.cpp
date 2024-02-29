#include <random>
#include <fstream>
#include <iostream>

#include "utils.h"

using namespace std;

vector<HeapSortInput> gen_tcs_randomly() {
    vector<HeapSortInput> tcs;
    mt19937 rng(random_device{}());

    /* clang-format off */
    uniform_int_distribution<int> dist_size(1, 1000),       /* 数组长度范围 */
                                  dist_value(-1000, 1000);      /* 元素取值范围 */
    /* clang-format on */

    /* 构建测试用例 */
    for (int i = 0; i < TESTCASE_NUM; i++) {
        int size = dist_size(rng);
        vector<int> vec(size);
        for (int j = 0; j < size; j++)
            vec[j] = dist_value(rng);
        tcs.push_back(HeapSortInput(vec));
    }

    /* 写入文件, 方便调试 */
    ofstream fout("testcases.txt");
    for (int i = 0; i < TESTCASE_NUM; i++) {
        fout << "Testcase " << i << ": " << endl;
        fout << "------------------------------" << endl;
        fout << "vec: ";
        for (int j = 0; j < tcs[i].vec.size(); j++)
            fout << tcs[i].vec[j] << ",";
        fout << endl << endl;
    }

    return tcs;
}