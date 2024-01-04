#ifndef _HAVE_CONFIG_H
#define _HAVE_CONFIG_H

#include <vector>
using namespace std;

#define CRASH 0
#define INVALID 0
#define TESTCASE_NUM 1000

typedef struct BSearch1Input {
    BSearch1Input(vector<int> vec, int target) : vec(vec), target(target){};
    vector<int> vec;
    int target;
} BSearch1Input;

vector<BSearch1Input> gen_tcs_randomly();

#endif