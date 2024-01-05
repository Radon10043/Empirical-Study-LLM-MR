#ifndef _HAVE_UTILS_H
#define _HAVE_UTILS_H

#include <vector>
using namespace std;

#define CRASH 0
#define INVALID 0
#define TESTCASE_NUM 1000

typedef struct GetRangeInput {
    GetRangeInput(vector<int> vec, int target) : vec(vec), target(target){};
    vector<int> vec;
    int target;
} GetRangeInput;

vector<GetRangeInput> gen_tcs_randomly();

#endif