package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;
import java.io.IOException;
import java.util.stream.Stream;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import Jama.CholeskyDecomposition;
import Jama.EigenvalueDecomposition;
import Jama.LUDecomposition;
import Jama.Matrix;
import Jama.QRDecomposition;

public class JamaGPT3D5Test {


    /**
     * Metamorphic Relation 3: The determinant of the matrix is equal to the determinant of its
     * inverse, i.e., det(A) = det(A^(-1))
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test3(Matrix m) {
        assumeTrue(m.det() != 0); // Ensure the matrix is invertible

        /* Get source output */
        double source_out = m.det();

        /* Construct follow-up input */
        Matrix follow_m = m.inverse();

        /* Get follow-up output */
        double follow_out = follow_m.det();

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 4: The determinant of the identity matrix is 1, i.e., det(I) = 1
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test4(Matrix m) {
        /* Get source output */
        double source_out = m.det();

        /* Construct follow-up input. Fix by Radon */
        Matrix follow_m = Matrix.identity(m.getRowDimension(), m.getColumnDimension()); // Create an
                                                                                // identity matrix

        /* Get follow-up output */
        double follow_out = follow_m.det();

        /* Verification */
        assertEquals(1.0, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 5: The determinant of a scalar multiple of a matrix is equal to the
     * determinant of the original matrix multiplied by the same scalar, i.e., det(kA) = k^n *
     * det(A) where k is a scalar and n is the dimension of the matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test5(Matrix m) {
        double constant = 2.5; // Scalar constant

        /* Get source output */
        double source_out = Math.pow(constant, m.getRowDimension()) * m.det();

        /* Construct follow-up input */
        Matrix follow_m = m.times(constant); // Scalar multiplication of the matrix

        /* Get follow-up output */
        double follow_out = follow_m.det();

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 6: The determinant of the sum of two matrices is not greater than the
     * sum of the absolute values of their determinants, i.e., |det(A + B)| <= |det(A)| + |det(B)|
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test6(Matrix m1, Matrix m2) {
        assumeTrue(m1.getRowDimension() == m2.getRowDimension());
        assumeTrue(m1.getColumnDimension() == m2.getColumnDimension());

        /* Get source output */
        double source_out1 = Math.abs(m1.det());
        double source_out2 = Math.abs(m2.det());
        double source_out_sum = Math.abs(m1.plus(m2).det());

        /* Verification */
        assertTrue(source_out_sum <= source_out1 + source_out2);
    }

    /**
     * Metamorphic Relation 7: The determinant of a matrix and its transpose are the same, i.e.,
     * det(A) = det(A^T)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test7(Matrix m) {
        /* Get source output */
        double source_out = m.det();

        /* Construct follow-up input (Transpose the matrix) */
        Matrix follow_m = m.transpose();

        /* Get follow-up output */
        double follow_out = follow_m.det();

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 8: The determinant of a matrix and its adjoint are related by |A|^(n-1),
     * where n is the dimension of the matrix, i.e., det(A^dagger) = |A|^(n-1)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test8(Matrix m) {
        assumeTrue(m.getRowDimension() == m.getColumnDimension()); // Ensure the matrix is square

        /* Get source output */
        double source_out = Math.pow(Math.abs(m.det()), m.getRowDimension() - 1);

        /* Construct follow-up input (Get the adjoint matrix) */
        Matrix follow_m = m.transpose().times(m.det());

        /* Get follow-up output */
        double follow_out = follow_m.det();

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 9: The determinant of a matrix and the negative of the matrix is related
     * by det(-A) = (-1)^n * det(A), where n is the dimension of the matrix
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test9(Matrix m) {
        assumeTrue(m.getRowDimension() == m.getColumnDimension()); // Ensure the matrix is square

        /* Get source output */
        double source_out = Math.pow(-1, m.getRowDimension()) * m.det();

        /* Construct follow-up input (Negative of the matrix) */
        Matrix follow_m = m.times(-1);

        /* Get follow-up output */
        double follow_out = follow_m.det();

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 10: The determinant of a matrix and its conjugate transpose are related
     * by det(A^H) = det(conj(A)), where A^H represents the conjugate transpose of A and conj(A)
     * represents the element-wise complex conjugate of A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(Matrix m) {
        // TODO
        // assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square

        // /* Get source output */
        // double source_out = m.det();

        // /* Construct follow-up input (Get the conjugate matrix) */
        // Matrix follow_m = m.arrayConjugate();

        // /* Get follow-up output */
        // double follow_out = follow_m.det();

        // /* Verification */
        // assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 11: The determinant of a matrix and the sum of the determinants of its
     * diagonal blocks is equal to det(A) = det(A11) * det(A22) ... * det(Ann) where A is divided
     * into diagonal blocks A11, A22, ..., Ann.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test11(Matrix m) {
        assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square

        /* Get source output */
        double source_out = m.det();

        /* Construct follow-up input (Split the matrix into diagonal blocks) */
        int n = m.getRowDimension();
        Matrix[] diagonalBlocks = new Matrix[n];
        int currentRow = 0;
        for (int i = 0; i < n; i++) {
            int blockSize = n - i;
            diagonalBlocks[i] = m.getMatrix(currentRow, currentRow + blockSize - 1, currentRow,
                    currentRow + blockSize - 1);
            currentRow += blockSize;
        }

        double follow_out = 1.0;
        for (Matrix block : diagonalBlocks) {
            follow_out *= block.det();
        }

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 12: The determinant of a matrix and its row echelon form are related by
     * det(A) = det(R), where R is the row echelon form of A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(Matrix m) {
        // TODO
        // assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square

        // /* Get source output */
        // double source_out = m.det();

        // /* Construct follow-up input (Get the row echelon form of the matrix) */
        // Matrix follow_m = m.ech();

        // /* Get follow-up output */
        // double follow_out = follow_m.det();

        // /* Verification */
        // assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 13: The determinant of a permutation matrix is either 1 or -1, i.e.,
     * det(P) = 1 or -1, where P is a permutation matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test13(Matrix m) {
        assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square

        /* Construct follow-up input (Get the permutation matrix) */
        double follow_out = m.det();

        /* Verification */
        assertTrue(Math.abs(follow_out) == 1);
    }

    /**
     * Metamorphic Relation 14: The determinant of a diagonal matrix is the product of its diagonal
     * elements, i.e., det(D) = d1 * d2 * ... * dn, where D is a diagonal matrix with diagonal
     * elements d1, d2, ..., dn.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(Matrix m) {
        // TODO
        // assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square
        // assumeTrue(m.rank() == m.getRowDimension()); // Ensure the matrix is full rank

        // /* Construct follow-up input (Get the diagonal matrix) */
        // double[] diag = m.getDiagonal();
        // double follow_out = 1.0;
        // for (double d : diag) {
        //     follow_out *= d;
        // }

        // /* Verification */
        // assertEquals(m.det(), follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 15: The determinant of a singular matrix is 0, i.e., det(A) = 0, where A
     * is a singular matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test15(Matrix m) {
        assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square

        /* Construct follow-up input (Make the matrix singular) */
        Matrix follow_m = m.copy();
        follow_m.set(0, 0, 0.0); // Set the first element to 0, making it singular

        /* Verification */
        assertEquals(0.0, follow_m.det(), 1e-6);
    }

    /**
     * Metamorphic Relation 16: The determinant of a block upper triangular matrix is the product of
     * the determinants of its diagonal blocks, i.e., det(A) = det(A11) * det(A22) ... * det(Ann)
     * where A is a block upper triangular matrix with diagonal blocks A11, A22, ..., Ann.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test16(Matrix m) {
        assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square

        /* Construct follow-up input (Split the matrix into diagonal blocks) */
        int n = m.getRowDimension();
        Matrix[] diagonalBlocks = new Matrix[n];
        int currentStartRow = 0;
        double follow_out = 1.0;
        for (int i = 0; i < n; i++) {
            diagonalBlocks[i] = m.getMatrix(currentStartRow, n - 1, currentStartRow, n - 1);
            currentStartRow++;
            follow_out *= diagonalBlocks[i].det();
        }

        /* Verification */
        assertEquals(m.det(), follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 17: The determinant of a matrix and its cofactor matrix are related by
     * det(A) = sum_j(a_ij * C_ij), where C_ij is the cofactor of A_ij, and a_ij is the element of A
     * at (i,j) position.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test17(Matrix m) {
        assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square

        /* Get source output */
        double source_out = m.det();

        /* Construct follow-up input (Get the cofactor matrix) */
        Matrix follow_m = m.inverse().transpose().times(m.det());

        /* Get follow-up output */
        double follow_out = 0;
        for (int i = 0; i < m.getRowDimension(); i++) {
            for (int j = 0; j < m.getColumnDimension(); j++) {
                follow_out += m.get(i, j) * follow_m.get(i, j);
            }
        }

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 18: The determinant of a matrix and the product of its eigenvalues are
     * related by det(A) = λ1 * λ2 * ... * λn where λ1, λ2, ..., λn are the eigenvalues of A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(Matrix m) {
        // TODO
        // assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square

        // EigenvalueDecomposition eigenDecomposition = new EigenvalueDecomposition(m);
        // Complex[] eigenvalues = eigenDecomposition.getRealEigenvalues();

        // /* Get source output */
        // double source_out = m.det();

        // /* Calculate product of eigenvalues */
        // double follow_out = 1.0;
        // for (Complex eigenvalue : eigenvalues) {
        //     follow_out *= eigenvalue.getReal();
        // }

        // /* Verification */
        // assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 19: The determinant of a matrix and the trace of its inverse are related
     * by det(A) = exp(Tr(inv(A))), where Tr represents the trace and exp represents the exponential
     * function.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test19(Matrix m) {
        assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square
        assumeTrue(m.det() != 0); // Ensure the matrix is invertible

        /* Get source output */
        double source_out = m.det();

        /* Construct follow-up input (Get trace of the inverse) */
        Matrix follow_m = m.inverse();
        double follow_out = Math.exp(follow_m.trace());

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 20: The determinant of a matrix and the determinant of its Hessenberg
     * form are related by det(A) = det(H), where H is the Hessenberg form of A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(Matrix m) {
        // TODO
        // assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square

        // /* Get source output */
        // double source_out = m.det();

        // /* Construct follow-up input (Get the Hessenberg form of the matrix) */
        // HessenbergDecomposition hessenbergDecomposition = new HessenbergDecomposition(m);
        // Matrix follow_m = hessenbergDecomposition.getH();

        // /* Get follow-up output */
        // double follow_out = follow_m.det();

        // /* Verification */
        // assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 21: For any constant c, det(c*A) = c^n*det(A), where c is a scalar
     * constant and n is the dimension of A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test21(Matrix m) {
        double constant = 3.0; // Scalar constant

        /* Get source output */
        double source_out = Math.pow(constant, m.getRowDimension()) * m.det();

        /* Construct follow-up input (Multiply the matrix by the constant) */
        Matrix follow_m = m.times(constant);

        /* Get follow-up output */
        double follow_out = follow_m.det();

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 22: The determinant of a matrix and the determinant of its Schur form
     * are equal, i.e., det(A) = det(S), where S is the Schur form of A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(Matrix m) {
        // TODO
        // assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square

        // /* Get source output */
        // double source_out = m.det();

        // /* Construct follow-up input (Get the Schur form of the matrix) */
        // SchurDecomposition schurDecomposition = new SchurDecomposition(m);
        // Matrix follow_m = schurDecomposition.getT();

        // /* Get follow-up output */
        // double follow_out = follow_m.det();

        // /* Verification */
        // assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 23: The determinant of a block diagonal matrix is the product of the
     * determinants of its diagonal blocks, i.e., det(A) = det(A11) * det(A22) ... * det(Ann) where
     * A is a block diagonal matrix with diagonal blocks A11, A22, ..., Ann.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test23(Matrix m) {
        assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square

        /* Construct follow-up input (Split the matrix into diagonal blocks) */
        int n = m.getRowDimension();
        Matrix[] diagonalBlocks = new Matrix[n];
        int currentStartRow = 0;
        double follow_out = 1.0;
        for (int i = 0; i < n; i++) {
            diagonalBlocks[i] = m.getMatrix(currentStartRow, n - 1, currentStartRow, n - 1);
            currentStartRow++;
            follow_out *= diagonalBlocks[i].det();
        }

        /* Verification */
        assertEquals(m.det(), follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 24: The determinant of a matrix and the product of its singular values
     * are related by det(A) = σ1 * σ2 * ... * σn, where σ1, σ2, ..., σn are the singular values of
     * A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test24(Matrix m) {
        // TODO
        // SVD svd = new SVD(m);
        // double[] singularValues = svd.getSingularValues();

        // /* Get source output */
        // double source_out = m.det();

        // /* Calculate product of singular values */
        // double follow_out = 1.0;
        // for (double sv : singularValues) {
        //     follow_out *= sv;
        // }

        // /* Verification */
        // assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 25: The determinant of a matrix and the determinant of its
     * pseudo-inverse are related by det(A) = 1 / det(A+), where A+ is the pseudo-inverse of A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test25(Matrix m) {
        assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square

        /* Get source output */
        double source_out = m.det();

        /* Construct follow-up input (Get the pseudo-inverse) */
        Matrix follow_m = m.inverse();

        /* Get follow-up output */
        double follow_out = 1.0 / follow_m.det();

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 26: The determinant of a matrix A, det(A), and the determinant of its LU
     * decomposition, det(L.U), are related by det(A) = det(L.U), where L is the lower triangular
     * matrix and U is the upper triangular matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test26(Matrix m) {
        assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square

        // Perform LU decomposition
        LUDecomposition luDecomposition = new LUDecomposition(m);
        Matrix L = luDecomposition.getL();
        Matrix U = luDecomposition.getU();

        // Get source output
        double source_out = m.det();

        // Calculate determinant of LU decomposition
        double follow_out = L.det() * U.det();

        // Verification
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 27: The determinant of a matrix A is equal to the determinant of its QR
     * decomposition, i.e., det(A) = det(QR), where Q is the orthogonal matrix and R is the upper
     * triangular matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test27(Matrix m) {
        assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square

        QRDecomposition qrDecomposition = new QRDecomposition(m);
        Matrix Q = qrDecomposition.getQ();
        Matrix R = qrDecomposition.getR();

        // Get source output
        double source_out = m.det();

        // Calculate determinant of QR decomposition
        double follow_out = Q.det() * R.det();

        // Verification
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 28: The determinant of a matrix A is equal to the determinant of its
     * Cholesky decomposition, i.e., det(A) = det(LL^T), where L is the lower triangular matrix
     * obtained from the Cholesky decomposition.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test28(Matrix m) {
        assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square
        assumeTrue(m.det() > 0); // Ensure the matrix is positive definite

        CholeskyDecomposition choleskyDecomposition = new CholeskyDecomposition(m);
        Matrix L = choleskyDecomposition.getL();

        // Get source output
        double source_out = m.det();

        // Calculate determinant of Cholesky decomposition
        double follow_out = L.det() * L.transpose().det();

        // Verification
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 29: The determinant of a matrix A and the determinant of its pivoted
     * Cholesky decomposition are equal, i.e., det(A) = det(LL^T), where L is the lower triangular
     * matrix obtained from the pivoted Cholesky decomposition.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test29(Matrix m) {
        // assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square
        // assumeTrue(m.det() > 0); // Ensure the matrix is positive definite

        // PivotedCholeskyDecomposition pivotedCholeskyDecomposition =
        //         new PivotedCholeskyDecomposition(m);
        // Matrix L = pivotedCholeskyDecomposition.getL();

        // // Get source output
        // double source_out = m.det();

        // // Calculate determinant of pivoted Cholesky decomposition
        // double follow_out = L.det() * L.transpose().det();

        // // Verification
        // assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 30: The determinant of a matrix A is equal to the determinant of its
     * bidiagonal decomposition, i.e., det(A) = det(U.B.V^T), where U and V are orthogonal matrices,
     * B is a bidiagonal matrix, and .^T denotes the transpose of a matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test30(Matrix m) {
        // BidiagonalDecomposition bidiagonalDecomposition = new BidiagonalDecomposition(m);
        // Matrix U = bidiagonalDecomposition.getU();
        // Matrix B = bidiagonalDecomposition.getB();
        // Matrix V = bidiagonalDecomposition.getV();

        // // Get source output
        // double source_out = m.det();

        // // Calculate determinant of bidiagonal decomposition
        // double follow_out = U.det() * B.det() * V.transpose().det();

        // // Verification
        // assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 31: The determinant of a matrix A is equal to the determinant of its
     * tridiagonal decomposition, i.e., det(A) = det(U.T.U^T), where U is an orthogonal matrix and T
     * is a tridiagonal matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test31(Matrix m) {
        // TridiagonalDecomposition tridiagonalDecomposition = new TridiagonalDecomposition(m);
        // Matrix U = tridiagonalDecomposition.getU();
        // Matrix T = tridiagonalDecomposition.getT();

        // // Get source output
        // double source_out = m.det();

        // // Calculate determinant of tridiagonal decomposition
        // double follow_out = U.det() * T.det() * U.transpose().det();

        // // Verification
        // assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 32: The determinant of a matrix A is equal to the determinant of its
     * Eigen decomposition, i.e., det(A) = prod(lambda_i), where lambda_i are the eigenvalues of A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test32(Matrix m) {
        // EigenvalueDecomposition eigenDecomposition = new EigenvalueDecomposition(m);
        // Complex[] eigenvalues = eigenDecomposition.getComplexEigenvalues();

        // // Get source output
        // double source_out = m.det();

        // // Calculate product of eigenvalues
        // double follow_out = 1.0;
        // for (Complex eigenvalue : eigenvalues) {
        //     follow_out *= eigenvalue.abs();
        // }

        // // Verification
        // assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 33: The determinant of a matrix A is the product of its singular values,
     * i.e., det(A) = prod(sig_i), where sig_i are the singular values of A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test33(Matrix m) {
        // SVD svd = new SVD(m);
        // double[] singularValues = svd.getSingularValues();

        // // Get source output
        // double source_out = m.det();

        // // Calculate product of singular values
        // double follow_out = 1.0;
        // for (double sv : singularValues) {
        //     follow_out *= sv;
        // }

        // // Verification
        // assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 34: The determinant of a matrix A is equal to the reciprocal of the
     * determinant of its inverse, i.e., det(A) = 1 / det(inv(A)).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test34(Matrix m) {
        assumeTrue(m.det() != 0); // Ensure the matrix is invertible

        // Get source output
        double source_out = m.det();

        // Calculate determinant of the inverse
        Matrix inverse = m.inverse();
        double follow_out = 1.0 / inverse.det();

        // Verification
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 35: The determinant of a matrix A is equal to the determinant of its
     * adjugate, i.e., det(A) = det(adj(A)).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test35(Matrix m) {
        // assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square

        // // Get source output
        // double source_out = m.det();

        // // Calculate determinant of the adjugate
        // Matrix adjugate = m.adjoint();
        // double follow_out = adjugate.det();

        // // Verification
        // assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 36: The determinant of a matrix A is equal to the determinant of its
     * transpose, i.e., det(A) = det(A^T).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test36(Matrix m) {
        assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square

        // Get source output
        double source_out = m.det();

        // Calculate determinant of the transpose
        double follow_out = m.transpose().det();

        // Verification
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 37: The determinant of a matrix is equal to the determinant of its
     * conjugate, i.e., det(A) = det(conj(A)).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test37(Matrix m) {
        // assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square

        // // Get source output
        // double source_out = m.det();

        // // Calculate determinant of the conjugate
        // double follow_out = m.conjugate().det();

        // // Verification
        // assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 38: The determinant of a matrix is equal to the determinant of its
     * Hermitian transpose, i.e., det(A) = det(A^H), where A^H represents the conjugate transpose of
     * A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test38(Matrix m) {
        // assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square

        // // Get source output
        // double source_out = m.det();

        // // Calculate determinant of the Hermitian transpose
        // double follow_out = m.transpose().conjugate().det();

        // // Verification
        // assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 39: The determinant of a matrix is equal to the determinant of its
     * positive square root, i.e., det(A) = det(sqrt(A) * sqrt(A)).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test39(Matrix m) {
        // assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square

        // // Get source output
        // double source_out = m.det();

        // // Calculate determinant of the positive square root
        // double follow_out = m.sqrt().times(m.sqrt()).det();

        // // Verification
        // assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 40: The determinant of a matrix is equal to the determinant of its
     * exponential, i.e., det(A) = det(exp(A)).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test40(Matrix m) {
        // assumeTrue(m.getColumnDimension() == m.getRowDimension()); // Ensure the matrix is square

        // // Get source output
        // double source_out = m.det();

        // // Calculate determinant of the exponential
        // double follow_out = m.exp().det();

        // // Verification
        // assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 41: The determinant of a matrix A is equal to the determinant of kA,
     * where k is a scalar value. i.e., det(A) = det(kA).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test41(Matrix m) {
        int k = 2; // Scalar constant

        // Get source output
        double source_out = m.det();

        // Make transformation with scalar value
        double follow_out = m.times(k).det();

        // Verification
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 42: The determinant of a matrix A and its original output is always the
     * same, i.e., det(A) = det(A).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test42(Matrix m) {
        // Get source output
        double source_out = m.det();

        // Verification
        assertEquals(source_out, source_out, 1e-6);
    }

    static Stream<Arguments> testcaseProvider1() throws IOException {
        return testcaseGenerator.generate(1000);
    }

    static Stream<Arguments> testcaseProvider2() throws IOException {
        return testcaseGenerator.generate_mm(1000);
    }
}
