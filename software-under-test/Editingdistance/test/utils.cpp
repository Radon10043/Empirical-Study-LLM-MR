#include <random>
#include <vector>
#include <fstream>

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
    uniform_int_distribution<int> dist_len(1, 8), dist_value(0, 25), dist_num(1, 100);
    int upper_prob = 50;    // 添加的字符为大写字母的概率

    /* 构建测试用例 */
    for (int i = 0; i < TESTCASE_NUM; i++) {
        int len_str1 = dist_len(rng), len_str2 = dist_len(rng);
        string str1, str2;
        for (int j = 0; j < len_str1; j++) {
            if (dist_num(rng) > upper_prob)
                str1 += 'a' + dist_value(rng);
            else
                str1 += 'A' + dist_value(rng);
        }
        for (int j = 0; j < len_str2; j++) {
            if (dist_num(rng) > upper_prob)
                str2 += 'a' + dist_value(rng);
            else
                str2 += 'A' + dist_value(rng);
        }
        tcs.push_back(EditingdistanceInput(str1, str2));
    }

    /* 保存测试用例到文件, 方便调试 */
    ofstream fout("testcases.txt");
    for (int i = 0; i < tcs.size(); i++) {
        fout << "Testcase " << i << ": " << endl;
        fout << "------------------------------" << endl;
        fout << "str1: " << tcs[i].str1 << endl;
        fout << "str2: " << tcs[i].str2 << endl << endl;
    }
    fout.close();

    return tcs;
}