#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "utils.h"

using namespace std;

vector<RSAInput> gen_tcs_randomly() {
    vector<RSAInput> tcs;
    mt19937 rng(random_device{}());

    uniform_int_distribution<int> dist1(0, prime_nums.size() - 1);
    uniform_int_distribution<int> dist2(0, 1000000);

    /* 构建测试用例 */
    for (int i = 0; i < TESTCASE_NUM; i++) {
        int p = prime_nums[dist1(rng)], q = prime_nums[dist1(rng)], e = prime_nums[dist1(rng)];
        int m = dist2(rng);
        tcs.push_back(RSAInput(m, e, p, q));
    }

    /* 写入文件, 方便调试 */
    ofstream fout("testcases.txt");
    for (int i = 0; i < TESTCASE_NUM; i++) {
        fout << "Testcase " << i << ": " << endl;
        fout << "------------------------------" << endl;
        fout << "m: " << tcs[i].m << endl;
        fout << "e: " << tcs[i].e << endl;
        fout << "p: " << tcs[i].p << endl;
        fout << "q: " << tcs[i].q << endl;
        fout << endl;
    }
    fout.close();

    return tcs;
}
