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
 * @brief Metamorphic Relation 4: Reversing the input array should produce a reversed output array.
 *
 */
TEST_P(QuickSortParamTest, MR4) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec(source_vec.rbegin(), source_vec.rend());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    std::reverse(source_out.begin(), source_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 5: Duplicating the input array elements should not affect the sorted order of the output array.
 *
 */
TEST_P(QuickSortParamTest, MR5) {   // Fixed
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input by duplicating each element */
    vector<int> follow_vec;
    for (int elem : source_vec) {
        follow_vec.push_back(elem);
        follow_vec.push_back(elem);
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Filter duplicates and compare to source output */
    for (int i = 0, j = 0; i < source_out.size(), j < follow_out.size(); i++, j += 2) {
        EXPECT_EQ(source_out[i], follow_out[j]);
    }
}

/**
 * @brief Metamorphic Relation 6: Removing any element from the input array should not affect the sorted order of the remaining elements in the output array.
 *
 */
TEST_P(QuickSortParamTest, MR6) {   // Fixed
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    if (!source_vec.empty()) {
        /* Construct follow-up input */
        vector<int> follow_vec = source_vec;
        int mn_index = min_element(follow_vec.begin(), follow_vec.end()) - follow_vec.begin();
        follow_vec.erase(follow_vec.begin() + mn_index); // Remove the minimum element

        /* Get follow-up output */
        vector<int> follow_out = quick_sort(follow_vec);

        /* Verification */
        source_out.erase(source_out.begin()); // Remove the first element (sorted)
        EXPECT_EQ(follow_out, source_out);
    }
}

/**
 * @brief Metamorphic Relation 7: Inverting the order of elements should produce the correct inverse sorted array.
 *
 */
TEST_P(QuickSortParamTest, MR7) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec(source_vec.rbegin(), source_vec.rend());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    std::sort(follow_vec.begin(), follow_vec.end(), std::greater<int>());
    EXPECT_EQ(follow_out, follow_vec); // Verify the follow_out array is sorted in descending order
}
/**
 * @brief Metamorphic Relation 8: Concatenating a sorted array to the original array, sorting the result, should lead to the original sorted array followed by the added sorted array
 *
 */
TEST_P(QuickSortParamTest, MR8) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get a copy of the original vector and sort it */
    vector<int> sorted_vec = source_vec;
    std::sort(sorted_vec.begin(), sorted_vec.end());

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec(source_vec);
    follow_vec.insert(follow_vec.end(), sorted_vec.begin(), sorted_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Construct expected output */
    vector<int> expected_out = source_out; // contains the sorted original elements
    expected_out.insert(expected_out.end(), sorted_vec.begin(), sorted_vec.end()); // concatenate with the second already sorted array

    /* Verification */
    EXPECT_EQ(follow_out, expected_out);
}

/**
 * @brief Metamorphic Relation 9: Sorting an already sorted array should result in the same array.
 *
 */
TEST_P(QuickSortParamTest, MR9) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* The source output is already sorted, so we use it as the follow-up input */
    vector<int> follow_vec = source_out;

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 10: If we split the input array into two, sort each part separately and then concatenate them, the complete sorted array should be obtainable after sorting the concatenated array.
 *
 */
TEST_P(QuickSortParamTest, MR10) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Split the array into two */
    int middle = source_vec.size() / 2;
    vector<int> first_half(source_vec.begin(), source_vec.begin() + middle);
    vector<int> second_half(source_vec.begin() + middle, source_vec.end());

    /* Sort both halves */
    vector<int> sorted_first = quick_sort(first_half);
    vector<int> sorted_second = quick_sort(second_half);

    /* Concatenate the sorted halves */
    vector<int> concatenated;
    concatenated.insert(concatenated.end(), sorted_first.begin(), sorted_first.end());
    concatenated.insert(concatenated.end(), sorted_second.begin(), sorted_second.end());

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Sort the concatenated vector */
    vector<int> follow_out = quick_sort(concatenated);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 11: Sorting an array with all elements being the same should result in an array with the same elements.
 *
 */
TEST_P(QuickSortParamTest, MR11) {
    const int SIZE = 10;
    const int VALUE = 5;

    /* Create a source array with all the same values */
    vector<int> source_vec(SIZE, VALUE);

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(source_vec);

    /* Verification */
    for (int i = 0; i < SIZE; ++i) {
        EXPECT_EQ(follow_out[i], VALUE);
    }
}
/**
 * @brief Metamorphic Relation 12: For an array consisting of repeating patterns, sorting it should result in identical sorted sub-sequences.
 *
 */
TEST_P(QuickSortParamTest, MR12) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Create a repeating pattern input by duplicating the source array multiple times */
    vector<int> follow_vec;
    int repetitions = 3; // Number of times the pattern repeats
    for (int i = 0; i < repetitions; ++i) {
        follow_vec.insert(follow_vec.end(), source_vec.begin(), source_vec.end());
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Get source output, which serves as the pattern */
    vector<int> source_out = quick_sort(source_vec);

    /* Verification - every sub-sequence of the pattern's length in the follow-up output should be equal to the source output */
    for (int i = 0; i < repetitions; ++i) {
        std::vector<int>::const_iterator start = follow_out.begin() + i * source_out.size();
        std::vector<int>::const_iterator end = start + source_out.size();
        std::vector<int> sub_sequence(start, end);
        EXPECT_EQ(sub_sequence, source_out);
    }
}

/**
 * @brief Metamorphic Relation 13: Sorting an array with a single element appended or prepended should result in the same sorted array with the element placed in the correct order.
 *
 */
TEST_P(QuickSortParamTest, MR13) {
    const int APPENDED_VALUE = 100;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input by prepending a value */
    vector<int> prepended_vec = {APPENDED_VALUE};
    prepended_vec.insert(prepended_vec.end(), source_vec.begin(), source_vec.end());

    /* Get follow-up output for the prepended input */
    vector<int> prepended_out = quick_sort(prepended_vec);

    /* Construct follow-up input by appending a value */
    vector<int> appended_vec(source_vec);
    appended_vec.push_back(APPENDED_VALUE);

    /* Get follow-up output for the appended input */
    vector<int> appended_out = quick_sort(appended_vec);

    /* Verification for prepended input */
    auto prepended_position = std::find(prepended_out.begin(), prepended_out.end(), APPENDED_VALUE);
    EXPECT_TRUE(prepended_position != prepended_out.end());
    EXPECT_TRUE(std::is_sorted(prepended_out.begin(), prepended_out.end()));

    /* Verification for appended input */
    auto appended_position = std::find(appended_out.begin(), appended_out.end(), APPENDED_VALUE);
    EXPECT_TRUE(appended_position != appended_out.end());
    EXPECT_TRUE(std::is_sorted(appended_out.begin(), appended_out.end()));
}

/**
 * @brief Metamorphic Relation 14: Sorting an array and then inserting an element should result in the same ordered array with the new element placed correctly.
 *
 */
TEST_P(QuickSortParamTest, MR14) {
    const int INSERTED_VALUE = 50;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Insert an element into the sorted output */
    auto sorted_position = std::lower_bound(source_out.begin(), source_out.end(), INSERTED_VALUE);
    source_out.insert(sorted_position, INSERTED_VALUE);

    /* Verification */
    EXPECT_TRUE(std::is_sorted(source_out.begin(), source_out.end()));
}

/**
 * @brief Metamorphic Relation 15: Sorting an array with distinct elements and one that has duplicates, should result in a sorted array with duplicates grouped together.
 *
 */
TEST_P(QuickSortParamTest, MR15) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Duplicate a random element in the array */
    if (!source_vec.empty()) {
        std::default_random_engine rng(std::random_device{}());
        std::uniform_int_distribution<size_t> dist(0, source_vec.size() - 1);
        size_t random_index = dist(rng);
        int duplicated_value = source_vec[random_index];
        source_vec.push_back(duplicated_value); // inserting a duplicate

        /* Get follow-up output */
        vector<int> follow_out = quick_sort(source_vec);

        /* Verification */
        EXPECT_TRUE(std::is_sorted(follow_out.begin(), follow_out.end()));
        
        auto it = std::adjacent_find(follow_out.begin(), follow_out.end());
        // Ensure a duplicate exists and is grouped together
        EXPECT_TRUE(it != follow_out.end() && *it == duplicated_value && *std::next(it) == duplicated_value);
    }
}
/**
 * @brief Metamorphic Relation 16: Sorting the input array should result in the output where the difference between consecutive elements is non-negative (ascending order).
 */
TEST_P(QuickSortParamTest, MR16) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    /* Get sorted output */
    vector<int> sorted_vec = quick_sort(vec);

    /* Verification: No pair of consecutive elements should be in descending order */
    for (size_t i = 0; i < sorted_vec.size() - 1; ++i) {
        EXPECT_LE(sorted_vec[i], sorted_vec[i + 1]);
    }
}

/**
 * @brief Metamorphic Relation 17: Rotating the elements of the sorted output array any number of times should not change the relative sorted order of the elements.
 */
TEST_P(QuickSortParamTest, MR17) {
    const int ROTATION_STEPS = 3;  // The number of rotation steps to the right

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    /* Get sorted output */
    vector<int> sorted_vec = quick_sort(vec);

    /* Rotate the sorted output */
    std::rotate(sorted_vec.begin(), sorted_vec.begin() + ROTATION_STEPS % sorted_vec.size(), sorted_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(sorted_vec);

    /* Verification */
    EXPECT_EQ(follow_out, sorted_vec);
}

/**
 * @brief Metamorphic Relation 18: Flipping the sorted array about a pivot should result in two separately sorted subarrays, on either side of the pivot.
 */
TEST_P(QuickSortParamTest, MR18) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    /* Get sorted output */
    vector<int> sorted_vec = quick_sort(vec);

    /* Flip around the middle pivot */
    size_t pivot = sorted_vec.size() / 2;
    std::reverse(sorted_vec.begin(), sorted_vec.begin() + pivot);
    std::reverse(sorted_vec.begin() + pivot, sorted_vec.end());

    /* Verification */
    EXPECT_TRUE(std::is_sorted(sorted_vec.begin(), sorted_vec.begin() + pivot));
    EXPECT_TRUE(std::is_sorted(sorted_vec.begin() + pivot, sorted_vec.end()));
}

/**
 * @brief Metamorphic Relation 19: Replacing all elements with the minimum or maximum element and sorting should result in the array remaining unchanged.
 */
TEST_P(QuickSortParamTest, MR19) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    if (!vec.empty()) {
        /* Find the min and max elements */
        int min_elem = *std::min_element(vec.begin(), vec.end());
        int max_elem = *std::max_element(vec.begin(), vec.end());
        
        /* Replace all elements with min_elem and sort */
        vector<int> min_vec(vec.size(), min_elem);
        vector<int> sorted_min_vec = quick_sort(min_vec);
        
        /* Replace all elements with max_elem and sort */
        vector<int> max_vec(vec.size(), max_elem);
        vector<int> sorted_max_vec = quick_sort(max_vec);

        /* Verification */
        EXPECT_EQ(min_vec, sorted_min_vec);
        EXPECT_EQ(max_vec, sorted_max_vec);
    }
}

/**
 * @brief Metamorphic Relation 20: Sorting two arrays separately and then sorting the concatenated result should give the same sorted array as sorting the concatenated two sources and then sorting the result.
 */
TEST_P(QuickSortParamTest, MR20) {
    /* Get source inputs */
    QuickSortInput input1 = GetParam();
    QuickSortInput input2 = GetParam();
    vector<int> vec1 = input1.vec;
    vector<int> vec2 = input2.vec;

    /* Sort both arrays */
    vector<int> sorted_vec1 = quick_sort(vec1);
    vector<int> sorted_vec2 = quick_sort(vec2);

    /* Concatenate sorted arrays and then sort */
    vector<int> concatenated_sorted = sorted_vec1;
    concatenated_sorted.insert(concatenated_sorted.end(), sorted_vec2.begin(), sorted_vec2.end());
    vector<int> final_sorted_vec = quick_sort(concatenated_sorted);
    
    /* Concatenate source arrays and then sort */
    vector<int> concatenated_source = vec1;
    concatenated_source.insert(concatenated_source.end(), vec2.begin(), vec2.end());
    vector<int> source_sorted_vec = quick_sort(concatenated_source);

    /* Verification */
    EXPECT_EQ(final_sorted_vec, source_sorted_vec);
}
/**
 * @brief Metamorphic Relation 21: Sorting an array, then removing one element should still result in a sorted array.
 */
TEST_P(QuickSortParamTest, MR21) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    /* Get sorted output */
    vector<int> sorted_vec = quick_sort(vec);

    if (!sorted_vec.empty()) {
        /* Remove an element from the sorted output */
        sorted_vec.erase(sorted_vec.begin() + sorted_vec.size() / 2); // Remove the middle element for simplicity

        /* Verification */
        EXPECT_TRUE(std::is_sorted(sorted_vec.begin(), sorted_vec.end()));
    }
}

/**
 * @brief Metamorphic Relation 22: Sorting an array, then replacing one element with a new element and sorting again should result in a correctly sorted array.
 */
TEST_P(QuickSortParamTest, MR22) {
    const int NEW_ELEMENT = 999;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    /* Get sorted output */
    vector<int> sorted_vec = quick_sort(vec);

    if (!sorted_vec.empty()) {
        /* Replace an element with a new element */
        sorted_vec[sorted_vec.size() / 2] = NEW_ELEMENT; // Insert new element at middle position

        /* Sort the array again */
        sorted_vec = quick_sort(sorted_vec);

        /* Verification */
        EXPECT_TRUE(std::is_sorted(sorted_vec.begin(), sorted_vec.end()));
    }
}

/**
 * @brief Metamorphic Relation 23: Sorting multiple arrays separately and concatenating the results should yield the same sorted order as concatenating the arrays first and then sorting.
 */
TEST_P(QuickSortParamTest, MR23) {
    /* Get multiple source inputs */
    QuickSortInput input1 = GetParam();
    QuickSortInput input2 = GetParam();
    QuickSortInput input3 = GetParam();
    vector<int> vec1 = input1.vec;
    vector<int> vec2 = input2.vec;
    vector<int> vec3 = input3.vec;

    /* Sort each array separately */
    vector<int> sorted_vec1 = quick_sort(vec1);
    vector<int> sorted_vec2 = quick_sort(vec2);
    vector<int> sorted_vec3 = quick_sort(vec3);

    /* Concatenate sorted outputs */
    sorted_vec1.insert(sorted_vec1.end(), sorted_vec2.begin(), sorted_vec2.end());
    sorted_vec1.insert(sorted_vec1.end(), sorted_vec3.begin(), sorted_vec3.end());

    /* Concatenate source arrays */
    vec1.insert(vec1.end(), vec2.begin(), vec2.end());
    vec1.insert(vec1.end(), vec3.begin(), vec3.end());

    /* Sort the concatenated source */
    vector<int> sorted_combined_vec = quick_sort(vec1);

    /* Verification */
    EXPECT_EQ(sorted_vec1, sorted_combined_vec);
}

/**
 * @brief Metamorphic Relation 24: Inverting the signs of all elements in the input array, then sorting and re-inverting should yield the original sorted array in reverse order.
 */
TEST_P(QuickSortParamTest, MR24) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    /* Invert all the signs */
    std::transform(vec.begin(), vec.end(), vec.begin(), std::negate<int>());

    /* Sort the inverted input */
    vector<int> sorted_inverted_vec = quick_sort(vec);

    /* Re-invert the signs */
    std::transform(sorted_inverted_vec.begin(), sorted_inverted_vec.end(), sorted_inverted_vec.begin(), std::negate<int>());

    /* Retrieve the expected sorted order of the original array */
    vector<int> expected_sorted_vec = quick_sort(input.vec);

    /* Expected sorted vector in reverse order */
    std::reverse(expected_sorted_vec.begin(), expected_sorted_vec.end());

    /* Verification */
    EXPECT_EQ(sorted_inverted_vec, expected_sorted_vec);
}

/**
 * @brief Metamorphic Relation 25: Sorting an array and then interchanging the first and the last element should not yield a sorted array.
 */
TEST_P(QuickSortParamTest, MR25) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    /* Get sorted output */
    vector<int> sorted_vec = quick_sort(vec);

    if (sorted_vec.size() > 1) {
        /* Swap the first and the last elements */
        std::swap(sorted_vec.front(), sorted_vec.back());

        /* Verification */
        EXPECT_FALSE(std::is_sorted(sorted_vec.begin(), sorted_vec.end()));
    }
}
/**
 * @brief Metamorphic Relation 26: Removing all instances of a specific element from the input array and then sorting should result in a sorted array without that element.
 */
TEST_P(QuickSortParamTest, MR26) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    /* Get sorted output */
    vector<int> sorted_vec = quick_sort(vec);

    if (!sorted_vec.empty()) {
        // Choose an element to remove, for testing we can choose an element in the middle of the sorted array
        int element_to_remove = sorted_vec[sorted_vec.size() / 2];

        // Remove all instances of the chosen element
        vector<int> reduced_vec;
        std::copy_if(sorted_vec.begin(), sorted_vec.end(), std::back_inserter(reduced_vec), 
                     [element_to_remove](int val) { return val != element_to_remove; });

        // Sort the reduced array
        vector<int> sorted_reduced_vec = quick_sort(reduced_vec);

        // Verification
        EXPECT_TRUE(std::is_sorted(sorted_reduced_vec.begin(), sorted_reduced_vec.end()));
        EXPECT_EQ(std::find(sorted_reduced_vec.begin(), sorted_reduced_vec.end(), element_to_remove), sorted_reduced_vec.end());
    }
}

/**
 * @brief Metamorphic Relation 27: Sorting an input array, inverting all elements, then sorting once more should result in the same array but inverted.
 */
TEST_P(QuickSortParamTest, MR27) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    /* Get sorted output */
    vector<int> sorted_vec = quick_sort(vec);

    // Invert the sorted array
    std::transform(sorted_vec.begin(), sorted_vec.end(), sorted_vec.begin(), [](int val) { return -val; });

    // Sort the inverted array
    vector<int> resorted_vec = quick_sort(sorted_vec);

    // Invert the expected array
    std::reverse(sorted_vec.begin(), sorted_vec.end());

    // Verification
    EXPECT_EQ(resorted_vec, sorted_vec);
}

/**
 * @brief Metamorphic Relation 28: Performing an arbitrary permutation of the input array elements should not affect the resulting sorted array.
 */
TEST_P(QuickSortParamTest, MR28) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    // Get sorted output
    vector<int> sorted_vec = quick_sort(vec);

    // Shuffle the original array
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(vec.begin(), vec.end(), g);

    // Sort again
    vector<int> shuffled_sorted_vec = quick_sort(vec);

    // Verification
    EXPECT_EQ(shuffled_sorted_vec, sorted_vec);
}

/**
 * @brief Metamorphic Relation 29: Changing any element of the input array (except the maximum) to the maximum value, sorting it should still result in the original maximum value being at the end of the sorted array.
 */
TEST_P(QuickSortParamTest, MR29) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    if (!vec.empty()) {
        // Get sorted output
        vector<int> sorted_vec = quick_sort(vec);

        // Find maximum value from the sorted array
        int max_value = sorted_vec.back();

        // Change one of the non-maximum elements to the maximum value
        for (auto& elem : vec) {
            if (elem != max_value) {
                elem = max_value;
                break;
            }
        }

        // Sort the modified array
        vector<int> modified_sorted_vec = quick_sort(vec);
    
        // Verification
        EXPECT_EQ(modified_sorted_vec.back(), max_value);
        EXPECT_TRUE(std::is_sorted(modified_sorted_vec.begin(), modified_sorted_vec.end()));
    }
}

/**
 * @brief Metamorphic Relation 30: Sorting an array that consists of two interleaved sorted arrays should result in a single sorted array.
 */
TEST_P(QuickSortParamTest, MR30) {
    /* Get two source inputs */
    QuickSortInput input = GetParam();
    vector<int> vec1 = input.vec;
    vector<int> vec2 = input.vec;

    // Sort both arrays
    sort(vec1.begin(), vec1.end());
    sort(vec2.begin(), vec2.end());

    // Interleave the two sorted arrays
    vector<int> interleaved_vec;
    size_t max_length = std::max(vec1.size(), vec2.size());
    for (size_t i = 0; i < max_length; ++i) {
        if (i < vec1.size()) interleaved_vec.push_back(vec1[i]);
        if (i < vec2.size()) interleaved_vec.push_back(vec2[i]);
    }

    // Sort the interleaved array
    vector<int> sorted_interleaved_vec = quick_sort(interleaved_vec);
    
    // Verification
    EXPECT_TRUE(std::is_sorted(sorted_interleaved_vec.begin(), sorted_interleaved_vec.end()));
}
/**
 * @brief Metamorphic Relation 31: Sorting an input array with a known number of inversions should result in a sorted array where all inversions are corrected.
 */
TEST_P(QuickSortParamTest, MR31) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    if (vec.size() > 1) {
        // Create a known number of inversions (2 inversions)
        std::swap(vec[0], vec[vec.size() - 1]);

        // Sort the array with inversions
        vector<int> sorted_vec_with_inversions = quick_sort(vec);

        // Sort the original array without inversions
        vector<int> correctly_sorted_vec = quick_sort(input.vec);
    
        // Verification
        EXPECT_EQ(sorted_vec_with_inversions, correctly_sorted_vec);
    }
}

/**
 * @brief Metamorphic Relation 32: Independently sorting the even and odd indexed elements of the array and then merging should result in a fully sorted array.
 */
TEST_P(QuickSortParamTest, MR32) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    vector<int> evens, odds;
    
    // Separate even and odd indexed elements
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i % 2 == 0) {
            evens.push_back(vec[i]);
        } else {
            odds.push_back(vec[i]);
        }
    }

    // Sort the even- and odd-indexed arrays
    vector<int> sorted_evens = quick_sort(evens);
    vector<int> sorted_odds = quick_sort(odds);

    // Merge the sorted subarrays
    vector<int> merged_vec;
    std::merge(sorted_evens.begin(), sorted_evens.end(), sorted_odds.begin(), sorted_odds.end(), std::back_inserter(merged_vec));
    
    // Sort the original array for comparison
    vector<int> sorted_vec = quick_sort(vec);

    // Verification
    EXPECT_EQ(merged_vec, sorted_vec);
}

/**
 * @brief Metamorphic Relation 33: Scaling all elements in the input array by a certain factor and sorting should result in a sorted output where elements are also scaled by the same factor.
 */
TEST_P(QuickSortParamTest, MR33) {
    const int SCALE_FACTOR = 10;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    vector<int> scaled_vec(vec.size());
    
    // Scale all elements by a factor
    std::transform(vec.begin(), vec.end(), scaled_vec.begin(), [SCALE_FACTOR](int val) { return val * SCALE_FACTOR; });

    // Quick sort the scaled vector
    vector<int> sorted_scaled_vec = quick_sort(scaled_vec);

    // Scale the sorted array for comparison
    vector<int> sorted_vec = quick_sort(vec);
    std::transform(sorted_vec.begin(), sorted_vec.end(), sorted_vec.begin(), [SCALE_FACTOR](int val) { return val * SCALE_FACTOR; });

    // Verification
    EXPECT_EQ(sorted_scaled_vec, sorted_vec);
}

/**
 * @brief Metamorphic Relation 34: Concatenating a reversed sorted array should result in the first half as sorted and the second half as reverse sorted.
 */
TEST_P(QuickSortParamTest, MR34) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    // Sort the vector
    vector<int> sorted_vec = quick_sort(vec);

    // Make a reversed copy of the sorted vector
    vector<int> reversed_sorted_vec(sorted_vec.rbegin(), sorted_vec.rend());

    // Concatenate it to the original sorted array
    vector<int> concatenated_vec(sorted_vec);
    concatenated_vec.insert(concatenated_vec.end(), reversed_sorted_vec.begin(), reversed_sorted_vec.end());

    // Sort the concatenated vector
    vector<int> final_sorted_vec = quick_sort(concatenated_vec);

    // Verification
    // First half should be the same as sorted_vec
    EXPECT_TRUE(std::equal(sorted_vec.begin(), sorted_vec.end(), final_sorted_vec.begin()));
    
    // The second half should be reversed_sorted_vec
    auto second_half_start = final_sorted_vec.begin() + sorted_vec.size();
    EXPECT_TRUE(std::equal(reversed_sorted_vec.begin(), reversed_sorted_vec.end(), second_half_start));
}


/**
 * @brief Metamorphic Relation 35: Doubling each element in the input array should not affect the overall sorting order, just the individual values.
 */
 TEST_P(QuickSortParamTest, MR35) {
    const int DOUBLING_FACTOR = 2;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    // Quick sort the original vector
    vector<int> sorted_vec = quick_sort(vec);

    // Double the elements in the original array
    vector<int> doubled_vec(vec.size());
    std::transform(vec.begin(), vec.end(), doubled_vec.begin(), [DOUBLING_FACTOR](int val) { return val * DOUBLING_FACTOR; });

    // Quick sort the doubled array
    vector<int> sorted_doubled_vec = quick_sort(doubled_vec);

    // Double the elements in the previously sorted array for comparison
    vector<int> double_sorted_vec(sorted_vec.size());
    std::transform(sorted_vec.begin(), sorted_vec.end(), double_sorted_vec.begin(), [DOUBLING_FACTOR](int val) { return val * DOUBLING_FACTOR; });

    // Verification
    EXPECT_EQ(sorted_doubled_vec, double_sorted_vec);
}
/**
 * @brief Metamorphic Relation 36: Concatenating two arrays and sorting should result in the final array's elements being a sorted combination of both arrays irrespective of their initial order.
 */
TEST_P(QuickSortParamTest, MR36) {
    /* Get source input */
    QuickSortInput input1 = GetParam();
    QuickSortInput input2 = GetParam();
    vector<int> vec1 = input1.vec;
    vector<int> vec2 = input2.vec;

    // Concatenate both vectors
    vector<int> concatenated_vec(vec1);
    concatenated_vec.insert(concatenated_vec.end(), vec2.begin(), vec2.end());

    // Sort the concatenated vector
    vector<int> sorted_concatenated_vec = quick_sort(concatenated_vec);

    // Combine and sort the vectors independently for comparison
    vec1.insert(vec1.end(), vec2.begin(), vec2.end());
    vector<int> independently_sorted_vec = quick_sort(vec1);

    // Verification
    EXPECT_EQ(sorted_concatenated_vec, independently_sorted_vec);
}

/**
 * @brief Metamorphic Relation 37: Sorting an array and then applying any bijective function to the elements should not change the relative order of the elements.
 */
TEST_P(QuickSortParamTest, MR37) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    // Quick sort the original vector
    vector<int> sorted_vec = quick_sort(vec);

    // Apply a bijective function, e.g., f(x) = 3x + 1
    std::transform(sorted_vec.begin(), sorted_vec.end(), sorted_vec.begin(),
                   [](int x) { return 3 * x + 1; });

    // Quick sort the transformed vector
    vector<int> transformed_sorted_vec = quick_sort(sorted_vec);

    // Verify the order has not changed by applying the inverse function
    std::transform(transformed_sorted_vec.begin(), transformed_sorted_vec.end(), transformed_sorted_vec.begin(),
                   [](int y) { return (y - 1) / 3; });

    // Expect the vector to retain the same order as sorted_vec
    EXPECT_EQ(transformed_sorted_vec, sorted_vec);
}

/**
 * @brief Metamorphic Relation 38: Sorting an array, then sorting a subset should result in the same order as the corresponding subset of the originally sorted array.
 */
TEST_P(QuickSortParamTest, MR38) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    // Quick sort the original vector
    vector<int> sorted_vec = quick_sort(vec);

    // Take a random subset of the array
    std::default_random_engine generator;
    std::shuffle(vec.begin(), vec.end(), generator);
    vector<int> subset(vec.begin(), vec.begin() + vec.size() / 2);

    // Sort the subset
    vector<int> sorted_subset = quick_sort(subset);

    // Find the sorted subset in the fully sorted array
    vector<int> sorted_full_subset;
    std::copy_if(sorted_vec.begin(), sorted_vec.end(), std::back_inserter(sorted_full_subset),
                 [&subset](const int& element) {
                     return std::find(subset.begin(), subset.end(), element) != subset.end();
                 });

    // Verification
    EXPECT_EQ(sorted_subset, sorted_full_subset);
}
/**
 * @brief Metamorphic Relation 39: Sorting an array and then applying a monotonic increasing function to all the elements should keep the array sorted.
 */
TEST_P(QuickSortParamTest, MR39) {
    // Monotonic increasing function: f(x) = x^3
    auto monotonic_fn = [](int x) { return x * x * x; };

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    // Sort the original vector
    vector<int> sorted_vec = quick_sort(vec);

    // Apply the monotonic increasing function
    std::transform(sorted_vec.begin(), sorted_vec.end(), sorted_vec.begin(), monotonic_fn);

    // Verify that the transformed array is still sorted
    EXPECT_TRUE(std::is_sorted(sorted_vec.begin(), sorted_vec.end()));
}

#if 0
/**
 * @brief Metamorphic Relation 40: Sorting the same elements with different data types (e.g., integer vs. floating point) should result in the same sorting order.
 */
TEST_P(QuickSortParamTest, MR40) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> int_vec = input.vec;
    // Convert integer vector to floating point
    vector<float> float_vec(int_vec.begin(), int_vec.end());

    // Sort the integer array
    vector<int> sorted_int_vec = quick_sort(int_vec);
    // Sort the floating point array
    vector<float> sorted_float_vec = quick_sort(float_vec);

    // Verify the elements are in the same order
    EXPECT_EQ(sorted_int_vec.size(), sorted_float_vec.size());
    for (size_t i = 0; i < sorted_int_vec.size(); i++) {
        EXPECT_FLOAT_EQ(static_cast<float>(sorted_int_vec[i]), sorted_float_vec[i]);
    }
}
#endif

/**
 * @brief Metamorphic Relation 41: Sorting an array and concatenating it with its inverted copy should result in a palindromic sorted array after sorting again.
 */
TEST_P(QuickSortParamTest, MR41) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    // Sort the original vector
    vector<int> sorted_vec = quick_sort(vec);

    // Create an inverted copy of the sorted array
    vector<int> inverted_vec(sorted_vec.rbegin(), sorted_vec.rend());

    // Concatenate the sorted array with its inverted copy
    sorted_vec.insert(sorted_vec.end(), inverted_vec.begin(), inverted_vec.end());

    // Sort the concatenated array
    vector<int> doubly_sorted_vec = quick_sort(sorted_vec);

    // Verify that the sorted array is palindromic
    EXPECT_TRUE(std::equal(doubly_sorted_vec.begin(), doubly_sorted_vec.begin() + doubly_sorted_vec.size() / 2,
                           doubly_sorted_vec.rbegin()));
}

/**
 * @brief Metamorphic Relation 42: Sorting an array should result in the first element being less than or equal to the last element if the array size is greater than one.
 */
TEST_P(QuickSortParamTest, MR42) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    /* Sort the vector */
    vector<int> sorted_vec = quick_sort(vec);

    /* Verify that the first element is less than or equal to the last one */
    if (sorted_vec.size() > 1) {
        EXPECT_LE(sorted_vec.front(), sorted_vec.back());
    }
}
/**
 * @brief Metamorphic Relation 43: Inverting the sign of each element in a sorted array should yield a sorted array in descending order.
 */
TEST_P(QuickSortParamTest, MR43) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> vec = input.vec;

    // Sort the original vector
    vector<int> sorted_vec = quick_sort(vec);

    // Invert the sign of each element
    std::transform(sorted_vec.begin(), sorted_vec.end(), sorted_vec.begin(), std::negate<int>());

    // Verify that the array is sorted in descending order
    EXPECT_TRUE(std::is_sorted(sorted_vec.begin(), sorted_vec.end(), std::greater<int>()));
}

INSTANTIATE_TEST_CASE_P(TrueReturn, QuickSortParamTest, testing::ValuesIn(gen_tcs_randomly()));
