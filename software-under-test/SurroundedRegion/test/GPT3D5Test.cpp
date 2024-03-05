#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class SurroundedRegionParamTest : public ::testing::TestWithParam<SurroundedRegionInput> {};

/**
 * @brief Metamorphic Relation 1: Reversing the order of rows in the input matrix should not change the output.
 *
 */
TEST_P(SurroundedRegionParamTest, MR1) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input */
    vector<string> follow_vec(source_vec.rbegin(), source_vec.rend());
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Output of original input should be same as reverse input */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 2: Shifting every character in the input matrix down by one position, then the result should also be shifted down by one position.
 *
 */
TEST_P(SurroundedRegionParamTest, MR2) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    for (int i = follow_vec.size() - 1; i > 0; i--) {
        follow_vec[i] = source_vec[i - 1];
    }
    follow_vec[0] = string(follow_vec[0].length(), 'O');
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Result of shifting down the input should match shifted down result */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 3: Replacing all 'O's with 'X' in the input matrix, then the output should also have all 'O's replaced with 'X'.
 *
 */
TEST_P(SurroundedRegionParamTest, MR3) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Replace 'O's with 'X' in source input */
    for (auto& row : source_vec) {
        replace(row.begin(), row.end(), 'O', 'X');
    }
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Verification: Output of source input with 'O's replaced by 'X' should match output of original input */
    for (auto& row : source_out) {
        replace(row.begin(), row.end(), 'O', 'X');
    }
    EXPECT_EQ(source_out, source_out);
}

/**
 * @brief Metamorphic Relation 4: Adding a row of 'X's to the input matrix, then the output should remain the same.
 *
 */
TEST_P(SurroundedRegionParamTest, MR4) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input */
    int cols = source_vec[0].length();
    vector<string> follow_vec = source_vec;
    follow_vec.push_back(string(cols, 'X'));
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Result of original input should be same as input with extra row of 'X's */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 5: Removing the first row of the input matrix, then the output should be the same as the output of the modified matrix.
 *
 */
TEST_P(SurroundedRegionParamTest, MR5) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Remove the first row in the input matrix */
    vector<string> follow_vec(source_vec.begin() + 1, source_vec.end());
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Result of modified input (removed first row) should match original output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 6: Repeating the input matrix twice (concatenating with itself), then the output should remain the same as the original input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR6) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input by concatenating original input with itself */
    vector<string> follow_vec = source_vec;
    follow_vec.insert(follow_vec.end(), source_vec.begin(), source_vec.end());
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Repeating input matrix should not change the output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 7: Flipping the characters in each row of the input matrix (reversing each row), then the output should also have the characters in each row flipped.
 *
 */
TEST_P(SurroundedRegionParamTest, MR7) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input by reversing characters in each row */
    vector<string> follow_vec = source_vec;
    for (auto& row : follow_vec) {
        reverse(row.begin(), row.end());
    }
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Result of reversing each row characters in input should match reversed output */
    for (auto& row : source_out) {
        reverse(row.begin(), row.end());
    }
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 8: Transposing the input matrix (interchanging rows and columns), then the output should also be transposed.
 *
 */
TEST_P(SurroundedRegionParamTest, MR8) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input as transpose of source input */
    vector<string> follow_vec(source_vec[0].size(), string(source_vec.size(), ' '));
    for (size_t i = 0; i < source_vec.size(); i++) {
        for (size_t j = 0; j < source_vec[i].size(); j++) {
            follow_vec[j][i] = source_vec[i][j];
        }
    }
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Result of transposing input should match transposed output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 9: Adding a border of 'X's around the input matrix, then the output should remain the same as the original input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR9) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input by adding a border of 'X's around original input */
    int rows = source_vec.size();
    int cols = source_vec[0].size();
    vector<string> follow_vec;
    follow_vec.push_back(string(cols + 2, 'X'));
    for (const auto& row : source_vec) {
        follow_vec.push_back("X" + row + "X");
    }
    follow_vec.push_back(string(cols + 2, 'X'));
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Adding border of 'X's around input should not change the output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 10: Rotating the input matrix 90 degrees clockwise, then the output should also be rotated 90 degrees clockwise.
 *
 */
TEST_P(SurroundedRegionParamTest, MR10) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input by rotating original input 90 degrees clockwise */
    vector<string> follow_vec(source_vec[0].size(), string(source_vec.size(), ' '));
    for (size_t i = 0; i < source_vec.size(); i++) {
        for (size_t j = 0; j < source_vec[i].size(); j++) {
            follow_vec[j][source_vec.size() - 1 - i] = source_vec[i][j];
        }
    }
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Result of rotating input should match rotated output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 11: Scaling the input matrix by doubling the width and height, then the output should remain the same as the original input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR11) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input by doubling the width and height of original input with additional 'O's */
    vector<string> follow_vec;
    for (auto row : source_vec) {
        follow_vec.push_back(row + row);
    }
    for (auto row : source_vec) {
        follow_vec.push_back(row + row);
    }
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Doubling the input size should not change the output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 12: Replacing all characters of the input matrix with a single character 'O', then the output should also have all characters replaced with 'O'.
 *
 */
TEST_P(SurroundedRegionParamTest, MR12) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input by replacing all characters with 'O' */
    vector<string> follow_vec;
    for (auto row : source_vec) {
        follow_vec.push_back(string(row.size(), 'O'));
    }
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Result of replacing all characters with 'O' in input should match output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 13: Swapping rows in the input matrix, then the output should also have the rows swapped accordingly.
 *
 */
TEST_P(SurroundedRegionParamTest, MR13) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input by swapping the first and last rows of original input */
    vector<string> follow_vec = source_vec;
    swap(follow_vec.front(), follow_vec.back());
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Result of swapping rows in input should match swapped output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 14: Reversing the order of columns in the input matrix, then the output should also have the columns reversed accordingly.
 *
 */
TEST_P(SurroundedRegionParamTest, MR14) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input by reversing the order of columns in original input */
    vector<string> follow_vec;
    for (const auto& row : source_vec) {
        follow_vec.push_back(string(row.rbegin(), row.rend()));
    }
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Result of reversing columns in input should match reversed output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 15: Removing every second row from the input matrix, then the output should also be the modified accordingly.
 *
 */
TEST_P(SurroundedRegionParamTest, MR15) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Remove every second row from the input matrix */
    vector<string> follow_vec;
    for (size_t i = 0; i < source_vec.size(); i += 2) {
        follow_vec.push_back(source_vec[i]);
    }
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Result of removing every second row from input should match modified output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 16: Permuting the rows of the input matrix, then the output should also be the permuted accordingly.
 *
 */
TEST_P(SurroundedRegionParamTest, MR16) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Permute the rows of the input matrix */
    vector<string> follow_vec = source_vec;
    random_shuffle(follow_vec.begin(), follow_vec.end());
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Result of permuting rows in input should match permuted output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 17: Reversing the order of columns in the input matrix, then the output should also have the columns reversed accordingly.
 *
 */
TEST_P(SurroundedRegionParamTest, MR17) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input by reversing the order of columns in the original input */
    vector<string> follow_vec;
    for (const auto& row : source_vec) {
        follow_vec.push_back(string(row.rbegin(), row.rend()));
    }
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Result of reversing columns in the input should match reversed output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 18: Adding a column of 'O's to the input matrix, then the output should remain unchanged.
 *
 */
TEST_P(SurroundedRegionParamTest, MR18) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input by adding a column of 'O's to the original input */
    vector<string> follow_vec;
    for (const auto& row : source_vec) {
        follow_vec.push_back(row + "O");
    }
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Result of adding a column of 'O's to the input should remain unchanged */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 19: Replacing all 'O's with 'X' in the input matrix, then the output should also have all 'O's replaced with 'X'.
 *
 */
TEST_P(SurroundedRegionParamTest, MR19) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Replace 'O's with 'X' in source input */
    for (auto& row : source_vec) {
        replace(row.begin(), row.end(), 'O', 'X');
    }
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Verification: Output of source input with 'O's replaced by 'X' should match output of original input */
    for (auto& row : source_out) {
        replace(row.begin(), row.end(), 'O', 'X');
    }
    EXPECT_EQ(source_out, source_out);
}

/**
 * @brief Metamorphic Relation 20: Adding a row of 'X's to the input matrix, then the output should remain the same as the original input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR20) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input by adding a row of 'X's to the original input */
    int cols = source_vec[0].length();
    vector<string> follow_vec = source_vec;
    follow_vec.push_back(string(cols, 'X'));
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Result of original input should be same as input with extra row of 'X's */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 21: Permuting the rows and columns of the input matrix, then the output should also be permuted accordingly.
 *
 */
TEST_P(SurroundedRegionParamTest, MR21) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Permute the rows of the input matrix */
    vector<string> follow_vec = source_vec;
    random_shuffle(follow_vec.begin(), follow_vec.end());
    for (auto &row : follow_vec) {
        random_shuffle(row.begin(), row.end());
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification: Result of permuting rows and columns in input should match permuted output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 22: Replacing all 'X's with 'O' in the input matrix, then the output should also have all 'X's replaced with 'O'.
 *
 */
TEST_P(SurroundedRegionParamTest, MR22) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Replace 'X's with 'O' in source input */
    for (auto& row : source_vec) {
        replace(row.begin(), row.end(), 'X', 'O');
    }

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Verification: Output of source input with 'X's replaced by 'O' should match output of original input */
    for (auto& row : source_out) {
        replace(row.begin(), row.end(), 'X', 'O');
    }
    EXPECT_EQ(source_out, source_out);
}

/**
 * @brief Metamorphic Relation 23: Rotating the input matrix 180 degrees, then the output should also be rotated 180 degrees.
 *
 */
TEST_P(SurroundedRegionParamTest, MR23) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by rotating original input 180 degrees */
    vector<string> follow_vec(source_vec.rbegin(), source_vec.rend());
    for (auto &row : follow_vec) {
        reverse(row.begin(), row.end());
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification: Result of rotating input 180 degrees should match rotated output */
    EXPECT_EQ(follow_out, source_out);
}

//fixed
/**
 * @brief Metamorphic Relation 24: Replacing all 'O's in the input matrix with 'X' and vice versa, then the output should remain unchanged.
 *
 */
TEST_P(SurroundedRegionParamTest, MR24) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Replace 'O's with 'X' and 'X's with 'O' in source input */
    for (auto &row : source_vec) {
        for (char &ch : row) {
            if (ch == 'O') {
                ch = 'X';
            } else if (ch == 'X') {
                ch = 'O';
            }
        }
    }

    /* Get source output */
    //vector<string> source_out = surrounded_region(source_vec);

    /* Get follow output */
    vector<string> follow_out = surrounded_region(source_vec);

    /* Verification: Output of source input with 'O's and 'X's swapped should match output of original input */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 25: Adding an empty row to the input matrix, then the output should remain the same as the original input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR25) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by adding an empty row to the original input */
    int cols = source_vec[0].length();
    vector<string> follow_vec = source_vec;
    follow_vec.push_back(string(cols, ' '));

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification: Result of original input should be same as input with extra empty row */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 26: Removing the last column from the input matrix, then the output should remain the same as the original input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR26) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Remove the last column from the input matrix */
    vector<string> follow_vec;
    for (auto &row : source_vec) {
        follow_vec.push_back(row.substr(0, row.size() - 1));
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification: Result of modified input (removed last column) should match original output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 27: Replacing all characters in the input matrix with a single character 'X', then the output should also have all characters replaced with 'X'.
 *
 */
TEST_P(SurroundedRegionParamTest, MR27) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by replacing all characters with 'X' */
    vector<string> follow_vec;
    for (size_t i = 0; i < source_vec.size(); i++) {
        string row = "";
        for (size_t j = 0; j < source_vec[i].size(); j++) {
            row += "X";
        }
        follow_vec.push_back(row);
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification: Result of replacing all characters with 'X' in input should match output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 28: Removing the first column from the input matrix, then the output should remain the same as the original input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR28) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Remove the first column from the input matrix */
    vector<string> follow_vec;
    for (auto &row : source_vec) {
        follow_vec.push_back(row.substr(1, row.size() - 1));
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification: Result of modified input (removed first column) should match original output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 29: Reversing the rows of the input matrix, then the output should also have the rows reversed accordingly.
 *
 */
TEST_P(SurroundedRegionParamTest, MR29) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by reversing the order of rows in the original input */
    vector<string> follow_vec(source_vec.rbegin(), source_vec.rend());

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification: Result of reversing rows in input should match reversed output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 30: Removing every second column from the input matrix, then the output should remain the same as the original input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR30) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Remove every second column from the input matrix */
    vector<string> follow_vec;
    for (size_t i = 0; i < source_vec.size(); i++) {
        string row;
        for (size_t j = 0; j < source_vec[i].size(); j += 2) {
            row += source_vec[i][j];
        }
        follow_vec.push_back(row);
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification: Result of removing every second column from input should match original output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 31: Replacing all 'O's in the input matrix with 'X' and vice versa, then the output should also have 'O's and 'X's swapped accordingly.
 *
 */
TEST_P(SurroundedRegionParamTest, MR31) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by swapping 'O's and 'X's */
    for (auto &row : source_vec) {
        for (char &ch : row) {
            if (ch == 'O') {
                ch = 'X';
            } else if (ch == 'X') {
                ch = 'O';
            }
        }
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(source_vec);

    /* Verification: Result of swapping 'O's and 'X's in input should match modified output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 32: Adding a column of 'O's to the input matrix, then the output should remain the same as the original input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR32) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by adding a column of 'O's to the original input */
    vector<string> follow_vec;
    for (auto &row : source_vec) {
        follow_vec.push_back(row + "O");
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification: Result of original input should remain the same as input with extra column of 'O's */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 33: Doubling the input matrix by repeating each row, then the output should remain the same as the original input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR33) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by repeating each row of the original input */
    vector<string> follow_vec;
    for (auto &row : source_vec) {
        follow_vec.push_back(row + row);
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification: Result of repeating each row in input should remain unchanged */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 34: Removing every second row and column from the input matrix, then the output should remain the same as the original input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR34) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Remove every second row and column from the input matrix */
    vector<string> follow_vec;
    for (size_t i = 0; i < source_vec.size(); i += 2) {
        string row;
        for (size_t j = 0; j < source_vec[i].size(); j += 2) {
            row += source_vec[i][j];
        }
        follow_vec.push_back(row);
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification: Result of removing every second row and column from input should match original output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 35: Converting all characters in the input matrix to uppercase, then the output should remain the same as the original input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR35) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input by converting all characters to uppercase */
    vector<string> follow_vec = source_vec;
    for (auto& row : follow_vec) {
        transform(row.begin(), row.end(), row.begin(), ::toupper);
    }
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Result of converting characters to uppercase should match original output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 36: Converting all characters in the input matrix to lowercase, then the output should remain the same as the original input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR36) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input by converting all characters to lowercase */
    vector<string> follow_vec = source_vec;
    for (auto& row : follow_vec) {
        transform(row.begin(), row.end(), row.begin(), ::tolower);
    }
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Result of converting characters to lowercase should match original output */
    EXPECT_EQ(follow_out, source_out);
}

//fixed
/**
 * @brief Metamorphic Relation 37: Multiplying all characters in the input matrix by a number, then the output should remain the same as the original input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR37) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input by multiplying all characters by a number */
    //vector<string> follow_vec = source_vec;  // No change in characters
    vector<string> follow_vec;  
    int multiplier = 2;
    for (const auto& str : source_vec) {
        string multiplied_str;
        for (char ch : str) {
            multiplied_str += string(ch * multiplier, ch);
        }
        follow_vec.push_back(multiplied_str);
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Result of multiplying characters by a number should match original output */
    EXPECT_EQ(follow_out, source_out);
}

//fixed
/**
 * @brief Metamorphic Relation 38: Replacing all characters in the input matrix with a specific set of characters, then the output should remain the same as the original input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR38) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input by replacing all characters with a specific set of characters */
    //vector<string> follow_vec = source_vec;  // No change in characters
    vector<string> follow_vec;  
    for (const auto& str : source_vec) {
        string replaced_str;
        for (char ch : str) {
            replaced_str += 'X';
        }
        follow_vec.push_back(replaced_str);
    }
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Result of replacing characters with a specific set should match original output */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 39: Adding a column of 'X's to the end of the input matrix, then the output should remain the same as the original input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR39) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input by adding a column of 'X's to the original input */
    vector<string> follow_vec;
    for (auto &row : source_vec) {
        row.push_back('X');
        follow_vec.push_back(row);
    }
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Result of original input should remain the same as input with extra column of 'X's */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 40: Interchanging the rows and columns of the input matrix, then the output should remain the same as the original input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR40) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);
    
    /* Construct follow-up input as the transpose of the source input */
    vector<string> follow_vec(source_vec[0].size(), string(source_vec.size(), ' '));
    for (size_t i = 0; i < source_vec.size(); i++) {
        for (size_t j = 0; j < source_vec[i].size(); j++) {
            follow_vec[j][i] = source_vec[i][j];
        }
    }
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);
    
    /* Verification: Result of interchanging rows and columns of the input should match original output */
    EXPECT_EQ(follow_out, source_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, SurroundedRegionParamTest, testing::ValuesIn(gen_tcs_randomly()));