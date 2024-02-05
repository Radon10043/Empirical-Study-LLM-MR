```c++
/**
 * Metamorphic relation 1: Add a character to the end of s, the output should be the same or larger.
 */
TEST_P(DistinctSubsequenceParamTest, MR1) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    string follow_s = s.append("a");

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}
```