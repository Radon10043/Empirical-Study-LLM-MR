#include <algorithm>
#include <climits>
#include <cmath>
#include <gtest/gtest.h>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class GetRangeParamTest : public ::testing::TestWithParam<GetRangeInput> {};

/**
 * @brief Metamorphic relation 3: Reversing the array, the starting position of the searching number in the reversed array should be equals to
 * the ending position in the original array and the ending position in the reversed array should be equals to the starting position in the original array.
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
    vector<int> follow_vec = vec;
    reverse(follow_vec.begin(), follow_vec.end()); // Reverse the array

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[1], vec.size() - follow_out[0] - 1);
    EXPECT_EQ(source_out[0], vec.size() - follow_out[1] - 1);
}

/**
 * @brief Metamorphic relation 4: Doubling the size of the array, the starting and ending positions in the doubled array should be increased by the length of
 * the original array.
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
    vector<int> follow_vec = vec;
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.end()); // Double the size of the array

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0] + vec.size(), follow_out[0]);
    EXPECT_EQ(source_out[1] + vec.size(), follow_out[1]);
}

/**
 * @brief Metamorphic relation 5: Sorting the array in ascending order, the positions of the searching number in the sorted array should be
 * the same as the positions in the original array.
 */
TEST_P(GetRangeParamTest, MR5) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1 && source_out[1] == -1)
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end()); // Sort the array in ascending order

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], distance(vec.begin(), find(vec.begin(), vec.end(), follow_vec[follow_out[0]])));
    EXPECT_EQ(source_out[1], distance(vec.begin(), find(vec.begin(), vec.end(), follow_vec[follow_out[1]])));
}

/**
 * @brief Metamorphic relation 6: Changing the array elements to their squares, the positions of the searching number in the squared array should
 * be the same as the positions in the original array.
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

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return x * x; }); // Change the array elements to their squares

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], distance(vec.begin(), find(vec.begin(), vec.end(), follow_vec[follow_out[0]])));
    EXPECT_EQ(source_out[1], distance(vec.begin(), find(vec.begin(), vec.end(), follow_vec[follow_out[1]])));
}

/**
 * @brief Metamorphic relation 7: Multiplying all elements of the array by a constant factor, the positions of the searching number in the multiplied array
 * should be the same as the positions in the original array.
 */
TEST_P(GetRangeParamTest, MR7) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1 && source_out[1] == -1)
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    int multiplier = 3; // Multiplication factor
    for (int &num : follow_vec) {
        num *= multiplier; // Multiply all elements by a constant factor
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], distance(vec.begin(), find(vec.begin(), vec.end(), follow_vec[follow_out[0]])));
    EXPECT_EQ(source_out[1], distance(vec.begin(), find(vec.begin(), vec.end(), follow_vec[follow_out[1]])));
}

/**
 * @brief Metamorphic relation 8: Adding a constant value to all elements of the array, the positions of the searching number in the modified array should
 * be the same as the positions in the original array.
 */
TEST_P(GetRangeParamTest, MR8) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1 && source_out[1] == -1)
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    int addition = 5; // Constant value to add
    for (int &num : follow_vec) {
        num += addition; // Add a constant value to all elements
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], distance(vec.begin(), find(vec.begin(), vec.end(), follow_vec[follow_out[0]])));
    EXPECT_EQ(source_out[1], distance(vec.begin(), find(vec.begin(), vec.end(), follow_vec[follow_out[1]])));
}

/**
 * @brief Metamorphic relation 9: Removing duplicate elements from the array, the positions of the searching number in the modified array should be the same or
 * fewer than the positions in the original array.
 */
TEST_P(GetRangeParamTest, MR9) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1 && source_out[1] == -1)
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());               // Sort the array in ascending order
    auto last = unique(follow_vec.begin(), follow_vec.end()); // Remove duplicates
    follow_vec.erase(last, follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

#if INVALID
    /* Verification */
    EXPECT_GE(source_out[0], distance(follow_vec.begin(), find(follow_vec.begin(), follow_vec.end(), vec[source_out[0])));
    EXPECT_GE(source_out[1], distance(follow_vec.begin(), find(follow_vec.begin(), follow_vec.end(), vec[source_out[1])));
#else
    /* Verification */
    EXPECT_EQ(source_out[0], distance(follow_vec.begin(), find(follow_vec.begin(), follow_vec.end(), vec[source_out[0]])));
    EXPECT_EQ(source_out[1], distance(follow_vec.begin(), find(follow_vec.begin(), follow_vec.end(), vec[source_out[1]])));
#endif
}

/**
 * @brief Metamorphic relation 10: Reversing the order of the array's elements, the positions of the searching number in the modified array should be the same
 * as in the original array but in reverse order.
 */
TEST_P(GetRangeParamTest, MR10) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1 && source_out[1] == -1)
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    reverse(follow_vec.begin(), follow_vec.end()); // Reverse the order of the elements in the array

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], vec.size() - follow_out[1] - 1);
    EXPECT_EQ(source_out[1], vec.size() - follow_out[0] - 1);
}

/**
 * @brief Metamorphic relation 11: Shifting the elements of the array to the right by a certain number of positions, the positions of the searching number in
 * the shifted array should be the same as in the original array, with an offset due to the shift.
 */
TEST_P(GetRangeParamTest, MR11) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int shiftAmount = 3; // Number of positions to shift

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1 && source_out[1] == -1)
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    rotate(follow_vec.rbegin(), follow_vec.rbegin() + shiftAmount, follow_vec.rend()); // Shift the elements to the right

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], (follow_out[0] + shiftAmount) % vec.size());
    EXPECT_EQ(source_out[1], (follow_out[1] + shiftAmount) % vec.size());
}

/**
 * @brief Metamorphic relation 12: Replacing elements in the array with a certain pattern, the positions of the searching number in the modified array should
 * align with the pattern of replacement from the original array.
 */
TEST_P(GetRangeParamTest, MR12) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int replacementPattern[] = {5, 10, 15, 20}; // Pattern for replacement

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1 && source_out[1] == -1)
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    for (size_t i = 0; i < follow_vec.size(); ++i) {
        if (find(begin(replacementPattern), end(replacementPattern), follow_vec[i]) != end(replacementPattern)) {
            follow_vec[i] = target; // Replace elements with the searching number
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    for (size_t i = 0; i < follow_out.size(); ++i) {
        if (follow_out[i] != -1) {
            EXPECT_EQ(source_out[i], i);
        }
    }
}

/**
 * @brief Metamorphic relation 13: Adding a constant value to the target number, the positions of the modified target number should be shifted by the constant
 * added.
 */
TEST_P(GetRangeParamTest, MR13) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* New target number by adding a constant value */
    int modified_target = target + 5;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);
    vector<int> modified_out = get_range(vec, modified_target);

    /* Verify if both target and modified target exist in the array */
    if (source_out[0] != -1 && modified_out[0] != -1) {
        /* Verification */
        EXPECT_EQ(modified_out[0], source_out[0] + 5);
        EXPECT_EQ(modified_out[1], source_out[1] + 5);
    }
}

/**
 * @brief Metamorphic relation 14: Reversing the positions of the input array and the target number, the reversed target number should exist in the reversed
 * array with the positions shifted by the array size minus one.
 */
TEST_P(GetRangeParamTest, MR14) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Reverse the array and the target number */
    reverse(vec.begin(), vec.end());
    int reversed_target = vec.size() - target - 1;

    /* Get reversed array output */
    vector<int> reversed_out = get_range(vec, reversed_target);

    /* Verify if the target exists in the original array */
    if (source_out[0] != -1) {
        /* Verification */
        EXPECT_EQ(reversed_out[0], vec.size() - source_out[1] - 1);
        EXPECT_EQ(reversed_out[1], vec.size() - source_out[0] - 1);
    }
}

/**
 * @brief Metamorphic relation 15: Checking for the absence of a target number, all positions in the output array should be -1.
 */
TEST_P(GetRangeParamTest, MR15) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Verify if the target number does not exist in the array */
    if (source_out[0] == -1) {
        /* Verification */
        EXPECT_EQ(source_out[0], -1);
        EXPECT_EQ(source_out[1], -1);
    }
}

/**
 * @brief Metamorphic relation 16: Swapping the start and end indexes, the start and end indexes should be swapped in the output array as well.
 */
TEST_P(GetRangeParamTest, MR16) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Verify if the target exists in the original array */
    if (source_out[0] != -1) {
        /* Swap the start and end indexes */
        int temp = source_out[0];
        source_out[0] = source_out[1];
        source_out[1] = temp;

        /* Get output for swapped indexes */
        vector<int> swapped_out = get_range(vec, target);

        /* Verification */
        EXPECT_EQ(source_out[0], swapped_out[0]);
        EXPECT_EQ(source_out[1], swapped_out[1]);
    }
}

/**
 * @brief Metamorphic relation 17: Checking for a negative target number, the positions in the output array should be -1 if the negative of the target number
 * does not exist in the array.
 */
TEST_P(GetRangeParamTest, MR17) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int negative_target = -target;

    /* Get source output */
    vector<int> source_out = get_range(vec, negative_target);

    /* Verify if the negative target number does not exist in the array */
    if (source_out[0] == -1) {
        /* Verification */
        EXPECT_EQ(source_out[0], -1);
        EXPECT_EQ(source_out[1], -1);
    }
}

/**
 * @brief Metamorphic relation 18: Repeating the elements of the array, the positions of the searching number in the repeated array should align with the
 * initial positions, with offsets related to the index of the repeated array.
 */
TEST_P(GetRangeParamTest, MR18) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    vector<int> repeat_vec;
    int repeatCount = 3; // Number of times to repeat the array

    for (int i = 0; i < repeatCount; i++) {
        repeat_vec.insert(repeat_vec.end(), vec.begin(), vec.end());
    }

    /* Get source output */
    vector<int> source_out = get_range(vec, target);
    vector<int> repeated_out = get_range(repeat_vec, target);

    /* Verify if the target exists in the original array */
    if (source_out[0] != -1) {
        /* Verification */
        EXPECT_EQ(repeated_out[0], source_out[0] + vec.size() * repeatCount);
        EXPECT_EQ(repeated_out[1], source_out[1] + vec.size() * repeatCount);
    }
}

/**
 * @brief Metamorphic relation 19: Scaling the array elements by a constant, the positions of the searching number in the scaled array should align with the
 * positions in the original array, taking into account the scaling factor.
 */
TEST_P(GetRangeParamTest, MR19) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int scalefactor = 2; // Scaling factor

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int num : vec) {
        follow_vec.push_back(num * scalefactor);
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verify if the target exists in the original array */
    if (source_out[0] != -1) {
        /* Verification */
        EXPECT_EQ(source_out[0], follow_out[0] / scalefactor);
        EXPECT_EQ(source_out[1], follow_out[1] / scalefactor);
    }
}

/**
 * @brief Metamorphic relation 20: Applying a function to the array elements, the positions of the searching number in the modified array should align with the
 * positions in the original array, with adjustments based on the applied function.
 */
TEST_P(GetRangeParamTest, MR20) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec;
    transform(vec.begin(), vec.end(), back_inserter(follow_vec), [](int x) { return x * x + 1; }); // Apply a function (x^2 + 1) to array elements

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verify if the target exists in the original array */
    if (source_out[0] != -1) {
        /* Verification */
        EXPECT_NE(source_out[0], follow_out[0]);
        EXPECT_NE(source_out[1], follow_out[1]);
    }
}

/**
 * @brief Metamorphic relation 21: Reversing the polarity of the array elements, the positions of the searching number in the modified array should be the same
 * as the positions in the original array.
 */
TEST_P(GetRangeParamTest, MR21) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by reversing the polarity of array elements */
    vector<int> follow_vec;
    transform(vec.begin(), vec.end(), back_inserter(follow_vec), [](int x) { return -x; });

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 22: Rotating the array elements by a specific number of positions, the positions of the searching number in the rotated array
 * should align with the positions in the original array, with an offset due to the rotation.
 */
TEST_P(GetRangeParamTest, MR22) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int rotationAmount = 3; // Number of positions to rotate

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by rotating array elements */
    vector<int> follow_vec = vec;
    rotate(follow_vec.begin(), follow_vec.begin() + rotationAmount, follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], (follow_out[0] + rotationAmount) % vec.size());
    EXPECT_EQ(source_out[1], (follow_out[1] + rotationAmount) % vec.size());
}

/**
 * @brief Metamorphic relation 23: Adding a constant to each element in the array, the positions of the searching number in the modified array should align with
 * the positions in the original array, with an adjustable offset based on the constant.
 */
TEST_P(GetRangeParamTest, MR23) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int constant = 10; // Constant to add

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by adding a constant to each element */
    vector<int> follow_vec = vec;
    for (int &num : follow_vec) {
        num += constant;
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verify if the target exists in the original array */
    if (source_out[0] != -1) {
        /* Verification */
        EXPECT_EQ(source_out[0], follow_out[0] - constant);
        EXPECT_EQ(source_out[1], follow_out[1] - constant);
    }
}

/**
 * @brief Metamorphic relation 24: Replacing all occurrences of a specific number in the array with a different number, the positions of the searching number in
 * the modified array should align with the positions in the original array.
 */
TEST_P(GetRangeParamTest, MR24) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int replacementNumber = 0; // Number to replace the occurrences of the target

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by replacing occurrences of the target number */
    vector<int> follow_vec = vec;
    replace(follow_vec.begin(), follow_vec.end(), target, replacementNumber);

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 25: Removing specific elements from the array, the positions of the searching number in the modified array should be the same as
 * the positions in the original array, with an adjustment for the removed elements.
 */
TEST_P(GetRangeParamTest, MR25) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by removing specific elements */
    vector<int> follow_vec = vec;
    follow_vec.erase(remove(follow_vec.begin(), follow_vec.end(), target), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    if (source_out[0] != -1) {
        int num_removed = static_cast<int>(vec.size()) - static_cast<int>(follow_vec.size());
        EXPECT_EQ(source_out[0], follow_out[0] + num_removed);
        EXPECT_EQ(source_out[1], follow_out[1] + num_removed);
    }
}

/**
 * @brief Metamorphic relation 26: Adding specific elements to the array, the positions of the searching number in the modified array should be the same as the
 * positions in the original array, with an adjustment for the added elements.
 */
TEST_P(GetRangeParamTest, MR26) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int added_element = 0;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by adding specific elements */
    vector<int> follow_vec = vec;
    follow_vec.push_back(added_element);

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    if (source_out[0] != -1) {
        int num_added = 1;
        EXPECT_EQ(source_out[0], follow_out[0] - num_added);
        EXPECT_EQ(source_out[1], follow_out[1] - num_added);
    }
}

/**
 * @brief Metamorphic relation 27: Interchanging two elements in the array, the positions of the searching number in the modified array should be the same as
 * the positions in the original array, regardless of the interchange.
 */
TEST_P(GetRangeParamTest, MR27) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by interchanging two elements */
    vector<int> follow_vec = vec;
    if (follow_vec.size() >= 2) {
        swap(follow_vec[0], follow_vec[1]);
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 28: Sorting the array and then reversing it, the positions of the searching number in the modified array should align with the
 * positions in the original array, regardless of the sorting and reversal.
 */
TEST_P(GetRangeParamTest, MR28) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by sorting the array and then reversing it */
    vector<int> follow_vec = vec;
    sort(follow_vec.begin(), follow_vec.end());
    reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 29: Applying a mathematical operation to the elements in the array, the positions of the searching number in the modified array
 * should align with the positions in the original array, regardless of the mathematical operation applied.
 */
TEST_P(GetRangeParamTest, MR29) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by applying a mathematical operation to the array elements */
    vector<int> follow_vec = vec;
    transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return x * x + 2 * x + 1; });

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 30: Adding a value to the target number, the positions of the modified target number should be moved by the value added, compared
 * to the positions of the original target number.
 */
TEST_P(GetRangeParamTest, MR30) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* New target number by adding a value */
    int added_value = 5;
    int modified_target = target + added_value;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);
    vector<int> modified_out = get_range(vec, modified_target);

    /* Verification */
    if (source_out[0] != -1 && modified_out[0] != -1) {
        EXPECT_EQ(modified_out[0], source_out[0] + added_value);
        EXPECT_EQ(modified_out[1], source_out[1] + added_value);
    }
}

/**
 * @brief Metamorphic relation 31: Adding a constant to all elements in the array, the positions of the searching number in the modified array should align with
 * the positions in the original array, regardless of the constant added to all elements.
 */
TEST_P(GetRangeParamTest, MR31) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int constant = 10; // Constant to add to all elements

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by adding a constant to all elements */
    vector<int> follow_vec = vec;
    for (int &num : follow_vec) {
        num += constant;
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 32: Reversing the order of the array's elements and then sorting it, the positions of the searching number in the modified array
 * should align with the positions in the original array, regardless of the order reversal and sorting.
 */
TEST_P(GetRangeParamTest, MR32) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by reversing the order of elements and then sorting it */
    vector<int> follow_vec = vec;
    reverse(follow_vec.begin(), follow_vec.end());
    sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 33: Applying a bitwise operation to the elements in the array, the positions of the searching number in the modified array should
 * align with the positions in the original array, regardless of the bitwise operation applied.
 */
TEST_P(GetRangeParamTest, MR33) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by applying a bitwise operation to the array elements */
    vector<int> follow_vec = vec;
    transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int x) { return x ^ 255; });

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 34: Adding a constant value to the elements of the array and then subtracting the same constant value, the positions of the
 * searching number in the modified array should align with the positions in the original array, regardless of the addition and subtraction operations.
 */
TEST_P(GetRangeParamTest, MR34) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int constant = 5;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by adding and then subtracting a constant value from the array elements */
    vector<int> follow_vec = vec;
    transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [constant](int x) { return x + constant - constant; });

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 35: Performing an exclusive OR (XOR) operation with a specific value to the elements of the array, the positions of the searching
 * number in the modified array should align with the positions in the original array, regardless of the XOR operation.
 */
TEST_P(GetRangeParamTest, MR35) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int xor_value = 15; // XOR value

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by performing XOR operation with a specific value to the array elements */
    vector<int> follow_vec = vec;
    transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [xor_value](int x) { return x ^ xor_value; });

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 36: Reversing the sign of the elements in the array, the positions of the searching number in the modified array should align
 * with the positions in the original array, regardless of the sign reversal.
 */
TEST_P(GetRangeParamTest, MR36) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by reversing the sign of the array elements */
    vector<int> follow_vec = vec;
    transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), std::negate<int>());

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 37: Applying a modulo operation to the elements in the array, the positions of the searching number in the modified array should
 * align with the positions in the original array, regardless of the modulo operation applied.
 */
TEST_P(GetRangeParamTest, MR37) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    int modulo_value = 10; // Modulo value

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by applying a modulo operation to the array elements */
    vector<int> follow_vec = vec;
    transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [modulo_value](int x) { return x % modulo_value; });

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 38: Shuffling the elements in the array, the positions of the searching number in the shuffled array should align with the
 * positions in the original array.
 */
TEST_P(GetRangeParamTest, MR38) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by shuffling the array elements */
    vector<int> follow_vec = vec;
    random_shuffle(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 39: Combining the elements of the array by concatenating them, the positions of the searching number in the concatenated array
 * should align with the positions in the original array.
 */
TEST_P(GetRangeParamTest, MR39) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by concatenating the array elements */
    vector<int> follow_vec = vec;
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 40: Truncating the array to a smaller size, the positions of the searching number in the truncated array should align with the
 * positions in the original array.
 */
TEST_P(GetRangeParamTest, MR40) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    const size_t new_size = vec.size() / 2;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by truncating the array to a smaller size */
    vector<int> follow_vec(vec.begin(), vec.begin() + new_size);

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 41: Selecting a subset of elements from the array, the positions of the searching number in the subset array should align with
 * the positions in the original array.
 */
TEST_P(GetRangeParamTest, MR41) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    const size_t subsetSize = vec.size() / 2;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by selecting a subset of elements from the array */
    vector<int> follow_vec(vec.begin(), vec.begin() + subsetSize);

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

/**
 * @brief Metamorphic relation 42: Duplicating the elements of the array, the positions of the searching number in the duplicated array should align with the
 * positions in the original array.
 */
TEST_P(GetRangeParamTest, MR42) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input by duplicating the elements of the array */
    vector<int> follow_vec;
    for (const auto &element : vec) {
        follow_vec.push_back(element);
        follow_vec.push_back(element);
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0], follow_out[0]);
    EXPECT_EQ(source_out[1], follow_out[1]);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, GetRangeParamTest, testing::ValuesIn(gen_tcs_randomly()));