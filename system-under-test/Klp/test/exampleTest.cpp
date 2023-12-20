#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "../src/function.h"

using namespace std;

typedef struct KLPInput {
    KLPInput(vector<vector<int>> matrix) : matrix(matrix){};
    vector<vector<int>> matrix;
} KLPInput;

class KLPParamTest : public ::testing::TestWithParam<KLPInput> {};

/**
 * @brief Metamorphic relation 1: Adding a useless key row (all 0s, these cannot open any lock)
 * to the end of the matrix, then the output will not change.
 *
 */
TEST_P(KLPParamTest, MR1) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    follow_matrix.push_back(vector<int>(follow_matrix[0].size()));

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 2: Adding a column with all 1s (the added lock can be opened by any key)
 * to the matrix, then the output will not change.
 *
 */
TEST_P(KLPParamTest, MR2) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    for (auto &row : follow_matrix)
        row.emplace_back(1);

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/* clang-format off */
/**
 * @brief 读取测试用例
 *
 * @return vector<KLPInput>
 */
vector<KLPInput> load_testcases() {

    /* 存储测试用例的根目录 */
    filesystem::path tcs_dir = filesystem::current_path().parent_path().parent_path().append("testcases");

    /* 存储所有测试用例的vector */
    vector<KLPInput> testcases;

    /* 依次读取测试用例的内容并保存 */
    for (auto& tc : filesystem::recursive_directory_iterator(tcs_dir)) {

        ifstream fin(tc.path(), ios::in);
        vector<vector<int>> matrix;
        string line;

        if (fin.is_open()) {
            while (getline(fin, line)) {
                vector<int> row;
                for (auto& c : line) if (c == '0' || c == '1') row.emplace_back(c - '0');
                matrix.push_back(row);
            }
        }

        fin.close();
        testcases.push_back(matrix);

    }

    return testcases;

}
/* clang-format on */

INSTANTIATE_TEST_CASE_P(TrueReturn, KLPParamTest, testing::ValuesIn(load_testcases()));