#ifndef _HAVE_FUNCTION_H
#define _HAVE_FUNCTION_H

#include <vector>
#include <iostream>
using namespace std;

void swap(int* a, int* c)
{
    int t = *a;
    *a = *c;
    *c = t;
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high];  // selecting last element as pivot
    int i = (low - 1);  // index of smaller element
 
    for (int j = low; j <= high- 1; j++)
    {
        // If the current element is smaller than or equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
/*  
    a[] is the array, p is starting index, that is 0, 
    and r is the last index of array.  
*/
int* quicksort(int a[], int p, int r)    
{
    if(p < r)
    {
        int q;
        q = partition(a, p, r);
        quicksort(a, p, q-1);
        quicksort(a, q+1, r);
    }
    return a;
}

/**
 * @brief Quick sort
 *
 * @param vec
 * @return vector<int>
 */
vector<int> quick_sort(vector<int> vec) {
    quicksort(&vec[0], 0, vec.size() - 1);
    return vec;
}

#endif