#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

#define SKIP_CRASH

class BSearchParamTest : public ::testing::TestWithParam<BSearch2Input> {};

// Metamorphic Relation 1:
// If the target value is already in the array, add an element greater than the max value in the array to the end of the array, and the output should be
// unchanged.
TEST_P(BSearchParamTest, MR1) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    if (!source_out)
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.emplace_back(vec.back() + 1); // Adding an element greater than the max value in the array

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 2:
// Multiply all elements in the array and the element to be located by a constant, the output should remain the same.
TEST_P(BSearchParamTest, MR2) {
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
        val *= constant;                   // Multiply all elements in the array by a constant
    int follow_target = target * constant; // Multiply the target by the same constant

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 3:
// If the target value is already in the array, reverse the array, and the output should remain unchanged.
TEST_P(BSearchParamTest, MR3) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    if (!source_out)
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::reverse(follow_vec.begin(), follow_vec.end()); // Reverse the array

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 4:
// If the target value is already in the array, shuffle the elements in the array, and the output should remain unchanged.
TEST_P(BSearchParamTest, MR4) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    if (!source_out)
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::random_shuffle(follow_vec.begin(), follow_vec.end()); // Shuffle the elements in the array

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}
// Metamorphic Relation 5:
// If the target value is already in the array, duplicate all elements in the array, and the output should remain unchanged.
TEST_P(BSearchParamTest, MR5) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    if (!source_out)
        return;

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int val : vec) {
        follow_vec.push_back(val);
        follow_vec.push_back(val); // Duplicate all elements in the array
    }

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 6:
// If the target value is not in the array, add the target value to the array, and the output should be true.
TEST_P(BSearchParamTest, MR6) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Ensure the target is not in the array */
    if (std::find(vec.begin(), vec.end(), target) != vec.end())
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.push_back(target); // Add the target value to the array

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_TRUE(follow_out);
}

// Metamorphic Relation 7:
// If the target value is not in the array, remove one element from the array, and the output should remain false.
TEST_P(BSearchParamTest, MR7) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Ensure the target is not in the array */
    if (std::find(vec.begin(), vec.end(), target) != vec.end())
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    if (!follow_vec.empty()) {
        follow_vec.pop_back(); // Remove one element from the array
    }

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_FALSE(follow_out);
}

// Metamorphic Relation 8:
// If the input array is empty, the output should always be false regardless of the target value.
TEST_P(BSearchParamTest, MR8) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Ensure the input array is empty */
    if (!vec.empty())
        return;

    /* Get follow-up output */
    bool follow_out = bin_search(vec, target);

    /* Verification */
    EXPECT_FALSE(follow_out);
}

// Metamorphic Relation 9:
// If the target value is in the array and the array length is even, split the array into two equal parts and reverse the order of the elements in each part,
// the output should remain unchanged.
TEST_P(BSearchParamTest, MR9) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    if (!source_out)
        return;

    /* Ensure array length is even */
    if (vec.size() % 2 != 0)
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    int half_size = follow_vec.size() / 2;
    std::reverse(follow_vec.begin(), follow_vec.begin() + half_size); // Reverse the first part
    std::reverse(follow_vec.begin() + half_size, follow_vec.end());   // Reverse the second part

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 10:
// If the target value is not in the array and the array length is odd, remove the middle element from the array, the output should remain unchanged.
TEST_P(BSearchParamTest, MR10) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (source_out)
        return;

    /* Ensure array length is odd */
    if (vec.size() % 2 == 0)
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.erase(follow_vec.begin() + vec.size() / 2); // Remove the middle element from the array

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 11:
// If the target value is not in the array, add the target value to the array and reverse the array, the output should remain false.
TEST_P(BSearchParamTest, MR11) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Ensure the target is not in the array */
    if (std::find(vec.begin(), vec.end(), target) != vec.end())
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.push_back(target);                       // Add the target value to the array
    std::reverse(follow_vec.begin(), follow_vec.end()); // Reverse the array

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_FALSE(follow_out);
}

// Metamorphic Relation 12:
// If the array is sorted in descending order, reversing the array leads to the same result as sorting it in ascending order, and the output should also remain
// unchanged.
TEST_P(BSearchParamTest, MR12) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    if (source_out == false)
        return;

    /* Ensure the array is sorted in descending order */
    std::sort(vec.begin(), vec.end(), std::greater<int>());

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::reverse(follow_vec.begin(), follow_vec.end()); // Reverse the array

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 13:
// If the target value exists in the array, adding a constant value to each element in the array will not change the search result.
TEST_P(BSearchParamTest, MR13) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (!source_out)
        return;

    /* Construct follow-up input */
    const int constant = 5;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec) {
        val += constant; // Add a constant value to each element in the array
    }

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 14:
// If the target value does not exist in the array, then adding a constant value to each element in the array should not change the search result.
TEST_P(BSearchParamTest, MR14) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (source_out) // If the target exists in the array, return
        return;

    /* Construct follow-up input */
    const int constant = 5;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec) {
        val += constant; // Add a constant value to each element in the array
    }

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 15:
// If the target value is not in the array, replacing all occurrences of a specific value in the array with the target value should not change the search
// result.
TEST_P(BSearchParamTest, MR15) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Ensure the target is not in the array */
    if (std::find(vec.begin(), vec.end(), target) != vec.end())
        return;

    int value_to_replace = 0; // Assume 0 as the value to replace
    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::replace(follow_vec.begin(), follow_vec.end(), value_to_replace, target);

    /* Get follow-up output */
    bool source_out = bin_search(vec, target);
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 16:
// If the target value is not in the array, swng any two elements in the array should not change the search result.
TEST_P(BSearchParamTest, MR16) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Ensure the target is not in the array */
    if (std::find(vec.begin(), vec.end(), target) != vec.end())
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    if (follow_vec.size() >= 2) {
        std::swap(follow_vec[0], follow_vec[1]); // Swap the first two elements
    }

    /* Get source and follow-up output */
    bool source_out = bin_search(vec, target);
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 17:
// If the target value does not exist in the array, inserting the target value at a specific position in the array should not change the search result.
TEST_P(BSearchParamTest, MR17) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Ensure the target is not in the array */
    if (std::find(vec.begin(), vec.end(), target) != vec.end())
        return;

    // Insert the target value at index 0.
    vector<int> follow_vec = vec;
    follow_vec.insert(follow_vec.begin(), target);

    // Get source and follow-up output
    bool source_out = bin_search(vec, target);
    bool follow_out = bin_search(follow_vec, target);

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 18:
// If the array contains more than one occurrence of the target value, removing one occurrence of the target value should not change the search result.
TEST_P(BSearchParamTest, MR18) {
    // Get source input
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Ensure the array contains more than one occurrence of the target value
    if (std::count(vec.begin(), vec.end(), target) < 2)
        return;

    // Remove the first occurrence of the target value
    vector<int> follow_vec = vec;
    follow_vec.erase(std::find(follow_vec.begin(), follow_vec.end(), target));

    // Get source and follow-up output
    bool source_out = bin_search(vec, target);
    bool follow_out = bin_search(follow_vec, target);

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 19:
// If the array contains the target value and an additional value is added to the array, the search result should not change.
TEST_P(BSearchParamTest, MR19) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (!source_out)
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.push_back(target + 1); // Add an additional value to the array

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 20:
// If the array contains the target value and all elements in the array are negative, converting them to positive should not change the search result.
TEST_P(BSearchParamTest, MR20) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (!source_out)
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    for (int i = 0; i < follow_vec.size(); ++i) {
        follow_vec[i] = -follow_vec[i]; // Convert all elements to negative
    }

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 21:
// If the target value exists in the array, the result should remain the same when the array elements are nded with their squares.
TEST_P(BSearchParamTest, MR21) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (!source_out) // If the target value doesn't exist in the array, return
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    for (int &val : follow_vec) {
        val = val * val; // nd the squares of the elements to the array
    }

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 22:
// If the target value is not in the array, reversing the array should not change the search result.
TEST_P(BSearchParamTest, MR22) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (source_out) // If the target value exists in the array, return
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::reverse(follow_vec.begin(), follow_vec.end()); // Reverse the array

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 23:
// If the target value exists in the array, adding the elements of another array to the original array should not change the search result.
TEST_P(BSearchParamTest, MR23) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (!source_out) // If the target value doesn't exist in the array, return
        return;

    /* Construct follow-up input */
    vector<int> additional_array = {1, 2, 3}; // Additional array to be nded to the original array
    vector<int> follow_vec = vec;
    follow_vec.insert(follow_vec.end(), additional_array.begin(), additional_array.end()); // nd the elements of the additional array

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 24:
// If the target value exists in the array, sorting the array in ascending order should not change the search result.
TEST_P(BSearchParamTest, MR24) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (!source_out) // If the target value doesn't exist in the array, return
        return;

    /* Construct follow-up input */
    std::sort(vec.begin(), vec.end()); // Sort the array in ascending order

    /* Get follow-up output */
    bool follow_out = bin_search(vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 25:
// If the target value is not in the array, removing the last element from the array should not change the search result.
TEST_P(BSearchParamTest, MR25) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Ensure the target is not in the array */
    if (std::find(vec.begin(), vec.end(), target) != vec.end())
        return;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    if (!follow_vec.empty()) {
        follow_vec.pop_back(); // Remove the last element from the array
    }

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 26:
// If the target value exists in the array, performing a cyclic left shift on the array should not change the search result.
TEST_P(BSearchParamTest, MR26) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (!source_out) // If the target value doesn't exist in the array, return
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    if (!follow_vec.empty()) {
        int temp = follow_vec.front();
        follow_vec.erase(follow_vec.begin());
        follow_vec.push_back(temp); // Perform a cyclic left shift on the array
    }

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 27:
// If the target value exists in the array, multiplying all elements in the array by a constant should not change the search result.
TEST_P(BSearchParamTest, MR27) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (!source_out) // If the target value doesn't exist in the array, return
        return;

    /* Construct follow-up input */
    const int multiplier = 2;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec) {
        val *= multiplier; // Multiply each element in the array by a constant
    }

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 28:
// If the target value exists in the array, shifting all elements in the array by a constant value should not change the search result.
TEST_P(BSearchParamTest, MR28) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (!source_out) // If the target value doesn't exist in the array, return
        return;

    /* Construct follow-up input */
    const int shift_value = 3;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec) {
        val += shift_value; // Shift each element in the array by a constant value
    }

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 29:
// If the target value exists in the array, reversing the elements in the array should not change the search result.
TEST_P(BSearchParamTest, MR29) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (!source_out) // If the target value doesn't exist in the array, return
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::reverse(follow_vec.begin(), follow_vec.end()); // Reverse the array

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 30:
// If the target value exists in the array, multiplying all elements in the array by a negative constant should not change the search result.
TEST_P(BSearchParamTest, MR30) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (!source_out) // If the target value doesn't exist in the array, return
        return;

    /* Construct follow-up input */
    const int multiplier = -1;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec) {
        val *= multiplier; // Multiply each element in the array by a negative constant
    }

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 31:
// If the target value exists in the array, shuffling the elements in the array should not change the search result.
TEST_P(BSearchParamTest, MR31) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (!source_out) // If the target value doesn't exist in the array, return
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::random_shuffle(follow_vec.begin(), follow_vec.end()); // Shuffle the elements in the array

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 32:
// If the target value does not exist in the array, dynamically resizing the array should not change the search result.
TEST_P(BSearchParamTest, MR32) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Ensure the target is not in the array */
    if (std::find(vec.begin(), vec.end(), target) != vec.end())
        return;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    size_t new_size = vec.size() + 1; // Increase the size of the array by 1
    vector<int> follow_vec = vec;
    follow_vec.resize(new_size);

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 33:
// If the target value exists in the array, sorting the array in descending order should not change the search result.
TEST_P(BSearchParamTest, MR33) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (!source_out) // If the target value doesn't exist in the array, return
        return;

    /* Construct follow-up input */
    std::sort(vec.begin(), vec.end(), std::greater<int>()); // Sort the array in descending order

    /* Get follow-up output */
    bool follow_out = bin_search(vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 34:
// If the target value does not exist in the array, adding 0 to every element in the array should not change the search result.
TEST_P(BSearchParamTest, MR34) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Ensure the target is not in the array */
    if (std::find(vec.begin(), vec.end(), target) != vec.end())
        return;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::for_each(follow_vec.begin(), follow_vec.end(), [](int &val) { val += 0; }); // Add 0 to every element in the array

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 35:
// If the target value exists in the array, multiplying all elements in the array by 1 should not change the search result.
TEST_P(BSearchParamTest, MR35) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (!source_out) // If the target value doesn't exist in the array, return
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int val) { return val * 1; }); // Multiply each element by 1

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 36:
// If the target value is not in the array, ying any permutation to the array elements should not change the search result.
TEST_P(BSearchParamTest, MR36) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Ensure the target is not in the array */
    if (std::find(vec.begin(), vec.end(), target) != vec.end())
        return;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::random_shuffle(follow_vec.begin(), follow_vec.end()); // y a random permutation to the array

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 37:
// If the target value exists in the array, performing an exclusive OR (XOR) operation on each element in the array with itself should not change the search
// result.
TEST_P(BSearchParamTest, MR37) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (!source_out) // If the target value doesn't exist in the array, return
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    for (int &val : follow_vec) {
        val = val ^ val; // Perform XOR operation on each element with itself
    }

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 38:
// If the target value does not exist in the array, multiplying all elements in the array by 0 should not change the search result.
TEST_P(BSearchParamTest, MR38) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Ensure the target is not in the array */
    if (std::find(vec.begin(), vec.end(), target) != vec.end())
        return;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int val) -> int { return val * 0; }); // Multiply each element by 0

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 39:
// If the target value exists in the array, adding a constant value to each element in the array should not change the search result.
TEST_P(BSearchParamTest, MR39) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    if (!source_out) // If the target value doesn't exist in the array, return
        return;

    const int additive = 10;
    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    for (int &val : follow_vec) {
        val += additive; // Add a constant value to each element
    }

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 40:
// If the target value is not in the array, ying any permutation to the array elements should not change the search result.
TEST_P(BSearchParamTest, MR40) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    if (std::find(vec.begin(), vec.end(), target) != vec.end()) // If the target value exists in the array, return
        return;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    std::random_shuffle(follow_vec.begin(), follow_vec.end()); // y a random permutation to the array

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, BSearchParamTest, testing::ValuesIn(get_tcs_randomly()));