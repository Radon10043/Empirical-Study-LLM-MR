#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <climits>
#include <random>
#include <tuple>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

#define SKIP_CRASH

class BSearchParamTest : public ::testing::TestWithParam<BSearch2Input> {};

/**
 * @brief Metamorphic relation 2: Reversing the array and adjusting the output accordingly.
 *
 */
TEST_P(BSearchParamTest, MR2) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec(vec.rbegin(), vec.rend());
    // The target remains the same, but we need to adjust the expected index
    int expected_follow_out = vec.size() - source_out - 1;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    // If source_out was -1 (target not found), follow_out should also be -1
    if (source_out == -1) {
        EXPECT_EQ(source_out, follow_out);
    } else {
        EXPECT_EQ(expected_follow_out, follow_out);
    }
}

/**
 * @brief Metamorphic relation 3: Inserting a non-existing element should not change the result.
 *
 */
TEST_P(BSearchParamTest, MR3) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    int new_element = INT_MAX; // Use an integer guaranteed not to be in the array
    follow_vec.insert(follow_vec.begin() + follow_vec.size() / 2, new_element);

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    if (source_out == -1) {
        EXPECT_EQ(source_out, follow_out);
    } else {
        EXPECT_EQ(source_out + 1, follow_out);
    }
}

/**
 * @brief Metamorphic relation 4: Doubling (or any multiplier) every element and the target should preserve the relative ordering.
 *
 */
TEST_P(BSearchParamTest, MR4) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input - using 2 as an arbitrary constant multiplier */
    int multiplier = 2;
    vector<int> follow_vec;
    for (auto elem : vec) {
        follow_vec.push_back(elem * multiplier);
    }
    int follow_target = target * multiplier;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/***
 * @brief Metamorphic relation 5: If we remove an element smaller than the target from a sorted array,
 * the position of the target (if it exists) should decrease by 1.
 *
 */
TEST_P(BSearchParamTest, MR5) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Find an element that is smaller than the target */
    int smaller_elem_index = -1;
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] < target) {
            smaller_elem_index = i;
            break;
        }
    }

    /* If a smaller element exists, proceed with MR */
    if (smaller_elem_index != -1) {
        /* Get source output */
        int source_out = bin_search(vec, target);

        /* Construct follow-up input */
        vector<int> follow_vec = vec;
        follow_vec.erase(follow_vec.begin() + smaller_elem_index);

        /* Get follow-up output */
        int follow_out = bin_search(follow_vec, target);

        /* Verification */
        if (source_out != -1) {
            EXPECT_EQ(source_out - 1, follow_out);
        } else {
            EXPECT_EQ(source_out, follow_out);
        }
    }
}

/**
 * @brief Metamorphic relation 6: Incrementing every element by a constant
 * value should not affect the existence of the target in the array.
 *
 */
TEST_P(BSearchParamTest, MR6) { // Fixed
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int increment = 3;
    for (auto &item : vec) {
        item += increment;
    }
    int follow_target = target + increment;

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 7: If the array is sorted and we add a duplicate
 * of the target, the target should still be found, and its position should be either
 * the same or one less than before if the duplicate is added before the target.
 *
 */
TEST_P(BSearchParamTest, MR7) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    if (source_out != -1) {
        // If target exists, insert a duplicate before its position
        vec.insert(vec.begin() + source_out, target);
    } else {
        // If target does not exist, choose a position to insert
        vec.insert(vec.begin() + vec.size() / 2, target);
    }

    /* Get follow-up output */
    int follow_out = bin_search(vec, target);

    /* Verification */
    if (source_out != -1) {
        // If target was found initially, it should still be found.
        EXPECT_TRUE(follow_out == source_out || follow_out == source_out + 1);
    } else {
        // If target was not found initially, it should still not be found.
        EXPECT_EQ(-1, follow_out);
    }
}

/**
 * @brief Metamorphic relation 8: Concatenating a second sorted array that is all larger than
 * the elements of the first array should not change the index of the searched target in the original array.
 *
 */
TEST_P(BSearchParamTest, MR8) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct the second array */
    vector<int> second_vec(vec.size(), vec.back() + 10); // Make sure all elements are greater

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.insert(follow_vec.end(), second_vec.begin(), second_vec.end());

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/***
 * @brief Metamorphic relation 9: Increase the size of the array by adding elements greater
 * than any existing elements - the search result for the original target should not change.
 *
 */
TEST_P(BSearchParamTest, MR9) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Create new elements that are larger than the largest element in the array */
    vector<int> new_elements = {vec.back() + 1, vec.back() + 2};

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.insert(follow_vec.end(), new_elements.begin(), new_elements.end());

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 10: Decrease the size of the array by removing elements that
 * are not equal to the target - the result of the search should only change if the target is
 * no longer in the array.
 *
 */
TEST_P(BSearchParamTest, MR10) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Remove elements different from the target */
    vec.erase(std::remove_if(vec.begin(), vec.end(), [&target](int elem) { return elem != target; }), vec.end());

    /* It's possible that the entire list is removed,
       check if the target existed in the source array */
    auto source_has_target = std::find(input.vec.begin(), input.vec.end(), target) != input.vec.end();

    /* Get follow-up output - search for the target in the modified vector */
    int follow_out = bin_search(vec, target);

    /* Verification */
    // If the target was in the source and follow-up arrays, it should now be at index 0,
    // otherwise the element doesn't exist
    if (source_has_target) {
        EXPECT_EQ(0, follow_out);
    } else {
        EXPECT_EQ(-1, follow_out);
    }
}

/**
 * @brief Metamorphic relation 11: Shifting all elements in the array by a fixed amount -
 * the output index should change only if the target moves in the array or doesn't exist.
 *
 */
TEST_P(BSearchParamTest, MR11) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Compute the amount to shift elements such that the target if present is moved in the array */
    int shift_amount = vec.size() - 1;
    while (shift_amount > 0 && vec[shift_amount] != target) {
        shift_amount--;
    }
    shift_amount = (shift_amount == 0) ? 1 : shift_amount;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input by shifting elements up to the shift amount */
    vector<int> follow_vec;
    std::rotate_copy(vec.begin(), vec.begin() + shift_amount, vec.end(), std::back_inserter(follow_vec));

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    if (source_out == -1) {
        EXPECT_EQ(-1, follow_out);
    } else {
        int expected_index = (source_out - shift_amount + vec.size()) % vec.size();
        EXPECT_EQ(expected_index, follow_out);
    }
}

/**
 * @brief Metamorphic relation 12: Applying an offset to all elements, then searching for a new target
 * value with the same offset applied, should preserve the result of the search.
 *
 */
TEST_P(BSearchParamTest, MR12) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int offset = 5; // The offset we will apply
    for (auto &item : vec) {
        item += offset;
    }
    int new_target = target + offset; // Apply the same offset to the target

    /* Get follow-up output */
    int follow_out = bin_search(vec, new_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 13: Concatenating the same array to itself. The existence of the
 * target in the concatenated array should return the same result as in the original array.
 *
 */
TEST_P(BSearchParamTest, MR13) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec(vec);                                 // Copy the original vector
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.end()); // Concatenate the vector with itself

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    // If the target exists in the source, it should exist in concatenated vector
    if (source_out != -1) {
        EXPECT_NE(-1, follow_out);
    } else {
        EXPECT_EQ(-1, follow_out);
    }
}

/**
 * @brief Metamorphic relation 14: Sorting a possibly unsorted array before using binary search
 * should not affect the correctness of finding an existing target.
 *
 */
TEST_P(BSearchParamTest, MR14) {
    /* Get source and follow-up input */
    BSearch2Input input = GetParam();
    vector<int> source_vec = input.vec;
    int target = input.target;
    vector<int> follow_vec = source_vec;

    /* Sort the follow-up vector, binary search requires sorted input */
    sort(follow_vec.begin(), follow_vec.end());

    /* Get source and follow-up output */
    int source_out = bin_search(source_vec, target);
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    // The target should exist in both or neither
    EXPECT_EQ(source_out != -1, follow_out != -1);

    // If target exists, check if position differs because source might not be initially sorted
    if (source_out != -1 && follow_out != -1) {
        EXPECT_EQ(source_vec[source_out], follow_vec[follow_out]);
    }
}

/**
 * @brief Metamorphic relation 15: Shuffling a non-sorted array should not affect the existence
 * of a target, but the index might change (no guarantee on its consistency).
 *
 */
TEST_P(BSearchParamTest, MR15) {
    /* Get source and follow-up input */
    BSearch2Input input = GetParam();
    vector<int> source_vec = input.vec;
    int target = input.target;
    vector<int> follow_vec = source_vec;

    // Shuffle the follow-up vector
    std::random_shuffle(follow_vec.begin(), follow_vec.end());

    /* Get source and follow-up output */
    int source_out = bin_search(source_vec, target);
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    // The target should exist in both or neither before sorting,
    // but we cannot guarantee the index remains constant
    EXPECT_EQ(source_out != -1, follow_out != -1);
}

/***
 * @brief Metamorphic relation 16: Binary search should not modify the input array.
 *
 */
TEST_P(BSearchParamTest, MR16) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Presume it is sorted
    int target = input.target;

    /* Copy the vector to ensure we can check it wasn't modified */
    vector<int> original_vec = vec;

    /* Execute binary search */
    bin_search(vec, target);

    /* Verification */
    // Verify that the binary search operation has not modified the array
    EXPECT_EQ(vec, original_vec);
}

/**
 * @brief Metamorphic relation 17: Using binary search to find each element in the array
 * should always succeed.
 *
 */
TEST_P(BSearchParamTest, MR17) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Presume it is sorted

    /* Verify that every element can be found */
    for (auto &item : vec) {
        int index = bin_search(vec, item);
        // The found index should match the actual item, hence it should never be -1
        EXPECT_NE(index, -1);
        // Double-check the found item equals the searched item
        EXPECT_EQ(vec[index], item);
    }
}

/**
 * @brief Metamorphic relation 18: If an element is removed from the array, binary search
 * should no longer find it.
 *
 */
TEST_P(BSearchParamTest, MR18) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Presume it is sorted

    if (!vec.empty()) {
        // Remove a random element
        size_t element_to_remove_idx = rand() % vec.size();
        int element_to_remove = vec[element_to_remove_idx];

        vec.erase(vec.begin() + element_to_remove_idx);

        /* Verification */
        // The removed element should not be found
        EXPECT_EQ(bin_search(vec, element_to_remove), -1);
    }
}

/**
 * @brief Metamorphic relation 19: If a non-existent element is searched for in the array, binary search
 * should return -1.
 *
 */
TEST_P(BSearchParamTest, MR19) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Presume it is sorted

    /* Choose a value that does not exist in the array */
    int non_existent_value = *max_element(vec.begin(), vec.end()) + 1;

    /* Verification */
    // The non-existent element should not be found
    EXPECT_EQ(bin_search(vec, non_existent_value), -1);
}

/**
 * @brief Metamorphic relation 20: Swapping two non-target elements in the array should not affect
 * the result of finding the target.
 *
 */
TEST_P(BSearchParamTest, MR20) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Presume it is sorted
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Swap two non-target elements */
    if (vec.size() > 2) {
        for (int i = 0; i < vec.size() - 1; ++i) {
            if (vec[i] != target && vec[i + 1] != target) {
                std::swap(vec[i], vec[i + 1]);
                break;
            }
        }
    }

    /* Get follow-up output */
    int follow_out = bin_search(vec, target);

    /* Verification */
    // The existence of the target in the array should not change
    EXPECT_EQ((source_out != -1), (follow_out != -1));
}

/***
 * @brief Metamorphic relation 21: Searching for a target after inserting a duplicate of the target
 * should return the index of one of the duplicates.
 *
 */
TEST_P(BSearchParamTest, MR21) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Presume it is sorted
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Only proceed if the target is in the source vector */
    if (source_out != -1) {
        /* Insert duplicate of target right after its first occurrence */
        vec.insert(vec.begin() + source_out + 1, target);

        /* Get follow-up output */
        int follow_out = bin_search(vec, target);

        /* Verification */
        // Expect the index to be either the original or the next one
        EXPECT_TRUE(follow_out == source_out || follow_out == source_out + 1);
    }
}

/**
 * @brief Metamorphic relation 22: Concatenating the array with itself in reverse order
 * should maintain the discoverability of the target if it is present.
 *
 */
TEST_P(BSearchParamTest, MR22) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Presume it is sorted
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> reversed_vec(vec.rbegin(), vec.rend());
    vector<int> follow_vec(vec); // Start with the original vector
    follow_vec.insert(follow_vec.end(), reversed_vec.begin(), reversed_vec.end());

    /* Sort follow-up input because binary search requires sorted vectors */
    sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    // If the target was in the source, it should be in the concatenated and re-sorted vector
    EXPECT_EQ((source_out != -1), (follow_out != -1));
    // Since the array is sorted again, and the target exists, it should be found in the correct index
    if (source_out != -1) {
        EXPECT_EQ(target, follow_vec[follow_out]);
    }
}

/**
 * @brief Metamorphic relation 23: Subtracting a common offset from all elements in the array
 * as well as the target should yield the same result as the original search.
 *
 */
TEST_P(BSearchParamTest, MR23) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Presume it is sorted
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int offset = -3; // Apply a negative offset to all elements
    for (auto &item : vec) {
        item += offset;
    }
    int new_target = target + offset;

    /* Get follow-up output */
    int follow_out = bin_search(vec, new_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 24: Replacing all occurrences of the target with a new value and
 * searching for the new value should yield the same result as the original search for the target.
 *
 */
TEST_P(BSearchParamTest, MR24) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Presume it is sorted
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int new_value = vec.back() + 1; // Ensure this value is not already in the vector
    std::replace(vec.begin(), vec.end(), target, new_value);

    /* Get follow-up output for the new value */
    int follow_out = bin_search(vec, new_value);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 25: Inverting the sign of every element in the array and the target
 * should still yield the same search result when searching for the target with the sign inverted.
 *
 */
TEST_P(BSearchParamTest, MR25) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Presume it is sorted
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input by inverting all signs */
    std::transform(vec.begin(), vec.end(), vec.begin(), std::negate<>());
    int new_target = -target; // Invert the sign of the target

    /* Since we inverted all elements, we need to re-sort the array */
    std::sort(vec.begin(), vec.end());

    /* Get follow-up output for the inverted target */
    int follow_out = bin_search(vec, new_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/***
 * @brief Metamorphic relation 26: If the sorted array is split into two halves and the target resides in the
 * first half, then searching for the target in the first half should yield the same result.
 *
 */
TEST_P(BSearchParamTest, MR26) {    // Fixed
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Assume it is sorted
    int target = input.target;

    if (vec.size() < 2) GTEST_SKIP();

    /* Only apply this relation if the array has more than one element */
    if (vec.size() > 1) {
        size_t middle = vec.size() / 2;
        // Split array into two halves
        vector<int> first_half(vec.begin(), vec.begin() + middle);
        vector<int> second_half(vec.begin() + middle, vec.end());

        /* Get source output */
        int source_out = bin_search(vec, target);

        // Check if target is in the first half
        if (source_out && target < vec[middle]) {
            /* Get follow-up output */
            int follow_out = bin_search(first_half, target);

            /* Verification */
            EXPECT_EQ(source_out, follow_out);
        }
    }
}

/**
 * @brief Metamorphic relation 27: If every element in the array is multiplied by a positive constant,
 * and the target is also multiplied by the same constant, then the position of the target (if it exists)
 * should remain unchanged.
 *
 */
TEST_P(BSearchParamTest, MR27) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Assume it is sorted
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int multiplier = 10; // Choose a positive constant for multiplication
    for (auto &item : vec) {
        item *= multiplier;
    }
    int new_target = target * multiplier;

    /* Get follow-up output */
    int follow_out = bin_search(vec, new_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 28: Removing the last element from the array should not affect
 * the result of the search for the target unless the target is that last element.
 *
 */
TEST_P(BSearchParamTest, MR28) {    // Fixed
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Assume it is sorted
    int target = input.target;

    if (vec.size() < 2) GTEST_SKIP();

    /* Save the last element before removal */
    int last_element = vec.back();

    /* Remove the last element */
    vec.pop_back();

    /* Get follow-up output */
    int follow_out = bin_search(vec, target);

    /* Verification */
    if (target == last_element) {
        // If target was the last element, it should no longer be found in the follow-up search.
        EXPECT_EQ(0, follow_out);
    } else {
        // Otherwise, the target's index should not change significantly (-1 or same as before).
        int source_out = bin_search(input.vec, target); // Re-run initial search on the unmodified input for comparison
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic relation 29: Inserting a new minimal element to the array that is smaller than
 * any current element should shift the index of the target (if present) by one.
 *
 */
TEST_P(BSearchParamTest, MR29) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Assume it is sorted
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Only apply this relation if the source_out is not -1 */
    if (source_out != -1) {
        /* Insert a new minimal element which is smaller than the smallest element */
        vec.insert(vec.begin(), vec.front() - 1);

        /* Get follow-up output */
        int follow_out = bin_search(vec, target);

        /* Verification */
        // The index of the target should have shifted by one.
        EXPECT_EQ(source_out + 1, follow_out);
    }
}

/**
 * @brief Metamorphic relation 30: Concatenating an array with itself and then removing the target value should result
 * in the same search result minus the number of removed occurrences if the target was present initially.
 *
 */
TEST_P(BSearchParamTest, MR30) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Assume it is sorted
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    // Count the number of occurrences of the target in the vector
    size_t count = std::count(vec.begin(), vec.end(), target);

    /* Construct follow-up input by concatenating the array with itself */
    vec.insert(vec.end(), input.vec.begin(), input.vec.end());
    // Remove target from concatenated vector
    vec.erase(std::remove(vec.begin(), vec.end(), target), vec.end());

    /* Sort the follow-up vector since it may no longer be sorted after modifications */
    std::sort(vec.begin(), vec.end());

    /* Get follow-up output */
    int follow_out = bin_search(vec, target);

    /* Verification */
    if (count > 0) {
        // If target was in source, its new position should be lower by `count` because `count` instances were removed.
        EXPECT_EQ(source_out - count, follow_out);
    } else {
        // If target was not in the source, it should still not be found.
        EXPECT_EQ(-1, follow_out);
    }
}

/***
 * @brief Metamorphic relation 31: After removing an element greater than the target from a sorted array,
 * the search result index of the target should remain unchanged if the target exists.
 *
 */
TEST_P(BSearchParamTest, MR31) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Presume it is sorted
    int target = input.target;

    if (vec.size() < 2) GTEST_SKIP();

    int source_out = bin_search(vec, target); // Store source output

    // Modify array only if original target is present and if array has an element greater than the target
    if (source_out && vec.back() > target) {
        // Find and remove first element greater than the target
        auto remove_it = std::upper_bound(vec.begin(), vec.end(), target);
        vec.erase(remove_it);

        // Get the new output
        int follow_out = bin_search(vec, target);

        // Verify the output index is unchanged
        EXPECT_EQ(follow_out, source_out);
    }
}

/**
 * @brief Metamorphic relation 32: For a target not present in the array, adding the target to the array,
 * sorting it, and then performing the search should result in finding the newly added target.
 *
 */
TEST_P(BSearchParamTest, MR32) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Presume it is sorted
    int target = input.target;

    int source_out = bin_search(vec, target); // Store source output

    if (source_out == -1) {
        // Add the target to the vector
        vec.push_back(target);

        // Sort the new vector since it's modified
        std::sort(vec.begin(), vec.end());

        // Get the new output
        int follow_out = bin_search(vec, target);

        // Verify that the target is found in the new vector
        EXPECT_NE(follow_out, -1);
        EXPECT_EQ(vec[follow_out], target);
    }
}

/**
 * @brief Metamorphic relation 33: Inverting the order of elements in a sorted array (from ascending to descending)
 * and searching for the target should fail, as binary search assumes ascending order.
 *
 */
TEST_P(BSearchParamTest, MR33) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Presume it is sorted
    int target = input.target;

    // Reverse the vector to make it descending
    std::reverse(vec.begin(), vec.end());

    // Perform the binary search on the reversed vector
    int follow_out = bin_search(vec, target);

    // Verify that the binary search fails to find the target, as the order is not ascending
    EXPECT_EQ(follow_out, -1);
}

/**
 * @brief Metamorphic relation 34: Searching for the first element and the last element in a sorted array
 * should always give indices 0 and size-1, respectively.
 *
 */
TEST_P(BSearchParamTest, MR34) {
    /* Get source input */
    BSearch2Input input = GetParam();
    if (input.vec.empty())
        return;

    vector<int> vec = input.vec; // Presume it is sorted

    // Search for the first and last elements
    int first_elem = vec.front();
    int last_elem = vec.back();

    int first_elem_index = bin_search(vec, first_elem);
    int last_elem_index = bin_search(vec, last_elem);

    // Verify indices of first and last elements are correct
    EXPECT_EQ(first_elem_index, 0);
    EXPECT_EQ(last_elem_index, vec.size() - 1);
}

/**
 * @brief Metamorphic relation 35: Adding a sequence of elements greater than the current greatest element
 * in the array should not affect the search result for the existing target.
 *
 */
TEST_P(BSearchParamTest, MR35) {
    /* Get source input */
    BSearch2Input input = GetParam();
    if (input.vec.empty())
        return;

    vector<int> vec = input.vec; // Presume it is sorted
    int target = input.target;

    int source_out = bin_search(vec, target); // Store source output

    // Create a sequence of elements larger than the last element of vec
    int max_elem = vec.back();
    vector<int> new_elems = {max_elem + 1, max_elem + 2, max_elem + 3};

    // Add new elements to the vector
    vec.insert(vec.end(), new_elems.begin(), new_elems.end());

    // Perform the binary search on the new vector
    int follow_out = bin_search(vec, target);

    // Verify the binary search output is the same
    EXPECT_EQ(follow_out, source_out);
}

/***
 * @brief Metamorphic relation 36: Creating a prefixed array by adding a sequence less than the minimum element,
 * should preserve the result of the search for the existing elements.
 *
 */
TEST_P(BSearchParamTest, MR36) {
    /* Get source input */
    BSearch2Input input = GetParam();
    if (input.vec.empty())
        return; // Skip empty vector situations

    vector<int> vec = input.vec; // Presume it is sorted
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Create prefix that is strictly less than the smallest element in the vector */
    vector<int> prefix = {vec.front() - 3, vec.front() - 2, vec.front() - 1};

    /* Add prefix to the beginning of the vector */
    vec.insert(vec.begin(), prefix.begin(), prefix.end());

    /* Get follow-up output */
    int follow_out = bin_search(vec, target);

    /* Verification */
    if (source_out == -1) {
        // The result should still be -1 if the target was not in the original vector
        EXPECT_EQ(follow_out, source_out);
    } else {
        // The result should now be the original index plus the prefix size
        EXPECT_EQ(follow_out, source_out + prefix.size());
    }
}

/**
 * @brief Metamorphic relation 37: Performing binary search on alternating elements of the array
 * should still find the target if it is at an even index in the original array.
 *
 */
TEST_P(BSearchParamTest, MR37) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Presume it is sorted
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Create a vector of alternating elements from the original */
    vector<int> alt_vec;
    for (size_t i = 0; i < vec.size(); i += 2) {
        alt_vec.push_back(vec[i]);
    }

    /* Get follow-up output */
    int follow_out = bin_search(alt_vec, target);

    /* Verification */
    if (source_out != -1 && source_out % 2 == 0) {
        // Adjust the expected index for the target found at an even source index
        EXPECT_EQ(follow_out, source_out / 2);
    } else {
        // If target was not found or was at an odd index, expect -1
        EXPECT_EQ(follow_out, -1);
    }
}

/**
 * @brief Metamorphic relation 38: Expanding the range of elements between the minimum and maximum of the array,
 * and searching for the target with adjusted index, should yield the correct result.
 *
 */
TEST_P(BSearchParamTest, MR38) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Presume it is sorted
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Expand the vector range by adding intermediate values */
    vector<int> expanded_vec;
    for (int i = 0; i < vec.size() - 1; ++i) {
        expanded_vec.push_back(vec[i]);
        expanded_vec.push_back((vec[i] + vec[i + 1]) / 2); // Mid-value
    }
    expanded_vec.push_back(vec.back());

    /* Get follow-up output */
    int follow_out = bin_search(expanded_vec, target);

    /* Verification */
    if (source_out != -1) {
        // The result should now be twice the original index since we inserted elements in-between
        EXPECT_EQ(follow_out, source_out * 2);
    } else {
        // If target was not found in the original vector, it should not be found now
        EXPECT_EQ(follow_out, -1);
    }
}

/**
 * @brief Metamorphic relation 39: Shuffling even-indexed elements while maintaining the odd-indexed ones
 * should not affect the result of the binary search for targets at odd indices.
 *
 */
TEST_P(BSearchParamTest, MR39) {
    /* Get source and follow-up input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Assume it is sorted

    /* Shuffle even-indexed elements */
    for (size_t i = 0; i < vec.size(); i += 2) {
        if (i + 2 < vec.size()) {
            std::swap(vec[i], vec[i + 2]);
        }
    }

    /* Perform a search only for odd-indexed targets */
    for (size_t i = 1; i < vec.size(); i += 2) {
        int follow_out = bin_search(vec, vec[i]);
        // Verify that the target is found at the same odd index i
        EXPECT_EQ(follow_out, i);
    }
}

/**
 * @brief Metamorphic relation 40: Searching for each target after cyclically shifting the array k steps
 * should give a result that reflects the shift.
 *
 */
TEST_P(BSearchParamTest, MR40) {    // Fixed
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Presume it is sorted

    /* Get output for each element when array is cyclically shifted */
    int k = 3; // Shift amount
    vector<int> shifted_vec(vec.size());
    // Perform the cyclic shift by k
    std::rotate_copy(vec.begin(), vec.begin() + k, vec.end(), shifted_vec.begin());

    // Sort the shifted vec because binary search requires sorted array
    std::sort(shifted_vec.begin(), shifted_vec.end());

    // Search for each original element in the shifted and sorted array
    for (auto &target : vec) {
        int original_index = bin_search(vec, target);        // Index in original array
        int shifted_index = bin_search(shifted_vec, target); // Index in shifted array

        if (original_index != -1) {
            // Calculate expected index after shift
            int expected_index = (original_index + vec.size() - k) % vec.size();
            EXPECT_EQ(shifted_index, expected_index);
        }
    }
}

/***
 * @brief Metamorphic relation 41: If the target is not in the original array, and we insert another
 * element that is also not in the original array, the result of searching for either of the two should be -1.
 *
 */
TEST_P(BSearchParamTest, MR41) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec; // Presume it is sorted
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Insert an element that is not in the vector */
    int new_element = *std::max_element(vec.begin(), vec.end()) + 1; // Element larger than any in the array
    vec.push_back(new_element);
    std::sort(vec.begin(), vec.end()); // Sort the new vector

    /* Get follow-up output for both original and new elements */
    int follow_out_target = bin_search(vec, target);
    int follow_out_new_element = bin_search(vec, new_element);

    /* Verification */
    // Since neither original target nor new element was in the original array, the search should fail for both
    if (source_out == -1) {
        EXPECT_EQ(follow_out_target, -1);
        EXPECT_EQ(follow_out_new_element, -1);
    }
}

INSTANTIATE_TEST_CASE_P(TrueReturn, BSearchParamTest, testing::ValuesIn(get_tcs_randomly()));