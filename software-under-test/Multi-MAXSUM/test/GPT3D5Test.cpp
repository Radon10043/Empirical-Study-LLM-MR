#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class MultiMAXSUMParamTest : public ::testing::TestWithParam<MultiMAXSUMInput> {};

/**
 * @brief Metamorphic Relation 2: Reversing the order of the array, the output should be the same as the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR2) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 3: Multiplying all elements of the array by a positive scalar, the follow-up output should be `scalar * source_output`.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR3) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    int scalar = 2; // Example scalar value
    transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [scalar](int i) { return i * scalar; });

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, scalar * source_out);
}

/**
 * @brief Metamorphic Relation 4: Adding an offset to each element of the array, the follow-up output should remain the same as the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR4) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int offset = 5; // Example offset value
    for (int i = 0; i < source_vec.size(); i++) {
        source_vec[i] += offset;
    }
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(input.vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 5: Using a subset of the array, the follow-up output should be less than or equal to the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR5) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(input.vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = vector<int>(source_vec.begin(), source_vec.begin() + source_vec.size() / 2); // Example using half of the array

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 6: Sorting the array in ascending order, the output should remain the same as the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR6) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Sort the source vector */
    sort(source_vec.begin(), source_vec.end());

    /* Get follow-up output */
    int follow_out = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 7: Removing duplicate elements from the array, the output should remain the same as the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR7) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Remove duplicate elements from source vector */
    sort(source_vec.begin(), source_vec.end());
    source_vec.erase(unique(source_vec.begin(), source_vec.end()), source_vec.end());

    /* Get follow-up output */
    int follow_out = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 8: Replacing all negative elements in the array with zeros, the follow-up output should be less than or equal to the source
 * output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR8) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Replace negative elements with zeros */
    for (auto &num : source_vec) {
        if (num < 0) {
            num = 0;
        }
    }

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Get follow-up output */
    int follow_out = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 9: Adding a constant value to the subarray, the sum should increase by the product of the constant value and the subarray length.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR9) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;
    int constant = 10; // Example constant value to add

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Modify the subarray by adding the constant value */
    for (int i = 0; i < source_vec.size(); i++) {
        source_vec[i] += constant;
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out + source_vec.size() * constant);
}

/**
 * @brief Metamorphic Relation 10: Scaling the entire array by a factor, the output should scale accordingly.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR10) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int scalingFactor = 2; // Example scaling factor
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Scale the entire array */
    for (int &num : source_vec) {
        num *= scalingFactor;
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out * scalingFactor);
}

/**
 * @brief Metamorphic Relation 11: Shifting all elements of the array to the right by a fixed offset, the output should remain the same as the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR11) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int shiftOffset = 2; // Example shift offset
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Apply right shift to the entire array */
    rotate(source_vec.rbegin(), source_vec.rbegin() + shiftOffset, source_vec.rend());

    /* Get follow-up output */
    int follow_out = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
#include <cmath>

/**
 * @brief Metamorphic Relation 12: Replacing all even elements in the array with their square roots, the output should remain the same as the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR12) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Replace even elements with their square roots */
    for (int &num : source_vec) {
        if (num % 2 == 0) {
            num = static_cast<int>(sqrt(num)); // Using integer square root for simplicity
        }
    }

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Get follow-up output */
    int follow_out = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 13: Reversing the sign of all elements in the array, the output should remain the same as the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR13) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Reverse the sign of all elements */
    for (int &num : source_vec) {
        num = -num;
    }

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Get follow-up output */
    int follow_out = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
#include <numeric>

/**
 * @brief Metamorphic Relation 14: Slicing the array into two subarrays, summing the elements of the subarrays, and then summing the subarray sums, the result
 * should remain the same as the original sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR14) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    int half_size = source_vec.size() / 2;

    /* Sum of original array */
    int original_sum = accumulate(source_vec.begin(), source_vec.end(), 0);

    /* Calculate the sum of the two subarrays */
    int first_half_sum = accumulate(source_vec.begin(), source_vec.begin() + half_size, 0);
    int second_half_sum = accumulate(source_vec.begin() + half_size, source_vec.end(), 0);

    /* Calculate the sum of the subarray sums */
    int subarray_sum_sum = first_half_sum + second_half_sum;

    /* Verification */
    EXPECT_EQ(subarray_sum_sum, original_sum);
}

/**
 * @brief Metamorphic Relation 15: Computing the maximum subarray sum and then adding a value to each element, the new maximum subarray sum should increase by
 * the product of the value and the subarray length.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR15) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;
    int additional_value = 5; // Example additional value

    /* Source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Calculate the maximum subarray sum */
    int max_sum = multi_maxsum(source_vec, source_m);

    /* Add a value to each element */
    for (int i = 0; i < source_vec.size(); i++) {
        source_vec[i] += additional_value;
    }

    /* Calculate the new maximum subarray sum */
    int new_max_sum = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(new_max_sum, max_sum + (additional_value * source_m));
}

/**
 * @brief Metamorphic Relation 16: Sorting the array in descending order, the output should remain the same as the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR16) {
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Sort the source vector in descending order */
    sort(source_vec.rbegin(), source_vec.rend());

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Get follow-up output */
    int follow_out = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 17: Replacing all odd elements in the array with zeros, the follow-up output should be less than or equal to the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR17) {
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Replace odd elements with zeros */
    for (int &num : source_vec) {
        if (num % 2 != 0) {
            num = 0;
        }
    }

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Get follow-up output */
    int follow_out = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 18: Dividing each element of the array by a positive scalar, the output should remain the same as the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR18) {
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int scalar = 2; // Example scalar value
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Divide each element by the scalar */
    for (int &num : source_vec) {
        num /= scalar;
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 19: Applying a windowing function, such as a moving average, to the array, the output should change accordingly.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR19) {
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int window_size = 3; // Example window size
    int source_m = input.m;

    /* Fix by radon */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Apply a moving average window function to the array */
    for (int i = 0; i <= source_vec.size() - window_size; ++i) {
        int sum = 0;
        for (int j = i; j < i + window_size; ++j) {
            sum += source_vec[j];
        }
        source_vec[i] = sum / window_size;
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(source_vec, source_m);

    /* Verification */
#if INVALID
    EXPECT_NE(follow_out, input.out); // Ensure that the output has changed
#else
    EXPECT_NE(follow_out, source_out); // Ensure that the output has changed
#endif
}

/**
 * @brief Metamorphic Relation 20: Reversing the array and then reversing the subarray sums, the result should be the same as the original sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR20) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Fix by Radon */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Reverse the source array */
    reverse(source_vec.begin(), source_vec.end());

    /* Calculate the sum of the subarrays */
    vector<int> prefix_sum(source_vec.size() + 1, 0);
    for (int i = 1; i <= source_vec.size(); i++) {
        prefix_sum[i] = prefix_sum[i - 1] + source_vec[i - 1];
    }

    int original_sum = 0;
    for (int i = 0; i <= source_vec.size() - source_m; i++) {
        int sum = prefix_sum[i + source_m] - prefix_sum[i];
        original_sum += sum;
    }

    /* Verification */
#if INVALID
    EXPECT_EQ(original_sum, input.out);
#else
    EXPECT_EQ(original_sum, source_out);
#endif
}

/**
 * @brief Metamorphic Relation 21: Appending a copy of the array to itself and then finding the maximum subarray sum, the result should be at least double the
 * original maximum subarray sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR21) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Append a copy of the source array to itself */
    vector<int> extended_vec(source_vec);
    extended_vec.insert(extended_vec.end(), source_vec.begin(), source_vec.end());

    /* Get the original maximum subarray sum */
    int original_max_sum = multi_maxsum(source_vec, source_m);

    /* Get the maximum subarray sum of the extended array */
    int extended_max_sum = multi_maxsum(extended_vec, source_m);

    /* Verification */
    EXPECT_GE(extended_max_sum, original_max_sum * 2);
}

/**
 * @brief Metamorphic Relation 22: Multiplying each element of the array by a positive scalar, the output should scale accordingly.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR22) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int scalar = 3; // Example scalar value
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Multiply each element by the scalar */
    for (int &num : source_vec) {
        num *= scalar;
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out * scalar);
}

/**
 * @brief Metamorphic Relation 23: Reversing the array and then finding the maximum subarray sum, the result should be the same as the original maximum subarray
 * sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR23) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Reverse the source array */
    reverse(source_vec.begin(), source_vec.end());

    /* Get the original maximum subarray sum */
    int original_max_sum = multi_maxsum(input.vec, source_m);

    /* Get the maximum subarray sum of the reversed array */
    int reversed_max_sum = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(reversed_max_sum, original_max_sum);
}

/**
 * @brief Metamorphic Relation 24: Swapping the positions of two elements in the array, the output should remain the same as the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR24) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    if (source_vec.size() >= 2) {
        /* Swap the positions of the first two elements */
        swap(source_vec[0], source_vec[1]);

        /* Get source output */
        int source_out = multi_maxsum(input.vec, source_m);

        /* Get follow-up output */
        int follow_out = multi_maxsum(source_vec, source_m);

        /* Verification */
        EXPECT_EQ(follow_out, source_out);
    }
}

/**
 * @brief Metamorphic Relation 25: Applying a custom transformation function to the array, the maximum subarray sum should have a specific relationship with the
 * original maximum subarray sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR25) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Define a transformation function (e.g., squaring each element) */
    auto transformFunction = [](int x) -> int { return x * x; };

    /* Apply the transformation function to each element in the array */
    transform(source_vec.begin(), source_vec.end(), source_vec.begin(), transformFunction);

    /* Get the original maximum subarray sum */
    int original_max_sum = multi_maxsum(input.vec, source_m);

    /* Get the maximum subarray sum of the transformed array */
    int transformed_max_sum = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(transformed_max_sum, original_max_sum); // Example: verify they are equal, or use a specific relationship as necessary
}

/**
 * @brief Metamorphic Relation 26: Multiplying each element of the array by a constant and then adding another constant, the output should maintain the same
 * relationship with the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR26) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;
    int multiplier = 2; // Example constant for multiplication
    int addition = 3;   // Example constant for addition

    /* Apply the transformation to each element in the array */
    for (int &num : source_vec) {
        num = num * multiplier + addition;
    }

    /* Get the original maximum subarray sum */
    int original_max_sum = multi_maxsum(input.vec, source_m);

    /* Get the maximum subarray sum of the transformed array */
    int transformed_max_sum = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(transformed_max_sum, multiplier * original_max_sum + addition);
}

/**
 * @brief Metamorphic Relation 27: Replacing each element with its absolute value, the maximum subarray sum should remain the same.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR27) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Replace each element with its absolute value */
    for (int &num : source_vec) {
        num = abs(num);
    }

    /* Get the original maximum subarray sum */
    int original_max_sum = multi_maxsum(input.vec, source_m);

    /* Get the maximum subarray sum of the transformed array */
    int transformed_max_sum = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(transformed_max_sum, original_max_sum);
}

/**
 * @brief Metamorphic Relation 28: Subtracting a specific value from each element of the array, the maximum subarray sum should maintain a specific relationship
 * with the original maximum subarray sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR28) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;
    int subtrahend = 5; // Example value to subtract

    /* Subtract the value from each element in the array */
    for (int &num : source_vec) {
        num -= subtrahend;
    }

    /* Get the original maximum subarray sum */
    int original_max_sum = multi_maxsum(input.vec, source_m);

    /* Get the maximum subarray sum of the transformed array */
    int transformed_max_sum = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(transformed_max_sum, original_max_sum - (subtrahend * source_m)); // Example relationship between the maximum subarray sums
}

/**
 * @brief Metamorphic Relation 29: Replacing the elements of the array with their square roots, the maximum subarray sum should have a specific relationship
 * with the original maximum subarray sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR29) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Replace each element with its square root */
    for (int &num : source_vec) {
        num = sqrt(num);
    }

    /* Get the original maximum subarray sum */
    int original_max_sum = multi_maxsum(input.vec, source_m);

    /* Get the maximum subarray sum of the transformed array */
    int transformed_max_sum = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_GE(transformed_max_sum, original_max_sum); // Example relationship between the maximum subarray sums
}

/**
 * @brief Metamorphic Relation 30: Reversing the elements of the array and then finding the maximum subarray sum, the result should remain the same as the
 * original maximum subarray sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR30) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Reverse the source array */
    reverse(source_vec.begin(), source_vec.end());

    /* Get the original maximum subarray sum */
    int original_max_sum = multi_maxsum(input.vec, source_m);

    /* Get the maximum subarray sum of the reversed array */
    int reversed_max_sum = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(reversed_max_sum, original_max_sum);
}

/**
 * @brief Metamorphic Relation 31: Incrementing each element of the array by a constant value, the maximum subarray sum should increase by the product of the
 * constant value and the subarray length.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR31) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int constant = 10; // Example constant value
    int source_m = input.m;

    /* Get the original maximum subarray sum */
    int original_max_sum = multi_maxsum(source_vec, source_m);

    /* Increment each element by the constant value */
    for (int &num : source_vec) {
        num += constant;
    }

    /* Get the maximum subarray sum of the modified array */
    int incremented_max_sum = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(incremented_max_sum, original_max_sum + (constant * source_m));
}

/**
 * @brief Metamorphic Relation 32: Replacing all elements in the array with their squares and then finding the maximum subarray sum, the result should be
 * different from the original maximum subarray sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR32) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get the original maximum subarray sum */
    int original_max_sum = multi_maxsum(source_vec, source_m);

    /* Replace each element with its square */
    for (int &num : source_vec) {
        num = num * num;
    }

    /* Get the maximum subarray sum of the transformed array */
    int transformed_max_sum = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_NE(transformed_max_sum, original_max_sum); // Ensure that the output has changed
}

/**
 * @brief Metamorphic Relation 33: Adding a constant value to the array and then reversing the array, the maximum subarray sum should remain the same as the
 * original maximum subarray sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR33) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int constant = 5; // Example constant value
    int source_m = input.m;

    /* Add the constant value to each element in the array */
    for (int &num : source_vec) {
        num += constant;
    }

    /* Get the original maximum subarray sum */
    int original_max_sum = multi_maxsum(input.vec, source_m);

    /* Reverse the source array */
    reverse(source_vec.begin(), source_vec.end());

    /* Get the maximum subarray sum of the modified array */
    int reversed_max_sum = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(reversed_max_sum, original_max_sum);
}

/**
 * @brief Metamorphic Relation 34: Reversing the array and then finding the sum of the first and second halves separately, the sum of the two halves should
 * remain the same as the original sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR34) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get the original sum */
    int original_sum = std::accumulate(source_vec.begin(), source_vec.end(), 0);

    /* Reverse the source array */
    reverse(source_vec.begin(), source_vec.end());

    /* Calculate the sum of the first half */
    int first_half_sum = std::accumulate(source_vec.begin(), source_vec.begin() + source_vec.size() / 2, 0);

    /* Calculate the sum of the second half */
    int second_half_sum = std::accumulate(source_vec.begin() + source_vec.size() / 2, source_vec.end(), 0);

    /* Verification */
    EXPECT_EQ(first_half_sum + second_half_sum, original_sum);
}

/**
 * @brief Metamorphic Relation 35: Multiplying each element of the array by a positive scalar and then finding the maximum subarray sum, the result should
 * maintain a specific relationship with the original maximum subarray sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR35) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int scalar = 2; // Example scalar value
    int source_m = input.m;

    /* Get the original maximum subarray sum */
    int original_max_sum = multi_maxsum(source_vec, source_m);

    /* Multiply each element by the scalar */
    for (int &num : source_vec) {
        num *= scalar;
    }

    /* Get the maximum subarray sum of the modified array */
    int transformed_max_sum = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(transformed_max_sum, scalar * original_max_sum);
}

/**
 * @brief Metamorphic Relation 36: Replacing all elements in the array with their absolute differences from a fixed value, the maximum subarray sum should
 * remain the same as the original maximum subarray sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR36) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int fixed_value = 10; // Example fixed value
    int source_m = input.m;

    /* Get the original maximum subarray sum */
    int original_max_sum = multi_maxsum(source_vec, source_m);

    /* Replace each element with its absolute difference from the fixed value */
    for (int &num : source_vec) {
        num = abs(num - fixed_value);
    }

    /* Get the maximum subarray sum of the modified array */
    int modified_max_sum = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(modified_max_sum, original_max_sum);
}

/**
 * @brief Metamorphic Relation 37: Replacing all elements in the array with their cumulative sum, the maximum subarray sum should increase.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR37) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Calculate the cumulative sum of the source array */
    partial_sum(source_vec.begin(), source_vec.end(), source_vec.begin());

    /* Get the original maximum subarray sum */
    int original_max_sum = multi_maxsum(input.vec, source_m);

    /* Get the maximum subarray sum of the modified array */
    int modified_max_sum = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_GT(modified_max_sum, original_max_sum);
}

/**
 * @brief Metamorphic Relation 38: Replacing all elements in the array with their rounding to the nearest integer, the maximum subarray sum should remain the
 * same as the original maximum subarray sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR38) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Round each element to the nearest integer */
    for (int &num : source_vec) {
        num = round(num);
    }

    /* Get the original maximum subarray sum */
    int original_max_sum = multi_maxsum(input.vec, source_m);

    /* Get the maximum subarray sum of the modified array */
    int modified_max_sum = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(modified_max_sum, original_max_sum);
}

/**
 * @brief Metamorphic Relation 39: Multiplying each element of the array by its index and then finding the maximum subarray sum, the result should have a
 * specific relationship with the original maximum subarray sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR39) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Multiply each element by its index */
    for (size_t i = 0; i < source_vec.size(); i++) {
        source_vec[i] *= i;
    }

    /* Get the original maximum subarray sum */
    int original_max_sum = multi_maxsum(input.vec, source_m);

    /* Get the maximum subarray sum of the modified array */
    int transformed_max_sum = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(transformed_max_sum, 2 * original_max_sum); // Example relationship between the maximum subarray sums
}

/**
 * @brief Metamorphic Relation 40: Replacing all elements in the array with their absolute differences from the mean value, the maximum subarray sum should
 * remain the same as the original maximum subarray sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR40) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Calculate the mean value of the source array */
    double mean = accumulate(source_vec.begin(), source_vec.end(), 0.0) / source_vec.size();

    /* Get the original maximum subarray sum */
    int original_max_sum = multi_maxsum(source_vec, source_m);

    /* Replace each element with its absolute difference from the mean value */
    for (int &num : source_vec) {
        num = abs(num - mean);
    }

    /* Get the maximum subarray sum of the modified array */
    int modified_max_sum = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(modified_max_sum, original_max_sum);
}

/**
 * @brief Metamorphic Relation 41: Reversing the array and then finding the maximum subarray sum, the result should maintain a specific relationship with the
 * original maximum subarray sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR41) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get the original maximum subarray sum */
    int original_max_sum = multi_maxsum(input.vec, source_m);

    /* Reverse the source array */
    reverse(source_vec.begin(), source_vec.end());

    /* Get the maximum subarray sum of the reversed array */
    int reversed_max_sum = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(reversed_max_sum, original_max_sum);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, MultiMAXSUMParamTest, testing::ValuesIn(gen_tcs_randomly()));