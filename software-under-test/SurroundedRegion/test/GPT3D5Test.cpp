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
 * @brief Metamorphic Relation 4: If the input board contains only a single 'O', the output should remain the same as the input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR4) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec; // Follow-up input is the same as the source input
    follow_vec[0][0] = 'O'; // Change the original 'X' to 'O' in the follow-up input
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 5: If all 'O's are surrounded by 'X's in the original board, then the output should remain unchanged.
 *
 */
TEST_P(SurroundedRegionParamTest, MR5) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Verification */
    EXPECT_EQ(surrounded_region(source_out), source_out);
}

/**
 * @brief Metamorphic Relation 6: If the original input board and the follow-up input board are identical, then the original output and follow-up output should also be identical.
 *
 */
TEST_P(SurroundedRegionParamTest, MR6) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(source_vec); // Follow-up output is obtained from the same input as the original output

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 7: If all 'O's are already on the border of the board, then the output should remain the same as the input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR7) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec; // Follow-up input is the same as the source input
    for (auto& row : follow_vec) {
        if (row[0] == 'O') row[0] = 'X'; // Flip the 'O's on the borders to 'X's in the follow-up input
        if (row.back() == 'O') row.back() = 'X'; // Flip the 'O's on the borders to 'X's in the follow-up input
    }
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 8: If the input board is empty (contains no 'O's), the output should also be an empty board.
 *
 */
TEST_P(SurroundedRegionParamTest, MR8) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec; // Empty input board
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Verification */
    EXPECT_TRUE(source_out.empty());
}

/**
 * @brief Metamorphic Relation 9: If all cells on the board contain 'X', then the output should also contain 'X's only.
 *
 */
TEST_P(SurroundedRegionParamTest, MR9) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;
    // Convert all 'O's to 'X's in the source input
    for (auto& row : source_vec) {
        for (char& cell : row) {
            if (cell == 'O') cell = 'X';
        }
    }

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Verification */
    EXPECT_EQ(source_out, source_vec);
}
/**
 * @brief Metamorphic Relation 10: If the input board consists of a single row or a single column, the output should remain the same as the input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR10) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec; // Follow-up input is the same as the source input
    if (follow_vec.size() == 1 || follow_vec[0].size() == 1) { // If the input board consists of a single row or a single column
        // Add or remove 'O's in the follow-up input to test consistency of output
        follow_vec[0][0] = (follow_vec[0][0] == 'O') ? 'X' : 'O';
    }
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 11: If the input board contains a single enclosed region with 'O's, and the size of the region changes, then the output should reflect the change in size of the enclosed region.
 *
 */
TEST_P(SurroundedRegionParamTest, MR11) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Modify the enclosed region by adding or removing 'O's
    follow_vec[1][1] = (follow_vec[1][1] == 'O') ? 'X' : 'O'; // Change the status of a cell within the enclosed region
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_NE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 12: If the input board consists of multiple enclosed regions with 'O's, and the regions are repositioned within the board, then the output should reflect the repositioning of the enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR12) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Mix the enclosed regions by swapping the positions of 'O's
    swap(follow_vec[1][1], follow_vec[2][2]);

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_NE(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 13: If the input board is a symmetric board, the output should also be symmetric with respect to the same axis of symmetry.
 *
 */
TEST_P(SurroundedRegionParamTest, MR13) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Make the follow-up input symmetric along the horizontal axis
    reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    reverse(follow_out.begin(), follow_out.end());
    EXPECT_EQ(follow_out, source_out);
}

/* Fix by Radon */
vector<string> rotate_output_90_degrees_counterclockwise(vector<string> output) {
    vector<string> rotated_output(output[0].size(), string(output.size(), ' '));
    for (size_t i = 0; i < output.size(); ++i) {
        for (size_t j = 0; j < output[i].size(); ++j) {
            rotated_output[output[i].size() - 1 - j][i] = output[i][j];
        }
    }
    return rotated_output;
}

/**
 * @brief Metamorphic Relation 14: If the input board is a rotation of another input board, the output should also be a rotation of the output corresponding to the original input.
 *
 */
TEST_P(SurroundedRegionParamTest, MR14) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Rotate the follow-up input 90 degrees counterclockwise
    vector<string> rotated_vec(source_vec[0].size(), string(source_vec.size(), ' '));
    for (size_t i = 0; i < source_vec.size(); ++i) {
        for (size_t j = 0; j < source_vec[i].size(); ++j) {
            rotated_vec[source_vec[i].size() - 1 - j][i] = source_vec[i][j];
        }
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(rotated_vec);

    /* Verification */
    EXPECT_EQ(rotate_output_90_degrees_counterclockwise(source_out), follow_out);
}

/**
 * @brief Metamorphic Relation 15: If the input board contains a mixture of 'O's and 'X's, and the positions of 'O's are permuted within the board, the output should remain unchanged.
 *
 */
TEST_P(SurroundedRegionParamTest, MR15) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Permute the positions of 'O's within the input board
    for (auto& row : follow_vec) {
        random_shuffle(row.begin(), row.end());
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 16: If a row or column in the input board contains consecutive 'O's, and the number of consecutive 'O's changes, then the output should reflect the change in the number of consecutive 'O's.
 *
 */
TEST_P(SurroundedRegionParamTest, MR16) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Modify the number of consecutive 'O's in a row
    follow_vec[1][1] = (follow_vec[1][1] == 'O') ? 'X' : 'O'; // Change the status of a cell within a row with consecutive 'O's

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_NE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 17: If the input board contains isolated 'O's, adding or removing isolated 'O's should not change the output.
 *
 */
TEST_P(SurroundedRegionParamTest, MR17) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Add an isolated 'O' in the follow-up input
    follow_vec[1][1] = 'O';

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 18: If the input board contains a mixture of 'X's and 'O's, and the positions of 'X's are permuted within the board, the output should remain unchanged.
 *
 */
TEST_P(SurroundedRegionParamTest, MR18) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Permute the positions of 'X's within the input board
    for (auto& row : follow_vec) {
        random_shuffle(row.begin(), row.end());
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 19: If the input board contains a single enclosed region with 'O's, and the region is expanded or contracted, then the output should reflect the change in the size and shape of the enclosed region.
 *
 */
TEST_P(SurroundedRegionParamTest, MR19) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Expand or contract the enclosed region by adding or removing 'O's
    follow_vec[1][2] = (follow_vec[1][2] == 'O') ? 'X' : 'O'; // Change the status of a cell within the enclosed region
    
    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_NE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 20: If the input board contains only a single cell, the output should remain unchanged because there are no enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR20) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = { "O" }; // Single cell input
    
    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Verification */
    EXPECT_EQ(surrounded_region(source_out), source_out);
}
/**
 * @brief Metamorphic Relation 21: If the input board contains regions where all 'O's are surrounded by 'X's but are not directly connected to each other, the output should remain unchanged.
 *
 */
TEST_P(SurroundedRegionParamTest, MR21) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Verification */
    EXPECT_EQ(surrounded_region(source_out), source_out);
}

/**
 * @brief Metamorphic Relation 22: If the input board contains regions where two or more enclosed regions are directly connected, the output should still contain separate enclosed regions after the transformation.
 *
 */
TEST_P(SurroundedRegionParamTest, MR22) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Combine two enclosed regions to make them directly connected
    follow_vec[1][1] = 'O';
    follow_vec[1][2] = 'O';
    follow_vec[2][1] = 'O';
    follow_vec[2][2] = 'O';

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_NE(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 23: If the input board contains an enclosed region with a hole inside, the output should still contain the same enclosed region with the hole inside after the transformation.
 *
 */
TEST_P(SurroundedRegionParamTest, MR23) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Create a hole inside the enclosed region
    follow_vec[1][1] = 'X';
    follow_vec[1][2] = 'X';
    follow_vec[2][1] = 'X';
    follow_vec[2][2] = 'X';
    follow_vec[2][3] = 'O';

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_NE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 24: If the input board contains regions where 'O's form shapes other than rectangular or square, such as L-shapes, T-shapes, or irregular shapes, the output should still contain the same shapes after the transformation.
 *
 */
TEST_P(SurroundedRegionParamTest, MR24) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Create non-rectangular or non-square shapes
    follow_vec[1][1] = 'O';
    follow_vec[1][2] = 'O';
    follow_vec[2][2] = 'O';

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 25: If the input board contains only a single row or single column with 'O's, the output should remain unchanged after the transformation.
 *
 */
TEST_P(SurroundedRegionParamTest, MR25) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Create a single row or single column with 'O's
    if (follow_vec.size() == 1) {
        follow_vec.push_back(follow_vec[0]);
    } else {
        for (auto& row : follow_vec) {
            row += row;
        }
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 26: If the input board consists of a chessboard-like pattern of 'O's and 'X's, the output should also consist of the same chessboard-like pattern after the transformation.
 *
 */
TEST_P(SurroundedRegionParamTest, MR26) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Create a chessboard-like pattern
    for (int i = 0; i < follow_vec.size(); i++) {
        for (int j = 0; j < follow_vec[i].size(); j++) {
            if ((i + j) % 2 == 0) {
                follow_vec[i][j] = 'O';
            }
        }
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 27: If the input board contains a single enclosed region with 'O's, and the region is filled completely with 'X's, the output should consist of 'X's only.
 *
 */
TEST_P(SurroundedRegionParamTest, MR27) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Fill the enclosed region completely with 'X's
    for (size_t i = 1; i < follow_vec.size() - 1; ++i) {
        for (size_t j = 1; j < follow_vec[i].size() - 1; ++j) {
            follow_vec[i][j] = 'X';
        }
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    for (auto& row : follow_vec) {
        for (char& cell : row) {
            EXPECT_EQ(cell, 'X');
        }
    }
    EXPECT_EQ(follow_out, follow_vec);
}

/**
 * @brief Metamorphic Relation 28: If the input board contains a single enclosed region with 'O's, and the region is completely surrounded by 'X's, the output should remain unchanged.
 *
 */
TEST_P(SurroundedRegionParamTest, MR28) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Completely surround the enclosed region with 'X's
    for (size_t j = 0; j < follow_vec[0].size(); ++j) {
        follow_vec[0][j] = 'X';
        follow_vec[follow_vec.size()-1][j] = 'X';
    }
    for (size_t i = 0; i < follow_vec.size(); ++i) {
        follow_vec[i][0] = 'X';
        follow_vec[i][follow_vec[i].size()-1] = 'X';
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 29: If the input board is mirrored along the vertical axis, the output should also be mirrored along the vertical axis.
 *
 */
TEST_P(SurroundedRegionParamTest, MR29) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    // Vertically mirror the source input
    vector<string> vertical_mirrored_vec = source_vec;
    for (auto& row : vertical_mirrored_vec) {
        reverse(row.begin(), row.end());
    }

    /* Get vertical mirrored output */
    vector<string> vertical_mirrored_out = surrounded_region(vertical_mirrored_vec);

    /* Verification */
    EXPECT_EQ(vertical_mirrored_out, source_out);
}

/**
 * @brief Metamorphic Relation 30: If the input board is mirrored along the horizontal axis, the output should also be mirrored along the horizontal axis.
 *
 */
TEST_P(SurroundedRegionParamTest, MR30) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    // Horizontally mirror the source input
    vector<string> horizontal_mirrored_vec = source_vec;
    reverse(horizontal_mirrored_vec.begin(), horizontal_mirrored_vec.end());

    /* Get horizontal mirrored output */
    vector<string> horizontal_mirrored_out = surrounded_region(horizontal_mirrored_vec);

    /* Verification */
    EXPECT_EQ(horizontal_mirrored_out, source_out);
}
/**
 * @brief Metamorphic Relation 31: If the input board contains a single enclosed region with 'O's along the region borders, the output should remain unchanged.
 *
 */
TEST_P(SurroundedRegionParamTest, MR31) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Move the 'O's to the borders of the enclosed region
    for (size_t i = 1; i < follow_vec.size() - 1; ++i) {
        follow_vec[i][1] = 'O';
        follow_vec[i][follow_vec[i].size() - 2] = 'O';
    }
    for (size_t j = 1; j < follow_vec[0].size() - 1; ++j) {
        follow_vec[1][j] = 'O';
        follow_vec[follow_vec.size() - 2][j] = 'O';
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 32: If the input board contains a single enclosed region with 'O's in the shape of a cross, the output should consist of 'X's only, and no change should be made.
 *
 */
TEST_P(SurroundedRegionParamTest, MR32) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Create a cross shape with 'O's
    size_t center_row = source_vec.size() / 2;
    size_t center_col = source_vec[0].size() / 2;
    for (size_t i = 0; i < source_vec.size(); ++i) {
        follow_vec[i][center_col] = 'O';
    }
    for (size_t j = 0; j < source_vec[0].size(); ++j) {
        follow_vec[center_row][j] = 'O';
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    for (auto& row : follow_out) {
        for (char cell : row) {
            EXPECT_EQ(cell, 'X');
        }
    }
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 33: If the input board contains a single enclosed region with 'O's in the shape of a square, the output should consist of 'X's only, and no change should be made.
 *
 */
TEST_P(SurroundedRegionParamTest, MR33) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Create a square shape with 'O's
    size_t start_row = source_vec.size() / 4;
    size_t start_col = source_vec[0].size() / 4;
    size_t end_row = start_row * 3;
    size_t end_col = start_col * 3;
    for (size_t i = start_row; i <= end_row; ++i) {
        follow_vec[i][start_col] = 'O';
        follow_vec[i][end_col] = 'O';
    }
    for (size_t j = start_col; j <= end_col; ++j) {
        follow_vec[start_row][j] = 'O';
        follow_vec[end_row][j] = 'O';
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    for (auto& row : follow_out) {
        for (char cell : row) {
            EXPECT_EQ(cell, 'X');
        }
    }
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 34: If the input board contains a single enclosed region with 'O's forming a straight line, the output should consist of 'X's only, and no change should be made.
 *
 */
TEST_P(SurroundedRegionParamTest, MR34) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Create a straight line shape with 'O's
    size_t center_row = source_vec.size() / 2;
    for (size_t j = 0; j < source_vec[0].size(); ++j) {
        follow_vec[center_row][j] = 'O';
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    for (auto& row : follow_out) {
        for (char cell : row) {
            EXPECT_EQ(cell, 'X');
        }
    }
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 35: If the input board contains a single enclosed region with 'O's forming a diagonal line, the output should consist of 'X's only, and no change should be made.
 *
 */
TEST_P(SurroundedRegionParamTest, MR35) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Create a diagonal line shape with 'O's
    for (size_t i = 0; i < follow_vec.size(); ++i) {
        follow_vec[i][i] = 'O';
    }

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    for (auto& row : follow_out) {
        for (char cell : row) {
            EXPECT_EQ(cell, 'X');
        }
    }
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 36: If the input board contains a single enclosed region with 'O's forming an irregular shape, the output should consist of 'X's only, and no change should be made.
 *
 */
TEST_P(SurroundedRegionParamTest, MR36) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Create an irregular shape with 'O's
    follow_vec[1][1] = 'O';
    follow_vec[1][2] = 'O';
    follow_vec[2][3] = 'O';
    follow_vec[3][2] = 'O';

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    for (auto& row : follow_out) {
        for (char cell : row) {
            EXPECT_EQ(cell, 'X');
        }
    }
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 37: If the input board has multiple enclosed regions with 'O's, and the regions are merged, the output should reflect the merged enclosed region.
 *
 */
TEST_P(SurroundedRegionParamTest, MR37) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Merge multiple enclosed regions
    follow_vec[1][1] = 'O';
    follow_vec[1][2] = 'O';
    follow_vec[2][1] = 'O';
    follow_vec[2][2] = 'O';
    follow_vec[3][3] = 'O';

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_NE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 38: If the input board has multiple isolated 'O's that are not part of an enclosed region, adding or removing isolated 'O's should not change the output.
 *
 */
TEST_P(SurroundedRegionParamTest, MR38) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Add an isolated 'O' in the follow-up input
    follow_vec[1][1] = 'O';

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 39: If the input board contains a single enclosed region with 'O's and additional 'O's are added inside the region, the output should reflect the addition of the 'O's inside the region.
 *
 */
TEST_P(SurroundedRegionParamTest, MR39) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Add additional 'O's inside the enclosed region
    follow_vec[1][1] = 'O';
    follow_vec[1][2] = 'O';

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_NE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 40: If the input board contains a single enclosed region with 'O's, and some 'O's are removed from inside the region, the output should reflect the removal of the 'O's inside the region.
 *
 */
TEST_P(SurroundedRegionParamTest, MR40) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Remove some 'O's from inside the enclosed region
    follow_vec[1][1] = 'X';

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_NE(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 41: If the input board contains two enclosed regions with 'O's, if the two regions are merged into a single enclosed region, the output should reflect the merged enclosed region.
 *
 */
TEST_P(SurroundedRegionParamTest, MR41) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Merge two enclosed regions into a single enclosed region
    follow_vec[1][1] = 'O';
    follow_vec[1][2] = 'O';

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_NE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 42: If the input board contains two enclosed regions with 'O's, if the two regions are split into separate enclosed regions, the output should reflect the separate enclosed regions.
 *
 */
TEST_P(SurroundedRegionParamTest, MR42) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    // Split a single enclosed region into two separate enclosed regions
    follow_vec[1][1] = 'O';
    follow_vec[follow_vec.size()-2][1] = 'O';

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_NE(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 43: If the input board contains a single enclosed region with 'O's, if the shape of the region is altered, the output should reflect the altered shape of the enclosed region.
 *
 */
TEST_P(SurroundedRegionParamTest, MR43) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;

    // Alter the shape of the enclosed region
    follow_vec[1][1] = 'O';
    follow_vec[1][2] = 'O';
    follow_vec[2][1] = 'O';

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    EXPECT_NE(follow_out, source_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, SurroundedRegionParamTest, testing::ValuesIn(gen_tcs_randomly()));