#include <gtest/gtest.h>
#include <vector>

#include "../function.h"

using namespace std;

typedef struct ClosestPairInput {
    ClosestPairInput(vector<Point> vec) : vec(vec){};
    vector<Point> vec;
} ClosestPairInput;

class ClosestPairParamTest : public ::testing::TestWithParam<ClosestPairInput> {};

/**
 * Metamorphic relation 1: Add a point to the array, the output should not be larger than before.
 */
TEST_P(ClosestPairParamTest, MR1) {
    /* Get input data */
    ClosestPairInput input = GetParam();
    vector<Point> vec = input.vec;

    /* Get origin output */
    Point *ptr = &vec[0];
    float origin_out = closest(ptr, vec.size());

    /* Construct follow-up input */
    vector<Point> follow_vec = vec;
    follow_vec.push_back({100, 100});

    /* Get follow-up output */
    ptr = &follow_vec[0];
    float follow_out = closest(ptr, follow_vec.size());

    /* Verification */
    EXPECT_GE(origin_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(
    TrueReturn, ClosestPairParamTest,
    testing::Values(ClosestPairInput(
        {{795, 981}, {1905, 4574}, {8891, 665}, {6370, 1396}, {93, 8603}, {302, 7099}, {326, 5318}, {4493, 3977}, {429, 8687}, {9198, 1558}})));