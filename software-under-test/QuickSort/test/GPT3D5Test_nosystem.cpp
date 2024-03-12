#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class QuickSortParamTest : public ::testing::TestWithParam<QuickSortInput> {};

/**
 * @brief Metamorphic Relation 1: Reversing the elements in the input array, the output will also be reversed.
 *
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
    reverse(follow_out.begin(), follow_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 2: Adding a constant to each element in the input array, then each element of the output array will be larger by the constant
 * than the element at the same location of the source input.
 *
 */
TEST_P(QuickSortParamTest, MR2) {
    int constant = 3;

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
    for (auto &elem : follow_out)
        elem -= constant;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 3: Multiplying -1 to each element in the input array, then the output will also be multiplied by -1.
 *
 */
TEST_P(QuickSortParamTest, MR3) {
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
    for (auto &elem : follow_out)
        elem *= -1;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 4: Concatenating two input arrays and sorting the concatenated array is equivalent to sorting each array individually and then concatenating and sorting the combined array.
 *
 */
TEST_P(QuickSortParamTest, MR4) {   // Fixed
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> tmp_vec = source_vec;
    tmp_vec.insert(tmp_vec.end(), source_vec.begin(), source_vec.end());
    vector<int> source_out = quick_sort(tmp_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    vector<int> another_vec = follow_vec;
    sort(follow_vec.begin(), follow_vec.end());
    sort(another_vec.begin(), another_vec.end());
    vector<int> combined_vec;
    combined_vec.reserve(follow_vec.size() + another_vec.size());
    combined_vec.insert(combined_vec.end(), follow_vec.begin(), follow_vec.end());
    combined_vec.insert(combined_vec.end(), another_vec.begin(), another_vec.end());
    vector<int> combined_out = quick_sort(combined_vec);

    /* Verification */
    EXPECT_EQ(combined_out, source_out);
}

/**
 * @brief Metamorphic Relation 5: Repeating the elements in the input array multiple times does not change the output after sorting.
 *
 */
TEST_P(QuickSortParamTest, MR5) {
    int repeat_factor = 3;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int elem : source_vec) {
        for (int i = 0; i < repeat_factor; i++) follow_vec.push_back(elem);
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 6: Replacing all elements in the input array with their squares results in the same output array after sorting.
 *
 */
TEST_P(QuickSortParamTest, MR6) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec) elem = elem * elem;

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 7: Reversing the order of input arrays leads to the output array being sorted in the reverse order.
 *
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
    reverse(follow_out.begin(), follow_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 8: Appending a constant value to each element in the input array results in the same output array after sorting.
 *
 */
TEST_P(QuickSortParamTest, MR8) {
    int constant = 10;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec) elem += constant;

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 9: Multiplying all elements in the input array by a constant results in the same output array after sorting.
 */
TEST_P(QuickSortParamTest, MR9) {
    int constant = 5;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto& elem : follow_vec) elem *= constant;

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 10: If all elements in the input array are the same, the output should be the same as the input array.
 */
TEST_P(QuickSortParamTest, MR10) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Set all elements to the same value */
    for (auto& elem : source_vec) elem = 10;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 11: If all elements in the input array are in descending order, the output should be the same as the input array but in ascending order.
 */
TEST_P(QuickSortParamTest, MR11) {  // Fixed
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    sort(follow_vec.rbegin(), follow_vec.rend());

    /* Get the follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 12: If the input array is already sorted, the output should remain the same.
 */
TEST_P(QuickSortParamTest, MR12) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Sort the source vector */
    sort(source_vec.begin(), source_vec.end());

    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 13: If every element in the input array is greater than a constant, then the output array should be the same as the input array.
 */
TEST_P(QuickSortParamTest, MR13) {
    int constant = 100;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Replace all elements in the input array with the constant */
    for (auto& elem : source_vec) {
        elem = constant + 1;  // Setting every element to a value greater than the constant
    }

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 14: If every element in the input array is less than a constant, then the output array should be the same as the input array but in ascending order.
 */
TEST_P(QuickSortParamTest, MR14) {
    int constant = 100;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Replace all elements in the input array with the constant */
    for (auto& elem : source_vec) {
        elem = constant - 1;  // Setting every element to a value less than the constant
    }

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Sort the source array */
    sort(source_vec.begin(), source_vec.end());

    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 15: If the input array has only one element, the output array should be the same as the input array.
 */
TEST_P(QuickSortParamTest, MR15) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Modify the source vector to contain only one element */
    source_vec.resize(1);

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 16: If the input array is empty, the output array should also be empty.
 */
TEST_P(QuickSortParamTest, MR16) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Clear the source vector */
    source_vec.clear();

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Verify that the output is also empty */
    EXPECT_TRUE(source_out.empty());
}

/**
 * @brief Metamorphic Relation 17: Multiplying each element of the input array by a negative constant should result in the same output array but in reverse order.
 */
TEST_P(QuickSortParamTest, MR17) {  // Fixed
    int constant = -2;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Multiply each element in the input array by a negative constant */
    vector<int> follow_vec = source_vec;
    for (auto& elem : follow_vec) {
        elem *= constant;
    }

    /* Get the follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Reverse the source vector and undo the multiplication for comparison */
    reverse(follow_out.begin(), follow_out.end());
    for (auto& elem : follow_out) {
        elem /= constant;
    }

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 18: If all elements in the input array are equal, the output should be the same as the input array.
 */
TEST_P(QuickSortParamTest, MR18) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Replace all elements in the input array with the value of the first element */
    int first = source_vec[0];
    for (auto& elem : source_vec) {
        elem = first;
    }

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 19: Reversing the order of input arrays leads to the output array will be sorted in the reverse order.
 */
TEST_P(QuickSortParamTest, MR19) {
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
    reverse(follow_out.begin(), follow_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 20: If every element in the input array is greater than a constant, then the output array should be the same as the input array.
 */
TEST_P(QuickSortParamTest, MR20) {
    int constant = 500;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Replace all elements in the input array with the constant */
    for (auto& elem : source_vec) {
        elem = constant + 1;  // Setting every element to a value greater than the constant
    }

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 21: If the input array contains only negative numbers, the output array should be the same as the input array but in ascending order.
 */
TEST_P(QuickSortParamTest, MR21) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Replace all elements in the input array with negative values */
    for (auto& elem : source_vec) {
        elem = -abs(elem);
    }

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Sort the source array */
    sort(source_vec.begin(), source_vec.end());

    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 22: If every element in the input array is less than a constant, then the output array should be the same as the input array but in ascending order.
 */
TEST_P(QuickSortParamTest, MR22) {
    int constant = 50;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Replace all elements in the input array with the constant */
    for (auto& elem : source_vec) {
        elem = constant - 1;  // Setting every element to a value less than the constant
    }

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Sort the source array */
    sort(source_vec.begin(), source_vec.end());

    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 23: If the input array is already sorted in descending order, the output array should be sorted in ascending order.
 */
TEST_P(QuickSortParamTest, MR23) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the input array in descending order */
    sort(source_vec.rbegin(), source_vec.rend());

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Sort the source vector */
    sort(source_vec.begin(), source_vec.end());

    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 24: If the input array is alternating between positive and negative values, the output should be the same as the input array.
 */
TEST_P(QuickSortParamTest, MR24) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Alternate the signs of elements in the input array */
    for (int i = 0; i < source_vec.size(); ++i) {
        source_vec[i] = pow(-1, i) * abs(source_vec[i]);
    }

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 25: Concatenating the input array with its reversed version and sorting the concatenated array should yield the same result as sorting the input array individually and then concatenating and sorting the combined array.
 */
TEST_P(QuickSortParamTest, MR25) {  // Fixed
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    source_vec.insert(source_vec.end(), source_vec.rbegin(), source_vec.rend());

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Concatenate the input array with its reversed version */
    vector<int> combined_vec = input.vec;
    vector<int> reversed_vec = input.vec;
    reverse(reversed_vec.begin(), reversed_vec.end());
    combined_vec.insert(combined_vec.end(), reversed_vec.begin(), reversed_vec.end());
    combined_vec = quick_sort(combined_vec);

    /* Verification */
    EXPECT_EQ(combined_vec, source_out);
}

/**
 * @brief Metamorphic Relation 26: If the input array has only two elements, the output array should be the same if the two elements are swapped.
 */
TEST_P(QuickSortParamTest, MR26) {  // Fixed
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Make sure the input array has only two elements */
    if (source_vec.size() < 2) source_vec.emplace_back(source_vec.front() + 1);
    while (source_vec.size() > 2) source_vec.pop_back();
    vector<int> follow_vec = source_vec;

    /* Swap the two elements of the input array */
    swap(follow_vec[0], follow_vec[1]);

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(source_out, quick_sort(follow_vec));
}

/**
 * @brief Metamorphic Relation 27: If all elements in the input array are in descending order, the output array should be the same as the input array but in ascending order.
 */
TEST_P(QuickSortParamTest, MR27) {  // Fixed
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the input array in descending order */
    sort(source_vec.rbegin(), source_vec.rend());

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);
    
    /* Sort the source vector */
    source_vec = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 28: If every element in the input array has the same value, the output array should be the same as the input array.
 */
TEST_P(QuickSortParamTest, MR28) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Set all the elements in the input array to the same value */
    int value = source_vec[0];
    for (int i = 0; i < source_vec.size(); ++i) {
        source_vec[i] = value;
    }

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);
    
    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 29: If the input array is already sorted in descending order, the output array should be sorted in ascending order.
 */
TEST_P(QuickSortParamTest, MR29) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the input array in descending order */
    sort(source_vec.rbegin(), source_vec.rend());

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);
    
    /* Sort the source array */
    sort(source_vec.begin(), source_vec.end());

    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 30: If the input array contains only negative numbers, the output array should be sorted in ascending order.
 */
TEST_P(QuickSortParamTest, MR30) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Set all the elements in the input array to negative numbers */
    for (int i = 0; i < source_vec.size(); ++i) {
        source_vec[i] = -abs(source_vec[i]);
    }

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);
    
    /* Sort the source array */
    sort(source_vec.begin(), source_vec.end());

    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 31: If all elements in the input array have the same absolute value, the output array should be the same as the input array.
 */
TEST_P(QuickSortParamTest, MR31) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Set all the elements in the input array to the same absolute value */
    int value = abs(source_vec[0]);
    for (int i = 0; i < source_vec.size(); ++i) {
        source_vec[i] = (source_vec[i] < 0) ? -value : value;
    }

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);
    
    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 32: If the input array has all elements as zero, the output should be the same as the input array.
 */
TEST_P(QuickSortParamTest, MR32) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Set all the elements in the input array to zero */
    for (int i = 0; i < source_vec.size(); ++i) {
        source_vec[i] = 0;
    }

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);
    
    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 33: If all elements in the input array are pairwise distinct, the output array should be sorted in ascending order.
 */
TEST_P(QuickSortParamTest, MR33) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Set the input array to be pairwise distinct */
    for (int i = 0; i < source_vec.size(); ++i) {
        source_vec[i] = i;
    }

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);
    
    /* Sort the source array */
    sort(source_vec.begin(), source_vec.end());

    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 34: If the input array contains random values, the output array should be sorted in ascending order.
 */
TEST_P(QuickSortParamTest, MR34) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the input array */
    sort(source_vec.begin(), source_vec.end());

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);
    
    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 35: If the input array is already sorted in ascending order, the output array should be the same as the input array.
 */
TEST_P(QuickSortParamTest, MR35) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Sort the source vector */
    sort(source_vec.begin(), source_vec.end());

    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 36: If the input array is already sorted in ascending order, reversing the order of the elements should result in the output being the reverse of the input array.
 */
TEST_P(QuickSortParamTest, MR36) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the input array in ascending order */
    sort(source_vec.begin(), source_vec.end());

    /* Reverse the input array */
    reverse(source_vec.begin(), source_vec.end());

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Reverse the output to compare with the original input array */
    reverse(source_out.begin(), source_out.end());

    /* Verification */
    EXPECT_EQ(source_out, input.vec);
}

/**
 * @brief Metamorphic Relation 37: If all elements in the input array are equal, the output array should also be the same as the input array.
 */
TEST_P(QuickSortParamTest, MR37) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Set all elements to the first element value */
    int value = source_vec[0];
    for (int i = 1; i < source_vec.size(); ++i) {
        source_vec[i] = value;
    }

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 38: If the input array has one element less than the sorted input array, then the output array contains all elements in the input array along with the sorted element.
 */
TEST_P(QuickSortParamTest, MR38) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the input array */
    sort(source_vec.begin(), source_vec.end());

    /* Remove one element from the sorted array */
    source_vec.pop_back();

    /* Get the source output */
    vector<int> source_out = quick_sort(input.vec);

    /* Sort the source output */
    sort(source_out.begin(), source_out.end());

    /* Adding the removed element to the source output */
    source_out.push_back(input.vec.back());
    sort(source_out.begin(), source_out.end());

    /* Verification */
    EXPECT_EQ(source_out, input.vec);
}

/**
 * @brief Metamorphic Relation 39: If the input array has elements in alternating ascending and descending order, the output array should be sorted in ascending order.
 */
TEST_P(QuickSortParamTest, MR39) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Set the input array to be in alternating ascending and descending order */
    for (int i = 0; i < source_vec.size(); ++i) {
        source_vec[i] = (i % 2 == 0) ? i : -i;
    }

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Sort the source array to compare */
    sort(source_vec.begin(), source_vec.end());

    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 40: If every pair of elements in the input array is swapped, the output array should be the same as the input array.
 */
TEST_P(QuickSortParamTest, MR40) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Swap every pair of elements in the input array */
    for (int i = 0; i < source_vec.size() - 1; i += 2) {
        swap(source_vec[i], source_vec[i + 1]);
    }

    /* Get the source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(source_out, input.vec);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, QuickSortParamTest, testing::ValuesIn(gen_tcs_randomly()));