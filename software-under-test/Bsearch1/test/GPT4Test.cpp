#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class GetRangeParamTest : public ::testing::TestWithParam<GetRangeInput> {};


INSTANTIATE_TEST_CASE_P(TrueReturn, GetRangeParamTest,
                        testing::ValuesIn(gen_tcs_randomly()));