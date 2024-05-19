package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.Random;
import java.util.stream.Stream;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import src.Maxsub;

public class MaxsubTestGPT4 {
    /**
     * Metamorphic Relation 2: Scaling input array by a positive constant factor k, the output
     * should be scaled by the same factor k.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(ArrayList<Integer> arr) {
        final int k = 2; // Can be any positive constant
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        for (int num : arr) {
            follow_arr.add(num * k);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out * k, follow_out);
    }

    /**
     * Metamorphic Relation 3: If a constant c is added to each element of the input array, the
     * output sum should increase by c times the length of the maximum subarray found.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(ArrayList<Integer> arr) {
        final int c = 5;
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Sub-logic to find the length of the maximum subarray */
        int len_max_sub = 0;
        int cnt = 0;
        int ans = Integer.MIN_VALUE;
        for (int i = 0; i < arr.size(); ++i) {
            cnt += arr.get(i);
            if (cnt < 0) {
                cnt = 0;
            } else {
                len_max_sub = Math.max(len_max_sub, i); // Capture the length at current iteration
            }
            ans = Math.max(ans, cnt);
        }

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        for (int num : arr) {
            follow_arr.add(num + c);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out + len_max_sub * c, follow_out);
    }

    /**
     * Metamorphic Relation 4: Inverting the sign of each element in the input array should not
     * change the absolute value of the maximum subarray sum if the original array has at least one
     * positive element.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(ArrayList<Integer> arr) {
        /* Check if at least one positive element exists */
        if (arr.stream().noneMatch(num -> num > 0)) {
            return;
        }

        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        for (int num : arr) {
            follow_arr.add(-num);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(Math.abs(source_out), Math.abs(follow_out));
    }

    /**
     * Metamorphic Relation 5: Concatenating the input array with itself, the output should be no
     * less than the original output and at most twice the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        follow_arr.addAll(arr);
        follow_arr.addAll(arr); // Concatenation

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertTrue(follow_out >= source_out && follow_out <= source_out * 2);
    }

    /**
     * Metamorphic Relation 6: Shuffling the elements of the input array should not change the
     * maximum subarray sum, as the order of numbers within a subarray does not affect the sum.
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
     * Metamorphic Relation 7: Removing a subarray with a non-positive sum from the input array
     * should not decrease the maximum subarray sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Find a subarray with a non-positive sum, if possible */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>(arr);
        int start = -1, end = -1;
        int sum = 0;
        for (int i = 0; i < arr.size(); i++) {
            sum += arr.get(i);
            if (sum <= 0) {
                start = (start == -1) ? i : start;
                end = i;
                sum = 0;
            }
        }

        /* Remove the subarray with non-positive sum if found */
        if (start != -1 && end != -1) {
            for (int i = start; i <= end; i++) {
                follow_arr.remove(start);
            }
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 8: Adding a subarray with zero sum before or after the input array
     * should not change the maximum subarray sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input by adding zeros before the array */
        ArrayList<Integer> follow_arr_prepend = new ArrayList<Integer>();
        follow_arr_prepend.add(0);
        follow_arr_prepend.add(0);
        follow_arr_prepend.addAll(arr);

        /* Get follow-up output for the prepended array */
        int follow_out_prepended = Maxsub.max_sub(follow_arr_prepend);

        /* Construct follow-up input by adding zeros after the array */
        ArrayList<Integer> follow_arr_append = new ArrayList<Integer>(arr);
        follow_arr_append.add(0);
        follow_arr_append.add(0);

        /* Get follow-up output for the appended array */
        int follow_out_appended = Maxsub.max_sub(follow_arr_append);

        /* Verification */
        assertEquals(source_out, follow_out_prepended);
        assertEquals(source_out, follow_out_appended);
    }

    /**
     * Metamorphic Relation 9: Replacing any subarray with a positive sum with a single element
     * equal to the sum of that subarray should not change the maximum subarray sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>(arr);

        /* Initialize variables */
        int max_here = 0, max_so_far = Integer.MIN_VALUE;
        int start = 0, end = 0, s = 0;

        /* Apply Kadane's algorithm to find the maximum subarray */
        for (int i = 0; i < arr.size(); i++) {
            max_here += arr.get(i);
            if (max_here > max_so_far) {
                max_so_far = max_here;
                start = s;
                end = i;
            }
            if (max_here < 0) {
                max_here = 0;
                s = i + 1;
            }
        }

        /* Replace the found subarray */
        for (int i = end; i >= start; i--) {
            follow_arr.remove(i);
        }
        follow_arr.add(start, max_so_far);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 10: For any non-empty subarray, inserting an element with value equal to
     * the negative sum of the subarray within it should result in the same maximum subarray sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input by adding a negated subarray sum within the array */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>(arr);
        int subarraySum =
                follow_arr.subList(1, follow_arr.size()).stream().mapToInt(Integer::intValue).sum();
        follow_arr.add(1, -subarraySum);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 11: Duplicating the input array's elements should not change the maximum
     * subarray sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input by duplicating the array's elements */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        for (int num : arr) {
            follow_arr.add(num);
            follow_arr.add(num);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 12: Multiplying each element in the input array by -1 and then adding a
     * large positive constant (greater than the absolute value of the highest negative sum) to each
     * element should result in an output greater than or equal to the large positive constant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(ArrayList<Integer> arr) {
        final int largePositiveConstant = 1000; // Should be greater than the absolute value of the
                                                // largest negative sum in arr

        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        for (int num : arr) {
            follow_arr.add(-1 * num + largePositiveConstant);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertTrue(follow_out >= largePositiveConstant);
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 13: Removing a single occurrence of the smallest number from the array
     * should not increase the maximum subarray sum if the smallest number is non-positive.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(ArrayList<Integer> arr) {
        int smallestNum = arr.stream().min(Integer::compareTo).orElse(Integer.MAX_VALUE);
        if (smallestNum > 0) {
            // If the smallest number is positive, this MR is not applicable.
            return;
        }

        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input by removing one occurrence of the smallest number */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>(arr);
        follow_arr.remove(Integer.valueOf(smallestNum));

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertTrue(follow_out <= source_out);
    }

    /**
     * Metamorphic Relation 14: Inverting an input array with only non-positive integers should not
     * change the output which should be equal to the largest element of the array, since the
     * maximum subarray contains only one element in this case.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(ArrayList<Integer> arr) {
        if (arr.stream().anyMatch(num -> num > 0)) {
            // If any number is positive, this MR is not applicable.
            return;
        }

        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input by inverting signs of input array */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        for (int num : arr) {
            follow_arr.add(-num);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /*
         * The expected output should be the inverted sign of the smallest (the largest number when
         * negated) number in the original array
         */
        int expectedOut =
                arr.isEmpty() ? 0 : -arr.stream().max(Integer::compareTo).orElse(Integer.MIN_VALUE);

        /* Verification */
        assertEquals(expectedOut, follow_out);
        assertEquals(expectedOut, source_out);
    }

    /**
     * Metamorphic Relation 15: Inserting any integer k at the beginning of the input array should
     * not cause the maximum subarray sum to decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(ArrayList<Integer> arr) {
        final int k = 3; // Can be any integer

        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input by inserting k at the beginning of the array */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        follow_arr.add(k);
        follow_arr.addAll(arr);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 16: Inserting a new negative element in the input array should not
     * increase the maximum subarray sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Insert a new negative element */
        arr.add(-1);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(arr);

        /* Verification */
        assertTrue(follow_out <= source_out);
    }

    /**
     * Metamorphic Relation 17: Appending an array of non-positive integers that adds up to a
     * non-positive sum should not change the maximum subarray sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct an array of non-positive integers with a non-positive sum */
        ArrayList<Integer> nonPositiveArr = new ArrayList<>(Arrays.asList(-5, -1, 0, -3));

        /* Append the non-positive array to the original array */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        follow_arr.addAll(nonPositiveArr);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 18: Replacing any zero-value elements with a positive or negative
     * integer should not decrease the maximum subarray sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(ArrayList<Integer> arr) {
        int source_out = Maxsub.max_sub(arr);

        // Check if array has zeros and replace the first occurrence with k (can be any int)
        int k = 1;
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        if (follow_arr.contains(0)) {
            follow_arr.set(follow_arr.indexOf(0), k);
        }

        int follow_out = Maxsub.max_sub(follow_arr);

        // Since zero does not contribute to a sum, replacing it with any number shouldn't decrease
        // the sum
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 19: Inserting a subarray with zero sum in between the input array should
     * not change the maximum subarray sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct a subarray with zero sum */
        ArrayList<Integer> zeroSumSubArray = new ArrayList<>(Arrays.asList(2, -2, 3, -3));

        /* Insert the zero sum subarray at a random position in the original array */
        int position = new Random().nextInt(arr.size() + 1); // position can range from 0 to
                                                             // arr.size()
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        follow_arr.addAll(position, zeroSumSubArray);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 20: If all elements of the input array are multiplied by -1, the output
     * should be the negative of the maximum subarray sum of the original array if the array
     * contains both positive and negative numbers.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(ArrayList<Integer> arr) {
        // This MR is applicable if the array contains both positive and negative numbers.
        if (!arr.stream().anyMatch(num -> num > 0) || !arr.stream().anyMatch(num -> num < 0)) {
            return;
        }

        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input by multiplying each element by -1 */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (int num : arr) {
            follow_arr.add(num * -1);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Inverting all the elements should make it the highest negative sum */
        assertEquals(-source_out, follow_out);
    }

    /**
     * Metamorphic Relation 21: Removing a subarray with a positive sum that is not part of the
     * maximum subarray should not change the maximum subarray sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        // Using Kadane's algorithm again to find the starting and ending indexes
        // of the maximum subarray.
        int maxSoFar = 0;
        int maxEndingHere = 0;
        int start = 0, end = 0;
        int s = 0;

        for (int i = 0; i < arr.size(); i++) {
            maxEndingHere += arr.get(i);

            if (maxSoFar < maxEndingHere) {
                maxSoFar = maxEndingHere;
                start = s;
                end = i;
            }

            if (maxEndingHere < 0) {
                maxEndingHere = 0;
                s = i + 1;
            }
        }

        /*
         * Check if the maximum subarray is at the start or the end, if so, no elements can be
         * removed
         */
        if (start == 0 || end == arr.size() - 1) {
            return;
        }

        /* Remove a positive subarray that is not part of the maximum subarray */
        int removeFrom = end + 1;
        int removeSum = 0;
        while (removeFrom < arr.size() && (removeSum += arr.get(removeFrom)) > 0) {
            removeFrom++;
        }

        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        for (int i = removeFrom; i < arr.size() && arr.get(i) >= 0; i++) {
            follow_arr.remove(removeFrom);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 22: Splitting the input array into two halves and summing the max
     * subarrays of each half shouldn't exceed the original maximum subarray sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Split array into two halves */
        ArrayList<Integer> firstHalf = new ArrayList<>(arr.subList(0, arr.size() / 2));
        ArrayList<Integer> secondHalf = new ArrayList<>(arr.subList(arr.size() / 2, arr.size()));

        /* Get maximum subarrays sum of both halves */
        int firstHalfOut = Maxsub.max_sub(firstHalf);
        int secondHalfOut = Maxsub.max_sub(secondHalf);

        /* Sum of maximums of both halves */
        int sumHalvesOut = firstHalfOut + secondHalfOut;

        /* Verification */
        assertTrue(sumHalvesOut <= source_out);
    }

    /**
     * Metamorphic Relation 23: Replacing any subarray with a negative sum in the original array by
     * a zero shouldn't change the maximum subarray sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Find a negative sum subarray and replace it with zero */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        int sum = 0;
        int startNegSubarray = -1;

        for (int i = 0; i < follow_arr.size(); ++i) {
            sum += follow_arr.get(i);

            if (sum < 0) {
                startNegSubarray = (startNegSubarray == -1) ? i : startNegSubarray;
            }

            if ((sum >= 0 || i == follow_arr.size() - 1) && startNegSubarray != -1) {
                // Replace the negative sum subarray with a zero.
                for (int j = startNegSubarray; j <= i; ++j) {
                    follow_arr.set(j, 0);
                }
                startNegSubarray = -1;
            }

            if (sum >= 0) {
                sum = 0;
            }
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 24: For any constant k, multiplying all elements by k should result in
     * the maximum subarray sum being multiplied by k.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(ArrayList<Integer> arr) {
        int k = 5; // Could be any non-zero constant, using 5 as an example.

        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        for (int num : arr) {
            follow_arr.add(k * num);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(k * source_out, follow_out);
    }

    /**
     * Metamorphic Relation 25: Inserting any number of zeroes between the elements of the array
     * should not change the maximum subarray sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input by inserting zeroes between the elements */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        for (int num : arr) {
            follow_arr.add(num);
            follow_arr.add(0); // Inserting a zero
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 26: Adding the maximum subarray sum found in the original array as a new
     * element at the beginning or end should increase the new maximum subarray sum by that amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input by adding source_out at the beginning */
        ArrayList<Integer> follow_arr_beginning = new ArrayList<Integer>(arr);
        follow_arr_beginning.add(0, source_out);

        /* Get follow-up output for the new array */
        int follow_out_beginning = Maxsub.max_sub(follow_arr_beginning);

        /* Construct follow-up input by adding source_out at the end */
        ArrayList<Integer> follow_arr_end = new ArrayList<Integer>(arr);
        follow_arr_end.add(source_out);

        /* Get follow-up output for the new array */
        int follow_out_end = Maxsub.max_sub(follow_arr_end);

        /* The new max should be source_out (old max) plus the added value (source_out itself) */
        int expected_new_max = source_out + source_out;

        /* Verification */
        assertEquals(expected_new_max, follow_out_beginning);
        assertEquals(expected_new_max, follow_out_end);
    }

    /**
     * Metamorphic Relation 27: Inserting a large negative value that exceeds the largest sum in the
     * array should result in either the same maximum subarray sum or a new max which is one of the
     * positive elements.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(ArrayList<Integer> arr) {
        int source_out = Maxsub.max_sub(arr);

        /* Insert a large negative value */
        int largeNegativeValue = -1 * (source_out + 1000); // Assures the value exceeds any positive
                                                           // sum in arr.
        arr.add(largeNegativeValue);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(arr);

        /* Verification */
        if (arr.size() == 1 || source_out == 0) {
            /* It is expected that the largest single positive element would become the new max */
            int expected_max = arr.stream().filter(num -> num > 0).max(Integer::compare).orElse(0);
            assertEquals(expected_max, follow_out);
        } else {
            assertEquals(source_out, follow_out);
        }
    }

    /**
     * Metamorphic Relation 28: Dividing the entire array by a constant factor c where c > 1 should
     * not change the relative difference between the maximum subarray sums before and after the
     * division.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(ArrayList<Integer> arr) {
        int source_out = Maxsub.max_sub(arr);

        final int c = 2; // Constant factor for division, c > 1

        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (int num : arr) {
            follow_arr.add(num / c);
        }

        int follow_out = Maxsub.max_sub(follow_arr);

        /* The expected maximum would also be divided by c */
        assertEquals(source_out / c, follow_out);
    }

    /**
     * Metamorphic Relation 29: Excluding the maximum single element from the array if it does not
     * belong to the maximum subarray should not change the maximum subarray sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(ArrayList<Integer> arr) {
        /* Finding the maximum single element in array */
        int maxElement = arr.stream().mapToInt(Integer::intValue).max().orElse(0);
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        /* Remove first occurrence of maximum single element which might increase the max sum */
        follow_arr.remove(Integer.valueOf(maxElement));

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        if (source_out != maxElement) {
            assertEquals(source_out, follow_out);
        }
    }

    /**
     * Metamorphic Relation 30: Repeating the entire input array in reverse order and appending it
     * should not decrease the maximum subarray sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Reverse the input array */
        ArrayList<Integer> reversedArr = new ArrayList<>(arr);
        Collections.reverse(reversedArr);

        /* Concatenate the original and reversed arrays */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        follow_arr.addAll(reversedArr);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 31: Sorting the array should not change the maximum subarray sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input by sorting the array */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        Collections.sort(follow_arr);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 32: If the array has only non-negative elements, then summing all the
     * elements should give the maximum subarray sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(ArrayList<Integer> arr) {
        if (!arr.isEmpty() && arr.stream().allMatch(num -> num >= 0)) {
            int sum_of_elements = arr.stream().mapToInt(Integer::intValue).sum();
            int source_out = Maxsub.max_sub(arr);
            assertEquals(sum_of_elements, source_out);
        }
    }

    /**
     * Metamorphic Relation 33: For an array consisting of a single repeat element value, the
     * maximum subarray sum should equal that value multiplied by the array's length.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(ArrayList<Integer> arr) {
        if (!arr.isEmpty() && new HashSet<>(arr).size() == 1) {
            int repeated_value = arr.get(0);
            int array_length = arr.size();
            int expected_subarray_sum = repeated_value * array_length;
            int source_out = Maxsub.max_sub(arr);
            assertEquals(expected_subarray_sum, source_out);
        }
    }

    /**
     * Metamorphic Relation 34: Replacing each element of the array by its square should result in a
     * larger or equal maximum subarray sum if all elements are non-negative.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(ArrayList<Integer> arr) {
        int source_out = Maxsub.max_sub(arr);

        if (arr.stream().allMatch(num -> num >= 0)) {
            /* Create follow-up array with each element squared */
            ArrayList<Integer> follow_arr = new ArrayList<>();
            for (Integer element : arr) {
                follow_arr.add(element * element);
            }

            int follow_out = Maxsub.max_sub(follow_arr);

            /*
             * Verification: Squaring can only increase or retain the sum if all elements are
             * non-negative.
             */
            assertTrue(follow_out >= source_out);
        }
    }

    /**
     * Metamorphic Relation 35: If there is a single element in the array and it is negative, the
     * maximum subarray sum should be that element since we have to pick at least one number.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(ArrayList<Integer> arr) {
        if (arr.size() == 1 && arr.get(0) < 0) {
            int source_out = Maxsub.max_sub(arr);
            assertEquals(arr.get(0), source_out);
        }
    }

    /**
     * Metamorphic Relation 36: Extracting a contiguous subarray which includes the maximum subarray
     * should not change the output maximum subarray sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(ArrayList<Integer> arr) {
        if (arr.isEmpty())
            return;

        // Define the limits of the extraction, ensuring they encompass the middle of the array
        int start = 0;
        int end = arr.size() - 1;

        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct a follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr.subList(start, end + 1)); // Inclusive
                                                                                      // end

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 37: Concatenating a non-negative fixed integer 'p' to each element in
     * the array should produce a maximum subarray sum greater or equal to the source output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(ArrayList<Integer> arr) {
        final int p = 5;

        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input by adding 'p' to each element */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (Integer num : arr) {
            follow_arr.add(num + p);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 38: Concatenating an array to itself multiple times should result in a
     * maximum subarray sum that is a multiple of the original sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input by concatenating the array to itself */
        int concatenations = 3;
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        for (int i = 1; i < concatenations; i++) {
            follow_arr.addAll(arr);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertTrue(follow_out >= source_out && follow_out <= source_out * concatenations);
    }

    /**
     * Metamorphic Relation 39: For an array consisting of alternating negative and non-negative
     * numbers, the maximum subarray sum must be at least equal to the largest positive element.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(ArrayList<Integer> arr) {
        /* Verify the alternating pattern */
        if (!isAlternatingPattern(arr)) {
            return;
        }

        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Determine the largest non-negative number */
        int largestNonNegative = arr.stream().filter(n -> n >= 0).max(Integer::compareTo).orElse(0);

        /* Verification */
        assertTrue(source_out >= largestNonNegative);
    }

    private boolean isAlternatingPattern(ArrayList<Integer> arr) {
        boolean isNegative = arr.get(0) < 0;
        for (int i = 1; i < arr.size(); i++) {
            isNegative = !isNegative;
            if ((arr.get(i) < 0) != isNegative) {
                return false;
            }
        }
        return true;
    }

    /**
     * Metamorphic Relation 40: For an array where every element is the inverse of the next one,
     * except the last one, the maximum subarray sum should be equal to the first or last element,
     * whichever is non-negative.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(ArrayList<Integer> arr) {
        /* Verify inverse pattern (every element is the inverse of the next one) */
        boolean isValidPattern = true;
        for (int i = 0; i < arr.size() - 1; i++) {
            if (arr.get(i) != -arr.get(i + 1)) {
                isValidPattern = false;
                break;
            }
        }

        if (!isValidPattern || arr.isEmpty()) {
            return;
        }

        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Expected output should be the first or last element if it's non-negative */
        int expectedOut = arr.get(0) >= 0 ? arr.get(0) : arr.get(arr.size() - 1);

        /* Verification */
        assertEquals(expectedOut, source_out);
    }

    /**
     * Metamorphic Relation 41: Swapping any two elements in the array should not change the maximum
     * subarray sum if neither element is part of the maximum subarray.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test41(ArrayList<Integer> arr) {
        // Find the maximum subarray bounds
        int[] maxSubarrayBounds = findMaxSubarrayBounds(arr);
        if (maxSubarrayBounds == null)
            return; // In case we cannot determine bounds or array is empty

        int maxStart = maxSubarrayBounds[0];
        int maxEnd = maxSubarrayBounds[1];

        // Swap two elements outside the maximum subarray bounds
        int swapIndex1 = maxStart > 0 ? maxStart - 1 : arr.size() - 1;
        int swapIndex2 = maxEnd < arr.size() - 1 ? maxEnd + 1 : 0;

        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        int temp = follow_arr.get(swapIndex1);
        follow_arr.set(swapIndex1, follow_arr.get(swapIndex2));
        follow_arr.set(swapIndex2, temp);

        /* Get source output */
        int source_out = Maxsub.max_sub(arr);
        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    private int[] findMaxSubarrayBounds(ArrayList<Integer> arr) {
        if (arr.isEmpty())
            return null;

        int maxSum = Integer.MIN_VALUE;
        int currentSum = 0;
        int start = 0;
        int end = 0;
        int tempStart = 0;
        for (int i = 0; i < arr.size(); i++) {
            currentSum += arr.get(i);

            if (currentSum > maxSum) {
                maxSum = currentSum;
                start = tempStart;
                end = i;
            }

            if (currentSum < 0) {
                currentSum = 0;
                tempStart = i + 1;
            }
        }
        return new int[] {start, end};
    }

    /**
     * Metamorphic Relation 42: Concatenating two identical arrays should result in a maximum
     * subarray sum that is at least the sum of two individual max sums and at most twice the max
     * sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test42(ArrayList<Integer> arr) {
        int singleMaxSum = Maxsub.max_sub(arr);

        // Concatenate array with itself
        ArrayList<Integer> dupArr = new ArrayList<>(arr);
        dupArr.addAll(arr);

        int doubleMaxSum = Maxsub.max_sub(dupArr);

        // Concatenated sum should be between single and double the original max sum
        int doubleSingleMaxSum = 2 * singleMaxSum;
        assertTrue(doubleMaxSum >= singleMaxSum && doubleMaxSum <= doubleSingleMaxSum);
    }

    /**
     * Metamorphic Relation 43: If the input array is the maximum subarray itself, then removing any
     * single element should result in a maximum subarray sum which is at least the largest element
     * of the array when it contains all positive integers, or at most the sum without the removed
     * element.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test43(ArrayList<Integer> arr) {
        if (arr.isEmpty() || !arr.stream().allMatch(n -> n > 0)) {
            return;
        }

        int arrSum = arr.stream().mapToInt(Integer::intValue).sum();
        int maxElement = arr.stream().max(Integer::compareTo).orElse(0);
        int source_out = Maxsub.max_sub(arr);

        arr.remove(0);

        // After removing one element
        int follow_out = Maxsub.max_sub(arr);

        assertTrue(follow_out >= maxElement && follow_out <= source_out && source_out == arrSum);
    }

    /**
     * Metamorphic Relation 44: For each non-empty subarray, adding its sum to the end of the array
     * and computing the maximum subarray sum should result in a larger or equal sum compared to the
     * original array sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test44(ArrayList<Integer> arr) {
        // Skip if the array is empty
        if (arr.isEmpty())
            return;

        int source_out = Maxsub.max_sub(arr);

        // Calculate the sum of existing elements
        int sum_of_elements = arr.stream().mapToInt(Integer::intValue).sum();

        // Append the sum to the end of the array
        ArrayList<Integer> extendedArr = new ArrayList<>(arr);
        extendedArr.add(sum_of_elements);

        int extended_out = Maxsub.max_sub(extendedArr);

        assertTrue(extended_out >= source_out);
    }

    /**
     * Metamorphic Relation 45: Shuffle the array excluding its maximum subarray should not change
     * the result provided that the maximum subarray is not adjacent to the array boundaries.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test45(ArrayList<Integer> arr) {
        // Determine the bounds of the maximum subarray
        int[] maxSubarrayBounds = findMaxSubarrayBounds(arr);
        if (maxSubarrayBounds == null || maxSubarrayBounds[0] == 0
                || maxSubarrayBounds[1] == arr.size() - 1) {
            // The maximum subarray at the boundaries cannot be shuffled independently.
            return;
        }

        ArrayList<Integer> source_arr = new ArrayList<>(arr);
        int maxSum = Maxsub.max_sub(source_arr);
        int start = maxSubarrayBounds[0];
        int end = maxSubarrayBounds[1];

        // Extract the maximum subarray
        ArrayList<Integer> maxSubarray = new ArrayList<>(arr.subList(start, end + 1));

        // Remove max subarray from the original array
        for (int i = start; i <= end; i++) {
            arr.remove(start);
        }

        // Shuffle the remaining elements of the array
        Collections.shuffle(arr);

        // Reinsert the maximum subarray at its original position
        arr.addAll(start, maxSubarray);

        int follow_out = Maxsub.max_sub(arr);

        assertEquals(maxSum, follow_out);
    }

    public static Stream<Arguments> testcaseProvider() throws Exception {
        return testcaseGenerator.generate(1000);
    }
}
