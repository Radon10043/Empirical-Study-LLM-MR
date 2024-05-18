package test;

import static org.junit.Assume.assumeTrue;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.io.IOException;
import java.security.SecureRandom;
import java.util.Random;
import java.util.stream.Stream;
import org.junit.Assume;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import Jama.EigenvalueDecomposition;
import Jama.Matrix;

public class JamaGPT4Test {
    /* Helper methods, implemented by Radon */
    /**
     * Helper method to calculate the adjoint matrix of a given matrix.
     *
     * @param m
     * @return
     */
    public Matrix adjoint(Matrix m) {
        return m.inverse().times(m.det());
    }

    /**
     * Helper method to calculate the cofactor matrix.
     * @param m
     * @return
     */
    public Matrix cofactorMatrix(Matrix m) {
        return adjoint(m.transpose());
    }

    /**
     * Metamorphic Relation 2: The determinant of the original matrix should be multiplied by -1 if
     * two different rows (or columns) of the matrix are swapped.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantRowSwap(Matrix m) { // Fixed
        SecureRandom rand = new SecureRandom();
        assumeTrue(m.getRowDimension() > 1);

        // Get source output
        double source_out = m.det();

        // Swap two different rows to get follow-up input
        Matrix follow_m = m.copy();
        int row1 = rand.nextInt(m.getRowDimension());
        int row2 = ((row1 + 1) % m.getRowDimension());
        follow_m = swapRows(follow_m, row1, row2);

        // Get follow-up output
        double follow_out = follow_m.det();

        // Verification
        assertEquals(-source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 3: The determinant of a matrix A multiplied by a non-zero scalar c is
     * equal to c^n * det(A), where n is the size (number of rows or columns as it's a square
     * matrix) of the matrix A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantScalarMultiplication(Matrix m) {
        // Non-zero scalar
        double scalar = 2.0;

        // Calculate exponent n (size of the matrix)
        int n = m.getRowDimension(); // or m.getColumnDimension() because matrix is square

        // Get source output and multiply by c^n
        double scaled_source_out = Math.pow(scalar, n) * m.det();

        // Construct follow-up input (multiply all elements in the matrix by scalar)
        Matrix follow_m = m.times(scalar);

        // Get follow-up output
        double follow_out = follow_m.det();

        // Verification
        assertEquals(scaled_source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 4: If a multiple of one row of the matrix is added to another row, the
     * determinant should not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantRowAddition(Matrix m) { // Fixed
        SecureRandom rand = new SecureRandom();
        assumeTrue(m.getRowDimension() > 1);

        // Get source output
        double source_out = m.det();

        // Construct follow-up input by adding a multiple of a row to another row
        Matrix follow_m = m.copy();
        double multiple = 2.0;
        int srcRow = rand.nextInt(m.getRowDimension());
        int destRow = (srcRow + 1) % m.getRowDimension();
        for (int i = 0; i < m.getColumnDimension(); i++) {
            double newValue = follow_m.get(destRow, i) + multiple * follow_m.get(srcRow, i);
            follow_m.set(destRow, i, newValue);
        }

        // Get follow-up output
        double follow_out = follow_m.det();

        // Verification
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 5: The determinant of a matrix A should be zero if two rows (or two
     * columns) of the matrix are the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantDuplicateRow(Matrix m) { // Fixed
        SecureRandom rand = new SecureRandom();
        assumeTrue(m.getRowDimension() > 1);

        // Make a copy of the matrix
        Matrix follow_m = m.copy();

        // Duplicate a row
        int row = rand.nextInt(m.getRowDimension());
        for (int i = 0; i < m.getColumnDimension(); i++) {
            follow_m.set((row + 1) % m.getRowDimension(), i, m.get(row, i));
        }

        // Get follow-up output
        double follow_out = follow_m.det();

        // Verification that determinant is 0
        assertEquals(0.0, follow_out, 1e-6);
    }

    /**
     * Helper method to swap two rows in a matrix.
     *
     * @param m The matrix object.
     * @param row1 The index of the first row.
     * @param row2 The index of the second row.
     * @return The new matrix object with the two rows swapped.
     */
    private Matrix swapRows(Matrix m, int row1, int row2) {
        for (int i = 0; i < m.getColumnDimension(); i++) {
            double temp = m.get(row1, i);
            m.set(row1, i, m.get(row2, i));
            m.set(row2, i, temp);
        }
        return m;
    }

    /**
     * Metamorphic Relation 6: The determinant of the matrix A should be the same if the matrix is
     * multiplied by an identity matrix, i.e., det(A) = det(A * I)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantMultiplicationByIdentity(Matrix originalMatrix) {
        // Get source output
        double sourceOut = originalMatrix.det();

        // Create an identity matrix of the same size as originalMatrix
        Matrix identityMatrix = Matrix.identity(originalMatrix.getRowDimension(),
                originalMatrix.getColumnDimension());

        // Construct follow-up input (A * I)
        Matrix followUpMatrix = originalMatrix.times(identityMatrix);

        // Get follow-up output
        double followOut = followUpMatrix.det();

        // Verification
        assertEquals(sourceOut, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 7: The determinant of the matrix should change by a factor equal to the
     * determinant of the other matrix when it is right-multiplied by another matrix. i.e., det(A *
     * B) = det(A) * det(B)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantMultiplicationByOther(Matrix originalMatrix) {
        // Create another random matrix of the same size
        Matrix anotherMatrix = createRandomSquareMatrix(originalMatrix.getRowDimension());

        // Get source output and the determinant of the other matrix
        double sourceOut = originalMatrix.det();
        double otherOut = anotherMatrix.det();

        // Construct follow-up input (A * B)
        Matrix followUpMatrix = originalMatrix.times(anotherMatrix);

        // Get follow-up output
        double followOut = followUpMatrix.det();

        // Verification
        assertEquals(sourceOut * otherOut, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 8: Permuting two columns in a matrix should change the determinant sign.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantColumnSwap(Matrix m) { // Fixed
        SecureRandom rand = new SecureRandom();
        assumeTrue(m.getColumnDimension() > 1);

        // Get source output
        double source_out = m.det();

        // Swap two different columns
        Matrix follow_m = m.copy();
        int col1 = rand.nextInt(m.getColumnDimension());
        int col2 = ((col1 + 1) % m.getColumnDimension());
        follow_m = swapColumns(follow_m, col1, col2);

        // Get follow-up output
        double follow_out = follow_m.det();

        // Verification
        assertEquals(-source_out, follow_out, 1e-6);
    }

    /**
     * Helper method to swap two columns in a matrix.
     *
     * @param m The matrix object.
     * @param col1 The index of the first column.
     * @param col2 The index of the second column.
     * @return The new matrix object with the two columns swapped.
     */
    private Matrix swapColumns(Matrix m, int col1, int col2) {
        for (int i = 0; i < m.getRowDimension(); i++) {
            double temp = m.get(i, col1);
            m.set(i, col1, m.get(i, col2));
            m.set(i, col2, temp);
        }
        return m;
    }

    /**
     * Helper method to create a random square matrix.
     *
     * @param size The size of the square matrix.
     * @return A new square matrix with randomly initialized elements.
     */
    private Matrix createRandomSquareMatrix(int size) {
        Random rand = new Random();
        double[][] data = new double[size][size];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                data[i][j] = rand.nextDouble();
            }
        }
        return new Matrix(data);
    }

    /**
     * Metamorphic Relation 9: The determinant of a matrix multiplied by its inverse should be 1,
     * provided the matrix is invertible, i.e., det(A) * det(A^-1) = 1
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantWithInverse(Matrix matrix) { // Fixed
        // Skip test if the matrix is not invertible
        assumeTrue(isInvertible(matrix));

        // Get source output
        double sourceOut = matrix.det();

        // Construct follow-up input (invert the matrix)
        Matrix inverse = matrix.inverse();

        // Get follow-up output (determinant of the inverse)
        double inverseOut = inverse.det();

        // Verification
        assertEquals(1.0, sourceOut * inverseOut, 1e-6);
    }

    /**
     * Metamorphic Relation 10: The determinant of a diagonal matrix is the product of its diagonal
     * elements.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantOfDiagonalMatrix(Matrix matrix) {
        // Convert source matrix to a diagonal matrix with same diagonal elements
        Matrix diagonalMatrix = toDiagonal(matrix);

        // Calculate the expected determinant (product of diagonal)
        double expectedDet = calculateDiagonalProduct(diagonalMatrix);

        // Get follow-up output
        double diagonalDet = diagonalMatrix.det();

        // Verification
        assertEquals(expectedDet, diagonalDet, 1e-6);
    }

    /**
     * Helper method to convert a given square matrix to a diagonal matrix with the same diagonal
     * elements.
     *
     * @param m The original matrix.
     * @return A new diagonal matrix containing the diagonal elements of m.
     */
    private Matrix toDiagonal(Matrix m) {
        int size = m.getRowDimension();
        Matrix diagonalMatrix = new Matrix(size, size);
        for (int i = 0; i < size; i++) {
            diagonalMatrix.set(i, i, m.get(i, i));
        }
        return diagonalMatrix;
    }

    /**
     * Helper method to calculate the product of diagonal elements of a diagonal matrix.
     *
     * @param m The diagonal matrix.
     * @return The product of diagonal elements.
     */
    private double calculateDiagonalProduct(Matrix m) {
        double product = 1;
        for (int i = 0; i < m.getRowDimension(); i++) {
            product *= m.get(i, i);
        }
        return product;
    }

    /**
     * Helper method to check if a square matrix is invertible by checking if its determinant is not
     * zero.
     *
     * @param m The matrix to check.
     * @return true if the matrix is invertible, false otherwise.
     */
    private boolean isInvertible(Matrix m) {
        return Math.abs(m.det()) > 1e-6;
    }

    /**
     * Metamorphic Relation 11: The determinant of a block diagonal matrix is the product of the
     * determinants of its diagonal blocks.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantOfBlockDiagonalMatrix(Matrix matrix) {
        // Create a block diagonal matrix using the provided matrix as one block and an identity
        // matrix as another block.
        Matrix blockMatrix = createBlockDiagonalMatrix(matrix,
                Matrix.identity(matrix.getRowDimension(), matrix.getColumnDimension()));

        // Calculate the expected determinant (product of determinants of blocks)
        double expectedDet = matrix.det() * 1; // Since the determinant of the identity matrix is 1

        // Get the determinant of the block diagonal matrix
        double blockMatrixDet = blockMatrix.det();

        // Verification
        assertEquals(expectedDet, blockMatrixDet, 1e-6);
    }

    /**
     * Helper method to create a block diagonal matrix from two square matrices.
     *
     * @param A The first square matrix.
     * @param B The second square matrix.
     * @return The block diagonal matrix.
     */
    private Matrix createBlockDiagonalMatrix(Matrix A, Matrix B) {
        int aSize = A.getRowDimension();
        int bSize = B.getRowDimension();
        Matrix blockMatrix = new Matrix(aSize + bSize, aSize + bSize);

        // Place A in the top left
        for (int i = 0; i < aSize; i++) {
            for (int j = 0; j < aSize; j++) {
                blockMatrix.set(i, j, A.get(i, j));
            }
        }

        // Place B in the bottom right
        for (int i = 0; i < bSize; i++) {
            for (int j = 0; j < bSize; j++) {
                blockMatrix.set(aSize + i, aSize + j, B.get(i, j));
            }
        }

        return blockMatrix;
    }

    /**
     * Metamorphic Relation 12: The determinant of a scaled matrix is the same as scaling the
     * determinant of the original matrix by the scale factor raised to the power of the matrix's
     * dimensions.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantOfScaledMatrix(Matrix matrix) {
        double scaleFactor = 2.0;
        int dimension = matrix.getRowDimension(); // Assuming square matrix

        // Calculate expected determinant after scaling
        double expectedDet = Math.pow(scaleFactor, dimension) * matrix.det();

        // Construct scaled matrix
        Matrix scaledMatrix = matrix.times(scaleFactor);

        // Determine the determinant of the scaled matrix
        double scaledMatrixDet = scaledMatrix.det();

        // Verification
        assertEquals(expectedDet, scaledMatrixDet, 1e-6);
    }

    /**
     * Metamorphic Relation 13: The determinant of a skew-symmetric matrix (n-by-n) where n is odd,
     * should be 0 because skew-symmetric matrices with odd dimensions are singular.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testDeterminantOfSkewSymmetricMatrix(Matrix matrix) {
        // Create a skew-symmetric matrix from the given matrix
        Matrix skewSymmetricMatrix = createSkewSymmetricMatrix(matrix);

        // If the dimension of matrix is odd, the determinant should be 0
        if (matrix.getRowDimension() % 2 != 0) {
            double skewSymmetricDet = skewSymmetricMatrix.det();
            assertEquals(0.0, skewSymmetricDet, 1e-6);
        }
        // No verification for even dimensions because non-zero determinants are possible
    }

    /**
     * Helper method to create a skew-symmetric matrix from a square matrix. A skew-symmetric matrix
     * A is a matrix for which A^T = -A.
     *
     * @param m The square matrix to convert to skew-symmetric.
     * @return The skew-symmetric matrix.
     */
    private Matrix createSkewSymmetricMatrix(Matrix m) {
        Matrix A = m.copy();
        Matrix AT = A.transpose();

        // Create a skew symmetric matrix: A = (A - AT) / 2
        // since (A - AT) is skew symmetric
        for (int i = 0; i < A.getRowDimension(); i++) {
            for (int j = 0; j < A.getColumnDimension(); j++) {
                A.set(i, j, (A.get(i, j) - AT.get(i, j)) / 2);
            }
        }

        return A;
    }

    /**
     * Metamorphic Relation 14: If a matrix is multiplied (pre-multiplied) by a permutation matrix,
     * the determinant changes sign if the permutation matrix denotes an odd number of row
     * exchanges, and remains the same for an even number of exchanges. For simplicity, we can
     * construct a permutation matrix for a single row exchange.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantWithPermutationMatrix(Matrix originalMatrix) {   // Fixed
        assumeTrue(originalMatrix.getRowDimension() > 1); // Skip for 1x1 matrices

        // Get source output
        double sourceOut = originalMatrix.det();

        // Construct a permutation matrix by exchanging two rows of an identity matrix
        Matrix permutationMatrix = Matrix.identity(originalMatrix.getRowDimension(),
                originalMatrix.getColumnDimension());
        permutationMatrix = swapRows(permutationMatrix, 0, 1); // Swapping first two rows

        // Expected change in determinant (since we know it's a single swap, the sign will change)
        double expectedDet = -sourceOut;

        // Construct follow-up input (P * A where P is the permutation matrix)
        Matrix followUpMatrix = permutationMatrix.times(originalMatrix);

        // Get follow-up output
        double followOut = followUpMatrix.det();

        // Verification
        assertEquals(expectedDet, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 15: Adding a multiple of one row to another row in the matrix should not
     * change the determinant. This property can also be applied column-wise.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantRowAdditionMultiple(Matrix originalMatrix) { // Fixed
        assumeTrue(originalMatrix.getRowDimension() > 1); // Skip for 1x1 matrices

        // Get source output
        double sourceOut = originalMatrix.det();

        // Construct follow-up input by adding a multiple of one row to another row
        Matrix followUpMatrix = originalMatrix.copy();
        double factor = 2.0; // Arbitrary non-zero factor
        int sourceRow = 0;
        int targetRow = 1;
        for (int i = 0; i < originalMatrix.getColumnDimension(); i++) {
            double newValue =
                    followUpMatrix.get(targetRow, i) + factor * followUpMatrix.get(sourceRow, i);
            followUpMatrix.set(targetRow, i, newValue);
        }

        // Get follow-up output
        double followOut = followUpMatrix.det();

        // Verification
        assertEquals(sourceOut, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 16: If a matrix A has a row (or column) full of zeros, then the
     * determinant of A is zero.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantWithZeroRow(Matrix originalMatrix) {
        // Construct follow-up input with a zero row
        Matrix followUpMatrix = originalMatrix.copy();
        int zeroRow = 0; // Select the first row for simplicity
        for (int i = 0; i < originalMatrix.getColumnDimension(); i++) {
            followUpMatrix.set(zeroRow, i, 0);
        }

        // Get follow-up output which should be zero
        double followOut = followUpMatrix.det();

        // Verification
        assertEquals(0.0, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 17: For two identical matrices A and B, the determinant of their
     * Kronecker product should be the determinant of A (or B) raised to the power of the size of A
     * (or B).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantKroneckerProduct(Matrix originalMatrix) {
        // Calculate the Kronecker product of the matrix with itself
        Matrix kroneckerProductMatrix = kroneckerProduct(originalMatrix, originalMatrix);

        // Size of the original matrix
        int size = originalMatrix.getRowDimension();

        // Calculate the expected determinant (det(A)^size)
        double expectedDet = Math.pow(originalMatrix.det(), size);

        // Determine the determinant of the Kronecker product
        double kroneckerProductDet = kroneckerProductMatrix.det();

        // Verification
        assertEquals(expectedDet, kroneckerProductDet, 1e-6);
    }

    /**
     * Helper method to calculate the Kronecker product of two square matrices.
     *
     * @param A The first square matrix.
     * @param B The second square matrix.
     * @return The Kronecker product matrix.
     */
    private Matrix kroneckerProduct(Matrix A, Matrix B) {
        int aRows = A.getRowDimension();
        int aCols = A.getColumnDimension();
        int bRows = B.getRowDimension();
        int bCols = B.getColumnDimension();
        Matrix result = new Matrix(aRows * bRows, aCols * bCols);

        for (int aRow = 0; aRow < aRows; aRow++) {
            for (int aCol = 0; aCol < aCols; aCol++) {
                for (int bRow = 0; bRow < bRows; bRow++) {
                    for (int bCol = 0; bCol < bCols; bCol++) {
                        result.set(aRow * bRows + bRow, aCol * bCols + bCol,
                                A.get(aRow, aCol) * B.get(bRow, bCol));
                    }
                }
            }
        }
        return result;
    }

    /**
     * Metamorphic Relation 18: The determinant of a triangular matrix (either upper or lower
     * triangular) is the product of its diagonal elements.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantOfTriangularMatrix(Matrix matrix) {
        // Convert the matrix into an upper triangular matrix
        Matrix triangularMatrix = toUpperTriangular(matrix);

        // Expected determinant: product of the diagonal elements
        double expectedDet = 1.0;
        for (int i = 0; i < triangularMatrix.getRowDimension(); i++) {
            expectedDet *= triangularMatrix.get(i, i);
        }

        // Determine the determinant of the triangular matrix
        double triangularDet = triangularMatrix.det();

        // Verification
        assertEquals(expectedDet, triangularDet, 1e-6);
    }

    /**
     * Helper method to convert a square matrix into an upper triangular matrix using simple
     * Gaussian elimination without pivoting which may not always result in a strictly upper
     * triangular matrix if the matrix contains rows of zeros or if pivoting is needed. For this
     * relation, we assume the matrix is already in a form that does not require pivoting.
     *
     * @param m The original square matrix.
     * @return An upper triangular matrix.
     */
    private Matrix toUpperTriangular(Matrix m) {
        Matrix upperTriangular = m.copy();
        int n = upperTriangular.getRowDimension();
        for (int k = 0; k < n; k++) {
            for (int i = k + 1; i < n; i++) {
                double factor = upperTriangular.get(i, k) / upperTriangular.get(k, k);
                for (int j = k; j < n; j++) {
                    double newValue =
                            upperTriangular.get(i, j) - factor * upperTriangular.get(k, j);
                    upperTriangular.set(i, j, newValue);
                }
            }
        }
        return upperTriangular;
    }

    /**
     * Metamorphic Relation 19: If a matrix A is singular, any matrix obtained by adding a row of
     * zeros to matrix A (forming an augmented matrix) will also have a determinant of 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantOfAugmentedSingularMatrix(Matrix originalMatrix) {
        // Check if originalMatrix is singular (determinant is zero)
        Assume.assumeTrue(originalMatrix.det() == 0);

        // Augment the original matrix by adding a row of zeros
        Matrix augmentedMatrix = augmentMatrixWithZeroRow(originalMatrix);

        // Calculate the determinant of the augmented matrix
        double augmentedMatrixDet = augmentedMatrix.det();

        // Verification: the determinant of the augmented matrix should be 0
        assertEquals(0.0, augmentedMatrixDet, 1e-6);
    }

    /**
     * Helper method to augment a matrix with an additional row of zeros.
     *
     * @param matrix The original matrix to augment.
     * @return The augmented matrix with an extra row of zeros.
     */
    private Matrix augmentMatrixWithZeroRow(Matrix matrix) {
        int rows = matrix.getRowDimension();
        int cols = matrix.getColumnDimension();
        // Create an augmented matrix with one additional row
        Matrix augmentedMatrix = new Matrix(rows + 1, cols);
        // Copy the original matrix into the augmented matrix
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                augmentedMatrix.set(i, j, matrix.get(i, j));
            }
        }
        // The additional row is by default initialized to zero
        return augmentedMatrix;
    }

    /**
     * Metamorphic Relation 20: If a matrix A is non-singular and has an inverse, then the
     * determinant of the inverse of A is the reciprocal of the determinant of A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantOfInverseMatrix(Matrix originalMatrix) { // Fixed
        // Check if originalMatrix is non-singular (determinant is not zero)
        Assume.assumeTrue(isInvertible(originalMatrix));

        // Inverse the original matrix
        Matrix inverseMatrix = originalMatrix.inverse();

        // Calculate the determinant of the inverse matrix
        double inverseMatrixDet = inverseMatrix.det();
        double originalMatrixDet = originalMatrix.det();

        // Verification: det(A^-1) should be 1/det(A)
        assertEquals(1.0 / originalMatrixDet, inverseMatrixDet, 1e-6);
    }

    /**
     * Metamorphic Relation 21: The determinant of a matrix resulting from multiplying all elements
     * of a square matrix by a constant factor is equal to the constant factor raised to the power
     * of the matrix's size/dimension, multiplied by the original matrix's determinant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantAfterScalingMatrix(Matrix originalMatrix) {
        double scaleFactor = 3.0; // Arbitrary non-zero scale factor
        int dimension = originalMatrix.getRowDimension();

        // Scale the matrix by multiplying all its elements by scaleFactor
        Matrix scaledMatrix = originalMatrix.times(scaleFactor);

        // Calculate the determinant of the scaled matrix
        double scaledMatrixDet = scaledMatrix.det();

        // Calculate the expected determinant
        double expectedDet = Math.pow(scaleFactor, dimension) * originalMatrix.det();

        // Verification
        assertEquals(expectedDet, scaledMatrixDet, 1e-6);
    }

    /**
     * Metamorphic Relation 22: The determinant of a matrix product A * B is the product of the
     * determinants of matrices A and B.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantOfMatrixProduct(Matrix matrixA) {
        // Create a new square matrix B of the same size as A
        Matrix matrixB = createRandomSquareMatrix(matrixA.getRowDimension());

        // Calculate the product of matrices A and B
        Matrix productMatrix = matrixA.times(matrixB);

        // Calculate the determinant of the product matrix
        double productMatrixDet = productMatrix.det();

        // Calculate the expected determinant which is the product of the individual determinants
        double expectedDet = matrixA.det() * matrixB.det();

        // Verification
        assertEquals(expectedDet, productMatrixDet, 1e-6);
    }

    /**
     * Metamorphic Relation 23: The determinant of a matrix should be zero if there is a dependency
     * between its rows, i.e., one row is a linear combination of others.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantWithLinearDependentRows(Matrix matrix) {
        // Create a linear combination row that is the sum of all other rows
        Matrix modifiedMatrix = matrix.copy();
        for (int col = 0; col < modifiedMatrix.getColumnDimension(); col++) {
            double sum = 0;
            for (int row = 0; row < modifiedMatrix.getRowDimension() - 1; row++) {
                sum += modifiedMatrix.get(row, col);
            }
            modifiedMatrix.set(modifiedMatrix.getRowDimension() - 1, col, sum);
        }

        // Calculate the determinant of the modified matrix
        double modifiedMatrixDet = modifiedMatrix.det();

        // Verification
        assertEquals(0.0, modifiedMatrixDet, 1e-6);
    }

    /**
     * Metamorphic Relation 24: The determinant of an orthogonal matrix is either 1 or -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantOfOrthogonalMatrix(Matrix matrix) {
        // Assume the given matrix is orthogonal, which means A * A^T = I
        Assume.assumeTrue(isOrthogonal(matrix));

        // Calculate the determinant of the orthogonal matrix
        double orthogonalMatrixDet = matrix.det();

        // Verification: The determinant should be 1 or -1
        assertTrue(orthogonalMatrixDet == 1.0 || orthogonalMatrixDet == -1.0);
    }

    /**
     * Helper method to check if a matrix is orthogonal. An orthogonal matrix must satisfy A * A^T
     * == I. For simplicity, this method assumes the matrix is square and checks this property
     * approximately using the norm of each row and column, given that the exact arithmetic may
     * introduce errors due to floating point representation.
     *
     * @param matrix The matrix to check.
     * @return true if the matrix is orthogonal, false otherwise.
     */
    private boolean isOrthogonal(Matrix matrix) {
        Matrix product = matrix.times(matrix.transpose());
        Matrix identity = Matrix.identity(matrix.getRowDimension(), matrix.getColumnDimension());
        for (int i = 0; i < identity.getRowDimension(); i++) {
            for (int j = 0; j < identity.getColumnDimension(); j++) {
                if (Math.abs(product.get(i, j) - identity.get(i, j)) > 1e-6) {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * Metamorphic Relation 25: For any non-singular square matrix A, multiplying A by its adjoint
     * should result in a matrix where all elements are 0 except for the diagonal, where each
     * element is equal to the determinant of A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantAfterMultiplicationByAdjoint(Matrix originalMatrix) {
        // Skip test if the matrix is singular, as an adjoint for a singular matrix is not
        // well-defined
        double originalDet = originalMatrix.det();
        Assume.assumeTrue(originalDet != 0);

        // Calculate the adjoint of the matrix
        Matrix adjointMatrix = calculateAdjoint(originalMatrix);

        // Multiplying A by its adjoint should yield a diagonal matrix with diagonal elements equal
        // to det(A)
        Matrix resultMatrix = originalMatrix.times(adjointMatrix);

        // Verify that all diagonal elements are close to det(A) and all off-diagonal elements are
        // close to 0
        for (int i = 0; i < resultMatrix.getRowDimension(); i++) {
            for (int j = 0; j < resultMatrix.getColumnDimension(); j++) {
                if (i == j) {
                    assertEquals(originalDet, resultMatrix.get(i, j), 1e-6);
                } else {
                    assertEquals(0.0, resultMatrix.get(i, j), 1e-6);
                }
            }
        }
    }

    /**
     * Helper method to calculate the adjoint (adjugate) of a non-singular square matrix.
     *
     * @param matrix The non-singular square matrix.
     * @return The adjoint (adjugate) matrix.
     */
    private Matrix calculateAdjoint(Matrix matrix) {
        // Implementation placeholder - actual implementation would be required to calculate the
        // adjoint matrix
        return new Matrix(matrix.getRowDimension(), matrix.getColumnDimension());
    }

    /**
     * Metamorphic Relation 26: If all elements of matrix A are increased by a constant value k, the
     * determinant of the matrix increases by k times the sum of the cofactors of any row or column,
     * which is a non-trivial relation.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantAfterElementWiseAddition(Matrix originalMatrix) {
        double k = 5.0; // Arbitrary constant to add to each element of matrix A
        Matrix newMatrix = originalMatrix.copy();
        int size = originalMatrix.getRowDimension();

        // Add k to each element of the matrix
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                double newVal = originalMatrix.get(i, j) + k;
                newMatrix.set(i, j, newVal);
            }
        }

        // Calculate new determinant
        double newDet = newMatrix.det();

        // Assuming the method to calculate cofactors is implemented as `calculateCofactorSum(row,
        // originalMatrix)`
        double cofactorSum = calculateCofactorSum(0, originalMatrix); // An arbitrary row can be
                                                                      // chosen for the calculation

        // The expected relation, where the original determinant is increased by k times the sum of
        // cofactors of a row/column
        double expectedDet = originalMatrix.det() + k * cofactorSum;

        // Verification
        assertEquals(expectedDet, newDet, 1e-6);
    }

    /**
     * Helper method to calculate the sum of cofactors of a specific row in a square matrix.
     *
     * @param row The row for which to calculate the sum of cofactors.
     * @param matrix The square matrix.
     * @return The sum of cofactors of the given row.
     */
    private double calculateCofactorSum(int row, Matrix matrix) {
        Matrix cofactorMat = cofactorMatrix(matrix);
        double sum = 0;
        for (int i = 0; i < matrix.getColumnDimension(); i++) {
            sum += cofactorMat.get(row, i);
        }
        return sum;
    }

    /**
     * Metamorphic Relation 27: For any matrix A, appending an identity matrix of the same size to
     * form a block matrix [A|I] (where I is an identity matrix) does not change the determinant.
     * The determinant of [A|I] is the same as det(A).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantOfBlockMatrixWithIdentity(Matrix originalMatrix) {
        int dimension = originalMatrix.getRowDimension();
        // Create a block matrix [A|I]
        Matrix blockMatrix =
                createBlockMatrix(originalMatrix, Matrix.identity(dimension, dimension));

        // Calculate the determinant of the block matrix
        double blockMatrixDet = blockMatrix.det();

        // Calculate the original determinant
        double originalDet = originalMatrix.det();

        // Verification
        assertEquals(originalDet, blockMatrixDet, 1e-6);
    }

    /**
     * Helper method to create a block matrix [A|I] from an original matrix A and an identity matrix
     * I.
     *
     * @param A The original matrix.
     * @param I An identity matrix of the same size as A.
     * @return The block matrix [A|I].
     */
    private Matrix createBlockMatrix(Matrix A, Matrix I) {
        int size = A.getRowDimension();
        Matrix blockMatrix = new Matrix(size, size * 2);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                blockMatrix.set(i, j, A.get(i, j));
                blockMatrix.set(i, j + size, I.get(i, j));
            }
        }
        return blockMatrix;
    }

    /**
     * Metamorphic Relation 28: If two rows (or columns) are equal in a matrix A, then its
     * determinant is zero. Creating such situation by setting two rows (or columns) to be equal can
     * be used as a relationship.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testDeterminantWithEqualRows(Matrix originalMatrix) {
        // Make a copy of matrix and set two rows to be equal
        Matrix modifiedMatrix = originalMatrix.copy();
        for (int i = 0; i < originalMatrix.getColumnDimension(); i++) {
            modifiedMatrix.set(1, i, originalMatrix.get(0, i)); // Set the second row to be equal to
                                                                // the first row
        }

        // Calculate the determinant of the modified matrix
        double modifiedMatrixDet = modifiedMatrix.det();

        // Verification: determinant should be zero
        assertEquals(0.0, modifiedMatrixDet, 1e-6);
    }

    /**
     * Metamorphic Relation 29: Removing a row and a column from a non-singular matrix to form a
     * smaller matrix (a submatrix) changes the determinant in a way that is proportional to the
     * element of the removed cell, its cofactor, and the determinant of the original matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantOfSubmatrix(Matrix originalMatrix) { // Fixed
        // Skip test if the matrix is singular since we want to test on non-singular matrices
        double originalDet = originalMatrix.det();
        Assume.assumeTrue(Math.abs(originalDet) >= 0);

        // Remove the first row and the first column to form a submatrix
        Matrix submatrix = originalMatrix.getMatrix(1, originalMatrix.getRowDimension() - 1, 1,
                originalMatrix.getColumnDimension() - 1);

        // Get the determinant of the submatrix
        double submatrixDet = submatrix.det();

        // Expected determinant is related to the cofactor of the removed element (A11 in this case)
        double expectedDet =
                originalMatrix.get(0, 0) * getCofactor(originalMatrix, 0, 0) / originalDet;

        // The determinant of the submatrix should approximate the expected determinant above
        assertEquals(expectedDet, submatrixDet, 1e-6);
    }

    /**
     * Helper method to calculate the cofactor of an element in a matrix.
     *
     * @param matrix The matrix.
     * @param row Row index of the element.
     * @param col Column index of the element.
     * @return The cofactor of the element.
     */
    private double getCofactor(Matrix matrix, int row, int col) {
        Matrix cofactorMat = cofactorMatrix(matrix);
        return cofactorMat.get(row, col); // not an actual implementation
    }

    /**
     * Metamorphic Relation 30: The determinant of a matrix A is unaffected if a multiple of one of
     * its rows (or columns) is added to another of its rows (or columns).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantWithRowAddition(Matrix originalMatrix) { // Fixed
        assumeTrue(originalMatrix.getRowDimension() > 1); // Skip for 1x1 matrices

        // Get source output
        double sourceOut = originalMatrix.det();

        // Get a random scale factor
        Random random = new Random();
        double scaleFactor = random.nextDouble() + 1; // Ensure it's not zero

        // Construct follow-up input by adding a scaled row 0 to row 1
        Matrix modifiedMatrix = originalMatrix.copy();
        for (int i = 0; i < modifiedMatrix.getColumnDimension(); i++) {
            double newVal = modifiedMatrix.get(0, i) * scaleFactor + modifiedMatrix.get(1, i);
            modifiedMatrix.set(1, i, newVal);
        }

        // Get follow-up output
        double followOut = modifiedMatrix.det();

        // Verification: determinants should be the same
        assertEquals(sourceOut, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 31: For a matrix A, replacing one row by the sum of itself and a
     * multiple of another row does not change the determinant of A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantWithRowReplacement(Matrix originalMatrix) {  // Fixed
        assumeTrue(originalMatrix.getRowDimension() > 1); // Skip for 1x1 matrices

        // Get source output
        double sourceOut = originalMatrix.det();

        // Construct follow-up input by replacing a row with the sum of itself and a scaled version
        // of another row
        Matrix modifiedMatrix = originalMatrix.copy();
        int rowToReplace = 1;
        int otherRow = 0;
        double scalingFactor = 2.0; // Arbitrary factor
        for (int col = 0; col < originalMatrix.getColumnDimension(); col++) {
            modifiedMatrix.set(rowToReplace, col, modifiedMatrix.get(rowToReplace, col)
                    + scalingFactor * modifiedMatrix.get(otherRow, col));
        }

        // Get follow-up output
        double followOut = modifiedMatrix.det();

        // Verification
        assertEquals(sourceOut, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 32: The determinant of a matrix should be the negative of the
     * determinant of the matrix obtained by multiplying all elements of a single row or column by
     * -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantWithRowNegation(Matrix originalMatrix) {
        // Get source output
        double originalDet = originalMatrix.det();

        // Negate all elements in the first row
        Matrix negatedMatrix = originalMatrix.copy();
        for (int i = 0; i < negatedMatrix.getColumnDimension(); i++) {
            negatedMatrix.set(0, i, -negatedMatrix.get(0, i));
        }

        // Get determinant after negation
        double negatedDet = negatedMatrix.det();

        // Verification: determinant should be the opposite of the original
        assertEquals(-originalDet, negatedDet, 1e-6);
    }

    /**
     * Metamorphic Relation 33: The determinant of a matrix with a row or column of all zeros is
     * zero. We can manually set a row or column to all zeros to test this property.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testDeterminantWithZeroColumn(Matrix originalMatrix) {
        // Set all elements in the first column to zero
        Matrix zeroColumnMatrix = originalMatrix.copy();
        for (int i = 0; i < zeroColumnMatrix.getRowDimension(); i++) {
            zeroColumnMatrix.set(i, 0, 0.0);
        }

        // Get determinant of matrix with zero column
        double zeroColumnDet = zeroColumnMatrix.det();

        // Verification: determinant should be zero
        assertEquals(0.0, zeroColumnDet, 1e-6);
    }

    /**
     * Metamorphic Relation 34: For a square matrix A, the determinant of A multiplied by the
     * determinant of its inverse (if A is invertible) should be 1 (since A * A^-1 = I and det(I) =
     * 1).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantMultipliedByInverse(Matrix originalMatrix) { // Fixed
        // Check if matrix is invertible (non-singular), otherwise skip the test
        double originalDet = originalMatrix.det();
        Assume.assumeTrue(Math.abs(originalDet) > 1e-6);

        // Invert the matrix
        Matrix inverseMatrix = originalMatrix.inverse();

        // Get the determinant of the inverse matrix
        double inverseDet = inverseMatrix.det();

        // Calculate the product of determinants
        double determinantsProduct = originalDet * inverseDet;

        // Verification: the product should be 1 (or very close to 1 within a reasonable epsilon)
        assertEquals(1.0, determinantsProduct, 1e-6);
    }

    /**
     * Metamorphic Relation 35: The determinant of a matrix after adding the scalar multiple of a
     * row to another row remains unchanged. We can test this by performing such an operation and
     * comparing the determinants.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantAfterAddingScalarMultipleOfRow(Matrix originalMatrix) {  // Fixed
        assumeTrue(originalMatrix.getRowDimension() > 1); // Skip for 1x1 matrices

        double scalar = 2.0; // Arbitrary non-zero scalar to use in row addition
        int sourceRow = 0; // Row to be scaled and added
        int targetRow = 1; // Target row to which the scaled row will be added

        // Perform row operation on a copy of the matrix
        Matrix modifiedMatrix = originalMatrix.copy();
        for (int col = 0; col < modifiedMatrix.getColumnDimension(); col++) {
            double scaledValue = scalar * modifiedMatrix.get(sourceRow, col);
            modifiedMatrix.set(targetRow, col, modifiedMatrix.get(targetRow, col) + scaledValue);
        }

        // The determinant should remain unchanged after the row operation
        double originalDet = originalMatrix.det();
        double modifiedDet = modifiedMatrix.det();

        // Verification
        assertEquals(originalDet, modifiedDet, 1e-6);
    }

    /**
     * Metamorphic Relation 36: The determinant of a 2x2 matrix {{a, b}, {c, d}} is ad - bc. We can
     * construct this matrix, calculate the determinant, and compare to the expected value.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantOfTwoByTwoMatrix(Matrix matrix) {
        // Make sure it's a 2x2 matrix for this relation
        Assume.assumeTrue(matrix.getRowDimension() == 2 && matrix.getColumnDimension() == 2);

        // Calculate the determinant manually
        double a = matrix.get(0, 0);
        double b = matrix.get(0, 1);
        double c = matrix.get(1, 0);
        double d = matrix.get(1, 1);
        double expectedDet = (a * d) - (b * c);

        // Calculate the determinant using the det() method
        double actualDet = matrix.det();

        // Verification
        assertEquals(expectedDet, actualDet, 1e-6);
    }

    /**
     * Metamorphic Relation 37: For a square matrix composed of submatrices, where A and D are
     * square matrices and B and C are zero matrices of compatible dimensions, the determinant of
     * the matrix should be the product of the determinants of A and D. This can be expressed as
     * det([[A, B], [C, D]]) = det(A) * det(D), where det(B) and det(C) are zero.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void testDeterminantOfBlockMatrixWithSubmatrices(Matrix a, Matrix d) {
        // Assume A and D are square and of the same size for this test
        Assume.assumeTrue(a.getRowDimension() == a.getColumnDimension()
                && a.getRowDimension() == d.getRowDimension());

        int size = a.getRowDimension();
        Matrix b = new Matrix(size, size); // Zero matrix
        Matrix c = new Matrix(size, size); // Zero matrix

        // Create the block matrix
        Matrix blockMatrix = createBlockMatrixFromSubmatrices(a, b, c, d);

        // Calculate determinant of block matrix
        double blockDet = blockMatrix.det();

        // Expected determinant is the product of determinants of A and D
        double expectedDet = a.det() * d.det();

        // Verification
        assertEquals(expectedDet, blockDet, 1e-6);
    }

    /**
     * Helper method to create a block matrix from submatrices.
     *
     * @param A square matrix A.
     * @param B zero matrix B with compatible dimensions.
     * @param C zero matrix C with compatible dimensions.
     * @param D square matrix D with dimensions equal to A.
     * @return the block matrix composed from the submatrices.
     */
    private Matrix createBlockMatrixFromSubmatrices(Matrix A, Matrix B, Matrix C, Matrix D) {
        int size = A.getRowDimension();
        Matrix blockMatrix = new Matrix(size * 2, size * 2);

        // Fill A into the top-left block
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                blockMatrix.set(i, j, A.get(i, j));
            }
        }

        // No need to fill B and C, as they are zero matrices

        // Fill D into the bottom-right block
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                blockMatrix.set(i + size, j + size, D.get(i, j));
            }
        }

        return blockMatrix;
    }

    /**
     * Metamorphic Relation 38: The determinant of a matrix remains the same after permuting its
     * rows and then permuting its columns with the same permutation. Essentially, det(A) = det(P *
     * A * P^-1), where P is the permutation matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantWithPermutation(Matrix originalMatrix) {
        // Determine the original determinant
        double originalDet = originalMatrix.det();

        // Create a permutation matrix P and its inverse P^-1
        Matrix permutationMatrix = createPermutationMatrix(originalMatrix.getRowDimension());
        Matrix permutationInverse = permutationMatrix.inverse();

        // Permute the rows with P and the columns with P^-1, equivalent to P * A * P^-1
        Matrix permutedMatrix = permutationMatrix.times(originalMatrix).times(permutationInverse);

        // Verify that the determinant remains unchanged
        double permutedDet = permutedMatrix.det();
        assertEquals(originalDet, permutedDet, 1e-6);
    }

    /**
     * Helper method to create a random permutation matrix of size n.
     *
     * @param n The size of the square permutation matrix.
     * @return The permutation matrix.
     */
    private Matrix createPermutationMatrix(int n) {
        Random rand = new Random();
        Matrix permutationMatrix = Matrix.identity(n, n);
        // Shuffle rows to create the permutation matrix
        for (int i = 0; i < n; i++) {
            int j = rand.nextInt(n);
            // Swap rows i and j
            permutationMatrix = swapRows(permutationMatrix, i, j);
        }
        return permutationMatrix;
    }

    /**
     * Metamorphic Relation 39: If matrix A has a zero determinant, then any matrix formed by
     * multiplying A by any other matrix B (of compatible dimensions) should also have a zero
     * determinant. This is because A has linearly dependent rows and this property won't change by
     * post-multiplication with any matrix B.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void testDeterminantAfterMultiplicationWithZeroDetMatrix(Matrix originalMatrix,
            Matrix otherMatrix) {   // Fixed
        // Ensure the first matrix has a zero determinant
        Assume.assumeTrue(Math.abs(originalMatrix.det()) <= 1e-6);

        // Multiply by another matrix of compatible dimensions
        Assume.assumeTrue(originalMatrix.getColumnDimension() == otherMatrix.getRowDimension());
        Matrix productMatrix = originalMatrix.times(otherMatrix);

        // Verify that the resultant matrix also has a zero determinant
        double productMatrixDet = productMatrix.det();
        assertEquals(0.0, productMatrixDet, 1e-6);
    }

    /**
     * Metamorphic Relation 40: For a non-singular matrix A, applying an elementary row operation
     * such as row scaling (multiplying a row by a non-zero constant) should change the determinant
     * by the factor of the scaling constant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantAfterRowScaling(Matrix originalMatrix) { // Fixed
        // Ensure matrix is non-singular
        double originalDet = originalMatrix.det();
        Assume.assumeTrue(Math.abs(originalDet) > 1e-6);

        double scalingConstant = 3; // Non-zero constant
        int rowToScale = 0; // Row to be scaled

        // Scale the row by the constant
        Matrix scaledMatrix = originalMatrix.copy();
        for (int col = 0; col < scaledMatrix.getColumnDimension(); col++) {
            scaledMatrix.set(rowToScale, col, scalingConstant * scaledMatrix.get(rowToScale, col));
        }

        // Verify that the determinant has been scaled by the scaling constant
        double scaledMatrixDet = scaledMatrix.det();
        assertEquals(scalingConstant * originalDet, scaledMatrixDet, 1e-6);
    }

    /**
     * Metamorphic Relation 41: The determinant of a matrix is the product of its eigenvalues. We
     * test this by comparing the calculated determinant with the product of eigenvalues obtained
     * from the eigenvalue decomposition.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeterminantAsProductOfEigenvalues(Matrix originalMatrix) {
        // Calculate the determinant of the original matrix
        double determinant = originalMatrix.det();

        // Calculate the eigenvalues of the original matrix
        EigenvalueDecomposition eigenDecomp = new EigenvalueDecomposition(originalMatrix);
        double[] eigenvalues = eigenDecomp.getRealEigenvalues();

        // Calculate the product of the eigenvalues
        double eigenvalueProduct = 1.0;
        for (double eigenvalue : eigenvalues) {
            eigenvalueProduct *= eigenvalue;
        }

        // Verification
        assertEquals(determinant, eigenvalueProduct, 1e-6);
    }

    static Stream<Arguments> testcaseProvider1() throws IOException {
        return testcaseGenerator.generate(1000);
    }

    static Stream<Arguments> testcaseProvider2() throws IOException {
        return testcaseGenerator.generate_mm(1000);
    }
}
