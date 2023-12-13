#include <gtest/gtest.h>
#include <vector>

#include "../function.h"

using namespace std;

typedef struct MultiMAXSUMInput {
    MultiMAXSUMInput(vector<int> vec, int m) : vec(vec), m(m){};
    vector<int> vec;
    int m;
} MultiMAXSUMInput;

class MultiMAXSUMParamTest : public ::testing::TestWithParam<MultiMAXSUMInput> {};

/**
 * Metamorphic Relation 1: Adding one number at the end of the array, the follow-up output should be the same as or larger than the source output.
 */
TEST_P(MultiMAXSUMParamTest, MR1) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = solve(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.push_back(source_vec.back());

    /* Get follow-up output */
    int follow_out = solve(follow_vec, source_m);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, MultiMAXSUMParamTest,
                        testing::Values(MultiMAXSUMInput({1, 2, 3, 4, 5}, 3), MultiMAXSUMInput({1, 2, 4, 5, 6, 7}, 4), MultiMAXSUMInput({1, 3, 5, 7, 9}, 2)));