package test;

import static org.junit.Assume.assumeThat;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

import java.io.IOException;
import java.util.Arrays;
import java.util.Collections;
import java.util.stream.Stream;

import org.junit.Assume;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import static org.hamcrest.Matchers.closeTo;
import static org.hamcrest.Matchers.is;
import static org.hamcrest.Matchers.not;

import flanagan.complex.Complex;
import flanagan.complex.ComplexMatrix;
import flanagan.math.Matrix;

public class Determinant1TestGPT3D5 {
    /**
     * Metamorphic Relation 3: The determinant of the inverse of the matrix is the
     * reciprocal of the
     * determinant of the original matrix, i.e., det(A^-1) = 1 / det(A)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test3(Matrix m) {
        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.inverse();

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(1 / source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 4: The determinant of the sum of two matrices is less
     * than or equal to
     * the sum of the determinants of the individual matrices, i.e., det(A + B) <=
     * det(A) + det(B)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test4(Matrix m1, Matrix m2) {
        assumeThat(m1.getNumberOfRows(), is(m2.getNumberOfRows()));
        assumeThat(m1.getNumberOfColumns(), is(m2.getNumberOfColumns()));

        /* Get source output */
        double source_res = m1.determinant() + m2.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m1.plus(m2); // Fix by Radon

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertTrue(follow_res <= source_res + 1e-6);
    }

    /**
     * Metamorphic Relation 5: The determinant of the product of two matrices is
     * equal to the
     * product of the determinants of the individual matrices, i.e., det(AB) =
     * det(A) * det(B)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test5(Matrix m1, Matrix m2) {
        assumeThat(m1.getNumberOfColumns(), is(m2.getNumberOfRows()));

        /* Get source output */
        double source_res = m1.determinant() * m2.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m1.times(m2);

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 6: The determinant of a triangular matrix is equal to
     * the product of its
     * diagonal elements, i.e., det(A) = a11 * a22 * ... * ann for an upper or lower
     * triangular
     * matrix A
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test6(Matrix m) {
        assumeThat(m.isSquare(), is(true));

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();

        // Set off-diagonal elements to zero
        for (int i = 0; i < follow_m.getNumberOfRows(); i++) {
            for (int j = 0; j < follow_m.getNumberOfColumns(); j++) {
                if (i != j) {
                    follow_m.setElement(i, j, 0.0);
                }
            }
        }

        /* Get follow-up output */
        double follow_res = 1.0;
        for (int i = 0; i < follow_m.getNumberOfRows(); i++) {
            follow_res *= follow_m.getElement(i, i);
        }

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 7: The determinant of the identity matrix is equal to 1,
     * i.e., det(I) =
     * 1
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test7(Matrix m) {
        assumeThat(m.isSquare(), is(true));

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = Matrix.identityMatrix(m.getNumberOfRows()); // Fix by Radon

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(1.0, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 8: The determinant of a matrix and its transpose matrix
     * are equal, i.e.,
     * det(A) = det(A^T)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test8(Matrix m) {
        assumeThat(m.isSquare(), is(true));

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.transpose();

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 9: The determinant of the sum of a matrix and its
     * inverse is greater
     * than or equal to zero, i.e., det(A + A^-1) >= 0
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test9(Matrix m) {
        assumeThat(m.isSquare(), is(true));

        /* Get source output */
        double source_res = m.determinant() + m.inverse().determinant();

        /* Construct follow-up input */
        // Add identity matrix to m and then get the determinant
        Matrix follow_m = m.plus(Matrix.identityMatrix(m.getNumberOfRows()));

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertTrue(follow_res >= 0.0 || Math.abs(follow_res) < 1e-6);
    }

    /**
     * 根据行对矩阵进行随机排列
     *
     * @param m
     * @return
     */
    public Matrix permutateMatrix(Matrix m) {
        int n = m.getNumberOfRows();
        int[] permutation = new int[n];

        for (int i = 0; i < n; i++) {
            permutation[i] = i;
        }
        Collections.shuffle(Arrays.asList(permutation)); // Randomly shuffle the permutation array

        Matrix perm_matrix = new Matrix(n, n);
        double[][] data = perm_matrix.getArrayReference();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                data[i][j] = m.getElement(permutation[i], j);
            }
        }

        return perm_matrix;
    }

    /**
     * Metamorphic Relation 10: Swapping two rows of a matrix changes the sign of
     * the determinant, i.e., det(PA) = -det(A) where P is a permutation matrix
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test10(Matrix m) {
        assumeThat(m.isSquare(), is(true));

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = permutateMatrix(m); // Optimize by Radon

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(-source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 11: The determinant of the sum of two identical matrices
     * is equal to
     * twice the determinant of the original matrix, i.e., det(A + A) = 2 * det(A)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test11(Matrix m) {
        /* Get source output */
        double source_res = m.determinant() * 2; // The determinant of A + A

        /* Construct follow-up input */
        Matrix follow_m = m.plus(m);

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 12: The determinant of a matrix and its negative matrix
     * have opposite
     * signs, i.e., det(-A) = (-1)^n * det(A) where n is the order of the matrix
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test12(Matrix m) {
        assumeThat(m.isSquare(), is(true));

        /* Get source output */
        double source_res = Math.pow(-1, m.getNumberOfRows()) * m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.times(-1); // Negation of all elements in the matrix. Fix by Radon

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 13: Scaling all elements in a matrix by a constant
     * scales the
     * determinant by the same constant raised to the power of the matrix order,
     * i.e., det(kA) = k^n
     * det(A) where n is the order of the matrix
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test13(Matrix m) {
        assumeThat(m.isSquare(), is(true));

        double scalingConstant = 2.5; // Replace with any desired constant

        /* Get source output */
        double source_res = Math.pow(scalingConstant, m.getNumberOfRows()) * m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.times(scalingConstant);

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 14: The determinant of a diagonal matrix is the product
     * of its diagonal elements, i.e., det(A) = a11 * a22 * ... * ann for a diagonal
     * matrix A
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test14(Matrix m) {
        assumeThat(m.isSquare(), is(true));

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();

        // Zero out all off-diagonal elements
        for (int i = 0; i < follow_m.getNumberOfRows(); i++) {
            for (int j = 0; j < follow_m.getNumberOfColumns(); j++) {
                if (i != j) {
                    follow_m.setElement(i, j, 0.0);
                }
            }
        }

        /* Get follow-up output */
        double follow_res = 1.0;
        for (int i = 0; i < follow_m.getNumberOfRows(); i++) {
            follow_res *= follow_m.getElement(i, i);
        }

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 15: Permuting rows in a matrix changes the sign of the
     * determinant, i.e., det(PA) = -det(A) where P is a permutation matrix
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test15(Matrix m) {
        assumeThat(m.isSquare(), is(true));

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        Matrix permutationMatrix = Matrix.identityMatrix(m.getNumberOfRows());

        /* Fix by Radon */
        permutationMatrix = permutateMatrix(permutationMatrix);

        follow_m = permutationMatrix.times(follow_m);

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(-source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 16: The determinant of a matrix is not affected by
     * scaling any row or column by a non-zero constant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test16(Matrix m) {
        assumeThat(m.isSquare(), is(true));

        int rowToScale = 0; // Replace with the desired row or column
        double scalingFactor = 2.0; // Replace with any non-zero constant

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();

        /* Fix by Radon */
        for (int i = 0; i < follow_m.getNumberOfColumns(); i++) {
            follow_m.setElement(rowToScale, i, follow_m.getElement(rowToScale, i) * scalingFactor);
        }

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Calculate cofactor of matrix
     *
     * @param m
     * @return
     */
    public static Matrix getCofactor(Matrix input) {
        double[][] matrix = input.getArrayCopy();

        double[][] cofactorMatrix = new double[matrix.length][matrix.length];
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix.length; j++) {
                double[][] minor = new double[matrix.length - 1][matrix.length - 1];
                for (int m = 0; m < matrix.length; m++) {
                    for (int n = 0; n < matrix.length; n++) {
                        if (m != i && n != j) {
                            int rowIndex = m < i ? m : m - 1;
                            int colIndex = n < j ? n : n - 1;
                            minor[rowIndex][colIndex] = matrix[m][n];
                        }
                    }
                }
                Matrix tmp = new Matrix(minor);
                cofactorMatrix[i][j] = Math.pow(-1, i + j) * tmp.determinant();
            }
        }

        return new Matrix(cofactorMatrix);
    }

    /**
     * Calculate adjoint matrix
     *
     * @param input
     * @return
     */
    public static Matrix getAdjointMatrix(Matrix input) {
        return getCofactor(input).transpose();
    }

    /**
     * Metamorphic Relation 17: The determinant of a matrix and its adjoint matrix
     * have a specific mathematical relation, i.e., det(A) = det(adjoint(A))
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test17(Matrix m) {
        assumeThat(m.isSquare(), is(true));

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix adjoint_m = getAdjointMatrix(m);

        /* Get follow-up output */
        double follow_res = adjoint_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    private static Matrix getMinor(Matrix input, int row, int column) {
        double[][] matrix = input.getArrayCopy();
        double[][] minor = new double[matrix.length - 1][matrix.length - 1];
        for (int i = 0, minorRow = 0; i < matrix.length; i++) {
            if (i == row)
                continue;
            for (int j = 0, minorCol = 0; j < matrix[i].length; j++) {
                if (j == column)
                    continue;
                minor[minorRow][minorCol] = matrix[i][j];
                minorCol++;
            }
            minorRow++;
        }
        return new Matrix(minor);
    }

    public double getCofactor(Matrix m, int row, int column) {
        Matrix minor = getMinor(m, row, column);
        double determinant = minor.determinant();
        return Math.pow(-1, row + column) * determinant;
    }

    /**
     * Metamorphic Relation 18: For a square matrix A, the determinant of A and its
     * cofactor matrix have a specific mathematical relation, i.e., det(A) = sum of
     * products of A and its cofactor matrix
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test18(Matrix m) {
        assumeThat(m.isSquare(), is(true));

        /* Get source output */
        double source_res = m.determinant();

        /* Calculate follow-up output using the mathematical relation */
        double follow_res = 0.0;
        for (int i = 0; i < m.getNumberOfColumns(); i++) {
            follow_res += m.getElement(0, i) * getCofactor(m, 0, i);
        }

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 19: If matrix B is obtained by interchanging two rows or
     * columns of matrix A, then det(B) equals det(A) multiplied by -1 raised to the
     * power of the number of interchanges
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test19(Matrix m) {
        assumeThat(m.isSquare(), is(true));

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        // Interchange two rows or columns of follow_m
        int row1 = 0; // Replace with the first row or column index to interchange
        int row2 = 1; // Replace with the second row or column index to interchange

        double[][] data = follow_m.getArrayCopy();
        double[] temp = data[row1];
        data[row1] = data[row2];
        data[row2] = temp;
        follow_m = new Matrix(data);

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Calculate the expected follow-up output using the mathematical relation */
        double expected_follow_res = Math.pow(-1, Math.abs(row1 - row2)) *
                source_res;

        /* Verification */
        assertEquals(expected_follow_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 20: The determinant of a block matrix is related to
     * the determinants of its submatrices according to specific mathematical rules
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test20(Matrix m) {
        assumeThat(m.getNumberOfRows(), is(4)); // Assuming a block matrix of size 4x4 for this example
        assumeThat(m.getNumberOfColumns(), is(4));

        /* Split the matrix into submatrices. Fix by Radon */
        Matrix A = m.getSubMatrix(new int[] { 0, 1 }, new int[] { 0, 1 }); // Top-left submatrix
        Matrix B = m.getSubMatrix(new int[] { 0, 1 }, new int[] { 2, 3 }); // Top-right submatrix
        Matrix C = m.getSubMatrix(new int[] { 2, 3 }, new int[] { 0, 1 }); // Bottom-left submatrix
        Matrix D = m.getSubMatrix(new int[] { 2, 3 }, new int[] { 2, 3 }); // Bottom-right submatrix

        /* Get source output */
        double source_res = m.determinant();

        /* Calculate follow-up output using the mathematical relation */
        // Assuming the block matrix is partitioned as [[A, B], [C, D]]
        double follow_res = A.determinant() * D.determinant() - B.determinant() *
                C.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 21: The determinant of an upper triangular matrix is the
     * product of its diagonal elements, i.e., det(A) = a11 * a22 * ... * ann for an
     * upper triangular matrix A
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test21(Matrix m) {
        /* Fix by Radon */
        assumeThat(m.isSquare(), is(true));

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        if (!m.isUpperTriagonal())
            return;

        /* Get follow-up output */
        double follow_res = 1.0;
        for (int i = 0; i < m.getNumberOfRows(); i++) {
            follow_res *= m.getElement(i, i);
        }

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 22: The determinant of a lower triangular matrix is the
     * product of its diagonal elements, i.e., det(A) = a11 * a22 * ... * ann for a
     * lower triangular matrix A
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test22(Matrix m) {
        /* Fix by Radon */
        assumeThat(m.isSquare(), is(true));

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        if (!m.isLowerTriagonal())
            return;

        /* Get follow-up output */
        double follow_res = 1.0;
        for (int i = 0; i < m.getNumberOfRows(); i++) {
            follow_res *= m.getElement(i, i);
        }

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Calculate the conjugate transpose of a real matrix
     * 
     * @param matrix
     * @return
     */
    public static ComplexMatrix conjugateTranspose(Matrix input) {
        double[][] matrix = input.getArrayCopy();

        // Convert the real matrix to a complex matrix
        Complex[][] complexMatrix = new Complex[matrix.length][matrix[0].length];
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[0].length; j++) {
                complexMatrix[i][j] = new Complex(matrix[i][j], 0.0);
            }
        }

        // Create a ComplexMatrix object
        ComplexMatrix complexMatrixObject = new ComplexMatrix(complexMatrix);

        // Transpose the matrix
        ComplexMatrix transposedMatrix = complexMatrixObject.transpose();

        // Take the complex conjugate of each element
        ComplexMatrix conjugateTransposedMatrix = transposedMatrix.conjugate();

        return conjugateTransposedMatrix;
    }

    /**
     * Metamorphic Relation 23: The determinant of a matrix is equal to the
     * determinant of its conjugate transpose, i.e., det(A) = det(A*) where A* is
     * the conjugate transpose of A
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test23(Matrix m) {
        // TODO
        // assumeThat(m.isSquare(), is(true));

        // /* Get source output */
        // double source_res = m.determinant();

        // /* Construct follow-up input */
        // ComplexMatrix follow_m = conjugateTranspose(m);

        // /* Get follow-up output */
        // double follow_res = follow_m.determinant();

        // /* Verification */
        // assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 24: The determinant of a matrix and its symmetric part
     * have a specific mathematical relation, i.e., det(A) = det((A + A^T) / 2)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test24(Matrix m) {
        assumeThat(m.isSquare(), is(true));

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.plus(m.transpose()).times(0.5); // Symmetric part of the matrix

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    public static ComplexMatrix calculateHermitianTranspose(Matrix input) {
        double[][] matrix = input.getArrayCopy();

        // Convert the real matrix to a complex matrix
        Complex[][] complexData = new Complex[matrix.length][matrix[0].length];
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                complexData[i][j] = new Complex(matrix[i][j], 0.0);
            }
        }

        // Create a ComplexMatrix object
        ComplexMatrix complexMatrix = new ComplexMatrix(complexData);

        // Transpose the matrix
        ComplexMatrix transposedMatrix = complexMatrix.transpose();

        // Conjugate the transposed matrix
        ComplexMatrix hermitianMatrix = transposedMatrix.conjugate();

        return hermitianMatrix;
    }

    /**
     * Metamorphic Relation 25: The determinant of a matrix and the determinant of
     * its Hermitian part have a specific mathematical relation, i.e., det(A) =
     * det((A + A^H) / 2)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test25(Matrix m) {
        // TODO
        // assumeThat(m.isSquare(), is(true));

        // /* Get source output */
        // double source_res = m.determinant();

        // /* Construct follow-up input */
        // Matrix follow_m = m.plus(m.hermitianTranspose()).times(0.5); // Hermitian
        // part of the matrix

        // /* Get follow-up output */
        // double follow_res = follow_m.determinant();

        // /* Verification */
        // assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 26: The determinant of a matrix and the determinant of
     * its skew-Hermitian part have a specific mathematical relation, i.e., det(A) =
     * i^n det((A - A^H) / 2)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test26(Matrix m) {
        // TODO
        // assumeThat(m.isSquare(), is(true));

        // /* Get source output */
        // double source_res = m.determinant();

        // /* Construct follow-up input */
        // Matrix follow_m = m.minus(m.hermitianTranspose()).times(0.5); //
        // Skew-Hermitian part of the matrix

        // /* Get follow-up output */
        // double follow_res = Math.pow(Math.sqrt(-1), m.getNumberOfRows()) *
        // follow_m.determinant();

        // /* Verification */
        // assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 27: The determinant of a matrix and the determinant of
     * its inverse transpose have a specific mathematical relation, i.e., det(A) = 1
     * / det(A^T)^{-1}
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test27(Matrix m) {
        assumeThat(m.isSquare(), is(true));
        assumeThat(m.determinant(), not(closeTo(0.0, 1e-6))); // Ensure determinant is non-zero

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.inverse().transpose();

        /* Get follow-up output */
        double follow_res = 1.0 / follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 28: The determinant of a unitary matrix has a specific
     * mathematical
     * relation, i.e., |det(A)| = 1 for a unitary matrix A
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test28(Matrix m) {
        // TODO
        // assumeThat(m.isSquare(), is(true));
        // assumeThat(m.times(m.hermitianTranspose()),
        // is(closeTo(Matrix.identityMatrix(m.getNumberOfRows()), 1e-6))); // Ensure
        // matrix is unitary

        // /* Get source output */
        // double source_res = m.determinant();

        // /* Get the absolute value of the determinant */
        // double abs_source_res = Math.abs(source_res);

        // /* Verification */
        // assertTrue(abs_source_res, closeTo(1.0, 1e-6));
    }

    /**
     * Metamorphic Relation 29: The determinant of a matrix and the determinant of
     * its singular value decomposition (SVD) have a specific mathematical relation,
     * i.e., det(A) = product of singular values of A
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test29(Matrix m) {
        // TODO
        // assumeThat(m.isSquare(), is(true));
        // SingularValueDecomposition svd = m.singularValueDecomposition();

        // /* Get source output */
        // double source_res = m.determinant();

        // /* Construct follow-up output using the singular values from the SVD */
        // double follow_res = 1.0;
        // for (double singularValue : svd.getSingularValues()) {
        // follow_res *= singularValue;
        // }

        // /* Verification */
        // assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 30: The determinant of a positive definite matrix is
     * always positive, i.e., det(A) > 0 for a positive definite matrix A
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test30(Matrix m) {
        // assumeThat(m.isSquare(), is(true));
        // assumeThat(m.isSymmetric(), is(true));
        // EigenvalueDecomposition evd = m.eigenvalueDecomposition();

        // /* Get source output */
        // double source_res = m.determinant();

        // /*
        // * Construct follow-up output by extracting the eigenvalues from the
        // * Eigenvalue Decomposition
        // */
        // double follow_res = 1.0;
        // for (double eigenvalue : evd.getRealEigenvalues()) {
        // follow_res *= eigenvalue;
        // }

        // /* Verification */
        // assertTrue(follow_res > 0);
        // assertEquals(source_res > 0, follow_res > 0);
    }

    /**
     * Metamorphic Relation 31: The determinant of a square matrix and its trace
     * raised to the power of the matrix order have a specific mathematical
     * relation, i.e., det(A) = trace(A)^n
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test31(Matrix m) {
        assumeThat(m.isSquare(), is(true));

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        double trace = m.trace();
        double power = Math.pow(trace, m.getNumberOfRows());

        /* Verification */
        assertEquals(source_res, power, 1e-6);
    }

    /**
     * Metamorphic Relation 32: The determinant of a matrix and the determinant of
     * its Jordan normal form have a specific mathematical relation, i.e., det(A) =
     * det(J) where J is the Jordan normal form of A
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(Matrix m) {
        // assumeThat(m.isSquare(), is(true));

        // /* Get source output */
        // double source_res = m.determinant();

        // /* Construct follow-up input */
        // EigenvalueDecomposition evd = m.eigenvalueDecomposition();
        // Matrix jordanMatrix =
        // evd.getV().times(evd.getD()).times(evd.getV().inverse());

        // /* Get follow-up output */
        // double follow_res = jordanMatrix.determinant();

        // /* Verification */
        // assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 33: The determinant of a matrix and the determinant of
     * its exponential have a specific mathematical relation, i.e., det(A) =
     * exp(trace(A))
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test33(Matrix m) {
        assumeThat(m.isSquare(), is(true));

        /* Get source output */
        double source_res = m.determinant();

        /* Calculate the exponential of the trace of the matrix */
        double trace = m.trace();
        double exp_trace = Math.exp(trace);

        /* Verification */
        assertEquals(source_res, exp_trace, 1e-6);
    }

    /**
     * Metamorphic Relation 34: The determinant of a matrix and the determinant of
     * its adjugate have a specific mathematical relation, i.e., det(A) =
     * det(Adj(A))
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(Matrix m) {
        // TODO
        // assumeThat(m.isSquare(), is(true));

        // /* Get source output */
        // double source_res = m.determinant();

        // /* Construct follow-up input */
        // Matrix follow_m = m.adjugate();

        // /* Get follow-up output */
        // double follow_res = follow_m.determinant();

        // /* Verification */
        // assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 35: The determinant of a matrix and the determinant of
     * its inverse
     * have a specific mathematical relation, i.e., det(A) * det(A^-1) = 1
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test35(Matrix m) {
        assumeThat(m.isSquare(), is(true));
        assumeThat(m.determinant(), not(closeTo(0.0, 1e-6))); // Ensure determinant is non-zero

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.inverse();

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Calculate the product of the determinants */
        double product_res = source_res * follow_res;

        /* Verification */
        assertEquals(1.0, product_res, 1e-6);
    }

    /**
     * Metamorphic Relation 36: The determinant of a matrix and the determinant of
     * its Hermitian conjugate have a specific mathematical relation, i.e., det(A) =
     * det(A^H)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(Matrix m) {
        // TODO
        // assumeThat(m.isSquare(), is(true));

        // /* Get source output */
        // double source_res = m.determinant();

        // /* Construct follow-up input */
        // Matrix follow_m = m.hermitianTranspose();

        // /* Get follow-up output */
        // double follow_res = follow_m.determinant();

        // /* Verification */
        // assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 37: The determinant of a matrix and the determinant of
     * its orthogonal projection have a specific mathematical relation, i.e., det(A)
     * = det(P), where P is the orthogonal projection matrix of A
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test37(Matrix m) {
        assumeThat(m.isSquare(), is(true));

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.times(m.inverse());

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 38: The determinant of a matrix and the determinant of
     * its principal submatrix have a specific mathematical relation, i.e., det(A) =
     * det(Ai) * det(Aii), where Ai is the ith principal submatrix of A, and
     * det(Aii) is the additional element of A used to form Ai
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test38(Matrix m) {
        assumeThat(m.isSquare(), is(true));

        int n = m.getNumberOfRows();
        if (n < 2)
            return;

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.getSubMatrix(0, n - 2, 0, n - 2); // Get the principal submatrix excluding the last row and
                                                              // column
        double additionalElement = m.getElement(n - 1, n - 1); // Additional element for the last row and column

        /* Get follow-up output */
        double follow_res = follow_m.determinant() * additionalElement;

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 39: The determinant of a matrix and the determinant of
     * its permutation
     * have a specific mathematical relation, i.e., det(A) = det(PA), where P is a
     * permutation
     * matrix
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test39(Matrix m) {
        assumeThat(m.isSquare(), is(true));

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = permutateMatrix(m).times(m);

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 40: The determinant of a column-wise concatenated matrix
     * and the determinant of its constituent matrices have a specific mathematical
     * relation, i.e., det(A) = det([A1 A2 ... An]), where [A1 A2 ... An] denotes
     * the column-wise concatenation of matrices A1, A2, ..., An
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test40(Matrix m) {
        // TODO
        // assumeThat(m.isSquare(), is(true));

        // int n = m.getNumberOfColumns();
        // if (n < 2)
        // return; // Ensure at least two columns for concatenation

        // /* Get source output */
        // double source_res = m.determinant();

        // /* Split the matrix into individual constituent matrices */
        // Matrix[] matrices = m.splitColumns();

        // /* Concatenate the constituent matrices */
        // Matrix concatenatedMatrix = Matrix.constructWithCopy(matrices);

        // /* Get follow-up output */
        // double follow_res = concatenatedMatrix.determinant();

        // /* Verification */
        // assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 41: The determinant of a matrix and the determinant of
     * its truncated diagonal matrix have a specific relation, i.e., det(A) =
     * det(A_{1:k, 1:k})
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test41(Matrix m) {
        assumeThat(m.isSquare(), is(true));

        int k = Math.min(2, m.getNumberOfRows()); // Select the first 2 rows and columns
        Matrix truncatedMatrix = m.getSubMatrix(0, k - 1, 0, k - 1);

        /* Get source output */
        double source_res = m.determinant();

        /* Get follow-up output */
        double follow_res = truncatedMatrix.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 42: The determinant of a block diagonal matrix and the
     * determinant of
     * its block matrices have a specific relation, i.e., det(A) is the product of
     * the determinants
     * of the block matrices
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test42(Matrix m) {
        // assumeThat(m.isSquare(), is(true));
        // if (m.getNumberOfColumns() < 2)
        //     return; // Ensure at least two blocks for block diagonal

        // /* Get block matrices along the diagonal */
        // Matrix[] blocks = m.splitBlockDiagonal();

        // /* Get source output */
        // double source_res = m.determinant();

        // /* Calculate the product of the determinants of the block matrices */
        // double follow_res = 1.0;
        // for (Matrix block : blocks) {
        //     follow_res *= block.determinant();
        // }

        // /* Verification */
        // assertEquals(source_res, follow_res, 1e-6);
    }

    static Stream<Arguments> testcaseProvider1() throws IOException {
        return testcaseGenerator.generate_m(1000);
    }

    static Stream<Arguments> testcaseProvider2() throws IOException {
        return testcaseGenerator.generate_mm(1000);
    }
}
