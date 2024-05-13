#ifndef _HAVE_UTILS_H
#define _HAVE_UTILS_H

#include <vector>

using namespace std;

#define CRASH 0
#define INVALID 0
#define TESTCASE_NUM 1000

typedef struct HeapSortInput {
    HeapSortInput(vector<int> vec) : vec(vec){};
    vector<int> vec;
} HeapSortInput;

void write_tcs(HeapSortInput input, string filename);

vector<HeapSortInput> gen_tcs_randomly();

#endif