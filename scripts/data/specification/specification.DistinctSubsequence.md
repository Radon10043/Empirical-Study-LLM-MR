> ### `numDistinct` Function Specification
>
> #### Description
> The `numDistinct` function calculates the number of distinct subsequences of string `s` that match string `t`. A subsequence of a string is a new string generated from the original string with some characters(can be none) deleted without changing the relative order of the remaining characters.
>
> #### Function Signature
> ```c++
> int numDistinct(std::string s, std::string t);
> ```
>
> #### Parameters
> - `s` (`std::string`): The source string from which subsequences are generated.
> - `t` (`std::string`): The target string that the subsequences should match.
>
> #### Returns
> - `int`: The total number of distinct subsequences of `s` that match `t`.
>
> #### Methodology
> The function employs dynamic programming to solve the problem efficiently. It creates a 2D array `dp` where `dp[i][j]` represents the number of distinct subsequences of the first `j` characters of string `s` that match the first `i` characters of string `t`.
>
> - The first row of `dp` is initialized to 1 because an empty string is a subsequence of any string only once.
> - For each character in `t` (`i` from 1 to `n`), and each character in `s` (`j` from 1 to `m`), the function calculates `dp[i][j]` based on the following:
>     - If the current characters in `s` and `t` match (`t[i - 1] == s[j - 1]`), `dp[i][j]` is updated to `dp[i][j - 1] + dp[i - 1][j - 1]`. This means it includes all the subsequences counted by `dp[i][j - 1]` plus the subsequences ending with the current character.
>     - If the characters do not match, `dp[i][j]` is simply the value of `dp[i][j - 1]`, indicating that the current character of `s` does not contribute to new subsequences matching up to the `i-th` character of `t`.
>
> #### Notes
> - This function is case-sensitive, meaning 'A' and 'a' are considered different characters.
> - The approach effectively handles large strings by avoiding brute-force enumeration of all subsequences, which would be computationally expensive and impractical for long strings.
> - The function returns an `int`, which should be sufficient for most practical purposes, but if `s` and `t` are extremely large, the result might exceed the range of `int`. In such cases, modifying the function to return a larger integer type might be necessary.