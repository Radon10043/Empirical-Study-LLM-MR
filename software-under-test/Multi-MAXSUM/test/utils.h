#ifndef _HAVE_UTILS_H
#define _HAVE_UTILS_H

#include <vector>

using namespace std;

#define CRASH 0
#define INVALID 0
#define TESTCASE_NUM 1000

typedef struct MultiMAXSUMInput {
    MultiMAXSUMInput(vector<int> vec, int m) : vec(vec), m(m){};
    vector<int> vec;
    int m;
} MultiMAXSUMInput;

vector<MultiMAXSUMInput> gen_tcs_randomly();

#endif