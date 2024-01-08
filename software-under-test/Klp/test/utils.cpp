#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "utils.h"

using namespace std;

vector<KLPInput> gen_tcs_randomly() {
    vector<KLPInput> tcs;
    mt19937 rng(random_device{}());

    /* clang-format off */
    uniform_int_distribution<int> dist_size(1, 100), /* 矩阵大小取值范围 */
                                  dist_value(0, 1);   /* 元素取值范围 */
    /* clang-format on */

    /* 构建测试用例 */
    for (int i = 0; i < TESTCASE_NUM; i++) {
        int num_r = dist_size(rng), num_c = dist_size(rng);
        vector<vector<int>> matrix(num_r, vector<int>(num_c));
        for (int x = 0; x < num_r; x++)
            for (int y = 0; y < num_c; y++)
                matrix[x][y] = dist_value(rng);
        tcs.push_back(KLPInput(matrix));
    }

    /* 写入文件, 方便调试 */
    ofstream fout("testcases.txt");
    for (int i = 0; i < TESTCASE_NUM; i++) {
        vector<vector<int>> matrix = tcs[i].matrix;
        int num_r = matrix.size(), num_c = matrix[0].size();
        fout << "Testcase " << i << ": " << endl;
        fout << "------------------------------" << endl;
        for (int x = 0; x < num_r; x++) {
            for (int y = 0; y < num_c; y++) {
                fout << matrix[x][y] << ",";
            }
            fout << endl;
        }
        fout << endl;
    }

    return tcs;
}