#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <string>
#include <unordered_set>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class DistinctSubsequenceParamTest : public ::testing::TestWithParam<DistinctSubsequenceInput> {};

/**
 * Metamorphic relation 1: The number of distinct subsequences for s and t should be greater than or equal to the number of distinct subsequences for t and s.
 */
TEST_P(DistinctSubsequenceParamTest, MR1) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    int follow_out = numDistinct(t, s);

    /* Verification */
    EXPECT_GE(source_out, follow_out);
}

/**
 * Metamorphic relation 2: Add a character to the end of s, the number of distinct subsequences for the modified s and t should be greater than or equal to the
 * number of distinct subsequences for the original s and t.
 */
TEST_P(DistinctSubsequenceParamTest, MR2) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    string follow_s = s.append("a");
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * Metamorphic relation 3: Removing a character from s, the number of distinct subsequences for the reduced s and t should be smaller than or equal to the
 * number of distinct subsequences for the original s and t.
 */
TEST_P(DistinctSubsequenceParamTest, MR3) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    string follow_s = s.substr(0, s.size() - 1);
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}

/**
 * Metamorphic relation 4: Reversing the strings s and t should not change the number of distinct subsequences for them.
 */
TEST_P(DistinctSubsequenceParamTest, MR4) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    reverse(s.begin(), s.end());
    reverse(t.begin(), t.end());
    int follow_out = numDistinct(s, t);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 5: Swapping the strings s and t should not change the number of distinct subsequences for them.
 */
TEST_P(DistinctSubsequenceParamTest, MR5) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    int follow_out = numDistinct(t, s);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 6: If s and t are the same strings, the number of distinct subsequences should be 1.
 */
TEST_P(DistinctSubsequenceParamTest, MR6) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip if s and t are different */
    if (s != t) {
        GTEST_SKIP();
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Verification */
    EXPECT_EQ(source_out, 1);
}

/**
 * Metamorphic relation 7: If t is an empty string, the number of distinct subsequences should be 1.
 */
TEST_P(DistinctSubsequenceParamTest, MR7) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string t = input.t;

    /* Skip if t is not empty */
    if (!t.empty()) {
        GTEST_SKIP();
    }

    /* Get source output */
    int source_out = numDistinct(input.s, t);

    /* Verification */
    EXPECT_EQ(source_out, 1);
}

/**
 * Metamorphic relation 8: The number of distinct subsequences for s and t should be equal to or greater than the number of distinct subsequences for s and a
 * subsequence of t.
 */
TEST_P(DistinctSubsequenceParamTest, MR8) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    string sub_t = t.substr(0, t.size() - 1);
    int follow_out = numDistinct(s, sub_t);

    /* Verification */
    EXPECT_GE(source_out, follow_out);
}

/**
 * Metamorphic relation 9: If t is a substring of s, the number of distinct subsequences for s and t should be greater than or equal to the number of distinct
 * subsequences for t and t.
 */
TEST_P(DistinctSubsequenceParamTest, MR9) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip if t is not a substring of s */
    if (s.find(t) == string::npos) {
        GTEST_SKIP();
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    int follow_out = numDistinct(t, t);

    /* Verification */
    EXPECT_GE(source_out, follow_out);
}

/**
 * Metamorphic relation 10: Repeat the input strings for a certain number of times, the number of distinct subsequences should increase or remain the same.
 */
TEST_P(DistinctSubsequenceParamTest, MR10) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    string follow_s = s + s + s; // Repeat s three times

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * Metamorphic relation 11: If t is longer than s, the number of distinct subsequences for s and t should be 0.
 */
TEST_P(DistinctSubsequenceParamTest, MR11) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip if t is not longer than s */
    if (t.size() <= s.size()) {
        GTEST_SKIP();
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Verification */
    EXPECT_EQ(source_out, 0);
}

/**
 * Metamorphic relation 12: Multiply the length of s by a factor, the number of distinct subsequences should also be multiplied by the same factor.
 */
TEST_P(DistinctSubsequenceParamTest, MR12) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    string follow_s = string(s);
    follow_s.append(s);

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    EXPECT_EQ(follow_out, source_out * 2);
}

/**
 * Metamorphic relation 13: If t is an empty string, increasing the length of s should not change the number of distinct subsequences.
 */
TEST_P(DistinctSubsequenceParamTest, MR13) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip if t is not empty */
    if (!t.empty()) {
        GTEST_SKIP();
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    string follow_s = s + "x"; // Append a character to s

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 14: Reversing the string t should not change the number of distinct subsequences for s and t.
 */
TEST_P(DistinctSubsequenceParamTest, MR14) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    reverse(t.begin(), t.end());

    /* Get follow-up output */
    int follow_out = numDistinct(s, t);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 15: If the two strings have no common characters, the number of distinct subsequences for s and t should be 1.
 */
TEST_P(DistinctSubsequenceParamTest, MR15) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Check if the strings have common characters */
    bool hasCommonCharacter = false;
    for (char c : s) {
        if (t.find(c) != string::npos) {
            hasCommonCharacter = true;
            break;
        }
    }

    /* Skip if the strings have common characters */
    if (hasCommonCharacter) {
        GTEST_SKIP();
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Verification */
    EXPECT_EQ(source_out, 1);
}

/**
 * Metamorphic relation 16: Inserting a character into string t should not decrease the number of distinct subsequences for s and t.
 */
TEST_P(DistinctSubsequenceParamTest, MR16) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    t.insert(0, "x"); // Insert a character into t
    int follow_out = numDistinct(s, t);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}

/**
 * Metamorphic relation 17: The number of distinct subsequences for string s and an empty string should be the same as the length of s.
 */
TEST_P(DistinctSubsequenceParamTest, MR17) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s;

    /* Get source output */
    int source_out = numDistinct(s, "");

    /* Verification */
    EXPECT_EQ(source_out, s.length());
}

/**
 * Metamorphic relation 18: If the strings are identical, decreasing the length of s should decrease the number of distinct subsequences.
 */
TEST_P(DistinctSubsequenceParamTest, MR18) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip if s and t are different strings */
    if (s != t) {
        GTEST_SKIP();
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    string follow_s = s.substr(0, s.size() - 1);

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}

/**
 * Metamorphic relation 19: The number of distinct subsequences for an empty string should be 1, regardless of the string t.
 */
TEST_P(DistinctSubsequenceParamTest, MR19) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string t = input.t;

    /* Get source output */
    int source_out = numDistinct("", t);

    /* Verification */
    EXPECT_EQ(source_out, 1);
}

/**
 * Metamorphic relation 20: If the length of string t is 1, the number of distinct subsequences for s and t should be equal to the count of occurrences of t in
 * s.
 */
TEST_P(DistinctSubsequenceParamTest, MR20) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip if the length of t is not 1 */
    if (t.length() != 1) {
        GTEST_SKIP();
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Count occurrences of t in s */
    int count = 0;
    for (char c : s) {
        if (c == t[0]) {
            count++;
        }
    }

    /* Verification */
    EXPECT_EQ(source_out, count);
}

/**
 * Metamorphic relation 21: The number of distinct subsequences for t and s should be the same as the number of distinct subsequences for s and t.
 */
TEST_P(DistinctSubsequenceParamTest, MR21) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Get source output */
    int source_out = numDistinct(s, t);
    int follow_out = numDistinct(t, s);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * Metamorphic relation 22: If both s and t are empty strings, the number of distinct subsequences should be 1.
 */
TEST_P(DistinctSubsequenceParamTest, MR22) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip if both s and t are not empty */
    if (!s.empty() || !t.empty()) {
        GTEST_SKIP();
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Verification */
    EXPECT_EQ(source_out, 1);
}

/**
 * Metamorphic relation 23: If s is an empty string, the number of distinct subsequences for s and t should be 0, unless t is also an empty string.
 */
TEST_P(DistinctSubsequenceParamTest, MR23) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip if s is not empty */
    if (!s.empty()) {
        GTEST_SKIP();
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Verification */
    if (t.empty()) {
        EXPECT_EQ(source_out, 1);
    } else {
        EXPECT_EQ(source_out, 0);
    }
}

/**
 * Metamorphic relation 24: If t is a subsequence of s, then the number of distinct subsequences of s and t should be greater than or equal to the number of
 * distinct subsequences of s and the first half of t.
 */
TEST_P(DistinctSubsequenceParamTest, MR24) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip if t is not a subsequence of s */
    if (s.find(t) == string::npos) {
        GTEST_SKIP();
    }

    /* Get source output */
    int source_out = numDistinct(s, t);
    string sub_t = t.substr(0, t.size() / 2);
    int sub_t_out = numDistinct(s, sub_t);

    /* Verification */
    EXPECT_GE(source_out, sub_t_out);
}

/**
 * Metamorphic relation 25: If s and t are the same string, duplicating t should not change the number of distinct subsequences of s and t.
 */
TEST_P(DistinctSubsequenceParamTest, MR25) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    if (s.compare(t))
        return;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    string follow_t = t + t; // Duplicate t
    int follow_out = numDistinct(s, follow_t);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Check whether s2 is the subsequence of s1.
 *
 * @param s1
 * @param s2
 * @return true s2 is the subsequence of s1.
 * @return false s2 isn't the subsequence of s1.
 */
bool isSubsequence(string s1, string s2) {
    int p2 = 0;
    for (int p1 = 0; p1 < s1.length(); p1++) {
        if (p2 >= s2.length())
            break;
        if (s1[p1] == s2[p2])
            p2++;
    }
    return p2 >= s2.length();
}

/**
 * Metamorphic relation 26: If t is a subsequence of s, then removing characters from s should not decrease the number of distinct subsequences for s and t.
 */
TEST_P(DistinctSubsequenceParamTest, MR26) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    if (!isSubsequence(s, t))
        return;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    string follow_s = s.substr(0, s.size() - 1); // Remove last character from s
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * Metamorphic relation 27: If the length of t is greater than the length of s, the number of distinct subsequences for s and t should be zero.
 */
TEST_P(DistinctSubsequenceParamTest, MR27) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip if the length of t is not greater than the length of s */
    if (t.length() <= s.length()) {
        GTEST_SKIP();
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Verification */
    EXPECT_EQ(source_out, 0);
}

/**
 * Metamorphic relation 28: If repeated characters are removed from both s and t, the number of distinct subsequences for s and t should not change.
 */
TEST_P(DistinctSubsequenceParamTest, MR28) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Remove repeated characters from s and t */
    string cleaned_s = "", cleaned_t = "";
    for (char c : s) {
        if (cleaned_s.find(c) == string::npos) {
            cleaned_s.push_back(c);
        }
    }
    for (char c : t) {
        if (cleaned_t.find(c) == string::npos) {
            cleaned_t.push_back(c);
        }
    }

    /* Get source output */
    int source_out = numDistinct(cleaned_s, cleaned_t);

    /* Verification */
    EXPECT_LE(source_out, numDistinct(s, t));
}

/**
 * Metamorphic relation 29: Exchanging the positions of two characters in string s should not change the number of distinct subsequences for s and t.
 */
TEST_P(DistinctSubsequenceParamTest, MR29) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input with exchanged characters */
    string follow_s = s;
    if (follow_s.length() >= 2) {
        swap(follow_s[0], follow_s[1]); // Exchange the positions of the first two characters
    }
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * Metamorphic relation 30: If s and t contain duplicate characters, removing duplicate characters from both strings should not change the number of distinct
 * subsequences for s and t.
 */
TEST_P(DistinctSubsequenceParamTest, MR30) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Remove duplicate characters from s and t */
    string unique_s = "", unique_t = "";
    for (char c : s) {
        if (unique_s.find(c) == string::npos) {
            unique_s += c;
        }
    }
    for (char c : t) {
        if (unique_t.find(c) == string::npos) {
            unique_t += c;
        }
    }

    /* Get source output */
    int source_out = numDistinct(unique_s, unique_t);

    /* Verification */
    EXPECT_EQ(source_out, numDistinct(s, t));
}

/**
 * Metamorphic relation 31: Swapping the first and last characters of string t should not change the number of distinct subsequences for s and t.
 */
TEST_P(DistinctSubsequenceParamTest, MR31) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    string follow_t = t;
    if (follow_t.length() >= 2) {
        swap(follow_t[0], follow_t[follow_t.length() - 1]); // Swap first and last characters of t
    }
    int follow_out = numDistinct(s, follow_t);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * Metamorphic relation 32: If the characters in both s and t are alphabetically sorted, the number of distinct subsequences for s and t should be the same as
 * the number of distinct subsequences for the original s and t.
 */
TEST_P(DistinctSubsequenceParamTest, MR32) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Sort characters in s and t */
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Verification */
    EXPECT_EQ(source_out, numDistinct(input.s, input.t));
}

/**
 * Metamorphic relation 33: Replacing all occurrences of a character in s with a different character should not change the number of distinct subsequences for s
 * and t.
 */
TEST_P(DistinctSubsequenceParamTest, MR33) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Replace all occurrences of a character in s with a different character */
    char original_char = s[0];
    char replacement_char = 'x';
    for (char &c : s) {
        if (c == original_char) {
            c = replacement_char;
        }
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Verification */
    EXPECT_EQ(source_out, numDistinct(input.s, t));
}

/**
 * Metamorphic relation 34: If s and t are of different lengths and s is a substring of t, the number of distinct subsequences for s and t should be 0.
 */
TEST_P(DistinctSubsequenceParamTest, MR34) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip if the lengths are the same or s is not a substring of t */
    if (s.length() >= t.length() || t.find(s) == string::npos) {
        GTEST_SKIP();
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Verification */
    EXPECT_EQ(source_out, 0);
}

/**
 * Metamorphic relation 35: If string s is empty, the number of distinct subsequences should be 0.
 */
TEST_P(DistinctSubsequenceParamTest, MR35) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip if s is not empty */
    if (!s.empty()) {
        GTEST_SKIP();
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Verification */
    EXPECT_EQ(source_out, 0);
}

/**
 * Metamorphic relation 36: If t is a subsequence of s, adding characters to t should not reduce the number of distinct subsequences for s and t.
 */
TEST_P(DistinctSubsequenceParamTest, MR36) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    if (!isSubsequence(s, t))
        return;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    t += "x"; // Add a character to t
    int follow_out = numDistinct(s, t);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * Metamorphic relation 37: If t is empty, then the number of distinct subsequences for s and t should be 1, regardless of the content of s.
 */
TEST_P(DistinctSubsequenceParamTest, MR37) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string t = input.t;

    /* Get source output */
    int source_out = numDistinct("", t);

    /* Verification */
    EXPECT_EQ(source_out, 1);
}

/**
 * Metamorphic relation 38: If t is an empty string, adding characters to s should not decrease the number of distinct subsequences for s and t.
 */
TEST_P(DistinctSubsequenceParamTest, MR38) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    if (!t.empty())
        return;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    s += "x"; // Add a character to s
    int follow_out = numDistinct(s, t);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}

/**
 * Metamorphic relation 39: Modifying the string t to contain characters not present in s should not change the number of distinct subsequences for s and t.
 */
TEST_P(DistinctSubsequenceParamTest, MR39) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    string newChars = ""; // Characters not present in s

    for (char c = 'a'; c <= 'z'; c++) {
        if (s.find(c) == string::npos)
            newChars += c;
    }

    /* Replace characters in t with new characters */
    for (char &c : t) {
        if (s.find(c) == string::npos) {
            c = newChars[rand() % newChars.size()]; // Replace with a random new character
        }
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Verification */
    EXPECT_EQ(source_out, numDistinct(input.s, input.t));
}

/**
 * Metamorphic relation 40: If t is a non-empty substring of s, then changing the order of characters in t should not change the number of distinct subsequences
 * for s and t.
 */
TEST_P(DistinctSubsequenceParamTest, MR40) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    if (s.length() < 2 || t.length() < 2) {
        GTEST_SKIP();
    }

    /* Shuffle the characters in t */
    random_shuffle(t.begin(), t.end());

    /* Get source output */
    int source_out = numDistinct(input.s, t);

    /* Verification */
    EXPECT_EQ(source_out, numDistinct(s, input.t));
}

INSTANTIATE_TEST_CASE_P(TrueReturn, DistinctSubsequenceParamTest, testing::ValuesIn(gen_tcs_randomly()));