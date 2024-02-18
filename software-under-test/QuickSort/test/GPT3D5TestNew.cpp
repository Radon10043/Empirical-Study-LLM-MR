#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class QuickSortParamTest : public ::testing::TestWithParam<QuickSortInput> {};

/**
 * @brief Metamorphic Relation 1: Reversing the elements in the input array, the output will be in the reverse order of the source output.
 */
TEST_P(QuickSortParamTest, MR1) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    reverse(source_out.begin(), source_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 2: Doubling each element in the input array, the output will remain the same relative order, only the value will be doubled.
 */
TEST_P(QuickSortParamTest, MR2) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem *= 2;

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    for (auto &elem : source_out)
        elem *= 2;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief  * Metamorphic Relation 3: Subtracting a constant from each element in the input array, then the output array is still in ascending order.
 */
TEST_P(QuickSortParamTest, MR3) {
    int constant = 5;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem -= constant;

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 4: Appending duplicate elements to the input array, the output array will have the same relative order as the source output, with the duplicates appearing after their original counterparts.
 */
TEST_P(QuickSortParamTest, MR4) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.insert(follow_vec.end(), source_vec.begin(), source_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 5: Replacing all elements with the maximum value in the input array, the output will have every element equal to the maximum value, as the array will be sorted.
 */
TEST_P(QuickSortParamTest, MR5) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec(source_vec.size(), *max_element(source_vec.begin(), source_vec.end()));

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 6: Appending the input array with an increasing sequence, the output array will be the same as the source output with the increasing sequence appended at the end.
 */
TEST_P(QuickSortParamTest, MR6) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    int max_elem = *max_element(source_vec.begin(), source_vec.end());
    for (int i = max_elem; i < max_elem + source_vec.size(); ++i) {
        follow_vec.push_back(i);
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 7: Reversing the order of elements in the input array, the output array will be sorted in descending order.
 */
TEST_P(QuickSortParamTest, MR7) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    reverse(source_out.begin(), source_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 8: Adding a constant to each element in the input array, then each element of the output array will be larger by the constant than the element at the same location of the source output.
 */
TEST_P(QuickSortParamTest, MR8) {
    int constant = 2;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem += constant;

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    for (auto &elem : source_out)
        elem += constant;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 9: Multiplying each element in the input array by -1, then the output array will be sorted in descending order.
 */
TEST_P(QuickSortParamTest, MR9) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem *= -1;

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    reverse(source_out.begin(), source_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 10: Multiplying each element in the input array by a positive constant c, the output array will be in ascending order, with each element c times larger than the corresponding element of the source output.
 */
TEST_P(QuickSortParamTest, MR10) {
    int constant = 3;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem *= constant;

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    vector<int> expected_out = source_out;
    for (auto &elem : expected_out)
        elem *= constant;
    EXPECT_EQ(follow_out, expected_out);
}

/**
 * @brief Metamorphic Relation 11: Multiplying each element in the input array by a negative constant c, the output array will be sorted in descending order, with each element c times smaller than the corresponding element of the source output.
 */
TEST_P(QuickSortParamTest, MR11) {
    int constant = -2;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem *= constant;

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    reverse(source_out.begin(), source_out.end());
    vector<int> expected_out = source_out;
    for (auto &elem : expected_out)
        elem *= constant;
    EXPECT_EQ(follow_out, expected_out);
}

/**
 * @brief Metamorphic Relation 12: Adding a constantly increasing sequence to the input array, the output array will have the same relative order as the source output, with the increasing sequence appended at the end.
 */
TEST_P(QuickSortParamTest, MR12) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    int max_elem = *max_element(source_vec.begin(), source_vec.end());
    for (int i = max_elem; i < max_elem + source_vec.size(); ++i) {
        follow_vec.push_back(i);
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 13: Reversing the first half of the input array, the output will be the same as the source output.
 */
TEST_P(QuickSortParamTest, MR13) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    reverse(follow_vec.begin(), follow_vec.begin() + follow_vec.size() / 2);

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 14: Appending a decreasing sequence to the input array, the output array will be sorted in ascending order, with the decreasing sequence appended at the end.
 */
TEST_P(QuickSortParamTest, MR14) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int i = source_vec.size(); i > 0; --i) {
        follow_vec.push_back(i);
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 15: Sorting the input array in ascending order, the output will be the same as the source output.
 */
TEST_P(QuickSortParamTest, MR15) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    sort(source_vec.begin(), source_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 16: Swapping two random elements in the input array, the output array will have the same relative order as the source output, with the two elements swapped.
 */
TEST_P(QuickSortParamTest, MR16) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    if (follow_vec.size() >= 2) {
        int idx1 = rand() % follow_vec.size();
        int idx2 = rand() % follow_vec.size();
        swap(follow_vec[idx1], follow_vec[idx2]);
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 17: Rotating the input array, the output array will have the same relative order as the source output, just shifted.
 */
TEST_P(QuickSortParamTest, MR17) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    rotate(follow_vec.begin(), follow_vec.begin() + 1, follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 18: Appending the input array with a constant value, the output array will have the same relative order as the source output, with the appended value at the end.
 */
TEST_P(QuickSortParamTest, MR18) {
    int constant = 10;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.push_back(constant);

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 19: Applying a random permutation to the input array, the output array will have the same relative order as the source output, with the elements permuted accordingly.
 */
TEST_P(QuickSortParamTest, MR19) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    random_shuffle(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    sort(source_out.begin(), source_out.end());  // Sort source_out to compare with the sorted follow_out
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 20: Replacing each element in the input array by its square, the output array will be sorted in ascending order.
 */
TEST_P(QuickSortParamTest, MR20) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec(source_vec.size());
    transform(source_vec.begin(), source_vec.end(), follow_vec.begin(), [](int x){ return x * x; });

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 21: Sorting the input array in descending order, the output array will be sorted in ascending order.
 */
TEST_P(QuickSortParamTest, MR21) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    sort(source_vec.rbegin(), source_vec.rend());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(source_vec);

    /* Verification */
    sort(source_out.begin(), source_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 22: Taking the absolute value of each element in the input array, the output array will have the same relative order as the source output, as the sorting is not affected by the element signs.
 */
TEST_P(QuickSortParamTest, MR22) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec(source_vec.size());
    transform(source_vec.begin(), source_vec.end(), follow_vec.begin(), [](int x){ return abs(x); });

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 23: Shifting all elements in the input array by a constant value, the output array will have the same relative order as the source output, just shifted.
 */
TEST_P(QuickSortParamTest, MR23) {
    int shift_value = 3;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem += shift_value;

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 24: Appending the input array with a decreasing sequence, the output array will be sorted in ascending order, with the decreasing sequence appended at the end.
 */
TEST_P(QuickSortParamTest, MR24) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int i = source_vec.size(); i > 0; --i) {
        follow_vec.push_back(i);
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 25: Multiplying each element in the input array by a constant and then adding another constant to each element, the output array will be sorted in ascending order.
 */
TEST_P(QuickSortParamTest, MR25) {
    int multiplier = 2;
    int addend = 5;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem = elem * multiplier + addend;

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 26: Replacing each even-indexed element in the input array with a constant, the output array will have the same relative order as the source output, with the modified elements.
 */
TEST_P(QuickSortParamTest, MR26) {
    int replacement_value = 10;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int i = 0; i < follow_vec.size(); i += 2) {
        follow_vec[i] = replacement_value;
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 27: Multiplying each element in the input array by -1, the output array will be sorted in descending order.
 */
TEST_P(QuickSortParamTest, MR27) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem *= -1;

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    reverse(source_out.begin(), source_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 28: Appending the input array with a constant value, the output array will have the same relative order as the source output, with the appended value at the end.
 */
TEST_P(QuickSortParamTest, MR28) {
    int append_value = 100;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.push_back(append_value);

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 29: Repeating the input array multiple times, the output array will have the same relative order as the source output, with the repeated elements.
 */
TEST_P(QuickSortParamTest, MR29) {
    int num_repeats = 3;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int i = 0; i < num_repeats; ++i) {
        follow_vec.insert(follow_vec.end(), source_vec.begin(), source_vec.end());
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 30: Swapping the first and last elements of the input array, the output array will have the same relative order as the source output, with the two elements swapped.
 */
TEST_P(QuickSortParamTest, MR30) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    if (!follow_vec.empty()) {
        swap(follow_vec.front(), follow_vec.back());
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 31: Replacing all elements of the input array with a single constant value, the output array will have the same relative order as the source output, with all elements equal to the constant value.
 */
TEST_P(QuickSortParamTest, MR31) {
    int constant_value = 42;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec(source_vec.size(), constant_value);

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 32: Sorting the input array in ascending order, the output will remain the same.
 */
TEST_P(QuickSortParamTest, MR32) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Sort the source vector */
    sort(source_vec.begin(), source_vec.end());

    /* Verification */
    EXPECT_EQ(quick_sort(source_vec), source_out);
}

/**
 * @brief Metamorphic Relation 33: Sorting the input array in descending order, the output array will be sorted in ascending order.
 */
TEST_P(QuickSortParamTest, MR33) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    /* Sort the source vector in descending order */
    sort(source_vec.rbegin(), source_vec.rend());

    /* Verification */
    auto follow_out = quick_sort(source_vec);
    sort(source_vec.begin(), source_vec.end());
    EXPECT_EQ(follow_out, source_vec);
}

/**
 * @brief Metamorphic Relation 34: Randomly shuffling the elements in the input array, the output array will have the same relative order as the source output, regardless of the shuffling.
 */
TEST_P(QuickSortParamTest, MR34) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    random_shuffle(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 35: Sorting the input array in ascending order, then reversing it, the output will be sorted in descending order.
 */
TEST_P(QuickSortParamTest, MR35) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output after sorting in ascending order */
    vector<int> source_out_sorted = quick_sort(source_vec);

    /* Reverse the sorted output */
    reverse(source_out_sorted.begin(), source_out_sorted.end());

    /* Verification */
    auto follow_out = quick_sort(source_out_sorted);
    reverse(source_out_sorted.begin(), source_out_sorted.end());
    EXPECT_EQ(follow_out, source_out_sorted);
}

/**
 * @brief Metamorphic Relation 36: Sorting the elements of the input array in descending order, the output will be sorted in ascending order.
 */
TEST_P(QuickSortParamTest, MR36) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the source vector in descending order */
    sort(source_vec.rbegin(), source_vec.rend());

    /* Verification */
    auto follow_out = quick_sort(source_vec);
    sort(source_vec.begin(), source_vec.end());
    EXPECT_EQ(follow_out, source_vec);
}

/**
 * @brief Metamorphic Relation 37: Sorting the input array in ascending order, then applying a cyclic permutation to the array, the output will have the same relative order as the source output, just shifted.
 */
TEST_P(QuickSortParamTest, MR37) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output after sorting in ascending order */
    vector<int> source_out_sorted = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    rotate(follow_vec.begin(), follow_vec.begin() + 1, follow_vec.end());  // Applying cyclic permutation

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out_sorted);
}

/**
 * @brief Metamorphic Relation 38: Sorting the input array and then reversing it, the output will be sorted in descending order.
 */
TEST_P(QuickSortParamTest, MR38) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output after sorting in ascending order */
    vector<int> source_out_sorted = quick_sort(source_vec);

    /* Reverse the sorted output */
    reverse(source_out_sorted.begin(), source_out_sorted.end());

    /* Verification */
    auto follow_out = quick_sort(source_out_sorted);
    reverse(source_out_sorted.begin(), source_out_sorted.end());
    EXPECT_EQ(follow_out, source_out_sorted);
}

/**
 * @brief Metamorphic Relation 39: Sorting the input array and then appending the sorted array with a decreasing sequence, the output array will be sorted in ascending order, with the decreasing sequence appended at the end.
 */
TEST_P(QuickSortParamTest, MR39) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output after sorting in ascending order */
    vector<int> source_out_sorted = quick_sort(source_vec);

    /* Construct follow-up input by appending the sorted array with a decreasing sequence */
    vector<int> follow_vec = source_out_sorted;
    for (int i = source_vec.size(); i > 0; --i) {
        follow_vec.push_back(i);
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out_sorted);
}

/**
 * @brief Metamorphic Relation 40: Replacing each element in the input array by the negative of its value, the output array will be in reverse order to the source output.
 */
TEST_P(QuickSortParamTest, MR40) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &element : follow_vec) {
        element = -element;
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    reverse(source_out.begin(), source_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 41: Sorting the input array and then replacing all elements with the maximum value, the output array will have every element equal to the maximum value, as the array will be sorted.
 */
TEST_P(QuickSortParamTest, MR41) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    /* Get source output after sorting in ascending order */
    vector<int> source_out_sorted = quick_sort(source_vec);

    /* Construct follow-up input, replacing all elements with the maximum */
    vector<int> follow_vec(source_vec.size(), *max_element(source_vec.begin(), source_vec.end()));

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out_sorted);
}

/**
 * @brief Metamorphic Relation 42: Sorting the input array and then appending the sorted array with an increasing sequence, the output array will have the same relative order as the source output, with the increasing sequence appended at the end.
 */
TEST_P(QuickSortParamTest, MR42) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output after sorting in ascending order */
    vector<int> source_out_sorted = quick_sort(source_vec);

    /* Construct follow-up input by appending the sorted array with an increasing sequence */
    vector<int> follow_vec = source_out_sorted;
    int max_elem = *max_element(source_vec.begin(), source_vec.end());
    for (int i = max_elem; i < max_elem + source_vec.size(); ++i) {
        follow_vec.push_back(i);
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out_sorted);
}

/**
 * @brief Metamorphic Relation 43: Sorting the first half of the input array, the output will form a prefix of the source output.
 */
TEST_P(QuickSortParamTest, MR43) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output after sorting in ascending order */
    vector<int> source_out_sorted = quick_sort(source_vec);

    /* Construct follow-up input by sorting the first half of the input array */
    vector<int> follow_vec = source_vec;
    sort(follow_vec.begin(), follow_vec.begin() + (follow_vec.size() / 2));

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    bool is_prefix = true;
    for (int i = 0; i < follow_out.size(); ++i) {
        if (follow_out[i] != source_out_sorted[i]) {
            is_prefix = false;
            break;
        }
    }
    EXPECT_TRUE(is_prefix);
}

/**
 * @brief Metamorphic Relation 44: Appending the input array with a duplicate of itself, the output array will have the same relative order as the source output, with the duplicate elements appearing after their original counterparts.
 */
TEST_P(QuickSortParamTest, MR44) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output after sorting in ascending order */
    vector<int> source_out_sorted = quick_sort(source_vec);

    /* Construct follow-up input by appending the input array with itself */
    vector<int> follow_vec = source_vec;
    follow_vec.insert(follow_vec.end(), source_vec.begin(), source_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out_sorted);
}

/**
 * @brief Metamorphic Relation 45: Reversing the input array, the output will be in reverse order of the source output.
 */
TEST_P(QuickSortParamTest, MR45) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output after sorting in ascending order */
    vector<int> source_out_sorted = quick_sort(source_vec);

    /* Construct follow-up input by reversing the input array */
    vector<int> follow_vec = source_vec;
    reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    reverse(source_out_sorted.begin(), source_out_sorted.end());
    EXPECT_EQ(follow_out, source_out_sorted);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, QuickSortParamTest, testing::ValuesIn(gen_tcs_randomly()));
