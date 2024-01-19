package test;

import static org.junit.jupiter.api.Assertions.assertArrayEquals;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import src.Maxsub;

public class MaxsubTestGPT3D5 {
    /**
     * Metamorphic Relation 1: Scaling input array by a constant, the output should
     * be scaled by the same constant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        int scalingFactor = 2; // Can be any positive integer
        for (int num : arr) {
            follow_arr.add(num * scalingFactor);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out * scalingFactor, follow_out);
    }

    /**
     * Metamorphic Relation 2: Adding a constant to all elements of input array, the
     * output should have the same constant added to it.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        int constantToAdd = 5; // Can be any integer
        for (int num : arr) {
            follow_arr.add(num + constantToAdd);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out + constantToAdd, follow_out);
    }

    /**
     * Metamorphic Relation 3: Removing elements from input array, the output should
     * be less than or equal to the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        int numToRemove = 2; // Can be any non-negative integer less than arr.size()
        for (int i = numToRemove; i < arr.size(); i++) {
            follow_arr.add(arr.get(i));
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertTrue(follow_out <= source_out);
    }

    /**
     * Metamorphic Relation 4: Reversing the order of elements in the input array,
     * the output should be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        for (int i = arr.size() - 1; i >= 0; i--) {
            follow_arr.add(arr.get(i));
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 5: Adding the input array to itself, the output should
     * be greater than or equal to the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>(arr);
        follow_arr.addAll(arr);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 6: Shuffling the input array, the output should be the
     * same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>(arr);
        Collections.shuffle(follow_arr);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 7: Applying a mathematical transformation (e.g.,
     * squaring) to all elements of the input array, the output should be
     * transformed accordingly.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        for (int num : arr) {
            follow_arr.add(num * num);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out * source_out, follow_out);
    }

    /**
     * Metamorphic Relation 8: Appending a constant to the input array, the output
     * should be greater than or equal to the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>(arr);
        int constantToAppend = 10; // Can be any integer
        follow_arr.add(constantToAppend);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 9: Removing all negative elements from the input array,
     * the output should be greater than or equal to the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (int num : arr) {
            if (num >= 0) {
                follow_arr.add(num);
            }
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 10: Multiplying consecutive elements of the input array
     * and using the resulting array as input, the output should be greater than or
     * equal to the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (int i = 0; i < arr.size() - 1; i++) {
            follow_arr.add(arr.get(i) * arr.get(i + 1));
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 11: Replacing all elements in the input array with their
     * absolute values, the output should be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (int num : arr) {
            follow_arr.add(Math.abs(num));
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 12: Appending the reverse of the input array to itself,
     * the output should be greater than or equal to the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        Collections.reverse(follow_arr);
        follow_arr.addAll(arr);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 13: Negating all elements in the input array, the output
     * should remain unchanged (as the largest sum won't change by simply negating
     * the numbers).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (int num : arr) {
            follow_arr.add(-num);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 14: Reverse the order of inputs and outputs for the same
     * array, the original output should be the reverse of the follow-up output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Get follow-up output */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Reverse the input and output order */
        Collections.reverse(follow_arr);
        int[] follow_result = new int[follow_arr.size()];
        for (int i = follow_arr.size() - 1; i >= 0; i--) {
            follow_result[follow_arr.size() - 1 - i] = follow_arr.get(i);
        }

        /* Verification */
        assertArrayEquals(
                Arrays.stream(follow_result).toArray(),
                Arrays.stream(String.valueOf(source_out).split("")).mapToInt(Integer::parseInt).toArray());
    }

    /**
     * Metamorphic Relation 15: Adding the reverse of the input array to itself, the
     * output should remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        Collections.reverse(follow_arr);
        for (int i = 0; i < arr.size(); i++) {
            follow_arr.set(i, follow_arr.get(i) + arr.get(i));
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 16: Appending the input array to itself and removing the
     * last element, the output should remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        follow_arr.addAll(arr.subList(0, arr.size() - 1));

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 17: Replacing an element in the input array with a
     * larger value, the output should increase or remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        int indexToReplace = 0; // Choose any valid index within the array
        int largerValue = 100; // A larger value to replace the element
        follow_arr.set(indexToReplace, largerValue);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 18: Replacing a subarray with another subarray that has
     * a larger sum, the output should be greater than or equal to the original
     * output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        int startIndex = 0; // Choose any valid start index within the array
        int endIndex = 3; // Choose any valid end index within the array, must be greater than startIndex
        ArrayList<Integer> subArrToReplace = new ArrayList<>(Arrays.asList(10, 20, 30)); // Subarray with a larger sum
        follow_arr.subList(startIndex, endIndex).clear();
        follow_arr.addAll(startIndex, subArrToReplace);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 19: Multiplying all elements in the input array by -1
     * and adding a constant, the output should remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = arr.stream().map(i -> -i).collect(Collectors.toCollection(ArrayList::new));

        /* Choose any constant */
        int constant = 5;
        for (int i = 0; i < follow_arr.size(); i++) {
            follow_arr.set(i, follow_arr.get(i) + constant);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 20: Applying a rotation operation to the input array,
     * the output should remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        int rotationDistance = 2; // Choose any valid value for rotation
        List<Integer> follow_arr = new ArrayList<>(Collections.nCopies(arr.size(), 0));
        for (int i = 0; i < arr.size(); i++) {
            int newPosition = (i + rotationDistance) % arr.size();
            follow_arr.set(newPosition, arr.get(i));
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub((ArrayList<Integer>)follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 21: Mirroring the input array, the output should remain
     * unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        Collections.reverse(follow_arr);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 22: Replacing all odd elements in the input array with
     * zeros, the output should remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (int num : arr) {
            if (num % 2 != 0) {
                follow_arr.add(0);
            } else {
                follow_arr.add(num);
            }
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 23: Replacing adjacent elements in the input array with
     * their average value, the output should remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        for (int i = 0; i < arr.size() - 1; i++) {
            int avg = (arr.get(i) + arr.get(i + 1)) / 2;
            follow_arr.set(i, avg);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 24: Doubling the frequency of each element in the array,
     * the output should double.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (int num : arr) {
            follow_arr.add(num);
            follow_arr.add(num);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out * 2, follow_out);
    }

    /**
     * Metamorphic Relation 25: Incrementing all elements in the input array by 1,
     * the output should increase by the size of the array.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = arr.stream()
                .map(i -> i + 1)
                .collect(Collectors.toCollection(ArrayList::new));

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out + arr.size(), follow_out);
    }

    /**
     * Metamorphic Relation 26: Sorting the input array in ascending order, the
     * output should remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        Collections.sort(follow_arr);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 27: Reversing the order of the elements, then adding 1
     * to all values in the input array; the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        Collections.reverse(follow_arr);
        for (int i = 0; i < follow_arr.size(); i++) {
            follow_arr.set(i, follow_arr.get(i) + 1);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 28: Concatenating the input array with itself, the
     * output should be greater than the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        follow_arr.addAll(arr);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 29: Adding a new element to the start and end of the
     * input array, the output should increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        follow_arr.add(0, 0); // Add at the start
        follow_arr.add(arr.size() + 1); // Add at the end

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertTrue(follow_out > source_out);
    }

    /**
     * Metamorphic Relation 30: Multiplying the largest element in the array by a
     * value greater than 1, the output should also increase by the same factor.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        int maxVal = Collections.max(arr);
        int multiplier = 3; // Can be any value greater than 1
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        int maxIndex = follow_arr.indexOf(maxVal);
        follow_arr.set(maxIndex, maxVal * multiplier);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out * multiplier, follow_out);
    }

    /**
     * Metamorphic Relation 31: Removing the first and last elements of the input
     * array, the output should remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        if (arr.size() <= 2) {
            // If the array has less than 2 elements, skip the transformation
            return;
        }
        ArrayList<Integer> follow_arr = new ArrayList<>(arr.subList(1, arr.size() - 1));

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 32: Replacing each element in the input array with the
     * square of the element, the output should remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = arr.stream()
                .map(i -> i * i)
                .collect(Collectors.toCollection(ArrayList::new));

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 33: Replacing each element in the input array with its
     * negation, the output should remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = arr.stream()
                .map(i -> -i)
                .collect(Collectors.toCollection(ArrayList::new));

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 34: Constructing a new array with elements shuffled from
     * the original array, the output should remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        Collections.shuffle(arr);
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 35: Remove the first and last elements of the array and
     * sort the remaining elements in ascending order. As a result, the output
     * should remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(ArrayList<Integer> arr) {
        if (arr.size() > 2) {
            /* Get source output */
            int source_out = Maxsub.max_sub(arr);

            /* Construct follow-up input */
            ArrayList<Integer> follow_arr = new ArrayList<>(arr);
            follow_arr.remove(0);
            follow_arr.remove(follow_arr.size() - 1);
            Collections.sort(follow_arr);

            /* Get follow-up output */
            int follow_out = Maxsub.max_sub(follow_arr);

            /* Verification */
            assertEquals(source_out, follow_out);
        }
    }

    /**
     * Metamorphic Relation 36: Replace every element in the input array with a
     * negative value of the element. The output should remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = arr.stream()
                .map(i -> -i)
                .collect(Collectors.toCollection(ArrayList::new));

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 37: Replace every element in the input array with its
     * absolute value. The output should ideally remain unchanged for an algorithm
     * that searches for the maximum sum of a subarray.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = arr.stream()
                .map(Math::abs)
                .collect(Collectors.toCollection(ArrayList::new));

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 38: Reverse the order of elements in the input array and
     * then reverse the sign of each element. The output should ideally remain
     * unchanged for an algorithm that searches for the maximum sum of a subarray.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = arr.stream()
                .map(i -> -i)
                .collect(Collectors.toCollection(ArrayList::new));
        Collections.reverse(follow_arr);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 39: Appending a constant value to all elements of the
     * input array and reversing the array, the output should remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        int constantToAdd = 10; // Can be any integer
        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (int num : arr) {
            follow_arr.add(num + constantToAdd);
        }
        Collections.reverse(follow_arr);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 40: Replacing every element in the input array with the
     * negative absolute value of the element, the output should remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = arr.stream()
                .map(i -> -Math.abs(i))
                .collect(Collectors.toCollection(ArrayList::new));

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    public static Stream<Arguments> testcaseProvider() throws Exception {
        return testcaseGenerator.generate(1000);
    }
}
