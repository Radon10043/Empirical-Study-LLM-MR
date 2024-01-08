#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class RSAParamTest : public ::testing::TestWithParam<RSAInput> {};

/**
 * @brief Metamorphic Relation 1: Keeping p, q and e the same, giving a new plaintext which is equals to m + p*q, the ciphertext is the same.
 *
 */
TEST_P(RSAParamTest, MR1) {
    /* Get source input */
    RSAInput input = GetParam();
    int source_m = input.m, source_e = input.e, source_p = input.p, source_q = input.q;

    /* Get source output */
    long long source_out = candp(source_m, source_e, source_p, source_q);

    /* Construct follow-up input */
    int follow_m = source_m + source_p * source_q;

    /* Get follow-up output */
    long long follow_out = candp(follow_m, source_e, source_p, source_q);

    /* Verification */
    ASSERT_EQ(source_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, RSAParamTest, testing::ValuesIn(gen_tcs_randomly()));