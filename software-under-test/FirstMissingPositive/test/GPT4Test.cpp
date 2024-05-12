#include <algorithm>
#include <gtest/gtest.h>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class FMPInputParamTest : public ::testing::TestWithParam<FMPInput> {};

/**
 * @brief Metamorphic Relation 3: Appending a negative number or zero to the array
 * should not affect the result.
 *
 */
TEST_P(FMPInputParamTest, MR3) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input by appending a negative number */
    vector<int> follow_vec = source_vec;
    follow_vec.push_back(-1); // Append a negative number

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 4: Removing any negative number or zero from the array
 * should not affect the result.
 *
 */
TEST_P(FMPInputParamTest, MR4) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input by removing the first non-positive integer, if any */
    vector<int> follow_vec;
    for (int num : source_vec) {
        if (num > 0) {
            follow_vec.push_back(num);
        }
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 5: Replacing a number in the array with a larger number
 * that is greater than the size of the array should not affect the result.
 *
 */
TEST_P(FMPInputParamTest, MR5) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input by replacing a positive number with a larger number, if any */
    vector<int> follow_vec = source_vec;
    for (size_t i = 0; i < follow_vec.size(); ++i) {
        if (follow_vec[i] > 0) {                   // Find a positive number
            follow_vec[i] = follow_vec.size() + 2; // Replace with a large number
            break;
        }
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 6: Duplicating the entire array but appending or prepending
 * additional positive numbers that do not interfere with the missing positive logic should
 * not affect the result.
 *
 */
TEST_P(FMPInputParamTest, MR6) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input by duplicating the array and appending additional positives */
    vector<int> follow_vec = source_vec;
    int max_elem = *max_element(source_vec.begin(), source_vec.end());
    follow_vec.insert(follow_vec.end(), source_vec.begin(), source_vec.end());
    follow_vec.push_back(max_elem + 1); // Append a positive number that's known to be missing

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 7: Inserting an additional positive number not present in the source array
 * that doesn't affect the smallest missing positive should not change the result.
 *
 */
TEST_P(FMPInputParamTest, MR7) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Find a number not present in the source array */
    int number_to_insert = 1;
    while (find(source_vec.begin(), source_vec.end(), number_to_insert) != source_vec.end()) {
        number_to_insert++;
    }
    // If the number to insert is the same as the missing positive, increment it again
    if (number_to_insert == first_missing_positive(source_vec)) {
        number_to_insert++;
    }

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.push_back(number_to_insert); // Insert number not present in the source array

    /* Sort array to maintain the same missing positive */
    sort(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 8: Reversing the array should not affect the result since the array is not
 * required to be sorted to find the missing positive number.
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
    reverse(follow_vec.begin(), follow_vec.end()); // Reverse the array

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 9: Doubling the values of all the positive integers in
 * the array should not change the smallest missing positive integer if it remains within the
 * bounds of the array size.
 *
 */
TEST_P(FMPInputParamTest, MR9) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Double values of all positive integers */
    vector<int> follow_vec;
    for (int num : source_vec) {
        if (num > 0 && num * 2 <= static_cast<int>(source_vec.size())) {
            follow_vec.push_back(num * 2);
        } else {
            follow_vec.push_back(num);
        }
    }

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 10: Adding a positive number larger than the current largest number in the
 * source array should not change the result if the source array already contains 1 to n,
 * because the missing number would then be n+1, and the addition of n+2 or greater does not change that fact.
 *
 */
TEST_P(FMPInputParamTest, MR10) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get maximum value from source array */
    int max_value = *max_element(source_vec.begin(), source_vec.end());
    int number_to_add = max_value + 1;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.push_back(number_to_add); // Add the new number

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 11: Removing all negative numbers and zeros should not affect the outcome
 * because they do not influence the determination of the smallest missing positive integer.
 *
 */
TEST_P(FMPInputParamTest, MR11) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input by excluding non-positive numbers */
    vector<int> follow_vec;
    copy_if(source_vec.begin(), source_vec.end(), back_inserter(follow_vec), [](int num) { return num > 0; });

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 12: If the array contains all elements from 1 to n consecutively,
 * appending another series of consecutive numbers starting from n+2 till 2n+1 should not affect the output
 * as the first missing positive integer would still be n+1.
 *
 */
TEST_P(FMPInputParamTest, MR12) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Check if 1 to n are all present */
    bool all_present = true;
    int n = source_vec.size();
    for (int i = 1; all_present && i <= n; ++i) {
        if (find(source_vec.begin(), source_vec.end(), i) == source_vec.end()) {
            all_present = false;
        }
    }

    if (all_present) {
        /* Get source output */
        int source_out = first_missing_positive(source_vec);

        /* Construct follow-up input */
        vector<int> follow_vec = source_vec;

        // Add another series of consecutive numbers, starting from n + 2 to 2n + 1
        for (int i = n + 2; i <= 2 * n + 1; ++i) {
            follow_vec.push_back(i);
        }

        /* Get follow-up output */
        int follow_out = first_missing_positive(follow_vec);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 13: Replacing all the occurrences of the smallest missing positive integer
 * with any other positive integer that is already present in the array should not affect the result.
 *
 */
TEST_P(FMPInputParamTest, MR13) { // Fixed
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;
    vector<int> follow_vec = source_vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Find a positive integer that is present in the array */
    int number_already_present = source_vec.front();

    /* Replace the smallest missing positive with a number already present */
    int smallest_missing = source_out;
    for (size_t i = 0; i < follow_vec.size(); ++i) {
        if (follow_vec[i] == smallest_missing) {
            follow_vec[i] = number_already_present;
        }
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 14: Incrementing every positive integer in the array by 1 (and leaving
 * non-positive integers unchanged) will result in the first missing positive integer also being
 * incremented by 1.
 *
 */
TEST_P(FMPInputParamTest, MR14) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input */
    vector<int> follow_vec;
    for (int num : source_vec) {
        if (num > 0) {
            follow_vec.push_back(num + 1); // Increment positive integers by 1
        } else {
            follow_vec.push_back(num); // Leave non-positive integers unchanged
        }
    }

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out + 1, follow_out);
}

/**
 * @brief Metamorphic Relation 15: Adding the smallest missing positive integer to the array will change
 * the result to the next smallest missing positive integer, which is the original result incremented by 1.
 *
 */
TEST_P(FMPInputParamTest, MR15) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input by adding the smallest missing positive integer */
    vector<int> follow_vec = source_vec;
    follow_vec.push_back(source_out); // Add the missing positive number

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out + 1, follow_out);
}

/**
 * @brief Metamorphic Relation 16: Removing the largest number from a duplicated array should
 * not change the result unless the number to be removed is the smallest missing positive.
 *
 */
TEST_P(FMPInputParamTest, MR16) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;
    vector<int> follow_vec = source_vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Double the array by repeating the contents */
    follow_vec.insert(follow_vec.end(), source_vec.begin(), source_vec.end());

    /* Find the maximum value in the follow_vec */
    int max_value = *max_element(follow_vec.begin(), follow_vec.end());

    /* Remove the largest number from the duplicated array if it's not the smallest missing positive */
    if (max_value != source_out) {
        follow_vec.erase(remove(follow_vec.begin(), follow_vec.end(), max_value), follow_vec.end());
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    if (max_value != source_out) {
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 17: Replacing all occurrences of any single positive integer in
 * the array with its negative counterpart (or zero) should not affect the result, unless the replaced
 * number is the first missing positive integer.
 *
 */
TEST_P(FMPInputParamTest, MR17) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input by replacing a positive number with its negative (if not the missing positive) */
    vector<int> follow_vec = source_vec;
    for (size_t i = 0; i < follow_vec.size(); ++i) {
        if (follow_vec[i] > 0 && follow_vec[i] != source_out) {
            follow_vec[i] = -follow_vec[i];
            break; // Replace only one occurrence
        }
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 18: Removing a positive integer larger than the first missing positive
 * will not change the result.
 *
 */
TEST_P(FMPInputParamTest, MR18) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Identify the first missing positive integer */
    int missing = first_missing_positive(source_vec);

    /* Remove a positive integer larger than the missing number, if any */
    vector<int> follow_vec;
    for (int num : source_vec) {
        if (!(num > missing)) {
            follow_vec.push_back(num);
        }
    }

    /* If the follow-up vector is the same as source, the test case is not applicable */
    if (follow_vec.size() == source_vec.size()) {
        return; // Test case not applicable
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(missing, follow_out);
}

/**
 * @brief Metamorphic Relation 19: Permuting an array such that the relative order of non-positive
 * integers and positive integers greater than the array size remains the same should not change the result.
 *
 */
TEST_P(FMPInputParamTest, MR19) {   // Fixed
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Get a permutation of positive integers up to the array size */
    vector<int> permuted_vec;
    for (auto& num : source_vec) {
        if (num > 0 && num <= static_cast<int>(source_vec.size())) {
            permuted_vec.push_back(num);
        }
    }
    shuffle(permuted_vec.begin(), permuted_vec.end(), default_random_engine());

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    int index = 0;
    for (auto& num : follow_vec) {
        if (num > 0 && num <= static_cast<int>(source_vec.size())) {
            num = permuted_vec[index++];
        }
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 20: If all positive numbers are greater than the size of the array,
 * the result should always be 1, regardless of the order or values of those numbers.
 *
 */
TEST_P(FMPInputParamTest, MR20) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Find if all positive numbers are greater than the array size */
    bool all_greater = all_of(source_vec.begin(), source_vec.end(), [&source_vec](int num) { return num <= 0 || num > static_cast<int>(source_vec.size()); });

    if (all_greater) {
        int expected = 1; // The expected smallest missing positive is always 1 in this case

        /* Construct a follow-up input with shuffled elements of source_vec */
        vector<int> follow_vec = source_vec;
        shuffle(follow_vec.begin(), follow_vec.end(), default_random_engine());

        /* Get follow-up output */
        int follow_out = first_missing_positive(follow_vec);

        /* Verification */
        EXPECT_EQ(expected, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 21: Increasing all positive elements by the same integer offset (which is greater than 0)
 * should result in the first missing positive integer also being incremented by the same offset.
 *
 */
TEST_P(FMPInputParamTest, MR21) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Choose an offset that is a positive integer greater than 0 */
    int offset = 2; // Example offset

    /* Construct follow-up input by adding the offset to each positive element */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        if (num > 0) {
            num += offset;
        }
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out + offset, follow_out);
}

/**
 * @brief Metamorphic Relation 22: Subtracting a constant integer (less than the first missing positive integer
 * but greater than 0) from each positive integer in the array should result in the first missing positive integer
 * also being decremented by the same constant.
 *
 */
TEST_P(FMPInputParamTest, MR22) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Choose a constant to subtract, ensuring it is less than source_out and greater than 0 */
    int constant_to_subtract = min(1, source_out - 1); // Example: Use 1 if possible

    /* Construct follow-up input by subtracting the constant from each positive integer */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        if (num > 0) {
            num -= constant_to_subtract;
        }
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out - constant_to_subtract, follow_out);
}

/**
 * @brief Metamorphic Relation 23: Concatenating the array with itself should result in the same missing positive integer.
 *
 */
TEST_P(FMPInputParamTest, MR23) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input by duplicating the source array */
    vector<int> follow_vec(source_vec);
    follow_vec.insert(follow_vec.end(), source_vec.begin(), source_vec.end());

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 24: Multiplying all the elements by -1 should not affect the result, as
 * the sign does not impact the algorithm's search for the smallest missing positive integer.
 *
 */
TEST_P(FMPInputParamTest, MR24) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input by negating each element */
    vector<int> follow_vec;
    transform(source_vec.begin(), source_vec.end(), back_inserter(follow_vec), [](int num) { return num * -1; });

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 25: If the input array is already sorted in ascending order, reversing the array
 * should not change the result since the order does not affect the identification of missing positive numbers.
 *
 */
TEST_P(FMPInputParamTest, MR25) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Check if the array is sorted */
    if (is_sorted(source_vec.begin(), source_vec.end())) {
        /* Get source output */
        int source_out = first_missing_positive(source_vec);

        /* Construct follow-up input by reversing the sorted array */
        vector<int> follow_vec = source_vec;
        reverse(follow_vec.begin(), follow_vec.end());

        /* Get follow-up output */
        int follow_out = first_missing_positive(follow_vec);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 26: Doubling the size of the input array by appending another copy should not
 * change the result, given that the first missing positive integer would exist in the first half of the array.
 *
 */
TEST_P(FMPInputParamTest, MR26) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input by appending a copy of the source array */
    vector<int> follow_vec = source_vec;
    follow_vec.insert(follow_vec.end(), source_vec.begin(), source_vec.end());

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 27: If the first missing positive integer is k, appending k-1 to the array
 * should change the smallest missing positive to k or k+1, adding to the verifiability of the algorithm.
 *
 */
TEST_P(FMPInputParamTest, MR27) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input by appending k-1 to the array */
    vector<int> follow_vec = source_vec;
    follow_vec.push_back(source_out - 1);

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    if (source_out == 1) {
        EXPECT_EQ(2, follow_out);
    } else {
        EXPECT_TRUE(follow_out == source_out || follow_out == source_out + 1);
    }
}

/**
 * @brief Metamorphic Relation 28: Inverting the sign of all the non-positive integers in the array should not
 * change the result, as they don't contribute to finding the smallest missing positive integer.
 *
 */
TEST_P(FMPInputParamTest, MR28) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input by inverting the sign of non-positive integers */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        if (num <= 0) {
            num = -num;
        }
    }

    /* Get source and follow-up outputs */
    int source_out = first_missing_positive(source_vec);
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 29: Adding a large number of zeros to the array should not change the result,
 * assuming that only positive integers define the first missing number and not the zeros.
 *
 */
TEST_P(FMPInputParamTest, MR29) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input by appending zeros */
    vector<int> follow_vec = source_vec;
    follow_vec.insert(follow_vec.end(), 100, 0); // Appending 100 zeros

    /* Get source and follow-up outputs */
    int source_out = first_missing_positive(source_vec);
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 30: Removing the smallest positive integer from the array, if present,
 * should result in that number being the missing positive integer returned by the function.
 *
 */
TEST_P(FMPInputParamTest, MR30) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Find the smallest positive integer in the array, if any */
    int smallest_positive = *min_element(source_vec.begin(), source_vec.end(), [](int a, int b) {
        if (a <= 0)
            return false;
        if (b <= 0)
            return true;
        return a < b;
    });

    /* Check if a positive integer was found */
    bool positive_found = smallest_positive > 0;

    if (positive_found) {
        /* Construct follow-up input by removing one instance of the smallest positive integer */
        vector<int> follow_vec;
        bool removed = false;
        for (int num : source_vec) {
            if (!removed && num == smallest_positive) {
                removed = true; // Remove one instance of smallest_positive
                continue;
            }
            follow_vec.push_back(num);
        }

        /* Get follow-up output */
        int follow_out = first_missing_positive(follow_vec);

        /* Verification */
        EXPECT_EQ(smallest_positive, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 31: Scaling all positive integers in the array by a positive factor greater than one
 * should not change the first missing positive, as long as the scaled version of each integer does not exceed the array length.
 *
 */
TEST_P(FMPInputParamTest, MR31) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Scaling factor; must be a positive integer greater than one */
    int scale_factor = 2;

    /* Construct follow-up input by scaling positive integers */
    vector<int> follow_vec = source_vec;
    for (int &num : follow_vec) {
        if (num > 0 && (num * scale_factor) <= static_cast<int>(follow_vec.size())) {
            num *= scale_factor;
        }
    }

    /* Get source and follow-up outputs */
    int source_out = first_missing_positive(source_vec);
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 32: Removing duplicates from the input array should not change the result,
 * since the first missing positive integer is not dependent on the presence of duplicate values.
 *
 */
TEST_P(FMPInputParamTest, MR32) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input by removing duplicates */
    vector<int> follow_vec = source_vec;
    sort(follow_vec.begin(), follow_vec.end());
    auto last = unique(follow_vec.begin(), follow_vec.end());
    follow_vec.erase(last, follow_vec.end());

    /* Get source and follow-up outputs */
    int source_out = first_missing_positive(source_vec);
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 33: If the array consists only of a single positive integer, adding another
 * instance of that integer should not change the first missing positive, which should be 1 or 2.
 *
 */
TEST_P(FMPInputParamTest, MR33) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Condition: the array must consist of a single positive integer */
    if (source_vec.size() == 1 && source_vec[0] > 0) {
        /* Get source output */
        int source_out = first_missing_positive(source_vec);

        /* Construct follow-up input by adding another instance of the integer */
        vector<int> follow_vec = source_vec;
        follow_vec.push_back(source_vec[0]);

        /* Get follow-up output */
        int follow_out = first_missing_positive(follow_vec);

        /* Verification */
        EXPECT_EQ(follow_out, source_out);
    }
}

/**
 * @brief Metamorphic Relation 34: For any input array that contains all integers from 1 to m without any gaps or
 * duplicates, appending another series of integers from m+1 to m+n should not change the smallest missing positive
 * integer, which is expected to be m+n+1
 *
 */
TEST_P(FMPInputParamTest, MR34) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Identify the range of integers 1 to m */
    int m = *max_element(source_vec.begin(), source_vec.end());
    bool all_present = true;
    for (int i = 1; i <= m && all_present; ++i) {
        if (find(source_vec.begin(), source_vec.end(), i) == source_vec.end()) {
            all_present = false;
        }
    }

    if (all_present) {
        /* Construct follow-up input by appending integers m+1 to m+n */
        vector<int> follow_vec = source_vec;
        for (int i = m + 1; i <= m + m; ++i) {
            follow_vec.push_back(i);
        }

        /* Expected smallest missing positive integer */
        int expected_smallest_missing = m + m + 1;

        /* Get follow-up output */
        int follow_out = first_missing_positive(follow_vec);

        /* Verification */
        EXPECT_EQ(expected_smallest_missing, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 35: For any input array, concatenating a sequence of negative integers should not
 * change the first missing positive integer.
 *
 */
TEST_P(FMPInputParamTest, MR35) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input by concatenating negative integers */
    vector<int> negative_sequence = {-1, -2, -3};
    vector<int> follow_vec = source_vec;
    follow_vec.insert(follow_vec.end(), negative_sequence.begin(), negative_sequence.end());

    /* Get source and follow-up outputs */
    int source_out = first_missing_positive(source_vec);
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 36: For an array containing the sequence of integers 1 to n without any gaps,
 * inserting a new integer greater than n at any position should not affect the result.
 *
 */
TEST_P(FMPInputParamTest, MR36) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Determine if array contains a full sequence from 1 to n */
    bool is_full_sequence = true;
    int n = source_vec.size();
    for (int i = 1; i <= n && is_full_sequence; ++i) {
        if (find(source_vec.begin(), source_vec.end(), i) == source_vec.end()) {
            is_full_sequence = false;
        }
    }

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    if (is_full_sequence) {
        /* Construct follow-up input by inserting an integer greater than n */
        vector<int> follow_vec = source_vec;
        follow_vec.push_back(n + 2); // Could be any number greater than n

        /* Get follow-up output */
        int follow_out = first_missing_positive(follow_vec);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 37: Removing any single non-positive integer from the array should not change
 * the result as non-positive integers do not affect the computation of the smallest missing positive integer.
 *
 */
TEST_P(FMPInputParamTest, MR37) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input by removing the first non-positive integer if exists */
    auto it = find_if(source_vec.begin(), source_vec.end(), [](int x) { return x <= 0; });
    if (it != source_vec.end()) {
        source_vec.erase(it);
    }

    /* Get source and follow-up outputs */
    int source_out = first_missing_positive(input.vec);
    int follow_out = first_missing_positive(source_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 38: If the array includes all positive numbers from 1 up to `array.size()` (n),
 * removing any number from this sequence and appending any number greater than n should cause the result to be
 * the removed number.
 *
 */
TEST_P(FMPInputParamTest, MR38) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Determine if the array contains the full sequence */
    bool has_full_sequence = true;
    for (int i = 1; i <= static_cast<int>(source_vec.size()) && has_full_sequence; ++i) {
        if (find(source_vec.begin(), source_vec.end(), i) == source_vec.end()) {
            has_full_sequence = false;
        }
    }

    if (has_full_sequence && source_vec.size() > 0) {
        /* Remove one number from the sequence */
        int removed_number = source_vec.size() / 2; // Remove the middle number for simplicity
        source_vec.erase(remove(source_vec.begin(), source_vec.end(), removed_number), source_vec.end());

        /* Append a number greater than the size of the array */
        source_vec.push_back(source_vec.size() + 2); // Can be any number larger than the new array size

        /* Get follow-up output */
        int follow_out = first_missing_positive(source_vec);

        /* Verification */
        EXPECT_EQ(removed_number, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 39: Appending the sequence of integers from the array size (n) + 2 and onward
 * should not change the result as long as the sequence does not fill the gap of the first missing positive.
 *
 */
TEST_P(FMPInputParamTest, MR39) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input by appending integers starting from n+2 */
    int n = source_vec.size();
    vector<int> follow_vec = source_vec;
    for (int i = n + 2; i <= n + 10; ++i) {
        follow_vec.push_back(i);
    }

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 40: Interspersing the elements of the array with zeros should not change
 * the result, as zeros do not contribute to the determination of the first missing positive integer.
 *
 */
TEST_P(FMPInputParamTest, MR40) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Construct follow-up input by interspersing zeros between original elements */
    vector<int> follow_vec;
    for (int num : source_vec) {
        follow_vec.push_back(num);
        follow_vec.push_back(0); // Intersperse zero
    }

    /* Get source and follow-up outputs */
    int source_out = first_missing_positive(source_vec);
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 41: Sorting a vector that contains the full sequence 1 to n in any order should result
 * in the first missing positive being n+1.
 *
 */
TEST_P(FMPInputParamTest, MR41) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Check if array contains a full sequence from 1 to n */
    sort(source_vec.begin(), source_vec.end());
    vector<int>::iterator it = unique(source_vec.begin(), source_vec.end());
    source_vec.resize(distance(source_vec.begin(), it));
    bool is_full_sequence = true;
    int n = source_vec.size();
    for (int i = 1; i <= n; ++i) {
        if (source_vec[i - 1] != i) {
            is_full_sequence = false;
            break;
        }
    }

    if (is_full_sequence) {
        /* The expected result should be n+1 */
        int expected_result = n + 1;

        /* Get follow-up output */
        int follow_out = first_missing_positive(source_vec);

        /* Verification */
        EXPECT_EQ(expected_result, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 42: For any input array, interchanging the positions of any two positive integers
 * should not affect the outcome of the first missing positive.
 *
 */
TEST_P(FMPInputParamTest, MR42) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Find two positive elements to swap */
    auto first = find_if(source_vec.begin(), source_vec.end(), [](int x) { return x > 0; });
    auto second = find_if(first + 1, source_vec.end(), [](int x) { return x > 0; });

    /* Conduct swap if two positives are found */
    if (first != source_vec.end() && second != source_vec.end()) {
        iter_swap(first, second);
    }

    /* Get source and follow-up outputs */
    int source_out = first_missing_positive(input.vec);
    int follow_out = first_missing_positive(source_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, FMPInputParamTest, testing::ValuesIn(gen_tcs_randomly()));