#include <gtest/gtest.h>
#include <string>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class EditingdistanceParamTest : public ::testing::TestWithParam<EditingdistanceInput> {};

/**
 * @brief Metamorphic relation 1: Add a character to the end of str1, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR1) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    string follow_str1 = str1.append("a");

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, EditingdistanceParamTest, testing::ValuesIn(gen_tcs_randomly()));