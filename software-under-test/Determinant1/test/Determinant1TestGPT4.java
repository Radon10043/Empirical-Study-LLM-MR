package test;

import static org.junit.Assume.assumeTrue;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.io.IOException;
import java.util.Arrays;
import java.util.Random;
import java.util.stream.Stream;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import flanagan.math.Matrix;

public class Determinant1TestGPT4 {
    /********** Helper Methods, implemented by Radon **********/
    /**
     * Get the adjoint matrix of m adj(m) = det(m) * m^-1
     *
     * @param m
     * @return
     */
    public Matrix adjugate(Matrix m) {
        return m.inverse().times(m.determinant());
    }

    /**
     * Metamorphic Relation 3: The determinant of a matrix should become negative if one row of the
     * matrix is multiplied by -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test3(Matrix m) {
        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        double[][] ref = follow_m.getArrayReference();
        int k = new Random().nextInt(m.getNumberOfRows()); // Select a row randomly
        for (int i = 0; i < follow_m.getNumberOfColumns(); i++)
            ref[k][i] *= -1;

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(-source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 4: Swapping any two rows of a matrix should change the sign of the
     * determinant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test4(Matrix m) {   // Fixed
        assumeTrue(m.getNumberOfRows() > 1);

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        double[][] ref = follow_m.getArrayReference();
        int numRows = follow_m.getNumberOfRows();
        int row1 = new Random().nextInt(numRows);
        int row2 = new Random().nextInt(numRows);
        while (row1 == row2) {
            row2 = new Random().nextInt(numRows); // Make sure we have two different rows
        }
        double[] tempRow = ref[row1];
        ref[row1] = ref[row2];
        ref[row2] = tempRow;

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(-source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 5: The determinant of a matrix should not change if a multiple of one
     * row is added to another row.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test5(Matrix m) {   // Fixed
        assumeTrue(m.getNumberOfRows() > 1);

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        double[][] ref = follow_m.getArrayReference();
        int numRows = follow_m.getNumberOfRows();
        int rowToAddTo = new Random().nextInt(numRows);
        int rowToAddFrom = new Random().nextInt(numRows);
        while (rowToAddTo == rowToAddFrom) {
            rowToAddFrom = new Random().nextInt(numRows); // Make sure we have two different rows
        }
        double multiple = new Random().nextDouble() * 10.0 - 5.0; // any random scalar
        for (int i = 0; i < follow_m.getNumberOfColumns(); i++)
            ref[rowToAddTo][i] += multiple * ref[rowToAddFrom][i];

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 6: The determinant of the matrix should be the product of the
     * determinants of two matrices if the original matrix is the block diagonal composition of the
     * two matrices.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test6(Matrix m1, Matrix m2) {
        /* Get source output */
        double res1 = m1.determinant();
        double res2 = m2.determinant();
        double source_res = res1 * res2;

        /* Construct follow-up input */
        int size1 = m1.getNumberOfRows();
        int size2 = m2.getNumberOfRows();
        Matrix follow_m = new Matrix(size1 + size2, size1 + size2);
        for (int i = 0; i < size1; i++) {
            for (int j = 0; j < size1; j++) {
                follow_m.getArrayReference()[i][j] = m1.getElement(i, j);
            }
        }
        for (int i = 0; i < size2; i++) {
            for (int j = 0; j < size2; j++) {
                follow_m.getArrayReference()[i + size1][j + size1] = m2.getElement(i, j);
            }
        }

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 7: If you multiply all elements of the matrix by a constant k, the
     * determinant should be equal to k raised to the nth power multiplied by the original
     * determinant, where n is the order of the square matrix (n x n).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test7(Matrix m) { // Fixed
        int constant = 2; // Can be any non-zero constant
        int order = m.getNumberOfRows(); // Assuming it's a square matrix
        double expectedFactor = Math.pow(constant, order);

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.times(constant);

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(expectedFactor * source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 8: If two rows or columns of a matrix are identical, the determinant
     * should be zero.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test8(Matrix m) {
        /* Make a copy of the matrix and alter it to have two identical rows */
        Matrix follow_m = m.copy();
        double[][] ref = follow_m.getArrayReference();
        int row1 = new Random().nextInt(m.getNumberOfRows());
        int row2 = (row1 + 1) % m.getNumberOfRows(); // Ensures a different row, given square matrix
        ref[row2] = ref[row1].clone();

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(0.0, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 9: The determinant of an identity matrix of any order should be 1.
     */
    @ParameterizedTest
    @MethodSource("sizeProvider")   // TODO
    public void test9(int size) {
        /* Generate an identity matrix of the given size */
        Matrix identityMatrix = Matrix.identityMatrix(size);

        /* Calculate the determinant */
        double det = identityMatrix.determinant();

        /* Verification */
        assertEquals(1.0, det, 1e-6);
    }

    /**
     * Metamorphic Relation 10: The determinant should remain unchanged if the entire matrix is
     * pre-multiplied or post-multiplied by an identity matrix of the same order.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test10(Matrix m) {
        /* Get source output */
        double source_res = m.determinant();

        /* Create an identity matrix of the same size as m */
        Matrix identityMatrix = Matrix.identityMatrix(m.getNumberOfRows());

        /* Pre-multiply and post-multiply m by the identity matrix */
        Matrix follow_m_pre = identityMatrix.times(m);
        Matrix follow_m_post = m.times(identityMatrix);

        /* Get follow-up outputs */
        double follow_res_pre = follow_m_pre.determinant();
        double follow_res_post = follow_m_post.determinant();

        /* Verification */
        assertEquals(source_res, follow_res_pre, 1e-6);
        assertEquals(source_res, follow_res_post, 1e-6);
    }

    /**
     * Metamorphic Relation 11: The determinant of a matrix with all elements of a column multiplied
     * by a constant k should be the original determinant multiplied by k.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test11(Matrix m) { // Fixed
        int constant = 5; // Can be any non-zero constant

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        double[][] ref = follow_m.getArrayCopy(); // Use getArrayCopy to avoid modifying original
                                                  // matrix
        int col = new Random().nextInt(m.getNumberOfColumns()); // Select a column randomly
        for (int i = 0; i < follow_m.getNumberOfRows(); i++) {
            ref[i][col] *= constant;
        }
        follow_m = new Matrix(ref);

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(constant * source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 12: The determinant should have the same absolute value but opposite
     * sign if any two columns of the matrix are swapped.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test12(Matrix m) {  // Fixed
        assumeTrue(m.getNumberOfColumns() > 1);

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        double[][] ref = follow_m.getArrayReference();
        int numCols = follow_m.getNumberOfColumns();
        int col1 = new Random().nextInt(numCols);
        int col2 = new Random().nextInt(numCols);
        while (col1 == col2) {
            col2 = new Random().nextInt(numCols); // Make sure we have two different columns
        }
        for (int i = 0; i < follow_m.getNumberOfRows(); i++) {
            double temp = ref[i][col1];
            ref[i][col1] = ref[i][col2];
            ref[i][col2] = temp;
        }

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(-source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 13: The determinant of the matrix should not change if we multiply a
     * column by a scalar and add it to another column.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test13(Matrix m) {  // Fixed
        assumeTrue(m.getNumberOfColumns() > 1);

        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        double[][] ref = follow_m.getArrayReference();
        int numCols = follow_m.getNumberOfColumns();
        int colToAddTo = new Random().nextInt(numCols);
        int colToAddFrom = new Random().nextInt(numCols);
        while (colToAddTo == colToAddFrom) {
            colToAddFrom = new Random().nextInt(numCols); // Ensure different columns
        }
        double scalar = new Random().nextDouble();
        for (int i = 0; i < follow_m.getNumberOfRows(); i++) {
            ref[i][colToAddTo] += scalar * ref[i][colToAddFrom];
        }

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 14: The determinant of the original matrix multiplied by the determinant
     * of any invertible matrix should be equal to the determinant of the product of the original
     * matrix and the invertible matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test14(Matrix m, Matrix invertibleMatrix) { // Fixed
        assumeTrue(m.getNumberOfRows() == invertibleMatrix.getNumberOfRows());

        /* Get source outputs */
        double source_res_m = m.determinant();
        double source_res_invertible = invertibleMatrix.determinant();

        /* Construct follow-up input */
        Matrix product_m = m.times(invertibleMatrix);

        /* Get follow-up output */
        double follow_res = product_m.determinant();

        /* Verification */
        assertEquals(source_res_m * source_res_invertible, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 15: The determinant of a singular matrix (non-invertible matrix) should
     * be zero. We can create a singular matrix by making one row (or column) a multiple of another.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test15(Matrix m) {
        /* Get source matrix copy */
        Matrix follow_m = m.copy();

        /*
         * Manipulate copy to be singular by setting one row to be a multiple of another
         */
        double[][] ref = follow_m.getArrayReference();
        int numRows = follow_m.getNumberOfRows();
        int row1 = new Random().nextInt(numRows);
        int row2 = (row1 + 1) % numRows; // Ensure a different row
        double multiple = 2; // Any non-zero constant would work
        for (int i = 0; i < follow_m.getNumberOfColumns(); i++) {
            ref[row2][i] = ref[row1][i] * multiple;
        }

        /* Calculate the determinant of the singular matrix */
        double follow_res = follow_m.determinant();

        /* Verify the determinant is zero */
        assertEquals(0.0, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 16: For any non-singular square matrix, the determinant of the inverse
     * of that matrix should be the reciprocal of the determinant of the matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test16(Matrix m) {  // Fixed
        /* Get source output */
        double source_res = m.determinant();

        assumeTrue(Math.abs(source_res) > 1e-6);

        /* Construct follow-up input */
        Matrix inverse_m = m.inverse();

        /* Get follow-up output */
        double follow_res = inverse_m.determinant();

        /* Verification */
        assertEquals(1 / source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 17: The determinant of a matrix should be zero if all elements of a row
     * or column are zero.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test17(Matrix m) {
        /* Get source matrix copy */
        Matrix follow_m = m.copy();

        /* Manipulate copy: Set all elements of a random row to zero */
        double[][] ref = follow_m.getArrayReference();
        int numRows = follow_m.getNumberOfRows();
        int zeroRow = new Random().nextInt(numRows);
        Arrays.fill(ref[zeroRow], 0.0);

        /* Calculate the determinant of the matrix with the zeroed row */
        double follow_res = follow_m.determinant();

        /* Verify the determinant is zero */
        assertEquals(0.0, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 18: The determinant after cyclically permuting rows should be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test18(Matrix m) {
        /* Get source output */
        double source_res = m.determinant();

        /* Construct follow-up input with rows cyclically permuted */
        Matrix follow_m = m.copy();
        double[][] ref = follow_m.getArrayReference();
        double[] tempRow = ref[0];
        for (int i = 0; i < ref.length - 1; i++) {
            ref[i] = ref[i + 1];
        }
        ref[ref.length - 1] = tempRow;

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    /**
     * Metamorphic Relation 19: If you scale a matrix by a non-zero scalar, the determinant is
     * scaled by the scalar to the power of the size of the matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test19(Matrix m) { // Fixed
        double scalar = 2; // Scalar to scale the matrix with

        /* Get source determinant */
        double source_det = m.determinant();

        /* Scale the matrix */
        Matrix scaledMatrix = m.times(scalar);

        /* Determine the determinant of the scaled matrix */
        double scaled_det = scaledMatrix.determinant();

        /* Calculation of expected determinant */
        double expected_det = source_det * Math.pow(scalar, m.getNumberOfRows());

        /* Verification */
        assertEquals(expected_det, scaled_det, 1e-6);
    }

    /**
     * Metamorphic Relation 20: The determinant of a scaled matrix, where the scale is applied to a
     * single row, should match the original determinant scaled by the same factor.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test20(Matrix m) {
        double scale = 3.5; // Scale factor for the row

        /* Get original determinant */
        double originalDet = m.determinant();

        /* Scale a random row */
        Matrix scaledMatrix = m.copy();
        double[][] ref = scaledMatrix.getArrayReference();
        int rowToScale = new Random().nextInt(m.getNumberOfRows());
        for (int j = 0; j < m.getNumberOfColumns(); j++) {
            ref[rowToScale][j] *= scale;
        }

        /* Calculate the determinant of the scaled matrix */
        double scaledDet = scaledMatrix.determinant();

        /* Verify that the scaled determinant matches expectation */
        assertEquals(scale * originalDet, scaledDet, 1e-6);
    }

    /**
     * Metamorphic Relation 21: The determinant of a matrix obtained by adding a scaled row to
     * another should be identical to the determinant of the original matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test21(Matrix m) {  // Fixed
        assumeTrue(m.getNumberOfRows() > 1);

        double scale = 2.0; // Scaling factor for the row addition

        /* Get original determinant */
        double originalDet = m.determinant();

        /* Add scaled row to another */
        Matrix modifiedMatrix = m.copy();
        double[][] ref = modifiedMatrix.getArrayReference();
        int numRows = m.getNumberOfRows();
        int sourceRow = new Random().nextInt(numRows);
        int targetRow = new Random().nextInt(numRows);
        // Ensure we are not adding the row to itself
        while (sourceRow == targetRow) {
            targetRow = new Random().nextInt(numRows);
        }
        for (int j = 0; j < m.getNumberOfColumns(); j++) {
            ref[targetRow][j] += scale * ref[sourceRow][j];
        }

        /* Calculate the determinant of the modified matrix */
        double modifiedDet = modifiedMatrix.determinant();

        /* Verify that the determinant remains unchanged */
        assertEquals(originalDet, modifiedDet, 1e-6);
    }

    /**
     * Metamorphic Relation 22: Multiplying a matrix by its adjugate (adjoint matrix) should result
     * in a diagonal matrix where the diagonal elements are the determinant of the original matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test22(Matrix m) {  // Fixed
        /* Calculate original determinant */
        double originalDet = m.determinant();

        /* Calculate adjugate matrix */
        Matrix adjugateMatrix = adjugate(m);

        /* Multiply original matrix by its adjugate */
        Matrix productMatrix = m.times(adjugateMatrix);

        /*
         * Verify that the product is a diagonal matrix where each diagonal element is the original
         * determinant
         */
        for (int i = 0; i < productMatrix.getNumberOfRows(); i++) {
            for (int j = 0; j < productMatrix.getNumberOfColumns(); j++) {
                if (i == j) {
                    assertEquals(originalDet, productMatrix.getElement(i, j), 1e-6);
                } else {
                    assertEquals(0.0, productMatrix.getElement(i, j), 1e-6);
                }
            }
        }
    }

    /**
     * Metamorphic Relation 23: Doubling a single element in a matrix should not double the
     * determinant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test23(Matrix m) {
        /* Get original determinant */
        double originalDet = m.determinant();

        /* Double a random element in the matrix */
        Matrix modifiedMatrix = m.copy();
        double[][] ref = modifiedMatrix.getArrayReference();
        int row = new Random().nextInt(m.getNumberOfRows());
        int col = new Random().nextInt(m.getNumberOfColumns());
        ref[row][col] *= 2;

        /* Calculate the determinant of the modified matrix */
        double modifiedDet = modifiedMatrix.determinant();

        /*
         * The modified determinant should not be simply double the original determinant
         */
        assertNotEquals(2 * originalDet, modifiedDet);
    }

    /**
     * Metamorphic Relation 24: The determinant of a matrix should be the product of its
     * eigenvalues.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test24(Matrix m) {
        // /* Calculate original determinant */
        // double originalDet = m.determinant();

        // /* Calculate eigenvalues */
        // EigenvalueDecomposition eigenDecomp = m.eigenvalueDecomposition();
        // Complex[] eigenvalues = eigenDecomp.getEigenvalues();
        // double productOfEigenvalues = Arrays.stream(eigenvalues).filter(Complex::isReal)
        //         .mapToDouble(Complex::getReal).reduce(1.0, (a, b) -> a * b);

        // /*
        //  * Verify that the determinant is close to the product of its real eigenvalues
        //  */
        // assertEquals(originalDet, productOfEigenvalues, 1e-6);
    }

    /**
     * Metamorphic Relation 25: The determinant of a matrix should be zero if the matrix is not full
     * rank.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test25(Matrix m) {
        /* Make the matrix rank deficient */
        Matrix modifiedMatrix = m.copy();
        double[][] ref = modifiedMatrix.getArrayReference();
        if (m.getNumberOfRows() > 1) {
            System.arraycopy(ref[0], 0, ref[1], 0, ref[0].length); // Copy first row to second row
        }

        /* Calculate the determinant of the rank deficient matrix */
        double modifiedDet = modifiedMatrix.determinant();

        /* Verify that the determinant is zero */
        assertEquals(0.0, modifiedDet, 1e-6);
    }

    /**
     * Metamorphic Relation 26: The determinant should remain unchanged if the matrix is multiplied
     * by its own inverse.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test26(Matrix m) {  // Fixed
        /* Calculate original determinant */
        double originalDet = m.determinant();

        assumeTrue(Math.abs(originalDet) > 1e-6);

        /* Multiply the matrix by its inverse */
        Matrix inverseMatrix = m.inverse();
        Matrix productMatrix = m.times(inverseMatrix);

        /* Verify that the product matrix has a determinant equal to 1 */
        double productDet = productMatrix.determinant();
        assertEquals(1.0, productDet, 1e-6);

        /*
         * The original determinant should remain the same when the matrix is multiplied by its
         * inverse
         */
        assertEquals(originalDet, m.determinant(), 1e-6);
    }

    /**
     * Metamorphic Relation 27: The determinant of a matrix where one row is scaled by a factor and
     * another row is later subtracted by the scaled row should remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test27(Matrix m) {
        /* Get original determinant */
        double originalDet = m.determinant();

        /* Make modified matrix */
        Matrix modifiedMatrix = m.copy();
        double[][] ref = modifiedMatrix.getArrayReference();
        int numRows = m.getNumberOfRows();
        int scalingRow = new Random().nextInt(numRows); // Row to be scaled
        int affectedRow = new Random().nextInt(numRows); // Row to be subtracted from
        double scalingFactor = 3; // Factor to scale row
        double[] scaledRow = new double[ref[scalingRow].length];

        // Scale the selected row by the scaling factor
        for (int i = 0; i < scaledRow.length; i++) {
            scaledRow[i] = ref[scalingRow][i] * scalingFactor;
        }

        // Subtract the scaled row from another row
        for (int i = 0; i < ref[affectedRow].length; i++) {
            ref[affectedRow][i] -= scaledRow[i];
        }

        /* Calculate determinant of modified matrix */
        double modifiedDet = modifiedMatrix.determinant();

        /* Verify determinant is unchanged */
        assertEquals(originalDet, modifiedDet, 1e-6);
    }

    /**
     * Metamorphic Relation 28: The determinant of a matrix that has a row replaced with the sum of
     * that row and another row multiplied by a scalar should remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test28(Matrix m) {
        /* Get original determinant */
        double originalDet = m.determinant();

        /* Make modified matrix */
        Matrix modifiedMatrix = m.copy();
        double[][] ref = modifiedMatrix.getArrayReference();
        int numRows = m.getNumberOfRows();
        int baseRow = new Random().nextInt(numRows); // Row that will be changed
        int addingRow = new Random().nextInt(numRows); // Row that will be added after scaling
        double scalarMultiplier = 5; // Scalar multiplier

        for (int i = 0; i < ref[baseRow].length; i++) {
            ref[baseRow][i] += scalarMultiplier * ref[addingRow][i];
        }

        /* Calculate determinant of modified matrix */
        double modifiedDet = modifiedMatrix.determinant();

        /* Verify determinant is unchanged */
        assertEquals(originalDet, modifiedDet, 1e-6);
    }

    /**
     * Metamorphic Relation 29: The determinant of a matrix after interchanging two rows and then
     * interchanging them back should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test29(Matrix m) {  // Fixed
        assumeTrue(m.getNumberOfRows() > 1);

        /* Get original determinant */
        double originalDet = m.determinant();

        /* Interchange two rows */
        Matrix modifiedMatrix = m.copy();
        double[][] ref = modifiedMatrix.getArrayReference();
        int numRows = m.getNumberOfRows();
        int row1 = new Random().nextInt(numRows);
        int row2;
        do {
            row2 = new Random().nextInt(numRows);
        } while (row1 == row2);

        double[] tempRow = ref[row1];
        ref[row1] = ref[row2];
        ref[row2] = tempRow;

        /* Interchange the rows back to original */
        tempRow = ref[row2];
        ref[row2] = ref[row1];
        ref[row1] = tempRow;

        /* Calculate determinant after row interchange */
        double modifiedDet = modifiedMatrix.determinant();

        /* Verify determinant is unchanged */
        assertEquals(originalDet, modifiedDet, 1e-6);
    }

    /**
     * Metamorphic Relation 30: The determinant of a matrix after replacing a row with the sum of
     * itself and another row, followed by subtracting the original values of the second row should
     * remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test30(Matrix m) {
        assumeTrue(m.getNumberOfRows() > 1);

        /* Get original determinant */
        double originalDet = m.determinant();

        /* Modify matrix */
        Matrix modifiedMatrix = m.copy();
        double[][] ref = modifiedMatrix.getArrayReference();
        int numRows = m.getNumberOfRows();
        int row1 = new Random().nextInt(numRows);
        int row2 = new Random().nextInt(numRows);
        while (row1 == row2) {
            row2 = new Random().nextInt(numRows); // Make sure we have two different rows
        }

        // Save the original values of the second row
        double[] originalRow2Values = new double[ref[row2].length];
        System.arraycopy(ref[row2], 0, originalRow2Values, 0, ref[row2].length);

        // Add the values of the second row to the first row
        for (int i = 0; i < ref[row1].length; i++) {
            ref[row1][i] += ref[row2][i];
        }

        // Subtract the original values of the second row from the first row
        for (int i = 0; i < ref[row1].length; i++) {
            ref[row1][i] -= originalRow2Values[i];
        }

        /* Calculate determinant of modified matrix */
        double modifiedDet = modifiedMatrix.determinant();

        /* Verify determinant is unchanged */
        assertEquals(originalDet, modifiedDet, 1e-6);
    }

    /**
     * Metamorphic Relation 31: The determinant of a matrix remains unchanged when any row (or
     * column) is multiplied by a scalar and then all the elements of that row (or column) are added
     * to the corresponding elements of any other row (or column).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test31(Matrix m) {  // Fixed
        assumeTrue(m.getNumberOfRows() > 1);

        /* Get original determinant */
        double originalDet = m.determinant();

        /* Make modified matrix by adding a scalar multiple of a row to another row */
        Matrix modifiedMatrix = m.copy();
        double[][] ref = modifiedMatrix.getArrayReference();
        int numRows = m.getNumberOfRows();
        int sourceRow = new Random().nextInt(numRows); // The row to be multiplied
        int targetRow = new Random().nextInt(numRows); // The row to add to
        while (targetRow == sourceRow) { // Ensure it's not the same row
            targetRow = new Random().nextInt(numRows);
        }
        double scalar = 2.0; // The scalar multiplier
        for (int col = 0; col < m.getNumberOfColumns(); col++) {
            ref[targetRow][col] += scalar * ref[sourceRow][col];
        }

        /* Calculate determinant of modified matrix */
        double modifiedDet = modifiedMatrix.determinant();

        /* Verify determinant is unchanged */
        assertEquals(originalDet, modifiedDet, 1e-6);
    }

    /**
     * Metamorphic Relation 32: If a matrix is upper or lower triangular, the determinant should be
     * the product of its diagonal elements.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test32(Matrix triMatrix) {
        /* Get original determinant */
        double originalDet = triMatrix.determinant();

        /* Calculate the product of diagonal elements for a triangular matrix */
        double productOfDiagonals = 1.0;
        for (int i = 0; i < triMatrix.getNumberOfRows(); i++) {
            productOfDiagonals *= triMatrix.getElement(i, i);
        }

        /* Verify determinant is the product of diagonal elements */
        assertEquals(originalDet, productOfDiagonals, 1e-6);
    }

    /**
     * Metamorphic Relation 33: Multiplying all elements of a matrix by -1 should result in a
     * determinant that is the negation of the original determinant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test33(Matrix m) {
        /* Get original determinant */
        double originalDet = m.determinant();

        /* Make modified matrix by multiplying all elements by -1 */
        Matrix modifiedMatrix = m.copy();
        double[][] ref = modifiedMatrix.getArrayReference();
        for (int row = 0; row < m.getNumberOfRows(); row++) {
            for (int col = 0; col < m.getNumberOfColumns(); col++) {
                ref[row][col] = -ref[row][col];
            }
        }

        /* Calculate determinant of modified matrix */
        double modifiedDet = modifiedMatrix.determinant();

        /* Verify determinant is negation of original determinant */
        assertEquals(-originalDet, modifiedDet, 1e-6);
    }

    /**
     * Metamorphic Relation 34: Multiplying two matrices and taking the determinant should give the
     * same result as taking the determinants of each and multiplying them together.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test34(Matrix m1, Matrix m2) {
        /* Calculate determinants of individual matrices */
        double detM1 = m1.determinant();
        double detM2 = m2.determinant();

        /* Multiply matrices */
        Matrix productMatrix = m1.times(m2);

        /* Calculate determinant of product matrix */
        double detProductMatrix = productMatrix.determinant();

        /* Verify product of individual determinants equals determinant of product */
        assertEquals(detM1 * detM2, detProductMatrix, 1e-6);
    }

    /**
     * Metamorphic Relation 35: The determinant of a matrix remains unchanged if all rows and
     * columns are permuted in the same way.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test35(Matrix m) {
        // /* Get original determinant */
        // double originalDet = m.determinant();

        // /* Permute rows and columns of the matrix in the same way */
        // Matrix permutedMatrix = m.copy();
        // int[] permutation = generatePermutation(m.getNumberOfRows()); // assume this method
        //                                                               // generates a random
        //                                                               // permutation array
        // permuteMatrixRowsAndColumns(permutedMatrix, permutation); // assume this method permutes
        //                                                           // matrix rows and columns
        //                                                           // given permutation array

        // /* Calculate determinant of permuted matrix */
        // double permutedDet = permutedMatrix.determinant();

        // /* Verify determinant is unchanged after permutation of rows and columns */
        // assertEquals(originalDet, permutedDet, 1e-6);
    }

    /**
     * Metamorphic Relation 36: The determinant of the product of a matrix and its transpose is
     * non-negative.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test36(Matrix m) {
        /* Calculate matrix transpose */
        Matrix transpose = m.transpose();

        /* Calculate the product of the matrix with its transpose */
        Matrix product = m.times(transpose);

        /* Calculate determinant of the product matrix */
        double detProduct = product.determinant();

        /* Verify that determinant of the product is non-negative */
        assertTrue(detProduct >= 0);
    }

    /**
     * Metamorphic Relation 37: The determinant of a block matrix, composed of four sub-matrices (A,
     * B, C, D), where B and C are zero matrices, should be the determinant of A times the
     * determinant of D.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider3")
    public void test37(Matrix A, Matrix B, Matrix C, Matrix D) {    // Fixed
        /* Calculate determinants of sub-matrices A and D */
        double detA = A.determinant();
        double detD = D.determinant();

        /* Construct a block matrix with A, B, C, D */
        int size = A.getNumberOfRows();

        B = new Matrix(size, size); // Ensure B is a zero matrix
        C = new Matrix(size, size); // Ensure C is a zero matrix

        Matrix blockMatrix = new Matrix(size * 2, size * 2);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                blockMatrix.setElement(i, j, A.getElement(i, j));
                blockMatrix.setElement(i, j + size, B.getElement(i, j));
                blockMatrix.setElement(i + size, j, C.getElement(i, j));
                blockMatrix.setElement(i + size, j + size, D.getElement(i, j));
            }
        }

        /* Calculate determinant of block matrix */
        double detBlockMatrix = blockMatrix.determinant();

        /*
         * Verify the determinant of the block matrix is the product of the determinants of A and D
         */
        assertEquals(detA * detD, detBlockMatrix, 1e-6);
    }

    /**
     * Metamorphic Relation 38: The determinant of a diagonal matrix should be the product of its
     * diagonal entries.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test38(Matrix diagonalMatrix) {
        /* Compute the product of the diagonal entries */
        double prodDiagonalEntries = 1.0;
        for (int i = 0; i < diagonalMatrix.getNumberOfRows(); i++) {
            prodDiagonalEntries *= diagonalMatrix.getElement(i, i);
        }

        /* Calculate determinant of diagonal matrix */
        double detDiagonalMatrix = diagonalMatrix.determinant();

        /* Verify that the determinant is the product of its diagonal entries */
        assertEquals(prodDiagonalEntries, detDiagonalMatrix, 1e-6);
    }

    /**
     * Metamorphic Relation 39: The determinant of a matrix with a row (or column) replaced by a
     * linear combination of the other rows (or columns) is the same as the original matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test39(Matrix m) {
        /* Get original determinant */
        double originalDet = m.determinant();

        /* Replace a row of m with a linear combination of other rows */
        Matrix newMatrix = m.copy();
        double[][] ref = newMatrix.getArrayReference();
        int numRows = newMatrix.getNumberOfRows();
        int targetRow = new Random().nextInt(numRows);

        // Reset the target row to 0
        Arrays.fill(ref[targetRow], 0.0);

        // Add a linear combination of other rows to the target row
        for (int i = 0; i < numRows; i++) {
            if (i == targetRow)
                continue;
            double coeff = new Random().nextDouble() - 0.5; // Coefficient for the linear
                                                            // combination, randomly chosen
            for (int j = 0; j < newMatrix.getNumberOfColumns(); j++) {
                ref[targetRow][j] += coeff * m.getElement(i, j);
            }
        }

        /* Calculate the determinant of the new matrix */
        double newDet = newMatrix.determinant();

        /* Verify that the determinant has not changed */
        assertEquals(originalDet, newDet, 1e-6);
    }

    /**
     * Metamorphic Relation 40: The determinant of a matrix multiplied (element-wise) by the
     * determinant of the identity matrix should be the same as the original matrix determinant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test40(Matrix m) {  // Fixed
        /* Get original determinant */
        double originalDet = m.determinant();

        /* Create an identity matrix of the same order and get its determinant */
        Matrix identity = Matrix.identityMatrix(m.getNumberOfRows());
        double identityDet = identity.determinant(); // Should be 1 for an identity matrix, but
                                                     // included for
                                                     // completeness

        /* Multiply matrix m (element-wise) by the determinant of the identity matrix */
        Matrix scaledMatrix = m.times(identityDet);

        /* Calculate determinant of the scaled matrix */
        double scaledDet = scaledMatrix.determinant();

        /* Verify that the determinant is the same as the original */
        assertEquals(originalDet, scaledDet, 1e-6);
    }

    /**
     * Metamorphic Relation 41: The determinant of a matrix where one column is multiplied by a
     * non-zero constant and another is multiplied by the reciprocal of that constant, should not
     * change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test41(Matrix m) {  // Fixed
        assumeTrue(m.getNumberOfColumns() > 1);

        /* Get original determinant */
        double originalDet = m.determinant();

        /* Choose a non-zero scalar and its reciprocal */
        double scalar = 2.0;
        double reciprocal = 1.0 / scalar;

        /* Multiply one column by the scalar and another by the reciprocal */
        Matrix newMatrix = m.copy();
        double[][] ref = newMatrix.getArrayReference();
        int col1 = new Random().nextInt(m.getNumberOfColumns());
        int col2;
        do {
            col2 = new Random().nextInt(m.getNumberOfColumns());
        } while (col1 == col2);

        for (int i = 0; i < m.getNumberOfRows(); i++) {
            ref[i][col1] *= scalar;
            ref[i][col2] *= reciprocal;
        }

        /* Calculate the determinant of the new matrix */
        double newDet = newMatrix.determinant();

        /* Verify that the determinant has not changed */
        assertEquals(originalDet, newDet, 1e-6);
    }

    /**
     * Metamorphic Relation 42: The determinant should remain unaffected if an entire row (or
     * column) of a matrix is set to zero and then restored to its original state.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test42(Matrix m) {
        /* Get original determinant */
        double originalDet = m.determinant();

        /* Zero out a row and then restore it */
        Matrix modifiedMatrix = m.copy();
        double[][] ref = modifiedMatrix.getArrayReference();
        int rowToModify = new Random().nextInt(m.getNumberOfRows());
        double[] originalRow = Arrays.copyOf(ref[rowToModify], ref[rowToModify].length);

        // Zero out the row
        Arrays.fill(ref[rowToModify], 0.0);

        // Restore the original row
        ref[rowToModify] = originalRow;

        /* Calculate the determinant of the modified matrix */
        double modifiedDet = modifiedMatrix.determinant();

        /* Verify that the determinant has not changed */
        assertEquals(originalDet, modifiedDet, 1e-6);
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
}
