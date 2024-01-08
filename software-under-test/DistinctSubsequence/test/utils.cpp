#include <random>
#include <vector>

#include "utils.h"

using namespace std;

/**
 * @brief 随机生成一定数量的测试用例
 *
 * @return vector<DistinctSubseqenceInput>
 */
vector<DistinctSubseqenceInput> gen_tcs_randomly() {
    vector<DistinctSubseqenceInput> tcs;
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist_len(1, 1000), dist_value(0, 25);

    for (int i = 0; i < TESTCASE_NUM; i++) {
        int len_s = dist_len(rng), len_t = dist_len(rng);
        string s, t;
        for (int j = 0; j < len_s; j++) {
            s += 'a' + dist_value(rng);
        }
        for (int j = 0; j < len_t; j++) {
            t += 'a' + dist_value(rng);
        }
        tcs.push_back(DistinctSubseqenceInput(s, t));
    }

    return tcs;
}