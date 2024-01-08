#ifndef _HAVE_UTILS_H
#define _HAVE_UTILS_H

#include <vector>
#include <string>

using namespace std;

#define CRASH 0
#define INVALID 0
#define TESTCASE_NUM 1000

typedef struct SurroundedRegionInput {
    SurroundedRegionInput(vector<string> vec) : vec(vec){};
    vector<string> vec;
} SurroundedRegionInput;

vector<SurroundedRegionInput> gen_tcs_randomly();

#endif