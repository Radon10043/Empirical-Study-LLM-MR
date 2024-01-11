#include <algorithm>
#include <gtest/gtest.h>
#include <random>
#include <string>
#include <unordered_set>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class FMPInputParamTest : public ::testing::TestWithParam<FMPInput> {};

/**
 * @brief Metamorphic Relation 3: Reversing the input array, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR3) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    std::reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 4: Multiplying all elements in the input array by a constant factor, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR4) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Define the constant factor */
    int factor = 2;

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int num : source_vec) {
        follow_vec.push_back(num * factor);
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 5: Adding a constant value to all elements in the input array, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR5) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Define the constant value */
    int constant = 5;

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int num : source_vec) {
        follow_vec.push_back(num + constant);
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 6: Removing duplicates from the input array, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR6) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    std::sort(follow_vec.begin(), follow_vec.end());
    follow_vec.erase(std::unique(follow_vec.begin(), follow_vec.end()), follow_vec.end());

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 7: Adding a sorted array to the original array, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR7) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    std::sort(follow_vec.begin(), follow_vec.end());
    follow_vec.insert(follow_vec.begin(), follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 8: Multiplying all even elements by a constant and dividing all odd elements by the same constant, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR8) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Define the constant factor */
    int factor = 3;

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int num : source_vec) {
        if (num % 2 == 0) {
            follow_vec.push_back(num * factor);
        } else {
            follow_vec.push_back(num / factor);
        }
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 9: Multiplying the entire input array by -1, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR9) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int num : source_vec) {
        follow_vec.push_back(num * -1);
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 10: Using a subset of the input array as the follow-up input, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR10) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec(source_vec.begin(), source_vec.begin() + source_vec.size() / 2);

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 11: Replacing all negative numbers with their absolute values, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR11) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int num : source_vec) {
        follow_vec.push_back(abs(num));
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 12: Repeating the input array multiple times, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR12) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Define the number of repetitions */
    int repetitions = 3;

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int i = 0; i < repetitions; i++) {
        follow_vec.insert(follow_vec.end(), source_vec.begin(), source_vec.end());
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 13: Inserting one or more zeros into the input array, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR13) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.insert(follow_vec.begin() + source_vec.size() / 2, 0); // Inserting one zero at the middle position

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 14: Combining the input array with its reverse, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR14) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    vector<int> reverse_vec = source_vec;
    std::reverse(reverse_vec.begin(), reverse_vec.end());
    follow_vec.insert(follow_vec.end(), reverse_vec.begin(), reverse_vec.end());

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 15: Adding a constant value to each element and then sorting the input array, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR15) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Define the constant value */
    int constant = 5;

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int& num : follow_vec) {
        num += constant;
    }
    std::sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 16: Replacing all elements in the input array with their squares, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR16) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int num : source_vec) {
        follow_vec.push_back(num * num);
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 17: Reversing the input array and then taking the absolute values of all elements, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR17) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    std::reverse(follow_vec.begin(), follow_vec.end());
    for (int& num : follow_vec) {
        num = abs(num);
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 18: Appending a constant value to all elements in the input array, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR18) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Define the constant value */
    int constant = 100;

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int num : source_vec) {
        follow_vec.push_back(num + constant);
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 19: Applying a transformation function to each element of the array, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR19) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Define the transformation function */
    auto transformFunc = [](int num) { return num * num - 3; };

    /* Construct follow-up input */
    vector<int> follow_vec;
    std::transform(source_vec.begin(), source_vec.end(), std::back_inserter(follow_vec), transformFunc);

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 20: Appending the reverse of the input array to the original array, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR20) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    vector<int> reverseVec = source_vec;
    std::reverse(reverseVec.begin(), reverseVec.end());
    follow_vec.insert(follow_vec.end(), reverseVec.begin(), reverseVec.end());

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 21: Multiplying the elements in the input array by a factor and then sorting the array, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR21) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Define the factor for multiplication */
    int factor = 2;

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int& num : follow_vec) {
        num *= factor;
    }
    std::sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 22: Interchanging the positions of two elements in the array, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR22) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    std::swap(follow_vec[0], follow_vec[1]); // Interchange the positions of the first two elements

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 23: Appending the first element of the array to itself, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR23) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.push_back(source_vec[0]);

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 24: Adding the maximum value of the original array to all elements, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR24) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Find the maximum value in the original array */
    int maxVal = *max_element(source_vec.begin(), source_vec.end());

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int num : source_vec) {
        follow_vec.push_back(num + maxVal);
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 25: Multiplying each element in the array by -1 and then sorting the array, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR25) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int n) { return -n; });
    std::sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 26: Taking the square root of the absolute value of each element in the array, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR26) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int num : source_vec) {
        follow_vec.push_back(static_cast<int>(sqrt(abs(num))));     /* Fixed By Radon */
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 27: Multiplying each element in the array by a constant and then reversing the array, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR27) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Define the constant for multiplication */
    int constant = 3;

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int& num : follow_vec) {
        num *= constant;
    }
    std::reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 28: Removing all occurrences of a specific element in the array, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR28) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);
    
    /* Define the element to be removed */
    int elementToRemove = 0;

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.erase(std::remove(follow_vec.begin(), follow_vec.end(), elementToRemove), follow_vec.end());

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 29: Multiplying all odd elements by 2 and all even elements by -1, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR29) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int num : source_vec) {
        if (num % 2 == 0) {
            follow_vec.push_back(-1 * num);
        } else {
            follow_vec.push_back(2 * num);
        }
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 30: Repeating the input array with an additional duplicate of the array, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR30) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.insert(follow_vec.end(), source_vec.begin(), source_vec.end());

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 31: Multiplying all elements in the array by 0, the output remains the same.
 *
 */
TEST_P(FMPInputParamTest, MR31) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int num : source_vec) {
        follow_vec.push_back(0);
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 32: Incrementing all elements in the array by 1, the output is incremented by 1.
 *
 */
TEST_P(FMPInputParamTest, MR32) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int num : source_vec) {
        follow_vec.push_back(num + 1);
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out + 1, follow_out);
}

/**
 * @brief Metamorphic Relation 33: Replacing all elements in the array with 1, the output is 1.
 *
 */
TEST_P(FMPInputParamTest, MR33) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input */
    vector<int> follow_vec(source_vec.size(), 1);

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(1, follow_out);
}

/**
 * @brief Metamorphic Relation 34: Multiplying the elements in the array by a factor and then adding a constant value, the output relation is preserved.
 *
 */
TEST_P(FMPInputParamTest, MR34) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Define factor and constant */
    int factor = 2;
    int constant = 5;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Applying the transformation to follow-up input */
    vector<int> follow_vec;
    for (int num : source_vec) {
        follow_vec.push_back(num * factor + constant);
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 35: Reversing the input array twice, the output is the same as reversing the input array once.
 *
 */
TEST_P(FMPInputParamTest, MR35) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Applying the transformation to follow-up input */
    vector<int> follow_vec = source_vec;
    std::reverse(follow_vec.begin(), follow_vec.end());
    std::reverse(follow_vec.begin(), follow_vec.end()); // Reversing the array twice

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 36: Sorting the input array, the output relation is preserved.
 *
 */
TEST_P(FMPInputParamTest, MR36) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Applying the transformation to follow-up input */
    vector<int> follow_vec = source_vec;
    std::sort(follow_vec.begin(), follow_vec.end()); // Sorting the array

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 37: Applying a square root transformation to the elements in the input array, the output relation is preserved.
 *
 */
TEST_P(FMPInputParamTest, MR37) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Applying the transformation to follow-up input */
    vector<int> follow_vec;
    for (int num : source_vec) {
        follow_vec.push_back(sqrt(num));
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 38: Removing all negative elements from the input array, the output relation is preserved.
 *
 */
TEST_P(FMPInputParamTest, MR38) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Applying the transformation to follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.erase(std::remove_if(follow_vec.begin(), follow_vec.end(), [](int i) { return i < 0; }), follow_vec.end());

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 39: Replacing all duplicate elements in the input array with their square values, the output relation is preserved.
 *
 */
TEST_P(FMPInputParamTest, MR39) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Applying the transformation to follow-up input */
    vector<int> follow_vec = source_vec;
    std::unordered_set<int> unique_nums;
    for (auto it = follow_vec.begin(); it != follow_vec.end();) {
        if (!unique_nums.insert(*it).second) {
            *it = (*it) * (*it);
        }
        ++it;
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 40: Adding a constant value to one subset of the input array and subtracting the same constant value from another disjoint subset, the output relation is preserved.
 *
 */
TEST_P(FMPInputParamTest, MR40) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Define the constant value */
    int constant = 10;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Applying the transformation to follow-up input */
    vector<int> follow_vec = source_vec;
    int halfSize = source_vec.size() / 2;
    for (int i = 0; i < halfSize; ++i) {
        follow_vec[i] += constant;
    }
    for (int i = halfSize; i < source_vec.size(); ++i) {
        follow_vec[i] -= constant;
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 41: Reversing the input array and then adding the reversed array as a suffix, the output relation is preserved.
 *
 */
TEST_P(FMPInputParamTest, MR41) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Applying the transformation to follow-up input */
    vector<int> follow_vec = source_vec;
    vector<int> reversed_vec = source_vec;
    std::reverse(reversed_vec.begin(), reversed_vec.end());
    follow_vec.insert(follow_vec.end(), reversed_vec.begin(), reversed_vec.end());

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 42: Multiplying all elements in the array by 0 and then replacing the first element with 1, the output relation is preserved.
 *
 */
TEST_P(FMPInputParamTest, MR42) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Applying the transformation to follow-up input */
    vector<int> follow_vec = source_vec;
    std::transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), [](int n) { return 0; });
    follow_vec[0] = 1;

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, FMPInputParamTest, testing::ValuesIn(gen_tcs_randomly()));