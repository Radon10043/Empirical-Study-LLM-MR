#ifndef _HAVE_UTILS_H
#define _HAVE_UTILS_H

#include <vector>

using namespace std;

#define CRASH 0
#define INVALID 0
#define TESTCASE_NUM 1000

typedef struct RSAInput {
    RSAInput(int m, int e, int p, int q) : m(m), e(e), p(p), q(q) {}
    int m, e, p, q;
} RSAInput;

vector<RSAInput> gen_tcs_randomly();

#endif