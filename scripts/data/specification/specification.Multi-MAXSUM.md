> ### `multi_maxsum` Function Specification
>
> #### Description
> The `multi_maxsum` function calculates the maximum sum of `m` contiguous, non-overlapping subarrays within a given array of integers. This problem extends the classic maximum subarray sum problem by considering multiple segments for optimization.
>
> #### Function Signatures
> ```c++
> int multi_maxsum(vector<int> nums, int m);
> ```
>
> #### Parameters
> - `nums`: A `vector<int>` representing the sequence of integers.
> - `m`: An integer representing the number of contiguous, non-overlapping subarrays to be considered for calculating the maximum sum.
>
> #### Returns
> - `int`: The maximum sum of the chosen `m` contiguous, non-overlapping subarrays.
>
> #### Helper Functions
> - `int max(int a, int c)`: Returns the maximum of two integers.
> - `int solve(int dp[], int num[], int n, int m)`: A utility function that employs dynamic programming to solve the multi-maxsum problem.
>
> #### Logic
> 1. **Initialization**: The function initializes a dynamic programming (DP) array `dp` to store intermediate results. This DP array helps in avoiding recomputation of subproblems.
>
> 2. **DP Solution**: The `solve` function iterates through the array, computing the maximum sum possible up to each index for `m` subarrays. For each position, it calculates the maximum sum that can be obtained by including the current element in one of the `m` subarrays. This involves:
>    - Calculating the sum of elements up to the current index for the first subarray.
>    - Updating the DP array with the maximum sum achievable by either including the current element in an existing subarray or starting a new subarray, ensuring that the total number of subarrays does not exceed `m`.
>
> 3. **Result**: The final result, which is the maximum sum of `m` contiguous, non-overlapping subarrays, is stored in `dp[n-1]` and returned by the `multi_maxsum` function.
>
> #### Notes
> - This problem and its solution are a variant of the classic "Maximum Subarray Sum" problem, with the added complexity of dividing the array into `m` non-overlapping subarrays.
> - The dynamic programming approach ensures that the solution is efficient and scalable for large arrays.
> - It's crucial to understand that the choice of `m` subarrays is done in a way to maximize the overall sum, which may not necessarily involve dividing the array into equal parts or selecting the maximum individual elements.
> - The implementation assumes the input array `nums` is non-empty and that `m` is a valid positive integer not exceeding the size of `nums`.