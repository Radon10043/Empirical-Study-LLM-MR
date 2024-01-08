#ifndef _HAVE_UTILS_H
#define _HAVE_UTILS_H

#include <vector>

using namespace std;

#define CRASH 0
#define INVALID 0
#define TESTCASE_NUM 1000

typedef struct QuickSortInput {
    QuickSortInput(vector<int> vec) : vec(vec){};
    vector<int> vec;
} QuickSortInput;

vector<QuickSortInput> gen_tcs_randomly();

#endif