#include <gtest/gtest.h>
#include <string>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class EditingdistanceParamTest : public ::testing::TestWithParam<EditingdistanceInput> {};

/**
 * @brief Metamorphic relation 1: Add a character to the end of str1 (the character is not exist in str2), the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR1) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    char c = 'a';
    while (c <= 'z' && str2.find(c) != string::npos)
        c++;
    if (c > 'z')
        return;
    string follow_str1 = str1 + c;

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, EditingdistanceParamTest, testing::ValuesIn(gen_tcs_randomly()));