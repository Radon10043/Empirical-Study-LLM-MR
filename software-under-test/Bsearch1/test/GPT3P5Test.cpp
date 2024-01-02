#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <vector>

#include "../src/function.h"
#include <climits>

using namespace std;

#define SKIP_CRASH
#define INVALID 0

typedef struct BSearch1Input {
    BSearch1Input(vector<int> vec, int target) : vec(vec), target(target){};
    vector<int> vec;
    int target;
} BSearch1Input;

class BSearchParamTest : public ::testing::TestWithParam<BSearch1Input> {};

// Metamorphic Relation 3: Reverse the order of elements in the array and perform the binary search. The output should remain the same.c
TEST_P(BSearchParamTest, MR3) {
    /* Get source input */
    BSearch1Input input = GetParam();
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

// Metamorphic Relation 4: Increment or decrement the target element by a constant value, the output should either remain unchanged or be -1.
TEST_P(BSearchParamTest, MR4) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 5;
    int follow_target = target + constant;

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_TRUE(source_out == follow_out || follow_out == -1);
}

// Metamorphic Relation 5: Replace a random element in the array with the target, the output should either remain unchanged or be the index of the replaced
// element.c
TEST_P(BSearchParamTest, MR5) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int replace_index = rand() % vec.size();
    vector<int> follow_vec = vec;
    follow_vec[replace_index] = target;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_TRUE(source_out == follow_out || follow_out == replace_index);
}

// Metamorphic Relation 6: Add a constant value to all elements in the array and the target, the output should remain the same.cc
TEST_P(BSearchParamTest, MR6) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 10;
    vector<int> follow_vec = vec;
    int follow_target = target + constant;
    for (int &val : follow_vec)
        val += constant;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 7: Remove a specific element from the array and test the binary search, the output should be -1 or the previous index if it existed.
TEST_P(BSearchParamTest, MR7) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int remove_index = rand() % vec.size();
    vector<int> follow_vec;
    for (int i = 0; i < vec.size(); i++) {
        if (i != remove_index) {
            follow_vec.push_back(vec[i]);
        }
    }

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_TRUE(follow_out == -1 || follow_out == remove_index);
}

// Metamorphic Relation 8: Shuffle the array, the output should remain the same.
TEST_P(BSearchParamTest, MR8) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    random_shuffle(vec.begin(), vec.end());

    /* Get follow-up output */
    int follow_out = bin_search(vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 9: Repeating all elements in the array twice, the output should remain unchanged.
TEST_P(BSearchParamTest, MR9) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int val : vec) {
        follow_vec.push_back(val);
        follow_vec.push_back(val);
    }

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 10: Change the target to an element that doesn't exist in the array, the output should be -1.
TEST_P(BSearchParamTest, MR10) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int non_existing = INT_MAX; // An element that doesn't exist in the array
    int follow_out = bin_search(vec, non_existing);

    /* Verification */
    EXPECT_EQ(-1, follow_out);
}

// Metamorphic Relation 11: Update all elements of the array to the same constant, the output should be the location of target if it exists, otherwise -1.
TEST_P(BSearchParamTest, MR11) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 5; // Any arbitrary constant
    vector<int> follow_vec(vec.size(), constant);
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    if (source_out != -1) {
        EXPECT_EQ(source_out, follow_out);
    } else {
        EXPECT_EQ(-1, follow_out);
    }
}

// Metamorphic Relation 12: Remove a segment of elements from the array and perform the binary search, the result should still be either the index of the target
// in the original array or -1.
TEST_P(BSearchParamTest, MR12) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int segment_start = rand() % vec.size();
    int segment_length = rand() % (vec.size() - segment_start);
    vector<int> follow_vec;
    for (int i = 0; i < vec.size(); i++) {
        if (i < segment_start || i >= segment_start + segment_length) {
            follow_vec.push_back(vec[i]);
        }
    }

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_TRUE(follow_out == source_out || follow_out == -1);
}

// Metamorphic Relation 13: Modify the array to be a non-standard distribution (e.g., all elements are the same, reverse order, etc.), the result should still
// be the index of the target in the original array or -1.
TEST_P(BSearchParamTest, MR13) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    random_shuffle(follow_vec.begin(), follow_vec.end()); // Non-standard distribution

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_TRUE(follow_out == source_out || follow_out == -1);
}

// Metamorphic Relation 14: Add a duplicate of the target element to the array, the output should still be the index of the original target in the original
// array.
TEST_P(BSearchParamTest, MR14) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.push_back(target);

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 15: Introduce a shift in the array elements by a specific amount without changing the sorted order. The output should remain the same.
TEST_P(BSearchParamTest, MR15) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int shift_amount = 3; // Can be any constant
    vector<int> follow_vec = vec;
    rotate(follow_vec.begin(), follow_vec.begin() + shift_amount, follow_vec.end());

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 16: Split the elements of the array into two arrays, then perform the binary search, the output should still be either the index of the
// target in the original array or -1.
TEST_P(BSearchParamTest, MR16) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int split_index = rand() % vec.size();
    vector<int> follow_vec1(vec.begin(), vec.begin() + split_index);
    vector<int> follow_vec2(vec.begin() + split_index, vec.end());

    /* Get follow-up output */
    int follow_out1 = bin_search(follow_vec1, target);
    int follow_out2 = bin_search(follow_vec2, target);
    int follow_out = (follow_out1 != -1) ? follow_out1 : follow_out2;

    /* Verification */
    EXPECT_TRUE(follow_out == source_out || follow_out == -1);
}

// Metamorphic Relation 17: Perturb the target element slightly, the output should either be the index of the original target in the original array or -1.
TEST_P(BSearchParamTest, MR17) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    double perturbation = 0.001; // Can be any small value
    double follow_target = target + perturbation;

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_TRUE(follow_out == source_out || follow_out == -1);
}

// Metamorphic Relation 18: Generate a new array with some elements in common with the original array, but also containing additional elements, then perform the
// binary search. The output should either be the index of the target in the original array or -1.
TEST_P(BSearchParamTest, MR18) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> common_elements = {1, 3, 5};  // Common elements with the original array
    vector<int> additional_elements = {7, 9}; // Additional elements not present in the original array
    vector<int> follow_vec = vec;
    follow_vec.insert(follow_vec.end(), common_elements.begin(), common_elements.end());
    follow_vec.insert(follow_vec.end(), additional_elements.begin(), additional_elements.end());

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_TRUE(follow_out == source_out || follow_out == -1);
}

// Metamorphic Relation 19: Shuffle the array and then sort it again, the output should remain the same.
TEST_P(BSearchParamTest, MR19) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    random_shuffle(vec.begin(), vec.end());
    sort(vec.begin(), vec.end());

    /* Get follow-up output */
    int follow_out = bin_search(vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 20: Modify the array by adding a constant value to all elements and the target. The output should remain the same.
TEST_P(BSearchParamTest, MR20) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 10;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec) {
        val += constant;
    }
    int follow_target = target + constant;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 21: Remove some elements from the array and perform the binary search. The output should either be the index of the target in the
// original array or -1.
TEST_P(BSearchParamTest, MR21) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int num_removed = rand() % vec.size();
    random_shuffle(vec.begin(), vec.end());
    vec.resize(vec.size() - num_removed);

    /* Get follow-up output */
    int follow_out = bin_search(vec, target);

    /* Verification */
    EXPECT_TRUE(follow_out == source_out || follow_out == -1);
}

// Metamorphic Relation 22: Ensure the input array is sorted in reverse order, then perform the binary search. The output should either be the index of the
// target in the original array or -1.
TEST_P(BSearchParamTest, MR22) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    sort(vec.begin(), vec.end(), greater<int>());

    /* Get follow-up output */
    int follow_out = bin_search(vec, target);

    /* Verification */
    EXPECT_TRUE(follow_out == source_out || follow_out == -1);
}

// Metamorphic Relation 23: Create a new array by removing duplicate elements from the original array, then perform the binary search. The output should either
// be the index of the target in the original array or -1.
TEST_P(BSearchParamTest, MR23) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec(vec.begin(), vec.end());
    sort(follow_vec.begin(), follow_vec.end());
    follow_vec.erase(unique(follow_vec.begin(), follow_vec.end()), follow_vec.end());

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_TRUE(follow_out == source_out || follow_out == -1);
}

// Metamorphic Relation 24: Multiply all elements in the array by a constant value and perform the binary search; the output should remain the same.
TEST_P(BSearchParamTest, MR24) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int multiplier = 10; // Any constant
    vector<int> follow_vec = vec;
    for (int &val : follow_vec) {
        val *= multiplier;
    }

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 25: Create a new array by reversing the order of elements in the original array and perform the binary search. The output should remain
// the same.
TEST_P(BSearchParamTest, MR25) {
    /* Get source input */
    BSearch1Input input = GetParam();
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

// Metamorphic Relation 26: Insert a new element in the middle of the array while maintaining sorted order, and then perform the binary search. The output
// should either be the index of the target in the original array or -1.
TEST_P(BSearchParamTest, MR26) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    int middle_index = follow_vec.size() / 2;
    follow_vec.insert(follow_vec.begin() + middle_index, target);
    sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_TRUE(follow_out == source_out || follow_out == -1);
}

// Metamorphic Relation 27: Replace all elements in the array with their absolute values, then perform the binary search. The output should remain the same.
TEST_P(BSearchParamTest, MR27) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int val : vec) {
        follow_vec.push_back(abs(val));
    }

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 28: Randomly shuffle the array and then perform the binary search. The output should remain the same.
TEST_P(BSearchParamTest, MR28) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    random_shuffle(vec.begin(), vec.end());

    /* Get follow-up output */
    int follow_out = bin_search(vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 29: Add a constant value to the target and then perform the binary search. The output should remain the same or be -1.
TEST_P(BSearchParamTest, MR29) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 5; // Any constant
    int follow_target = target + constant;

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_TRUE(source_out == follow_out || follow_out == -1);
}

// Metamorphic Relation 30: Split the input array into two sub-arrays and then perform a binary search on each sub-array separately. The result should be the
// same as if the search were done on the original array.
TEST_P(BSearchParamTest, MR30) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    // Construct follow-up input
    int mid = vec.size() / 2;
    vector<int> subarray1(vec.begin(), vec.begin() + mid);
    vector<int> subarray2(vec.begin() + mid, vec.end());

    // Get follow-up output
    int follow_out1 = bin_search(subarray1, target);
    int follow_out2 = bin_search(subarray2, target);
    int follow_out = (follow_out1 != -1) ? follow_out1 : follow_out2;

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

#if INVALID
// Metamorphic Relation 31: Convert the input array to a set and then perform a binary search on this set. The result should match the result from the binary
// search on the original array.
TEST_P(BSearchParamTest, MR31) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    // Construct follow-up input
    set<int> follow_set(vec.begin(), vec.end());

    // Get follow-up output
    int follow_out = binary_search(follow_set.begin(), follow_set.end(), target) != follow_set.end() ? 1 : -1;

    // Verification
    EXPECT_EQ(source_out, follow_out);
}
#endif

// Metamorphic Relation 32: Create a new array by sorting the elements of the original array in descending order, then perform the binary search. The output
// should either be the index of the target in the original array or -1.
TEST_P(BSearchParamTest, MR32) {
    /* Get source input */
    BSearch1Input input = GetParam();
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
    EXPECT_TRUE(follow_out == source_out || follow_out == -1);
}

// Metamorphic Relation 33: Modify the array by replacing all elements with their squares, and then perform the binary search. The output should remain the
// same.
TEST_P(BSearchParamTest, MR33) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    for (int &val : follow_vec) {
        val = val * val;
    }

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 34: Create a new array by reversing the order of elements in the original array and then negating all elements. Perform the binary
// search on this new array. The output should remain the same.
TEST_P(BSearchParamTest, MR34) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    reverse(follow_vec.begin(), follow_vec.end());
    for (int &val : follow_vec) {
        val = -val;
    }

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 35: Increment all elements in the array by a constant value and then perform the binary search. The output should remain the same.
TEST_P(BSearchParamTest, MR35) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 10; // Arbitrary constant value
    vector<int> follow_vec = vec;
    for (int &val : follow_vec) {
        val += constant;
    }

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 36: Generate a new array by adding a fixed value to each element of the original array, and then perform the binary search using this
// new array. The output should remain the same or be -1.
TEST_P(BSearchParamTest, MR36) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int fixedValue = 5; // Fixed value to be added to each element
    vector<int> follow_vec = vec;
    for (int &val : follow_vec) {
        val += fixedValue;
    }

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_TRUE(source_out == follow_out || follow_out == -1);
}

// Metamorphic Relation 37: Remove any duplicate elements from the array and then perform the binary search. The output should remain the same.
TEST_P(BSearchParamTest, MR37) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    sort(vec.begin(), vec.end());
    auto it = unique(vec.begin(), vec.end());
    vec.resize(distance(vec.begin(), it));

    /* Get follow-up output */
    int follow_out = bin_search(vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 38: Rotate the elements in the array, and then perform the binary search. The output should remain the same.
TEST_P(BSearchParamTest, MR38) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int source_out = bin_search(vec, target);

    // Construct follow-up input
    int rotateBy = 3; // Arbitrary value
    rotate(vec.begin(), vec.begin() + rotateBy, vec.end());

    // Get follow-up output
    int follow_out = bin_search(vec, target);

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 39: Reverse the order of elements in the array and then perform the binary search. The output should remain the same.
TEST_P(BSearchParamTest, MR39) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int source_out = bin_search(vec, target);

    // Construct follow-up input
    reverse(vec.begin(), vec.end());

    // Get follow-up output
    int follow_out = bin_search(vec, target);

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 40: Add a constant value to all elements of the array and then perform the binary search. The output should remain the same.
TEST_P(BSearchParamTest, MR40) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int source_out = bin_search(vec, target);

    // Construct follow-up input
    int constant = 5; // Any constant value
    vector<int> follow_vec = vec;
    for (int &val : follow_vec) {
        val += constant;
    }

    // Get follow-up output
    int follow_out = bin_search(follow_vec, target);

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 41: Shift all elements of the array by a specific amount to the right, and then perform the binary search. The output should remain the
// same.
TEST_P(BSearchParamTest, MR41) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int source_out = bin_search(vec, target);

    // Construct follow-up input
    int shiftBy = 2; // Arbitrary value
    rotate(vec.begin(), vec.begin() + shiftBy, vec.end());

    // Get follow-up output
    int follow_out = bin_search(vec, target);

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 42: Scaling the array elements by a constant factor and then performing the binary search. The output should remain the same.
TEST_P(BSearchParamTest, MR42) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int source_out = bin_search(vec, target);

    // Construct follow-up input
    int scalingFactor = 2; // Any constant
    vector<int> follow_vec = vec;
    for (int &val : follow_vec) {
        val *= scalingFactor;
    }

    // Get follow-up output
    int follow_out = bin_search(follow_vec, target);

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 43: Applying a fixed mathematical function to the array elements (e.g., square, cube, sine, cosine, etc.) and then performing the binary
// search. The output should remain the same.
TEST_P(BSearchParamTest, MR43) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int source_out = bin_search(vec, target);

    // Construct follow-up input
    vector<int> follow_vec = vec;
    for (int &val : follow_vec) {
        val = pow(val, 2); // Example: Squaring the element
    }

    // Get follow-up output
    int follow_out = bin_search(follow_vec, target);

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 44: Repeat the elements of the array multiple times, and then perform the binary search. The output should remain the same.
TEST_P(BSearchParamTest, MR44) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int source_out = bin_search(vec, target);

    // Construct follow-up input
    int numRepetitions = 2; // Arbitrary value
    vector<int> follow_vec;
    for (int i = 0; i < numRepetitions; ++i) {
        follow_vec.insert(follow_vec.end(), vec.begin(), vec.end());
    }

    // Get follow-up output
    int follow_out = bin_search(follow_vec, target);

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 45: Randomly reorder the elements of the array and then perform the binary search. The output should remain the same.
TEST_P(BSearchParamTest, MR45) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int source_out = bin_search(vec, target);

    // Construct follow-up input
    vector<int> follow_vec = vec;
    random_shuffle(follow_vec.begin(), follow_vec.end());

    // Get follow-up output
    int follow_out = bin_search(follow_vec, target);

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 46: Add a constant value to all elements in the array and then shuffle the array, followed by a binary search. The output should remain
// the same.
TEST_P(BSearchParamTest, MR46) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int source_out = bin_search(vec, target);

    // Construct follow-up input
    int constant = 5; // Arbitrary constant value
    vector<int> follow_vec = vec;
    for (int &val : follow_vec) {
        val += constant;
    }
    random_shuffle(follow_vec.begin(), follow_vec.end());

    // Get follow-up output
    int follow_out = bin_search(follow_vec, target);

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 47: Divide all elements of the array by a constant value, and then perform the binary search. The output should remain the same.
TEST_P(BSearchParamTest, MR47) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int source_out = bin_search(vec, target);

    // Construct follow-up input
    int divisor = 3; // Arbitrary constant value
    vector<int> follow_vec = vec;
    for (int &val : follow_vec) {
        val /= divisor;
    }

    // Get follow-up output
    int follow_out = bin_search(follow_vec, target);

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 48: Remove every alternate element from the array and then perform the binary search. The output should either be the same as the
// original result or -1.
TEST_P(BSearchParamTest, MR48) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int source_out = bin_search(vec, target);

    // Construct follow-up input
    vector<int> follow_vec;
    for (int i = 0; i < vec.size(); i += 2) {
        follow_vec.push_back(vec[i]);
    }

    // Get follow-up output
    int follow_out = bin_search(follow_vec, target);

    // Verification
    EXPECT_TRUE(follow_out == source_out || follow_out == -1);
}

// Metamorphic Relation 49: Select a subrange of elements from the array, sort them, and then perform the binary search. The output should remain the same.
TEST_P(BSearchParamTest, MR49) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int source_out = bin_search(vec, target);

    // Construct follow-up input
    int start = 2; // Arbitrary subrange start index
    int end = 6;   // Arbitrary subrange end index
    vector<int> follow_vec(vec.begin() + start, vec.begin() + end);
    sort(follow_vec.begin(), follow_vec.end());

    // Get follow-up output
    int follow_out = bin_search(follow_vec, target);

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 50: Select every alternate element from the array, and then append the original array to this new array. Perform the binary search on
// the resulting array. The output should remain the same.
TEST_P(BSearchParamTest, MR50) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int source_out = bin_search(vec, target);

    // Construct follow-up input
    vector<int> follow_vec;
    for (size_t i = 0; i < vec.size(); i += 2) {
        follow_vec.push_back(vec[i]);
    }
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.end());

    // Get follow-up output
    int follow_out = bin_search(follow_vec, target);

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 51: Reverse the elements of the array, and then perform a binary search. The output should be the same as for the original array.
TEST_P(BSearchParamTest, MR51) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int source_out = bin_search(vec, target);

    // Construct follow-up input
    vector<int> follow_vec = vec;
    reverse(follow_vec.begin(), follow_vec.end());

    // Get follow-up output
    int follow_out = bin_search(follow_vec, target);

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 52: Concatenate the original array with itself, resulting in a new array, and then perform a binary search. The output should remain the
// same.
TEST_P(BSearchParamTest, MR52) {
    // Get source input
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    // Get source output
    int source_out = bin_search(vec, target);

    // Construct follow-up input
    vector<int> follow_vec = vec;
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.end());

    // Get follow-up output
    int follow_out = bin_search(follow_vec, target);

    // Verification
    EXPECT_EQ(source_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TreuReturn, BSearchParamTest,
                        testing::Values(BSearch1Input({1, 2, 3, 4, 5}, 3), BSearch1Input({1, 2, 3, 4, 5}, 1), BSearch1Input({1, 2, 3, 4, 5}, 99)));