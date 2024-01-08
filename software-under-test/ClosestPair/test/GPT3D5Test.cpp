#include <gtest/gtest.h>
#include <vector>
#include <random>
#include <algorithm>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class ClosestPairParamTest : public ::testing::TestWithParam<ClosestPairInput> {};

/*  修改说吗:
    1. point_set 替换为 vec
    2. set<pair<int,int> 替换为 vector<pair<int, int>>
    3. vec.insert 替换为 vec.push_back
 */

/**
 * @brief Metamorphic relation 2: Reversing the order of the points should not change the distance of the closest pair of points.
 *
 */
TEST_P(ClosestPairParamTest, MR2) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec(vec.rbegin(), vec.rend());

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 3: Scaling all the points by a certain factor should scale the closest distance by the same factor.
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
    for (const auto& point : vec) {
        follow_vec.push_back({point.first * 2, point.second * 2});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out * 2, follow_out);
}

/**
 * @brief Metamorphic relation 4: Translating all the points by a certain vector should not change the distance of the closest pair of points.
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
    pair<int, int> translation_vector = {10, -5};
    for (const auto& point : vec) {
        follow_vec.push_back({point.first + translation_vector.first, point.second + translation_vector.second});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 5: Adding duplicate points to the set should not change the distance of the closest pair of points.
 *
 */
TEST_P(ClosestPairParamTest, MR5) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec = vec;
    follow_vec.push_back(*vec.begin());  // Inserting a duplicate point

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/* Implemented by Radon */
vector<pair<int, int>> addRandomNoise(vector<pair<int,int>> vec, int val) {
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(-val, val);
    for (auto& point : vec) {
        point.first += dist(rng);
        point.second += dist(rng);
    }
    return vec;
}

/**
 * @brief Metamorphic relation 6: Adding random noise to the points should not change the distance of the closest pair of points significantly.
 *
 */
TEST_P(ClosestPairParamTest, MR6) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec = addRandomNoise(vec, 5);  // Adding random noise within a range of 5

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_NEAR(source_out, follow_out, 1e-5);
}

/**
 * @brief Metamorphic relation 7: Removing a point from the set should not increase the distance of the closest pair of points.
 *
 */
TEST_P(ClosestPairParamTest, MR7) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

#if INVALID
    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec = vec;
    follow_vec.erase(*vec.begin());  // Removing a point
#else
    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec = vec;
    follow_vec.erase(follow_vec.begin());  // Removing a point
#endif

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_LE(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 8: Swapping two points in the set should not change the distance of the closest pair of points.
 *
 */
TEST_P(ClosestPairParamTest, MR8) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec = vec;
    auto it = follow_vec.begin();
    auto next_it = std::next(it);
    std::iter_swap(it, next_it);  // Swapping two points

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 9: Applying a scaling transformation to all points in the set should not change the relative distances between the points, and consequently should not change the distance of the closest pair of points.
 */
TEST_P(ClosestPairParamTest, MR9) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Find centroid of the points */
    pair<int, int> centroid = {0, 0};
    for (const auto& point : vec) {
        centroid.first += point.first;
        centroid.second += point.second;
    }
    centroid.first /= vec.size();
    centroid.second /= vec.size();

    /* Apply scaling transformation to all points relative to the centroid */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        int scaled_x = centroid.first + 2 * (point.first - centroid.first);
        int scaled_y = centroid.second + 2 * (point.second - centroid.second);
        follow_vec.push_back({scaled_x, scaled_y});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 10: Adding a constant value to all points in the set should not change the relative distances between the points, and consequently should not change the distance of the closest pair of points.
 */
TEST_P(ClosestPairParamTest, MR10) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Apply translation transformation to all points by a constant value */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        int translated_x = point.first + 5;
        int translated_y = point.second + 5;
        follow_vec.push_back({translated_x, translated_y});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 11: If we duplicate all the points and add them to the set, the distance of the closest pair of points should not change.
 */
TEST_P(ClosestPairParamTest, MR11) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by duplicating all points */
    vector<pair<int, int>> follow_vec = vec;
    for(const auto& point : vec) {
        follow_vec.push_back(point);
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 12: If we apply a horizontal reflection to all the points, the distance of the closest pair of points should not change.
 */
TEST_P(ClosestPairParamTest, MR12) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by applying a horizontal reflection to all points */
    vector<pair<int, int>> follow_vec;
    for(const auto& point : vec) {
        follow_vec.push_back({-point.first, point.second});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 13: If we sort the points in non-decreasing order of x-coordinate and then calculate the closest pair of points, the distance should not change.
 */
TEST_P(ClosestPairParamTest, MR13) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> point_vec(input.vec.begin(), input.vec.end());

    /* Sort the points in non-decreasing order of x-coordinate */
    sort(point_vec.begin(), point_vec.end());

    /* Get source output */
    float source_out = closest_distance(point_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, closest_distance(input.vec));
}

/**
 * @brief Metamorphic relation 14: If we rotate all the points about the origin by a certain angle, the distance of the closest pair of points should not change.
 */
TEST_P(ClosestPairParamTest, MR14) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    constexpr double pi = 3.14159265358979323846;
    constexpr double rotation_angle = pi / 6;  // Rotate by 30 degrees

    /* Rotate all the points about the origin */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        int new_x = static_cast<int>(point.first * cos(rotation_angle) - point.second * sin(rotation_angle) + 0.5);
        int new_y = static_cast<int>(point.first * sin(rotation_angle) + point.second * cos(rotation_angle) + 0.5);
        follow_vec.push_back({new_x, new_y});
    }

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 15: If we add a constant value to each x-coordinate of the points and recalculate the closest pair of points, the output should not change.
 */
TEST_P(ClosestPairParamTest, MR15) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;
    
    int deltaX = 5; // Constant to be added to x-coordinates
    
    /* Get source output */
    float source_out = closest_distance(vec);

    /* Get follow-up output after applying the transformation */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({point.first + deltaX, point.second});
    }
    
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 16: If we add a constant value to each y-coordinate of the points and recalculate the closest pair of points, the output should not change.
 */
TEST_P(ClosestPairParamTest, MR16) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;
    
    int deltaY = 5; // Constant to be added to y-coordinates
    
    /* Get source output */
    float source_out = closest_distance(vec);

    /* Get follow-up output after applying the transformation */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({point.first, point.second + deltaY});
    }
    
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 17: If we double the x-coordinate and y-coordinate of each point and recalculate the closest pair of points, the output should not change.
 */
TEST_P(ClosestPairParamTest, MR17) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Get follow-up output after doubling the coordinates of each point */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({2 * point.first, 2 * point.second});
    }

    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 18: If we square the x-coordinate and y-coordinate of each point and recalculate the closest pair of points, the output should not change.
 */
TEST_P(ClosestPairParamTest, MR18) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Get follow-up output after squaring the coordinates of each point */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({point.first * point.first, point.second * point.second});
    }

    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 19: If all y-coordinates of the points are negated and recalculate the closest pair of points, the distance should remain the same.
 */
TEST_P(ClosestPairParamTest, MR19) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Get follow-up output after negating the y-coordinates of each point */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({point.first, -point.second});
    }

    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 20: If all points are rotated 90 degrees counterclockwise, the distance of the closest pair of points should not change.
 */
TEST_P(ClosestPairParamTest, MR20) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Get follow-up output by rotating all points 90 degrees counterclockwise */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({-point.second, point.first});
    }

    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 21: If all the points are shifted along the x-axis by a constant value, the distance of the closest pair of points should not change.
 */
TEST_P(ClosestPairParamTest, MR21) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    int shiftValue = 10; // Constant value to shift the points along the x-axis

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Get follow-up output by shifting all points along the x-axis */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({point.first + shiftValue, point.second});
    }

    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 22: If all the points are shifted along the y-axis by a constant value, the distance of the closest pair of points should not change.
 */
TEST_P(ClosestPairParamTest, MR22) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    int shiftValue = 10; // Constant value to shift the points along the y-axis

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Get follow-up output by shifting all points along the y-axis */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({point.first, point.second + shiftValue});
    }

    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 23: If we replace every point p(x, y) with p(-x, y) and recalculate the closest pair of points, the output should remain the same.
 */
TEST_P(ClosestPairParamTest, MR23) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Get follow-up output after replacing every point p(x, y) with p(-x, y) */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({-point.first, point.second});
    }

    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 24: If we replace every point p(x, y) with p(x, -y) and recalculate the closest pair of points, the output should remain the same.
 */
TEST_P(ClosestPairParamTest, MR24) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Get follow-up output after replacing every point p(x, y) with p(x, -y) */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({point.first, -point.second});
    }

    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 25: If we add a constant value to each x-coordinate and subtract the same constant value from each y-coordinate of the points, the closest pair of points should not change.
 */
TEST_P(ClosestPairParamTest, MR25) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;
    
    int constant = 5; // Constant value to be added to x-coordinate and subtracted from y-coordinate
    
    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({point.first + constant, point.second - constant});
    }
    
    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 26: If all the points are mirrored along the line y=x and recalculate the closest pair of points, the distance should remain the same.
 */
TEST_P(ClosestPairParamTest, MR26) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by mirroring all points along the line y=x */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({point.second, point.first});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 27: If we replace each point (x, y) with (x+y, x-y), the distance of the closest pair of points should remain unchanged.
 */
TEST_P(ClosestPairParamTest, MR27) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by replacing each point (x, y) with (x+y, x-y) */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({point.first + point.second, point.first - point.second});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 28: If we sort the points by the distance from the origin and recalculate the closest pair of points, the output distance should remain unchanged.
 */
TEST_P(ClosestPairParamTest, MR28) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> point_vec(input.vec.begin(), input.vec.end());

    /* Sort points by distance from the origin */
    sort(point_vec.begin(), point_vec.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return hypot(a.first, a.second) < hypot(b.first, b.second);
    });

    /* Get source output */
    float source_out = closest_distance(point_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, closest_distance(input.vec));
}

/**
 * @brief Metamorphic relation 29: If we expand the x-coordinate and y-coordinate of each point by a certain scaling factor, the closest pair of points should not change.
 */
TEST_P(ClosestPairParamTest, MR29) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;
    
    double scalingFactor = 2.0; // Scaling factor for expansion
    
    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by expanding the coordinates of each point */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({static_cast<int>(point.first * scalingFactor), static_cast<int>(point.second * scalingFactor)});
    }
    
    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 30: If the x-coordinate and y-coordinate of each point are halved, the closest pair of points should not change.
 */
TEST_P(ClosestPairParamTest, MR30) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;
    
    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by halving the coordinates of each point */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({point.first / 2, point.second / 2});
    }
    
    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 31: If all the points are translated such that the centroid of the set becomes the origin, the closest pair of points should not change.
 */
TEST_P(ClosestPairParamTest, MR31) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    // Calculate centroid of points
    int centroidX = 0, centroidY = 0;
    for (const auto& point : vec) {
        centroidX += point.first;
        centroidY += point.second;
    }
    centroidX /= vec.size();
    centroidY /= vec.size();

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by translating all points so that the centroid becomes the origin */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({point.first - centroidX, point.second - centroidY});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 32: If we replace each point p(x, y) with p(y, x) and recalculate the closest pair of points, the output should remain the same.
 */
TEST_P(ClosestPairParamTest, MR32) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by replacing each point p(x, y) with p(y, x) */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({point.second, point.first});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 33: If we replace each point p(x, y) with p(x, -y) and recalculate the closest pair of points, the output should remain the same.
 */
TEST_P(ClosestPairParamTest, MR33) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by replacing each point p(x, y) with p(x, -y) */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({point.first, -point.second});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 34: If we replace each point p(x, y) with p(-x, -y) and recalculate the closest pair of points, the output should remain the same.
 */
TEST_P(ClosestPairParamTest, MR34) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by replacing each point p(x, y) with p(-x, -y) */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({-point.first, -point.second});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 35: If we add a constant value to both x and y coordinates of all points and recalculate the closest pair of points, the output should remain the same.
 */
TEST_P(ClosestPairParamTest, MR35) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    int constant = 5; // Constant to be added to all coordinates

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by adding a constant value to both x and y coordinates */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({point.first + constant, point.second + constant});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 36: If we subtract a constant value from both x and y coordinates of all points and recalculate the closest pair of points, the output should remain the same.
 */
TEST_P(ClosestPairParamTest, MR36) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    int constant = 5; // Constant to be subtracted from all coordinates

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by subtracting a constant value from both x and y coordinates */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({point.first - constant, point.second - constant});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 37: If we replace each point p(x, y) with p(y, -x) and recalculate the closest pair of points, the output should remain the same.
 */
TEST_P(ClosestPairParamTest, MR37) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by replacing each point p(x, y) with p(y, -x) */
    vector<pair<int, int>> follow_vec;
    for (const auto& point : vec) {
        follow_vec.push_back({point.second, -point.first});
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 38: If we concatenate the original set of points with itself and recalculate the closest pair of points, the output should remain unchanged.
 */
TEST_P(ClosestPairParamTest, MR38) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    // Create follow-up input by concatenating the original set of points with itself
    vector<pair<int, int>> follow_vec = vec;
    for (const auto& point : vec) {
        follow_vec.push_back(point);
    }

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 39: If we apply a random permutation to the order of the points and recalculate the closest pair of points, the output should remain the same.
 */
TEST_P(ClosestPairParamTest, MR39) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> point_vec(input.vec.begin(), input.vec.end());

    // Apply random permutation to the order of the points
    random_shuffle(point_vec.begin(), point_vec.end());

    /* Get source output */
    float source_out = closest_distance(point_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, closest_distance(input.vec));
}

/**
 * @brief Metamorphic relation 40: If we remove some points from the set and recalculate the closest pair of points, the output should not significantly change.
 */
TEST_P(ClosestPairParamTest, MR40) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    // Remove some points from the set
    vector<pair<int, int>> follow_vec = vec;
    if (follow_vec.size() > 3) {
        auto it = follow_vec.begin();
        advance(it, 3); // Removing the first 3 points
        follow_vec.erase(follow_vec.begin(), it);
    }

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_NEAR(source_out, follow_out, 1e-5);
}

/**
 * @brief Metamorphic relation 41: If we reverse the order of the points and calculate the closest pair of points, the output should remain unchanged.
 */
TEST_P(ClosestPairParamTest, MR41) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> point_vec(input.vec.begin(), input.vec.end());

    // Reverse the order of the points
    reverse(point_vec.begin(), point_vec.end());

    /* Get source output */
    float source_out = closest_distance(point_vec);

    /* Verification */
    EXPECT_DOUBLE_EQ(source_out, closest_distance(input.vec));
}

INSTANTIATE_TEST_CASE_P(TrueReturn, ClosestPairParamTest, testing::ValuesIn(gen_tcs_randomly()));