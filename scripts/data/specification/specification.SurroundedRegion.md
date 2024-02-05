> ### `surrounded_region` Function Specification
>
> #### Description
> The `surrounded_region` function identifies all regions in a 2D matrix that are surrounded by the character 'X' and replaces all characters 'O' in these regions with 'X'. A region is defined as a group of connected 'O's (vertically and horizontally), and a surrounded region is one that is entirely enclosed by 'X's without any 'O's touching the boundary of the matrix.
>
> #### Function Signature
> ```c++
> std::vector<std::string> surrounded_region(std::vector<std::string> vec);
> ```
>
> #### Parameters
> - `vec`: A `std::vector<std::string>` representing the input 2D matrix where each string in the vector represents a row in the matrix.
>
> #### Returns
> - The function returns a `std::vector<std::string>`, which is the modified matrix after all surrounded regions of 'O's have been replaced with 'X's.
>
> #### Logic
> 1. **Initialization**: Converts the input vector of strings into a 2D character array `mat` for easier manipulation.
>
> 2. **Replace 'O' with '-'**: Iterates through the entire matrix and replaces all 'O' characters with '-' to mark them as unprocessed.
>
> 3. **Process Boundary 'O's**: Uses a flood fill algorithm starting from all boundary cells (top, bottom, left, right sides of the matrix) to replace '-' (previously 'O') with 'O' if they are connected to the boundary. This step ensures that 'O's which are not surrounded by 'X's are restored back to 'O's.
>
> 4. **Replace '-' with 'X'**: After processing the boundary, all remaining '-' characters (which are the 'O's that are surrounded by 'X's and not connected to the boundary) are replaced with 'X'.
>
> 5. **Conversion to Output Format**: Converts the modified 2D character array `mat` back into a vector of strings `result` and returns it.
>
> #### Notes
> - The function employs a flood fill utility (`floodFillUtil`) to perform the task of identifying and marking the regions for replacement.
> - This approach ensures that only 'O's that are fully enclosed by 'X's and not touching the matrix boundary are replaced.
> - The algorithm efficiently handles the conversion and processes the matrix in-place, making it space-efficient.
> - The size of the character array `mat` is defined with a fixed width of 900 columns, assuming that the input matrix will not exceed this width. This could be adjusted based on expected input sizes or dynamically allocated for more flexibility.