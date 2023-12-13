#include <algorithm>
#include <gtest/gtest.h>
#include <random>
#include <string>

#include "../function.h"

using namespace std;

typedef struct InterleavingStringInput {
    InterleavingStringInput(string A, string B, string C) : A(A), B(B), C(C){};
    string A, B, C;
} InterleavingStringInput;

class InterleavingStringParamTest : public ::testing::TestWithParam<InterleavingStringInput> {};

/**
 * Metamorphic Relation 1: Adding one same character to the end of A and C, the result will be the same.
 */
TEST_P(InterleavingStringParamTest, MR1) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = isInterleaved(&A[0], &B[0], &C[0]);

    /* Construct follow-up input */
    char ch = 'a';
    string follow_A = A + ch, follow_C = C + ch;

    /* Get follow-up output */
    bool follow_out = isInterleaved(&follow_A[0], &B[0], &follow_C[0]);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, InterleavingStringParamTest,
                        testing::Values(InterleavingStringInput("abc", "def", "adbecf"), InterleavingStringInput("abc", "xyz", "abcxyz"),
                                        InterleavingStringInput("leet", "code", "github")));