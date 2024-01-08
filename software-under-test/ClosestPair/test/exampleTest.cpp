#include <gtest/gtest.h>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class ClosestPairParamTest : public ::testing::TestWithParam<ClosestPairInput> {};

/**
 * @brief Metamorphic relation 1: Add a point to the array, the output should not be larger than before.
 *
 */
TEST_P(ClosestPairParamTest, MR1) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec = vec;
    follow_vec.push_back({100, 100});

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_GE(source_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, ClosestPairParamTest, testing::ValuesIn(gen_tcs_randomly()));