#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class QuickSortParamTest : public ::testing::TestWithParam<QuickSortInput> {};

/**
 * @brief Metamorphic Relation 1: Reversing the elements in the input array, the output will be in reverse order.
 *
 */
TEST_P(QuickSortParamTest, MR1) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    reverse(source_out.begin(), source_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 2: Multiplying a constant to each element in the input array, then each element of the output array will be
 * larger by a factor of the constant than the element at the same location of the source input.
 *
 */
TEST_P(QuickSortParamTest, MR2) {
    int constant = 2;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem *= constant;

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    for (auto &elem : follow_out)
        elem /= constant;
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 3: Repeating the elements in the input array, the output will remain unchanged.
 *
 */
TEST_P(QuickSortParamTest, MR3) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int i = 0; i < 3; ++i) {
        follow_vec.insert(follow_vec.end(), source_vec.begin(), source_vec.end());
    }
    
    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 4: Sorting the input array in descending order, the output will be in ascending order.
 *
 */
TEST_P(QuickSortParamTest, MR4) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    sort(follow_vec.rbegin(), follow_vec.rend());  // Sort in descending order
    
    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    reverse(follow_out.begin(), follow_out.end());  // Reverse to get in ascending order
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 5: Appending a value to the input array, the output will remain unchanged.
 *
 */
TEST_P(QuickSortParamTest, MR5) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.push_back(100);  // Append a value
    
    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 6: Taking the absolute value of each element in the input array, the output will remain unchanged.
 *
 */
TEST_P(QuickSortParamTest, MR6) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem = abs(elem);  // Take absolute value
    
    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 7: Replacing all elements in the input array with a single value, the output will be sorted and filled with the single value.
 *
 */
TEST_P(QuickSortParamTest, MR7) {
    int single_value = 10;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input */
    vector<int> follow_vec(source_vec.size(), single_value);  // Replace with single value
    
    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    vector<int> expected_out(source_vec.size(), single_value);
    EXPECT_EQ(follow_out, expected_out);
}

/**
 * @brief Metamorphic Relation 8: Removing duplicates from the input array, the output will remain unchanged.
 *
 */
TEST_P(QuickSortParamTest, MR8) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    sort(follow_vec.begin(), follow_vec.end());
    follow_vec.erase(unique(follow_vec.begin(), follow_vec.end()), follow_vec.end());  // Remove duplicates
    
    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 9: Reversing the elements in the input array, the output will be in reverse order and equal to source output.
 *
 */
TEST_P(QuickSortParamTest, MR9) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    reverse(follow_vec.begin(), follow_vec.end());
    
    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    reverse(source_out.begin(), source_out.end());  // Reverse to get in ascending order
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 10: Rotating the elements in the input array, the output will remain unchanged.
 *
 */
TEST_P(QuickSortParamTest, MR10) {  // Fixed
    int shift = 3;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    if (source_vec.size() < shift) GTEST_SKIP();

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    rotate(follow_vec.begin(), follow_vec.begin() + shift, follow_vec.end());  // Rotate the array
    
    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 11: Multipling all elements by -1 in the input array, the output will be sorted and reversed.
 *
 */
TEST_P(QuickSortParamTest, MR11) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem *= -1;  // Multiply by -1
    
    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    reverse(follow_out.begin(), follow_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 12: Sorting the input array using a different sorting algorithm, the output will be in the same order as the source output.
 *
 */
TEST_P(QuickSortParamTest, MR12) {  // Fixed
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);
    
    /* Get follow-up output using a different sorting algorithm */
    vector<int> follow_out = source_vec;
    sort(follow_out.begin(), follow_out.end());  // Sort using a different algorithm

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 13: Appending the reverse of the input array to the input array, the output will be sorted.
 *
 */
TEST_P(QuickSortParamTest, MR13) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);
    
    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    vector<int> reverse_source_vec = source_vec;
    reverse(reverse_source_vec.begin(), reverse_source_vec.end());
    follow_vec.insert(follow_vec.end(), reverse_source_vec.begin(), reverse_source_vec.end());  // Append reverse of the input array
    
    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 14: Sorting the input array once and then sorting it again, the output will remain unchanged.
 *
 */
TEST_P(QuickSortParamTest, MR14) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);
    
    /* Get follow-up output by sorting twice */
    vector<int> follow_out = quick_sort(source_out);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 15: Interchanging any two elements of the input array, the output will change accordingly with only those two elements swapped.
 *
 */
TEST_P(QuickSortParamTest, MR15) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input by swapping two elements */
    vector<int> follow_vec = source_vec;
    if (follow_vec.size() > 1) {
        swap(follow_vec[0], follow_vec[1]);
    }
    
    /* Get source and follow-up outputs */
    vector<int> source_out = quick_sort(source_vec);
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    bool swapped = false;
    for (int i = 0; i < source_vec.size(); ++i) {
        if (follow_vec[i] != source_vec[i]) {
            if (!swapped) {
                swap(follow_vec[0], follow_vec[1]);
                swapped = true;
            } else {
                break;  // Only one pair should be swapped
            }
        }
    }
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 16: Adding a constant to each element in the input array, the output will change accordingly by adding the constant to each element.
 *
 */
TEST_P(QuickSortParamTest, MR16) {  // Fixed
    int constant = 5;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input by adding a constant to each element */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec) {
        elem += constant;
    }
    
    /* Get source and follow-up outputs */
    vector<int> source_out = quick_sort(source_vec);
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    for (int i = 0; i < source_vec.size(); ++i) {
        follow_out[i] -= constant;
    }
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 17: Subtracting a constant from each element in the input array, the output will change accordingly by subtracting the constant from each element.
 *
 */
TEST_P(QuickSortParamTest, MR17) {  // Fixed
    int constant = 5;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input by subtracting a constant from each element */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec) {
        elem -= constant;
    }
    
    /* Get source and follow-up outputs */
    vector<int> source_out = quick_sort(source_vec);
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    for (int i = 0; i < source_vec.size(); ++i) {
        follow_out[i] += constant;
    }
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 18: Multiplying a constant to each element in the input array, the output will change accordingly by multiplying the constant to each element.
 *
 */
TEST_P(QuickSortParamTest, MR18) {  // Fixed
    int constant = 3;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input by multiplying a constant to each element */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec) {
        elem *= constant;
    }
    
    /* Get source and follow-up outputs */
    vector<int> source_out = quick_sort(source_vec);
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    for (int i = 0; i < source_vec.size(); ++i) {
        follow_out[i] /= constant;
    }
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 19: Appending the square of each element to the input array, the output will be sorted.
 *
 */
TEST_P(QuickSortParamTest, MR19) {  // Fixed
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);
    
    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int i = 0; i < source_vec.size(); ++i) {
        follow_vec.push_back(follow_vec[i] * follow_vec[i]);  // Append the square of each element
    }
    
    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 20: Reversing the elements in the input array and then taking absolute value of each element, the output will be in ascending order.
 *
 */
TEST_P(QuickSortParamTest, MR20) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);
    
    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    reverse(follow_vec.begin(), follow_vec.end());
    for (auto &elem : follow_vec) {
        elem = abs(elem);
    }
    
    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 21: Sorting the elements in the input array, the output will remain unchanged.
 *
 */
TEST_P(QuickSortParamTest, MR21) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    stable_sort(follow_vec.begin(), follow_vec.end());  // Sort without changing the order of equal elements

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 22: Reversing the elements in the input array, the output will be in reversed order.
 *
 */
TEST_P(QuickSortParamTest, MR22) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    reverse(follow_vec.begin(), follow_vec.end());  // Reverse the elements

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    reverse(source_out.begin(), source_out.end());
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 23: Concatenating a reversed copy of the input array to the existing input array, the output will be sorted.
 *
 */
TEST_P(QuickSortParamTest, MR23) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    vector<int> reversed_source_vec = source_vec;
    reverse(reversed_source_vec.begin(), reversed_source_vec.end());
    follow_vec.insert(follow_vec.end(), reversed_source_vec.begin(), reversed_source_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 24: Taking the square root of each element in the input array, the output will be sorted.
 *
 */
TEST_P(QuickSortParamTest, MR24) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (auto &elem : source_vec) {
        follow_vec.push_back(sqrt(elem));  // Taking square root of each element
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 25: Removing all occurrences of a specific value from the input array, the output will be sorted without the removed value.
 *
 */
TEST_P(QuickSortParamTest, MR25) {
    int value_to_remove = 5;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input by removing all occurrences of the specific value */
    vector<int> follow_vec;
    for (auto &elem : source_vec) {
        if (elem != value_to_remove) {
            follow_vec.push_back(elem);
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 26: Replacing all elements in the input array with their squares, the output will be sorted.
 *
 */
TEST_P(QuickSortParamTest, MR26) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input by replacing each element with its square */
    vector<int> follow_vec;
    for (auto &elem : source_vec) {
        follow_vec.push_back(elem * elem);
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 27: Multiplying all elements by a constant and then adding another constant to each element in the input array, the output will be sorted.
 *
 */
TEST_P(QuickSortParamTest, MR27) {
    int multiply_constant = 2;
    int add_constant = 3;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input by applying two constants to each element */
    vector<int> follow_vec;
    for (auto &elem : source_vec) {
        follow_vec.push_back((elem * multiply_constant) + add_constant);
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 28: Using a modulus operation on each element in the input array, the output will be sorted.
 *
 */
TEST_P(QuickSortParamTest, MR28) {
    int modulus_val = 10;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input using modulus operation on each element */
    vector<int> follow_vec;
    for (auto &elem : source_vec) {
        follow_vec.push_back(elem % modulus_val);
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 29: Multiplying all elements by -1 and then adding a constant to each element in the input array, the output will be sorted in reverse order.
 *
 */
TEST_P(QuickSortParamTest, MR29) {
    int add_constant = 100;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input by applying the transformations to each element */
    vector<int> follow_vec;
    for (auto &elem : source_vec) {
        follow_vec.push_back((elem * -1) + add_constant);
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    reverse(follow_out.begin(), follow_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 30: Applying a logarithm operation to each element in the input array, the output will be sorted.
 *
 */
TEST_P(QuickSortParamTest, MR30) {  // Fixed
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input using logarithm operation on each element */
    vector<int> follow_vec;
    for (auto &elem : source_vec) {
        follow_vec.push_back(log(elem + 1));  // Avoiding logarithm of 0 or negative values
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 31: Shifting elements to the right in the input array, the output will be sorted but shifted accordingly.
 *
 */
TEST_P(QuickSortParamTest, MR31) {
    int shift_distance = 2;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input by shifting elements to the right */
    vector<int> follow_vec = source_vec;
    rotate(follow_vec.rbegin(), follow_vec.rbegin() + shift_distance, follow_vec.rend());  // Shift to the right
    
    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    rotate(follow_out.begin(), follow_out.begin() + shift_distance, follow_out.end());  // Shift to the right
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 32: Applying a step function to each element in the input array, the output will be sorted.
 *
 */
TEST_P(QuickSortParamTest, MR32) {  // Fixed
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input using step function on each element */
    vector<int> follow_vec;
    for (auto &elem : source_vec)
        follow_vec.push_back(elem >= 0 ? 1 : -1);  // Step function

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 33: Sorting the input array in descending order and then sorting it in ascending order, the output will be in ascending order.
 *
 */
TEST_P(QuickSortParamTest, MR33) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input by sorting in descending order and then in ascending order */
    vector<int> follow_vec = source_vec;
    sort(follow_vec.rbegin(), follow_vec.rend());  // Sort in descending order
    sort(follow_vec.begin(), follow_vec.end());  // Sort in ascending order
    
    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, follow_vec);
}

/**
 * @brief Metamorphic Relation 34: Sorting subarrays of the input array, the output will be sorted using the results of the subarrays.
 *
 */
TEST_P(QuickSortParamTest, MR34) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    // Define subarray indices
    int start = 1;
    int end = 4;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input by sorting subarrays */
    vector<int> follow_vec = source_vec;
    sort(follow_vec.begin() + start, follow_vec.begin() + end + 1);  // Sort the subarray defined by indices
    
    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 35: Doubling each element in the input array, the output will be sorted.
 *
 */
TEST_P(QuickSortParamTest, MR35) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input by doubling each element */
    vector<int> follow_vec;
    for (auto &elem : source_vec) {
        follow_vec.push_back(elem * 2);
    }

    /* Get source and follow-up outputs */
    vector<int> source_out = quick_sort(source_vec);
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 36: Halving each element in the input array, the output will be sorted.
 *
 */
TEST_P(QuickSortParamTest, MR36) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input by halving each element */
    vector<int> follow_vec;
    for (auto &elem : source_vec) {
        follow_vec.push_back(elem / 2);
    }

    /* Get source and follow-up outputs */
    vector<int> source_out = quick_sort(source_vec);
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 37: Applying a bitwise NOT operation to each element in the input array, the output will be sorted in reverse order.
 *
 */
TEST_P(QuickSortParamTest, MR37) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input by applying bitwise NOT operation to each element */
    vector<int> follow_vec;
    for (auto &elem : source_vec) {
        follow_vec.push_back(~elem);
    }

    /* Get source and follow-up outputs */
    vector<int> source_out = quick_sort(source_vec);
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    reverse(follow_out.begin(), follow_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 38: Reordering elements in the input array, the output will be sorted as per the reordered sequence.
 *
 */
TEST_P(QuickSortParamTest, MR38) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input by reordering elements */
    vector<int> follow_vec = source_vec;
    random_shuffle(follow_vec.begin(), follow_vec.end());  // Reorder the elements

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    sort(source_vec.begin(), source_vec.end());  // Sort the source vector
    EXPECT_EQ(follow_out, source_vec);
}
/**
 * @brief Metamorphic Relation 39: Shifting all elements by a constant value in the input array, the output will remain sorted with shifted values.
 *
 */
TEST_P(QuickSortParamTest, MR39) {
    int shift_value = 10;

    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = quick_sort(source_vec);

    /* Construct follow-up input by shifting all elements by a constant */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec) {
        elem += shift_value;
    }

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    for (auto &elem : follow_out) {
        elem -= shift_value;
    }
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 40: Sorting only the first half of the input array, the output will be sorted as per the sorted first half.
 *
 */
TEST_P(QuickSortParamTest, MR40) {
    /* Get source input */
    QuickSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input by sorting only the first half of the elements */
    vector<int> follow_vec = source_vec;
    sort(follow_vec.begin(), follow_vec.begin() + (follow_vec.size() / 2)); // Sort only the first half

    /* Get follow-up output */
    vector<int> follow_out = quick_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, follow_vec);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, QuickSortParamTest, testing::ValuesIn(gen_tcs_randomly()));