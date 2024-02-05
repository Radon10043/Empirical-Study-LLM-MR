> ### `first_missing_positive` Function Specification
>
> #### Description
> The `first_missing_positive` function finds the smallest positive integer that does not appear in an array of integers. This algorithm efficiently handles an unsorted array with a time complexity of O(n) and does not require additional space, aside from variable storage, making it an in-place solution.
>
> #### Function Signature (C++)
>
> ```c++
> int first_missing_positive(std::vector<int> nums);
> ```
>
> #### Parameters
> - `nums` (`std::vector<int>`): An unsorted vector of integers which can include positive numbers, negative numbers, and zeros.
>
> #### Returns
> - `int`: The smallest positive integer (greater than 0) that is missing from the array. If all positive integers up to `n` (where `n` is the size of the array) are present, the function returns `n + 1`.
>
> #### Logic
> 1. **Rearrange Positive Numbers**: Iterate through each number in the array. For any positive number `x` within the range of 1 to `n` (inclusive), place it in its "correct" position, i.e., swap `nums[i]` with `nums[nums[i] - 1]` as long as the target position does not already contain the correct number. This step ensures that if an integer `k` is present in the array, it will be placed at the index `k-1`.
>
> 2. **Find the First Missing Positive**: After rearrangement, iterate through the array again, checking if the integer at each index `i` equals `i + 1`. The first index `i` where this condition does not hold true indicates that `i + 1` is the smallest missing positive integer.
>
> 3. **Handling Edge Cases**: If all positions `1` to `n` are correctly occupied by their respective integers, the smallest missing positive integer is `n + 1`.
>
> #### Notes
> - The function modifies the original array due to the swapping operation, which may not be desirable in all cases. If preserving the original array is necessary, consider making a copy before calling the function.
> - This approach is designed to achieve O(n) time complexity with constant space complexity, except for input storage.
> - The function assumes that the input vector does not contain integers that could cause an out-of-bounds access when used as indices. Proper error handling or validation might be required for robust use cases.