#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class RSAParamTest : public ::testing::TestWithParam<RSAInput> {};

/****** Helper methods, implemented by Radon ******/
int generateNewE(int e, int p, int q) {
    for (e++; e < (p - 1) * (q - 1); e++) {
        if (__gcd(e, (p - 1) * (q - 1)) == 1) {
            break;
        }
    }
    return e;
}

long long modInverse(long long v1, long long v2) {
    long long v2_copy = v2;
    long long v1_copy = v1;
    long long v1_prev = 0;
    long long v2_prev = 1;
    while (v2 != 0) {
        long long quotient = v1 / v2;
        long long temp = v2;
        v2 = v1 % v2;
        v1 = temp;
        temp = v1_prev;
        v1_prev = v2_prev - quotient * v1_prev;
        v2_prev = temp;
    }
    if (v1_prev < 0) {
        v1_prev += v2_copy;
    }
    return v1_prev;
}
/**************************************************/

/**
 * @brief Metamorphic Relation 1: Keeping e and p the same, the result should be equivalent with different m.
 *
 */
TEST_P(RSAParamTest, MR1) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // New m value
    int follow_m = 2 * m;

    // Get follow-up output
    long long result2 = candp(follow_m, e, p, q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 2: Keeping m and q the same, the result should be equivalent with different e.
 *
 */
TEST_P(RSAParamTest, MR2) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Construct follow-up input
    int follow_e = generateNewE(e, p, q);

    // Get follow-up output
    long long result2 = candp(m, follow_e, p, q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 3: Keeping m, e, and q the same, giving a new p which is a factor of q, the result should be equivalent.
 *
 */
TEST_P(RSAParamTest, MR3) { // Fixed
    // NOTE: p和q需要互质, 但衍生的pq不是互质的
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Construct follow-up input
    int follow_p = q;

    // Get follow-up output
    long long result2 = candp(m, e, follow_p, q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 4: Keeping m and p the same, giving a new q as q+1, the result should be equivalent.
 *
 */
TEST_P(RSAParamTest, MR4) { // Fixed
    // NOTE: p和q需要互质, 但q+1和p不一定是互质的
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Construct follow-up input
    int follow_q = q + 1;

    // Get follow-up output
    long long result2 = candp(m, e, p, follow_q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 5: Keeping p and q the same, the result should be equivalent with different m and e where m2 = m * m, e2 = e * e.
 *
 */
TEST_P(RSAParamTest, MR5) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // New m and e values
    int follow_m = m * m;
    int follow_e = e * e;

    // Get follow-up output
    long long result2 = candp(follow_m, follow_e, p, q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 6: Keeping m and e the same, the result should be equivalent with different p and q where p*q is the same.
 *
 */
TEST_P(RSAParamTest, MR6) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, 3, 35);

    // Swap p and q to make sure p*q is the same
    // Get follow-up output
    long long result2 = candp(m, e, 5, 7);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 7: Keeping p, q, and e the same, giving a new m' as m' = m + k*(pq), the result should be equivalent where k is an arbitrary
 * integer.
 *
 */
TEST_P(RSAParamTest, MR7) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // New m value
    int k = 2;
    int new_m = m + k * p * q;

    // Get follow-up output
    long long result2 = candp(new_m, e, p, q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 8: Keeping m, e, p, and q the same, the result should be the same if m is replaced by m + npq for any integer n.
 *
 */
TEST_P(RSAParamTest, MR8) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // New m value
    int n = 3;
    int new_m = m + n * p * q;

    // Get follow-up output
    long long result2 = candp(new_m, e, p, q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 9: Keeping m and e the same, giving a new p as 2 * p, the result should be equivalent.
 *
 */
TEST_P(RSAParamTest, MR9) { // Fixed
    // NOTE: p和q需要互质, 但2p和q不一定是互质的
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Get follow-up output
    long long result2 = candp(m, e, 2 * p, q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 10: Keeping m and e the same, giving a new q as 2 * q, the result should be equivalent.
 *
 */
TEST_P(RSAParamTest, MR10) { // Fixed
    // NOTE: p和q需要互质, 但p和2q不一定是互质的
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Get follow-up output
    long long result2 = candp(m, e, p, 2 * q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 11: Given the input values m, e, p and q, the result should remain unchanged for the same input values.
 */
TEST_P(RSAParamTest, MR11) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Get follow-up output with the same input
    long long result2 = candp(m, e, p, q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 12: Given the input values, swapping the values of p and q should result in the same output.
 */
TEST_P(RSAParamTest, MR12) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get output with original p, q
    long long result1 = candp(m, e, p, q);

    // Get output with swapped p, q
    long long result2 = candp(m, e, q, p);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 13: Given the input values, keeping m and e the same, and changing p to p+1 and q to q-1, the result should be equivalent.
 */
TEST_P(RSAParamTest, MR13) { // Fixed
    // NOTE: p和q需要互质, 但p+1和q-1不一定是互质的
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Get follow-up output
    long long result2 = candp(m, e, p + 1, q - 1);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 14: Given the input values, keeping m and e the same, and changing p and q to be prime numbers resulting in the same product pq,
 * the result should be equivalent.
 */
TEST_P(RSAParamTest, MR14) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    e = generateNewE(e, p, q);

    // Get initial output
    long long result1 = candp(m, e, 5, 7);

    // Get follow-up output with new p and q
    long long result2 = candp(m, e, 3, 35); // 3*35 = 105 = 5*7

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 15: Given the input values, keeping e constant, multiplying m, p, and q by the same factor should result in the same output.
 */
TEST_P(RSAParamTest, MR15) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Get follow-up output with new input values
    long long result2 = candp(2 * m, e, 2 * p, 2 * q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 16: Given the input values, keeping e constant, multiplying m and p by the same factor and dividing q by the same factor should
 * result in the same output.
 */
TEST_P(RSAParamTest, MR16) { // Fixed
    // NOTE: 输入转换后不一定满足RSA的输入要求
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Get follow-up output with new input values
    long long result2 = candp(2 * m, e, 2 * p, q / 2);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 17: Given the input values, keeping p and q constant, and changing m to its negative counterpart, the result should remain
 * unchanged.
 */
TEST_P(RSAParamTest, MR17) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Get follow-up output with negative m
    long long result2 = candp(-m, e, p, q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 18: Given the input values, keeping m and p constant, and setting q to be the sum of two prime numbers, the result should remain
 * unchanged.
 */
TEST_P(RSAParamTest, MR18) { // Fixed
    // NOTE: p和q需要互质, 但p和p+q不一定是互质的
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Get follow-up output with new q being sum of prime numbers
    long long result2 = candp(m, e, p, p + q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 19: Given the input values, keeping m and e constant, and changing the values of p and q by adding/subtracting the same prime
 * number, the result should be equivalent.
 */
TEST_P(RSAParamTest, MR19) { // Fixed
    // NOTE: 转换后的输入不一定满足RSA的输入要求
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    int prime = 11; // A prime number

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Add the prime number to p and q
    long long result2 = candp(m, e, p + prime, q + prime);

    // Subtract the prime number from p and q
    long long result3 = candp(m, e, p - prime, q - prime);

    // Verification
    ASSERT_EQ(result1, result2);
    ASSERT_EQ(result1, result3);
}

/**
 * @brief Metamorphic Relation 20: Given the input values, keeping m, e, p and q constant, and changing m to its modulus with p*q+(p+1) should result in the
 * same output.
 */
TEST_P(RSAParamTest, MR20) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    int modulus_m = (m) % (p * q + (p + 1));

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Get follow-up output with new m
    long long result2 = candp(modulus_m, e, p, q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 21: Given the input values, keeping m, e, p and q constant, using the property (a+b) mod c = ((a mod c) + (b mod c)) mod c, we
 * have (m+1) mod (p*q) = (m mod (p*q) + 1) mod (p*q). Therefore, when we change m to m+1, the result should remain unchanged.
 */
TEST_P(RSAParamTest, MR21) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    int new_m = m + 1;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Get follow-up output with new m
    long long result2 = candp(new_m, e, p, q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 22: Given the input values, keeping e, p, and q constant, and changing m to m * p * q, the result should be equivalent.
 */
TEST_P(RSAParamTest, MR22) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Get follow-up output with new m
    long long result2 = candp(m * p * q, e, p, q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 23: Given the input values, keeping m, e, p, and q the same, negating the exponent e should result in the same output.
 */
TEST_P(RSAParamTest, MR23) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Get follow-up output with negated exponent e
    long long result2 = candp(m, -e, p, q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 24: Given the input values, keeping m and e the same, and switching p and q, the result should remain unchanged.
 */
TEST_P(RSAParamTest, MR24) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Swap p and q
    long long result2 = candp(m, e, q, p);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 25: Given the input values, keeping m and e the same, and doubling both p and q, the result should remain unchanged.
 */
TEST_P(RSAParamTest, MR25) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Double p and q
    long long result2 = candp(m, e, 2 * p, 2 * q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 26: Given the input values, keeping m and e the same, changing p and q to their cubes, the result should remain unchanged.
 */
TEST_P(RSAParamTest, MR26) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Set p and q to their cubes
    long long result2 = candp(m, e, p * p * p, q * q * q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 27: Given the input values, keeping m, p, and q constant, and incrementing the exponent e by 1, the result should be m * (m^e mod
 * (p*q)).
 */
TEST_P(RSAParamTest, MR27) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Get follow-up output with incremented exponent e
    long long result2 = candp(m, e + 1, p, q);
    long long expect = m * (static_cast<long long>(pow(m, e)) % (p * q));

    // Verification
    ASSERT_EQ(expect, result2);
}

/**
 * @brief Metamorphic Relation 28: Given the input values, keeping e, p, and q constant, if m1 and m2 are congruent modulo (p*q), then the result of m1 and m2
 * using the same exponent e, p, and q should also be the same.
 */
TEST_P(RSAParamTest, MR28) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    int modulus = p * q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Construct follow-up input, make sure m%(p*q) == folow_m%(p*q)
    int follow_m = m + p * q;

    // Get follow-up output with m2 being congruent to m1 modulo (p*q)
    long long result2 = candp(follow_m, e, p, q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 29: Given the input values, keeping m, e, and q constant, and adding a multiple of p*q to m, the result should be unchanged.
 */
TEST_P(RSAParamTest, MR29) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    int k = 2; // Any integer

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Get follow-up output with new m
    long long result2 = candp(m + k * p * q, e, p, q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 30: Given the input values, keeping m and e constant, switching the values of p and q so that p*q remains the same, the result
 * should be equivalent.
 */
TEST_P(RSAParamTest, MR30) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Switch p and q while keeping their product the same
    long long result2 = candp(m, e, q, p);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 31: Given the input values, keeping e, p and q constant, and multiplying m by a non-zero integer k, the result should show a
 * congruence relation with the original result.
 */
TEST_P(RSAParamTest, MR31) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    int k = 3; // non-zero integer

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Get follow-up output with new m
    long long result2 = candp((m * k) % (p * q), e, p, q);

    // Verification
    ASSERT_EQ((result1 % (p * q)), (result2 % (p * q)));
}

/**
 * @brief Metamorphic Relation 32: Given the input values, keeping m, p, and q constant, changing the exponent e to its square, the result should be the square
 * of the original result.
 */
TEST_P(RSAParamTest, MR32) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Get follow-up output with squared exponent e
    long long result2 = candp(m, e * e, p, q);

    // Verification
    ASSERT_EQ(result1 * result1, result2);
}

/**
 * @brief Metamorphic Relation 33: Given the input values, keeping m, p, and q constant, changing e to its negative counterpart, the result should be
 * modInverse(candp(m, e, p, q), p*q)
 */
TEST_P(RSAParamTest, MR33) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Compute modInverse of the original result
    long long inv_result = modInverse(candp(m, e, p, q), p * q);

    // Get follow-up output with negated exponent e
    long long result2 = candp(m, -e, p, q);

    // Verification
    ASSERT_EQ(inv_result, result2);
}

/**
 * @brief Metamorphic Relation 34: Given the input values, keeping e, p, and q constant, and setting m to the product of p and q, the result should be 0.
 */
TEST_P(RSAParamTest, MR34) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Get follow-up output with m equal to the product of p and q
    long long result2 = candp(p * q, e, p, q);

    // Verification
    ASSERT_EQ(0, result2);
}

/**
 * @brief Metamorphic Relation 35: Given the input values, keeping e, and p constant, and setting m to be the minimum value of p*q-1, the result should be the
 * same as m.
 */
TEST_P(RSAParamTest, MR35) { // Fixed
    RSAInput input = GetParam();
    int e = input.e, p = input.p, q = input.q;
    unsigned long long m = (p * q) - 1;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Verification
    ASSERT_EQ(static_cast<long long>(m), result1);
}

/**
 * @brief Metamorphic Relation 36: Given the input values, keeping p, q, and e constant, doubling the value of m should result in a congruent output modulo
 * (p*q).
 */
TEST_P(RSAParamTest, MR36) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Get follow-up output with m being doubled
    long long result2 = candp(2 * m, e, p, q);

    // Verification
    ASSERT_EQ(result1 % (p * q), result2 % (p * q)); // Check the congruence
}

/**
 * @brief Metamorphic Relation 37: Given the input values, keeping m, p, and q constant, the result should remain unchanged when e is set to 1.
 */
TEST_P(RSAParamTest, MR37) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    // Get initial output
    long long result1 = candp(m, e, p, q);

    // Get follow-up output with exponent e set to 1
    long long result2 = candp(m, 1, p, q);

    // Verification
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 38: Given the input values, keeping e, p and q constant, if m_1 and m_2 are equivalent modulo (p*q), the result of m_1 and m_2
 * using the same exponent e, p, and q should also be the same.
 */
TEST_P(RSAParamTest, MR38) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    int modulus = p * q;

    // Get initial outputs
    long long result1 = candp(m, e, p, q);

    // Construct follow-up input
    int follow_m = m + modulus;
    long long result2 = candp(follow_m, e, p, q);

    // Verification
    ASSERT_EQ(m % modulus, follow_m % modulus);
    ASSERT_EQ(result1, result2);
}

/**
 * @brief Metamorphic Relation 39: Given the input values, keeping e, p, and q constant and setting m to 0, the result should be 0.
 */
TEST_P(RSAParamTest, MR39) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    m = 0;

    // Get the output
    long long result = candp(m, e, p, q);

    // Verification
    ASSERT_EQ(0, result);
}

/**
 * @brief Metamorphic Relation 40: Given the input values, keeping e, p, and q constant and setting m to 1, the result should be congruent to 1 modulo (p*q).
 */
TEST_P(RSAParamTest, MR40) { // Fixed
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    m = 1;

    // Get the output
    long long result = candp(m, e, p, q);

    // Verification
    ASSERT_EQ(1, result % (p * q)); // Check the congruence
}

INSTANTIATE_TEST_CASE_P(TrueReturn, RSAParamTest, testing::ValuesIn(gen_tcs_randomly()));