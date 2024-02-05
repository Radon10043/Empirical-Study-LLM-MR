> ### `edit_dist` Function Specification
>
> #### Description
> The `edit_dist` function calculates the minimum number of operations required to convert one string (`str1`) into another (`str2`). The allowable operations are insertion, deletion, or substitution of a single character. This computation is a classic example of using dynamic programming to solve the Levenshtein distance problem.
>
> #### Function Signature
> ```c++
> int edit_dist(std::string& str1, std::string& str2);
> ```
>
> #### Parameters
> - `str1` (`std::string&`): The original string to be transformed.
> - `str2` (`std::string&`): The target string that `str1` is to be transformed into.
>
> #### Returns
> - `int`: The minimum number of edit operations (insertions, deletions, substitutions) required to transform `str1` into `str2`.
>
> #### Helper Function
> - `min(int x, int y, int z)`: A utility function to find the minimum of three integers. This is used to determine the minimum number of operations by comparing the results of insertion, deletion, and substitution.
>
> #### Methodology
> - The function `editDist` is a recursive implementation of the problem. It breaks down the problem into smaller subproblems and solves them using the following logic:
>   - If `m` (the length of `str1`) is 0, the result is `n` (the length of `str2`), since it would take `n` insertions to transform an empty string into `str2`.
>   - If `n` (the length of `str2`) is 0, the result is `m`, as it would take `m` deletions to transform `str1` into an empty string.
>   - If the last characters of `str1` and `str2` are the same, no operation is required for the last character, so the function recurs with the lengths of both strings reduced by 1.
>   - If the last characters are not the same, the function calculates the minimum of three operations: insertion, deletion, and substitution. It then adds 1 to this minimum value, representing the operation required to fix the last character.
>
> #### Notes
> - This recursive implementation is straightforward and illustrates the concept clearly but can be inefficient for large strings due to the high number of repeated calculations. For practical applications, a dynamic programming approach that stores intermediate results to avoid redundant calculations is preferable.
> - The `edit_dist` wrapper function simplifies the usage by only requiring the two strings as arguments, automatically passing their lengths to the recursive `editDist` function.