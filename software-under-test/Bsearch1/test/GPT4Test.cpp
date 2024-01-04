#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class BSearchParamTest : public ::testing::TestWithParam<BSearch1Input> {};

/**
 * @brief Metamorphic relation 3: Increase all elements except for the target in the array by a constant.
 * If the target exists, the index should remain the same. If the target does not exist and all elements
 * are increased, the function should still return -1.
 *
 */
TEST_P(BSearchParamTest, MR3) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 1; // or any other positive value
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        if (val != target)
            val += constant;

    /* Sort the follow-up vector since the order might be changed */
    sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    if (source_out != -1)
        EXPECT_EQ(source_out, follow_out);
    else
        EXPECT_EQ(follow_out, -1);
}

// MR5: Reversing the Array and Adjusting the Index: Since the array is in ascending order, reversing it will give a descending array. If we then search for the
// target element, the index we receive should mirror the index from the original array if the element exists. Specifically, the relation should be
// `original_index = (vec.size() - 1) - reversed_index`.
TEST_P(BSearchParamTest, MR5) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int source_out = bin_search(vec, target);

    // Construct follow-up input (reverse the vector)
    vector<int> reversed_vec = vec;
    std::reverse(reversed_vec.begin(), reversed_vec.end());

    // Get follow-up output
    int reversed_out = bin_search(reversed_vec, target);

    // Verification
    if (source_out != -1) {
        int expected_reversed_out = reversed_vec.size() - 1 - source_out;
        EXPECT_EQ(expected_reversed_out, reversed_out);
    } else {
        EXPECT_EQ(reversed_out, -1);
    }
}

// MR6: Doubling Elements Except Target: If you double all elements in the array except for the target (leaving it unchanged), then the index of the target
// should not change if it exists. If the target does not exist, the function should still return -1.
TEST_P(BSearchParamTest, MR6) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int source_out = bin_search(vec, target);

    // Construct follow-up input
    vector<int> modified_vec = vec;
    for (int &val : modified_vec)
        if (val != target)
            val *= 2;

    // Sort the modified vector since the order might be changed
    std::sort(modified_vec.begin(), modified_vec.end());

    // Get follow-up output
    int modified_out = bin_search(modified_vec, target);

    // Verification
    if (source_out != -1)
        EXPECT_EQ(source_out, modified_out);
    else
        EXPECT_EQ(modified_out, -1);
}

// MR7: Filtering Out Non-Target Elements Greater or Lesser Than Target: If you remove elements that are either all greater than or all lesser than the target,
// the index of the target (if present) will shift according to the number of elements removed but should otherwise remain present in the array.
TEST_P(BSearchParamTest, MR7) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int source_out = bin_search(vec, target);

    // Construct two follow-up inputs: filter greater than and less than target
    vector<int> less_filtered_vec(vec.begin(), std::find(vec.begin(), vec.end(), target));
    vector<int> greater_filtered_vec(std::find(vec.begin(), vec.end(), target), vec.end());

    // Get follow-up outputs
    int less_filtered_out = source_out != -1 ? bin_search(less_filtered_vec, target) : -1;
    int greater_filtered_out = bin_search(greater_filtered_vec, target);

    // Verification
    if (source_out != -1) {
        EXPECT_EQ(less_filtered_out, source_out);
        EXPECT_EQ(greater_filtered_out, 0); // If target exists, it should now be the first element
    } else {
        EXPECT_EQ(less_filtered_out, -1);
        EXPECT_EQ(greater_filtered_out, -1);
    }
}

// MR8: Insertion of Non-target Elements: Inserting additional elements that are not equal to the `target` should not change the index of the target if it
// already exists in the array. After the insertion, the target's index will either remain the same or increase, depending on whether the inserted elements are
// less than the target.
TEST_P(BSearchParamTest, MR8) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by inserting non-target elements
    vector<int> enlarged_vec = vec;
    enlarged_vec.insert(enlarged_vec.begin() + enlarged_vec.size() / 2, vec.front() - 1); // Insert a smaller element
    enlarged_vec.insert(enlarged_vec.begin() + enlarged_vec.size() / 2, vec.back() + 1);  // Insert a larger element
    std::sort(enlarged_vec.begin(), enlarged_vec.end());                                  // Assure the vector remains sorted

    // Get follow-up output
    int enlarged_index = bin_search(enlarged_vec, target);

    // Verification
    if (original_index != -1) {
        EXPECT_LE(original_index, enlarged_index);
    } else {
        EXPECT_EQ(enlarged_index, -1);
    }
}

// MR9: Reducing the Array: Shortening the array by removing elements other than the target should result in the target having the same index or a smaller
// index. If the target is not present in the original array, it should remain absent and the function should return -1.
TEST_P(BSearchParamTest, MR9) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by removing some non-target elements
    vector<int> shortened_vec = vec;
    shortened_vec.erase(shortened_vec.begin(), shortened_vec.begin() + shortened_vec.size() / 4);
    shortened_vec.erase(shortened_vec.end() - shortened_vec.size() / 4, shortened_vec.end());

    // Get follow-up output
    int shortened_index = bin_search(shortened_vec, target);

    // Verification
    if (original_index != -1) {
        EXPECT_GE(original_index, shortened_index);
    } else {
        EXPECT_EQ(shortened_index, -1);
    }
}

// MR10: Target Duplication: If the `target` exists in the array and we add more instances of the target, the index of the first occurrence of the target should
// remain the same since binary search typically returns the first match.
TEST_P(BSearchParamTest, MR10) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by duplicating the target element
    vector<int> duplicated_vec = vec;
    if (original_index != -1) {
        duplicated_vec.insert(duplicated_vec.begin() + original_index, target);     // Duplicate the target
        duplicated_vec.insert(duplicated_vec.begin() + original_index + 1, target); // Duplicate again
    }
    // Note: No sorting needed since we're inserting at the known index of target

    // Get follow-up output
    int duplicated_index = bin_search(duplicated_vec, target);

    // Verification
    EXPECT_EQ(original_index, duplicated_index);
}

// MR11: Element Value Shift: If you add a constant value to every element in the array (including the `target`), the index of the `target` should remain the
// same because the relative order of the elements is retained.
TEST_P(BSearchParamTest, MR11) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by adding a constant to all elements
    int shift = 10; // Example constant value
    vector<int> shifted_vec(vec.size());
    std::transform(vec.begin(), vec.end(), shifted_vec.begin(), [shift](int el) { return el + shift; });
    int shifted_target = target + shift;

    // Get follow-up output
    int shifted_index = bin_search(shifted_vec, shifted_target);

    // Verification
    EXPECT_EQ(original_index, shifted_index);
}

// MR12: Subarray with Target: Create a subarray that starts from an index before the `target` (if present) and includes it to the end of the array. The
// `target` index within the subarray should be the same as within the original array, relative to the start of the subarray.
TEST_P(BSearchParamTest, MR12) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by creating a subarray including the target
    // Use max to prevent underflow if the target is at the beginning of the array
    size_t subarray_start = std::max(0, original_index - 1);
    vector<int> subarray(vec.begin() + subarray_start, vec.end());

    // Get follow-up output
    int subarray_index = bin_search(subarray, target);

    // Verification: The expected index should be original_index - subarray_start
    if (original_index != -1) {
        EXPECT_EQ(subarray_index, original_index - subarray_start);
    } else {
        EXPECT_EQ(subarray_index, -1);
    }
}

// MR13: Random Shuffling Non-target Elements: Randomly shuffle elements in the array except for the `target`, then sort the array to maintain the ascending
// order. The target's index should remain the same.
TEST_P(BSearchParamTest, MR13) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by shuffling non-target elements
    vector<int> shuffled_vec(vec);
    std::srand(unsigned(std::time(0))); // Seed with current time for randomness
    std::random_shuffle(shuffled_vec.begin(), shuffled_vec.end(), [target](int i) { return i != target; });
    std::sort(shuffled_vec.begin(), shuffled_vec.end()); // Re-sort to ensure ascending order

    // Get follow-up output
    int shuffled_index = bin_search(shuffled_vec, target);

    // Verification
    EXPECT_EQ(original_index, shuffled_index);
}

// MR14: Inversion of Array Elements Relative to Target: Invert the relation of array elements to the `target` (i.e., if `element < target`, then `element >
// new_target`) and re-sort the array. The `target` index should either remain the same, become `-1`, or shift accordingly if the relation of the other elements
// is preserved.
TEST_P(BSearchParamTest, MR14) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by inverting elements relative to the target
    int max_elem = *std::max_element(vec.begin(), vec.end());
    vector<int> inverted_vec(vec.size());
    std::transform(vec.begin(), vec.end(), inverted_vec.begin(), [max_elem, target](int el) { return el < target ? max_elem + (target - el) : el; });
    std::sort(inverted_vec.begin(), inverted_vec.end());

    // Get follow-up output
    int inverted_index = bin_search(inverted_vec, target);

    // Verification
    if (original_index != -1) {
        EXPECT_EQ(original_index, inverted_index);
    } else {
        // If the target was not in the original array, it should not be in the transformed array
        EXPECT_EQ(inverted_index, -1);
    }
}

// MR15: Array Extension with Elements Less Than Target: Extending the array with new elements that are all less than the `target` will not affect the index of
// the target if it exists. After the extension, if the target is present, its new index will be greater, offset by the number of new elements added.
TEST_P(BSearchParamTest, MR15) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by extending with lesser elements
    int number_of_new_elements = 3; // For example
    vector<int> extended_vec = vec;
    extended_vec.insert(extended_vec.begin(), number_of_new_elements, vec.front() - 1);

    // Get follow-up output
    int extended_index = bin_search(extended_vec, target);

    // Verification
    if (original_index != -1) {
        EXPECT_EQ(extended_index, original_index + number_of_new_elements);
    } else {
        EXPECT_EQ(extended_index, -1);
    }
}

// MR16: Array Extension with Elements Greater Than Target: Extending the array with new elements that are all greater than the `target` should not change the
// index of the target if it exists in the array.
TEST_P(BSearchParamTest, MR16) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by extending with greater elements
    int number_of_new_elements = 3; // For example
    vector<int> extended_vec(vec.begin(), vec.end() - number_of_new_elements);
    extended_vec.insert(extended_vec.end(), number_of_new_elements, vec.back() + 1);

    // Get follow-up output
    int extended_index = bin_search(extended_vec, target);

    // Verification
    EXPECT_EQ(extended_index, original_index);
}

// MR17: Alteration of Non-Target Elements Without Order Change: Modify array elements not equal to the `target` in a way that does not affect their relative
// order, for example, by applying a monotonic increasing function. The index of the `target` should remain unchanged.
TEST_P(BSearchParamTest, MR17) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by altering non-target elements
    vector<int> altered_vec = vec;
    for (int &value : altered_vec) {
        if (value != target) {
            value = std::pow(value, 2); // Apply a square function as an example
        }
    }
    std::sort(altered_vec.begin(), altered_vec.end()); // Sorting to maintain the ascending order

    // Get follow-up output
    int altered_index = bin_search(altered_vec, target);

    // Verification
    EXPECT_EQ(altered_index, original_index);
}

// MR18: Repetition with Removal of Target: Duplicate the array by appending it to the end, except for the `target`. When the `target` is searched in this new
// array, the original index of the `target` should match the index in the repeated array. If the `target` was not present, it should remain absent (-1).
TEST_P(BSearchParamTest, MR18) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by repeating the array without the target
    vector<int> repeated_vec(vec);
    repeated_vec.reserve(vec.size() * 2); // Reserve enough space for repetition
    std::copy_if(vec.begin(), vec.end(), std::back_inserter(repeated_vec), [target](int value) { return value != target; });

    // Get follow-up output
    int repeated_index = bin_search(repeated_vec, target);

    // Verification
    EXPECT_EQ(repeated_index, original_index);
}

// MR19: Splitting the Array Around the Target: If the target exists in the array, splitting the array at the target's index and conducting a binary search on
// the appropriate half should yield an index relative to that subarray.
TEST_P(BSearchParamTest, MR19) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by splitting the array at the target's index
    std::size_t split_index = original_index != -1 ? original_index : vec.size() / 2;
    vector<int> first_half(vec.begin(), vec.begin() + split_index);
    vector<int> second_half(vec.begin() + split_index, vec.end());

    // Get follow-up output
    int first_half_index = bin_search(first_half, target);
    int second_half_index = bin_search(second_half, target);

    // Verification
    if (original_index != -1 && original_index < split_index) {
        EXPECT_EQ(first_half_index, original_index);
        EXPECT_EQ(second_half_index, -1);
    } else if (original_index != -1) {
        EXPECT_EQ(first_half_index, -1);
        EXPECT_EQ(second_half_index, original_index - split_index);
    } else {
        EXPECT_EQ(first_half_index, -1);
        EXPECT_EQ(second_half_index, -1);
    }
}

// MR20: Concatenation of Arrays: Concatenate the original array with another sorted array that contains all elements greater than any element in the original
// array. The index of the `target` should remain unchanged if it exists.
TEST_P(BSearchParamTest, MR20) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by concatenating with another sorted array
    vector<int> greater_elements = {vec.back() + 1, vec.back() + 2, vec.back() + 3};
    vector<int> concatenated_vec(vec);
    concatenated_vec.insert(concatenated_vec.end(), greater_elements.begin(), greater_elements.end());

    // Get follow-up output
    int concatenated_index = bin_search(concatenated_vec, target);

    // Verification
    EXPECT_EQ(concatenated_index, original_index);
}

#if CRASH
// MR21: Value Replacement Outside the Target: Replace every element except the target with a specific value that does not equal the target, and sort the array.
// The index of the target should be either unchanged or become the first or last index if the replacement value is less or greater than the target,
// respectively.
TEST_P(BSearchParamTest, MR21) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by replacing other values
    int repl_value = vec.front() - 1; // Example value less than all elements
    vector<int> replaced_vec(vec.size(), repl_value);
    replaced_vec[original_index] = target;               // Place the target at its original index
    std::sort(replaced_vec.begin(), replaced_vec.end()); // Sort the vector

    // Get follow-up output
    int replaced_index = bin_search(replaced_vec, target);

    // Verification
    if (original_index != -1) {
        // Target should remain in the array; its position might shift to the beginning
        EXPECT_LE(replaced_index, original_index);
    } else {
        EXPECT_EQ(replaced_index, -1);
    }
}
#endif

// MR22: Mirror Transformation: Apply a mirror transformation to the array elements with respect to the largest element, and adjust the target accordingly. The
// index of the new target should match the original index if the target originally existed.
TEST_P(BSearchParamTest, MR22) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Find the largest element for the mirror transformation
    int max_elem = *std::max_element(vec.begin(), vec.end());

    // Construct follow-up input by mirroring elements
    vector<int> mirrored_vec(vec);
    std::transform(mirrored_vec.begin(), mirrored_vec.end(), mirrored_vec.begin(), [max_elem](int el) { return 2 * max_elem - el; });
    int mirrored_target = 2 * max_elem - target;
    std::sort(mirrored_vec.begin(), mirrored_vec.end());

    // Get follow-up output
    int mirrored_index = bin_search(mirrored_vec, mirrored_target);

    // Verification
    EXPECT_EQ(mirrored_index, original_index);
}

// MR23: Element Replacement with Incremental Values: If we replace all elements except for the `target` with incremental values that do not include the
// `target`, the index of the `target` should remain unchanged if it exists.
TEST_P(BSearchParamTest, MR23) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by replacing other values with a sequence
    vector<int> incremental_vec(vec.size());
    std::generate(incremental_vec.begin(), incremental_vec.end(), [n = 0]() mutable { return n++; });

    // Place target in the expected position if it exists in the original array
    if (original_index != -1) {
        incremental_vec[original_index] = target;
    }
    std::sort(incremental_vec.begin(), incremental_vec.end()); // Sort to maintain order

    // Get follow-up output
    int incremental_index = bin_search(incremental_vec, target);

    // Verification
    EXPECT_EQ(incremental_index, original_index);
}

// MR24: Adding Target Duplicates with Different Intervals: Duplicate the `target` multiple times and intersperse these duplicates at different intervals in the
// array. The index of the first occurrence of the `target` should remain the same.
TEST_P(BSearchParamTest, MR24) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by adding duplicates of the target
    vector<int> duplicated_vec = vec;
    if (original_index != -1) {
        duplicated_vec.insert(duplicated_vec.begin() + original_index, target);
        duplicated_vec.insert(duplicated_vec.end(), target);
        std::sort(duplicated_vec.begin(), duplicated_vec.end());
    }

    // Get follow-up output
    int duplicated_index = bin_search(duplicated_vec, target);

    // Verification
    EXPECT_EQ(duplicated_index, original_index);
}

// MR25: Scaling the Array: Multiply every element in the array by a positive scaling factor, including the `target`. The resulting index of the `target` should
// remain the same after scaling since the relative order is preserved.
TEST_P(BSearchParamTest, MR25) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by scaling the array
    int scaling_factor = 2; // Example: Double the size of each element
    vector<int> scaled_vec(vec.size());
    std::transform(vec.begin(), vec.end(), scaled_vec.begin(), [scaling_factor](int el) { return el * scaling_factor; });
    int scaled_target = target * scaling_factor;

    // Get follow-up output
    int scaled_index = bin_search(scaled_vec, scaled_target);

    // Verification
    EXPECT_EQ(scaled_index, original_index);
}

// MR26: Periodic Offset: If you offset every `nth` element in the array by the same constant value, and this does not alter the relative ordering around the
// `target`, the index of the `target` should remain unchanged.
TEST_P(BSearchParamTest, MR26) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by offsetting every nth element
    vector<int> offset_vec = vec;
    int constant_value = 5; // An arbitrary offset
    int n = 3;              // Every third element
    for (size_t i = 0; i < offset_vec.size(); i += n) {
        if (offset_vec[i] != target) { // Avoid changing the target
            offset_vec[i] += constant_value;
        }
    }
    std::sort(offset_vec.begin(), offset_vec.end()); // Sort to preserve ascending order

    // Get follow-up output
    int offset_index = bin_search(offset_vec, target);

    // Verification
    EXPECT_EQ(offset_index, original_index);
}

// MR27: Subdivision and Search: Split the sorted array into two equally sized subarrays (or as equal as possible). If the `target` is present in the original
// array, it will be present in one of the subarrays. A binary search on both subarrays should yield a non-negative index from one subarray and `-1` from the
// other.
TEST_P(BSearchParamTest, MR27) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int mid = vec.size() / 2; // Midpoint for division

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by subdividing the array
    vector<int> first_half(vec.begin(), vec.begin() + mid);
    vector<int> second_half(vec.begin() + mid, vec.end());

    // Get follow-up output from both halves
    int index_first_half = bin_search(first_half, target);
    int index_second_half = bin_search(second_half, target);

    // Verification
    if (original_index != -1) {
        // Target was in original array, must be in one of the halves
        bool found_in_first_half = (index_first_half != -1);
        bool found_in_second_half = (index_second_half != -1);
        ASSERT_TRUE(found_in_first_half != found_in_second_half); // Should be in exactly one half
        if (found_in_first_half) {
            ASSERT_EQ(index_first_half, original_index);
        } else {
            ASSERT_EQ(index_second_half, original_index - mid);
        }
    } else {
        // Target was not in the original array, should not be in any half
        ASSERT_EQ(index_first_half, -1);
        ASSERT_EQ(index_second_half, -1);
    }
}

// MR28: Array Expansion by Repetition with Potential Shift: Duplicate the entire array but shift the elements of the second half by a value large enough to
// keep the overall array sorted. The index of the `target` in the new array will be the same as in the original array if the `target` is less than the shift
// value (and existed in the original array), otherwise, it should give `-1`.
TEST_P(BSearchParamTest, MR28) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    size_t vec_size = vec.size();
    int max_val = vec.back();
    int shift_val = max_val + 10; // Shift value ensures the array stays sorted

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by duplicating and shifting the second half of the array
    vector<int> expanded_vec;
    expanded_vec.reserve(2 * vec_size);
    expanded_vec.insert(expanded_vec.end(), vec.begin(), vec.end());         // First half
    std::transform(vec.begin(), vec.end(), std::back_inserter(expanded_vec), // Second half
                   [shift_val](int val) { return val + shift_val; });

    // Get follow-up output
    int expanded_index = bin_search(expanded_vec, target);

    // Verification
    if (original_index != -1 && target < shift_val) {
        EXPECT_EQ(expanded_index, original_index);
    } else {
        EXPECT_EQ(expanded_index, -1);
    }
}

// MR29: Element Distortion within Target Range: Apply a distortion that does not alter the relative order of elements within a range that includes the
// `target`. For instance, if the `target` exists and you square only the elements within a certain range around the `target`, except for the `target` itself,
// the index should remain unchanged.
TEST_P(BSearchParamTest, MR29) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by applying distortion around the target's range
    vector<int> distorted_vec = vec;
    int range = 2; // For instance, distort elements within +/- 2 positions of the target
    for (int i = std::max(original_index - range, 0), end = std::min(original_index + range + 1, static_cast<int>(vec.size())); i < end; ++i) {
        if (distorted_vec[i] != target) {
            distorted_vec[i] *= distorted_vec[i]; // For example, square the value
        }
    }
    std::sort(distorted_vec.begin(), distorted_vec.end()); // Sort to maintain ascending order

    // Get follow-up output
    int distorted_index = bin_search(distorted_vec, target);

    // Verification
    EXPECT_EQ(distorted_index, original_index);
}

// MR30: Array Rotation: Rotating a sorted array should not alter the relative ordering of elements drastically. If we rotate a sorted array around a pivot
// (other than the `target`) and adjust the `target`'s value according to the rotation, the new index of this adjusted `target` should correspond to the old
// index of the original target.
TEST_P(BSearchParamTest, MR30) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Construct follow-up input by rotating the array
    int pivot = vec.size() / 2;                               // For example, use the middle element as the pivot
    std::rotate(vec.begin(), vec.begin() + pivot, vec.end()); // Rotate the vector

    // Adjust target according to the rotation
    int adjusted_target = target + pivot < vec.size() ? vec[target + pivot] : vec[target + pivot - vec.size()];

    // Get follow-up output
    int rotated_index = bin_search(vec, adjusted_target);

    // Verification
    EXPECT_EQ(rotated_index, original_index);
}

#if INVALID
// MR31: Changing Array Bounds: If the binary search implementation allows searching within a specified sub-range of the array, then reducing the search bounds
// to exclude the target should result in the function returning -1. Conversely, expanding the search bounds wider than the array size (if allowed) should have
// no effect on the search result.
TEST_P(BSearchParamTest, MR31) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output within full bounds of the array
    int original_index = bin_search(vec, 0, vec.size() - 1, target);

    // Reduce search bounds to exclude the target
    int reduced_bounds_index = original_index > 0 ? bin_search(vec, 0, original_index - 1, target) : -1;

    // Expand search bounds beyond the array size
    int expanded_bounds_index = bin_search(vec, 0, vec.size() * 2, target);

    // Verification: Reduced bounds should not find the target, expanded bounds should return the same result
    EXPECT_EQ(reduced_bounds_index, -1);
    EXPECT_EQ(expanded_bounds_index, original_index);
}
#endif

// MR32: Inserting Elements Equal to the Target: If new elements equal to the target are inserted at positions before where the target is located, the index
// found by the binary search should shift accordingly (increasing by the count of inserted elements), if the implementation guarantees finding the first
// occurrence.
TEST_P(BSearchParamTest, MR32) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Insert target elements before the original index of the target
    int num_insertions = 3; // Assume we insert 3 elements equal to the target
    vector<int> modified_vec = vec;
    if (original_index != -1) {
        modified_vec.insert(modified_vec.begin() + original_index, num_insertions, target);
    }

    // Get follow-up output
    int modified_index = bin_search(modified_vec, target);

    // Verification
    int expected_index = (original_index != -1) ? (original_index + num_insertions) : -1;
    EXPECT_EQ(modified_index, expected_index);
}

// MR33: Modifying Elements Exceeding the Target: Increasing the values of elements exceeding the target should not affect the index of the target if it exists
// because the relative ordering of the array up to and including the target remains the same.
TEST_P(BSearchParamTest, MR33) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Increase the values of elements greater than the target
    vector<int> modified_vec = vec;
    for (auto &item : modified_vec) {
        if (item > target) {
            item += 10; // Arbitrary increment
        }
    }

    // Assuming the modified elements didn't disrupt the sorting order
    // Get follow-up output
    int modified_index = bin_search(modified_vec, target);

    // Verification
    EXPECT_EQ(modified_index, original_index);
}

// MR34: Array Inflation by Interspersing Minimal Values: Insert new elements with minimal values (less than the smallest original array element) dispersed
// throughout the array. The index of the target should increase but reflect the unchanged relative position of the original elements.
TEST_P(BSearchParamTest, MR34) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Intersperse minimal values
    vector<int> inflated_vec;
    int minimal_value = vec.front() - 10; // Value lower than the smallest element
    int intersperse_freq = 3;             // Frequency of interspersion

    for (size_t i = 0; i < vec.size(); ++i) {
        if (i % intersperse_freq == 0) {
            inflated_vec.push_back(minimal_value);
        }
        inflated_vec.push_back(vec[i]);
    }

    // Get follow-up output
    int inflated_index = bin_search(inflated_vec, target);

    // Verification
    int expected_index_shift = original_index / intersperse_freq;
    int expected_index = original_index + expected_index_shift;
    EXPECT_EQ(inflated_index, expected_index);
}

// MR35: Array Truncation Before the Target: Truncate all elements before the target's known index. The index of the target in the new array should match the
// subtracted truncated size if the element exists.
TEST_P(BSearchParamTest, MR35) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Truncate elements before the target's index
    int truncate_before_count = original_index / 2; // Elements to truncate before the target
    vector<int> truncated_vec(vec.begin() + truncate_before_count, vec.end());

    // Get follow-up output
    int truncated_index = bin_search(truncated_vec, target);

    // Verification
    int expected_index = original_index - truncate_before_count;
    EXPECT_EQ(truncated_index, expected_index);
}

// MR36: Array Truncation After the Target: Truncate all elements after the target's known index. If the target exists, its index should not change in the new
// array.
TEST_P(BSearchParamTest, MR36) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // If the target exists, truncate elements after its index
    vector<int> truncated_vec = vec;
    if (original_index >= 0) {
        truncated_vec.resize(original_index + 1);
    }

    // Get follow-up output
    int truncated_index = bin_search(truncated_vec, target);

    // Verification
    EXPECT_EQ(truncated_index, original_index);
}

// MR37: Concatenation of Identical Arrays: Concatenate the array with itself. The binary search index for the target in the new array should remain the same as
// in the original array if the target is located in the first half of the concatenated array.
TEST_P(BSearchParamTest, MR37) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Concatenate the array with itself
    vector<int> concatenated_vec(vec);
    concatenated_vec.insert(concatenated_vec.end(), vec.begin(), vec.end());

    // Get follow-up output
    int concatenated_index = bin_search(concatenated_vec, target);

    // Verification
    if (original_index != -1) {
        // The target index in concatenated array should match the original index
        EXPECT_EQ(concatenated_index, original_index);
    } else {
        // If the target did not exist, it should return -1
        EXPECT_EQ(concatenated_index, -1);
    }
}

// MR38: Exchanging Target With an Adjacent Value: Exchange the target value with one of its adjacent values. The index of the target should shift one position
// left or right if the swap maintains the array's sorted order.
TEST_P(BSearchParamTest, MR38) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Swap the target with its adjacent value (if possible)
    if (original_index > 0 && original_index < vec.size() - 1) {
        std::swap(vec[original_index], vec[original_index + 1]);
        // Ensure the ordering is still maintained
        if (vec[original_index] > vec[original_index + 1]) {
            std::sort(vec.begin(), vec.end()); // This might change the target index
        }
    }

    // Get follow-up output
    int swapped_index = bin_search(vec, target);

    // Verification
    int expected_index = (original_index == swapped_index - 1 || original_index == swapped_index + 1)
                             ? original_index
                             : original_index; // Remains the same if sorting was needed
    EXPECT_EQ(swapped_index, expected_index);
}

// MR39: Target Value Inflation: If the target value is inflated to become the largest element in the array and this new inflated target is searched for, the
// index returned should be the last index in the array or -1 if the original target did not exist.
TEST_P(BSearchParamTest, MR39) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Inflate the target's value to be the largest
    int inflated_target = vec.back() + 100;

    // If the original target exists replace it with the inflated value
    if (original_index >= 0) {
        vec[original_index] = inflated_target;
        std::sort(vec.begin(), vec.end()); // Re-sort the array
    }

    // Get follow-up output
    int inflated_index = bin_search(vec, inflated_target);

    // Verification
    if (original_index != -1) {
        // The inflated target should now be the last element
        EXPECT_EQ(inflated_index, vec.size() - 1);
    } else {
        // Original target didn't exist, so the inflated target shouldn't be found
        EXPECT_EQ(inflated_index, -1);
    }
}

// MR40: Array Element Scrambling Outside of Target Bounds: Scramble or shuffle the elements around the target, excluding the target itself and its immediate
// neighbors. Afterwards, sort the array again. The target's index should remain unchanged because the sorting restores the order.
TEST_P(BSearchParamTest, MR40) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Scramble elements around the target, then sort
    if (original_index > 1 && original_index < vec.size() - 2) {
        std::random_shuffle(vec.begin() + original_index + 2, vec.end());
        std::random_shuffle(vec.begin(), vec.begin() + original_index - 1);
        std::sort(vec.begin(), vec.end());
    }

    // Get follow-up output
    int scrambled_index = bin_search(vec, target);

    // Verification
    EXPECT_EQ(scrambled_index, original_index);
}

// MR41: Incremental Addition and Removal of Array Elements: Add incrementally increased values to the end of the array, and then remove a few of the lowest
// elements, all while ensuring the target element remains. The resulting position of the target should either stay the same or increase.
TEST_P(BSearchParamTest, MR41) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get initial output
    int original_index = bin_search(vec, target);

    // Add incrementally increased values at the end
    vec.push_back(vec.back() + 1);
    vec.push_back(vec.back() + 1);
    // Remove a few elements from the beginning
    vec.erase(vec.begin(), vec.begin() + 2);

    // Get follow-up output
    int modified_index = bin_search(vec, target);

    // Verification
    if (original_index != -1) {
        EXPECT_TRUE(modified_index == original_index || modified_index > original_index);
    } else {
        EXPECT_EQ(modified_index, -1);
    }
}

// MR42: Duplicating Array Elements Except for Target: Duplicate each element in the array except for the target. The position of the target should either
// remain the same when if it's the first of its value, or move to the second occurrence after duplication.
TEST_P(BSearchParamTest, MR42) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get initial output
    int original_index = bin_search(vec, target);

    // Duplicate all elements except the target
    vector<int> duplicated_vec;
    for (int val : vec) {
        duplicated_vec.push_back(val);
        if (val != target) {
            duplicated_vec.push_back(val);
        }
    }

    // Perform binary search on the new array
    int duplicated_index = bin_search(duplicated_vec, target);

    // Verification
    if (original_index != -1) {
        // Since the function might target the first occurrence,
        // the index of the target should remain the same.
        EXPECT_EQ(duplicated_index, original_index);
    } else {
        EXPECT_EQ(duplicated_index, -1);
    }
}

// MR43: Interspersing Values From a Separate Range: Insert elements from a separate range strictly between the existing array elements, inflating its index but
// maintaining the ordering. The index of the target in the new array should be higher by the number of inserted elements before the original index.
TEST_P(BSearchParamTest, MR43) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    vector<int> augmented_vec = vec;
    int new_elements = 0;
    for (int i = 1; i < augmented_vec.size(); i += 2) {
        augmented_vec.insert(augmented_vec.begin() + i, vec[i - 1] + 1);
        if (i <= original_index) {
            new_elements += 1; // Count inserted elements that are before the target's original index
        }
    }

    // Get follow-up output
    int augmented_index = bin_search(augmented_vec, target);

    // Verification
    if (original_index != -1) {
        int expected_index = original_index + new_elements;
        EXPECT_EQ(augmented_index, expected_index);
    } else {
        EXPECT_EQ(augmented_index, -1);
    }
}

// MR44: Partial Reversal of Array: Reverse a contiguous subset of the array that does not contain the target value, and then sort the array. The index of the
// target should remain unchanged as the sort restores the order.
TEST_P(BSearchParamTest, MR44) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Determine a subrange of the array to reverse (that should not include the target index)
    std::pair<int, int> subrange(1, original_index - 1); // Arbitrary subset before the target
    if (original_index + 2 < vec.size()) {
        subrange = std::make_pair(original_index + 2, vec.size() - 1); // Subset after the target
    }

    // Reverse the selected subrange
    if (subrange.first < subrange.second) {
        std::reverse(vec.begin() + subrange.first, vec.begin() + subrange.second);
    }

    // Sort the array after reversal
    std::sort(vec.begin(), vec.end());

    // Get follow-up output
    int after_reversal_index = bin_search(vec, target);

    // Verification
    EXPECT_EQ(after_reversal_index, original_index);
}

#if INVALID
// MR45: Combining Arrays with Non-Overlapping Ranges: Combine two sorted arrays with non-overlapping ranges with the second array containing all elements
// greater than those in the first. The presence and index of the target in the combined array should be consistent with the original if it was part of the
// first array.
TEST_P(BSearchParamTest, MR45) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec1 = input.vec;
    int target = input.target;
    vector<int> vec2 = GenerateNonOverlappingVector(vec1.back() + 10, vec1.size()); // Assuming this generates the second vector.

    // Get source output
    int original_index = bin_search(vec1, target);

    // Combine the two arrays
    vector<int> combined_vec(vec1);
    combined_vec.insert(combined_vec.end(), vec2.begin(), vec2.end());

    // Get follow-up output
    int combined_index = bin_search(combined_vec, target);

    // Verification
    EXPECT_EQ(combined_index, original_index);
}
#endif

// MR46: Adding and Subtracting a Constant Value from Array Elements: Add a constant value to each element of the array and then subtract that same value from
// the whole array. The index of the target should remain unchanged if found in the array since the changes cancel each other out.
TEST_P(BSearchParamTest, MR46) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> original_vec = input.vec;
    int target = input.target;
    int constant = 5; // Some non-zero constant

    // Apply transformations
    vector<int> vec = original_vec;
    for (auto &element : vec) {
        element += constant; // Increment all elements by the constant
    }
    for (auto &element : vec) {
        element -= constant; // Now, decrement them back to the original values
    }

    // Search for the target in the original and modified array
    int original_index = bin_search(original_vec, target);
    int modified_index = bin_search(vec, target);

    // Verification
    EXPECT_EQ(modified_index, original_index);
}

// MR47: Stretching Array Elements with Target Exclusion: Multiply all elements except for the target by a scaling factor (greater than one) and expand the
// target proportionally. The index of the target in the new, sorted array should remain the same.
TEST_P(BSearchParamTest, MR47) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    float scaling_factor = 2.0; // Scaling factor should be greater than 1

    // Get source output
    int original_index = bin_search(vec, target);

    // Apply the stretching transformation
    for (auto &element : vec) {
        if (element != target) {
            element = static_cast<int>(element * scaling_factor);
        }
    }
    vec.push_back(static_cast<int>(target * scaling_factor)); // Expand the target proportionally
    std::sort(vec.begin(), vec.end());                        // Re-sort the array to maintain sorted order

    // Perform search
    int modified_index = bin_search(vec, static_cast<int>(target * scaling_factor));

    // Verification
    EXPECT_EQ(modified_index, original_index);
}

// MR48: Negative Array Inversion: Invert all the elements in the array by multiplying them by -1, which effectively mirrors the array around zero, and find the
// 'negative' target. The order is reversed, so the correspondence of indices will mirror around the middle.
TEST_P(BSearchParamTest, MR48) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Invert the array and the target
    std::transform(vec.begin(), vec.end(), vec.begin(), std::negate<int>());
    std::sort(vec.begin(), vec.end());
    target *= -1;

    // Get source and follow-up output
    int original_index = bin_search(input.vec, input.target);
    int inverted_index = bin_search(vec, target);

    // Verification
    if (original_index != -1) {
        // Indices mirror each other
        EXPECT_EQ(inverted_index, vec.size() - 1 - original_index);
    } else {
        // The negative target should not be found if original was not
        EXPECT_EQ(inverted_index, -1);
    }
}

// MR49: Array Doubling With Incremental Gap: Double the values of each subsequent element with a constant incremental gap. If this transformation retains the
// sorted property, the index of the target (if present) should stay consistent.
TEST_P(BSearchParamTest, MR49) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int gap = 1; // The incremental gap

    // Get source output
    int original_index = bin_search(vec, target);

    // Double each element's value with an incremental gap
    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i] = 2 * vec[i] + gap * i;
    }

    // Perform search in the modified array
    int modified_index = bin_search(vec, 2 * target);

    // Verification
    EXPECT_EQ(modified_index, original_index);
}

// MR50: Multiplicative Scaling of the Array and Target: Multiply all elements in the array and the target value itself by the same positive non-zero constant.
// The index of the target should remain unchanged.
TEST_P(BSearchParamTest, MR50) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int scale_factor = 3; // Any positive non-zero constant

    // Get source output
    int original_index = bin_search(vec, target);

    // Scale the elements and the target
    for (auto &el : vec) {
        el *= scale_factor;
    }
    target *= scale_factor;

    // Get follow-up output after scaling
    int scaled_index = bin_search(vec, target);

    // Verification
    EXPECT_EQ(scaled_index, original_index);
}

// MR51: Conditional Element Swapping: For every adjacent pair of elements in the array, if neither element is the target, swap them. Afterward, sort the array
// to maintain ascending order. The index of the target should remain unchanged as their relative ordering is restored by sorting.
TEST_P(BSearchParamTest, MR51) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Swap adjacent non-target elements
    for (size_t i = 0; i < vec.size() - 1; i += 2) {
        if (vec[i] != target && vec[i + 1] != target) {
            std::swap(vec[i], vec[i + 1]);
        }
    }

    // Sort the array to maintain order
    std::sort(vec.begin(), vec.end());

    // Get follow-up output after swapping
    int swapped_index = bin_search(vec, target);

    // Verification
    EXPECT_EQ(swapped_index, original_index);
}

// MR52: Reflection of Non-target Elements: If you reflect the elements of the array around a chosen pivot that is not the target, then sort the array, the
// position of the target should stay the same in the sorted array as the original.
TEST_P(BSearchParamTest, MR52) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int pivot = vec[vec.size() / 2]; // Middle element

    // Get source output
    int original_index = bin_search(vec, target);

    // Reflect elements around a pivot that is not the target
    if (target != pivot) {
        for (auto &el : vec) {
            if (el != target) {
                el = 2 * pivot - el;
            }
        }
    }

    // Sort the array to re-establish the order
    std::sort(vec.begin(), vec.end());

    // Get follow-up output after reflection
    int reflected_index = bin_search(vec, target);

    // Verification
    EXPECT_EQ(reflected_index, original_index);
}

#if CRASH
// MR53: Shuffling Subarray Excluding Target: Shuffle the elements in a subarray that does not contain the target. After shuffling, re-sort the array. The index
// of the target should remain unchanged in the sorted array since sorting restores the order.
TEST_P(BSearchParamTest, MR53) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int original_index = bin_search(vec, target);

    // Shuffle a subarray excluding the target
    const size_t shuffle_start = 0;
    const size_t shuffle_end = original_index - 1; // An example subarray before the target
    std::random_shuffle(vec.begin() + shuffle_start, vec.begin() + shuffle_end);

    // Sort the array to ensure it's in ascending order
    std::sort(vec.begin(), vec.end());

    // Get follow-up output after shuffling and sorting
    int shuffled_index = bin_search(vec, target);

    // Verification
    EXPECT_EQ(shuffled_index, original_index);
}
#endif

INSTANTIATE_TEST_CASE_P(TrueReturn, BSearchParamTest,
                        testing::ValuesIn(gen_tcs_randomly()));