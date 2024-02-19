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
 * @brief Metamorphic Relation 1: Reversing the elements in the input array, the output will be sorted in descending order.
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
    sort(source_out.begin(), source_out.end(), greater<int>());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 2: Adding a constant to each element in the input array, then the output will be sorted in ascending order, and all elements will be larger by the constant.
 *
 */
TEST_P(HeapSortParamTest, MR2) {
    int constant = 5;

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
    sort(source_out.begin(), source_out.end());
    for (auto &elem : follow_out)
        elem -= constant;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 3: Multiplying -1 to each element in the input array, then the output will be sorted in descending order, and if we multiply -1 to each element of the output array, it should be the same as the source output array.
 *
 */
TEST_P(HeapSortParamTest, MR3) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem *= -1;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    sort(source_out.begin(), source_out.end(), greater<int>());
    for (auto &elem : follow_out)
        elem *= -1;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 4: Replacing elements in the input array with their square, then the output will be in ascending sorted order.
 *
 */
TEST_P(HeapSortParamTest, MR4) {
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
    sort(source_out.begin(), source_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 5: Replacing elements in the input array with their absolute values, then the output will be the same as if the input array remained unchanged.
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
        elem = abs(elem);

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 6: Replacing elements in the input array with their negative values, then if we multiply -1 to each element of the output array, it should be the same as the source output array but in reverse order.
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
    for (auto &elem : follow_vec)
        elem = -elem;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    for (auto &elem : follow_out)
        elem *= -1;
    reverse(follow_out.begin(), follow_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 7: Replacing the input array with its reverse, then the output will be in descending sorted order.
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
    sort(source_out.begin(), source_out.end(), greater<int>());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 8: Scaling all elements in the input array by a constant, then the output will be sorted in ascending order, and all elements will be scaled by the constant.
 *
 */
TEST_P(HeapSortParamTest, MR8) {
    int constant = 2;

    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem *= constant;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    sort(source_out.begin(), source_out.end());
    for (auto &elem : follow_out)
        elem /= constant;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 9: Adding a constant to each element in the input array, then the output will be sorted in ascending order, and all elements will be larger by the constant.
 *
 */
TEST_P(HeapSortParamTest, MR9) {
    int constant = 10;

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
    sort(source_out.begin(), source_out.end());
    for (auto &elem : follow_out)
        elem -= constant;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 10: Sorting a subset of the input array, then the output will be the same as the result of sorting the entire input array.
 *
 */
TEST_P(HeapSortParamTest, MR10) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Generate a random subset size
    int subset_size = rand() % source_vec.size();

    // Select random subset indices
    vector<int> indices(subset_size);
    iota(indices.begin(), indices.end(), 0);
    random_shuffle(indices.begin(), indices.end(), [](int i) { return rand() % i; });

    // Sort the subset
    sort(indices.begin(), indices.end(), [&](int i, int j) { return source_vec[i] < source_vec[j]; });

    // Copy the sorted subset to a new vector
    vector<int> sorted_subset(subset_size);
    transform(indices.begin(), indices.end(), sorted_subset.begin(), [&](int idx) { return source_vec[idx]; });

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int i = 0; i < subset_size; i++)
        follow_vec[indices[i]] = sorted_subset[i];

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 11: Replacing the input array with its prefix sum, then the output will be sorted in ascending order.
 *
 */
TEST_P(HeapSortParamTest, MR11) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec(source_vec.size());
    partial_sum(source_vec.begin(), source_vec.end(), follow_vec.begin());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    sort(source_out.begin(), source_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 12: Replacing the input array with its suffix sum, then the output will be sorted in ascending order.
 *
 */
TEST_P(HeapSortParamTest, MR12) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec(source_vec.size());
    partial_sum(source_vec.rbegin(), source_vec.rend(), follow_vec.rbegin());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    sort(source_out.begin(), source_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 13: Replacing the input array with a sorted array, then the output will be the same as the result of sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR13) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the source input */
    sort(source_vec.begin(), source_vec.end());

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 14: Reversing the input array and then reversing the range [l, r] in the array, then the output will remain the same after reversing the range [l, r] in the initial input.
 *
 */
TEST_P(HeapSortParamTest, MR14) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Reverse the input array */
    reverse(source_vec.begin(), source_vec.end());

    /* Randomly select range [l, r] */
    int l = rand() % source_vec.size();
    int r = rand() % source_vec.size();
    if (l > r) swap(l, r);

    /* Reverse the range [l, r] in the reversed array */
    reverse(source_vec.begin() + l, source_vec.begin() + r + 1);

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(source_vec);

    /* Reverse the range [l, r] in the initial input array */
    reverse(source_out.begin() + l, source_out.begin() + r + 1);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 15: Reversing the input array and then reversing the range [l, r] in the array, then the output will be the same as reversing the original range [l, r] in the output obtained from the initial input.
 *
 */
TEST_P(HeapSortParamTest, MR15) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Reverse the input array */
    reverse(source_vec.begin(), source_vec.end());

    /* Randomly select range [l, r] */
    int l = rand() % source_vec.size();
    int r = rand() % source_vec.size();
    if (l > r) swap(l, r);

    /* Reverse the range [l, r] in the reversed array */
    reverse(source_vec.begin() + l, source_vec.begin() + r + 1);

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(source_vec);

    /* Reverse the range [l, r] in the initial output array */
    reverse(source_out.begin() + l, source_out.begin() + r + 1);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 16: Replacing the input array with its kth permutation, then the output will be sorted in ascending order.
 *
 */
TEST_P(HeapSortParamTest, MR16) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Constants */
    const int k = 3;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int i = 0; i < k; ++i) {
        next_permutation(follow_vec.begin(), follow_vec.end());
    }

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    sort(source_out.begin(), source_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 17: Replacing the input array with elements in non-decreasing order, then the output will be the same as the result of sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR17) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the source input in non-decreasing order */
    sort(source_vec.begin(), source_vec.end());

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 18: Replacing the array with all the same elements, then the output will remain the same as the result of sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR18) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Set all elements in the source input to the first element */
    for (int i = 1; i < source_vec.size(); ++i) {
        source_vec[i] = source_vec[0];
    }

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 19: Replacing the input array with a sequence of consecutive integers, then the output will be the same as the result of sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR19) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Generate a sequence of consecutive integers */
    for (int i = 0; i < source_vec.size(); ++i) {
        source_vec[i] = i;
    }

    /* Get source output */
    vector<int> source_out = heap_sort(input.vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(input.vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 20: Replacing the input array with its prefix array, then the output will remain the same as the result of sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR20) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get prefix sum array */
    partial_sum(source_vec.begin(), source_vec.end(), source_vec.begin());

    /* Get source output */
    vector<int> source_out = heap_sort(input.vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    rotate(follow_vec.begin(), follow_vec.begin() + 1, follow_vec.end()); // Right rotate one position

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 21: Replacing the input array with its suffix array, then the output will remain the same as the result of sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR21) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get suffix sum array */
    partial_sum(source_vec.rbegin(), source_vec.rend(), source_vec.rbegin());

    /* Get source output */
    vector<int> source_out = heap_sort(input.vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    rotate(follow_vec.rbegin(), follow_vec.rbegin() + 1, follow_vec.rend()); // Right rotate one position

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 22: Negating all elements in the input array, then the output will be the same as the result of sorting the original input array in reverse order.
 *
 */
TEST_P(HeapSortParamTest, MR22) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Negate all elements in the source input */
    for (int i = 0; i < source_vec.size(); ++i) {
        source_vec[i] = -source_vec[i];
    }

    /* Get source output */
    vector<int> source_out = heap_sort(input.vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);
    reverse(follow_out.begin(), follow_out.end()); // Reverse the output

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 23: Replacing the input array with its square root, then the output will remain the same as the result of sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR23) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Replace elements in the source input with their square root */
    for (int i = 0; i < source_vec.size(); ++i) {
        source_vec[i] = sqrt(source_vec[i]);
    }

    /* Get source output */
    vector<int> source_out = heap_sort(input.vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 24: Replacing the input array with elements in descending order, then the output will be the same as the result of sorting the original input array in reverse order.
 *
 */
TEST_P(HeapSortParamTest, MR24) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the source input in descending order */
    sort(source_vec.begin(), source_vec.end(), greater<int>());

    /* Get source output */
    vector<int> source_out = heap_sort(input.vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);
    reverse(follow_out.begin(), follow_out.end()); // Reverse the output

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 25: Replacing the input array with its cumulative product, then the output will be sorted in ascending order.
 *
 */
TEST_P(HeapSortParamTest, MR25) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Compute the cumulative product of the source input */
    for (int i = 1; i < source_vec.size(); ++i) {
        source_vec[i] *= source_vec[i - 1];
    }

    /* Get source output */
    vector<int> source_out = heap_sort(input.vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 26: Replacing the input array with elements in ascending order, then the output will be sorted in ascending order.
 *
 */
TEST_P(HeapSortParamTest, MR26) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the source input in ascending order */
    sort(source_vec.begin(), source_vec.end());

    /* Get source output */
    vector<int> source_out = heap_sort(input.vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 27: Replacing the input array with elements in descending order, then the output will be sorted in descending order.
 *
 */
TEST_P(HeapSortParamTest, MR27) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the source input in descending order */
    sort(source_vec.rbegin(), source_vec.rend());

    /* Get source output */
    vector<int> source_out = heap_sort(input.vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    sort(source_out.begin(), source_out.end(), greater<int>());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 28: Rotating the input array to the left, then the output will be the same as the result of sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR28) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Left rotate the source input */
    rotate(source_vec.begin(), source_vec.begin() + 1, source_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(source_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 29: Rotating the input array to the right, then the output will be the same as the result of sorting the original input array.
 *
 */
TEST_P(HeapSortParamTest, MR29) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Right rotate the source input */
    rotate(source_vec.rbegin(), source_vec.rbegin() + 1, source_vec.rend());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(source_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 30: Replacing the input array with a random permutation, then the output will be sorted in ascending order.
 *
 */
TEST_P(HeapSortParamTest, MR30) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(input.vec);

    /* Generate a random permutation */
    random_shuffle(source_vec.begin(), source_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(source_vec);

    /* Verification */
    sort(source_out.begin(), source_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 31: Appending a constant value to each element in the input array, then the output will be sorted in ascending order and all elements will be greater by the constant.
 *
 */
TEST_P(HeapSortParamTest, MR31) {
    const int constant = 5;

    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto& elem : follow_vec)
        elem += constant;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    for (auto& elem : follow_out)
        elem -= constant;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 32: Multiplying each element in the input array by a constant value, then the output will be sorted in ascending order and all elements will be larger by a factor of the constant.
 *
 */
TEST_P(HeapSortParamTest, MR32) {
    const int constant = 3;

    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto& elem : follow_vec)
        elem *= constant;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    for (auto& elem : follow_out)
        elem /= constant;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 33: Subtracting each element in the input array by a constant value, then the output will be sorted in ascending order and all elements will be reduced by the constant.
 *
 */
TEST_P(HeapSortParamTest, MR33) {
    const int constant = 4;

    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto& elem : follow_vec)
        elem -= constant;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    for (auto& elem : follow_out)
        elem += constant;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 34: Testing the algorithm with an empty input array, the output should also be an empty array or vector.
 *
 */
TEST(HeapSortTest, MR34) {
    /* Prepare empty input */
    vector<int> source_vec;

    /* Call the function under test */
    vector<int> result_vec = heap_sort(source_vec);

    /* Verify that the result is also empty */
    EXPECT_TRUE(result_vec.empty());
}

/**
 * @brief Metamorphic Relation 35: Repeating the same value in the input array, the output will also have the same repeated value.
 *
 */
TEST_P(HeapSortParamTest, MR35) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Set all elements in the source input to a specific value */
    for (int i = 1; i < source_vec.size(); ++i) {
        source_vec[i] = source_vec[0];
    }

    /* Get source output */
    vector<int> source_out = heap_sort(input.vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 36: Reversing the array twice, the output should be the same as the initial input since the array is back to its original order.
 *
 */
TEST_P(HeapSortParamTest, MR36) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Reverse the input array twice */
    reverse(source_vec.begin(), source_vec.end());
    reverse(source_vec.begin(), source_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(source_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 37: Applying the function on a monotonically increasing input array, the output should also be in ascending order.
 *
 */
TEST_P(HeapSortParamTest, MR37) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(input.vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 38: Applying the function on a monotonically decreasing input array, the output should also be in ascending order.
 *
 */
TEST_P(HeapSortParamTest, MR38) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(input.vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    sort(follow_vec.rbegin(), follow_vec.rend());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    sort(source_out.begin(), source_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 39: Applying the function on an array with all elements incrementing by 1, the output should also have elements incrementing by 1.
 *
 */
TEST_P(HeapSortParamTest, MR39) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(input.vec);

    /* Construct follow-up input */
    vector<int> follow_vec(source_vec.size());
    iota(follow_vec.begin(), follow_vec.end(), source_vec[0]);

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 40: Applying the function on an array with elements repeating in a pattern, the output should also repeat the same pattern.
 *
 */
TEST_P(HeapSortParamTest, MR40) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(input.vec);

    /* Construct follow-up input with a repeating pattern */
    vector<int> follow_vec(source_vec.size());
    for (size_t i = 0; i < source_vec.size(); ++i)
        follow_vec[i] = i % 2;  // Alternating 0s and 1s pattern

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 41: Applying the function on an array with a single element, the output should be the same single element. 
 * 
 */
TEST(HeapSortTest, MR41) {
    /* Create input array with a single element */
    vector<int> source_vec = {5};

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Expected output should be the same single element */
    vector<int> expected_out = {5};

    /* Verification */
    EXPECT_EQ(source_out, expected_out);
}

/**
 * @brief Metamorphic Relation 42: Applying the function on an array with all elements equal, the output should also have all elements equal.
 * 
 */
TEST_P(HeapSortParamTest, MR42) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec(input.vec.size(), 10); // Initialize all elements with value 10

    /* Get source output */
    vector<int> source_out = heap_sort(input.vec);

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(source_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, HeapSortParamTest, testing::ValuesIn(gen_tcs_randomly()));
