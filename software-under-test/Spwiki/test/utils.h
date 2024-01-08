#ifndef _HAVE_UTILS_H
#define _HAVE_UTILS_H

#include <vector>

using namespace std;

#define CRASH 0
#define INVALID 0
#define TESTCASE_NUM 1000

typedef struct SpwikiInput {
    SpwikiInput(vector<vector<int>> edges, int src, int dst, int n) : edges(edges), src(src), dst(dst), n(n) {}
    vector<vector<int>> edges;
    int src, dst, n;
} SpwikiInput;

vector<SpwikiInput> gen_tcs_randomly();

#endif