#include <gtest/gtest.h>
#include <vector>

#include "../function.h"

using namespace std;

typedef struct BSearch1Input {
    BSearch1Input(vector<int> vec, int target) : vec(vec), target(target) {};
    vector<int> vec;
    int target;
} BSearch1Input;

class BSearchParamTest : public::testing::TestWithParam<BSearch1Input> {

};

/**
 * Metamorphic Relation 1: Add an element to the end of the array and keep the array in ascending order;
 * the output should be unchanged or greater.
 */
TEST_P(BSearchParamTest, MR1) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.emplace_back(vec.back() + 1);

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_LE(origin_out, follow_out);
}

/**
 * Metamorphic Relation 2: Multiply all elements in the array and the element to be located by a constant;
 * the output should remain the same.
 */
TEST_P(BSearchParamTest, MR2) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    int constant = 2;
    vector<int> follow_vec = vec;
    for (int& val : follow_vec)
        val *= constant;
    int follow_target = target * constant;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 3: Reverse the order of elements in the array; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR3) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 4: Shuffle the elements in the array; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR4) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::random_shuffle(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 5: Add a constant to all elements in the array and the element to be located; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR5) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    int constant = 5;
    vector<int> follow_vec = vec;
    for (int& val : follow_vec)
        val += constant;
    int follow_target = target + constant;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 6: Remove an element from the array, and the element to be located; the output should be -1 (indicating that the target is not present).
 */
TEST_P(BSearchParamTest, MR6) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.pop_back();  // Remove the last element

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(-1, follow_out);
}

/**
 * Metamorphic Relation 7: Change the target to an element that is not present in the array; the output should be -1.
 */
TEST_P(BSearchParamTest, MR7) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    int non_present_target = target + 1;

    /* Get follow-up output */
    int follow_out = BinSearch(vec, non_present_target, 0, vec.size() - 1);

    /* Verification */
    EXPECT_EQ(-1, follow_out);
}

/**
 * Metamorphic Relation 8: Change the array to be an empty array; the output should be -1.
 */
TEST_P(BSearchParamTest, MR8) {
    /* Get input data */
    BSearch1Input input = GetParam();
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch({}, target, 0, 0);

    /* Verification */
    EXPECT_EQ(-1, origin_out);
}

/**
 * Metamorphic Relation 9: Duplicate all elements in the array and the target; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR9) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.end());  // Duplicate elements
    int follow_target = target * 2;  // Duplicate the target

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 10: Rotate the array to the right by a certain number of positions, keeping the elements in ascending order; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR10) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    int rotate_positions = 2; // Change this value to rotate by a different number of positions
    vector<int> follow_vec = vec;
    std::rotate(follow_vec.rbegin(), follow_vec.rbegin() + rotate_positions, follow_vec.rend());

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 11: Square all elements in the array and the target; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR11) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return x * x; });
    int follow_target = target * target;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation: Change the array to be a constant value; the output should be -1 if the target is not equal to the constant, otherwise, the output should be 0.
 */
TEST_P(BSearchParamTest, MR12) {
    /* Get input data */
    BSearch1Input input = GetParam();
    int target = input.target;

    /* Construct follow-up input */
    int constant = 42;  // Change this value to a constant
    vector<int> follow_vec(input.vec.size(), constant);

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    if (target == constant) {
        EXPECT_EQ(0, follow_out);
    } else {
        EXPECT_EQ(-1, follow_out);
    }
}

/**
 * Metamorphic Relation 13: Reverse the order of elements in the array and negate all values; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR13) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::reverse(follow_vec.begin(), follow_vec.end());
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), std::negate<int>());

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 14: Add a constant to all elements in the array and subtract the constant from the target; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR14) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    int constant = 10;  // Change this value to a constant
    vector<int> follow_vec = vec;
    for (int& val : follow_vec)
        val += constant;
    int follow_target = target - constant;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 15: Add an element to the middle of the array; the output should be unchanged or greater
 */
TEST_P(BSearchParamTest, MR15) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    int middle = follow_vec.size() / 2;
    follow_vec.insert(follow_vec.begin() + middle, vec.back() + 1);

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_LE(origin_out, follow_out);
}

/**
 * Metamorphic Relation 16: Divide all elements in the array and the target by a constant; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR16) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    int constant = 2;  // Change this value to a constant
    vector<int> follow_vec = vec;
    for (int& val : follow_vec)
        val /= constant;
    int follow_target = target / constant;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 17: Swap the first and last elements in the array; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR17) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::swap(follow_vec.front(), follow_vec.back());

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 18: Replace all elements in the array with the square root of each element; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR18) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return std::sqrt(x); });

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 19: Increment all elements in the array and increment the target by the same value; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR19) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    int increment_value = 5;  // Change this value to an increment value
    vector<int> follow_vec = vec;
    for (int& val : follow_vec)
        val += increment_value;
    int follow_target = target + increment_value;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 20: Reverse the order of elements in the array and keep the target unchanged; the output should remain the same.
*/
TEST_P(BSearchParamTest, MR20) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 21: Change the array to be a repeated sequence of the original array; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR21) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    int repeat_factor = 3;  // Change this value to control repetition
    vector<int> follow_vec;
    for (int i = 0; i < repeat_factor; ++i)
        follow_vec.insert(follow_vec.end(), vec.begin(), vec.end());

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 22: Subtract a constant from all elements in the array and add the constant to the target; the output should remain the same.
*/
TEST_P(BSearchParamTest, MR22) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    int constant = 7;  // Change this value to a constant
    vector<int> follow_vec = vec;
    for (int& val : follow_vec)
        val -= constant;
    int follow_target = target + constant;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 23: Add a constant to the target; the output should remain the same.
*/
TEST_P(BSearchParamTest, MR23) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    int constant = 5;  // Change this value to a constant
    int follow_target = target + constant;

    /* Get follow-up output */
    int follow_out = BinSearch(vec, follow_target, 0, vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 24: Double the array size by appending the original array to itself; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR24) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.end());

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation: Randomly shuffle the array; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR25) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::random_shuffle(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 26: Insert a constant value into the middle of the array; the output should remain the same or increase.
 */
TEST_P(BSearchParamTest, MR26) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    int constant = 15;  // Change this value to a constant
    vector<int> follow_vec = vec;
    follow_vec.insert(follow_vec.begin() + follow_vec.size() / 2, constant);

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_LE(origin_out, follow_out);
}

/**
 * Metamorphic Relation 27: Replace all elements in the array with a constant value; the output should be -1 if the target is not equal to the constant, otherwise, the output should be 0.
 */
TEST_P(BSearchParamTest, MR27) {
    /* Get input data */
    BSearch1Input input = GetParam();
    int target = input.target;

    /* Construct follow-up input */
    int constant = 10;  // Change this value to a constant
    vector<int> follow_vec(input.vec.size(), constant);

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    if (target == constant) {
        EXPECT_EQ(0, follow_out);
    } else {
        EXPECT_EQ(-1, follow_out);
    }
}

/**
 * Metamorphic Relation 28: Reverse the order of elements in the array and take the absolute value of each element; the output should remain the same.
*/
TEST_P(BSearchParamTest, MR28) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::reverse(follow_vec.begin(), follow_vec.end());
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return std::abs(x); });

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 29: Remove an element from the array and subtract 1 from the target; the output should be unchanged or -1.
*/
TEST_P(BSearchParamTest, MR29) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.pop_back();  // Remove the last element
    int follow_target = target - 1;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_LE(origin_out, follow_out);
}

/**
 * Metamorphic Relation 30: Multiply all elements in the array by a constant and double the target; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR30) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    int constant = 3;  // Change this value to a constant
    vector<int> follow_vec = vec;
    for (int& val : follow_vec)
        val *= constant;
    int follow_target = target * 2;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 31: Replace all elements in the array with their squares and divide the target by 2; the output should remain the same.
*/
TEST_P(BSearchParamTest, MR31) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return x * x; });
    int follow_target = target / 2;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 32: Replace all elements in the array with their absolute values and subtract the target by 1; the output should remain the same or -1.
*/
TEST_P(BSearchParamTest, MR32) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return std::abs(x); });
    int follow_target = target - 1;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_LE(origin_out, follow_out);
}

/**
 * Metamorphic Relation 33: Replace all elements in the array with their squares and add 1 to the target; the output should remain the same or increase.
*/
TEST_P(BSearchParamTest, MR33) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return x * x; });
    int follow_target = target + 1;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_LE(origin_out, follow_out);
}

/**
 * Metamorphic Relation 34: Increment all elements in the array and multiply the target by the same value; the output should remain the same.
*/
TEST_P(BSearchParamTest, MR34) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    int increment_value = 3;  // Change this value to an increment value
    vector<int> follow_vec = vec;
    for (int& val : follow_vec)
        val += increment_value;
    int follow_target = target * increment_value;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 35: Subtract a constant from the target; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR35) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    int constant = 5;  // Change this value to a constant
    int follow_target = target - constant;

    /* Get follow-up output */
    int follow_out = BinSearch(vec, follow_target, 0, vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 36: Rotate the array to the left by a certain number of positions, keeping the elements in ascending order; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR36) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    int rotate_positions = 2; // Change this value to rotate by a different number of positions
    vector<int> follow_vec = vec;
    std::rotate(follow_vec.begin(), follow_vec.begin() + rotate_positions, follow_vec.end());

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 37: Divide the array into two parts and switch their positions; the output should remain the same.
*/
TEST_P(BSearchParamTest, MR37) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    int split_index = vec.size() / 2;
    vector<int> follow_vec = vec;
    std::rotate(follow_vec.begin(), follow_vec.begin() + split_index, follow_vec.end());

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 38: Replace all elements in the array with their cubes and triple the target; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR38) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return x * x * x; });
    int follow_target = target * 3;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation: Replace all elements in the array with their logarithmic values (base 2) and divide the target by 2; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR39) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return static_cast<int>(log2(x)); });
    int follow_target = target / 2;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 40: Replace all elements in the array with their square roots and subtract 1 from the target; the output should remain the same or -1.
 */
TEST_P(BSearchParamTest, MR40) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return static_cast<int>(sqrt(x)); });
    int follow_target = target - 1;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_LE(origin_out, follow_out);
}

/**
 * Metamorphic Relation 41: Replace all elements in the array with their negations and subtract the target from 1; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR41) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), std::negate<int>());
    int follow_target = 1 - target;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 42: Replace all elements in the array with their reciprocals, and divide the target by the reciprocal of a constant; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR42) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    double constant = 2.5;  // Change this value to a constant
    vector<double> follow_vec(vec.begin(), vec.end());
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [constant](double x) { return 1 / x; });
    double follow_target = target / (1 / constant);

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, static_cast<int>(follow_target), 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 43: Replace all elements in the array with their absolute values and subtract 1 from the target; the output should remain the same or -1.
 */
TEST_P(BSearchParamTest, MR43) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return std::abs(x); });
    int follow_target = target - 1;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_LE(origin_out, follow_out);
}

/**
 * Metamorphic Relation 44: Replace all elements in the array with their square roots and subtract 1 from the target; the output should remain the same or -1.
*/
TEST_P(BSearchParamTest, MR44) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return static_cast<int>(std::sqrt(x)); });
    int follow_target = target - 1;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_LE(origin_out, follow_out);
}

/**
 * Metamorphic Relation 45: Subtract a constant from all elements in the array and divide the target by the constant; the output should remain the same.
 */
TEST_P(BSearchParamTest, MR45) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    int constant = 5;  // Change this value to a constant
    vector<int> follow_vec = vec;
    for (int& val : follow_vec)
        val -= constant;
    int follow_target = target / constant;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 46: Reverse the order of elements in the array and add 1 to the target; the output should remain the same or increase.
*/
TEST_P(BSearchParamTest, MR46) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::reverse(follow_vec.begin(), follow_vec.end());
    int follow_target = target + 1;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_LE(origin_out, follow_out);
}

/**
 * Metamorphic Relation 47: Replace all elements in the array with their squares and subtract 1 from the target; the output should remain the same or decrease.
*/
TEST_P(BSearchParamTest, MR47) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return x * x; });
    int follow_target = target - 1;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_LE(origin_out, follow_out);
}

/**
 * Metamorphic Relation 48: Reverse the order of elements in the array and take the absolute value of each element; the output should remain the same.
*/
TEST_P(BSearchParamTest, MR48) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::reverse(follow_vec.begin(), follow_vec.end());
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return std::abs(x); });

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic Relation 49: Replace all elements in the array with their cubes and add 1 to the target; the output should remain the same or increase.
*/
TEST_P(BSearchParamTest, MR49) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return x * x * x; });
    int follow_target = target + 1;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_LE(origin_out, follow_out);
}

/**
 * Metamorphic Relation 50: Replace all elements in the array with their negations and add 1 to the target; the output should remain the same.
*/
TEST_P(BSearchParamTest, MR50) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get original output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), std::negate<int>());
    int follow_target = target + 1;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_LE(origin_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TreuReturn, BSearchParamTest, testing::Values(
    BSearch1Input({1,2,3,4,5}, 3),
    BSearch1Input({1,2,3,4,5}, 1),
    BSearch1Input({1,2,3,4,5}, 99)
));