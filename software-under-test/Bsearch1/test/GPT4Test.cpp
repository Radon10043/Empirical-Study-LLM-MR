#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <random>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class GetRangeParamTest : public ::testing::TestWithParam<GetRangeInput> {};

/**
 * @brief Metamorphic relation 3: Doubling the array, if the searching number is in the array,
 * the starting index should remain the same, and the ending index should be the original ending index plus the length of the array.
 */
TEST_P(GetRangeParamTest, MR3) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    size_t vec_len = vec.size();

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1 && source_out[1] == -1)
        return;

    /* Construct follow-up input by appending the original vector to itself */
    vector<int> follow_vec(vec);
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1] + vec_len, follow_out[1]);
}

/**
 * @brief Metamorphic relation 4: Extracting a subarray that encompasses the target's range.
 * The resultant starting and ending indexes should match the range within the subarray.
 */
TEST_P(GetRangeParamTest, MR4) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1 && source_out[1] == -1)
        return;

    /* Extract a subarray that includes target's range */
    vector<int> follow_vec(vec.begin() + source_out[0], vec.begin() + source_out[1] + 1);

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(0, follow_out[0]);
    EXPECT_EQ(source_out[1] - source_out[0], follow_out[1]);
}

/**
 * @brief Metamorphic relation 5: Reversing the array should reverse the indexes of the target's range.
 */
TEST_P(GetRangeParamTest, MR5) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by reversing the vector */
    vector<int> follow_vec(vec.rbegin(), vec.rend());

    /* Adjust target if necessary for the reversed array, assuming unique elements */
    int follow_target = target; // Here you might need a target transformation logic if applicable

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, follow_target);

    /* Verification */
    size_t n = vec.size();
    EXPECT_EQ(n - 1 - source_out[1], follow_out[0]);
    EXPECT_EQ(n - 1 - source_out[0], follow_out[1]);
}

/**
 * @brief Metamorphic relation 6: Adding repetitions of target at the start and the end should expand the range from the end.
 */
TEST_P(GetRangeParamTest, MR6) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1 && source_out[1] == -1)
        return;

    /* Add target to both ends of the vector */
    vector<int> prefix(3, target); // Add 3 repetitions for example
    vector<int> suffix(2, target); // Add 2 repetitions for example
    vector<int> follow_vec = prefix;
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.end());
    follow_vec.insert(follow_vec.end(), suffix.begin(), suffix.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1] + suffix.size(), follow_out[1]);
}

/**
 * @brief Metamorphic relation 7: Removing elements after target's range should not affect its starting and ending indexes.
 */
TEST_P(GetRangeParamTest, MR7) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1 || source_out[1] == -1 || source_out[1] == vec.size() - 1)
        return;

    /* Remove elements after the target's range */
    vector<int> follow_vec(vec.begin(), vec.begin() + source_out[1] + 1);

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 8: If all elements and the target are multiplied by the same
 * positive constant, the range should not change.
 */
TEST_P(GetRangeParamTest, MR8) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int multiplier = 2; // Multiply by 2 for example

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by multiplying each element by 'multiplier' */
    vector<int> follow_vec(vec.size());
    std::transform(vec.begin(), vec.end(), follow_vec.begin(), [multiplier](int element) { return element * multiplier; });
    int follow_target = target * multiplier;

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 9: Change the target to the next greater element in the array.
 */
TEST_P(GetRangeParamTest, MR9) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Ensure target is not the last element */
    auto it = std::upper_bound(vec.begin(), vec.end(), target);
    if (it == vec.end())
        return;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input (next greater element) */
    int follow_target = *it;

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out[1] + 1, follow_out[0]);
}

/**
 * @brief Metamorphic relation 10: Concatenating the array with another array of larger elements.
 */
TEST_P(GetRangeParamTest, MR10) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    vector<int> new_elements = {vec.back() + 1, vec.back() + 2}; // For example

    /* Concatenate vec with new_elements */
    vector<int> concatenated(vec);
    concatenated.insert(concatenated.end(), new_elements.begin(), new_elements.end());

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Get follow-up output */
    vector<int> follow_out = get_range(concatenated, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 11: Inserting occurrences of the target within its range should extend the end index by the number of occurrences added.
 */
TEST_P(GetRangeParamTest, MR11) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip the test if the target is not present */
    if (source_out[0] == -1 || source_out[1] == -1)
        return;

    /* Construct follow-up input by adding more occurrences of the target within the range */
    vec.insert(vec.begin() + source_out[1], 3, target); // Inserting 3 more occurrences for example

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1] + 3, follow_out[1]);
}

/**
 * @brief Metamorphic relation 12: Target indexes remain the same when removing elements outside of target's range.
 */
TEST_P(GetRangeParamTest, MR12) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip the test if the target is not present or if it's at the ends */
    if (source_out[0] <= 0 || source_out[1] >= vec.size() - 1)
        return;

    /* Construct follow-up input by removing an element before and after the target's range */
    vector<int> follow_vec = vec;
    follow_vec.erase(follow_vec.begin() + source_out[1] + 1);
    follow_vec.erase(follow_vec.begin());

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0] - 1, follow_out[0]); // Adjusted for the element removed at the start
    EXPECT_EQ(source_out[1] - 1, follow_out[1]); // Adjusted for the element removed at the start
}

/**
 * @brief Metamorphic relation 13: Extending the array with larger elements should not change the target index range.
 */
TEST_P(GetRangeParamTest, MR13) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip the test if the target is not present */
    if (source_out[0] == -1 || source_out[1] == -1)
        return;

    /* Construct follow-up input by adding larger elements to the array */
    vector<int> follow_vec = vec;
    follow_vec.push_back(vec.back() + 1); // Add one element larger than the max
    follow_vec.push_back(vec.back() + 2); // Add another larger element

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 14: If the array is repeated and the target is not in the original array,
 * it should not be in the repeated array, and the result should be unchanged {-1, -1}.
 */
TEST_P(GetRangeParamTest, MR14) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Construct follow-up input */
    vector<int> follow_vec(vec);
    // Repeat the vec to append to itself
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* If the target isn't in the original vector, it shouldn't be in the follow-up */
    EXPECT_TRUE((get_range(vec, target) == std::vector<int>{-1, -1}) == (follow_out == std::vector<int>{-1, -1}));
}

/**
 * @brief Metamorphic relation 15: Removing elements within the target range should decrease the end index.
 */
TEST_P(GetRangeParamTest, MR15) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    // Skip if target is not in the array or occurs only once
    if (source_out[0] == -1 || source_out[0] == source_out[1])
        return;

    /* Construct follow-up input by removing some elements within the target range */
    int remove_count = 1; // Remove just one occurrence for example
    vector<int> follow_vec = vec;
    follow_vec.erase(follow_vec.begin() + source_out[0], follow_vec.begin() + source_out[0] + remove_count);

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1] - remove_count, follow_out[1]);
}

/**
 * @brief Metamorphic relation 16: Inverting elements around target values inverts the target's index range around the mid-point.
 */
TEST_P(GetRangeParamTest, MR16) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    // Skip if target is not in the array
    if (source_out[0] == -1)
        return;

    /* Construct follow-up input by inverting elements around the target's range */
    if (source_out[0] > 0 && source_out[1] < vec.size() - 1) {
        std::reverse(vec.begin(), vec.begin() + source_out[0]);
        std::reverse(vec.begin() + source_out[1] + 1, vec.end());
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification - The start and end indices should get swapped */
    EXPECT_EQ(vec.size() - 1 - source_out[1], follow_out[0]);
    EXPECT_EQ(vec.size() - 1 - source_out[0], follow_out[1]);
}

/**
 * @brief Metamorphic relation 17: If all elements and the target are divided by the same positive constant, the range should remain unchanged.
 */
TEST_P(GetRangeParamTest, MR17) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int divisor = 2; // Example divisor, should not produce a remainder for the elements

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip division by divisor if it would produce a remainder for the target */
    if (target % divisor != 0)
        return;

    /* Division of all elements by 'divisor' */
    std::transform(vec.begin(), vec.end(), vec.begin(), [divisor](int element) { return element / divisor; });

    /* Adjust target for division */
    int follow_target = target / divisor;

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 18: Shuffling elements outside the target's index range does not affect the target's range.
 */
TEST_P(GetRangeParamTest, MR18) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip if target is not in the array */
    if (source_out[0] == -1)
        return;

    /* Shuffle elements outside of the target range */
    std::random_shuffle(vec.begin(), vec.begin() + source_out[0]);
    std::random_shuffle(vec.begin() + source_out[1] + 1, vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 19: Adding non-target elements to the array should not change the target's index range.
 */
TEST_P(GetRangeParamTest, MR19) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip if target is not in the array */
    if (source_out[0] == -1)
        return;

    /* Add non-target element */
    vec.insert(vec.begin() + source_out[0], target - 1); // Assume 'target - 1' is not in the array

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0] + 1, follow_out[0]);
    EXPECT_EQ(source_out[1] + 1, follow_out[1]);
}

/**
 * @brief Metamorphic relation 20: Inserting non-target elements before the target's range shifts the index range to the right.
 */
TEST_P(GetRangeParamTest, MR20) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    int num_insertions = 3;
    int value_to_insert = target - 1; // Assumed to not be equal to target

    /* Construct follow-up input */
    vector<int> follow_vec(vec);
    follow_vec.insert(follow_vec.begin() + source_out[0], num_insertions, value_to_insert);

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    if (source_out[0] != -1) {
        EXPECT_EQ(source_out[0] + num_insertions, follow_out[0]);
        EXPECT_EQ(source_out[1] + num_insertions, follow_out[1]);
    } else {
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic relation 21: Duplicating elements not equal to the target should not affect the target's range.
 */
TEST_P(GetRangeParamTest, MR21) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (auto &e : vec) {
        follow_vec.push_back(e);
        if (e != target) {
            // Duplicate elements not equal to the target
            follow_vec.push_back(e);
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    if (source_out[0] != -1) {
        EXPECT_EQ(source_out[0] * 2, follow_out[0]); // Position doubled because of the duplicate elements
        EXPECT_EQ(source_out[1] * 2, follow_out[1]);
    } else {
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic relation 22: Reducing the array size while keeping the target inside,
 * should keep the target's range indices the same.
 */
TEST_P(GetRangeParamTest, MR22) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip if target is not in the array or if it's at the extremes */
    if (source_out[0] == -1 || source_out[0] == 0 || source_out[1] == vec.size() - 1)
        return;

    /* Reduce the array, removing elements from both ends but not the target */
    vector<int> reduced_vec(vec.begin() + 1, vec.end() - 1);

    /* Get follow-up output */
    vector<int> follow_out = get_range(reduced_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0] - 1, follow_out[0]);
    EXPECT_EQ(source_out[1] - 1, follow_out[1]);
}

/**
 * @brief Metamorphic relation 23: Injecting elements greater than target after the target's range
 * should not change the target's range indices.
 */
TEST_P(GetRangeParamTest, MR23) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip test for target not in array or if it's the maximum element */
    if (source_out[1] == -1 || source_out[1] == vec.size() - 1)
        return;

    /* Inject larger elements after the target's range */
    vector<int> larger_elements = {vec.back() + 1, vec.back() + 2};
    vec.insert(vec.end(), larger_elements.begin(), larger_elements.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 24: Injecting elements smaller than target before the target's range
 * shifts the index range of the target by the number of elements added.
 */
TEST_P(GetRangeParamTest, MR24) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Inject smaller elements before where the target's range would start */
    vector<int> smaller_elements = {target - 2, target - 3}; // Assuming no duplicates

    vec.insert(vec.begin(), smaller_elements.begin(), smaller_elements.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    int num_smaller_elements = smaller_elements.size();
    EXPECT_EQ(source_out[0] + num_smaller_elements, follow_out[0]);
    EXPECT_EQ(source_out[1] + num_smaller_elements, follow_out[1]);
}

/**
 * @brief Metamorphic relation 25: Splitting and swapping array parts while excluding the target's range
 * should maintain the range width for the target.
 */
TEST_P(GetRangeParamTest, MR25) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1) {
        // If target is not found, the check is trivial
        return;
    }

    // Ensure we're splitting at a point that is not inside the target's range
    int split_index = (source_out[0] > 0) ? source_out[0] - 1 : source_out[1] + 1;

    /* Construct follow-up input */
    vector<int> follow_vec(vec.begin() + split_index, vec.end());
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.begin() + split_index);

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    int expected_start = (split_index <= source_out[0]) ? source_out[0] - split_index : vec.size() - split_index + source_out[0];
    int expected_end = expected_start + (source_out[1] - source_out[0]);

    EXPECT_EQ(expected_start, follow_out[0]);
    EXPECT_EQ(expected_end, follow_out[1]);
}

/**
 * @brief Metamorphic relation 26: Scaling all elements except for the target should leave the target's range unchanged.
 */
TEST_P(GetRangeParamTest, MR26) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by scaling elements except the target */
    vector<int> follow_vec(vec.size());
    std::transform(vec.begin(), vec.end(), follow_vec.begin(), [target](int element) { return (element == target) ? element : element * 2; });

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 27: Compressing the target's range by removing every other occurrence
 * should reduce the end index accordingly.
 */
TEST_P(GetRangeParamTest, MR27) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1 || vec[source_out[0]] != target) {
        // If target is not found or does not have consecutive occurrences, the check is trivial
        return;
    }

    /* Construct follow-up input by compressing target's range */
    vector<int> follow_vec;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i >= static_cast<size_t>(source_out[0]) && i <= static_cast<size_t>(source_out[1]) && (i - source_out[0]) % 2 == 1) {
            // Skip every other occurrence of the target
            continue;
        }
        follow_vec.push_back(vec[i]);
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    // Calculate the expected range by halving the size of the original target occurrences
    int target_range_size = source_out[1] - source_out[0] + 1;
    int half_range_size = target_range_size / 2; // Using integer division

    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[0] + half_range_size - 1, follow_out[1]);
}

/**
 * @brief Metamorphic relation 28: Creating a complement array with non-overlapping ranges.
 * If target exists in the original array, it should not exist in the complement array.
 */
TEST_P(GetRangeParamTest, MR28) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Assume the vec has unique sorted elements */
    // Create complement_vec consisting of elements not in vec
    vector<int> complement_vec;
    // Logic to fill complement_vec

    /* Fix by Radon */
    int max_elem = vec.back();
    for (int i = 0; i < vec.size(); i++)
        complement_vec.emplace_back(max_elem + vec[i]);

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Get follow-up output from complement_vec for the same target */
    vector<int> complement_out = get_range(complement_vec, target);

#if INVALID
    if (source_out == std::vector<int>{-1, -1}) {
        // If the target did not exist in the original vec
        EXPECT_NE(complement_out, std::vector<int>{-1, -1});
    } else {
        // If the target existed in the original vec
        EXPECT_EQ(complement_out, std::vector<int>{-1, -1});
    }
#endif

    /* Fix by Radon */
    if (source_out == std::vector<int>{-1, -1}) {
        // If the target did not exist in the original vec
        EXPECT_NE(complement_out, std::vector<int>(2, -1));
    } else {
        // If the target existed in the original vec
        EXPECT_EQ(complement_out, std::vector<int>(2, -1));
    }
}

/**
 * @brief Metamorphic relation 29: Shifting the target in the array should shift the range by the same amount.
 */
TEST_P(GetRangeParamTest, MR29) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1 || source_out[1] == vec.size() - 1) {
        // If target is not found or it's at the end of the array
        return;
    }

    /* Construct follow-up input by shifting the target */
    vector<int> follow_vec = vec;
    int next_val = vec[source_out[1] + 1];
    std::replace(follow_vec.begin() + source_out[0], follow_vec.begin() + source_out[1] + 1, target, next_val);

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, next_val);

    /* Verification */
    EXPECT_EQ(source_out[0] + 1, follow_out[0]);
    EXPECT_EQ(source_out[1] + 1, follow_out[1]);
}

/**
 * @brief Metamorphic relation 30: Doubling each instance of the target in the array should double the length of the target's range.
 */
TEST_P(GetRangeParamTest, MR30) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1) {
        // If target is not found
        return;
    }

    /* Construct follow-up input by doubling the target's range */
    vector<int> follow_vec;
    for (size_t i = 0; i < vec.size(); ++i) {
        follow_vec.push_back(vec[i]);
        if (i >= static_cast<size_t>(source_out[0]) && i <= static_cast<size_t>(source_out[1])) {
            // Double each instance of the target
            follow_vec.push_back(vec[i]);
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    int range_length = source_out[1] - source_out[0] + 1;
    /* Verification */
    EXPECT_EQ(source_out[0] * 2, follow_out[0]);
    EXPECT_EQ(follow_out[0] + range_length * 2 - 1, follow_out[1]);
}

/**
 * @brief Metamorphic relation 31: Removing elements before the target's range should shift the target range to the left.
 */
TEST_P(GetRangeParamTest, MR31) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] <= 1) { // Ensuring we have at least one element that can be removed before target's range
        return;
    }

    /* Construct follow-up input */
    int number_of_elements_to_remove = 1; // Remove one element for example
    vector<int> follow_vec(vec.begin() + number_of_elements_to_remove, vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0] - number_of_elements_to_remove, follow_out[0]);
    EXPECT_EQ(source_out[1] - number_of_elements_to_remove, follow_out[1]);
}

/**
 * @brief Metamorphic relation 32: Removing elements after the target's range should not change the target range indices.
 */
TEST_P(GetRangeParamTest, MR32) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[1] == -1 || source_out[1] == vec.size() - 1) { // Ensuring there are elements to remove after target's range
        return;
    }

    /* Construct follow-up input */
    vector<int> follow_vec(vec.begin(), vec.begin() + source_out[1] + 1);

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 33: Changing target to its immediate predecessor value updates target range starting index.
 */
TEST_P(GetRangeParamTest, MR33) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip if target is the first element */
    if (source_out[0] == 0) {
        return;
    }

    /* Construct follow-up input */
    int predecessor_target = vec[source_out[0] - 1];

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, predecessor_target);

    /* Verification */
    EXPECT_EQ(source_out[0] - (follow_out[1] - follow_out[0] + 1), follow_out[0]);
}

/**
 * @brief Metamorphic relation 34: Appending elements equal to the target after its range should extend the ending index.
 */
TEST_P(GetRangeParamTest, MR34) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[1] >= static_cast<int>(vec.size()) - 1 || source_out[0] == -1) {
        // If the target is at the end of the array or not found, test does not apply
        return;
    }

    /* Construct follow-up input by appending target elements at the end */
    int append_count = 2; // Example count of elements to append
    vec.insert(vec.end(), append_count, target);

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1] + append_count, follow_out[1]);
}

/**
 * @brief Metamorphic relation 35: Prepending elements less than the target shifts its indexes to the right.
 */
TEST_P(GetRangeParamTest, MR35) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1) {
        // Target not found, test does not apply
        return;
    }

    /* Construct follow-up input by prepending elements */
    int prepend_count = 3;                                    // Example count of elements to prepend
    vector<int> new_elements(prepend_count, vec.front() - 1); // Prepending smaller elements
    vec.insert(vec.begin(), new_elements.begin(), new_elements.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0] + prepend_count, follow_out[0]);
    EXPECT_EQ(source_out[1] + prepend_count, follow_out[1]);
}

/**
 * @brief Metamorphic relation 36: Removing duplicates of the target but leaving one should result in equal start and end indexes.
 */
TEST_P(GetRangeParamTest, MR36) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1) {
        // Target not found, test does not apply
        return;
    }

    /* Construct follow-up input by removing duplicates of the target */
    vec.erase(std::unique(vec.begin() + source_out[0], vec.begin() + source_out[1] + 1), vec.begin() + source_out[1] + 1);

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(follow_out[0], follow_out[1]);
}

/**
 * @brief Metamorphic relation 37: Inverting the array (excluding the target) inverts the range of non-target numbers.
 */
TEST_P(GetRangeParamTest, MR37) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    size_t vec_size = vec.size();

    /* Exclude the target and invert the rest of the array */
    vector<int> inverted_array(vec);
    auto start_it = inverted_array.begin();
    auto end_it = inverted_array.end();
    if (std::find(start_it, end_it, target) != end_it) {
        vector<int>::iterator target_range_start, target_range_end;
        target_range_start = std::lower_bound(start_it, end_it, target);
        target_range_end = std::upper_bound(start_it, end_it, target);
        std::reverse(start_it, target_range_start);
        std::reverse(target_range_end, end_it);
    } else {
        std::reverse(start_it, end_it);
    }

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Get inverted output */
    vector<int> inverted_out = get_range(inverted_array, target);

    /* Verification */
    if (source_out[0] != -1) {
        EXPECT_EQ(vec_size - source_out[1] - 1, inverted_out[0]);
        EXPECT_EQ(vec_size - source_out[0] - 1, inverted_out[1]);
    } else {
        EXPECT_EQ(inverted_out[0], -1);
    }
}

/**
 * @brief Metamorphic relation 38: Duplicating the target's range elsewhere (non-overlapping) maintains the target range.
 */
TEST_P(GetRangeParamTest, MR38) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1 || source_out[1] == -1) {
        // Target not found, or no room for duplication
        return;
    }

    /* Construct follow-up input by duplicating the target's range */
    vector<int> target_range(vec.begin() + source_out[0], vec.begin() + source_out[1] + 1);
    // Insert duplicate range at the end of the array
    vec.insert(vec.end(), target_range.begin(), target_range.end());

    /* Perform a stable sort to maintain relative order */
    std::stable_sort(vec.begin(), vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    int range_size = source_out[1] - source_out[0] + 1;
    EXPECT_EQ(range_size, follow_out[1] - follow_out[0] + 1);
    EXPECT_GE(follow_out[0], source_out[1] + 1); // Ensure the new range starts after the old range
}

/**
 * @brief Metamorphic relation 39: Swapping target with non-adjacent, non-target elements results in range shift.
 */
TEST_P(GetRangeParamTest, MR39) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1) {
        // Target not found
        return;
    }

    /* Construct follow-up input by swapping target with a non-adjacent, non-target element */
    int swap_index = (source_out[0] > 0) ? 0 : vec.size() - 1; // Example swap index
    std::swap(vec[swap_index], vec[source_out[0]]);

    /* Sort array as swapping may disrupt the order */
    std::sort(vec.begin(), vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    // The new start index should not be the same as before
    EXPECT_NE(source_out[0], follow_out[0]);
}

/**
 * @brief Metamorphic relation 40: Extending the array with elements outside the current bounds should not change the target index range.
 */
TEST_P(GetRangeParamTest, MR40) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    // Skip the relation if the target is not found or it is the only element
    if (source_out[0] == -1 || vec.size() == 1) {
        return;
    }

    int min_extension = vec.front() - 1; // Smaller than the smallest element
    int max_extension = vec.back() + 1;  // Greater than the largest element

    /* Extend the array */
    vec.insert(vec.begin(), min_extension);
    vec.push_back(max_extension);

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    int expected_start_index = source_out[0] + 1; // Adjusted for the new element at the start
    int expected_end_index = source_out[1] + 1;   // Adjusted for the new element at the start

    EXPECT_EQ(expected_start_index, follow_out[0]);
    EXPECT_EQ(expected_end_index, follow_out[1]);
}

/**
 * @brief Metamorphic relation 41: Removing boundary elements that are not the target should not change the target's index range.
 */
TEST_P(GetRangeParamTest, MR41) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Skip if array does not have enough elements */
    if (vec.size() < 3) {
        return;
    }

    /* Ensure targets are not at the boundaries */
    vector<int> source_out = get_range(vec, target);
    if (source_out[0] == 0 || source_out[1] == vec.size() - 1) {
        return;
    }

    /* Remove boundary elements */
    vec.erase(vec.begin());
    vec.pop_back();

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    int expected_start_index = source_out[0] - 1; // Adjusted after boundary removal
    int expected_end_index = source_out[1] - 1;   // Adjusted after boundary removal

    EXPECT_EQ(expected_start_index, follow_out[0]);
    EXPECT_EQ(expected_end_index, follow_out[1]);
}

/**
 * @brief Metamorphic relation 42: Replacing the target with a non-existing close element should result in target not being found.
 */
TEST_P(GetRangeParamTest, MR42) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    // If target is not found, test is not applicable
    if (source_out[0] == -1) {
        return;
    }

    // Replace target with the closest non-existing element
    int replacement = target + 1;
    while (std::binary_search(vec.begin(), vec.end(), replacement)) {
        ++replacement;
    }

    // Replace target occurrences with the replacement
    std::replace(vec.begin() + source_out[0], vec.begin() + source_out[1] + 1, target, replacement);

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(follow_out[0], -1);
    EXPECT_EQ(follow_out[1], -1);
}

/**
 * @brief Metamorphic relation 43: Even expansion of the array preserves the relative position of the target range.
 */
TEST_P(GetRangeParamTest, MR43) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    std::vector<int> follow_vec;
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        follow_vec.push_back(vec[i]);
        int new_elem = (vec[i] + vec[i + 1]) / 2;
        follow_vec.push_back(new_elem); // Inserting average of consecutive elements
    }
    follow_vec.push_back(vec.back()); // Don't forget to add the last element

    /* Get follow-up output */
    std::vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    if (source_out[0] != -1) {
        // Expecting the start index to be double (minus possible off-by-one due to new elements)
        EXPECT_NEAR(source_out[0] * 2, follow_out[0], 1);
        // Expecting the end index to be double (minus possible off-by-one due to new elements)
        EXPECT_NEAR(source_out[1] * 2, follow_out[1], 1);
    } else {
        // If the target was not found in the source array, it should not be found in the follow-up array
        EXPECT_EQ(follow_out[0], -1);
        EXPECT_EQ(follow_out[1], -1);
    }
}

/**
 * @brief Metamorphic relation 44: Shrinking array by removing alternating elements should affect the target range proportionally.
 */
TEST_P(GetRangeParamTest, MR44) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    std::vector<int> follow_vec;
    for (size_t i = 0; i < vec.size(); i += 2) { // Take every other element
        follow_vec.push_back(vec[i]);
    }

    /* Get follow-up output */
    std::vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    if (source_out[0] != -1 && source_out[1] != source_out[0]) { // There is a range in the original array
        // The new start and end indices should roughly be half of the original indices
        EXPECT_NEAR(follow_out[0], source_out[0] / 2, 1);
        EXPECT_NEAR(follow_out[1], source_out[1] / 2, 1);
    } else {
        // If the target was alone or not found, the follow-up results should be the same as the original
        EXPECT_EQ(follow_out, source_out);
    }
}

/**
 * @brief Metamorphic relation 45: Replacing target with nearest greater nonexistent element results in a range of {-1, -1}.
 */
TEST_P(GetRangeParamTest, MR45) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip if target is at the end or not in array */
    if (source_out[1] == -1 || source_out[1] == vec.size() - 1) {
        return;
    }

    /* Find the nearest greater element than target that doesn't exist in the vector */
    int new_target = vec[source_out[1] + 1] + 1;
    while (std::find(vec.begin(), vec.end(), new_target) != vec.end()) {
        new_target++; // Ensure it's not present in the array
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, new_target);

    /* Verification */
    EXPECT_EQ(follow_out[0], -1);
    EXPECT_EQ(follow_out[1], -1);
}

/**
 * @brief Metamorphic relation 46: Multiplying non-target elements by a factor should not change the index range of the target.
 */
TEST_P(GetRangeParamTest, MR46) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int factor = 2; // Example multiplication factor

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec(vec.size());
    std::transform(vec.begin(), vec.end(), follow_vec.begin(), [target, factor](int element) { return (element == target) ? element : element * factor; });

    /* Sort array as multiplication may disrupt the order */
    std::sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 47: Incrementing the target values results in a new value that should not be found in the array.
 */
TEST_P(GetRangeParamTest, MR47) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip if target is not in array */
    if (source_out[0] == -1) {
        return;
    }

    /* Increment target values by a small amount */
    for (int i = source_out[0]; i <= source_out[1]; ++i) {
        vec[i]++;
    }

    /* Sort array as incrementing may disrupt the order */
    std::sort(vec.begin(), vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(follow_out[0], -1);
    EXPECT_EQ(follow_out[1], -1);
}

/**
 * @brief Metamorphic relation 48: Replacing elements within target range with new target value adjusts range to match the new target.
 */
TEST_P(GetRangeParamTest, MR48) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Determine new target that doesn't exist in the array */
    int new_target = vec.back() + 1;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip if target is not found */
    if (source_out[0] == -1) {
        return;
    }

    /* Replace all occurrences of the old target with the new target */
    std::fill(vec.begin() + source_out[0], vec.begin() + source_out[1] + 1, new_target);

    /* Sort array as it may now be unordered */
    std::sort(vec.begin(), vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, new_target);

    /* Verification */
    EXPECT_EQ(follow_out[0], source_out[0]);
    EXPECT_EQ(follow_out[1], source_out[1]);
}

/**
 * @brief Metamorphic relation 49: Subtracting a constant from all non-target elements leaves the target range unchanged.
 */
TEST_P(GetRangeParamTest, MR49) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int subtract_value = 1; // A constant value to subtract from non-target elements

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1) {
        // If target is not found, skip the test
        return;
    }

    /* Construct follow-up input by subtracting from non-target elements */
    for (int &element : vec) {
        if (element != target) {
            element -= subtract_value;
        }
    }

    // Normally, we would need to sort the resulting vector, but since the
    // subtraction keeps the relative order of the elements, and we are only adjusting
    // non-target elements, the order should still be correct as long as
    // the subtraction does not cause target to be lower than its preceding element.

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 50: Merging two identical arrays extends the range of the target.
 */
TEST_P(GetRangeParamTest, MR50) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);
    size_t original_length = vec.size();

    // Create a merged array of two identical arrays
    vector<int> merged_vec(vec);
    merged_vec.insert(merged_vec.end(), vec.begin(), vec.end());

    /* Sort the merged array */
    std::sort(merged_vec.begin(), merged_vec.end()); // Sorting is required to maintain the sorted property after merging

    /* Get follow-up output */
    vector<int> follow_out = get_range(merged_vec, target);

    /* Verification - only perform verification if target is present */
    if (source_out[0] != -1) {
        EXPECT_EQ(source_out[0], follow_out[0]); // First occurrence remains unchanged
        // End index should be extended by the length of the array since the array was duplicated
        EXPECT_EQ(source_out[1] + original_length, follow_out[1]);
    } else {
        EXPECT_EQ(follow_out[0], -1);
        EXPECT_EQ(follow_out[1], -1);
    }
}

/**
 * @brief Metamorphic relation 51: Removing a non-target element should not change the index range of the target.
 */
TEST_P(GetRangeParamTest, MR51) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    // Identify a non-target element for removal
    int non_target_element = (source_out[0] > 0) ? vec[0] : vec[vec.size() - 1];
    if (non_target_element == target) {
        // If the only non-target is the target itself (all elements are the same), skip the test
        return;
    }

    // Remove non-target element
    vec.erase(std::remove(vec.begin(), vec.end(), non_target_element), vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 52: Repeating the target value adds to its index range.
 */
TEST_P(GetRangeParamTest, MR52) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vec.push_back(target);             // Add an extra target value at the end
    std::sort(vec.begin(), vec.end()); // Sort to maintain order

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    if (source_out[0] != -1) {
        // The range of target indices should be extended to include the new target
        EXPECT_EQ(source_out[0], follow_out[0]);
        EXPECT_EQ(source_out[1] + 1, follow_out[1]);
    } else {
        // If the target was not in the original array, the result should show the new index where it was added
        EXPECT_EQ(vec.size() - 1, follow_out[0]);
        EXPECT_EQ(vec.size() - 1, follow_out[1]);
    }
}

INSTANTIATE_TEST_CASE_P(TrueReturn, GetRangeParamTest, testing::ValuesIn(gen_tcs_randomly()));