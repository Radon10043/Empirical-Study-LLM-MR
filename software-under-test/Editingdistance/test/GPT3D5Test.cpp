#include <algorithm>
#include <gtest/gtest.h>
#include <random>
#include <string>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class EditingdistanceParamTest : public ::testing::TestWithParam<EditingdistanceInput> {};

// Metamorphic Relation 2: Remove a character from `str1`, the output should be the same or larger.
TEST_P(EditingdistanceParamTest, MR2) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    if (str1.empty())
        return;
    string follow_str1 = str1.substr(0, str1.size() - 1);

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

// Metamorphic Relation 3: Replace a character in `str1` with a different character, the output should be the same or larger.
TEST_P(EditingdistanceParamTest, MR3) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    if (str1.empty())
        return;
    string follow_str1 = str1;
    follow_str1[0] = 'x'; // replace the first character with 'x'

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

// Metamorphic Relation 4: Swap two adjacent characters in `str1`, the output should be the same or larger.
TEST_P(EditingdistanceParamTest, MR4) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    if (str1.size() < 2)
        return;
    string follow_str1 = str1;
    swap(follow_str1[0], follow_str1[1]); // swap the first two characters

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

// Metamorphic Relation 5: Reverse `str1`, the output should be the same or larger.
TEST_P(EditingdistanceParamTest, MR5) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    string follow_str1 = str1;
    reverse(follow_str1.begin(), follow_str1.end()); // reverse the string

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

// Metamorphic Relation 6: Repeat a character in `str1`, the output should be the same or larger.
TEST_P(EditingdistanceParamTest, MR6) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    if (str1.empty())
        return;
    string follow_str1 = str1 + str1[0]; // repeat the first character

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

// Metamorphic Relation 7: Concatenate 'str1' with a substring of 'str2', the output should be equal to or less than the source output.
TEST_P(EditingdistanceParamTest, MR7) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    for (int i = 1; i <= str2.size(); i++) {
        string follow_str1 = str1 + str2.substr(0, i);

        /* Get follow-up output */
        int follow_out = edit_dist(follow_str1, str2);

        /* Verification */
        EXPECT_LE(follow_out, source_out);
    }
}

// Metamorphic Relation 8: Remove a substring from 'str2', the output should be equal to or less than the source output.
TEST_P(EditingdistanceParamTest, MR8) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    for (int i = 0; i <= str2.size(); i++) {
        string follow_str2 = str2;
        follow_str2.erase(0, i);

        /* Get follow-up output */
        int follow_out = edit_dist(str1, follow_str2);

        /* Verification */
        EXPECT_LE(follow_out, source_out);
    }
}

// Metamorphic Relation 9: If `str1` and `str2` are already equal, then the edit distance should be 0.
TEST_P(EditingdistanceParamTest, MR9) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    if (str1 == str2) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), 0);
    }
}

// Metamorphic Relation 10: If `str1` is an empty string, then the edit distance should be the same as the length of `str2`.
TEST_P(EditingdistanceParamTest, MR10) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    if (str1.empty()) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), str2.length());
    }
}

// Metamorphic Relation 11: If both `str1` and `str2` are empty strings, the edit distance should be 0.
TEST_P(EditingdistanceParamTest, MR11) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    if (str1.empty() && str2.empty()) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), 0);
    }
}

// Metamorphic Relation 12: If the lengths of `str1` and `str2` differ by 'k', then the edit distance should be at least 'k'.
TEST_P(EditingdistanceParamTest, MR12) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    int diff = abs(static_cast<int>(str1.length()) - static_cast<int>(str2.length()));

    /* Verification */
    EXPECT_LE(edit_dist(str1, str2), diff);
}

// Metamorphic Relation 13: If `str1` is a prefix of `str2`, the edit distance should be equal to the length of `str2` minus the length of `str1`.
TEST_P(EditingdistanceParamTest, MR13) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    if (str2.find(str1) == 0) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), str2.length() - str1.length());
    }
}

// Metamorphic Relation 14: If `str1` and `str2` are permutations of each other, the edit distance should be the same.
TEST_P(EditingdistanceParamTest, MR14) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());

    if (str1 == str2) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), edit_dist(str2, str1));
    }
}

// Metamorphic Relation 15: If `str1` and `str2` are mirror images of each other (e.g., "abc" and "cba"), the edit distance should be the same.
TEST_P(EditingdistanceParamTest, MR15) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    string reverse_str1 = str1;
    reverse(reverse_str1.begin(), reverse_str1.end());

    if (reverse_str1 == str2) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), edit_dist(str2, str1));
    }
}

// Metamorphic Relation 16: If `str2` is a substring of `str1`, the edit distance should be equal to the difference in lengths between `str1` and `str2`.
TEST_P(EditingdistanceParamTest, MR16) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    if (str1.find(str2) != string::npos) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), str1.size() - str2.size());
    }
}

// Metamorphic Relation 17: If `str1` and `str2` have a common prefix, the edit distance should be at least the difference in lengths between `str1` and the
// common prefix.
TEST_P(EditingdistanceParamTest, MR17) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    int prefix_len = 0;
    for (int i = 0; i < min(str1.size(), str2.size()); i++) {
        if (str1[i] != str2[i]) {
            prefix_len = i;
            break;
        }
    }

    /* Verification */
    EXPECT_LE(edit_dist(str1, str2), abs(static_cast<int>(str1.length()) - prefix_len));
}

// Metamorphic Relation 18: If `str1` and `str2` have a common suffix, the edit distance should be at least the difference in lengths between `str1` and the
// common suffix.
TEST_P(EditingdistanceParamTest, MR18) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    int suffix_len = 0;
    for (int i = 0; i < min(str1.size(), str2.size()); i++) {
        if (str1[str1.size() - 1 - i] != str2[str2.size() - 1 - i]) {
            suffix_len = i;
            break;
        }
    }

    /* Verification */
    EXPECT_LE(edit_dist(str1, str2), abs(static_cast<int>(str1.length()) - suffix_len));
}

// Metamorphic Relation 19: If `str1` and `str2` have no common characters, then the edit distance should be equal to the sum of their lengths.
TEST_P(EditingdistanceParamTest, MR19) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    if (str1.find_first_of(str2) == string::npos) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), str1.length() + str2.length());
    }
}

// Metamorphic Relation 20: If `str1` is a substring of `str2`, the edit distance should be equal to the length of `str2` minus the length of `str1`.
TEST_P(EditingdistanceParamTest, MR20) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    if (str2.find(str1) != string::npos) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), str2.length() - str1.length());
    }
}

// Metamorphic Relation 21: If `str1` and `str2` are palindromes of each other, then the edit distance should be the same.
TEST_P(EditingdistanceParamTest, MR21) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    string rev_str1 = str1;
    reverse(rev_str1.begin(), rev_str1.end());

    if (rev_str1 == str2) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), edit_dist(str2, str1));
    }
}

// Metamorphic Relation 22: If `str1` is a rotation of `str2`, the edit distance should be the same.
TEST_P(EditingdistanceParamTest, MR22) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    string concat_str1 = str1 + str1;

    if (concat_str1.find(str2) != string::npos) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), edit_dist(str2, str1));
    }
}

// Metamorphic Relation 23: If `str1` is a repetition of a substring, the edit distance should be the same as the difference in lengths between `str1` and the
// repeated substring.
TEST_P(EditingdistanceParamTest, MR23) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    int len = str1.length();
    int sub_len = 1;

    while (sub_len <= len / 2) {
        if (len % sub_len == 0) {
            bool is_repeated = true;
            for (int i = 0; i < len; i++) {
                if (str1[i] != str1[i % sub_len]) {
                    is_repeated = false;
                    break;
                }
            }

            if (is_repeated) {
                /* Verification */
                EXPECT_EQ(edit_dist(str1, str2), len - sub_len);
                return;
            }
        }
        sub_len++;
    }
}

// Metamorphic Relation 24 : If sing two characters in `str1` results in `str2`, the edit distance should be 2.
TEST_P(EditingdistanceParamTest, MR24) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    if (str1.length() == str2.length()) {
        for (size_t i = 0; i < str1.length() - 1; i++) {
            for (size_t j = i + 1; j < str2.length(); j++) {
                // string sed_str1 = str1;
                // // swap(sed_str1[i], sed_str1[j]);
                // if (sed_str1 == str2) {
                /* Verification */
                EXPECT_EQ(edit_dist(str1, str2), 2);
                return;
            }
        }
    }
}

// Metamorphic Relation 25: If a character in `str1` is repeated more times than in `str2`, the edit distance should be at least the difference in repetition
// counts for that character.
TEST_P(EditingdistanceParamTest, MR25) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    map<char, int> char_count_1, char_count_2;

    for (char c : str1) {
        char_count_1[c]++;
    }

    for (char c : str2) {
        char_count_2[c]++;
    }

    for (auto it : char_count_1) {
        if (char_count_2.find(it.first) != char_count_2.end()) {
            /* Verification */
            EXPECT_LE(edit_dist(str1, str2), abs(char_count_1[it.first] - char_count_2[it.first]));
        }
    }
}

// Metamorphic Relation 26: If `str2` is obtained by shuffling the characters of `str1`, the edit distance should be 0.
TEST_P(EditingdistanceParamTest, MR26) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());

    if (str1.length() == str2.length() && str1 == str2) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), 0);
    }
}

// Metamorphic Relation 27: If all characters in `str1` are the same, the edit distance should be equal to the absolute difference in the counts of those
// characters in `str1` and `str2`.
TEST_P(EditingdistanceParamTest, MR27) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    if (str1.find_first_not_of(str1[0]) == string::npos) {
        int count1 = str1.size();
        int count2 = count(str2.begin(), str2.end(), str1[0]);

        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), abs(count1 - count2));
    }
}

// Metamorphic Relation 28 : If `str2` is a palindrome of `str1`ended with the same character, the edit distance should be 1.
TEST_P(EditingdistanceParamTest, MR28) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    string rev_str1 = str1;
    reverse(rev_str1.begin(), rev_str1.end());
    if (rev_str1 + str1.back() == str2) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), 1);
    }
}

// Metamorphic Relation 29: If `str1` and `str2` are the same, the edit distance should be 0.
TEST_P(EditingdistanceParamTest, MR29) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    if (str1 == str2) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), 0);
    }
}

// Metamorphic Relation 30: If `str1` and `str2` are of different lengths, the edit distance should be at least the absolute difference in lengths between
// `str1` and `str2`.
TEST_P(EditingdistanceParamTest, MR30) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Verification */
    EXPECT_GE(edit_dist(str1, str2), abs(static_cast<int>(str1.length()) - static_cast<int>(str2.length())));
}

// Metamorphic Relation 31: If both strings `str1` and `str2` are empty, the edit distance should also be 0.
TEST_P(EditingdistanceParamTest, MR31) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    if (str1.empty() && str2.empty()) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), 0);
    }
}

// Metamorphic Relation 32: If `str1` and `str2` contain the same set of characters with different frequencies, the edit distance should be equal to the sum of
// absolute differences in frequencies for each character.
TEST_P(EditingdistanceParamTest, MR32) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    map<char, int> freq1, freq2;

    // Compute character frequency for str1
    for (char c : str1) {
        freq1[c]++;
    }

    // Compute character frequency for str2
    for (char c : str2) {
        freq2[c]++;
    }

    int total_edit_distance = 0;

    // Calculate the sum of absolute differences in frequencies for each character
    for (auto const &[character, frequency] : freq1) {
        total_edit_distance += abs(frequency - freq2[character]);
    }

    /* Verification */
    EXPECT_EQ(edit_dist(str1, str2), total_edit_distance);
}

// Metamorphic Relation 33: If `str2` is obtained by adding extra characters to `str1`, the edit distance should be equal to the difference in lengths between
// `str2` and `str1`.
TEST_P(EditingdistanceParamTest, MR33) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    if (str2.find(str1) == 0 && str2.length() > str1.length()) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), str2.length() - str1.length());
    }
}

// Metamorphic Relation 34: If `str2` is obtained by removing characters from `str1`, the edit distance should also be equal to the difference in lengths
// between `str1` and `str2`.
TEST_P(EditingdistanceParamTest, MR34) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    if (str1.find(str2) == 0 && str2.length() < str1.length()) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), str1.length() - str2.length());
    }
}

// Metamorphic Relation 35: If `str2` is a substring of `str1`, the edit distance should be equal to the length of `str1` minus the length of `str2`.
TEST_P(EditingdistanceParamTest, MR35) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    if (str1.find(str2) != string::npos) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), str1.length() - str2.length());
    }
}

// Metamorphic Relation 36: If the characters in `str1` are in reverse order to those in `str2`, the edit distance should be equal to the length of `str1`.
TEST_P(EditingdistanceParamTest, MR36) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    reverse(str1.begin(), str1.end());

    if (str1 == str2) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), str1.length());
    }
}

// Metamorphic Relation 37: If all characters in `str1` are repeated the same number of times as in `str2`, the edit distance should be 0.
TEST_P(EditingdistanceParamTest, MR37) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    map<char, int> charCount1, charCount2;

    for (char c : str1) {
        charCount1[c]++;
    }

    for (char c : str2) {
        charCount2[c]++;
    }

    if (charCount1 == charCount2) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), 0);
    }
}

// Metamorphic Relation 38: If the characters in `str1` and `str2` are sorted in the same order, the edit distance should be the same.
TEST_P(EditingdistanceParamTest, MR38) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());

    if (str1 == str2) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), edit_dist(str2, str1));
    }
}

// Metamorphic Relation 39: If both `str1` and `str2` are non-empty strings and contain the same set of characters, then the edit distance should be equal to
// the absolute difference in their lengths.
TEST_P(EditingdistanceParamTest, MR39) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    set<char> chars1(str1.begin(), str1.end());
    set<char> chars2(str2.begin(), str2.end());

    if (!str1.empty() && !str2.empty() && chars1 == chars2) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), abs(static_cast<int>(str1.length()) - static_cast<int>(str2.length())));
    }
}

// Metamorphic Relation 40: If both `str1` and `str2` are non-empty strings and one is the reverse of the other, then the edit distance should be equal to the
// length of `str1`.
TEST_P(EditingdistanceParamTest, MR40) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    if (!str1.empty() && !str2.empty() && string(str1.rbegin(), str1.rend()) == str2) {
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), str1.length());
    }
}

// Metamorphic Relation 41: If `str1` and `str2` are the same length and the characters are at the same positions but in different orders, the edit distance
// should be equal to the number of inversions needed to sort `str1` into `str2`.
TEST_P(EditingdistanceParamTest, MR41) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    if (str1.length() == str2.length()) {
        int inversions = 0;
        for (size_t i = 0; i < str1.length(); i++) {
            for (size_t j = i + 1; j < str2.length(); j++) {
                if (str1[i] > str1[j] && str2[i] < str2[j]) {
                    inversions++;
                }
            }
        }
        /* Verification */
        EXPECT_EQ(edit_dist(str1, str2), inversions);
    }
}

INSTANTIATE_TEST_CASE_P(TrueReturn, EditingdistanceParamTest, testing::ValuesIn(gen_tcs_randomly()));