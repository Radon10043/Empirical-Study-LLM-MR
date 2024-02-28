#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "utils.h"

using namespace std;

vector<InterleavingStringInput> gen_tcs_randomly() {
    vector<InterleavingStringInput> tcs;
    mt19937 rng(random_device{}());

    /* clang-format off */
    uniform_int_distribution<int> dist_size(1, 10),    /* 数据长度范围 */
                                  dist_value(0, 25),     /* 字符范围 */
                                  dist_prob(1, 100);     /* 交错概率 */
    /* clang-format on */

    /* 构建测试用例 */
    for (int i = 0; i < TESTCASE_NUM; i++) {
        int size_A = dist_size(rng), size_B = dist_size(rng);
        string A = "", B = "", C = "";
        for (int j = 0; j < size_A; j++) {
            A += 'a' + dist_value(rng);
        }
        for (int j = 0; j < size_B; j++) {
            B += 'a' + dist_value(rng);
        }

        /* 生成交错字符串和随机字符串的概率分别是50% */
        bool interleave = dist_prob(rng) > 50;
        if (interleave) {
            int i = 0, j = 0;
            while (i < size_A && j < size_B) {
                C += A[i++];
                C += B[j++];
            }
        } else {
            int size_C = dist_size(rng);
            for (int j = 0; j < size_C; j++) {
                C += 'a' + dist_value(rng);
            }
        }
        tcs.push_back(InterleavingStringInput(A, B, C));
    }

    /* 输出到文件, 方便调试 */
    ofstream fout("testcases.txt");
    for (int i = 0; i < TESTCASE_NUM; i++) {
        fout << "Testcase " << i << ": " << endl;
        fout << "------------------------------" << endl;
        fout << "A: " << tcs[i].A << endl;
        fout << "B: " << tcs[i].B << endl;
        fout << "C: " << tcs[i].C << endl;
        fout << endl;
    }

    return tcs;
}