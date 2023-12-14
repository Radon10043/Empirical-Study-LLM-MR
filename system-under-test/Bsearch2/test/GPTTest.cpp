#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <vector>

#include "../function.h"

using namespace std;

#define SKIP_CRASH

typedef struct BSearch2Input {
    BSearch2Input(vector<int> vec, int target) : vec(vec), target(target){};
    vector<int> vec;
    int target;
} BSearch2Input;

class BSearchParamTest : public ::testing::TestWithParam<BSearch2Input> {};

INSTANTIATE_TEST_CASE_P(TrueReturn, BSearchParamTest,
                        testing::Values(BSearch2Input({1, 2, 3, 4, 5}, 3), BSearch2Input({1, 2, 3, 4, 5}, 1), BSearch2Input({1, 2, 3, 4, 5}, 99), BSearch2Input({1,1,2,2,3,3,4,4,5,5}, 2)));