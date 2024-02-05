> ### `bin_search` Function Specification
>
> #### Description
> The `bin_search` function is a wrapper that utilizes an underlying C++ function `p` to perform a binary search on a sorted array (or vector) to determine if a specified element exists within that array. The function operates by comparing the target value `x` against the elements of the array, narrowing down the search range until the value is found or the search range is exhausted.
>
> #### Signature
> ```c++
> bool bin_search(vector<int> vec, int x);
> ```
>
> #### Parameters
> - `vec` (`vector<int>`): A vector of integers which should be sorted in ascending order for the binary search algorithm to work correctly.
> - `x` (`int`): The value to search for within the vector.
>
> #### Returns
> - `bool`: Returns `true` if `x` is found within `vec`; otherwise, returns `false`.
>
> #### Logic
> 1. **Initialization**: The search starts with two markers, `l` (low) and `h` (high), which initially point to the start and end of the array, respectively.
> 2. **Binary Search**:
>    - The midpoint `mid` is calculated as the average of `l` and `h`.
>    - If the element at `mid` is equal to `x`, the function sets `ret` to `1`, indicating success.
>    - If `x` is greater than the element at `mid`, the search continues in the upper half of the current range by setting `l` to `mid + 1`.
>    - If `x` is less than the element at `mid`, the search continues in the lower half by setting `h` to `mid - 1`.
>    - This process repeats until `h` is no longer greater than `l`.
> 3. **Final Check**:
>    - After exiting the loop, a final check is performed to catch cases where the target is located at the final `mid` point calculated after the loop.
>    - If `ret` is not already set to `1` and the element at the final `mid` is equal to `x`, `ret` is set to `1`.
> 4. **Return Value**:
>    - The function returns `true` if `x` was found (`ret` is `1`); otherwise, it returns `false`.
>
> #### Notes
> - The vector `vec` must be sorted in ascending order before calling `bin_search` since the underlying binary search algorithm relies on the sorted nature of the array to function correctly.
> - The function `p` directly manipulates raw pointers and array indices, typical of a more traditional C-style approach within C++ code. This method is wrapped by `bin_search` to provide a more modern C++ interface using `std::vector`.