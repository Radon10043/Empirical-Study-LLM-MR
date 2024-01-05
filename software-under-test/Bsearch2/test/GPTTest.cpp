#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

#define SKIP_CRASH

class BSearchParamTest : public ::testing::TestWithParam<BSearch2Input> {};

INSTANTIATE_TEST_CASE_P(TrueReturn, BSearchParamTest, testing::Values(get_tcs_randomly()));