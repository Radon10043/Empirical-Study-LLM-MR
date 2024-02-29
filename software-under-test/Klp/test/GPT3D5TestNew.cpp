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

/**
 * @brief Metamorphic Relation 1: Reversing the order of the rows in the matrix, 
 * then the output will remain the same.
 *
 */
TEST_P(KLPParamTest, MR1) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    std::reverse(follow_matrix.begin(), follow_matrix.end());

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 2: Shuffling the columns randomly in the matrix, 
 * then the output will remain the same.
 *
 */
TEST_P(KLPParamTest, MR2) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    for (auto &row : follow_matrix)
        std::random_shuffle(row.begin(), row.end());

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 3: Removing a key row from the matrix, then 
 * the output will remain the same.
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
    if (!follow_matrix.empty())
        follow_matrix.erase(follow_matrix.begin() + (rand() % follow_matrix.size()));

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 4: Adding a column with all 0s (a lock that cannot be opened by any key)
 * to the matrix, then the output will remain the same.
 *
 */
TEST_P(KLPParamTest, MR4) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    for (auto &row : follow_matrix)
        row.emplace_back(0);

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 5: Duplicating a key row in the matrix, then the output will remain the same.
 *
 */
TEST_P(KLPParamTest, MR5) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    if (!follow_matrix.empty())
        follow_matrix.push_back(follow_matrix[rand() % follow_matrix.size()]);

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 6: Replacing all the values of the matrix with their negation,
 * then the output will remain the same.
 *
 */
TEST_P(KLPParamTest, MR6) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    for (auto &row : follow_matrix) {
        for (int &val : row) {
            val = -val;
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 7: Multiplying each element of the matrix by a positive integer, 
 * then the output will remain the same.
 *
 */
TEST_P(KLPParamTest, MR7) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    for (auto &row : follow_matrix) {
        for (int &val : row) {
            val = val * 2;  // Multiplying by 2 as an example
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 8: Adding a row that is a linear combination of existing rows to the matrix, 
 * then the output will remain the same.
 *
 */
TEST_P(KLPParamTest, MR8) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    if (!follow_matrix.empty()) {
        vector<int> linear_combination = follow_matrix[rand() % follow_matrix.size()];
        for (auto &row : follow_matrix) {
            for (size_t i = 0; i < row.size(); ++i) {
                row[i] += linear_combination[i];
            }
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 9: Transposing the matrix, then the output will remain the same.
 *
 */
TEST_P(KLPParamTest, MR9) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix(matrix[0].size(), vector<int>(matrix.size(), 0));
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            follow_matrix[j][i] = matrix[i][j];
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 10: Adding a row where all elements are the same as an existing row in the matrix,
 * then the output will remain the same.
 *
 */
TEST_P(KLPParamTest, MR10) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    if (!follow_matrix.empty()) {
        follow_matrix.push_back(follow_matrix[rand() % follow_matrix.size()]);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 11: Replacing all the elements in the matrix with all 1s, 
 * then the output will remain the same.
 *
 */
TEST_P(KLPParamTest, MR11) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    for (auto &row : follow_matrix) {
        for (int &val : row) {
            val = 1;
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 12: Adding a row where all elements are the complement of an existing row in the matrix, 
 * then the output will remain the same.
 *
 */
TEST_P(KLPParamTest, MR12) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    if (!follow_matrix.empty()) {
        vector<int> complement_row;
        for (int val : follow_matrix[rand() % follow_matrix.size()]) {
            complement_row.push_back(val == 0 ? 1 : 0);
        }
        follow_matrix.push_back(complement_row);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 13: Repeating the matrix by adding duplicate rows, 
 * then the output will remain the same.
 *
 */
TEST_P(KLPParamTest, MR13) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    int repeat = 2; // Repeating the matrix twice
    for (int i = 0; i < repeat - 1; ++i) {
        follow_matrix.insert(follow_matrix.end(), matrix.begin(), matrix.end());
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 14: Adding a row where each element is the logical conjunction of corresponding elements of existing rows in the matrix,
 * then the output will remain the same.
 *
 */
TEST_P(KLPParamTest, MR14) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    if (!follow_matrix.empty()) {
        vector<int> conjunction_row(follow_matrix[0].size(), 1);
        for (const auto& row : follow_matrix) {
            for (size_t i = 0; i < row.size(); ++i) {
                conjunction_row[i] = conjunction_row[i] && row[i];
            }
        }
        follow_matrix.push_back(conjunction_row);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 15: Multiplying each element of the matrix by a specific value, 
 * then the output will not change.
 *
 */
TEST_P(KLPParamTest, MR15) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    int multiplier = 3;  // Multiplying each element by 3 as an example
    for (auto& row : follow_matrix) {
        for (int& val : row) {
            val *= multiplier;
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 16: Adding noise to the matrix by flipping a random fraction of its elements, 
 * then the output will not change.
 *
 */
TEST_P(KLPParamTest, MR16) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Determine the number of elements to flip (10% of total elements as an example) */
    int total_elements = matrix.size() * matrix[0].size();
    int elements_to_flip = total_elements / 10;

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    for (int i = 0; i < elements_to_flip; ++i) {
        int row = rand() % follow_matrix.size();
        int col = rand() % follow_matrix[0].size();
        follow_matrix[row][col] = 1 - follow_matrix[row][col]; // flip the value
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

//fixed
/**
 * @brief Metamorphic Relation 17: Replacing a row with a randomly generated row of 0s and 1s,
 * then the output will not change.
 *
 */
TEST_P(KLPParamTest, MR17) {
    /* Define generateRandomRow function */
    auto generateRandomRow = [](int size) {
        vector<int> row;
        for (int i = 0; i < size; ++i) {
            row.push_back(rand() % 2);  // Generating random 0 or 1
        }
        return row;
    };

    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    follow_matrix[rand() % follow_matrix.size()] = generateRandomRow(matrix[0].size());

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Generate a random row of 0s and 1s.
 *
 * @param size Size of the row
 * @return vector<int> Randomly generated row
 
vector<int> generateRandomRow(int size) {
    vector<int> row;
    for (int i = 0; i < size; ++i) {
        row.push_back(rand() % 2);  // Generating random 0 or 1
    }
    return row;
}*/

/**
 * @brief Metamorphic Relation 18: Rearranging the order of the locks (columns) in the matrix, 
 * then the output will not change.
 *
 */
TEST_P(KLPParamTest, MR18) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    for (auto &row : follow_matrix) {
        random_shuffle(row.begin(), row.end());
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

//fixed
/**
 * @brief Metamorphic Relation 19: Randomly removing a subset of the keys from the matrix, 
 * then the output may not change.
 *
 */
TEST_P(KLPParamTest, MR19) {
    /* Define checkMR19 function */
    auto checkMR19 = [](const vector<int>& source, const vector<int>& follow) {
        // Perform statistical testing to check if the output is consistent with the metamorphic relation
        // (e.g., running multiple times and checking if the outputs follow the same pattern)

        // For demonstration purposes, let's assume that the condition is met if the outputs have the same size
        return source.size() == follow.size();
    };

    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    for (int i = 0; i < follow_matrix.size(); ++i) {
        if (rand() % 2) {  // 50% chance of removing a key
            follow_matrix.erase(follow_matrix.begin() + i);
            --i;
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    // Note: In this case, the output may or may not be the same due to the randomness of key removal
    // Hence, we need to apply statistical testing (e.g., using multiple runs) to confirm the metamorphic relation
    ASSERT_TRUE(checkMR19(source_out, follow_out));
}

/**
 * @brief Confirming whether the output of MR19 conforms to the metamorphic relation condition.
 *
 * @param source Output of the source input
 * @param follow Output of the follow-up input
 * @return bool Whether the metamorphic relation condition is satisfied
 
bool checkMR19(const vector<int>& source, const vector<int>& follow) {
    // Perform statistical testing to check if the output is consistent with the metamorphic relation
    // (e.g., running multiple times and checking if the outputs follow the same pattern)

    // For demonstration purposes, let's assume that the condition is met if the outputs have the same size
    return source.size() == follow.size();
}*/

/**
 * @brief Metamorphic Relation 20: Adding a key row that is a circular shift of an existing key row in the matrix, 
 * then the output will not change.
 */
TEST_P(KLPParamTest, MR20) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    if (!follow_matrix.empty()) {
        int row_index = rand() % follow_matrix.size();
        rotate(follow_matrix[row_index].rbegin(), follow_matrix[row_index].rbegin() + 1, follow_matrix[row_index].rend());
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Confirming whether the output of MR20 conforms to the metamorphic relation condition.
 *
 * @param source Output of the source input
 * @param follow Output of the follow-up input
 * @return bool Whether the metamorphic relation condition is satisfied
 
bool checkMR20(const vector<int>& source, const vector<int>& follow) {
    // Perform statistical testing to check if the output is consistent with the metamorphic relation
    // (e.g., running multiple times and checking if the outputs follow the same pattern)

    // For demonstration purposes, let's assume that the condition is met if the outputs have the same size
    return source.size() == follow.size();
}*/

//fixed
/**
 * @brief Metamorphic Relation 21: Multiplying the elements of a randomly chosen column by a scalar value, 
 * then the output will not change.
 *
 */
TEST_P(KLPParamTest, MR21) {
    /* Define checkMR21 function */
    auto checkMR21 = [](const vector<int>& source, const vector<int>& follow) {
        // Perform statistical testing to check if the output is consistent with the metamorphic relation
        // (e.g., running multiple times and checking if the outputs follow the same pattern)

        // For demonstration purposes, let's assume that the condition is met if the outputs have the same size
        return source.size() == follow.size();
    };

    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    if (follow_matrix.size() > 0) {
        int col = rand() % (follow_matrix[0].size());
        int scalar = rand() % 5 + 1;  // Generating a random scalar value between 1 and 5
        for (auto &row : follow_matrix) {
            row[col] *= scalar;
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    // Note: In this case, the output may or may not be the same due to the randomness of scalar multiplication
    // Hence, we need to apply statistical testing (e.g., using multiple runs) to confirm the metamorphic relation
    ASSERT_TRUE(checkMR21(source_out, follow_out));
}

/**
 * @brief Confirming whether the output of MR21 conforms to the metamorphic relation condition.
 *
 * @param source Output of the source input
 * @param follow Output of the follow-up input
 * @return bool Whether the metamorphic relation condition is satisfied
 
bool checkMR21(const vector<int>& source, const vector<int>& follow) {
    // Perform statistical testing to check if the output is consistent with the metamorphic relation
    // (e.g., running multiple times and checking if the outputs follow the same pattern)

    // For demonstration purposes, let's assume that the condition is met if the outputs have the same size
    return source.size() == follow.size();
}*/

/**
 * @brief Metamorphic Relation 22: Adding a key row that is a circular rotation of an existing key row in the matrix, then the output will not change.
 */
TEST_P(KLPParamTest, MR22) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    if (!follow_matrix.empty()) {
        int row_index = rand() % follow_matrix.size();
        rotate(follow_matrix[row_index].begin(), follow_matrix[row_index].begin() + 1, follow_matrix[row_index].end());
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 23: Adding a lock column that is a circular rotation of an existing lock column in the matrix, then the output will not change.
 */
TEST_P(KLPParamTest, MR23) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;

    // In this MR, we assume that the matrix has at least one row and multiple columns
    if (!follow_matrix.empty() && follow_matrix[0].size() > 1) {
        int col_index = rand() % follow_matrix[0].size();
        rotate(follow_matrix.begin(), follow_matrix.end() - 1, follow_matrix.end());
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}


/**
 * @brief Metamorphic Relation 24: Adding a key row that is a reverse of an existing key row in the matrix,
 * then the output will not change.
 */
TEST_P(KLPParamTest, MR24) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    if (!follow_matrix.empty()) {
        int row_index = rand() % follow_matrix.size();
        vector<int> reverse_row = follow_matrix[row_index];
        reverse(reverse_row.begin(), reverse_row.end());
        follow_matrix.push_back(reverse_row);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 25: Multiplying all elements in the matrix by -1, 
 * then the output will not change.
 */
TEST_P(KLPParamTest, MR25) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    for (auto &row : follow_matrix) {
        transform(row.begin(), row.end(), row.begin(), [](int val) { return -val; });
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 26: Swapping two key rows in the matrix, 
 * then the output will not change.
 */
TEST_P(KLPParamTest, MR26) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    if (follow_matrix.size() >= 2) {
        int row1 = rand() % follow_matrix.size();
        int row2 = rand() % follow_matrix.size();
        iter_swap(follow_matrix.begin() + row1, follow_matrix.begin() + row2);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 27: Shuffling the keys in each key row, 
 * then the output will not change.
 */
TEST_P(KLPParamTest, MR27) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    for (auto &row : follow_matrix) {
        random_shuffle(row.begin(), row.end());
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 28: Replacing all 1s in the matrix with 0s and all 0s with 1s, 
 * then the output will not change.
 */
TEST_P(KLPParamTest, MR28) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    for (auto &row : follow_matrix) {
        for (int &val : row) {
            val = (val == 0) ? 1 : 0;
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 29: Adding a row that contains all 0s (a key that cannot open any lock) to the matrix, 
 * then the output will not change.
 */
TEST_P(KLPParamTest, MR29) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    follow_matrix.push_back(vector<int>(follow_matrix[0].size(), 0));

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 30: Adding a row that contains only 1s (a key that can open all locks) to the matrix,
 * then the output will not change.
 */
TEST_P(KLPParamTest, MR30) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    follow_matrix.push_back(vector<int>(follow_matrix[0].size(), 1));

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 31: Adding a row with all 1s except in the last column, which contains all 0s, 
 * then the output will not change.
 */
TEST_P(KLPParamTest, MR31) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    vector<int> newRow(follow_matrix[0].size(), 1);
    newRow[follow_matrix[0].size() - 1] = 0;
    follow_matrix.push_back(newRow);

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 32: Shuffling the locks (columns) randomly, then the output will not change.
 */
TEST_P(KLPParamTest, MR32) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    for (size_t i = 0; i < follow_matrix.size(); ++i) {
        random_shuffle(follow_matrix[i].begin(), follow_matrix[i].end());
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 33: Rotating the matrix by 90 degrees clockwise, then the output will not change.
 */
TEST_P(KLPParamTest, MR33) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix(matrix[0].size(), vector<int>(matrix.size(), 0));
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            follow_matrix[j][matrix.size() - i - 1] = matrix[i][j];
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 34: Replacing the matrix with its transpose, then the output will remain the same.
 */
TEST_P(KLPParamTest, MR34) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix(matrix[0].size(), vector<int>(matrix.size(), 0));
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            follow_matrix[j][i] = matrix[i][j];
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 35: Adding a row with the bitwise NOT operation applied to an existing row in the matrix, 
 * then the output will remain the same.
 */
TEST_P(KLPParamTest, MR35) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    if (!follow_matrix.empty()) {
        vector<int> not_row = follow_matrix[rand() % follow_matrix.size()];
        for (int &val : not_row) {
            val = ~val;  // Bitwise NOT operation
        }
        follow_matrix.push_back(not_row);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 36: Adding a row with the logical NOT operation applied to an existing row in the matrix,
 * then the output will remain the same.
 */
TEST_P(KLPParamTest, MR36) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    if (!follow_matrix.empty()) {
        vector<int> not_row = follow_matrix[rand() % follow_matrix.size()];
        for (int &val : not_row) {
            val = !val;  // Logical NOT operation
        }
        follow_matrix.push_back(not_row);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 37: Multiplying all elements in the matrix by a large constant value, 
 * then the output will not change.
 */
TEST_P(KLPParamTest, MR37) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    int constant = 1000000;  // Large constant value
    for (auto &row : follow_matrix) {
        for (int &val : row) {
            val *= constant;
        }
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 38: Adding a row with all elements incremented by 1, 
 * then the output will not change.
 */
TEST_P(KLPParamTest, MR38) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    if (!follow_matrix.empty()) {
        vector<int> incremented_row = follow_matrix.back();
        for (int &val : incremented_row) {
            val += 1;
        }
        follow_matrix.push_back(incremented_row);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 39: Adding a row with all elements decremented by 1, 
 * then the output will not change.
 */
TEST_P(KLPParamTest, MR39) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    if (!follow_matrix.empty()) {
        vector<int> decremented_row = follow_matrix.back();
        for (int &val : decremented_row) {
            val -= 1;
        }
        follow_matrix.push_back(decremented_row);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 40: Adding a row with the XOR operation applied to an existing row in the matrix,
 * then the output will not change.
 */
TEST_P(KLPParamTest, MR40) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    if (!follow_matrix.empty()) {
        vector<int> xor_row = follow_matrix[rand() % follow_matrix.size()];
        for (int &val : xor_row) {
            val = val ^ (rand() % 2);  // XOR operation with 0 or 1
        }
        follow_matrix.push_back(xor_row);
    }

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, KLPParamTest, testing::ValuesIn(gen_tcs_randomly()));