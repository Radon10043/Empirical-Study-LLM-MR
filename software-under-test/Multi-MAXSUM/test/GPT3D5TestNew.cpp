#include <algorithm>
#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include <random>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class MultiMAXSUMParamTest : public ::testing::TestWithParam<MultiMAXSUMInput> {};

/**
 * @brief Metamorphic Relation 1: Increasing the value of m, the follow-up output should be the same as or larger than the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR1) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    int follow_up_m = source_m + 1;

    /* Get follow-up output */
    int follow_out = multi_maxsum(source_vec, follow_up_m);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 2: Reversing the input array, the follow-up output should be the same as the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR2) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    reverse(source_vec.begin(), source_vec.end());

    /* Get follow-up output */
    int follow_out = multi_maxsum(source_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 3: Adding a constant value to each element of the input array, the follow-up output should be increased by the constant times the number of subarrays (m).
 *
 */
TEST_P(MultiMAXSUMParamTest, MR3) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    int constant = 5; // Example constant value
    for (int i = 0; i < follow_vec.size(); ++i) {
        follow_vec[i] += constant;
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out + constant * source_m);
}

/**
 * @brief Metamorphic Relation 4: Multiplying each element of the input array by a constant value, the follow-up output should be multiplied by the constant to the power of the number of subarrays (m).
 *
 */
TEST_P(MultiMAXSUMParamTest, MR4) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    int constant = 2; // Example constant value
    for (int i = 0; i < follow_vec.size(); ++i) {
        follow_vec[i] *= constant;
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, pow(source_out, source_m) * pow(constant, source_m));
}

/**
 * @brief Metamorphic Relation 5: Reordering the elements of the input array, the follow-up output should be the same as the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR5) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 6: Scaling the input array by a factor, the follow-up output should be scaled by the same factor.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR6) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    int scale_factor = 3; // Example scale factor
    for (int i = 0; i < follow_vec.size(); ++i) {
        follow_vec[i] *= scale_factor;
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out * scale_factor);
}

/**
 * @brief Metamorphic Relation 7: Shifting all elements of the input array by a fixed number of positions to the left, the follow-up output should remain the same.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR7) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    int shift = 2; // Example shift amount

    /* Perform left shift */
    rotate(follow_vec.begin(), follow_vec.begin() + shift, follow_vec.end());

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 8: Performing a cyclic rotation on the input array, the follow-up output should remain the same.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR8) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;

    /* Perform cyclic rotation */
    rotate(follow_vec.rbegin(), follow_vec.rbegin() + 1, follow_vec.rend());

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 9: Multiplying all elements of the input array by -1, the follow-up output should remain the same.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR9) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    
    /* Multiply all elements by -1 */
    for (int i = 0; i < follow_vec.size(); ++i) {
        follow_vec[i] *= -1;
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 10: Randomly shuffling the input array, the follow-up output should remain the same.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR10) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;

    /* Randomly shuffle the elements */
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(follow_vec.begin(), follow_vec.end(), std::default_random_engine(seed));

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 11: Taking a subarray of the input array, the follow-up output should be less than or equal to the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR11) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;
    int n = source_vec.size();

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec(source_vec.begin(), source_vec.begin() + n / 2); // Taking the first half as follow-up input

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 12: Duplicating the input array, the follow-up output should be at least double the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR12) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.insert(follow_vec.end(), source_vec.begin(), source_vec.end()); // Concatenating the input array with itself

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_GE(follow_out, source_out * 2);
}

/**
 * @brief Metamorphic Relation 13: Replacing all elements of the input array with their absolute values, the follow-up output should be the same as the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR13) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int i = 0; i < follow_vec.size(); ++i) {
        follow_vec[i] = abs(follow_vec[i]);
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 14: Replacing the input array with a sorted version (in non-decreasing order), the follow-up output should be the same as the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR14) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 15: Applying a reverse sorting to the input array, the follow-up output should be the same as the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR15) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    sort(follow_vec.rbegin(), follow_vec.rend());

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 16: Multiplying all elements of the input array by a negative number, the output remains the same.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR16) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int i = 0; i < follow_vec.size(); ++i) {
        follow_vec[i] *= -1;
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 17: Appending the reverse of the input array to itself, the follow-up output should be at least double the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR17) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    vector<int> temp = source_vec;
    reverse(temp.begin(), temp.end());
    follow_vec.insert(follow_vec.end(), temp.begin(), temp.end());

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_GE(follow_out, source_out * 2);
}

/**
 * @brief Metamorphic Relation 18: Repeating the input array multiple times, the follow-up output should be at least equal to the count of repetitions times the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR18) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;
    int repetition_count = 3;  // Number of times to repeat the array

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int i = 0; i < repetition_count; ++i) {
        follow_vec.insert(follow_vec.end(), source_vec.begin(), source_vec.end());
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_GE(follow_out, source_out * repetition_count);
}

/**
 * @brief Metamorphic Relation 19: Multiplying each element of the input array by a different scaling factor, the follow-up output should be scaled accordingly.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR19) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    vector<int> scaling_factors = {1, 2, 3, 4, 5}; // Example scaling factors
    for (int i = 0; i < follow_vec.size(); ++i) {
        follow_vec[i] *= scaling_factors[i % scaling_factors.size()]; // Applying different scaling factors
    }

    /* Get follow-up output */
    int expected_follow_out = source_out;
    for (int i = 0; i < scaling_factors.size(); ++i) {
        expected_follow_out *= scaling_factors[i];
    }

    /* Verification */
    EXPECT_EQ(multi_maxsum(follow_vec, source_m), expected_follow_out);
}

/**
 * @brief Metamorphic Relation 20: Replacing a subset of elements in the input array with 0, the follow-up output should be smaller than or equal to the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR20) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;
    int n = source_vec.size();

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    int start_index = n / 4;
    int end_index = n / 2;
    fill(follow_vec.begin() + start_index, follow_vec.begin() + end_index, 0); // Replacing a subset of elements with 0

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 21: Replacing all even elements of the input array with their negative values, the follow-up output should be the same as the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR21) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int i = 0; i < follow_vec.size(); ++i) {
        if (follow_vec[i] % 2 == 0) {
            follow_vec[i] *= -1;
        }
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 22: Replacing all negative elements of the input array with 0, the follow-up output should be the same as or larger than the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR22) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int i = 0; i < follow_vec.size(); ++i) {
        if (follow_vec[i] < 0) {
            follow_vec[i] = 0;
        }
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 23: Rotating the input array by a certain number of positions, the follow-up output should remain the same.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR23) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;
    int n = source_vec.size();

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    int shift = 2;  // Example shift amount
    
    /* Perform rotation */
    rotate(follow_vec.begin(), follow_vec.begin() + shift, follow_vec.end());

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 24: Reversing the elements of the input array, the follow-up output should remain the same.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR24) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input by reversing the array */
    vector<int> follow_vec = source_vec;
    reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 25: Replacing all elements of the input array with the absolute difference between the element and a fixed value, the follow-up output should remain the same.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR25) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;
    int fixed_value = 5;   // Example fixed value

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int i = 0; i < source_vec.size(); ++i) {
        follow_vec.push_back(abs(source_vec[i] - fixed_value));  // Absolute difference from the fixed value
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 26: Multiplying the input array by a constant factor and then taking the absolute values, the follow-up output remains the same.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR26) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;
    int constant = 2;   // Example constant factor

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int i = 0; i < follow_vec.size(); ++i) {
        follow_vec[i] = abs(follow_vec[i] * constant);  // Applying constant factor and taking absolute value
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 27: If all elements of the input are positive, keep all even elements and set all odd elements to 1, the follow-up output should be less than or equal to the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR27) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int i = 0; i < follow_vec.size(); ++i) {
        if (follow_vec[i] % 2 != 0) {
            follow_vec[i] = 1;  // Set to 1 if odd
        }
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 28: Adding a constant to all elements of the input array, the follow-up output should be increased by the sum of the array multiplied by the constant.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR28) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;
    int constant = 2;  // Example constant value
    
    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int val : source_vec) {
        follow_vec.push_back(val + constant);
    }

    /* Get follow-up output */
    int follow_up_out = multi_maxsum(follow_vec, source_m);

    /* Calculate the expected follow-up output */
    int expected_follow_up_out = source_out + accumulate(source_vec.begin(), source_vec.end(), 0) * constant;

    /* Verification */
    EXPECT_EQ(follow_up_out, expected_follow_up_out);
}

/**
 * @brief Metamorphic Relation 29: Taking the absolute difference between consecutive elements in the input array, the follow-up output should remain the same.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR29) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int i = 1; i < source_vec.size(); ++i) {
        follow_vec.push_back(abs(source_vec[i] - source_vec[i-1]));  // Absolute difference between consecutive elements
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 30: Replacing the elements of the input array with 1 if they are greater than a threshold value, the follow-up output should be less than or equal to the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR30) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;
    int threshold = 10;  // Example threshold value

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int i = 0; i < follow_vec.size(); ++i) {
        if (follow_vec[i] > threshold) {
            follow_vec[i] = 1;  // Replace with 1 if greater than the threshold
        }
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 31: Replacing all elements of the input array with their squares, the follow-up output should be greater than or equal to the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR31) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int i = 0; i < source_vec.size(); ++i) {
        follow_vec.push_back(source_vec[i] * source_vec[i]);  // Replace with the square of each element
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 32: Replacing all elements of the input array with their cubes, the follow-up output should be greater than or equal to the square of the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR32) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);
    int source_out_squared = source_out * source_out;

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int i = 0; i < source_vec.size(); ++i) {
        follow_vec.push_back(source_vec[i] * source_vec[i] * source_vec[i]);  // Replace with the cube of each element
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_GE(follow_out, source_out_squared);
}

/**
 * @brief Metamorphic Relation 33: Replacing all elements of the input array with their square roots, the follow-up output should be less than or equal to the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR33) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int i = 0; i < source_vec.size(); ++i) {
        follow_vec.push_back(sqrt(source_vec[i]));  // Replace with the square root of each element
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 34: Replacing all elements of the input array with their logarithms, the follow-up output should be less than or equal to the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR34) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int i = 0; i < source_vec.size(); ++i) {
        follow_vec.push_back(log(source_vec[i]));  // Replace with the logarithm of each element
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 35: Reversing the input array and then negating all elements, the follow-up output should be the same as the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR35) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    reverse(follow_vec.begin(), follow_vec.end());
    transform(follow_vec.begin(), follow_vec.end(), follow_vec.begin(), 
              [](int value) { return -value; });  // Reversing and negating all elements

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 36: Adding a constant value to each element of the input array, the follow-up output should be incremented by a factor corresponding to the constant value.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR36) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;
    int constant_value = 10;  // Example constant value

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int& value : follow_vec) {
        value += constant_value;  // Adding a constant value to each element
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out + constant_value * source_vec.size());
}

/**
 * @brief Metamorphic Relation 37: Dividing each element of the input array by a scaling factor, the follow-up output should be decreased by a factor corresponding to the scaling factor.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR37) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;
    int scaling_factor = 2;  // Example scaling factor

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int& value : follow_vec) {
        value /= scaling_factor;  // Dividing each element by a scaling factor
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out / scaling_factor);
}

/**
 * @brief Metamorphic Relation 38: Replacing all elements of the input array with their exponential values, the follow-up output should be the summation of the exponential values.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR38) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    vector<long long> exponential_elements;
    for (int value : follow_vec) {
        exponential_elements.push_back(exp(value)); // Calculating the exponential values
    }

    /* Get source and follow-up outputs */
    int source_out = multi_maxsum(source_vec, source_m);
    long long follow_up_out = 0;
    for (long long value : exponential_elements) {
        follow_up_out += value;  // Summing the exponential values
    }

    /* Verification */
    EXPECT_EQ(follow_up_out, source_out);
}

/**
 * @brief Metamorphic Relation 39: Multiplying the input array by a constant factor and then adding a constant value to each element, the follow-up output should be scaled by the constant and offset by the value correspondingly.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR39) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;
    int scaling_factor = 2;  // Example scaling factor
    int constant_offset = 5;  // Example constant offset

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int& value : follow_vec) {
        value = value * scaling_factor + constant_offset;  // Applying scaling and offset
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out * scaling_factor + constant_offset * source_vec.size());
}

/**
 * @brief Metamorphic Relation 40: Multiplying the squared elements of the input array by a constant factor, the follow-up output should be scaled by the factor squared.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR40) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;
    int scaling_factor = 3;  // Example scaling factor

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (int& value : follow_vec) {
        value = value * value * scaling_factor;  // Applying scaling to squared elements
    }

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_EQ(follow_out, source_out * scaling_factor * scaling_factor);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, MultiMAXSUMParamTest, testing::ValuesIn(gen_tcs_randomly()));
