#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class KLPParamTest : public ::testing::TestWithParam<KLPInput> {};

// Metamorphic Relation 3:
// Permuting the rows of the matrix, the output remains unchanged.
TEST_P(KLPParamTest, MR3) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Permute the rows of the matrix */
    std::random_shuffle(matrix.begin(), matrix.end());

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 4:
// Adding a row to the matrix with the same values as an existing row, the output remains unchanged.
TEST_P(KLPParamTest, MR4) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Add a row with the same values as an existing row */
    vector<int> new_row = matrix[0]; // Assume the first row is replicated
    matrix.push_back(new_row);

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 5:
// Adding a column to the matrix with the same values as an existing column, the output remains unchanged.
TEST_P(KLPParamTest, MR5) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Add a column with the same values as an existing column */
    vector<int> new_column;
    for (const auto &row : matrix) {
        new_column.push_back(row[0]); // Assume the first column is replicated
    }
    for (size_t i = 0; i < matrix.size(); i++) {
        matrix[i].push_back(new_column[i]);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 6:
// Multiplying all elements in a row by a nonzero scalar, the output remains unchanged.
TEST_P(KLPParamTest, MR6) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Multiply all elements in a row by a nonzero scalar */
    int row_index = 0; // Assuming the first row is selected
    int scalar = 2;    // Example scalar value
    for (auto &element : matrix[row_index]) {
        element *= scalar;
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 7:
// Adding a new lock that can be opened by an existing key, the output remains unchanged.
TEST_P(KLPParamTest, MR7) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Add a new lock that can be opened by an existing key */
    for (auto &row : matrix) {
        row.push_back(1); // Assume the new lock can be opened by an existing key
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 8:
// If the matrix has duplicate rows, the output remains unchanged.
TEST_P(KLPParamTest, MR8) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Add duplicate rows to the matrix */
    matrix.push_back(matrix[0]); // Add a duplicate of the first row

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 9:
// If the matrix has duplicate columns, the output remains unchanged.
TEST_P(KLPParamTest, MR9) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Add duplicate columns to the matrix */
    for (size_t i = 0; i < matrix.size(); i++) {
        matrix[i].push_back(matrix[i][0]); // Add a duplicate of the first column to each row
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 10:
// If all the keys have the same set of locks that they can open, the order of the keys in the output is reversed and the output will also be reversed.
TEST_P(KLPParamTest, MR10) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Reverse the order of keys and the matrix itself */
    reverse(matrix.begin(), matrix.end());
    for (auto &row : matrix) {
        reverse(row.begin(), row.end());
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Reverse the output */
    reverse(follow_out.begin(), follow_out.end());

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 11:
// If the matrix contains all zeros, the output is an empty array.
TEST_P(KLPParamTest, MR11) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Set all elements of the matrix to zero */
    for (auto &row : matrix) {
        fill(row.begin(), row.end(), 0);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Expected output is an empty array */
    vector<int> expected_empty_out;

    /* Verification */
    EXPECT_EQ(expected_empty_out, follow_out);
}

// Metamorphic Relation 12:
// If a key can open all locks, then removing that key from the matrix will not change the output.
TEST_P(KLPParamTest, MR12) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    // Find a key that can open all locks
    int keyIndex = -1;
    for (size_t i = 0; i < matrix.size(); i++) {
        bool canOpenAllLocks = true;
        for (size_t j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == 0) {
                canOpenAllLocks = false;
                break;
            }
        }
        if (canOpenAllLocks) {
            keyIndex = i;
            break;
        }
    }

    if (keyIndex >= 0) {
        // Remove the key from the matrix
        matrix.erase(matrix.begin() + keyIndex);

        /* Get follow-up output */
        vector<int> follow_out = KLP(matrix);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    } else {
        // If no such key exists, the test is skipped
        GTEST_SKIP();
    }
}

// Metamorphic Relation 13:
// Adding a row that is a linear combination of existing rows, the output remains unchanged.
TEST_P(KLPParamTest, MR13) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    // Create a new row as a linear combination of existing rows
    vector<int> new_row(matrix[0].size(), 0);
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            new_row[j] += matrix[i][j];
        }
    }

    /* Add the new row to the matrix */
    matrix.push_back(new_row);

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 14:
// If all the locks can be opened by a single key, then permuting the order of locks will result in a reordering of the output.
TEST_P(KLPParamTest, MR14) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    // Find a key that can open all locks
    int keyIndex = -1;
    for (size_t i = 0; i < matrix.size(); i++) {
        bool canOpenAllLocks = true;
        for (size_t j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == 0) {
                canOpenAllLocks = false;
                break;
            }
        }
        if (canOpenAllLocks) {
            keyIndex = i;
            break;
        }
    }

    if (keyIndex >= 0) {
        /* Get source output */
        vector<int> source_out = KLP(matrix);

        /* Permute the order of locks */
        std::random_shuffle(matrix[keyIndex].begin(), matrix[keyIndex].end());

        /* Get follow-up output */
        vector<int> follow_out = KLP(matrix);

        /* Verification */
        EXPECT_NE(source_out, follow_out);
    } else {
        // If no such key exists, the test is skipped
        GTEST_SKIP();
    }
}

// Metamorphic Relation 15:
// Doubling the number of keys (adding a duplicate set of keys), the output remains unchanged.
TEST_P(KLPParamTest, MR15) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Double the number of keys */
    size_t originalSize = matrix.size();
    for (size_t i = 0; i < originalSize; i++) {
        matrix.push_back(matrix[i]); // Duplicate each key
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 16:
// If multiple keys can open the same lock, removing one of these keys while keeping others unchanged will not change the output.
TEST_P(KLPParamTest, MR16) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    // Find a lock that can be opened by multiple keys
    int lockIndex = -1;
    for (size_t j = 0; j < matrix[0].size(); j++) {
        int sum = 0;
        for (size_t i = 0; i < matrix.size(); i++) {
            sum += matrix[i][j];
        }
        if (sum > 1) {
            lockIndex = j;
            break;
        }
    }

    if (lockIndex >= 0) {
        /* Get source output */
        vector<int> source_out = KLP(matrix);

        // Remove one of the keys which can open the lock
        size_t keyToRemove = 0;
        for (size_t i = 0; i < matrix.size(); i++) {
            if (matrix[i][lockIndex] == 1) {
                keyToRemove = i;
                break;
            }
        }
        matrix.erase(matrix.begin() + keyToRemove);

        /* Get follow-up output */
        vector<int> follow_out = KLP(matrix);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    } else {
        // If no such lock exists, the test is skipped
        GTEST_SKIP();
    }
}

// Metamorphic Relation 17:
// If a key can open all locks, removing that key from the matrix will result in at least one lock that cannot be opened.
TEST_P(KLPParamTest, MR17) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    // Find a key that can open all locks
    int keyIndex = -1;
    for (size_t i = 0; i < matrix.size(); i++) {
        bool canOpenAllLocks = true;
        for (size_t j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == 0) {
                canOpenAllLocks = false;
                break;
            }
        }
        if (canOpenAllLocks) {
            keyIndex = i;
            break;
        }
    }

    if (keyIndex >= 0) {
        // Remove the key from the matrix
        matrix.erase(matrix.begin() + keyIndex);

        /* Get follow-up output */
        vector<int> follow_out = KLP(matrix);

        // Check if there is at least one lock that cannot be opened
        bool atLeastOneLockUnopened = false;
        for (size_t j = 0; j < matrix[0].size(); j++) {
            int sum = 0;
            for (size_t i = 0; i < matrix.size(); i++) {
                sum += matrix[i][j];
            }
            if (sum == 0) {
                atLeastOneLockUnopened = true;
                break;
            }
        }

        /* Verification */
        EXPECT_TRUE(atLeastOneLockUnopened);
    } else {
        // If no such key exists, the test is skipped
        GTEST_SKIP();
    }
}

// Metamorphic Relation 18:
// If a key can open all locks, then adding additional locks that can be opened by the same key will not change the output.
TEST_P(KLPParamTest, MR18) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    // Find a key that can open all locks
    int keyIndex = -1;
    for (size_t i = 0; i < matrix.size(); i++) {
        bool canOpenAllLocks = true;
        for (size_t j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == 0) {
                canOpenAllLocks = false;
                break;
            }
        }
        if (canOpenAllLocks) {
            keyIndex = i;
            break;
        }
    }

    if (keyIndex >= 0) {
        /* Get source output */
        vector<int> source_out = KLP(matrix);

        // Add additional locks that can be opened by the same key
        for (size_t j = 0; j < matrix[0].size(); j++) {
            if (matrix[keyIndex][j] == 0) {
                matrix[keyIndex][j] = 1; // Assume the lock can be opened by the selected key
            }
        }

        /* Get follow-up output */
        vector<int> follow_out = KLP(matrix);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    } else {
        // If no such key exists, the test is skipped
        GTEST_SKIP();
    }
}

// Metamorphic Relation 19:
// If a key can open all locks, then shuffling the order of locks while preserving which keys can open them will not change the output.
TEST_P(KLPParamTest, MR19) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    // Find a key that can open all locks
    int keyIndex = -1;
    for (size_t i = 0; i < matrix.size(); i++) {
        bool canOpenAllLocks = true;
        for (size_t j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == 0) {
                canOpenAllLocks = false;
                break;
            }
        }
        if (canOpenAllLocks) {
            keyIndex = i;
            break;
        }
    }

    if (keyIndex >= 0) {
        /* Get source output */
        vector<int> source_out = KLP(matrix);

        // Shuffle the order of locks while preserving which keys can open them
        vector<int> shuffled_indices(matrix[0].size());
        iota(shuffled_indices.begin(), shuffled_indices.end(), 0); // Generate indices 0 to size-1
        shuffle(shuffled_indices.begin(), shuffled_indices.end(), default_random_engine());

        vector<vector<int>> shuffled_matrix(matrix.size(), vector<int>(matrix[0].size()));
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = 0; j < matrix[i].size(); j++) {
                shuffled_matrix[i][shuffled_indices[j]] = matrix[i][j];
            }
        }

        /* Get follow-up output */
        vector<int> follow_out = KLP(shuffled_matrix);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    } else {
        // If no such key exists, the test is skipped
        GTEST_SKIP();
    }
}

// Metamorphic Relation 20:
// If the keys and locks are interchanged, the output will change to represent the complementary set of locks for each key.
TEST_P(KLPParamTest, MR20) {
    // Get source input
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    // Get source output
    vector<int> source_out = KLP(matrix);

    // Create the complementary matrix where keys and locks are interchanged
    vector<vector<int>> complementary_matrix(matrix[0].size(), vector<int>(matrix.size()));
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            complementary_matrix[j][i] = matrix[i][j];
        }
    }

    // Get follow-up output using the complementary matrix
    vector<int> follow_out = KLP(complementary_matrix);

    // Verification
    // Assert that the follow-up output complements the source output
    for (size_t i = 0; i < source_out.size(); i++) {
        EXPECT_EQ(1 - source_out[i], follow_out[i]);
    }
}

// Metamorphic Relation 21:
// If a key can open no locks, removing that key from the matrix will not change the output.
TEST_P(KLPParamTest, MR21) {
    // Get source input
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    // Find a key that cannot open any locks
    int keyIndex = -1;
    for (size_t i = 0; i < matrix.size(); i++) {
        bool canOpenAnyLock = false;
        for (size_t j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == 1) {
                canOpenAnyLock = true;
                break;
            }
        }
        if (!canOpenAnyLock) {
            keyIndex = i;
            break;
        }
    }

    if (keyIndex >= 0) {
        // Get source output
        vector<int> source_out = KLP(matrix);

        // Remove the key from the matrix
        matrix.erase(matrix.begin() + keyIndex);

        // Get follow-up output
        vector<int> follow_out = KLP(matrix);

        // Verification
        EXPECT_EQ(source_out, follow_out);
    } else {
        // If no such key exists, the test is skipped
        GTEST_SKIP();
    }
}

// Metamorphic Relation 22:
// If all locks are opened by at least one key, adding a new key that can open all locks will not change the output.
TEST_P(KLPParamTest, MR22) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    // Ensure that all locks are opened by at least one key
    for (size_t j = 0; j < matrix[0].size(); j++) {
        bool lockCovered = false;
        for (size_t i = 0; i < matrix.size(); i++) {
            if (matrix[i][j] == 1) {
                lockCovered = true;
                break;
            }
        }
        // If there is a lock not covered by any key, the test is skipped
        if (!lockCovered) {
            GTEST_SKIP();
            return;
        }
    }

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    // Add a new key that opens all locks
    vector<int> new_key(matrix[0].size(), 1);
    matrix.push_back(new_key);

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 23:
// If all the keys can open all locks or all the locks can be opened by all keys, adding more keys or locks will not change the output.
TEST_P(KLPParamTest, MR23) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    bool allKeysCanOpenAllLocks = true;
    bool allLocksCanBeOpenedByAllKeys = true;

    // Ensure that all keys can open all locks or all locks can be opened by all keys
    for (size_t j = 0; j < matrix[0].size(); j++) {
        bool lockCovered = false;
        bool lockUncovered = false;
        for (size_t i = 0; i < matrix.size(); i++) {
            if (matrix[i][j] == 1) {
                lockCovered = true;
            } else {
                lockUncovered = true;
            }
        }
        if (lockCovered && lockUncovered) {
            allLocksCanBeOpenedByAllKeys = false;
            break;
        }
    }

    for (size_t i = 0; i < matrix.size(); i++) {
        bool keyCanOpenAllLocks = true;
        bool keyCannotOpenAnyLock = true;
        for (size_t j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == 0) {
                keyCanOpenAllLocks = false;
            } else {
                keyCannotOpenAnyLock = false;
            }
        }
        if (!keyCanOpenAllLocks && !keyCannotOpenAnyLock) {
            allKeysCanOpenAllLocks = false;
            break;
        }
    }

    if (!allKeysCanOpenAllLocks && !allLocksCanBeOpenedByAllKeys) {
        // If neither all keys can open all locks nor all locks can be opened by all keys, the test is skipped
        GTEST_SKIP();
        return;
    }

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    // Add more keys or locks
    // Example: Adding a new key
    vector<int> new_key(matrix[0].size(), 1);
    matrix.push_back(new_key);

    // OR

    // Example: Adding a new lock
    for (auto &key : matrix) {
        key.push_back(1);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 24:
// If all the keys have the same set of locks that they can open, the output will remain unchanged if the order of the locks are reversed.
TEST_P(KLPParamTest, MR24) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    bool allKeysIdentical = true;

    // Check if all keys can open identical locks
    for (size_t i = 1; i < matrix.size(); i++) {
        if (matrix[i] != matrix[i - 1]) {
            allKeysIdentical = false;
            break;
        }
    }

    if (!allKeysIdentical) {
        // If the keys don't have an identical set of locks, the test is skipped
        GTEST_SKIP();
        return;
    }

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    // Reverse the order of locks
    for (auto &row : matrix) {
        reverse(row.begin(), row.end());
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 25:
// If the matrix contains duplicate rows, then the output will remain unchanged.
TEST_P(KLPParamTest, MR25) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Add duplicate rows to the matrix */
    matrix.push_back(matrix[0]); // Add a duplicate of the first row

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 26:
// If the matrix contains multiple rows where one row is a subset of another, the output should remain unchanged.
TEST_P(KLPParamTest, MR26) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    // Add a row that is a subset of another row
    if (matrix.size() > 1) {
        auto subset_row = matrix[0];
        matrix.push_back(subset_row);

        /* Get follow-up output */
        vector<int> follow_out = KLP(matrix);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    } else {
        // If the matrix has only one row, the test is skipped
        GTEST_SKIP();
    }
}

// Metamorphic Relation 27:
// If all the locks can be opened by at least one key, then doubling the number of locks by adding a duplicate set of locks will not change the output.
TEST_P(KLPParamTest, MR27) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Double the number of locks by adding a duplicate set of locks */
    size_t original_num_locks = matrix[0].size();
    for (size_t i = 0; i < original_num_locks; i++) {
        vector<int> duplicate_lock = matrix[0];
        matrix.push_back(duplicate_lock);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 28:
// If all the locks can be opened by at least one key, then permuting the order of keys will result in a reordering of the output.
TEST_P(KLPParamTest, MR28) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    // Find a lock that can be opened by multiple keys
    int lockIndex = -1;
    for (size_t j = 0; j < matrix[0].size(); j++) {
        int sum = 0;
        for (size_t i = 0; i < matrix.size(); i++) {
            sum += matrix[i][j];
        }
        if (sum > 1) {
            lockIndex = j;
            break;
        }
    }

    if (lockIndex >= 0) {
        /* Get source output */
        vector<int> source_out = KLP(matrix);

        /* Permute the order of keys */
        std::random_shuffle(matrix.begin(), matrix.end());

        /* Get follow-up output */
        vector<int> follow_out = KLP(matrix);

        /* Verification */
        EXPECT_NE(source_out, follow_out);
    } else {
        // If no such lock exists, the test is skipped
        GTEST_SKIP();
    }
}

// Metamorphic Relation 29:
// If a lock can be opened by all keys, then removing one of these keys while keeping others unchanged will not change the output.
TEST_P(KLPParamTest, MR29) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    // Find a lock that can be opened by all keys
    int lockIndex = -1;
    for (size_t j = 0; j < matrix[0].size(); j++) {
        bool canOpenByAllKeys = true;
        for (size_t i = 0; i < matrix.size(); i++) {
            if (matrix[i][j] == 0) {
                canOpenByAllKeys = false;
                break;
            }
        }
        if (canOpenByAllKeys) {
            lockIndex = j;
            break;
        }
    }

    if (lockIndex >= 0) {
        /* Get source output */
        vector<int> source_out = KLP(matrix);

        // Remove one of the keys which can open the lock
        size_t keyToRemove = 0;
        for (size_t i = 0; i < matrix.size(); i++) {
            if (matrix[i][lockIndex] == 1) {
                keyToRemove = i;
                break;
            }
        }
        matrix.erase(matrix.begin() + keyToRemove);

        /* Get follow-up output */
        vector<int> follow_out = KLP(matrix);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    } else {
        // If no such lock exists, the test is skipped
        GTEST_SKIP();
    }
}

// Metamorphic Relation 30:
// If the matrix contains equal rows, then the output will remain unchanged.
TEST_P(KLPParamTest, MR30) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    // Find the first row with non-zero elements
    vector<int> targetRow;
    for (const auto &row : matrix) {
        if (accumulate(row.begin(), row.end(), 0) != 0) {
            targetRow = row;
            break;
        }
    }

    if (targetRow.empty()) {
        // If all rows are zero, skip the test
        GTEST_SKIP();
    }

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    // Add a duplicate row
    matrix.push_back(targetRow);

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 31:
// Adding a new lock that cannot be opened by any key will not change the output.
TEST_P(KLPParamTest, MR31) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    // Find a key that opens all locks
    int keyIndex = -1;
    for (size_t i = 0; i < matrix.size(); i++) {
        bool canOpenAllLocks = true;
        for (size_t j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] != 1) {
                canOpenAllLocks = false;
                break;
            }
        }
        if (canOpenAllLocks) {
            keyIndex = i;
            break;
        }
    }

    if (keyIndex >= 0) {
        /* Get source output */
        vector<int> source_out = KLP(matrix);

        // Add a new lock that cannot be opened by any key
        for (size_t i = 0; i < matrix.size(); i++) {
            matrix[i].push_back(0);
        }

        /* Get follow-up output */
        vector<int> follow_out = KLP(matrix);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    } else {
        // If no such key exists, the test is skipped
        GTEST_SKIP();
    }
}

// Metamorphic Relation 32:
// If the keys and locks are interchanged, the output will change to represent the complementary set of locks for each key.
TEST_P(KLPParamTest, MR32) {
    // Get source input
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    // Get source output
    vector<int> source_out = KLP(matrix);

    // Create the complementary matrix where keys and locks are interchanged
    vector<vector<int>> complementary_matrix(matrix[0].size(), vector<int>(matrix.size()));
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            complementary_matrix[j][i] = matrix[i][j];
        }
    }

    // Get follow-up output using the complementary matrix
    vector<int> follow_out = KLP(complementary_matrix);

    // Verification
    // Assert that the follow-up output complements the source output
    for (size_t i = 0; i < source_out.size(); i++) {
        EXPECT_EQ(1 - source_out[i], follow_out[i]);
    }
}

// Metamorphic Relation 33:
// If all the locks can be opened by at least one key, removing a non-critical key will not change the output. A non-critical key is a key that can open a lock
// that can also be opened by other keys.
TEST_P(KLPParamTest, MR33) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    // Identify a non-critical key
    size_t nonCriticalKeyIndex = 0;
    bool foundNonCriticalKey = false;

    for (size_t i = 0; i < matrix.size(); i++) {
        bool nonCritical = true;

        for (size_t j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == 1) { // If the key can open a lock
                bool otherKeyOpens = false;

                for (size_t k = 0; k < matrix.size(); k++) {
                    if (k != i && matrix[k][j] == 1) {
                        otherKeyOpens = true;

                        // There's another key that opens this lock, so this key is non-critical
                        break;
                    }
                }

                if (otherKeyOpens) {
                    nonCritical = false;
                    break;
                }
            }
        }

        if (nonCritical) {
            nonCriticalKeyIndex = i;
            foundNonCriticalKey = true;
            break;
        }
    }

    if (foundNonCriticalKey) {
        /* Get source output */
        vector<int> source_out = KLP(matrix);

        // Remove the non-critical key
        matrix.erase(matrix.begin() + nonCriticalKeyIndex);

        /* Get follow-up output */
        vector<int> follow_out = KLP(matrix);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    } else {
        // If no non-critical key is found, skip the test
        GTEST_SKIP();
    }
}

// Metamorphic Relation 34:
// If the matrix contains all zeros, the output is an empty array.
TEST_P(KLPParamTest, MR34) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Set all elements of the matrix to zero */
    for (auto &row : matrix) {
        fill(row.begin(), row.end(), 0);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Expected output is an empty array */
    vector<int> expected_empty_out;

    /* Verification */
    EXPECT_EQ(expected_empty_out, follow_out);
}

// Metamorphic Relation 35:
// If a lock can only be opened by one specific key, removing that key will result in one locked lock that will not be opened by any key.
TEST_P(KLPParamTest, MR35) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    // Find a lock that can only be opened by one specific key
    size_t lockColumn = 0;
    size_t keyRow = 0;
    bool uniqueLockFound = false;

    for (size_t j = 0; j < matrix[0].size(); j++) {
        int keyCount = 0;
        for (size_t i = 0; i < matrix.size(); i++) {
            if (matrix[i][j] == 1) {
                keyCount++;
                keyRow = i;
                lockColumn = j;
            }
        }
        if (keyCount == 1) {
            uniqueLockFound = true;
            break;
        }
    }

    if (uniqueLockFound) {
        /* Get source output */
        vector<int> source_out = KLP(matrix);

        // Remove the key that can open the unique lock
        matrix[keyRow][lockColumn] = 0;

        /* Get follow-up output */
        vector<int> follow_out = KLP(matrix);

        /* Verification */
        EXPECT_NE(source_out, follow_out);
    } else {
        // If no lock that can only be opened by a single key, the test is skipped
        GTEST_SKIP();
    }
}

// Metamorphic Relation 36:
// If the matrix contains duplicate columns, the output will remain unchanged.
TEST_P(KLPParamTest, MR36) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Add duplicate columns to the matrix */
    for (size_t i = 0; i < matrix.size(); i++) {
        matrix[i].push_back(matrix[i][0]); // Duplicate the first column in each row
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 37:
// If all locks can be opened by at least one key and at least one lock has multiple keys to open it, removing any key that opens that lock will not change the
// output.
TEST_P(KLPParamTest, MR37) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    int lockIndex = -1;
    int keyIndex = -1;

    // Find a lock that can be opened by multiple keys
    for (size_t j = 0; j < matrix[0].size(); j++) {
        int keyCount = 0;
        for (size_t i = 0; i < matrix.size(); i++) {
            if (matrix[i][j] == 1) {
                keyCount++;
                keyIndex = i;
                lockIndex = j;
            }
        }
        if (keyCount > 1) {
            break;
        }
    }

    if (lockIndex != -1 && keyIndex != -1) {
        /* Get source output */
        vector<int> source_out = KLP(matrix);

        // Remove the key that opens the lock
        matrix[keyIndex][lockIndex] = 0;

        /* Get follow-up output */
        vector<int> follow_out = KLP(matrix);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    } else {
        // If no such lock exists, the test is skipped
        GTEST_SKIP();
    }
}

// Metamorphic Relation 38:
// If all the keys can open all locks, then permuting the order of keys and locks will result in a reordering of the output.
TEST_P(KLPParamTest, MR38) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Permute the order of keys and locks */
    random_shuffle(matrix.begin(), matrix.end());
    for (auto &row : matrix) {
        random_shuffle(row.begin(), row.end());
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verification */
    EXPECT_NE(source_out, follow_out);
}

// Metamorphic Relation 39:
// If the matrix contains all ones, double the number of locks by adding an extra set of locks will not change the output.
TEST_P(KLPParamTest, MR39) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Double the number of locks by adding an extra set of locks */
    for (auto &row : matrix) {
        row.insert(row.end(), row.begin(), row.end());
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 40:
//  If a key can open all locks, doubling the number of keys by adding a duplicate set of keys will not change the output.
TEST_P(KLPParamTest, MR40) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get the source output */
    vector<int> source_out = KLP(matrix);

    /* Double the number of keys by adding a duplicate set of keys */
    size_t original_num_keys = matrix.size();
    for (size_t i = 0; i < original_num_keys; i++) {
        matrix.push_back(matrix[i]); // Duplicate each key
    }

    /* Get the follow-up output */
    vector<int> follow_out = KLP(matrix);

    /* Verify that the output remains unchanged */
    EXPECT_EQ(source_out, follow_out);
}

// Metamorphic Relation 41:
// If the matrix contains a row such that every lock can be opened by exactly one key, removing that row will not change the output.
TEST_P(KLPParamTest, MR41) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    // Find a row where every lock can be opened by exactly one key
    size_t uniqueKeyRow = 0;
    bool foundUnique = false;

    for (size_t i = 0; i < matrix.size(); i++) {
        int keyCount = 0;
        for (size_t j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == 1) {
                keyCount++;
            }
        }
        if (keyCount == 1) {
            foundUnique = true;
            uniqueKeyRow = i;
            break;
        }
    }

    if (foundUnique) {
        /* Get source output */
        vector<int> source_out = KLP(matrix);

        // Remove the row where every lock can be opened by exactly one key
        matrix.erase(matrix.begin() + uniqueKeyRow);

        /* Get follow-up output */
        vector<int> follow_out = KLP(matrix);

        /* Verify that the output remains unchanged */
        EXPECT_EQ(source_out, follow_out);
    } else {
        // Skip the test if no such row is found
        GTEST_SKIP();
    }
}

// Metamorphic Relation 42:
// Introducing a permutation of keys and locks that maintains the same pairwise unlock-ability relationships will not change the output.
TEST_P(KLPParamTest, MR42) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get the source output */
    vector<int> source_out = KLP(matrix);

#if INVALID
    /* Find the set of keys */
    set<int> keys;
    for (size_t i = 0; i < matrix.size(); i++) {
        keys.insert(i);
    }

    /* Find the set of locks */
    set<int> locks;
    for (size_t j = 0; j < matrix[0].size(); j++) {
        locks.insert(j);
    }
#else
    /* Fix by Radon */
    /* Find the vector of keys */
    vector<int> keys;
    for (size_t i = 0; i < matrix.size(); i++) {
        keys.emplace_back(i);
    }

    /* Find the vector of locks */
    vector<int> locks;
    for (size_t j = 0; j < matrix[0].size(); j++) {
        locks.emplace_back(j);
    }
#endif

    do {
        do {
            bool isValid = true;
            for (int key : keys) {
                for (int lock : locks) {
                    if (matrix[key][lock] != matrix[*keys.begin()][*locks.begin()]) {
                        isValid = false;
                        break;
                    }
                }
            }
            if (isValid) {
                vector<vector<int>> permuted_matrix(matrix.size(), vector<int>(matrix[0].size()));
                int i = 0, j = 0;
                for (int key : keys) {
                    for (int lock : locks) {
                        permuted_matrix[i][j] = matrix[key][lock];
                        j++;
                    }
                    i++;
                    j = 0;
                }

                /* Get the follow-up output */
                vector<int> follow_out = KLP(permuted_matrix);

                /* Verify that the output remains unchanged */
                EXPECT_EQ(source_out, follow_out);
            }
        } while (next_permutation(locks.begin(), locks.end()));
    } while (next_permutation(keys.begin(), keys.end()));
}

INSTANTIATE_TEST_CASE_P(TrueReturn, KLPParamTest, testing::ValuesIn(gen_tcs_randomly()));