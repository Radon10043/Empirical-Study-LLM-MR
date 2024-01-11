#include <algorithm>
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
 * @brief Metamorphic Relation 1: Reversing the elements in the input array, the output will be sorted in ascending order.
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
    sort(source_out.begin(), source_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 2: Deleting a constant from each element in the input array, then each element of the output array will be smaller by the
 * constant than the element at the same location of the source input.
 *
 */
TEST_P(HeapSortParamTest, MR2) {
    int constant = 3;

    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem -= constant;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    for (auto &elem : follow_out)
        elem += constant;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 4: Adding a constant to each element in the input array, then the output should be the same as the original output array shifted
 * to the right by 1 position.
 *
 */
TEST_P(HeapSortParamTest, MR4) {
    int constant = 2;

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
    rotate(source_out.rbegin(), source_out.rbegin() + 1, source_out.rend());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 5: Replacing all even elements in the input array with their squares, and all odd elements in the input array with their cubes,
 * the output array should still be sorted in descending order.
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
    for (auto &elem : follow_vec) {
        if (elem % 2 == 0) {
            elem = elem * elem;
        } else {
            elem = elem * elem * elem;
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 6: Repeating the elements in the input array, the output array should remain unchanged.
 *
 */
TEST_P(HeapSortParamTest, MR6) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (auto elem : source_vec) {
        follow_vec.push_back(elem);
        follow_vec.push_back(elem);
    }

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 7: Reversing the order of elements in the input array, the output array should also be reversed from the original output array.
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
    reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    reverse(source_out.begin(), source_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 8: Multiplying each element in the input array by a constant factor, the output array should also be multiplied by the same
 * constant factor.
 *
 */
TEST_P(HeapSortParamTest, MR8) {
    int factor = 5;

    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem *= factor;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    for (auto &elem : source_out)
        elem *= factor;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 9: Using the negative of each element in the input array to produce the follow-up input, the output array should also be the
 * negative of the original output array.
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
    for (auto &elem : follow_vec)
        elem = -elem;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    for (auto &elem : source_out)
        elem = -elem;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 10: Repeating the elements in the input array, the output array should remain unchanged.
 */
TEST_P(HeapSortParamTest, MR10) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input by repeating elements */
    vector<int> follow_vec;
    for (auto elem : source_vec) {
        follow_vec.push_back(elem);
        follow_vec.push_back(elem);
    }

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 11: Taking the absolute value of each element in the input array, the output array should remain unchanged.
 */
TEST_P(HeapSortParamTest, MR11) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input by taking absolute value of elements */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem = abs(elem);

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 12: Applying a transformation function to elements in the input array, the output array should reflect the transformation.
 */
TEST_P(HeapSortParamTest, MR12) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input by applying a transformation function */
    vector<int> follow_vec = source_vec;
    transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return x * x + 1; });

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 13: Multiplying each element in the input array by a constant, then sorting should yield the same result as sorting the original
 * array and multiplying the result by the constant.
 */
TEST_P(HeapSortParamTest, MR13) {
    int constant = 2;

    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Apply constant multiplication to source vector for follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem *= constant;

    /* Get sorted output for follow-up input */
    vector<int> sorted_follow_vec = heap_sort(follow_vec);
    for (auto &elem : sorted_follow_vec)
        elem *= constant;

    /* Verification */
    EXPECT_EQ(sorted_follow_vec, source_out);
}

/**
 * @brief Metamorphic Relation 14: Concatenating two input arrays and sorting should yield the same result as merging the sorted arrays for each input and then
 * sorting the merged array.
 */
TEST_P(HeapSortParamTest, MR14) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Generate a second input array */
    vector<int> second_vec;
    int size = source_vec.size();
    for (int i = 0; i < size; i++) {
        second_vec.push_back(size + i); // Elements are similar to source_vec but shifted
    }

    /* Concatenate the input arrays */
    vector<int> combined_vec = source_vec;
    combined_vec.insert(combined_vec.end(), second_vec.begin(), second_vec.end());

    /* Sorting the combined input */
    vector<int> combined_out = heap_sort(combined_vec);

    /* Sorting the individual inputs and merging */
    vector<int> sorted_source_vec = heap_sort(source_vec);
    vector<int> sorted_second_vec = heap_sort(second_vec);
    vector<int> merged_sorted_vec = sorted_source_vec;
    merged_sorted_vec.insert(merged_sorted_vec.end(), sorted_second_vec.begin(), sorted_second_vec.end());
    vector<int> sorted_merged_vec = heap_sort(merged_sorted_vec);

    /* Verification */
    EXPECT_EQ(combined_out, sorted_merged_vec);
}

/**
 * @brief Metamorphic Relation 15: Randomly shuffling the input array should yield the same result as sorting the shuffled input.
 */
TEST_P(HeapSortParamTest, MR15) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Shuffle the input array */
    vector<int> shuffled_vec = source_vec;
    random_shuffle(shuffled_vec.begin(), shuffled_vec.end());

    /* Get sorted output for shuffled input */
    vector<int> shuffled_out = heap_sort(shuffled_vec);

    /* Get sorted output for original input */
    vector<int> source_out = heap_sort(source_vec);

    /* Verification */
    EXPECT_EQ(shuffled_out, source_out);
}

/**
 * @brief Metamorphic Relation 16: Adding a constant to each element in the input array, then sorting should yield the same result as sorting the original array
 * and adding the constant to the result.
 */
TEST_P(HeapSortParamTest, MR16) {
    int constant = 10;

    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Apply constant addition to source vector for follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem += constant;

    /* Get sorted output for follow-up input */
    vector<int> sorted_follow_vec = heap_sort(follow_vec);
    for (auto &elem : sorted_follow_vec)
        elem += constant;

    /* Verification */
    EXPECT_EQ(sorted_follow_vec, source_out);
}

/**
 * @brief Metamorphic Relation 17: Sorting the input array in ascending order and then reversing it should yield the same result as sorting the original array
 * in descending order.
 */
TEST_P(HeapSortParamTest, MR17) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

#if INVALID
    /* Get ascending sort output */
    vector<int> asc_sorted_out = heap_sort(source_vec, true);

    /* Reverse the ascending sort output */
    vector<int> reversed_asc_sorted_out = asc_sorted_out;
    reverse(reversed_asc_sorted_out.begin(), reversed_asc_sorted_out.end());

    /* Get descending sort output */
    vector<int> desc_sorted_out = heap_sort(source_vec);
#else
    /* Fix by Radon */
    /* Get ascending sort output */
    vector<int> asc_sorted_out = heap_sort(source_vec);

    /* Reverse the ascending sort output */
    vector<int> reversed_asc_sorted_out = asc_sorted_out;
    reverse(reversed_asc_sorted_out.begin(), reversed_asc_sorted_out.end());

    /* Get descending sort output */
    vector<int> desc_sorted_out = source_vec;
    sort(desc_sorted_out.begin(), desc_sorted_out.end(), greater<int>());
#endif

    /* Verification */
    EXPECT_EQ(reversed_asc_sorted_out, desc_sorted_out);
}

/**
 * @brief Metamorphic Relation 18: Reversing the order of elements in the input array, the resulting sorted array should also be reversed.
 */
TEST_P(HeapSortParamTest, MR18) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the input array */
    vector<int> source_out = heap_sort(source_vec);

    /* Reverse the sorted output from the original input */
    vector<int> reversed_sorted_output;
    for (auto it = source_out.rbegin(); it != source_out.rend(); ++it) {
        reversed_sorted_output.push_back(*it);
    }

    /* Reverse the original input */
    vector<int> reversed_input = source_vec;
    reverse(reversed_input.begin(), reversed_input.end());

    /* Get sorted output for reversed input */
    vector<int> reversed_out = heap_sort(reversed_input);

    /* Verification */
    EXPECT_EQ(reversed_out, reversed_sorted_output);
}

/**
 * @brief Metamorphic Relation 19: Selecting a subset of the input array and sorting it should yield a result that is a subset of the sorted array from the
 * original input.
 */
TEST_P(HeapSortParamTest, MR19) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Randomly shuffle the input array */
    vector<int> shuffled_vec = source_vec;
    random_shuffle(shuffled_vec.begin(), shuffled_vec.end());

    /* Select a subset (first half) of the shuffled array */
    vector<int> subset(shuffled_vec.begin(), shuffled_vec.begin() + (shuffled_vec.size() / 2));

    /* Get sorted output for the subset */
    vector<int> subset_out = heap_sort(subset);

    /* Get sorted output for original input */
    vector<int> source_out = heap_sort(source_vec);

    /* Verification */
    bool is_subset = true;
    for (int elem : subset_out) {
        if (find(source_out.begin(), source_out.end(), elem) == source_out.end()) {
            is_subset = false;
            break;
        }
    }
    EXPECT_TRUE(is_subset);
}

/**
 * @brief Metamorphic Relation 20: Applying a transformation to the elements in the input array and then sorting should yield the same result as sorting the
 * original array and then applying the same transformation to the result.
 */
TEST_P(HeapSortParamTest, MR20) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get sorted output for original input */
    vector<int> source_out = heap_sort(source_vec);

    /* Applying a transformation to the sorted output */
    vector<int> transformed_sorted_output = source_out;
    for (int &elem : transformed_sorted_output) {
        elem = pow(elem, 2); // For example, squaring each element
    }

    /* Applying the same transformation to the original input and then sorting */
    vector<int> transformed_input = source_vec;
    for (int &elem : transformed_input) {
        elem = pow(elem, 2); // Applying the same transformation
    }
    vector<int> sorted_transformed_input = heap_sort(transformed_input);

    /* Verification */
    EXPECT_EQ(transformed_sorted_output, sorted_transformed_input);
}

/**
 * @brief Metamorphic Relation 21: Reversing the input array twice should yield the same sorted array as the original input.
 */
TEST_P(HeapSortParamTest, MR21) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Reverse the input array */
    reverse(source_vec.begin(), source_vec.end());

    /* Sort the reversed input array */
    vector<int> reversed_sorted_output = heap_sort(source_vec);

    /* Sort the original input */
    vector<int> source_out = heap_sort(input.vec);

    /* Reverse the sorted output from the original input */
    reverse(reversed_sorted_output.begin(), reversed_sorted_output.end());

    /* Verification */
    EXPECT_EQ(reversed_sorted_output, source_out);
}

/**
 * @brief Metamorphic Relation 22: Sorting an array with duplicate elements should yield the same result as sorting an array with the same elements, but without
 * duplicates.
 */
TEST_P(HeapSortParamTest, MR22) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Introduce duplicates in the input array */
    vector<int> duplicate_vec = source_vec;
    duplicate_vec.insert(duplicate_vec.end(), source_vec.begin(), source_vec.end());

    /* Sort the array with duplicates */
    vector<int> duplicate_out = heap_sort(duplicate_vec);

    /* Sort the array without duplicates */
    sort(source_vec.begin(), source_vec.end());
    vector<int> source_out = heap_sort(source_vec);

    /* Verification */
    EXPECT_EQ(duplicate_out, source_out);
}

/**
 * @brief Metamorphic Relation 23: Sorting an already sorted array should result in the same array.
 */
TEST_P(HeapSortParamTest, MR23) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the original input array */
    vector<int> sorted_output = heap_sort(source_vec);

    /* Sort the already sorted array */
    vector<int> re_sorted_output = heap_sort(sorted_output);

    /* Verification */
    EXPECT_EQ(re_sorted_output, sorted_output);
}

/**
 * @brief Metamorphic Relation 24: Sorting the input array and then applying a shift operation should yield the same result as applying the shift operation to
 * the input array and then sorting it.
 */
TEST_P(HeapSortParamTest, MR24) {
    int shiftAmount = 3;

    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the original input array */
    vector<int> original_sorted_output = heap_sort(source_vec);

    /* Apply the shift operation to the original sorted output */
    vector<int> shifted_original_sorted_output = original_sorted_output;
    rotate(shifted_original_sorted_output.rbegin(), shifted_original_sorted_output.rbegin() + shiftAmount, shifted_original_sorted_output.rend());

    /* Apply the shift operation to the original input and then sort it */
    vector<int> shifted_source_vec = source_vec;
    rotate(shifted_source_vec.rbegin(), shifted_source_vec.rbegin() + shiftAmount, shifted_source_vec.rend());
    vector<int> shifted_sorted_output = heap_sort(shifted_source_vec);

    /* Verification */
    EXPECT_EQ(shifted_original_sorted_output, shifted_sorted_output);
}

/**
 * @brief Metamorphic Relation 25: Sorting the input array and then reversing its every kth element should yield the same result as reversing the every kth
 * element of the input array and then sorting it.
 */
TEST_P(HeapSortParamTest, MR25) {
    int k = 3;

    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the original input array */
    vector<int> original_sorted_output = heap_sort(source_vec);

    /* Reverse every kth element of the original sorted output */
    vector<int> reversed_kth_original_sorted_output = original_sorted_output;
    for (size_t i = k - 1; i < reversed_kth_original_sorted_output.size(); i += k) {
        reverse(reversed_kth_original_sorted_output.begin() + i - k + 1, reversed_kth_original_sorted_output.begin() + i + 1);
    }

    /* Reverse every kth element of the input and then sort it */
    vector<int> reversed_kth_source_vec = source_vec;
    for (size_t i = k - 1; i < reversed_kth_source_vec.size(); i += k) {
        reverse(reversed_kth_source_vec.begin() + i - k + 1, reversed_kth_source_vec.begin() + i + 1);
    }
    vector<int> reversed_kth_sorted_output = heap_sort(reversed_kth_source_vec);

    /* Verification */
    EXPECT_EQ(reversed_kth_original_sorted_output, reversed_kth_sorted_output);
}

/**
 * @brief Metamorphic Relation 26: Sorting the distinct elements of the input array should yield the same result as sorting the original array with duplicates
 * and then removing the duplicates.
 */
TEST_P(HeapSortParamTest, MR26) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Introduce duplicates in the input array */
    vector<int> duplicate_vec = source_vec;
    duplicate_vec.insert(duplicate_vec.end(), source_vec.begin(), source_vec.end());

#if INVALID
    /* Sort the distinct elements of the original input */
    vector<int> distinct_sorted_output = heap_sort(set<int>(source_vec.begin(), source_vec.end()));
#else
    /* Fix by Radon */
    set<int> tmp = set<int>(source_vec.begin(), source_vec.end());
    vector<int> distinct_sorted_output = heap_sort(vector<int>(tmp.begin(), tmp.end()));
#endif

    /* Sort the array with duplicates and then remove duplicates */
    sort(duplicate_vec.begin(), duplicate_vec.end());
    duplicate_vec.erase(unique(duplicate_vec.begin(), duplicate_vec.end()), duplicate_vec.end());
    vector<int> sorted_without_duplicates_output = heap_sort(duplicate_vec);

    /* Verification */
    EXPECT_EQ(distinct_sorted_output, sorted_without_duplicates_output);
}

/**
 * @brief Metamorphic Relation 27: Sorting the input array should yield the same result as sorting a subarray of the input array.
 */
TEST_P(HeapSortParamTest, MR27) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    int size = source_vec.size();

    // Sort the entire input array
    vector<int> sorted_output = heap_sort(source_vec);

    // Sort a subarray of the input array
    vector<int> subarray(source_vec.begin() + 2, source_vec.begin() + size - 1);
    vector<int> subarray_sorted_output = heap_sort(subarray);

    // Verification
    EXPECT_EQ(sorted_output, subarray_sorted_output);
}

/**
 * @brief Metamorphic Relation 28: Sorting the input array should yield the same result as sorting the input array after removing one element.
 */
TEST_P(HeapSortParamTest, MR28) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    int size = source_vec.size();

    // Sort the entire input array
    vector<int> sorted_output = heap_sort(source_vec);

    // Sort the input array after removing the first element
    vector<int> modified_input(source_vec.begin() + 1, source_vec.end());
    vector<int> modified_input_sorted_output = heap_sort(modified_input);

    // Verification
    EXPECT_EQ(sorted_output, modified_input_sorted_output);
}

/**
 * @brief Metamorphic Relation 29: Sorting the input array should yield the same result as sorting the input array after replacing one element with another.
 */
TEST_P(HeapSortParamTest, MR29) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    int size = source_vec.size();

    // Sort the entire input array
    vector<int> sorted_output = heap_sort(source_vec);

    // Replace one element with another and sort the modified input array
    vector<int> modified_input = source_vec;
    modified_input[0] = 10; // Replace the first element with 10
    vector<int> modified_input_sorted_output = heap_sort(modified_input);

    // Verification
    EXPECT_EQ(sorted_output, modified_input_sorted_output);
}

/**
 * @brief Metamorphic Relation 30: Sorting the input array should yield the same result as sorting the input array after reversing its elements.
 */
TEST_P(HeapSortParamTest, MR30) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Sort the entire input array
    vector<int> sorted_output = heap_sort(source_vec);

    // Reverse the input array
    reverse(source_vec.begin(), source_vec.end());

    // Sort the reversed input array
    vector<int> reversed_sorted_output = heap_sort(source_vec);

    // Verification
    EXPECT_EQ(sorted_output, reversed_sorted_output);
}

/**
 * @brief Metamorphic Relation 31: Sorting the input array should yield the same result as sorting the input array with elements squared.
 */
TEST_P(HeapSortParamTest, MR31) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Sort the entire input array
    vector<int> sorted_output = heap_sort(source_vec);

    // Square each element in the input array
    for (int &elem : source_vec) {
        elem = elem * elem;
    }

    // Sort the squared input array
    vector<int> squared_sorted_output = heap_sort(source_vec);

    // Verification
    EXPECT_EQ(sorted_output, squared_sorted_output);
}

/**
 * @brief Metamorphic Relation 32: Sorting the input array should yield the same result as sorting a subarray of the input array (taking elements from the
 * middle).
 */
TEST_P(HeapSortParamTest, MR32) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    int size = source_vec.size();

    // Sort the entire input array
    vector<int> sorted_output = heap_sort(source_vec);

    // Sort a subarray of the input array (taking elements from the middle)
    int start = size / 4;
    int end = start + size / 2;
    vector<int> subarray_sorted_output = heap_sort(vector<int>(source_vec.begin() + start, source_vec.begin() + end));

    // Verification
    EXPECT_EQ(sorted_output, subarray_sorted_output);
}

/**
 * @brief Metamorphic Relation 33: Sorting the input array and then replacing negative elements with their absolute values should yield the same result as
 * replacing negative elements with their absolute values and then sorting the array.
 */
TEST_P(HeapSortParamTest, MR33) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the original input array */
    vector<int> sorted_output = heap_sort(source_vec);

    /* Replace negative elements with their absolute values in the sorted output */
    vector<int> abs_sorted_output = sorted_output;
    for (int &elem : abs_sorted_output) {
        elem = abs(elem);
    }

    /* Replace negative elements with their absolute values in the original input array and then sort it */
    vector<int> abs_source_vec = source_vec;
    for (int &elem : abs_source_vec) {
        elem = abs(elem);
    }
    vector<int> abs_sorted_input = heap_sort(abs_source_vec);

    /* Verification */
    EXPECT_EQ(abs_sorted_output, abs_sorted_input);
}

/**
 * @brief Metamorphic Relation 34: Sorting the input array and then multiplying each element by -1 should yield the same result as multiplying each element by
 * -1 and then sorting the array in reverse order.
 */
TEST_P(HeapSortParamTest, MR34) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the original input array */
    vector<int> sorted_output = heap_sort(source_vec);

    /* Multiply each element by -1 in the sorted output */
    vector<int> neg_sorted_output = sorted_output;
    for (int &elem : neg_sorted_output) {
        elem *= -1;
    }

    /* Multiply each element by -1 in the original input array and then sort it in reverse order */
    vector<int> neg_source_vec = source_vec;
    for (int &elem : neg_source_vec) {
        elem *= -1;
    }
    sort(neg_source_vec.begin(), neg_source_vec.end(), greater<int>());

    /* Verification */
    EXPECT_EQ(neg_sorted_output, neg_source_vec);
}

/**
 * @brief Metamorphic Relation 35: Sorting the input array and then taking the square root of each element should yield the same result as taking the square
 * root of each element and then sorting the array.
 */
TEST_P(HeapSortParamTest, MR35) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the original input array */
    vector<int> sorted_output = heap_sort(source_vec);

    /* Take the square root of each element in the sorted output */
    vector<int> sqrt_sorted_output = sorted_output;
    for (int &elem : sqrt_sorted_output) {
        elem = sqrt(elem);
    }

    /* Take the square root of each element in the original input array and then sort it */
    vector<int> sqrt_source_vec = source_vec;
    for (int &elem : sqrt_source_vec) {
        elem = sqrt(elem);
    }
    vector<int> sqrt_sorted_input = heap_sort(sqrt_source_vec);

    /* Verification */
    EXPECT_EQ(sqrt_sorted_output, sqrt_sorted_input);
}

/**
 * @brief Metamorphic Relation 36: Sorting the input array and then adding elements of a constant array should yield the same result as adding elements of the
 * constant array to the input array and then sorting it.
 */
TEST_P(HeapSortParamTest, MR36) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Create a constant array
    vector<int> constants = {5, 3, 8, 2};

    // Sort the original input array
    vector<int> sorted_output = heap_sort(source_vec);

    // Add elements of the constant array to the sorted output
    vector<int> modified_sorted_output = sorted_output;
    for (size_t i = 0; i < source_vec.size(); ++i) {
        modified_sorted_output[i] += constants[i % constants.size()];
    }

    // Add elements of the constant array to the original input array and then sort it
    vector<int> modified_input = source_vec;
    for (size_t i = 0; i < source_vec.size(); ++i) {
        modified_input[i] += constants[i % constants.size()];
    }
    vector<int> modified_sorted_input = heap_sort(modified_input);

    // Verification
    EXPECT_EQ(modified_sorted_output, modified_sorted_input);
}

/**
 * @brief Metamorphic Relation 37: Sorting the input array and then permuting its elements should yield the same result as permuting the input array and then
 * sorting it.
 */
TEST_P(HeapSortParamTest, MR37) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Sort the original input array
    vector<int> sorted_output = heap_sort(source_vec);

    // Permute the elements of the sorted output
    random_shuffle(sorted_output.begin(), sorted_output.end());

    // Permute the input array and then sort it
    vector<int> permuted_input = source_vec;
    random_shuffle(permuted_input.begin(), permuted_input.end());
    vector<int> permuted_sorted_input = heap_sort(permuted_input);

    // Verification
    EXPECT_EQ(sorted_output, permuted_sorted_input);
}

/**
 * @brief Metamorphic Relation 38: Sorting the input array and then multiplying each element by a constant should yield the same result as multiplying each
 * element by the constant and then sorting the array.
 */
TEST_P(HeapSortParamTest, MR38) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    int constant = 10;

    // Sort the original input array
    vector<int> sorted_output = heap_sort(source_vec);

    // Multiply each element by a constant in the sorted output
    vector<int> multiplied_sorted_output = sorted_output;
    for (int &elem : multiplied_sorted_output) {
        elem *= constant;
    }

    // Multiply each element by the constant in the input array and then sort it
    vector<int> multiplied_input = source_vec;
    for (int &elem : multiplied_input) {
        elem *= constant;
    }
    vector<int> multiplied_sorted_input = heap_sort(multiplied_input);

    // Verification
    EXPECT_EQ(multiplied_sorted_output, multiplied_sorted_input);
}

/**
 * @brief Metamorphic Relation 39: Sorting non-positive elements of the input array should yield the same result as sorting the non-positive elements rest of
 * the elements in the input array and then concatenating the two sorted sets.
 */
TEST_P(HeapSortParamTest, MR39) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Sort the entire input array
    vector<int> sorted_output = heap_sort(source_vec);

    // Separate non-positive and positive elements
    vector<int> non_positive_elements, remaining_elements;
    for (int element : source_vec) {
        if (element <= 0) {
            non_positive_elements.push_back(element);
        } else {
            remaining_elements.push_back(element);
        }
    }

    // Sort the non-positive elements
    vector<int> sorted_non_positive_elements = heap_sort(non_positive_elements);

    // Sort the remaining elements
    vector<int> sorted_remaining_elements = heap_sort(remaining_elements);

    // Merge the two sorted sets
    sorted_non_positive_elements.insert(sorted_non_positive_elements.end(), sorted_remaining_elements.begin(), sorted_remaining_elements.end());

    // Verification
    EXPECT_EQ(sorted_output, sorted_non_positive_elements);
}

/**
 * @brief Metamorphic Relation 40: Sorting the input array and then appending a constant element at the end should yield the same result as appending the
 * constant element to the input array and then sorting it.
 */
TEST_P(HeapSortParamTest, MR40) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    // Constant to append
    int constant = 100;

    // Sort the original input array
    vector<int> sorted_output = heap_sort(source_vec);

    // Append the constant element to the sorted output
    vector<int> appended_sorted_output = sorted_output;
    appended_sorted_output.push_back(constant);

    // Append the constant element to the original input array and then sort it
    vector<int> appended_input = source_vec;
    appended_input.push_back(constant);
    vector<int> appended_sorted_input = heap_sort(appended_input);

    // Verification
    EXPECT_EQ(appended_sorted_output, appended_sorted_input);
}

/**
 * @brief Metamorphic Relation 41: Sorting the input array and then rotating it rightwards by a certain number of positions should yield the same result as rotating the input array rightwards by the same number of positions and then sorting it.
 */
TEST_P(HeapSortParamTest, MR41) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    int shiftAmount = 3;

    // Sort the original input array
    vector<int> sorted_output = heap_sort(source_vec);

    // Rotate the sorted output rightwards
    vector<int> rotated_sorted_output = sorted_output;
    rotate(rotated_sorted_output.rbegin(), rotated_sorted_output.rbegin() + shiftAmount, rotated_sorted_output.rend());

    // Rotate the input array rightwards and then sort it
    vector<int> rotated_input = source_vec;
    rotate(rotated_input.rbegin(), rotated_input.rbegin() + shiftAmount, rotated_input.rend());
    vector<int> rotated_sorted_input = heap_sort(rotated_input);

    // Verification
    EXPECT_EQ(rotated_sorted_output, rotated_sorted_input);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, HeapSortParamTest, testing::ValuesIn(gen_tcs_randomly()));