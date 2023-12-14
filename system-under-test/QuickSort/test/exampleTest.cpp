#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../function.h"

using namespace std;

typedef struct QuickSortInput {
    QuickSortInput(vector<int> vec) : vec(vec){};
    vector<int> vec;
} QuickSortInput;

class QuickSortParamTest : public ::testing::TestWithParam<QuickSortInput> {};

/**
 * @brief Metamorphic Relation 1: Shuffling the elements in the input array, the output will be the same.
 *
 */
TEST_P(QuickSortParamTest, MR1) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    shuffle(follow_vec.begin(), follow_vec.end(), random_device());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 2: Adding a constant to each element in the input array, then each element of the output array will be larger by the constant
 * than the element at the same location of the source input.
 *
 */
TEST_P(QuickSortParamTest, MR2) {
    int constant = 3;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem += constant;

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    for (auto &elem : follow_out)
        elem -= constant;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief  * Metamorphic Relation 3: Multiplying -1 to each element in the input array, then if we multiply -1 to each element of the output array, it should be
 * the same as the source output array, but in reverse order.
 *
 */
TEST_P(QuickSortParamTest, MR3) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem *= -1;

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    for (auto &elem : follow_out)
        elem *= -1;
    reverse(follow_out.begin(), follow_out.end());
    EXPECT_EQ(follow_out, source_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, QuickSortParamTest,
                        testing::Values(QuickSortInput({2, 3, 1, 4, 5}), QuickSortInput({99, 999, 9, 10}), QuickSortInput({2, 4, 6, 8, 1, 2, 4, 2, 64})));