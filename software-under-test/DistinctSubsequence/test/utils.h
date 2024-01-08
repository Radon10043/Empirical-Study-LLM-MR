#ifndef _HAVE_UTILS_H
#define _HAVE_UTILS_H

#include <vector>
#include <string>

using namespace std;

#define CRASH 0
#define INVALID 0
#define TESTCASE_NUM 1000

typedef struct DistinctSubseqenceInput {
    DistinctSubseqenceInput(string s, string t) : s(s), t(t){};
    string s, t;
} DistinctSubseqenceInput;

vector<DistinctSubseqenceInput> gen_tcs_randomly();

#endif