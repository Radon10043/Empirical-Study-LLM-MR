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

public class MaxsubTestGPT3D5New {
    /**
     * Metamorphic Relation 1: Scaling the input array by a constant factor, the output should change by the same constant factor.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        follow_arr.addAll(arr);
        int factor = 2; // Example scaling factor
        for (int i = 0; i < follow_arr.size(); i++) {
            follow_arr.set(i, follow_arr.get(i) * factor);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out * factor, follow_out);
    }

    /**
     * Metamorphic Relation 2: Adding a constant to each element of the input array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        for (int num : arr) {
            follow_arr.add(num + 10); // Adding a constant value, 10 in this case
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 3: Reordering the elements of the input array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        follow_arr.addAll(arr);
        Collections.shuffle(follow_arr); // Randomly shuffle the elements

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 4: Multiplying each element of the input array by a constant factor, the output should change by the corresponding factor.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        for (int num : arr) {
            follow_arr.add(num * 2); // Multiplying each element by a constant factor, 2 in this case
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out * 2, follow_out);
    }

    /**
     * Metamorphic Relation 5: Replacing all elements of the input array with their absolute values, the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        for (int num : arr) {
            follow_arr.add(Math.abs(num)); // Replacing with absolute values
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 6: Appending an element to the end of the input array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        follow_arr.addAll(arr);
        follow_arr.add(100); // Appending an element

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 7: Removing the first element of the input array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        follow_arr.addAll(arr);
        follow_arr.remove(0); // Removing the first element

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 8: Repeating the input array n times should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        int n = 3; // Example repetition factor
        for (int i = 0; i < n; i++) {
            follow_arr.addAll(arr);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 9: Removing duplicate elements from the input array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>(new HashSet<>(arr)); // Remove duplicates

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 10: Multiplying all elements of the input array by -1 should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (int num : arr) {
            follow_arr.add(-1 * num); // Multiply by -1
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 11: Shifting all elements of the input array to the right by a fixed number of positions should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        int shiftBy = 3; // Example shift factor
        for (int i = 0; i < arr.size(); i++) {
            follow_arr.add(arr.get((i - shiftBy + arr.size()) % arr.size())); // Shift elements to the right
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 12: Replacing all occurrences of a number in the input array with another number should not change the output if the number being replaced does not affect the maximum subarray sum.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        int replaceThis = 10; // Example number to be replaced
        int replaceWith = 5; // Example number to replace with
        for (int i = 0; i < arr.size(); i++) {
            if (follow_arr.get(i) == replaceThis) {
                follow_arr.set(i, replaceWith); // Replace the number
            }
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 13: Replacing the input array with its prefix sum array should not change the output. 
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        int prefixSum = 0;
        for (int num : arr) {
            prefixSum += num;
            follow_arr.add(prefixSum); // Construct prefix sum array
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 14: Reversing the input array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(ArrayList<Integer> arr) {
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
     * Metamorphic Relation 15: Appending the reverse of the input array to itself should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        ArrayList<Integer> reverseArr = new ArrayList<>(arr);
        Collections.reverse(reverseArr);
        follow_arr.addAll(reverseArr);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 16: Replacing all elements of the input array with their consecutive differences should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (int i = 0; i < arr.size() - 1; i++) {
            follow_arr.add(arr.get(i + 1) - arr.get(i)); // Consecutive differences
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 17: Taking the absolute differences between consecutive elements of the input array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (int i = 0; i < arr.size() - 1; i++) {
            follow_arr.add(Math.abs(arr.get(i + 1) - arr.get(i))); // Absolute differences
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 18: Adding a constant to each element of the input array and then taking the absolute differences between consecutive elements should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        int constant = 5; // Example constant value
        for (int num : arr) {
            follow_arr.add(Math.abs(num + constant)); // Add constant and take absolute differences
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 19: Sorting the input array in ascending order should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        Collections.sort(follow_arr); // Sort in ascending order

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 20: Taking the square of each element of the input array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (int num : arr) {
            follow_arr.add(num * num); // Square each element
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 21: Multiplying each element of the input array by -1 and adding a constant should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        int constant = 10; // Example constant value
        for (int num : arr) {
            follow_arr.add(-1 * num + constant); // Multiply by -1 and add constant
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 22: Constructing a new array with only the even (or odd) elements of the input array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (int num : arr) {
            if (num % 2 == 0) { // Select even elements
                follow_arr.add(num);
            }
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 23: Multiplying the input array by a scalar value and then taking the absolute differences between consecutive elements should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        int scalar = 2; // Example scalar value
        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (int i = 0; i < arr.size() - 1; i++) {
            follow_arr.add(Math.abs(scalar * arr.get(i + 1) - scalar * arr.get(i))); // Multiply by scalar and take absolute differences
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 24: Reversing the order of the input array and then applying a prefix sum transformation should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> reversed_arr = new ArrayList<>(arr);
        Collections.reverse(reversed_arr); // Reverse the input array

        ArrayList<Integer> follow_arr = new ArrayList<>();
        int prefixSum = 0;
        for (int num : reversed_arr) {
            prefixSum += num;
            follow_arr.add(prefixSum); // Construct prefix sum array

        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 25: Applying a square root transformation to each element of the input array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Double> follow_arr = new ArrayList<>();
        for (int num : arr) {
            follow_arr.add(Math.sqrt(num)); // Apply square root transformation
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr.stream().map(Double::intValue).collect(Collectors.toCollection(ArrayList::new)));

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 26: Sorting the input array in descending order followed by taking the prefix sum transformation should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> sortedDesc = new ArrayList<>(arr);
        Collections.sort(sortedDesc, Collections.reverseOrder()); // Sort in descending order

        ArrayList<Integer> follow_arr = new ArrayList<>();
        int prefixSum = 0;
        for (int num : sortedDesc) {
            prefixSum += num;
            follow_arr.add(prefixSum); // Construct prefix sum array

        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 27: Multiplying each element of the input array by a positive constant should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        int constant = 2; // Example constant value
        for (int num : arr) {
            follow_arr.add(num * constant); // Multiply each element by a positive constant
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 28: Constructing a new array with every alternate element of the input array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (int i = 0; i < arr.size(); i += 2) {
            follow_arr.add(arr.get(i)); // Select every alternate element
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 29: Modifying the input array to only contain prime numbers should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (int num : arr) {
            if (isPrime(num)) {
                follow_arr.add(num); // Add only prime numbers to the follow-up input
            }
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    private boolean isPrime(int num) {
        if (num <= 1) {
            return false;
        }
        for (int i = 2; i <= Math.sqrt(num); i++) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }

    /**
     * Metamorphic Relation 30: Allowing duplicates to be removed from the input array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        Set<Integer> follow_arr = new HashSet<>(arr); // Use a set to remove duplicates

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(new ArrayList<>(follow_arr));

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 31: Reversing the input array and then sorting it in ascending order should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        Collections.reverse(follow_arr); // Reverse the input array
        Collections.sort(follow_arr); // Sort in ascending order

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 32: Multiplying the input array by -1 and taking its absolute values should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (int num : arr) {
            follow_arr.add(Math.abs(-1 * num)); // Multiply each element by -1 and take absolute value
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 33: Replacing the input array with the cumulative product array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        int cumulativeProduct = 1;
        for (int num : arr) {
            cumulativeProduct *= num;
            follow_arr.add(cumulativeProduct); // Construct cumulative product array
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 34: Shifting all elements of the input array to the left by a fixed number of positions and then taking the absolute differences between consecutive elements should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        int shiftBy = 3; // Example shift factor
        for (int i = 0; i < arr.size() - shiftBy; i++) {
            follow_arr.add(Math.abs(arr.get(i) - arr.get(i + shiftBy))); // Take absolute differences after shifting
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 35: Constructing a new array with all non-negative elements of the input array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (int num : arr) {
            if (num >= 0) {
                follow_arr.add(num); // Select only non-negative elements
            }
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 36: Constructing a new array by combining the prefix sum and suffix sum of the input array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        int prefixSum = 0;
        int suffixSum = 0;
        for (int i = 0; i < arr.size(); i++) {
            prefixSum += arr.get(i);
            suffixSum += arr.get(arr.size() - i - 1); // Calculate prefix and suffix sums
            follow_arr.add(prefixSum + suffixSum);
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 37: Randomly shuffling the input array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        Collections.shuffle(follow_arr);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 38: Double reversing the input array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>(arr);
        Collections.reverse(follow_arr);
        Collections.reverse(follow_arr);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 39: Splitting the input array into two subarrays and concatenating them in reverse order should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        int splitIndex = arr.size() / 2;
        ArrayList<Integer> follow_arr = new ArrayList<>(arr.subList(splitIndex, arr.size()));
        follow_arr.addAll(arr.subList(0, splitIndex)); // Concatenate in reverse order

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 40: Replacing all elements of the input array with their squares and doubles should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<>();
        for (int num : arr) {
            follow_arr.add(num * num * 2); // Replace with square and double of each number
        }

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    public static Stream<Arguments> testcaseProvider() throws Exception {
        return testcaseGenerator.generate(1000);
    }
}