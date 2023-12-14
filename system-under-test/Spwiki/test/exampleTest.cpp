#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../function.h"

using namespace std;

typedef struct SpwikiInput {
    SpwikiInput(tuple<vector<vector<int>>, int, int, int> testcase) {
        edges = get<0>(testcase);
        src = get<1>(testcase);
        dst = get<2>(testcase);
        n = get<3>(testcase);
    };
    vector<vector<int>> edges;
    int src, dst, n;
} SpwikiInput;

class SpwikiParamTest : public ::testing::TestWithParam<SpwikiInput> {};

/**
 * @brief Metamorphic Relation 1: Reversing the source and destination vertices, the length of the shortest path should be the same.
 *
 */
TEST_P(SpwikiParamTest, MR1) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    int follow_src = source_dst, follow_dst = source_src;

    /* Get follow-up output */
    int follow_out = shortest_path(source_edges, follow_src, follow_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 2: Doubling the weight of each edge, the length of the shortest path should be doubled.
 *
 */
TEST_P(SpwikiParamTest, MR2) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> follow_edges = source_edges;
    for (auto &elem : follow_edges)
        elem[2] *= 2;

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out * 2);
}

tuple<vector<vector<int>>, int, int, int> testcase1() {
    vector<vector<int>> edges = {{0, 1, 9}, {1, 2, 1}, {2, 3, 2}, {3, 4, 3}, {4, 5, 4}, {5, 6, 5}, {6, 1, 6}};
    int src = 1, dst = 6, n = 7;
    return make_tuple(edges, src, dst, n);
}

tuple<vector<vector<int>>, int, int, int> testcase2() {
    vector<vector<int>> edges = {{0, 1, 1}, {0, 2, 2}, {1, 3, 6}, {2, 3, 5}};
    int src = 0, dst = 3, n = 4;
    return make_tuple(edges, src, dst, n);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, SpwikiParamTest, testing::Values(testcase1(), testcase2()));