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

// Metamorphic relation 1: If the target value is already in the array,
// add an element greater than the max value in the array to the end of the array,
// and the output should be unchanged.
TEST_P(BSearchParamTest, MR1) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    if (!origin_out) return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.emplace_back(vec.back() + 1);

    /* Get follow-up output */
    int follow_out = p(follow_vec, target, follow_vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 2: Multiply all elements in the array and the element to be located
// by a constant, the output should remain the same.
TEST_P(BSearchParamTest, MR2) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    int constant = 2;
    vector<int> follow_vec = vec;
    for (int& val : follow_vec)
        val *= constant;
    int follow_target = target * constant;

    /* Get follow-up output */
    int follow_out = p(follow_vec, follow_target, follow_vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 3: Reverse the order of elements in the array,
// and the output should remain the same.
TEST_P(BSearchParamTest, MR3) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    reverse(vec.begin(), vec.end());

    /* Get follow-up output */
    int follow_out = p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 4: Add a constant to all elements in the array
// and to the element to be located, the output should remain the same.
TEST_P(BSearchParamTest, MR4) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    int constant = 5;
    vector<int> follow_vec = vec;
    for (int& val : follow_vec)
        val += constant;
    int follow_target = target + constant;

    /* Get follow-up output */
    int follow_out = p(follow_vec, follow_target, follow_vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 5: Replace all elements in the array with their squares,
// and square the element to be located, the output should remain the same.
TEST_P(BSearchParamTest, MR5) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    transform(vec.begin(), vec.end(), vec.begin(),
                   [](int val) { return val * val; });
    int follow_target = target * target;

    /* Get follow-up output */
    int follow_out = p(vec, follow_target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 6: Remove the first element from the array,
// and the element to be located is not present in the modified array,
// the output should be 0 (not found).
TEST_P(BSearchParamTest, MR6) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    if (!vec.empty()) {
        vec.erase(vec.begin());
    }

    /* Get follow-up output */
    int follow_out = p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(0, follow_out);
}

// Metamorphic relation 7: Swap the positions of the first and last elements in the array,
// and the output should remain the same.
TEST_P(BSearchParamTest, MR7) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    if (vec.size() >= 2) {
        swap(vec.front(), vec.back());
    }

    /* Get follow-up output */
    int follow_out = p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 8: Shuffle the elements randomly in the array,
// and the output should remain the same.
TEST_P(BSearchParamTest, MR8) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    random_shuffle(vec.begin(), vec.end());

    /* Get follow-up output */
    int follow_out = p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 9: Add a duplicate of the target element to the array,
// and the output should remain the same.
TEST_P(BSearchParamTest, MR9) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    vec.push_back(target);

    /* Get follow-up output */
    int follow_out = p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 10: Subtract a constant from all elements in the array
// and from the element to be located, the output should remain the same.
TEST_P(BSearchParamTest, MR10) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    int constant = 3;
    vector<int> follow_vec = vec;
    for (int& val : follow_vec)
        val -= constant;
    int follow_target = target - constant;

    /* Get follow-up output */
    int follow_out = p(follow_vec, follow_target, follow_vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 11: Rotate the array to the right by one position,
// and the output should remain the same.
TEST_P(BSearchParamTest, MR11) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    if (!vec.empty()) {
        rotate(vec.rbegin(), vec.rbegin() + 1, vec.rend());
    }

    /* Get follow-up output */
    int follow_out = p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 12: Insert the target element at the beginning of the array,
// and the output should be 1 (target found) since it is now the first element.
TEST_P(BSearchParamTest, MR12) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    vec.insert(vec.begin(), target);

    /* Get follow-up output */
    int follow_out = p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(1, follow_out);
}

// Metamorphic relation 13: Reverse the order of the array and negate all elements,
// and the output should remain the same.
TEST_P(BSearchParamTest, MR13) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    reverse(vec.begin(), vec.end());
    transform(vec.begin(), vec.end(), vec.begin(), negate<int>());

    /* Get follow-up output */
    int follow_out = p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 14: Multiply all elements in the array by a constant,
// and double the target element, the output should remain the same.
TEST_P(BSearchParamTest, MR14) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    int constant = 3;
    vector<int> follow_vec = vec;
    transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(),
                   [constant](int val) { return val * constant; });
    int follow_target = target * 2;

    /* Get follow-up output */
    int follow_out = p(follow_vec, follow_target, follow_vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 15: Insert a new element greater than the target at the beginning of the array,
// and the output should remain the same.
TEST_P(BSearchParamTest, MR15) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    int newElement = target + 1;
    vec.insert(vec.begin(), newElement);

    /* Get follow-up output */
    int follow_out = p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 16: Replace all occurrences of the target element with a new element,
// and the output should be 0 (target not found) as the target is not present in the modified array.
TEST_P(BSearchParamTest, MR16) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    int newElement = target + 1;
    replace(vec.begin(), vec.end(), target, newElement);

    /* Get follow-up output */
    int follow_out = p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(0, follow_out);
}

// Metamorphic relation 17: Remove all occurrences of the target element from the array,
// and the output should be 0 (target not found) as the target is not present in the modified array.
TEST_P(BSearchParamTest, MR17) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    vec.erase(remove(vec.begin(), vec.end(), target), vec.end());

    /* Get follow-up output */
    int follow_out = p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(0, follow_out);
}

// Metamorphic relation 18: Remove the last element from the array,
// and the output should remain the same unless the target was the last element.
TEST_P(BSearchParamTest, MR18) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    if (!vec.empty()) {
        vec.pop_back();
    }

    /* Get follow-up output */
    int follow_out = (target == vec.back()) ? 1 : p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 19: Replace all elements in the array with a constant value,
// and the output should remain the same unless the target is not equal to the constant.
TEST_P(BSearchParamTest, MR19) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    int constant = 10;
    fill(vec.begin(), vec.end(), constant);

    /* Get follow-up output */
    int follow_out = (target == constant) ? origin_out : p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 20: Duplicate all elements in the array,
// and the output should remain the same unless the target is duplicated as well.
TEST_P(BSearchParamTest, MR20) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    vec.insert(vec.end(), vec.begin(), vec.end());

    /* Get follow-up output */
    int follow_out = (target == vec[vec.size() / 2]) ? origin_out : p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 21: Shuffle the array and then sort it in ascending order,
// the output should remain the same.
TEST_P(BSearchParamTest, MR21) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    random_shuffle(vec.begin(), vec.end());
    sort(vec.begin(), vec.end());

    /* Get follow-up output */
    int follow_out = p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 22: Reverse the order of the array and then sort it in descending order,
// the output should remain the same.
TEST_P(BSearchParamTest, MR22) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    reverse(vec.begin(), vec.end());
    sort(vec.begin(), vec.end(), greater<int>());

    /* Get follow-up output */
    int follow_out = p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 23: Replace all elements in the array with the target element,
// and the output should be 1 (target found) if the array is not empty.
TEST_P(BSearchParamTest, MR23) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    fill(vec.begin(), vec.end(), target);

    /* Get follow-up output */
    int follow_out = (vec.empty()) ? 0 : 1;

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 24: Add the target element at the end of the array twice,
// and the output should be 1 (target found) if the array is not empty.
TEST_P(BSearchParamTest, MR24) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    vec.push_back(target);
    vec.push_back(target);

    /* Get follow-up output */
    int follow_out = (vec.empty()) ? 0 : 1;

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 25: Remove all occurrences of the target element from the array,
// and the output should be 0 (target not found) if the array is not empty.
TEST_P(BSearchParamTest, MR25) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    vec.erase(remove(vec.begin(), vec.end(), target), vec.end());

    /* Get follow-up output */
    int follow_out = (vec.empty()) ? 0 : 1;

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 26: Insert the target element at the beginning and end of the array,
// and the output should be 1 (target found) if the array is not empty.
TEST_P(BSearchParamTest, MR26) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    vec.insert(vec.begin(), target);
    vec.push_back(target);

    /* Get follow-up output */
    int follow_out = (vec.empty()) ? 0 : 1;

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 27: Subtract 1 from all elements in the array and the target element,
// and the output should remain the same.
TEST_P(BSearchParamTest, MR27) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    for_each(vec.begin(), vec.end(), [](int& val) { val -= 1; });
    int follow_target = target - 1;

    /* Get follow-up output */
    int follow_out = p(vec, follow_target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 28: Add 1 to all elements in the array and the target element,
// and the output should remain the same.
TEST_P(BSearchParamTest, MR28) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    for_each(vec.begin(), vec.end(), [](int& val) { val += 1; });
    int follow_target = target + 1;

    /* Get follow-up output */
    int follow_out = p(vec, follow_target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 29: Replace the target element with a new element in the array,
// and the output should be 1 (target found) if the new element is equal to the target.
TEST_P(BSearchParamTest, MR29) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    int newElement = target + 1;
    replace(vec.begin(), vec.end(), target, newElement);

    /* Get follow-up output */
    int follow_out = (newElement == target) ? 1 : p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 30: Reverse the array and replace all occurrences of the target element with a new element,
// and the output should be 0 (target not found) if the new element is not equal to the target.
TEST_P(BSearchParamTest, MR30) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    reverse(vec.begin(), vec.end());
    int newElement = target + 1;
    replace(vec.begin(), vec.end(), target, newElement);

    /* Get follow-up output */
    int follow_out = (newElement != target) ? 0 : p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 31: Rotate the array to the right by a random number of positions,
// and the output should remain the same.
TEST_P(BSearchParamTest, MR31) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    int rotationAmount = rand() % vec.size();
    rotate(vec.rbegin(), vec.rbegin() + rotationAmount, vec.rend());

    /* Get follow-up output */
    int follow_out = p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 32: Reverse the order of the array and swap the target element with the first element,
// and the output should be 1 (target found) if the target is now the first element.
TEST_P(BSearchParamTest, MR32) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    reverse(vec.begin(), vec.end());
    if (!vec.empty()) {
        swap(vec.front(), vec.at(rand() % vec.size()));
    }

    /* Get follow-up output */
    int follow_out = (target == vec.front()) ? 1 : p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 33: Remove the first element from the array and the target element,
// and the output should remain the same unless the target was the first element.
TEST_P(BSearchParamTest, MR33) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    if (!vec.empty()) {
        vec.erase(vec.begin());
    }

    /* Get follow-up output */
    int follow_out = (target == vec.front()) ? 1 : p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 34: Add a new element smaller than the target at the beginning of the array,
// and the output should remain the same unless the target was the first element.
TEST_P(BSearchParamTest, MR34) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    int newElement = target - 1;
    vec.insert(vec.begin(), newElement);

    /* Get follow-up output */
    int follow_out = (target == vec.front()) ? 1 : p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 35: Add a new element greater than the target at the end of the array,
// and the output should remain the same unless the target was the last element.
TEST_P(BSearchParamTest, MR35) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    int newElement = target + 1;
    vec.push_back(newElement);

    /* Get follow-up output */
    int follow_out = (target == vec.back()) ? 1 : p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 36: Remove the last element from the array and the target element,
// and the output should remain the same unless the target was the last element.
TEST_P(BSearchParamTest, MR36) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    if (!vec.empty()) {
        vec.pop_back();
    }

    /* Get follow-up output */
    int follow_out = (target == vec.back()) ? 1 : p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 37: Swap the positions of the target element and the middle element,
// and the output should remain the same unless the target was the middle element.
TEST_P(BSearchParamTest, MR37) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    if (vec.size() >= 3) {
        swap(vec[vec.size() / 2], vec[vec.size() / 2 - 1]);
    }

    /* Get follow-up output */
    int follow_out = (target == vec[vec.size() / 2]) ? 1 : p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 38: Replace all occurrences of the target element with a new element,
// and the output should be 0 (target not found) if the array is not empty.
TEST_P(BSearchParamTest, MR38) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    int newElement = target + 1;
    replace(vec.begin(), vec.end(), target, newElement);

    /* Get follow-up output */
    int follow_out = (vec.empty()) ? 0 : p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 39: Add a new element equal to the target in the middle of the array,
// and the output should be 1 (target found) if the array is not empty.
TEST_P(BSearchParamTest, MR39) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    if (!vec.empty()) {
        vec.insert(vec.begin() + vec.size() / 2, target);
    }

    /* Get follow-up output */
    int follow_out = (vec.empty()) ? 0 : 1;

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 40: Subtract 1 from all elements in the array,
// and the output should remain the same unless the target was 0.
TEST_P(BSearchParamTest, MR40) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    for_each(vec.begin(), vec.end(), [](int& val) { val -= 1; });
    int follow_target = (target == 0) ? 0 : target - 1;

    /* Get follow-up output */
    int follow_out = p(vec, follow_target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 41: Add a new element greater than the target at the beginning and the end of the array,
// and the output should remain the same unless the target was the first or last element.
TEST_P(BSearchParamTest, MR41) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    int newElement = target + 1;
    vec.insert(vec.begin(), newElement);
    vec.push_back(newElement);

    /* Get follow-up output */
    int follow_out = ((target == vec.front()) || (target == vec.back())) ? 1 : p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 42: Multiply all elements in the array by 2,
// and the output should remain the same unless the target was an odd number.
TEST_P(BSearchParamTest, MR42) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    for_each(vec.begin(), vec.end(), [](int& val) { val *= 2; });
    int follow_target = (target % 2 == 1) ? target * 2 : target;

    /* Get follow-up output */
    int follow_out = p(vec, follow_target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 43: Reverse the order of the array and add a new element equal to the target at the beginning,
// and the output should be 1 (target found) if the target is now the first element.
TEST_P(BSearchParamTest, MR43) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    reverse(vec.begin(), vec.end());
    vec.insert(vec.begin(), target);

    /* Get follow-up output */
    int follow_out = (target == vec.front()) ? 1 : p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 44: Replace the target element with a new element in the array,
// and the output should be 0 (target not found) if the array is not empty.
TEST_P(BSearchParamTest, MR44) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    int newElement = target + 1;
    replace(vec.begin(), vec.end(), target, newElement);

    /* Get follow-up output */
    int follow_out = (vec.empty()) ? 0 : p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 45: Insert the target element at random positions in the array,
// and the output should be 1 (target found) if the array is not empty.
TEST_P(BSearchParamTest, MR45) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    if (!vec.empty()) {
        int randomPos = rand() % (vec.size() + 1);
        vec.insert(vec.begin() + randomPos, target);
    }

    /* Get follow-up output */
    int follow_out = (vec.empty()) ? 0 : 1;

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 46: Sort the array in descending order and add a new element smaller than the target at the end,
// and the output should be 0 (target not found) if the array is not empty.
TEST_P(BSearchParamTest, MR46) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    sort(vec.begin(), vec.end(), greater<int>());
    int newElement = target - 1;
    vec.push_back(newElement);

    /* Get follow-up output */
    int follow_out = (vec.empty()) ? 0 : p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 47: Shuffle the array randomly, and the output should remain the same.
TEST_P(BSearchParamTest, MR47) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    random_shuffle(vec.begin(), vec.end());

    /* Get follow-up output */
    int follow_out = p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 48: Remove all elements in the array that are smaller than the target,
// and the output should remain the same unless the target was the smallest element.
TEST_P(BSearchParamTest, MR48) {
#ifndef SKIP_CRASH
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    vec.erase(remove_if(vec.begin(), vec.end(), [target](int val) { return val < target; }), vec.end());

    /* Get follow-up output */
    int follow_out = (target == *min_element(vec.begin(), vec.end())) ? 1 : p(vec, target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
#endif
}

// Metamorphic relation 49: Duplicate all elements in the array and the target element,
// and the output should remain the same.
TEST_P(BSearchParamTest, MR49) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    vec.insert(vec.end(), vec.begin(), vec.end());
    int follow_target = target;

    /* Get follow-up output */
    int follow_out = p(vec, follow_target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

// Metamorphic relation 50: Replace all elements in the array with a constant value,
// and the output should remain the same unless the target was the constant value.
TEST_P(BSearchParamTest, MR50) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    int constant = 42;
    fill(vec.begin(), vec.end(), constant);
    int follow_target = (target == constant) ? target : 0; // Set target to constant value if it was already

    /* Get follow-up output */
    int follow_out = p(vec, follow_target, vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, BSearchParamTest,
                        testing::Values(BSearch2Input({1, 2, 3, 4, 5}, 3), BSearch2Input({1, 2, 3, 4, 5}, 1), BSearch2Input({1, 2, 3, 4, 5}, 99), BSearch2Input({1,1,2,2,3,3,4,4,5,5}, 2)));