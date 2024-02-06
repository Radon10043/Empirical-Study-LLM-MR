#include <algorithm>
#include <climits>
#include <cmath>
#include <gtest/gtest.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class GetRangeParamTest : public ::testing::TestWithParam<GetRangeInput> {};

/**
 * @brief Metamorphic relation 1: If the original vector is unchanged, the range start and end indices should remain the same. 
 */
TEST_P(GetRangeParamTest, MR1) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(source_out, get_range(vec, target));
}

/**
 * @brief Metamorphic relation 2: If the target number is larger than the largest number in the array, both start and end indices should be -1.
 */
TEST_P(GetRangeParamTest, MR2) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    int follow_target = *max_element(vec.begin(), vec.end()) + 1;

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, follow_target);

    /* Verification */
    vector<int> expect = {-1, -1};
    EXPECT_EQ(expect, follow_out);
}

/**
 * @brief Metamorphic relation 3: If two vectors are the same except for a permutation of elements, the output range indices should remain the same. 
 */
TEST_P(GetRangeParamTest, MR3) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    random_shuffle(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 4: If the input vector is reversed, the range indices should remain the same. 
 */
TEST_P(GetRangeParamTest, MR4) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 5: If all elements of the input vector are multiplied by a positive integer, the range indices should remain the same. 
 */
TEST_P(GetRangeParamTest, MR5) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int i : vec) {
        follow_vec.push_back(i * 2);
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 6: If the input vector is empty, the output range indices should both be -1. 
 */
TEST_P(GetRangeParamTest, MR6) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec;

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    vector<int> expect = {-1, -1};
    EXPECT_EQ(expect, follow_out);
}

/**
 * @brief Metamorphic relation 7: If the target value is increased by 1, the output range indices should either both be -1 or should have a difference of 1 between them.
 */
TEST_P(GetRangeParamTest, MR7) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    int follow_target = target + 1;

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, follow_target);

    /* Verification */
    if (follow_out[0] == -1 && follow_out[1] == -1) {
        vector<int> expect = {-1, -1};
        EXPECT_EQ(expect, source_out);
    } else {
        EXPECT_TRUE(follow_out[1] - follow_out[0] == 1 || follow_out[0] == source_out[1]);
    }
}

/**
 * @brief Metamorphic relation 8: If the input vector is modified such that the target value is no longer present, the output range indices should both be -1.
 */
TEST_P(GetRangeParamTest, MR8) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    for (int i = 0; i < follow_vec.size(); ++i) {
        if (follow_vec[i] == target) {
            follow_vec[i] = target + 1;
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    vector<int> expect = {-1, -1};
    EXPECT_EQ(expect, follow_out);
}

/**
 * @brief Metamorphic relation 9: If all elements of the vector are increased by a constant, the output range indices should remain the same. 
 */
TEST_P(GetRangeParamTest, MR9) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int i : vec) {
        follow_vec.push_back(i + 5);
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 10: If the input vector is modified such that the middle element is changed to the target value, the output range indices should reflect the single occurrence at the middle index.
 */
TEST_P(GetRangeParamTest, MR10) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    if (follow_vec.size() > 0) {
        follow_vec[follow_vec.size()/2] = target;
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    if (source_out[0] != -1 && source_out[1] != -1) {
        int n = follow_vec.size();
        vector<int> expect = {n / 2, n / 2};
        EXPECT_EQ(expect, follow_out);
    }
}

/**
 * @brief Metamorphic relation 11: If all elements of the input vector are multiplied by -1, the range indices should remain the same. 
 */
TEST_P(GetRangeParamTest, MR11) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int i : vec) {
        follow_vec.push_back(i * -1);
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 12: If the target value is set to the maximum value in the vector, the output range indices should remain the same as if it was set to the second maximum value in the vector.
 */
TEST_P(GetRangeParamTest, MR12) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;

    /* Get source output for maximum value */
    int max_value = *max_element(vec.begin(), vec.end());
    vector<int> source_out_max = get_range(vec, max_value);

    /* Get source output for second maximum value */
    vector<int> follow_vec = vec;
    follow_vec.erase(max_element(follow_vec.begin(), follow_vec.end()));
    int second_max_value = *max_element(follow_vec.begin(), follow_vec.end());
    vector<int> source_out_second_max = get_range(vec, second_max_value);

    /* Verification */
    EXPECT_EQ(source_out_max, source_out_second_max);
}

/**
 * @brief Metamorphic relation 13: If the vector contains duplicate values, the output range indices for any value should remain the same as the output range indices for its first occurrence in the vector.
 */
TEST_P(GetRangeParamTest, MR13) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;

    /* Find all the unique values in the vector */
    vector<int> unique_values;
    for (int value : vec) {
        if (find(unique_values.begin(), unique_values.end(), value) == unique_values.end()) {
            unique_values.push_back(value);
        }
    }

    /* Get source output for each unique value */
    for (int value : unique_values) {
        vector<int> source_out = get_range(vec, value);
        
        /* Find the first occurrence of the value in the vector */
        int first_occurrence = find(vec.begin(), vec.end(), value) - vec.begin();
        int last_occurrence = first_occurrence;
        while (last_occurrence < vec.size() && vec[last_occurrence] == value) {
            last_occurrence++;
        }

        /* Verification */
        vector<int> expect = {first_occurrence, last_occurrence - 1};
        EXPECT_EQ(expect, source_out);
    }
}

/**
 * @brief Metamorphic relation 14: If all elements of the input vector are decreased by a constant, the range indices should remain the same. 
 */
TEST_P(GetRangeParamTest, MR14) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int i : vec) {
        follow_vec.push_back(i - 3); // Decreasing all elements by 3
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 15: If the vector contains negative values, the output range indices for any positive value should remain the same as the output range indices for its absolute counterpart in the vector.
 */
TEST_P(GetRangeParamTest, MR15) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;

    /* Find all the positive values in the vector */
    vector<int> positive_values;
    for (int value : vec) {
        if (value > 0) {
            positive_values.push_back(value);
        }
    }

    /* Get source output for each positive value */
    for (int value : positive_values) {
        vector<int> source_out = get_range(vec, value);
        
        /* Find the absolute value counterpart in the vector */
        int absolute_value = -value;

        int first_occurrence = find(vec.begin(), vec.end(), absolute_value) - vec.begin();
        int last_occurrence = first_occurrence;
        while (last_occurrence < vec.size() && vec[last_occurrence] == absolute_value) {
            last_occurrence++;
        }

        /* Verification */
        EXPECT_EQ(source_out, get_range(vec, absolute_value));
    }
}

/**
 * @brief Metamorphic relation 16: If all elements of the input vector are modified such that the target value duplicates evenly across the vector, the output range indices should remain the same.
 */
TEST_P(GetRangeParamTest, MR16) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    for (int& value : follow_vec) {
        if (value == target) {
            value *= 2; // Duplicating the target value
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 17: If the input vector is modified to contain only a single occurrence of the target value, the output range indices should reflect that single occurrence.
 */
TEST_P(GetRangeParamTest, MR17) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int value : vec) {
        if (value == target) {
            follow_vec.push_back(value); // Only a single occurrence of the target value
            break;
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    if (!follow_vec.empty()) {
        vector<int> expect = {0, 0};
        EXPECT_EQ(expect, follow_out);
    } else {
        vector<int> expect = {-1, -1};
        EXPECT_EQ(expect, follow_out);
    }
}

/**
 * @brief Metamorphic relation 18: If all elements of the input vector are multiplied by a negative integer, the range indices should remain the same. 
 */
TEST_P(GetRangeParamTest, MR18) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int i : vec) {
        follow_vec.push_back(i * -2);
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 19: If the input vector consists of a single element, the output range indices for that element should be [0, 0].
 */
TEST_P(GetRangeParamTest, MR19) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;

    /* Get source output */
    vector<int> source_out = get_range(vec, vec[0]);

    /* Verification */
    if (vec.size() == 1) {
        vector<int> expect = {0, 0};
        EXPECT_EQ(expect, source_out);
    }
}

/**
 * @brief Metamorphic relation 20: If the input vector is a sorted sequence, the output range for a value should remain the same even after shuffling the vector.
 */
TEST_P(GetRangeParamTest, MR20) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Shuffle the vector */
    random_shuffle(vec.begin(), vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 21: If the input vector is reversed, the range indices for any value should remain the same.
 */
TEST_P(GetRangeParamTest, MR21) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Reverse the vector */
    reverse(vec.begin(), vec.end());

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 22: If the input vector has only one unique value, the output range indices should cover the entire range of the vector.
 */
TEST_P(GetRangeParamTest, MR22) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;

    /* Verify unique values */
    unordered_set<int> unique_values(vec.begin(), vec.end());

    if (unique_values.size() == 1) {
        int value = *unique_values.begin();

        /* Get source output */
        vector<int> source_out = get_range(vec, value);

        /* Verification */
        if (source_out[0] != -1 && source_out[1] != -1) {
            EXPECT_EQ(0, source_out[0]);
            EXPECT_EQ(static_cast<int>(vec.size()) - 1, source_out[1]);
        }
    }
}

/**
 * @brief Metamorphic relation 23: If the input vector contains all negative values, the output range indices for any negative value should remain the same as the output range indices for its absolute value counterpart in the vector.
 */
TEST_P(GetRangeParamTest, MR23) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;

    /* Verify negative values */
    vector<int> negative_values;
    for (int value : vec) {
        if (value < 0) {
            negative_values.push_back(value);
        }
    }

    /* Get source output for each negative value */
    for (int value : negative_values) {
        if (value != INT_MIN) {  // Avoid overflow for abs(INT_MIN)
            vector<int> source_out = get_range(vec, value);
        
            /* Find the absolute value counterpart in the vector */
            int absolute_value = abs(value);

            int first_occurrence = find(vec.begin(), vec.end(), absolute_value) - vec.begin();
            int last_occurrence = first_occurrence;
            while (last_occurrence < vec.size() && vec[last_occurrence] == absolute_value) {
                last_occurrence++;
            }

            /* Verification */
            EXPECT_EQ(source_out, get_range(vec, absolute_value));
        }
    }
}

/**
 * @brief Metamorphic relation 24: If the input vector contains all positive values, the output range indices for any positive value should remain the same as the output range indices for its negative counterpart in the vector.
 */
TEST_P(GetRangeParamTest, MR24) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;

    /* Verify positive values */
    vector<int> positive_values;
    for (int value : vec) {
        if (value > 0) {
            positive_values.push_back(value);
        }
    }

    /* Get source output for each positive value */
    for (int value : positive_values) {
        if (value != INT_MAX) {  // Avoid overflow for -INT_MAX
            vector<int> source_out = get_range(vec, value);
        
            /* Find the negative value counterpart in the vector */
            int negative_value = -value;

            int first_occurrence = find(vec.begin(), vec.end(), negative_value) - vec.begin();
            int last_occurrence = first_occurrence;
            while (last_occurrence < vec.size() && vec[last_occurrence] == negative_value) {
                last_occurrence++;
            }

            /* Verification */
            EXPECT_EQ(source_out, get_range(vec, negative_value));
        }
    }
}

/**
 * @brief Metamorphic relation 25: If the input vector is an arithmetic sequence, the output range indices for any value should remain the same after applying a constant difference to the sequence.
 */
TEST_P(GetRangeParamTest, MR25) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    /* Apply a constant difference to the sequence */
    for (int i = 0; i < vec.size(); ++i) {
        vec[i] += 5;
    }

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 26: If the input vector is empty, the output range indices for any value should be [-1, -1].
 */
TEST_P(GetRangeParamTest, MR26) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* When input vector is empty */
    if (vec.empty()) {
        vector<int> source_out = get_range(vec, target);
        vector<int> expect = {-1, -1};
        EXPECT_EQ(expect, source_out);
    }
}

/**
 * @brief Metamorphic relation 27: If the input vector contains duplicate values, the output range indices for any value should remain the same as the output range indices for its first occurrence in the vector when considering unique values.
 */
TEST_P(GetRangeParamTest, MR27) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;

    /* Get unique values from input vector */
    vector<int> unique_values;
    for (int value : vec) {
        if (find(unique_values.begin(), unique_values.end(), value) == unique_values.end()) {
            unique_values.push_back(value);
        }
    }

    /* Verify metamorphic relations for unique values */
    for (int value : unique_values) {
        vector<int> source_out = get_range(vec, value);
        int first_occurrence = find(vec.begin(), vec.end(), value) - vec.begin();
        int last_occurrence = first_occurrence;
        while (last_occurrence < vec.size() && vec[last_occurrence] == value) {
            last_occurrence++;
        }
        vector<int> expect = {first_occurrence, last_occurrence - 1};
        EXPECT_EQ(source_out, expect);
    }
}

/**
 * @brief Metamorphic relation 28: If the input vector contains a single value, the output range indices for that value should be [0, 0].
 */
TEST_P(GetRangeParamTest, MR28) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;

    /* When input vector contains a single value */
    if (vec.size() == 1) {
        int target = vec[0];
        vector<int> source_out = get_range(vec, target);
        vector<int> expect = {0, 0};
        EXPECT_EQ(expect, source_out);
    }
}

/**
 * @brief Metamorphic relation 29: If the input vector contains all even numbers, the output range indices for any even number should remain the same as the output range indices for its corresponding odd number (if present) in the vector.
 */
TEST_P(GetRangeParamTest, MR29) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;

    /* Verify even values */
    vector<int> even_values;
    for (int value : vec) {
        if (value % 2 == 0) {
            even_values.push_back(value);
        }
    }

    /* Get source output for each even value */
    for (int value : even_values) {
        if (find(vec.begin(), vec.end(), value - 1) != vec.end()) {  // Check if odd counterpart is present
            vector<int> source_out = get_range(vec, value);
            EXPECT_EQ(source_out, get_range(vec, value - 1));  // Output range indices should be the same for even and odd counterparts
        }
    }
}

/**
 * @brief Metamorphic relation 30: If the input vector contains all negative numbers, the output range indices for any negative number should remain the same as the output range indices for its positive counterpart (if present) in the vector.
 */
TEST_P(GetRangeParamTest, MR30) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;

    /* Verify negative values */
    vector<int> negative_values;
    for (int value : vec) {
        if (value < 0) {
            negative_values.push_back(value);
        }
    }

    /* Get source output for each negative value */
    for (int value : negative_values) {
        if (find(vec.begin(), vec.end(), -value) != vec.end()) {  // Check if positive counterpart is present
            vector<int> source_out = get_range(vec, value);
            EXPECT_EQ(source_out, get_range(vec, -value));  // Output range indices should be the same for negative and positive counterparts
        }
    }
}

/**
 * @brief Metamorphic relation 31: If the input vector contains all zeroes, the output range indices should be [0, 0] for value 0 and [-1, -1] for any other value.
 */
TEST_P(GetRangeParamTest, MR31) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;

    /* Fix: construct a vector whose elements are all zeros */
    vector<int> follow_vec = vec;
    for (auto& val : follow_vec) val = 0;

    /* Get source output for value 0 */
    vector<int> source_out_zero = get_range(follow_vec, 0);
    vector<int> tmp1 = {0, 0};
    EXPECT_EQ(tmp1, source_out_zero);

    /* Get source output for any value other than 0 */
    for (int value : vec) {
        if (value != 0) {
            vector<int> source_out = get_range(follow_vec, value);
            vector<int> tmp2 = {-1, -1};
            EXPECT_EQ(tmp2, source_out);
        }
    }
}

/**
 * @brief Metamorphic relation 32: If the input vector is all non-negative numbers, the output range indices for a value x should be the same as the output range indices for the value x-1 if it exists in the vector. If x-1 does not exist in the vector, the output range for x should be [i, i] where i is the index of x if x is found in the vector and [-1, -1] if x is not found.
 */
TEST_P(GetRangeParamTest, MR32) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;

    /* Find minimum value if the vector is non-empty */
    int min_value = vec.empty() ? 0 : *min_element(vec.begin(), vec.end());

    /* Verify the metamorphic relation for each value x >= min_value */
    for (int x = min_value; x <= *max_element(vec.begin(), vec.end()); ++x) {
        vector<int> source_out = get_range(vec, x);
        if (x - 1 >= min_value && find(vec.begin(), vec.end(), x-1) != vec.end()) {
            vector<int> expected_out = get_range(vec, x - 1);
            EXPECT_EQ(expected_out, source_out);
        } else {
            if (find(vec.begin(), vec.end(), x) != vec.end()) {
                int index_x = find(vec.begin(), vec.end(), x) - vec.begin();
                vector<int> expect = {index_x, index_x};
                EXPECT_EQ(expect, source_out);
            } else {
                vector<int> expect = {-1, -1};
                EXPECT_EQ(expect, source_out);
            }
        }
    }
}

/**
 * @brief Metamorphic relation 33: If the input vector is non-empty, the output range indices for any value x should be the same as the output range indices for the value abs(x) if it exists in the vector. If abs(x) does not exist in the vector, the output range for x should be the same as if x does not exist in the vector.
 */
TEST_P(GetRangeParamTest, MR33) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;

    /* Verify the metamorphic relation for each value x */
    for (int x : vec) {
        vector<int> source_out = get_range(vec, x);
        int abs_x = abs(x);

        if (find(vec.begin(), vec.end(), abs_x) != vec.end()) {
            vector<int> expected_out = get_range(vec, abs_x);
            EXPECT_EQ(expected_out, source_out);
        } 
        // No else condition required as the output will be the same if x is not found in the vector
    }
}

/**
 * @brief Metamorphic relation 34: If the input vector is non-empty and all elements are distinct, then modifying the input vector by removing one element should not affect the output range of any other element. 
 */
TEST_P(GetRangeParamTest, MR34) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;

    // Ensure the vector is non-empty and contains distinct elements
    if (vec.size() > 0 && unordered_set<int>(vec.begin(), vec.end()).size() == vec.size()) {
        vector<int> source_ranges;
        
        // Get the range for each element
        for (int value : vec) {
            vector<int> range = get_range(vec, value);
            source_ranges.push_back(range[0]);  // Save the starting index of the range
            source_ranges.push_back(range[1]);  // Save the ending index of the range
        }

        // Remove one element and get the new range for each element
        for (size_t i = 0; i < vec.size(); ++i) {
            vector<int> modified_vec = vec;
            modified_vec.erase(modified_vec.begin() + i);
            for (int value : modified_vec) {
                vector<int> new_range = get_range(modified_vec, value);
                EXPECT_EQ(source_ranges[2 * value], new_range[0]);  // Starting index should be unchanged
                EXPECT_EQ(source_ranges[2 * value + 1], new_range[1]);  // Ending index should be unchanged
            }
        }
    }
}

/**
 * @brief Metamorphic relation 35: If the input vector contains duplicate elements, and we remove all occurrences of any duplicate element, then the range for that element should be [-1, -1].
 */
TEST_P(GetRangeParamTest, MR35) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;

    // Ensure the vector contains duplicate elements
    unordered_set<int> element_set;
    int duplicate_element = 0;
    for (int value : vec) {
        if (element_set.find(value) != element_set.end()) {
            duplicate_element = value;
            break;
        }
        element_set.insert(value);
    }
    if (duplicate_element == 0) {
        return;
    }

    // Copy the vector and remove all occurrences of the duplicate element
    vector<int> modified_vec = vec;
    modified_vec.erase(remove(modified_vec.begin(), modified_vec.end(), duplicate_element), modified_vec.end());

    // Get the range for the duplicate element and verify it is [-1, -1]
    vector<int> range = get_range(modified_vec, duplicate_element);
    vector<int> expect = {-1, -1};
    EXPECT_EQ(expect, range);
}

/**
 * @brief Metamorphic relation 36: For any two values x and y such that x > y, if the range for x is [-1, -1], then the range for y should also be [-1, -1].
 */
TEST_P(GetRangeParamTest, MR36) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Fix */
    vector<int> source_out = get_range(vec, target);

    int follow_target = target - 1;
    vector<int> follow_out = get_range(vec, follow_target);

    if (source_out[0] == -1) {
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic relation 37: If the input vector has a single element k multiplied by a constant factor c, then the output range indices for k should also be multiplied by the same factor c.
 */
TEST_P(GetRangeParamTest, MR37) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;

    if(vec.size() !=1) {
        return;
    }

    int k = vec[0];
    vector<int> range = get_range(vec, k);
    vector<int> modified_vec = vec;
    int c = 2; // Constant factor

    vector<int> modifiedRange = get_range(modified_vec, k);
    vector<int> expect = {range[0]*c, range[1]*c};
    EXPECT_EQ(expect, modifiedRange);
}

/**
 * @brief Metamorphic relation 38: If the input vector contains all negative numbers, sorting the vector should not change the output range for any value.
 */
TEST_P(GetRangeParamTest, MR38) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;

    // Verify if all elements are negative
    bool allNegative = all_of(vec.begin(), vec.end(), [](int value) { return value < 0; });

    if (allNegative) {
        // Get the ranges for the original vector
        unordered_map<int, vector<int>> originalRanges;
        for (int value : vec) {
            originalRanges[value] = get_range(vec, value);
        }

        // Sort the vector
        sort(vec.begin(), vec.end());

        // Verify the ranges after sorting
        for (const auto& [value, range] : originalRanges) {
            EXPECT_EQ(range, get_range(vec, value));
        }
    }
}

/**
 * @brief Metamorphic relation 39: If the input vector contains all positive numbers, scaling the vector by a factor 'k' should scale the output range for any value 'x' by the same factor 'k'.
 */
TEST_P(GetRangeParamTest, MR39) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;

    // Verify if all elements are positive
    bool allPositive = all_of(vec.begin(), vec.end(), [](int value) { return value > 0; });

    if (allPositive) {
        // Scale factor
        int k = 2; // Let's consider the scale factor as 2

        // Get the ranges for the original vector
        unordered_map<int, vector<int>> originalRanges;
        for (int value : vec) {
            originalRanges[value] = get_range(vec, value);
        }

        // Scale the vector
        transform(vec.begin(), vec.end(), vec.begin(), [=](int value) { return value * k; });

        // Verify the scaled ranges
        for (const auto &[value, range] : originalRanges) {
            vector<int> scaledRange = get_range(vec, value * k);
            EXPECT_EQ(range[0] * k, scaledRange[0]);
            EXPECT_EQ(range[1] * k, scaledRange[1]);
        }
    }
}

/**
 * @brief Metamorphic relation 40: If the input vector contains all distinct non-negative numbers, adding a constant 'c' to each element should not change the output range for any value.
 */
TEST_P(GetRangeParamTest, MR40) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;

    if (all_of(vec.begin(), vec.end(), [](int value) { return value >= 0; })) {
        // Get the ranges for the original vector
        unordered_map<int, vector<int>> originalRanges;
        for (int value : vec) {
            originalRanges[value] = get_range(vec, value);
        }

        // Add a constant to each element
        int constant = 5;  // Adding a constant value of 5
        for (int &value : vec) {
            value += constant;
        }

        // Verify the ranges after adding the constant
        for (const auto &entry : originalRanges) {
          int value = entry.first;
          vector<int> originalRange = entry.second;
          vector<int> updatedRange = get_range(vec, value + constant);
          EXPECT_EQ(originalRange, updatedRange);
        }
    }
}


INSTANTIATE_TEST_CASE_P(TrueReturn, GetRangeParamTest, testing::ValuesIn(gen_tcs_randomly()));