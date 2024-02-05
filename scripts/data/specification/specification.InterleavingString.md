> ### `is_interleaved` Function Specification
>
> #### Description
> The `is_interleaved` function checks whether a given string `C` is an interleaving of two other strings `A` and `B`. Interleaving means that `C` is made up of all the characters of `A` and `B` where the order of characters is preserved but not necessarily continuous.
>
> #### Function Signatures
> C++ Version (C-style strings):
> ```c++
> bool isInterleaved(char* A, char* B, char* C);
> ```
>
> C++ Version (std::string):
> ```c++
> bool is_interleaved(string& A, string& B, string& C);
> ```
>
> #### Parameters
> - `A`, `B`: Pointers to the first character of C-style strings or references to `std::string` objects. These strings represent the sequences that could interleave to form `C`.
> - `C`: Pointer to the first character of a C-style string or a reference to a `std::string` object that might be an interleaving of `A` and `B`.
>
> #### Returns
> - `true`: If `C` is an interleaving of `A` and `B`.
> - `false`: Otherwise.
>
> #### Logic
> - The function recursively checks if the current character of `C` matches the current character of either `A` or `B` and proceeds accordingly by advancing in the strings where a match is found.
> - The recursion base case is when all three strings are empty (`*A`, `*B`, `*C` are all null characters), in which case `true` is returned since empty strings are considered interleaved by default.
> - If `C` is exhausted (i.e., `*C` is the null character) while `A` or `B` is not, `false` is returned because not all characters from `A` and `B` could be interleaved to form `C`.
> - The function explores both possibilities recursively: one where the current character of `C` matches the current character of `A` and another where it matches the current character of `B`.
>
> #### Notes
> - The function does not dynamically allocate memory or modify the input strings, ensuring that the operation is safe in terms of memory management.
> - Since this implementation uses recursion without memoization or dynamic programming, it may not be efficient for long strings due to potential repeated calculations.
> - The `is_interleaved` function with `std::string` parameters is a wrapper that allows the function to work with C++ string objects, providing a more convenient and safer interface compared to using C-style string pointers directly.