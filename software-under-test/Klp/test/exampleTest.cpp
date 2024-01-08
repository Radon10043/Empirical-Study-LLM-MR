#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

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

INSTANTIATE_TEST_CASE_P(TrueReturn, KLPParamTest, testing::ValuesIn(gen_tcs_randomly()));