#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../src/function.h"
#include "utils.h"
#include <climits>

using namespace std;

class RSAParamTest : public ::testing::TestWithParam<RSAInput> {};

/****** Helper methods, implemented by Radon ******/
int ComputeModInverse(int a, long long m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

long long pow_mod(int base, int exp, long long modulus) {
    long long result = 1;
    base = base % modulus;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % modulus;
        }
        exp = exp >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

/**
 * @brief Metamorphic Relation 2: Given m, e, p, and q, if we choose a different e' such that e' = e + k * phi(n) where phi(n) = (p-1) * (q-1),
 * the result of candp(m, e', p, q) should be the same as candp(m, e, p, q), assuming that m and n are coprime and (e, phi(n)) are as well.
 *
 */
TEST_P(RSAParamTest, MR2) { // Fixed
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Calculate phi(n) */
    long long phi_n = (p - 1) * (long long)(q - 1);

    /* Get source output */
    long long source_out = candp(m, e, p, q);

    long long n = p * (long long)q;
    if (__gcd((long long)m, n) != 1 || __gcd((long long)e, phi_n) != 1) {
        GTEST_SKIP() << "Skipping test due to coprimality condition not met.";
    }

    /* Construct follow-up input */
    int k = 2; // Example, but k can be any integer.
    int follow_e = e + k * phi_n;

    /* Get follow-up output */
    long long follow_out = candp(m, follow_e, p, q);

    /* Verification */
    ASSERT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 3: If we keep m, e, p the same, and choose a different q' such that n' = p * q' is congruent to n (mod phi(n)),
 * then the output of candp(m, e, p, q') should be congruent to the output of candp(m, e, p, q) (mod phi(n)).
 *
 */
TEST_P(RSAParamTest, MR3) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Calculate phi(n) and n */
    long long phi_n = (p - 1) * (long long)(q - 1);
    long long n = p * (long long)q;

    /* Get source output */
    long long source_out = candp(m, e, p, q);

    /* Find a q' such that n' = p * q' is congruent to n (mod phi(n)) */
    int q_prime = q + 1; // Example, but in practice, we should find a suitable q' that fits the requirement.
    long long n_prime = p * (long long)q_prime;

    /* Get follow-up output */
    long long follow_out = candp(m, e, p, q_prime);

    /* Verification */
    ASSERT_EQ((source_out % phi_n), (follow_out % phi_n));
}

/**
 * @brief Metamorphic Relation 4: Multiplicative property of the modulus. Given m1, m2, e, p, and q, the product of the separate results
 * should be equivalent to the result of the product (m1 * m2) raised to the power e modulo n.
 * In other words, candp(m1, e, p, q) * candp(m2, e, p, q) should be congruent to candp(m1 * m2, e, p, q) modulo n.
 *
 */
TEST_P(RSAParamTest, MR4) {
    /* Get source input */
    RSAInput input = GetParam();
    int m1 = input.m, m2 = m1 + 1; // Example separate messages
    int e = input.e, p = input.p, q = input.q;
    long long n = p * (long long)q;

    /* Get source outputs */
    long long source_out1 = candp(m1, e, p, q);
    long long source_out2 = candp(m2, e, p, q);

    /* Calculate the expected product output modulo n */
    long long expected_product_mod_n = (source_out1 * source_out2) % n;

    /* Construct follow-up input (m1 * m2) */
    int follow_m = m1 * m2;

    /* Get follow-up output */
    long long follow_out = candp(follow_m, e, p, q);

    /* Verification */
    ASSERT_EQ(expected_product_mod_n, follow_out);
}

/**
 * @brief Metamorphic Relation 5: Given m, e, p, and q, computing candp(candp(m, e, p, q), d, p, q) where d is the modular inverse of e modulo phi(n),
 * should yield the original message m, assuming m and n are coprime.
 *
 */
TEST_P(RSAParamTest, MR5) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Calculate phi(n) */
    long long phi_n = (p - 1) * (long long)(q - 1);

    /* Get source output */
    long long encrypted = candp(m, e, p, q);

    /* Calculate modular inverse d of e modulo phi(n) */
    int d = ComputeModInverse(e, phi_n); // ComputeModInverse would be a method within the given context.

    /* Encrypt the encrypted message again with d */
    long long decrypted = candp(encrypted, d, p, q);

    /* Verification */
    ASSERT_EQ(m, decrypted);
}

/**
 * @brief Metamorphic Relation 6: Commutative property of exponentiation modulo n. Given m, e1, e2, p, and q, the result of
 * candp(candp(m, e1, p, q), e2, p, q) should equal the result of candp(candp(m, e2, p, q), e1, p, q) and also the result of
 * candp(m, e1 * e2, p, q) modulo n.
 *
 */
TEST_P(RSAParamTest, MR6) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e1 = input.e, e2 = e1 + 2; // Example, but e1 != e2
    int p = input.p, q = input.q;
    long long n = p * (long long)q;

    /* Get source outputs */
    long long encrypted_e1 = candp(m, e1, p, q);
    long long encrypted_e2 = candp(m, e2, p, q);

    /* Double encrypt the message, once with e1 then e2, and vice versa */
    long long double_encrypted_1 = candp(encrypted_e1, e2, p, q);
    long long double_encrypted_2 = candp(encrypted_e2, e1, p, q);

    /* Construct follow-up input (e1 * e2) */
    int follow_e = e1 * e2;

    /* Get follow-up output */
    long long follow_out = candp(m, follow_e, p, q);

    /* Verification */
    ASSERT_EQ(double_encrypted_1, double_encrypted_2);
    ASSERT_EQ(double_encrypted_1, follow_out);
}

/**
 * @brief Metamorphic Relation 7: Given m, e, p, and q, if we adjust m by multiplying it with a co-factor k such that gcd(k, n) = 1,
 * then the result of candp(k * m, e, p, q) should be congruent to k^e * candp(m, e, p, q) modulo n.
 *
 */
TEST_P(RSAParamTest, MR7) { // Fixed
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    long long n = p * (long long)q;

    int k = 3; // Example co-factor, but in actual we should ensure gcd(k, n) = 1.

    if (__gcd((long long)k, n) != 1) {
        GTEST_SKIP() << "Skipping test due to coprimality condition not met.";
    }

    /* Get source output */
    long long source_out = candp(m, e, p, q);

    /* Construct follow-up input */
    int follow_m = k * m;

    /* Get follow-up output */
    long long follow_out = candp(follow_m, e, p, q);

    /* Compute expected result */
    long long k_exp_mod_n = pow_mod(k, e, n); // pow_mod is a hypothetical method to compute (k^e) mod n
    long long expected_result = (k_exp_mod_n * source_out) % n;

    /* Verification */
    ASSERT_EQ(expected_result, follow_out);
}

/**
 * @brief Metamorphic Relation 8: Given m, e, p, and q, if we compute the result with p and q swapped,
 * the output should be the same since the modulus n remains unchanged.
 *
 */
TEST_P(RSAParamTest, MR8) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get source output */
    long long source_out = candp(m, e, p, q);

    /* Swap p and q */
    int temp = p;
    p = q;
    q = temp;

    /* Get follow-up output */
    long long follow_out = candp(m, e, p, q);

    /* Verification */
    ASSERT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 9: Given a fixed modulus n, changing the base m and exponent e by a common factor k
 * should not affect the outcome, as the mod operation should cancel out the common factor.
 *
 */
TEST_P(RSAParamTest, MR9) { // Fixed
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get source output */
    long long source_out = candp(m, e, p, q);

    /* Common factor k, chosen arbitrarily */
    int k = e;  // Make sure e is divisible by k

    /* Adjust m and e by a common factor k */
    int adjusted_m = m * k;
    int adjusted_e = e / k;

    /* Get follow-up output */
    long long follow_out = candp(adjusted_m, adjusted_e, p, q);

    /* Verification */
    ASSERT_EQ(source_out, follow_out);
}

/**
 * Taking gcd(m, n) = 1 for granted, MR7, MR9 might not hold true under all circumstances
 * due to integer overflow issues or if the conditions are not satisfied. They are more general representations
 * of what kind of metamorphic relations could be designed, but additional checks and constraints
 * would need to be put in place to ensure correct application.
 */

/**
 * @brief Metamorphic Relation 10: If we raise the result to the power of e modulo n, we should get the same result.
 * This is based on the property that (a^b)^c ≡ a^(b*c) mod n, assuming gcd(a, n) = 1.
 *
 */
TEST_P(RSAParamTest, MR10) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    long long n = p * (long long)q;

    /* Get source output */
    long long source_out = candp(m, e, p, q);

    /* Raise the source output to the power of e mod n */
    long long raised_out = candp(source_out, e, p, q);

    /* The raised output should be congruent to the source output mod n */
    ASSERT_EQ(raised_out % n, source_out % n);
}

/**
 * @brief Metamorphic Relation 11: The function should satisfy the identity property: candp(m, 1, p, q) should always be congruent to m mod n.
 *
 */
TEST_P(RSAParamTest, MR11) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, p = input.p, q = input.q;
    long long n = p * (long long)q;

    /* Identity exponent */
    int e = 1;

    /* Calculate candp(m, 1, p, q) which should be congruent to m mod n */
    long long result = candp(m, e, p, q);

    /* Verification */
    ASSERT_EQ(result % n, m % n);
}

/**
 * @brief Metamorphic Relation 12: Changing the base m to its multiplicative inverse modulo n, when raised to the exponent e,
 * should give us the multiplicative inverse of the original output modulo n.
 * This presumes gcd(m, n) = 1, meaning m has a multiplicative inverse modulo n.
 *
 */
TEST_P(RSAParamTest, MR12) {    // Fixed
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    long long n = p * (long long)q;

    if (__gcd((long long)m, n) != 1) {
        GTEST_SKIP() << "Skipping test due to coprimality condition not met.";
    }

    /* Calculate the multiplicative inverse of m modulo n */
    int m_inverse = ComputeModInverse(m, n); // ComputeModInverse is a hypothetical method to compute the modular inverse.

    /* Get source output */
    long long source_out = candp(m, e, p, q);

    /* Construct follow-up input: the multiplicative inverse of m */
    int follow_m = m_inverse;

    /* Calculate output using the multiplicative inverse as the base */
    long long inverse_out = candp(follow_m, e, p, q);

    /* Calculate the multiplicative inverse of the source output modulo n */
    long long source_out_inverse = ComputeModInverse(source_out, n);

    /* Verification */
    ASSERT_EQ(inverse_out, source_out_inverse);
}

/**
 * @brief Metamorphic Relation 13: Using Euler's theorem, wherein if gcd(m, n) = 1, then m^phi(n) ≡ 1 mod n,
 * we can derive that candp(m, phi(n), p, q) should be congruent to 1 mod n.
 *
 */
TEST_P(RSAParamTest, MR13) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, p = input.p, q = input.q;
    long long n = p * (long long)q;

    /* Calculate phi(n) */
    long long phi_n = (p - 1) * (long long)(q - 1);

    /* Get output for exponent phi(n) */
    long long output_phi_n = candp(m, phi_n, p, q);

    /* Verification */
    ASSERT_EQ(output_phi_n % n, 1);
}

/**
 * @brief Metamorphic Relation 14: Raising a previously computed result to a new exponent should equal the result of directly
 * raising the base to the combined exponent. Metamorphic relation based on (m^e1)^e2 ≡ m^(e1*e2) mod n.
 *
 */
TEST_P(RSAParamTest, MR14) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e1 = input.e, e2 = e1 + 3, p = input.p, q = input.q;
    long long n = p * (long long)q;

    /* Get source output for exponent e1 */
    long long source_out_e1 = candp(m, e1, p, q);

    /* Get source output for exponent e2 applied to source_out_e1 */
    long long source_out_e2 = candp(source_out_e1, e2, p, q);

    /* Calculate the combined exponent */
    int combined_exponent = e1 * e2;

    /* Get the follow-up output using the combined exponent */
    long long follow_out_combined = candp(m, combined_exponent, p, q);

    /* Verification */
    ASSERT_EQ(source_out_e2 % n, follow_out_combined % n);
}

/**
 * @brief Metamorphic Relation 15: The result of candp(m, e, p, q) should not change if we perform computation with a larger modulus
 * that is a multiple of the original modulus n and then reduce the result modulo n.
 */
TEST_P(RSAParamTest, MR15) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    long long n = p * (long long)q;

    /* Compute with the original modulus */
    long long original_result = candp(m, e, p, q);

    /* Compute with a larger modulus */
    int larger_factor = 3; // arbitrarily chosen
    long long larger_modulus = n * larger_factor;
    long long larger_modulus_result = candp(m, e, p * larger_factor, q);

    /* Reduce the result with larger modulus back to original modulo n */
    long long reduced_result = larger_modulus_result % n;

    /* Verification */
    ASSERT_EQ(original_result, reduced_result);
}

/**
 * @brief Metamorphic Relation 16: Given that modular exponentiation is periodic with period phi(n),
 * if we increase the exponent by a multiple of phi(n), we should obtain the same result.
 * This is based on the property that m^(e + k*phi(n)) ≡ m^e mod n.
 *
 */
TEST_P(RSAParamTest, MR16) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Calculate phi(n) */
    long long phi_n = (p - 1) * (long long)(q - 1);

    /* Get source output */
    long long source_out = candp(m, e, p, q);

    /* Construct follow-up input with exponent increased by a multiple of phi(n) */
    int k = 2; // Example multiple, could be any integer.
    int new_e = e + k * phi_n;

    /* Get follow-up output */
    long long follow_out = candp(m, new_e, p, q);

    /* Verification */
    ASSERT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 17: Given two distinct bases m1 and m2, the product of their respective
 * modular exponentiation results should equal the modular exponentiation of the product of the bases.
 * In other words, (candp(m1, e, p, q) * candp(m2, e, p, q)) mod n should be equal to candp((m1 * m2) mod n, e, p, q).
 *
 */
TEST_P(RSAParamTest, MR17) {
    /* Get source input */
    RSAInput input = GetParam();
    int m1 = input.m, m2 = m1 + 2, e = input.e, p = input.p, q = input.q; // Assume m2 != m1
    long long n = p * (long long)q;

    /* Get the modular exponentiation of m1 and m2 */
    long long result_m1 = candp(m1, e, p, q);
    long long result_m2 = candp(m2, e, p, q);

    /* Calculate the product modulo n */
    long long product_mod_n = (result_m1 * result_m2) % n;

    /* Compute the modular exponentiation of the product of m1 and m2 modulo n */
    long long product_m1_m2 = (m1 * (long long)m2) % n;
    long long mod_exp_product = candp(product_m1_m2, e, p, q);

    /* Verification */
    ASSERT_EQ(product_mod_n, mod_exp_product);
}

/**
 * @brief Metamorphic Relation 18: If a constant c is coprime to n and we compute the modular exponentiation of (c * m),
 * the result should be the original result multiplied by c raised to the power of e, all modulo n.
 *
 */
TEST_P(RSAParamTest, MR18) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    long long n = p * (long long)q;

    /* Get source output */
    long long source_out = candp(m, e, p, q);

    /* A constant c that is coprime to n */
    int c = 2; // For actual testing, it needs to be ensured that gcd(c, n) = 1

    /* Get the result of (c * m) */
    long long result_c_m = candp((c * m) % n, e, p, q);

    /* Get the expected result */
    long long c_raised = pow_mod(c, e, n); // pow_mod is a hypothetical function that computes (base^exp) mod modulus
    long long expected_result = (c_raised * source_out) % n;

    /* Verification */
    ASSERT_EQ(result_c_m, expected_result);
}

/**
 * @brief Metamorphic Relation 19: Exponentiation by a negative exponent, where e is replaced by its modular multiplicative inverse modulo phi(n),
 * should return the modular multiplicative inverse of the outcome given exponent e.
 * This relies on the property that m^(-1) ≡ m^(phi(n) - 1) mod n and that m^(e * e^(-1)) ≡ m^1 mod n.
 *
 */
TEST_P(RSAParamTest, MR19) { // Fixed
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    int n = p * q;

    /* Calculate phi(n) */
    long long phi_n = (p - 1) * (long long)(q - 1);

    /* Get source output */
    long long source_out = candp(m, e, p, q);

    /* Calculate e's modular multiplicative inverse modulo phi(n) */
    int e_inverse = ComputeModInverse(e, phi_n); // ComputeModInverse would be a function in the given context.

    /* Compute the result using the inverse exponent */
    long long result_inverse_exp = candp(m, e_inverse, p, q);

    /* Calculate the expected result */
    long long source_out_inverse = ComputeModInverse(source_out, n);

    /* Verification */
    ASSERT_EQ(result_inverse_exp, source_out_inverse);
}

/**
 * @brief Metamorphic Relation 20: Verifying the associative property of modular exponentiation. Given three exponents e1, e2, e3,
 * the sequence of operations ((m^e1)^e2)^e3 should be equivalent to m^(e1*e2*e3) modulo n.
 *
 */
TEST_P(RSAParamTest, MR20) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e1 = input.e, e2 = e1 + 4, e3 = e1 + 5, p = input.p, q = input.q; // Using distinct e1, e2, e3
    long long n = p * (long long)q;

    /* Perform the operations in sequence */
    long long result_e1 = candp(m, e1, p, q);
    long long result_e1_e2 = candp(result_e1, e2, p, q);
    long long final_result = candp(result_e1_e2, e3, p, q);

    /* Compute directly using the combined exponent */
    long long combined_exponent = e1 * e2 * e3;
    long long combined_result = candp(m, combined_exponent, p, q);

    /* Verification */
    ASSERT_EQ(final_result % n, combined_result % n);
}

/**
 * @brief Note on MR18, MR19, and MR20:
 * These metamorphic relations are constructed based on specific arithmetic properties and make strong assumptions about the coprimality of
 * certain numbers and the existence of modular inverses. Care should be taken to ensure that these assumptions are valid in the testing environment
 * and that the functions computing powers and inverses are implemented correctly to prevent false negative test results.
 */
/**
 * @brief Metamorphic Relation 21: Verifying the distributive property over multiplication for different bases and same exponent.
 * Given two different bases m1 and m2 and the same exponent e, the result of (m1 * m2)^e should be congruent to
 * (m1^e) * (m2^e) modulo n.
 */
TEST_P(RSAParamTest, MR21) {
    /* Get source input */
    RSAInput input = GetParam();
    int m1 = input.m, m2 = m1 + 3, e = input.e, p = input.p, q = input.q;
    long long n = p * (long long)q;

    /* Perform the exponentiations separately and then multiply */
    long long result_m1 = candp(m1, e, p, q);
    long long result_m2 = candp(m2, e, p, q);
    long long combined_results = (result_m1 * result_m2) % n;

    /* Multiply first, then perform the exponentiation */
    long long m1_times_m2 = (m1 * (long long)m2) % n;
    long long result_product_exponentiated = candp(m1_times_m2, e, p, q);

    /* Verification */
    ASSERT_EQ(combined_results, result_product_exponentiated);
}

/**
 * @brief Metamorphic Relation 22: For any integer z such that z is a multiple of n (modulus), the result of candp(m+z, e, p, q)
 * should be the same as candp(m, e, p, q) since z mod n is 0 and should therefore not affect the result.
 */
TEST_P(RSAParamTest, MR22) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    long long n = p * (long long)q;

    /* Get source output */
    long long source_out = candp(m, e, p, q);

    /* Calculate m+z, where z is a multiple of n */
    int z = 2 * n; // As an example
    int m_plus_z = m + z;

    /* Get the result with adjusted base m+z */
    long long adjusted_out = candp(m_plus_z, e, p, q);

    /* Verification */
    ASSERT_EQ(source_out, adjusted_out);
}

/**
 * @brief Metamorphic Relation 23: When e is 0, according to the convention of modular exponentiation, candp(m, 0, p, q) should be 1,
 * since any number to the power of 0 is 1.
 */
TEST_P(RSAParamTest, MR23) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, p = input.p, q = input.q;

    /* The exponent is zero */
    int e = 0;

    /* Perform the exponentiation with exponent 0 */
    long long result = candp(m, e, p, q);

    /* Verification */
    ASSERT_EQ(result, 1);
}

/**
 * @brief Metamorphic Relation 24: Given the same base m and modulus n, consecutive powers e1, e2, ... , ei should yield a sequence of results
 * where each result is congruent to the previous result multiplied by m mod n.
 */
TEST_P(RSAParamTest, MR24) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, p = input.p, q = input.q;
    long long n = p * (long long)q;

    /* Choose a sequence of increasing exponents */
    int e1 = input.e, e2 = e1 + 1, e3 = e2 + 1; // Example sequence

    /* Calculate the results for consecutive powers */
    long long result_e1 = candp(m, e1, p, q);
    long long result_e2 = candp(m, e2, p, q);
    long long result_e3 = candp(m, e3, p, q);

    /* Verification */
    ASSERT_EQ(result_e2, (result_e1 * m) % n);
    ASSERT_EQ(result_e3, (result_e2 * m) % n); // Each result should relate to the previous as described
}

// Note: These metamorphic relations are also based on mathematical properties that need to be upheld for the relations to be valid.
// It is important to consider the potential for overflow or computational errors when implementing the corresponding tests.
/**
 * @brief Metamorphic Relation 25: If you exponentiate the same base m with two distinct exponents e1 and e2 multiple times,
 * the sequence of results should be equivalent to direct exponentiation of m with the product e1*e2*e1*e2*... modulo n.
 */
TEST_P(RSAParamTest, MR25) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e1 = input.e, e2 = e1 + 7, p = input.p, q = input.q; // Example, ensuring e1 and e2 are distinct
    long long n = p * (long long)q;

    /* Perform repeated exponentiation */
    long long result_e1 = candp(m, e1, p, q);
    long long result_e1_e2 = candp(result_e1, e2, p, q);
    long long result_e1_e2_e1 = candp(result_e1_e2, e1, p, q);
    long long result_e1_e2_e1_e2 = candp(result_e1_e2_e1, e2, p, q);

    /* Compute result of single exponentiation with combined exponent */
    int combined_exponent = e1 * e2 * e1 * e2;
    long long combined_result = candp(m, combined_exponent, p, q);

    /* Verification */
    ASSERT_EQ(result_e1_e2_e1_e2 % n, combined_result % n);
}

/**
 * @brief Metamorphic Relation 26: If the base m is elevated to an exponent e and then the result is reduced by modulo n,
 * performing the exponentiation afterward should yield the same result.
 */
TEST_P(RSAParamTest, MR26) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    long long n = p * (long long)q;

    /* Raise the base m to the exponent e first and then reduce mod n */
    long long result_e = pow_mod(m, e, LLONG_MAX); // Assuming pow_mod can handle large exponents without overflow
    long long result_mod_n = result_e % n;

    /* Perform the exponentiation directly via the function */
    long long direct_result = candp(m, e, p, q);

    /* Verification */
    ASSERT_EQ(result_mod_n, direct_result);
}

/**
 * @brief Metamorphic Relation 27: If m1 is the multiplicative inverse of m2 modulo n, then raising each to the same
 * exponent e should result in multiplicative inverses modulo n.
 */
TEST_P(RSAParamTest, MR27) {
    /* Get source input */
    RSAInput input = GetParam();
    int m2 = input.m, e = input.e, p = input.p, q = input.q;
    long long n = p * (long long)q;

    /* Calculate the multiplicative inverse of m2 modulo n */
    int m1 = ComputeModInverse(m2, n);

    /* Perform the exponentiation on both m1 and m2 */
    long long result_m1 = candp(m1, e, p, q);
    long long result_m2 = candp(m2, e, p, q);

    /* The results should be multiplicative inverses modulo n */
    long long check_inverse = (result_m1 * result_m2) % n;

    /* Verification */
    ASSERT_EQ(check_inverse, 1);
}

/**
 * @brief Metamorphic Relation 28: For a prime base m and a prime modulus n, any exponent e greater than 0 should yield a result
 * different from m unless e is a multiple of phi(n).
 */
TEST_P(RSAParamTest, MR28) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m;              // Received m should be a prime for this relation
    int e = input.e + 1;          // Ensure that e is not a multiple of phi(n)
    int p = input.p, q = input.q; // p and q should be primes to make n prime
    long long n = p * (long long)q;
    long long phi_n = (p - 1) * (long long)(q - 1);

    /* Perform the exponentiation */
    long long result = candp(m, e, p, q);

    /* Verification */
    if (e % phi_n != 0) {
        ASSERT_NE(result, m);
    } else {
        // Skipped because e is a multiple of phi(n), where the relation does not hold
    }
}

// Note: The metamorphic relations provided consider mathematical properties of modular exponentiation that should hold true.
// However, they may not be comprehensive. They are sufficient to test the correctness of the implementation considering various aspects.
// Edge cases and overflow conditions should be carefully checked when implementing these tests in practice.
/**
 * @brief Metamorphic Relation 29: Given two distinct bases m1 and m2, if they are congruent modulo n, then the
 * results of candp(m1, e, p, q) and candp(m2, e, p, q) should also be congruent modulo n.
 */
TEST_P(RSAParamTest, MR29) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    long long n = p * (long long)q;

    /* m1 and m2 are distinct but congruent modulo n */
    int m1 = m;
    int m2 = m1 + (int)n; // Assume that adding n to m1 does not cause overflow

    /* Perform the exponentiation for m1 and m2 */
    long long result_m1 = candp(m1, e, p, q);
    long long result_m2 = candp(m2, e, p, q);

    /* Verification */
    ASSERT_EQ(result_m1 % n, result_m2 % n);
}

/**
 * @brief Metamorphic Relation 30: For two distinct exponents e1 and e2 that are congruent modulo phi(n),
 * the result of candp(m, e1, p, q) should be congruent to the result of candp(m, e2, p, q) modulo n.
 */
TEST_P(RSAParamTest, MR30) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    long long n = p * (long long)q;
    long long phi_n = (p - 1) * (long long)(q - 1);

    /* e1 and e2 are distinct but congruent modulo phi(n) */
    int e1 = e;
    int e2 = e1 + (int)phi_n; // Assume that e is sufficiently small to prevent overflow

    /* Perform the exponentiation for e1 and e2 */
    long long result_e1 = candp(m, e1, p, q);
    long long result_e2 = candp(m, e2, p, q);

    /* Verification */
    ASSERT_EQ(result_e1 % n, result_e2 % n);
}

/**
 * @brief Metamorphic Relation 31: Increasing the base m by a factor f that is a multiple of n should not alter the result.
 * The results of candp(m, e, p, q) and candp(m + f*n, e, p, q) should be equal.
 */
TEST_P(RSAParamTest, MR31) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    long long n = p * (long long)q;

    /* f is an arbitrary factor and f*n is added to m */
    int f = 2; // Example factor
    int m_adjusted = m + f * n;

    /* Perform the exponentiation with the original and adjusted m */
    long long original_result = candp(m, e, p, q);
    long long adjusted_result = candp(m_adjusted, e, p, q);

    /* Verification */
    ASSERT_EQ(original_result, adjusted_result);
}

/**
 * @brief Metamorphic Relation 32: Exponentiation by a very large exponent that is a power of 2 should not affect the result more than a single multiplication.
 * The result of m^(2^k) mod n for some large k should be congruent to m^2 mod n.
 */
TEST_P(RSAParamTest, MR32) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, p = input.p, q = input.q;
    long long n = p * (long long)q;

    /* Calculate a very large exponent that is a power of 2 */
    int k = 10;                    // Example: 2^10 is 1024, which is a large exponent
    int large_exponent = (1 << k); // 1 shifted left k times results in 2^k

    /* Perform the exponentiation with the large exponent */
    long long large_exp_result = candp(m, large_exponent, p, q);

    /* Perform the exponentiation with a square */
    int e2 = 2;
    long long square_result = candp(m, e2, p, q);

    /* Verification */
    ASSERT_EQ(large_exp_result % n, square_result % n);
}

// Note: Implementation of these metamorphic relations in tests should take into account that they are built on some mathematical assumptions.
// Ensure that these relations are applied in cases where the mathematical properties hold true and manage potential integer overflows carefully.
/**
 * @brief Metamorphic Relation 33: Swapping the factors of the modulus should have no impact on the result of the modular exponentiation.
 * candp(m, e, p, q) should be equal to candp(m, e, q, p).
 */
TEST_P(RSAParamTest, MR33) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Perform the exponentiation with the original order of factors */
    long long original_result = candp(m, e, p, q);

    /* Perform the exponentiation with the swapped factors */
    long long swapped_result = candp(m, e, q, p);

    /* Verification */
    ASSERT_EQ(original_result, swapped_result);
}

/**
 * @brief Metamorphic Relation 34: For any integers k1 and k2, if e1 = e + k1*phi(n) and e2 = e + k2*phi(n),
 * then candp(m, e1, p, q) should be equal to candp(m, e2, p, q).
 */
TEST_P(RSAParamTest, MR34) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;
    long long n = p * (long long)q;
    long long phi_n = (p - 1) * (long long)(q - 1);

    /* Calculate e1 and e2 by adding multiples of phi(n) to e */
    int k1 = 3, k2 = 5; // Example multipliers
    int e1 = e + k1 * phi_n;
    int e2 = e + k2 * phi_n;

    /* Perform exponentiation with e1 and e2 */
    long long result_e1 = candp(m, e1, p, q);
    long long result_e2 = candp(m, e2, p, q);

    /* Verification */
    ASSERT_EQ(result_e1, result_e2);
}

/**
 * @brief Metamorphic Relation 35: For a base m that is a factor of n, the modular exponentiation always yields 0.
 */
TEST_P(RSAParamTest, MR35) {
    /* Get source input */
    RSAInput input = GetParam();
    int e = input.e, p = input.p, q = input.q;
    long long n = p * (long long)q;

    /* Set m as a factor of n */
    int m = p;

    /* Perform the exponentiation */
    long long result = candp(m, e, p, q);

    /* Verification */
    ASSERT_EQ(result, 0);
}

/**
 * @brief Metamorphic Relation 36: Using the element m and its additive inverse modulo n, the modulo exponentiation results
 * should be multiplicatively inverse to each other modulo n assuming e is odd and gcd(m,n)=1. That is, candp(m, e, p, q) *
 * candp(n-m, e, p, q) should be congruent to 1 mod n for odd e.
 */
TEST_P(RSAParamTest, MR36) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = 3, p = input.p, q = input.q; // Choose an odd exponent
    long long n = p * (long long)q;

    /* Compute the additive inverse of m modulo n */
    int m_inverse = (n - m) % (int)n; // Ensure m_inverse is between 0 and (n - 1)

    /* Perform exponentiation for m and its additive inverse */
    long long result_m = candp(m, e, p, q);
    long long result_m_inverse = candp(m_inverse, e, p, q);

    /* Verification */
    ASSERT_EQ((result_m * result_m_inverse) % n, 1);
}

/**
 * @brief Note:
 * Testing implementations should be careful to assume that the input e is positive,
 * and the values of p and q should be such that n = p*q is within the bounds of the integer
 * limits to avoid overflow. In practice, e should typically be coprime to phi(n), among other constraints
 * for cryptographic applications. The operations should also handle cases where the usual assumptions
 * like gcd(m,n) = 1 might not hold, and those cases should be explicitly accounted for.
 */

/**
 * @brief Metamorphic Relation 37: Given a fixed modulus n, if the base m is nimonic (i.e., m is congruent to 1 modulo n),
 * then candp(m, e, p, q) should be equal to m mod n for any exponent e.
 */
TEST_P(RSAParamTest, MR37) {
    /* Get source input */
    RSAInput input = GetParam();
    int e = input.e, p = input.p, q = input.q;
    long long n = p * (long long)q;

    /* Set base m to be congruent to 1 modulo n (m is nimonic) */
    int m = 1 + (int)n; // n + 1 to ensure m is greater than n and still nimonic

    /* Perform modular exponentiation */
    long long result = candp(m, e, p, q);

    /* Verification */
    ASSERT_EQ(result % n, m % n);
}

/**
 * @brief Metamorphic Relation 38: For any base m and exponents e1 and e2 where e1 is equal to e2 modulo phi(n),
 * the results of candp(m, e1, p, q) and candp(m, e2, p, q) should be congruent modulo n.
 */
TEST_P(RSAParamTest, MR38) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e1 = input.e, p = input.p, q = input.q;
    long long phi_n = (p - 1) * (long long)(q - 1);

    /* Make e2 congruent to e1 modulo phi(n) */
    int e2 = e1 + phi_n; // e2 is e1 plus a multiple of phi(n)

    /* Perform modular exponentiation */
    long long result_e1 = candp(m, e1, p, q);
    long long result_e2 = candp(m, e2, p, q);

    /* Verification */
    ASSERT_EQ(result_e1 % (p * (long long)q), result_e2 % (p * (long long)q));
}

/**
 * @brief Metamorphic Relation 39: For any base m, if the base is equal to 0 modulo n, then for
 * any exponent e, candp(m, e, p, q) should always yield 0.
 */
TEST_P(RSAParamTest, MR39) {
    /* Get source input */
    RSAInput input = GetParam();
    int e = input.e, p = input.p, q = input.q;

    /* Set base m to be 0 modulo n */
    int m = 0; // m is directly set to 0, which is congruent to 0 modulo any n

    /* Perform modular exponentiation */
    long long result = candp(m, e, p, q);

    /* Verification */
    ASSERT_EQ(result, 0);
}

/**
 * @brief Metamorphic Relation 40: Given the multiplicative property of exponents, for bases m1 and m2
 * and exponent e, the result of candp(m1 * m2, e, p, q) should be the same as the product of
 * candp(m1, e, p, q) and candp(m2, e, p, q) modulo n.
 */
TEST_P(RSAParamTest, MR40) {
    /* Get source input */
    RSAInput input = GetParam();
    int m1 = input.m, m2 = m1 + 4, e = input.e, p = input.p, q = input.q; // m2 is different from m1
    long long n = p * (long long)q;

    /* Perform modular exponentiation on m1 and m2 */
    long long result_m1 = candp(m1, e, p, q);
    long long result_m2 = candp(m2, e, p, q);

    /* Perform modular exponentiation on the product of m1 and m2 */
    long long result_product = candp((m1 * (long long)m2) % n, e, p, q);

    /* Verification */
    ASSERT_EQ(result_product, (result_m1 * result_m2) % n);
}

// Note: As with previous metamorphic relations, it's crucial to take into consideration
// the possibility of integer overflow when dealing with large numbers, and to ensure the
// mathematical properties assumed in these relations are preserved by the implementation.
/**
 * @brief Metamorphic Relation 41: For two coprime integers m and n, the results of candp(m, 1, p, q) and m % (p*q) should be the same.
 * This follows from the definition of modular reduction.
 */
TEST_P(RSAParamTest, MR41) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m; // Assume m is coprime to n
    int p = input.p, q = input.q;
    long long n = p * (long long)q;

    /* Compute candp(m, 1, p, q) */
    long long result_m = candp(m, 1, p, q);

    /* Verify that the result is congruent to m % n */
    ASSERT_EQ(result_m, m % n);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, RSAParamTest, testing::ValuesIn(gen_tcs_randomly()));