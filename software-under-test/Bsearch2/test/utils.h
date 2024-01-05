#ifndef _HAVE_UTILS_H
#define _HAVE_UTILS_H

#include <vector>

using namespace std;

#define CRASH 0
#define INVALID 0
#define NOT_SATISFIED 0
#define TESTCASE_NUM 1000

typedef struct BSearch2Input {
    BSearch2Input(vector<int> vec, int target) : vec(vec), target(target){};
    vector<int> vec;
    int target;
} BSearch2Input;

vector<BSearch2Input> get_tcs_randomly();

#endif