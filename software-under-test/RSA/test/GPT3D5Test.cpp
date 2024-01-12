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
long long rsaEncrypt(int m, int e, int p, int q) {
    return candp(m, e, p, q);
}

int generateNewE(int e) {
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, prime_nums.size() - 1);
    int new_e = e;
    while (new_e == e)
        new_e = prime_nums[dist(rng)];
    return new_e;
}

int generateNewExponent(int e, int val) {
    return generateNewE(e);
}

int generateDifferentPrivateKey(int e, int p, int q) {
    return generateNewE(e);
}

int generateDifferentPublicKeyExponent(int e, int val) {
    return generateNewE(e);
}

int generateNewPlaintext(int m) {
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, 1000000);
    int new_m = m;
    while (new_m == m)
        new_m = dist(rng);
    return new_m;
}

int generateDifferentPlaintext(int m) {
    return generateNewPlaintext(m);
}

int generateRandomConstant() {
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, 100);
    return dist(rng);
}

int generateRandomNumber() {
    return generateRandomConstant();
}

int generateRandomInteger() {
    return generateRandomConstant();
}

int generateRandomCoprime(int val) {
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, prime_nums.size() - 1);
    int res = prime_nums[dist(rng)];
    while (res == val)
        res = prime_nums[dist(rng)];
    return res;
}

bool areCoprime(int v1, int v2) {
    return __gcd(v1, v2) == 1;
}

int flipSingleBit(int val) {
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, 10);
    return val ^ (1 << dist(rng));
}

long long modularInverse(long long v1, long long v2) {
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

long long modInverse(long long v1, long long v2) {
    return modularInverse(v1, v2);
}

int calculateInverseModulo(long long v1, long long v2) {
    return modularInverse(v1, v2);
}

int modExp(long long base, int exponent, int n) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % n;
        }
        base = (base * base) % n;
        exponent = exponent / 2;
    }
    return result;
}

int rsaDecrypt(long long c, int e, int p, int q) {
    return modExp(c, e, p * q);
}

int reverseInteger(int v) {
    int res = 0;
    while (v > 0) {
        res = res * 10 + v % 10;
        v /= 10;
    }
    return res;
}

int applyPermutation(int v) {
    vector<int> digits;
    while (v > 0) {
        digits.push_back(v % 10);
        v /= 10;
    }
    shuffle(digits.begin(), digits.end(), default_random_engine());
    int res = 0;
    for (int i = 0; i < digits.size(); i++) {
        res = res * 10 + digits[i];
    }
    return res;
}
/**************************************************/

/**
 * @brief Metamorphic Relation 2: Keeping p, q, and e the same, giving a new plaintext which is 0, the ciphertext is 0.
 *
 */
TEST_P(RSAParamTest, MR2) {
    /* Get source input */
    RSAInput input = GetParam();
    int e = input.e, p = input.p, q = input.q;

    /* Get source output */
    long long source_out = rsaEncrypt(0, e, p, q);

    /* Verification */
    ASSERT_EQ(0, source_out);
}

/**
 * @brief Metamorphic Relation 3: Keeping p, q the same, giving a new values of e, the ciphertext is different.
 *
 */
TEST_P(RSAParamTest, MR3) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, p = input.p, q = input.q;

    /* Get source output */
    long long source_out = rsaEncrypt(m, input.e, p, q);

    /* Construct follow-up input */
    int follow_e = generateNewE(input.e); // Function to generate a new value of e

    /* Get follow-up output */
    long long follow_out = rsaEncrypt(m, follow_e, p, q);

    /* Verification */
    ASSERT_NE(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 4: Keeping e, p, and q the same, giving a new plaintext and then decrypting the resulting ciphertext, the decrypted plaintext is
 * the same as the original.
 *
 */
TEST_P(RSAParamTest, MR4) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get source output */
    long long source_out = rsaEncrypt(m, e, p, q);

    /* Decrypt source output */
    int decrypted_source = rsaDecrypt(source_out, e, p, q);

    /* Verification */
    ASSERT_EQ(m, decrypted_source);
}

/**
 * @brief Metamorphic Relation 5: Keeping m, e, and p, q the same, changing the ciphertext to its square, the resulting plaintext after decryption is not the
 * same as the original plaintext.
 *
 */
TEST_P(RSAParamTest, MR5) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get source output */
    long long source_out = rsaEncrypt(m, e, p, q);

    /* Square the source output */
    long long squared_out = source_out * source_out;

    /* Decrypt squared output */
    int decrypted_squared = rsaDecrypt(squared_out, e, p, q);

    /* Verification */
    ASSERT_NE(m, decrypted_squared);
}

/**
 * @brief Metamorphic Relation 6: Keeping m, e, p, and q the same, changing the order of encryption with the same public key, the resulting ciphertexts are
 * different.
 *
 */
TEST_P(RSAParamTest, MR6) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get first source output */
    long long source_out1 = rsaEncrypt(m, e, p, q);

    /* Get second source output (changing the order of encryption) */
    long long source_out2 = rsaEncrypt(source_out1, e, p, q);

    /* Verification */
    ASSERT_NE(source_out1, source_out2);
}

/**
 * @brief Metamorphic Relation 7: Keeping e, p, and q the same, changing the plaintext and then decrypting the resulting ciphertext with the private key, the
 * decrypted plaintext is the same as the original.
 *
 */
TEST_P(RSAParamTest, MR7) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get source output */
    long long source_out = rsaEncrypt(m, e, p, q);

    /* Decrypt source output with private key */
    int decrypted_source = rsaDecrypt(source_out, e, p, q);

    /* Verification */
    ASSERT_EQ(m, decrypted_source);
}

/**
 * @brief Metamorphic Relation 8: Keeping e, p, and q the same, switching the plaintext and the public key, the resulting ciphertexts are different.
 *
 */
TEST_P(RSAParamTest, MR8) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get source output */
    long long source_out = rsaEncrypt(m, e, p, q);

    /* Switch plaintext and public key */
    long long switched_out = rsaEncrypt(e, m, q, p);

    /* Verification */
    ASSERT_NE(source_out, switched_out);
}

/**
 * @brief Metamorphic Relation 9: Keeping m, e, p, and q the same, changing the exponent for decryption, the resulting decrypted plaintext is not the same as
 * the original.
 *
 */
TEST_P(RSAParamTest, MR9) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get source output */
    long long source_out = rsaEncrypt(m, e, p, q);

    /* Decrypt source output with a different exponent */
    int decrypted_different_exp = rsaDecrypt(source_out, generateNewExponent(e, (p - 1) * (q - 1)), p, q);

    /* Verification */
    ASSERT_NE(m, decrypted_different_exp);
}

/**
 * @brief Metamorphic Relation 10: Keeping m, e, p, and q the same, changing the ciphertext to its inverse modulo (p-1)*(q-1), the resulting plaintext after
 * decryption is the inverse modulo m.
 *
 */
TEST_P(RSAParamTest, MR10) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get source output */
    long long source_out = rsaEncrypt(m, e, p, q);

    /* Calculate inverse modulo (p-1)*(q-1) */
    long long inverse_out = modInverse(source_out, (p - 1) * (q - 1));

    /* Decrypt inverse output */
    int decrypted_inverse = rsaDecrypt(inverse_out, e, p, q);

    /* Verification */
    ASSERT_EQ(modularInverse(m, m), decrypted_inverse);
}

/**
 * @brief Metamorphic Relation 11: Keeping e, p, and q the same, changing the plaintext and exponent, the resulting ciphertext using the original exponent is
 * the same as the original ciphertext raised to the power of the new exponent.
 *
 */
TEST_P(RSAParamTest, MR11) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get source output */
    long long source_out = rsaEncrypt(m, e, p, q);

    /* Change exponent and plaintext */
    int new_m = generateNewPlaintext(m);
    int new_e = generateNewExponent(e, (p - 1) * (q - 1));

    /* Get new output using the changed exponent and plaintext */
    long long new_out = rsaEncrypt(new_m, new_e, p, q);

    /* Verification */
    ASSERT_EQ(source_out, modExp(source_out, new_e, p * q)); // modExp calculates (base^exponent) mod n
}

/**
 * @brief Metamorphic Relation 12: Keeping e, p, and q the same, multiplying the plaintext by a constant and then encrypting, the resulting ciphertext is equal
 * to the original ciphertext raised to the power of the constant.
 *
 */
TEST_P(RSAParamTest, MR12) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    long long c = generateRandomConstant(); // generate a constant

    /* Get source output */
    long long source_out = rsaEncrypt(m, e, p, q);

    /* Multiply plaintext by constant */
    int new_m = m * c;

    /* Get new output */
    long long new_out = rsaEncrypt(new_m, e, p, q);

    /* Verification */
    ASSERT_EQ(new_out, modExp(source_out, c, p * q)); // modExp calculates (base^exponent) mod n
}

/**
 * @brief Metamorphic Relation 13: Keeping e and p the same, replacing the plaintext with its encryption and then encrypting, the resulting ciphertext is the
 * same as the original ciphertext.
 *
 */
TEST_P(RSAParamTest, MR13) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get source output */
    long long source_out = rsaEncrypt(m, e, p, q);

    /* Replace the plaintext with its encryption */
    long long replaced_m = rsaEncrypt(m, e, p, q);

    /* Get new output */
    long long new_out = rsaEncrypt(replaced_m, e, p, q);

    /* Verification */
    ASSERT_EQ(source_out, new_out);
}

/**
 * @brief Metamorphic Relation 14: Keeping e and the product p*q the same, replacing the plaintext with another plaintext and then encrypting, the resulting
 * ciphertext is different from the original ciphertext.
 *
 */
TEST_P(RSAParamTest, MR14) {
    /* Get source input */
    RSAInput input = GetParam();
    int m1 = input.m, e = input.e, p = input.p, q = input.q;

    /* Get original output */
    long long original_out = rsaEncrypt(m1, e, p, q);

    /* Replace the plaintext with a different plaintext */
    int m2 = generateDifferentPlaintext(m1);

    /* Get new output */
    long long new_out = rsaEncrypt(m2, e, p, q);

    /* Verification */
    ASSERT_NE(original_out, new_out);
}

/**
 * @brief Metamorphic Relation 15: Keeping p, q, and m the same, changing the exponent and then decrypting the resulting ciphertext, the decrypted plaintext is
 * the same as the original plaintext raised to the power of the new exponent.
 *
 */
TEST_P(RSAParamTest, MR15) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get source output */
    long long source_out = rsaEncrypt(m, e, p, q);

    /* Change the exponent for decryption */
    int new_e = generateNewExponent(e, (p - 1) * (q - 1));

    /* Decrypt with the new exponent */
    int decrypted_new_exponent = rsaDecrypt(source_out, new_e, p, q);

    /* Verification */
    ASSERT_EQ(decrypted_new_exponent, modExp(m, new_e, p * q)); // modExp calculates (base^exponent) mod n
}

/**
 * @brief Metamorphic Relation 16: Keeping p, q, and e the same, multiplying the plaintext by a constant and then decrypting the resulting ciphertext, the
 * decrypted plaintext is equal to the original plaintext multiplied by the constant.
 *
 */
TEST_P(RSAParamTest, MR16) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    long long c = generateRandomConstant(); // generate a constant

    /* Get source output */
    long long source_out = rsaEncrypt(m, e, p, q);

    /* Multiply plaintext by constant */
    int new_m = m * c;

    /* Decrypt new output */
    int decrypted_new_m = rsaDecrypt(source_out, e, p, q);

    /* Verification */
    ASSERT_EQ(decrypted_new_m, new_m);
}

/**
 * @brief Metamorphic Relation 17: Keeping e, p, and q the same, encrypting the plaintext with both public and private keys, the resulting ciphertexts are the
 * same.
 *
 */
TEST_P(RSAParamTest, MR17) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get source output using public key */
    long long public_key_out = rsaEncrypt(m, e, p, q);

    /* Get source output using private key */
    long long private_key_out = rsaDecrypt(m, e, p, q);

    /* Verification */
    ASSERT_EQ(public_key_out, private_key_out);
}

/**
 * @brief Metamorphic Relation 18: Keeping e, p, and q the same, encrypting the plaintext with the public key and also with a different public key, the
 * resulting ciphertexts are different.
 *
 */
TEST_P(RSAParamTest, MR18) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    long long different_e = generateNewExponent(e, (p - 1) * (q - 1)); // generate a different public key exponent

    /* Get output using the original public key */
    long long original_out = rsaEncrypt(m, e, p, q);

    /* Get output using a different public key */
    long long different_out = rsaEncrypt(m, different_e, p, q);

    /* Verification */
    ASSERT_NE(original_out, different_out);
}

/**
 * @brief Metamorphic Relation 19: Keeping e, p, and q the same, encrypting the plaintext with the public key and then decrypting the resulting ciphertext with
 * the private key, the decrypted plaintext is the same as the original plaintext.
 *
 */
TEST_P(RSAParamTest, MR19) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get output using the public key */
    long long public_out = rsaEncrypt(m, e, p, q);

    /* Decrypt using the private key */
    int private_decrypt = rsaDecrypt(public_out, e, p, q);

    /* Verification */
    ASSERT_EQ(private_decrypt, m);
}

/**
 * @brief Metamorphic Relation 20: Keeping the product p*q the same, changing the plaintext and exponent, the resulting ciphertext is different from the
 * original ciphertext.
 *
 */
TEST_P(RSAParamTest, MR20) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get source output */
    long long source_out = rsaEncrypt(m, e, p, q);

    /* Change plaintext and exponent */
    int new_m = generateNewPlaintext(m);
    int new_e = generateNewExponent(e, (p - 1) * (q - 1));

    /* Get new output */
    long long new_out = rsaEncrypt(new_m, new_e, p, q);

    /* Verification */
    ASSERT_NE(source_out, new_out);
}

/**
 * @brief Metamorphic Relation 21: Keeping e, p, and q the same, decrypting the original ciphertext and then encrypting the resulting plaintext, the second
 * ciphertext is the same as the original ciphertext.
 *
 */
TEST_P(RSAParamTest, MR21) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get source output */
    long long encrypted = rsaEncrypt(m, e, p, q);

    /* Decrypt the original ciphertext */
    int decrypted = rsaDecrypt(encrypted, e, p, q);

    /* Encrypt the resulting plaintext */
    long long reencrypted = rsaEncrypt(decrypted, e, p, q);

    /* Verification */
    ASSERT_EQ(reencrypted, encrypted);
}

/**
 * @brief Metamorphic Relation 22: Keeping the product p*q the same, adding a multiple of p*q to the plaintext and then encrypting, the resulting ciphertext is
 * the same as encrypting the original plaintext.
 *
 */
TEST_P(RSAParamTest, MR22) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get source output */
    long long original_output = rsaEncrypt(m, e, p, q);

    /* Fix by Radon */
    int k = 2;

    /* Add a multiple of p*q to the plaintext */
    int new_m = m + k * (p * q); // add a multiple of p*q to the original plaintext

    /* Get new output */
    long long new_output = rsaEncrypt(new_m, e, p, q);

    /* Verification */
    ASSERT_EQ(new_output, original_output);
}

/**
 * @brief Metamorphic Relation 23: Keeping e, p, and q the same, encrypting the plaintext and then raising the resulting ciphertext to an exponent, the
 * resulting ciphertext is equal to encrypting the original plaintext raised to the power of the exponent.
 *
 */
TEST_P(RSAParamTest, MR23) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    long long exponent = generateNewExponent(e, (p - 1) * (q - 1)); // generate a new exponent

    /* Get original output */
    long long original_output = rsaEncrypt(m, e, p, q);

    /* Calculate new output using the raised exponent */
    long long new_output = modExp(original_output, exponent, p * q); // modExp calculates (base^exponent) mod n

    /* Verification */
    ASSERT_EQ(new_output, rsaEncrypt(modExp(m, exponent, p * q), e, p, q));
}

/**
 * @brief Metamorphic Relation 24: Keeping e, p, and q the same, encrypting the plaintext and then multiplying the ciphertext by a constant, the resulting
 * ciphertext is the original ciphertext raised to the power of the constant.
 *
 */
TEST_P(RSAParamTest, MR24) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    long long c = generateRandomConstant(); // generate a constant

    /* Get source output */
    long long source_out = rsaEncrypt(m, e, p, q);

    /* Multiply ciphertext by constant */
    long long new_out = source_out * c;

    /* Verification */
    ASSERT_EQ(new_out, modExp(source_out, c, p * q)); // modExp calculates (base^exponent) mod n
}

/**
 * @brief Metamorphic Relation 25: Keeping e, p, and q the same, decrypting the ciphertext and then encrypting the resulting plaintext, the resulting ciphertext
 * is equal to the original ciphertext.
 *
 */
TEST_P(RSAParamTest, MR25) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get source output */
    long long source_out = rsaEncrypt(m, e, p, q);

    /* Decrypt the ciphertext */
    int decrypted = rsaDecrypt(source_out, e, p, q);

    /* Encrypt the resulting plaintext */
    long long reencrypted = rsaEncrypt(decrypted, e, p, q);

    /* Verification */
    ASSERT_EQ(reencrypted, source_out);
}

/**
 * @brief Metamorphic Relation 26: Keeping e, p, and q the same, encrypting the plaintext and then multiplying the plaintext by a constant, the resulting
 * ciphertext is the same as encrypting the original plaintext.
 */
TEST_P(RSAParamTest, MR26) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get original output */
    long long original_output = rsaEncrypt(m, e, p, q);

    /* Fix by Radon */
    int k = 2;

    /* Multiply plaintext by a constant */
    int scaled_m = k * m; // Multiply the plaintext by a constant

    /* Get new output */
    long long new_output = rsaEncrypt(scaled_m, e, p, q);

    /* Verification */
    ASSERT_EQ(original_output, new_output);
}

/**
 * @brief Metamorphic Relation 27: Keeping e, p, and q the same, encrypting the plaintext followed by decryption using a different private key, the resulting
 * decrypted plaintext is different from the original plaintext.
 */
TEST_P(RSAParamTest, MR27) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get original output */
    long long encrypted = rsaEncrypt(m, e, p, q);

    /* Decrypt using different private key */
    int different_d = generateDifferentPrivateKey(e, p, q);

    int decrypted = rsaDecrypt(encrypted, different_d, p, q);

    /* Verification */
    ASSERT_NE(decrypted, m);
}

/**
 * @brief Metamorphic Relation 28: Keeping e, p, and q the same, encrypting a plaintext $m$ and then encrypting the complement of $m$ (i.e., $p*q - m$), the
 * resulting ciphertexts are the same.
 */
TEST_P(RSAParamTest, MR28) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get original output */
    long long encrypted_m = rsaEncrypt(m, e, p, q);

    int complement_m = p * q - m; // Get the complement of m

    /* Get output with complement of m */
    long long encrypted_complement_m = rsaEncrypt(complement_m, e, p, q);

    /* Verification */
    ASSERT_EQ(encrypted_m, encrypted_complement_m);
}

/**
 * @brief Metamorphic Relation 29: Keeping e, p, and q the same, encrypting the same plaintext multiple times, the resulting ciphertexts are the same each time.
 */
TEST_P(RSAParamTest, MR29) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    long long original_output = rsaEncrypt(m, e, p, q);

    // Encrypt the same plaintext multiple times
    long long new_output1 = rsaEncrypt(m, e, p, q);
    long long new_output2 = rsaEncrypt(m, e, p, q);

    /* Verification */
    ASSERT_EQ(original_output, new_output1);
    ASSERT_EQ(original_output, new_output2);
}

/**
 * @brief Metamorphic Relation 30: Keeping e, p, and q the same, encrypting a plaintext $m$ and then encrypting the same plaintext in reverse order, the
 * resulting ciphertexts are different.
 */
TEST_P(RSAParamTest, MR30) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Encrypt the plaintext m */
    long long encrypted_m = rsaEncrypt(m, e, p, q);

    /* Reverse the order of the digits in m */
    int reversed_m = reverseInteger(m);

    /* Encrypt the reversed plaintext */
    long long encrypted_reversed_m = rsaEncrypt(reversed_m, e, p, q);

    /* Verification */
    ASSERT_NE(encrypted_m, encrypted_reversed_m);
}

/**
 * @brief Metamorphic Relation 31: Keeping p, q, and e the same, encrypting two different plaintexts $m_1$ and $m_2$, the resulting ciphertexts are different if
 * $m_1$ and $m_2$ are coprime.
 */
TEST_P(RSAParamTest, MR31) {
    /* Get source input */
    RSAInput input = GetParam();
    int e = input.e, p = input.p, q = input.q;

    /* Get two different plaintexts */
    int m1 = generateRandomCoprime(p * q);
    int m2 = generateRandomCoprime(p * q);

    /* Encrypt the two different plaintexts */
    long long encrypted_m1 = rsaEncrypt(m1, e, p, q);
    long long encrypted_m2 = rsaEncrypt(m2, e, p, q);

    /* Verification */
    if (areCoprime(m1, m2)) {
        ASSERT_NE(encrypted_m1, encrypted_m2);
    }
}

/**
 * @brief Metamorphic Relation 32: Keeping e, p, and q the same, encrypting the plaintext and multiplying the public key $e$ by a constant, the resulting
 * ciphertext is the original ciphertext raised to the power of the constant.
 */
TEST_P(RSAParamTest, MR32) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    long long c = generateRandomConstant(); // generate a constant

    /* Get original output */
    long long original_output = rsaEncrypt(m, e, p, q);

    /* Multiply the public key $e$ by a constant */
    int new_e = e * c;

    /* Get new output */
    long long new_output = rsaEncrypt(m, new_e, p, q);

    /* Verification */
    ASSERT_EQ(new_output, modExp(original_output, c, p * q)); // modExp calculates (base^exponent) mod n
}

/**
 * @brief Metamorphic Relation 33: Keeping e, p, and q the same, encrypting two different plaintexts $m_1$ and $m_2$, and then encrypting their product, the
 * resulting ciphertext is equal to the product of the original ciphertexts.
 */
TEST_P(RSAParamTest, MR33) {
    /* Get source input */
    RSAInput input = GetParam();
    int e = input.e, p = input.p, q = input.q;

    /* Get two different plaintexts */
    int m1 = generateRandomNumber();
    int m2 = generateRandomNumber();

    /* Encrypt the two different plaintexts */
    long long encrypted_m1 = rsaEncrypt(m1, e, p, q);
    long long encrypted_m2 = rsaEncrypt(m2, e, p, q);

    /* Encrypt the product of the plaintexts */
    long long encrypted_product = rsaEncrypt(m1 * m2, e, p, q);

    /* Verification */
    ASSERT_EQ(encrypted_product, (encrypted_m1 * encrypted_m2) % (p * q));
}

/**
 * @brief Metamorphic Relation 34: Keeping e, p, and q the same, encrypting a plaintext $m$ and its inverse modulo $n$, the resulting ciphertexts are the same.
 */
TEST_P(RSAParamTest, MR34) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get original output */
    long long encrypted_m = rsaEncrypt(m, e, p, q);

    /* Get the inverse modulo n of the plaintext m */
    int inverse_m = modInverse(m, p * q);

    /* Get new output */
    long long encrypted_inverse_m = rsaEncrypt(inverse_m, e, p, q);

    /* Verification */
    ASSERT_EQ(encrypted_m, encrypted_inverse_m);
}

/**
 * @brief Metamorphic Relation 35: Keeping p, q, and e the same, encrypting the plaintext and then swapping the values of $p$ and $q$, the resulting ciphertext
 * is the same as encrypting the original plaintext with the new values of $p$ and $q.
 */
TEST_P(RSAParamTest, MR35) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get original output */
    long long original_output = rsaEncrypt(m, e, p, q);

    /* Swap the values of p and q */
    long long new_output = rsaEncrypt(m, e, q, p);

    /* Verification */
    ASSERT_EQ(original_output, new_output);
}

/**
 * @brief Metamorphic Relation 36: Keeping e, p, and q the same, encrypting a plaintext $m$ and then encrypting the plaintext $-m$, the resulting ciphertexts
 * are the same.
 */
TEST_P(RSAParamTest, MR36) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get original output */
    long long encrypted_m = rsaEncrypt(m, e, p, q);

    /* Get the negation of the plaintext m */
    int negated_m = -m;

    /* Get new output */
    long long encrypted_negated_m = rsaEncrypt(negated_m, e, p, q);

    /* Verification */
    ASSERT_EQ(encrypted_m, encrypted_negated_m);
}

/**
 * @brief Metamorphic Relation 37: Keeping e the same, encrypting a plaintext $m$ and then encrypting the same plaintext after applying a permutation, the
 * resulting ciphertexts are different.
 */
TEST_P(RSAParamTest, MR37) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Get original output */
    long long encrypted_m = rsaEncrypt(m, e, p, q);

    /* Apply a permutation to plaintext m */
    int permuted_m = applyPermutation(m);

    /* Get new output */
    long long encrypted_permuted_m = rsaEncrypt(permuted_m, e, p, q);

    /* Verification */
    ASSERT_NE(encrypted_m, encrypted_permuted_m);
}

/**
 * @brief Metamorphic Relation 38: Keeping p, q, and e the same, encrypting a plaintext $m$ and then encrypting the plaintext $m$ with the inverse of the public
 * key $e$ modulo $(p-1)*(q-1)$, the resulting ciphertexts are the same.
 */
TEST_P(RSAParamTest, MR38) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Encrypt the plaintext m */
    long long encrypted_m = rsaEncrypt(m, e, p, q);

    /* Calculate the inverse of e modulo (p-1)*(q-1) */
    int inverse_e = calculateInverseModulo(e, (p - 1) * (q - 1));

    /* Encrypt the plaintext m with inverse of e modulo (p-1)*(q-1) */
    long long encrypted_m_with_inverse_e = rsaEncrypt(m, inverse_e, p, q);

    /* Verification */
    ASSERT_EQ(encrypted_m, encrypted_m_with_inverse_e);
}

/**
 * @brief Metamorphic Relation 39: Keeping e, p, and q the same, encrypting the plaintext and then encrypting the intermediate ciphertext with an additional
 * public key exponent, the resulting ciphertext is the same as encrypting the plaintext with both public key exponents.
 */
TEST_P(RSAParamTest, MR39) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Encrypt the plaintext m with public key exponent e */
    long long encrypted_m_with_e = rsaEncrypt(m, e, p, q);

    /* Get a new public key exponent */
    int new_e = generateRandomCoprime((p - 1) * (q - 1));

    /* Encrypt the intermediate ciphertext with the new public key exponent */
    long long encrypted_intermediate = rsaEncrypt(encrypted_m_with_e, new_e, p, q);

    /* Encrypt the plaintext m with both public key exponents */
    long long encrypted_m_with_both_exponents = rsaEncrypt(m, e * new_e, p, q);

    /* Verification */
    ASSERT_EQ(encrypted_intermediate, encrypted_m_with_both_exponents);
}

/**
 * @brief Metamorphic Relation 40: Keeping p, q, and e the same, encrypting the plaintext and then flipping a single bit in the plaintext, the resulting
 * ciphertext is different.
 */
TEST_P(RSAParamTest, MR40) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Encrypt the original plaintext m */
    long long encrypted_m = rsaEncrypt(m, e, p, q);

    /* Flip a single bit in the original plaintext m */
    int perturbed_m = flipSingleBit(m);

    /* Encrypt the perturbed plaintext */
    long long encrypted_perturbed_m = rsaEncrypt(perturbed_m, e, p, q);

    /* Verification */
    ASSERT_NE(encrypted_m, encrypted_perturbed_m);
}

/**
 * @brief Metamorphic Relation 41: Keeping e, p, and q the same, encrypting the plaintext and then multiplying the ciphertext by a random constant, the
 * resulting ciphertext is different from the original.
 */
TEST_P(RSAParamTest, MR41) {
    /* Get source input */
    RSAInput input = GetParam();
    int m = input.m, e = input.e, p = input.p, q = input.q;

    /* Encrypt the original plaintext m */
    long long encrypted_m = rsaEncrypt(m, e, p, q);

    /* Multiply the ciphertext by a random constant */
    long long perturbed_ciphertext = encrypted_m * generateRandomConstant();

    /* Verification */
    ASSERT_NE(encrypted_m, perturbed_ciphertext);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, RSAParamTest, testing::ValuesIn(gen_tcs_randomly()));