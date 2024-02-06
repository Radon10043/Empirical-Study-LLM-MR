> ### Function Specification: `edit_dist`
>
> #### Purpose
> The `edit_dist` function computes the minimum number of operations required to transform one string (`str1`) into another string (`str2`). These operations include inserting a character, deleting a character, or substituting one character for another.
>
> #### Parameters
> - `str1` (std::string&): Reference to the source string that is to be transformed.
> - `str2` (std::string&): Reference to the target string that `str1` is to be transformed into.
>
> #### Return Value
> - `int`: Returns the minimum number of edit operations needed to transform `str1` into `str2`.
>
> #### Detailed Behavior
> - The function leverages a recursive approach to determine the minimum edit distance between two strings.
> - It compares the characters of `str1` and `str2` from the end towards the beginning.
> - If the current characters of `str1` and `str2` match, the function moves to the next pair of characters without counting an edit operation.
> - If the characters do not match, the function considers all possibilities—insertion, deletion, and substitution—calculating the minimum number of steps from these options.
> - Base cases are when one of the strings is empty (`m == 0` or `n == 0`), in which case the edit distance is the length of the other string, representing either insertions or deletions of all characters.
>
> #### Helper Function: `min`
> - Used internally to find the minimum among three values, corresponding to the counts of the different edit operations.
>
> #### Notes
> - The `edit_dist` function is a wrapper that initializes the recursive calculation by calling `editDist` with the lengths of the input strings.
> - This approach does not employ dynamic programming, hence might exhibit poor performance for longer strings due to repeated calculations for the same substrings.