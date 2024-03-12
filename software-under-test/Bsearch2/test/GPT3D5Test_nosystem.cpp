#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <vector>
#include <climits>

#include "../src/function.h"
#include "utils.h"

using namespace std;

#define SKIP_CRASH

class BSearchParamTest : public ::testing::TestWithParam<BSearch2Input> {};

/**
 * @brief Metamorphic relation 1: Reversing the order of elements in the vector does not change the result.
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
 * @brief Metamorphic relation 2: Adding a constant to all elements in the vector and to the target value does not change the result.
 */
TEST_P(BSearchParamTest, MR2) {
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
    int follow_target = target + constant;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 3: Replacing all elements in the vector with their square values and the target value with its square does not change the result.
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
    for (int &val : follow_vec)
        val = val * val;
    int follow_target = target * target;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 4: If we swap the position of two elements in the vector while keeping the target value the same, the result should not change.
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
    if(follow_vec.size() >= 2){
        swap(follow_vec[0], follow_vec[1]);
    }

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 5: If all the elements in the vector are incremented by 1 and the target value is decremented by 1, the result should remain the same.
 */
TEST_P(BSearchParamTest, MR5) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    int follow_target = target - 1;
    for (int &val : follow_vec)
        val += 1;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 6: If all the elements in the vector are multiplied by -1 and the target value is also multiplied by -1, the result should remain the same.
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
    int follow_target = target * -1;
    for (int &val : follow_vec)
        val *= -1;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 7: If the target value is greater than all elements in the vector, then the result should be false.
 */
TEST_P(BSearchParamTest, MR7) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;

    // Sort the vector in ascending order
    sort(vec.begin(), vec.end());

    // Get the largest element in the vector
    int largest = vec.back();

    // The target value is greater than the largest element in the vector
    int target = largest + 1;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Verification */
    EXPECT_FALSE(source_out);
}

/**
 * @brief Metamorphic relation 8: If the target value is less than all elements in the vector, then the result should be false.
 */
TEST_P(BSearchParamTest, MR8) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;

    // Sort the vector in ascending order
    sort(vec.begin(), vec.end());

    // The target value is less than the smallest element in the vector
    int target = vec.front() - 1;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Verification */
    EXPECT_FALSE(source_out);
}

/**
 * @brief Metamorphic relation 9: If the input vector is empty, the result should always be false, regardless of the target value.
 */
TEST(BSearchEdgeCases, MR9) {
    /* Construct empty vector */
    vector<int> vec;

    /* Set a target value */
    int target = 5;

    /* Test the function with empty vector */
    bool result = bin_search(vec, target);

    /* Verification */
    EXPECT_FALSE(result);
}

/**
 * @brief Metamorphic relation 10: If the input vector contains only one element and it is the same as the target, the result should be true.
 */
TEST(BSearchEdgeCases, MR10) {
    /* Construct vector with single element */
    vector<int> vec = {10};

    /* Set target value that exists in the vector */
    int target = vec[0];

    /* Test the function with single-element vector */
    bool result = bin_search(vec, target);

    /* Verification */
    EXPECT_TRUE(result);
}

/**
 * @brief Metamorphic relation 11: If the input vector is repeated, the result should remain the same.
 */
TEST_P(BSearchParamTest, MR11) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int i = 0; i < 3; ++i) {
        follow_vec.insert(follow_vec.end(), vec.begin(), vec.end());
    }

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 12: If the input vector is divided into two sub-vectors and the target element is also divided into two sub-targets which are the same number of times, then the result should remain the same.
 */
TEST_P(BSearchParamTest, MR12) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int mid = vec.size() / 2;
    vector<int> sub_vec1(vec.begin(), vec.begin() + mid);
    vector<int> sub_vec2(vec.begin() + mid, vec.end());
    int sub_target1 = target / 2;
    int sub_target2 = target - sub_target1;

    /* Get follow-up output */
    bool follow_out = bin_search(sub_vec1, sub_target1) || bin_search(sub_vec2, sub_target2);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 13: If the input vector and the target element are transformed by sorting them in descending order, the result should not change.
 */
TEST_P(BSearchParamTest, MR13) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Transform input by sorting in descending order */
    sort(vec.rbegin(), vec.rend());
    int target_transformed = target;

    /* Get follow-up output */
    int follow_out = bin_search(vec, target_transformed);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 14: If the input vector contains duplicate elements and the target element is one of the duplicates, the result should remain the same.
 */
TEST(BSearchEdgeCases, MR14) {
    /* Construct vector with duplicate elements */
    vector<int> vec = {5, 5, 5, 5, 5, 5, 5, 5};

    /* Set target value from the duplicates */
    int target = 5;

    /* Test the function with duplicate elements vector */
    bool result = bin_search(vec, target);

    /* Verification */
    EXPECT_TRUE(result);
}

/**
 * @brief Metamorphic relation 15: If the target value is present in the array, then removing all instances of the target value from the array should result in a false output.
 */
TEST_P(BSearchParamTest, MR15) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.erase(remove(follow_vec.begin(), follow_vec.end(), target), follow_vec.end());

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_FALSE(source_out && follow_out);
}

/**
 * @brief Metamorphic relation 16: If all elements in the input vector are incremented by 1, and the target value is also incremented by 1, the result should remain the same.
 */
TEST_P(BSearchParamTest, MR16) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val += 1;
    int follow_target = target + 1;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 17: If the input vector is sorted, the result should remain the same.
 */
TEST_P(BSearchParamTest, MR17) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Sort the input vector in ascending order */
    sort(vec.begin(), vec.end());

    /* Get follow-up output */
    bool follow_out = bin_search(vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 18: If all elements of the input vector are incremented by a constant amount, the result should not change.
 */
TEST_P(BSearchParamTest, MR18) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Increment all elements in the vector by a constant amount */
    vector<int> follow_vec = vec;
    int increment = 5;
    for (int &val : follow_vec) {
        val += increment;
    }

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target + increment);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 20: If all elements in the vector are increased but the target is unchanged, the result should not change.
 */
TEST_P(BSearchParamTest, MR20) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Increase all elements in the vector by 1 */
    for (int &val : vec) {
        val++;
    }

    /* Get follow-up output */
    bool follow_out = bin_search(vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 21: If the input vector contains negative numbers and the target is also negative, changing all inputs and target to their absolute values should not change the result.
 */
TEST_P(BSearchParamTest, MR21) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Change input vector to absolute values */
    vector<int> abs_vec;
    for (int val : vec) {
        abs_vec.push_back(abs(val));
    }

    /* Change target to absolute value */
    int abs_target = abs(target);

    /* Get follow-up output */
    bool follow_out = bin_search(abs_vec, abs_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 22: If we remove negative signs from the input vector and the target, the output remain the same.
 */
TEST_P(BSearchParamTest, MR22) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Remove negative signs from vector and target */
    vector<int> follow_vec;
    for (int val : vec) {
        follow_vec.push_back(abs(val));
    }
    int follow_target = abs(target);

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 23: If  the input vector is doubled by concatenating it with itself and the target value is also doubled, the result should remain the same.
 */
TEST_P(BSearchParamTest, MR23) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.end()); // doubling the vector
    int follow_target = target * 2; // double the target value

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 24: If the input vector has elements added to the beginning of the vector and the position of the target element is shifted accordingly. The result should remain the same.
 */
TEST_P(BSearchParamTest, MR24) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Add elements to the beginning of the vector */
    int new_element = -100;
    vec.insert(vec.begin(), new_element);
    int new_target = target + 1; // target's position is shifted due to new insertion

    /* Get follow-up output */
    bool follow_out = bin_search(vec, new_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 25: If the input vector is reversed, the result should remain the same.
 */
TEST_P(BSearchParamTest, MR25) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Reverse the input vector */
    reverse(vec.begin(), vec.end());

    /* Get follow-up output */
    bool follow_out = bin_search(vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 26: If all elements in the vector are doubled and the target value is also doubled, the result should remain the same.
 */
TEST_P(BSearchParamTest, MR26) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Double all elements in the vector */
    for (int &val : vec) {
        val *= 2;
    }

    /* Double the target value */
    int follow_target = target * 2;

    /* Get follow-up output */
    bool follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 27: If we add 1 to the middle element of the vector and also add 1 to the target, the result should remain the same.
 */
TEST_P(BSearchParamTest, MR27) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Add 1 to the element in the middle of the vector */
    int mid = vec.size() / 2;
    vec[mid] += 1;

    /* Increase the target value by 1 */
    int follow_target = target + 1;

    /* Get follow-up output */
    bool follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 28: If all elements in the vector are decremented by 1 and the target value is also decremented by 1, the result should remain the same.
 */
TEST_P(BSearchParamTest, MR28) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Decrement all elements in the vector by 1 */
    for (int &val : vec) {
        val -= 1;
    }

    /* Decrement the target value by 1 */
    int follow_target = target - 1;

    /* Get follow-up output */
    bool follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 29: If the input vector is multiplied by a negative number and the target value is also multiplied by a negative number, the result should remain the same.
 */
TEST_P(BSearchParamTest, MR29) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Multiply all elements in the vector by -1 */
    for (int &val : vec) {
        val *= -1;
    }

    /* Multiply the target value by -1 */
    int follow_target = target * -1;

    /* Get follow-up output */
    bool follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 30: If the target is outside the range of the vector (target < vec[0] or target > vec[n-1]), then the result should always be false.
 */
TEST_P(BSearchParamTest, MR30) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Sort the vector
    sort(vec.begin(), vec.end());

    // Target less than the first element in the vector
    int target_lower = vec.front() - 1;

    // Target greater than the last element in the vector
    int target_higher = vec.back() + 1;

    /* Test the function */
    bool result_lower = bin_search(vec, target_lower);
    bool result_higher = bin_search(vec, target_higher);

    /* Verification */
    EXPECT_FALSE(result_lower);
    EXPECT_FALSE(result_higher);
}

/**
 * @brief Metamorphic relation 31: If the vector contains the target at multiple positions, removing one of the occurrences of the target should not change the result.
 */
TEST_P(BSearchParamTest, MR31) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    if (find(vec.begin(), vec.end(), target) != vec.end()) {
        // Get source output
        bool source_out = bin_search(vec, target);

        // Find the first occurrence of the target and remove it
        auto it = find(vec.begin(), vec.end(), target);
        vec.erase(it);

        // Get follow-up output
        bool follow_out = bin_search(vec, target);

        // Verification
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic relation 32: If the vector and target are all multiplied by the same positive constant, the result should remain the same.
 */
TEST_P(BSearchParamTest, MR32) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    bool source_out = bin_search(vec, target);

    // Multiply all elements of the vector by a positive constant
    const int multiplier = 3;
    for (int &val : vec) {
        val *= multiplier;
    }

    // Multiply the target also by the same constant
    int modified_target = target * multiplier;

    // Get follow-up output
    bool follow_out = bin_search(vec, modified_target);

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 33: If the vector has two or more identical elements, and the target is one of these identical elements, the search result should not change if we remove one of the identical elements from the vector.
 */
TEST_P(BSearchParamTest, MR33) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    std::vector<int>::iterator it = std::find(vec.begin(), vec.end(), target);
    if (it != vec.end()) { // if the target is in the vector
        // Get source output
        bool source_out = bin_search(vec, target);

        std::vector<int> follow_vec = vec;
        follow_vec.erase(it); // Remove one occurrence of the target

        // Get follow-up output
        bool follow_out = bin_search(follow_vec, target);

        // Verification
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic relation 34: If we insert an element that is smaller than the minimum value in the vector and set it as the target, the result should be false.
 */
TEST_P(BSearchParamTest, MR34) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int min_val = INT_MAX;

    for (int val : vec) {
      min_val = min(min_val, val);
    }

    int new_element = min_val - 1;

    // Insert the element smaller than the minimum value in the vector
    vec.push_back(new_element);

    // Set the new element as the target
    bool result = bin_search(vec, new_element);

    // Verification
    EXPECT_FALSE(result);
}

/**
 * @brief Metamorphic relation 35: If we insert multiple elements that are greater than the maximum value in the vector and set one of them as the target, the result should be the same.
 */
TEST_P(BSearchParamTest, MR35) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int max_val = INT_MIN;

    for (int val : vec) {
      max_val = max(max_val, val);
    }
    // Increase the max value by a large increment
    max_val += 100;

    // Insert multiple elements greater than the maximum value in the vector
    vec.push_back(max_val + 1);
    vec.push_back(max_val + 2);
    vec.push_back(max_val + 3);

    // Set the maximum value plus 2 as the target
    bool result = bin_search(vec, max_val + 2);

    // Verification
    EXPECT_EQ(result, bin_search(vec, target));
}

/**
 * @brief Metamorphic relation 36: Repeating the vector and setting the target to a known value that is present in the repeated vector should identify the target in any of the repeated vectors.
 */
TEST_P(BSearchParamTest, MR36) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    bool source_out = bin_search(vec, target);
    
    vector<int> double_vec;
    double_vec.insert(double_vec.end(), vec.begin(), vec.end());
    double_vec.insert(double_vec.end(), vec.begin(), vec.end());

    // Get follow-up output
    bool follow_out = bin_search(double_vec, target);

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 37: If the target is present in the vector, duplicating the vector should not change the result.
 */
TEST_P(BSearchParamTest, MR37) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    bool source_out = bin_search(vec, target);
    
    // Duplicate the vector
    vector<int> duplicate_vec(vec);
    
    // Get follow-up output
    bool follow_out = bin_search(duplicate_vec, target);

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 38: If the vector and the target are both multiplied by -1, the result should not change.
 */
TEST_P(BSearchParamTest, MR38) {
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    bool source_out = bin_search(vec, target);
    
    // Multiply all elements in the vector by -1
    for (int &val : vec) {
        val *= -1;
    }

    // Multiply the target also by -1
    int modified_target = target * -1;

    // Get follow-up output
    bool follow_out = bin_search(vec, modified_target);

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 39: If the vector is empty, performing the binary search should always result in false.
 */
TEST(BSearchEdgeCases, MR39) {
    vector<int> emptyVec;
    int target = 10;

    // Test the function with an empty vector
    bool result = bin_search(emptyVec, target);

    // Verification
    EXPECT_FALSE(result);
}

/**
 * @brief Metamorphic relation 40: If all elements in the vector are the same, the result should be true if the target is equal to any of the elements. 
 */
TEST(BSearchEdgeCases, MR40) {
    vector<int> vec = {1, 1, 1, 1, 1, 1, 1};
    int target = 1;

    // Test the function with a vector containing the same element
    bool result = bin_search(vec, target);

    // Verification
    EXPECT_TRUE(result);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, BSearchParamTest, testing::ValuesIn(get_tcs_randomly()));