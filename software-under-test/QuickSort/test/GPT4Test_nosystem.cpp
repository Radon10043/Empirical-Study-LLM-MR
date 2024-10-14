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
 * @brief Metamorphic Relation 4: Doubling each element in the input array. The sorted sequence 
 * returned should be the same as the original sorted sequence, but with each element doubled.
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
    for (auto &elem : follow_vec)
        elem *= 2;

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    for (size_t i = 0; i < source_out.size(); ++i)
        source_out[i] *= 2;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 5: Reversing the input array should not affect the sorted output.
 *
 */
TEST_P(QuickSortParamTest, MR5) {
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
 * @brief Metamorphic Relation 6: Concatenating any sorted array to the input array should result in the
 * same sorted array but with the added sorted elements appended in order.
 *
 */
TEST_P(QuickSortParamTest, MR6) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> sorted_suffix = {10, 11, 12, 13, 14, 15}; // Assume this is sorted
    vector<int> follow_vec = source_vec;
    follow_vec.insert(follow_vec.end(), sorted_suffix.begin(), sorted_suffix.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    vector<int> expected_out = source_out;
    expected_out.insert(expected_out.end(), sorted_suffix.begin(), sorted_suffix.end());
    EXPECT_EQ(follow_out, expected_out);
}

/**
 * @brief Metamorphic Relation 7: Removing any number of elements from the input should result in a sorted array
 * that contains all the elements from the original sorted output, except for the ones that were removed.
 *
 */
TEST_P(QuickSortParamTest, MR7) {   // Fixed
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    if (source_vec.size() < 5) GTEST_SKIP();

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;

    // Remove elements from the array (e.g., at random positions or specific indices)
    vector<int> indices_to_remove = {2, 4}; // Example positions, we assume they are valid
    for (int i = indices_to_remove.size() - 1; i >= 0; --i) {
        int index = indices_to_remove[i];
        follow_vec.erase(follow_vec.begin() + index);
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    vector<int> expected_out = source_out;
    for (int i = indices_to_remove.size() - 1; i >= 0; --i) {
        int index = find(expected_out.begin(), expected_out.end(), source_vec[indices_to_remove[i]]) - expected_out.begin();
        expected_out.erase(expected_out.begin() + index);
    }
    EXPECT_EQ(expected_out, follow_out);
}
/**
 * @brief Metamorphic Relation 8: Concatenating a duplicate of the input array should result in a sorted 
 * array where each element from the original array appears twice in sequence.
 *
 */
TEST_P(QuickSortParamTest, MR8) {   // Fixed
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
    for (int i = 0, j = 0; i < source_out.size(), j < follow_out.size(); i++, j += 2) {
        EXPECT_EQ(source_out[i], follow_out[j]);
        EXPECT_EQ(source_out[i], follow_out[j + 1]);
    }
}

/**
 * @brief Metamorphic Relation 9: Permuting the elements in the output array will not affect the final sorted array.
 *
 */
TEST_P(QuickSortParamTest, MR9) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output and permute it */
    vector<int> permuted_vec = quick_sort(source_vec);
    shuffle(permuted_vec.begin(), permuted_vec.end(), random_device());

    /* Sorting the permuted vector */
    vector<int> followed_out = quick_sort(permuted_vec);

    /* Verification */
    EXPECT_EQ(followed_out, quick_sort(source_vec));
}

/**
 * @brief Metamorphic Relation 10: If we split the input array into two arbitrary subsets and sort them 
 * separately then concatenate and sort the results, it should match the sorted array of the combined original input.
 *
 */
TEST_P(QuickSortParamTest, MR10) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    // Split into two subsets, can pick elements at random or use an even/odd criteria for simplicity
    vector<int> subset1, subset2;
    for (size_t i = 0; i < source_vec.size(); ++i) {
        if (i % 2 == 0)
            subset1.push_back(source_vec[i]);
        else
            subset2.push_back(source_vec[i]);
    }

    /* Sort individual subsets */
    subset1 = quick_sort(subset1);
    subset2 = quick_sort(subset2);

    /* Concatenate the sorted subsets and sort */
    vector<int> concatenated = subset1;
    concatenated.insert(concatenated.end(), subset2.begin(), subset2.end());
    vector<int> follow_out = quick_sort(concatenated);

    /* Verification */
    EXPECT_EQ(follow_out, quick_sort(source_vec));
}

/**
 * @brief Metamorphic Relation 11: If an element x is removed from the input array and then added back after 
 * the array is sorted, resulting array should be sorted and be the same as the original sorted array.
 *
 */
TEST_P(QuickSortParamTest, MR11) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    if (source_vec.empty()) return; // Ensure there's at least one element to remove

    /* Remove an element, sort, then add it back */
    int removed = source_vec.back(); // Remove the last element (or any other element)
    source_vec.pop_back();
    vector<int> sorted_vec_without_x = quick_sort(source_vec);
    sorted_vec_without_x.push_back(removed); // Add the removed element back

    /* Sort the new vector with x added back */
    vector<int> follow_out = quick_sort(sorted_vec_without_x);

    /* Verification */
    EXPECT_EQ(follow_out, quick_sort(input.vec));
}
/**
 * @brief Metamorphic Relation 12: If the input array is already sorted, the output should remain unchanged 
 * when the `quick_sort` function is applied again.
 *
 */
TEST_P(QuickSortParamTest, MR12) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> sorted_vec = quick_sort(input.vec);

    /* Apply quick_sort again on the sorted vector */
    vector<int> sorted_again = quick_sort(sorted_vec);

    /* Verification */
    EXPECT_EQ(sorted_again, sorted_vec);
}

/**
 * @brief Metamorphic Relation 13: Concatenating the input array with itself in reverse should result in a
 * sorted array with two sequences of each element.
 *
 */
TEST_P(QuickSortParamTest, MR13) {  // Fixed
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get sorted version of source input */
    vector<int> sorted_vec = quick_sort(source_vec);

    /* Construct follow-up input by concatenating the input with its reverse */
    vector<int> reverse_vec(source_vec.rbegin(), source_vec.rend());
    source_vec.insert(source_vec.end(), reverse_vec.begin(), reverse_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(source_vec);

    /* Verification */
    for (int i = 0, j = 0; i < sorted_vec.size(), j < follow_out.size(); i++, j += 2) {
        EXPECT_EQ(sorted_vec[i], follow_out[j]);
        EXPECT_EQ(sorted_vec[i], follow_out[j + 1]);
    }
}

/**
 * @brief Metamorphic Relation 14: Repeating each element in the input array should result in each element
 * in the sorted output also being repeated.
 *
 */
TEST_P(QuickSortParamTest, MR14) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Double each element in the input vector */
    vector<int> modified_vec;
    for (int num : source_vec) {
        modified_vec.push_back(num);
        modified_vec.push_back(num); // Repeat the element
    }

    /* Get the sorted result of the modified vector */
    vector<int> follow_out = quick_sort(modified_vec);

    /* Verification */
    vector<int> expected_out;
    for (int num : quick_sort(source_vec)) {
        expected_out.push_back(num);
        expected_out.push_back(num); // Expected element to be repeated
    }
    EXPECT_EQ(follow_out, expected_out);
}

/**
 * @brief Metamorphic Relation 15: Sorting two separate arrays and then merging the sorted arrays 
 * should yield the same output as sorting the merged array of unsorted inputs.
 *
 */
TEST_P(QuickSortParamTest, MR15) {
    /* Get first source input */
    QuickSortInput input1 = GetParam();
    vector<int> source_vec1 = input1.vec;

    /* Get second source input */
    QuickSortInput input2 = GetParam(); // Assume GetParam generates a different parameter
    vector<int> source_vec2 = input2.vec;

    /* Sort both source vectors separately */
    vector<int> sorted_vec1 = quick_sort(source_vec1);
    vector<int> sorted_vec2 = quick_sort(source_vec2);

    /* Merge the two sorted vectors */
    vector<int> merged_sorted;
    std::merge(sorted_vec1.begin(), sorted_vec1.end(), sorted_vec2.begin(), sorted_vec2.end(), std::back_inserter(merged_sorted));

    /* Combine the two source vectors and sort the combination */
    vector<int> combined_vec = source_vec1;
    combined_vec.insert(combined_vec.end(), source_vec2.begin(), source_vec2.end());
    vector<int> sorted_combined = quick_sort(combined_vec);

    /* Verification */
    EXPECT_EQ(merged_sorted, sorted_combined);
}

/**
 * @brief Metamorphic Relation 16: Inverting the order of the sorted output array (e.g., from ascending to 
 * descending) and then applying the `quick_sort` function should return a sorted array in ascending order.
 *
 */
TEST_P(QuickSortParamTest, MR16) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    vector<int> sorted_vec = quick_sort(source_vec);

    // Invert the sorted array order
    std::reverse(sorted_vec.begin(), sorted_vec.end());

    // Sort the inverted array
    vector<int> sorted_inverted_vec = quick_sort(sorted_vec);

    /* Verification */
    EXPECT_EQ(sorted_inverted_vec, quick_sort(source_vec));
}

/**
 * @brief Metamorphic Relation 17: Sorting an array composed of a single repeated value should result in
 * the same array.
 *
 */
TEST_P(QuickSortParamTest, MR17) {
    /* Create a vector with repeated elements */
    vector<int> repeated_value_vec(10, 0); // Vector with 10 zeros

    /* Apply quick_sort on this vector */
    vector<int> sorted_repeated_value_vec = quick_sort(repeated_value_vec);

    /* Verification */
    EXPECT_EQ(sorted_repeated_value_vec, repeated_value_vec);
}

/**
 * @brief Metamorphic Relation 18: If one input array is a subset of another, the sorted array of the subset 
 * should be a subset of the sorted array of the superset.
 *
 */
TEST_P(QuickSortParamTest, MR18) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> superset_vec = input.vec;
    vector<int> subset_vec(superset_vec.begin(), superset_vec.begin() + superset_vec.size() / 2); // Take the first half as a subset

    /* Sort both vectors */
    vector<int> sorted_superset_vec = quick_sort(superset_vec);
    vector<int> sorted_subset_vec = quick_sort(subset_vec);

    /* Check that all elements in the sorted subset are in the sorted superset */
    bool is_subset = std::includes(sorted_superset_vec.begin(), sorted_superset_vec.end(), sorted_subset_vec.begin(), sorted_subset_vec.end());

    /* Verification */
    EXPECT_TRUE(is_subset);
}

/**
 * @brief Metamorphic Relation 19: Replacing an element with another such that the relative ordering does 
 * not change should not affect the sorted order (e.g., replacing a middle value with another number that 
 * keeps it in the middle).
 *
 */
TEST_P(QuickSortParamTest, MR19) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    if (source_vec.size() < 3) return; // Ensure there's an element to replace in the middle

    /* Get sorted output */
    vector<int> sorted_vec = quick_sort(source_vec);

    /* Create follow-up input by replacing a middle value */
    vector<int> follow_vec = source_vec;
    size_t mid_index = follow_vec.size() / 2;
    follow_vec[mid_index] = follow_vec[mid_index - 1] + (follow_vec[mid_index + 1] - follow_vec[mid_index - 1]) / 2; // New value that keeps it in the middle

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    // We can't directly compare the sorted vectors since the change could affect the final positions.
    // However, we know that the relative ordering should be the same, and this can be checked by comparing
    // the original and modified inputs against their respective outputs.
    std::sort(follow_vec.begin(), follow_vec.end());
    EXPECT_EQ(follow_out, follow_vec);
    EXPECT_NE(follow_vec, sorted_vec); // The vectors should not be identical due to the replacement
}

/**
 * @brief Metamorphic Relation 20: Concatenating the input array with a new array with smaller values 
 * should still yield a sorted array, and the additional elements should appear at the beginning of
 * the resultant array.
 *
 */
TEST_P(QuickSortParamTest, MR20) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get sorted output */
    vector<int> sorted_vec = quick_sort(source_vec);
    
    /* Create an array with smaller values than the minimum of source_vec */
    vector<int> smaller_values_vec(5, *min_element(sorted_vec.begin(), sorted_vec.end()) - 1); // Assuming min_element returns a valid iterator

    /* Concatenate the smaller values in front of the original vector */
    vector<int> combined_vec(smaller_values_vec);
    combined_vec.insert(combined_vec.end(), source_vec.begin(), source_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(combined_vec);

    /* Verification */
    // Verify the smaller values appear at the start of the sorted combined vector
    for (size_t i = 0; i < smaller_values_vec.size(); ++i) {
        EXPECT_EQ(follow_out[i], smaller_values_vec[i]);
    }
}
/**
 * @brief Metamorphic Relation 21: If an element is inserted into the sorted array such that it maintains 
 * the sorted order, then applying the `quick_sort` function should return the same sorted array with 
 * the inserted element.
 *
 */
TEST_P(QuickSortParamTest, MR21) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> sorted_vec = quick_sort(input.vec);

    // Insert an element that maintains the sorted order
    int new_element = sorted_vec[0] - 1; // Smaller than the first element
    sorted_vec.insert(sorted_vec.begin(), new_element); // Insert at the beginning

    // Apply quick_sort after the insertion
    vector<int> follow_out = quick_sort(sorted_vec);

    /* Verification */
    EXPECT_EQ(follow_out, sorted_vec);
}

/**
 * @brief Metamorphic Relation 22: If the input array consists of consecutive numbers in increasing order,
 * then sorting the array should yield the same array.
 *
 */
TEST_P(QuickSortParamTest, MR22) {
    // Create a vector with consecutive numbers
    vector<int> consecutive_vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Apply quick_sort on this vector
    vector<int> sorted_consecutive_vec = quick_sort(consecutive_vec);

    /* Verification */
    EXPECT_EQ(sorted_consecutive_vec, consecutive_vec);
}

/**
 * @brief Metamorphic Relation 23: If two elements are swapped in the input array (neither at the first 
 * nor at the last position), it should not affect the final sorted output compared to the original unswapped array.
 *
 */
TEST_P(QuickSortParamTest, MR23) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    
    if (source_vec.size() < 3) return; // Ensure there's enough elements to perform a swap

    // Sort original input
    vector<int> sorted_source_vec = quick_sort(source_vec);

    // Swap two elements not at the ends
    std::swap(source_vec[1], source_vec[2]); // Swap second and third element

    // Sort swapped input
    vector<int> sorted_swapped_vec = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(sorted_swapped_vec, sorted_source_vec);
}

/**
 * @brief Metamorphic Relation 24: Sorting a list with a single duplicated element removed should result 
 * in a list that has one fewer occurrence of that element than the list that includes the duplicate.
 *
 */
TEST_P(QuickSortParamTest, MR24) {
    /* Get source input */
    QuickSortInput input = GetParam();
    if (input.vec.empty()) return; // Must have at least one element to duplicate

    vector<int> source_vec = input.vec;

    // Sort original input
    vector<int> sorted_source_vec = quick_sort(source_vec);

    // Duplicate last element and sort
    source_vec.push_back(source_vec.back());
    vector<int> sorted_with_duplicate = quick_sort(source_vec);

    // Remove duplicated element
    source_vec.pop_back();
    
    /* Verification */
    EXPECT_EQ(sorted_source_vec, source_vec);
    EXPECT_EQ(sorted_with_duplicate.size(), sorted_source_vec.size() + 1);
}

/**
 * @brief Metamorphic Relation 25: Sorting two identical arrays independently and then interchanging the
 * elements at any two positions should leave the arrays out of order.
 *
 */
TEST_P(QuickSortParamTest, MR25) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec1 = input.vec;
    vector<int> source_vec2 = input.vec;

    // Sort both arrays
    vector<int> sorted_vec1 = quick_sort(source_vec1);
    vector<int> sorted_vec2 = quick_sort(source_vec2);

    if (sorted_vec1.size() < 2) return; // Ensure there's enough elements to perform interchange

    // Interchange elements at two positions
    std::swap(sorted_vec1[0], sorted_vec2[1]);

    /* Verification */
    EXPECT_FALSE(std::is_sorted(sorted_vec1.begin(), sorted_vec1.end()));
    EXPECT_FALSE(std::is_sorted(sorted_vec2.begin(), sorted_vec2.end()));
}
/**
 * @brief Metamorphic Relation 26: Sorting the input array and then inverting the sign of each element 
 * should yield an array that is the inverse of the original sorted array.
 *
 */
TEST_P(QuickSortParamTest, MR26) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Sort the array and then invert the signs
    vector<int> sorted_vec = quick_sort(source_vec);
    std::transform(sorted_vec.begin(), sorted_vec.end(), sorted_vec.begin(), std::negate<int>());

    // Sort the inverted array
    vector<int> sorted_inverted_vec = quick_sort(sorted_vec);

    // Invert the signs of the sorted_inverted_vec to compare
    std::transform(sorted_inverted_vec.begin(), sorted_inverted_vec.end(), sorted_inverted_vec.begin(), std::negate<int>());

    /* Verification */
    std::reverse(sorted_vec.begin(), sorted_vec.end()); // Original sorted vector with signs inverted
    EXPECT_EQ(sorted_inverted_vec, sorted_vec);
}

/**
 * @brief Metamorphic Relation 27: If each element in the input array is incremented by the same value, the 
 * order of elements in the sorted output should not change.
 *
 */
TEST_P(QuickSortParamTest, MR27) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Sort original array
    vector<int> sorted_original_vec = quick_sort(source_vec);

    // Increment each element by a value
    int value = 5;
    for (int &elem : source_vec) {
        elem += value;
    }

    // Sort the modified array
    vector<int> sorted_modified_vec = quick_sort(source_vec);

    // Decrement each element of the sorted modified array to compare
    for (int &elem : sorted_modified_vec) {
        elem -= value;
    }

    /* Verification */
    EXPECT_EQ(sorted_modified_vec, sorted_original_vec);
}

/**
 * @brief Metamorphic Relation 28: Concatenating the input array with an array of elements all greater 
 * than the max element of the input array should yield the input array followed by the concatenated 
 * elements in the sorted output.
 *
 */
TEST_P(QuickSortParamTest, MR28) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Find max element in the input array to construct greater elements vector
    int max_value = *max_element(source_vec.begin(), source_vec.end());
    vector<int> greater_elements_vec = {max_value + 1, max_value + 2, max_value + 3};

    // Combine original array and greater elements
    vector<int> combined_vec = source_vec;
    combined_vec.insert(combined_vec.end(), greater_elements_vec.begin(), greater_elements_vec.end());

    // Sort combined array
    vector<int> sorted_combined_vec = quick_sort(combined_vec);

    /* Verification */
    // The elements from greater_elements_vec should appear at the end of the sorted_combined_vec
    for (size_t i = 0; i < greater_elements_vec.size(); ++i) {
        EXPECT_EQ(sorted_combined_vec[source_vec.size() + i], greater_elements_vec[i]);
    }
}

/**
 * @brief Metamorphic Relation 29: Sorting an input array that consists of two interlaced sorted sequences 
 * should yield the same sorted array as sorting each sequence individually and then merging them.
 *
 */
TEST_P(QuickSortParamTest, MR29) {
    /* Create two sorted vectors */
    vector<int> sorted_vec1 = {1, 3, 5, 7, 9};
    vector<int> sorted_vec2 = {2, 4, 6, 8, 10};
    
    // Combine them into an interlaced vector
    vector<int> interlaced_vec;
    for (size_t i = 0; i < sorted_vec1.size(); ++i) {
        interlaced_vec.push_back(sorted_vec1[i]);
        interlaced_vec.push_back(sorted_vec2[i]);
    }

    // Sort the interlaced vector
    vector<int> sorted_interlaced_vec = quick_sort(interlaced_vec);

    // Merge sorted sequences
    vector<int> merged_sorted_vec;
    std::merge(sorted_vec1.begin(), sorted_vec1.end(), sorted_vec2.begin(), sorted_vec2.end(), std::back_inserter(merged_sorted_vec));

    /* Verification */
    EXPECT_EQ(sorted_interlaced_vec, merged_sorted_vec);
}

/**
 * @brief Metamorphic Relation 30: Sorting an array and then creating a new array where the sign of each 
 * element is random (positive or negative) should, after sorting, give a result where the absolute values 
 * are in sorted order.
 *
 */
TEST_P(QuickSortParamTest, MR30) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Sort the source array
    vector<int> sorted_vec = quick_sort(source_vec);

    // Create a new array where the sign of each element is random
    std::default_random_engine re(static_cast<unsigned>(time(nullptr)));
    std::uniform_int_distribution<int> dist(0, 1);

    vector<int> randomized_signs_vec;
    for (int value : sorted_vec) {
        randomized_signs_vec.push_back(dist(re) == 0 ? value : -value);
    }

    // Sort the new array
    vector<int> sorted_randomized_signs_vec = quick_sort(randomized_signs_vec);

    // Compare the absolute values with the sorted array
    std::transform(
        sorted_randomized_signs_vec.begin(),
        sorted_randomized_signs_vec.end(),
        sorted_randomized_signs_vec.begin(),
        [](int val) { return std::abs(val); }
    );

    /* Verification */
    EXPECT_EQ(sorted_randomized_signs_vec, sorted_vec);
}
/**
 * @brief Metamorphic Relation 31: Replicating each element in the input array several times and then 
 * sorting should maintain the order but with replicated elements.
 *
 */
TEST_P(QuickSortParamTest, MR31) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Sort the input array
    vector<int> sorted_vec = quick_sort(source_vec);

    int replication_count = 3; // Each element will be replicated this many times
    vector<int> replicated_vec;

    // Replicate each sorted element
    for (int value : sorted_vec) {
        for (int i = 0; i < replication_count; ++i) {
            replicated_vec.push_back(value);
        }
    }

    // Sort the replicated array
    vector<int> sorted_replicated_vec = quick_sort(replicated_vec);

    /* Verification */
    EXPECT_EQ(sorted_replicated_vec, replicated_vec);
}

/**
 * @brief Metamorphic Relation 32: Removing all but one instance of each unique element in the input
 * should yield a sorted array of unique elements when sorted.
 *
 */
TEST_P(QuickSortParamTest, MR32) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Sort the source array
    vector<int> sorted_vec = quick_sort(source_vec);

    // Remove duplicates, maintaining only one instance of each element
    auto it = std::unique(sorted_vec.begin(), sorted_vec.end());
    sorted_vec.erase(it, sorted_vec.end());

    // Sort the array of unique elements
    vector<int> sorted_unique_vec = quick_sort(sorted_vec);

    /* Verification */
    EXPECT_EQ(sorted_unique_vec, sorted_vec);
}

/**
 * @brief Metamorphic Relation 33: If elements of the input array are pairwise swapped (e.g., first and 
 * second, third and fourth, ...), the outcome of sorting should not change compared to sorting without
 * such swaps.
 *
 */
TEST_P(QuickSortParamTest, MR33) {
    /* Get source input and sort it */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;
    vector<int> sorted_vec = quick_sort(source_vec);

    // Perform pairwise swaps on the source array
    for (size_t i = 1; i < source_vec.size(); i += 2) {
        std::swap(source_vec[i], source_vec[i - 1]);
    }

    // Sort the array after the pairwise swaps
    vector<int> sorted_swapped_vec = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(sorted_swapped_vec, sorted_vec);
}

/**
 * @brief Metamorphic Relation 34: If all negative numbers are removed from the input array and the 
 * remaining array is sorted, the output should equal the positive part of the original sorted array.
 *
 */
TEST_P(QuickSortParamTest, MR34) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Sort the source array
    vector<int> sorted_vec = quick_sort(source_vec);

    // Remove negatives from both
    source_vec.erase(std::remove_if(source_vec.begin(), source_vec.end(), [](int n) { return n < 0; }), source_vec.end());
    sorted_vec.erase(std::remove_if(sorted_vec.begin(), sorted_vec.end(), [](int n) { return n < 0; }), sorted_vec.end());

    // Sort the positive-only source array
    vector<int> sorted_positive_vec = quick_sort(source_vec);

    /* Verification */
    EXPECT_EQ(sorted_positive_vec, sorted_vec);
}

/**
 * @brief Metamorphic Relation 35: Sorting two input arrays of equal elements (e.g., all zeros) of 
 * different lengths should produce sorted arrays with the only difference being the length.
 *
 */
TEST_P(QuickSortParamTest, MR35) {
    /* Create input arrays */
    vector<int> input_vec_short(10, 0); // Short array with all zeros

    // Longer vector with the same element (all zeros)
    vector<int> input_vec_long(20, 0); 

    // Sort both arrays
    vector<int> sorted_vec_short = quick_sort(input_vec_short);
    vector<int> sorted_vec_long = quick_sort(input_vec_long);

    /* Verification */
    EXPECT_TRUE(std::all_of(sorted_vec_short.begin(), sorted_vec_short.end(), [](int n) { return n == 0; }));
    EXPECT_TRUE(std::all_of(sorted_vec_long.begin(), sorted_vec_long.end(), [](int n) { return n == 0; }));
    EXPECT_EQ(sorted_vec_short.size(), input_vec_short.size());
    EXPECT_EQ(sorted_vec_long.size(), input_vec_long.size());
    EXPECT_NE(sorted_vec_short.size(), sorted_vec_long.size());
}
/**
 * @brief Metamorphic Relation 36: Replacing a subset of the input array with elements greater than any 
 * in the original array should result in a sorted array where these greater elements appear at the end.
 *
 */
TEST_P(QuickSortParamTest, MR36) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Sort the source array
    vector<int> sorted_vec = quick_sort(source_vec);
    if(sorted_vec.empty()) return; // Cannot replace an empty array

    int greater_element = sorted_vec.back() + 1; // Ensure greater than any in the original
    // Replace a subset of the original array with greater elements
    for (size_t i = sorted_vec.size() / 2; i < sorted_vec.size(); ++i) {
        sorted_vec[i] = greater_element++;
    }

    // Sort the modified array
    vector<int> modified_sorted = quick_sort(sorted_vec);

    /* Verification: the final half should match the sequence we introduced */
    for (size_t i = sorted_vec.size() / 2; i < sorted_vec.size(); ++i) {
        EXPECT_EQ(modified_sorted.at(i), i - sorted_vec.size() / 2 + modified_sorted.at(sorted_vec.size() / 2));
    }
}

/**
 * @brief Metamorphic Relation 37: The union of sorted arrays from disjoint subsets of the input 
 * array should be equal to the sorted array of the original array.
 *
 */
TEST_P(QuickSortParamTest, MR37) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Create disjoint subsets
    vector<int> subset1(source_vec.begin(), source_vec.begin() + source_vec.size() / 2);
    vector<int> subset2(source_vec.begin() + source_vec.size() / 2, source_vec.end());
    
    // Sort the subsets and the original array
    vector<int> sorted_subset1 = quick_sort(subset1);
    vector<int> sorted_subset2 = quick_sort(subset2);
    vector<int> sorted_vec = quick_sort(source_vec);

    // Union of sorted subsets
    vector<int> sorted_union_subset(sorted_subset1);
    sorted_union_subset.insert(sorted_union_subset.end(), sorted_subset2.begin(), sorted_subset2.end());
    sort(sorted_union_subset.begin(), sorted_union_subset.end());

    /* Verification */
    EXPECT_EQ(sorted_union_subset, sorted_vec);
}

/**
 * @brief Metamorphic Relation 38: The sorted output should not change if a sorted array is concatenated 
 * with the original array and then the entire collection is sorted.
 *
 */
TEST_P(QuickSortParamTest, MR38) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Sort the source array
    vector<int> sorted_vec = quick_sort(source_vec);

    // Concatenate sorted array with the original array
    vector<int> concatenated_vec(sorted_vec);
    concatenated_vec.insert(concatenated_vec.end(), source_vec.begin(), source_vec.end());

    // Sort the concatenated array
    vector<int> sorted_concatenated = quick_sort(concatenated_vec);

    /* Verification: we need to replicate the sorted array before comparing */
    vector<int> expected_sorted(sorted_vec);
    expected_sorted.insert(expected_sorted.end(), sorted_vec.begin(), sorted_vec.end());
    sort(expected_sorted.begin(), expected_sorted.end());
    
    EXPECT_EQ(sorted_concatenated, expected_sorted);
}

/**
 * @brief Metamorphic Relation 39: Sorting a collection of arrays with assorted ranges should still 
 * yield a fully sorted array when all are combined and then sorted collectively.
 *
 */
TEST_P(QuickSortParamTest, MR39) {
    /* Create assorted range arrays */
    vector<int> range1 = {1, 4, 7};
    vector<int> range2 = {-2, 0, 3};
    vector<int> range3 = {2, 5, 8};

    // Combine ranges, then sort
    vector<int> combined_ranges;
    combined_ranges.insert(combined_ranges.end(), range1.begin(), range1.end());
    combined_ranges.insert(combined_ranges.end(), range2.begin(), range2.end());
    combined_ranges.insert(combined_ranges.end(), range3.begin(), range3.end());
    vector<int> sorted_combined = quick_sort(combined_ranges);

    /* Verification */
    // Sort arrays individually
    vector<int> sorted_range1 = quick_sort(range1);
    vector<int> sorted_range2 = quick_sort(range2);
    vector<int> sorted_range3 = quick_sort(range3);

    // Combine individually sorted ranges
    vector<int> sorted_ranges_combined(sorted_range1);
    sorted_ranges_combined.insert(sorted_ranges_combined.end(), sorted_range2.begin(), sorted_range2.end());
    sorted_ranges_combined.insert(sorted_ranges_combined.end(), sorted_range3.begin(), sorted_range3.end());
    
    // The combined sorted ranges should match the collective sort result
    EXPECT_EQ(sorted_combined, sorted_ranges_combined);
}

/**
 * @brief Metamorphic Relation 40: If a zero-sum pair (x, -x) is added to the input array, the output 
 * array should still be sorted and include both new elements.
 *
 */
TEST_P(QuickSortParamTest, MR40) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Sort the input array
    vector<int> sorted_vec = quick_sort(source_vec);

    // Add a zero-sum pair to the array
    int positive_value = 10; // Example of a positive value not present in the array
    source_vec.push_back(positive_value);
    source_vec.push_back(-positive_value);

    // Sort the new array
    vector<int> sorted_with_zerosum = quick_sort(source_vec);

    /* Verification */
    bool found_positive = std::find(sorted_with_zerosum.begin(), sorted_with_zerosum.end(), positive_value) != sorted_with_zerosum.end();
    bool found_negative = std::find(sorted_with_zerosum.begin(), sorted_with_zerosum.end(), -positive_value) != sorted_with_zerosum.end();
    
    EXPECT_TRUE(found_positive && found_negative);
}
/**
 * @brief Metamorphic Relation 41: Sorting an array, then negating all its elements should give the
 * same result as sorting the array after having negated all its original elements.
 *
 */
TEST_P(QuickSortParamTest, MR41) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Negate all elements of the original array
    vector<int> negated_source_vec(source_vec.size());
    std::transform(source_vec.begin(), source_vec.end(), negated_source_vec.begin(), std::negate<int>());

    // Sort the negated array
    vector<int> sorted_negated_source_vec = quick_sort(negated_source_vec);

    // Negate all elements of the original sorted array
    vector<int> sorted_vec = quick_sort(source_vec);
    vector<int> negated_sorted_vec(sorted_vec.size());
    std::transform(sorted_vec.begin(), sorted_vec.end(), negated_sorted_vec.begin(), std::negate<int>());
    
    /* Verification */
    EXPECT_EQ(sorted_negated_source_vec, negated_sorted_vec);
}

/**
 * @brief Metamorphic Relation 42: Concatenating the input array with itself one or more times should 
 * produce a sorted array with repeated sequences equivalent to the sorted version of the input array.
 *
 */
TEST_P(QuickSortParamTest, MR42) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Sort the source array
    vector<int> sorted_vec = quick_sort(source_vec);

    // Concatenate the original array with itself
    vector<int> duplicated_vec(source_vec);
    duplicated_vec.insert(duplicated_vec.end(), source_vec.begin(), source_vec.end());

    // Sort the concatenated array
    vector<int> sorted_duplicated_vec = quick_sort(duplicated_vec);

    // Prepare the expected repeated sorted sequence
    vector<int> expected_sorted_duplicated(sorted_vec);
    expected_sorted_duplicated.insert(expected_sorted_duplicated.end(), sorted_vec.begin(), sorted_vec.end());

    /* Verification */
    sort(expected_sorted_duplicated.begin(), expected_sorted_duplicated.end());
    EXPECT_EQ(sorted_duplicated_vec, expected_sorted_duplicated);
}

/**
 * @brief Metamorphic Relation 43: If all occurrences of a certain element are removed from the input array, 
 * the output array should no longer contain that element and be sorted.
 *
 */
TEST_P(QuickSortParamTest, MR43) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Choose a value to be removed (for instance, the first one if it exists)
    if (source_vec.empty()) return;
    int value_to_remove = source_vec[0];

    // Remove all occurrences of the chosen value
    source_vec.erase(
        std::remove(source_vec.begin(), source_vec.end(), value_to_remove),
        source_vec.end()
    );

    // Sort the modified array
    vector<int> sorted_modified_vec = quick_sort(source_vec);

    /* Verification */
    EXPECT_TRUE(std::find(sorted_modified_vec.begin(), sorted_modified_vec.end(), value_to_remove) == sorted_modified_vec.end());
}

INSTANTIATE_TEST_CASE_P(TrueReturn, QuickSortParamTest, testing::ValuesIn(gen_tcs_randomly()));
