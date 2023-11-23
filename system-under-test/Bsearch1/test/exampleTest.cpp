#include <gtest/gtest.h>
#include <vector>

#include "../function.h"

using namespace std;

typedef struct BSearch1Input {
    BSearch1Input(vector<int> vec, int target) : vec(vec), target(target) {};
    vector<int> vec;
    int target;
} BSearch1Input;

class BSearchParamTest : public::testing::TestWithParam<BSearch1Input> {

};

/**
 * Metamorphic relation 1: Add an element to the end of the array and keep the array in
 * ascending order, the output should be unchanged or greater.
 */
TEST_P(BSearchParamTest, MR1) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.emplace_back(vec.back() + 1);

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_LE(origin_out, follow_out);
}

/**
 * Metamorphic relation 2: Multiply all elements in the array and the element to be located by a constant,
 * the output should remain the same.
 */
TEST_P(BSearchParamTest, MR2) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    int constant = 2;
    vector<int> follow_vec = vec;
    for (int& val : follow_vec)
        val *= constant;
    int follow_target = target * constant;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TreuReturn, BSearchParamTest, testing::Values(
    BSearch1Input({1,2,3,4,5}, 3),
    BSearch1Input({1,2,3,4,5}, 1),
    BSearch1Input({1,2,3,4,5}, 99)
));