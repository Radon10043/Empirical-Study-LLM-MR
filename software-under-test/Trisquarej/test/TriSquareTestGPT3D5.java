package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;
import static src.TriSquareJ.triangle_square;

import java.io.IOException;
import java.util.stream.Stream;
import org.apache.commons.lang3.tuple.Pair;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

// Fixed: "TriangleUtil." -> ""
public class TriSquareTestGPT3D5 {
    /**
     * Metamorphic Relation 1: If a', b', c' is the second triangle where a'=a+k, b'=b+k, c'=c+k for any k > 0,
     * then the area of second triangle should be equal to the area of the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int k = 1;
        int follow_a = a + k, follow_b = b + k, follow_c = c + k;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(source_out.getValue(), follow_out.getValue());
    }

    /**
     * Metamorphic Relation 2: If a', b', c' is the second triangle where a'=ka, b'=kb, c'=kc for k > 1,
     * then the area of the second triangle should be k^2 times the area of the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(int a, int b, int c) {
        assumeTrue(a > 0 && b > 0 && c > 0);

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int k = 2;
        int follow_a = a * k, follow_b = b * k, follow_c = c * k;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        double source_area = source_out.getValue();
        assertEquals(source_area * k * k, follow_out.getValue(), 1e-6); // Fixed
    }

    /**
     * Metamorphic Relation 3: If a', b', c' is the second triangle where a'=b and b'=a,
     * then the area of the second triangle should be equal to the area of the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(int a, int b, int c) {
        assumeTrue(a > 0 && b > 0 && c > 0);

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = b, follow_b = a, follow_c = c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(source_out.getValue(), follow_out.getValue());
    }

    /**
     * Metamorphic Relation 4: If a', b', c' is the second triangle where a'=b and b'=c,
     * then the area of the second triangle should be equal to the area of the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(int a, int b, int c) {
        assumeTrue(a > 0 && b > 0 && c > 0);

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = b, follow_b = c, follow_c = a;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(source_out.getValue(), follow_out.getValue());
    }

    /**
     * Metamorphic Relation 5: If a', b', c' is the second triangle where a', b', c' are in arithmetic progression
     * with common difference d, then the area of the second triangle should be equal to the area of the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int d = 2;
        int follow_a = a, follow_b = a + d, follow_c = a + 2 * d;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(source_out.getValue(), follow_out.getValue());
    }

    /**
     * Metamorphic Relation 6: If a', b', c' is the second triangle where a', b', c' are in geometric progression
     * with common ratio r, then the area of the second triangle should be r^2 times the area of the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(int a, int b, int c) {
        assumeTrue(a > 0 && b > 0 && c > 0);

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int r = 2;
        int follow_a = a, follow_b = a * r, follow_c = a * r * r;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        double source_area = source_out.getValue();
        assertEquals(source_area * r * r, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 7: If a', b', c' is the second triangle where a', b', c' are in harmonic progression
     * with common difference d, then the area of the second triangle should be k times the area of the first triangle,
     * where k is a constant value determined by the progression.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(int a, int b, int c) {
        // assumeTrue(a > 0 && b > 0 && c > 0);

        // /* Get source output */
        // Pair<Integer, Double> source_out = triangle_square(a, b, c);

        // /* Construct follow-up input */
        // int d = 2;
        // int follow_a = a, follow_b = 1 / (1.0 / a + 1.0 / d), follow_c = 1 / (1.0 / a + 1.0 / (2 * d));

        // /* Get follow-up output */
        // Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        // /* Verification */
        // double source_area = source_out.getValue();
        // assertEquals(source_area * k, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 8: If a', b', c' is the second triangle where a'=b, b'=c, c'=a, then the area of the second
     * triangle should be equal to the area of the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(int a, int b, int c) {
        assumeTrue(a > 0 && b > 0 && c > 0);

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = b, follow_b = c, follow_c = a;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(source_out.getValue(), follow_out.getValue());
    }

    /**
     * Metamorphic Relation 9: If a', b', c' is the second triangle where a'=b'=c', then the area of the second
     * triangle should be greater than the area of the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(int a, int b, int c) {
        assumeTrue(a > 0 && b > 0 && c > 0);

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = b, follow_b = b, follow_c = b;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertTrue(follow_out.getValue() > source_out.getValue());
    }

    /**
     * Metamorphic Relation 10: If a', b', c' is the second triangle where a'<b'+c', then the type of the second
     * triangle should be 0 (not a triangle) and the area should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = a, follow_b = b, follow_c = b + c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, follow_out.getKey().intValue());
        assertEquals(0.0, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 11: If a', b', c' is the second triangle where a'=b=c, then the type of the second
     * triangle should be 3 (equilateral triangle) and the area should be equal to the area of the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(int a, int b, int c) {
        assumeTrue(a > 0 && b > 0 && c > 0);

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = b, follow_b = b, follow_c = b;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(3, follow_out.getKey().intValue());
        assertEquals(source_out.getValue(), follow_out.getValue());
    }

    /**
     * Metamorphic Relation 12: If a', b', c' is the second triangle where a'=b, and a'+b'<c', then the type of the
     * second triangle should be 0 (not a triangle) and the area should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = b, follow_b = b, follow_c = b + 1;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, follow_out.getKey().intValue());
        assertEquals(0.0, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 13: If a', b', c' is the second triangle where a'=b, and a'>c', then the type of the
     * second triangle should be 0 (not a triangle) and the area should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = b, follow_b = b, follow_c = b - 1;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, follow_out.getKey().intValue());
        assertEquals(0.0, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 14: If a', b', c' is the second triangle where a'=c, b'=c, a'=b', then the type of the
     * second triangle should be 3 (equilateral triangle) and the area should be equal to the area of the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(int a, int b, int c) {
        assumeTrue(a > 0 && b > 0 && c > 0);

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = c, follow_b = c, follow_c = c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(3, follow_out.getKey().intValue());
        assertEquals(source_out.getValue(), follow_out.getValue());
    }

    /**
     * Metamorphic Relation 15: If a', b', c' is the second triangle where a'=b+c, then the type of the second
     * triangle should be 0 (not a triangle) and the area should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = b + c, follow_b = b, follow_c = c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, follow_out.getKey().intValue());
        assertEquals(0.0, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 16: If a', b', c' is the second triangle where a'=b+c, then the type of the second
     * triangle should be 0 (not a triangle) and the area should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = a, follow_b = a + c, follow_c = c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, follow_out.getKey().intValue());
        assertEquals(0.0, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 17: If a', b', c' is the second triangle where a'=b, and b'=a+c, then the type of the second
     * triangle should be 0 (not a triangle) and the area should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = b, follow_b = a + c, follow_c = c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, follow_out.getKey().intValue());
        assertEquals(0.0, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 18: If a', b', c' is the second triangle where a'=c, and a'=b+c, then the type of the second
     * triangle should be 0 (not a triangle) and the area should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = c, follow_b = b + c, follow_c = c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, follow_out.getKey().intValue());
        assertEquals(0.0, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 19: If a', b', c' is the second triangle where a'=b, and b'=a, then the type of the second
     * triangle should be 0 (not a triangle) and the area should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = b, follow_b = a, follow_c = c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, follow_out.getKey().intValue());
        assertEquals(0.0, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 20: If a', b', c' is the second triangle where a'=a, and b'=c, then the type of the second
     * triangle should be isosceles (2) if a'=c, and the area should be equal to the area of the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(int a, int b, int c) {
        assumeTrue(a > 0 && b > 0 && c > 0);

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = a, follow_b = c, follow_c = c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(2, follow_out.getKey().intValue());
        assertEquals(source_out.getValue(), follow_out.getValue());
    }

    /**
     * Metamorphic Relation 21: If a', b', c' is the second triangle where a'=a, and b'=b, then the type of the second
     * triangle should depend on the inequality of sides, and the area should be equal to the area of the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(int a, int b, int c) {
        assumeTrue(a > 0 && b > 0 && c > 0);

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = a, follow_b = b, follow_c = b + 1;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, follow_out.getKey().intValue());
        assertEquals(0.0, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 22: If a', b', c' is the second triangle where a', b', c' are all equal to 1, then the type of
     * the second triangle should be 0 (not a triangle) and the area should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 1, follow_b = 1, follow_c = 1;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, follow_out.getKey().intValue());
        assertEquals(0.0, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 23: If a', b', c' is the second triangle where a'=b, and c'=a+b, then the type of the second
     * triangle should be 0 (not a triangle) and the area should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = b, follow_b = b, follow_c = a + b;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, follow_out.getKey().intValue());
        assertEquals(0.0, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 24: If a', b', c' is the second triangle where a'=b, and a'>=c', then the type of the second
     * triangle should be 0 (not a triangle) and the area should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = b, follow_b = b, follow_c = b-1;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, follow_out.getKey().intValue());
        assertEquals(0.0, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 25: If a', b', c' is the second triangle where a'=b, b'=c and c'=a, then the type of the second
     * triangle should be 3 (equilateral triangle) and the area should be equal to the area of the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(int a, int b, int c) {
        assumeTrue(a > 0 && b > 0 && c > 0);

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = b, follow_b = c, follow_c = a;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(3, follow_out.getKey().intValue());
        assertEquals(source_out.getValue(), follow_out.getValue());
    }

    /**
     * Metamorphic Relation 26: If a', b', c' is the second triangle where a' = 0, b' = c', and c'=a', then the type of the second
     * triangle should be 0 (not a triangle) and the area should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 0, follow_b = c, follow_c = 0;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, follow_out.getKey().intValue());
        assertEquals(0.0, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 27: If a', b', c' is the second triangle where a' = 3a, b' = 3b, c' = 3c, then the type of the second
     * triangle should remain the same as the first triangle, but the area should be 9 times the area of the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(int a, int b, int c) {
        assumeTrue(a > 0 && b > 0 && c > 0 && a + b > c && a + c > b && b + c > a);

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 3 * a, follow_b = 3 * b, follow_c = 3 * c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = follow_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertEquals(source_area * 9, follow_area, 1e-4);   // Fixed
    }

    /**
     * Metamorphic Relation 28: If a', b', c' is the second triangle where a'=b=k, and c' is (1+k) times a',
     * then the type of the second triangle should always be isosceles and the area should be equal to the area of the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(int a, int b, int c) {
        assumeTrue(a > 0 && b > 0 && c > 0);

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int k = 3;
        int follow_a = k, follow_b = k, follow_c = (1 + k) * k;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(2, follow_out.getKey().intValue());
        assertEquals(source_out.getValue(), follow_out.getValue());
    }

    /**
     * Metamorphic Relation 29: If a', b', c' is the second triangle where a'=b=k, and c' is (1-k) times a',
     * then the type of the second triangle should always be not a triangle and the area should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(int a, int b, int c) {
        assumeTrue(a > 0 && b > 0 && c > 0);

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int k = 2;
        int follow_a = k, follow_b = k, follow_c = (1 - k) * k;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, follow_out.getKey().intValue());
        assertEquals(0.0, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 30: If a', b', c' is the second triangle where a' = 1, b' = c = k,
     * then the type of the second triangle should always be not a triangle and the area should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(int a, int b, int c) {
        assumeTrue(a > 0 && b > 0 && c > 0);

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int k = 2;
        int follow_a = 1, follow_b = k, follow_c = k;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, follow_out.getKey().intValue());
        assertEquals(0.0, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 31: If a', b', c' is the second triangle where a'=c=2 and b'=4,
     * then the type of the second triangle should be isosceles (2) and the area should be the same as the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 2, follow_b = 4, follow_c = 2;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(2, follow_out.getKey().intValue());
        assertEquals(source_out.getValue(), follow_out.getValue());
    }

    /**
     * Metamorphic Relation 32: If a', b', c' is the second triangle where a'=b'=c' = 2, then the type of the second triangle
     * should be equilateral (3) and the area should be 1.732 times the area of the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 2, follow_b = 2, follow_c = 2;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(3, follow_out.getKey().intValue());
        assertTrue(Math.abs(source_out.getValue() - follow_out.getValue() * 1.732) < 1e-6);
    }

    /**
     * Metamorphic Relation 33: If a', b', c' is the second triangle where a'=3, b'=4, and c'=5, then the type of the
     * second triangle should be scalene (1) and the area should be the same as the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(int a, int b, int c) {
        assumeTrue(a > 0 && b > 0 && c > 0);

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 3, follow_b = 4, follow_c = 5;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(1, follow_out.getKey().intValue());
        assertEquals(source_out.getValue(), follow_out.getValue());
    }

    /**
     * Metamorphic Relation 34: If a', b', c' is the second triangle where a'=b'=1, and c'=2,
     * then the type of the second triangle should be not a triangle (0) and the area should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 1, follow_b = 1, follow_c = 2;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, follow_out.getKey().intValue());
        assertEquals(0.0, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 35: If a', b', c' is the second triangle where a' = 1, b' = 2, c' = 3,
     * then the type of the second triangle should be scalene (1) and the area should be the same as the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(int a, int b, int c) {
        assumeTrue(a > 0 && b > 0 && c > 0);

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 1, follow_b = 2, follow_c = 3;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(1, follow_out.getKey().intValue());
        assertEquals(source_out.getValue(), follow_out.getValue());
    }

    /**
     * Metamorphic Relation 36: If a', b', c' is the second triangle where a' = 1, b' = 1, c' = 3,
     * then the type of the second triangle should be not a triangle (0) and the area should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 1, follow_b = 1, follow_c = 3;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, follow_out.getKey().intValue());
        assertEquals(0.0, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 37: If a', b', c' is the second triangle where a'=1, b'=2, and c'=4,
     * then the type of the second triangle should be not a triangle (0) and the area should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 1, follow_b = 2, follow_c = 4;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, follow_out.getKey().intValue());
        assertEquals(0.0, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 38: If a', b', c' is the second triangle where a'=3, b'=3, and c'=3,
     * then the type of the second triangle should be equilateral (3) and the area should be the same as the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(int a, int b, int c) {
        assumeTrue(a > 0 && b > 0 && c > 0);

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 3, follow_b = 3, follow_c = 3;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(3, follow_out.getKey().intValue());
        assertEquals(source_out.getValue(), follow_out.getValue());
    }

    /**
     * Metamorphic Relation 39: If a', b', c' is the second triangle where a'=b'=1, and c'=1,
     * then the type of the second triangle should be not a triangle (0) and the area should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 1, follow_b = 1, follow_c = 1;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, follow_out.getKey().intValue());
        assertEquals(0.0, follow_out.getValue());
    }

    /**
     * Metamorphic Relation 40: If a', b', c' is the second triangle where a'=2, b'=3, and c'=4,
     * then the type of the second triangle should be scalene (1) and the area should be the same as the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(int a, int b, int c) {
        assumeTrue(a > 0 && b > 0 && c > 0);

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 2, follow_b = 3, follow_c = 4;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(1, follow_out.getKey().intValue());
        assertEquals(source_out.getValue(), follow_out.getValue());
    }

    public static Stream<Arguments> testcaseProvider() throws IOException {
        return testcaseGenerator.generate(1000);
    }
}