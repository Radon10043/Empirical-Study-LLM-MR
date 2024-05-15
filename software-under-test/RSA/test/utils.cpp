#include <algorithm>
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
void write_tcs(RSAInput input, string filename) {
    ofstream fout(filename);
    fout << "m: " << input.m << endl;
    fout << "e: " << input.e << endl;
    fout << "p: " << input.p << endl;
    fout << "q: " << input.q << endl;
    fout << endl;
    fout.close();
}

/**
 * @brief 随机生成测试数据
 *
 * @return vector<RSAInput>
 */
vector<RSAInput> gen_tcs_randomly() {
    vector<RSAInput> tcs;
    mt19937 rng(random_device{}());

    uniform_int_distribution<int> dist1(0, prime_nums.size() - 1);
    uniform_int_distribution<int> dist2(0, 1000000);

    /* 构建测试用例 */
    for (int i = 0; i < TESTCASE_NUM; i++) {
        int p = prime_nums[dist1(rng)], q = prime_nums[dist1(rng)];
        int e = 2;
        for (; e < (p - 1) * (q - 1) / 2; e++) {
            if (__gcd(e, (p - 1) * (q - 1)) == 1) {
                break;
            }
        }
        int m = dist2(rng);
        tcs.push_back(RSAInput(m, e, p, q));
    }

    return tcs;
}
