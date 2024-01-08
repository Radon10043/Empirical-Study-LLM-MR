#include <algorithm>
#include <gtest/gtest.h>
#include <random>
#include <string>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class InterleavingStringParamTest : public ::testing::TestWithParam<InterleavingStringInput> {};

/**
 * @brief Metamorphic Relation 1: Adding one same character to the end of A and C, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR1) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    char ch = 'a';
    string follow_A = A + ch, follow_C = C + ch;

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, InterleavingStringParamTest, testing::ValuesIn(gen_tcs_randomly()));