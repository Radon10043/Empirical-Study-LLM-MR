```c++
/**
 * @brief Metamorphic relation 1: Increasing the searching number by 1, if the original searching and this new searching number are both in the array, then the
 * starting position of the new number should be larger by 1 than the ending position of the original number.
 *
 */
TEST_P(GetRangeParamTest, MR1) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1 && source_out[1] == -1)
        return;

    /* Construct follow-up input */
    int follow_target = target + 1;

    /* Get follow-up output */
    vector<int> follow_out = get_range(vec, follow_target);
    if (follow_out[0] == -1 && follow_out[1] == -1)
        return;

    /* Verification */
    EXPECT_LE(source_out[1] + 1, follow_out[0]);
}

/**
 * @brief Metamorphic relation 2: Adding one small number to the head of the array, then the index of the searching number should also be increased by 1 (both
 * the starting and ending positions) if it is contained in the array.
 */
TEST_P(GetRangeParamTest, MR2) {
    /* Get source input */
    GetRangeInput input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    vector<int> source_out = get_range(vec, target);

    if (source_out[0] == -1 && source_out[1] == -1)
        return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.insert(follow_vec.begin(), follow_vec.front() - 1);

    /* Get follow-up output */
    vector<int> follow_out = get_range(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out[0] + 1, follow_out[0]);
    EXPECT_EQ(source_out[1] + 1, follow_out[1]);
}
```