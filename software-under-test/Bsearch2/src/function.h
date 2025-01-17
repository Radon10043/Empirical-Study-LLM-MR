#ifndef _HAVE_FUNCTION_H
#define _HAVE_FUNCTION_H

#include <iostream>
#include <vector>
using namespace std;

int p(int a[], int e, int len) {

    int l, h, mid, ret;
    l = 0;
    h = len - 1;
    ret = 0;
    while (h > l) {
        mid = (l + h) / 2;
        if (e == a[mid])
            ret = 1;
        if (e > a[mid])
            l = mid + 1;
        else
            h = mid - 1;
    }

    mid = (l + h) / 2;
    if (ret != 1 && e == a[mid])
        ret = 1;
    return ret;
}

bool bin_search(vector<int> vec, int x) {
    return p(vec.data(), x, vec.size());
}

#endif