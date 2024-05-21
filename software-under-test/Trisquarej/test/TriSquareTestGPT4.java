package test;

import static org.junit.Assert.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;
import static src.TriSquareJ.triangle_square;

import java.io.IOException;
import java.util.Arrays;
import java.util.function.Consumer;
import java.util.stream.Stream;
import org.apache.commons.lang3.tuple.Pair;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

public class TriSquareTestGPT4 {
    /**
     * Metamorphic Relation 1: Permuting the input sides of a triangle doesn't change its type or
     * its area.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest1(int a, int b, int c) {
        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Generate follow-up inputs by permuting sides */
        Pair<Integer, Double> output1 = triangle_square(b, a, c);
        Pair<Integer, Double> output2 = triangle_square(b, c, a);
        Pair<Integer, Double> output3 = triangle_square(c, a, b);
        Pair<Integer, Double> output4 = triangle_square(c, b, a);
        Pair<Integer, Double> output5 = triangle_square(a, c, b);

        /* Verify that type and area are consistent */
        assertEquals(originalOutput, output1);
        assertEquals(originalOutput, output2);
        assertEquals(originalOutput, output3);
        assertEquals(originalOutput, output4);
        assertEquals(originalOutput, output5);
    }

    /**
     * Metamorphic Relation 2: Doubling the lengths of the sides of a triangle doubles its area, but
     * doesn't change its type.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest2(int a, int b, int c) {
        assumeTrue(a <= Integer.MAX_VALUE / 2 && b <= Integer.MAX_VALUE / 2
                && c <= Integer.MAX_VALUE / 2);

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Scale the sides by 2 */
        int scaledA = a * 2;
        int scaledB = b * 2;
        int scaledC = c * 2;

        /* Compute the follow-up output */
        Pair<Integer, Double> scaledOutput = triangle_square(scaledA, scaledB, scaledC);

        /* Verify the type is the same and the area is scaled appropriately */
        assertEquals(originalOutput.getKey(), scaledOutput.getKey());
        assertEquals(4 * originalOutput.getValue(), scaledOutput.getValue(), 1e-6);
    }

    /**
     * Metamorphic Relation 3: Adding the same value to each side of a valid triangle produces a
     * valid triangle of the same type and with proportionally larger area.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest3(int a, int b, int c) { // Fixed
        assumeTrue(a + b > c && a + c > b && b + c > a); // Ensure it's a valid triangle

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Add the same value to each side */
        int addition = 1;
        int newA = a + addition;
        int newB = b + addition;
        int newC = c + addition;

        /* Get follow-up output */
        Pair<Integer, Double> followUpOutput = triangle_square(newA, newB, newC);

        assertEquals(originalOutput.getKey(), followUpOutput.getKey());
        assertTrue(originalOutput.getValue() < followUpOutput.getValue());
    }

    /**
     * Metamorphic Relation 4: Subtracting the same smallest positive integer value from two sides
     * of an isosceles triangle (where neither subtraction would result in a side-length of 0), will
     * result in a new triangle that is either scalene or isosceles with a different area, but not
     * equilateral.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest4(int a, int b, int c) {
        // Find the two equal sides of an isosceles triangle (ignoring the case of an
        // equilateral triangle) assuming no side is the smallest integer (1).
        assumeTrue(((a == b && a != c) || (a == c && a != b) || (b == c && a != b)) && a > 1
                && b > 1 && c > 1);

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Subtract 1 from two equal sides */
        int newA = a == c ? a - 1 : a;
        int newB = b == c ? b - 1 : b;
        int newC = (a == b && a != c) ? c - 1 : c;

        /* Get follow-up output */
        Pair<Integer, Double> followUpOutput = triangle_square(newA, newB, newC);

        /* Verify the type is not equilateral and the area has changed */
        assertNotEquals(Integer.valueOf(3), followUpOutput.getKey());
        assertNotEquals(originalOutput.getValue(), followUpOutput.getValue(), 1e-6);
    }

    /**
     * Metamorphic Relation 5: If the input triangle is scaled by a factor k > 1, the area is scaled
     * by a factor of k^2, but the type remains the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest5(int a, int b, int c) { // Fixed
        assumeTrue(a + b > c && a + c > b && b + c > a); // Ensure it's a valid triangle

        int k = 3;

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Scale the sides by k */
        int scaledA = a * k;
        int scaledB = b * k;
        int scaledC = c * k;

        /* Compute the follow-up output */
        Pair<Integer, Double> scaledOutput = triangle_square(scaledA, scaledB, scaledC);

        /* Verify the type is the same and the area is scaled appropriately */
        assertEquals(originalOutput.getKey(), scaledOutput.getKey());
        assertEquals(Math.pow(k, 2) * originalOutput.getValue(), scaledOutput.getValue(), 1e-6);
    }

    /**
     * Metamorphic Relation 6: If one side of the triangle is extended by adding a positive value
     * that cannot convert the triangle from an isosceles into an equilateral, the type either
     * remains the same or changes to scalene, and the area increases.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest6(int a, int b, int c) {
        // Extend one side of the triangle by 1, ensuring the resulting triangle
        // does not become equilateral if it was originally isosceles.
        assumeTrue(a + 1 != b || b != c);

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Get the follow-up outputs by extending each side separately */
        Pair<Integer, Double> extendAOutput = triangle_square(a + 1, b, c);
        Pair<Integer, Double> extendBOutput = triangle_square(a, b + 1, c);
        Pair<Integer, Double> extendCOutput = triangle_square(a, b, c + 1);

        /* Verify that the triangle type is not equilateral and the area increases */
        assertNotEquals(Integer.valueOf(3), extendAOutput.getKey());
        assertTrue(extendAOutput.getValue() > originalOutput.getValue());

        assertNotEquals(Integer.valueOf(3), extendBOutput.getKey());
        assertTrue(extendBOutput.getValue() > originalOutput.getValue());

        assertNotEquals(Integer.valueOf(3), extendCOutput.getKey());
        assertTrue(extendCOutput.getValue() > originalOutput.getValue());
    }

    /**
     * Metamorphic Relation 7: Swapping the sides of an isosceles triangle does not change the type
     * or area.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest7(int a, int b, int c) { // Fixed
        assumeTrue(((a == b && a != c) || (a == c && a != b) || (b == c && a != b)));

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Construct follow-up input based on isosceles sides */
        int followA = b, followB = a, followC = c;

        /* Get follow-up output */
        Pair<Integer, Double> followUpOutput = triangle_square(followA, followB, followC);

        /* Verify that the type and area remain unchanged */
        assertEquals(originalOutput.getKey(), followUpOutput.getKey());
        assertEquals(originalOutput.getValue(), followUpOutput.getValue(), 1e-6);
    }

    /**
     * Metamorphic Relation 8: Scaling the sides of an equilateral triangle by an integer factor k >
     * 1 results in an equilateral triangle, and the area is scaled by k^2.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest8(int a) {
        int b = a, c = a; // Ensuring the triangle is equilateral
        int k = 2; // Scale factor

        assumeTrue(a <= Integer.MAX_VALUE / k);

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Scale the sides by factor k and get the follow-up output */
        Pair<Integer, Double> scaledOutput = triangle_square(a * k, b * k, c * k);

        /* Verify the triangle type is still equilateral */
        assertEquals(Integer.valueOf(3), scaledOutput.getKey());

        /* Verify the area is scaled by k^2 */
        assertEquals(Math.pow(k, 2) * originalOutput.getValue(), scaledOutput.getValue(), 1e-6);
    }

    /**
     * Metamorphic Relation 9: For any valid triangle, multiplying the side lengths by a positive
     * integer 'k' will result in a valid triangle with the same type, and the area will increase by
     * a factor of k^2.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest9(int a, int b, int c) { // Fixed
        int k = 5;
        assumeTrue(a + b > c && a + c > b && b + c > a);

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Multiply all sides by 'k' */
        int scaledA = a * k;
        int scaledB = b * k;
        int scaledC = c * k;

        /* Get follow-up output */
        Pair<Integer, Double> scaledOutput = triangle_square(scaledA, scaledB, scaledC);

        /* Verify that the triangle's type does not change */
        assertEquals(originalOutput.getKey(), scaledOutput.getKey());

        /* Verify that the area increases by a factor of k^2 */
        assertEquals(originalOutput.getValue() * k * k, scaledOutput.getValue(), 1e-6);
    }

    /**
     * Metamorphic Relation 10: If a valid scalene triangle's smallest side is replaced by the sum
     * of the other two sides, it will return 'Not a Triangle'.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest10(int a, int b, int c) {
        // Make sure the triangle is scalene and valid
        assumeTrue(a != b && a != c && b != c && a < b + c && b < a + c && c < a + b);
        int smallestSide = Math.min(a, Math.min(b, c));

        /* Replace the smallest side with the sum of the other two */
        int newA = (smallestSide == a) ? (b + c) : a;
        int newB = (smallestSide == b) ? (a + c) : b;
        int newC = (smallestSide == c) ? (a + b) : c;

        /* Get follow-up output */
        Pair<Integer, Double> followUpOutput = triangle_square(newA, newB, newC);

        /* Verify that it is not a triangle */
        assertEquals(Integer.valueOf(0), followUpOutput.getKey());
        assertEquals(Double.valueOf(0.0), followUpOutput.getValue());
    }

    /**
     * Metamorphic Relation 11: For a valid scalene triangle, replacing the longest side with the
     * sum of the other two sides minus one should yield a scalene triangle with a different area.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest11(int a, int b, int c) {
        // Make sure the triangle is scalene and valid
        assumeTrue(a != b && a != c && b != c && a < b + c && b < a + c && c < a + b);
        int longestSide = Math.max(a, Math.max(b, c));

        /* Get original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /*
         * Replace the longest side with the sum of the other two sides minus one, creating a new
         * triangle
         */
        int newA = (longestSide == a) ? (b + c - 1) : a;
        int newB = (longestSide == b) ? (a + c - 1) : b;
        int newC = (longestSide == c) ? (a + b - 1) : c;

        /* Get follow-up output */
        Pair<Integer, Double> followUpOutput = triangle_square(newA, newB, newC);

        /* Verify that the resulting triangle is scalene and has a different area */
        assertEquals(Integer.valueOf(1), followUpOutput.getKey());
        assertNotEquals(originalOutput.getValue(), followUpOutput.getValue());
    }

    /**
     * Metamorphic Relation 12: Multiplying the side lengths of an equilateral triangle by a
     * fraction (1/2) should still result in an equilateral triangle with an area that is
     * one-quarter of the original area.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest12(int o) {
        assumeTrue(o % 2 == 0 && o > 2); // Ensure that the side can be halved and still remains an
                                         // integer
        int a = o, b = o, c = o; // Equilateral sides

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Halve the side lengths */
        a /= 2;
        b /= 2;
        c /= 2;

        /* Get follow-up output */
        Pair<Integer, Double> followUpOutput = triangle_square(a, b, c);

        /* Verify that the triangle remains equilateral */
        assertEquals(Integer.valueOf(3), followUpOutput.getKey());

        /* Verify that the area is one-quarter of the original */
        assertEquals(0.25 * originalOutput.getValue(), followUpOutput.getValue(), 1e-6);
    }

    /**
     * Metamorphic Relation 13: If an isosceles triangle has its unique side length multiplied by a
     * scalar 'k', the type remains the same while the area changes.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest13(int a, int b, int c) {
        // Determine if it's an isosceles triangle but not equilateral
        assumeTrue(((a == b && a != c) || (a == c && a != b) || (b == c && b != a))
                && (a != b || b != c || a != c));
        int scalar = 2; // A scalar 'k' to alter the unique side

        /* Obtain the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Isosceles triangle with unique side 'a' */
        if (a != b) {
            int newA = a * scalar;

            /* Calculate follow-up output */
            Pair<Integer, Double> followUpOutput = triangle_square(newA, b, c);

            /* Validate type stays same */
            assertEquals(originalOutput.getKey(), followUpOutput.getKey());

            /* Validate area has changed */
            assertNotEquals(originalOutput.getValue(), followUpOutput.getValue());
        }

        /* Isosceles triangle with unique side 'b' */
        if (b != c) {
            int newB = b * scalar;

            /* Calculate follow-up output */
            Pair<Integer, Double> followUpOutput = triangle_square(a, newB, c);

            /* Validate type stays same */
            assertEquals(originalOutput.getKey(), followUpOutput.getKey());

            /* Validate area has changed */
            assertNotEquals(originalOutput.getValue(), followUpOutput.getValue());
        }

        /* Isosceles triangle with unique side 'c' */
        if (c != a) {
            int newC = c * scalar;

            /* Calculate follow-up output */
            Pair<Integer, Double> followUpOutput = triangle_square(a, b, newC);

            /* Validate type stays same */
            assertEquals(originalOutput.getKey(), followUpOutput.getKey());

            /* Validate area has changed */
            assertNotEquals(originalOutput.getValue(), followUpOutput.getValue());
        }
    }

    /**
     * Metamorphic Relation 14: For any valid triangle, reducing all sides by the same smallest
     * integer 'n' that does not invalidate the triangle inequality should result in a valid
     * triangle of the same type with a smaller area.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest14(int a, int b, int c) {
        // Ensure reduction won't lead to non-positive side lengths or invalidate the
        // triangle inequality
        int minSide = Math.min(Math.min(a, b), c);
        int reduction = Math.min(minSide - 1, (a + b - c) - 1);
        reduction = Math.min(reduction, (a + c - b) - 1);
        reduction = Math.min(reduction, (b + c - a) - 1);
        assumeTrue(reduction > 0);

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Reduce sides by 'n' and calculate the follow-up output */
        Pair<Integer, Double> reducedOutput =
                triangle_square(a - reduction, b - reduction, c - reduction);

        /* Verify the triangle’s type remains the same */
        assertEquals(originalOutput.getKey(), reducedOutput.getKey());

        /* Verify the area is smaller */
        assertTrue(originalOutput.getValue() > reducedOutput.getValue());
    }

    /**
     * Metamorphic Relation 15: Triangles that share two equal side lengths but vary by one in the
     * length of the third side should be of the same type and the area of the latter should be
     * slightly larger.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest15(int a, int b, int c) {
        // Select two sides to hold constant and adjust the third
        assumeTrue(a < b && b == c); // Select a as the adjustable side, ensuring b and c are
                                     // constant

        /* Get original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Slightly increase the length of side 'a' */
        int adjustedA = a + 1;

        /* Get the output for the adjusted triangle */
        Pair<Integer, Double> adjustedOutput = triangle_square(adjustedA, b, c);

        /* Check that the triangle type remains the same (scalen or isosceles) */
        assertEquals(originalOutput.getKey(), adjustedOutput.getKey());

        /* Check that the area of the adjusted triangle is larger */
        assertTrue(adjustedOutput.getValue() > originalOutput.getValue());
    }

    /**
     * Metamorphic Relation 16: For a scalene triangle, increasing the length of the shortest side
     * should result in a larger area but maintain the triangle's scalene property.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest16(int a, int b, int c) {
        // Prepare to identify the shortest side of the triangle.
        assumeTrue(a != b && b != c && c != a); // Ensure it's a scalene triangle.

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        // Calculate the new side lengths by increasing the shortest side's length by 1.
        // This assumes that no side's length exceeds the max value by more than 1.
        int shortestSideValue = Math.min(a, Math.min(b, c));
        int newA = (shortestSideValue == a) ? a + 1 : a;
        int newB = (shortestSideValue == b) ? b + 1 : b;
        int newC = (shortestSideValue == c) ? c + 1 : c;

        /* Calculate the new output */
        Pair<Integer, Double> newOutput = triangle_square(newA, newB, newC);

        /* Verify that the triangle remains scalene */
        assertEquals(Integer.valueOf(1), newOutput.getKey());

        /* Verify that the area has increased */
        assertTrue(newOutput.getValue() > originalOutput.getValue());
    }

    /**
     * Metamorphic Relation 17: For a right-angled triangle (not included in the initial program,
     * assuming it could be type 4), if one of the sides adjacent to the right angle is increased,
     * the area should increase, while the triangle remains a right-angled one.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest17(int a, int b, int c) {
        // Assuming a, b, c form a right-angled triangle with 'c' being the hypotenuse
        // (not implemented in the original program)
        assumeTrue((a * a + b * b == c * c) && c > a && c > b);

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Increase length of side 'a' */
        int newA = a + 1;

        /* Calculate the new output */
        Pair<Integer, Double> newOutputForA = triangle_square(newA, b, c);

        // Assert the triangle is still right-angled and the area has increased.
        assertEquals(Integer.valueOf(4), newOutputForA.getKey());
        assertTrue(newOutputForA.getValue() > originalOutput.getValue());

        /* Increase length of side 'b' */
        int newB = b + 1;

        /* Calculate the new output */
        Pair<Integer, Double> newOutputForB = triangle_square(a, newB, c);

        // Assert the triangle is still right-angled and the area has increased.
        assertEquals(Integer.valueOf(4), newOutputForB.getKey());
        assertTrue(newOutputForB.getValue() > originalOutput.getValue());
    }

    /**
     * Metamorphic Relation 18: Scaling down the side lengths of a valid triangle by a common factor
     * that results in integer lengths should produce a similar triangle with the same type and a
     * proportionally smaller area.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest18(int a, int b, int c) {
        // Common factor for scaling down, making sure the sides still stay as integers
        int k = 2;
        assumeTrue(a % k == 0 && b % k == 0 && c % k == 0);

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Scale down the lengths */
        int scaledA = a / k;
        int scaledB = b / k;
        int scaledC = c / k;

        /* Get the scaled output */
        Pair<Integer, Double> scaledOutput = triangle_square(scaledA, scaledB, scaledC);

        /* Verify the triangle type remains the same */
        assertEquals(originalOutput.getKey(), scaledOutput.getKey());

        /* Verify the area is reduced by a factor of k^2 */
        assertEquals(originalOutput.getValue() / (k * k), scaledOutput.getValue(), 1e-6);
    }

    /**
     * Metamorphic Relation 19: Changing the order of the sides of any triangle does not change the
     * type or the area of the triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest19(int a, int b, int c) {
        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Permute sides and get the new outputs */
        Pair<Integer, Double> output1 = triangle_square(b, c, a);
        Pair<Integer, Double> output2 = triangle_square(c, a, b);

        /* Verify that the type and area remain the same */
        assertEquals(originalOutput.getKey(), output1.getKey());
        assertEquals(originalOutput.getValue(), output1.getValue(), 1e-6);

        assertEquals(originalOutput.getKey(), output2.getKey());
        assertEquals(originalOutput.getValue(), output2.getValue(), 1e-6);
    }

    /**
     * Metamorphic Relation 20: Reducing each side of an equilateral triangle by the same positive
     * integer length should result in an equilateral triangle with a smaller area.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest20(int a) {
        assumeTrue(a > 3); // Ensure each side can be reduced
        int reduction = 1; // The length to be reduced from each side

        /* Get the original output assuming it's an equilateral triangle */
        Pair<Integer, Double> originalOutput = triangle_square(a, a, a);

        /* Reduce sides by the same length and get the new output */
        Pair<Integer, Double> newOutput =
                triangle_square(a - reduction, a - reduction, a - reduction);

        /* Verify that the triangle remains equilateral */
        assertEquals(Integer.valueOf(3), newOutput.getKey());

        /* Verify that the area is smaller */
        assertTrue(newOutput.getValue() < originalOutput.getValue());
    }

    /**
     * Metamorphic Relation 21: If each side of a valid triangle is multiplied by a negative scalar,
     * the result should not form a valid triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest21(int a, int b, int c) {
        int scalar = -1;

        /* Multiply each side by a negative scalar */
        int negativeA = a * scalar;
        int negativeB = b * scalar;
        int negativeC = c * scalar;

        /* Get the output for the negative sides */
        Pair<Integer, Double> outputNegative = triangle_square(negativeA, negativeB, negativeC);

        /* Verify that the output indicates it's not a valid triangle */
        assertEquals(Integer.valueOf(0), outputNegative.getKey());
        assertEquals(Double.valueOf(0.0), outputNegative.getValue());
    }

    /**
     * Metamorphic Relation 22: If each side of an equilateral triangle is incremented by different
     * positive integers, the triangle should change to a scalene triangle, and the area should be
     * different.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest22(int a) {
        assumeTrue(a > 1); // Make sure we have room to increment without overflowing

        /* Get the output assuming it's an equilateral triangle */
        Pair<Integer, Double> originalOutput = triangle_square(a, a, a);

        /* Increment each side by different amounts */
        Pair<Integer, Double> outputIncremented = triangle_square(a + 1, a + 2, a + 3);

        /* Verify that the type changes to scalene */
        assertEquals(Integer.valueOf(1), outputIncremented.getKey());

        /* Verify that the area is different */
        assertNotEquals(originalOutput.getValue(), outputIncremented.getValue());
    }

    /**
     * Metamorphic Relation 23: If one side of an isosceles triangle is increased by a fraction of
     * the other two equal sides, it remains an isosceles triangle with a changed area.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest23(int a, int b, int c) { // Fixed
        assumeTrue((a == b && b != c) || (a == c && a != b) || (b == c & b != a)); // Ensure it's an
                                                                                   // isosceles
                                                                                   // triangle

        /* Get original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Increase unique side by a fraction of the equal sides */
        int newA = (a != b) ? a : a + b / 10;
        int newB = (b != c) ? b : b + a / 10;
        int newC = c; // one of 'a' or 'b' is the unique side in an isosceles triangle

        /* Get new output */
        Pair<Integer, Double> outputIncreased = triangle_square(newA, newB, newC);

        /* Verify that type remains isosceles */
        assertEquals(Integer.valueOf(2), outputIncreased.getKey());

        /* Verify area has changed */
        assertNotEquals(originalOutput.getValue(), outputIncreased.getValue());
    }

    /**
     * Metamorphic Relation 24: Multiplication of the side lengths of a valid triangle by a scalar
     * k, then division by the same scalar k, should yield a triangle of the same type and area.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest24(int a, int b, int c) {
        int k = 3; // The scalar by which to multiply and then divide the side lengths

        assumeTrue(a <= Integer.MAX_VALUE / k && b <= Integer.MAX_VALUE / k
                && c <= Integer.MAX_VALUE / k);

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Multiply then divide each side length by k */
        int scaledA = (a * k) / k;
        int scaledB = (b * k) / k;
        int scaledC = (c * k) / k;

        /* Get the scaled output */
        Pair<Integer, Double> scaledOutput = triangle_square(scaledA, scaledB, scaledC);

        /* Verify that the triangle type and area remains the same */
        assertEquals(originalOutput.getKey(), scaledOutput.getKey());
        assertEquals(originalOutput.getValue(), scaledOutput.getValue(), 1e-6);
    }

    /**
     * Metamorphic Relation 25: Scaling the sides of any triangle such that the largest side becomes
     * equal to the sum of the other two should result in a degenerate triangle (type 0).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest25(int a, int b, int c) {
        // Determine the largest side
        int largestSide = Math.max(a, Math.max(b, c));

        // Calculate scale factors that would ensure the largest side becomes the sum of
        // the other two
        int scaleA = (largestSide == a) ? 1 : largestSide - ((largestSide == b) ? c : b);
        int scaleB = (largestSide == b) ? 1 : largestSide - ((largestSide == c) ? a : c);
        int scaleC = (largestSide == c) ? 1 : largestSide - ((largestSide == a) ? b : a);

        // Avoid zero scaling which does not change triangle properties
        assumeTrue(scaleA > 0 && scaleB > 0 && scaleC > 0);

        /* Get the output for the degenerate case */
        Pair<Integer, Double> degenerateOutput =
                triangle_square(a + scaleA, b + scaleB, c + scaleC);

        /* Verify that a degenerate triangle is identified */
        assertEquals(Integer.valueOf(0), degenerateOutput.getKey());
    }

    /**
     * Metamorphic Relation 26: Exchanging two equal sides of an isosceles triangle should result in
     * an identical triangle type and area.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest26(int a, int b, int c) {
        assumeTrue((a == b && a != c) || (a == c && a != b) || (b == c && a != b)); // Isosceles
                                                                                    // triangles

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        // Compute the new side lengths by exchanging the equal sides
        int newA = (a == b) ? c : a;
        int newB = (a == b) ? c : b;
        int newC = (a == b) ? b : ((b == c) ? a : c);

        /* Get the output for the exchanged sides */
        Pair<Integer, Double> exchangedOutput = triangle_square(newA, newB, newC);

        /* Verify that the exchanged triangle has the same type and area */
        assertEquals(originalOutput.getKey(), exchangedOutput.getKey());
        assertEquals(originalOutput.getValue(), exchangedOutput.getValue(), 1e-6);
    }

    /**
     * Metamorphic Relation 27: For an isosceles triangle, increasing both of the equal sides by a
     * positive integer 'k' should result in a triangle with a larger area but of the same type.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest27(int a, int b, int c) { // Fixed
        b = a;
        assumeTrue(a + b > c && a + c > b && b + c > a); // Ensure it's a valid triangle

        int k = 2; // The positive integer to increase the equal sides
        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        // Determine which sides to increase
        int newA = a;
        int newB = b;
        int newC = c;
        if (a == b) {
            newA += k;
            newB += k;
        } else if (a == c) {
            newA += k;
            newC += k;
        } else if (b == c) {
            newB += k;
            newC += k;
        }

        /* Get the output for the modified sides */
        Pair<Integer, Double> increasedOutput = triangle_square(newA, newB, newC);

        /* Verify that the modified triangle has the same type and a larger area */
        assertEquals(originalOutput.getKey(), increasedOutput.getKey());
        assertTrue(increasedOutput.getValue() > originalOutput.getValue());
    }

    /**
     * Metamorphic Relation 28: Multiplying two sides of a scalene triangle by the same scalar 'k'
     * should result in a triangle with an altered area but should maintain it as a scalene
     * triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest28(int a, int b, int c) {
        assumeTrue(a != b && b != c && c != a); // Scalene triangle
        int k = 2; // Scalar 'k' to multiply two sides of the triangle

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Multiply only 'a' and 'b' by scalar 'k' */
        int newA = a * k;
        int newB = b * k;

        /* Get the output for the modified sides */
        Pair<Integer, Double> modifiedOutput = triangle_square(newA, newB, c);

        /* Verify that the modified triangle is still scalene and has a changed area */
        assertEquals(Integer.valueOf(1), modifiedOutput.getKey());
        assertNotEquals(originalOutput.getValue(), modifiedOutput.getValue());
    }

    /**
     * Metamorphic Relation 29: Swapping the lengths of the two equal sides of an isosceles triangle
     * with each other does not change the triangle’s type or area.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest29(int a, int b, int c) { // Fixed
        b = a;

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        int newA, newB, newC;
        if (a == b) {
            // Swap a and b
            newA = b;
            newB = a;
            newC = c;
        } else if (a == c) {
            // Swap a and c
            newA = c;
            newB = b;
            newC = a;
        } else { // b == c
            // Swap b and c
            newA = a;
            newB = c;
            newC = b;
        }
        Pair<Integer, Double> swappedOutput = triangle_square(newA, newB, newC);

        /* Verify the type and area remain the same after swapping equal sides */
        assertEquals(originalOutput.getKey(), swappedOutput.getKey());
        assertEquals(originalOutput.getValue(), swappedOutput.getValue(), 1e-6);
    }

    /**
     * Metamorphic Relation 30: If a valid triangle has its longest side replaced with a length that
     * is one less than the sum of the two shorter sides, it should still be a valid triangle,
     * though not equilateral.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest30(int a, int b, int c) {
        // Identify the longest side of the triangle to replace
        int longest = Math.max(a, Math.max(b, c));
        int sumOfOthers = (longest == a) ? (b + c) : (longest == b) ? (a + c) : (a + b);

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        // Avoid modifying the equilateral triangle, and ensure that new lengths stay
        // positive
        assumeTrue(sumOfOthers - longest > 1);

        // Replace the longest side length to be sum of other two sides minus one
        int newA = (longest == a) ? (sumOfOthers - 1) : a;
        int newB = (longest == b) ? (sumOfOthers - 1) : b;
        int newC = (longest == c) ? (sumOfOthers - 1) : c;

        /* Get the new output */
        Pair<Integer, Double> newOutput = triangle_square(newA, newB, newC);

        /* Verify that the triangle is still valid and not equilateral */
        assertNotEquals(Integer.valueOf(0), newOutput.getKey());
        assertNotEquals(Integer.valueOf(3), newOutput.getKey());
        assertTrue(newOutput.getValue() != originalOutput.getValue());
    }

    /**
     * Metamorphic Relation 31: Reducing the longest side of a valid non-equilateral triangle by a
     * small amount should not change the type of the triangle but should decrease the area.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest31(int a, int b, int c) {
        // Identify the longest side
        int maxLength = Math.max(a, Math.max(b, c));
        assumeTrue((maxLength == a && a > b && a > c) || (maxLength == b && b > a && b > c)
                || (maxLength == c && c > a && c > b)); // Ensure it's not equilateral

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        // Reduce the longest side by 1
        int newMaxLength = maxLength - 1;
        int newA = (maxLength == a) ? newMaxLength : a;
        int newB = (maxLength == b) ? newMaxLength : b;
        int newC = (maxLength == c) ? newMaxLength : c;

        /* Get the output for the modified triangle */
        Pair<Integer, Double> modifiedOutput = triangle_square(newA, newB, newC);

        /* Verify that the triangle type remains and area has decreased */
        assertEquals(originalOutput.getKey(), modifiedOutput.getKey());
        assertTrue(modifiedOutput.getValue() < originalOutput.getValue());
    }

    /**
     * Metamorphic Relation 32: For any valid triangle, swapping the lengths of the two shorter
     * sides should not affect the type of the triangle and should yield either the same area or a
     * different area for non-equilateral triangles.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest32(int a, int b, int c) { // Fixed
        assumeTrue(a + b > c && a + c > b && b + c > a); // Ensure it's a valid triangle
        assumeTrue(a != b && b != c && c != a);

        // Identify the lengths of the shorter sides
        int minSide = Math.min(a, Math.min(b, c));
        int midSide =
                (minSide == a) ? Math.min(b, c) : (minSide == b) ? Math.min(a, c) : Math.min(a, b);
        assumeTrue(minSide != midSide); // Ensures we are not working with an equilateral triangle

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        // Swap the lengths of the two shorter sides
        int newA = (minSide == a) ? midSide : (midSide == a) ? minSide : a;
        int newB = (minSide == b) ? midSide : (midSide == b) ? minSide : b;
        int newC = (minSide == c) ? midSide : (midSide == c) ? minSide : c;

        /* Get the output for the modified triangle */
        Pair<Integer, Double> modifiedOutput = triangle_square(newA, newB, newC);

        /* Verify that the triangle type remains the same */
        assertEquals(originalOutput.getKey(), modifiedOutput.getKey());
        // Area might be the same or different for non-equilateral triangles
    }

    /**
     * Metamorphic Relation 33: Altering an equilateral triangle such that two sides remain equal,
     * but the third side is changed, will result in either a scalene or an isosceles triangle with
     * a different area.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest33(int a) {
        assumeTrue(a > 1); // Ensure the side length allows modification without hitting zero or
                           // negative

        /* Get the original output assuming equilateral triangle */
        Pair<Integer, Double> originalOutput = triangle_square(a, a, a);

        /* Decrease one side by 1 to break the equilateral nature */
        Pair<Integer, Double> newOutput = triangle_square(a, a, a - 1);

        /* Verify the triangle is no longer equilateral */
        assertNotEquals(Integer.valueOf(3), newOutput.getKey());

        /* Verify the area has changed */
        assertNotEquals(originalOutput.getValue(), newOutput.getValue());
    }

    /**
     * Metamorphic Relation 34: If a valid triangle is an isosceles, and we increment the two equal
     * sides while decrementing the base by twice the increment, the result should be a scalene
     * triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest34(int a, int b, int c) {
        // Find two equal sides in an isosceles triangle, ensure it is not also
        // equilateral or degenerate
        assumeTrue((a == b && b != c) || (a == c && c != b) || (b == c && c != a));

        /* Get original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        // Increment value for isosceles sides, calculate how much to decrement the base
        int increment = 1;
        int decrement = 2 * increment;

        // Make sure the base side remains positive and the triangle stays valid
        int base = (a == b) ? c : (a == c) ? b : a;
        assumeTrue(base > decrement && base - decrement < a + b - base);

        // Modify sides
        int newA = (a == b || a == c) ? a + increment : a - decrement;
        int newB = (b == a || b == c) ? b + increment : b - decrement;
        int newC = (c == a || c == b) ? c + increment : c - decrement;

        /* Calculate follow-up output */
        Pair<Integer, Double> followUpOutput = triangle_square(newA, newB, newC);

        /* Verify that the triangle has changed its type to scalene */
        assertEquals(Integer.valueOf(1), followUpOutput.getKey());
        // Verify that the area is different
        assertNotEquals(originalOutput.getValue(), followUpOutput.getValue());
    }

    /**
     * Metamorphic Relation 35: Adding the same non-zero integer to all sides of an equilateral
     * triangle should result in an isosceles triangle with a larger area.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest35(int a) {
        assumeTrue(a > 1); // Ensure positive side length

        int addend = 1; // Value to add to each side

        /* Get original output assuming equilateral triangle */
        Pair<Integer, Double> originalOutput = triangle_square(a, a, a);

        // Modify the triangle
        a += addend;
        int b = a - 1;

        /* Get follow-up output for the altered triangle */
        Pair<Integer, Double> alteredOutput = triangle_square(a, a, b);

        /* Verify that the altered triangle does not remain equilateral */
        assertNotEquals(Integer.valueOf(3), alteredOutput.getKey());

        /* Verify that the area is larger */
        assertTrue(alteredOutput.getValue() > originalOutput.getValue());
    }

    /**
     * Metamorphic Relation 36: Tripling only one side of a scalene triangle results in a
     * non-triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest36(int a, int b, int c) {
        // Identify if it's scalene
        assumeTrue(a != b && b != c && c != a);

        /* Compute and attempt to form a triangle by tripling side 'a' */
        Pair<Integer, Double> tripleAOutput = triangle_square(a * 3, b, c);

        /* Verify that it does not form a valid triangle */
        assertEquals(Integer.valueOf(0), tripleAOutput.getKey());
        assertEquals(Double.valueOf(0.0), tripleAOutput.getValue());
    }

    /**
     * Metamorphic Relation 37: Multiplying the smallest side of an equilateral triangle by 2 and
     * the other two sides by 1 should change it to an isosceles triangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest37(int a) {
        a = 50;

        assumeTrue(a > 0); // Ensure positive side length
        /* Get original output assuming equilateral triangle */
        Pair<Integer, Double> originalOutput = triangle_square(a, a, a);

        // Modify one side of the triangle
        a *= 2;

        /* Get the new output for altered triangle */
        Pair<Integer, Double> modifiedOutput = triangle_square(a, a / 2, a / 2);

        /* Verify that the triangle's type has changed */
        assertNotEquals(Integer.valueOf(3), modifiedOutput.getKey());
        // Note: We can also verify that the modifiedOutput key should be
        // Integer.valueOf(2)

        /* Verify that the area has changed */
        assertNotEquals(originalOutput.getValue(), modifiedOutput.getValue());
    }

    /**
     * Metamorphic Relation 38: Swapping the two smaller sides of a scalene right triangle should
     * not alter its right triangle property. This assumes that 'c' is the hypotenuse and the
     * program correctly identifies a right triangle with a unique type number (e.g., 4).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest38(int a, int b, int c) {
        // Check if it's a right triangle with c as the hypotenuse. Replace 4 with
        // actual right-triangle type number if different.
        assumeTrue(a * a + b * b == c * c);

        /* Get the original output assuming right triangle */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        // Swap the two smaller sides
        Pair<Integer, Double> swappedOutput = triangle_square(b, a, c);

        /* Verify that the triangle still qualifies as a right triangle */
        assertEquals(Integer.valueOf(4), swappedOutput.getKey());

        /* Verify that the area remains the same */
        assertEquals(originalOutput.getValue(), swappedOutput.getValue(), 1e-6);
    }

    /**
     * Metamorphic Relation 39: Multiplying the sides of a valid triangle by the same positive
     * integer 'k' should increase the area without changing the type, even if the order of the
     * sides is permuted.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest39(int a, int b, int c) {
        int k = 2; // Scalar 'k' to multiply sides of the triangle

        assumeTrue(a <= Integer.MAX_VALUE / k && b <= Integer.MAX_VALUE / k
                && c <= Integer.MAX_VALUE / k);

        /* Get the original output */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Multiply sides by 'k' and permute */
        Pair<Integer, Double> outputPermutedMultiplied = triangle_square(b * k, c * k, a * k);

        /* Verify that the type stays the same */
        assertEquals(originalOutput.getKey(), outputPermutedMultiplied.getKey());

        /* Verify that the area is larger */
        assertEquals(k * k * originalOutput.getValue(), outputPermutedMultiplied.getValue(), 1e-6);
    }

    /**
     * Metamorphic Relation 40: For a valid triangle, creating a new triangle by subtracting a
     * unique positive integer less than or equal to the smallest side from each side, the area will
     * decrease, but the type of the triangle will remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void metamorphicTest40(int a, int b, int c) {
        int minSide = Math.min(Math.min(a, b), c);
        int subtractionAmount = minSide / 2;

        /* First get the output for the original triangle */
        Pair<Integer, Double> originalOutput = triangle_square(a, b, c);

        /* Calculate new side lengths */
        int newA = a - subtractionAmount;
        int newB = b - subtractionAmount;
        int newC = c - subtractionAmount;

        /* Verify that triangle inequality still holds */
        assumeTrue(newA < newB + newC && newB < newA + newC && newC < newA + newB);

        /* Get the new output */
        Pair<Integer, Double> newOutput = triangle_square(newA, newB, newC);

        /* Check that the type has not changed */
        assertEquals(originalOutput.getKey(), newOutput.getKey());

        /* Check that the area has decreased */
        assertTrue(newOutput.getValue() < originalOutput.getValue());
    }

    public static Stream<Arguments> testcaseProvider() throws IOException {
        return testcaseGenerator.generate(1000);
    }
}
