#include <random>
#include <vector>

#include "utils.h"

using namespace std;

/**
 * @brief 随机生成一定数量的测试用例
 *
 * @return vector<EditingdistanceInput>
 */
vector<EditingdistanceInput> gen_tcs_randomly() {
    vector<EditingdistanceInput> tcs;
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist_len(1, 10), dist_value(0, 25);

    for (int i = 0; i < TESTCASE_NUM; i++) {
        int len_str1 = dist_len(rng), len_str2 = dist_len(rng);
        string str1, str2;
        for (int j = 0; j < len_str1; j++) {
            str1 += 'a' + dist_value(rng);
        }
        for (int j = 0; j < len_str2; j++) {
            str2 += 'a' + dist_value(rng);
        }
        tcs.push_back(EditingdistanceInput(str1, str2));
    }

    return tcs;
}