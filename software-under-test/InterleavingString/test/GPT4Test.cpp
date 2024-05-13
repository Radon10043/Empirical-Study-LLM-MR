#include <algorithm>
#include <gtest/gtest.h>
#include <random>
#include <string>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class InterleavingStringParamTest : public ::testing::TestWithParam<InterleavingStringInput> {};

/**
 * @brief Metamorphic Relation 2: Swapping A and B should produce the same result.
 *
 */
TEST_P(InterleavingStringParamTest, MR2) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input by swapping A and B */
    string follow_A = B, follow_B = A;

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 3: Adding one same character to the end of A, B and C preserves the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR3) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input by appending the same character to A, B and C */
    char ch = 'z';
    string follow_A = A + ch, follow_B = B + ch, follow_C = C + ch;

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 4: Removing the same prefix from A, B, and C that doesn't change their interleaving status should preserve the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR4) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Ensure we have a non-empty common prefix */
    if (!A.empty() && !B.empty() && !C.empty() && A.front() == C.front() && B.front() == C.front()) {
        /* Get source output */
        bool source_out = is_interleaved(A, B, C);

        /* Construct follow-up input by removing the common prefix */
        string follow_A = A.substr(1), follow_B = B.substr(1), follow_C = C.substr(1);

        /* Get follow-up output */
        bool follow_out = is_interleaved(follow_A, follow_B, follow_C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 5: Interchanging two non-overlapping segments between A and B should not affect the result if segments match their respective
 * positions in C.
 *
 */
TEST_P(InterleavingStringParamTest, MR5) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Check for non-overlapping segments in A and B that are in C and interchange them */
    if (A.length() >= 2 && B.length() >= 2) {
        string segA = A.substr(0, 2);
        string segB = B.substr(0, 2);
        if (C.find(segA) != string::npos && C.find(segB) != string::npos) {
            /* Get source output */
            bool source_out = is_interleaved(A, B, C);

            /* Swap the segments in A and B */
            string follow_A = B.substr(0, 2) + A.substr(2);
            string follow_B = A.substr(0, 2) + B.substr(2);

            /* Get follow-up output */
            bool follow_out = is_interleaved(follow_A, follow_B, C);

            /* Verification */
            EXPECT_EQ(source_out, follow_out);
        }
    }
}
/**
 * @brief Metamorphic Relation 6: If C is an interleaved string of A and B, then C reversed is an interleaving of A reversed and B reversed.
 *
 */
TEST_P(InterleavingStringParamTest, MR6) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input by reversing A, B, and C */
    string follow_A(A.rbegin(), A.rend());
    string follow_B(B.rbegin(), B.rend());
    string follow_C(C.rbegin(), C.rend());

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 7: Adding a character to the start of A and C, different from the start of B, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR7) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct a follow-up input */
    char ch = '#'; // Assuming '#' is not the start of B
    if (!B.empty() && B.front() != ch) {
        string follow_A = ch + A;
        string follow_C = ch + C;

        /* Get follow-up output */
        bool follow_out = is_interleaved(follow_A, B, follow_C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 8: If C is an interleaving of A and B, then C with any character removed from only A or B (but not both) will still be an
 * interleaving.
 *
 */
TEST_P(InterleavingStringParamTest, MR8) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    // Verify that the string A is not empty and that its first character is present in C.
    if (!A.empty() && C.find(A[0]) != string::npos) {
        /* Get source output */
        bool source_out = is_interleaved(A, B, C);

        /* Construct follow-up input by removing the first character of A from C */
        size_t pos = C.find(A[0]);
        string follow_C = C.substr(0, pos) + C.substr(pos + 1);
        string follow_A = A.substr(1); // Remove corresponding character from A

        /* Get follow-up output */
        bool follow_out = is_interleaved(follow_A, B, follow_C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 9: If C is an interleaving of A and B, then any permutation of C which keeps the relative order of A and B characters should
 * yield true.
 *
 */
TEST_P(InterleavingStringParamTest, MR9) { // Fixed
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Failure to permute C while preserving order means the test is not applicable */
    if (!source_out) {
        GTEST_SKIP() << "The input C is not an interleaving of A and B.";
    } else {
        /* Let's create a simple permutation by interleaving A and B in a predictable pattern */
        string permuted_C;
        auto iter_A = A.begin();
        auto iter_B = B.begin();
        while (iter_A != A.end() || iter_B != B.end()) {
            if (iter_B != B.end()) {
                permuted_C += *iter_B++;
            }
            if (iter_A != A.end()) {
                permuted_C += *iter_A++;
            }
        }

        /* Get follow-up output */
        bool follow_out = is_interleaved(A, B, permuted_C);

        /* Verification */
        EXPECT_EQ(true, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 10: Concatenating a string D to A and B, and D + D to C, should yield the same result.
 *
 */
TEST_P(InterleavingStringParamTest, MR10) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C, D = "xyz";

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input by concatenating D to A, B, and D + D to C */
    string follow_A = A + D, follow_B = B + D, follow_C = C + (D + D);

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, follow_B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}
/**
 * @brief Metamorphic Relation 11: If a character `ch` is added anywhere in A (or B), and the same `ch` is added at the corresponding position in C, the result
 * should be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR11) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    char ch = '$';       // Choose a character that may not be in A, B, or C.
    size_t pos_in_A = 1; // Example position to insert `ch` for A.

    /* Ensure that the position is within the bounds of A and C */
    if (A.length() >= pos_in_A && C.length() >= pos_in_A) {
        string follow_A = A.substr(0, pos_in_A) + ch + A.substr(pos_in_A);
        string follow_C = C.substr(0, pos_in_A) + ch + C.substr(pos_in_A);

        /* Get follow-up output */
        bool follow_out = is_interleaved(follow_A, B, follow_C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 12: Repeating A (or B) and also its corresponding characters in C should not change the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR12) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Only proceed if A is non-empty, and the first character of A is in C */
    if (!A.empty() && C.find(A[0]) != string::npos) {
        /* Get source output */
        bool source_out = is_interleaved(A, B, C);

        /* Construct follow-up input by repeating A and its corresponding interleaved sequence in C */
        string repeat_A = A + A;
        string follow_C = C;

        /* Find indices in C where characters from A appear and duplicate them */
        for (auto &charA : A) {
            size_t pos = follow_C.find(charA);
            if (pos != string::npos) {
                follow_C.insert(pos + 1, 1, charA); // Duplicate character at found position
            }
        }

        /* Get follow-up output */
        bool follow_out = is_interleaved(repeat_A, B, follow_C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 13: Trimming matching characters from the beginning of A, B, and C should not change the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR13) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* We need to trim all the matching characters from A and B */
    while (!A.empty() && !B.empty() && !C.empty() && (A.front() == C.front() || B.front() == C.front())) {
        if (A.front() == C.front()) {
            A.erase(0, 1);
            C.erase(0, 1);
        }
        if (!B.empty() && B.front() == C.front()) {
            B.erase(0, 1);
            C.erase(0, 1);
        }
    }

    /* Get source output after trimming */
    bool trimmed_source_out = is_interleaved(A, B, C);

    /* Get original inputs */
    InterleavingStringInput original_input = GetParam();
    string original_A = original_input.A, original_B = original_input.B, original_C = original_input.C;

    /* Get source output from the original input */
    bool original_source_out = is_interleaved(original_A, original_B, original_C);

    /* Verification */
    EXPECT_EQ(trimmed_source_out, original_source_out);
}

/**
 * @brief Metamorphic Relation 14: For every pair of adjacent characters that come from the same parent string A or B in C, switching them should not affect the
 * result.
 *
 */
TEST_P(InterleavingStringParamTest, MR14) { // Can not get source of characters in C
#if 0
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Assume a function that provides the source of each character in C (from A or B) */
    /* This function needs to be implemented and may require tracking the interleaving process */
    vector<char> sources = getSourceOfCharactersInC(A, B, C); 

    /* Iterate through C and find adjacent characters with the same source */
    for (size_t i = 0; i < sources.size() - 1; ++i) {
        if (sources[i] == sources[i + 1]) {
            /* Swap the adjacent characters in C */
            string follow_C = C;
            swap(follow_C[i], follow_C[i + 1]);

            /* Get source output */
            bool source_out = is_interleaved(A, B, C);

            /* Get follow-up output */
            bool follow_out = is_interleaved(A, B, follow_C);

            /* Verification */
            EXPECT_EQ(source_out, follow_out);
        }
    }
#endif
}

/**
 * @brief Metamorphic Relation 15: If C is a valid interleaving of A and B, removing the same character from both A and C (or B and C) should still result in a
 * valid interleaving.
 *
 */
TEST_P(InterleavingStringParamTest, MR15) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Select a character to remove */
    char ch_to_remove = 'x'; // This character should exist in both A and C (or B and C).

    if (A.find(ch_to_remove) != string::npos && C.find(ch_to_remove) != string::npos) {
        size_t pos_in_A = A.find(ch_to_remove);
        size_t pos_in_C = C.find(ch_to_remove);

        /* Remove selected character from A and C */
        string follow_A = A;
        follow_A.erase(pos_in_A, 1);
        string follow_C = C;
        follow_C.erase(pos_in_C, 1);

        /* Get source output */
        bool source_out = is_interleaved(A, B, C);

        /* Get follow-up output */
        bool follow_out = is_interleaved(follow_A, B, follow_C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}
/**
 * @brief Metamorphic Relation 16: Concatenating A with some string D and C with D (having no common characters with A or B) should not affect the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR16) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Define a string D that has no characters in common with A or B - for simplicity, we choose uncommon Unicode characters */
    string D = "\u2C60\u2C61\u2C62"; // Some arbitrary Unicode characters (assuming A and B are ASCII for instance).

    /* Construct follow-up input by concatenating D to A and D to C */
    string follow_A = A + D;
    string follow_C = C + D;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 17: Replacing every occurrence of a character in A, B and C with two of the same character, should not change the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR17) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    char ch = 'a'; // Choose a character that is present in A or B.

    /* Replace all occurrences of ch in A with two ch characters */
    size_t pos = 0;
    while ((pos = A.find(ch, pos)) != string::npos) {
        A.replace(pos, 1, 2, ch);
        pos += 2;
    }
    /* Replace all occurrences of ch in B with two ch characters */
    pos = 0;
    while ((pos = B.find(ch, pos)) != string::npos) {
        B.replace(pos, 1, 2, ch);
        pos += 2;
    }
    /* Replace all occurrences of ch in C with two ch characters */
    pos = 0;
    while ((pos = C.find(ch, pos)) != string::npos) {
        C.replace(pos, 1, 2, ch);
        pos += 2;
    }

    /* After modifications, we should get the same result */
    bool modified_out = is_interleaved(A, B, C);

    /* Get original output */
    bool original_out = is_interleaved(input.A, input.B, input.C);

    /* Verification */
    EXPECT_EQ(original_out, modified_out);
}

/**
 * @brief Metamorphic Relation 18: If A is empty, any permutation of B should result in true as long as it's equal to C.
 *
 */
TEST_P(InterleavingStringParamTest, MR18) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A;
    string B = input.B;
    string C = input.C;

    /* Check only for the cases when A is empty */
    if (A.empty()) {
        std::sort(B.begin(), B.end()); // Permute B by sorting it.
        string permuted_B = B;

        // The result should be true only if permuted_B is equal to C after C is sorted.
        std::sort(C.begin(), C.end());
        bool expectation = (permuted_B == C);

        bool actual_out = is_interleaved(A, permuted_B, C);

        /* Verification */
        EXPECT_EQ(expectation, actual_out);
    }
}

/**
 * @brief Metamorphic Relation 19: Turning A and B into uppercase should not affect the outcome as long as C is changed accordingly.
 *
 */
TEST_P(InterleavingStringParamTest, MR19) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    // Convert A to uppercase, B to uppercase, and modify C accordingly
    std::transform(A.begin(), A.end(), A.begin(), ::toupper);
    std::transform(B.begin(), B.end(), B.begin(), ::toupper);

    for (char &c : C) {
        if (std::find(input.A.begin(), input.A.end(), c) != input.A.end()) {
            c = std::toupper(c);
        } else if (std::find(input.B.begin(), input.B.end(), c) != input.B.end()) {
            c = std::toupper(c);
        }
    }

    /* Get source output */
    bool source_out = is_interleaved(input.A, input.B, input.C);

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 20: If the order of characters from A and B are preserved in C, then any contiguous substring of C that is a mix of A and B can
 * be moved as a block to the end of C and the result should remain the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR20) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Ensure that C is not empty and there's at least one character from both A and B */
    if (!C.empty() && !A.empty() && !B.empty() && C.size() > 1) {
        /* Identify a contiguous substring of C which we can move to the end */
        size_t len = C.size();
        size_t start = len / 2 - 1; // Some central position as an example

        // Ensure the substring is a valid mix of A and B and not just a part of A or part of B
        while (start < len - 1 && (A.find(C[start]) == string::npos || B.find(C[start + 1]) == string::npos))
            ++start;

        if (start < len - 1) {
            string block = C.substr(start, 2);
            string moved_block_C = C.substr(0, start) + C.substr(start + 2) + block;

            /* Get source output before moving the block */
            bool source_out = is_interleaved(A, B, C);

            /* Get follow-up output after moving the block */
            bool follow_out = is_interleaved(A, B, moved_block_C);

            /* Verification */
            EXPECT_EQ(source_out, follow_out);
        }
    }
}
/**
 * @brief Metamorphic Relation 21: If characters from B are removed from C, and B is shortened accordingly, the result should still be true.
 *
 */
TEST_P(InterleavingStringParamTest, MR21) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Remove the first character of B from C, while also removing it from B */
    if (!B.empty() && C.find(B[0]) != string::npos) {
        size_t pos = C.find(B[0]);
        B.erase(0, 1);
        C.erase(pos, 1);

        /* Get follow-up output */
        bool follow_out = is_interleaved(A, B, C);

        /* Verification */
        EXPECT_TRUE(follow_out);
    }
}

/**
 * @brief Metamorphic Relation 22: Reversing C while keeping A and B the same should not result in a valid interleaving, unless A or B is empty.
 *
 */
TEST_P(InterleavingStringParamTest, MR22) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Reverse C */
    string reversed_C(C.rbegin(), C.rend());

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, B, reversed_C);

    /* Expected result */
    bool expected_out = A.empty() || B.empty();

    /* Verification */
    EXPECT_EQ(expected_out, follow_out);
}

/**
 * @brief Metamorphic Relation 23: Swapping two non-overlapping subsequences in A which also appear in that order in C should not affect the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR23) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Assuming subsequences of length 2 for simplicity */
    if (A.length() > 4) {
        /* Find subsequences in A that appear in C */
        size_t first_pos_C = C.find(A[0]);
        size_t second_pos_C = C.find(A[2], first_pos_C + 2);

        /* Only valid if subsequences are in same relative order in C */
        if (first_pos_C != string::npos && second_pos_C != string::npos) {
            /* Swap subsequences */
            string swapped_A = A.substr(2, 2) + A.substr(4) + A.substr(0, 2);

            /* Get source output */
            bool source_out = is_interleaved(A, B, C);

            /* Get follow-up output */
            bool follow_out = is_interleaved(swapped_A, B, C);

            /* Verification */
            EXPECT_EQ(source_out, follow_out);
        }
    }
}

/**
 * @brief Metamorphic Relation 24: Replacing some characters of A and B with different characters not present in A or B, and replacing them accordingly in C,
 * should not affect the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR24) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Define a mapping of character replacements */
    std::map<char, char> replacements{{'a', '@'}, {'b', '#'}, {'c', '&'}};

    /* Replace characters in A and B */
    for (auto &repl : replacements) {
        std::replace(A.begin(), A.end(), repl.first, repl.second);
        std::replace(B.begin(), B.end(), repl.first, repl.second);
    }

    /* Replace corresponding characters in C */
    for (auto &repl : replacements) {
        std::replace(C.begin(), C.end(), repl.first, repl.second);
    }

    /* Get source output */
    bool source_out = is_interleaved(input.A, input.B, input.C);

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 25: Shuffling non-adjacent characters in A or B should not affect whether C is considered an interleaving as long as these
 * characters are also shuffled in C.
 *
 */
TEST_P(InterleavingStringParamTest, MR25) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Shuffle characters in A */
    if (A.length() > 2) {
        const size_t idx1 = 0;
        const size_t idx2 = 2; // Ensure idx1 and idx2 are non-adjacent
        std::swap(A[idx1], A[idx2]);

        /* Shuffle corresponding characters in C */
        size_t pos_C1 = C.find(input.A[idx1]);
        size_t pos_C2 = C.find(input.A[idx2], pos_C1 + 1);
        if (pos_C1 != string::npos && pos_C2 != string::npos && pos_C1 != pos_C2) {
            std::swap(C[pos_C1], C[pos_C2]);

            /* Get source output */
            bool source_out = is_interleaved(input.A, input.B, input.C);

            /* Get follow-up output */
            bool follow_out = is_interleaved(A, B, C);

            /* Verification */
            EXPECT_EQ(source_out, follow_out);
        }
    }
}
/**
 * @brief Metamorphic Relation 26: If C is an interleaving of A and B, then inserting a character in A and the same character in C preserving the order should
 * give the same result.
 *
 */
TEST_P(InterleavingStringParamTest, MR26) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Choose a character to insert */
    char insert_char = '*';

    /* Insert the character into A at a random position */
    int insert_position_A = rand() % (A.size() + 1);
    A.insert(insert_position_A, 1, insert_char);

    /* Insert the same character into C at the corresponding position */
    int insert_position_C = insert_position_A;
    for (const char &character : B) {
        if ((size_t)insert_position_C < C.size() && C[insert_position_C] == character) {
            ++insert_position_C;
        }
    }
    C.insert(insert_position_C, 1, insert_char);

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 27: If C is not an interleaving of A and B, appending A or B to itself, and C to itself, should maintain the non-interleaving
 * status.
 *
 */
TEST_P(InterleavingStringParamTest, MR27) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* If the original strings are not an interleaving, we can double A or B and also double C */
    if (!source_out) {
        A += A; // Double A
        C += C; // Double C

        /* The result should still be false */
        bool follow_out = is_interleaved(A, B, C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 28: For a substring of A, if changing the characters to a distinct character that's not in B and not in the remaining A doesn't
 * affect the interleaving.
 *
 */
TEST_P(InterleavingStringParamTest, MR28) {
    /* Get the source inputs */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Assuming we can find a substring of length 2 in A that doesn't intersect with B */
    size_t pos = A.find("aa");
    if (pos != string::npos && B.find('a') == string::npos) {
        char distinct_char = '!';
        fill_n(A.begin() + pos, 2, distinct_char);

        /* Replicate changes in C */
        size_t c_pos = C.find("aa");
        if (c_pos != string::npos) {
            fill_n(C.begin() + c_pos, 2, distinct_char);
        }

        /* Verify if interleaving is still valid */
        bool modified_out = is_interleaved(A, B, C);

        /* Get the original result */
        bool original_out = is_interleaved(input.A, input.B, input.C);

        /* Verification */
        EXPECT_EQ(original_out, modified_out);
    }
}

/**
 * @brief Metamorphic Relation 29: Swapping characters in C that come from the same parent A or B should keep the result unchanged.
 *
 */
TEST_P(InterleavingStringParamTest, MR29) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Make a copy of C to apply swap */
    string swapped_C = C;

    /* Pick two characters from A in C and swap their places */
    if (A.length() >= 2) {
        size_t first_pos = C.find(A[0]);
        size_t second_pos = C.rfind(A[1]);

        if (first_pos != string::npos && second_pos != string::npos && first_pos != second_pos) {
            std::swap(swapped_C[first_pos], swapped_C[second_pos]);

            bool source_out = is_interleaved(A, B, C);
            bool swapped_out = is_interleaved(A, B, swapped_C);

            /* Verification */
            EXPECT_EQ(source_out, swapped_out);
        }
    }
}

/**
 * @brief Metamorphic Relation 30: Removing matching prefixes in A and B, and the prefix in C that's the interleaving of these prefixes, should give the same
 * result.
 *
 */
TEST_P(InterleavingStringParamTest, MR30) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    size_t prefix_length_A = 0, prefix_length_B = 0, prefix_length_C = 0;
    // Starting from C, count how many characters are from A and B respectively
    for (char c : C) {
        if (prefix_length_A < A.length() && c == A[prefix_length_A]) {
            ++prefix_length_A;
            ++prefix_length_C;
        } else if (prefix_length_B < B.length() && c == B[prefix_length_B]) {
            ++prefix_length_B;
            ++prefix_length_C;
        } else {
            break; // Stop when no longer a prefix
        }
    }

    /* Trim the prefixes */
    A.erase(0, prefix_length_A);
    B.erase(0, prefix_length_B);
    C.erase(0, prefix_length_C);

    /* Get source output */
    bool source_out = is_interleaved(input.A, input.B, input.C);

    /* Get follow-up output after trimming */
    bool follow_out = is_interleaved(A, B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}
/**
 * @brief Metamorphic Relation 31: Applying the same set of string operations to A, B, and C should maintain their interleaving relationship.
 *
 */
TEST_P(InterleavingStringParamTest, MR31) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Define a set of operations */
    auto to_uppercase = [](string &str) { std::transform(str.begin(), str.end(), str.begin(), ::toupper); };
    auto reverse_string = [](string &str) { std::reverse(str.begin(), str.end()); };

    /* Apply operations to strings */
    to_uppercase(A);
    to_uppercase(B);
    to_uppercase(C);
    reverse_string(A);
    reverse_string(B);
    reverse_string(C);

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 32: If the last character of C corresponds to the end of A or B, removing it should maintain the interleaving relationship.
 *
 */
TEST_P(InterleavingStringParamTest, MR32) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Check if the last character of C matches the end of A or B */
    if (!C.empty() && ((!A.empty() && C.back() == A.back()) || (!B.empty() && C.back() == B.back()))) {
        /* Remove last character from C and from A or B accordingly */
        C.pop_back();
        if (!A.empty() && C.back() == A.back()) {
            A.pop_back();
        } else if (!B.empty() && C.back() == B.back()) {
            B.pop_back();
        }

        /* Get follow-up output */
        bool follow_out = is_interleaved(A, B, C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

/**
 * @brief Metamorphic Relation 33: Swapping characters within A or within B that are not present in C should not affect the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR33) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Find two characters in A that are not present in C */
    if (A.length() >= 4) {
        char charA1 = '?', charA2 = '!';
        if (A.find(charA1) != std::string::npos && A.find(charA2) != std::string::npos && C.find(charA1) == std::string::npos &&
            C.find(charA2) == std::string::npos) {
            std::swap(A[A.find(charA1)], A[A.find(charA2)]);

            /* Get source output */
            bool source_out = is_interleaved(input.A, input.B, input.C);

            /* Get follow-up output */
            bool follow_out = is_interleaved(A, B, C);

            /* Verification */
            EXPECT_EQ(source_out, follow_out);
        }
    }
}

/**
 * @brief Metamorphic Relation 34: Inverting the case (uppercase <-> lowercase) of characters in A and B should not change the result, if the case is also
 * inverted in C.
 *
 */
TEST_P(InterleavingStringParamTest, MR34) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Invert the case of A */
    std::for_each(A.begin(), A.end(), [](char &c) {
        if (std::isupper(c))
            c = std::tolower(c);
        else if (std::islower(c))
            c = std::toupper(c);
    });

    /* Invert the case of B */
    std::for_each(B.begin(), B.end(), [](char &c) {
        if (std::isupper(c))
            c = std::tolower(c);
        else if (std::islower(c))
            c = std::toupper(c);
    });

    /* Invert the case of C to correspond with changes in A and B */
    std::for_each(C.begin(), C.end(), [](char &c) {
        if (std::isupper(c))
            c = std::tolower(c);
        else if (std::islower(c))
            c = std::toupper(c);
    });

    /* Get source output */
    bool source_out = is_interleaved(input.A, input.B, input.C);

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 35: Concatenating a common suffix 'D' to both A and B, and 'DD' to C, should not change the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR35) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C, D = "DD";

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Concatenate 'D' to A, B and 'DD' to C */
    A += D;
    B += D;
    C += D + D;

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}
/**
 * @brief Metamorphic Relation 36: Duplicating every character in A and B and their corresponding characters in C should keep the result unchanged.
 *
 */
TEST_P(InterleavingStringParamTest, MR36) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Function to duplicate each character in a string */
    auto duplicate_chars = [](string &str) {
        size_t length = str.length();
        for (size_t i = length; i > 0; --i) {
            str.insert(i - 1, 1, str[i - 1]);
        }
    };

    /* Duplicate characters in A and B */
    duplicate_chars(A);
    duplicate_chars(B);

    /* Duplicate corresponding characters in C */
    duplicate_chars(C);

    /* Get source output */
    bool source_out = is_interleaved(input.A, input.B, input.C);

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 37: For any characters in A or B, replacing occurrences in both A and B with a unique character, and doing the same in C, should
 * keep the result unchanged.
 *
 */
TEST_P(InterleavingStringParamTest, MR37) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Choose a character in A or B for replacement and its replacement */
    char char_to_replace = 'm';  // The character in A and B for replacement.
    char replacement_char = '~'; // The unique character not present in A or B.

    /* Replace the chosen character with the unique character */
    std::replace(A.begin(), A.end(), char_to_replace, replacement_char);
    std::replace(B.begin(), B.end(), char_to_replace, replacement_char);
    std::replace(C.begin(), C.end(), char_to_replace, replacement_char);

    /* Get source output */
    bool source_out = is_interleaved(input.A, input.B, input.C);

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 38: Extending A and B with characters not in C and extending C with any string that includes the extensions should keep the
 * result unchanged.
 *
 */
TEST_P(InterleavingStringParamTest, MR38) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    string A_extension = "&!$";    // Characters not in C
    string B_extension = "*#@";    // Characters not in C
    string C_extension = "&!*@$#"; // Some combination of A_extension and B_extension

    /* Extend A, B, and C */
    A += A_extension;
    B += B_extension;
    C += C_extension;

    /* Get source output */
    bool source_out = is_interleaved(input.A, input.B, input.C);

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, B, C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 39: If C contains additional characters not from A or B, removing them from C should keep the result unchanged.
 *
 */
TEST_P(InterleavingStringParamTest, MR39) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Find and remove characters from C that do not belong to A or B */
    string filtered_C;
    std::copy_if(C.begin(), C.end(), std::back_inserter(filtered_C),
                 [&A, &B](const char &c) { return A.find(c) != std::string::npos || B.find(c) != std::string::npos; });

    /* Get source output */
    bool source_out = is_interleaved(input.A, input.B, input.C);

    /* Get follow-up output */
    bool follow_out = is_interleaved(A, B, filtered_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 40: Trimming identical trailing characters from A, B, and C when all three strings end with the same character should not affect
 * the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR40) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    if (!(A.empty() || B.empty() || C.empty()) && A.back() == B.back() && A.back() == C.back()) {
        /* Trim identical trailing characters from A, B, and C */
        while (!(A.empty() || B.empty() || C.empty()) && A.back() == B.back() && A.back() == C.back()) {
            A.pop_back();
            B.pop_back();
            C.pop_back();
        }

        /* Get source output */
        bool source_out = is_interleaved(input.A, input.B, input.C);

        /* Get follow-up output */
        bool follow_out = is_interleaved(A, B, C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}
/**
 * @brief Metamorphic Relation 41: If every character in A is replaced with a non-alphabetic character not in B or C, and C is modified accordingly, it should
 * not affect the result.
 *
 */
TEST_P(InterleavingStringParamTest, MR41) {
    /* Get the source inputs */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    // Character to be used for replacement
    char replacement = '1';

    // Ensure the replacement character is not in B or C
    if (B.find(replacement) == string::npos && C.find(replacement) == string::npos) {
        // Replace every character of A in C with the replacement character
        for (char &c : C) {
            if (A.find(c) != string::npos) {
                c = replacement; // Replace with non-alphabetic character
            }
        }

        // Replace every character in A with the replacement character
        std::fill(A.begin(), A.end(), replacement);

        /* Get source output */
        bool source_out = is_interleaved(input.A, input.B, input.C);

        /* Get follow-up output */
        bool follow_out = is_interleaved(A, B, C);

        /* Verification */
        EXPECT_EQ(source_out, follow_out);
    }
}

INSTANTIATE_TEST_CASE_P(TrueReturn, InterleavingStringParamTest, testing::ValuesIn(gen_tcs_randomly()));