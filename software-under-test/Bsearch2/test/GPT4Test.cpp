#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <tuple>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

#define SKIP_CRASH

class BSearchParamTest : public ::testing::TestWithParam<BSearch2Input> {};

/**
 * @brief Metamorphic relation 2: Sorting a second array in descending order, the element should not be found in the new array.
 *
 */
TEST_P(BSearchParamTest, MR2) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input on a sorted array in descending order */
    vector<int> follow_vec(vec.rbegin(), vec.rend());

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    // As the binary search assumes the array is sorted in ascending order,
    // if the array is sorted in descending order, the binary search should always fail.
    EXPECT_FALSE(follow_out);
}

/**
 * @brief Metamorphic relation 3: After adding or deleting a repeated target value in the array, the output should be the same.
 *
 */
TEST_P(BSearchParamTest, MR3) { // Fixed
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Make sure the size of vec is larger than 1 */
    if (vec.size() == 1)
        vec.emplace_back(vec[0]);

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;

    // Add an extra instance of the target if it was found, otherwise remove an arbitrary element
    if (source_out) {
        follow_vec.push_back(target);
    } else if (!follow_vec.empty()) {
        follow_vec.pop_back();
    }

    // If the extra instance has been added, sort the array again
    if (source_out) {
        sort(follow_vec.begin(), follow_vec.end());
    }

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 4: Permuting the array while keeping it sorted should not affect the result of the search.
 *
 */
TEST_P(BSearchParamTest, MR4) { // Fixed
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input by permuting the elements of the array while keeping it sorted */
    // Permute the array
    random_shuffle(vec.begin(), vec.end());
    sort(vec.begin(), vec.end());

    /* Get follow-up output */
    bool follow_out = bin_search(vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 5: Scaling all elements of the array, including the target by a positive non-zero constant should not change the result of the
 * search.
 *
 */
TEST_P(BSearchParamTest, MR5) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int scale = 3; // A positive non-zero constant
    vector<int> follow_vec;
    for (int val : vec) {
        follow_vec.push_back(val * scale);
    }
    int follow_target = target * scale;

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 6: Doubling the array size by appending the same elements should not change the result if the target is present in the original
 * array.
 *
 */
TEST_P(BSearchParamTest, MR6) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input by doubling the array size */
    vector<int> follow_vec = vec;
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.end());
    sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    if (source_out) {
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic relation 7: Searching for a value outside the range of the array elements should always return false.
 *
 */
TEST_P(BSearchParamTest, MR7) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int max_elem = *max_element(vec.begin(), vec.end());
    int min_elem = *min_element(vec.begin(), vec.end());

    /* Search for out-of-range values */
    bool out_of_range_high_out = bin_search(vec, max_elem + 1);
    bool out_of_range_low_out = bin_search(vec, min_elem - 1);

    /* Verification */
    EXPECT_FALSE(out_of_range_high_out);
    EXPECT_FALSE(out_of_range_low_out);
}

/**
 * @brief Metamorphic relation 8: Inverting all elements of the array, including the target, should not change the result if the target is present.
 *
 */
TEST_P(BSearchParamTest, MR8) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input by inverting all elements */
    vector<int> follow_vec;
    for (int val : vec) {
        follow_vec.push_back(-val);
    }
    sort(follow_vec.begin(), follow_vec.end());
    int follow_target = -target;

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 9: Removing an element other than the target from a duplicated array should not change the result of the search for the target.
 *
 */
TEST_P(BSearchParamTest, MR9) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Ensure the target is in the vector before testing this MR */
    bool source_out = bin_search(vec, target);

    if (source_out && vec.size() > 1) {
        /* Construct follow-up input by duplicating and then removing a non-target element */
        vector<int> follow_vec = vec;
        follow_vec.push_back(vec[0] != target ? vec[0] : vec[1]); // Duplicate a non-target element
        sort(follow_vec.begin(), follow_vec.end());
        auto it = find_if(follow_vec.begin(), follow_vec.end(), [&](int v) { return v != target; });
        follow_vec.erase(it); // Remove a non-target element

        /* Get follow-up output */
        bool follow_out = bin_search(follow_vec, target);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic relation 10: Adding a new element greater than all existing elements in the array should not affect the result for the existing targets.
 *
 */
TEST_P(BSearchParamTest, MR10) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input by adding a larger element at the end */
    vector<int> follow_vec = vec;
    follow_vec.push_back(*max_element(vec.begin(), vec.end()) + 10); // Add an element that is larger than the largest in vec

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 11: If the target is found in the source array, adding a new element smaller than all existing elements in the array should not
 * affect the result.
 *
 */
TEST_P(BSearchParamTest, MR11) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* If the target was found then test the MR */
    if (source_out) {
        /* Construct follow-up input by adding a smaller element at the start */
        vector<int> follow_vec = vec;
        follow_vec.insert(follow_vec.begin(), *min_element(vec.begin(), vec.end()) - 10); // Add an element that is smaller than the smallest in vec

        /* Get follow-up output */
        bool follow_out = bin_search(follow_vec, target);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic relation 12: Changing the order of elements in the array without de-sorting should yield the same result.
 *
 * For example, if the array is [1, 2, 3, 4], then permutations such as [1, 3, 2, 4] are not allowed,
 * as they are not sorted, but [1, 1, 2, 3, 4] or [1, 2, 2, 3, 4] are allowed as they maintain the sorted property.
 *
 */
TEST_P(BSearchParamTest, MR12) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Proceed only if there are duplicates in the vector to maintain the sorted property while changing order */
    std::map<int, int> elem_counts;
    for (int elem : vec) {
        elem_counts[elem]++;
    }
    vector<int> vec_with_duplicates;
    for (auto &[elem, count] : elem_counts) {
        if (count > 1) {
            // Just double one element with duplicates, maintaining sort order
            vec_with_duplicates.push_back(elem);
            vec_with_duplicates.push_back(elem);
        } else {
            vec_with_duplicates.push_back(elem);
        }
    }

    /* If we were able to create a vector that maintains sorted order and changes element order proceed with the test */
    if (vec_with_duplicates.size() > vec.size()) {
        /* Get source output */
        bool source_out = bin_search(vec, target);

        /* Get follow-up output */
        bool follow_out = bin_search(vec_with_duplicates, target);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic relation 13: If the target does not exist in the array, reversing the array should also yield false when searching for the same target.
 *
 */
TEST_P(BSearchParamTest, MR13) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* If the target was not found then test the MR */
    if (!source_out) {
        /* Construct follow-up input by reversing sorted array */
        vector<int> follow_vec(vec.rbegin(), vec.rend()); // Reverse vec

        /* Get follow-up output */
        bool follow_out = bin_search(follow_vec, target);

        /* Verification */
        EXPECT_FALSE(follow_out); // Should still be false, as reversing won't make it suddenly exist
    }
}

/**
 * @brief Metamorphic relation 14: Removing all instances of the target from the array should return false when searching for the target.
 *
 */
TEST_P(BSearchParamTest, MR14) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* If the target was found then test the MR */
    if (source_out) {
        /* Construct follow-up input by removing all instances of the target */
        vector<int> follow_vec;
        copy_if(vec.begin(), vec.end(), back_inserter(follow_vec), [target](int v) { return v != target; });

        /* Get follow-up output */
        bool follow_out = bin_search(follow_vec, target);

        /* Verification */
        EXPECT_FALSE(follow_out); // Should return false, as the target has been removed
    }
}

/**
 * @brief Metamorphic relation 15: Replacing the target with another element that exists in the array should yield a positive result if the target was present,
 * otherwise the result should remain the same.
 *
 */
TEST_P(BSearchParamTest, MR15) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Select a replacement element that is different from the target and known to exist in the array */
    int replacement = vec[0] == target ? vec[1] : vec[0];

    /* Get follow-up output */
    bool follow_out = bin_search(vec, replacement);

    /* Verification */
    if (source_out) {
        // If the original target was in the list, then replacing it with another element from the list should also result in true.
        EXPECT_TRUE(follow_out);
    } else {
        // If the original target was not in the list, it should remain the same as the source output.
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic relation 16: If the array contains duplicates of the target, removing one occurrence should still yield true when searching for the
 * target.
 *
 */
TEST_P(BSearchParamTest, MR16) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Ensure that there is more than one occurrence of the target in the vector */
    bool has_duplicates = std::count(vec.begin(), vec.end(), target) > 1;

    if (has_duplicates) {
        /* Get source output */
        bool source_out = bin_search(vec, target);

        /* Construct follow-up input by removing one occurrence of the target */
        vector<int> follow_vec;
        bool removed = false;
        for (int v : vec) {
            if (v == target && !removed) {
                removed = true; // Remove only one occurrence of the target
                continue;
            }
            follow_vec.push_back(v);
        }

        /* Get follow-up output */
        bool follow_out = bin_search(follow_vec, target);

        /* Verification */
        EXPECT_EQ(source_out, follow_out); // Should still return true
    }
}

/**
 * @brief Metamorphic relation 17: If the target is greater than the largest element in the array,
 * adding additional elements smaller than the target should not affect the result.
 *
 */
TEST_P(BSearchParamTest, MR17) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = *max_element(vec.begin(), vec.end()) + 5; // Ensure the target is not in the original vector.

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input by adding elements smaller than the target */
    vector<int> follow_vec = vec;
    follow_vec.push_back(target - 1);
    follow_vec.push_back(target - 2);
    sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out); // Should return false as in the source output.
}

/**
 * @brief Metamorphic relation 18: For an array with unique elements, doubling the target and
 * multiplying all array elements by two should not affect the presence of the target.
 *
 */
TEST_P(BSearchParamTest, MR18) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Check if array elements are unique to apply this MR */
    std::set<int> unique_elements(vec.begin(), vec.end());
    if (unique_elements.size() == vec.size()) {
        /* Get source output */
        bool source_out = bin_search(vec, target);

        /* Construct follow-up input by multiplying elements and target by two */
        vector<int> follow_vec;
        std::transform(vec.begin(), vec.end(), std::back_inserter(follow_vec), [](int v) { return v * 2; });
        int follow_target = target * 2;

        /* Get follow-up output */
        bool follow_out = bin_search(follow_vec, follow_target);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic relation 19: For every target value that is found in the array, incrementing that target value by one
 * should result in a 'false' search result, assuming the incremented value does not exist in the array.
 *
 */
TEST_P(BSearchParamTest, MR19) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Apply this MR only if the target is found and incrementing it won't make it an existing element */
    if (source_out && std::find(vec.begin(), vec.end(), target + 1) == vec.end()) {
        /* Increment the target */
        int incremented_target = target + 1;

        /* Get follow-up output */
        bool follow_out = bin_search(vec, incremented_target);

        /* Verification */
        EXPECT_FALSE(follow_out); // The incremented value should not be found
    }
}

/**
 * @brief Metamorphic relation 20: For any target not found in the array, decrementing the largest element of the array should not
 * make the original target found.
 *
 */
TEST_P(BSearchParamTest, MR20) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Apply this MR only if the target is not found */
    if (!source_out) {
        /* Find the largest element and decrement it */
        auto max_it = std::max_element(vec.begin(), vec.end());
        int new_max = *max_it - 1;

        /* Construct follow-up input */
        vec.erase(max_it);
        vec.push_back(new_max);
        sort(vec.begin(), vec.end());

        /* Get follow-up output */
        bool follow_out = bin_search(vec, target);

        /* Verification */
        EXPECT_FALSE(follow_out); // The original target should not be found
    }
}

/**
 * @brief Metamorphic relation 21: Removing any element that is not equal to the target should not affect the result of the
 * search operation if the target is actually present in the array.
 *
 */
TEST_P(BSearchParamTest, MR21) { // Fixed
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construction of follow-up test only makes sense if the target is found (source_out is true) */
    if (source_out) {
        /* Construct follow-up input by removing an element that is not the target */
        vector<int> follow_vec;
        bool has_removed = false;
        for (int v : vec) {
            if (v != target && !has_removed) {
                has_removed = true; // Only remove one such element
            } else {
                follow_vec.push_back(v);
            }
        }

        /* Get follow-up output */
        bool follow_out = bin_search(follow_vec, target);

        /* Verification */
        EXPECT_EQ(source_out, follow_out); // Removal of a non-target element should not affect the presence of the target
    }
}

/**
 * @brief Metamorphic relation 22: Truncating the array before the position of the found target should keep the result unchanged.
 * That is, for any target found in the array, if we create a sub-array from the beginning up to the target, the target should still be
 * found in this new array.
 *
 */
TEST_P(BSearchParamTest, MR22) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* If the target is found in the array, truncate the array to test the MR */
    if (source_out) {
        auto target_position = std::find(vec.begin(), vec.end(), target);

        /* Construct follow-up input with elements up to and including the target */
        vector<int> follow_vec(vec.begin(), target_position + 1);

        /* Get follow-up output */
        bool follow_out = bin_search(follow_vec, target);

        /* Verification */
        EXPECT_TRUE(follow_out); // The target should still be present in the follow-up output
    }
}

/**
 * @brief Metamorphic relation 23: For any missing target, repeating the array elements should still result in the same output.
 *
 */
TEST_P(BSearchParamTest, MR23) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* If the target is not found in the array, repeat the array to test the MR */
    if (!source_out) {
        vector<int> repeated_vec(vec);
        repeated_vec.insert(repeated_vec.end(), vec.begin(), vec.end());

        /* Get follow-up output */
        bool follow_out = bin_search(repeated_vec, target);

        /* Verification */
        EXPECT_FALSE(follow_out); // The target should still not be present in the follow-up output
    }
}

/**
 * @brief Metamorphic relation 24: For an array containing the target, appending elements larger than the target should not affect the result.
 *
 */
TEST_P(BSearchParamTest, MR24) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* If target is found in source input */
    if (source_out) {
        /* Construct follow-up input by appending elements larger than any in the current array */
        int max_elem = *max_element(vec.begin(), vec.end());
        vec.push_back(max_elem + 1);
        vec.push_back(max_elem + 2);

        /* Get follow-up output */
        bool follow_out = bin_search(vec, target);

        /* Verification */
        EXPECT_TRUE(follow_out); // As the target is present, appending larger numbers don't affect result
    }
}

/**
 * @brief Metamorphic relation 25: For an array not containing the target, removing elements should still not find the target.
 *
 */
TEST_P(BSearchParamTest, MR25) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* If target is not found in source input */
    if (!source_out) {
        /* Construct follow-up input by removing elements */
        if (!vec.empty()) {
            vec.pop_back();         // Remove an element
            vec.erase(vec.begin()); // Remove another element
        }

        /* Get follow-up output */
        bool follow_out = bin_search(vec, target);

        /* Verification */
        EXPECT_FALSE(follow_out); // As the target is not present initially, removal of elements don't affect result
    }
}

/**
 * @brief Metamorphic relation 26: For an array that does not include the target, inserting the target anywhere inside the array, the target should be found.
 *
 */
TEST_P(BSearchParamTest, MR26) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* If target is not found in source input */
    if (!source_out) {
        vector<int> follow_vec = vec;
        auto it = std::upper_bound(follow_vec.begin(), follow_vec.end(), target);
        follow_vec.insert(it, target); // Insert target in a sorted position

        /* Get follow-up output */
        bool follow_out = bin_search(follow_vec, target);

        /* Verification */
        EXPECT_TRUE(follow_out); // Now the target should be in the follow-up input, and found
    }
}

/**
 * @brief Metamorphic relation 27: For an array where the target is found, shuffling the array without changing the elements should result in search failure due
 * to order violation.
 *
 */
TEST_P(BSearchParamTest, MR27) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* If target is found in source input */
    if (source_out) {
        vector<int> shuffled_vec = vec;
        std::random_shuffle(shuffled_vec.begin(), shuffled_vec.end()); // Shuffle elements

        /* Get follow-up output */
        bool follow_out = bin_search(shuffled_vec, target);

        /* Verification */
        EXPECT_FALSE(follow_out); // Since order is not maintained, binary search should not find the target
    }
}

/**
 * @brief Metamorphic relation 28: For an array containing the target, duplicating the target should not affect the search result.
 *
 */
TEST_P(BSearchParamTest, MR28) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* If target is found in source input */
    if (source_out) {
        vector<int> duplicated_vec = vec;
        duplicated_vec.insert(std::lower_bound(duplicated_vec.begin(), duplicated_vec.end(), target), target); // Duplicate the target

        /* Get follow-up output */
        bool follow_out = bin_search(duplicated_vec, target);

        /* Verification */
        EXPECT_TRUE(follow_out); // As the target is present, duplicating it doesn't change the search result
    }
}

/**
 * @brief Metamorphic relation 29: If the source array contains the target and is multiplied with -1,
 * searching for the negative of the original target should yield a true result.
 *
 */
TEST_P(BSearchParamTest, MR29) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (source_out) {
        /* Construct follow-up input by negating all elements */
        vector<int> negated_vec;
        std::transform(vec.begin(), vec.end(), std::back_inserter(negated_vec), [](int v) { return -v; });
        // Sorting is required as negation changes element order
        std::sort(negated_vec.begin(), negated_vec.end());

        /* Get follow-up output */
        bool follow_out = bin_search(negated_vec, -target);

        /* Verification */
        EXPECT_TRUE(follow_out); // Target's negation should be found
    }
}

/**
 * @brief Metamorphic relation 30: For an array with a known target,
 * searching for any element not equal to the target should remain consistent even
 * after repeatedly reversing the array.
 *
 */
TEST_P(BSearchParamTest, MR30) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int non_target_value = target + 1; // Assume that non_target_value does not exist in the array

    /* Get source output */
    bool source_out = bin_search(vec, non_target_value);

    /* Construct follow-up input by reversing the array multiple times */
    vector<int> reversed_vec = vec;
    std::reverse(reversed_vec.begin(), reversed_vec.end());
    std::reverse(reversed_vec.begin(), reversed_vec.end());

    /* Get follow-up output */
    bool follow_out = bin_search(reversed_vec, non_target_value);

    /* Verification */
    EXPECT_EQ(source_out, follow_out); // Searching for a non-existing element should yield the same result
}

/**
 * @brief Metamorphic relation 31: For an array not containing the target,
 * splitting the array into two sub-arrays and performing a binary search should also result in a negative result.
 *
 */
TEST_P(BSearchParamTest, MR31) { // Fixed
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Make sure the size of array is larger than 1 */
    if (vec.size() == 1)
        vec.emplace_back(vec.back() + 1);

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Apply MR only when the target is not found */
    if (!source_out) {
        /* Split the array into two sub-arrays */
        vector<int> sub_vec1(vec.begin(), vec.begin() + vec.size() / 2);
        vector<int> sub_vec2(vec.begin() + vec.size() / 2, vec.end());

        /* Get follow-up outputs */
        bool follow_out1 = bin_search(sub_vec1, target);
        bool follow_out2 = bin_search(sub_vec2, target);

        /* Verification */
        EXPECT_FALSE(follow_out1); // The target should not be found in the first half
        EXPECT_FALSE(follow_out2); // The target should not be found in the second half
    }
}

/**
 * @brief Metamorphic relation 32: Complementing a MR where the array is negated, for an array not including a negative target,
 * negating and sorting the array should also result in a negative find for the positive target.
 *
 */
TEST_P(BSearchParamTest, MR32) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = -input.target; // Use a target value that is not in the array

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (!source_out) {
        /* Construct follow-up input by negating all elements */
        vector<int> negated_vec;
        std::transform(vec.begin(), vec.end(), std::back_inserter(negated_vec), [](int v) { return -v; });
        // Sorting is required as negation changes element order
        std::sort(negated_vec.begin(), negated_vec.end());

        /* Get follow-up output */
        bool follow_out = bin_search(negated_vec, -target);

        /* Verification */
        EXPECT_FALSE(follow_out); // A non-existing negative target should still be non-existent when inverted
    }
}

/**
 * @brief Metamorphic relation 33: Inserting the target multiple times at different locations
 * should not affect the outcome of the binary search if the target was initially found.
 *
 */
TEST_P(BSearchParamTest, MR33) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (source_out) {
        /* Construct follow-up input by inserting the target multiple times */
        vector<int> extended_vec = vec;
        extended_vec.insert(extended_vec.begin() + extended_vec.size() / 3, target);
        extended_vec.insert(extended_vec.begin() + 2 * extended_vec.size() / 3, target);
        sort(extended_vec.begin(), extended_vec.end());

        /* Get follow-up output */
        bool follow_out = bin_search(extended_vec, target);

        /* Verification */
        EXPECT_TRUE(follow_out); // The target should still be detected
    }
}

/**
 * @brief Metamorphic relation 34: If the target is not initially found,
 * ensuring that all array element values are changed to a single constant (not equal to target) should also result in not finding the target.
 *
 */
TEST_P(BSearchParamTest, MR34) { // Fixed
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (!source_out) {
        /* Construct follow-up input */
        vector<int> uniform_vec(vec.size(), vec[0]); // Use any constant value that is not equal to the target

        /* Get follow-up output */
        bool follow_out = bin_search(uniform_vec, target);

        /* Verification */
        EXPECT_FALSE(follow_out); // The target should not be found as it does not match the uniform element value
    }
}

/**
 * @brief Metamorphic relation 35: Changing the target to any value within the range of the array
 * should either give a true (if the chosen value exists) or false (if the chosen value does not exist) regardless of the original outcome.
 *
 */
TEST_P(BSearchParamTest, MR35) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;

    /* Get source output with an arbitrary target */
    int target = vec[vec.size() / 2];
    bool source_out = bin_search(vec, target);

    /* Choose a different target value within the range of the array */
    int new_target = target;
    if (source_out) {
        // Choose a value that is less than the smallest element in the vector
        new_target = *min_element(vec.begin(), vec.end()) - 1;
    } else {
        // Choose a valid existing element
        new_target = vec[vec.size() / 2];
    }

    /* Get follow-up output */
    bool follow_out = bin_search(vec, new_target);

    /* We know new_target should be in the array, as we picked it from there */
    EXPECT_TRUE(follow_out);
}

/**
 * @brief Metamorphic relation 36: If the source array does not contain the target, replacing any single
 * element with the target should result in finding the new target in the array.
 *
 */
TEST_P(BSearchParamTest, MR36) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Apply MR only if the target is not found initially */
    if (!source_out) {
        /* Construct follow-up input by replacing an array element with the target */
        vec[vec.size() / 2] = target;      // Replace the middle element with the target
        std::sort(vec.begin(), vec.end()); // Sort the vector again

        /* Get follow-up output */
        bool follow_out = bin_search(vec, target);

        /* Verification */
        EXPECT_TRUE(follow_out); // The target is now inserted into the vector
    }
}

/**
 * @brief Metamorphic relation 37: Replicating the array into a larger array
 * and searching for the target should give the same result.
 *
 */
TEST_P(BSearchParamTest, MR37) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Construct follow-up input */
    vector<int> larger_vec;
    larger_vec.reserve(3 * vec.size());
    for (int i = 0; i < 3; ++i) {
        larger_vec.insert(larger_vec.end(), vec.begin(), vec.end());
    }

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Get follow-up output */
    bool follow_out = bin_search(larger_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out); // Larger array composed of repeated blocks should give the same result
}

/**
 * @brief Metamorphic relation 38: If the target is not found, inserting a sequence of ascending
 * numbers that does not include the target should still result in the target not being found.
 *
 */
TEST_P(BSearchParamTest, MR38) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (!source_out) {
        /* Construct follow-up input */
        vector<int> extended_vec(vec.begin(), vec.end());
        extended_vec.push_back(target - 2);
        extended_vec.push_back(target - 1);
        std::sort(extended_vec.begin(), extended_vec.end());

        /* Get follow-up output */
        bool follow_out = bin_search(extended_vec, target);

        /* Verification */
        EXPECT_FALSE(follow_out); // The target is still not included in the array
    }
}

/**
 * @brief Metamorphic relation 39: If the target is found, appending a series of elements larger
 * than the target in descending order (which keeps the entire array sorted) should not affect the search result.
 *
 */
TEST_P(BSearchParamTest, MR39) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (source_out) {
        /* Construct follow-up input */
        vector<int> extended_vec(vec.begin(), vec.end());
        int max_elem = *max_element(vec.begin(), vec.end());
        for (int i = 1; i <= 3; ++i) {
            extended_vec.push_back(max_elem + i);
        }

        /* Get follow-up output */
        bool follow_out = bin_search(extended_vec, target);

        /* Verification */
        EXPECT_TRUE(follow_out); // The target should still be found
    }
}

/**
 * @brief Metamorphic relation 40: If the target is found, removing elements from the array
 * without removing the target should still result in finding the target.
 *
 */
TEST_P(BSearchParamTest, MR40) { // Fixed
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Make sure the size of vec is larger than 1 */
    if (vec.size() == 1)
        vec.emplace_back(vec.back() + 1);

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (source_out) {
        /* Construct follow-up input */
        vector<int> reduced_vec = vec;
        if (vec[0] != target) {
            reduced_vec.erase(reduced_vec.begin());
        } else {
            reduced_vec.pop_back();
        }

        /* Get follow-up output */
        bool follow_out = bin_search(reduced_vec, target);

        /* Verification */
        EXPECT_TRUE(follow_out); // The target should still be found
    }
}

/**
 * @brief Metamorphic relation 41: For an array containing only a single distinct value,
 * searching for any other value should consistently yield false.
 *
 */
TEST_P(BSearchParamTest, MR41) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec(10, 5); // Create an array of 10 elements, all with the value of 5.
    int target = 7;         // Choose a target that is not in the array

    /* Try searching for a target in this homogeneous array */
    bool source_out = bin_search(vec, target);

    /* Verification */
    EXPECT_FALSE(source_out); // Target is not present, so it should return false
}

INSTANTIATE_TEST_CASE_P(TrueReturn, BSearchParamTest, testing::ValuesIn(get_tcs_randomly()));