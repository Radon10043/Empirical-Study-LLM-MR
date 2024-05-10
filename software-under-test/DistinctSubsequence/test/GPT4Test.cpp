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
 * Metamorphic relation 2: Append any character not in string t to the end of s, the output should be the same.
 */
TEST_P(DistinctSubsequenceParamTest, MR2) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Find a character not in t */
    char c = 'a';
    while (t.find(c) != string::npos) {
        ++c;
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    string follow_s = s + c;

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    ASSERT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 3: Append a character from string t to the end of s, the output should be the same or larger.
 */
TEST_P(DistinctSubsequenceParamTest, MR3) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Get a character from t */
    char c = t.empty() ? 'a' : t.back();

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    string follow_s = s + c;

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    ASSERT_GE(follow_out, source_out);
}

/**
 * Metamorphic relation 4: Reverse string s and t, the output should be the same.
 */
TEST_P(DistinctSubsequenceParamTest, MR4) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input by reversing s and t */
    string follow_s(s.rbegin(), s.rend());
    string follow_t(t.rbegin(), t.rend());

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, follow_t);

    /* Verification */
    ASSERT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 5: Duplicate string s, the output should be the same or larger.
 */
TEST_P(DistinctSubsequenceParamTest, MR5) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    string follow_s = s + s;

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    ASSERT_GE(follow_out, source_out);
}

/**
 * Metamorphic relation 6: Replace a character in s with another character already in s, the output should be the same or larger.
 */
TEST_P(DistinctSubsequenceParamTest, MR6) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip if s is empty or has only 1 distinct character */
    if (s.empty() || set<char>(s.begin(), s.end()).size() < 2) {
        GTEST_SKIP();
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Find a character in s which has duplicates */
    char replace_with = s[0];
    size_t pos = s.find_first_not_of(replace_with);
    if (pos == string::npos) {
        replace_with = s[1];
        pos = 1;
    }
    char c = s[pos];
    /* Construct follow-up input */
    string follow_s = s;
    follow_s[pos] = replace_with;

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    ASSERT_GE(follow_out, source_out);
}

/**
 * Metamorphic relation 7: Insert a character from string t into string s at any position, the output should be the same or larger.
 */
TEST_P(DistinctSubsequenceParamTest, MR7) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip if t is empty */
    if (t.empty()) {
        GTEST_SKIP();
    }

    /* Get a character from t */
    char c = t[rand() % t.length()];

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input by inserting c into s at random position */
    int pos = rand() % (s.length() + 1);
    string follow_s = s.substr(0, pos) + c + s.substr(pos);

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    ASSERT_GE(follow_out, source_out);
}

/**
 * Metamorphic relation 8: If we remove a character from s that is not in t, then the output should remain unchanged.
 */
TEST_P(DistinctSubsequenceParamTest, MR8) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Find a character in s that is not in t */
    size_t position = string::npos;
    for (size_t i = 0; i < s.size(); ++i) {
        if (t.find(s[i]) == string::npos) {
            position = i;
            break;
        }
    }

    /* If no such character is found, skip the test */
    if (position == string::npos) {
        GTEST_SKIP();
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Construct follow-up input */
    string follow_s = s.substr(0, position) + s.substr(position + 1);

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    ASSERT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 9: Deleting a character from string t which is present in s should result in the same or smaller output.
 */
TEST_P(DistinctSubsequenceParamTest, MR9) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Check if there is overlap */
    bool has_overlap = false;
    for (char tc : t) {
        if (s.find(tc) != string::npos) {
            has_overlap = true;
            break;
        }
    }

    /* If no overlapping character, skip the test */
    if (!has_overlap) {
        GTEST_SKIP();
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Remove a character from t that is also in s */
    string follow_t;
    for (char tc : t) {
        if (s.find(tc) == string::npos) {
            follow_t += tc;
        }
    }

    /* If follow_t is empty or same as t, avoid retesting the same scenario or invalid case */
    if (follow_t.empty() || follow_t == t) {
        GTEST_SKIP();
    }

    /* Get follow-up output */
    int follow_out = numDistinct(s, follow_t);

    /* Verification */
    ASSERT_LE(follow_out, source_out);
}

/**
 * Metamorphic relation 10: Swapping two characters in s without affecting their existence in t should not change the result.
 */
TEST_P(DistinctSubsequenceParamTest, MR10) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Look for two characters to swap */
    size_t pos1 = string::npos, pos2 = string::npos;
    for (size_t i = 0; i < s.size() - 1; ++i) {
        for (size_t j = i + 1; j < s.size(); ++j) {
            if (s[i] != s[j] && t.find(s[i]) != string::npos && t.find(s[j]) != string::npos) {
                pos1 = i;
                pos2 = j;
                break;
            }
        }
        if (pos1 != string::npos)
            break;
    }

    /* Check if suitable characters found */
    if (pos1 == string::npos) {
        GTEST_SKIP();
    }

    /* Construct follow-up input by swapping two characters in s */
    string follow_s = s;
    std::swap(follow_s[pos1], follow_s[pos2]);

    /* Get source and follow-up outputs */
    int source_out = numDistinct(s, t);
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    ASSERT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 11: Doubling string t should not change the output as there are no subsequences which can match the doubled string.
 */
TEST_P(DistinctSubsequenceParamTest, MR11) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Construct follow-up input by doubling t */
    string follow_t = t + t;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(s, follow_t);

    /* Verification */
    ASSERT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 12: Capitalizing all characters in both s and t should not change the output (Case-insensitive MR).
 */
TEST_P(DistinctSubsequenceParamTest, MR12) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Convert s and t to uppercase */
    string follow_s = s;
    std::transform(follow_s.begin(), follow_s.end(), follow_s.begin(), ::toupper);
    string follow_t = t;
    std::transform(follow_t.begin(), follow_t.end(), follow_t.begin(), ::toupper);

    /* Get source and follow-up outputs */
    int source_out = numDistinct(s, t);
    int follow_out = numDistinct(follow_s, follow_t);

    /* Verification */
    ASSERT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 13: If we prepend a character from string t to string s, then the output should be the same or larger.
 */
TEST_P(DistinctSubsequenceParamTest, MR13) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip the test if t is empty */
    if (t.empty()) {
        GTEST_SKIP();
    }

    /* Prepend a character from t to s */
    char c = t[0];
    string follow_s = c + s;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    ASSERT_GE(follow_out, source_out);
}

/**
 * Metamorphic relation 14: If string s contains duplicate adjacent characters and one is removed, the output should not decrease.
 */
TEST_P(DistinctSubsequenceParamTest, MR14) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Find the first occurrence of duplicate adjacent characters in s */
    size_t duplicate_pos = string::npos;
    for (size_t i = 0; i < s.size() - 1; ++i) {
        if (s[i] == s[i + 1]) {
            duplicate_pos = i;
            break;
        }
    }

    /* Skip the test if no duplicate adjacent characters are found */
    if (duplicate_pos == string::npos) {
        GTEST_SKIP();
    }

    /* Remove one instance of the duplicated character */
    string follow_s = s.substr(0, duplicate_pos) + s.substr(duplicate_pos + 1);

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    ASSERT_GE(follow_out, source_out);
}

/**
 * Metamorphic relation 15: Permuting characters in string s that do not exist in string t should not change the output.
 */
TEST_P(DistinctSubsequenceParamTest, MR15) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Generate a permutation of characters in s that are not in t */
    string chars_not_in_t;
    for (char sc : s) {
        if (t.find(sc) == string::npos) {
            chars_not_in_t.push_back(sc);
        }
    }

    /* Skip the test if there are no such characters */
    if (chars_not_in_t.empty()) {
        GTEST_SKIP();
    }

    std::random_shuffle(chars_not_in_t.begin(), chars_not_in_t.end());

    /* Generate follow-up input by placing the permuted characters back into s */
    string follow_s(s);
    size_t index_in_perm = 0;
    for (size_t i = 0; i < follow_s.size(); ++i) {
        if (t.find(follow_s[i]) == string::npos) {
            follow_s[i] = chars_not_in_t[index_in_perm++];
        }
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    ASSERT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 16: Repeating string t multiple times within string s should not decrease the output count.
 */
TEST_P(DistinctSubsequenceParamTest, MR16) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip if t is not entirely found in s */
    if (s.find(t) == string::npos) {
        GTEST_SKIP();
    }

    /* Interleave s with t */
    string follow_s = s.substr(0, s.find(t) + t.size()) + t + s.substr(s.find(t) + t.size());

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    ASSERT_GE(follow_out, source_out);
}

/**
 * Metamorphic relation 17: Concatenating a copy of t to the end of t itself should not change the number of distinct subsequences in s.
 */
TEST_P(DistinctSubsequenceParamTest, MR17) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* If t is empty skip this test case */
    if (t.empty()) {
        GTEST_SKIP();
    }

    /* Concatenate t to the end of itself */
    string follow_t = t + t;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(s, follow_t);

    /* Verification */
    ASSERT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 18: Inserting the entire string t at any position within s should not decrease the number of distinct subsequences matching t.
 */
TEST_P(DistinctSubsequenceParamTest, MR18) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip if t is empty or s does not contain t */
    if (t.empty() || s.find(t) == string::npos) {
        GTEST_SKIP();
    }

    /* Insert t at a random position in s */
    size_t insert_pos = rand() % (s.length() + 1);
    string follow_s = s.substr(0, insert_pos) + t + s.substr(insert_pos);

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    ASSERT_GE(follow_out, source_out);
}

/**
 * Metamorphic relation 19: Removing any number of occurrences of a character from s that does not appear in t should not change the output.
 */
TEST_P(DistinctSubsequenceParamTest, MR19) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Create a follow-up input by removing characters not in t from s */
    string follow_s;
    for (char c : s) {
        if (t.find(c) != string::npos) {
            follow_s += c;
        }
    }

    /* Skip test if no characters were removed */
    if (follow_s.size() == s.size()) {
        GTEST_SKIP();
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    ASSERT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 20: Doubling every character in s should at least double the output if t is non-empty.
 */
TEST_P(DistinctSubsequenceParamTest, MR20) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip test if t is empty */
    if (t.empty()) {
        GTEST_SKIP();
    }

    /* Construct follow-up input */
    string follow_s;
    std::for_each(s.begin(), s.end(), [&follow_s](char c) {
        follow_s.push_back(c);
        follow_s.push_back(c);
    });

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    ASSERT_GE(follow_out, 2 * source_out);
}

/**
 * Metamorphic relation 21: If string s is a repetition of string t, then the number of distinct subsequences should match the number of repetitions.
 */
TEST_P(DistinctSubsequenceParamTest, MR21) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip test if s is shorter than t */
    if (s.size() < t.size()) {
        GTEST_SKIP();
    }

    /* Repeat t until it is the same length as s */
    string repeated_t;
    while (repeated_t.size() < s.size()) {
        repeated_t += t;
    }

    /* Truncate the repeated t to be same length as s */
    repeated_t = repeated_t.substr(0, s.size());

    /* Check if s is actually a repetition of t */
    if (s != repeated_t) {
        GTEST_SKIP();
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Compute expected output based on how many times t is repeated in s */
    int expected_out = s.size() / t.size();

    /* Verification */
    ASSERT_EQ(source_out, expected_out);
}

/**
 * Metamorphic relation 22: Replacing a character in t with another non-existing character in t nor s should not change the output.
 */
TEST_P(DistinctSubsequenceParamTest, MR22) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip test if t is empty */
    if (t.empty()) {
        GTEST_SKIP();
    }

    /* Find a character that does not exist in t nor s */
    char replace_with = 'a';
    while (s.find(replace_with) != string::npos || t.find(replace_with) != string::npos) {
        ++replace_with;
    }

    /* Replace first character in t with the new character */
    string follow_t = t;
    follow_t[0] = replace_with;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(s, follow_t);

    /* Verification */
    ASSERT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 23: Shuffle string s randomly, should not change the output if each character in t is present at least as many times in s.
 */
TEST_P(DistinctSubsequenceParamTest, MR23) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Create a map to count occurrences of characters in t */
    std::map<char, int> char_count_in_t;
    for (char c : t) {
        char_count_in_t[c]++;
    }

    /* Check if each character in t is present in s at least as many times  */
    for (auto &[c, count] : char_count_in_t) {
        if (std::count(s.begin(), s.end(), c) < count) {
            GTEST_SKIP();
        }
    }

    /* Shuffle s randomly */
    std::random_shuffle(s.begin(), s.end());

    /* Get source output */
    int source_out = numDistinct(input.s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(s, t);

    /* Verification */
    ASSERT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 24: Removing all occurrences of a specific character from both s and t should not change the result,
 * given that the character appears the same number of times in s and t.
 */
TEST_P(DistinctSubsequenceParamTest, MR24) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Find a character that appears the same number of times in s and t */
    char character_to_remove = '\0';
    for (char c : t) {
        if (std::count(s.begin(), s.end(), c) == std::count(t.begin(), t.end(), c)) {
            character_to_remove = c;
            break;
        }
    }

    /* If no such character exists, skip the test */
    if (character_to_remove == '\0') {
        GTEST_SKIP();
    }

    /* Remove the character from both s and t */
    s.erase(std::remove(s.begin(), s.end(), character_to_remove), s.end());
    t.erase(std::remove(t.begin(), t.end(), character_to_remove), t.end());

    /* Get source output */
    int source_out = numDistinct(input.s, input.t);

    /* Get follow-up output */
    int follow_out = numDistinct(s, t);

    /* Verification */
    ASSERT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 25: If t is non-empty and s starts with character x, appending x to the start of s should increase the number of distinct subsequences.
 */
TEST_P(DistinctSubsequenceParamTest, MR25) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip test if t is empty or if s does not start with a character in t */
    if (t.empty() || t.find(s.front()) == string::npos) {
        GTEST_SKIP();
    }

    /* Append the first character of s to the start */
    string follow_s = s.front() + s;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    ASSERT_GT(follow_out, source_out);
}

/**
 * Metamorphic relation 26: If t is a non-empty substring of s, reversing s should not change the number of distinct subsequences.
 */
TEST_P(DistinctSubsequenceParamTest, MR26) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip test if t is empty or not a substring of s */
    if (t.empty() || s.find(t) == string::npos) {
        GTEST_SKIP();
    }

    /* Reverse the string s */
    std::reverse(s.begin(), s.end());

    /* Get source output */
    int source_out = numDistinct(input.s, input.t);

    /* Get follow-up output */
    int follow_out = numDistinct(s, t);

    /* Verification */
    ASSERT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 27: If a non-empty t is an anagram of s, then numDistinct should return 1.
 */
TEST_P(DistinctSubsequenceParamTest, MR27) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Shuffle t to create its anagram */
    std::random_shuffle(t.begin(), t.end());

    /* Skip test if shuffled t equals s or if t is empty */
    if (t == s || t.empty()) {
        GTEST_SKIP();
    }

    /* Since t is an anagram of s, we should expect only 1 match */
    int expected_out = 1;

    /* Get actual output */
    int actual_out = numDistinct(s, t);

    /* Verification */
    ASSERT_EQ(actual_out, expected_out);
}

/**
 * Metamorphic relation 28: Shuffling the characters of string t should not change the number of distinct subsequences in s.
 */
TEST_P(DistinctSubsequenceParamTest, MR28) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Shuffle string t */
    std::string shuffled_t = t;
    std::random_shuffle(shuffled_t.begin(), shuffled_t.end());

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(s, shuffled_t);

    /* Verification */
    ASSERT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 29: Adding a common prefix to both s and t should not decrease the number of distinct subsequences.
 */
TEST_P(DistinctSubsequenceParamTest, MR29) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Define a common prefix */
    string prefix = "common_prefix_";

    /* Add the common prefix to both s and t */
    string prefixed_s = prefix + s;
    string prefixed_t = prefix + t;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(prefixed_s, prefixed_t);

    /* Verification */
    ASSERT_GE(follow_out, source_out);
}

/**
 * Metamorphic relation 30: Interleaving string s with characters that do not appear in string t should not change the number of distinct subsequences.
 */
TEST_P(DistinctSubsequenceParamTest, MR30) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Find a character not in both s and t */
    vector<char> candidates;
    for (char c = 'a'; c <= 'z'; c++) {
        if (t.find(c) == string::npos && s.find(c) == string::npos) {
            candidates.push_back(c);
        }
    }
    if (candidates.empty()) {
        GTEST_SKIP();
    }

    // Choose one candidate randomly
    char unique_char = candidates[rand() % candidates.size()];

    // Interleave the character into string s
    string interleaved_s;
    for (char c : s) {
        interleaved_s.push_back(c);
        interleaved_s.push_back(unique_char); // inserting unique character
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(interleaved_s, t);

    /* Verification */
    ASSERT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 31: Inverting the case of all characters in s and t should not change the number of distinct subsequences.
 */
TEST_P(DistinctSubsequenceParamTest, MR31) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Invert case for string s */
    string inverted_case_s = s;
    std::transform(s.begin(), s.end(), inverted_case_s.begin(), [](char c) { return ::isupper(c) ? ::tolower(c) : ::toupper(c); });

    /* Invert case for string t */
    string inverted_case_t = t;
    std::transform(t.begin(), t.end(), inverted_case_t.begin(), [](char c) { return ::isupper(c) ? ::tolower(c) : ::toupper(c); });

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(inverted_case_s, inverted_case_t);

    /* Verification */
    ASSERT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 32: If we append any non-empty string w at the end of both s and t, the output should not be less.
 */
TEST_P(DistinctSubsequenceParamTest, MR32) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    string w = "appendix"; // Non-empty string to be appended

    /* Construct follow-up input */
    string follow_s = s + w;
    string follow_t = t + w;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, follow_t);

    /* Verification */
    ASSERT_GE(follow_out, source_out);
}

/**
 * Metamorphic relation 33: If we prepend any non-empty string w to t and the same string or its substring to s, the output should not increase.
 */
TEST_P(DistinctSubsequenceParamTest, MR33) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    string w = "prefix"; // Non-empty string to be prepended

    /* Construct follow-up input */
    string follow_s = w.substr(0, w.size() / 2) + s; // prepend a substring of w to s
    string follow_t = w + t;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, follow_t);

    /* Verification */
    ASSERT_LE(follow_out, source_out);
}

/**
 * Metamorphic relation 34: Reordering the occurrences of characters in s that also exist in t should not change the output.
 */
TEST_P(DistinctSubsequenceParamTest, MR34) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Create a shuffled order of the characters in s which exist in t */
    string subset_in_s_and_t;
    for (char c : s) {
        if (t.find(c) != string::npos) {
            subset_in_s_and_t.push_back(c);
        }
    }

    std::random_shuffle(subset_in_s_and_t.begin(), subset_in_s_and_t.end());

    /* Reorder s by following the shuffled characters */
    string shuffled_s;
    size_t index = 0;
    for (char c : s) {
        if (t.find(c) != string::npos) {
            shuffled_s.push_back(subset_in_s_and_t[index++]); // Use shuffled order for characters present in t
        } else {
            shuffled_s.push_back(c); // Keep characters not present in t as is
        }
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(shuffled_s, t);

    /* Verification */
    ASSERT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 35: Replacing every occurrence of a specific character in s that also exists in t with a string u of that character should not decrease
 * the result.
 */
TEST_P(DistinctSubsequenceParamTest, MR35) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;
    string u = "xx"; // String to replace character with

    // Find the first character that appears in both s and t
    for (char c : t) {
        if (s.find(c) != string::npos) {
            /* Replace every occurrence of c in s with u */
            size_t pos = 0;
            while ((pos = s.find(c, pos)) != string::npos) {
                s.replace(pos, 1, u);
                pos += u.length();
            }
            break;
        }
    }

    /* Get source output */
    int source_out = numDistinct(input.s, input.t);

    /* Get follow-up output */
    int follow_out = numDistinct(s, t);

    /* Verification */
    ASSERT_GE(follow_out, source_out);
}

/**
 * Metamorphic relation 36: If all occurrences of a specific character are removed from s, and that character does not exist in t,
 * the number of distinct subsequences should not change.
 */
TEST_P(DistinctSubsequenceParamTest, MR36) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Find a character that exists in s but not in t and remove all occurrences of it */
    char char_to_remove = '\0'; // Placeholder for the character to be removed
    string follow_s;
    for (char c : s) {
        if (t.find(c) == string::npos) {
            char_to_remove = c;
            break;
        }
    }
    if (char_to_remove) {
        follow_s = s;
        follow_s.erase(std::remove(follow_s.begin(), follow_s.end(), char_to_remove), follow_s.end());
    } else {
        follow_s = s; // Skip if such a character doesn't exist
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output if a character was removed */
    int follow_out = source_out;
    if (char_to_remove) {
        follow_out = numDistinct(follow_s, t);
    }

    /* Verification */
    ASSERT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 37: For all characters in t, increasing their frequency in s should not decrease the number of distinct subsequences.
 */
TEST_P(DistinctSubsequenceParamTest, MR37) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Create a new string s by doubling each character from t that is found in s */
    string follow_s;
    for (char sc : s) {
        follow_s.push_back(sc);
        if (t.find(sc) != string::npos) {
            follow_s.push_back(sc); // Double the character if it's in t
        }
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    ASSERT_GE(follow_out, source_out);
}

/**
 * Metamorphic relation 38: Concatenating s with itself multiple times should exponentially increase the number of distinct subsequences.
 */
TEST_P(DistinctSubsequenceParamTest, MR38) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip test if s is empty */
    if (s.empty()) {
        GTEST_SKIP();
    }

    /* Double s by concatenating it with itself */
    string follow_s = s + s;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification (expect at least the square of source_out due to doubling s) */
    ASSERT_GE(follow_out, source_out * source_out);
}

/**
 * Metamorphic relation 39: If every character in t is at the end of s, adding non-t characters to the start should not change the output.
 */
TEST_P(DistinctSubsequenceParamTest, MR39) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip test if s does not end with t */
    if (s.length() < t.length() || s.substr(s.length() - t.length()) != t) {
        GTEST_SKIP();
    }

    /* Get a string of characters not in t */
    string not_t = "XYZ"; // Assuming 'X', 'Y', and 'Z' are not in t

    /* Add not_t characters to the start of s */
    string follow_s = not_t + s;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    ASSERT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 40: For every character c in t, replacing all occurrences in s with the same number of any other character not in t
 * should result in the same number of distinct subsequences.
 */
TEST_P(DistinctSubsequenceParamTest, MR40) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    // Character not present in t to be used in replacement
    char replacement_char = '1';
    while (t.find(replacement_char) != string::npos) {
        replacement_char++;
    }

    /* Replace all occurrences of each character in t from s with equivalent number of replacement_char */
    string follow_s = s;
    for (char c : t) {
        std::transform(follow_s.begin(), follow_s.end(), follow_s.begin(), [c, replacement_char](char sc) { return sc == c ? replacement_char : sc; });
    }

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    ASSERT_EQ(follow_out, source_out);
}

/**
 * Metamorphic relation 41: If t is non-empty and we concatenate s to itself in reverse, the number of distinct subsequences should increase.
 */
TEST_P(DistinctSubsequenceParamTest, MR41) {
    /* Get source input */
    DistinctSubsequenceInput input = GetParam();
    string s = input.s, t = input.t;

    /* Skip test if t is empty */
    if (t.empty()) {
        GTEST_SKIP();
    }

    /* Construct follow-up input by concatenating s to its reverse */
    string reversed_s(s.rbegin(), s.rend());
    string follow_s = s + reversed_s;

    /* Get source output */
    int source_out = numDistinct(s, t);

    /* Get follow-up output */
    int follow_out = numDistinct(follow_s, t);

    /* Verification */
    ASSERT_GT(follow_out, source_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, DistinctSubsequenceParamTest, testing::ValuesIn(gen_tcs_randomly()));