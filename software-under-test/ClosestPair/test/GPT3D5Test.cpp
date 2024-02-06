#include <gtest/gtest.h>
#include <vector>
#include <random>
#include <algorithm>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class ClosestPairParamTest : public ::testing::TestWithParam<ClosestPairInput> {};

/**
 * @brief Metamorphic relation 1: If the input points are translated by a constant vector, the output should remain the same.
 *
 */
TEST_P(ClosestPairParamTest, MR1) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    for (auto &point : vec) {
        follow_vec.push_back({point.first + 5, point.second + 5});  // Translate each point by a constant vector
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 2: If the order of the input points is changed, the output should remain the same.
 *
 */
TEST_P(ClosestPairParamTest, MR2) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec = vec;
    random_shuffle(follow_vec.begin(), follow_vec.end());  // Change the order of points

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 3: If all points are scaled by a constant factor, the output should be scaled by the same factor.
 *
 */
TEST_P(ClosestPairParamTest, MR3) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    for (auto &point : vec) {
        follow_vec.push_back({2 * point.first, 2 * point.second});  // Scale each point by a constant factor
    }

    /* Calculate expected output */
    float expected_follow_out = 2 * source_out;  // Expected follow-up output, scaled by the same factor

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(expected_follow_out, follow_out);
}

/**
 * @brief Metamorphic relation 4: If the input points are reversed along the x-axis, the output should remain the same.
 *
 */
TEST_P(ClosestPairParamTest, MR4) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    for (auto &point : vec) {
        follow_vec.push_back({-point.first, point.second});  // Reverse each point along the x-axis
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 5: If the input points are shifted along the y-axis, the output should remain the same.
 *
 */
TEST_P(ClosestPairParamTest, MR5) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    for (auto &point : vec) {
        follow_vec.push_back({point.first, point.second + 100});  // Shift each point along the y-axis
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 6: Adding a point inside the boundary defined by the original points should not increase the minimum distance.
 *
 */
TEST_P(ClosestPairParamTest, MR6) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec = vec;
    // Insert a point at the centroid of the given points
    int sumX = 0, sumY = 0;
    for (auto &point : vec) {
        sumX += point.first;
        sumY += point.second;
    }
    follow_vec.push_back({sumX / vec.size(), sumY / vec.size()});

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_GE(source_out, follow_out);  /* Fix */
}

/**
 * @brief Metamorphic relation 7: If the input points are duplicated, the output should remain the same.
 *
 */
TEST_P(ClosestPairParamTest, MR7) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec = vec;
    // Duplicate the input points
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.end());

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 8: If all points are shifted in the same direction by a constant distance, the output should remain the same.
 *
 */
TEST_P(ClosestPairParamTest, MR8) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    int shiftDistance = 10;  // Constant shift distance
    for (auto &point : vec) {
        follow_vec.push_back({point.first + shiftDistance, point.second + shiftDistance});  // Shift each point in the same direction
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 9: If the input points form a convex hull, adding any new point inside or on the boundary of the convex hull should not increase the minimum distance.
 *
 */
TEST_P(ClosestPairParamTest, MR9) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec = vec;
    // Add a new point inside the convex hull of the original points
    // For simplicity, the centroid of the points can be considered to be inside the convex hull in many cases
    int sumX = 0, sumY = 0;
    for (auto &point : vec) {
        sumX += point.first;
        sumY += point.second;
    }
    follow_vec.push_back({sumX / vec.size(), sumY / vec.size()});

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_GE(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 10: If the input points are restricted to lie on a straight line, the output should remain the same.
 *
 */
TEST_P(ClosestPairParamTest, MR10) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    // Make all points lie on a straight line
    int yValue = vec[0].second;  // Change all y-coordinates to be the same
    for (auto &point : vec) {
        follow_vec.push_back({point.first, yValue});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 11: If the input points are all on the same horizontal line, the output should remain the same.
 *
 */
TEST_P(ClosestPairParamTest, MR11) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    // Make all points lie on the same horizontal line
    int x = vec[0].first;  // Take the x-coordinate of the first point
    for (auto &point : vec) {
        follow_vec.push_back({x, point.second});  // Change x-coordinate to be the same
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 12: If the input points are all on the same vertical line, the output should remain the same.
 *
 */
TEST_P(ClosestPairParamTest, MR12) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    // Make all points lie on the same vertical line
    int y = vec[0].second;  // Take the y-coordinate of the first point
    for (auto &point : vec) {
        follow_vec.push_back({point.first, y});  // Change y-coordinate to be the same
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 13: If the points are randomly shuffled, the output should remain the same.
 *
 */
TEST_P(ClosestPairParamTest, MR13) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Shuffle the input points */
    random_shuffle(vec.begin(), vec.end());

    /* Get follow-up output */
    float follow_out = closest_distance(vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 14: If the input points are rotated about their centroid, the output should remain the same.
 *
 */
TEST_P(ClosestPairParamTest, MR14) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Calculate centroid of the points */
    int sumX = 0, sumY = 0;
    for (auto &point : vec) {
        sumX += point.first;
        sumY += point.second;
    }
    int centroidX = sumX / vec.size();
    int centroidY = sumY / vec.size();

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Rotate the points about their centroid */
    vector<pair<int, int>> follow_vec;
    for (auto &point : vec) {
        int x = point.first;
        int y = point.second;
        // Perform a 90-degree clockwise rotation
        int newX = centroidX + (y - centroidY);
        int newY = centroidY - (x - centroidX);
        follow_vec.push_back({newX, newY});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 15: If the input contains duplicate points, removing duplicates should not change the output.
 *
 */
TEST_P(ClosestPairParamTest, MR15) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    // Introduce duplicate points
    vec.push_back(vec[0]);
    vec.push_back(vec[1]);

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Remove duplicates */
    set<pair<int, int>> unique_set(vec.begin(), vec.end());
    vec.assign(unique_set.begin(), unique_set.end());

    /* Get follow-up output */
    float follow_out = closest_distance(vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 16: If the input points are halved such that only every other point is considered, the output should remain the same.
 *
 */
TEST_P(ClosestPairParamTest, MR16) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input with every other point */
    vector<pair<int, int>> follow_vec;
    for (int i = 0; i < vec.size(); i += 2) {
        follow_vec.push_back(vec[i]);  // Use only every other point
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 17: If all points are shifted to the same origin, the output should remain the same.
 *
 */
TEST_P(ClosestPairParamTest, MR17) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);
    
    /* Calculate the centroid of the points */
    int sumX = 0, sumY = 0;
    for (auto &point : vec) {
        sumX += point.first;
        sumY += point.second;
    }
    int centroidX = sumX / vec.size();
    int centroidY = sumY / vec.size();

    /* Construct follow-up input with shift points */
    vector<pair<int, int>> follow_vec;
    for (auto &point : vec) {
        follow_vec.push_back({point.first - centroidX, point.second - centroidY});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 18: If the input points are replaced with their negations, the output should remain the same.
 *
 */
TEST_P(ClosestPairParamTest, MR18) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input with negated points */
    vector<pair<int, int>> follow_vec;
    for (auto &point : vec) {
        follow_vec.push_back({-point.first, -point.second});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 19: If the input points are rotated around the origin, the output should remain the same.
 *
 */
TEST_P(ClosestPairParamTest, MR19) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Rotate the points around the origin */
    vector<pair<int, int>> follow_vec;
    for (auto &point : vec) {
        int x = point.first;
        int y = point.second;
        // Perform a 90-degree counter-clockwise rotation
        int newX = -y;
        int newY = x;
        follow_vec.push_back({newX, newY});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 20: If a scalar value is added to all x-coordinates of the input points, the output should not change.
 *
 */
TEST_P(ClosestPairParamTest, MR20) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);
    
    /* Construct follow-up input */
    int scalar = 10;  // Scalar value to be added to x-coordinates
    vector<pair<int, int>> follow_vec;
    for (auto &point : vec) {
        follow_vec.push_back({point.first + scalar, point.second});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 21: If a scalar value is added to all y-coordinates of the input points, the output should not change.
 *
 */
TEST_P(ClosestPairParamTest, MR21) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);
    
    /* Construct follow-up input */
    int scalar = 10;  // Scalar value to be added to y-coordinates
    vector<pair<int, int>> follow_vec;
    for (auto &point : vec) {
        follow_vec.push_back({point.first, point.second + scalar});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 22: If the x-coordinates of the input points are replaced by their absolute values, the output should not change.
 *
 */
TEST_P(ClosestPairParamTest, MR22) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);
    
    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    for (auto &point : vec) {
        follow_vec.push_back({abs(point.first), point.second});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 23: If the y-coordinates of the input points are replaced by their absolute values, the output should not change.
 *
 */
TEST_P(ClosestPairParamTest, MR23) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);
    
    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    for (auto &point : vec) {
        follow_vec.push_back({point.first, abs(point.second)});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 24: If the x-coordinates of the input points are replaced by their squares, the output should not change.
 *
 */
TEST_P(ClosestPairParamTest, MR24) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);
    
    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    for (auto &point : vec) {
        follow_vec.push_back({point.first * point.first, point.second});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 25: If the y-coordinates of the input points are replaced by their squares, the output should not change.
 *
 */
TEST_P(ClosestPairParamTest, MR25) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);
    
    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    for (auto &point : vec) {
        follow_vec.push_back({point.first, point.second * point.second});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 26: If the x-coordinates and y-coordinates are swapped for all points, the output should not change.
 *
 */
TEST_P(ClosestPairParamTest, MR26) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    for (auto &point : vec) {
        follow_vec.push_back({point.second, point.first});  // Swap x and y coordinates
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 27: If all x-coordinates are increased by a constant, the minimum distance should not change.
 */
TEST_P(ClosestPairParamTest, MR27) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    int shiftValue = 10;  // Constant shift value
    for (auto &point : vec) {
        follow_vec.push_back({point.first + shiftValue, point.second}); // Increase all x-coordinates by a constant
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 28: If all y-coordinates are increased by a constant, the minimum distance should not change.
 */
TEST_P(ClosestPairParamTest, MR28) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    int shiftValue = 10;  // Constant shift value
    for (auto &point : vec) {
        follow_vec.push_back({point.first, point.second + shiftValue}); // Increase all y-coordinates by a constant
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 29: If all x-coordinates and y-coordinates are non-negatively increased by a constant, the minimum distance should not decrease.
 */
TEST_P(ClosestPairParamTest, MR29) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    int shiftValue = 10;  // Constant shift value
    for (auto &point : vec) {
        follow_vec.push_back({max(0, point.first + shiftValue), max(0, point.second + shiftValue)}); // Increase all coordinates non-negatively by a constant
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_LE(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 30: If all x-coordinates and y-coordinates are non-positively decreased by a constant, the minimum distance should not increase.
 */
TEST_P(ClosestPairParamTest, MR30) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    int shiftValue = 10;  // Constant shift value
    for (auto &point : vec) {
        follow_vec.push_back({min(0, point.first - shiftValue), min(0, point.second - shiftValue)}); // Decrease all coordinates non-positively by a constant
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_GE(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 31: If the original points are mirrored about the x-axis, the minimum distance should not change.
 */
TEST_P(ClosestPairParamTest, MR31) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input with mirrored points about the x-axis */
    vector<pair<int, int>> follow_vec;
    for (auto &point : vec) {
        follow_vec.push_back({point.first, -point.second});  // Mirror original points about the x-axis
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 32: If the original points are mirrored about the y-axis, the minimum distance should not change.
 */
TEST_P(ClosestPairParamTest, MR32) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input with mirrored points about the y-axis */
    vector<pair<int, int>> follow_vec;
    for (auto &point : vec) {
        follow_vec.push_back({-point.first, point.second});  // Mirror original points about the y-axis
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 33: If the original points are mirrored about the origin, the minimum distance should not change.
 */
TEST_P(ClosestPairParamTest, MR33) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input with mirrored points about the origin */
    vector<pair<int, int>> follow_vec;
    for (auto &point : vec) {
        follow_vec.push_back({-point.first, -point.second});  // Mirror original points about the origin
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 34: If the original points are randomly perturbed within a small range, the minimum distance should remain the same.
 */
TEST_P(ClosestPairParamTest, MR34) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Define the perturbation range */
    int range = 5;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Perturb the original points within a small range */
    vector<pair<int, int>> follow_vec;
    for (auto &point : vec) {
        int perturbX = point.first + (rand() % (2*range + 1)) - range;
        int perturbY = point.second + (rand() % (2*range + 1)) - range;
        follow_vec.push_back({perturbX, perturbY});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 35: If the original points are slightly rotated, the minimum distance should not change significantly.
 */
TEST_P(ClosestPairParamTest, MR35) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Rotate the points slightly */
    vector<pair<int, int>> follow_vec;
    double angle = 0.1; // small angle in radians
    for (auto &point : vec) {
        int x = point.first;
        int y = point.second;
        int newX = x * cos(angle) - y * sin(angle);
        int newY = x * sin(angle) + y * cos(angle);
        follow_vec.push_back({newX, newY});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_NEAR(source_out, follow_out, 0.001);  // Allowing a small error
}

/**
 * @brief Metamorphic relation 36: If the original points are scaled by a constant factor, the minimum distance should be scaled by the same factor.
 */
TEST_P(ClosestPairParamTest, MR36) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Scale the original points by a constant factor */
    vector<pair<int, int>> follow_vec;
    int scaleFactor = 2; // constant scale factor
    for (auto &point : vec) {
        int newX = point.first * scaleFactor;
        int newY = point.second * scaleFactor;
        follow_vec.push_back({newX, newY});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out * scaleFactor, follow_out);
}

/**
 * @brief Metamorphic relation 37: If the original points are sheared by a factor, the minimum distance should not change.
 */
TEST_P(ClosestPairParamTest, MR37) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Shear the original points by a factor */
    vector<pair<int, int>> follow_vec;
    double shearFactor = 0.5; // constant shear factor
    for (auto &point : vec) {
        int newX = point.first + shearFactor * point.second;
        follow_vec.push_back({newX, point.second});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 38: If the original points are uniformly randomly scattered, the minimum distance should not significantly change.
 */
TEST_P(ClosestPairParamTest, MR38) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Define the scatter range */
    int scatterRange = 20;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Scatter the original points uniformly */
    vector<pair<int, int>> follow_vec;
    for (auto &point : vec) {
        int perturbX = point.first + (rand() % (2*scatterRange + 1)) - scatterRange;
        int perturbY = point.second + (rand() % (2*scatterRange + 1)) - scatterRange;
        follow_vec.push_back({perturbX, perturbY});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_NEAR(source_out, follow_out, 10);  // Allowing a small error
}

/**
 * @brief Metamorphic relation 39: If the original points are shifted or translated by a vector, the minimum distance should not change.
 */
TEST_P(ClosestPairParamTest, MR39) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Translate the original points by a vector */
    vector<pair<int, int>> follow_vec;
    pair<int, int> translationVector = make_pair(5, 5);
    for (auto &point : vec) {
        int newX = point.first + translationVector.first;
        int newY = point.second + translationVector.second;
        follow_vec.push_back({newX, newY});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 40: If a subset of the original points is considered, the minimum distance should not increase.
 */
TEST_P(ClosestPairParamTest, MR40) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    // Considering only the first half of the points
    vector<pair<int, int>> subset_vec(vec.begin(), vec.begin() + vec.size() / 2);

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Get follow-up output */
    float follow_out = closest_distance(subset_vec);

    /* Verification */
    EXPECT_LE(source_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, ClosestPairParamTest, testing::ValuesIn(gen_tcs_randomly()));