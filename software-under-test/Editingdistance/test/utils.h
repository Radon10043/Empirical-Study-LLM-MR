#ifndef _HAVE_UTILS_H
#define _HAVE_UTILS_H

#include <vector>
#include <string>

using namespace std;

#define CRASH 0
#define INVALID 0
#define TESTCASE_NUM 1000

typedef struct EditingdistanceInput {
    EditingdistanceInput(string str1, string str2) : str1(str1), str2(str2){};
    string str1, str2;
} EditingdistanceInput;

vector<EditingdistanceInput> gen_tcs_randomly();

#endif