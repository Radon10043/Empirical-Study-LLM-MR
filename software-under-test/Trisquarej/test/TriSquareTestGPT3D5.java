package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.IOException;
import java.util.stream.Stream;

import org.apache.commons.lang3.tuple.Pair;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import src.TriSquareJ;

public class TriSquareTestGPT3D5 {

    /**
     * Metamorphic Relation 4: If a' = 2a, b' = 2b, c' = 2c, the type will not
     * change, but the area
     * of the first triangle is four times the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 2 * a, follow_b = 2 * b, follow_c = 2 * c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - follow_area * 4) < 1e-6);
    }

    /**
     * Metamorphic Relation 5: If a' = a, b' = b, c' = c, the output will not
     * change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = a, follow_b = b, follow_c = c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 6: If a', b', c' is the second triangle, if
     * (a,b,c)=(b,c,a'), the output
     * will not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = b, follow_b = c, follow_c = a;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 7: If a', b', c' is the second triangle, if
     * (a,b,c)=(c,a',b), the output
     * will not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = c, follow_b = a, follow_c = b;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 8: If a', b', c' is the second triangle, if
     * (a,b,c)=(-a,b,c), the output
     * will not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = -a;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, b, c);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 9: If a', b', c' is the second triangle, if
     * (a,b,c)=(a,b,-c), the output
     * will not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_c = -c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(a, b, follow_c);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 10: If a', b', c' is the second triangle, if
     * (a,b,c)=(b,-c,a), the output
     * will not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = b, follow_b = -c, follow_c = a;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 11: If a', b', c' is the second triangle, if
     * (a,b,c)=(-b,a,c), the output
     * will not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = -b, follow_b = a;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, c);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 12: If a', b', c' is the second triangle, if
     * (a,b,c)=(-a,-b,c), the output
     * will not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = -a, follow_b = -b;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, c);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 13: If a', b', c' is the second triangle, if
     * (a,b,c)=(b,a,c), the output will not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = b, follow_b = a;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, c);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 14: If a', b', c' is the second triangle, if
     * (a,b,c)=(c,a,b), the output will not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = c, follow_b = a, follow_c = b;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 15: If a', b', c' is the second triangle, if
     * (a,b,c)=(a,-b,c), the output will not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_b = -b;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(a, follow_b, c);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 16: If a', b', c' is the second triangle, if
     * (a,b,c)=(a,b,a), the output will not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_c = a;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(a, b, follow_c);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 17: If a', b', c' is the second triangle, if
     * (a,b,c)=(a,c,b), the output will not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = a, follow_b = c, follow_c = b;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 18: If a', b', c' is the second triangle, if
     * (a,b,c)=(b,a,b), the output will not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = b, follow_b = a, follow_c = b;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 19: If a', b', c' is the second triangle, if
     * (a,b,c)=(a,b,2c), the type will not change,
     * but the area of the first triangle is four times the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_c = 2 * c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(a, b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - follow_area * 4) < 1e-6);
    }

    /**
     * Metamorphic Relation 20: If a', b', c' is the second triangle, if
     * (a,b,c)=(a,2b,c), the type will not change,
     * but the area of the first triangle is four times the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_b = 2 * b;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(a, follow_b, c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - follow_area * 4) < 1e-6);
    }

    /**
     * Metamorphic Relation 21: If a', b', c' is the second triangle, if
     * (a,b,c)=(2a,b,c), the type will not change,
     * but the area of the first triangle is four times the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 2 * a;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, b, c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - follow_area * 4) < 1e-6);
    }

    /**
     * Metamorphic Relation 22: If a', b', c' is the second triangle, if
     * (a,b,c)=(3a,b,c), the type will not change,
     * but the area of the first triangle is nine times the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 3 * a;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, b, c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - follow_area * 9) < 1e-6);
    }

    /**
     * Metamorphic Relation 23: If a', b', c' is the second triangle, if
     * (a,b,c)=(a,3b,c), the type will not change,
     * but the area of the first triangle is nine times the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_b = 3 * b;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(a, follow_b, c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - follow_area * 9) < 1e-6);
    }

    /**
     * Metamorphic Relation 24: If a', b', c' is the second triangle, if
     * (a,b,c)=(a,b,3c), the type will not change,
     * but the area of the first triangle is nine times the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_c = 3 * c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(a, b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - follow_area * 9) < 1e-6);
    }

    /**
     * Metamorphic Relation 25: If a', b', c' is the second triangle, if
     * (a,b,c)=(a,2b,3c), the type will not change,
     * but the area of the first triangle is six times the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_b = 2 * b, follow_c = 3 * c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - follow_area * 6) < 1e-6);
    }

    /**
     * Metamorphic Relation 26: If a', b', c' is the second triangle, if
     * (a,b,c)=(2a,3b,4c), the type will not change,
     * but the area of the first triangle is eighteen times the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 2 * a, follow_b = 3 * b, follow_c = 4 * c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - follow_area * 18) < 1e-6);
    }

    /**
     * Metamorphic Relation 27: If a', b', c' is the second triangle, if
     * (a,b,c)=(3a,4b,5c), the type will not change,
     * but the area of the first triangle is sixty times the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 3 * a, follow_b = 4 * b, follow_c = 5 * c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - follow_area * 60) < 1e-6);
    }

    /**
     * Metamorphic Relation 28: If a', b', c' is the second triangle, if
     * (a,b,c)=(6a,8b,10c), the type will not change,
     * but the area of the first triangle is three hundred times the second
     * triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 6 * a, follow_b = 8 * b, follow_c = 10 * c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - follow_area * 300) < 1e-6);
    }

    /**
     * Metamorphic Relation 29: If a', b', c' is the second triangle, if
     * (a,b,c)=(a+b,b+c,c+a), the type will not change,
     * but the area of the first triangle is square root of 3 times the second
     * triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = a + b, follow_b = b + c, follow_c = c + a;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - follow_area * Math.sqrt(3)) < 1e-6);
    }

    /**
     * Metamorphic Relation 30: If a', b', c' is the second triangle, if
     * (a,b,c)=(b+c,c+a,a+b), the type will not change,
     * but the area of the first triangle is square root of 3 times the second
     * triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = b + c, follow_b = c + a, follow_c = a + b;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - follow_area * Math.sqrt(3)) < 1e-6);
    }

    /**
     * Metamorphic Relation 31: If a', b', c' is the second triangle, if
     * (a,b,c)=(3a,3b,3c), the type will not change,
     * but the area of the first triangle is nine times the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 3 * a, follow_b = 3 * b, follow_c = 3 * c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - follow_area * 9) < 1e-6);
    }

    /**
     * Metamorphic Relation 32: If a', b', c' is the second triangle, if
     * (a,b,c)=(k*a, k*b, k*c), where k is a positive constant,
     * then the type will not change, but the area of the first triangle is k^2
     * times the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(int a, int b, int c) {
        /* Choose a positive constant k */
        int k = 5;

        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = k * a, follow_b = k * b, follow_c = k * c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - follow_area * (k * k)) < 1e-6);
    }

    /**
     * Metamorphic Relation 33: If a', b', c' is the second triangle, if
     * (a,b,c)=(a+c,b,2c), the type will not change,
     * but the area of the first triangle is two times the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = a + c, follow_b = b, follow_c = 2 * c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - follow_area * 2) < 1e-6);
    }

    /**
     * Metamorphic Relation 34: If a', b', c' is the second triangle, if
     * (a,b,c)=(2a,b+c,2c), the type will not change,
     * but the area of the first triangle is two times the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = 2 * a, follow_b = b + c, follow_c = 2 * c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - follow_area * 2) < 1e-6);
    }

    /**
     * Metamorphic Relation 35: If a', b', c' is the second triangle, if
     * (a,b,c)=(a,2b,a+c), the type will not change,
     * but the area of the first triangle is two times the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = a, follow_b = 2 * b, follow_c = a + c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - follow_area * 2) < 1e-6);
    }

    /**
     * Metamorphic Relation 36: If a', b', c' is the second triangle, if
     * (a,b,c)=(a+b,a+c,2c), the type will not change,
     * but the area of the first triangle is two times the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = a + b, follow_b = a + c, follow_c = 2 * c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - follow_area * 2) < 1e-6);
    }

    /**
     * Metamorphic Relation 37: If a', b', c' is the second triangle, if (a,b,c) and
     * (c,b,a) are two different triangles,
     * then their areas are equal.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(int a, int b, int c) {
        /* Get the source triangle area */
        double area1 = TriSquareJ.triangle_square(a, b, c).getValue();

        /* Get the follow-up triangle area */
        double area2 = TriSquareJ.triangle_square(c, b, a).getValue();

        /* Verification */
        assertEquals(area1, area2, 0.0001);
    }

    /**
     * Metamorphic Relation 38: If a', b', c' is the second triangle, if
     * (a,b,c)=(b,b,c), the triangle might be an isosceles triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(int a, int b, int c) {
        /* Get the source triangle type */
        int source_type = TriSquareJ.triangle_square(a, b, c).getKey().intValue();

        /* Get the follow-up triangle type */
        int follow_type = TriSquareJ.triangle_square(b, b, c).getKey().intValue();

        /* Verification */
        assertTrue((source_type == 1 || follow_type == 1) && source_type != follow_type);
    }

    /**
     * Metamorphic Relation 39: If a', b', c' is the second triangle, if
     * (a,b,c)=(a,a,a), the triangle might be an equilateral triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(int a, int b, int c) {
        /* Get the source triangle type */
        int source_type = TriSquareJ.triangle_square(a, b, c).getKey().intValue();

        /* Get the follow-up triangle type */
        int follow_type = TriSquareJ.triangle_square(a, a, a).getKey().intValue();

        /* Verification */
        assertTrue((source_type == 2 || follow_type == 2) && source_type != follow_type);
    }

    /**
     * Metamorphic Relation 40: If a', b', c' is the second triangle, if
     * (a,b,c)=(6,8,10), the triangle is a right-angled triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(int a, int b, int c) {
        /* Get the source triangle type */
        int source_type = TriSquareJ.triangle_square(6, 8, 10).getKey().intValue();

        /* Verification */
        assertEquals(3, source_type);
    }

    /**
     * Metamorphic Relation 41: If a', b', c' is the second triangle, the sum of the
     * lengths of any two sides
     * of the original triangle is greater than the length of the third side.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test41(int a, int b, int c) {
        boolean validation1 = a + b > c;
        boolean validation2 = b + c > a;
        boolean validation3 = a + c > b;

        /* Verification */
        assertTrue(validation1 && validation2 && validation3);
    }

    /**
     * Metamorphic Relation 42: If a', b', c' is the second triangle, the area of a
     * triangle can never be negative.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test42(int a, int b, int c) {
        double area = TriSquareJ.triangle_square(a, b, c).getValue();

        /* Verification */
        assertTrue(area >= 0);
    }

    /**
     * Metamorphic Relation 43: If all sides of the two triangles are equal, then
     * their type will be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test43(int a, int b, int c) {
        int type1 = TriSquareJ.triangle_square(3, 3, 3).getKey().intValue();
        int type2 = TriSquareJ.triangle_square(3, 3, 3).getKey().intValue();

        /* Verification */
        assertEquals(type1, type2);
    }

    public static Stream<Arguments> testcaseProvider() throws IOException {
        return testcaseGenerator.generate(1000);
    }
}
