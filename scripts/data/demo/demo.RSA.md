```c++
/**
 * @brief Metamorphic Relation 1: Keeping p, q and e the same, giving a new plaintext which is equals to m + p*q, the ciphertext is the same.
 *
 */
TEST_P(RSAParamTest, MR1) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get source output */
    long long source_out = candp(m, e, p, q);

    /* Construct follow-up input */
    int follow_m = m + p * q;

    /* Get follow-up output */
    long long follow_out = candp(follow_m, e, p, q);

    /* Verification */
    ASSERT_EQ(source_out, follow_out);
}
```