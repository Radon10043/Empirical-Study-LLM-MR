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
void write_tcs(KLPInput input, string filename) {
    ofstream fout(filename);
    vector<vector<int>> matrix = input.matrix;
    int num_r = matrix.size(), num_c = matrix[0].size();
    for (int x = 0; x < num_r; x++) {
        for (int y = 0; y < num_c; y++) {
            fout << matrix[x][y] << ",";
        }
        fout << endl;
    }
}

/**
 * @brief 随机生成测试数据
 *
 * @return vector<KLPInput>
 */
vector<KLPInput> gen_tcs_randomly() {
    vector<KLPInput> tcs;
    mt19937 rng(random_device{}());

    /* clang-format off */
    uniform_int_distribution<int> dist_row(1, 5),   /* 矩阵行取值范围 */
                                  dist_col(1, 5),   /* 矩阵列取值范围 */
                                  dist_value(0, 1); /* 元素取值范围 */
    /* clang-format on */

    /* 构建测试用例 */
    for (int i = 0; i < TESTCASE_NUM; i++) {
        int num_r = dist_row(rng), num_c = dist_col(rng);
        vector<vector<int>> matrix(num_r, vector<int>(num_c));
        for (int x = 0; x < num_r; x++)
            for (int y = 0; y < num_c; y++)
                matrix[x][y] = dist_value(rng);
        tcs.push_back(KLPInput(matrix));
    }

    return tcs;
}