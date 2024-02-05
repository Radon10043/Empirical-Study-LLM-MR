> ### `quick_sort` Function Specification
>
> #### Description
> The `quick_sort` function is a C++ implementation of the Quick Sort algorithm, designed to sort a `std::vector<int>` in ascending order. Quick Sort is a divide-and-conquer algorithm that picks an element as a pivot and partitions the given array around the picked pivot.
>
> #### Function Signature
> ```c++
> vector<int> quick_sort(vector<int> vec);
> ```
>
> #### Parameters
> - `vec` (`vector<int>`): A vector of integers that needs to be sorted.
>
> #### Returns
> - (`vector<int>`): A new vector containing all elements from the input vector, sorted in ascending order.
>
> #### Logic
> 1. **Partition**: The function selects the last element of the array as the pivot, places the pivot element at its correct position in the sorted array, and places all smaller elements to the left of the pivot and all greater elements to the right of the pivot.
>
> 2. **Recursion**: The function then recursively applies the above steps to the sub-arrays formed by partitioning.
>
> 3. **Base Case**: The recursion ends when the sub-array has fewer than two elements, as a single element (or no element) is already sorted.
>
> #### Helper Functions
> - `void swap(int* a, int* c)`: Swaps the values of two integers pointed by `a` and `c`.
> - `int partition(int arr[], int low, int high)`: Partitions the array `arr[]` in the range from `low` to `high` using `arr[high]` as pivot.
> - `int* quicksort(int a[], int p, int r)`: Sorts the elements of the array `a[]` in the range from `p` to `r` using the Quick Sort algorithm. This function is used recursively.
>
> #### Notes
> - The `quick_sort` function acts as a wrapper for the `quicksort` function, enabling sorting of `std::vector<int>` directly, which makes it more convenient for C++ users.
> - Quick Sort's average and worst-case time complexities are O(n log n) and O(n^2), respectively. However, its practical performance is often better than its worst-case performance would suggest.
> - This implementation uses the Lomuto partition scheme, which is easier to understand and implement but generally performs less efficiently than the Hoare partition scheme.
> - The sorting is done in-place, minimizing the need for additional memory beyond the input vector.