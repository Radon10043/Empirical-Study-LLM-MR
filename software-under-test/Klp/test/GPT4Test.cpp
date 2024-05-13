#include <algorithm>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class KLPParamTest : public ::testing::TestWithParam<KLPInput> {};

#if 0
/**
 * @brief Metamorphic Relation 3: Duplication of a row (key) will not change the minimal set of keys required to open all locks.
 *
 */
TEST_P(KLPParamTest, MR3) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    follow_matrix.push_back(matrix[0]); // Duplicate the first row (key)

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 4: Reversing the order of columns (locks) should not affect the indices of selected keys in the output.
 *
 */
TEST_P(KLPParamTest, MR4) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix;
    for (auto &row : matrix) {
        reverse(row.begin(), row.end());
        follow_matrix.push_back(row);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification: The key indices should remain the same even with reversed columns. */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 5: Removing a row (key) that is not part of the minimal set should not affect the output.
 *
 */
TEST_P(KLPParamTest, MR5) {
#if 0
    /* Get source input and output */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;
    vector<int> source_out = KLP(matrix);

    if (!source_out.empty()) {
        /* Construct follow-up input: Remove a key that is not in the minimal set */
        vector<vector<int>> follow_matrix;
        for (int i = 0; i < matrix.size(); ++i) {
            if (find(source_out.begin(), source_out.end(), i) == source_out.end()) {
                follow_matrix = matrix;
                follow_matrix.erase(follow_matrix.begin() + i);
                break;
            }
        }

        /* Get follow-up output */
        vector<int> follow_out = KLP(follow_matrix);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
#endif
}

/**
 * @brief Metamorphic Relation 6: Permuting the rows (keys) does not affect the set of keys identified, though the order in the output might change.
 *
 */
TEST_P(KLPParamTest, MR6) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);
    std::sort(source_out.begin(), source_out.end());

    /* Construct follow-up input: Shuffle rows */
    vector<vector<int>> follow_matrix = matrix;
    std::random_shuffle(follow_matrix.begin(), follow_matrix.end());

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);
    std::sort(follow_out.begin(), follow_out.end());

    /* Verification: Check if the sorted indices of the keys are the same. */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 7: If a column (lock) is a duplicate of another column, then the output should not include more keys than before.
 *
 */
TEST_P(KLPParamTest, MR7) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input by duplicating a column */
    vector<vector<int>> follow_matrix = matrix;
    for (auto &row : follow_matrix) {
        row.push_back(row[0]); // Duplicate the first column (lock)
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification: The number of keys should not increase */
    EXPECT_GE(source_out.size(), follow_out.size());
}

/**
 * @brief Metamorphic Relation 8: Swapping two columns (locks) does not affect the indices of selected keys in the output.
 *
 */
TEST_P(KLPParamTest, MR8) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input: Swap two columns if there are at least 2 columns */
    if (matrix[0].size() >= 2) {
        vector<vector<int>> follow_matrix = matrix;
        for (auto &row : follow_matrix) {
            swap(row[0], row[1]); // Swap first two columns
        }

        /* Get follow-up output */
        vector<int> follow_out = KLP(follow_matrix);

        /* Verification: The set of keys should be the same. */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 9: Adding a key that can open the same locks as another key in the minimal set should not change the minimal set.
 *
 */
TEST_P(KLPParamTest, MR9) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input by adding a key that has identical capabilities as an already selected key in the minimal set, if one exists */
    if (!source_out.empty()) {
        vector<vector<int>> follow_matrix = matrix;
        follow_matrix.push_back(matrix[source_out[0]]); // Add a duplicate of the first key from the minimal set

        /* Get follow-up output */
        vector<int> follow_out = KLP(follow_matrix);

        /* Verification: The number of keys in the minimal set should not change */
        EXPECT_EQ(source_out.size(), follow_out.size());
    }
}

/**
 * @brief Metamorphic Relation 10: Zeroing a column that corresponds to a lock that no key can open doesn't change the output.
 *
 */
TEST_P(KLPParamTest, MR10) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    bool zero_column_exists = false;

    // Find a column (lock) that can't be opened by any key
    for (size_t j = 0; j < matrix[0].size(); ++j) {
        int sum = 0;
        for (size_t i = 0; i < matrix.size(); ++i) {
            sum += matrix[i][j];
        }
        if (sum == 0) {
            zero_column_exists = true;
            break;
        }
    }

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Verification: If such a column exists, the output should be the same
       after zeroing a column */
    if (zero_column_exists) {
        vector<vector<int>> follow_matrix(matrix.size(), vector<int>(matrix[0].size(), 0));
        /* Get follow-up output */
        vector<int> follow_out = KLP(follow_matrix);

        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 11: Increasing the dimensions of the matrix with additional rows and columns that introduce redundant keys and locks (which have
 * identical properties to existing ones) should not change the size of the resulting minimal set.
 *
 */
TEST_P(KLPParamTest, MR11) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);
    int original_minimal_set_size = source_out.size();

    /* Construct follow-up input by adding redundant rows and columns */
    vector<vector<int>> follow_matrix = matrix;

    // Add an extra row that is a copy of an existing one
    if (!matrix.empty()) {
        follow_matrix.push_back(matrix[0]);
    }

    // Add an extra column that is a copy of an existing one
    if (!matrix[0].empty()) {
        for (auto &row : follow_matrix) {
            row.push_back(row[0]);
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification: after adding redundant keys and locks, the minimal set size should not change */
    EXPECT_EQ(original_minimal_set_size, follow_out.size());
}

/**
 * @brief Metamorphic Relation 12: If two keys open exactly the same set of locks, removing one of them should not change the output.
 *
 */
TEST_P(KLPParamTest, MR12) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Find two keys that open the exact same set of locks */
    for (int i = 0; i < matrix.size() - 1; ++i) {
        for (int j = i + 1; j < matrix.size(); ++j) {
            if (matrix[i] == matrix[j]) {
                /* Construct follow-up input: remove one of the keys */
                vector<vector<int>> follow_matrix = matrix;
                follow_matrix.erase(follow_matrix.begin() + j);

                /* Get follow-up output */
                vector<int> follow_out = KLP(follow_matrix);

                /* Verification: Removing the key should not change the output */
                EXPECT_EQ(source_out, follow_out);
                return;
            }
        }
    }
}

/**
 * @brief Metamorphic Relation 13: Adding multiple identical keys (rows), that are already in the solution, should still provide the same set of keys in the
 * output, as per minimal requirement.
 *
 */
TEST_P(KLPParamTest, MR13) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Add multiple identical keys that are already in the solution */
    vector<int> indices_to_duplicate;
    for (int key_index : source_out) {
        indices_to_duplicate.push_back(key_index);
    }
    vector<vector<int>> follow_matrix = matrix;
    for (int key_index : indices_to_duplicate) {
        follow_matrix.push_back(matrix[key_index]);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verify that the set of keys returned does not change in size indicating no extra keys were selected */
    EXPECT_EQ(source_out.size(), follow_out.size());
}

/**
 * @brief Metamorphic Relation 14: If multiple keys are added that only open locks which are already opened by the existing selected keys, output should remain
 * same.
 *
 */
TEST_P(KLPParamTest, MR14) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct new keys that open a subset of locks that any key in the solution opens */
    vector<int> new_key(matrix[0].size(), 0);
    for (int key_index : source_out) {
        for (size_t i = 0; i < matrix[key_index].size(); ++i) {
            if (matrix[key_index][i] == 1) {
                new_key[i] = 1; // Lock i can be opened by new_key
            }
        }
    }

    vector<vector<int>> follow_matrix = matrix;
    follow_matrix.push_back(new_key); // Add new_key to the matrix

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verify that output remains the same as no new locks were introduced */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 15: Removing all keys that are not in the minimal set should not change the output set of keys.
 *
 */
TEST_P(KLPParamTest, MR15) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input by removing all keys that are not part of the minimal set */
    vector<vector<int>> follow_matrix;
    for (int key_index : source_out) {
        follow_matrix.push_back(matrix[key_index]);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification: After removing non-minimal set keys, output should not change */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 16: Scrambling the order of 1s within a row (representing a key) should not change whether it is selected or not.
 *
 */
TEST_P(KLPParamTest, MR16) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input by scrambling 1s within each row */
    vector<vector<int>> follow_matrix = matrix;
    for (auto &row : follow_matrix) {
        std::random_shuffle(row.begin(), row.end());
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification: Whether the rows are scrambled should not change the output indices. */
    EXPECT_EQ(source_out.size(), follow_out.size()); // The counts should be the same
    // Verify that each key that was selected in the source output is still selected after scrambling 1s
    for (int index : source_out) {
        EXPECT_NE(std::find(follow_out.begin(), follow_out.end(), index), follow_out.end());
    }
}

/**
 * @brief Metamorphic Relation 17: Doubling the matrix (adding an exact copy of the matrix below the original) should not change the output set of keys.
 *
 */
TEST_P(KLPParamTest, MR17) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input by doubling the matrix */
    vector<vector<int>> follow_matrix = matrix;
    follow_matrix.insert(follow_matrix.end(), matrix.begin(), matrix.end());

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification: Doubling the matrix should not add more keys to the selected set */
    EXPECT_EQ(source_out.size(), follow_out.size());
}

/**
 * @brief Metamorphic Relation 18: For each key in the optimal set, toggling any 0 to a 1 shouldn't change the output, as the key is already in the set.
 *
 */
TEST_P(KLPParamTest, MR18) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input: For each key in the output, toggle a 0 to 1 */
    vector<vector<int>> follow_matrix = matrix;
    for (int key : source_out) {
        for (size_t j = 0; j < follow_matrix[key].size(); ++j) {
            if (follow_matrix[key][j] == 0) {
                follow_matrix[key][j] = 1;
                break; // Toggle first 0 to 1 found
            }
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification: Optimal set should remain unchanged. */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 19: Removing all 0s from the rows corresponding to the keys in the output should not change the output.
 *
 */
TEST_P(KLPParamTest, MR19) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input: Remove all 0s from the selected keys' rows */
    vector<vector<int>> follow_matrix = matrix;
    for (int key : source_out) {
        std::fill(follow_matrix[key].begin(), follow_matrix[key].end(), 1);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification: Optimal set should remain unchanged */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 20: Inverting all elements in the matrix does not affect the selected keys but might change their order in the output vector.
 *
 */
TEST_P(KLPParamTest, MR20) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Invert all elements in each row */
    vector<vector<int>> follow_matrix(matrix.size(), vector<int>(matrix[0].size(), 0));
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            follow_matrix[i][j] = matrix[i][j] == 0 ? 1 : 0;
        }
    }

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);
    // Since the inversion could have created a completely different problem,
    // we can only guarantee the counts are the same.
    EXPECT_EQ(source_out.size(), follow_out.size());
}

/**
 * @brief Metamorphic Relation 21: Concatenating the matrix with its transpose should not change the number of keys in the minimal set.
 * This MR assumes there are as many keys as locks originally, and that the problem is symmetric.
 */
TEST_P(KLPParamTest, MR21) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input: concatenate the matrix with its transpose */
    vector<vector<int>> transpose_matrix(matrix[0].size(), vector<int>(matrix.size(), 0));
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            transpose_matrix[j][i] = matrix[i][j];
        }
    }

    vector<vector<int>> follow_matrix = matrix;
    follow_matrix.insert(follow_matrix.end(), transpose_matrix.begin(), transpose_matrix.end());

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification: The number of keys selected should not exceed the number previously determined, adjusted for the added keys */
    EXPECT_LE(follow_out.size(), source_out.size() * 2);
}

/**
 * @brief Metamorphic Relation 22: Adding a 'universal' key that can open all locks after the initial solution set should not change the set.
 * This MR assumes that the 'universal' key is intentionally added at a position that is beyond the original keys' indices.
 */
TEST_P(KLPParamTest, MR22) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input: Add a 'universal' key */
    vector<int> universal_key(matrix[0].size(), 1);
    vector<vector<int>> follow_matrix = matrix;
    follow_matrix.push_back(universal_key); // Add 'universal' key at the end

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification: The minimal set of keys should remain unchanged */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 23: Permuting the rows (keys) while simultaneously permuting corresponding columns (locks) should not change the output.
 */
TEST_P(KLPParamTest, MR23) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Ensure the matrix is square to perform this operation */
    if (matrix.size() != matrix[0].size()) {
        GTEST_SKIP() << "Matrix must be square for MR23";
    }

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Generate a random permutation of indices */
    std::vector<int> permutation(matrix.size());
    std::iota(permutation.begin(), permutation.end(), 0);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(permutation.begin(), permutation.end(), g);

    /* Construct follow-up input: Apply the permutation to both rows and corresponding columns */
    vector<vector<int>> follow_matrix(matrix.size(), vector<int>(matrix.size(), 0));
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix.size(); ++j) {
            follow_matrix[i][j] = matrix[permutation[i]][permutation[j]];
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification: The size of the minimal set should remain the same */
    EXPECT_EQ(source_out.size(), follow_out.size());
}

/**
 * @brief Metamorphic Relation 24: Replacing a key in the output set by another that can open all locks opened by the former (plus potentially more) should not
 * change the set size.
 */
TEST_P(KLPParamTest, MR24) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    for (const auto &key_index : source_out) {
        /* Construct a new key that opens all locks opened by the key at key_index */
        vector<int> new_key(matrix[key_index]);
        for (size_t j = 0; j < new_key.size(); ++j) {
            // Make sure this new key can open at least all the locks the original key could open
            new_key[j] = 1;
        }

        /* Construct follow-up input: Replace the key in the matrix */
        vector<vector<int>> follow_matrix = matrix;
        follow_matrix[key_index] = new_key;

        /* Get follow-up output */
        vector<int> follow_out = KLP(follow_matrix);

        /* Verification: Replacing a key with one tha taht can open more locks should not change the minimal set size */
        EXPECT_EQ(source_out.size(), follow_out.size());
    }
}

/**
 * @brief Metamorphic Relation 25: Scaling all elements of the matrix by a non-zero factor should not change the minimal set of keys.
 * Since the matrix is binary, scaling by a non-zero factor is equivalent to leaving it unchanged.
 */
TEST_P(KLPParamTest, MR25) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input by scaling matrix elements */
    int scale_factor = 2; // scaling by 2, but since the matrix is binary, it's equivalent to 1
    vector<vector<int>> follow_matrix = matrix;
    for (auto &row : follow_matrix) {
        for (auto &elem : row) {
            elem *= scale_factor;
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification: The output should remain unchanged */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 26: If the matrix is appended with its negation (0s become 1s, and vice versa) as additional rows, the minimal set of keys should
 * not be reduced in size.
 */
TEST_P(KLPParamTest, MR26) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input by appending negated rows */
    vector<vector<int>> follow_matrix = matrix;
    for (const auto &row : matrix) {
        vector<int> negated_row(row.size());
        std::transform(row.begin(), row.end(), negated_row.begin(), [](int val) { return val == 0 ? 1 : 0; });
        follow_matrix.push_back(negated_row);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification: The number of keys in the minimal set should not decrease */
    EXPECT_LE(source_out.size(), follow_out.size());
}

/**
 * @brief Metamorphic Relation 27: Removing a key that is not in the minimal set and then adding a new key that can't open any lock should not change the
 * output.
 */
TEST_P(KLPParamTest, MR27) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Find a key that is not in the minimal set */
    for (size_t i = 0; i < matrix.size(); ++i) {
        if (std::find(source_out.begin(), source_out.end(), i) == source_out.end()) {
            /* Construct follow-up input */
            vector<vector<int>> follow_matrix = matrix;
            follow_matrix.erase(follow_matrix.begin() + i); // Remove key i
            vector<int> new_key(matrix[0].size(), 0);       // New key that can't open any lock
            follow_matrix.push_back(new_key);

            /* Get follow-up output */
            vector<int> follow_out = KLP(follow_matrix);

            /* Verification: The minimal set should remain unchanged */
            EXPECT_EQ(source_out.size(), follow_out.size());
            break;
        }
    }
}

/**
 * @brief Metamorphic Relation 28: Adding a new lock that can only be opened by keys in the minimal set should not change the output.
 */
TEST_P(KLPParamTest, MR28) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input by adding a new lock that can only be opened by keys in the minimal set */
    for (auto &row : matrix) {
        row.push_back(std::find(source_out.begin(), source_out.end(), &row - &matrix[0]) != source_out.end() ? 1 : 0);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verification: The output should remain the same */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 29: Shuffling the order of 1s within each column (lock) should not change the minimal set of keys required to open all locks.
 *
 */
TEST_P(KLPParamTest, MR29) {
    /* Get source input and output */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;
    vector<int> source_out = KLP(matrix);

    // Prepare a shuffled version of each column in the matrix
    vector<vector<int>> follow_matrix = matrix;
    for (size_t j = 0; j < matrix[0].size(); ++j) {
        vector<int> column_values;
        for (auto &row : follow_matrix) {
            column_values.push_back(row[j]);
        }
        std::random_shuffle(column_values.begin(), column_values.end());

        for (size_t i = 0; i < matrix.size(); ++i) {
            follow_matrix[i][j] = column_values[i];
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification: The minimal set of keys should remain unchanged */
    EXPECT_EQ(source_out.size(), follow_out.size());
}

/**
 * @brief Metamorphic Relation 30: Incrementing the value of each lock that a non-selected key can open should not change the minimal set
 * when no key can open a lock more than once.
 *
 */
TEST_P(KLPParamTest, MR30) {
    /* Get source input and output */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;
    vector<int> source_out = KLP(matrix);

    vector<vector<int>> follow_matrix = matrix;
    for (int k = 0; k < matrix.size(); ++k) {
        if (std::find(source_out.begin(), source_out.end(), k) == source_out.end()) {
            // This key is not in the minimal set, increment the lock values it can open
            for (size_t j = 0; j < matrix[k].size(); ++j) {
                if (matrix[k][j] == 1)
                    follow_matrix[k][j]++;
            }
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification: The minimal set of keys should remain unchanged */
    EXPECT_EQ(source_out.size(), follow_out.size());
}

/**
 * @brief Metamorphic Relation 31: Transposing the entire matrix (making keys into locks and vice versa) should produce a minimal set with the same number of
 * elements. This assumes the problem has an equivalent structure when transposed.
 */
TEST_P(KLPParamTest, MR31) {
    /* Get source input and output */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;
    vector<int> source_out = KLP(matrix);

    vector<vector<int>> follow_matrix(matrix[0].size(), vector<int>(matrix.size(), 0));
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            follow_matrix[j][i] = matrix[i][j];
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification: The number of elements in the minimal set should be equal */
    EXPECT_EQ(source_out.size(), follow_out.size());
}

/**
 * @brief Metamorphic Relation 32: Interchanging locks that are opened by the same set of keys should not affect the output.
 *
 */
TEST_P(KLPParamTest, MR32) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    // Find two locks opened by the same set of keys
    bool locks_found = false;
    vector<int> lock_a, lock_b;
    for (size_t j1 = 0; j1 < matrix[0].size(); ++j1) {
        lock_a.clear();
        for (size_t i = 0; i < matrix.size(); ++i) {
            if (matrix[i][j1] == 1) {
                lock_a.push_back(i);
            }
        }
        for (size_t j2 = j1 + 1; j2 < matrix[0].size(); ++j2) {
            lock_b.clear();
            for (size_t i = 0; i < matrix.size(); ++i) {
                if (matrix[i][j2] == 1) {
                    lock_b.push_back(i);
                }
            }
            if (lock_a == lock_b) {
                // Found locks opened by the same keys
                locks_found = true;
                // Interchange locks j1 and j2
                for (auto &row : matrix) {
                    std::swap(row[j1], row[j2]);
                }
                break;
            }
        }
        if (locks_found)
            break;
    }

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Conditions and assumptions for this MR to be valid must hold */
    if (locks_found) {
        /* Get follow-up output */
        vector<int> follow_out = KLP(matrix);

        /* Verification: Interchanging locks should not affect the keys in the minimal set */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 33: Converting the optimization problem to a decision problem by asking if all locks can be opened with up to 'k' keys,
 * where 'k' is the number of keys in the minimal set, should return 'true'.
 */
TEST_P(KLPParamTest, MR33) {
    /* Get source input and output */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;
    vector<int> source_out = KLP(matrix);

    // Convert to a decision problem: Can all locks be opened with up to k keys?
    int k = source_out.size();
    bool can_open_all_locks = true; // Assume the KLP function provides a correct solution

    // Check if k keys can open all locks
    vector<int> opened_locks(matrix[0].size(), 0);
    for (int key : source_out) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            opened_locks[j] += matrix[key][j];
        }
    }

    for (int is_open : opened_locks) {
        if (is_open == 0) {
            can_open_all_locks = false; // Found a lock that cannot be opened
            break;
        }
    }

    /* Verification */
    EXPECT_TRUE(can_open_all_locks);
}

/**
 * @brief Metamorphic Relation 34: Removing a selected key and all locks it opens should reduce the minimal set by one.
 *
 * Note: This relation assumes that each key in the minimal set opens at least one lock that no other key can open.
 */
TEST_P(KLPParamTest, MR34) { // Fixed
    /* Get source input and output */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;
    vector<int> source_out = KLP(matrix);

    if (!source_out.empty()) {
        // Select a key to remove
        int keyToRemove = source_out.front();
        vector<vector<int>> follow_matrix = matrix;

        // Remove the selected key
        for (auto &val : follow_matrix[keyToRemove])
            val = -1;

        // Remove the corresponding locks
        for (int i = 0; i < matrix.size(); i++) {
            if (i == keyToRemove)
                continue;
            for (int j = 0; j < matrix[0].size(); j++)
                if (matrix[keyToRemove][j] == 1)
                    follow_matrix[i][j] = -1;
        }

        /* Get follow-up output */
        vector<int> follow_out = KLP(matrix);

        // The size of the output set should be reduced by 1
        EXPECT_EQ(source_out.size() - 1, follow_out.size());
    }
}

/**
 * @brief Metamorphic Relation 35: Inverting a non-selected key (changing its 0s to 1s and 1s to 0s) should not change the minimal set.
 *
 * Note: This relation assumes there is a non-selected key and that inverting it does not transform it into a universal key or a non-functional key.
 */
TEST_P(KLPParamTest, MR35) {
    /* Get source input and output */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;
    vector<int> source_out = KLP(matrix);

    for (size_t i = 0; i < matrix.size(); ++i) {
        if (std::find(source_out.begin(), source_out.end(), i) == source_out.end()) {
            // Invert a non-selected key
            std::transform(matrix[i].begin(), matrix[i].end(), matrix[i].begin(), [](int val) { return val == 0 ? 1 : 0; });

            /* Get follow-up output */
            vector<int> follow_out = KLP(matrix);

            /* Verification: The set of selected keys should remain unchanged. */
            EXPECT_EQ(source_out, follow_out);
            break;
        }
    }
}

/**
 * @brief Metamorphic Relation 36: Combining two non-selected keys into a new key with their combined capabilities should not change the minimal set.
 *
 * Note: This relation assumes there are at least two non-selected keys.
 */
TEST_P(KLPParamTest, MR36) {
    /* Get source input and output */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;
    vector<int> source_out = KLP(matrix);

    // Find two non-selected keys
    vector<int> non_selected_keys;
    for (size_t i = 0; i < matrix.size(); ++i) {
        if (std::find(source_out.begin(), source_out.end(), i) == source_out.end()) {
            non_selected_keys.push_back(i);
            if (non_selected_keys.size() == 2)
                break;
        }
    }

    if (non_selected_keys.size() == 2) {
        // Combine two non-selected keys
        vector<int> combined_key(matrix[0].size(), 0);
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            if (matrix[non_selected_keys[0]][j] == 1 || matrix[non_selected_keys[1]][j] == 1) {
                combined_key[j] = 1;
            }
        }
        // Add to the end of the matrix
        matrix.push_back(combined_key);

        /* Get follow-up output */
        vector<int> follow_out = KLP(matrix);

        /* Verification: The set of selected keys should remain unchanged. */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 37: Adding a column of zeros (i.e., a lock that cannot be opened by any key) should not change the minimal set of keys.
 *
 */
TEST_P(KLPParamTest, MR37) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Add a new lock that none of the keys can open (column of zeros) */
    for (auto &row : matrix) {
        row.push_back(0);
    }

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Verification: The minimal set of keys should remain unchanged */
    EXPECT_EQ(source_out, KLP(matrix));
}

/**
 * @brief Metamorphic Relation 38: Concatenating the matrix with a completely new matrix of non-functional keys (rows of zeros) should not change the minimal
 * set.
 *
 */
TEST_P(KLPParamTest, MR38) {
    /* Get source input and output */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;
    vector<int> source_out = KLP(matrix);

    vector<int> non_functional_key(matrix[0].size(), 0);
    vector<vector<int>> new_matrix(matrix.size(), non_functional_key);

    // Append the matrix with new_matrix
    matrix.insert(matrix.end(), new_matrix.begin(), new_matrix.end());

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verification: Adding non-functional keys should not change the set of selected keys. */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 39: Inverting all elements in the matrix, then reverting only the rows corresponding to the keys selected, should not change the
 * minimal set.
 *
 */
TEST_P(KLPParamTest, MR39) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Invert all elements in the matrix */
    vector<vector<int>> inverted_matrix(matrix.size(), vector<int>(matrix[0].size()));
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            inverted_matrix[i][j] = matrix[i][j] == 0 ? 1 : 0;
        }
    }

    /* Revert the rows corresponding to the selected keys */
    for (int key : source_out) {
        inverted_matrix[key] = matrix[key];
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(inverted_matrix);

    /* Verification: The set of selected keys should remain the same after inverting the matrix and reverting the selected keys */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 40: If one lock is already opened by all keys in the minimal set, adding a key that opens only that lock should not be part of
 * the new minimal set.
 *
 */
TEST_P(KLPParamTest, MR40) {    // Fixed
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    int m = matrix.size(), n = matrix[0].size();

    /* Find a lock opened by all keys in the minimal set */
    int all_open_lock = -1;
    for (int j = 0; j < n; j++) {
        int open_cnt = 0;
        for (auto& key : source_out) {
            open_cnt += matrix[key][j];
        }
        if (open_cnt != 0 && open_cnt == source_out.size()) {
            all_open_lock = j;
            break;
        }
    }

    if (all_open_lock == -1)
        GTEST_SKIP() << "No lock is opened by all keys in the minimal set";

    /* Construct follow-up input by adding a key that opens only the lock opened by all keys in the minimal set */
    vector<vector<int>> follow_matrix = matrix;
    vector<int> new_key(n, 0);
    new_key[all_open_lock] = 1;
    follow_matrix.push_back(new_key);

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    if (find(follow_out.begin(), follow_out.end(), m) != follow_out.end())
        write_tcs(input, "testcases.txt");

    /* Verification: The new minimal set should not include the new key */
    EXPECT_TRUE(find(follow_out.begin(), follow_out.end(), m) == follow_out.end());
}
#endif

/**
 * @brief Metamorphic Relation 41: Swapping two locks when each is exclusively opened by a different single key in the minimal set should not affect the minimal
 * set.
 *
 */
TEST_P(KLPParamTest, MR41) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Find two keys that exclusively open different locks */
    vector<size_t> exclusive_locks(matrix[0].size(), 0);
    for (size_t i = 0; i < matrix.size(); ++i) {
        int sum = std::accumulate(matrix[i].begin(), matrix[i].end(), 0);
        if (sum == 1) {
            size_t lock_index = std::find(matrix[i].begin(), matrix[i].end(), 1) - matrix[i].begin();
            exclusive_locks[lock_index]++;
        }
    }
    std::vector<size_t> exclusive_lock_indices;
    for (size_t i = 0; i < exclusive_locks.size(); ++i) {
        if (exclusive_locks[i] == 1) {
            exclusive_lock_indices.push_back(i);
        }
    }

    if (exclusive_lock_indices.size() >= 2) {
        // Swap two exclusive locks
        size_t lock1 = exclusive_lock_indices[0];
        size_t lock2 = exclusive_lock_indices[1];
        for (auto &row : matrix) {
            std::swap(row[lock1], row[lock2]);
        }

        /* Get follow-up output */
        vector<int> follow_out = KLP(matrix);

        /* Verification: The minimal set of keys should remain unchanged */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 42: Doubling each 1 in a key's row representing locks it can open should not change the minimal set.
 * This MR is based on the idea that the function looks at whether a lock can be opened, not how many times.
 */
TEST_P(KLPParamTest, MR42) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input by doubling the value for openings */
    vector<vector<int>> doubled_matrix = matrix;
    for (auto &row : doubled_matrix) {
        std::transform(row.begin(), row.end(), row.begin(), [](int val) { return val == 1 ? 2 : 0; });
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(doubled_matrix);

    /* Verification: The minimal set of keys should not change when doubling the values representing an opening. */
    EXPECT_EQ(source_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, KLPParamTest, testing::ValuesIn(gen_tcs_randomly()));