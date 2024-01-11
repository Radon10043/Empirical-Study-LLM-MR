#include <algorithm>
#include <gtest/gtest.h>
#include <random>
#include <string>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class InterleavingStringParamTest : public ::testing::TestWithParam<InterleavingStringInput> {};

/**
 * @brief Metamorphic Relation 2: Swapping the positions of A and B will not change the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR2) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_C = C;

    /* Get follow-up output */
    bool follow_out = is_interleaved(B, A, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 3: Reversing the order of C will not change the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR3) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_C = C;
    reverse(follow_C.begin(), follow_C.end());

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 4: Repeating the characters in A and B will not change the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR4) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A + A, follow_B = B + B;

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 5: Reversing the order of A and B will not change the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR5) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A, follow_B = B;
    reverse(follow_A.begin(), follow_A.end());
    reverse(follow_B.begin(), follow_B.end());

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 6: Removing the first character of A and C will not change the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR6) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A.substr(1), follow_C = C.substr(1);

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 7: Concatenating A and B together will not change the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR7) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

#if INVALID
    /* Construct follow-up input */
    string follow_A = A + B;

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, "", C);
#else
    /* Fix by Radon */
    /* Construct follow-up input */
    string follow_A = A + B, follow_B = "";

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, C);
#endif

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 8: Replacing all instances of a character with another character in A and B does not change the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR8) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    char replace_char = 'a';
    char new_char = 'b';
    string follow_A = A, follow_B = B;
    replace(follow_A.begin(), follow_A.end(), replace_char, new_char);
    replace(follow_B.begin(), follow_B.end(), replace_char, new_char);

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 9: Reversing the order of A, B, and C simultaneously will not change the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR9) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A, follow_B = B, follow_C = C;
    reverse(follow_A.begin(), follow_A.end());
    reverse(follow_B.begin(), follow_B.end());
    reverse(follow_C.begin(), follow_C.end());

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 10: Using all uppercase characters in A, B, and C should not change the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR10) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A, follow_B = B, follow_C = C;
    transform(follow_A.begin(), follow_A.end(), follow_A.begin(), ::toupper);
    transform(follow_B.begin(), follow_B.end(), follow_B.begin(), ::toupper);
    transform(follow_C.begin(), follow_C.end(), follow_C.begin(), ::toupper);

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 11: Reversing the order of A and B while keeping the order of C unchanged does not change the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR11) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A, follow_B = B;
    reverse(follow_A.begin(), follow_A.end());
    reverse(follow_B.begin(), follow_B.end());

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 12: Reversing the order of A and keeping B and C unchanged does not change the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR12) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A;
    reverse(follow_A.begin(), follow_A.end());

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 13: Empty string A should always return false.
 *
 */
TEST_P(InterleavingStringParamTest, MR13) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = "";

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, B, C);

    /* Verification */
    EXPECT_FALSE(follow_out);
}

/**
 * @brief Metamorphic Relation 14: Adding a prefix to A and B simultaneously will not change the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR14) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string prefix = "prefix_";
    string follow_A = prefix + A;
    string follow_B = prefix + B;

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 15: Repeating A and B while keeping C unchanged will not change the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR15) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A + A;
    string follow_B = B + B;

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 16: Repeating C while keeping A and B unchanged will change the result to false.
 *
 */
TEST_P(InterleavingStringParamTest, MR16) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_C = C + C;

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, B, follow_C);

    /* Verification */
    EXPECT_FALSE(follow_out);
}

/**
 * @brief Metamorphic Relation 17: Interchanging the positions of A and C will not change the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR17) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = C, follow_C = A;

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 18: Swapping the positions of B and C will not change the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR18) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_B = C, follow_C = B;

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, follow_B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 19: Using an empty string for C should always return true if both A and B are also empty.
 *
 */
TEST_P(InterleavingStringParamTest, MR19) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    if (A.empty() && B.empty()) {
        /* Verification */
        EXPECT_TRUE(source_out);
    }
}

/**
 * @brief Metamorphic Relation 20: Repeating the last character of A and B while keeping C unchanged will not change the result.
 */
TEST_P(InterleavingStringParamTest, MR20) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    if (!A.empty() && !B.empty()) {
        char lastCharA = A.back();
        char lastCharB = B.back();

        /* Construct follow-up input */
        string follow_A = A + lastCharA;
        string follow_B = B + lastCharB;

        /* Get follow-up output */
        bool follow_out = is_interleaved(follow_A, follow_B, C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 21: Adding a prefix to C will not change the result if both A and B are empty strings.
 */
TEST_P(InterleavingStringParamTest, MR21) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    if (A.empty() && B.empty()) {
        string prefix = "prefix_";

        /* Construct follow-up input */
        string follow_C = prefix + C;

        /* Get follow-up output */
        bool follow_out = is_interleaved(A, B, follow_C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 22: Reversing the order of A, B, and C while keeping the lengths unchanged will not change the result.
 */
TEST_P(InterleavingStringParamTest, MR22) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    if (A.length() == B.length() && A.length() == C.length()) {
        /* Construct follow-up input */
        string follow_A = A, follow_B = B, follow_C = C;
        reverse(follow_A.begin(), follow_A.end());
        reverse(follow_B.begin(), follow_B.end());
        reverse(follow_C.begin(), follow_C.end());

        /* Get follow-up output */
        bool follow_out = is_interleaved(follow_A, follow_B, follow_C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 23: Adding a suffix to A and B while keeping C unchanged will not change the result.
 */
TEST_P(InterleavingStringParamTest, MR23) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    if (!A.empty() && !B.empty()) {
        char lastCharA = A.back();
        char lastCharB = B.back();

        /* Construct follow-up input */
        string follow_A = A + lastCharA;
        string follow_B = B + lastCharB;

        /* Get follow-up output */
        bool follow_out = is_interleaved(follow_A, follow_B, C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 24: Replacing all occurrences of a character with another character in A and B while keeping C unchanged will not change the result.
 */
TEST_P(InterleavingStringParamTest, MR24) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    if (!A.empty() && !B.empty()) {
        char oldChar = 'a';
        char newChar = 'b';

        /* Construct follow-up input */
        string follow_A = A, follow_B = B;
        replace(follow_A.begin(), follow_A.end(), oldChar, newChar);
        replace(follow_B.begin(), follow_B.end(), oldChar, newChar);

        /* Get follow-up output */
        bool follow_out = is_interleaved(follow_A, follow_B, C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 25: Reversing the order of A, B, and C while keeping the lengths unchanged will not change the result.
 */
TEST_P(InterleavingStringParamTest, MR25) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    if (A.length() == B.length() && A.length() == C.length()) {
        /* Construct follow-up input */
        string follow_A = A, follow_B = B, follow_C = C;
        reverse(follow_A.begin(), follow_A.end());
        reverse(follow_B.begin(), follow_B.end());
        reverse(follow_C.begin(), follow_C.end());

        /* Get follow-up output */
        bool follow_out = is_interleaved(follow_A, follow_B, follow_C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 26: Repeating the entire string A and B while keeping C unchanged will not change the result.
 */
TEST_P(InterleavingStringParamTest, MR26) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    if (!A.empty() && !B.empty()) {
        /* Construct follow-up input */
        string follow_A = A + A;
        string follow_B = B + B;

        /* Get follow-up output */
        bool follow_out = is_interleaved(follow_A, follow_B, C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 27: Removing the last character of A and B while keeping C unchanged will not change the result.
 */
TEST_P(InterleavingStringParamTest, MR27) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    if (!A.empty() && !B.empty()) {
        /* Construct follow-up input */
        string follow_A = A.substr(0, A.size() - 1);
        string follow_B = B.substr(0, B.size() - 1);

        /* Get follow-up output */
        bool follow_out = is_interleaved(follow_A, follow_B, C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 28: Reversing the order of A and keeping B and C unchanged will not change the result.
 */
TEST_P(InterleavingStringParamTest, MR28) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A;
    reverse(follow_A.begin(), follow_A.end());

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 29: Reversing the order of B and keeping A and C unchanged will not change the result.
 */
TEST_P(InterleavingStringParamTest, MR29) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_B = B;
    reverse(follow_B.begin(), follow_B.end());

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, follow_B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 30: Repeating the string C while keeping A and B unchanged will change the result.
 */
TEST_P(InterleavingStringParamTest, MR30) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_C = C + C;

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, B, follow_C);

    /* Verification */
    EXPECT_NE(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 31: Using all lowercase characters in A, B, and C should not change the result.
 */
TEST_P(InterleavingStringParamTest, MR31) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A, follow_B = B, follow_C = C;
    transform(follow_A.begin(), follow_A.end(), follow_A.begin(), ::tolower);
    transform(follow_B.begin(), follow_B.end(), follow_B.begin(), ::tolower);
    transform(follow_C.begin(), follow_C.end(), follow_C.begin(), ::tolower);

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 32: Repeating the last character of C while keeping A and B unchanged will not change the result.
 */
TEST_P(InterleavingStringParamTest, MR32) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    if (!C.empty()) {
        char lastCharC = C.back();

        /* Construct follow-up input */
        string follow_C = C + lastCharC;

        /* Get follow-up output */
        bool follow_out = is_interleaved(A, B, follow_C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 33: Repeating the entire string C while keeping A and B unchanged will not change the result.
 */
TEST_P(InterleavingStringParamTest, MR33) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    if (!C.empty()) {
        /* Construct follow-up input */
        string follow_C = C + C;

        /* Get follow-up output */
        bool follow_out = is_interleaved(A, B, follow_C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 34: Reversing the order of A and B will not change the result when both A and B are empty strings.
 */
TEST_P(InterleavingStringParamTest, MR34) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    if (A.empty() && B.empty()) {
        /* Construct follow-up input */
        string follow_A = A, follow_B = B;
        reverse(follow_A.begin(), follow_A.end());
        reverse(follow_B.begin(), follow_B.end());

        /* Get follow-up output */
        bool follow_out = is_interleaved(follow_A, follow_B, C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 35: Reversing the order of B and keeping A and C unchanged will not change the result when B is an empty string.
 */
TEST_P(InterleavingStringParamTest, MR35) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    if (B.empty()) {
        /* Construct follow-up input */
        string follow_B = B;
        reverse(follow_B.begin(), follow_B.end());

        /* Get follow-up output */
        bool follow_out = is_interleaved(A, follow_B, C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 36: Reversing the order of A and keeping B and C unchanged does not change the result when A is an empty string.
 */
TEST_P(InterleavingStringParamTest, MR36) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    if (A.empty()) {
        /* Construct follow-up input */
        string follow_A = A;
        reverse(follow_A.begin(), follow_A.end());

        /* Get follow-up output */
        bool follow_out = is_interleaved(follow_A, B, C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 37: Adding a suffix to C will not change the result when both A and B are empty strings.
 */
TEST_P(InterleavingStringParamTest, MR37) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    if (A.empty() && B.empty()) {
        string suffix = "_suffix";

        /* Construct follow-up input */
        string follow_C = C + suffix;

        /* Get follow-up output */
        bool follow_out = is_interleaved(A, B, follow_C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 38: Prepending both A and B with the same prefix while keeping C unchanged does not change the result.
 */
TEST_P(InterleavingStringParamTest, MR38) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string prefix = "pre_";
    string follow_A = prefix + A;
    string follow_B = prefix + B;

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 39: Repeating characters in A and B while keeping C unchanged will not change the result.
 */
TEST_P(InterleavingStringParamTest, MR39) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    if (!A.empty() && !B.empty()) {
        /* Construct follow-up input */
        string follow_A = accumulate(A.begin(), A.end(), string());
        string follow_B = accumulate(B.begin(), B.end(), string());

        /* Get follow-up output */
        bool follow_out = is_interleaved(follow_A, follow_B, C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 40: Reversing the entire strings A, B, and C will not change the result.
 */
TEST_P(InterleavingStringParamTest, MR40) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    reverse(C.begin(), C.end());

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 41: Reversing the order of A and B simultaneously while keeping C unchanged will produce the same result.
 */
TEST_P(InterleavingStringParamTest, MR41) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string tempA = A;
    string tempB = B;
    reverse(tempA.begin(), tempA.end());
    reverse(tempB.begin(), tempB.end());

    /* Get follow-up output */
    bool follow_out = is_interleaved(tempA, tempB, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, InterleavingStringParamTest, testing::ValuesIn(gen_tcs_randomly()));