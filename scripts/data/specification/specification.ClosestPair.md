> ### `closest_distance` Function Specification
>
> #### Description
> The `closest_distance` function calculates the smallest Euclidean distance between any two points in a given set. This function is designed to efficiently find the minimum distance in a set of points by utilizing the divide and conquer algorithm, which is more efficient than the brute-force approach for large datasets.
>
> #### Signature
> ```c++
> float closest_distance(vector<pair<int, int>> vec);
> ```
>
> #### Parameters
> - `vec` (`vector<pair<int, int>>`): A vector of pairs where each pair represents the x and y coordinates of a point in a 2-dimensional space.
>
> #### Returns
> - `float`: The minimum Euclidean distance between any two points in the set.
>
> #### Implementation Details
> 1. **Data Preparation**: Converts the input vector of pairs into an array of `Point` structures.
> 2. **Sorting**: Sorts the points according to their x and y coordinates using `qsort` and custom comparison functions (`compareX` and `compareY`).
> 3. **Recursive Division**: Utilizes a recursive function `closestUtil` to divide the set of points into smaller subsets, finding the minimum distance within these subsets.
>    - For sets with 2 or 3 points, it uses a brute-force approach for comparison (`bruteForce` function).
>    - For larger sets, it divides the points around a middle point and recursively finds the minimum distance in the left and right subsets.
> 4. **Crossing Points Handling**: Considers points near the division line that could potentially form a closer pair than those found in the separate subsets.
> 5. **Combining Results**: Combines the results of the divided subsets and the crossing points to find the overall minimum distance.
>
> #### Auxiliary Functions
> - `dist`: Calculates the Euclidean distance between two points.
> - `bruteForce`: A brute-force approach to find the minimum distance for small subsets of points.
> - `min`: Returns the smaller of two floating-point numbers.
> - `stripClosest`: Finds the minimum distance in a strip of points close to the division line, considering only those within a certain distance from each other in the y-axis.
> - `closestUtil`: A utility function that implements the divide and conquer strategy to find the minimum distance.
> - `compareX`, `compareY`: Comparison functions used for sorting the points by their x and y coordinates, respectively.
>
> #### Notes
> - The input vector of points should not be empty; otherwise, the behavior is undefined.
> - This function is efficient for a large number of points, significantly reducing the time complexity compared to a naive brute-force approach.