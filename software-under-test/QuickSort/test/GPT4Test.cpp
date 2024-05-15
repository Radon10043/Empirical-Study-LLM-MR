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
 * @brief Metamorphic Relation 4: Reversing the elements in the input array, the output will be the same.
 *
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
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 5: If any element is duplicated in the input array, the output should have those duplicates next to each other.
 *
 */
TEST_P(QuickSortParamTest, MR5) { // Fixed
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.push_back(follow_vec[0]); // Assuming there is at least one element in the vector

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    bool has_matched = false;
    for (size_t i = 0; i < source_out.size(); i++) {
        if (source_out[i] == follow_vec[0] && !has_matched) {
            has_matched = true;
            EXPECT_EQ(source_out[i], follow_out[i + 1]);
        }
    }
}

/**
 * @brief Metamorphic Relation 6: Removing duplicates in the input should not change the output, except for the missing duplicates.
 *
 */
TEST_P(QuickSortParamTest, MR6) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input without duplicates */
    vector<int> follow_vec = source_vec;
    sort(follow_vec.begin(), follow_vec.end());
    follow_vec.erase(unique(follow_vec.begin(), follow_vec.end()), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    auto it_source = source_out.begin();
    for (auto elem : follow_out) {
        while (it_source != source_out.end() && elem != *it_source) {
            ++it_source;
        }
        EXPECT_EQ(elem, *it_source);
        if (it_source != source_out.end()) {
            ++it_source;
        }
    }
}

/**
 * @brief Metamorphic Relation 7: Concatenating another sorted array should not change the order of the original elements, and the concatenated elements should
 * also follow the order.
 *
 */
TEST_P(QuickSortParamTest, MR7) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> extra_sorted_array = {100, 101, 102, 103, 104}; // Example sorted vector
    vector<int> follow_vec(source_vec);
    follow_vec.insert(follow_vec.end(), extra_sorted_array.begin(), extra_sorted_array.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out.size() + extra_sorted_array.size(), follow_out.size());
    bool correct_order = std::is_sorted(follow_out.begin(), follow_out.end());
    EXPECT_TRUE(correct_order);
}

/**
 * @brief Metamorphic Relation 8: If the input array is already sorted, the output will be the same as the input.
 *
 */
TEST_P(QuickSortParamTest, MR8) {
    /* Get source input already sorted */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    sort(source_vec.begin(), source_vec.end());

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(source_vec, source_out);
}

/**
 * @brief Metamorphic Relation 9: Doubling each element in the input array, the relative order in the output array should remain the same.
 *
 */
TEST_P(QuickSortParamTest, MR9) {
    const int factor = 2;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec) {
        elem *= factor;
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    for (size_t i = 0; i < source_out.size(); ++i) {
        source_out[i] *= factor;
    }
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 10: Appending reversed input array to itself, the output should be symmetrical around the center.
 *
 */
TEST_P(QuickSortParamTest, MR10) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    vector<int> reversed_vec = source_vec;
    reverse(reversed_vec.begin(), reversed_vec.end());

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.insert(follow_vec.end(), reversed_vec.begin(), reversed_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    const size_t mid = follow_out.size() / 2;
    for (size_t i = 0; i < mid; ++i) {
        EXPECT_EQ(follow_out[i], follow_out[follow_out.size() - 1 - i]);
    }
}

/**
 * @brief Metamorphic Relation 11: Sorting only a part of the input array should yield the same output for that part.
 *
 */
TEST_P(QuickSortParamTest, MR11) {
    /* Get source input, ensure there are at least two elements for partial sorting */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    if (source_vec.size() <= 1) {
        source_vec.push_back(source_vec[0] - 1); // Append an element for partial sorting
    }

    /* Get source output of the whole vector */
    vector<int> sorted_all = quick_sort(source_vec);

    /* Get source output of the part vector */
    vector<int> part_vec(source_vec.begin(), source_vec.begin() + source_vec.size() / 2); // Take first half for partial sort
    vector<int> sorted_part = quick_sort(part_vec);

    /* Verification */
    for (size_t i = 0; i < sorted_part.size(); ++i) {
        EXPECT_EQ(sorted_all[i], sorted_part[i]);
    }
}

/**
 * @brief Metamorphic Relation 12: Concatenating the inverse of the input array to itself and sorting should result in a palindrome.
 *
 */
TEST_P(QuickSortParamTest, MR12) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input */
    vector<int> inverted_vec = source_vec;
    for (auto &elem : inverted_vec) {
        elem = -elem;
    }
    vector<int> follow_vec = source_vec;
    follow_vec.insert(follow_vec.end(), inverted_vec.begin(), inverted_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    size_t mid = follow_out.size() / 2;
    for (size_t i = 0; i < mid; ++i) {
        EXPECT_EQ(follow_out[i], -follow_out[follow_out.size() - 1 - i]);
    }
}

/**
 * @brief Metamorphic Relation 13: Inserting a maximum/minimum value in the input array should result in that value being the last/first in the output array.
 *
 */
TEST_P(QuickSortParamTest, MR13) {
    const int max_value = std::numeric_limits<int>::max();
    const int min_value = std::numeric_limits<int>::min();

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec_max = source_vec;
    follow_vec_max.push_back(max_value);
    vector<int> follow_vec_min = source_vec;
    follow_vec_min.push_back(min_value);

    /* Get follow-up output */
    vector<int> follow_out_max = quick_sort(follow_vec_max);
    vector<int> follow_out_min = quick_sort(follow_vec_min);

    /* Verification */
    EXPECT_EQ(follow_out_max[follow_out_max.size() - 1], max_value);
    EXPECT_EQ(follow_out_min[0], min_value);
}

/**
 * @brief Metamorphic Relation 14: Concatenating a non-sorted array to the sorted input array should result in the non-sorted elements being integrated in
 * place.
 *
 */
TEST_P(QuickSortParamTest, MR14) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> sorted_vec = quick_sort(input.vec); // Ensure the first part is sorted

    /* Non-sorted array to append */
    vector<int> non_sorted = {3, 1, 4, 1, 5};

    /* Construct follow-up input */
    vector<int> follow_vec = sorted_vec;
    follow_vec.insert(follow_vec.end(), non_sorted.begin(), non_sorted.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out.size(), sorted_vec.size() + non_sorted.size());
    EXPECT_TRUE(std::is_sorted(follow_out.begin(), follow_out.end()));
}

/**
 * @brief Metamorphic Relation 15: Removing any element from the input array should result in the same output array with that element removed.
 *
 */
TEST_P(QuickSortParamTest, MR15) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Make sure input vector has at least one element to remove */
    if (source_vec.empty()) {
        source_vec.push_back(1); // Add a dummy element for this test
    }

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input by removing an element from the middle */
    vector<int> follow_vec = source_vec;
    auto it_rm = follow_vec.begin() + follow_vec.size() / 2;
    int removed_element = *it_rm;
    follow_vec.erase(it_rm);

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    auto it_source_out = std::find(source_out.begin(), source_out.end(), removed_element);
    if (it_source_out != source_out.end()) {
        source_out.erase(it_source_out);
    }
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 16: Interleaving the input array with another sorted array should maintain the order of each element from both arrays in the
 * output.
 *
 */
TEST_P(QuickSortParamTest, MR16) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Second sorted array for interleaving */
    vector<int> sorted_vec2 = {7, 8, 9, 10, 11};
    quick_sort(sorted_vec2); // Ensure the array is sorted even if the input numbers are modified

    /* Construct follow-up input by interleaving the two arrays */
    vector<int> follow_vec;
    auto it1 = source_vec.begin(), it2 = sorted_vec2.begin();
    while (it1 != source_vec.end() && it2 != sorted_vec2.end()) {
        follow_vec.push_back(*it1++);
        follow_vec.push_back(*it2++);
    }
    // Append the remaining elements of the longer array
    follow_vec.insert(follow_vec.end(), it1, source_vec.end());
    follow_vec.insert(follow_vec.end(), it2, sorted_vec2.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_TRUE(std::is_sorted(follow_out.begin(), follow_out.end()));
    // Check that relative ordering within each interleaved set is maintained
    for (size_t i = 0; i < source_vec.size(); ++i) {
        size_t pos_in_output = std::find(follow_out.begin(), follow_out.end(), source_vec[i]) - follow_out.begin();
        if (i < source_vec.size() - 1) {
            size_t next_pos_in_output = std::find(follow_out.begin(), follow_out.end(), source_vec[i + 1]) - follow_out.begin();
            EXPECT_LT(pos_in_output, next_pos_in_output);
        }
    }
}

/**
 * @brief Metamorphic Relation 17: Performing two consecutive sorts should yield the same result as a single sort.
 *
 */
TEST_P(QuickSortParamTest, MR17) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the input array */
    vector<int> once_sorted = quick_sort(source_vec);

    /* Sort the sorted array again */
    vector<int> twice_sorted = quick_sort(once_sorted);

    /* Verification */
    EXPECT_EQ(once_sorted, twice_sorted);
}

/**
 * @brief Metamorphic Relation 18: Sorting an array composed only of one unique element should yield the same array.
 *
 */
TEST_P(QuickSortParamTest, MR18) {
    /* Construct source input with one unique element */
    vector<int> source_vec(10, 42); // Vector with 10 elements all set to 42

    /* Sort the input array */
    vector<int> sorted = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(source_vec, sorted);
}

/**
 * @brief Metamorphic Relation 19: Inverting the order of a sorted array should also result in a sorted array in reverse order.
 *
 */
TEST_P(QuickSortParamTest, MR19) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> sorted_vec = quick_sort(input.vec);

    /* Invert the sorted array */
    vector<int> reversed_sorted_vec = sorted_vec;
    std::reverse(reversed_sorted_vec.begin(), reversed_sorted_vec.end());

    /* Sort the inverted array */
    vector<int> sorted_reversed = quick_sort(reversed_sorted_vec);

    /* Verification */
    std::reverse(sorted_reversed.begin(), sorted_reversed.end());
    EXPECT_EQ(sorted_vec, sorted_reversed); // The second sort should be the original sorted array
}

/**
 * @brief Metamorphic Relation 20: Sorting an array that is the concatenation of two sorted arrays should not change the order of elements within each original
 * array.
 *
 */
TEST_P(QuickSortParamTest, MR20) {
    /* Get source input and ensure it is sorted */
    QuickSortInput input = GetParam();
    vector<int> source_vec1 = quick_sort(input.vec);

    /* Create second sorted array */
    vector<int> source_vec2 = {5, 10, 15, 20, 25};
    vector<int> sorted_vec2 = quick_sort(source_vec2);

    /* Concatenate the two sorted arrays */
    vector<int> concatenated_vec(source_vec1);
    concatenated_vec.insert(concatenated_vec.end(), sorted_vec2.begin(), sorted_vec2.end());

    /* Sort the concatenated array */
    vector<int> sorted_concatenated = quick_sort(concatenated_vec);

    /* Verification */
    // All elements from the first array should be before any element from the second array
    auto it = std::find_if(sorted_concatenated.begin(), sorted_concatenated.end(),
                           [&sorted_vec2](const int &val) { return std::find(sorted_vec2.begin(), sorted_vec2.end(), val) != sorted_vec2.end(); });
    EXPECT_TRUE(std::is_sorted(sorted_concatenated.begin(), it));
    EXPECT_TRUE(std::is_sorted(it, sorted_concatenated.end()));
}

/**
 * @brief Metamorphic Relation 21: If all elements in the input array are incremented in a sequence, their relative order should be the same in the output.
 *
 */
TEST_P(QuickSortParamTest, MR21) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Increment elements in the input vector by their index */
    vector<int> modified_vec;
    std::transform(source_vec.begin(), source_vec.end(), std::back_inserter(modified_vec), [i = 0](int x) mutable { return x + i++; });

    /* Sort the modified array */
    vector<int> sorted_modified = quick_sort(modified_vec);

    /* Verify that relative ordering is maintained */
    auto cmp = [](const int &a, const int &b) { return a < b; };
    EXPECT_TRUE(std::is_sorted(sorted_modified.begin(), sorted_modified.end(), cmp));
}

/**
 * @brief Metamorphic Relation 22: If a sorted array is split into two parts, the two parts should also be sorted.
 *
 */
TEST_P(QuickSortParamTest, MR22) {
    /* Get a sorted input array */
    QuickSortInput input = GetParam();
    vector<int> sorted_vec = quick_sort(input.vec);

    /* Split the sorted array into two parts */
    vector<int> first_half(sorted_vec.begin(), sorted_vec.begin() + sorted_vec.size() / 2);
    vector<int> second_half(sorted_vec.begin() + sorted_vec.size() / 2, sorted_vec.end());

    /* Verification */
    EXPECT_TRUE(std::is_sorted(first_half.begin(), first_half.end()));
    EXPECT_TRUE(std::is_sorted(second_half.begin(), second_half.end()));
}

/**
 * @brief Metamorphic Relation 23: Splitting the input array into even and odd indices, sorting both, and merging should result in a sorted array.
 *
 */
TEST_P(QuickSortParamTest, MR23) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct even and odd indexed arrays */
    vector<int> even_indexed, odd_indexed;
    for (size_t i = 0; i < source_vec.size(); ++i) {
        if (i % 2 == 0) {
            even_indexed.push_back(source_vec[i]);
        } else {
            odd_indexed.push_back(source_vec[i]);
        }
    }

    /* Sort both even and odd indexed arrays */
    even_indexed = quick_sort(even_indexed);
    odd_indexed = quick_sort(odd_indexed);

    /* Merge the sorted even and odd indexed arrays */
    vector<int> merged_vec;
    auto even_it = even_indexed.begin();
    auto odd_it = odd_indexed.begin();
    while (even_it != even_indexed.end() || odd_it != odd_indexed.end()) {
        if (even_it != even_indexed.end()) {
            merged_vec.push_back(*even_it++);
        }
        if (odd_it != odd_indexed.end()) {
            merged_vec.push_back(*odd_it++);
        }
    }

    /* Sort the merged array */
    vector<int> sorted_merged_vec = quick_sort(merged_vec);

    /* Verification */
    EXPECT_TRUE(std::is_sorted(sorted_merged_vec.begin(), sorted_merged_vec.end()));
}

/**
 * @brief Metamorphic Relation 24: Extracting subsets of the input array and sorting them individually should yield subsets of the sorted input.
 *
 */
TEST_P(QuickSortParamTest, MR24) {
    /* Get source input and ensure it is sorted */
    QuickSortInput input = GetParam();
    vector<int> sorted_vec = quick_sort(input.vec);

    /* Extract and sort subsets of the input array */
    vector<int> subsets;
    for (size_t i = 0; i < input.vec.size(); i += 3) { // Taking a subset every 3 elements
        vector<int> subset;
        for (size_t j = i; j < std::min(i + 3, input.vec.size()); ++j) {
            subset.push_back(input.vec[j]);
        }
        subset = quick_sort(subset);
        subsets.insert(subsets.end(), subset.begin(), subset.end());
    }

    /* Verification */
    auto subset_it = subsets.begin();
    for (size_t i = 0; i < sorted_vec.size() && subset_it != subsets.end(); ++i) {
        if (sorted_vec[i] == *subset_it) {
            ++subset_it;
        }
    }
    EXPECT_TRUE(subset_it == subsets.end());
}

/**
 * @brief Metamorphic Relation 25: Sorting a permutation of the input array with removed elements should result in a subsequence of the sorted array.
 *
 */
TEST_P(QuickSortParamTest, MR25) {
    /* Get source input and ensure it is sorted */
    QuickSortInput input = GetParam();
    vector<int> sorted_vec = quick_sort(input.vec);

    /* Permute and remove some elements from the input array */
    vector<int> modified_vec = input.vec;
    std::random_shuffle(modified_vec.begin(), modified_vec.end());
    modified_vec.erase(modified_vec.begin(), modified_vec.begin() + modified_vec.size() / 4);

    /* Sort the modified vector */
    vector<int> sorted_modified_vec = quick_sort(modified_vec);

    /* Verification: sorted modified vector should be a subsequence of the sorted_vec */
    auto it_original = sorted_vec.begin();
    for (auto val : sorted_modified_vec) {
        it_original = std::find(it_original, sorted_vec.end(), val);
        EXPECT_TRUE(it_original != sorted_vec.end());
        if (it_original != sorted_vec.end()) {
            ++it_original;
        }
    }
}

/**
 * @brief Metamorphic Relation 26: Sorting an array whose elements are squared should yield a sorted array, and the order should be maintained after taking the
 * square root.
 *
 */
TEST_P(QuickSortParamTest, MR26) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Square elements of source array */
    vector<int> squared_vec;
    std::transform(source_vec.begin(), source_vec.end(), std::back_inserter(squared_vec), [](int x) { return x * x; });

    /* Sort the squared array */
    vector<int> sorted_squared_vec = quick_sort(squared_vec);

    /* Apply square root to the sorted squared array */
    vector<int> root_sorted_squared_vec;
    std::transform(sorted_squared_vec.begin(), sorted_squared_vec.end(), std::back_inserter(root_sorted_squared_vec),
                   [](int x) { return static_cast<int>(std::sqrt(x)); });

    /* Sort the source array */
    vector<int> sorted_vec = quick_sort(source_vec);

    /* Verification: The order of elements in sorted_vec and root_sorted_squared_vec should be the same */
    EXPECT_EQ(sorted_vec.size(), root_sorted_squared_vec.size());
    for (size_t i = 0; i < root_sorted_squared_vec.size(); i++) {
        EXPECT_EQ(sorted_vec[i], root_sorted_squared_vec[i]);
    }
}

/**
 * @brief Metamorphic Relation 27: Sorting the concatenation of the same input array should yield a sorted array with each element repeating consecutively.
 *
 */
TEST_P(QuickSortParamTest, MR27) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Concatenate the input array with itself */
    vector<int> concatenated_vec(source_vec);
    concatenated_vec.insert(concatenated_vec.end(), source_vec.begin(), source_vec.end());

    /* Sort the concatenated array */
    vector<int> sorted_concatenated_vec = quick_sort(concatenated_vec);

    /* Verification */
    for (size_t i = 0; i < concatenated_vec.size(); i += 2) {
        EXPECT_EQ(sorted_concatenated_vec[i], sorted_concatenated_vec[i + 1]);
    }
}

/**
 * @brief Metamorphic Relation 28: Exchanging the position of any two elements should not alter the output of the sorted array.
 *
 */
TEST_P(QuickSortParamTest, MR28) {
    /* Get source input and ensure it has more than one element */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    if (source_vec.size() < 2) {
        source_vec.push_back(source_vec.front() + 1); // ensure at least two different elements
    }

    /* Sort the source array */
    vector<int> sorted_vec = quick_sort(source_vec);

    /* Exchange two elements in source array */
    std::swap(source_vec[0], source_vec[1]);

    /* Sort the modified array */
    vector<int> sorted_modified_vec = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(sorted_vec, sorted_modified_vec);
}

/**
 * @brief Metamorphic Relation 29: Sorting an array with elements in descending order should reverse their sequence in the output.
 *
 */
TEST_P(QuickSortParamTest, MR29) {
    /* Get source input and ensure it is sorted in descending order */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    std::sort(source_vec.begin(), source_vec.end(), std::greater<int>());

    /* Sort the source array to get into ascending order */
    vector<int> sorted_vec = quick_sort(source_vec);

    /* Expect the sorted_vec to be the reverse of source_vec */
    std::reverse(sorted_vec.begin(), sorted_vec.end());

    /* Verification */
    EXPECT_EQ(source_vec, sorted_vec);
}

/**
 * @brief Metamorphic Relation 30: Doubling the value of each element should not alter their relative sorting order.
 *
 */
TEST_P(QuickSortParamTest, MR30) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Double the value of each element */
    for (auto &val : source_vec) {
        val *= 2;
    }
    /* Sort the modified source array */
    vector<int> sorted_doubled_vec = quick_sort(source_vec);

    /* Halve the value of each element in the sorted doubled array */
    for (auto &val : sorted_doubled_vec) {
        val /= 2;
    }
    /* Sort the original source array */
    vector<int> sorted_vec = quick_sort(input.vec);

    /* Verification */
    EXPECT_EQ(sorted_vec, sorted_doubled_vec);
}

/**
 * @brief Metamorphic Relation 31: Sorting an input array of negative elements should yield a sorted array where the relative order is inverse to the sorting of
 * their absolute values.
 *
 */
TEST_P(QuickSortParamTest, MR31) {
    /* Get source input and negate all elements to ensure they are negative */
    QuickSortInput input = GetParam();
    vector<int> negative_vec(input.vec.size());
    std::transform(input.vec.begin(), input.vec.end(), negative_vec.begin(), [](int x) { return -abs(x); });

    /* Sort the negative vector */
    vector<int> sorted_negative_vec = quick_sort(negative_vec);

    /* Convert all elements to positive */
    vector<int> positive_vec(negative_vec.size());
    std::transform(sorted_negative_vec.begin(), sorted_negative_vec.end(), positive_vec.begin(), [](int x) { return abs(x); });

    /* Sort the positive vector */
    vector<int> sorted_positive_vec = quick_sort(positive_vec);

    /* Expect the sorted_positive_vec to be the reverse of sorted_negative_vec */
    std::reverse(sorted_positive_vec.begin(), sorted_positive_vec.end());

    /* Verification */
    EXPECT_EQ(positive_vec, sorted_positive_vec);
}

/**
 * @brief Metamorphic Relation 32: Sorting the same input array multiple times should yield the same output each time.
 *
 */
TEST_P(QuickSortParamTest, MR32) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the input array multiple times */
    vector<int> sorted_vec1 = quick_sort(source_vec);
    vector<int> sorted_vec2 = quick_sort(source_vec);
    vector<int> sorted_vec3 = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(sorted_vec1, sorted_vec2);
    EXPECT_EQ(sorted_vec2, sorted_vec3);
}

/**
 * @brief Metamorphic Relation 33: Sorting an array where each element is incremented by an index-dependent variable should have no effect on the sorted array
 * except each element should be increased by the same variable.
 *
 */
TEST_P(QuickSortParamTest, MR33) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Increment each element in the array by index */
    vector<int> incremented_vec(source_vec.size());
    std::transform(source_vec.begin(), source_vec.end(), incremented_vec.begin(), [increment = 0](int x) mutable { return x + increment++; });

    /* Sort the incremented array */
    vector<int> sorted_incremented_vec = quick_sort(incremented_vec);

    /* Correct the increment to get the original sort order */
    std::transform(sorted_incremented_vec.begin(), sorted_incremented_vec.end(), sorted_incremented_vec.begin(),
                   [decrement = (int)source_vec.size() - 1](int x) mutable { return x - decrement--; });

    /* Sort the original array */
    vector<int> sorted_vec = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(sorted_vec, sorted_incremented_vec);
}

/**
 * @brief Metamorphic Relation 34: Sorting an array and then removing outliers (smallest and largest elements) should not affect the order of the remaining
 * elements.
 *
 */
TEST_P(QuickSortParamTest, MR34) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the source array */
    vector<int> sorted_vec = quick_sort(source_vec);

    /* Remove first and last elements (smallest and largest) if the array has at least 3 elements */
    if (sorted_vec.size() > 2) {
        sorted_vec.erase(sorted_vec.begin()); // Remove smallest
        sorted_vec.erase(--sorted_vec.end()); // Remove largest
    }

    /* Verification */
    EXPECT_TRUE(std::is_sorted(sorted_vec.begin(), sorted_vec.end()));
}

/**
 * @brief Metamorphic Relation 35: Sorting an array and then applying a non-decreasing function to all elements should not change the relative order.
 *
 */
TEST_P(QuickSortParamTest, MR35) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the source array */
    vector<int> sorted_vec = quick_sort(source_vec);

    /* Apply a non-decreasing function,e.g., x -> 3*x + 1, to all sorted elements */
    vector<int> transformed_vec(sorted_vec.size());
    std::transform(sorted_vec.begin(), sorted_vec.end(), transformed_vec.begin(), [](int x) { return 3 * x + 1; });

    /* Verification */
    for (size_t i = 1; i < transformed_vec.size(); ++i) {
        EXPECT_LE(transformed_vec[i - 1], transformed_vec[i]);
    }
}

/**
 * @brief Metamorphic Relation 36: Sorting an array and inverting the sign of each element should result in a sorted array with signs inverted and reversed
 * order.
 *
 */
TEST_P(QuickSortParamTest, MR36) {  // Fixed
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the source array */
    vector<int> sorted_vec = quick_sort(source_vec);

    /* Invert the sign of each element and sort again */
    std::transform(sorted_vec.begin(), sorted_vec.end(), sorted_vec.begin(), [](int x) { return -x; });

    /* Construct a sorted array with signs inverted and reverse its order */
    vector<int> follow_vec = source_vec;
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return -x; });
    vector<int> follow_out = quick_sort(follow_vec);
    std::reverse(follow_out.begin(), follow_out.end());

    /* Verification */
    EXPECT_EQ(sorted_vec, follow_out);
}

/**
 * @brief Metamorphic Relation 37: Concatenating multiples of the same array, resizing, and sorting should not change the order of elements within the sub-range
 * of the original array size.
 *
 */
TEST_P(QuickSortParamTest, MR37) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Concatenate multiple copies of the array */
    vector<int> extended_vec = source_vec;
    for (int i = 0; i < 2; ++i) {
        extended_vec.insert(extended_vec.end(), source_vec.begin(), source_vec.end());
    }

    /* Resize the vector to include one and a half times the elements */
    extended_vec.resize(source_vec.size() + source_vec.size() / 2);

    /* Sort the extended array */
    vector<int> sorted_extended_vec = quick_sort(extended_vec);

    /* Sort the original array */
    vector<int> sorted_vec = quick_sort(source_vec);

    /* Verification */
    for (size_t i = 0; i < sorted_vec.size(); ++i) {
        EXPECT_EQ(sorted_vec[i], sorted_extended_vec[i]);
    }
}

/**
 * @brief Metamorphic Relation 38: Interleaving the sorted array with itself should result in each element appearing twice consecutively.
 *
 */
TEST_P(QuickSortParamTest, MR38) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the input array */
    vector<int> sorted_vec = quick_sort(source_vec);

    /* Interleave the sorted input array with itself */
    vector<int> interleaved_vec;
    for (int value : sorted_vec) {
        interleaved_vec.push_back(value);
        interleaved_vec.push_back(value);
    }

    /* Sort the interleaved array */
    vector<int> sorted_interleaved_vec = quick_sort(interleaved_vec);

    /* Verification: Each element of sorted_vec should appear twice consecutively in sorted_interleaved_vec */
    for (size_t i = 0; i < sorted_interleaved_vec.size(); i += 2) {
        EXPECT_EQ(sorted_interleaved_vec[i], sorted_interleaved_vec[i + 1]);
    }
}

/**
 * @brief Metamorphic Relation 39: Sorting an array and then applying a ceiling function to each element should not change the relative order of the elements.
 *
 */
TEST_P(QuickSortParamTest, MR39) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the input array */
    vector<int> sorted_vec = quick_sort(source_vec);

    /* Apply ceiling function on sorted array */
    vector<int> ceiling_vec = sorted_vec;
    std::transform(ceiling_vec.begin(), ceiling_vec.end(), ceiling_vec.begin(), [](int x) -> int {
        return (x % 10) ? (x + 10 - x % 10) : x; // Ceiling to the nearest multiple of 10
    });

    /* Verification: ceiling(sorted_vec) should have the same relative order as sorted_vec */
    for (size_t i = 1; i < ceiling_vec.size(); i++) {
        EXPECT_LE(ceiling_vec[i - 1], ceiling_vec[i]);
    }
}

/**
 * @brief Metamorphic Relation 40: Sorting an array where all elements are set to the median of the original unsorted array should result in identical elements.
 *
 */
TEST_P(QuickSortParamTest, MR40) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Calculate the median value of the unsorted array */
    vector<int> vec_copy = source_vec; // Copy for median calculation
    sort(vec_copy.begin(), vec_copy.end());
    int median = vec_copy[vec_copy.size() / 2];

    /* Set all elements in the original array to the median value */
    std::fill(source_vec.begin(), source_vec.end(), median);

    /* Sort the array with all median values */
    vector<int> sorted_median_vec = quick_sort(source_vec);

    /* Verification: sorted_median_vec should have identical values (median) */
    for (size_t i = 0; i < sorted_median_vec.size(); i++) {
        EXPECT_EQ(sorted_median_vec[i], median);
    }
}

/**
 * @brief Metamorphic Relation 41: Sorting an array and then extracting every k-th element should result in a sorted subset.
 *
 */
TEST_P(QuickSortParamTest, MR41) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the input array */
    vector<int> sorted_vec = quick_sort(source_vec);

    /* Extract every k-th element to form a subset, here k = 3 */
    const int k = 3;
    vector<int> subset_vec;
    for (size_t i = 0; i < sorted_vec.size(); i += k) {
        subset_vec.push_back(sorted_vec[i]);
    }

    /* Verification: The subset formed by every kth element should be sorted */
    EXPECT_TRUE(std::is_sorted(subset_vec.begin(), subset_vec.end()));
}

/**
 * @brief Metamorphic Relation 42: Sorting an array and then negating all the elements should result in a sorted array in descending order.
 *
 */
TEST_P(QuickSortParamTest, MR42) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the input array */
    vector<int> sorted_vec = quick_sort(source_vec);

    /* Negate all elements of the sorted array */
    std::transform(sorted_vec.begin(), sorted_vec.end(), sorted_vec.begin(), [](int x) { return -x; });

    /* Verification: Negated sorted array should be in descending order */
    EXPECT_TRUE(std::is_sorted(sorted_vec.begin(), sorted_vec.end(), std::greater<int>()));
}

/**
 * @brief Metamorphic Relation 43: Sorting an array after setting all elements to their maximum should result in an array with identical values.
 *
 */
TEST_P(QuickSortParamTest, MR43) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Find maximum element in the array */
    int max_elem = *std::max_element(source_vec.begin(), source_vec.end());

    /* Set all elements to the maximum value */
    std::fill(source_vec.begin(), source_vec.end(), max_elem);

    /* Sort the modified array */
    vector<int> sorted_vec = quick_sort(source_vec);

    /* Verification: All elements in sorted_vec should be equal to max_elem */
    for (int elem : sorted_vec) {
        EXPECT_EQ(elem, max_elem);
    }
}

/**
 * @brief Metamorphic Relation 44: Sorting an array and then applying modulus with a non-zero divisor should not alter the relative order of non-zero elements.
 *
 */
TEST_P(QuickSortParamTest, MR44) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the input array */
    vector<int> sorted_vec = quick_sort(source_vec);

    /* Apply modulus with a divisor (such as 2) to all sorted elements */
    int divisor = 2;
    std::transform(sorted_vec.begin(), sorted_vec.end(), sorted_vec.begin(), [divisor](int x) { return x % divisor; });

    /* Verification: sorted_vec with modulus applied should not alter the relative order of non-zero elements */
    int last_non_zero = -1;
    for (int elem : sorted_vec) {
        if (elem != 0) {
            if (last_non_zero != -1) {
                EXPECT_LE(last_non_zero, elem);
            }
            last_non_zero = elem;
        }
    }
}

/**
 * @brief Metamorphic Relation 45: Sorting an array and then shuffling elements within sub-ranges should result in the sub-ranges being in sorted order.
 *
 */
TEST_P(QuickSortParamTest, MR45) {
    /* Get source input and sort it */
    QuickSortInput input = GetParam();
    vector<int> sorted_vec = quick_sort(input.vec);

    /* Shuffle elements within sub-ranges */
    std::default_random_engine rng{std::random_device{}()};
    int subrange_length = 5; // Assuming the sub-ranges have a fixed length, e.g., 5
    for (size_t i = 0; i < sorted_vec.size(); i += subrange_length) {
        size_t end_range = std::min(i + subrange_length, sorted_vec.size());
        std::shuffle(sorted_vec.begin() + i, sorted_vec.begin() + end_range, rng);
    }

    /* Sort each sub-range */
    for (size_t i = 0; i < sorted_vec.size(); i += subrange_length) {
        size_t end_range = std::min(i + subrange_length, sorted_vec.size());
        std::sort(sorted_vec.begin() + i, sorted_vec.begin() + end_range);
    }

    /* Verification: Each sub-range should be in sorted order */
    for (size_t i = 0; i < sorted_vec.size(); i += subrange_length) {
        size_t end_range = std::min(i + subrange_length, sorted_vec.size());
        EXPECT_TRUE(std::is_sorted(sorted_vec.begin() + i, sorted_vec.begin() + end_range));
    }
}

INSTANTIATE_TEST_CASE_P(TrueReturn, QuickSortParamTest, testing::ValuesIn(gen_tcs_randomly()));
