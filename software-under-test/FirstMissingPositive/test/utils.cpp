#include <fstream>
#include <random>
#include <algorithm>

#include "utils.h"

using namespace std;

vector<FMPInput> gen_tcs_randomly() {
    vector<FMPInput> tcs;
    mt19937 rng(random_device{}());

    /* clang-format off */
    uniform_int_distribution<int> dist_size(1, 1000),   /* 数组大小范围 */
                                  dist_value(-1000, 1000);  /* 元素取值范围 */
    /* clang-format on */

    /* 构建测试用例 */
    for (int i = 0; i < TESTCASE_NUM; i++) {
        int size = dist_size(rng);
        vector<int> vec;
        vec.reserve(size);
        for (int j = 0; j < size; j++)
            vec.push_back(dist_value(rng));
        sort(vec.begin(), vec.end());
        tcs.push_back(FMPInput(vec));
    }

    /* 将测试用力保存到文件, 方便调试 */
    ofstream fout("testcases.txt");
    for (int i = 0; i < TESTCASE_NUM; i++) {
        fout << "Testcase " << i << ": ";
        fout << "------------------------------" << endl;
        for (int j = 0; j < tcs[i].vec.size(); j++)
            fout << tcs[i].vec[j] << ",";
        fout << endl << endl;
    }

    return tcs;
}