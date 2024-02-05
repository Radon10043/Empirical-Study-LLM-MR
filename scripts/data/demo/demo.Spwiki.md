```c++
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
```