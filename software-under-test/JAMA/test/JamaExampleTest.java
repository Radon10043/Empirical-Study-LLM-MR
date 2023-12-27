package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import java.util.stream.Stream;
import java.util.Random;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import Jama.Matrix;

public class JamaExampleTest {
    private Random rand = new Random(System.currentTimeMillis());

    /**
     * Metamorphic Relation 1: The determinant of the matrix is equal to the determinant of the
     * transposed matrix, i.e., det(A)=det(A^T)
     *
     * @param m Source input
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(Matrix m) {
        /* Get source output */
        double source_out = m.det();

        /* Construct follow-up input */
        Matrix follow_m = m.transpose();

        /* Get follow-up output */
        double follow_out = follow_m.det();

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 2: The determinant of the matrix multiply a constant equals to the
     * determinant of the matrix which elements in a row multiply the same constant.
     *
     * @param m
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(Matrix m) {
        int constant = 3;

        /* Get source output */
        double source_out = constant * m.det();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        int k = rand.nextInt(m.getRowDimension()); // Select a row randomly
        for (int i = 0; i < follow_m.getRowDimension(); i++)
            follow_m.set(k, i, follow_m.get(k, i) * constant);

        /* Get follow-up output */
        double follow_out = follow_m.det();

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    static Stream<Arguments> testcaseProvider() {
        Matrix m1 = new Matrix(new double[][] {{1, 2}, {3, 4}});
        Matrix m2 = new Matrix(new double[][] {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        return Stream.of(Arguments.of(m1), Arguments.of(m2));
    }
}
