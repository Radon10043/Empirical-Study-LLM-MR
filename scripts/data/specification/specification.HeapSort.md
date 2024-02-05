> ### `heap_sort` Function Specification
>
> #### Description
> The `heap_sort` function is an implementation of the heap sort algorithm, which is a comparison-based sorting technique based on a binary heap data structure. This function sorts an array of integers in ascending order. The algorithm organizes the input array into a heap, then repeatedly extracts the minimum element from the heap and rebuilds the heap until the array is sorted.
>
> #### Function Signatures
> C++ Version:
> ```c++
> int* HeapSort(int data[], int length);
> ```
>
> Wrapper for `std::vector<int>`:
> ```c++
> vector<int> heap_sort(vector<int> vec);
> ```
>
> #### Parameters
> - `data[]`: A pointer to the first element of an array of integers to be sorted.
> - `length`: The number of elements in the array.
> - `vec`: A `std::vector<int>` containing the integers to be sorted.
>
> #### Returns
> - The C++ version (`HeapSort`) returns a pointer to the first element of the sorted array.
> - The `std::vector<int>` version (`heap_sort`) returns a sorted `std::vector<int>`.
>
> #### Logic
> 1. **Building a Min Heap**: The initial part of the algorithm builds a min heap from the input array. This is done by considering the array as a complete binary tree and then adjusting each subtree to follow the min heap property (parent node is smaller than its child nodes) starting from the last non-leaf node all the way up to the root node.
>
> 2. **Heap Rebuilding and Element Swapping**: After the heap is built, the algorithm repeatedly swaps the first element of the array (which is the smallest element of the heap) with the last element of the current heap, reduces the heap size by one, and then rebuilds the heap to ensure the heap property is maintained. This process is repeated until the heap size is reduced to 0, resulting in a sorted array.
>
> 3. **Sorting in Place**: The sorting is performed in place, meaning that no additional arrays are used for the sorting process. The input array is modified to contain the sorted elements.
>
> #### Notes
> - The provided `HeapSort` function operates directly on C-style arrays, while the `heap_sort` function provides a more modern C++ interface by accepting and returning a `std::vector<int>`.
> - The algorithm's time complexity is O(n log n) in the worst case, making it efficient for sorting large datasets.
> - The heap sort is not a stable sort; that is, the relative order of equal elements may not be preserved.
> - The implementation assumes that the input is valid; specifically, it does not check for `NULL` pointers or negative array lengths in the `HeapSort` function, which could lead to undefined behavior if invalid input is provided.