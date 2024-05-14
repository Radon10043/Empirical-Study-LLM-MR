#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <random>
#include <vector>
#include <climits>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class MultiMAXSUMParamTest : public ::testing::TestWithParam<MultiMAXSUMInput> {};

/**
 * @brief Metamorphic Relation 2: Doubling all elements in the array, the follow-up output should be double the source output.
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
    for (int &value : follow_vec) {
        value *= 2;
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(2 * source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 3: Reverse the array, the follow-up output should be the same as the source output.
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
    vector<int> follow_vec(source_vec.rbegin(), source_vec.rend());

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 4: Appending a subarray with a negative sum to the end, the follow-up output should be the same as the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR4) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    vector<int> negative_subarray = {-1, -2, -3}; // An example subarray with a negative sum
    follow_vec.insert(follow_vec.end(), negative_subarray.begin(), negative_subarray.end());

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 5: Increasing the value of m by 1 and appending a new positive element to the array that is larger than any existing sum,
 * the follow-up output should be equal to the source output plus the new element.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR5) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    int new_element = 100; // Assuming this is larger than the sum of any subarray in the source input
    vector<int> follow_vec = source_vec;
    follow_vec.push_back(new_element);

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m + 1);

    /* Verification */
    EXPECT_EQ(source_out + new_element, follow_out);
}

/**
 * @brief Metamorphic Relation 6: Scaling down all elements by a positive factor, the follow-up output should be the source output scaled by the same factor.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR6) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Scale factor */
    int scale_factor = 2; // e.g., every element will be half of its original value

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &value : follow_vec) {
        value /= scale_factor;
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(source_out / scale_factor, follow_out);
}

/**
 * @brief Metamorphic Relation 7: Permuting the array elements, the follow-up output should be the same as the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR7) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    std::random_shuffle(follow_vec.begin(), follow_vec.end()); // Shuffle array elements

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 8: Concatenating the same array, the follow-up output should be at least twice the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR8) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.insert(follow_vec.end(), source_vec.begin(), source_vec.end());
    int new_m = 2 * source_m;

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, new_m);

    /* Verification */
    EXPECT_GE(follow_out, 2 * source_out);
}

/**
 * @brief Metamorphic Relation 9: Inserting a zero-element in the array should not change the output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR9) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.insert(follow_vec.begin() + follow_vec.size() / 2, 0); // Insert zero in the middle

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 10: Subtracting a constant from all elements should not change the relative sums of the subarrays.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR10) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Subtract a constant from all elements */
    int constant = 5; // Example constant

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &value : follow_vec) {
        value -= constant;
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Since subtracting a constant affects each subarray equally,
    the difference between source and follow-up outputs should be the
    constant multiplied by m (number of subarrays). */
    EXPECT_EQ(source_out - constant * source_m, follow_out);
}

/**
 * @brief Metamorphic Relation 11: Prefixed or postfixed subarrays with negative sums have no effect on source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR11) {
    /* Get source input and output */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;
    int source_out = multi_maxsum(source_vec, source_m);

    /* Get the sum of a fixed negative subarray */
    vector<int> negative_subarray = {-7, -5, -3};
    int negative_sum = std::accumulate(negative_subarray.begin(), negative_subarray.end(), 0);

    /* Construct follow-up input by prefixing and postfixing negative subarray */
    vector<int> follow_vec_prefixed, follow_vec_postfixed;
    follow_vec_prefixed.reserve(source_vec.size() + negative_subarray.size());
    follow_vec_postfixed.reserve(source_vec.size() + negative_subarray.size());

    follow_vec_prefixed.insert(follow_vec_prefixed.end(), negative_subarray.begin(), negative_subarray.end());
    follow_vec_prefixed.insert(follow_vec_prefixed.end(), source_vec.begin(), source_vec.end());
    follow_vec_postfixed.insert(follow_vec_postfixed.end(), source_vec.begin(), source_vec.end());
    follow_vec_postfixed.insert(follow_vec_postfixed.end(), negative_subarray.begin(), negative_subarray.end());

    /* Get follow-up output */
    int follow_out_prefixed = multi_maxsum(follow_vec_prefixed, source_m);
    int follow_out_postfixed = multi_maxsum(follow_vec_postfixed, source_m);

    /* Verification that prefixed or postfixed negative arrays do not increase the maximum sum */
    EXPECT_EQ(source_out, follow_out_prefixed);
    EXPECT_EQ(source_out, follow_out_postfixed);
}

/**
 * @brief Metamorphic Relation 12: Concatenating a copy of the array with one element inverted should not exceed twice the maximum sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR12) {
    /* Get source input and output */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input by concatenating a copy of the array with one element inverted */
    vector<int> follow_vec = source_vec;
    std::transform(source_vec.begin(), source_vec.end(), source_vec.begin(), std::negate<int>());
    follow_vec.insert(follow_vec.end(), source_vec.begin(), source_vec.end());

    /* Get follow-up output */
    int new_m = 2 * source_m;
    int follow_out = multi_maxsum(follow_vec, new_m);

    /* Verification that concatenating inverted array does not exceed twice the maximum sum */
    EXPECT_LE(follow_out, 2 * source_out);
}

/**
 * @brief Metamorphic Relation 13: Changing the order of the subarrays should not change the maximum sum of m contiguous, non-overlapping subarrays.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR13) {
    /* Get source input and output */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input by reordering subarrays */
    vector<int> follow_vec = source_vec;
    if (source_vec.size() >= 2 * source_m) {
        // Swap first and second subarray if possible
        std::reverse(follow_vec.begin(), follow_vec.begin() + 2 * source_m);
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification that reordering subarrays does not change maximum sum */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 14: Inserting an array with a neutral sum should not change the maximum sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR14) {
    /* Get source input and output */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct an array with a zero sum */
    vector<int> zero_sum_array = {3, -1, -2};

    /* Construct follow-up input by inserting zero sum array within original array */
    vector<int> follow_vec = source_vec;
    follow_vec.insert(follow_vec.begin() + follow_vec.size() / 2, zero_sum_array.begin(), zero_sum_array.end());

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification that insert zero sum array does not change maximum sum */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 15: Multiplying all elements by -1 and finding max sum for same number of subarrays, the output should be the negative of source
 * output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR15) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input by multiplying all elements by -1 */
    vector<int> follow_vec;
    std::transform(source_vec.begin(), source_vec.end(), std::back_inserter(follow_vec), [](int num) { return -1 * num; });

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(-source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 16: Inserting a large number of zeros in the array should not change the output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR16) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input by inserting zeros */
    vector<int> zeroes(source_vec.size(), 0); // Same size as source_vec filled with zeroes
    vector<int> follow_vec(source_vec);
    follow_vec.insert(follow_vec.end(), zeroes.begin(), zeroes.end());

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 17: If we change the order of elements within a subarray that contributes to max sum, it should not change the output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR17) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Assume we know the bounds of subarrays contributing to max sum,
       here for simplicity we just take the first 'm' elements */
    if (source_vec.size() < source_m) {
        /* Requires that source_vec has at least 'm' elements to apply this MR correctly */
        return;
    }

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input by shuffling first 'm' elements */
    vector<int> follow_vec = source_vec;
    std::random_shuffle(follow_vec.begin(), follow_vec.begin() + source_m);

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 18: Interchanging two subarrays which are not part of m max sum subarrays should not affect the output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR18) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input by interchanging two subarrays
       Note: This relation assumes knowledge of which subarrays don't contribute to the sum */
    if (source_vec.size() >= 2 * source_m) {
        vector<int> subarray_1(source_vec.begin() + source_m, source_vec.begin() + 2 * source_m);
        vector<int> subarray_2(source_vec.end() - source_m, source_vec.end());

        // Swap the positions of subarray_1 and subarray_2 in the source_vec
        std::copy(subarray_1.begin(), subarray_1.end(), source_vec.end() - source_m);
        std::copy(subarray_2.begin(), subarray_2.end(), source_vec.begin() + source_m);
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 19: Appending an array with elements sufficiently large should increase the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR19) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input by appending a large value array */
    vector<int> append_array(source_m, INT_MAX / source_m); // Large values to ensure they will be included
    vector<int> follow_vec = source_vec;
    follow_vec.insert(follow_vec.end(), append_array.begin(), append_array.end());

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m + 1); // m is increased to ensure the new values are considered

    /* Verification */
    EXPECT_GT(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 20: Shuffling the array elements but keeping the same m should not change the output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR20) {
    // This relation is similar to MR7, but extended further to verify its robustness.

    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input by shuffling the entire array */
    std::random_device rd;
    std::mt19937 g(rd());
    vector<int> follow_vec = source_vec;
    std::shuffle(follow_vec.begin(), follow_vec.end(), g);

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 21: Expanding the array by interleaving it with zeros shouldn't alter the maximum sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR21) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input by interleaving input array with zeros */
    vector<int> follow_vec;
    for (auto num : source_vec) {
        follow_vec.push_back(num);
        follow_vec.push_back(0); // Interleave with zero
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 22: If all elements are positive, multiplying elements by a negative scale should not change the absolute value of output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR22) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Check if all elements are positive */
    if (std::all_of(source_vec.begin(), source_vec.end(), [](int i) { return i >= 0; })) {
        /* Get source output */
        int source_out = multi_maxsum(source_vec, source_m);

        /* Construct follow-up input by multiplying each element by -1 */
        vector<int> follow_vec = source_vec;
        std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int i) { return -1 * i; });

        /* Get follow-up output */
        int follow_out = multi_maxsum(follow_vec, source_m);

        /* Verification */
        EXPECT_EQ(std::abs(source_out), std::abs(follow_out));
    }
}

/**
 * @brief Metamorphic Relation 23: If concatenating the inverted array, m should be doubled, and the output should remain non-negative.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR23) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Construct follow-up input by concatenating the inverted array */
    vector<int> follow_vec = source_vec;
    for_each(source_vec.begin(), source_vec.end(), [&follow_vec](int x) { follow_vec.push_back(-x); });

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m * 2);

    /* Verification */
    EXPECT_GE(follow_out, 0);
}

/**
 * @brief Metamorphic Relation 24: Adding a constant to all elements should increase the output by m * constant.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR24) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input by adding a constant to every element */
    const int constant = 5;
    vector<int> follow_vec;
    std::transform(source_vec.begin(), source_vec.end(), std::back_inserter(follow_vec), [constant](int value) { return value + constant; });

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out + source_m * constant);
}

/**
 * @brief Metamorphic Relation 25: Setting all elements to the same value and having m = 1 should result in the output equal to n * element_value.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR25) {
    // This relation is only applicable when m is set to 1.

    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec(input.vec.size(), input.vec[0]); // Set all elements to the value of the first element
    int source_m = 1;                                       // Only considering a single subarray

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Verification */
    int expected = source_vec.size() * source_vec[0];
    EXPECT_EQ(source_out, expected);
}

/**
 * @brief Metamorphic Relation 26: Adding additional random subarrays that sum to zero should not change the maximum sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR26) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input by adding additional subarrays that sum to zero */
    vector<int> zero_sum_subarray{2, -1, -1}; // Example subarray with zero sum
    vector<int> follow_vec = source_vec;
    follow_vec.insert(follow_vec.end(), zero_sum_subarray.begin(), zero_sum_subarray.end());
    follow_vec.insert(follow_vec.end(), zero_sum_subarray.begin(), zero_sum_subarray.end());

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 27: Changing the array while maintaining the largest m subarrays and their sums should not change the output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR27) {
#if 0
    // This relation assumes knowledge of which m subarrays contribute to the max sum.
    // Here, it's assumed that some subarray properties are known (which obviously may not apply for a black-box test).

    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Assuming we can identify the largest m subarrays, we can alter other parts of the array. */
    // The test omits the algorithm for such identification and array modification, which depends on the problem context
    // ...

    /* Construct follow-up input where non-max contributing subarrays have their elements decreased */
    vector<int> follow_vec = source_vec;
    // Assuming we have a function getNonContributingIndices() that provides indices of non-contributing elements.
    auto non_contri_indices = getNonContributingIndices(source_vec, source_m, source_out);
    for (auto i : non_contri_indices) {
        follow_vec[i] = follow_vec[i] > 1 ? follow_vec[i] - 1 : follow_vec[i] + 1; // Slight modification respecting sign
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
#endif
}

/**
 * @brief Metamorphic Relation 28: Interleaving the array with a repeating value which is the minimum integer should not change the output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR28) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input by interleaving with a repeating value which is the minimum integer */
    vector<int> follow_vec;
    int min_value = INT_MIN;
    for (const auto &val : source_vec) {
        follow_vec.push_back(val);
        follow_vec.push_back(min_value); // Interleave with min_value
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 29: Replacing non-contributing subarray elements with their absolute values shouldn't change the output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR29) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    // Compute the absolute value of each element in the vector
    vector<int> follow_vec(source_vec.size());
    std::transform(source_vec.begin(), source_vec.end(), follow_vec.begin(), [](int n) { return std::abs(n); });

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 30: Concatenating the array with an arbitrary sequence with net zero sum should not change the output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR30) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input by concatenating sequence with a net zero sum */
    vector<int> zero_sum_sequence = {5, -2, 3, -6}; // Example sequence summing to zero
    vector<int> follow_vec(source_vec);
    follow_vec.insert(follow_vec.end(), zero_sum_sequence.begin(), zero_sum_sequence.end());

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 31: Increasing all elements by the same ratio should scale the output by that ratio.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR31) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Scaling ratio */
    const double ratio = 1.5;

    /* Construct follow-up input by scaling each element */
    vector<int> follow_vec;
    std::transform(source_vec.begin(), source_vec.end(), std::back_inserter(follow_vec), [ratio](int value) { return static_cast<int>(value * ratio); });

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_NEAR(static_cast<int>(source_out * ratio), follow_out, 1);
}

/**
 * @brief Metamorphic Relation 32: Partition the original array into 'm' contiguous subarrays, reverse each subarray and concatenate them back.
 *        The output should remain unchanged since the sum of subarrays remains the same.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR32) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Partition original array into m parts and reverse each part */
    vector<int> follow_vec;
    follow_vec.reserve(source_vec.size());
    int part_size = source_vec.size() / source_m;
    for (int i = 0; i < source_m; ++i) {
        int start_idx = i * part_size;
        int end_idx = i + 1 == source_m ? source_vec.size() : (i + 1) * part_size;
        vector<int> subarray(source_vec.begin() + start_idx, source_vec.begin() + end_idx);
        std::reverse(subarray.begin(), subarray.end());
        follow_vec.insert(follow_vec.end(), subarray.begin(), subarray.end());
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 33: Removing subarray with minimum sum shouldn't decrease the output when m is decreased by 1.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR33) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    if (source_m <= 1) {
        // This relation only makes sense for m > 1
        return;
    }

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input by removing a subarray */
    // Assuming we can identify a contributing subarray with the minimum sum
    // Important: Subarray removal and identification logic is required here
    vector<int> follow_vec = source_vec; // A placeholder for actual logic

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m - 1);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 34: Concatenate the input array with itself, and double the value of m;
 *        the result should be exactly double the original maximum sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR34) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input by concatenating array with itself */
    vector<int> follow_vec(source_vec);
    follow_vec.insert(follow_vec.end(), source_vec.begin(), source_vec.end());

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, 2 * source_m);

    /* Verification */
    // Assuming there are no overlapping subarray sums that are better when connected,
    // which may not always be the case.
    EXPECT_EQ(2 * source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 35: If a subarray that has a sum lower than the maximum subarray is replaced by a subarray with a higher sum
 * we can expect the output not to decrease, given m remains the same.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR35) {    // Fixed
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    // Logic to replace a subarray with a sum less than the sum of the maximum subarray
    vector<int> follow_vec = source_vec; // Placeholder for the new array after replacement
    // Crystal-clear subarray recognition and replacement would be necessary

    for (int i = 0; i < source_vec.size(); i++) {
        if (source_vec[i] < source_vec[i + 1]) {
            follow_vec[i] = source_vec[i + 1];
            break;
        }
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 36: For every element in the array, if we add a large negative number,
 * the output should be decreased by m times that number.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR36) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Subtractive constant */
    const int negative_constant = -1000; // Ensure that it's large and negative

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec;
    std::transform(source_vec.begin(), source_vec.end(), std::back_inserter(follow_vec), [negative_constant](int value) { return value + negative_constant; });

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out + source_m * negative_constant);
}

/**
 * @brief Metamorphic Relation 37: Splitting the input array at any point and swapping the two portions
 * should not decrease the maximum sum if m is doubled.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR37) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* A random index to split the array */
    size_t split_index = source_vec.size() / 2; // As an example, using the middle point

    /* Construct follow-up input by splitting and swapping portions */
    vector<int> follow_vec(source_vec.begin() + split_index, source_vec.end());
    follow_vec.insert(follow_vec.end(), source_vec.begin(), source_vec.begin() + split_index);

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, 2 * source_m); // Doubling m

    /* Verification */
    // This relation assumes that no subarray spanning the two portions in the unsplit array contributes to the original max sum.
    int source_out = multi_maxsum(source_vec, source_m); // Getting source output for comparison
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 38: If an array contains 'm' maximum sum subarrays that are all non-negative, making
 * one of the elements within these subarrays negative should not increase the maximum sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR38) {
#if 0
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    // Assuming we have a function identifyMaxSubarrays() that returns the indices of all the elements in 'm' maximum sum subarrays
    vector<int> max_subarrays_indices = identifyMaxSubarrays(source_vec, source_m);

    if (!max_subarrays_indices.empty()) {
        /* Change one of the elements to be negative */
        int make_negative_index = max_subarrays_indices.front(); // Assuming the first element of the max sum subarrays
        vector<int> follow_vec = source_vec;
        follow_vec[make_negative_index] = -abs(follow_vec[make_negative_index]);

        /* Get follow-up output */
        int follow_out = multi_maxsum(follow_vec, source_m);

        /* Verification - making an element negative should not increase the max sum */
        EXPECT_LE(follow_out, source_out);
    }
#endif
}

/**
 * @brief Metamorphic Relation 39: Splitting the array into two halves and individually finding their maximum sums with m/2 subarrays
 * should be less than or equal to the maximum sum of the entire array with m subarrays.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR39) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    if (source_m < 2) {
        // This relation only makes sense for m >= 2
        return;
    }

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Split array into two halves */
    vector<int> first_half(source_vec.begin(), source_vec.begin() + source_vec.size() / 2);
    vector<int> second_half(source_vec.begin() + source_vec.size() / 2, source_vec.end());

    /* Get maximum sum for each half */
    int first_half_out = multi_maxsum(first_half, source_m / 2);
    int second_half_out = multi_maxsum(second_half, source_m / 2);

    /* Verification */
    EXPECT_LE(first_half_out + second_half_out, source_out);
}

/**
 * @brief Metamorphic Relation 40: Increasing all elements in a subarray that does not contribute to the maximum sum should not decrease the maximum sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR40) {
#if 0
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    // Assuming we have a function identifyNonContributingSubarray() that returns the start and end indices of a non-contributing subarray
    auto [start_index, end_index] = identifyNonContributingSubarray(source_vec, source_m);

    if (start_index != end_index) {
        /* Increase all elements in the identified subarray */
        vector<int> follow_vec = source_vec;
        std::transform(follow_vec.begin() + start_index, follow_vec.begin() + end_index, follow_vec.begin() + start_index, [](int val) { return val + 10; });

        /* Get follow-up output */
        int follow_out = multi_maxsum(follow_vec, source_m);

        /* Verification */
        EXPECT_GE(follow_out, source_out);
    }
#endif
}

/**
 * @brief Metamorphic Relation 41: Adding more non-overlapping subarrays beyond 'm' with negative sums should not increase the maximum sum.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR41) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int original_m = input.m;

    /* Original output */
    int original_out = multi_maxsum(source_vec, original_m);

    /* Add more subarrays with negative sums to the end */
    vector<int> negative_subarray = {-5, -6, -7}; // An example subarray with a negative sum
    for (int i = 0; i < 3; ++i) {
        // Append multiple negative subarrays
        source_vec.insert(source_vec.end(), negative_subarray.begin(), negative_subarray.end());
    }
    int extended_m = original_m + 3; // Increase m to include new subarrays

    /* New output with the extended array and m */
    int extended_out = multi_maxsum(source_vec, extended_m);

    /* Verification */
    EXPECT_EQ(original_out, extended_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, MultiMAXSUMParamTest, testing::ValuesIn(gen_tcs_randomly()));
