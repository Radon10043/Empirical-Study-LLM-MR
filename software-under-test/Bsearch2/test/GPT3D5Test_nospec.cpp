#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <vector>
#include <numeric>

#include "../src/function.h"
#include "utils.h"

using namespace std;

#define SKIP_CRASH

class BSearchParamTest : public ::testing::TestWithParam<BSearch2Input> {};

/**
 * @brief Metamorphic relation 1: Reversing the order of the array elements should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR1) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 2: Shifting the array elements circularly should not affect the output.
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
    rotate(follow_vec.begin(), follow_vec.begin() + 1, follow_vec.end());

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 3: Adding a constant value to all elements of the array should not affect the output.
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
    int constant = 5;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val += constant;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 4: Replacing all elements of the array with their squares should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR4) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val = val * val;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 5: Multiplying all the elements of the array by a constant, then adding another constant to each element, should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR5) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int multiply_constant = 3;
    int add_constant = 2;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val = val * multiply_constant + add_constant;

    int follow_target = target * multiply_constant + add_constant;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 6: Sorting the array should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR6) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 7: Reversing the order of the array elements and negating all elements should not affect the output.
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
    vector<int> follow_vec = vec;
    reverse(follow_vec.begin(), follow_vec.end());
    for (int &val : follow_vec)
        val = -val;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, -target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 8: Multiplying all the elements of the array by -1 should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR8) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val = -val;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, -target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 9: Adding a constant value to the target should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR9) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 10;
    int follow_target = target + constant;

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 10: Replacing all elements of the array with their absolute values should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR10) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;    
    for (int &val : follow_vec)
        val = abs(val);

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 11: Multiplying all the elements of the array by a constant, then taking the modulo by another constant, should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR11) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int multiply_constant = 3;
    int modulo_constant = 7;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val = (val * multiply_constant) % modulo_constant;

    int follow_target = (target * multiply_constant) % modulo_constant;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 12: Applying a bitwise XOR operation to all elements of the array with a constant should not affect the output.
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
    int constant = 20;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val = val ^ constant;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 13: Multiplying all the elements of the array by a constant, then adding a constant, should not affect the output.
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
    int multiply_constant = 3;
    int add_constant = 5;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val = val * multiply_constant + add_constant;

    int follow_target = target * multiply_constant + add_constant;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 14: Concatenating the array with itself should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR14) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.end());

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 15: Multiplying all the elements of the array by -1, then sorting the array, should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR15) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val = -val;
    sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, -target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 16: Reversing the order of the array elements, then multiplying all elements by a constant, should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR16) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 3;
    vector<int> follow_vec = vec;
    reverse(follow_vec.begin(), follow_vec.end());
    for (int &val : follow_vec)
        val *= constant;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target * constant);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 17: Appending a constant value to all elements of the array and then sorting the array, should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR17) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 100;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val += constant;
    sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target + constant);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 18: Appending a constant value to the target and then searching for the result in the original array, should yield the same output.
 *
 */
TEST_P(BSearchParamTest, MR18) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 10;
    int follow_target = target + constant;

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 19: Replacing all occurrences of a specific number in the array with another number, should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR19) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int replace_num = 5;
    int replacement = 10;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec) {
        if (val == replace_num) {
            val = replacement;
        }
    }

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 20: Multiplying the target by a constant, then finding the original target within the array, should yield the same result.
 *
 */
TEST_P(BSearchParamTest, MR20) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 3;
    int follow_target = target * constant;

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 21: Adding a constant value to the target and then multiplying the target by another constant should yield the same result as multiplying the original target by the same constant and then adding the multiple of the constant and the original constant.
 *
 */
TEST_P(BSearchParamTest, MR21) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant1 = 5;
    int constant2 = 3;
    int follow_target = (target + constant1) * constant2;

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 22: Reversing the order of the array elements and then applying a square root to each element should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR22) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    reverse(follow_vec.begin(), follow_vec.end());
    for (int &val : follow_vec)
        val = sqrt(val);

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 23: Replacing all elements of the array with their cube roots should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR23) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val = cbrt(val);

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 24: Flipping the sign of the target and searching for the negative of the original target should yield the same result.
 *
 */
TEST_P(BSearchParamTest, MR24) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int follow_target = -target;

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 25: Reversing the order of the array elements and then applying the absolute value function to each element should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR25) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    reverse(follow_vec.begin(), follow_vec.end());
    for (int &val : follow_vec)
        val = abs(val);

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 26: Sorting the array in descending order should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR26) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    sort(follow_vec.rbegin(), follow_vec.rend());

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 27: Replacing all elements of the array with their absolute differences from a constant value should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR27) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 10;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val = abs(val - constant);

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 28: Replacing all elements of the array with their differences from the mean of the array should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR28) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Calculate mean of the array */
    float mean = accumulate(vec.begin(), vec.end(), 0.0) / vec.size();

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val = val - mean;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 29: Multiplying all the numbers in the array by a constant, then taking the square of each number, should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR29) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 2;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val = pow(val * constant, 2);

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 30: Replacing all elements of the array with their reciprocal should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR30) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    for (int &val : follow_vec) {
        if (val != 0) {
            val = 1 / val;
        }
    }

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 31: Taking the absolute value of the target and searching for the result in the original array should yield the same result.
 *
 */
TEST_P(BSearchParamTest, MR31) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int follow_target = abs(target);

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 32: Multiplying a number by its reciprocal should yield 1, and searching for the result in the array should yield the same index as searching for the original number.
 *
 */
TEST_P(BSearchParamTest, MR32) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_idx = bin_search(vec, target);

    /* Construct follow-up input */
    float reciprocal = 1.0 / target;
    int follow_target = 1;

    /* Get follow-up output */
    int follow_idx = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_idx, follow_idx);
}

/**
 * @brief Metamorphic relation 33: Multiplying all the elements of the array by a constant, then taking the natural logarithm of each element, should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR33) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 2;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val = log(val * constant);

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 34: Cubing each element in the array and then selecting the original target should yield the same result as if the original target was cubed.
 *
 */
TEST_P(BSearchParamTest, MR34) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    int follow_target = pow(target, 3);

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 35: Adding a constant to the array elements and then taking the absolute value should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR35) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 10;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val = abs(val + constant);

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 36: Reversing the array elements should not affect the output for the maximum value.
 *
 */
TEST_P(BSearchParamTest, MR36) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    reverse(vec.begin(), vec.end());

    /* Get follow-up output */
    int follow_out = bin_search(vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 37: Replacing all elements of the array with the square of their differences from a target value should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR37) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 5;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val = pow((val - target), 2);

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 38: Multiplying all the elements of the array by a constant, then dividing by the target, should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR38) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 3;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val = val * constant / target;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 39: Multiplying all the elements of the array by a constant, then adding the target, should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR39) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 2;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val = val * constant + target;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 40: Applying a modulus operation to all elements of the array by a constant and then sorting the array should not affect the output.
 *
 */
TEST_P(BSearchParamTest, MR40) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 3;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val = val % constant;
    sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, BSearchParamTest, testing::ValuesIn(get_tcs_randomly()));