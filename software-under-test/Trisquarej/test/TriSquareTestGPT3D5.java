package test;

import static org.junit.Assert.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static src.TriSquareJ.triangle_square;

import java.io.IOException;
import java.util.List;
import java.util.stream.Stream;
import java.util.ArrayList;
import java.util.Collections;

import org.apache.commons.lang3.tuple.Pair;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

public class TriSquareTestGPT3D5 {
    /**
     * Metamorphic Relation 1: If we swap the positions of the side lengths of a triangle, the output will not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = b, follow_b = c, follow_c = a;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 2: If we multiply all sides of a triangle by a positive constant, the type will not change, but the area of the first triangle is a square of the constant times the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(int a, int b, int c) {
        if (a <= 0 || b <= 0 || c <= 0)
            return;

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = a * 2, follow_b = b * 2, follow_c = c * 2;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - Math.pow(follow_area, 2)) < 1e-6);
    }

    /**
     * Metamorphic Relation 3: If we add a positive constant to all sides of a triangle, the type will not change, but the area of the first triangle plus the constant times the perimeter of the triangle is the area of the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(int a, int b, int c) {
        if (a <= 0 || b <= 0 || c <= 0)
            return;

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int constant = 3;
        int follow_a = a + constant, follow_b = b + constant, follow_c = c + constant;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area + constant * (a + b + c) - follow_area) < 1e-6);
    }

    /**
     * Metamorphic Relation 4: If we swap any two sides of a triangle, the type will not change, but the triangle areas will not be equal.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = c, follow_b = a, follow_c = b;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertNotEquals(source_area, follow_area);
    }

    /**
     * Metamorphic Relation 5: If all sides of the triangle are equal, and we increase all sides by the same constant, the type of the triangle will remain the same, but the area of the second triangle will be the square of the constant times the area of the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(int a, int b, int c) {
        if (a != b || b != c) // Not an equilateral triangle
            return;

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int constant = 2;
        int follow_a = a + constant, follow_b = b + constant, follow_c = c + constant;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertEquals(follow_area, Math.pow(source_area, 2));
    }

    //fixed
    /**
     * Metamorphic Relation 6: If two sides of the triangle are equal, and a new triangle is formed by scaling the sides by a factor, then the triangle type will remain the same, but the area of the second triangle will be the square of the scaling factor times the area of the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(int a, int b, int c) {
        if (a != b && b != c && c != a) // Not a triangle with at least two equal sides
            return;

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int scalingFactor = 2;
        int follow_a = a * scalingFactor, follow_b = b * scalingFactor, follow_c = c * scalingFactor;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertEquals(follow_area, Math.pow(scalingFactor, 2) * source_area, 0.001);
    }

    /**
     * Metamorphic Relation 7: If we double the length of one side of the triangle and halve the length of another side, the type of the triangle will remain the same, but the area of the first triangle multiplied by the halved side length will be equal to the area of the second triangle multiplied by the doubled side length.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a, follow_b, follow_c;

        if (a > b) {
            follow_a = a * 2;
            follow_b = b / 2;
            follow_c = c;
        } else {
            follow_a = a / 2;
            follow_b = b * 2;
            follow_c = c;
        }

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertEquals(source_area * (b / 2), follow_area * (a * 2));
    }

    /**
     * Metamorphic Relation 8: If we add a positive constant to one side, and subtract the same constant from another side of the triangle, the type of the triangle will remain the same, but the area of the first triangle plus the constant times the difference of the sides will be equal to the area of the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(int a, int b, int c) {
        if (a <= 0 || b <= 0 || c <= 0)
            return;

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int constant = 3;
        int follow_a = a + constant, follow_b = b - constant, follow_c = c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area + constant * (a - b) - follow_area) < 1e-6);
    }

    /**
     * Metamorphic Relation 9: If we subtract a positive constant from all sides of a triangle, the type will remain the same, but the area of the first triangle minus the constant times the perimeter of the triangle will be equal to the area of the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(int a, int b, int c) {
        if (a <= 0 || b <= 0 || c <= 0)
            return;

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int constant = 3;
        int follow_a = a - constant, follow_b = b - constant, follow_c = c - constant;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area - constant * (a + b + c) - follow_area) < 1e-6);
    }

    /**
     * Metamorphic Relation 10: If the three sides of the triangle form an arithmetic progression, then the type of the triangle and the area of the triangle will not change when adding or subtracting a constant from all sides of the triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(int a, int b, int c) {
        if (a <= 0 || b <= 0 || c <= 0)
            return;

        if (2 * b == a + c) // Sides form an arithmetic progression
        {
            /* Get source output */
            Pair<Integer, Double> source_out = triangle_square(a, b, c);

            /* Construct follow-up input */
            int constant = 5;
            int follow_a = a + constant, follow_b = b + constant, follow_c = c + constant;

            /* Get follow-up output */
            Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

            /* Verification */
            int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
            double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
            assertEquals(source_type, follow_type);
            assertEquals(source_area, follow_area);
        }
    }

    //fixed
    /**
     * Metamorphic Relation 11: If we scale all sides of the triangle by a positive constant, the type of the triangle remains the same, and the area of the second triangle is the square of the scaling factor times the area of the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(int a, int b, int c) {
        if (a <= 0 || b <= 0 || c <= 0)
            return;

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int scalingFactor = 2;
        int follow_a = a * scalingFactor, follow_b = b * scalingFactor, follow_c = c * scalingFactor;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertEquals(follow_area, Math.pow(scalingFactor, 2) * source_area, 0.001);
    }

    /**
     * Metamorphic Relation 12: If we scale all sides of the triangle by a positive constant, the type of the triangle remains the same, and the perimeter of the second triangle is the scaling factor times the perimeter of the first triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(int a, int b, int c) {
        if (a <= 0 || b <= 0 || c <= 0)
            return;

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int scalingFactor = 2;
        int follow_a = a * scalingFactor, follow_b = b * scalingFactor, follow_c = c * scalingFactor;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertEquals((a + b + c) * scalingFactor, (follow_a + follow_b + follow_c));
    }

    /**
     * Metamorphic Relation 13: If one side of the triangle is doubled and another side is halved, the type of the triangle will remain the same, and the perimeter of the first triangle plus the difference of the sides will be equal to the perimeter of the second triangle
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = a * 2, follow_b = b / 2, follow_c = c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertEquals((a + b + c) + (a * 2 - b / 2), follow_a + follow_b + follow_c);
    }

    /**
     * Metamorphic Relation 14: If the difference of the sides of a triangle is a constant, and we add this constant to one side and subtract from another side, the type remains the same, and the area of the first triangle plus the constant times the difference of the sides will be equal to the area of the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(int a, int b, int c) {
        if (a <= 0 || b <= 0 || c <= 0)
            return;

        int diff = Math.abs(a - b);
        if (diff == Math.abs(b - c) && diff == Math.abs(c - a)) // All sides have the same difference
        {
            /* Get source output */
            Pair<Integer, Double> source_out = triangle_square(a, b, c);

            /* Construct follow-up input */
            int constant = 3;
            int follow_a = a + constant, follow_b = b - constant, follow_c = c;

            /* Get follow-up output */
            Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

            /* Verification */
            int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
            double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
            assertEquals(source_type, follow_type);
            assertTrue(Math.abs(source_area + constant * diff - follow_area) < 1e-6);
        }
    }

    /**
     * Metamorphic Relation 15: If all sides of the triangle are equal, and a positive constant is added to one side, the type of the triangle will remain the same, and the area of the first triangle plus the constant times the perimeter of the triangle will be equal to the area of the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(int a, int b, int c) {
        if (a == b && b == c) // Equilateral triangle
        {
            /* Get source output */
            Pair<Integer, Double> source_out = triangle_square(a, b, c);

            /* Construct follow-up input */
            int constant = 3;
            int follow_a = a + constant, follow_b = b, follow_c = c;

            /* Get follow-up output */
            Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

            /* Verification */
            int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
            double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
            assertEquals(source_type, follow_type);
            assertTrue(Math.abs(source_area + constant * (a + b + c) - follow_area) < 1e-6);
        }
    }

    /**
     * Metamorphic Relation 16: If the difference of the sides of the triangle forms a geometric sequence, the type remains the same, and scaling all sides by a positive constant scales the perimeter of the first triangle by the same constant as the perimeter of the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(int a, int b, int c) {
        if (a <= 0 || b <= 0 || c <= 0)
            return;

        int diff = Math.abs(a - b);
        if (diff == Math.abs(b - c) && diff == Math.abs(c - a)) // All sides form a geometric sequence
        {
            /* Get source output */
            Pair<Integer, Double> source_out = triangle_square(a, b, c);

            /* Construct follow-up input */
            int scalingFactor = 2;
            int follow_a = a * scalingFactor, follow_b = b * scalingFactor, follow_c = c * scalingFactor;

            /* Get follow-up output */
            Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

            /* Verification */
            int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
            double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
            assertEquals(source_type, follow_type);
            assertEquals((a + b + c) * scalingFactor, (follow_a + follow_b + follow_c));
        }
    }

    /**
     * Metamorphic Relation 17: If two triangles are the same, their types and areas will be the same regardless of the order of the side lengths provided.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Get follow-up output with swapped sides */
        Pair<Integer, Double> follow_out = triangle_square(b, c, a);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 18: If two triangles are the same, their types and areas will be the same regardless of the repetition of side lengths provided.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(int a, int b, int c) {
        if (a == b && b == c) // Equilateral triangle
            return;

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Get follow-up output with the last side repeated at the front */
        Pair<Integer, Double> follow_out = triangle_square(c, a, b);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 19: If we subtract a positive constant from one side and add the same constant to another side of the triangle, the type will remain the same, and the area of the first triangle plus the constant times the difference of the sides will be equal to the area of the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(int a, int b, int c) {
        if (a <= 0 || b <= 0 || c <= 0)
            return;

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int constant = 3;
        int follow_a = a - constant, follow_b = b + constant, follow_c = c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertTrue(Math.abs(source_area + constant * (b - a) - follow_area) < 1e-6);
    }

    /**
     * Metamorphic Relation 20: If all sides of the triangle are equal and a positive constant is added to one side, the type of the triangle will remain the same, and the area of the first triangle plus the constant times the perimeter of the triangle will be equal to the area of the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(int a, int b, int c) {
        if (a == b && b == c) // Equilateral triangle
        {
            /* Get source output */
            Pair<Integer, Double> source_out = triangle_square(a, b, c);

            /* Construct follow-up input */
            int constant = 3;
            int follow_a = a + constant, follow_b = b, follow_c = c;

            /* Get follow-up output */
            Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

            /* Verification */
            int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
            double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
            assertEquals(source_type, follow_type);
            assertTrue(Math.abs(source_area + constant * (a + b + c) - follow_area) < 1e-6);
        }
    }

    /**
     * Metamorphic Relation 21: If we double the length of one side of the triangle and halve the length of another side, the type of the triangle will remain the same, but the area of the first triangle multiplied by the halved side length will be equal to the area of the second triangle multiplied by the doubled side length.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = a * 2, follow_b = b / 2, follow_c = c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertEquals(source_area * follow_b, follow_area * follow_a);
    }

    /**
     * Metamorphic Relation 22: If the difference between the sides of the triangle is a constant, and we add the constant to one side and subtract from another side, the type remains the same, and the area of the first triangle plus the constant times the difference of the sides will be equal to the area of the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(int a, int b, int c) {
        if (a <= 0 || b <= 0 || c <= 0)
            return;

        int diff = Math.abs(a - b);
        if (diff == Math.abs(b - c) && diff == Math.abs(c - a)) // All sides have the same difference
        {
            /* Get source output */
            Pair<Integer, Double> source_out = triangle_square(a, b, c);

            /* Construct follow-up input */
            int constant = 3;
            int follow_a = a + constant, follow_b = b - constant, follow_c = c;

            /* Get follow-up output */
            Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

            /* Verification */
            int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
            double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
            assertEquals(source_type, follow_type);
            assertTrue(Math.abs(source_area + constant * diff - follow_area) < 1e-6);
        }
    }

    //fixed
    /**
     * Metamorphic Relation 23: If the triangle is valid, then its type and area will remain the same after any permutation of the sides.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Generate all possible permutations of sides */
        List<List<Integer>> permutations = generatePermutations(a, b, c);

        for (List<Integer> perm : permutations) {
            /* Get follow-up output using permutation */
            Pair<Integer, Double> follow_out = triangle_square(perm.get(0), perm.get(1), perm.get(2));

            /* Verification */
            assertEquals(source_out, follow_out);
        }
    }
    public static List<List<Integer>> generatePermutations(int a, int b, int c) {
        List<List<Integer>> permutations = new ArrayList<>();

        // 将边长添加到列表中
        List<Integer> sides = new ArrayList<>();
        sides.add(a);
        sides.add(b);
        sides.add(c);

        // 使用Collections类的permute方法获取所有可能的排列
        permute(permutations, sides, 0);

        return permutations;
    }
    private static void permute(List<List<Integer>> permutations, List<Integer> sides, int start) {
        if (start == sides.size() - 1) {
            // 添加当前排列到结果列表
            permutations.add(new ArrayList<>(sides));
            return;
        }

        for (int i = start; i < sides.size(); i++) {
            // 交换当前元素与后面的每个元素
            Collections.swap(sides, i, start);

            // 递归调用permute方法
            permute(permutations, sides, start + 1);

            // 恢复原始列表以进行下一个排列
            Collections.swap(sides, start, i);
        }
    }

    /**
     * Metamorphic Relation 24: If the triangle is valid, then its type and area will remain the same after changing the order of the sides.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(int a, int b, int c) {
        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Get follow-up output by reversing the order of sides */
        Pair<Integer, Double> follow_out = triangle_square(c, b, a);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 25: If the triangle is valid, then its type and area will remain the same after changing the order of the sides and scaling all sides by a positive constant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(int a, int b, int c) {
        if (a <= 0 || b <= 0 || c <= 0) {
            return;
        }

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Get follow-up output by reversing the order of sides and scaling by a constant */
        int scalingFactor = 2;
        Pair<Integer, Double> follow_out = triangle_square(c * scalingFactor, b * scalingFactor, a * scalingFactor);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 26: If the triangle is valid, then its type and area will remain the same after changing the order of the sides and adding the same constant to all sides of the triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(int a, int b, int c) {
        if (a <= 0 || b <= 0 || c <= 0) {
            return;
        }

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Get follow-up output by reversing the order of sides and adding a constant */
        int constant = 3;
        Pair<Integer, Double> follow_out = triangle_square(c + constant, b + constant, a + constant);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    //fixed
    /**
     * Metamorphic Relation 27: If the sides of the triangle form an arithmetic sequence, then scaling all sides by the same positive constant will result in a triangle with the same type and an area scaled by the squared value of the constant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(int a, int b, int c) {
        if ((a + c) % 2 == 1) {
            return;  // Not an arithmetic sequence
        }

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int scalingFactor = 3;
        int follow_a = a * scalingFactor, follow_b = b * scalingFactor, follow_c = c * scalingFactor;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertEquals(source_area * Math.pow(scalingFactor, 2), follow_area, 0.001);
    }

    /**
     * Metamorphic Relation 28: If the sides of the triangle form a geometric sequence, then scaling all sides by the same positive constant will result in a triangle with the same type and an area scaled by the power of the constant based on the type of sequence formed.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(int a, int b, int c) {
        if (a == 0 || b == 0 || c == 0) {
            return;  // Not a valid triangle
        }

        if (a * a == b * c) {
            int scalingFactor = 2;

            /* Get source output */
            Pair<Integer, Double> source_out = triangle_square(a, b, c);

            /* Construct follow-up input */
            int follow_a = a * scalingFactor, follow_b = b * scalingFactor, follow_c = c * scalingFactor;

            /* Get follow-up output */
            Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

            /* Verification */
            int source_type = source_out.getKey().intValue(), follow_type = source_out.getKey().intValue();
            double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
            assertEquals(source_type, follow_type);
            assertEquals(source_area * Math.pow(scalingFactor, 2), follow_area);
        }
    }

    /**
     * Metamorphic Relation 29: If the side lengths are valid, then multiplying all sides by a positive constant and then taking the square root of the product should result in a triangle with the same type and an area scaled by the square root of the constant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(int a, int b, int c) {
        if (a <= 0 || b <= 0 || c <= 0) {
            return; // Not a valid triangle
        }

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input by taking the square root of the product of the sides after multiplying by a constant */
        int constant = 4;
        double product = a * b * c;
        double scaledProduct = product * constant;
        double scaledArea = source_out.getValue() * Math.sqrt(constant);
        Pair<Integer, Double> follow_out = triangle_square((int)Math.sqrt(scaledProduct), (int)Math.sqrt(scaledProduct), (int)Math.sqrt(scaledProduct));

        /* Verification */
        assertEquals(source_out.getKey(), follow_out.getKey()); // Triangle type remains the same
        assertEquals(scaledArea, follow_out.getValue(), 0.001); // Area scaled by the square root of the constant
    }


    /**
     * Metamorphic Relation 30: If the triangle is valid and one side is doubled and the other side remains the same, the type will remain the same, and the area of the first triangle multiplied by the unchanged side length will be equal to the area of the second triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(int a, int b, int c) {
        if (a <= 0 || b <= 0 || c <= 0) {
            return;
        }

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input */
        int follow_a = a * 2; // double one side
        int follow_b = b; // keep the other side unchanged
        int follow_c = c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        int source_type = source_out.getKey().intValue(), follow_type = follow_out.getKey().intValue();
        double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
        assertEquals(source_type, follow_type);
        assertEquals(source_area * follow_b, follow_area * a);
    }

    /**
     * Metamorphic Relation 31: If the triangle is valid and one side is set to zero, the type and area will not change, and the function should return "Not a triangle" (type 0) and area 0.0 for both triangles.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(int a, int b, int c) {
        if (a <= 0 || b <= 0 || c <= 0) {
            return; // Not a valid triangle
        }

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input with one side set to zero */
        int follow_a = 0, follow_b = b, follow_c = c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, source_out.getKey().intValue()); // source should not be a triangle
        assertEquals(0.0, source_out.getValue().doubleValue()); // area should be 0.0
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 32: If the triangle is valid and one side is set to a negative value, the type and area will not change, and the function should return "Not a triangle" (type 0) and area 0.0 for both triangles.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(int a, int b, int c) {
        if (a <= 0 || b <= 0 || c <= 0) {
            return; // Not a valid triangle
        }

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input with one side set to a negative value */
        int follow_a = -a, follow_b = b, follow_c = c;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, source_out.getKey().intValue()); // source should not be a triangle
        assertEquals(0.0, source_out.getValue().doubleValue()); // area should be 0.0
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 33: If all sides are zero, the function should return "Not a triangle" (type 0) and area 0.0 for both triangles.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(int a, int b, int c) {

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input where all sides are set to zero */
        int follow_a = 0, follow_b = 0, follow_c = 0;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, source_out.getKey().intValue()); // source should not be a triangle
        assertEquals(0.0, source_out.getValue().doubleValue()); // area should be 0.0
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 34: If two sides are negative and one side is positive making it invalid, the function should return "Not a triangle" (type 0) and area 0.0 for both triangles.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(int a, int b, int c) {

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input where two sides are negative and one side is positive */
        int follow_a = -3, follow_b = -4, follow_c = 5;

        /* Get follow-up output */
        Pair<Integer, Double> follow_out = triangle_square(follow_a, follow_b, follow_c);

        /* Verification */
        assertEquals(0, source_out.getKey().intValue()); // source should not be a triangle
        assertEquals(0.0, source_out.getValue().doubleValue()); // area should be 0.0
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 35: If the side lengths of the triangle are non-integer values, then scaling the sides by a positive constant will result in a triangle with the same type and an area scaled by the power of the constant based on the type of triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(double a, double b, double c) {
        if (a <= 0 || b <= 0 || c <= 0) {
            return; // Not a valid triangle
        }

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square((int)a, (int)b, (int)c);

        /* Construct follow-up input */
        double scalingFactor = 1.5;
        Pair<Integer, Double> follow_out = triangle_square((int)(a * scalingFactor), (int)(b * scalingFactor), (int)(c * scalingFactor));

        /* Verification */
        assertEquals(source_out.getKey(), follow_out.getKey()); // Triangle type remains the same
        double expectedArea = source_out.getValue() * Math.pow(scalingFactor, 2);
        assertEquals(expectedArea, follow_out.getValue(), 0.001); // Area scaled by the square of the scaling factor
    }

    /**
     * Metamorphic Relation 36: If the side lengths are such that two sides sum up to less than or equal to the third side, then the triangle is invalid. Adding a positive constant to one side will still result in an invalid triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(int a, int b, int c) {
        if (a <= 0 || b <= 0 || c <= 0) {
            return; // Not a valid triangle
        }

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input where the triangle is still invalid */
        int constant = 1;
        Pair<Integer, Double> follow_out = triangle_square(a + constant, b, c);

        /* Verification */
        assertEquals(0, source_out.getKey().intValue()); // Triangle should be invalid
        assertEquals(0.0, source_out.getValue().doubleValue()); // Area should be 0.0
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 37: If the sum of the squares of two sides equals the square of the third side, then it results in a right-angled triangle. Scaling all sides by a positive constant will preserve the type and result in an area scaled by the square of the constant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(double a, double b, double c) {
        if (a <= 0 || b <= 0 || c <= 0) {
            return; // Not a valid triangle
        }

        if (a * a + b * b == c * c || a * a + c * c == b * b || b * b + c * c == a * a) {
            /* Get source output */
            Pair<Integer, Double> source_out = triangle_square((int)a, (int)b, (int)c);

            /* Construct follow-up input */
            double scalingFactor = 2;
            Pair<Integer, Double> follow_out = triangle_square((int)(a * scalingFactor), (int)(b * scalingFactor), (int)(c * scalingFactor));

            /* Verification */
            assertEquals(source_out.getKey(), follow_out.getKey()); // Triangle type remains the same
            double expectedArea = source_out.getValue() * Math.pow(scalingFactor, 2);
            assertEquals(expectedArea, follow_out.getValue(), 0.0001); // Area scaled by the square of the scaling factor
        }
    }

    /**
     * Metamorphic Relation 38: If all sides are equal and the triangle is valid, then scaling all sides by a positive constant will preserve the type and result in an area scaled by the square of the constant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(double a, double b, double c) {
        if (a <= 0 || b <= 0 || c <= 0) {
            return; // Not a valid triangle
        }

        if (a == b && b == c) {
            /* Get source output */
            Pair<Integer, Double> source_out = triangle_square((int)a, (int)b, (int)c);

            /* Construct follow-up input */
            double scalingFactor = 3;
            Pair<Integer, Double> follow_out = triangle_square((int)(a * scalingFactor), (int)(b * scalingFactor), (int)(c * scalingFactor));

            /* Verification */
            assertEquals(source_out.getKey(), follow_out.getKey()); // Triangle type remains the same
            double expectedArea = source_out.getValue() * Math.pow(scalingFactor, 2);
            assertEquals(expectedArea, follow_out.getValue(), 0.0001); // Area scaled by the square of the scaling factor
        }
    }

    /**
     * Metamorphic Relation 39: If the triangle is valid, then swapping the side lengths and applying a positive scaling factor should preserve the type and result in an area scaled by the square of the scaling factor.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(int a, int b, int c) {
        if (a <= 0 || b <= 0 || c <= 0) {
            return; // Not a valid triangle
        }

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input by swapping sides and applying scaling factor */
        int scalingFactor = 2;
        Pair<Integer, Double> follow_out = triangle_square(b * scalingFactor, c * scalingFactor, a * scalingFactor);

        /* Verification */
        assertEquals(source_out.getKey(), follow_out.getKey()); // Triangle type remains the same
        double expectedArea = source_out.getValue() * Math.pow(scalingFactor, 2);
        assertEquals(expectedArea, follow_out.getValue(), 0.0001); // Area scaled by the square of the scaling factor
    }

    /**
     * Metamorphic Relation 40: If the triangle is valid, updating the side lengths with their respective square roots and applying a positive constant scaling factor should preserve the triangle type and result in an area scaled by the constant value.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(int a, int b, int c) {
        if (a <= 0 || b <= 0 || c <= 0) {
            return; // Not a valid triangle
        }

        /* Get source output */
        Pair<Integer, Double> source_out = triangle_square(a, b, c);

        /* Construct follow-up input by applying square root and scaling factor */
        int constant = 3;
        double follow_a = Math.sqrt(a);
        double follow_b = Math.sqrt(b);
        double follow_c = Math.sqrt(c);
        Pair<Integer, Double> follow_out = triangle_square((int)(follow_a * constant), (int)(follow_b * constant), (int)(follow_c * constant));

        /* Verification */
        assertEquals(source_out.getKey(), follow_out.getKey()); // Triangle type remains the same
        double expectedArea = source_out.getValue() * constant;
        assertEquals(expectedArea, follow_out.getValue(), 0.0001); // Area scaled by the constant value
    }

    public static Stream<Arguments> testcaseProvider() throws IOException {
        return testcaseGenerator.generate(1000);
    }
}