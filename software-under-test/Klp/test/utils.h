#ifndef _HAVE_UTILS_H
#define _HAVE_UTILS_H

#include <iostream>
#include <vector>

using namespace std;

#define CRASH 0
#define INVALID 0
#define TESTCASE_NUM 1000

typedef struct KLPInput {
    KLPInput(vector<vector<int>> matrix) : matrix(matrix){};
    vector<vector<int>> matrix;
} KLPInput;

vector<KLPInput> gen_tcs_randomly();

#endif