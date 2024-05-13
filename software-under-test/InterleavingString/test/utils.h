#ifndef _HAVE_UTILS_H
#define _HAVE_UTILS_H

#include <iostream>
#include <vector>

using namespace std;

#define CRASH 0
#define INVALID 0
#define TESTCASE_NUM 1000

typedef struct InterleavingStringInput {
    InterleavingStringInput(string A, string B, string C) : A(A), B(B), C(C){};
    string A, B, C;
} InterleavingStringInput;

void write_tcs(InterleavingStringInput tcs, string filename);

vector<InterleavingStringInput> gen_tcs_randomly();

#endif