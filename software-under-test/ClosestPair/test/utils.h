#ifndef _HAVE_UTILS_H
#define _HAVE_UTILS_H

#include <iostream>
#include <vector>

using namespace std;

#define CRASH 0
#define INVALID 0
#define TESTCASE_NUM 1000

typedef struct ClosestPairInput {
    ClosestPairInput(vector<pair<int, int>> vec) : vec(vec){};
    vector<pair<int, int>> vec;
} ClosestPairInput;

vector<ClosestPairInput> gen_tcs_randomly();

#endif