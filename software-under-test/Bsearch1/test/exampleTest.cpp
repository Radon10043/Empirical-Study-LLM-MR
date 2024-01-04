#include <gtest/gtest.h>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class BSearchParamTest : public ::testing::TestWithParam<BSearch1Input> {};

/**
 * @brief Metamorphic relation 1: Add an element to the end of the array and keep the array in
 * ascending order, the output should be unchanged or greater.
 *
 */
TEST_P(BSearchParamTest, MR1) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.emplace_back(vec.back() + 1);

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_LE(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 2: Multiply all elements in the array and the element to be located by a constant,
 * the output should remain the same.
 *
 */
TEST_P(BSearchParamTest, MR2) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 2;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val *= constant;
    int follow_target = target * constant;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, BSearchParamTest,
                        testing::ValuesIn(gen_tcs_randomly()));