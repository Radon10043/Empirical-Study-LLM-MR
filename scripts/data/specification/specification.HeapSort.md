> ### `heap_sort` Function Specification
>
> #### Description
> The `heap_sort` function provides an implementation of the heap sort algorithm for sorting a vector of integers in decreasing order. This function utilizes an auxiliary function `HeapSort`, which performs the sorting on a raw array of integers. After sorting the elements using the heap sort algorithm, it returns the sorted vector.
>
> #### Parameters
> - `vec` (`vector<int>`): A vector of integers to be sorted. This vector is passed by value, which means the function operates on a copy of the original vector, leaving the original vector unchanged.
>
> #### Returns
> - `vector<int>`: A new vector containing the sorted integers in non-decreasing order.
>
> #### Behavior
> - The function first converts the vector into a heap structure by calling the `HeapSort` function with the underlying array data of the vector and its size.
> - It applies the heap sort algorithm, which involves building a heap from the input data and then repeatedly extracting the maximum element from the heap and restoring the heap property until all elements are sorted.
> - The sorted elements are moved into their correct positions in the original array, effectively sorting the entire vector.
> - Finally, the function returns the sorted vector.
>
> #### Usage Notes
> - The input vector can contain any integers, including negative numbers and duplicates.
> - If the input vector is empty or contains a single element, the function will return it as is without any modifications.
> - The function does not modify the original input vector passed to it; instead, it operates on a copy of the vector and returns a new sorted vector.
>
> #### Implementation Details
> - Internally, the function uses the `HeapSort` C++ function which requires a raw pointer to the array and the length of the array as its parameters.
> - Error handling for null pointers or invalid data is managed within the `HeapSort` function by returning the input pointer as is if it points to `NULL` or if the length is non-positive.
> - The `heap_sort` function itself does not include additional error handling since it operates on C++ vectors, which manage their memory and size.