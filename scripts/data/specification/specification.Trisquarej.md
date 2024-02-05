> ### `triangle_square` Function Specification
>
> #### Description
> The `triangle_square` function evaluates the type of a triangle based on its side lengths and calculates the area of the triangle. It uses the side lengths (`a`, `b`, `c`) as input and returns a pair containing an integer representing the triangle type and a double representing the area of the triangle.
>
> #### Function Signature (Java)
> ```java
> public static Pair<Integer, Double> triangle_square(int a, int b, int c)
> ```
>
> #### Parameters
> - `a`: An integer representing the length of the first side of the triangle.
> - `b`: An integer representing the length of the second side of the triangle.
> - `c`: An integer representing the length of the third side of the triangle.
>
> #### Returns
> - The function returns a `Pair<Integer, Double>` where the first element (`Integer`) represents the type of the triangle, and the second element (`Double`) represents the area of the triangle. The triangle type is indicated as follows:
>   - `0`: Not a triangle.
>   - `1`: Scalene triangle (all sides of different lengths).
>   - `2`: Isosceles triangle (two sides of equal length).
>   - `3`: Equilateral triangle (all sides of the same length).
>
> #### Logic
> 1. **Triangle Validation**: First, it checks if the input side lengths form a valid triangle based on the triangle inequality theorem. If not, it returns "0 0.0" indicating it is not a triangle.
>
> 2. **Type and Area Calculation**:
>     - If the triangle is valid, it calculates the area of the triangle using Heron's formula for a scalene triangle, the formula for an isosceles triangle based on its height, or the formula for an equilateral triangle based on its side length.
>     - It identifies the triangle type based on the equality of its side lengths (`match` variable).
>
> 3. **Utility Methods**:
>     - `TriangleSquare`: A helper method that performs the main logic for determining the triangle type and calculating its area. Returns a string combining the triangle type and area separated by a space.
>     - `sqrt`: A method to compute the square root of a given number using Newton's method.
>
> #### Notes
> - The function assumes all input side lengths are positive integers.
> - It uses a custom `sqrt` method for square root calculation, ensuring the logic is self-contained without relying on `Math.sqrt` from the Java standard library.
> - The classification into triangle types and the area calculation are done in a single pass, optimizing performance.
> - The `Pair` class used in the return type is assumed to be from a utility library like Apache Commons Lang or a similar implementation.