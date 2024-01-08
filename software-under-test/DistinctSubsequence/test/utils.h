#ifndef _HAVE_UTILS_H
#define _HAVE_UTILS_H

#include <vector>
#include <string>

using namespace std;

#define CRASH 0
#define INVALID 0
#define TESTCASE_NUM 1000

typedef struct DistinctSubsequenceInput {
    DistinctSubsequenceInput(string s, string t) : s(s), t(t){};
    string s, t;
} DistinctSubsequenceInput;

vector<DistinctSubsequenceInput> gen_tcs_randomly();

#endif