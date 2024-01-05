#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <vector>
#include <tuple>

#include "../src/function.h"
#include "utils.h"

using namespace std;

#define SKIP_CRASH

class BSearchParamTest : public ::testing::TestWithParam<BSearch2Input> {};

/**
 * @brief Metamorphic relation 1: Adding an element greater than the max value of the array should not change the search outcome.
 *
 */
TEST_P(BSearchParamTest, MR1) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    bool source_out = bin_search(vec, target);

    // Append a larger element and test again
    vec.push_back(vec.back() + 1);
    bool follow_up_out = bin_search(vec, target);

    EXPECT_EQ(source_out, follow_up_out);
}

/**
 * @brief Metamorphic relation 2: If the array and target element are scaled by a positive multiplier, the result should be the same.
 *
 */
TEST_P(BSearchParamTest, MR2) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    bool source_out = bin_search(vec, target);

    int multiplier = 2;
    std::vector<int> scaled_vec;
    std::transform(vec.begin(), vec.end(), std::back_inserter(scaled_vec), [multiplier](int x) { return x * multiplier; });
    int scaled_target = target * multiplier;

    bool follow_up_out = bin_search(scaled_vec, scaled_target);

    EXPECT_EQ(source_out, follow_up_out);
}

/**
 * @brief Metamorphic relation 3: Removing elements other than the target should not change the result of the search.
 *
 */
TEST_P(BSearchParamTest, MR3) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    bool source_out = bin_search(vec, target);

    // Remove an element that is not the target
    if (vec.size() > 1 && vec[0] != target) {
        vec.erase(vec.begin());
    }
    bool follow_up_out = bin_search(vec, target);

    EXPECT_EQ(source_out, follow_up_out);
}

/**
 * @brief Metamorphic relation 4: Dividing all elements and the target by a common divisor should not affect the search result.
 *
 */
TEST_P(BSearchParamTest, MR4) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    bool source_out = bin_search(vec, target);

    int divisor = 2;

    if (target % divisor == 0) {
        // Divide the elements and the target by the divisor to produce a follow-up input
        std::vector<int> reduced_vec;
        std::transform(vec.begin(), vec.end(), std::back_inserter(reduced_vec), [divisor](int x) { return x / divisor; });
        int reduced_target = target / divisor;

        bool follow_up_out = bin_search(reduced_vec, reduced_target);
        EXPECT_EQ(source_out, follow_up_out);
    }
}

/**
 * @brief Metamorphic relation 5: Reversing the input vector (which breaks the sorted order) should result in a false return since the specification requires an
 * ascending array.
 *
 */
TEST_P(BSearchParamTest, MR5) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    std::vector<int> reversed_vec(vec.rbegin(), vec.rend()); // Create a reversed vector

    EXPECT_FALSE(bin_search(reversed_vec, target));
}

/**
 * @brief If you remove an element that does not exist in the array, the outcome of the search should remain the same.
 *
 */
TEST_P(BSearchParamTest, MR6) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Initial binary search
    bool source_out = bin_search(vec, target);

    // Insert a random element that is not the target and re-sort the array
    int new_element = vec.back() + 1; // Ensure it's larger than any element in the array
    vec.push_back(new_element);
    std::sort(vec.begin(), vec.end());

    // Now, remove the element we just added
    vec.pop_back(); // Element is at the end, as vector was sorted

    // Follow-up binary search
    bool follow_up_out = bin_search(vec, target);

    // The result should remain the same regardless of the modification
    EXPECT_EQ(source_out, follow_up_out);
}

/**
 * @brief Perform a binary search on subsets of the array containing the target should return true.
 *
 */
TEST_P(BSearchParamTest, MR7) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Ensure the target exists in the array before testing this relation
    bool source_out = bin_search(vec, target);
    if (!source_out)
        return;

    // Get the position of the target
    auto it = std::find(vec.begin(), vec.end(), target);
    if (it != vec.end()) {
        int index = it - vec.begin();

        // Create a subset of the array that includes the target
        std::vector<int> subset(vec.begin(), vec.begin() + index + 1);

        // Follow-up binary search in the subset
        bool follow_up_out = bin_search(subset, target);

        // The result should be the same since the target is in the subset
        EXPECT_EQ(source_out, follow_up_out);
    }
}

/**
 * @brief If `bin_search` finds the target, then doubling every element except the target value should not change the outcome of the function.
 *
 */
TEST_P(BSearchParamTest, MR8) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Perform the initial search
    bool source_out = bin_search(vec, target);
    if (!source_out)
        return;

    // Double every element except the target
    std::vector<int> modified_vec;
    std::transform(vec.begin(), vec.end(), std::back_inserter(modified_vec), [&target](int val) { return val == target ? val : val * 2; });

    // Perform the follow-up search
    bool follow_up_out = bin_search(modified_vec, target);

    // The result should not change as the search for the target should still be successful
    EXPECT_EQ(source_out, follow_up_out);
}

/**
 * @brief If the `target` is present in the array, then replacing the `target` with another number not already in the array, re-sorting it, and searching for
 * the original `target` should yield `false`.c
 *
 */
TEST_P(BSearchParamTest, MR9) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Only proceed if the target is in the array
    bool source_out = bin_search(vec, target);
    if (!source_out)
        return;

    std::vector<int> modified_vec = vec;

    // Find and replace the target with a new value
    auto target_position = std::find(modified_vec.begin(), modified_vec.end(), target);
    if (target_position != modified_vec.end()) {
        int new_value = vec.back() + 1; // Ensure to pick a value not in the array
        *target_position = new_value;
        std::sort(modified_vec.begin(), modified_vec.end()); // Re-sort the array

        // Perform the search again
        bool follow_up_out = bin_search(modified_vec, target);
        EXPECT_FALSE(follow_up_out);
    }
}

/**
 * @brief If the `target` exists in the original array and you add a duplicate of the `target`, the result should still be `true`.
 *
 */
TEST_P(BSearchParamTest, MR10) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    bool source_out = bin_search(vec, target);
    if (!source_out)
        return;

    // Add a duplicate of the target to the array and re-sort
    vec.push_back(target);
    std::sort(vec.begin(), vec.end());

    // Perform the search again
    bool follow_up_out = bin_search(vec, target);

    // The output should remain true as the target is still in the array
    EXPECT_TRUE(follow_up_out);
}

/**
 * @brief For an array that does not contain the `target`, adding the `target` to the array, re-sorting it, and then searching should yield `true`.
 *
 */
TEST_P(BSearchParamTest, MR11) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    bool source_out = bin_search(vec, target);
    if (source_out)
        return; // Skip if the target is already in the array

    // Add the target to the array
    vec.push_back(target);
    std::sort(vec.begin(), vec.end());

    // Perform the search again
    bool follow_up_out = bin_search(vec, target);

    // Now the target has been added, and the result should be true
    EXPECT_TRUE(follow_up_out);
}

/**
 * @brief If the `target` is at the beginning of the array, adding a new element smaller than the `target` at the beginning should not change the result (if the
 * target was in the array).
 *
 */
TEST_P(BSearchParamTest, MR12) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Perform the initial search
    bool source_out = bin_search(vec, target);
    if (!source_out)
        return;

    // Add a smaller element than the smallest one in the vector at the beginning
    vec.insert(vec.begin(), vec.front() - 1);

    // Perform the search again
    bool follow_up_out = bin_search(vec, target);

    // The result should not change since the target is still in the array
    EXPECT_EQ(source_out, follow_up_out);
}

/**
 * @brief If `target` is at the end of the array, adding a new element larger than the `target` at the end should not change the result (if the target was in
 * the array).
 *
 */
TEST_P(BSearchParamTest, MR13) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Perform the initial search
    bool source_out = bin_search(vec, target);
    if (!source_out)
        return;

    // Add a larger element than the largest one in the vector at the end
    vec.push_back(vec.back() + 1);

    // Perform the search again
    bool follow_up_out = bin_search(vec, target);

    // The result should not change since the target is still in the array
    EXPECT_EQ(source_out, follow_up_out);
}

/**
 * @brief If `target` is not found in the array, and elements in the array are shuffled randomly (disrupting the ascending order), `bin_search` should still
 * return `false` if it checks for sorted order as a precondition.
 *
 */
TEST_P(BSearchParamTest, MR14) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Perform the initial search
    bool source_out = bin_search(vec, target);
    if (source_out)
        return; // Skip if the target is already in the array

    // Shuffle the array elements
    std::random_shuffle(vec.begin(), vec.end());

    // Perform the search again
    bool follow_up_out = bin_search(vec, target);

    // The result should still be false, as the binary search requires sorted order
    EXPECT_FALSE(follow_up_out);
}

/**
 * @brief If an array does not contain the `target`, inserting the `target` multiple times (to create duplicates), then sorting the array, should change the
 * search result from `false` to `true`.
 *
 */
TEST_P(BSearchParamTest, MR15) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Perform the initial search
    bool source_out = bin_search(vec, target);
    if (source_out)
        return; // Skip test if target is found

    // Insert the target into multiple positions
    vec.push_back(target);
    vec.push_back(target);
    std::sort(vec.begin(), vec.end()); // Sort the vector again

    // Perform the search after adding duplicates
    bool follow_up_out = bin_search(vec, target);

    // Now the target has been added, the search result should be true
    EXPECT_TRUE(follow_up_out);
}

/**
 * @brief If the array contains the `target`, inverting the sign of every element in the array as well as the `target` should not change the outcome of the
 * search.
 *
 */
TEST_P(BSearchParamTest, MR16) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Perform the initial search
    bool source_out = bin_search(vec, target);

    // Invert signs of all elements and the target
    for (auto &element : vec) {
        element = -element;
    }
    std::sort(vec.begin(), vec.end()); // Sort the vector again since the order is reversed
    int inverted_target = -target;

    // Perform the search after inverting the signs
    bool follow_up_out = bin_search(vec, inverted_target);

    // The result should remain the same
    EXPECT_EQ(source_out, follow_up_out);
}

/**
 * @brief If the target is at the beginning or end of the array, reversing the array and using the negative of the target should yield the same result if
 * numbers are symmetrically distributed.
 *
 */
TEST_P(BSearchParamTest, MR17) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Perform the initial search
    bool source_out = bin_search(vec, target);
    if (!source_out)
        return; // Skip if the target is not found

    // Reverse the array and negate the target
    std::reverse(vec.begin(), vec.end());
    int neg_target = -target;

    // Assuming the negative of every element also exists in the array,
    // perform the search again with the negative target on the reversed array
    bool follow_up_out = bin_search(vec, neg_target);

    // The result should be the same
    EXPECT_EQ(source_out, follow_up_out);
}

/**
 * @brief For an array containing the `target`, replacing any single element that is not the `target` with another value (while maintaining the sorted property)
 * should not change the result of searching for `target`.c
 *
 */
TEST_P(BSearchParamTest, MR18) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Initial search
    bool source_out = bin_search(vec, target);
    if (!source_out)
        return; // Skip this relation if the target is not in the array

    // Change a non-target element
    if (vec.size() > 1) {
        for (auto &el : vec) {
            if (el != target) {
                el = (vec.front() - 1); // Replace with a value smaller than the smallest to keep array sorted
                break;
            }
        }
    }

    // Follow-up search
    bool follow_out = bin_search(vec, target);

    // The result should remain true
    EXPECT_TRUE(follow_out);
}

/**
 * @brief If `target` exists in the array, inversely scaling the array (multiplying by -1) and searching for the negative `target` should yield `true`.
 *
 */
TEST_P(BSearchParamTest, MR19) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Initial search
    bool source_out = bin_search(vec, target);
    if (!source_out)
        return; // Skip if the target is not present

    // Inverse scaling
    for (auto &el : vec) {
        el *= -1; // Multiply by -1
    }
    std::sort(vec.begin(), vec.end()); // Re-sort to maintain ascending order

    // New target is the negative of the original
    int new_target = -target;

    // Follow-up search
    bool follow_out = bin_search(vec, new_target);

    // The result should still be true
    EXPECT_TRUE(follow_out);
}

/**
 * @brief If `target` does not exist in the array, removing elements neither affects nor alters the non-presence of the `target`.
 *
 */
TEST_P(BSearchParamTest, MR20) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Initial search
    bool source_out = bin_search(vec, target);
    if (source_out)
        return; // Skip the following checks if target is initially found

    // Remove elements while keeping array sorted and ensuring the target is still not present
    vec.erase(vec.begin() + vec.size() / 2);

    // Follow-up search
    bool follow_out = bin_search(vec, target);

    // The result should still be false
    EXPECT_FALSE(follow_out);
}

/**
 * @brief If the `target` does exist in the array, and we create a second array by replicating each element of the original array, the search result for the
 * `target` in the new array should still be `true`.
 *
 */
TEST_P(BSearchParamTest, MR21) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Perform the initial search
    bool source_out = bin_search(vec, target);
    if (!source_out)
        return; // Skip if target is not in the array

    // Create a new vector by duplicating each element of the original
    std::vector<int> vec_duplicated;
    for (const auto &el : vec) {
        vec_duplicated.push_back(el);
        vec_duplicated.push_back(el); // Duplicate element
    }

    // Perform search in the new array with duplicated elements
    bool follow_out = bin_search(vec_duplicated, target);

    // The result should remain true as the target is still present
    EXPECT_TRUE(follow_out);
}

/**
 * @brief In the case where the `target` is not in the array, concatenating the original array with an exact copy of itself should still return a `false` search
 * result for the `target`.
 *
 */
TEST_P(BSearchParamTest, MR22) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Perform the initial search
    bool source_out = bin_search(vec, target);
    if (source_out)
        return; // Skip if target is in the array

    // Concatenate the vector with itself
    std::vector<int> vec_concatenated(vec);
    vec_concatenated.insert(vec_concatenated.end(), vec.begin(), vec.end());

    // Perform search in the concatenated vector
    bool follow_out = bin_search(vec_concatenated, target);

    // The result should remain false as the target was not in the original array
    EXPECT_FALSE(follow_out);
}

/**
 * @brief If the `target` is present in the array, taking a prefix of the array that contains the `target` and searching for `target` should return `true`.
 *
 */
TEST_P(BSearchParamTest, MR23) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    bool source_out = bin_search(vec, target);
    if (!source_out)
        return; // Skip if target is not in the array

    // Assuming the vector is sorted, the target must be within the first 'i' elements
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == target) {
            // Create prefix vector containing target
            std::vector<int> prefix_vec(vec.begin(), vec.begin() + i + 1);

            // Search for the target within the prefix vector
            bool follow_out = bin_search(prefix_vec, target);

            // We expect the result to be true as target is within the prefix
            EXPECT_TRUE(follow_out);
            break;
        }
    }
}

/**
 * @brief Doubling the target value and every element in the array, and then dividing them all back by two should not change the search result.
 *
 */
TEST_P(BSearchParamTest, MR24) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Perform the initial search
    bool source_out = bin_search(vec, target);

    // Double every element and the target
    std::transform(vec.begin(), vec.end(), vec.begin(), [](int n) { return n * 2; });
    target *= 2;

    bool mid_out = bin_search(vec, target);

    // Now divide them all by two to revert to the original numbers
    std::transform(vec.begin(), vec.end(), vec.begin(), [](int n) { return n / 2; });
    target /= 2;

    bool follow_up_out = bin_search(vec, target);

    // The result should not change throughout
    EXPECT_TRUE(mid_out);
    EXPECT_EQ(source_out, follow_up_out);
}

/**
 * @brief If the `target` does not exist in the array, inserting the `target` into its correctly sorted position then removing it should yield a `false` search
 * result throughout.
 *
 */
TEST_P(BSearchParamTest, MR25) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Initial search
    bool source_out = bin_search(vec, target);
    if (source_out)
        return; // Skip if target is in the array initially

    // Insert the target into its sorted position
    auto it = std::lower_bound(vec.begin(), vec.end(), target);
    vec.insert(it, target);

    // Perform search after inserting
    bool mid_out = bin_search(vec, target);
    EXPECT_TRUE(mid_out);

    // Now remove the target
    vec.erase(std::remove(vec.begin(), vec.end(), target), vec.end());

    // Perform search after removing
    bool follow_out = bin_search(vec, target);
    EXPECT_FALSE(follow_out);
}

/**
 * @brief For a non-empty array that excludes the `target`, searching for any value not in the array (including the `target`) after inverting the array
 * sign-wise should not yield the search result `true`.
 *
 */
TEST_P(BSearchParamTest, MR26) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Skip if the array is empty or target is found
    bool source_out = bin_search(vec, target);
    if (source_out || vec.empty())
        return;

    // Invert the sign of each element and the target
    std::transform(vec.begin(), vec.end(), vec.begin(), std::negate<int>());
    target = -target;
    std::sort(vec.begin(), vec.end()); // Re-sort the vector after inversion

    // Perform search in the sign-inverted array
    bool follow_out = bin_search(vec, target);

    // The result should remain false as the target was not in the original array
    EXPECT_FALSE(follow_out);
}

/**
 * @brief If the `target` doesn't exist in the array and we change the order of the elements in the array without adding or removing any, `bin_search` should
 * still return `false`.
 *
 */
TEST_P(BSearchParamTest, MR27) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Perform the initial search
    bool source_out = bin_search(vec, target);
    if (source_out)
        return; // Skip if target is initially found

    // Attempt to shuffle the elements, which would break the precondition of bin_search
    std::random_shuffle(vec.begin(), vec.end());

    // Perform the search again
    bool follow_up_out = bin_search(vec, target);

    // The result should also be false
    EXPECT_FALSE(follow_up_out);
}

/**
 * @brief If the `target` is greater than all elements in the array, increasing all elements by a constant that gives a new array where all elements are still
 * less than the `target` should not change the outcome from `false`.
 *
 */
TEST_P(BSearchParamTest, MR28) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Initial search
    bool source_out = bin_search(vec, target);
    if (vec.empty() || vec.back() >= target)
        return; // if the array is empty or target is less than max element

    // Increase all elements by a constant
    int constant_increase = target - vec.back() - 1;
    std::transform(vec.begin(), vec.end(), vec.begin(), [constant_increase](int val) { return val + constant_increase; });

    // Follow-up search
    bool follow_up_out = bin_search(vec, target);

    // The result should still be false
    EXPECT_FALSE(follow_up_out);
}

/**
 * @brief If the `target` exists in the array, taking any contiguous subarray that includes the `target` and performing `bin_search` should return `true`.
 *
 */
TEST_P(BSearchParamTest, MR29) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Perform the initial search
    bool source_out = bin_search(vec, target);
    if (!source_out)
        return; // Proceed only if the target exists in the array

    // Find the index of the target to form a subarray including the target
    auto it = std::find(vec.begin(), vec.end(), target);
    if (it != vec.end()) {
        // Take a subarray including the target
        int idx = std::distance(vec.begin(), it);
        std::vector<int> sub_vec(vec.begin() + std::max(idx - 2, 0), vec.begin() + std::min(idx + 3, int(vec.size())));

        // Perform search on the subarray
        bool follow_up_out = bin_search(sub_vec, target);

        // The result should be the same
        EXPECT_TRUE(follow_up_out);
    }
}

/**
 * @brief For any array that does not include the `target`, inverting the sign of all its elements, including the `target`, then re-sorting the array, should
 * not change the result of the binary search (assuming the array remains sorted).
 *
 */
TEST_P(BSearchParamTest, MR30) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Perform the initial search
    bool source_out = bin_search(vec, target);

    // Invert the sign of all elements and the target, then sort the array
    std::transform(vec.begin(), vec.end(), vec.begin(), std::negate<>());
    std::sort(vec.begin(), vec.end());
    target = -target; // Invert the target

    // Perform the search again
    bool follow_up_out = bin_search(vec, target);

    // The result should remain the same
    EXPECT_EQ(source_out, follow_up_out);
}

/**
 * @brief If an array contains the `target`, repeating the array elements (i.e., concatenating the array with itself) should still yield `true` when searching
 * for the `target`.
 *
 */
TEST_P(BSearchParamTest, MR31) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Initial search
    bool source_out = bin_search(vec, target);

    // Skip if target is not found initially
    if (!source_out)
        return;

    // Repeat the array
    std::vector<int> repeated_vec = vec;
    repeated_vec.insert(repeated_vec.end(), vec.begin(), vec.end());

    // Perform the search on the repeated array
    bool follow_out = bin_search(repeated_vec, target);

    // The result should still be true
    EXPECT_TRUE(follow_out);
}

/**
 * @brief If the target is not present in the array, changing the target to another value that is also not present should not affect the outcome of
 * `bin_search`.
 *
 */
TEST_P(BSearchParamTest, MR32) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Perform the initial search
    bool source_out = bin_search(vec, target);

    if (source_out)
        return; // Proceed only if the initial target is not found

    // Change target to a new value that isn't present in the array
    int new_target = vec.back() + 1; // Assuming the array contains positive integers

    // Perform the search with the new target
    bool follow_up_out = bin_search(vec, new_target);

    // The result should still be false
    EXPECT_EQ(source_out, follow_up_out);
}

/**
 * @brief For an array containing the `target`, incrementing all elements in the array including the `target` by the same positive value should not change the
 * result of the binary search.
 *
 */
TEST_P(BSearchParamTest, MR33) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    const int increment_value = 10; // Use any positive value for increment

    // Perform the initial search before modification
    bool source_out = bin_search(vec, target);
    if (!source_out)
        return; // Proceed only if the target is found intially

    // Increment all elements and the target by a positive value
    for (auto &el : vec) {
        el += increment_value;
    }
    target += increment_value;

    // Perform the search after incrementing
    bool follow_up_out = bin_search(vec, target);

    EXPECT_EQ(source_out, follow_up_out);
}

/**
 * @brief For an array that does not contain the `target`, searching for any value that is less than the minimum value in the array should consistently yield
 * `false`.
 *
 */
TEST_P(BSearchParamTest, MR34) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Perform the initial search to confirm absence of the target
    bool source_out = bin_search(vec, target);
    if (source_out || vec.empty())
        return; // Proceed only if the array is not empty and the target is not found

    // Search for a value less than the minimum value of the array
    int new_target = vec.front() - 1;
    bool follow_up_out = bin_search(vec, new_target);

    EXPECT_FALSE(follow_up_out);
}

/**
 * @brief Duplicate one of the elements of the array that is not the `target`. This operation should not affect the search result for the `target`.
 *
 */
TEST_P(BSearchParamTest, MR35) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Perform the initial search
    bool source_out = bin_search(vec, target);

    // Skip if the target is not in array or if the array is empty
    if (!source_out || vec.empty())
        return;

    // Duplicate an element that is not the target
    for (auto &el : vec) {
        if (el != target) {
            vec.push_back(el);
            break;
        }
    }
    std::sort(vec.begin(), vec.end()); // Sort the array after insertion to maintain precondition

    // Perform the binary search again
    bool follow_up_out = bin_search(vec, target);

    EXPECT_EQ(source_out, follow_up_out);
}

/**
 * @brief If an array does not contain the `target`, subdividing the array into smaller arrays (still sorted) and searching for the `target` in each subarray
 * should yield `false` for each search.
 *
 */
TEST_P(BSearchParamTest, MR36) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Perform the initial search to confirm absence of the target
    bool source_out = bin_search(vec, target);
    if (source_out)
        return; // Proceed only if the target is not found

    // Divide the array into subarrays and search the target in each
    std::size_t subarray_size = vec.size() / 2;
    bool subarray_search_out = true; // Defaults to true for edge case with empty vector
    for (size_t i = 0; i < vec.size(); i += subarray_size) {
        std::vector<int> subvec(vec.begin() + i, std::min(vec.begin() + i + subarray_size, vec.end()));
        subarray_search_out &= bin_search(subvec, target);
    }

    // Should still not find the target in any subarray
    EXPECT_FALSE(subarray_search_out);
}

/**
 * @brief For an array that contains the `target`, removing the first element (if it is not the `target`) should still result in `target` being found via
 * `bin_search`.
 *
 */
TEST_P(BSearchParamTest, MR37) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Initial search to ensure the target exists
    bool source_out = bin_search(vec, target);
    if (!source_out || vec.front() == target || vec.empty())
        return;

    // Removing the first element (not the target)
    vec.erase(vec.begin());

    // Perform the search after removing the first element
    bool follow_up_out = bin_search(vec, target);

    EXPECT_TRUE(follow_up_out);
}

/**
 * @brief For any array, searching for the minimum value minus one should yield `false`.
 *
 */
TEST_P(BSearchParamTest, MR38) {
    std::vector<int> vec;
#if NOT_SATISFIED
    std::tie(vec, std::ignore) = GetParam(); // Ignore the target for this relation
#else
    BSearch2Input input = GetParam();
    int target;
    vec = input.vec, target = input.target;
#endif

    if (vec.empty())
        return; // Skip if the vector is empty

    int new_target = vec.front() - 1; // The new target is less than the minimum value in the array

    // Perform the search for the new target
    bool follow_up_out = bin_search(vec, new_target);

    EXPECT_FALSE(follow_up_out);
}

/**
 * @brief If the `target` is within the array, transforming the array by adding a constant to all elements except the `target`, and then subtracting that
 * constant, should result in the same search outcome.
 *
 */
TEST_P(BSearchParamTest, MR39) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Initial search to confirm the presence of the target
    bool source_out = bin_search(vec, target);
    if (!source_out)
        return;

    int increment = 5; // The constant to add and then subtract
    for (auto &el : vec) {
        if (el != target) {
            el += increment;
        }
    }
    // Subtract the constant right away
    for (auto &el : vec) {
        if (el != target) {
            el -= increment;
        }
    }

    // Perform the search after the transformation
    bool follow_up_out = bin_search(vec, target);

    // The result should still be true as the target's relative position is unchanged
    EXPECT_TRUE(follow_up_out);
}

/**
 * @brief For an array containing both positive and negative numbers, including the `target`, multiplying all the elements by `-1`, and flipping the `target`
 * sign, should not change the result of the binary search.
 *
 */
TEST_P(BSearchParamTest, MR40) {
    std::vector<int> vec;
    int target;
#if NOT_SATISFIED
    std::tie(vec, target) = GetParam();
#else
    BSearch2Input input = GetParam();
    vec = input.vec, target = input.target;
#endif

    // Initial search to confirm the presence of the target
    bool source_out = bin_search(vec, target);
    if (!source_out)
        return;

    target = -target; // flip the target sign
    std::transform(vec.begin(), vec.end(), vec.begin(), [](int el) { return -el; });

    // Sort the array as the order will now be reversed
    std::sort(vec.begin(), vec.end());

    // Perform the search after the transformation
    bool follow_up_out = bin_search(vec, target);

    // The result should still hold as the target still exists in the array even after flip
    EXPECT_TRUE(follow_up_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, BSearchParamTest, testing::ValuesIn(get_tcs_randomly()));