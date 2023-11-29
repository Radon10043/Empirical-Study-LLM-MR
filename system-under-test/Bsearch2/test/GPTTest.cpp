#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <vector>

#include "../function.h"

using namespace std;

#define SKIP_CRASH

typedef struct BSearch2Input {
    BSearch2Input(vector<int> vec, int target) : vec(vec), target(target){};
    vector<int> vec;
    int target;
} BSearch2Input;

class BSearchParamTest : public ::testing::TestWithParam<BSearch2Input> {};

/**
 * Metamorphic relation 1: If the target value is already in the array, add an element greater than the max value in the array to the end of the array, and the output should be unchanged.
 */
TEST_P(BSearchParamTest, MR1) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    if (origin_out == -1)
        return;

    // Construct follow-up input
    vector<int> follow_vec = vec;
    follow_vec.emplace_back(vec.back() + 1);

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 2: Multiply all elements in the array and the element to be located by a constant, the output should remain the same.
 */
TEST_P(BSearchParamTest, MR2) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input
    int constant = 2;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val *= constant;
    int follow_target = target * constant;

    // Get follow-up output
    int follow_out = p(follow_vec, follow_target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 3: If the target value is not in the array, append the target to the end of the array, and the output should be -1.
 */
TEST_P(BSearchParamTest, MR3) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    if (origin_out != -1)
        return;

    // Construct follow-up input
    vector<int> follow_vec = vec;
    follow_vec.emplace_back(target);

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(-1, follow_out);
}

/**
 * Metamorphic relation 4: Reverse the array and the target, the output should remain the same.
 */
TEST_P(BSearchParamTest, MR4) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input
    vector<int> follow_vec = vec;
    reverse(follow_vec.begin(), follow_vec.end());
    int follow_target = -target; // Assuming target is positive

    // Get follow-up output
    int follow_out = p(follow_vec, follow_target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 5: If the array is empty, the output should always be -1, regardless of the target value.
 */
TEST_P(BSearchParamTest, MR5) {
#ifndef SKIP_CRASH
    // Construct an empty array
    vector<int> vec;
    int target = 42; // Choose any target value

    // Get output for the empty array
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (add any value to the empty array)
    vec.push_back(0);

    // Get follow-up output
    int follow_out = p(vec, target, vec.size());

    // Verification
    EXPECT_EQ(-1, origin_out);
    EXPECT_EQ(-1, follow_out);
#endif
}

/**
 * Metamorphic relation 6: If all elements in the array are multiplied by a constant, the target should also be multiplied by the same constant, and the output should remain the same.
 */
TEST_P(BSearchParamTest, MR6) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (multiply array and target by a constant)
    int constant = 3;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val *= constant;
    int follow_target = target * constant;

    // Get follow-up output
    int follow_out = p(follow_vec, follow_target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 7: If all elements in the array are incremented by a constant, the target should also be incremented by the same constant, and the output should remain the same.
 */
TEST_P(BSearchParamTest, MR7) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (increment array and target by a constant)
    int constant = 5;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val += constant;
    int follow_target = target + constant;

    // Get follow-up output
    int follow_out = p(follow_vec, follow_target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 8: If the array has duplicate elements, removing duplicates from the array should not change the output.
 */
TEST_P(BSearchParamTest, MR8) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (remove duplicates from the array)
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());

    // Get follow-up output
    int follow_out = p(vec, target, vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 9: If the array is initially unsorted, sorting the array should not change the output.
 */
TEST_P(BSearchParamTest, MR9) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (sort the array)
    sort(vec.begin(), vec.end());

    // Get follow-up output
    int follow_out = p(vec, target, vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 10: If the array is rotated, the output should remain the same.
 */
TEST_P(BSearchParamTest, MR10) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (rotate the array)
    rotate(vec.begin(), vec.begin() + 1, vec.end()); // rotate one position to the right

    // Get follow-up output
    int follow_out = p(vec, target, vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 11: If the array has repeated occurrences of the target, removing one or more occurrences should not change the output.
 */
TEST_P(BSearchParamTest, MR11) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (remove one or more occurrences of the target)
    auto it = remove(vec.begin(), vec.end(), target);
    vec.erase(it, vec.end());

    // Get follow-up output
    int follow_out = p(vec, target, vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 12: If the array has repeated occurrences of the target, increasing the number of occurrences should not change the output.
 */
TEST_P(BSearchParamTest, MR12) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (increase the number of occurrences of the target)
    vec.push_back(target);

    // Get follow-up output
    int follow_out = p(vec, target, vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 13: If the array has duplicate elements, replacing one occurrence of the target with a different value should not change the output.
 */
TEST_P(BSearchParamTest, MR13) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Find one occurrence of the target and replace it with a different value
    auto it = find(vec.begin(), vec.end(), target);
    if (it != vec.end()) {
        *it = target + 1; // Replace with a different value
    }

    // Get follow-up output
    int follow_out = p(vec, target, vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 14: If the array has duplicate elements, swapping the positions of two occurrences of the target should not change the output.
 */
TEST_P(BSearchParamTest, MR14) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Find two occurrences of the target and swap their positions
    auto it1 = find(vec.begin(), vec.end(), target);
    auto it2 = find(it1 + 1, vec.end(), target);
    if (it1 != vec.end() && it2 != vec.end()) {
        iter_swap(it1, it2);
    }

    // Get follow-up output
    int follow_out = p(vec, target, vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 15: If the array has repeated occurrences of the target, reversing the order of the array should not change the output.
 */
TEST_P(BSearchParamTest, MR15) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (reverse the order of the array)
    reverse(vec.begin(), vec.end());

    // Get follow-up output
    int follow_out = p(vec, target, vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 16: If the array has repeated occurrences of the target, shuffling the elements of the array should not change the output.
 */
TEST_P(BSearchParamTest, MR16) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (shuffle the elements of the array)
    random_shuffle(vec.begin(), vec.end());

    // Get follow-up output
    int follow_out = p(vec, target, vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 17: If the array has repeated occurrences of the target, adding a prefix or suffix to the array should not change the output.
 */
TEST_P(BSearchParamTest, MR17) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (add a prefix or suffix to the array)
    vector<int> follow_vec_prefix = {1, 2, 3}; // Prefix
    follow_vec_prefix.insert(follow_vec_prefix.end(), vec.begin(), vec.end());

    vector<int> follow_vec_suffix = vec; // Suffix
    vector<int> tmp = {4, 5, 6};
    follow_vec_suffix.insert(follow_vec_suffix.end(), tmp.begin(), tmp.end());

    // Get follow-up outputs
    int follow_out_prefix = p(follow_vec_prefix, target, follow_vec_prefix.size());
    int follow_out_suffix = p(follow_vec_suffix, target, follow_vec_suffix.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out_prefix);
    EXPECT_EQ(origin_out, follow_out_suffix);
}

/**
 * Metamorphic relation 18: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while maintaining their frequency should not change the output.
 */
TEST_P(BSearchParamTest, MR18) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order of repeated occurrences)
    vector<int> follow_vec = vec;
    random_shuffle(follow_vec.begin(), follow_vec.end());

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 19: If the array is multiplied by a constant factor, the target should be multiplied by the same factor, and the output should remain the same.
 */
TEST_P(BSearchParamTest, MR19) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (multiply array and target by a constant)
    int constant = 3;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val *= constant;
    int follow_target = target * constant;

    // Get follow-up output
    int follow_out = p(follow_vec, follow_target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 20: If the array is empty, adding elements to the array should not change the output.
 */
TEST_P(BSearchParamTest, MR20) {
#ifndef SKIP_CRASH
    // Construct an empty array
    vector<int> vec;
    int target = 42; // Choose any target value

    // Get output for the empty array
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (add any value to the empty array)
    vec.push_back(0);

    // Get follow-up output
    int follow_out = p(vec, target, vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
#endif
}

/**
 * Metamorphic relation 21: If the array has repeated occurrences of the target, duplicating or removing one or more occurrences should not change the output.
 */
TEST_P(BSearchParamTest, MR21) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (duplicate or remove one or more occurrences of the target)
    auto it = find(vec.begin(), vec.end(), target);
    if (it != vec.end()) {
        vec.insert(it, target); // Duplicate
        // Alternatively, you can remove an occurrence: vec.erase(it);
    }

    // Get follow-up output
    int follow_out = p(vec, target, vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 22: If the array is initially unsorted, sorting only a subset of the array containing the target should not change the output.
 */
TEST_P(BSearchParamTest, MR22) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (sort only a subset of the array containing the target)
    auto target_range = equal_range(vec.begin(), vec.end(), target);
    sort(target_range.first, target_range.second);

    // Get follow-up output
    int follow_out = p(vec, target, vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 23: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while maintaining their frequency should not change the output.
 */
TEST_P(BSearchParamTest, MR23) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order of repeated occurrences while maintaining their frequency)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 24: If the array is initially empty, adding elements to the array should not change the output.
 */
TEST_P(BSearchParamTest, MR24) {
#ifndef SKIP_CRASH
    // Construct an empty array
    vector<int> vec;
    int target = 42; // Choose any target value

    // Get output for the empty array
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (add any value to the empty array)
    vec.push_back(0);

    // Get follow-up output
    int follow_out = p(vec, target, vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
#endif
}

/**
 * Metamorphic relation 25: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while altering their frequency should not change the output.
 */
TEST_P(BSearchParamTest, MR25) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order and frequency of repeated occurrences)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 26: If the array is initially unsorted, sorting a subset of the array not containing the target should not change the output.
 */
TEST_P(BSearchParamTest, MR26) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (sort a subset of the array not containing the target)
    auto target_range = equal_range(vec.begin(), vec.end(), target);
    sort(vec.begin(), target_range.first);
    sort(target_range.second, vec.end());

    // Get follow-up output
    int follow_out = p(vec, target, vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 27: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and adding a prefix or suffix to the array should not change the output.
 */
TEST_P(BSearchParamTest, MR27) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and add a prefix or suffix)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Add a prefix
    vector<int> prefix = {1, 2, 3};
    follow_vec.insert(follow_vec.begin(), prefix.begin(), prefix.end());

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 28: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and removing a subset of the array containing the target should not change the output.
 */
TEST_P(BSearchParamTest, MR28) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and remove a subset containing the target)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Remove a subset containing the target
    follow_vec.erase(target_range.first, target_range.second);

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 29: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and inserting elements randomly within the array should not change the output.
 */
TEST_P(BSearchParamTest, MR29) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and insert elements randomly)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Insert elements randomly
    vector<int> random_elements = {100, 200, 300};
    random_shuffle(random_elements.begin(), random_elements.end());
    follow_vec.insert(follow_vec.begin() + vec.size() / 2, random_elements.begin(), random_elements.end());

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 30: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and reversing a subset of the array containing the target should not change the output.
 */
TEST_P(BSearchParamTest, MR30) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and reverse a subset containing the target)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Reverse a subset containing the target
    reverse(target_range.first, target_range.second);

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 31: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and rotating the array should not change the output.
 */
TEST_P(BSearchParamTest, MR31) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and rotate the array)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Rotate the array
    rotate(follow_vec.begin(), follow_vec.begin() + vec.size() / 2, follow_vec.end());

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 32: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and replacing a subset of the array containing the target should not change the output.
 */
TEST_P(BSearchParamTest, MR32) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and replace a subset containing the target)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Replace a subset containing the target
    replace(target_range.first, target_range.second, target, target + 1);

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 33: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and removing a subset and then adding it back to the array should not change the output.
 */
TEST_P(BSearchParamTest, MR33) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, remove a subset, and add it back)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Remove a subset containing the target
    follow_vec.erase(target_range.first, target_range.second);

    // Add the removed subset back to the array
    follow_vec.insert(follow_vec.end(), target_range.first, target_range.second);

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 34: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and reversing the entire array should not change the output.
 */
TEST_P(BSearchParamTest, MR34) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and reverse the entire array)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Reverse the entire array
    reverse(follow_vec.begin(), follow_vec.end());

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 35: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and inserting a subset of the array containing the target in a different position should not change the output.
 */
TEST_P(BSearchParamTest, MR35) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and insert a subset in a different position)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Insert the subset in a different position
    follow_vec.insert(follow_vec.begin() + vec.size() / 2, target_range.first, target_range.second);

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 36: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and replacing a subset of the array containing the target with a different set of elements should not change the output.
 */
TEST_P(BSearchParamTest, MR36) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and replace a subset with different elements)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Replace the subset with different elements
    replace(target_range.first, target_range.second, target, target + 1);

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 37: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and interleaving the array with a different set of elements should not change the output.
 */
TEST_P(BSearchParamTest, MR37) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and interleave with a different set of elements)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Interleave with a different set of elements
    vector<int> interleaved_elements = {100, 200, 300};
    vector<int> interleaved_vec;
    for (size_t i = 0; i < follow_vec.size(); ++i) {
        interleaved_vec.push_back(follow_vec[i]);
        if (i < interleaved_elements.size()) {
            interleaved_vec.push_back(interleaved_elements[i]);
        }
    }

    // Get follow-up output
    int follow_out = p(interleaved_vec, target, interleaved_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 38: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and shuffling the entire array should not change the output.
 */
TEST_P(BSearchParamTest, MR38) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and shuffle the entire array)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the entire array
    random_shuffle(follow_vec.begin(), follow_vec.end());

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 39: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and rotating a subset of the array containing the target should not change the output.
 */
TEST_P(BSearchParamTest, MR39) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and rotate a subset containing the target)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Rotate a subset containing the target
    rotate(target_range.first, target_range.first + 1, target_range.second);

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 40: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and reversing a subset of the array not containing the target should not change the output.
 */
TEST_P(BSearchParamTest, MR40) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and reverse a subset not containing the target)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Reverse a subset not containing the target
    reverse(follow_vec.begin(), target_range.first);

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 41: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and replacing a subset containing the target with the same set of elements in a different order should not change the output.
 */
TEST_P(BSearchParamTest, MR41) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and replace a subset with the same elements in a different order)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Replace a subset with the same elements in a different order
    replace(target_range.first, target_range.second, target, target);
    reverse(target_range.first, target_range.second);

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 42: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and adding a prefix to the array should not change the output.
 */
TEST_P(BSearchParamTest, MR42) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and add a prefix to the array)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Add a prefix to the array
    vector<int> prefix = {1, 2, 3};
    follow_vec.insert(follow_vec.begin(), prefix.begin(), prefix.end());

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 43: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and replacing a subset not containing the target with a different set of elements should not change the output.
 */
TEST_P(BSearchParamTest, MR43) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and replace a subset not containing the target)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Replace a subset not containing the target with a different set of elements
    replace(target_range.second, follow_vec.end(), target, target + 1);

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 44: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and removing a prefix from the array should not change the output.
 */
TEST_P(BSearchParamTest, MR44) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and remove a prefix from the array)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Remove a prefix from the array
    follow_vec.erase(follow_vec.begin(), follow_vec.begin() + 3);

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 45: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and swapping the positions of two elements not containing the target should not change the output.
 */
TEST_P(BSearchParamTest, MR45) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and swap positions of two elements not containing the target)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Swap positions of two elements not containing the target
    iter_swap(follow_vec.begin() + 1, follow_vec.begin() + 3);

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 46: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and replacing a subset not containing the target with the same set of elements in reverse order should not change the output.
 */
TEST_P(BSearchParamTest, MR46) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and replace a subset not containing the target with the same elements in reverse order)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Replace a subset not containing the target with the same elements in reverse order
    reverse(follow_vec.begin() + 1, follow_vec.begin() + 4);

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 47: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and replacing a subset containing the target with a subset not containing the target should not change the output.
 */
TEST_P(BSearchParamTest, MR47) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and replace a subset containing the target with a subset not containing the target)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Replace a subset containing the target with a subset not containing the target
    vector<int> replacement_subset = {1, 2, 3};
    follow_vec.erase(target_range.first, target_range.second);
    follow_vec.insert(target_range.first, replacement_subset.begin(), replacement_subset.end());

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 48: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and replacing a subset not containing the target with a subset containing the target should not change the output.
 */
TEST_P(BSearchParamTest, MR48) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and replace a subset not containing the target with a subset containing the target)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Replace a subset not containing the target with a subset containing the target
    vector<int> replacement_subset = {target, target};
    follow_vec.erase(target_range.first, target_range.second);
    follow_vec.insert(target_range.first, replacement_subset.begin(), replacement_subset.end());

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 49: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and replacing a subset containing the target with a reversed version of that subset should not change the output.
 */
TEST_P(BSearchParamTest, MR49) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and replace a subset containing the target with a reversed version of that subset)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Replace a subset containing the target with a reversed version of that subset
    reverse(target_range.first, target_range.second);

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 50: If the array has repeated occurrences of the target, changing the order of the repeated occurrences while modifying their frequency and replacing a subset not containing the target with a reversed version of that subset should not change the output.
 */
TEST_P(BSearchParamTest, MR50) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get origin output
    int origin_out = p(vec, target, vec.size());

    // Construct follow-up input (change the order, frequency, and replace a subset not containing the target with a reversed version of that subset)
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    // Increase the frequency of the target
    follow_vec.insert(follow_vec.end(), {target, target});

    // Shuffle the repeated occurrences
    auto target_range = equal_range(follow_vec.begin(), follow_vec.end(), target);
    random_shuffle(target_range.first, target_range.second);

    // Replace a subset not containing the target with a reversed version of that subset
    reverse(follow_vec.begin() + 1, follow_vec.begin() + 4);

    // Get follow-up output
    int follow_out = p(follow_vec, target, follow_vec.size());

    // Verification
    EXPECT_EQ(origin_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, BSearchParamTest,
                        testing::Values(BSearch2Input({1, 2, 3, 4, 5}, 3), BSearch2Input({1, 2, 3, 4, 5}, 1), BSearch2Input({1, 2, 3, 4, 5}, 99)));