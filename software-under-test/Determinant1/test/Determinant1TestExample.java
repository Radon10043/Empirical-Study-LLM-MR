package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import java.util.stream.Stream;
import java.io.IOException;
import java.security.SecureRandom;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import flanagan.math.Matrix;

public class Determinant1TestExample {
    SecureRandom rand = new SecureRandom();

    /**
     * Metamorphic Relation 1: The determinant of the matrix is equal to the determinant of the
     * transposed matrix, i.e., det(A)=det(A^T)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(Matrix m) {
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
     * Metamorphic Relation 2: The determinant of the matrix multiply a constant equals to the
     * determinant of the matrix which elements in a row multiply the same constant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(Matrix m) {
        int constant = 3;

        /* Get source output */
        double source_res = constant * m.determinant();

        /* Construct follow-up input */
        Matrix follow_m = m.copy();
        double[][] ref = follow_m.getArrayReference();
        int k = rand.nextInt(m.getNumberOfRows()); // Select a row randomly
        for (int i = 0; i < follow_m.getNumberOfColumns(); i++)
            ref[k][i] *= constant;

        /* Get follow-up output */
        double follow_res = follow_m.determinant();

        /* Verification */
        assertEquals(source_res, follow_res, 1e-6);
    }

    static Stream<Arguments> testcaseProvider() throws IOException {
        return testcaseGenerator.generate_m(1000);
    }
}
