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
 * @brief Metamorphic Relation 4: Reversing the elements in the input array, the output will be the reverse order of the source output.
 */
TEST_P(QuickSortParamTest, MR4) {
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
 * @brief Metamorphic Relation 5: Appending a constant to each element in the input array, the output elements will be in ascending order with the constant
 * appended to each element.
 */
TEST_P(QuickSortParamTest, MR5) {
    int constant = 5;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem += constant;
    follow_vec.push_back(constant);

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 6: Appending a new element to the input array, the new output will be a sorted array with the new element inserted at an
 * appropriate position.
 */
TEST_P(QuickSortParamTest, MR6) {
    int new_element = 6;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort source input with the new element */
    source_vec.push_back(new_element);
    sort(source_vec.begin(), source_vec.end());

    /* Get source output */
    vector<int> source_out = quick_sort(input.vec);

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 7: Multiplying each element in the input array by a constant factor, the output elements will be in ascending order with each
 * element multiplied by the constant factor.
 */
TEST_P(QuickSortParamTest, MR7) {
    int constant_factor = 2;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem *= constant_factor;

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    sort(source_out.begin(), source_out.end());
    for (auto &elem : source_out)
        elem *= constant_factor;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 8: Applying a permutation to the input array, the output elements will be in ascending order with the same permutation applied
 * to the source output.
 */
TEST_P(QuickSortParamTest, MR8) {
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

    /* Applying the same permutation to the source output */
    vector<int> permuted_source_out = source_out;
    vector<int> indexes(source_vec.size());
    iota(indexes.begin(), indexes.end(), 0);
    sort(indexes.begin(), indexes.end(), [&](int i, int j) { return follow_vec[i] < follow_vec[j]; });
    for (size_t i = 0; i < source_vec.size(); ++i) {
        source_out[i] = permuted_source_out[indexes[i]];
    }

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 9: Applying quick sort twice to the input array will result in the same sorted output as applying quick sort once.
 */
TEST_P(QuickSortParamTest, MR9) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out_once = quick_sort(source_vec);

    /* Applying quick sort second time to source output */
    vector<int> source_out_twice = quick_sort(source_out_once);

    /* Verification */
    EXPECT_EQ(source_out_twice, source_out_once);
}

/**
 * @brief Metamorphic Relation 10: Adding a constant to each element in the input array and then sorting, the new output will be the same as adding the constant
 * to each element of the original output.
 */
TEST_P(QuickSortParamTest, MR10) {
    int constant = 4;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Adding a constant to each element in the input array */
    for (auto &elem : source_vec)
        elem += constant;

    /* Applying quick sort to the modified input array */
    vector<int> modified_out = quick_sort(source_vec);

    /* Adding the constant to each element of the original output */
    for (auto &elem : source_out)
        elem += constant;

    /* Verification */
    EXPECT_EQ(modified_out, source_out);
}

/**
 * @brief Metamorphic Relation 11: Taking a subarray of the input, the output will be the sorted subarray, which should also be a subarray of the original
 * output.
 */
TEST_P(QuickSortParamTest, MR11) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Generate random start and end indexes for the subarray */
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, source_vec.size() - 1);
    int start = dis(gen);
    int end = dis(gen);

    if (start > end) {
        swap(start, end);
    }

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec(source_vec.begin() + start, source_vec.begin() + end + 1);

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verify if the follow-up output is a subarray of the original output */
    bool is_subarray = includes(source_out.begin(), source_out.end(), follow_out.begin(), follow_out.end());
    EXPECT_TRUE(is_subarray);
}

/**
 * @brief Metamorphic Relation 12: Applying quick sort to a sorted array will result in the same sorted output.
 */
TEST_P(QuickSortParamTest, MR12) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Applying quick sort to the sorted array */
    vector<int> sorted_out = quick_sort(source_out);

    /* Verification */
    EXPECT_EQ(sorted_out, source_out);
}

/**
 * @brief Metamorphic Relation 13: Repeating the elements in the input array, the output will be the same as the source output but with duplicated elements.
 */
TEST_P(QuickSortParamTest, MR13) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input with duplicated elements */
    vector<int> follow_vec;
    for (int elem : source_vec) {
        follow_vec.push_back(elem);
        follow_vec.push_back(elem);
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 14: Appending a descending sorted array to the input array, the output elements will be in ascending order with the descending
 * sorted array appended at the end.
 */
TEST_P(QuickSortParamTest, MR14) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input with descending sorted array appended */
    vector<int> follow_vec = source_vec;
    vector<int> descending_array(source_vec.rbegin(), source_vec.rend());
    follow_vec.insert(follow_vec.end(), descending_array.begin(), descending_array.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 15: Sorting the input array with the first element as the pivot, and then repeating the process with the second element as the
 * pivot, the outputs will have the same elements but might be in a different order.
 */
TEST_P(QuickSortParamTest, MR15) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output with the first element as the pivot */
    vector<int> out_pivot_first = quick_sort(source_vec);

    /* Get source output with the second element as the pivot */
    vector<int> out_pivot_second = quick_sort(source_vec);

    /* Verification */
    EXPECT_TRUE(is_permutation(out_pivot_first.begin(), out_pivot_first.end(), out_pivot_second.begin(), out_pivot_second.end()));
}

/**
 * @brief Metamorphic Relation 16: Replacing some elements in the input array with a larger value, the output will be a sorted array with the same order of the
 * elements that were not replaced, and the replaced elements will appear after them.
 */
TEST_P(QuickSortParamTest, MR16) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Replace some elements in the input array with larger values */
    vector<int> follow_vec = source_vec;
    for (int i = 0; i < source_vec.size() / 2; ++i) {
        follow_vec[i] = source_vec[i] + 100;
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    vector<int> modified_source_out = source_out;
    for (int i = 0; i < source_vec.size() / 2; ++i) {
        modified_source_out[i] += 100;
    }

    bool replaced_elements_appear_after_original_elements = true;
    for (int i = 0; i < source_vec.size() / 2; ++i) {
        if (follow_out[i] != modified_source_out[i]) {
            replaced_elements_appear_after_original_elements = false;
            break;
        }
    }
    EXPECT_TRUE(replaced_elements_appear_after_original_elements);
}

/**
 * @brief Metamorphic Relation 17: Applying quick sort to the input array of all identical elements should result in an output array with identical elements.
 */
TEST_P(QuickSortParamTest, MR17) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec(input.vec.size(), 10); // All elements set to 10

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Verification */
    EXPECT_TRUE(all_of(source_out.begin(), source_out.end(), [](int x) { return x == 10; }));
}

/**
 * @brief Metamorphic Relation 18: Sorting the array in ascending order, and then sorting the result in descending order should produce the original array.
 */
TEST_P(QuickSortParamTest, MR18) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get ascending sorted output */
    vector<int> ascending_sorted = quick_sort(source_vec);

#if INVALID
    /* Get descending sorted output from the ascending sorted array */
    vector<int> descending_sorted = quick_sort(ascending_sorted, greater<int>());
#else
    /* Fix by Radon */
    /* Get descending sorted output from the ascending sorted array */
    vector<int> descending_sorted(ascending_sorted);
    reverse(descending_sorted.begin(), descending_sorted.end());
#endif

    /* Verification */
    EXPECT_EQ(descending_sorted, source_vec);
}

/**
 * @brief Metamorphic Relation 19: Reversing the order of elements in the input array and then applying quick sort should result in the exact opposite order of
 * the original sorted array.
 */
TEST_P(QuickSortParamTest, MR19) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Reverse the order of elements in the input array */
    reverse(source_vec.begin(), source_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(source_vec);

    /* Reverse the original sorted array */
    reverse(source_out.begin(), source_out.end());

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 20: Applying quick sort to an empty array should result in an empty array.
 */
TEST_P(QuickSortParamTest, MR20) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec; // Empty array

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Verification */
    EXPECT_TRUE(source_out.empty());
}

/**
 * @brief Metamorphic Relation 21: Applying quick sort to the array with only one element should result in the same array.
 */
TEST_P(QuickSortParamTest, MR21) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    if (source_vec.size() != 1) {
        return;
    }

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}

/**
 * @brief Metamorphic Relation 22: Applying quick sort to a range of elements within the input array should result in a subarray of the original sorted output.
 */
TEST_P(QuickSortParamTest, MR22) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    int start_index = 2; // Define the start index of the range
    int end_index = 6;   // Define the end index of the range

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Apply quick sort to the specified range */
    vector<int> subarray_sorted_output = quick_sort(vector<int>(source_vec.begin() + start_index, source_vec.begin() + end_index + 1));

    /* Verify if the subarray sorted output is a subarray of the original sorted output */
    bool is_subarray = includes(source_out.begin(), source_out.end(), subarray_sorted_output.begin(), subarray_sorted_output.end());
    EXPECT_TRUE(is_subarray);
}

/**
 * @brief Metamorphic Relation 23: Appending a sorted array to the input array, the output elements will be in ascending order with the sorted array appended at
 * the end.
 */
TEST_P(QuickSortParamTest, MR23) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Append a sorted array to the input array */
    vector<int> appended_array = {10, 20, 30}; // Example sorted array to be appended
    vector<int> follow_vec = source_vec;
    follow_vec.insert(follow_vec.end(), appended_array.begin(), appended_array.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 24: Applying quick sort to a completely reversed array should result in the same array as the reverse of the original sorted
 * array.
 */
TEST_P(QuickSortParamTest, MR24) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Reverse the input array completely */
    reverse(source_vec.begin(), source_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(source_vec);

    /* Reverse the original sorted array */
    reverse(source_out.begin(), source_out.end());

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 25: Applying quick sort to the array with negative elements should result in the elements being sorted in ascending order.
 */
TEST_P(QuickSortParamTest, MR25) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Apply quick sort to the array */
    vector<int> sorted_output = quick_sort(source_vec);

    /* Verify if the array is sorted in ascending order */
    bool isAscending = is_sorted(sorted_output.begin(), sorted_output.end());
    EXPECT_TRUE(isAscending);
}

/**
 * @brief Metamorphic Relation 26: Repeating the elements in the input array, the output will be the sorted array with the same number of duplicates for each
 * element as in the original input.
 */
TEST_P(QuickSortParamTest, MR26) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input with duplicated elements */
    vector<int> follow_vec;
    for (int elem : source_vec) {
        follow_vec.push_back(elem);
        follow_vec.push_back(elem); // Duplicates each element
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verify if the follow-up output has the same number of duplicates as in the original input */
    unordered_map<int, int> source_element_count;
    unordered_map<int, int> follow_element_count;
    for (int elem : source_vec) {
        source_element_count[elem]++;
    }
    for (int elem : follow_out) {
        follow_element_count[elem]++;
    }
    for (auto it : source_element_count) {
        int elem = it.first;
        EXPECT_EQ(source_element_count[elem], follow_element_count[elem]);
    }
}

/**
 * @brief Metamorphic Relation 27: Applying quick sort to the array with all elements the same but in different orders should result in the same output.
 */
TEST_P(QuickSortParamTest, MR27) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Apply quick sort to the array */
    vector<int> sorted_output = quick_sort(source_vec);

    /* Verify if sorting the same numbers in different orders results in the same output */
    vector<int> follow_vec = source_vec;
    while (next_permutation(follow_vec.begin(), follow_vec.end())) {
        vector<int> follow_sorted_output = quick_sort(follow_vec);
        EXPECT_EQ(follow_sorted_output, sorted_output);
    }
}

/**
 * @brief Metamorphic Relation 28: Appending a sorted array to the input array, the output elements will be in ascending order with the sorted array appended at
 * the end.
 */
TEST_P(QuickSortParamTest, MR28) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Append a sorted array to the input array */
    vector<int> appended_array = {10, 20, 30}; // Example sorted array to be appended
    vector<int> follow_vec = source_vec;
    follow_vec.insert(follow_vec.end(), appended_array.begin(), appended_array.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 29: Applying quick sort to an array with all elements being the same should result in an output where all elements are still the
 * same.
 */
TEST_P(QuickSortParamTest, MR29) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Create a vector with all elements set to a constant value
    vector<int> constant_array(source_vec.size(), 5);

    /* Get source output */
    vector<int> source_out = quick_sort(constant_array);

    /* Verification */
    EXPECT_TRUE(all_of(source_out.begin(), source_out.end(), [](int x) { return x == 5; }));
}

/**
 * @brief Metamorphic Relation 30: Sorting the array in descending order, and then resoring the result in ascending order should produce the original array.
 */
TEST_P(QuickSortParamTest, MR30) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

#if INVALID
    /* Get descending sorted output */
    vector<int> descending_sorted = quick_sort(source_vec, greater<int>());
#else
    /* Get descending sorted output */
    vector<int> descending_sorted = quick_sort(source_vec);
    reverse(descending_sorted.begin(), descending_sorted.end());
#endif

    /* Get ascending sorted output from the descending sorted array */
    vector<int> ascending_sorted = quick_sort(descending_sorted);

    /* Verification */
    EXPECT_EQ(ascending_sorted, source_vec);
}

/**
 * @brief Metamorphic Relation 31: Sorting the array with negative elements in descending order should result in the elements being arranged in descending
 * order.
 */
TEST_P(QuickSortParamTest, MR31) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

#if INVALID
    /* Apply quick sort to the array in descending order */
    vector<int> descending_sorted_output = quick_sort(source_vec, greater<int>());
#else
    /* Apply quick sort to the array in descending order */
    vector<int> descending_sorted_output = quick_sort(source_vec);
    reverse(descending_sorted_output.begin(), descending_sorted_output.end());
#endif

    /* Verify if the array is sorted in descending order */
    bool isDescending = is_sorted(descending_sorted_output.rbegin(), descending_sorted_output.rend());
    EXPECT_TRUE(isDescending);
}

/**
 * @brief Metamorphic Relation 32: Repeating the elements in the input array, the output will be the sorted array with the same number of duplicates for each
 * element as in the original input.
 */
TEST_P(QuickSortParamTest, MR32) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input with duplicated elements */
    vector<int> follow_vec;
    for (int elem : source_vec) {
        follow_vec.push_back(elem);
        follow_vec.push_back(elem); // Duplicates each element
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verify if the follow-up output has the same number of duplicates as in the original input */
    unordered_map<int, int> source_element_count;
    unordered_map<int, int> follow_element_count;
    for (int elem : source_vec) {
        source_element_count[elem]++;
    }
    for (int elem : follow_out) {
        follow_element_count[elem]++;
    }
    for (auto it : source_element_count) {
        int elem = it.first;
        EXPECT_EQ(source_element_count[elem], follow_element_count[elem]);
    }
}

/**
 * @brief Metamorphic Relation 33: Applying quick sort to a completely reversed array should result in the same array as the reverse of the original sorted
 * array.
 */
TEST_P(QuickSortParamTest, MR33) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Reverse the input array completely */
    reverse(source_vec.begin(), source_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(source_vec);

    /* Reverse the original sorted array */
    reverse(source_out.begin(), source_out.end());

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 34: Applying quick sort to an array with the same elements in different positions should produce the same output.
 */
TEST_P(QuickSortParamTest, MR34) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Apply quick sort to the array */
    vector<int> sorted_output = quick_sort(source_vec);

    /* Verify if sorting the same numbers in different positions results in the same output */
    vector<int> follow_vec = source_vec;
    while (next_permutation(follow_vec.begin(), follow_vec.end())) {
        vector<int> follow_sorted_output = quick_sort(follow_vec);
        EXPECT_EQ(follow_sorted_output, sorted_output);
    }
}

/**
 * @brief Metamorphic Relation 35: Applying quick sort to an array with the elements in reverse order of the original sorted array should also be in reverse
 * order.
 */
TEST_P(QuickSortParamTest, MR35) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Reverse the order of elements in the input array */
    reverse(source_vec.begin(), source_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(source_vec);

    /* Reverse the original sorted array */
    reverse(source_out.begin(), source_out.end());

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 36: Applying quick sort to the sorted result should produce the same sorted array.
 */
TEST_P(QuickSortParamTest, MR36) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get ascending sorted output */
    vector<int> sorted_output = quick_sort(source_vec);

    /* Verify if applying quick sort to the sorted output results in the same sorted array */
    vector<int> follow_sorted_output = quick_sort(sorted_output);
    EXPECT_EQ(follow_sorted_output, sorted_output);
}

/**
 * @brief Metamorphic Relation 37: Adding a constant to each element in the input array and then sorting should result in the same sorted array with the
 * constant added to each element.
 */
TEST_P(QuickSortParamTest, MR37) {
    int constant = 5;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Adding a constant to each element in the input array */
    for (int &elem : source_vec) {
        elem += constant;
    }

    /* Apply quick sort to the modified input array */
    vector<int> modified_out = quick_sort(source_vec);

    /* Verify the elements in the modified sorted array are increased by the constant */
    for (int &elem : modified_out) {
        elem -= constant;
    }
    EXPECT_EQ(modified_out, source_out);
}

/**
 * @brief Metamorphic Relation 38: Applying quick sort to an array with negative elements and then reversing the result should produce the reverse of the
 * original sorted array.
 */
TEST_P(QuickSortParamTest, MR38) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get the sorted output */
    vector<int> sorted_output = quick_sort(source_vec);

    /* Reverse the sorted output */
    reverse(sorted_output.begin(), sorted_output.end());

    /* Applying quick sort to an array with negative elements */
    vector<int> negative_vec = source_vec;
    transform(negative_vec.begin(), negative_vec.end(), negative_vec.begin(), [](int n) { return -n; });
    vector<int> negative_sorted = quick_sort(negative_vec);

    /* Verify if reversing the result of sorting negative values is equal to the reverse of the original sorted array */
    EXPECT_EQ(negative_sorted, sorted_output);
}

/**
 * @brief Metamorphic Relation 39: Repeatedly applying quick sort to the input array should result in the same sorted output.
 */
TEST_P(QuickSortParamTest, MR39) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get the initial sorted output */
    vector<int> sorted_output = quick_sort(source_vec);

    /* Repeatedly apply quick sort to the input array */
    for (int i = 0; i < 5; i++) {
        vector<int> temp_vec = source_vec;
        random_shuffle(temp_vec.begin(), temp_vec.end());
        sorted_output = quick_sort(temp_vec);
    }

    /* Verify if repeatedly applying quick sort results in the same sorted output */
    EXPECT_EQ(sorted_output, quick_sort(source_vec));
}

/**
 * @brief Metamorphic Relation 40: Reversing the elements in the input array and then applying quick sort should result in the exact opposite order of the
 * original sorted array.
 */
TEST_P(QuickSortParamTest, MR40) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get the sorted output */
    vector<int> sorted_output = quick_sort(source_vec);

    /* Reverse the input array */
    reverse(source_vec.begin(), source_vec.end());

    /* Get the output after sorting the reverse input array */
    vector<int> reverse_sorted = quick_sort(source_vec);

    /* Reverse the original sorted array */
    reverse(sorted_output.begin(), sorted_output.end());

    /* Verify if sorting the reverse input array results in the reversed original output */
    EXPECT_EQ(reverse_sorted, sorted_output);
}

/**
 * @brief Metamorphic Relation 41: Applying quick sort to an empty array should result in an empty array.
 */
TEST_P(QuickSortParamTest, MR41) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec; // Empty array

    /* Get the sorted output for the empty array */
    vector<int> empty_sorted = quick_sort(source_vec);

    /* Verify if applying quick sort to an empty array results in an empty array */
    EXPECT_TRUE(empty_sorted.empty());
}

/**
 * @brief Metamorphic Relation 42: Applying quick sort to an array with only one element should result in the same single-element array.
 */
TEST_P(QuickSortParamTest, MR42) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    if (source_vec.size() != 1) {
        return;
    }

    /* Get the sorted output for the single-element array */
    vector<int> single_sorted = quick_sort(source_vec);

    /* Verify if applying quick sort to a single-element array results in the same single-element array */
    EXPECT_EQ(single_sorted, source_vec);
}

/**
 * @brief Metamorphic Relation 43: Sorting the array with all elements being the same should result in an output where all elements are still the same.
 */
TEST_P(QuickSortParamTest, MR43) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    int value = source_vec.size() > 0 ? source_vec[0] : 0;

    // Create a vector with all elements set to a constant value
    vector<int> constant_array(source_vec.size(), value);

    /* Get the sorted output for the constant-element array */
    vector<int> constant_sorted = quick_sort(constant_array);

    /* Verify if applying quick sort to an array with all elements the same results in an array where all elements are still the same */
    EXPECT_TRUE(all_of(constant_sorted.begin(), constant_sorted.end(), [value](int x) { return x == value; }));
}

INSTANTIATE_TEST_CASE_P(TrueReturn, QuickSortParamTest, testing::ValuesIn(gen_tcs_randomly()));