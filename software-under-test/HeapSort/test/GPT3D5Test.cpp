#include <algorithm>
#include <bitset>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class HeapSortParamTest : public ::testing::TestWithParam<HeapSortInput> {};

/**
 * @brief Metamorphic relation 1: Reversing the elements in the input array should not change the order of the output array.
 *
 */
TEST_P(HeapSortParamTest, MR1) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 2: Sorting the absolute values of the elements in the input array should yield the same output as sorting the original input
 * array.
 *
 */
TEST_P(HeapSortParamTest, MR2) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem = abs(elem);

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 3: Adding a constant to each element in the input array, then each element of the output array will be larger by the constant
 * than the element at the same location of the source input.
 *
 */
TEST_P(HeapSortParamTest, MR3) {
    int constant = 3;

    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem += constant;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    for (auto &elem : follow_out)
        elem -= constant;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 4: Repeating each element in the input array multiple times should not change the order of the output array.
 *
 */
TEST_P(HeapSortParamTest, MR4) {
    int repeat_factor = 3; // Repeat each element 3 times

    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (auto elem : source_vec) {
        for (int i = 0; i < repeat_factor; ++i) {
            follow_vec.push_back(elem);
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 5: Substituting each element in the input array with its square, then the output array should be the same as sorting the modified
 * input array.
 *
 */
TEST_P(HeapSortParamTest, MR5) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem = elem * elem;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 6: Inverting the order of the elements in the input array, inverting the order of the output array should be the same as sorting
 * the modified input array.
 *
 */
TEST_P(HeapSortParamTest, MR6) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    sort(follow_vec.rbegin(), follow_vec.rend());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 7: Replacing all elements in the input array with their negations, then if we negate all elements in the output array, it should
 * be the same as the source output array, but in reverse order.
 *
 */
TEST_P(HeapSortParamTest, MR7) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem = -elem;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    for (auto &elem : follow_out)
        elem = -elem;
    reverse(follow_out.begin(), follow_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 8: Taking the absolute values of the elements in the input array, then sorting the modified input array will yield the same
 * output as sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR8) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem = abs(elem);

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 9: Sorting the elements in the input array in non-decreasing order will result in the same output as sorting the original input
 * array.
 *
 */
TEST_P(HeapSortParamTest, MR9) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 10: Multiplying each element in the input array by a constant, then all elements in the output array should be larger by the
 * constant than the corresponding elements in the source output array.
 *
 */
TEST_P(HeapSortParamTest, MR10) { // fixed
    int constant = 5;             // Constant multiplier

    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem *= constant; // Multiply each element by the constant

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    for (auto &elem : follow_out)
        elem /= constant;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 11: Repeating each element in the input array multiple times should not change the order of the output array.
 *
 */
TEST_P(HeapSortParamTest, MR11) {
    int repeat_factor = 2; // Repeat each element 2 times

    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (auto elem : source_vec) {
        for (int i = 0; i < repeat_factor; ++i) {
            follow_vec.push_back(elem);
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 12: Sorting the input array in non-increasing order will result in the same output as sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR12) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    sort(follow_vec.rbegin(), follow_vec.rend());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 13: Randomly permuting the elements in the input array should not change the order of the output array.
 *
 */
TEST_P(HeapSortParamTest, MR13) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    random_shuffle(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 14: Sorting the input array with the same elements repeated in different orders will result in the same output as sorting the
 * original input array.
 *
 */
TEST_P(HeapSortParamTest, MR14) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Modify source vector to add repeated elements in different orders */
    vector<int> follow_vec;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < source_vec.size(); ++j) {
            follow_vec.push_back(source_vec[j]);
        }
        random_shuffle(follow_vec.begin(), follow_vec.end()); // Shuffle the repeated elements
    }

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 15: Sorting an empty input array should result in an empty output array.
 *
 */
TEST_P(HeapSortParamTest, MR15) { // fixed
    vector<int> empty_vec;

    /* Get output for empty input */
    vector<int> output = heap_sort(empty_vec);

    /* Verification */
    EXPECT_TRUE(output.empty());
}
/**
 * @brief Metamorphic Relation 16: Sorting a single-element input array should result in the same single-element output array.
 *
 */
TEST_P(HeapSortParamTest, MR16) {          // fixed
    vector<int> single_element_vec = {42}; // Single-element input array

    /* Get output for single-element input */
    vector<int> output = heap_sort(single_element_vec);

    /* Verification */
    ASSERT_EQ(output.size(), 1);
    EXPECT_EQ(output[0], 42);
}

/**
 * @brief Metamorphic Relation 17: Sorting an already sorted input array should result in the same sorted output array.
 *
 */
TEST_P(HeapSortParamTest, MR17) { // fixed
    HeapSortInput input = GetParam();
    vector<int> sorted_vec = input.vec;
    sort(sorted_vec.begin(), sorted_vec.end()); // Sorted input array

    /* Get output for sorted input */
    vector<int> output = heap_sort(sorted_vec);

    /* Verification */
    EXPECT_EQ(output, sorted_vec);
}

/**
 * @brief Metamorphic Relation 18: Sorting a reverse-sorted input array should result in the same sorted output array as the reverse of the input array.
 *
 */
TEST_P(HeapSortParamTest, MR18) {
    HeapSortInput input = GetParam();
    vector<int> reverse_sorted_vec = input.vec;
    sort(reverse_sorted_vec.rbegin(), reverse_sorted_vec.rend()); // Reverse-sorted input array

    /* Get output for reverse-sorted input */
    vector<int> output = heap_sort(reverse_sorted_vec);

    /* Verification */
    reverse(reverse_sorted_vec.begin(), reverse_sorted_vec.end());
    EXPECT_EQ(output, reverse_sorted_vec);
}
/**
 * @brief Metamorphic Relation 19: Reversing the input array should result in the reversal of the output array.
 *
 */
TEST_P(HeapSortParamTest, MR19) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    reverse(source_out.begin(), source_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 20: Replacing all elements in the input array with their squares, then sorting the modified input array should yield the
 * same output as sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR20) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return x * x; });

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 21: Sorting an input array with duplicate elements should result in the same output as sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR21) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input with duplicate elements */
    vector<int> follow_vec = source_vec;
    follow_vec.push_back(source_vec[0]); // Introduce a duplicate element

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 22: Sorting the elements in the input array in non-decreasing order will yield the same output as sorting the original input
 * array.
 *
 */
TEST_P(HeapSortParamTest, MR22) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 23: Sorting an array with all elements equal should result in the same sorted output as the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR23) {
    vector<int> all_equal_vec(100, 42); // Array with all elements equal to 42

    /* Get output for array with all equal elements */
    vector<int> output = heap_sort(all_equal_vec);

    /* Verification */
    vector<int> expected_output(100, 42);
    EXPECT_EQ(output, expected_output);
}

/**
 * @brief Metamorphic Relation 24: Sorting the squared elements of the input array should yield the same output as sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR24) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return x * x; });

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 25: Sorting the negative elements of the input array should yield the same output as sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR25) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (auto elem : source_vec) {
        if (elem < 0) {
            follow_vec.push_back(elem);
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 26: Sorting the non-negative elements of the input array should yield the same output as sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR26) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (auto elem : source_vec) {
        if (elem >= 0) {
            follow_vec.push_back(elem);
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 27: Sorting the array of absolute differences of adjacent elements in the input array should yield the same output as sorting the
 * original input array.
 *
 */
TEST_P(HeapSortParamTest, MR27) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (size_t i = 1; i < source_vec.size(); ++i) {
        follow_vec.push_back(abs(source_vec[i] - source_vec[i - 1]));
    }

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 28: Sorting the input array in non-increasing order will yield the same output as sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR28) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    sort(follow_vec.rbegin(), follow_vec.rend());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 29: Sorting the array of squared distances from a given value in the input array should yield the same output as sorting the
 * original input array.
 *
 */
TEST_P(HeapSortParamTest, MR29) {
    int reference_value = 10;

    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (auto elem : source_vec) {
        follow_vec.push_back((elem - reference_value) * (elem - reference_value));
    }

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 30: Sorting the input array of absolute differences between elements and the highest value in the input array should yield the
 * same output as sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR30) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Get the highest value in the input array */
    int max_value = *max_element(source_vec.begin(), source_vec.end());

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (auto elem : source_vec) {
        follow_vec.push_back(abs(elem - max_value));
    }

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 31: Sorting the input array of absolute differences between elements and the lowest value in the input array should yield the
 * same output as sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR31) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Get the lowest value in the input array */
    int min_value = *min_element(source_vec.begin(), source_vec.end());

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (auto elem : source_vec) {
        follow_vec.push_back(abs(elem - min_value));
    }

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 32: Sorting the elements in the input array modified by taking the modulo with a constant should yield the same output as
 * sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR32) {
    int modulus = 5; // Constant modulus value

    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem = elem % modulus;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 33: Sorting the absolute differences between adjacent elements in the input array should yield the same output as sorting the
 * original input array.
 *
 */
TEST_P(HeapSortParamTest, MR33) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (size_t i = 1; i < source_vec.size(); ++i) {
        follow_vec.push_back(abs(source_vec[i] - source_vec[i - 1]));
    }

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 34: Sorting the elements in the input array with the same elements repeated in different orders will result in the same output as
 * sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR34) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Modify source vector to add repeated elements in different orders */
    vector<int> follow_vec;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < source_vec.size(); ++j) {
            follow_vec.push_back(source_vec[j]);
        }
        random_shuffle(follow_vec.begin(), follow_vec.end()); // Shuffle the repeated elements
    }

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 35: Sorting an array of elements from the even positions in the input array should yield the same output as sorting the original
 * input array.
 *
 */
TEST_P(HeapSortParamTest, MR35) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (size_t i = 0; i < source_vec.size(); i += 2) {
        follow_vec.push_back(source_vec[i]);
    }

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 36: Sorting an array of elements from the odd positions in the input array should yield the same output as sorting the original
 * input array.
 *
 */
TEST_P(HeapSortParamTest, MR36) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (size_t i = 1; i < source_vec.size(); i += 2) {
        follow_vec.push_back(source_vec[i]);
    }

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 37: Sorting the absolute values of the elements in the input array should yield the same output as sorting the original input
 * array.
 *
 */
TEST_P(HeapSortParamTest, MR37) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem = abs(elem);

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 38: Sorting the array of differences between each element and the mean value of the elements in the input array should yield the
 * same output as sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR38) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Calculate the mean value of the input array */
    double mean_value = accumulate(source_vec.begin(), source_vec.end(), 0.0) / source_vec.size();

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (auto elem : source_vec) {
        follow_vec.push_back(abs(elem - mean_value));
    }

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 39: Sorting the elements in the input array after mapping each element to its position in the input array when sorted should
 * yield the same output as sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR39) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (size_t i = 0; i < follow_vec.size(); ++i) {
        follow_vec[i] = (int)(lower_bound(source_vec.begin(), source_vec.end(), source_vec[i]) - source_vec.begin());
    }

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 40: Sorting the negation of the elements in the input array should yield the same output as sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR40) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem = -elem;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, HeapSortParamTest, testing::ValuesIn(gen_tcs_randomly()));
