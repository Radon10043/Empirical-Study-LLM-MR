> ### `get_range` Function Specification
>
> #### Description
> The `get_range` function finds the range (start and end indices) of a given value `x` within a sorted array or vector. It uses binary search to find an occurrence of `x` and then expands the range to include all occurrences of `x` in the array.
>
> #### Function Signature (C++)
> ```c++
> vector<int> get_range(vector<int> vec, int x);
> ```
>
> #### Parameters
> - `vec`: A `vector<int>` that represents the sorted array in which the range for the value `x` is to be found.
> - `x`: An `int` representing the value for which the range is to be determined within `vec`.
>
> #### Returns
> - The function returns a `vector<int>` containing two elements:
>   - The first element is the start index of `x` within `vec`.
>   - The second element is the end index of `x` within `vec`.
> - If `x` is not found in `vec`, both elements of the returned vector will be `-1`.
>
> #### Logic
> 1. **Binary Search (`BinSearch`)**: First, the function performs a binary search to find an occurrence of `x` within the sorted array. If `x` is found, `BinSearch` returns the index of `x`. If `x` is not found, `BinSearch` returns `-1`.
>
> 2. **Range Expansion (`GetRange`)**: Starting from the index found by `BinSearch`, `GetRange` expands the search to the left and right to find the start and end indices of `x`, effectively determining the full range of `x` within `vec`.
>
> 3. **Handling of Not Found Case**: If `x` is not found by `BinSearch`, `get_range` directly returns a vector with both elements set to `-1`, indicating that `x` does not exist within `vec`.
>
> #### Notes
> - This function assumes that the input vector `vec` is sorted. If `vec` is not sorted, the binary search and subsequent range expansion will not correctly determine the range of `x`.
> - The function is designed for use with non-negative integer indices. If `x` does not exist within `vec`, the function returns `-1` for both the start and end indices to indicate this.
> - The implementation of `BinSearch` is recursive and may not be the most efficient for very large arrays due to stack size limitations.