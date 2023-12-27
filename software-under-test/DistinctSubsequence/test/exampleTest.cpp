#include <gtest/gtest.h>
#include <string>

#include "../src/function.h"

using namespace std;

typedef struct DistinctSubseqenceInput {
    DistinctSubseqenceInput(string s, string t) : s(s), t(t){};
    string s, t;
} DistinctSubseqenceInput;

class DistinctSubsequenceParamTest : public ::testing::TestWithParam<DistinctSubseqenceInput> {};

/**
 * Metamorphic relation 1: Add a character to the end of s, the output should be the same or larger.
 */
TEST_P(DistinctSubsequenceParamTest, MR1) {
    /* Get source input */
    DistinctSubseqenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    string follow_s = s.append("a");

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, DistinctSubsequenceParamTest, testing::Values(
    DistinctSubseqenceInput("abbccc", "abc"),
    DistinctSubseqenceInput("rabbbit", "rabbit"),
    DistinctSubseqenceInput("babgbag", "bag")
));