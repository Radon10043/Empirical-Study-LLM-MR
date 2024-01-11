#include <cmath>
#include <gtest/gtest.h>
#include <string>
#include <unordered_set>
#include <algorithm>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class DistinctSubsequenceParamTest : public ::testing::TestWithParam<DistinctSubsequenceInput> {};

// Metamorphic relation 4: Remove a character from s, the output should be smaller or the same.
TEST_P(DistinctSubsequenceParamTest, MR4) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    string follow_s = s.substr(0, s.size() - 1); // Remove the last character
    int follow_out = numDistinct(follow_s, t);

    EXPECT_LE(follow_out, source_out);
}

// Metamorphic relation 5: Insert a character at any position in s, the output should be larger or the same.
TEST_P(DistinctSubsequenceParamTest, MR5) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    string follow_s = s.insert(0, "a"); // Insert 'a' at the beginning
    int follow_out = numDistinct(follow_s, t);

    EXPECT_GE(follow_out, source_out);
}

// Metamorphic relation 6: Modify the case of characters in s (e.g., change lowercase to uppercase), the output should remain unchanged.
TEST_P(DistinctSubsequenceParamTest, MR6) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    transform(s.begin(), s.end(), s.begin(), ::toupper); // Change case of characters
    int follow_out = numDistinct(s, t);

    EXPECT_EQ(follow_out, source_out);
}

// Metamorphic relation 7: Change the order of characters while keeping the same characters, the output should remain unchanged.
TEST_P(DistinctSubsequenceParamTest, MR7) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    random_shuffle(s.begin(), s.end()); // Change the order of characters
    int follow_out = numDistinct(s, t);

    EXPECT_EQ(follow_out, source_out);
}

// Metamorphic relation 8: Concatenate s with itself, the output should be larger or the same.
TEST_P(DistinctSubsequenceParamTest, MR8) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    string follow_s = s + s; // Concatenate s with itself
    int follow_out = numDistinct(follow_s, t);

    EXPECT_GE(follow_out, source_out);
}

// Metamorphic relation 9: Replace a character in s with another character, the output should remain unchanged.
TEST_P(DistinctSubsequenceParamTest, MR9) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    string follow_s = s;
    if (follow_s.size() > 1) {
        swap(follow_s[0], follow_s[1]); // Swap the first two characters
    }
    int follow_out = numDistinct(follow_s, t);

    EXPECT_EQ(follow_out, source_out);
}

// Metamorphic relation 10: Swap the positions of two characters in s, the output should remain unchanged.
TEST_P(DistinctSubsequenceParamTest, MR10) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    string follow_s = s;
    if (follow_s.size() > 1) {
        replace(follow_s.begin(), follow_s.end(), 'a', 'b'); // Replace 'a' with 'b'
    }
    int follow_out = numDistinct(follow_s, t);

    EXPECT_EQ(follow_out, source_out);
}

// Metamorphic relation 11: Double the occurrence of a particular character in s, the output should be larger or the same.
TEST_P(DistinctSubsequenceParamTest, MR11) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    // Double the occurrence of the first character in s
    string follow_s = s;
    if (!follow_s.empty()) {
        follow_s.insert(1, 1, follow_s[0]);
    }
    int follow_out = numDistinct(follow_s, t);

    EXPECT_GE(follow_out, source_out);
}

// Metamorphic relation 12: Reverse the string s, the output should remain unchanged.
TEST_P(DistinctSubsequenceParamTest, MR12) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    reverse(s.begin(), s.end());
    int follow_out = numDistinct(s, t);

    EXPECT_EQ(follow_out, source_out);
}

// Metamorphic relation 13: Remove all occurrences of a character in s, the output should be larger or the same.
TEST_P(DistinctSubsequenceParamTest, MR13) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    // Remove all occurrences of the first character in s
    string follow_s = s;
    if (!follow_s.empty()) {
        follow_s.erase(remove(follow_s.begin(), follow_s.end(), follow_s[0]), follow_s.end());
    }
    int follow_out = numDistinct(follow_s, t);

    EXPECT_GE(follow_out, source_out);
}

// Metamorphic relation 14: Swap the positions of two substrings within s, the output should remain unchanged.
TEST_P(DistinctSubsequenceParamTest, MR14) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    // Swap the positions of the first two characters
    string follow_s = s;
    if (follow_s.size() > 2) {
        swap_ranges(follow_s.begin(), follow_s.begin() + 2, follow_s.begin() + 2);
    }
    int follow_out = numDistinct(follow_s, t);

    EXPECT_EQ(follow_out, source_out);
}

// Metamorphic relation 15: Append a substring to s, the output should be larger or the same.
TEST_P(DistinctSubsequenceParamTest, MR15) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    string follow_s = s + "xyz"; // Append "xyz" to s
    int follow_out = numDistinct(follow_s, t);

    EXPECT_GE(follow_out, source_out);
}

// Metamorphic relation 16: Convert each character in s to its corresponding ASCII value, the output should remain unchanged.
TEST_P(DistinctSubsequenceParamTest, MR16) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    // Convert each character in s to its ASCII value
    for (char &c : s) {
        c = static_cast<char>(int(c)); // Convert to ASCII value
    }
    int follow_out = numDistinct(s, t);

    EXPECT_EQ(follow_out, source_out);
}

/* Implemented by Radon */
int factorial(int n) {
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

// Metamorphic relation 17: If all characters in s are unique, the output should be equal to the factorial of the string length.
TEST_P(DistinctSubsequenceParamTest, MR17) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    // If all characters in s are unique, the output should be the factorial of the string length
    bool allUniqueChars = (s.size() == std::unordered_set<char>(s.begin(), s.end()).size());
    int expected_out = allUniqueChars ? factorial(s.size()) : source_out;

    EXPECT_EQ(source_out, expected_out);
}

// Metamorphic relation 18: Reverse the order of the characters in the target string t, the output should remain unchanged.
TEST_P(DistinctSubsequenceParamTest, MR18) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    // Reverse the order of characters in the target string t
    reverse(t.begin(), t.end());
    int follow_out = numDistinct(s, t);

    EXPECT_EQ(follow_out, source_out);
}

// Metamorphic relation 19: Remove all occurrences of a character in t, the output should be smaller or the same.
TEST_P(DistinctSubsequenceParamTest, MR19) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    // Remove all occurrences of the first character in t
    string follow_t = t;
    if (!follow_t.empty()) {
        follow_t.erase(remove(follow_t.begin(), follow_t.end(), follow_t[0]), follow_t.end());
    }
    int follow_out = numDistinct(s, follow_t);

    EXPECT_LE(follow_out, source_out);
}

// Metamorphic relation 20: If the target string t is empty, the output should be 1 if the source string s is also empty, and 0 otherwise.
TEST_P(DistinctSubsequenceParamTest, MR20) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    // If the target string t is empty, the output should be 1 if the source string s is also empty, and 0 otherwise
    int expected_out = (t.empty() && s.empty()) ? 1 : (t.empty() ? 0 : source_out);

    EXPECT_EQ(source_out, expected_out);
}

// Metamorphic relation 21: If the source string s is empty, the output should be 0 if the target string t is not empty.
TEST_P(DistinctSubsequenceParamTest, MR21) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    if (s.empty()) {
        // If the source string s is empty, the output should be 0 if the target string t is not empty
        int follow_out = numDistinct(s, "xyz"); // Assume t is not empty
        ASSERT_EQ(follow_out, 0);
    }
}

// Metamorphic relation 22: If `t` is a subsequence of `s`, then the output should be greater than or equal to 1.
TEST_P(DistinctSubsequenceParamTest, MR22) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    size_t found = s.find(t);
    int expected_out = (found != string::npos) ? 1 : source_out;

    EXPECT_GE(source_out, expected_out);
}

// Metamorphic relation 23: If the lengths of `s` and `t` are equal, and `t` is a permutation of `s`, then the output should be 1.
TEST_P(DistinctSubsequenceParamTest, MR23) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    int expected_out = (s == t) ? 1 : source_out;

    EXPECT_EQ(source_out, expected_out);
}

// Metamorphic relation 24: If `t` is an empty string, the output should be 1 as an empty string is always a subsequence of any string.
TEST_P(DistinctSubsequenceParamTest, MR24) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    int expected_out = (t.empty()) ? 1 : source_out;

    EXPECT_EQ(source_out, expected_out);
}

// Metamorphic relation 25: If `t` is longer than `s`, the output should be 0 as it is not possible for `t` to be a subsequence of `s` if it is longer.
TEST_P(DistinctSubsequenceParamTest, MR25) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    int expected_out = (t.length() > s.length()) ? 0 : source_out;

    EXPECT_EQ(source_out, expected_out);
}

/* TODO: Implemented by Radon */
int countSubstring(string s, string t) {}

// Metamorphic relation 26: If `t` is a substring of `s`, the output should be equal to the number of occurrences of `t` in `s`.
TEST_P(DistinctSubsequenceParamTest, MR26) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    size_t found = s.find(t);
    int expected_out = (found != string::npos) ? countSubstring(s, t) : 0;

    EXPECT_EQ(source_out, expected_out);
}

/**
 * @brief Implemented By Radon, check whether t is a subsequence of s
 *
 * @param s
 * @param t
 * @return true
 * @return false
 */
bool checkSubsequence(string &s, string &t) {
    int m = s.length(), n = t.length();
    int j = 0; // Index of t
    for (int i = 0; i < m && j < n; i++) {
        if (s[i] == t[j]) {
            j++;
        }
    }
    return (j == n);
}

// Metamorphic relation 27: If `t` is not a subsequence of `s`, the output should be 0.
TEST_P(DistinctSubsequenceParamTest, MR27) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    bool isSubsequence = checkSubsequence(s, t);
    int expected_out = (isSubsequence) ? source_out : 0;

    EXPECT_EQ(source_out, expected_out);
}

// Metamorphic relation 28: If both `s` and `t` are empty, the output should be 1 as an empty string is a subsequence of another empty string.
TEST_P(DistinctSubsequenceParamTest, MR28) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    int expected_out = (s.empty() && t.empty()) ? 1 : source_out;

    EXPECT_EQ(source_out, expected_out);
}

// Metamorphic relation 29: If `s` and `t` have the same characters but in a different order, the output should be the same.
TEST_P(DistinctSubsequenceParamTest, MR29) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    int expected_out = (s == t) ? source_out : numDistinct(t, s);

    EXPECT_EQ(source_out, expected_out);
}

/**
 * @brief Implemented by Radon.
 *
 * @param s
 * @param t
 * @return int
 */
int numDistinctWithDuplicates(string &s, string &t) {
    return numDistinct(s, t);       // ?
}

// Metamorphic relation 30: If `t` contains duplicate characters, the output should be equal to the number of distinct subsequences of `s` which equals `t`.
TEST_P(DistinctSubsequenceParamTest, MR30) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    std::unordered_set<char> uniqueChars(t.begin(), t.end());
    int expected_out = (uniqueChars.size() == t.size()) ? numDistinctWithDuplicates(s, t) : source_out;

    EXPECT_EQ(source_out, expected_out);
}

// Metamorphic relation 31: If `t` is the empty string, the output should be the total number of distinct subsequences of `s`.
TEST_P(DistinctSubsequenceParamTest, MR31) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    int expected_out = numDistinct(s, "");

    EXPECT_EQ(source_out, expected_out);
}

// Metamorphic relation 32: If `t` is a subsequence of `s`, removing a character from `t` should not increase the number of distinct subsequences of `s` that
// equal `t`.
TEST_P(DistinctSubsequenceParamTest, MR32) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    if (t.length() > 1) {
        string reduced_t = t.substr(1); // Remove the first character
        int reduced_out = numDistinct(s, reduced_t);
        EXPECT_LE(reduced_out, source_out);
    }
}

// Metamorphic relation 33: If `t` is a subsequence of `s`, adding a character to `t` should not decrease the number of distinct subsequences of `s` that equal
// `t`.
TEST_P(DistinctSubsequenceParamTest, MR33) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    string extended_t = t + "x"; // Add a new character at the end
    int extended_out = numDistinct(s, extended_t);
    EXPECT_GE(extended_out, source_out);
}

// Metamorphic relation 34: If `t` is a subsequence of `s`, doubling the occurrences of a character in `t` should not decrease the number of distinct
// subsequences of `s` that equal `t`.
TEST_P(DistinctSubsequenceParamTest, MR34) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    string doubled_t = "";
    for (char c : t) {
        doubled_t += c;
        doubled_t += c;
    }
    int doubled_out = numDistinct(s, doubled_t);
    EXPECT_GE(doubled_out, source_out);
}

// Metamorphic relation 35: If `t` is a subsequence of `s`, removing special characters from `t` should not increase the number of distinct subsequences of `s`
// that equal the modified `t`.
TEST_P(DistinctSubsequenceParamTest, MR35) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    string modified_t = "";
    for (char c : t) {
        if (isalpha(c)) { // Removing special characters
            modified_t += c;
        }
    }
    int modified_out = numDistinct(s, modified_t);
    EXPECT_LE(modified_out, source_out);
}

// Metamorphic relation 36: If `t` is a subsequence of `s`, changing the order of characters while keeping the same characters in `t`, the output should remain
// unchanged.
TEST_P(DistinctSubsequenceParamTest, MR36) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    random_shuffle(t.begin(), t.end()); // Change the order of characters in t
    int follow_out = numDistinct(s, t);

    EXPECT_EQ(follow_out, source_out);
}

// Metamorphic relation 37: If each character in `t` is replaced with a different character while keeping the same number of occurrences, the output should
// remain unchanged.
TEST_P(DistinctSubsequenceParamTest, MR37) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    string modified_t = "";
    char replaceChar = 'A';
    map<char, char> replacementMap;
    for (char c : t) {
        if (replacementMap.find(c) == replacementMap.end()) {
            replacementMap[c] = replaceChar++;
        }
        modified_t += replacementMap[c];
    }
    int modified_out = numDistinct(s, modified_t);
    EXPECT_EQ(modified_out, source_out);
}

// Metamorphic relation 38: If `t` is a subsequence of `s`, adding a prefix to `t` should not decrease the number of distinct subsequences of `s` that equal the
// modified `t`.
TEST_P(DistinctSubsequenceParamTest, MR38) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    string prefixed_t = "prefix" + t; // Add a prefix to t
    int prefixed_out = numDistinct(s, prefixed_t);

    EXPECT_GE(prefixed_out, source_out);
}

// Metamorphic relation 39: If `t` is a subsequence of `s`, converting `t` to uppercase or lowercase should not change the number of distinct subsequences of
// `s` that equal `t`.
TEST_P(DistinctSubsequenceParamTest, MR39) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    string upperT = t;
    for (auto &c : upperT) {
        c = toupper(c);
    }
    int upper_out = numDistinct(s, upperT);
    EXPECT_EQ(upper_out, source_out);

    string lowerT = t;
    for (auto &c : lowerT) {
        c = tolower(c);
    }
    int lower_out = numDistinct(s, lowerT);
    EXPECT_EQ(lower_out, source_out);
}

// Metamorphic relation 40: If `t` is a subsequence of `s`, inserting a character at any position in `t` should not decrease the number of distinct subsequences
// of `s` that equal the modified `t`.
TEST_P(DistinctSubsequenceParamTest, MR40) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    string inserted_t = t;
    for (size_t i = 0; i <= t.size(); i++) {
        inserted_t.insert(i, "x"); // Insert a character at any position in t
        int modified_out = numDistinct(s, inserted_t);
        EXPECT_GE(modified_out, source_out);
        // Reset inserted_t
        inserted_t = t;
    }
}

// Metamorphic relation 41: If `t` is a subsequence of `s`, the output should be equal or greater when non-alphabetic characters are removed from `t`.
TEST_P(DistinctSubsequenceParamTest, MR41) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    string modified_t = "";
    for (char c : t) {
        if (isalpha(c)) {
            modified_t += c;
        }
    }
    int modified_out = numDistinct(s, modified_t);
    EXPECT_GE(modified_out, source_out);
}

// Metamorphic relation 42: If `t` is a subsequence of `s`, replacing a character in `t` with another character should not decrease the number of distinct
// subsequences of `s` that equal the modified `t`.
TEST_P(DistinctSubsequenceParamTest, MR42) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    string replaced_t = t;
    if (!t.empty()) {
        replaced_t[0] = 'x'; // Replace the first character
        int replaced_out = numDistinct(s, replaced_t);
        EXPECT_GE(replaced_out, source_out);
    }
}

// Metamorphic relation 43: If `t` is a subsequence of `s`, appending a substring to `t` should not decrease the number of distinct subsequences of `s` that
// equal the modified `t`.
TEST_P(DistinctSubsequenceParamTest, MR43) {
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    int source_out = numDistinct(s, t);

    string appended_t = t + "xyz"; // Append "xyz" to t
    int appended_out = numDistinct(s, appended_t);
    EXPECT_GE(appended_out, source_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, DistinctSubsequenceParamTest, testing::ValuesIn(gen_tcs_randomly()));