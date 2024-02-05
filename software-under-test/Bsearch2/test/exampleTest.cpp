#include <gtest/gtest.h>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class BSearchParamTest : public ::testing::TestWithParam<BSearch2Input> {};

/**
 * @brief Metamorphic relation 1: Multiplying all the numbers (including the numbers in the array and the searching number), then the output should be the same.
 *
 */
TEST_P(BSearchParamTest, MR1) {
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

INSTANTIATE_TEST_CASE_P(TrueReturn, BSearchParamTest, testing::ValuesIn(get_tcs_randomly()));