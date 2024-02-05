```c++
/**
 * @brief Metamorphic Relation 1: Adding one number at the end of the array, the follow-up output should be the same as or larger than the source output.
 *
 */
TEST_P(MultiMAXSUMParamTest, MR1) {
    /* Get source input */
    MultiMAXSUMInput input = GetParam();
    vector<int> source_vec = input.vec;
    int source_m = input.m;

    /* Get source output */
    int source_out = multi_maxsum(source_vec, source_m);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.push_back(source_vec.back());

    /* Get follow-up output */
    int follow_out = multi_maxsum(follow_vec, source_m);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}
```