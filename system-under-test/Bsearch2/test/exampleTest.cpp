#include <gtest/gtest.h>
#include <vector>

#include "../function.h"

using namespace std;

typedef struct BSearch2Input {
    BSearch2Input(vector<int> vec, int target) : vec(vec), target(target){};
    vector<int> vec;
    int target;
} BSearch2Input;

class BSearchParamTest : public ::testing::TestWithParam<BSearch2Input> {};

/**
 * @brief Metamorphic relation 1: If the target value is already in the array, add an element greater than the max value in array to the end of the array, and
 * the output should be unchanged.
 *
 */
TEST_P(BSearchParamTest, MR1) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    if (!source_out)
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.emplace_back(vec.back() + 1);

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 2: Multiply all elements in the array and the element to be located by a constant, the output should remain the same.
 *
 */
TEST_P(BSearchParamTest, MR2) {
    /* Get source input */
    BSearch2Input input = GetParam();
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
                        testing::Values(BSearch2Input({1, 2, 3, 4, 5}, 3), BSearch2Input({1, 2, 3, 4, 5}, 1), BSearch2Input({1, 2, 3, 4, 5}, 99)));