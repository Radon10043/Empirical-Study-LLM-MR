#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <vector>

#include "../function.h"

using namespace std;

#define SKIP_CRASH

typedef struct BSearch1Input {
    BSearch1Input(vector<int> vec, int target) : vec(vec), target(target){};
    vector<int> vec;
    int target;
} BSearch1Input;

class BSearchParamTest : public ::testing::TestWithParam<BSearch1Input> {};

INSTANTIATE_TEST_CASE_P(TreuReturn, BSearchParamTest,
                        testing::Values(BSearch1Input({1, 2, 3, 4, 5}, 3), BSearch1Input({1, 2, 3, 4, 5}, 1), BSearch1Input({1, 2, 3, 4, 5}, 99)));