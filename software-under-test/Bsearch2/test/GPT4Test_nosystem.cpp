#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <random>
#include <tuple>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

#define SKIP_CRASH

class BSearchParamTest : public ::testing::TestWithParam<BSearch2Input> {};

/**
 * @brief Metamorphic relation 2: Reversing the order of the array and searching for a number should yield the same result provided the number is transformed
 * appropriately.
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
    vector<int> follow_vec = vec;
    reverse(follow_vec.begin(), follow_vec.end());
    int follow_target = (vec.size() - 1) - distance(vec.begin(), find(vec.begin(), vec.end(), target));

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 3: Appending or prepending elements to the vector which are outside the current search range should not affect the outcome.
 *
 */
TEST_P(BSearchParamTest, MR3) { // Fixed
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input by appending elements greater than the maximum element */
    vector<int> append_vec(vec);
    append_vec.insert(append_vec.end(), {*max_element(vec.begin(), vec.end()) + 1, *max_element(vec.begin(), vec.end()) + 2});

    /* Get follow-up output for appended vector */
    int follow_out_appended = bin_search(append_vec, target);

    /* Construct follow-up input by prepending elements less than the minimum element */
    vector<int> prepend_vec(vec);
    prepend_vec.insert(prepend_vec.begin(), {*min_element(vec.begin(), vec.end()) - 2, *min_element(vec.begin(), vec.end()) - 1});

    /* Get follow-up output for prepended vector */
    int follow_out_prepended = bin_search(prepend_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out_appended);
    EXPECT_EQ(source_out, follow_out_prepended);
}

/**
 * @brief Metamorphic relation 4: If the function returns true for a certain value, searching for the same value after inserting it multiple times should also
 * return true.
 *
 */
TEST_P(BSearchParamTest, MR4) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);
    if (source_out) { // Proceed only if the target is found in the original vector
        /* Construct follow-up input */
        vector<int> follow_vec(vec);
        follow_vec.insert(follow_vec.end(), {target, target, target});
        sort(follow_vec.begin(), follow_vec.end());

        /* Get follow-up output */
        int follow_out = bin_search(follow_vec, target);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic relation 5: Removing any occurrence of the target number from the vector should cause the search function to return false if it originally
 * returned true.
 *
 */
TEST_P(BSearchParamTest, MR5) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);
    if (source_out) { // Proceed only if the target is found in the original vector
        /* Construct follow-up input */
        vector<int> follow_vec(vec);
        follow_vec.erase(remove(follow_vec.begin(), follow_vec.end(), target), follow_vec.end());

        /* Get follow-up output */
        int follow_out = bin_search(follow_vec, target);

        /* Verification */
        EXPECT_FALSE(follow_out);
    }
}

/**
 * @brief Metamorphic relation 6: If an element is found at position `i` in the sorted array, searching for the same value after cyclically shifting the array
 * should find the element at a different position but still return true.
 *
 */
TEST_P(BSearchParamTest, MR6) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    if (source_out) { // Proceed only if the target is found in the original vector
        /* Construct follow-up input */
        vector<int> follow_vec(vec);
        rotate(follow_vec.begin(), follow_vec.begin() + 1, follow_vec.end()); // Shift right by one

        /* Get follow-up output */
        int follow_out = bin_search(follow_vec, target);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic relation 7: Doubling the size of the vector by repeating its elements, while keeping it sorted, should not change the result of the
 * search.
 *
 */
TEST_P(BSearchParamTest, MR7) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input by duplicating the vector and merging */
    vector<int> follow_vec(vec);
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.end());
    sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 8: Incrementing each element by a constant while incrementing the target by the same constant should not change the outcome.
 *
 */
TEST_P(BSearchParamTest, MR8) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input by incrementing each element and target by the same constant */
    int increment = 10; // the constant value to add
    vector<int> follow_vec = vec;
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [increment](int val) { return val + increment; });
    int follow_target = target + increment;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 9: Splitting the vector into two halves and searching both should yield true if and only if the search on the whole vector yields
 * true.
 *
 */
TEST_P(BSearchParamTest, MR9) { // Fixed
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    if (vec.size() < 2) GTEST_SKIP();

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Split the vector into two halves */
    vector<int> first_half(vec.begin(), vec.begin() + vec.size() / 2);
    vector<int> second_half(vec.begin() + vec.size() / 2, vec.end());

    /* Get follow-up output by searching both halves */
    bool found_in_first_half = bin_search(first_half, target);
    bool found_in_second_half = bin_search(second_half, target);

    /* Verification */
    EXPECT_EQ(source_out, found_in_first_half || found_in_second_half);
}

/**
 * @brief Metamorphic relation 10: Shuffling the vector and then re-sorting it should yield the same search outcome.
 *
 */
TEST_P(BSearchParamTest, MR10) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Shuffling and sorting vector */
    random_device rd;
    mt19937 g(rd());
    vector<int> shuffled_vec(vec);
    shuffle(shuffled_vec.begin(), shuffled_vec.end(), g); // Shuffle the vector
    sort(shuffled_vec.begin(), shuffled_vec.end());       // Sort it back

    /* Get follow-up output */
    int follow_out = bin_search(shuffled_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 11: Searching for an element not in the initial vector in an extended vector, where the new elements are all greater than the
 * target, should yield the same result.
 *
 */
TEST_P(BSearchParamTest, MR11) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Make sure the target is not already in the initial vector */
    if (!bin_search(vec, target)) {

        /* Get source output */
        int source_out = bin_search(vec, target); // Should be false

        /* Extend the vector with elements greater than the target */
        vector<int> follow_vec(vec);
        follow_vec.push_back(target + 1);
        follow_vec.push_back(target + 2);

        /* Get follow-up output */
        int follow_out = bin_search(follow_vec, target);

        /* Verification */
        EXPECT_EQ(source_out, follow_out); // both should be false
    }
}

/**
 * @brief Metamorphic relation 12: Inverting the elements of the vector (multiplying by -1), including the target, should yield the same outcome if the vector
 * is re-sorted.
 *
 */
TEST_P(BSearchParamTest, MR12) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct inverted follow-up input */
    vector<int> inverted_vec = vec;
    std::transform(inverted_vec.begin(), inverted_vec.end(), inverted_vec.begin(), [](int val) { return -val; });
    sort(inverted_vec.begin(), inverted_vec.end()); // Ensure the vector is sorted after inversion
    int inverted_target = -target;

    /* Get inverted follow-up output */
    bool inverted_follow_out = bin_search(inverted_vec, inverted_target);

    /* Verification */
    EXPECT_EQ(source_out, inverted_follow_out);
}

/**
 * @brief Metamorphic relation 13: Increasing the range of numbers in the vector uniformly should not affect the search outcome.
 *
 */
TEST_P(BSearchParamTest, MR13) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct expanded follow-up input */
    vector<int> expanded_vec(vec.size() * 2);
    std::transform(vec.begin(), vec.end(), expanded_vec.begin(), [extension = vec.size()](int val) { return val * extension; });

    /* Ensure target has the appropriate expansion */
    int expanded_target = target * static_cast<int>(vec.size());

    /* Get expanded follow-up output */
    bool expanded_follow_out = bin_search(expanded_vec, expanded_target);

    /* Verification */
    EXPECT_EQ(source_out, expanded_follow_out);
}

/**
 * @brief Metamorphic relation 14: If searching for `x` yields true, searching for any value less than `x` should not yield true unless that value is also
 * present in the array.
 *
 */
TEST_P(BSearchParamTest, MR14) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Check if the target is in the vector */
    if (bin_search(vec, target)) {
        bool found = false;
        for (const int &elem : vec) {
            if (elem < target) {
                found = bin_search(vec, elem);
                /* Verification for each elem < target */
                EXPECT_TRUE(found);
            }
        }
        /* Ensure at least one element less than target was tested */
        EXPECT_TRUE(found);
    }
}

/**
 * @brief Metamorphic relation 15: Searching for a target twice, after ensuring no modification to the vector or target, should yield the same result.
 *
 */
TEST_P(BSearchParamTest, MR15) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get outcome of first search */
    bool first_search_outcome = bin_search(vec, target);

    /* Get outcome of second search */
    bool second_search_outcome = bin_search(vec, target);

    /* Verification */
    EXPECT_EQ(first_search_outcome, second_search_outcome);
}

/**
 * @brief Metamorphic relation 16: Inserting an element greater than the search target at any position should not change the outcome of the search for the
 * target.
 *
 */
TEST_P(BSearchParamTest, MR16) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Find a value greater than the target, which is not in the vector */
    int max_value = *max_element(vec.begin(), vec.end()) + 1;
    while (find(vec.begin(), vec.end(), max_value) != vec.end()) {
        max_value++;
    }

    /* Construct follow-up input by inserting the new element at a random position */
    vector<int> follow_vec(vec);
    std::mt19937 g(std::random_device{}());
    std::uniform_int_distribution<size_t> distr(0, follow_vec.size());
    follow_vec.insert(follow_vec.begin() + distr(g), max_value);

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 17: Changing the order of the elements without modifying their values should not change the search outcome.
 *
 */
TEST_P(BSearchParamTest, MR17) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Shuffle the vector without changing elements' values */
    std::mt19937 g(std::random_device{}());
    shuffle(vec.begin(), vec.end(), g);

    /* Now sort the vector to restore property of binary search */
    sort(vec.begin(), vec.end());

    /* Get shuffled-then-sorted vector output */
    bool shuffled_sorted_out = bin_search(vec, target);

    /* Verification */
    EXPECT_EQ(source_out, shuffled_sorted_out);
}

/**
 * @brief Metamorphic relation 18: Searching for the target after replacing an element that is not the target should not change the outcome.
 *
 */
TEST_P(BSearchParamTest, MR18) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Make sure the target is in the vector */
    if (find(vec.begin(), vec.end(), target) != vec.end()) {
        /* Get source output */
        bool source_out = bin_search(vec, target);

        /* Replace a non-target element with a new value and sort */
        for (auto &item : vec) {
            if (item != target) {
                item = *max_element(vec.begin(), vec.end()) + 1; // Guarantee the new value is not in the original vector
                break;                                           // Only replace one element
            }
        }
        sort(vec.begin(), vec.end()); // Ensure the vector remains valid for the binary search

        /* Get follow-up output */
        bool follow_out = bin_search(vec, target);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic relation 19: Searching for an element at the boundary (start or end) of the vector should have a deterministic outcome.
 *
 */
TEST_P(BSearchParamTest, MR19) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;

    /* Search for elements at the boundaries */
    int start_elem = vec.front();
    int end_elem = vec.back();

    /* Get outcomes */
    bool start_elem_found = bin_search(vec, start_elem);
    bool end_elem_found = bin_search(vec, end_elem);

    /* Verification */
    EXPECT_TRUE(start_elem_found);
    EXPECT_TRUE(end_elem_found);
}

/**
 * @brief Metamorphic relation 20: Searching for a value between two adjacent elements that are not the target should return false.
 *
 */
TEST_P(BSearchParamTest, MR20) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Ensure target is not on the edges and there are at least 2 elements */
    if (vec.size() > 1 && target != vec.front() && target != vec.back()) {
        /* Start from the second element and find two consecutive elements not equal to the target */
        for (size_t i = 1; i < vec.size(); ++i) {
            if (vec[i - 1] != target && vec[i] != target && vec[i - 1] < target && vec[i] > target) {
                /* Check if searching for the target returns false as expected */
                bool result = bin_search(vec, target);
                EXPECT_FALSE(result);
                break;
            }
        }
    }
}

/**
 * @brief Metamorphic relation 21: Searching for a nonexistent element that is not equal to any of the existing elements should return false.
 *
 */
TEST_P(BSearchParamTest, MR21) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;

    /* Choose a value that is not in the vector */
    int non_existent_value = *max_element(vec.begin(), vec.end()) + 1;

    /* Search for the non-existent value */
    bool result = bin_search(vec, non_existent_value);

    /* Verification */
    EXPECT_FALSE(result);
}

/**
 * @brief Metamorphic relation 22: Searching for a known interior element before and after shuffling should yield the same result.
 *
 */
TEST_P(BSearchParamTest, MR22) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec_original = input.vec;

    // Ensure there's at least one interior element
    if (vec_original.size() > 2) {
        /* Get an interior element (not the first or last) */
        int interior_elem_index = vec_original.size() / 2; // Middle for simplicity
        int target = vec_original[interior_elem_index];

        /* Get output before shuffling */
        bool before_shuffle_out = bin_search(vec_original, target);

        /* Shuffle and sort the vector */
        vector<int> vec_shuffled = vec_original;
        std::random_shuffle(vec_shuffled.begin(), vec_shuffled.end());
        std::sort(vec_shuffled.begin(), vec_shuffled.end());

        /* Get output after shuffling */
        bool after_shuffle_out = bin_search(vec_shuffled, target);

        /* Verification */
        EXPECT_EQ(before_shuffle_out, after_shuffle_out);
    } else {
        GTEST_SKIP() << "Vector too small to have interior elements";
    }
}

/**
 * @brief Metamorphic relation 23: If the search for an element is true, removing all elements equal to the search element should cause the search to fail.
 *
 */
TEST_P(BSearchParamTest, MR23) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Original search */
    bool original_search_out = bin_search(vec, target);

    if (original_search_out) {
        /* Remove all instances of the search element */
        vec.erase(std::remove(vec.begin(), vec.end(), target), vec.end());

        /* Attempt to find removed element */
        bool after_removal_out = bin_search(vec, target);

        /* Verify the element cannot be found after removal */
        EXPECT_FALSE(after_removal_out);
    } else {
        GTEST_SKIP() << "Element not found in the original search, can't apply relation";
    }
}

/**
 * @brief Metamorphic relation 24: If the search for an element is true, replacing a random different element with the search element should still yield true.
 *
 */
TEST_P(BSearchParamTest, MR24) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Original search */
    bool original_search_out = bin_search(vec, target);

    if (original_search_out) {
        std::random_device rd;
        std::mt19937 g(rd());

        /* Choose a random index that does not contain the search element */
        std::uniform_int_distribution<> dist(0, vec.size() - 1);
        auto rng = std::default_random_engine{};
        int random_index;
        do {
            random_index = dist(g);
        } while (vec[random_index] == target);

        /* Replace a different element with the target */
        vec[random_index] = target;
        /* Sort the vector again as the change may have unsorted it */
        std::sort(vec.begin(), vec.end());

        /* Search after replacement */
        bool after_replacement_out = bin_search(vec, target);

        /* Verify the element can still be found after replacement */
        EXPECT_TRUE(after_replacement_out);
    } else {
        GTEST_SKIP() << "Element not found in the original search, can't apply relation";
    }
}

/**
 * @brief Metamorphic relation 25: Searching for the same value with different vector sizes should yield the same result if the value is present.
 *
 */
TEST_P(BSearchParamTest, MR25) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Search in the original vector */
    bool original_search_outcome = bin_search(vec, target);

    /* Make sure the target value is in the original vector to apply this relation */
    if (original_search_outcome) {
        /* Construct a larger vector by duplicating elements but excluding the target value */
        vector<int> expanded_vec = vec;
        expanded_vec.erase(remove(expanded_vec.begin(), expanded_vec.end(), target), expanded_vec.end());
        expanded_vec.insert(expanded_vec.end(), vec.begin(), vec.end());
        sort(expanded_vec.begin(), expanded_vec.end());

        /* Search in the expanded vector */
        bool expanded_search_outcome = bin_search(expanded_vec, target);

        /* Verification */
        EXPECT_EQ(original_search_outcome, expanded_search_outcome);
    } else {
        GTEST_SKIP() << "Target value is not in the original vector; cannot apply this relation.";
    }
}

/**
 * @brief Metamorphic relation 26: If the search target is the minimum or maximum value of the vector, adding duplicates of this value should not change the
 * search outcome.
 *
 */
TEST_P(BSearchParamTest, MR26) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Search for target */
    bool original_search_outcome = bin_search(vec, target);

    /* Check if the target is the min or max value of the vector */
    bool is_min_or_max = (target == *min_element(vec.begin(), vec.end())) || (target == *max_element(vec.begin(), vec.end()));

    if (original_search_outcome && is_min_or_max) {
        /* Add duplicates of the target value */
        vec.insert(vec.end(), {target, target, target});
        sort(vec.begin(), vec.end()); // Sort to maintain the precondition for binary search

        /* Search in the modified vector */
        bool modified_search_outcome = bin_search(vec, target);

        /* Verification */
        EXPECT_EQ(original_search_outcome, modified_search_outcome);
    }
}

/**
 * @brief Metamorphic relation 27: Searching for a value not present in the original vector within a subset of the original vector should also yield false.
 *
 */
TEST_P(BSearchParamTest, MR27) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = *max_element(vec.begin(), vec.end()) + 1; // Choose a value not in the vector

    /* Make sure there are at least two elements for a proper subset */
    if (vec.size() > 1) {
        /* Search in the original — full — vector */
        bool original_search_outcome = bin_search(vec, target);

        /* Create a subset vector */
        vector<int> subset_vec(vec.begin(), vec.begin() + vec.size() / 2);

        /* Search in the subset vector */
        bool subset_search_outcome = bin_search(subset_vec, target);

        /* Verification */
        EXPECT_EQ(original_search_outcome, subset_search_outcome);
    } else {
        GTEST_SKIP() << "Not enough elements in the vector to create a proper subset.";
    }
}

/**
 * @brief Metamorphic relation 28: Concatenating two sorted vectors containing the search target should not change the result of the search.
 *
 */
TEST_P(BSearchParamTest, MR28) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec_original = input.vec;
    int target = input.target;

    /* Ensure the target is in the original vector */
    if (bin_search(vec_original, target)) {
        /* Concatenate the original vector to itself */
        vector<int> vec_doubled(vec_original.size() * 2);
        merge(vec_original.begin(), vec_original.end(), vec_original.begin(), vec_original.end(), vec_doubled.begin());

        /* Search for the target in the concatenated vector */
        bool doubled_search_outcome = bin_search(vec_doubled, target);

        /* Verification */
        EXPECT_TRUE(doubled_search_outcome);
    } else {
        GTEST_SKIP() << "The target is not present in the original vector, relation does not apply.";
    }
}

/**
 * @brief Metamorphic relation 29: Searching within a prefix or suffix of the vector containing the target should yield true.
 *
 */
TEST_P(BSearchParamTest, MR29) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec_original = input.vec;
    int target = input.target;

    /* Make sure the target value is present */
    if (bin_search(vec_original, target)) {
        /* Find the position of the target and create prefix/suffix vectors */
        auto it = find(vec_original.begin(), vec_original.end(), target);
        if (it != vec_original.end()) {
            size_t index = distance(vec_original.begin(), it);

            /* Prefix vector */
            vector<int> vec_prefix(vec_original.begin(), vec_original.begin() + index + 1);
            bool prefix_search_outcome = bin_search(vec_prefix, target);

            /* Suffix vector */
            vector<int> vec_suffix(vec_original.begin() + index, vec_original.end());
            bool suffix_search_outcome = bin_search(vec_suffix, target);

            /* Verification for both prefix and suffix */
            EXPECT_TRUE(prefix_search_outcome);
            EXPECT_TRUE(suffix_search_outcome);
        }
    }
}

/**
 * @brief Metamorphic relation 30: Multiplying each element by a negative constant should maintain the result of the search after re-sorting the vector.
 *
 */
TEST_P(BSearchParamTest, MR30) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_outcome = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = -3; // Negative multiplier
    vector<int> follow_vec = vec;
    for (auto &val : follow_vec) {
        val *= constant;
    }
    sort(follow_vec.begin(), follow_vec.end()); // Sort to maintain binary search pre-condition
    int follow_target = target * constant;      // The target also needs to be transformed

    /* Get follow-up output */
    bool follow_outcome = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_outcome, follow_outcome);
}

/**
 * @brief Metamorphic relation 31: For every even positive number in the search range, if the search yields true, dividing it by 2 should also yield true.
 *
 */
TEST_P(BSearchParamTest, MR31) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int even_target = input.target;

    // Adjust target to an even number if necessary
    if (even_target % 2 != 0) {
        even_target++;
    }

    // Check if the even_target is present
    bool even_search_outcome = bin_search(vec, even_target);

    if (even_search_outcome) {
        // Now, search for half that value
        int half_even_target = even_target / 2;
        bool half_even_search_outcome = bin_search(vec, half_even_target);

        // Verification
        EXPECT_TRUE(half_even_search_outcome);
    } else {
        GTEST_SKIP() << "The adjusted even target is not present in the original vector, relation does not apply.";
    }
}

/**
 * @brief Metamorphic relation 32: If the search yields false for a target, doubling the target and repeating the search should yield false, assuming there's no
 * element twice the target in the vector.
 *
 */
TEST_P(BSearchParamTest, MR32) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Search for the target in the vector
    bool initial_search_outcome = bin_search(vec, target);

    if (!initial_search_outcome) {
        // Double the target
        int double_target = target * 2;

        // Check there's no element of double the target value
        if (find(vec.begin(), vec.end(), double_target) == vec.end()) {
            // Search for the double target
            bool double_search_outcome = bin_search(vec, double_target);

            // Verification
            EXPECT_FALSE(double_search_outcome);
        } else {
            GTEST_SKIP() << "The vector contains an element that is double the target, relation does not apply.";
        }
    } else {
        GTEST_SKIP() << "The target is present in the original vector, relation does not apply.";
    }
}

/**
 * @brief Metamorphic relation 33: For every pair of consecutive elements in the vector, searching for a target between them should yield false.
 *
 */
TEST_P(BSearchParamTest, MR33) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;

    for (size_t i = 0; i < vec.size() - 1; ++i) {
        // Choose a value between the two consecutive elements
        int in_between_target = vec[i] + (vec[i + 1] - vec[i]) / 2;

        // Ensure the in-between value is not equal to either of the consecutive elements
        if (in_between_target != vec[i] && in_between_target != vec[i + 1]) {
            // Search for the in-between target
            bool in_between_search_outcome = bin_search(vec, in_between_target);

            // Verification that the in-between value should not be found
            EXPECT_FALSE(in_between_search_outcome);
        }
    }
}

/**
 * @brief Metamorphic relation 34: Concatenating a sorted vector with a shifted copy of itself should retain the search outcome for the original vector
 * elements.
 *
 */
TEST_P(BSearchParamTest, MR34) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Verify the target exists
    if (bin_search(vec, target)) {
        // Shift copy of itself by adding an offset (greater than max element)
        int offset = *max_element(vec.begin(), vec.end()) + 1;
        vector<int> vec_shifted(vec.size());
        transform(vec.begin(), vec.end(), vec_shifted.begin(), [offset](int v) { return v + offset; });

        // Concatenate
        vector<int> concatenated_vector = vec;
        concatenated_vector.insert(concatenated_vector.end(), vec_shifted.begin(), vec_shifted.end());
        sort(concatenated_vector.begin(), concatenated_vector.end());

        // Search for the target in concatenated vector
        bool concatenated_search_outcome = bin_search(concatenated_vector, target);

        // Verification
        EXPECT_TRUE(concatenated_search_outcome);
    } else {
        GTEST_SKIP() << "Target is not present in the original vector, relation does not apply.";
    }
}

/**
 * @brief Metamorphic relation 35: The number of times a target appears in the vector should not change the outcome of the search as long as the target is
 * present.
 *
 */
TEST_P(BSearchParamTest, MR35) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Make sure the target exists in the original vector
    if (bin_search(vec, target)) {
        // Count the occurrences of the target
        int initial_count = count(vec.begin(), vec.end(), target);

        // Multiply occurrences of target in vector
        vec.insert(vec.end(), initial_count, target);
        sort(vec.begin(), vec.end()); // Maintain sorted order

        // Search for target in modified vector
        bool search_outcome_in_modified_vector = bin_search(vec, target);

        // Verification
        EXPECT_TRUE(search_outcome_in_modified_vector);
    } else {
        GTEST_SKIP() << "Target is not present in the original vector, relation does not apply.";
    }
}

/**
 * @brief Metamorphic relation 36: When a range of values is added to the vector that does not include the target, the search outcome should not change.
 *
 */
TEST_P(BSearchParamTest, MR36) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source outcome
    bool source_outcome = bin_search(vec, target);

    // Find a range of values that are not in the vector
    int new_value_1 = *max_element(vec.begin(), vec.end()) + 1;
    int new_value_2 = new_value_1 + 1;
    if (!(new_value_1 == target || new_value_2 == target)) {
        // Insert the new values
        vec.push_back(new_value_1);
        vec.push_back(new_value_2);
        sort(vec.begin(), vec.end()); // Keep the vector sorted

        // Perform the search again
        bool modified_outcome = bin_search(vec, target);

        // Verification
        EXPECT_EQ(source_outcome, modified_outcome);
    } else {
        GTEST_SKIP() << "Generated values clash with the target, relation does not apply.";
    }
}

/**
 * @brief Metamorphic relation 37: If searching for the target yields false, inverting the vector elements should also yield false for inverted target value.
 *
 */
TEST_P(BSearchParamTest, MR37) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Ensure the target is not found in the original search
    if (!bin_search(vec, target)) {
        // Invert each element and the target
        std::transform(vec.begin(), vec.end(), vec.begin(), [](int x) { return -x; });
        sort(vec.begin(), vec.end()); // The vector must be sorted for binary search to work correctly
        int inverted_target = -target;

        // Perform the search in the inverted vector
        bool inverted_search_outcome = bin_search(vec, inverted_target);

        // Verification
        EXPECT_FALSE(inverted_search_outcome);
    }
}

/**
 * @brief Metamorphic relation 38: Searching for an element that is not the maximum value plus one should return false, provided vector is not modified.
 *
 */
TEST_P(BSearchParamTest, MR38) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;

    // Search for max value + 1
    int beyond_max_target = *max_element(vec.begin(), vec.end()) + 1;
    bool beyond_max_search_outcome = bin_search(vec, beyond_max_target);

    // Verification
    EXPECT_FALSE(beyond_max_search_outcome);
}

/**
 * @brief Metamorphic relation 39: If the search target exists at least once, then interleaving the vector with any distinct element should still yield true for
 * the search target.
 *
 */
TEST_P(BSearchParamTest, MR39) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    if (bin_search(vec, target)) {
        // Choose a value that does not exist in the vector
        int distinct_value = *max_element(vec.begin(), vec.end()) + 2;

        // Interleave `distinct_value` between elements of the vector
        auto it = vec.begin();
        while (it != vec.end()) {
            it = vec.insert(++it, distinct_value);
            if (++it == vec.end())
                break;
        }

        // Perform the search
        bool interleaved_search_outcome = bin_search(vec, target);

        // Verification
        EXPECT_TRUE(interleaved_search_outcome);
    } else {
        GTEST_SKIP() << "Target is not in the original vector, relation does not apply.";
    }
}

/**
 * @brief Metamorphic relation 40: Searching for a target immediately after an unsuccessful search for a different value should yield the same result as the
 * initial search for the target.
 *
 */
TEST_P(BSearchParamTest, MR40) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Known value not found
    int not_found_value = *max_element(vec.begin(), vec.end()) + 1;

    // Ensure the value is not found
    EXPECT_FALSE(bin_search(vec, not_found_value));

    // Search for the original target
    bool original_search_outcome = bin_search(vec, target);
    // Search for the target again immediately
    bool repeated_search_outcome = bin_search(vec, target);

    // Verification that the result is consistent
    EXPECT_EQ(original_search_outcome, repeated_search_outcome);
}

/**
 * @brief Metamorphic relation 41: If the vector elements and target are positive, multiplying them by -1 and sorting should yield the opposite result only if
 * the target was not present initially.
 *
 */
TEST_P(BSearchParamTest, MR41) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Check if initial target is positive and not present in the vector
    bool target_positive_and_not_found = target > 0 && !bin_search(vec, target);

    // Invert and search if condition holds
    if (target_positive_and_not_found) {
        // Invert elements and target
        std::transform(vec.begin(), vec.end(), vec.begin(), [](int x) { return -x; });
        target = -target;

        // Sort the inverted vector for binary search
        std::sort(vec.begin(), vec.end());

        // Search for the inverted target
        bool inverted_search_outcome = bin_search(vec, target);

        // Expect it to be found in the inverted vector
        EXPECT_TRUE(inverted_search_outcome);
    }
}

INSTANTIATE_TEST_CASE_P(TrueReturn, BSearchParamTest, testing::ValuesIn(get_tcs_randomly()));