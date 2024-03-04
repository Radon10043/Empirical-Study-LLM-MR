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
 * @brief Metamorphic Relation 1: Adding one negative integer to the source array, the output should be the same.
 *
 */
TEST_P(FMPInputParamTest, MR1) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.push_back(-1); // Adding a negative integer to the array

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 2: Replacing all positive integers in the input array with their negation, the output will be the same.
 *
 */
TEST_P(FMPInputParamTest, MR2) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        if (num > 0) {
            num = -num; // Replace positive integers with their negation
        }
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 3: Multiplying all elements in the input array by a positive integer, the output should be the same.
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
    int multiplier = 2; // Multiplying all elements by a positive integer
    for (int &num : follow_vec) {
        num *= multiplier;
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 4: Reversing the elements in the input array, the output should be the same.
 *
 */
TEST_P(FMPInputParamTest, MR4) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    reverse(follow_vec.begin(), follow_vec.end()); // Reverse the elements

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 5: Adding a constant value to all elements in the input array, the output should be incremented by the same constant.
 *
 */
TEST_P(FMPInputParamTest, MR5) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    int constant = 5; // Add a constant value to all elements
    for (int &num : follow_vec) {
        num += constant;
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out + constant, follow_out);
}

/**
 * @brief Metamorphic Relation 6: Sorting the elements in the input array, the output should be the same.
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
    sort(follow_vec.begin(), follow_vec.end()); // Sort the elements

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 7: Multiplying all elements in the input array by -1, the output should be the same.
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
    for (int &num : follow_vec) {
        num *= -1; // Multiply all elements by -1
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 8: Replacing all elements in the input array with their absolute values, the output should be the same.
 *
 */
TEST_P(FMPInputParamTest, MR8) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        num = abs(num); // Replace each element with its absolute value
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 9: Replacing all elements in the input array with their squares, the output should be the same.
 *
 */
TEST_P(FMPInputParamTest, MR9) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        num = num * num; // Replace each element with its square
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 10: Adding one to all elements in the input array, the output should also increase by one.
 *
 */
TEST_P(FMPInputParamTest, MR10) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        num += 1; // Adding one to each element
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out + 1, follow_out);
}

/**
 * @brief Metamorphic Relation 11: Removing all duplicate elements in the input array, the output should be the same.
 *
 */
TEST_P(FMPInputParamTest, MR11) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    sort(follow_vec.begin(), follow_vec.end());
    follow_vec.erase(unique(follow_vec.begin(), follow_vec.end()), follow_vec.end()); // Remove duplicates

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 12: Adding a new positive integer greater than the size of the array to the input array, the output should be the same as before.
 *
 */
TEST_P(FMPInputParamTest, MR12) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.push_back(source_vec.size() + 1); // Add a new positive integer greater than the size of the array

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 13: Removing a positive integer from the input array, the output should be the same.
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
    follow_vec.erase(remove_if(follow_vec.begin(), follow_vec.end(), [](int x) { return x > 0; }), follow_vec.end()); // Remove positive integers

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 14: Reversing the order of the positive elements in the input array, the output should be the same.
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
    reverse(follow_vec.begin(), follow_vec.end());
    // Only consider positive elements for reversal
    auto pos_start = partition(follow_vec.begin(), follow_vec.end(), [](int x) { return x > 0; });
    reverse(pos_start, follow_vec.end()); // Reverse the positive elements

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 15: Removing all negative elements from the input array, the output should be the same.
 *
 */
TEST_P(FMPInputParamTest, MR15) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.erase(remove_if(follow_vec.begin(), follow_vec.end(), [](int x) { return x <= 0; }), follow_vec.end()); // Remove non-positive elements

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 16: Doubling all positive elements and removing negative elements from the input array, the output should be the same.
 *
 */
TEST_P(FMPInputParamTest, MR16) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.erase(remove_if(follow_vec.begin(), follow_vec.end(), [](int x) { return x <= 0; }), follow_vec.end()); // Remove non-positive elements
    for (int &num : follow_vec) {
        num *= 2; // Double all positive elements
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 17: Multiplying all negative elements in the input array by -1, the output should be the same.
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
    for (int &num : follow_vec) {
        if (num < 0) {
            num *= -1; // Multiply negative elements by -1
        }
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 18: Replacing all odd elements in the input array with their squares, the output should be the same.
 *
 */
TEST_P(FMPInputParamTest, MR18) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        if (num % 2 != 0) {
            num = num * num; // Replace each odd element with its square
        }
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// fixed max_element -> max_val
/**
 * @brief Metamorphic Relation 19: Adding the maximum element in the input array to all elements, the output should be the same as before.
 *
 */
TEST_P(FMPInputParamTest, MR19) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Find the maximum element in the input array */
    int max_val = *max_element(source_vec.begin(), source_vec.end());

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        num += max_val; // Add the maximum element to all elements
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 20: Randomly shuffling the positive elements in the input array, the output should be the same.
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
    // Random shuffle for positive elements only
    vector<int> positive_elements;
    copy_if(source_vec.begin(), source_vec.end(), back_inserter(positive_elements), [](int x) { return x > 0; });
    shuffle(positive_elements.begin(), positive_elements.end(), std::default_random_engine());

    // Replace the positive elements with the shuffled ones
    auto pos_it = positive_elements.begin();
    for (int &num : follow_vec) {
        if (num > 0) {
            num = *pos_it++;
        }
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 21: Replacing all even elements in the input array with their squares, the output should be the same.
 *
 */
TEST_P(FMPInputParamTest, MR21) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        if (num % 2 == 0) {
            num = num * num; // Replace each even element with its square
        }
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// fixed min_element -> min_val
/**
 * @brief Metamorphic Relation 22: Adding the minimum element in the input array to all elements, the output should be the same as before.
 *
 */
TEST_P(FMPInputParamTest, MR22) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Find the minimum element in the input array */
    int min_val = *min_element(source_vec.begin(), source_vec.end());

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        num += min_val; // Add the minimum element to all elements
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 23: Negating all elements in the input array, the output should be the same.
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
    for (int &num : follow_vec) {
        num = -num; // Negate all elements
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 24: Replacing all elements in the input array with their cubes, the output should be the same.
 *
 */
TEST_P(FMPInputParamTest, MR24) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        num = num * num * num; // Replace each element with its cube
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 25: Sorting the input array in descending order, the output should be the same as before.
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
    sort(follow_vec.rbegin(), follow_vec.rend()); // Sort the array in descending order

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 26: Replacing all elements in the input array with their absolute cubes, the output should be the same.
 *
 */
TEST_P(FMPInputParamTest, MR26) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        num = abs(num * num * num); // Replace each element with its absolute cube
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 27: Replacing all elements in the input array with their negative values, the output should be the same as before.
 *
 */
TEST_P(FMPInputParamTest, MR27) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        num = -abs(num); // Replace each element with its negative value
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 28: Negating the elements and then sorting the input array, the output should be the same as before.
 *
 */
TEST_P(FMPInputParamTest, MR28) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        num = -num; // Negate each element
    }
    sort(follow_vec.begin(), follow_vec.end()); // Sort the elements

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 29: Replacing all elements in the input array with their reciprocals, the output should be the same as before.
 *
 */
TEST_P(FMPInputParamTest, MR29) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec(source_vec.size());
    // Calculate the reciprocals of the elements
    transform(source_vec.begin(), source_vec.end(), follow_vec.begin(), [](int x) {
        return (x != 0) ? 1 / x : 0; // Handle division by zero
    });

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 30: Replacing all elements in the input array with their negated reciprocals, the output should be the same as before.
 *
 */
TEST_P(FMPInputParamTest, MR30) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec(source_vec.size());
    // Calculate the negated reciprocals of the elements
    transform(source_vec.begin(), source_vec.end(), follow_vec.begin(), [](int x) {
        return (x != 0) ? -1 / x : 0; // Handle division by zero
    });

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 31: Applying a hash function to the elements in the input array, the output should be the same as before.
 *
 */
TEST_P(FMPInputParamTest, MR31) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Define a simple hash function */
    auto simpleHash = [](int x) {
        return x % 10; // Modulus by 10 as a simple hash function
    };

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        num = simpleHash(num); // Apply the hash function to each element
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 32: Randomly changing the sign of the elements in the input array, the output should be the same as before.
 *
 */
TEST_P(FMPInputParamTest, MR32) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        if (rand() % 2 == 0) {
            num = -num; // Randomly change the sign of each element
        }
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 33: Applying a linear transformation to the elements in the input array, the output should be the same as before.
 *
 */
TEST_P(FMPInputParamTest, MR33) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    // Define the linear transformation for demonstration purposes
    int a = 2; // Scaling factor
    int b = 3; // Translation factor

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        num = a * num + b; // Apply the linear transformation
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 34: Doubling each element and then adding its square, the output should be the same as before.
 *
 */
TEST_P(FMPInputParamTest, MR34) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        num = num * num + num; // Doubling each element and then adding its square
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 35: Adding the square of each element to itself, the output should be the same as before.
 *
 */
TEST_P(FMPInputParamTest, MR35) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    // Define the morphing function for demonstration purposes
    auto morphingFunction = [](int x) {
        return x + (x * x); // Adding the square of the element to itself
    };

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        num = morphingFunction(num); // Apply the morphing function
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 36: Applying a complex mathematical function to the elements in the input array, the output should be the same as before.
 *
 */
TEST_P(FMPInputParamTest, MR36) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    // Define the complex function for demonstration purposes
    auto complexFunction = [](int x) {
        return (3 * x * x) + (5 * x) + 7; // A complex mathematical function
    };

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        num = complexFunction(num); // Apply the complex function
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 37: Squaring each element and then adding the original value, the output should be the same as before.
 *
 */
TEST_P(FMPInputParamTest, MR37) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        num = num * num + num; // Square each element and then adding the original value
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 38: Substracting 1 from each element in the input array, the output should be decremented by the same number.
 *
 */
TEST_P(FMPInputParamTest, MR38) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        num -= 1; // Substract 1 from each element
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out - 1, follow_out);
}

/**
 * @brief Metamorphic Relation 39: Adding 1 to each element in the input array, the output should be incremented by the same number.
 *
 */
TEST_P(FMPInputParamTest, MR39) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        num += 1; // Add 1 to each element
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out + 1, follow_out);
}

/**
 * @brief Metamorphic Relation 40: Replacing each element in the input array with a random number, the output should be the same as before.
 *
 */
TEST_P(FMPInputParamTest, MR40) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int &num : source_vec) {
        num = rand(); // Replace each element with a random number
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, FMPInputParamTest, testing::ValuesIn(gen_tcs_randomly()));