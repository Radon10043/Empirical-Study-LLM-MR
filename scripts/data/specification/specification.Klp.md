> ### `KLP` Function Specification
>
> #### Description
> The `KLP` function is a C++ implementation designed to solve a specific optimization problem related to selecting keys to open locks. Given a matrix where the rows represent keys and the columns represent locks, and the value at `matrix[i][j]` is `1` if the `i`-th key can open the `j`-th lock (otherwise `0`), the function aims to identify a minimal set of keys that can open all locks.
>
> #### Function Signature
> ```c++
> vector<int> KLP(vector<vector<int>> matrix);
> ```
>
> #### Parameters
> - `matrix` (`vector<vector<int>>`): A 2D vector representing the `m` rows by `n` columns matrix. Each element `matrix[i][j]` indicates whether the `i`-th key can open the `j`-th lock (`1` for yes, `0` for no).
>
> #### Returns
> - `vector<int>`: A vector of integers where each element represents the index of a selected key. If an element's value is present, it indicates that the corresponding key is selected as part of the minimal set required to open all locks.
>
> #### Algorithm
> 1. **Initialization**: Determine the dimensions of the matrix (`m` for rows/keys and `n` for columns/locks). Initialize a counter for the number of selected keys (`cnt`) and a result vector (`res`) to store the indices of the chosen keys.
> 2. **Key Selection Loop**: Iterate through the keys to select the one that can open the maximum number of locks that haven't been opened yet.
>    - For each key, count the number of locks (`1`s) it can open.
>    - Select the key (`best_row_index`) that can open the maximum number of locks.
>    - If the best key can open 0 locks, break the loop as it indicates that all locks are either opened or cannot be opened by any remaining keys.
> 3. **Lock Removal**: For the selected key, mark all locks it can open as opened by setting the corresponding column values to `-1` for all keys. This simulates the "removal" of the lock, as it no longer needs to be considered for future keys.
> 4. **Key Removal**: Mark the selected key as used by setting all its matrix values to `-1`. This prevents the key from being selected again.
> 5. **Result Update**: Add the index of the selected key to the `res` vector and increment the `cnt` counter.
> 6. **Iteration**: Repeat steps 2-5 until either all locks are opened or no single key can open any remaining locks.
> 7. **Return**: Return the `res` vector containing the indices of the keys that form the minimal set to open all locks.
>
> #### Notes
> - The function aims to find an optimal or near-optimal solution to select the minimal number of keys to open all locks by prioritizing keys that can open the most locks at each step.
> - The removal of keys and locks from consideration is simulated by setting their values to `-1` in the matrix, rather than actually deleting rows or columns, which simplifies the logic and maintains the original indices of keys for the result.
> - The returned indices in `res` are based on the zero-based indexing of the input matrix.