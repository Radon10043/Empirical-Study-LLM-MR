#include <algorithm>
#include <gtest/gtest.h>
#include <random>
#include <string>

#include "../function.h"

using namespace std;

typedef struct FMPInput {
    FMPInput(vector<int> vec) : vec(vec){};
    vector<int> vec;
} FMPInput;

class FMPInputParamTest : public ::testing::TestWithParam<FMPInput> {};

/**
 * @brief Metamorphic Relation 1: Adding one integer to the source array, which is identical to
 * one element of the original array, the output should be the same.
 *
 */
TEST_P(FMPInputParamTest, MR1) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.push_back(source_vec.front());

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 2: Shuffling the elements in the input array, the output will be the same.
 *
 */
TEST_P(FMPInputParamTest, MR2) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    shuffle(follow_vec.begin(), follow_vec.end(), random_device());

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, FMPInputParamTest, testing::Values(FMPInput({1, 2, 3, 4, 5}), FMPInput({1, 2, 4, 5, 6, 7}), FMPInput({1, 3, 5, 7, 9})));