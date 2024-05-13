#include <fstream>
#include <iostream>
#include <random>

#include "utils.h"

using namespace std;

/**
 * @brief 将测试数据写入文件中, 方便调试
 *
 * @param input
 * @param filename
 */
void write_tcs(HeapSortInput input, string filename) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cerr << "Error: cannot open file " << filename << endl;
        return;
    }

    vector<int> vec = input.vec;
    for (auto& val : vec)
        fout << val << ",";
    fout << endl;

    fout.close();
}

/**
 * @brief 随机生成测试数据
 *
 * @return vector<HeapSortInput>
 */
vector<HeapSortInput> gen_tcs_randomly() {
    vector<HeapSortInput> tcs;
    mt19937 rng(random_device{}());

    /* clang-format off */
    uniform_int_distribution<int> dist_size(1, 1000),       /* 数组长度范围 */
                                  dist_value(-1000, 1000);  /* 元素取值范围 */
    /* clang-format on */

    /* 构建测试用例 */
    for (int i = 0; i < TESTCASE_NUM; i++) {
        int size = dist_size(rng);
        vector<int> vec(size);
        for (int j = 0; j < size; j++)
            vec[j] = dist_value(rng);
        tcs.push_back(HeapSortInput(vec));
    }

    return tcs;
}