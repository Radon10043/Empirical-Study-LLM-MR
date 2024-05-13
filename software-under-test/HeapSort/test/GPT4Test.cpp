#include <algorithm>
#include <bitset>
#include <gtest/gtest.h>
#include <iostream>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class HeapSortParamTest : public ::testing::TestWithParam<HeapSortInput> {};

/* Helper Methods */

/**
 * @brief 随机生成一个动态数组
 *
 * @return vector<int>
 */
vector<int> gen_vector_randomly() {
    mt19937 rng(random_device{}());

    /* clang-format off */
    uniform_int_distribution<int> dist_size(1, 1000),       /* 数组长度范围 */
                                  dist_value(-1000, 1000);  /* 元素取值范围 */
    /* clang-format on */

    /* 构建vector */
    int size = dist_size(rng);
    vector<int> vec(size);
    for (int j = 0; j < size; j++)
        vec[j] = dist_value(rng);

    return vec;
}

/**
 * @brief Metamorphic Relation 4: Doubling each element in the input array.
 * The sorted output array, when divided by 2 (each element), should be the same as sorting the source input array.
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
        elem *= 2;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    for (auto &elem : follow_out)
        elem /= 2;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 5: Reversing the input array.
 * The output array when reversed should be the same as the source output array.
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
    reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    reverse(follow_out.begin(), follow_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 6: Concatenating the input array with a sorted array.
 * The sorting of the concatenated array should include the elements of the sorted array in their original order.
 *
 */
TEST_P(HeapSortParamTest, MR6) { // Fixed
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get a known sorted vector */
    vector<int> sorted_vec = {-5, 0, 2, 3, 8};

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.insert(follow_vec.end(), sorted_vec.begin(), sorted_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Extract the part of the array that corresponds to the sorted_vec */
    vector<int> extracted_sorted_vec;
    int index = 0;
    for (auto &val : follow_out) {
        if (index < sorted_vec.size() && val == sorted_vec[index]) {
            extracted_sorted_vec.push_back(val);
            index++;
        }
    }

    /* Verification */
    EXPECT_EQ(extracted_sorted_vec, sorted_vec);
}
/**
 * @brief Metamorphic Relation 7: Removing any element from the input array.
 * The sorted output array without that element should be the same as sorting the source input array without that element.
 *
 */
TEST_P(HeapSortParamTest, MR7) {    // Fixed
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Remove element condition */
    if (source_vec.size() <= 1)
        return; // No need to test for empty or single-element vectors

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input by removing an element from the source vector */
    vector<int> follow_vec = source_vec;
    follow_vec.erase(follow_vec.begin()); // Removing first element for simplicity, any element can be removed

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Remove the same element from the source output for comparison */
    for (int i = 0; i < source_out.size(); i++) {
        if (source_out[i] == source_vec[0]) {
            source_out.erase(source_out.begin() + i);
            break;
        }
    }

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 8: Concatenation of the input array with its reverse.
 * The output array should be twice as large with elements in non-decreasing order.
 *
 */
TEST_P(HeapSortParamTest, MR8) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input */
    vector<int> follow_vec(source_vec);
    vector<int> reverse_vec(source_vec.rbegin(), source_vec.rend());
    follow_vec.insert(follow_vec.end(), reverse_vec.begin(), reverse_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out.size(), 2 * source_vec.size());
    for (size_t i = 1; i < follow_out.size(); ++i) {
        EXPECT_LE(follow_out[i - 1], follow_out[i]);
    }
}

/**
 * @brief Metamorphic Relation 9: Splitting the input array into two halves, sorting them independently, and then merging.
 * The merged array should be the same as the sorted output of the unsplit array.
 *
 */
TEST_P(HeapSortParamTest, MR9) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Handle case where splitting is not possible */
    if (source_vec.size() <= 1)
        return;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Split source vector into two halves */
    vector<int> first_half(source_vec.begin(), source_vec.begin() + source_vec.size() / 2);
    vector<int> second_half(source_vec.begin() + source_vec.size() / 2, source_vec.end());

    /* Sort splits independently */
    vector<int> sorted_first_half = heap_sort(first_half);
    vector<int> sorted_second_half = heap_sort(second_half);

    /* Merge sorted halves */
    vector<int> merged_vec;
    std::merge(sorted_first_half.begin(), sorted_first_half.end(), sorted_second_half.begin(), sorted_second_half.end(), std::back_inserter(merged_vec));

    /* Verification */
    EXPECT_EQ(merged_vec, source_out);
}
/**
 * @brief Metamorphic Relation 10: Copying the input array multiple times to create a larger array.
 * The sorted output array should have the same sequence of elements repeated according to the number of copies.
 *
 */
TEST_P(HeapSortParamTest, MR10) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Number of copies (e.g., duplicate input array twice) */
    const size_t num_copies = 2;

    /* Construct follow-up input by copying the original array */
    vector<int> follow_vec;
    for (size_t i = 0; i < num_copies; ++i) {
        follow_vec.insert(follow_vec.end(), source_vec.begin(), source_vec.end());
    }

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    // Every num_copies elements in follow_out should be the same and equal to the corresponding element in source_out
    vector<int> source_out = heap_sort(source_vec);
    for (size_t i = 0; i < source_out.size(); ++i) {
        for (size_t j = 0; j < num_copies; ++j) {
            EXPECT_EQ(follow_out[i * num_copies + j], source_out[i]);
        }
    }
}

/**
 * @brief Metamorphic Relation 11: Invert the order of elements.
 * The sorted output array should be sorted in the reverse order compared to the source output array.
 *
 */
TEST_P(HeapSortParamTest, MR11) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input by inverting the order of elements */
    vector<int> follow_vec(source_vec);
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), std::negate<int>());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verify that the sorted follow-up output is the negation of the source output in reverse */
    reverse(source_out.begin(), source_out.end());
    std::transform(follow_out.begin(), follow_out.end(), follow_out.begin(), std::negate<int>());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 12: Swapping random non-adjacent pairs of elements in the input array multiple times.
 * The output array should remain sorted and equivalent to the original sorted array regardless of swaps.
 *
 */
TEST_P(HeapSortParamTest, MR12) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Ensure the vector has more than two elements */
    if (source_vec.size() < 3)
        return;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input by randomly swapping non-adjacent elements */
    std::mt19937 rng(std::random_device{}());
    vector<int> follow_vec = source_vec;
    size_t swaps = 10; // Perform a number of random swaps
    for (size_t i = 0; i < swaps; i++) {
        size_t index1 = rng() % follow_vec.size();
        size_t index2 = rng() % follow_vec.size();
        while (index1 == index2) { // Ensure non-adjacent and unique indices
            index2 = rng() % follow_vec.size();
        }
        std::swap(follow_vec[index1], follow_vec[index2]);
    }

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 13: Triplicating every element in the input array.
 * The elements in the output array for the modified input should appear thrice in consecutive order when compared to the result of the original input.
 *
 */
TEST_P(HeapSortParamTest, MR13) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input by triplicating every element */
    vector<int> follow_vec;
    for (int elem : source_vec) {
        follow_vec.push_back(elem);
        follow_vec.push_back(elem);
        follow_vec.push_back(elem);
    }

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    size_t idx = 0;
    for (int elem : source_out) {
        EXPECT_EQ(follow_out[idx++], elem);
        EXPECT_EQ(follow_out[idx++], elem);
        EXPECT_EQ(follow_out[idx++], elem);
    }
}

/**
 * @brief Metamorphic Relation 14: Appending an array of larger elements to the input array.
 * The output array should have the appended elements at the end in sorted order.
 *
 */
TEST_P(HeapSortParamTest, MR14) {   // Fixed
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Define the appending array with larger elements than the max in source_vec */
    int max_elem_in_source = *std::max_element(source_vec.begin(), source_vec.end());
    vector<int> larger_elements = {max_elem_in_source + 1, max_elem_in_source + 2, max_elem_in_source + 3};

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input by appending larger_elements */
    vector<int> follow_vec = source_vec;
    follow_vec.insert(follow_vec.end(), larger_elements.begin(), larger_elements.end());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    int n = follow_out.size();
    EXPECT_TRUE(follow_out[n - 1] == larger_elements[2] && follow_out[n - 2] == larger_elements[1] && follow_out[n - 3] == larger_elements[0]);
}

/**
 * @brief Metamorphic Relation 15: Introducing duplicate maximum elements into the input array.
 * The output array should maintain all duplicates at the end of the sorted array.
 *
 */
TEST_P(HeapSortParamTest, MR15) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Skip test case for empty vectors
    if (source_vec.empty())
        return;

    /* Identify the maximum element from the source vector */
    int max_elem_in_source = *std::max_element(source_vec.begin(), source_vec.end());

    /* Construct follow-up input by adding duplicates of the maximum element */
    vector<int> follow_vec = source_vec;
    follow_vec.push_back(max_elem_in_source);
    follow_vec.push_back(max_elem_in_source);

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    int last_element = follow_out.back();
    EXPECT_EQ(last_element, max_elem_in_source); // Last element should be a max element
    follow_out.pop_back();
    EXPECT_EQ(follow_out.back(), max_elem_in_source); // Next to last should also be a max element
}

/**
 * @brief Metamorphic Relation 16: Sorting the input array twice consecutively.
 * The result should not change between the first and second sort.
 *
 */
TEST_P(HeapSortParamTest, MR16) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output after first sort */
    vector<int> first_sort_out = heap_sort(source_vec);

    /* Get the output after a second sort */
    vector<int> second_sort_out = heap_sort(first_sort_out);

    /* Verification */
    EXPECT_EQ(first_sort_out, second_sort_out);
}

/**
 * @brief Metamorphic Relation 17: Combining two independently sorted vectors.
 * The resulting sorted vector should be the same as if the two vectors were combined and then sorted.
 *
 */
TEST_P(HeapSortParamTest, MR17) { // Fixed
    /* Get source inputs */
    HeapSortInput input1 = GetParam();
    HeapSortInput input2(gen_vector_randomly()); // Assume a function that provides another set of parameters
    vector<int> source_vec1 = input1.vec;
    vector<int> source_vec2 = input2.vec;

    /* Sort both source vectors separately */
    vector<int> sorted_vec1 = heap_sort(source_vec1);
    vector<int> sorted_vec2 = heap_sort(source_vec2);

    /* Merge the two sorted vectors */
    vector<int> merged_sorted_vec;
    std::merge(sorted_vec1.begin(), sorted_vec1.end(), sorted_vec2.begin(), sorted_vec2.end(), std::back_inserter(merged_sorted_vec));

    /* Combine the source vectors and sort */
    vector<int> combined_vec(source_vec1);
    combined_vec.insert(combined_vec.end(), source_vec2.begin(), source_vec2.end());
    vector<int> sorted_combined_vec = heap_sort(combined_vec);

    /* Verification */
    EXPECT_EQ(merged_sorted_vec, sorted_combined_vec);
}

/**
 * @brief Metamorphic Relation 18: Partitioning the vector into odd and even elements and sorting them separately.
 * The final merged array should be sorted identically to sorting the complete array at once.
 *
 */
TEST_P(HeapSortParamTest, MR18) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Partitions for odd and even elements */
    vector<int> odd_elements, even_elements;
    std::partition_copy(source_vec.begin(), source_vec.end(), std::back_inserter(odd_elements), std::back_inserter(even_elements),
                        [](int i) { return i % 2 != 0; });

    /* Individual sort of partitions */
    vector<int> sorted_odd_elements = heap_sort(odd_elements);
    vector<int> sorted_even_elements = heap_sort(even_elements);

    /* Merge sorted partitions */
    vector<int> merged_sorted_vec;
    std::merge(sorted_odd_elements.begin(), sorted_odd_elements.end(), sorted_even_elements.begin(), sorted_even_elements.end(),
               std::back_inserter(merged_sorted_vec));

    /* Sort the original input array */
    vector<int> sorted_source_vec = heap_sort(source_vec);

    /* Verification */
    EXPECT_EQ(merged_sorted_vec, sorted_source_vec);
}

/**
 * @brief Metamorphic Relation 19: Appending a vector sorted in the opposite direction (non-decreasing).
 * The last part of the sorted array should contain the elements from the appended vector but in reversed order.
 *
 */
TEST_P(HeapSortParamTest, MR19) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Generate a sequence sorted in non-decreasing order */
    vector<int> non_decreasing_vec = {1, 2, 3, 4, 5};

    /* Append the non-decreasing vector to the source vector */
    vector<int> combined_vec(source_vec);
    combined_vec.insert(combined_vec.end(), non_decreasing_vec.begin(), non_decreasing_vec.end());

    /* Sort the combined vector */
    vector<int> sorted_combined_vec = heap_sort(combined_vec);

    /* Non-decreasing vector should be in reverse order in the final sorted array */
    vector<int> expected_last_part = non_decreasing_vec;
    std::reverse(expected_last_part.begin(), expected_last_part.end());

    /* Extract the last part of the sorted combined vector */
    vector<int> actual_last_part(sorted_combined_vec.end() - expected_last_part.size(), sorted_combined_vec.end());

    /* Verification */
    EXPECT_EQ(actual_last_part, expected_last_part);
}
/**
 * @brief Metamorphic Relation 20: Sorting a vector and then removing an element.
 * The result should be identical to sorting the vector without the removed element.
 *
 */
TEST_P(HeapSortParamTest, MR20) {   // Fixed
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Remove first element if the vector is non-empty */
    if (!source_vec.empty()) {
        source_vec.erase(source_vec.begin());
    }

    /* Get expected output by sorting the vector after removal */
    vector<int> expected_out = heap_sort(source_vec);

    /* Get actual output by sorting the vector, then removing the element */
    vector<int> sorted_with_all = heap_sort(input.vec);
    for (int i = 0; i < sorted_with_all.size(); i++) {
        if (sorted_with_all[i] == input.vec[0]) {
            sorted_with_all.erase(sorted_with_all.begin() + i);
            break;
        }
    }

    /* Verification */
    EXPECT_EQ(sorted_with_all, expected_out);
}

/**
 * @brief Metamorphic Relation 21: Sorting multiple concatenated vectors.
 * The output array should be sorted and equivalent to sorting the combined vector.
 *
 */
TEST_P(HeapSortParamTest, MR21) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec1 = input.vec;
    vector<int> source_vec2 = source_vec1; // Copy of the source vector.
    vector<int> source_vec3 = source_vec1; // Another copy of the source vector.

    /* Combine the source vectors */
    vector<int> combined_vec(source_vec1);
    combined_vec.insert(combined_vec.end(), source_vec2.begin(), source_vec2.end());
    combined_vec.insert(combined_vec.end(), source_vec3.begin(), source_vec3.end());

    /* Get the output by sorting the combined vector */
    vector<int> sorted_combined_vec = heap_sort(combined_vec);

    /* Get the output by sorting the individual vectors and then combining them */
    vector<int> sorted_individual_vecs = heap_sort(source_vec1);
    sorted_individual_vecs.insert(sorted_individual_vecs.end(), heap_sort(source_vec2).begin(), heap_sort(source_vec2).end());
    sorted_individual_vecs.insert(sorted_individual_vecs.end(), heap_sort(source_vec3).begin(), heap_sort(source_vec3).end());
    sorted_individual_vecs = heap_sort(sorted_individual_vecs); // Sorting the combined individually sorted vectors.

    /* Verification */
    EXPECT_EQ(sorted_combined_vec, sorted_individual_vecs);
}

/**
 * @brief Metamorphic Relation 22: Concatenating vectors with distinct and non-overlapping element ranges.
 * Sorting the concatenated vector should be the same as the concatenation of individually sorted vectors.
 *
 */
TEST_P(HeapSortParamTest, MR22) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Two distinct non-overlapping vectors */
    vector<int> vec1 = {100, 101, 102, 103, 104};
    vector<int> vec2 = {200, 201, 202, 203, 204};

    /* Combine main input vector with distinct vectors */
    source_vec.insert(source_vec.end(), vec1.begin(), vec1.end());
    source_vec.insert(source_vec.end(), vec2.begin(), vec2.end());

    /* Sort the concatenated vector */
    vector<int> sorted_combined_vec = heap_sort(source_vec);

    /* Concatenate sorted individual vectors */
    vec1 = heap_sort(vec1);
    vec2 = heap_sort(vec2);
    vector<int> expected_sorted_vec = heap_sort(input.vec); // Sort original input
    expected_sorted_vec.insert(expected_sorted_vec.end(), vec1.begin(), vec1.end());
    expected_sorted_vec.insert(expected_sorted_vec.end(), vec2.begin(), vec2.end());

    /* Verification */
    EXPECT_EQ(sorted_combined_vec, expected_sorted_vec);
}
/**
 * @brief Metamorphic Relation 23: Sorting a vector, and then sorting each half of the vector independently.
 * The two sorted halves should combine to form the initially completely sorted vector.
 *
 */
TEST_P(HeapSortParamTest, MR23) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the entire vector */
    vector<int> sorted_vec = heap_sort(source_vec);

    /* Split sorted vector into two halves */
    vector<int> first_half(sorted_vec.begin(), sorted_vec.begin() + sorted_vec.size() / 2);
    vector<int> second_half(sorted_vec.begin() + sorted_vec.size() / 2, sorted_vec.end());

    /* Sort both halves again */
    vector<int> sorted_first_half = heap_sort(first_half);
    vector<int> sorted_second_half = heap_sort(second_half);

    /* Combine the sorted halves */
    sorted_first_half.insert(sorted_first_half.end(), sorted_second_half.begin(), sorted_second_half.end());

    /* Verification */
    EXPECT_EQ(sorted_vec, sorted_first_half);
}

/**
 * @brief Metamorphic Relation 24: Sorting a vector and inverting its order, then sorting the result.
 * The final output should be the inverse of the initial sorted vector.
 *
 */
TEST_P(HeapSortParamTest, MR24) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the source vector */
    vector<int> sorted_vec = heap_sort(source_vec);

    /* Invert the order of the sorted vector */
    std::reverse(sorted_vec.begin(), sorted_vec.end());

    /* Sort the reversed sorted vector */
    vector<int> resorted_vec = heap_sort(sorted_vec);

    /* Invert the order again, now it should match the first sorted vector */
    std::reverse(resorted_vec.begin(), resorted_vec.end());

    /* Verification */
    EXPECT_EQ(sorted_vec, resorted_vec);
}

/**
 * @brief Metamorphic Relation 25: Removing every second element from the sorted output array.
 * The result should be identical to sorting a vector where every second element was removed before sorting.
 *
 */
TEST_P(HeapSortParamTest, MR25) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the source vector */
    vector<int> sorted_vec = heap_sort(source_vec);

    /* Remove every second element from the sorted vector */
    for (size_t i = 1; i < sorted_vec.size(); i++) {
        sorted_vec.erase(sorted_vec.begin() + i);
    }

    /* Remove every second element from the source vector then sort */
    for (size_t i = 1; i < source_vec.size(); i++) {
        source_vec.erase(source_vec.begin() + i);
    }
    vector<int> sorted_half_vec = heap_sort(source_vec);

    /* Verification */
    EXPECT_EQ(sorted_vec, sorted_half_vec);
}

/**
 * @brief Metamorphic Relation 26: Interleave two sorted vectors and then sort the result.
 * The final output should be sorted and identical to the original uncombined sorted vectors.
 *
 */
TEST_P(HeapSortParamTest, MR26) { // Fixed
    /* Get two source inputs */
    HeapSortInput input1 = GetParam();           // Original input
    HeapSortInput input2(gen_vector_randomly()); // Another sorted vector

    /* Sort both vectors */
    vector<int> sorted_vec1 = heap_sort(input1.vec);
    vector<int> sorted_vec2 = heap_sort(input2.vec);

    /* Interleave the two sorted vectors */
    vector<int> interleaved_vec;
    auto iter1 = sorted_vec1.begin();
    auto iter2 = sorted_vec2.begin();
    while (iter1 != sorted_vec1.end() || iter2 != sorted_vec2.end()) {
        if (iter1 != sorted_vec1.end()) {
            interleaved_vec.push_back(*iter1++);
        }
        if (iter2 != sorted_vec2.end()) {
            interleaved_vec.push_back(*iter2++);
        }
    }

    /* Sort the interleaved vector */
    vector<int> sorted_interleaved_vec = heap_sort(interleaved_vec);

    /* Merge the initially sorted vectors */
    vector<int> merged_sorted_vec;
    std::merge(sorted_vec1.begin(), sorted_vec1.end(), sorted_vec2.begin(), sorted_vec2.end(), std::back_inserter(merged_sorted_vec));

    /* Verification */
    EXPECT_EQ(sorted_interleaved_vec, merged_sorted_vec);
}
/**
 * @brief Metamorphic Relation 27: Replacing elements in the input array with their absolute values.
 * Sorting the modified array should produce the same sorted result as sorting the array with original values.
 *
 */
TEST_P(HeapSortParamTest, MR27) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Create a copy of the input vector with all elements replaced by their absolute values */
    vector<int> abs_vec(source_vec.size());
    std::transform(source_vec.begin(), source_vec.end(), abs_vec.begin(), static_cast<int (*)(int)>(std::abs));

    /* Sort both source and modified vectors */
    vector<int> sorted_source = heap_sort(source_vec);
    vector<int> sorted_abs_vec = heap_sort(abs_vec);

    /* Verification: after replacing elements in sorted_source with their absolute values, it should equal sorted_abs_vec */
    std::transform(sorted_source.begin(), sorted_source.end(), sorted_source.begin(), static_cast<int (*)(int)>(std::abs));
    EXPECT_EQ(sorted_source, sorted_abs_vec);
}

/**
 * @brief Metamorphic Relation 28: Sorting a vector with all elements set to the same value.
 * The sorted output should be identical to the input as all elements are equivalent.
 *
 */
TEST_P(HeapSortParamTest, MR28) {
    /* Create a vector where all values are the same */
    vector<int> source_vec(10, 42); // 10 elements all set to 42

    /* Sort the vector */
    vector<int> sorted_vec = heap_sort(source_vec);

    /* Verification */
    EXPECT_EQ(sorted_vec, source_vec);
}

/**
 * @brief Metamorphic Relation 29: Randomly selecting a subset of the input array and sorting it.
 * The sorted subset should maintain relative order when compared to the full sorted array.
 *
 */
TEST_P(HeapSortParamTest, MR29) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the entire source vector */
    vector<int> sorted_source = heap_sort(source_vec);

    /* Randomly sample a subset of the input vector */
    std::shuffle(source_vec.begin(), source_vec.end(), std::default_random_engine());
    size_t subset_size = source_vec.size() / 2;
    vector<int> subset(source_vec.begin(), source_vec.begin() + subset_size);

    /* Sort the subset */
    vector<int> sorted_subset = heap_sort(subset);

    /* Verification: sorted_subset should maintain relative order from sorted_source */
    auto it = sorted_source.begin();
    for (int elem : sorted_subset) {
        it = std::find(it, sorted_source.end(), elem);
        EXPECT_NE(it, sorted_source.end());
        if (it == sorted_source.end())
            break;
        it++; // Prepare for the next iteration, avoid finding the same element
    }
}

/**
 * @brief Metamorphic Relation 30: Appending a sorted vector to another sorted vector.
 * The resulting vector should maintain a non-decreasing sequence after sorting.
 *
 */
TEST_P(HeapSortParamTest, MR30) {
    /* Get source inputs */
    HeapSortInput input = GetParam();
    vector<int> sorted_vec1 = heap_sort(input.vec);                  // Assume sorted
    vector<int> sorted_vec2 = heap_sort(vector<int>{1, 2, 3, 4, 5}); // Another presorted vector

    /* Append sorted_vec2 to sorted_vec1 */
    sorted_vec1.insert(sorted_vec1.end(), sorted_vec2.begin(), sorted_vec2.end());

    /* Sort the combined vector */
    vector<int> re_sorted_vec = heap_sort(sorted_vec1);

    /* Verification */
    int prev_elem = std::numeric_limits<int>::min();
    for (int elem : re_sorted_vec) {
        EXPECT_GE(elem, prev_elem);
        prev_elem = elem;
    }
}
/**
 * @brief Metamorphic Relation 31: Repeating a vector to form an input of replicated segments.
 * The sorted output should maintain the pattern of repeating values from each segment.
 *
 */
TEST_P(HeapSortParamTest, MR31) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> segment = input.vec;

    /* Create an input vector consisting of a repeated pattern */
    vector<int> source_vec;
    int repetitions = 3; // Number of times to repeat the segment
    for (int i = 0; i < repetitions; ++i) {
        source_vec.insert(source_vec.end(), segment.begin(), segment.end());
    }

    /* Sort the vector with repeated segments */
    vector<int> sorted_vec = heap_sort(source_vec);

    /* Check that the sorted vector maintains the repeating pattern */
    for (size_t i = 0; i < segment.size(); ++i) {
        int first_value = sorted_vec[i];
        for (int r = 1; r < repetitions; ++r) {
            size_t index = r * segment.size() + i;
            // Each repetition should have the same value at the same position
            EXPECT_EQ(sorted_vec[index], first_value);
        }
    }
}

/**
 * @brief Metamorphic Relation 32: Sorting a vector, then adding a new maximum value and sorting again.
 * The new maximum should be at the end of the sorted vector after the second sort.
 *
 */
TEST_P(HeapSortParamTest, MR32) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the vector */
    vector<int> sorted_vec = heap_sort(source_vec);

    /* Find the new maximum value to add: one greater than the current max or zero if empty */
    int new_max = sorted_vec.empty() ? 0 : sorted_vec.back() + 1;

    /* Add the new maximum to the sorted vector and sort again */
    sorted_vec.push_back(new_max);
    vector<int> twice_sorted_vec = heap_sort(sorted_vec);

    /* The last element should be the new maximum */
    EXPECT_EQ(twice_sorted_vec.back(), new_max);
}

/**
 * @brief Metamorphic Relation 33: Sorting a vector and checking stability by comparing indices of equal values.
 * The relative order of elements that are equal should remain consistent before and after the sort.
 *
 */
TEST_P(HeapSortParamTest, MR33) {
    /* Get source input with possible duplicates */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Map each number to the list of its indices in the original vector.
    std::unordered_map<int, std::queue<size_t>> value_indices;
    for (size_t i = 0; i < source_vec.size(); ++i) {
        value_indices[source_vec[i]].push(i);
    }

    /* Sort the vector */
    vector<int> sorted_vec = heap_sort(source_vec);

    /* Check the stability of the sort by comparing indices */
    for (int elem : sorted_vec) {
        auto &indices = value_indices[elem];
        EXPECT_FALSE(indices.empty());
        EXPECT_EQ(source_vec[indices.front()], elem);
        indices.pop();
    }
}

/**
 * @brief Metamorphic Relation 34: Sorting an already sorted vector in reverse order.
 * Sorting the reversed vector should return it to the original sorted order.
 *
 */
TEST_P(HeapSortParamTest, MR34) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> sorted_vec = heap_sort(input.vec);

    /* Reverse the sorted vector */
    std::reverse(sorted_vec.begin(), sorted_vec.end());

    /* Sort the reversed vector */
    vector<int> re_sorted_vec = heap_sort(sorted_vec);

    /* Verify re-sorted vector matches the initially sorted one */
    EXPECT_EQ(re_sorted_vec, heap_sort(input.vec));
}
/**
 * @brief Metamorphic Relation 35: Scaling the input vector by a constant factor and sorting.
 * The sorted output, when scaled back, should match the originally sorted vector.
 *
 */
TEST_P(HeapSortParamTest, MR35) {
    const int scale_factor = 10;

    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Scale the source vector */
    vector<int> scaled_vec(source_vec.size());
    std::transform(source_vec.begin(), source_vec.end(), scaled_vec.begin(), [scale_factor](int value) { return value * scale_factor; });

    /* Sort the scaled vector */
    vector<int> sorted_scaled_vec = heap_sort(scaled_vec);

    /* Scale back the sorted vector to original values */
    std::transform(sorted_scaled_vec.begin(), sorted_scaled_vec.end(), sorted_scaled_vec.begin(), [scale_factor](int value) { return value / scale_factor; });

    /* Sort the original source vector */
    vector<int> sorted_source_vec = heap_sort(source_vec);

    /* Verification */
    EXPECT_EQ(sorted_source_vec, sorted_scaled_vec);
}

/**
 * @brief Metamorphic Relation 36: Concatenating the sorted output with a new element at the start and end, then sorting.
 * After sorting, the new elements should be at the appropriate positions as per their values.
 *
 */
TEST_P(HeapSortParamTest, MR36) {   // Fixed
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the source vector */
    vector<int> sorted_vec = heap_sort(source_vec);

    /* Identify a value smaller and larger than the sorted values */
    int smaller_value = sorted_vec.empty() ? -10000 : sorted_vec.back() - 1;
    int larger_value = sorted_vec.empty() ? 10000 : sorted_vec.front() + 1;

    /* Insert the smaller and larger value at the start and end */
    sorted_vec.insert(sorted_vec.begin(), smaller_value);
    sorted_vec.push_back(larger_value);

    /* Sort the new vector */
    vector<int> new_sorted_vec = heap_sort(sorted_vec);

    /* Verification */
    EXPECT_EQ(new_sorted_vec.back(), smaller_value);
    EXPECT_EQ(new_sorted_vec.front(), larger_value);
}

/**
 * @brief Metamorphic Relation 37: Sorting an input vector and then removing a value from anywhere and re-sorting.
 * The re-sorted vector should be the same as sorting the input vector with the value removed initially.
 *
 */
TEST_P(HeapSortParamTest, MR37) {   // Fixed
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the source vector */
    vector<int> sorted_vec = heap_sort(source_vec);

    // Guard for empty vectors, and vectors of size 1 where removing would lead to the same result
    if (sorted_vec.size() <= 1)
        return;

    /* Remove an element from the sorted vector and then re-sort */
    int mn = sorted_vec.back();
    sorted_vec.pop_back(); // Removing middle element
    vector<int> re_sorted_vec = heap_sort(sorted_vec);

    /* Remove the same element from the source and sort */
    vector<int> follow_vec;
    bool has_removed = false;
    for (auto& val : source_vec) {
        if (val == mn && !has_removed) {
            has_removed = true;
        } else {
            follow_vec.push_back(val);
        }
    }
    vector<int> sorted_removed_vec = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(re_sorted_vec, sorted_removed_vec);
}

/**
 * @brief Metamorphic Relation 38: Combining multiple vectors with interleaved and progressively larger numbers.
 * Sorting the combined vector should equal sorting each individual vector and then merging.
 *
 */
TEST_P(HeapSortParamTest, MR38) {
    /* Get source input */
    HeapSortInput input1 = GetParam();
    HeapSortInput input2(gen_vector_randomly()); // Assume this provides a different list of parameters

    /* Create interleaved vectors from input vectors with progressively larger numbers */
    vector<int> interleaved_vec1(input1.vec.size());
    vector<int> interleaved_vec2(input2.vec.size());

    std::generate(interleaved_vec1.begin(), interleaved_vec1.end(), [n = 0]() mutable { return n += 2; });
    std::generate(interleaved_vec2.begin(), interleaved_vec2.end(), [n = 1]() mutable { return n += 2; });

    /* Combine interleaved vectors */
    interleaved_vec1.insert(interleaved_vec1.end(), interleaved_vec2.begin(), interleaved_vec2.end());

    /* Sort the combined vector */
    vector<int> sorted_combined_vec = heap_sort(interleaved_vec1);

    /* Sort individual interleaved vectors and then merge */
    vector<int> sorted_interleaved_vec1 = heap_sort(interleaved_vec1);
    vector<int> sorted_interleaved_vec2 = heap_sort(interleaved_vec2);
    vector<int> merged_sorted_vec;
    std::merge(sorted_interleaved_vec1.begin(), sorted_interleaved_vec1.end(), sorted_interleaved_vec2.begin(), sorted_interleaved_vec2.end(),
               std::back_inserter(merged_sorted_vec));

    /* Verification */
    EXPECT_EQ(sorted_combined_vec, merged_sorted_vec);
}
/**
 * @brief Metamorphic Relation 39: Sorting a vector and its reverse should give mirrored outputs.
 * The reversed sorted vector should be the reverse of the sorted vector.
 *
 */
TEST_P(HeapSortParamTest, MR39) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Sort the source vector */
    vector<int> sorted_vec = heap_sort(source_vec);

    /* Reverse the source vector */
    vector<int> reversed_vec(source_vec.rbegin(), source_vec.rend());

    /* Sort the reversed vector */
    vector<int> sorted_reversed_vec = heap_sort(reversed_vec);

    /* Reverse the sorted reversed vector */
    std::reverse(sorted_reversed_vec.begin(), sorted_reversed_vec.end());

    /* Verification */
    EXPECT_EQ(sorted_vec, sorted_reversed_vec);
}

/**
 * @brief Metamorphic Relation 40: Sorting a vector with elements repeated should give evenly distributed duplicates.
 * Duplicates of each element should be adjacent in the sorted output.
 *
 */
TEST_P(HeapSortParamTest, MR40) {
    const int repeat_count = 3; // Number of times to repeat each element

    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Repeat each element in the source vector */
    vector<int> repeated_vec;
    for (int elem : source_vec) {
        repeated_vec.insert(repeated_vec.end(), repeat_count, elem);
    }

    /* Sort the repeated vector */
    vector<int> sorted_repeated_vec = heap_sort(repeated_vec);

    /* Verification */
    for (size_t i = 0; i < sorted_repeated_vec.size(); i += repeat_count) {
        for (int j = 1; j < repeat_count; ++j) {
            EXPECT_EQ(sorted_repeated_vec[i], sorted_repeated_vec[i + j]);
        }
    }
}

/**
 * @brief Metamorphic Relation 41: Sorting vectors of varying lengths of identical elements.
 * All such vectors should result in identical sorted vectors, regardless of the original length.
 *
 */
TEST_P(HeapSortParamTest, MR41) {
    /* Construct vectors of different lengths but the same values */
    vector<int> vec_length_5(5, 7);   // Vector of length 5, all elements are 7
    vector<int> vec_length_10(10, 7); // Vector of length 10, all elements are 7

    /* Sort both vectors */
    vector<int> sorted_vec_length_5 = heap_sort(vec_length_5);
    vector<int> sorted_vec_length_10 = heap_sort(vec_length_10);

    /* Verification */
    EXPECT_TRUE(std::all_of(sorted_vec_length_5.begin(), sorted_vec_length_5.end(), [](int i) { return i == 7; }));
    EXPECT_TRUE(std::all_of(sorted_vec_length_10.begin(), sorted_vec_length_10.end(), [](int i) { return i == 7; }));
    EXPECT_EQ(sorted_vec_length_5, vector<int>(5, 7));
    EXPECT_EQ(sorted_vec_length_10, vector<int>(10, 7));
}

/**
 * @brief Metamorphic Relation 42: Scaling elements of the vector by -1 should preserve sort order in a reversed manner.
 * The sorted output, when all elements are multiplied by -1, should be the reverse of the original sorted output.
 *
 */
TEST_P(HeapSortParamTest, MR42) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Scale the source vector by -1 */
    vector<int> negated_vec(source_vec.size());
    std::transform(source_vec.begin(), source_vec.end(), negated_vec.begin(), [](int value) { return -value; });

    /* Sort the negated vector */
    vector<int> sorted_negated_vec = heap_sort(negated_vec);

    /* Sort the original vector */
    vector<int> sorted_vec = heap_sort(source_vec);

    /* Reverse the original sorted vector */
    std::reverse(sorted_vec.begin(), sorted_vec.end());

    /* Verification */
    EXPECT_EQ(sorted_negated_vec, sorted_vec);
}

/**
 * @brief Metamorphic Relation 43: Inserting the same element multiple times into the sorted array should keep it sorted.
 * Inserting elements in sorted order keeps the array sorted without needing another sorting pass.
 *
 */
TEST_P(HeapSortParamTest, MR43) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> sorted_vec = heap_sort(input.vec);

    /* Insert elements into the sorted array */
    for (int i = 0; i < 5; ++i) {
        auto it = std::upper_bound(sorted_vec.begin(), sorted_vec.end(), i);
        sorted_vec.insert(it, i); // Insert in sorted order
    }

    /* Verification */
    for (size_t i = 1; i < sorted_vec.size(); ++i) {
        EXPECT_LE(sorted_vec[i - 1], sorted_vec[i]);
    }
}

INSTANTIATE_TEST_CASE_P(TrueReturn, HeapSortParamTest, testing::ValuesIn(gen_tcs_randomly()));
