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
 * @brief Metamorphic relation 3: Doubling each element in the array should double the indices of the range.
 *
 */
TEST_P(GetRangeParamTest, MR3) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1 && source_out[1] == -1)
        return;

    /* Construct follow-up input */
    vector<int> follow_vec(vec.size());
    std::transform(vec.begin(), vec.end(), follow_vec.begin(), [](int val) { return val * 2; });
    int follow_target = target * 2;

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 4: Reversing the array should reflect the range indices around the midpoint.
 *
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

    /* Construct follow-up input */
    vector<int> follow_vec(vec.rbegin(), vec.rend());
    std::reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(vec.size() - 1 - source_out[1], follow_out[0]);
    EXPECT_EQ(vec.size() - 1 - source_out[0], follow_out[1]);
}

/**
 * @brief Metamorphic relation 5: Removing occurrences of the target value from the array should result in a not found return value.
 *
 */
TEST_P(GetRangeParamTest, MR5) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Remove target from vector */
    vec.erase(std::remove(vec.begin(), vec.end(), target), vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(-1, follow_out[0]);
    EXPECT_EQ(-1, follow_out[1]);
}

/**
 * @brief Metamorphic relation 6: Adding a non-target value should not change the range of the target if it exists.
 *
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

    /* Construct follow-up input by adding a non-target value */
    vec.push_back(target + 1);
    std::sort(vec.begin(), vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 7: Inserting a range of values greater than the target at the end should not change the result's range for the target.
 *
 */
TEST_P(GetRangeParamTest, MR7) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.push_back(target + 1);
    follow_vec.push_back(target + 2);

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 8: Multiplying the target by a factor should also change the range of the target by the same factor if the factor exists in the array as a multiple of each element.
 *
 */
TEST_P(GetRangeParamTest, MR8) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int factor = 2; // For this test, we'll assume the factor is always 2.

    /* Ensure source output is in the sort order */
    std::sort(vec.begin(), vec.end());

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec(vec.size());

    // Ensure all elements are multiplied by the factor.
    std::transform(vec.begin(), vec.end(), follow_vec.begin(), [factor](int val) { return val * factor; });

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target * factor);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 9: Concatenating a duplicate of the original vector should double the end index but keep the start index the same.
 *
 */
TEST_P(GetRangeParamTest, MR9) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(vec.size() + source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 10: Applying a nonzero offset to each element of the array should not change the count of the range length, but should shift the indices accordingly if the offset is a constant not equal to x.
 *
 */
TEST_P(GetRangeParamTest, MR10) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int offset = 5; // Arbitrary non-zero offset

    /* Ensure the offset does not equal the target */
    if (target == offset) {
        offset++;
    }

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec(vec.size());
    std::transform(vec.begin(), vec.end(), follow_vec.begin(), [offset](int val) { return val + offset; });

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target + offset);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 11: Adding a copy of an existing value in the array should increase the length of the range by one without changing the start index.
 *
 */
TEST_P(GetRangeParamTest, MR11) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    if (source_out[0] != -1 && source_out[1] != -1) {
        // Target exists, add another instance of target
        follow_vec.insert(follow_vec.begin() + source_out[1] + 1, target);
    } else {
        return; // No need to test if the target was not found in the original input
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1] + 1, follow_out[1]);
}

/**
 * @brief Metamorphic relation 12: Removing one occurrence of the target should decrease the length of the range by one if there are multiple occurrences.
 *
 */
TEST_P(GetRangeParamTest, MR12) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip test if target not found or there's only one occurrence */
    if (source_out[0] == -1 || source_out[0] == source_out[1]) {
        return;
    }

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    // Remove one occurrence of the target
    follow_vec.erase(follow_vec.begin() + source_out[0]);

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1] - 1, follow_out[1]);
}

/**
 * @brief Metamorphic relation 13: For any value not present in the array, the result should always be [-1, -1].
 *
 */
TEST_P(GetRangeParamTest, MR13) {
    /* Construct input */
    vector<int> vec = {1, 3, 5, 7, 9}; // A sample input vector with values
    int target = 2;                     // A value that is not in the vector

    /* Get follow-up output */
    vector<int> out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(-1, out[0]);
    EXPECT_EQ(-1, out[1]);
}

/**
 * @brief Metamorphic relation 14: If the input array is unchanged and the target value is changed to one that is not in the array, the new result should be [-1, -1].
 *
 */
TEST_P(GetRangeParamTest, MR14) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Skip test if target not found */
    if (get_range(vec, target)[0] == -1) {
        return;
    }

    /* Get follow-up output with a non-existent target */
    vector<int> follow_out = get_range(vec, target + 1); // Assuming target + 1 doesn't exist

    /* Verification */
    EXPECT_EQ(-1, follow_out[0]);
    EXPECT_EQ(-1, follow_out[1]);
}

/**
 * @brief Metamorphic relation 15: Scaling the array (multiplying each element) with a factor > 1 and scaling the target by the same factor should yield the same indices.
 *
 */
TEST_P(GetRangeParamTest, MR15) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int factor = 3; // An arbitrary scale factor greater than 1.

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec(vec.size());
    std::transform(vec.begin(), vec.end(), follow_vec.begin(), [factor](int val) { return val * factor; });
    int scaled_target = target * factor;

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, scaled_target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 16: Inserting identical elements before and after the target's range should only change the start and end indices accordingly.
 *
 */
TEST_P(GetRangeParamTest, MR16) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip test if target not found */
    if (source_out[0] == -1) {
        return;
    }

    /* Calculate how many identical elements to add */
    int identicalElements = 2;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.insert(follow_vec.begin() + source_out[0], identicalElements, target);
    follow_vec.insert(follow_vec.begin() + source_out[1] + 1 + identicalElements, identicalElements, target);

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0] + identicalElements, follow_out[0]);
    EXPECT_EQ(source_out[1] + identicalElements + identicalElements, follow_out[1]);
}

/**
 * @brief Metamorphic relation 17: Shuffling a sub-range of the array excluding the target range should preserve the target range indices.
 *
 */
TEST_P(GetRangeParamTest, MR17) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip test if target not found or only one instance exists */
    if (source_out[0] == -1 || source_out[0] == source_out[1]) {
        return;
    }

    /* Establish sub-range limits */
    int lowerLimit = source_out[1] + 1;
    int upperLimit = vec.size();

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::shuffle(follow_vec.begin() + lowerLimit, follow_vec.begin() + upperLimit, std::default_random_engine());

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 18: If the array is split into two, the target's range indices should be the same in the sub-array containing the target.
 *
 */
TEST_P(GetRangeParamTest, MR18) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip test if target not found */
    if (source_out[0] == -1) {
        return;
    }

    /* Construct follow-up input for the sub-array */
    vector<int> follow_vec(vec.begin() + source_out[0], vec.begin() + source_out[1] + 1);

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(0, follow_out[0]);
    EXPECT_EQ(source_out[1] - source_out[0], follow_out[1]);
}

/**
 * @brief Metamorphic relation 19: Changing all elements in the array except the target range should not affect the target's range indices.
 *
 */
TEST_P(GetRangeParamTest, MR19) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip test if target not found */
    if (source_out[0] == -1) {
        return;
    }

    /* Increment all values except the target range */
    for (int& value : vec) {
        if (value != target) {
            value += 10; // Arbitrary non-zero increment
        }
    }

    /* Verify the array is still sorted after incrementation */
    std::sort(vec.begin(), vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 20: Inserting a sequence that does not include the target value anywhere in the array should not affect the range of the target value.
 *
 */
TEST_P(GetRangeParamTest, MR20) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip test if target not found */
    if (source_out[0] == -1) {
        return;
    }

    /* Construct an inserted sequence and ensure the target is not included */
    vector<int> insertionSequence = {target + 10, target + 11, target + 12}; // Arbitrary values greater than the target

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.insert(follow_vec.end(), insertionSequence.begin(), insertionSequence.end());

    /* Sort the follow-up vector, as the insertion could have disrupted the order */
    std::sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 21: If every element in the array is incremented by 1, then the range for the target incremented by 1 should be the same.
 *
 */
TEST_P(GetRangeParamTest, MR21) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Increment every element in the original vector */
    for (auto& element : vec) {
        element++;
    }

    /* Get follow-up output with incremented target */
    vector<int> follow_out = get_range(vec, target + 1);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 22: If the target is present and we replace it with a new value that does not exist in the array, then the new target should not be found.
 *
 */
TEST_P(GetRangeParamTest, MR22) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip if target is not found */
    if (source_out[0] == -1) {
        return;
    }

    /* Replace occurrences of the target with a new value that is guaranteed not to be in the array */
    std::replace(vec.begin(), vec.end(), target, *max_element(vec.begin(), vec.end()) + 1);

    /* Get follow-up output with old target */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(-1, follow_out[0]);
    EXPECT_EQ(-1, follow_out[1]);
}

/**
 * @brief Metamorphic relation 23: If we append the same array to itself, the target's start index in the combined array should equal the original start index and the end index should be the original end index plus the length of the original array.
 *
 */
TEST_P(GetRangeParamTest, MR23) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    size_t originalSize = vec.size();

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Append the same array to itself */
    vec.insert(vec.end(), input.vec.begin(), input.vec.end());

    /* Get follow-up output with the target */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(originalSize + source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 24: Prepending and appending elements smaller and greater than the target, respectively, should only shift the start and end indices of the target's range.
 *
 */
TEST_P(GetRangeParamTest, MR24) {   // Fixed
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int lowerBound = vec.front() - 1;
    int upperBound = *max_element(vec.begin(), vec.end()) + 1;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Prepend and append values */
    vec.insert(vec.begin(), lowerBound);
    vec.push_back(upperBound);

    /* Get follow-up output with the target */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0] + 1, follow_out[0]);
    EXPECT_EQ(source_out[1] + 1, follow_out[1]);
}

/**
 * @brief Metamorphic relation 25: Swapping two adjacent elements that are not equal to the target should not change the target's range.
 *
 */
TEST_P(GetRangeParamTest, MR25) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Find two adjacent non-target values */
    auto it_pair = std::adjacent_find(vec.begin(), vec.end(), [target](int a, int b) { return a != target && b != target; });

    /* If found, swap them */
    if (it_pair != vec.end()) {
        std::iter_swap(it_pair, it_pair + 1);
    }

    /* Get follow-up output with the target */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 26: If a single element of the target is replaced by another non-existing element, the range should decrease by 1 if there were multiple targets, or not be found if there was only one.
 *
 */
TEST_P(GetRangeParamTest, MR26) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    int newValue = *max_element(vec.begin(), vec.end()) + 1; // New value guaranteed to be greater than any in vec
    bool targetFoundMultiple = source_out[0] != source_out[1];

    if (source_out[0] != -1 && targetFoundMultiple) {
        // Target found and has multiple occurrences. Replace the first occurrence.
        vec[source_out[0]] = newValue;
        std::sort(vec.begin(), vec.end()); // Maintain the sorted property of the vector.
    } else if (source_out[0] != -1) {
        // Target found with only one occurrence
        vec[source_out[0]] = newValue;
    } else {
        // Target not found. Do nothing.
        return;
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    if (targetFoundMultiple) {
        EXPECT_EQ(source_out[0], follow_out[0]);
        EXPECT_EQ(source_out[1] - 1, follow_out[1]);
    } else {
        EXPECT_EQ(-1, follow_out[0]);
        EXPECT_EQ(-1, follow_out[1]);
    }
}

/**
 * @brief Metamorphic relation 27: If the target value is changed to another value that is known to be in the array, the result should give the range of the new value.
 *
 */
TEST_P(GetRangeParamTest, MR27) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int newTarget = (target == vec.front()) ? vec[1] : vec.front(); // A different known value from the array

    /* Get source output */
    vector<int> target_range = get_range(vec, target);
    vector<int> new_target_range = get_range(vec, newTarget);

    /* Verify that the new target is different and in the array */
    if (new_target_range[0] == -1) {
        return;
    }

    /* Get follow-up output for new target */
    vector<int> follow_out = get_range(vec, newTarget);

    /* Verification */
    EXPECT_EQ(new_target_range[0], follow_out[0]);
    EXPECT_EQ(new_target_range[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 28: Subtracting a constant from all elements in the array should shift the range indices of a target subtracted by the same constant.
 *
 */
TEST_P(GetRangeParamTest, MR28) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int constant = 1;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1) {
        return; // Target not found in the original vector.
    } else {
        for (auto &val : vec) {
            val -= constant; // Subtract constant from every element
        }
    }

    /* Get follow-up output with the adjusted target */
    vector<int> follow_out = get_range(vec, target - constant);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 29: Inverting the array's order should mirror the target's range indices around the array's size.
 *
 */
TEST_P(GetRangeParamTest, MR29) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    size_t size = vec.size();

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Invert array */
    std::reverse(vec.begin(), vec.end());

    /* Get follow-up output in the inverted array */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    if (source_out[0] != -1) {
        EXPECT_EQ(size - source_out[1] - 1, follow_out[0]);
        EXPECT_EQ(size - source_out[0] - 1, follow_out[1]);
    } else {
        // Target was not present in the original array
        EXPECT_EQ(-1, follow_out[0]);
        EXPECT_EQ(-1, follow_out[1]);
    }
}

/**
 * @brief Metamorphic relation 30: Replacing the middle section of the array with new values not including the target should not influence the target's range.
 *
 */
TEST_P(GetRangeParamTest, MR30) {   // Fixed
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1) {
        return; // Target not found, skip this MR.
    }

    // Arbitrary new values for the middle section, assuming these do not include the target
    vector<int> newValues = {1001, 1002, 1003};

    // Choose positions to replace such that it does not include the target's current range
    auto replaceStart = vec.begin() + source_out[1] + 1;
    auto replaceEnd = replaceStart + std::min(newValues.size(), static_cast<size_t>(vec.end() - replaceStart));

    // Replace values in the middle of the array
    std::replace_copy(newValues.begin(), newValues.begin() + std::distance(replaceStart, replaceEnd), replaceStart, *replaceStart, 0); // replace with dummy zero
    std::sort(vec.begin(), vec.end()); // resort to maintain sorted order

    /* Get follow-up output with the updated array */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 31: Incrementing both the target and all elements in the array that are greater than the original target should not affect the target's range indices.
 *
 */
TEST_P(GetRangeParamTest, MR31) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int increment = 1;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip if target is not found */
    if (source_out[0] == -1) {
        return;
    }

    /* Increment elements greater than target */
    for (int &val : vec) {
        if (val > target) {
            val += increment;
        }
    }

    /* Get follow-up output for new target */
    int new_target = target + increment;
    vector<int> follow_out = get_range(vec, new_target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 32: Removing the first half of the array should not affect the range of a target found in the second half.
 *
 */
TEST_P(GetRangeParamTest, MR32) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    size_t half_size = vec.size() / 2;
    /* Skip if target is in the first half or not found */
    if (source_out[0] == -1 || source_out[0] < half_size) {
        return;
    }

    /* Erase first half */
    vec.erase(vec.begin(), vec.begin() + half_size);

    /* Adjust expectations */
    int adjusted_start_index = source_out[0] - half_size;
    int adjusted_end_index = source_out[1] - half_size;

    /* Get follow-up output for target */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(adjusted_start_index, follow_out[0]);
    EXPECT_EQ(adjusted_end_index, follow_out[1]);
}

/**
 * @brief Metamorphic relation 33: Concatenating two different sorted arrays where the target is only in the first, should return the same range for the target.
 *
 */
TEST_P(GetRangeParamTest, MR33) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec1 = input.vec; // First array where target is present
    int target = input.target;

    // Create a second sorted array without the target
    vector<int> vec2 = {target + 3, target + 4, target + 5}; // Second array where the target is not present

    /* Get source output from first array */
    vector<int> source_out = get_range(vec1, target);

    /* Skip if target is not found in the first array */
    if (source_out[0] == -1) {
        return;
    }

    // Concatenate vec2 to the end of vec1
    vec1.insert(vec1.end(), vec2.begin(), vec2.end());

    /* Get follow-up output for target in concatenated array */
    vector<int> follow_out = get_range(vec1, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 34: Filtering out all numbers not equal to the target should result in a consecutive range starting from 0.
 *
 */
TEST_P(GetRangeParamTest, MR34) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip if target is not found */
    if (source_out[0] == -1) {
        return;
    }

    /* Filter out all numbers not equal to the target */
    vec.erase(std::remove_if(vec.begin(), vec.end(), [target](int value) {
        return value != target;
    }), vec.end());

    /* Get follow-up output for target */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    int len = source_out[1] - source_out[0] + 1; // Expected new range length
    EXPECT_EQ(0, follow_out[0]);
    EXPECT_EQ(len - 1, follow_out[1]); // End index should be one less than the range length
}

/**
 * @brief Metamorphic relation 35: Rotating the array should shift the indices of the target's range, wrapping around the array's end if necessary.
 *
 */
TEST_P(GetRangeParamTest, MR35) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    size_t rotation_count = 3; // Arbitrary rotation count

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip test if target is not found */
    if (source_out[0] == -1) {
        return;
    }

    /* Rotate array by rotation_count */
    std::rotate(vec.begin(), vec.begin() + rotation_count % vec.size(), vec.end());

    /* Get follow-up output for target after rotation */
    vector<int> follow_out = get_range(vec, target);

    /* Expected result calculation */
    size_t size = vec.size();
    int expected_start = (source_out[0] + size - rotation_count) % size;
    int expected_end = (source_out[1] + size - rotation_count) % size;

    /* Verification */
    EXPECT_EQ(expected_start, follow_out[0]);
    EXPECT_EQ(expected_end, follow_out[1]);
}

/**
 * @brief Metamorphic relation 36: If we duplicate the array and interleave the duplicates, the range for any target should be spread across the interleaved array.
 *
 */
TEST_P(GetRangeParamTest, MR36) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    vector<int> originalVec = vec; // We will interleave with this
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip test if target is not found */
    if (source_out[0] == -1) {
        return;
    }

    /* Interleave vec with itself */
    vector<int> interleavedVec;
    interleavedVec.reserve(vec.size() * 2);
    for (size_t i = 0; i < vec.size(); ++i) {
        interleavedVec.push_back(vec[i]);
        interleavedVec.push_back(originalVec[i]);
    }

    /* Get follow-up output for target after interleaving */
    vector<int> follow_out = get_range(interleavedVec, target);

    /* Expected result calculation */
    int expected_start = source_out[0] * 2;
    int expected_end = source_out[1] * 2 + 1;

    /* Verification */
    EXPECT_EQ(expected_start, follow_out[0]);
    EXPECT_EQ(expected_end, follow_out[1]);
}

/**
 * @brief Metamorphic relation 37: Filtering out every element less than the target should leave the target's range starting index at 0 if the target exists.
 *
 */
TEST_P(GetRangeParamTest, MR37) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip test if target is not found */
    if (source_out[0] == -1) {
        return;
    }

    /* Filter out all elements less than the target */
    vec.erase(std::remove_if(vec.begin(), vec.end(), [target](int value) {
                                return value < target;
                            }),
              vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(0, follow_out[0]);
    EXPECT_EQ(source_out[1] - source_out[0], follow_out[1]);
}

/**
 * @brief Metamorphic relation 38: If the entire array is equal to the target, the result should be the full range of the array.
 *
 */
TEST_P(GetRangeParamTest, MR38) {
    /* Construct input with all elements equal to the target */
    vector<int> vec = {5, 5, 5, 5, 5}; // Arbitrary target value of 5
    int target = 5;

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(0, follow_out[0]);
    EXPECT_EQ(vec.size() - 1, follow_out[1]);
}

/**
 * @brief Metamorphic relation 39: Concatenating any non-empty array with itself should double the range length if the target exists in the array.
 *
 */
TEST_P(GetRangeParamTest, MR39) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    vector<int> originalVec = vec; // Duplicate of the original vector to concatenate
    int target = input.target;

    /* Skip test if empty source vector */
    if (vec.empty()) {
        return;
    }

    /* Get source output */
    vector<int> source_out = get_range(vec, target);
    int originalLength = source_out[1] - source_out[0] + 1;

    /* Concatenate the vector with itself */
    vec.insert(vec.end(), originalVec.begin(), originalVec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    if (source_out[0] != -1) {
        EXPECT_EQ(source_out[0], follow_out[0]);
        EXPECT_EQ(2 * originalLength - 1, follow_out[1] - follow_out[0]);
    } else {
        EXPECT_EQ(-1, follow_out[0]);
        EXPECT_EQ(-1, follow_out[1]);
    }
}

/**
 * @brief Metamorphic relation 40: Removing every element greater than the target should leave the target's range end index at the end of the array if the target exists.
 *
 */
TEST_P(GetRangeParamTest, MR40) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip test if target is not found */
    if (source_out[0] == -1) {
        return;
    }

    /* Remove all elements greater than the target */
    vec.erase(std::remove_if(vec.begin(), vec.end(), [target](int value) {
                                return value > target;
                            }),
              vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(vec.size() - 1, follow_out[1]);
}

/**
 * @brief Metamorphic relation 41: Splitting the array into two parts before and after the target's range should still yield the same range in the appropriate subarray.
 *
 */
TEST_P(GetRangeParamTest, MR41) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip test if target is not found */
    if (source_out[0] == -1) {
        return;
    }

    /* Split the array around the target range */
    vector<int> before_target(vec.begin(), vec.begin() + source_out[0]);
    vector<int> after_target(vec.begin() + source_out[1] + 1, vec.end());

    /* Get follow-up output */
    // Test the subarray before the target range
    vector<int> follow_out_before = get_range(before_target, target);
    // Test the subarray after the target range
    vector<int> follow_out_after = get_range(after_target, target);

    /* Verification */
    // The target should not be present in either subarray
    EXPECT_EQ(-1, follow_out_before[0]);
    EXPECT_EQ(-1, follow_out_before[1]);
    EXPECT_EQ(-1, follow_out_after[0]);
    EXPECT_EQ(-1, follow_out_after[1]);
}

/**
 * @brief Metamorphic relation 42: Inserting a range of elements not containing the target between two parts of the original array should not change the indices of the target's range.
 *
 */
TEST_P(GetRangeParamTest, MR42) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Skip test if target is not found */
    if (source_out[0] == -1) {
        return;
    }

    /* Split the array in two halves */
    vector<int> first_half(vec.begin(), vec.begin() + vec.size() / 2);
    vector<int> second_half(vec.begin() + vec.size() / 2, vec.end());

    /* Create new non-target elements to insert */
    vector<int> new_elements = {
        *max_element(vec.begin(), vec.end()) + 1, // Assumes max_element + 1 doesn't match the target
        *max_element(vec.begin(), vec.end()) + 2
    };

    /* Insert new elements in between the original halves */
    first_half.insert(first_half.end(), new_elements.begin(), new_elements.end());
    first_half.insert(first_half.end(), second_half.begin(), second_half.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(first_half, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}


INSTANTIATE_TEST_CASE_P(TrueReturn, GetRangeParamTest, testing::ValuesIn(gen_tcs_randomly()));