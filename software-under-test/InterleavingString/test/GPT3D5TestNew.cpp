#include <algorithm>
#include <gtest/gtest.h>
#include <random>
#include <string>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class InterleavingStringParamTest : public ::testing::TestWithParam<InterleavingStringInput> {};

/**
 * @brief Metamorphic Relation 1: Reversing C and keeping A, B unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR1) {
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
 * @brief Metamorphic Relation 2: Swapping string A and B while keeping C unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR2) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    /* Swap A and B */
    string follow_A = input.B;
    string follow_B = input.A;

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 3: Appending the contents of B to A and keeping C unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR3) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    /* Append B to A */
    string follow_A = A + B;

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 4: Adding the same character to the beginning of A, B, and C, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR4) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    char ch = 'a';
    string follow_A = ch + A, follow_B = ch + B, follow_C = ch + C;

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 5: Repeating C twice and keeping A, B unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR5) {
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
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 6: Reversing A, B, and C simultaneously, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR6) {
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
 * @brief Metamorphic Relation 7: Doubling the characters of A, B, and C while keeping the order unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR7) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A + A;
    string follow_B = B + B;
    string follow_C = C + C;

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 8: Appending the reverse of B to A and keeping C unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR8) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A + string(B.rbegin(), B.rend());

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 9: Replacing all characters in A with a single character, replacing all characters in B with the same character, and replacing all characters in C with the same character, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR9) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    char replace_char = 'x';
    string follow_A(A.size(), replace_char);
    string follow_B(B.size(), replace_char);
    string follow_C(C.size(), replace_char);

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

//fixed (follow_input,follow_C_input)->(follow_input,empty_string,follow_C_input)
/**
 * @brief Metamorphic Relation 10: Reversing A and B, and concatenating them as input, while concatenating the reverse of C as input, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR10) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A(A.rbegin(), A.rend());
    string follow_B(B.rbegin(), B.rend());
    string follow_C(C.rbegin(), C.rend());
    string follow_input = follow_A + follow_B;
    string follow_C_input = follow_C;
    
    string empty_string;
    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_input,empty_string,follow_C_input);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 11: Appending the reverse of A to B, and appending the reverse of C to A, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR11) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);
    
    /* Construct follow-up input */
    string follow_B = B + string(A.rbegin(), A.rend());
    string follow_A = A + string(C.rbegin(), C.rend());

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, C);
    
    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 12: Taking the first half of A, swapping it with the second half of B, taking the second half of A, swapping it with the first half of B, and the C remains unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR12) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);
    
    /* Construct follow-up input */
    int halfA = A.size() / 2;
    int halfB = B.size() / 2;
    string follow_A = B.substr(halfB) + A.substr(halfA);
    string follow_B = A.substr(halfA) + B.substr(halfB);

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, C);
    
    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 13: Prepending A with B, appending B with A, and keeping C unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR13) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);
    
    /* Construct follow-up input */
    string follow_A = B + A;
    string follow_B = A + B;

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, C);
    
    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 14: Replacing all characters in A, B, and C with their uppercase counterparts, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR14) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Convert all characters to uppercase */
    transform(A.begin(), A.end(), A.begin(), ::toupper);
    transform(B.begin(), B.end(), B.begin(), ::toupper);
    transform(C.begin(), C.end(), C.begin(), ::toupper);

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A;
    string follow_B = B;
    string follow_C = C;

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 15: Repeating string A twice and keeping B, C unchanged, the result will be the same.
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

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

//fixed "" -> empty_string
/**
 * @brief Metamorphic Relation 16: Appending A and B in alternating order and keeping C unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR16) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A_B;
    for (size_t i = 0; i < max(A.size(), B.size()); ++i) {
        if (i < A.size()) {
            follow_A_B += A[i];
        }
        if (i < B.size()) {
            follow_A_B += B[i];
        }
    }
    string empty_string;
    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A_B, empty_string, C);  // No need to include B here for interleaving

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 17: Replacing each character in C with the corresponding character in A, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR17) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;
    
    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_C = C;
    for (size_t i = 0; i < C.size(); ++i) {
        if (i < A.size()) {
            follow_C[i] = A[i];
        }
    }

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 18: Appending A with B, and replacing each character in C with the corresponding character in the concatenated string, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR18) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;
    
    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string concat_A_B = A + B;
    string follow_C = C;
    for (size_t i = 0; i < C.size(); ++i) {
        if (i < concat_A_B.size()) {
            follow_C[i] = concat_A_B[i];
        }
    }

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 19: Reversing the order of A, B, and C, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR19) {
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
 * @brief Metamorphic Relation 20: Appending the reverse of B to A, appending the reverse of A to B, and keeping C unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR20) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;
    
    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A + string(B.rbegin(), B.rend());
    string follow_B = B + string(A.rbegin(), A.rend());

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 21: Appending the reverse of A to A, appending the reverse of B to B, and appending the reverse of C to C, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR21) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;
    
    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A + string(A.rbegin(), A.rend());
    string follow_B = B + string(B.rbegin(), B.rend());
    string follow_C = C + string(C.rbegin(), C.rend());

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 22: Reversing string C and keeping A, B unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR22) {
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
 * @brief Metamorphic Relation 23: Removing the first character of A, B, and C, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR23) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A.substr(1);
    string follow_B = B.substr(1);
    string follow_C = C.substr(1);

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 24: Taking the first half of C and using it as B, and taking the second half and using it as A, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR24) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    int half_size = C.size() / 2;
    string follow_B = C.substr(0, half_size);
    string follow_A = C.substr(half_size);

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

//fixed
/**
 * @brief Metamorphic Relation 25: Replacing each character in A with its ASCII value and keeping B, C unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR25) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    for (char &c : A) {
        //c = to_string((int)c)[0];
        c = static_cast<char>(static_cast<int>(c));
    }

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 26: Replacing each occurrence of a specific character in A with another specific character and keeping B, C unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR26) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Choose the specific character to be replaced */
    char old_char = 'a';
    char new_char = 'x';

    /* Construct follow-up input */
    for (char &c : A) {
        if (c == old_char) {
            c = new_char;
        }
    }

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 27: Repeating each character in A, B, and C three times, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR27) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = "", follow_B = "", follow_C = "";
    for (char &c : A) {
        follow_A += string(3, c);
    }
    for (char &c : B) {
        follow_B += string(3, c);
    }
    for (char &c : C) {
        follow_C += string(3, c);
    }

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 28: Adding a prefix to A, B, and C while keeping the order, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR28) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;
    
    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string prefix = "123_";
    string follow_A = prefix + A;
    string follow_B = prefix + B;
    string follow_C = prefix + C;

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 29: Adding a suffix to A, B, and C while keeping the order, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR29) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;
    
    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string suffix = "_789";
    string follow_A = A + suffix;
    string follow_B = B + suffix;
    string follow_C = C + suffix;

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 30: Adding a common prefix to A and B, append them to form C, then removing the common prefix from both A and B while keeping C unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR30) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string prefix = "common_";
    string combined_prefix = prefix + A;
    combined_prefix += prefix + B;
    string follow_C = C.substr(2*prefix.size()); // Remove the common prefix
    string follow_A = A.substr(prefix.size()); // Remove the common prefix
    string follow_B = B.substr(prefix.size()); // Remove the common prefix

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 31: Replacing all occurrences of a specific substring in A with another specific substring and keeping B, C unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR31) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Choose the specific substring to be replaced */
    string old_substr = "abc";
    string new_substr = "xyz";

    /* Construct follow-up input */
    string follow_A = A;
    size_t pos = follow_A.find(old_substr);
    while (pos != string::npos) {
        follow_A.replace(pos, old_substr.length(), new_substr);
        pos = follow_A.find(old_substr, pos + new_substr.length());
    }

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 32: Reversing string A and adding it to itself, conversely mixed with B, while keeping C unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR32) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A + string(A.rbegin(), A.rend());
    string follow_B = "";
    for (size_t i = 0; i < B.size(); ++i) {
        follow_B.push_back(B[i]);
        if (i < A.size()) {
            follow_B.push_back(A[A.size() - 1 - i]);
        }
    }

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 33: Appending the reverse of string A to B, appending the reverse of string B to A, while keeping C unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR33) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;
    
    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A + string(B.rbegin(), B.rend());
    string follow_B = B + string(A.rbegin(), A.rend());
    
    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, C);
    
    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 34: Appending the first half of A to the second half of B, appending the second half of A to the first half of B, while keeping C unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR34) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;
    
    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A.substr(A.size()/2) + B.substr(0, B.size()/2);
    string follow_B = B.substr(B.size()/2) + A.substr(0, A.size()/2);
    
    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, C);
    
    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 35: Appending A to the reverse of B and C, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR35) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_B = B + string(A.rbegin(), A.rend());
    string follow_C = C + string(A.rbegin(), A.rend());

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, follow_B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 36: Replacing all 'a's in B with 'b's and vice versa, keeping A and C unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR36) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_B = B;
    for (char &c : follow_B) {
        if (c == 'a') {
            c = 'b';
        } else if (c == 'b') {
            c = 'a';
        }
    }

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, follow_B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 37: Appending the reverse of string C to A and B, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR37) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A + string(C.rbegin(), C.rend());
    string follow_B = B + string(C.rbegin(), C.rend());

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 38: Prepending each character in A, B, and C with a specific character and keeping the order unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR38) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;
    
    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    char prefix = 'X';
    string follow_A, follow_B, follow_C;
    for (char c : A) {
        follow_A += prefix;
        follow_A += c;
    }
    for (char c : B) {
        follow_B += prefix;
        follow_B += c;
    }
    for (char c : C) {
        follow_C += prefix;
        follow_C += c;
    }
    
    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, follow_C);
    
    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 39: Replicating A, B, and C 3 times, while keeping the order unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR39) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;
    
    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A = A + A + A;
    string follow_B = B + B + B;
    string follow_C = C + C + C;
    
    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, follow_C);
    
    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 40: Repeating each character in A, B, and C three times, while keeping the order unchanged, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR40) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;
    
    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    string follow_A, follow_B, follow_C;
    for (char c : A) {
        follow_A += string(3, c);
    }
    for (char c : B) {
        follow_B += string(3, c);
    }
    for (char c : C) {
        follow_C += string(3, c);
    }
    
    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, follow_C);
    
    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, InterleavingStringParamTest, testing::ValuesIn(gen_tcs_randomly()));