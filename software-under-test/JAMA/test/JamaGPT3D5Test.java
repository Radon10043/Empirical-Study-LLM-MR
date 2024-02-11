package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

import java.io.IOException;
import java.security.SecureRandom;
import java.util.stream.Stream;
import org.junit.Assume;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import Jama.EigenvalueDecomposition;
import Jama.LUDecomposition;
import Jama.Matrix;
import Jama.SingularValueDecomposition;

public class JamaGPT3D5Test {
    /**
     * Metamorphic Relation 1: The determinant of the matrix is equal to the determinant of its inverse.
     * In mathematical terms, det(A) = 1 / det(inv(A))
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test1(Matrix m) {
        assumeTrue(Math.abs(m.det()) > 1e-6);

        /* Get source output */
        double source_out = m.det();

        /* Construct follow-up input */
        Matrix follow_m = m.inverse();

        /* Get follow-up output */
        double follow_out = follow_m.det();

        /* Verification */
        assertEquals(source_out, 1 / follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 2: The determinant of the product of two matrices equals the product of their determinants.
     * In mathematical terms, det(A * B) = det(A) * det(B)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test2(Matrix m1, Matrix m2) {
        /* Get source output */
        double source_out = m1.times(m2).det();

        /* Get source output for individual matrices */
        double source_out_m1 = m1.det();
        double source_out_m2 = m2.det();

        /* Verification */
        assertEquals(source_out, source_out_m1 * source_out_m2, 1e-6);
    }

    /**
     * Metamorphic Relation 3: The determinant of the sum of two matrices is not greater than the sum of their individual determinants.
     * In mathematical terms, det(A + B) ≤ det(A) + det(B)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test3(Matrix m1, Matrix m2) {
        /* Get source output */
        double source_out = m1.plus(m2).det();

        /* Get source output for individual matrices */
        double source_out_m1 = m1.det();
        double source_out_m2 = m2.det();

        /* Verification */
        assertTrue(source_out <= (source_out_m1 + source_out_m2));
    }

    /**
     * Metamorphic Relation 4: The determinant of a diagonal matrix should be the product of its diagonal elements.
     * In mathematical terms, det(D) = Π(diagonal elements)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test4(Matrix m) {
        /* Make sure m is a diagonal matrix */
        for (int i = 0; i < m.getRowDimension(); i++) {
            for (int j = 0; j < m.getColumnDimension(); j++) {
                if (i != j) {
                    m.set(i, j, 0);;
                }
            }
        }

        /* Get source output */
        double product = 1.0;
        for (int i = 0; i < m.getRowDimension(); i++)
            product *= m.get(i, i);

        /* Verification */
        assertEquals(product, m.det(), 1e-6);
    }

    /**
     * Metamorphic Relation 5: The determinant of the inverse of the transpose of a matrix is equal to the determinant of the original matrix.
     * In mathematical terms, det((A^T)^-1) = det(A)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test5(Matrix m) {
        assumeTrue(Math.abs(m.det()) > 1e-6);

        /* Get source output */
        double source_out = m.det();

        /* Construct follow-up input */
        Matrix follow_m = m.transpose().inverse();

        /* Get follow-up output */
        double follow_out = follow_m.det();

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 6: Swapping rows of a matrix changes the sign of its determinant.
     * In mathematical terms, det(A) = -det(A'), where A' is the matrix obtained by swapping two rows of A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test6(Matrix m) {
        assumeTrue(m.getRowDimension() > 1);
        SecureRandom rand = new SecureRandom();

        /* Choose two distinct rows randomly */
        int row1 = rand.nextInt(m.getRowDimension());
        int row2 = row1;
        while(row2 == row1) {
            row2 = rand.nextInt(m.getRowDimension());
        }

        /* Get source output */
        double source_out = m.det();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        for (int i = 0; i < m.getColumnDimension(); i++) {
            double temp = follow_m.get(row1, i);
            follow_m.set(row1, i, follow_m.get(row2, i));
            follow_m.set(row2, i, temp);
        }

        /* Get follow-up output */
        double follow_out = follow_m.det();

        /* Verification */
        assertEquals(-source_out, follow_out, 1e-6);
    }

    /**
     * Generate a random permutation matrix of size n.
     *
     * @param n
     * @return
     */
    public Matrix generateRandomPermutationMatrix(int n) {
        SecureRandom rand = new SecureRandom();
        Matrix permutationMatrix = new Matrix(n, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int val = rand.nextBoolean() ? 1 : 0;
                permutationMatrix.set(i, j, val);
            }
        }
        return permutationMatrix;
    }

    /**
     * Metamorphic Relation 7: The determinant of a matrix and its permutation matrix should be equal.
     * In mathematical terms, det(P * A) = det(A), where P is a permutation matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test7(Matrix m) {
        /* Generate a random permutation matrix */
        Matrix permutationMatrix = generateRandomPermutationMatrix(m.getRowDimension());

        /* Get source output */
        double source_out = m.det();

        /* Get follow-up output */
        double follow_out = permutationMatrix.times(m).det();

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 8: The determinant of the identity matrix is 1.
     * In mathematical terms, det(I) = 1, where I is the identity matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(Matrix m) {
        /* Make sure m is the identity matrix */
        m = Matrix.identity(m.getRowDimension(), m.getColumnDimension());

        /* Verification */
        assertEquals(1.0, m.det(), 1e-6);
    }

    /**
     * Metamorphic Relation 9: The determinant of a matrix with a scalar multiple added to one of its rows is equal to the determinant of the original matrix.
     * In mathematical terms, det(A) = det(A'), where A' is the matrix obtained by adding a scalar multiple to one of the rows of A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test9(Matrix m) {
        SecureRandom rand = new SecureRandom();

        int rowNum = rand.nextInt(m.getRowDimension());
        double scalar = rand.nextDouble() * 10;

        /* Get source output */
        double source_out = m.det();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        for (int i = 0; i < m.getColumnDimension(); i++) {
            follow_m.set(rowNum, i, m.get(rowNum, i) + scalar);
        }

        /* Get follow-up output */
        double follow_out = follow_m.det();

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 10: The determinant of a symmetric positive definite matrix is always positive.
     * In mathematical terms, if A is a symmetric positive definite matrix, det(A) > 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test10(Matrix m) {
        // assumeTrue(m.isSymmetric() && isPositiveDefinite(m));

        // /* Get source output */
        // double source_out = m.det();

        // /* Verification */
        // assertTrue(source_out > 0);
    }

    /**
     * Metamorphic Relation 11: The determinant of the Hermitian conjugate of a matrix is the complex conjugate of the determinant of the original matrix.
     * In mathematical terms, det(A*) = det(A)*, where A* is the Hermitian conjugate of A and det(A)* is the complex conjugate of det(A).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test11(Matrix m) {
        // /* Get source output */
        // double source_out = m.det();

        // /* Construct follow-up input */
        // Matrix follow_m = m.transpose().conjugate();

        // /* Get follow-up output */
        // double follow_out = follow_m.det();

        // /* Verification */
        // assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Calculate the adjoint of a matrix.
     * @param m
     * @return
     */
    public Matrix adjoint(Matrix m) {
        return m.inverse().times(m.det());
    }

    /**
     * Metamorphic Relation 12: Multiplying a matrix by its adjoint gives the determinant times the identity matrix.
     * In mathematical terms, det(A)*A = det(A)*I, where A* is the adjoint of A and I is the identity matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test12(Matrix m) {
        assumeTrue(Math.abs(m.det()) > 1e-6);

        /* Get source output */
        double detA = m.det();
        Matrix identityMatrix = Matrix.identity(m.getRowDimension(), m.getColumnDimension());
        Matrix expected = identityMatrix.times(detA);

        /* Get follow-up output */
        Matrix adjointA = adjoint(m);
        Matrix result = adjointA.times(m);

        /* Verification */
        assertTrue(expected.equals(result));
    }

    /**
     * Metamorphic Relation 13: The determinant of a product of two matrices is equal to the determinant of their individual matrices.
     * In mathematical terms, det(A * B) = det(A) * det(B)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test13(Matrix m1, Matrix m2) {
        /* Get source output */
        double source_out = m1.times(m2).det();

        /* Get source output for individual matrices */
        double source_out_m1 = m1.det();
        double source_out_m2 = m2.det();

        /* Verification */
        assertEquals(source_out, source_out_m1 * source_out_m2, 1e-6);
    }

    /**
     * Metamorphic Relation 14: The determinant of a block diagonal matrix is the product of the determinants of its diagonal blocks.
     * In mathematical terms, if A is a block diagonal matrix with diagonal blocks B1, B2, ..., Bk, then det(A) = det(B1) * det(B2) * ... * det(Bk)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test14(Matrix m) {
        // assumeTrue(m.isBlockDiagonal());

        // /* Get source output */
        // double source_out = m.det();

        // /* Get source output for individual diagonal blocks */
        // double product = 1.0;
        // for (int i = 0; i < m.getRowDimension(); i++) {
        //     if (m.isBlock(i, i)) {
        //         product *= m.getDiagonalBlock(i).det();
        //     }
        // }

        // /* Verification */
        // assertEquals(product, source_out, 1e-6);
    }

    /**
     * Calculate the cofactor matrix of a matrix.
     * @param m
     * @return
     */
    public Matrix cofactorMatrix(Matrix m) {
        return adjoint(m).transpose();
    }

    /**
     * Metamorphic Relation 15: The determinant of a matrix and its cofactor matrix is related by
     * a particular formula det(A) = Σ(a_ij * C_ij), for a given row or column of A, where C_ij is the cofactor of a_ij in matrix A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test15(Matrix m) {
        assumeTrue(Math.abs(m.det()) > 1e-6);
        SecureRandom rand = new SecureRandom();

        int dimension = m.getRowDimension();
        int row = rand.nextInt(dimension);
        int col = rand.nextInt(dimension);

        double cofactorSum = 0.0;
        Matrix cofactorMat = cofactorMatrix(m);
        for (int i = 0; i < dimension; i++) {
            cofactorSum += m.get(row, i) * cofactorMat.get(row, i);
            cofactorSum += m.get(i, col) * cofactorMat.get(i, col);
        }

        /* Get source output */
        double source_out = m.det();

        /* Verification */
        assertEquals(source_out, cofactorSum, 1e-6);
    }

    /**
     * Metamorphic Relation 16: If the determinant of a matrix A is zero, then its inverse does not exist.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test16(Matrix m) {
        // /* Get source output */
        // double source_out = m.det();

        // if (Math.abs(source_out) < 1e-6) {
        //     /* If determinant is close to zero, inverse should not exist */
        //     assertThrows(SingularMatrixException.class, () -> m.inverse());
        // } else {
        //     /* If determinant is non-zero, inverse should exist */
        //     assertNotNull(m.inverse());
        // }
    }

    /**
     * Metamorphic Relation 17: The determinant of a matrix and the determinant of its upper triangular matrix of the LU decomposition have the same value.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test17(Matrix m) {
        /* Get source output */
        double source_out = m.det();

        /* Perform LU decomposition */
        LUDecomposition luDecomposition = new LUDecomposition(m);
        Matrix upperTriangularMatrix = luDecomposition.getU();

        /* Get follow-up output */
        double follow_out = upperTriangularMatrix.det();

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 18: The determinant of the Kronecker product of two matrices is the product of their determinants.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test18(Matrix m1, Matrix m2) {
        // /* Get source output */
        // double source_out = m1.kron(m2).det();

        // /* Get source output for individual matrices */
        // double source_out_m1 = m1.det();
        // double source_out_m2 = m2.det();

        // /* Verification */
        // assertEquals(source_out, source_out_m1 * source_out_m2, 1e-6);
    }

    /**
     * Metamorphic Relation 19: The determinant of the matrix and its orthogonal complement have a specific relationship given by: det(A) * det(orthogonalComplement(A)) = 1
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test19(Matrix m) {
        // /* Get source output */
        // double source_out = m.det();

        // /* Get orthogonal complement of the matrix */
        // Matrix orthogonalComplement = m.orthogonalComplement();

        // /* Get determinant of the orthogonal complement */
        // double complement_det = orthogonalComplement.det();

        // /* Verification */
        // assertEquals(1.0, source_out * complement_det, 1e-6);
    }

    /**
     * Metamorphic Relation 20: For a permutation matrix, its determinant is either 1 or -1 based on whether the number of row exchanges required to transform the matrix into the identity matrix is even or odd.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test20(Matrix m) {
        // assumeTrue(m.isPermutation());

        // int numberOfRowExchanges = getNumberOfRowExchangesToIdentity(m);

        // /* Get source output */
        // double source_out = m.det();

        // /* Verification */
        // if (numberOfRowExchanges % 2 == 0) {
        //     assertEquals(1.0, source_out, 1e-6);
        // } else {
        //     assertEquals(-1.0, source_out, 1e-6);
        // }
    }

    /**
     * Metamorphic Relation 21: The determinant of a matrix is equal to the determinant of its conjugate transpose.
     * In mathematical terms, det(A) = det(A*), where A* is the conjugate transpose of A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test21(Matrix m) {
        // /* Get source output */
        // double source_out = m.det();

        // /* Construct follow-up input */
        // Matrix follow_m = m.transpose().conjugate();

        // /* Get follow-up output */
        // double follow_out = follow_m.det();

        // /* Verification */
        // assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 22: The determinant of the inverse of a matrix is equal to the reciprocal of the determinant of the original matrix.
     * In mathematical terms, if det(A) ≠ 0, then det(A^-1) = 1 / det(A).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test22(Matrix m) {
        /* Get source output */
        double source_out = m.det();

        Assume.assumeTrue(Math.abs(source_out) > 1e-6); // Ensure the determinant is non-zero

        /* Construct follow-up input */
        Matrix follow_m = m.inverse();

        /* Get follow-up output */
        double follow_out = follow_m.det();

        /* Verification */
        assertEquals(1 / source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 23: The determinant of a matrix and the determinant of its LU factorization have the same absolute value.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test23(Matrix m) {
        /* Get source output */
        double source_out = Math.abs(m.det());

        /* Perform LU factorization */
        LUDecomposition luDecomposition = new LUDecomposition(m);
        double follow_out = Math.abs(luDecomposition.det());

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 24: The determinant of a matrix and its trace are related by a specific formula: det(A) = exp(tr(log(A))), where tr() is the trace and log() is the matrix logarithm.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test24(Matrix m) {
        assumeTrue(m.trace() > 0);

        /* Get source output */
        double source_out_det = m.det();
        double source_out_trace = m.trace();

        /* Calculate exp(tr(log(m))) */
        double follow_out = Math.exp(Math.log(source_out_trace));

        /* Verification */
        assertEquals(source_out_det, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 25: The determinant of a matrix and the determinant of another matrix obtained by adding a multiple of one row to another are equal.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test25(Matrix m) {
        assumeTrue(m.getRowDimension() > 1);
        SecureRandom rand = new SecureRandom();

        int rowNum1 = rand.nextInt(m.getRowDimension());
        int rowNum2 = rowNum1;
        while (rowNum2 == rowNum1) {
            rowNum2 = rand.nextInt(m.getRowDimension());
        }
        double scalar = 2.0;

        /* Get source output */
        double source_out = m.det();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        for (int i = 0; i < m.getColumnDimension(); i++) {
            double val1 = m.get(rowNum1, i);
            double val2 = m.get(rowNum2, i);
            follow_m.set(rowNum2, i, val2 + scalar * val1);
        }

        /* Get follow-up output */
        double follow_out = follow_m.det();

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 26: The determinant of a matrix and its pseudo-inverse matrix have a specific relationship: det(A) * det(pseudoInverse(A)) ≈ 1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test26(Matrix m) {
        // /* Get source output */
        // double source_out = m.det();

        // /* Get pseudo-inverse matrix */
        // Matrix pseudoInverse = m.pseudoInverse();

        // /* Get determinant of the pseudo-inverse */
        // double pseudoInverseDet = pseudoInverse.det();

        // /* Verification */
        // assertEquals(1.0, source_out * pseudoInverseDet, 1e-6);
    }

    /**
     * Metamorphic Relation 27: The determinant of a matrix and the determinant of its hessenberg form are equivalent.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test27(Matrix m) {
        // /* Get source output */
        // double source_out = m.det();

        // /* Get hessenberg form */
        // HessenbergDecomposition hessenbergDecomposition = new HessenbergDecomposition(m);
        // Matrix hessenbergForm = hessenbergDecomposition.getH();

        // /* Get follow-up output */
        // double follow_out = hessenbergForm.det();

        // /* Verification */
        // assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 28: The determinant of a matrix and the determinant of its singular value decomposition have the same value.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test28(Matrix m) {
        /* Get source output */
        double source_out = m.det();

        /* Get singular value decomposition */
        SingularValueDecomposition svd = new SingularValueDecomposition(m);
        Matrix s = svd.getS();

        /* Get follow-up output */
        double follow_out = s.det();

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 29: The determinant of a diagonalizable matrix is the product of its eigenvalues.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test29(Matrix m) {
        /* Make sure m is diagonalizable matrix */
        for (int i = 0; i < m.getRowDimension(); i++) {
            for (int j = 0; j < m.getColumnDimension(); j++) {
                if (i != j) {
                    m.set(i, j, 0);;
                }
            }
        }

        /* Get eigenvalues */
        EigenvalueDecomposition evd = new EigenvalueDecomposition(m);
        double[] eigenvalues = evd.getRealEigenvalues();

        /* Calculate product of eigenvalues */
        double product = 1.0;
        for (double eigenvalue : eigenvalues) {
            product *= eigenvalue;
        }

        /* Get source output */
        double source_out = m.det();

        /* Verification */
        assertEquals(product, source_out, 1e-6);
    }

    /**
     * Metamorphic Relation 30: The determinant of a matrix and the determinant of its Householder transformation have the same absolute value.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(Matrix m) {
        // /* Get source output */
        // double source_out = Math.abs(m.det());

        // /* Get Householder transformation */
        // HouseholderTransformation h = new HouseholderTransformation(m);

        // /* Get follow-up output */
        // double follow_out = Math.abs(h.getH().det());

        // /* Verification */
        // assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 31: Multiplying a matrix by its characteristic polynomial matrix results in a matrix with determinant 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test31(Matrix m) {
        // /* Get characteristic polynomial matrix */
        // Matrix charPolyMatrix = m.getCharacteristicPolynomial().evaluate(m);

        // /* Get source output */
        // double source_out = charPolyMatrix.det();

        // /* Verification */
        // assertEquals(0, source_out, 1e-6);
    }

    /**
     * Metamorphic Relation 32: The determinant of the sum of two matrices is less than or equal to the sum of the absolute values of their determinants.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test32(Matrix m1, Matrix m2) {
        /* Get source outputs */
        double source_out_sum = Math.abs(m1.det()) + Math.abs(m2.det());
        double source_out = (m1.plus(m2)).det();

        /* Verification */
        assertTrue(source_out <= source_out_sum);
    }

    /**
     * Metamorphic Relation 33: The determinant of a matrix and the determinant of its exponential matrix have a specific relationship: det(A) = exp(tr(A)), where tr() is the trace.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test33(Matrix m) {
        // /* Get source output */
        // double source_out_det = m.det();
        // double source_out_trace = m.trace();

        // /* Get determinant of the exponential matrix */
        // Matrix expMatrix = m.exp();
        // double follow_out = expMatrix.det();

        // /* Verification */
        // assertEquals(Math.exp(source_out_trace), follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 34: The determinant of the sum of a matrix and its negative is zero: det(A + (-A)) = 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test34(Matrix m) {
        /* Get source output */
        double source_out = m.plus(m.uminus()).det();

        /* Verification */
        assertEquals(0, source_out, 1e-6);
    }

    /**
     * Metamorphic Relation 35: The determinant of an orthogonal matrix is either 1 or -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test35(Matrix m) {
        // /* Assume m is an orthogonal matrix */
        // assumeTrue(m.isOrthogonal());

        // /* Get source output */
        // double source_out = m.det();

        // /* Verification */
        // assertTrue(source_out == 1 || source_out == -1);
    }

    /**
     * Metamorphic Relation 36: The determinant of a block matrix can be expressed as the product of the determinants of its individual blocks.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test36(Matrix m) {
        // assumeTrue(m.isBlockMatrix());

        // /* Get source output */
        // double source_out = m.det();

        // /* Get source output for individual blocks */
        // double product = 1.0;
        // for (int i = 0; i < m.getRowDimension(); i++) {
        //     for (int j = 0; j < m.getColumnDimension(); j++) {
        //         if (m.isBlock(i, j)) {
        //             product *= m.get(i, j).det();
        //         }
        //     }
        // }

        // /* Verification */
        // assertEquals(product, source_out, 1e-6);
    }

    /**
     * Metamorphic Relation 37: The determinant of a matrix is unchanged under row operations like permutation or duplication.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test37(Matrix m) {
        // /* Get source output */
        // double source_out = m.det();

        // /* Perform row operations */
        // Matrix permuted = m.permuteRows(0, 1);
        // Matrix duplicated = m.duplicateRow(2, 1);

        // /* Get follow-up outputs */
        // double permuted_det = permuted.det();
        // double duplicated_det = duplicated.det();

        // /* Verification */
        // assertEquals(source_out, permuted_det, 1e-6);
        // assertEquals(source_out, duplicated_det, 1e-6);
    }

    /**
     * Metamorphic Relation 38: The determinant of a matrix and its quantization with respect to a specific threshold have a specific relationship.
     * For example, det(A) = det(round(A / threshold) * threshold).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test38(Matrix m) {
        double threshold = 10;

        /* Get source output */
        double source_out = m.det();

        /* Get quantized matrix */
        Matrix quantized = m.copy();
        for (int i = 0; i < m.getRowDimension(); i++) {
            for (int j = 0; j < m.getColumnDimension(); j++) {
                quantized.set(i, j, Math.round(m.get(i, j) / threshold) * threshold);
            }
        }

        /* Get follow-up output */
        double follow_out = quantized.det();

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 39: The determinant of a matrix and the determinant of the matrix obtained by multiplying all its elements with a scalar have a specific relationship:
     * det(s * A) = s^n * det(A), where s is the scalar and n is the dimension of the matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test39(Matrix m) {
        double scalar = 2.0;

        /* Get source output */
        double source_out = Math.pow(scalar, m.getRowDimension()) * m.det();

        /* Construct follow-up input */
        Matrix follow_m = m.times(scalar);

        /* Get follow-up output */
        double follow_out = follow_m.det();

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 40: The determinant of a matrix and the determinant of its power raise a specific power have the following relationship:
     * det(A^k) = (det(A))^k, where k is a positive integer.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test40(Matrix m) {
        int power = 3;

        /* Get source output */
        double source_out = m.det();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        for (int i = 0; i < power; i++)
            follow_m = follow_m.times(power);

        /* Get follow-up output */
        double follow_out = follow_m.det();

        /* Verification */
        assertEquals(Math.pow(source_out, power), follow_out, 1e-6);
    }

    static Stream<Arguments> testcaseProvider1() throws IOException {
        return testcaseGenerator.generate(1000);
    }

    static Stream<Arguments> testcaseProvider2() throws IOException {
        return testcaseGenerator.generate_mm(1000);
    }
}
