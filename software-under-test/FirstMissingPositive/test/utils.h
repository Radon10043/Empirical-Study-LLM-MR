#ifndef _HAVE_UTILS_H
#define _HAVE_UTILS_H

#include <vector>
#include <iostream>
using namespace std;

#define CRASH 0
#define INVALID 0
#define TESTCASE_NUM 1000

typedef struct FMPInput {
    FMPInput(vector<int> vec) : vec(vec){};
    vector<int> vec;
} FMPInput;

vector<FMPInput> gen_tcs_randomly();

#endif