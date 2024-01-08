#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class SurroundedRegionParamTest : public ::testing::TestWithParam<SurroundedRegionInput> {};

/**
 * @brief Metamorphic Relation 1: Adding one row with all 'O's to the end of the matrix, then the output should be ncreased by one row with all 'O's.
 *
 */
TEST_P(SurroundedRegionParamTest, MR1) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    int cols = source_vec[0].length();
    vector<string> follow_vec = source_vec;
    follow_vec.push_back(string(cols, 'O'));

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    source_out.push_back(string(cols, 'O'));
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 2: Adding one column with all 'O's to the end of the matrix , then the output should be increased by one column with all 'O's.
 *
 */
TEST_P(SurroundedRegionParamTest, MR2) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    for (auto& row : follow_vec) row.push_back('O');

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    for (auto& row : source_out) row.push_back('O');
    EXPECT_EQ(follow_out, source_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, SurroundedRegionParamTest, testing::ValuesIn(gen_tcs_randomly()));