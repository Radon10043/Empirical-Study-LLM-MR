#include <algorithm>
#include <gtest/gtest.h>
#include <random>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class ClosestPairParamTest : public ::testing::TestWithParam<ClosestPairInput> {};

/**
 * @brief Helper function to identify the closest pair of points in a vector.
 *
 * @param vec vector of points
 * @return pair<pair<int, int>, pair<int, int>> closest pair of points
 */
pair<pair<int, int>, pair<int, int>> identifyClosestPair(const vector<pair<int, int>> &vec) {
    pair<pair<int, int>, pair<int, int>> closestPair;
    float minDistance = numeric_limits<float>::max();
    for (size_t i = 0; i < vec.size(); ++i) {
        for (size_t j = i + 1; j < vec.size(); ++j) {
            float distance = sqrt(pow(vec[i].first - vec[j].first, 2) + pow(vec[i].second - vec[j].second, 2));
            if (distance < minDistance) {
                minDistance = distance;
                closestPair = {vec[i], vec[j]};
            }
        }
    }
    return closestPair;
}

/**
 * @brief Metamorphic relation 2: Scaling the coordinates of all points by a constant factor (positive) should not change the result.
 *
 */
TEST_P(ClosestPairParamTest, MR2) { // Fixed
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    const int scale_factor = 2;
    std::transform(vec.begin(), vec.end(), std::back_inserter(follow_vec),
                   [scale_factor](const pair<int, int> &p) { return make_pair(p.first * scale_factor, p.second * scale_factor); });

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out * scale_factor, follow_out);
}

/**
 * @brief Metamorphic relation 3: Translating all points by the same vector should not change the result.
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
    const pair<int, int> translation_vector = {10, 10};
    std::transform(vec.begin(), vec.end(), std::back_inserter(follow_vec), [translation_vector](const pair<int, int> &p) {
        return make_pair(p.first + translation_vector.first, p.second + translation_vector.second);
    });

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 4: Mirroring all points along the x-axis (or y-axis) should not change the result.
 *
 */
TEST_P(ClosestPairParamTest, MR4) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec_x;
    vector<pair<int, int>> follow_vec_y;
    std::transform(vec.begin(), vec.end(), std::back_inserter(follow_vec_x), [](const pair<int, int> &p) { return make_pair(p.first, -p.second); });
    std::transform(vec.begin(), vec.end(), std::back_inserter(follow_vec_y), [](const pair<int, int> &p) { return make_pair(-p.first, p.second); });

    /* Get follow-up output */
    float follow_out_x = closest_distance(follow_vec_x);
    float follow_out_y = closest_distance(follow_vec_y);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out_x);
    EXPECT_FLOAT_EQ(source_out, follow_out_y);
}

/**
 * @brief Metamorphic relation 5: Permutating the points should not change the result.
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
    std::next_permutation(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 6: Removing a point that is not part of the closest pair should not change the result.
 * (Note: This MR requires internal knowledge about the closest pair and thus may not always be applicable.)
 *
 */
TEST_P(ClosestPairParamTest, MR6) { // Fixed
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Assuming vec has more than two points and remove one that is not in the closest pair */
    if (vec.size() <= 2)
        return;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec = vec;

    /* Remove a point that is not part of the closest pair */
    auto closest_pair = identifyClosestPair(vec);
    for (auto it = follow_vec.begin(); it != follow_vec.end(); ++it) {
        if (*it != closest_pair.first && *it != closest_pair.second) {
            follow_vec.erase(it);
            break;
        }
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 7: Doubling each point should not change the result as all distance
 * measures will be doubled, and thus the relative minimum distance will remain the same.
 *
 */
TEST_P(ClosestPairParamTest, MR7) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    // Doubling each point effectively doubles the distance.
    std::transform(vec.begin(), vec.end(), std::back_inserter(follow_vec), [](const pair<int, int> &p) { return make_pair(p.first * 2, p.second * 2); });

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out * 2, follow_out);
}

/**
 * @brief Metamorphic relation 8: Rotating all points around the origin by 90 degrees should not change the result.
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
    // Rotate each point by 90 degrees: (x, y) becomes (-y, x)
    std::transform(vec.begin(), vec.end(), std::back_inserter(follow_vec), [](const pair<int, int> &p) { return make_pair(-p.second, p.first); });

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 9: Reversing the order of points should not change the result.
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
    std::reverse(follow_vec.begin(), follow_vec.end());

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 10: If all points are collinear and we add a new point on the line,
 * the closest distance should remain the same if the new point is not between any of the existing closest pairs.
 *
 */
TEST_P(ClosestPairParamTest, MR10) { // Fixed
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input - for simplicity, add a new point far away on the x-axis */
    pair<int, int> far_point = {vec.back().first + 1e9, vec.back().second};
    vector<pair<int, int>> follow_vec = vec;
    follow_vec.push_back(far_point);

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 11: Inverting the sign of all points' coordinates should not change the result.
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
    for (auto &p : vec) {
        follow_vec.emplace_back(-p.first, -p.second);
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 12: Uniformly scaling (both expanding and contracting) the points should change
 * the minimum distance by the same scaling factor.
 *
 */
TEST_P(ClosestPairParamTest, MR12) { // Fixed
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    float scaling_factor = 0.5; // Contracting by a factor of 0.5

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    for (auto &p : vec) {
        follow_vec.emplace_back(static_cast<int>(p.first * scaling_factor), static_cast<int>(p.second * scaling_factor));
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification: since distances are contracted, the closest distance should also be contracted. */
    EXPECT_FLOAT_EQ(source_out * scaling_factor, follow_out);
}

/**
 * @brief Metamorphic relation 13: Swapping the x and y coordinates of all points should not change the result.
 *
 */
TEST_P(ClosestPairParamTest, MR13) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by swapping x and y coordinates */
    vector<pair<int, int>> follow_vec;
    for (auto &p : vec) {
        follow_vec.emplace_back(p.second, p.first);
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 14: Adding a constant to the x-coordinates of all points should not change the result.
 *
 */
TEST_P(ClosestPairParamTest, MR14) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    int x_addition = 100; // Add 100 to x-coordinates
    for (auto &p : vec) {
        follow_vec.emplace_back(p.first + x_addition, p.second);
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 15: Adding a constant to the y-coordinates of all points should not change the result.
 *
 */
TEST_P(ClosestPairParamTest, MR15) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    int y_addition = 100; // Add 100 to y-coordinates
    for (auto &p : vec) {
        follow_vec.emplace_back(p.first, p.second + y_addition);
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 16: Removing all points but the closest pair should result in the same output value.
 * (Note: This MR requires internal knowledge about the closest pair and may not be applicable without identifying the closest pair first.)
 *
 */
TEST_P(ClosestPairParamTest, MR16) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Assuming vec has more than two points */
    if (vec.size() <= 2)
        return;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Identify the closest pair in vec (this is an assumed subroutine for this MR) */
    std::pair<pair<int, int>, pair<int, int>> closestPair = identifyClosestPair(vec);

    /* Construct follow-up input consisting only of the closest pair */
    vector<pair<int, int>> follow_vec = {closestPair.first, closestPair.second};

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 17: Reflecting all points across a random line should not change the result.
 *
 */
TEST_P(ClosestPairParamTest, MR17) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    // Choose an arbitrary line for reflection, here y = x for simplicity
    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    for (const auto &p : vec) {
        follow_vec.emplace_back(p.second, p.first); // Reflect each point across y = x
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 18: Applying a rigid transformation (rotation + translation) to all points should not change the result.
 *
 */
TEST_P(ClosestPairParamTest, MR18) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Rotation of 45 degrees around the origin and translation by a vector (50, 50) for simplicity */
    double angle = M_PI / 4;
    double cos_angle = cos(angle);
    double sin_angle = sin(angle);
    pair<int, int> translation_vector = {50, 50};

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec;
    for (const auto &p : vec) {
        int x_rotated = static_cast<int>(p.first * cos_angle - p.second * sin_angle + translation_vector.first);
        int y_rotated = static_cast<int>(p.first * sin_angle + p.second * cos_angle + translation_vector.second);
        follow_vec.emplace_back(x_rotated, y_rotated);
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 19: Given a set of points that are all equidistant from one another,
 * adding a new point equidistant from all the others should keep the closest distance unchanged.
 *
 */
TEST_P(ClosestPairParamTest, MR19) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    // Ensure all points are equidistant from the center (0,0) for simplicity
    // This precondition needs to be met for the test case to be valid

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by adding a new point equidistant from (0,0) */
    vector<pair<int, int>> follow_vec = vec;
    if (!vec.empty()) {
        // Assume the distance from the center is the same as the first point
        int distance = static_cast<int>(sqrt(vec.front().first * vec.front().first + vec.front().second * vec.front().second));
        follow_vec.emplace_back(0, distance); // New point with the same distance
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 20: If all points are identical, the output should be zero regardless
 * of the number of points.
 *
 */
TEST_P(ClosestPairParamTest, MR20) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    // All the points in vec are identical
    // This precondition needs to be met for the test case to be valid

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by adding additional points identical to the original ones */
    vector<pair<int, int>> follow_vec = vec;
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.end()); // Double the points

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    // For identical points, the closest distance is always zero.
    EXPECT_FLOAT_EQ(0, follow_out);
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 21: Adding the same multiple point should not affect the result.
 *
 */
TEST_P(ClosestPairParamTest, MR21) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by adding a duplicate of an existing point */
    vector<pair<int, int>> follow_vec = vec;

    // Add a duplicate point; assume vec is non-empty
    pair<int, int> duplicate_point = vec[0];
    follow_vec.push_back(duplicate_point);
    follow_vec.push_back(duplicate_point); // Add the same point twice

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 22: Excluding points that are not within the closest pair
 * from a larger subset should not affect the closest distance.
 * (This requires knowing the closest pair beforehand and only works under specific conditions.)
 *
 */
TEST_P(ClosestPairParamTest, MR22) {    // Fixed
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    // This MR assumes vec includes additional points that are not part of the closest pair.
    if (vec.size() <= 2)
        return;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Identify the closest pair (this part is assumed) */
    pair<pair<int, int>, pair<int, int>> closestPair = identifyClosestPair(vec);

    /* Construct follow-up input by only including the closest pair */
    vector<pair<int, int>> follow_vec = {closestPair.first, closestPair.second};

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 23: Shuffling the points should not change the closest distance outcome.
 *
 */
TEST_P(ClosestPairParamTest, MR23) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by shuffling the order of the points */
    vector<pair<int, int>> follow_vec = vec;

    // Shuffle the points randomly
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(follow_vec.begin(), follow_vec.end(), g);

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 24: Separating the closest pair by a large distance
 * should increase the closest distance.
 *
 */
TEST_P(ClosestPairParamTest, MR24) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    // Assume that we can identify the closest pair (potentially by using the same algorithm)
    pair<pair<int, int>, pair<int, int>> closestPair = identifyClosestPair(vec);

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by moving one of the closest pair points far away */
    vector<pair<int, int>> follow_vec = vec;

    for (auto &p : follow_vec) {
        if (p == closestPair.first) {
            p.first += 10000; // Move the point far away in the x direction
            break;
        }
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_GT(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 25: Inverting the coordinates of all points
 * (making x = -x and y = -y for all points) should not change the result.
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
    std::transform(vec.begin(), vec.end(), std::back_inserter(follow_vec), [](const pair<int, int> &p) { return make_pair(-p.first, -p.second); });

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 26: Multiplying all point coordinates by -1 should not change the closest_distance output
 *
 */
TEST_P(ClosestPairParamTest, MR26) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by negating all point coordinates */
    vector<pair<int, int>> follow_vec;
    for (auto &p : vec) {
        follow_vec.emplace_back(-p.first, -p.second);
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 27: Flipping the points around the x-axis should not change the closest_distance output
 *
 */
TEST_P(ClosestPairParamTest, MR27) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by flipping the y coordinate */
    vector<pair<int, int>> follow_vec;
    for (auto &p : vec) {
        follow_vec.emplace_back(p.first, -p.second);
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 28: Flipping the points around the y-axis should not change the closest_distance output
 *
 */
TEST_P(ClosestPairParamTest, MR28) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by flipping the x coordinate */
    vector<pair<int, int>> follow_vec;
    for (auto &p : vec) {
        follow_vec.emplace_back(-p.first, p.second);
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 29: Rotating points around the origin by 180 degrees should not change the closest_distance output
 *
 */
TEST_P(ClosestPairParamTest, MR29) {    // Fixed
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by rotating the points */
    vector<pair<int, int>> follow_vec;
    for (auto &p : vec) {
        follow_vec.emplace_back(-p.first, -p.second);
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 30: Combining two sets of points (without overlap) and ensuring the closest pair is within one of the sets should return the
 * minimum of the two closest pairs distance.
 *
 */
TEST_P(ClosestPairParamTest, MR30) {
    /* Get source input - two non-overlapping sets */
    ClosestPairInput input1 = GetParam();
    vector<pair<int, int>> vec1 = input1.vec;
    ClosestPairInput input2 = GetParam();
    vector<pair<int, int>> vec2 = input2.vec;

    // Translate the second vector to ensure no overlap.
    // Assume vec2 is translated to a far enough distance so as not to affect the minimum distance for vec1
    for (auto &p : vec2) {
        p.first += 10000; // Shift all points in vec2 by +10000 on the x-axis
    }

    /* Get source output for the individual sets */
    float source_out1 = closest_distance(vec1);
    float source_out2 = closest_distance(vec2);

    /* Combine vec1 and vec2 */
    vector<pair<int, int>> combined_vec(vec1);
    combined_vec.insert(combined_vec.end(), vec2.begin(), vec2.end());

    /* Get follow-up output */
    float follow_out = closest_distance(combined_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(follow_out, std::min(source_out1, source_out2)); // The closest pair should be within one of the sets
}

/**
 * @brief Metamorphic relation 31: Rotating the set of points around a random point (not necessarily the origin) should not change the closest distance.
 *
 */
TEST_P(ClosestPairParamTest, MR31) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Random rotation point, chose (50, 50) for simplicity */
    pair<int, int> rotation_point = {50, 50};

    /* Angle for rotation in radians */
    const double PI = 3.14159265358979323846;
    double rotation_angle = PI / 4; // 45 degrees for example

    /* Rotate around the point */
    vector<pair<int, int>> follow_vec;
    for (auto &p : vec) {
        int translated_x = p.first - rotation_point.first;
        int translated_y = p.second - rotation_point.second;
        follow_vec.emplace_back(static_cast<int>(translated_x * cos(rotation_angle) - translated_y * sin(rotation_angle)) + rotation_point.first,
                                static_cast<int>(translated_x * sin(rotation_angle) + translated_y * cos(rotation_angle)) + rotation_point.second);
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 32: Randomly scaling the points (independently scaling x and y) should preserve the ratio of distances between each pair of
 * points which guarantees the closest distance is scaled.
 *
 */
TEST_P(ClosestPairParamTest, MR32) {    // Fixed
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    float x_scale_factor = 3; // Scaling factor for x-axis
    float y_scale_factor = 2; // Scaling factor for y-axis

    /* Scale and construct follow-up input */
    vector<pair<int, int>> follow_vec;
    for (auto &p : vec) {
        follow_vec.emplace_back(static_cast<int>(p.first * x_scale_factor), static_cast<int>(p.second * y_scale_factor));
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    // Since the closest pair would also be scaled, we need to scale down the follow_out distance to compare
    // This is to account for the uneven scale in x and y directions
    float scaled_down_out = follow_out / sqrt(x_scale_factor * x_scale_factor + y_scale_factor * y_scale_factor);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, scaled_down_out);
}

/**
 * @brief Metamorphic relation 33: Adding a point that is at a large distance from all other points should not change the closest distance.
 *
 */
TEST_P(ClosestPairParamTest, MR33) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input by adding a distant point */
    vector<pair<int, int>> follow_vec = vec;
    follow_vec.emplace_back(10000, 10000); // Add a point far away from all existing points

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 34: Removing a subset of points far from the closest pair should not change the closest distance.
 *
 */
TEST_P(ClosestPairParamTest, MR34) {    // Fixed
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    // Assume that we have a way of determining a subset of points that are far from the closest pair.
    // The validity of this relation depends on the ability to choose such a subset correctly.
    if (vec.size() <= 2) return;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec = vec;
    // Remove a subset of points far from the closest pair - the mechanism to select these points is not specified
    // This operation is a placeholder for the actual filter operation that would be based on domain knowledge.
    auto closest_pair = identifyClosestPair(vec);
    for (auto it = follow_vec.begin(); it != follow_vec.end(); ++it) {
        if (*it != closest_pair.first && *it != closest_pair.second) {
            follow_vec.erase(it);
            break;
        }
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 35: If a set of points forms a perfect grid, then adding another row or column of points at the same distance should not change
 * the closest distance.
 *
 */
TEST_P(ClosestPairParamTest, MR35) {    // Fixed
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    // Assume the points in vec form a perfect grid with equal distances "grid_spacing" between adjacent points.
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(1, 1000);
    int grid_spacing = dist(rng); // Random grid spacing

    vec = {{0, 0}, {0, grid_spacing}, {grid_spacing, 0}, {grid_spacing, grid_spacing}};

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec = vec;

    // Add an additional column to the right
    follow_vec.emplace_back(2 * grid_spacing, 0);
    follow_vec.emplace_back(2 * grid_spacing, grid_spacing);

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 36: Rotating the points around their centroid should not change the closest distance.
 *
 */
TEST_P(ClosestPairParamTest, MR36) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Calculate the centroid */
    int sum_x = 0, sum_y = 0;
    for (const auto &p : vec) {
        sum_x += p.first;
        sum_y += p.second;
    }
    pair<int, int> centroid = {sum_x / vec.size(), sum_y / vec.size()};

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Rotate around centroid by a fixed angle (e.g., 90 degrees) */
    const double PI = 3.14159265358979323846;
    double angle = PI / 2; // 90 degrees
    double cos_angle = cos(angle);
    double sin_angle = sin(angle);

    vector<pair<int, int>> follow_vec;
    for (auto &p : vec) {
        int translated_x = p.first - centroid.first;
        int translated_y = p.second - centroid.second;
        int rotated_x = static_cast<int>(translated_x * cos_angle - translated_y * sin_angle);
        int rotated_y = static_cast<int>(translated_x * sin_angle + translated_y * cos_angle);
        follow_vec.emplace_back(rotated_x + centroid.first, rotated_y + centroid.second);
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 37: Reflecting all points across a chosen axis parallel to either the x or y axis should not change the closest distance.
 *
 */
TEST_P(ClosestPairParamTest, MR37) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Reflect points across an axis, e.g. y = 10 */
    int reflection_axis = 10; // Chosen axis y = 10 for reflection

    vector<pair<int, int>> follow_vec;
    for (auto &p : vec) {
        int reflected_y = 2 * reflection_axis - p.second;
        follow_vec.emplace_back(p.first, reflected_y);
    }

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 38: If a set of points all fall on the circumference of a circle, adding a new point anywhere on that circumference should not
 * change the closest distance as long as the points are evenly distributed.
 *
 */
TEST_P(ClosestPairParamTest, MR38) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    // Assume vec contains points on the circumference of a circle with center at zero and evenly spaced on the circle.
    // The radius of the circle would need to be determined or known in advance for this MR to hold.

    /* Get source output */
    float source_out = closest_distance(vec);

    /* Construct follow-up input */
    vector<pair<int, int>> follow_vec = vec;
    int radius = 10; // Pre-determined or calculated radius of the circle

    // Add a new point on the circle circumference
    follow_vec.emplace_back(radius, 0); // For simplicity, add a point on the positive x-axis.

    /* Get follow-up output */
    float follow_out = closest_distance(follow_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 39: Converting all points from Cartesian to polar coordinates and back should not change the closest distance.
 *
 */
TEST_P(ClosestPairParamTest, MR39) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Convert all points to polar coordinates and back to Cartesian coordinates */
    vector<pair<int, int>> converted_vec;
    for (auto &point : vec) {
        double r = sqrt(point.first * point.first + point.second * point.second);
        double theta = atan2(point.second, point.first);
        int x = static_cast<int>(r * cos(theta));
        int y = static_cast<int>(r * sin(theta));
        converted_vec.emplace_back(x, y);
    }

    /* Get source output and follow-up output */
    float source_out = closest_distance(vec);
    float follow_out = closest_distance(converted_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 40: Shearing the points along one axis should not change the closest distance.
 *
 */
TEST_P(ClosestPairParamTest, MR40) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Apply a shear transformation along the x-axis */
    vector<pair<int, int>> sheared_vec;
    float shear_factor = 1.5; // Shearing factor
    for (auto &point : vec) {
        int x = point.first + static_cast<int>(shear_factor * point.second);
        int y = point.second;
        sheared_vec.emplace_back(x, y);
    }

    /* Get source output and follow-up output */
    float source_out = closest_distance(vec);
    float follow_out = closest_distance(sheared_vec);

    /* Verification */
    EXPECT_FALSE(abs(source_out - follow_out) < FLT_EPSILON); // The closest distance is expected to change after shearing
}

/**
 * @brief Metamorphic relation 41: Inverting the sign of one coordinate axis should not change the closest distance.
 *
 */
TEST_P(ClosestPairParamTest, MR41) {
    /* Get source input */
    ClosestPairInput input = GetParam();
    vector<pair<int, int>> vec = input.vec;

    /* Invert the y-coordinate of each point */
    vector<pair<int, int>> inverted_vec;
    for (auto &point : vec) {
        inverted_vec.emplace_back(point.first, -point.second);
    }

    /* Get source output and follow-up output */
    float source_out = closest_distance(vec);
    float follow_out = closest_distance(inverted_vec);

    /* Verification */
    EXPECT_FLOAT_EQ(source_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, ClosestPairParamTest, testing::ValuesIn(gen_tcs_randomly()));