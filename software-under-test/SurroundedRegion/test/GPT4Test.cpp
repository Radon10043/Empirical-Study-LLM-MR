#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class SurroundedRegionParamTest : public ::testing::TestWithParam<SurroundedRegionInput> {};

#if 0
/**
 * @brief Metamorphic Relation 3: Flipping the matrix vertically (inverting each row), should not change the enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR3) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    for (auto &row : follow_vec) {
        reverse(row.begin(), row.end());
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    for (auto &row : source_out) {
        reverse(row.begin(), row.end());
    }
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 4: Filling all four borders with 'X's, any 'O's not already enclosed should become enclosed and thus converted to 'X's.
 *
 */
TEST_P(SurroundedRegionParamTest, MR4) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    int rows = follow_vec.size();
    int cols = follow_vec[0].length();
    for (int i = 0; i < rows; i++) {
        follow_vec[i][0] = 'X';
        follow_vec[i][cols - 1] = 'X';
    }
    follow_vec[0] = string(cols, 'X');
    follow_vec[rows - 1] = string(cols, 'X');

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_NE(follow_out, source_out); // Assuming source has 'O's touching borders
    // Check every originally enclosed 'O' is now an 'X'
    for (int i = 0; i < source_out.size(); ++i) {
        for (int j = 0; j < source_out[i].length(); ++j) {
            if (source_vec[i][j] == 'O' && source_out[i][j] == 'X') {
                EXPECT_EQ(follow_out[i][j], 'X');
            }
        }
    }
}

/**
 * @brief Metamorphic Relation 5: Rotating the matrix 180 degrees should not change the enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR5) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    std::reverse(follow_vec.begin(), follow_vec.end());
    for (auto &row : follow_vec) {
        reverse(row.begin(), row.end());
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    std::reverse(source_out.begin(), source_out.end());
    for (auto &row : source_out) {
        reverse(row.begin(), row.end());
    }
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 6: Replacing a non-boundary 'X' with 'O' and 'O' with 'X' shouldn't change the enclosed regions status.
 *
 */
TEST_P(SurroundedRegionParamTest, MR6) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by inverting an 'X' and 'O' in non-boundary locations */
    int mid_row = source_vec.size() / 2;
    int mid_col = source_vec[0].length() / 2;
    vector<string> follow_vec = source_vec;
    follow_vec[mid_row][mid_col] = follow_vec[mid_row][mid_col] == 'X' ? 'O' : 'X';

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification - Non-boundary changes should not affect enclosed regions */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 7: Transposing the matrix should not affect the status of the enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR7) { // Fixed
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by transposing the matrix */
    vector<string> follow_vec(source_vec[0].size(), std::string(source_vec.size(), ' ')); // Dimensions switched
    for (size_t i = 0; i < source_vec.size(); ++i) {
        for (size_t j = 0; j < source_vec[0].size(); ++j) {
            follow_vec[j][i] = source_vec[i][j];
        }
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Transpose the source output for comparison */
    vector<string> transposed_source_out(follow_vec.size(), std::string(follow_vec[0].size(), ' '));
    for (size_t i = 0; i < source_out.size(); ++i) {
        for (size_t j = 0; j < source_out[0].size(); ++j) {
            transposed_source_out[j][i] = source_out[i][j];
        }
    }

    /* Verification */
    EXPECT_EQ(follow_out, transposed_source_out);
}

/**
 * @brief Metamorphic Relation 8: Adding a frame of 'X's around the entire matrix should not change the inner enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR8) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input with a frame of 'X's */
    vector<string> follow_vec;
    int source_rows = source_vec.size();
    int source_cols = source_vec[0].size();
    follow_vec.push_back(string(source_cols + 2, 'X')); // top frame
    for (const auto &row : source_vec) {
        follow_vec.push_back('X' + row + 'X'); // left and right frames
    }
    follow_vec.push_back(string(source_cols + 2, 'X')); // bottom frame

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    for (int i = 1; i <= source_rows; ++i) {
        for (int j = 1; j <= source_cols; ++j) {
            EXPECT_EQ(follow_out[i][j], source_out[i - 1][j - 1]);
        }
    }
}

/**
 * @brief Metamorphic Relation 9: Replacing all non-boundary 'O's with 'X' and all 'X's with 'O' should invert the status of the enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR9) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by inverting X's and O's in non-boundary cells */
    vector<string> follow_vec = source_vec;
    for (size_t i = 1; i < source_vec.size() - 1; ++i) {
        for (size_t j = 1; j < source_vec[i].size() - 1; ++j) {
            follow_vec[i][j] = follow_vec[i][j] == 'X' ? 'O' : 'X';
        }
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Inverting source_out except for boundaries to see if enclosed regions have inverted status */
    for (size_t i = 1; i < source_out.size() - 1; ++i) {
        for (size_t j = 1; j < source_out[i].size() - 1; ++j) {
            if (source_vec[i][j] != source_out[i][j]) { // originally enclosed region
                source_out[i][j] = follow_vec[i][j];
            }
        }
    }

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 10: Swapping two non-boundary rows should not affect the status of the enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR10) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by swapping two non-boundary rows */
    vector<string> follow_vec = source_vec;
    std::swap(follow_vec[1], follow_vec[2]);

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    std::swap(source_out[1], source_out[2]);
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 11: Inverting the entire matrix ('X' becomes 'O' and 'O' becomes 'X') should not alter the result after inversion.
 *
 */
TEST_P(SurroundedRegionParamTest, MR11) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by inverting the whole matrix */
    vector<string> follow_vec = source_vec;
    for (auto &row : follow_vec) {
        for (auto &ch : row) {
            ch = ch == 'X' ? 'O' : 'X';
        }
    }

    /* Invert the source output for comparison */
    vector<string> source_out_inverted = source_out;
    for (auto &row : source_out_inverted) {
        for (auto &ch : row) {
            ch = ch == 'X' ? 'O' : 'X';
        }
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Invert the follow-up output for comparison */
    for (auto &row : follow_out) {
        for (auto &ch : row) {
            ch = ch == 'X' ? 'O' : 'X';
        }
    }

    /* Verification */
    EXPECT_EQ(follow_out, source_out_inverted);
}

/**
 * @brief Metamorphic Relation 12: Duplicating each row should not change the status of the originally enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR12) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by duplicating each row */
    vector<string> follow_vec;
    for (auto &row : source_vec) {
        follow_vec.push_back(row);
        follow_vec.push_back(row); // duplicate row
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification - check every second row of follow_out should match the original source_out */
    for (size_t i = 0; i < source_out.size(); ++i) {
        EXPECT_EQ(follow_out[i * 2], source_out[i]);
    }
}

/**
 * @brief Metamorphic Relation 13: Duplicating the matrix vertically should maintain enclosed regions on both halves.
 *
 */
TEST_P(SurroundedRegionParamTest, MR13) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by duplicating the matrix vertically */
    vector<string> follow_vec = source_vec;
    follow_vec.insert(follow_vec.end(), source_vec.begin(), source_vec.end()); // duplicate the matrix

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out.size(), 2 * source_out.size()); // follow_out should be twice as long
    for (size_t i = 0; i < source_out.size(); ++i) {
        EXPECT_EQ(follow_out[i], source_out[i]);                     // upper half should match
        EXPECT_EQ(follow_out[i + source_out.size()], source_out[i]); // lower half should match
    }
}

/**
 * @brief Metamorphic Relation 14: Adding 'X's at random non-boundary positions should not turn 'O's at non-boundary enclosed regions into 'X's.
 *
 */
TEST_P(SurroundedRegionParamTest, MR14) { // Fixed
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by adding 'X's at random non-boundary positions */
    int m = source_vec.size(), n = source_vec[0].size();
    if (m < 2 || n < 2) {
        GTEST_SKIP() << "Matrix is too small for this test";
    }

    vector<string> follow_vec = source_vec;
    follow_vec.insert(follow_vec.end() - 1, string(n, 'X')); // Insert 'X's at the 2nd last row

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    source_out.insert(source_out.end() - 1, string(n, 'X')); // Manually setting the same 'X' in the expected output
    EXPECT_EQ(follow_out, source_out);                       // Results should be the same for enclosed regions
}

/**
 * @brief Metamorphic Relation 15: Removing 'X's from non-boundary positions that are not enclosing 'O's should not change the result if no 'O's were enclosed
 * by the removed 'X's.
 *
 */
TEST_P(SurroundedRegionParamTest, MR15) {
#if 0
    /* Get source input */
    vector<string> source_vec = {"XXXXX", "XOOOX", "XXXOX", "XOOOX", "XXXXX"};

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by removing a non-enclosing 'X' from a non-boundary position */
    vector<string> follow_vec = source_vec;
    follow_vec[2][3] = 'O'; // This 'X' does not enclose any 'O'

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    source_out[2][3] = 'O'; // Manually setting the same 'O' in the expected output for consistency
    EXPECT_EQ(follow_out, source_out);
#endif
}

/**
 * @brief Metamorphic Relation 16: Expanding the matrix uniformly (e.g., adding a buffer of 'X's around the existing matrix) should not affect the status of the
 * existing enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR16) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by expanding the matrix uniformly */
    int col_num = source_vec[0].size();
    vector<string> expanded_vec = source_vec;
    for (auto &row : expanded_vec) {
        row = "X" + row + "X";
    }
    expanded_vec.insert(expanded_vec.begin(), string(col_num + 2, 'X'));
    expanded_vec.push_back(string(col_num + 2, 'X'));

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(expanded_vec);

    /* Verification - check the enclosed regions of the original matrix within the expanded one */
    for (size_t i = 1; i < source_out.size() + 1; ++i) {
        for (size_t j = 1; j < source_out[0].size() + 1; ++j) {
            EXPECT_EQ(follow_out[i][j], source_out[i - 1][j - 1]);
        }
    }
}

/**
 * @brief Metamorphic Relation 17: Reflecting the matrix along the main diagonal (transpose) should preserve the enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR17) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by reflecting the matrix along the main diagonal */
    vector<string> follow_vec(source_vec[0].size(), string(source_vec.size(), 'X'));
    for (size_t i = 0; i < source_vec.size(); ++i) {
        for (size_t j = 0; j < source_vec[i].size(); ++j) {
            follow_vec[j][i] = source_vec[i][j];
        }
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Reflect the source_out along the main diagonal for verification */
    vector<string> reflected_source_out(source_out[0].size(), string(source_out.size(), 'X'));
    for (size_t i = 0; i < source_out.size(); ++i) {
        for (size_t j = 0; j < source_out[i].size(); ++j) {
            reflected_source_out[j][i] = source_out[i][j];
        }
    }

    /* Verification */
    EXPECT_EQ(follow_out, reflected_source_out);
}

/**
 * @brief Metamorphic Relation 18: Scaling the matrix by multiplying each cell should not affect the status of the enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR18) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by scaling the matrix (2x here as an example) */
    vector<string> scaled_vec;

    for (auto &row : source_vec) {
        string new_row;
        for (char &ch : row) {
            new_row.append(2, ch); // Append each character twice
        }
        scaled_vec.push_back(new_row);
        scaled_vec.push_back(new_row); // Duplicate the row
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(scaled_vec);

    /* Verification */
    int scale = 2; // Scale factor
    for (size_t i = 0; i < source_out.size(); ++i) {
        for (size_t j = 0; j < source_out[0].size(); ++j) {
            char expected_char = source_out[i][j];
            // Check all cells that represent the same position in the scaled matrix
            for (int m = 0; m < scale; ++m) {
                for (int n = 0; n < scale; ++n) {
                    EXPECT_EQ(follow_out[i * scale + m][j * scale + n], expected_char);
                }
            }
        }
    }
}

/**
 * @brief Metamorphic Relation 19: Removing a 'non-enclosing' row should not change the status of the remaining enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR19) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Choose and remove a 'non-enclosing' row from the matrix */
    source_vec.erase(source_vec.begin() + 3); // Erases the 4th row, which does not enclose any 'O's

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(source_vec);

    /* Verification */
    // The source output should match the follow-up output, except for the missing row
    source_out.erase(source_out.begin() + 3); // Similarly, erase the 4th row for the output verification
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 20: Reversing the entire matrix order should not affect the status of the enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR20) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by reversing the order of the rows */
    vector<string> follow_vec = source_vec;
    std::reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Reverse the order of the rows in source_out */
    std::reverse(source_out.begin(), source_out.end());

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 21: Removing a 'non-enclosing' column should not change the status of the remaining enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR21) {
#if 0
    /* Get source input */
    vector<string> source_vec = {"XXXXX", "XOOOX", "XXXXX", "XXOXX", "XXXXX"};

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by removing a 'non-enclosing' column */
    vector<string> follow_vec = source_vec;
    for (string& row : follow_vec) {
        row.erase(row.begin() + 2); // Remove the 3rd column from each row
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    // The source output should match the follow-up output, except for the missing column
    for (string& row : source_out) {
        row.erase(row.begin() + 2); // Similarly, remove the 3rd column
    }
    EXPECT_EQ(follow_out, source_out);
#endif
}

/**
 * @brief Metamorphic Relation 22: Swapping two non-boundary columns should not affect the status of the enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR22) {   // Fixed
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    if (source_vec.size() < 5) {
        GTEST_SKIP() << "Matrix is too small for this test";
    }

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by swapping two non-boundary columns */
    vector<string> follow_vec = source_vec;
    for (string &row : follow_vec) {
        std::swap(row[1], row[3]); // Swap the 2nd and 4th columns
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    for (string &row : source_out) {
        std::swap(row[1], row[3]); // Swap the 2nd and 4th columns in the expected output
    }
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 23: Removing a 'non-enclosing' corner should not change the status of the remaining enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR23) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by removing a 'non-enclosing' corner, in this case, the bottom right */
    vector<string> follow_vec = source_vec;
    for (string &row : follow_vec) {
        row.pop_back();
    }
    follow_vec.pop_back();

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    // Adjust source_out by removing the last character of each row and the last row itself
    for (string &row : source_out) {
        row.pop_back();
    }
    source_out.pop_back();
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 24: Inserting a completely enclosed row of 'X's should not affect the status of the existing enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR24) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Insert a completely enclosed row of 'X's */
    string new_row(source_vec[0].length(), 'X');
    source_vec.insert(source_vec.begin() + 2, new_row); // Insert after the second row

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(source_vec);

    /* Verification */
    string new_out_row(source_out[0].length(), 'X');
    source_out.insert(source_out.begin() + 2, new_out_row); // Expected: similar insertion in the output
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 25: Moving an enclosed region to another location surrounded by 'X's should preserve its status.
 *
 */
TEST_P(SurroundedRegionParamTest, MR25) {
#if 0
    /* Get source input */
    vector<string> source_vec = {"XXXXX", "XOOOX", "XXXXX", "XXXOX", "XOXOX"};

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by moving the second row down by two rows */
    vector<string> follow_vec = source_vec;
    std::swap(follow_vec[1], follow_vec[3]);

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification - enclose region should maintain its status after move */
    // Swap the corresponding rows in the expected output
    std::swap(source_out[1], source_out[3]);
    EXPECT_EQ(follow_out, source_out);
#endif
}

/**
 * @brief Metamorphic Relation 26: Adding a row of 'X's within the matrix should not affect the status of the existing enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR26) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input by adding a new row of 'X's within the matrix */
    string new_row = string(source_vec[0].length(), 'X');
    source_vec.insert(source_vec.begin() + 2, new_row); // Add the new row after the second existing row

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(source_vec);

    /* Verification */
    // The source output should match the follow-up output, except with an additional row of 'X's
    source_out.insert(source_out.begin() + 2, new_row);
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 27: Rotating the matrix by 90 degrees clockwise should not change the enclosed regions' statuses.
 *
 */
TEST_P(SurroundedRegionParamTest, MR27) {   // Fixed
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Rotate the source input matrix by 90 degrees clockwise */
    vector<string> follow_vec(source_vec[0].size(), string(source_vec.size(), ' '));
    int m = source_vec.size(), n = source_vec[0].size();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            follow_vec[j][m - 1 - i] = source_vec[i][j];
        }
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Rotate the source_out matrix by 90 degrees clockwise for comparison */
    vector<string> rotated_source_out(follow_vec.size(), string(follow_vec[0].size(), ' '));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            rotated_source_out[j][m - 1 - i] = source_out[i][j];
        }
    }

    /* Verification */
    EXPECT_EQ(follow_out, rotated_source_out);
}

/**
 * @brief Metamorphic Relation 28: Converting all the 'O's to 'X's on the boundary should convert any path-connected 'O's to 'X's in output.
 *
 */
TEST_P(SurroundedRegionParamTest, MR28) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output before altering the boundaries */
    vector<string> source_out = surrounded_region(source_vec);

    /* Convert all boundary 'O's to 'X's in the source input */
    int rows = source_vec.size();
    int cols = source_vec[0].length();
    for (int i = 0; i < cols; ++i) {
        source_vec[0][i] = source_vec[rows - 1][i] = 'X'; // Top and bottom rows
    }
    for (int i = 0; i < rows; ++i) {
        source_vec[i][0] = source_vec[i][cols - 1] = 'X'; // Left and right columns
    }

    /* Get follow-up output after converting boundary 'O's to 'X's */
    vector<string> follow_out = surrounded_region(source_vec);

    /* Fill any 'O's that were path-connected to the boundary with 'X's in the original source output */
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                source_out[i][j] = 'X'; // Convert boundary
            }
        }
    }

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 29: Inverting the status of all cells (boundary 'X's become 'O's and vice versa) should result in a complete inversion of the
 * output matrix.
 *
 */
TEST_P(SurroundedRegionParamTest, MR29) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Invert the status of all cells in the source matrix */
    for (string &row : source_vec) {
        for (char &ch : row) {
            ch = (ch == 'X') ? 'O' : 'X';
        }
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(source_vec);

    /* Invert the status of all cells in the source_out matrix for comparison */
    for (string &row : source_out) {
        for (char &ch : row) {
            ch = (ch == 'X') ? 'O' : 'X';
        }
    }

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 30: Increasing the size of the matrix uniformly by adding a border of 'O's should result in all the original 'O's getting
 * converted to 'X's in the enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR30) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Increase the size of matrix by adding border of 'O's */
    vector<string> follow_vec;
    follow_vec.push_back(string(source_vec[0].length() + 2, 'O')); // Top border
    for (const string &row : source_vec) {
        follow_vec.push_back('O' + row + 'O'); // Left and right borders
    }
    follow_vec.push_back(string(source_vec[0].length() + 2, 'O')); // Bottom border

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification - all enclosed regions should now be 'X's */
    // Create a new expected result with a border and all the original 'O's converted to 'X's
    vector<string> expected_out;
    expected_out.push_back(string(source_out[0].length() + 2, 'O')); // adjusted Top border
    for (const string &row : source_out) {
        string new_row = "O"; // Left border
        for (char ch : row) {
            new_row += (ch == 'O') ? 'X' : ch; // Convert original 'O's to 'X'
        }
        new_row += 'O'; // Right border
        expected_out.push_back(new_row);
    }
    expected_out.push_back(string(source_out[0].length() + 2, 'O')); // adjusted Bottom border
    EXPECT_EQ(follow_out, expected_out);
}

/**
 * @brief Metamorphic Relation 31: Replacing an 'O' on the boundary with 'X' should potentially convert 'O's inside the matrix that were connected to it.
 *
 */
TEST_P(SurroundedRegionParamTest, MR31) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Replace an 'O' on the boundary with 'X' */
    source_vec[0][1] = 'X'; // Replace 2nd cell of the first row on the boundary

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(source_vec);

    /* Verification - since an 'O' on the border was replaced, connected 'O's should now change */
    source_out[0][1] = 'X'; // Replace the same cell in the expected output
    // Additional verification for any 'O's connected to the replaced boundary 'O' should go here
    EXPECT_NE(follow_out, source_out); // The matrices should not be the same due to the replacement
}

/**
 * @brief Metamorphic Relation 32: Ensuring that a single 'O' completely surrounded by 'X's in a row gets replaced by 'X'.
 *
 */
TEST_P(SurroundedRegionParamTest, MR32) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Verification */
    // The single 'O' in the second row should now be an 'X'
    EXPECT_EQ(source_out[1][3], 'X');
}

/**
 * @brief Metamorphic Relation 33: Swapping consecutive rows where one is all 'X's and the other contains an enclosed region of 'O's, should not change the
 * status of the enclosed region.
 *
 */
TEST_P(SurroundedRegionParamTest, MR33) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Swap the 3rd all 'X's row with the 2nd row that contains an enclosed region */
    std::swap(source_vec[2], source_vec[3]);

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(source_vec);

    /* Verification */
    // Swapping rows in the output for comparison
    std::swap(source_out[2], source_out[3]);
    EXPECT_EQ(follow_out, source_out);
}
#endif

/**
 * @brief Metamorphic Relation 34: Inserting rows of 'X's intermittently should not alter the status of existing enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR34) {   // Fixed
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    if (source_vec.size() < 6) {
        GTEST_SKIP() << "Matrix is too small for this test";
    }

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Insert a row of 'X's after the first row */
    source_vec.insert(source_vec.begin() + 1, string(source_vec[0].length(), 'X'));

    /* Insert another row of 'X's further down */
    source_vec.insert(source_vec.begin() + 4, string(source_vec[0].length(), 'X'));

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(source_vec);

    /* Insert corresponding rows of 'X's in the expected output array for comparison */
    source_out.insert(source_out.begin() + 1, string(source_out[0].length(), 'X'));
    source_out.insert(source_out.begin() + 4, string(source_out[0].length(), 'X'));

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 35: Replacing an 'X' that is part of an enclosing boundary with 'O' should result in changing the enclosed 'O' to 'X'.
 *
 */
TEST_P(SurroundedRegionParamTest, MR35) {
#if 0
    /* Get source input */
    vector<string> source_vec = {"XXXXXX", "XOOOXX", "XXXXXX"};

    /* Get source output before changing the enclosing 'X' */
    vector<string> source_out = surrounded_region(source_vec);

    /* Replace an 'X' that is part of the enclosing boundary with 'O' */
    source_vec[1][5] = 'O';

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(source_vec);

    /* Change the corresponding 'O' in the expected output array to 'X' for comparison */
    source_out[1][1] = source_out[1][2] = source_out[1][3] = 'X';

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
#endif
}

/**
 * @brief Metamorphic Relation 36: Replacing all 'X's within the matrix with 'O's, while keeping the boundary 'X's intact, should result in no 'O's in the
 * output, as they would all be surrounded.
 *
 */
TEST_P(SurroundedRegionParamTest, MR36) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get follow-up output after changing inner 'X's to 'O's */
    for (int i = 1; i < source_vec.size() - 1; ++i) {
        for (int j = 1; j < source_vec[i].length() - 1; ++j) {
            source_vec[i][j] = 'O';
        }
    }
    vector<string> follow_out = surrounded_region(source_vec);

    /* Verification - all 'O's (now at interior positions) should be 'X's in the output */
    for (int i = 1; i < follow_out.size() - 1; ++i) {
        for (int j = 1; j < follow_out[i].length() - 1; ++j) {
            EXPECT_EQ(follow_out[i][j], 'X');
        }
    }
}

/**
 * @brief Metamorphic Relation 37: Mirroring the matrix horizontally should not alter the status of enclosed regions of 'O's.
 *
 */
TEST_P(SurroundedRegionParamTest, MR37) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Mirror the matrix horizontally */
    for (auto &row : source_vec) {
        std::reverse(row.begin(), row.end());
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(source_vec);

    /* Mirror the expected output horizontally for comparison */
    for (auto &row : source_out) {
        std::reverse(row.begin(), row.end());
    }

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 38: Connecting two previously disjoint enclosed regions by a line of 'X's should leave their status unchanged.
 *
 */
TEST_P(SurroundedRegionParamTest, MR38) {
#if 0
    /* Get source input */
    vector<string> source_vec = {"XXXXXXX", "XOOOXOX", "XXXXXXX", "XOXOOOX", "XXXXXXX"};

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Connect the two enclosed 'O' regions by a vertical line of 'X's, which does not interfere with their status */
    for (int i = 1; i < source_vec.size() - 1; ++i) {
        source_vec[i][3] = 'X';
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(source_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
#endif
}

/**
 * @brief Metamorphic Relation 39: Adding padding of 'O's to a row should not affect the surrounded status of 'O's within the internal region of the matrix.
 *
 */
TEST_P(SurroundedRegionParamTest, MR39) { // Fixed
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    if (source_vec.size() < 2) {
        GTEST_SKIP() << "Matrix is too small for this test";
    }

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Add padding of 'O's to a middle row that is already surrounded */
    int m = source_vec.size(), n = source_vec[0].size();
    string new_row(n, 'O');
    source_vec.insert(source_vec.begin() + 1, new_row); // Insert after the first 

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(source_vec);

    /* Verification */
    // Adding padding 'O's should not change the result - the middle 'O's remain surrounded
    vector<string> expected_out = source_out;
    expected_out.insert(expected_out.begin() + 1, new_row);
    EXPECT_EQ(follow_out, expected_out);
}

/**
 * @brief Metamorphic Relation 40: Filling in a diagonal with 'X's that does not touch the boundary should not change the status of existing enclosed 'O's.
 *
 */
TEST_P(SurroundedRegionParamTest, MR40) { // Fixed
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    if (source_vec.size() < 3 || source_vec.size() != source_vec[0].size()) {
        GTEST_SKIP() << "Matrix is too small for this test";
    }

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Fill in a diagonal with 'X's */
    for (int i = 1; i < source_vec.size(); ++i) {
        source_vec[i][i] = 'X';
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(source_vec);

    /* Verification */
    // Diagonal fill with 'X's should not change the result, the 'O' remains surrounded
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 41: Adding a row and a column of 'X's should not affect the status of inner enclosed 'O's.
 *
 */
TEST_P(SurroundedRegionParamTest, MR41) {
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    vector<string> source_out = surrounded_region(source_vec);

    // Adding a row of 'X's at the top
    source_vec.insert(source_vec.begin(), string(source_vec[0].length(), 'X'));
    // Adding a column of 'X's at the front
    for (auto &row : source_vec) {
        row = "X" + row;
    }

    vector<string> follow_out = surrounded_region(source_vec);

    // Since we added a row at the beginning, we should expect an additional 'X' row in the output comparison
    source_out.insert(source_out.begin(), string(source_out[0].length(), 'X'));
    // The additional column of 'X's should also be reflected in the comparison
    for (auto &row : source_out) {
        row = "X" + row;
    }

    // Verification
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 42: Altering non-enclosed 'O's to 'X's should not affect enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR42) {
#if 0
    vector<string> source_vec = {"XOXOX", "OXOXO", "XOXOX", "OXOXO", "XOXOX"};
    vector<string> source_out = surrounded_region(source_vec);

    // Converting the non-enclosed 'O's to 'X's
    source_vec[1][0] = source_vec[1][4] = 'X';

    vector<string> follow_out = surrounded_region(source_vec);

    // Verification
    source_out[1][0] = source_out[1][4] = 'X';
    EXPECT_EQ(follow_out, source_out);
#endif
}

INSTANTIATE_TEST_CASE_P(TrueReturn, SurroundedRegionParamTest, testing::ValuesIn(gen_tcs_randomly()));