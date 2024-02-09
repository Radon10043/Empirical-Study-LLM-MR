package test;

import static org.junit.Assume.assumeFalse;
import static org.junit.Assume.assumeThat;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

import java.io.IOException;
import java.security.SecureRandom;
import java.util.Arrays;
import java.util.Collections;
import java.util.stream.Stream;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import flanagan.complex.Complex;
import flanagan.complex.ComplexMatrix;
import flanagan.math.Matrix;

public class Determinant1TestGPT3D5 {
    /**
     * Metamorphic Relation 1: The determinant of the matrix is equal to the determinant of its
     * inverse, i.e., det(A)=det(A^-1)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test1(Matrix m) {
        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.inverse();

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 2: The determinant of the product of two matrices is equal to the
     * product of their determinants, i.e., det(AB) = det(A) * det(B)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test2(Matrix m1, Matrix m2) {
        assumeTrue(m1.getNumberOfColumns() == m2.getNumberOfRows()); // Check the pre-condition for
                                                                     // matrix multiplication

        /* Get source output */
        double source_res = m1.times(m2).determinant();

        /* Get follow-up output */
        double follow_res = m1.determinant() * m2.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 3: The determinant of the sum of two matrices is not necessarily equal
     * to the sum of their determinants, i.e., det(A + B) != det(A) + det(B)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test3(Matrix m1, Matrix m2) {
        assumeTrue(m1.getNumberOfRows() == m2.getNumberOfRows()
                && m1.getNumberOfColumns() == m2.getNumberOfColumns()); // Check the pre-condition
                                                                        // for matrix addition

        /* Get source output */
        double source_res = m1.plus(m2).determinant();

        /* Get follow-up output */
        double follow_res = m1.determinant() + m2.determinant();

        /* Verification */
        assertNotEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 4: The determinant of a scalar multiple of a matrix is equal to the
     * determinant of the original matrix multiplied by the same scalar, i.e., det(kA) = k^n *
     * det(A) (where k is a scalar and n is the number of rows or columns of A)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test4(Matrix m) {
        double constant = 5.0;

        /* Get source output */
        double source_res = Math.pow(constant, m.getNumberOfRows()) * m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.times(constant);

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 5: The determinant of a diagonal matrix is the product of its diagonal
     * elements, i.e., det(D) = product of diagonal elements of D
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test5(Matrix m) {
        assumeTrue(m.isDiagonal()); // Check if the matrix is diagonal

        /* Get source output */
        double source_res = m.determinant();

        /* Get follow-up output */
        double follow_res = 1.0; // Initialize to 1
        for (int i = 0; i < m.getNumberOfRows(); i++) {
            follow_res *= m.getElement(i, i); // Multiply the diagonal elements
        }

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 6: The determinant of the identity matrix of order n is 1, i.e., det(I)
     * = 1, where I is the identity matrix of order n.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(Matrix m) {
        int order = 3; // Example: identity matrix of order 3
        Matrix identity = Matrix.identityMatrix(order);

        /* Get source output */
        double source_res = identity.determinant();

        /* Verification */
        assertEquals(1.0, source_res, 1e-6);
    }

    /**
     * Metamorphic Relation 7: The determinant of a matrix and its transpose are equal, i.e., det(A)
     * = det(A^T)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test7(Matrix m) {
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
     * Metamorphic Relation 8: Multiplying a matrix A by its inverse should result in the identity
     * matrix, i.e., A * A^-1 = I, where I is the identity matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test8(Matrix m) {
        assumeTrue(m.isSquare()); // Check if the matrix is square
        assumeFalse(Math.abs(m.determinant()) < 1e-6);

        /* Get source output */
        Matrix inverse = m.inverse();
        Matrix product = m.times(inverse);

        /* Verification */
        assertTrue(product.equals(Matrix.identityMatrix(m.getNumberOfRows())));
    }

    /**
     * Metamorphic Relation 9: Scaling a row of a matrix with a scalar factor scales the determinant
     * of the matrix by the same factor, i.e., det(A') = k * det(A), where A' is the matrix
     * resulting from scaling a row of matrix A with factor k.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test9(Matrix m) {
        int k = 2;
        int rowToScale = 0; // Scale the first row for example

        /* Get source output */
        double source_res = m.determinant() * k;

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        for (int i = 0; i < m.getNumberOfColumns(); i++) {
            follow_m.setElement(rowToScale, i, m.getElement(rowToScale, i) * k); // Scale the first
                                                                                 // row
        }

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 10: Swapping two rows of a matrix changes the sign of its determinant,
     * i.e., det(A') = -det(A), where A' is the matrix resulting from swapping two rows of matrix A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test10(Matrix m) {
        assumeTrue(m.getNumberOfRows() >= 2); // Check if the matrix has at least two rows

        /* Get source output */
        double source_res = -m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        // Swap the first and second rows
        for (int i = 0; i < m.getNumberOfColumns(); i++) {
            double tmp = follow_m.getElement(0, i);
            follow_m.setElement(0, i, follow_m.getElement(1, i));
            follow_m.setElement(1, i, tmp);
        }

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 11: Adding a multiple of one row to another row does not change the
     * determinant of the matrix, i.e., det(A) = det(A'), where A' is the matrix resulting from
     * adding a multiple of one row of matrix A to another row.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test11(Matrix m) {
        assumeTrue(m.getNumberOfRows() >= 2); // Check if the matrix has at least two rows

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        // Add a multiple of the first row to the second row
        double factor = 2.0;
        for (int i = 0; i < m.getNumberOfColumns(); i++) {
            follow_m.setElement(1, i,
                    follow_m.getElement(1, i) + factor * follow_m.getElement(0, i));
        }

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 12: If two rows of a matrix are equal, then its determinant is zero,
     * i.e., det(A) = 0, where A is a matrix with at least two equal rows.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test12(Matrix m) {
        assumeTrue(m.getNumberOfRows() >= 2); // Check if the matrix has at least two rows

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        // Set the second row equal to the first row
        for (int i = 0; i < m.getNumberOfColumns(); i++) {
            follow_m.setElement(1, i, follow_m.getElement(0, i));
        }

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(0.0, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 13: Combining two square matrices into a block matrix and taking the
     * determinant yields a result related to the product of the individual determinants, i.e.,
     * det([A B; C D]) = det(A) * det(D - C * A^-1 * B)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider3")
    public void test13(Matrix A, Matrix B, Matrix C, Matrix D) {
        assumeTrue(A.getNumberOfRows() == B.getNumberOfRows()
                && C.getNumberOfRows() == D.getNumberOfRows()
                && A.getNumberOfColumns() == C.getNumberOfColumns()
                && B.getNumberOfColumns() == D.getNumberOfColumns()); // Check if the blocks are of
                                                                      // the same size

        assumeTrue(A.isSquare() && D.isSquare()); // Check if A and D are square matrices

        assumeTrue(Math.abs(A.determinant()) > 1e-6); // Check if A is non-singular

        /* Compute the value det(D - C * A^-1 * B) */
        Matrix temp1 = A.inverse().times(B);
        Matrix temp2 = D.plus(C.times(temp1).times(-1));
        double tempDeterminant = temp2.determinant();

        /* Get source output */
        int size = A.getNumberOfRows();
        Matrix bigMatrix = new Matrix(size * 2, size * 2);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                bigMatrix.setElement(i, j, A.getElement(i, j));
                bigMatrix.setElement(i, j + size, B.getElement(i, j));
                bigMatrix.setElement(i + size, j, C.getElement(i, j));
                bigMatrix.setElement(i + size, j + size, D.getElement(i, j));
            }
        }
        double source_res = bigMatrix.determinant();

        /* Verification */
        assertEquals(A.determinant() * tempDeterminant, source_res, 1e-6);
    }

    public Matrix getCofactor(Matrix m, Matrix temp, int p, int q, int n) {
        int i = 0, j = 0;
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (row != p && col != q) {
                    temp.setElement(i, j++, m.getElement(row, col));
                    if (j == n - 1) {
                        j = 0;
                        i++;
                    }
                }
            }
        }
        return temp;
    }

    /**
     * Get the adjoint matrix of m adj(m) = det(m) * m^-1
     *
     * @param m
     * @return
     */
    public Matrix adjoint(Matrix m) {
        return m.inverse().times(m.determinant());
    }

    /**
     * Metamorphic Relation 14: The determinant of a matrix and its adjoint are related by a power
     * of n-1, where n is the size of the matrix, i.e., det(A) = det(Adj(A))^(n-1)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test14(Matrix m) {
        assumeTrue(m.isSquare()); // Check if the matrix is square
        assumeTrue(Math.abs(m.determinant()) > 1e-6); // Check if the matrix is non-singular

        /* Get source output */
        double source_res = Math.pow(adjoint(m).determinant(), m.getNumberOfRows() - 1);

        /* Verification */
        assertEquals(m.determinant(), source_res, 1e-6);
    }

    /**
     * Metamorphic Relation 15: The determinant of a triangular matrix is the product of its
     * diagonal elements, i.e., det(A) = product of diagonal elements of A
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test15(Matrix m) {
        // Make sure the matrix is triangular
        for (int i = 0; i < m.getNumberOfRows(); i++) {
            for (int j = 0; j < i; j++) {
                m.setElement(i, j, 0);
            }
        }

        /* Get source output */
        double source_res = 1.0; // Initialize to 1
        for (int i = 0; i < m.getNumberOfRows(); i++) {
            source_res *= m.getElement(i, i); // Multiply the diagonal elements
        }

        /* Verification */
        assertEquals(m.determinant(), source_res, 1e-6);
    }

    public Matrix cofactorMatrix(Matrix m) {
        return adjoint(m.transpose());
    }

    /**
     * Metamorphic Relation 16: The determinant of a matrix and its cofactor matrix are related by
     * the formula det(A) = det(cof(A)) / det(A).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test16(Matrix m) {
        assumeTrue(m.isSquare()); // Check if the matrix is square
        assumeTrue(Math.abs(m.determinant()) > 1e-6); // Check if the matrix is non-singular

        /* Get source output */
        double source_res = cofactorMatrix(m).determinant() / m.determinant();

        /* Verification */
        assertEquals(source_res, 1.0, 1e-6);
    }

    public Matrix elementaryRowOperation(Matrix m, int row1, int row2, double factor) {
        for (int i = 0; i < m.getNumberOfColumns(); i++) {
            m.setElement(row2, i, m.getElement(row2, i) + factor * m.getElement(row1, i));
        }
        return m;
    }

    /**
     * Metamorphic Relation 17: The determinant of a matrix and its elementary matrix related by the
     * formula det(A) = det(E) * det(A), where E is an elementary matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test17(Matrix m) {
        assumeTrue(m.isSquare()); // Check if the matrix is square
        assumeTrue(m.getNumberOfRows() >= 2); // Check if the matrix has at least two rows

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix identity = Matrix.identityMatrix(m.getNumberOfRows());
        Matrix elementary = elementaryRowOperation(identity, 0, 1, 2); // Apply elementary row
                                                                       // operation for example

        /* Get follow-up output */
        double follow_res = elementary.determinant() * source_res;

        /* Verification */
        assertEquals(follow_res, source_res, 1e-6);
    }

    /**
     * Metamorphic Relation 18: For a matrix A, if B is obtained from A by swapping two columns, the
     * determinant remains the same, i.e., det(A) = det(B).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test18(Matrix m) {
        assumeTrue(m.getNumberOfColumns() >= 2); // Check if the matrix has at least two columns

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        // Swap the first and second columns
        for (int i = 0; i < m.getNumberOfRows(); i++) {
            double tmp = follow_m.getElement(i, 0);
            follow_m.setElement(i, 0, follow_m.getElement(i, 1));
            follow_m.setElement(i, 1, tmp);
        }

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 19: Adding a multiple of one column to another column does not change
     * the determinant of the matrix, i.e., det(A) = det(A'), where A' is the matrix resulting from
     * adding a multiple of one column of matrix A to another column.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test19(Matrix m) {
        assumeTrue(m.getNumberOfColumns() >= 2); // Check if the matrix has at least two columns

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        // Add a multiple of the first column to the second column
        double factor = 2.0;
        for (int i = 0; i < m.getNumberOfRows(); i++) {
            follow_m.setElement(i, 1,
                    follow_m.getElement(i, 1) + factor * follow_m.getElement(i, 0));
        }

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 20: Transposing a matrix twice should yield the original matrix and thus
     * the same determinant, i.e., det(A) = det(A^T^T).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test20(Matrix m) {
        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.transpose().transpose();

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 21: For an orthogonal matrix A, its determinant should be either 1 or
     * -1, i.e., det(A) = 1 or -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test21(Matrix m) {
        assumeTrue(m.isSquare()); // Check if the matrix is square

        /* Get source output */
        double source_res = m.determinant();

        /* Verification */
        assertTrue(source_res == 1.0 || source_res == -1.0);
    }

    /**
     * Metamorphic Relation 22: For an upper triangular matrix A, the determinant is the product of
     * its diagonal elements, i.e., det(A) = product of diagonal elements of A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(Matrix m) {
        // Make sure the matrix is upper triangular
        for (int i = 0; i < m.getNumberOfRows(); i++) {
            for (int j = 0; j < i; j++) {
                m.setElement(i, j, 0);
            }
        }

        /* Get source output */
        double source_res = 1.0; // Initialize to 1
        for (int i = 0; i < m.getNumberOfRows(); i++) {
            source_res *= m.getElement(i, i); // Multiply the diagonal elements
        }

        /* Verification */
        assertEquals(m.determinant(), source_res, 1e-6);
    }

    /**
     * Metamorphic Relation 23: For a lower triangular matrix A, the determinant is the product of
     * its diagonal elements, i.e., det(A) = product of diagonal elements of A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(Matrix m) {
        // Make sure the matrix is lower triangular
        for (int i = 0; i < m.getNumberOfRows(); i++) {
            for (int j = i + 1; j < m.getNumberOfColumns(); j++) {
                m.setElement(i, j, 0);
            }
        }

        /* Get source output */
        double source_res = 1.0; // Initialize to 1
        for (int i = 0; i < m.getNumberOfRows(); i++) {
            source_res *= m.getElement(i, i); // Multiply the diagonal elements
        }

        /* Verification */
        assertEquals(m.determinant(), source_res, 1e-6);
    }

    /**
     * Metamorphic Relation 24: For a matrix A, the determinant of A and its cofactor matrix are
     * related by the formula det(A) = det(cof(A))^T, where T represents the transpose.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test24(Matrix m) {
        assumeTrue(m.isSquare()); // Check if the matrix is square
        assumeTrue(Math.abs(m.determinant()) > 1e-6); // Check if the matrix is non-singular

        /* Get source output */
        double source_res = m.determinant();
        double cofactorTransposeDeterminant = cofactorMatrix(m).transpose().determinant();

        /* Verification */
        assertEquals(source_res, cofactorTransposeDeterminant, 1e-6);
    }

    /**
     * Metamorphic Relation 25: For a triangular matrix A and a diagonal matrix D, the determinant
     * of A multiply D is equal to the determinant of A multiplied by the determinant of D, i.e.,
     * det(AD) = det(A) * det(D).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test25(Matrix m, Matrix d) {
        assumeTrue(m.isSquare() && d.isDiagonal()); // Check if the matrices are square and diagonal

        /* Get source output */
        double source_res = m.times(d).determinant();
        double determinant_product = m.determinant() * d.determinant();

        /* Verification */
        assertEquals(source_res, determinant_product, 1e-6);
    }

    /**
     * Metamorphic Relation 26: For a matrix A and an identity matrix I, the determinant of A
     * multiplied by I is equal to the determinant of A, i.e., det(AI) = det(A)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test26(Matrix m) {
        assumeTrue(m.isSquare()); // Check if the matrix is square
        int order = m.getNumberOfRows();

        /* Get source output */
        double source_res = m.times(Matrix.identityMatrix(order)).determinant();

        /* Verification */
        assertEquals(m.determinant(), source_res, 1e-6);
    }

    /**
     * Metamorphic Relation 27: For a matrix A, its determinant and the determinant of its inverse
     * are inversely related, i.e., det(A) * det(A^-1) = 1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test27(Matrix m) {
        assumeTrue(m.isSquare()); // Check if the matrix is square
        assumeTrue(Math.abs(m.determinant()) > 1e-6); // Check if the matrix is non-singular

        /* Get source output */
        double source_res = m.determinant() * m.inverse().determinant();

        /* Verification */
        assertEquals(1.0, source_res, 1e-6);
    }

    /**
     * Metamorphic Relation 28: For a matrix A and a permutation matrix P, the determinant of A
     * multiplied by P should be equal to the determinant of A multiplied by the sign of the
     * permutation. i.e., det(AP) = det(A) * sign(P).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider4")
    public void test28(Matrix m, Matrix p) {
        assumeTrue(m.isSquare()); // Check if the matrices are square and the second one is a
                                  // permutation matrix

        /* Get source output */
        double source_res = m.times(p).determinant();
        int signP = p.determinant() < 0 ? -1 : 1; // sign(P) is the sign of the permutation matrix

        /* Verification */
        assertEquals(m.determinant() * signP, source_res, 1e-6);
    }

    /**
     * Metamorphic Relation 29: For a matrix A and a unitary matrix U, the determinant of A
     * multiplied by U should be equal to the determinant of A. i.e., det(AU) = det(A).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test29(Matrix m, Matrix u) {
        // assumeTrue(m.isSquare() && u.isUnitary()); // Check if the matrices are square and the
        // second one is unitary

        // /* Get source output */
        // double source_res = m.times(u).determinant();

        // /* Verification */
        // assertEquals(m.determinant(), source_res, 1e-6);
    }

    /**
     * Metamorphic Relation 30: For a matrix A and a symmetric matrix S, the determinant of A
     * multiplied by S should be equal to the determinant of A multiplied by the determinant of S.
     * i.e., det(AS) = det(A) * det(S).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test30(Matrix m) {
        assumeTrue(m.isSquare()); // Check if the matrices are square and the second one is
                                  // symmetric

        int size = m.getNumberOfRows();
        Matrix s = new Matrix(size, size);
        SecureRandom rand = new SecureRandom();
        for (int i = 0; i < size; i++) {
            for (int j = i; j < size; j++) {
                int val = rand.nextInt(1, 5);
                s.setElement(i, j, val);
                s.setElement(j, i, val);
            }
        }

        /* Get source output */
        double source_res = m.times(s).determinant();

        /* Verification */
        assertEquals(m.determinant() * s.determinant(), source_res, 1e-6);
    }

    /**
     * Metamorphic Relation 31: For a matrix A and an orthogonal matrix O, the determinant of A
     * multiplied by O should be equal to the determinant of A multiplied by 1 or -1, depending on
     * whether O is a proper or improper orthogonal matrix. i.e., det(AO) = det(A) * sign(O).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test31(Matrix m, Matrix o) {
        // assumeTrue(m.isSquare()); // Check if the matrices are square and the second one is
        // orthogonal

        // Matrix o = generateOrthogonalMatrix(m.getNumberOfRows());

        // /* Get source output */
        // double source_res = m.times(o).determinant();
        // int signO = o.determinant() < 0 ? -1 : 1; // 1 for proper, -1 for improper orthogonal
        // matrix

        // /* Verification */
        // assertEquals(m.determinant() * signO, source_res, 1e-6);
    }

    /**
     * Metamorphic Relation 32: For a matrix A and a skew-symmetric matrix S, the determinant of A
     * multiplied by S should be equal to the determinant of A multiplied by the exponentiation of
     * -1 raised to the power of the rank of A. i.e., det(AS) = det(A) * (-1)^rank(A).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test32(Matrix m) {
        // assumeTrue(m.isSquare()); // Check if the matrices are square

        // Matrix s = generateSkewSymmetricMatrix(m.getNumberOfRows());

        // /* Get source output */
        // double source_res = m.times(s).determinant();
        // int rankA = m.rank();

        // /* Verification */
        // assertEquals(m.determinant() * Math.pow(-1, rankA), source_res, 1e-6);
    }

    /**
     * Metamorphic Relation 33: For a matrix A and a Hermitian matrix H, the determinant of A
     * multiplied by H should be equal to the determinant of A multiplied by the determinant of H.
     * i.e., det(AH) = det(A) * det(H).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test33(Matrix m, Matrix h) {
        // assumeTrue(m.isSquare() && h.isHermitian()); // Check if the matrices are square and the
        // second one is Hermitian

        // /* Get source output */
        // double source_res = m.times(h).determinant();

        // /* Verification */
        // assertEquals(m.determinant() * h.determinant(), source_res, 1e-6);
    }

    /**
     * Metamorphic Relation 34: For an upper triangular matrix A and a factor k, the determinant of
     * kA is k raised to the power of the size of A multiplied by the determinant of A, i.e.,
     * det(kA) = k^(n) * det(A), where k is a factor and n is the size of A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test34(Matrix m) {
        assumeTrue(m.isSquare()); // Check if the matrix is square
        int size = m.getNumberOfRows();

        // Select a random factor
        double k = 2 + Math.random() * 10;

        /* Get source output */
        double source_res = Math.pow(k, size) * m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        for (int i = 0; i < m.getNumberOfRows(); i++) {
            for (int j = 0; j < m.getNumberOfColumns(); j++) {
                follow_m.setElement(i, j, m.getElement(i, j) * k);
            }
        }

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 35: For a diagonal matrix A and a factor k, the determinant of kA is k
     * raised to the power of the size of A multiplied by the determinant of A, i.e., det(kA) =
     * k^(n) * det(A), where k is a factor and n is the size of A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(Matrix m) {
        assumeTrue(m.isDiagonal()); // Check if the matrix is diagonal
        int size = m.getNumberOfRows();

        // Select a random factor
        double k = 2 + Math.random() * 10;

        /* Get source output */
        double source_res = Math.pow(k, size) * m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        for (int i = 0; i < m.getNumberOfRows(); i++) {
            for (int j = 0; j < m.getNumberOfColumns(); j++) {
                follow_m.setElement(i, j, m.getElement(i, j) * k);
            }
        }

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 36: For a matrix A, the determinant of A and the determinant of its
     * column-wise absolute values are related by the formula det(A) = |det(|A|)|, where det(|A|) is
     * the determinant of A after taking the absolute value of each element in A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test36(Matrix m) {
        /* Get source output */
        double source_res = Math.abs(m.determinant());

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        for (int i = 0; i < m.getNumberOfRows(); i++) {
            for (int j = 0; j < m.getNumberOfColumns(); j++) {
                follow_m.setElement(i, j, Math.abs(m.getElement(i, j)));
            }
        }

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 37: For a matrix A and a scalar k, the determinant of matrix A and kA
     * are related by the formula det(kA) = k^n * det(A), where k is a scalar and n is the size of
     * A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test37(Matrix m) {
        assumeTrue(m.isSquare()); // Check if the matrix is square
        int size = m.getNumberOfRows();

        // Select a random factor
        double k = 2 + Math.random() * 10;

        /* Get source output */
        double source_res = Math.pow(k, size) * m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        for (int i = 0; i < m.getNumberOfRows(); i++) {
            for (int j = 0; j < m.getNumberOfColumns(); j++) {
                follow_m.setElement(i, j, m.getElement(i, j) * k);
            }
        }

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 38: For a matrix A, the determinant of A and the determinant of its
     * element-wise negation are related by the formula det(A) = (-1)^n * det(-A), where n is the
     * size of A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test38(Matrix m) {
        assumeTrue(m.isSquare()); // Check if the matrix is square
        int size = m.getNumberOfRows();

        /* Get source output */
        double source_res = Math.pow(-1, size) * m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        for (int i = 0; i < m.getNumberOfRows(); i++) {
            for (int j = 0; j < m.getNumberOfColumns(); j++) {
                follow_m.setElement(i, j, -m.getElement(i, j));
            }
        }

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 39: For a matrix A and its inverse, the determinant of the inverse
     * matrix is the reciprocal of the determinant of A. i.e., det(A^-1) = 1/det(A).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test39(Matrix m) {
        assumeTrue(m.isSquare() && Math.abs(m.determinant()) > 1e-6); // Check if the matrix is
                                                                      // square and invertible

        /* Get source output */
        double source_res = 1.0 / m.determinant();
        Matrix inverse = m.inverse();

        /* Verification */
        assertEquals(source_res, inverse.determinant(), 1e-6);
    }

    /**
     * Metamorphic Relation 40: For a square diagonal matrix A, the determinant of A^k is equal to
     * the determinant of A raised to the power of k, i.e., det(A^k) = (det(A))^k.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test40(Matrix m) {
        assumeTrue(m.isSquare() && m.isDiagonal()); // Check if the matrix is square and diagonal

        int k = 3; // Select a power k

        /* Get source output */
        double source_res = Math.pow(m.determinant(), k);

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        for (int i = 0; i < k; i++) {
            follow_m = follow_m.times(m);
        }

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    static Stream<Arguments> testcaseProvider1() throws IOException {
        return testcaseGenerator.generate_m(1000);
    }

    static Stream<Arguments> testcaseProvider2() throws IOException {
        return testcaseGenerator.generate_mm(1000);
    }

    static Stream<Arguments> testcaseProvider3() throws IOException {
        return testcaseGenerator.generate_m4(1000);
    }

    static Stream<Arguments> testcaseProvider4() throws IOException {
        return testcaseGenerator.generate_mpm(1000);
    }
}
