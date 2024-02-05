> ### `determinant` Function Specification from Flanagan's Java Library
>
> #### Description
> The `determinant` function calculates the determinant of a square matrix. The Flanagan's Java library provides this functionality through both instance and static methods, allowing users to calculate the determinant of a matrix represented either as an instance of the `Matrix` class or as a 2-dimensional array of doubles.
>
> #### Method Signatures
> 1. **Instance Method**:
>    ```java
>    public double determinant()
>    ```
>    - **Usage**: `b = aa.determinant();`
>    - **Parameter**: None (the method is called on a `Matrix` instance `aa`).
>    - **Returns**: The determinant of the square matrix represented by the `Matrix` instance.
>
> 2. **Static Method with Matrix Parameter**:
>    ```java
>    public static double determinant(Matrix aa)
>    ```
>    - **Usage**: `b = Matrix.determinant(aa);`
>    - **Parameter**: `aa` - A `Matrix` instance representing the square matrix.
>    - **Returns**: The determinant of the square matrix represented by the `Matrix` instance `aa`.
>
> 3. **Static Method with double Array Parameter**:
>    ```java
>    public static double determinant(double[][] aa)
>    ```
>    - **Usage**: `b = Matrix.determinant(aa);`
>    - **Parameter**: `aa` - A 2-dimensional array of doubles representing the square matrix.
>    - **Returns**: The determinant of the square matrix represented by the 2-dimensional array `aa`.
>
> #### Requirements
> - The matrix (`aa`) must be square (i.e., the number of rows must be equal to the number of columns). The methods do not explicitly handle non-square matrices and may throw an exception or produce incorrect results if given a non-square matrix.
> - For the static methods, the input can be either a `Matrix` object or a 2-dimensional array of doubles, allowing flexibility in how the matrix is represented in the calling code.
>
> #### Notes
> - Calculating the determinant is a fundamental operation in linear algebra, useful in a variety of contexts including solving systems of linear equations, finding the inverse of a matrix, and more.
> - The determinant calculation can become computationally expensive for large matrices due to its recursive nature in traditional calculation methods.