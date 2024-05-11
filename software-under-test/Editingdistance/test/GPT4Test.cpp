#include <algorithm>
#include <gtest/gtest.h>
#include <random>
#include <string>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class EditingdistanceParamTest : public ::testing::TestWithParam<EditingdistanceInput> {};

/**
 * @brief Metamorphic relation 2: Reversing both strings should not change the edit distance.
 *
 */
TEST_P(EditingdistanceParamTest, MR2) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    string reverse_str1(str1.rbegin(), str1.rend());
    string reverse_str2(str2.rbegin(), str2.rend());

    /* Get follow-up output */
    int follow_out = edit_dist(reverse_str1, reverse_str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 3: If two characters in str1 are swapped, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR3) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    if (str1.length() > 1) {
        string follow_str1 = str1;
        std::swap(follow_str1[0], follow_str1[1]);

        /* Get follow-up output */
        int follow_out = edit_dist(follow_str1, str2);

        /* Verification */
        EXPECT_GE(follow_out, source_out);
    }
}
/**
 * @brief Metamorphic relation 4: Adding the same suffix to both str1 and str2 should not change the edit distance.
 *
 */
TEST_P(EditingdistanceParamTest, MR4) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    string suffix = "suffix"; // Example suffix; Could also be generated.
    string follow_str1 = str1 + suffix;
    string follow_str2 = str2 + suffix;

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 5: Prefixing both strings with the same sequence of characters does not change the edit distance.
 *
 */
TEST_P(EditingdistanceParamTest, MR5) { // Fixed, the length of prefix is shortened
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    string prefix = "pr"; // Example prefix; Could also be generated.
    string follow_str1 = prefix + str1;
    string follow_str2 = prefix + str2;

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 6: Deleting the same character from both strings should not change the edit distance.
 *
 */
TEST_P(EditingdistanceParamTest, MR6) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Ensure there is a common character to delete */
    char common_char = '\0';
    for (char c = 'a'; c <= 'z'; ++c) {
        if (str1.find(c) != string::npos && str2.find(c) != string::npos) {
            common_char = c;
            break;
        }
    }
    if (common_char == '\0') return; // No common character to delete

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    str1.erase(remove(str1.begin(), str1.end(), common_char), str1.end());
    str2.erase(remove(str2.begin(), str2.end(), common_char), str2.end());

    /* Get follow-up output */
    int follow_out = edit_dist(str1, str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 7: If str1 is a non-trivial suffix of str2, the edit distance should be the difference in length.
 *
 */
TEST_P(EditingdistanceParamTest, MR7) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Make str1 a suffix of str2 */
    if (str1.length() < str2.length()) {
        str1 = str2.substr(str2.length() - str1.length());
    } else {
        // Skip the MR if str1 is not shorter
        return;
    }

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Expected follow-up output */
    int expected_out = str2.length() - str1.length();

    /* Verification */
    EXPECT_EQ(source_out, expected_out);
}
/**
 * @brief Metamorphic relation 8: Doubling str1 should double the edit distance when str2 is empty (and vice versa).
 *
 */
TEST_P(EditingdistanceParamTest, MR8) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1;
    string str2 = ""; // Make str2 empty

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    string follow_str1 = str1 + str1; // Double str1

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str2);

    /* Verification */
    EXPECT_EQ(follow_out, 2 * source_out);
}
/**
 * @brief Metamorphic relation 9: Removing a common prefix from both strings should not change the edit distance.
 *
 */
TEST_P(EditingdistanceParamTest, MR9) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Determine the length of the common prefix */
    size_t common_prefix_length = 0;
    while (common_prefix_length < str1.length() && common_prefix_length < str2.length() &&
           str1[common_prefix_length] == str2[common_prefix_length]) {
        ++common_prefix_length;
    }

    /* If a common prefix exists, remove it */
    if (common_prefix_length > 0) {
        str1 = str1.substr(common_prefix_length);
        str2 = str2.substr(common_prefix_length);
    } else {
        // If there is no common prefix, this MR does not apply
        return;
    }

    /* Get follow-up output */
    int follow_out = edit_dist(str1, str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 10: Appending the reverse of str2 to str1 increases the edit distance by the length of str2.
 *
 */
TEST_P(EditingdistanceParamTest, MR10) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    string reverse_str2(str2.rbegin(), str2.rend());
    string follow_str1 = str1 + reverse_str2;

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out + str2.length());
}
/**
 * @brief Metamorphic relation 11: Concatenating a third string to both str1 and str2 should increase the edit distance by at most the length of that third string.
 *
 */
TEST_P(EditingdistanceParamTest, MR11) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;
    string str3 = "thirdStr";  // The third string to concatenate

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    string follow_str1 = str1 + str3;
    string follow_str2 = str2 + str3;

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_LE(follow_out, source_out + str3.length());
}
/**
 * @brief Metamorphic relation 12: Exchanging str1 with str2 should not change the edit distance.
 *
 */
TEST_P(EditingdistanceParamTest, MR12) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    // Exchanging str1 with str2, so no need for additional follow-up input construction

    /* Get follow-up output */
    int follow_out = edit_dist(str2, str1);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 13: Inserting the same character at the same position in both str1 and str2 should not change the edit distance.
 *
 */
TEST_P(EditingdistanceParamTest, MR13) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Prepare a character to insert */
    char insert_char = 'z';

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    // Choose a position to insert; for simplicity, we use one before the last character if possible
    size_t position = (str1.length() > 1) ? str1.length() - 1 : 0;
    str1.insert(str1.begin() + position, insert_char);
    str2.insert(str2.begin() + position, insert_char);

    /* Get follow-up output */
    int follow_out = edit_dist(str1, str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 14: Increasing all characters in both str1 and str2 by one should not change the edit distance.
 *
 */
TEST_P(EditingdistanceParamTest, MR14) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    string follow_str1 = str1;
    string follow_str2 = str2;
    for (char &c : follow_str1) {
        if (c < 'z') c += 1;
    }
    for (char &c : follow_str2) {
        if (c < 'z') c += 1;
    }

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 15: If str1 contains str2 as a substring, the edit distance should be equal to the difference in lengths of str1 and str2.
 *
 */
TEST_P(EditingdistanceParamTest, MR15) {    // Fixed, the length of suffix is shortened
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Make sure str2 is a substring of str1 */
    size_t pos = str1.find(str2);
    if (pos == string::npos) {
        // If str2 is not a substring of str1, form it to be one
        str1 = str2 + "XX";
        pos = str2.length();
    }

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Expected follow-up output */
    int dist = str1.length() - str2.length();

    /* Verification */
    EXPECT_EQ(source_out, dist);
}
/**
 * @brief Metamorphic relation 16: Inserting a character in str1 that already exists at the same position in str2 should not increase the edit distance.
 *
 */
TEST_P(EditingdistanceParamTest, MR16) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Check for a position where the characters in str1 and str2 are different to insert a character */
    size_t position = 0;
    for (; position < std::min(str1.length(), str2.length()); ++position) {
        if (str1[position] != str2[position]) {
            break;
        }
    }

    /* If no suitable position is found, return as this metamorphic property cannot be applied */
    if (position == std::min(str1.length(), str2.length())) return;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input by choosing a character from str2 to insert into str1 */
    string follow_str1 = str1;
    if (position < str2.length()) {
        follow_str1.insert(position, 1, str2[position]);
    }
    else {
        return; // If position exceeds str2 length, we cannot apply this relation
    }

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str2);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 17: Swapping non-adjacent characters in str1 should not decrease the edit distance.
 *
 */
TEST_P(EditingdistanceParamTest, MR17) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Ensure that str1 has at least two non-adjacent characters to swap */
    if (str1.length() < 3) return;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input by swapping non-adjacent characters */
    string follow_str1 = str1;
    char temp = follow_str1[0];
    follow_str1[0] = follow_str1[2];
    follow_str1[2] = temp;

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 18: Swapping str1 with any permutation of str2 should yield the same edit distance.
 *
 */
TEST_P(EditingdistanceParamTest, MR18) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input by permuting str2 */
    string follow_str2 = str2;
    std::next_permutation(follow_str2.begin(), follow_str2.end());

    /* Get follow-up output */
    int follow_out = edit_dist(str1, follow_str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 19: If str2 is non-empty, removing the first character from str2 should increase the edit distance by one, unless that character matches the first character in str1.
 *
 */
TEST_P(EditingdistanceParamTest, MR19) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Check if str2 is non-empty */
    if (str2.empty()) return;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input by removing the first character from str2 */
    string follow_str2 = str2.substr(1);

    /* Get follow-up output */
    int follow_out = edit_dist(str1, follow_str2);

    /* Verification: If the first character of str1 is not the same as the removed character, expect an increase by one. */
    int expected_increase = (str1[0] == str2[0]) ? 0 : 1;
    EXPECT_EQ(follow_out, source_out + expected_increase);
}
/**
 * @brief Metamorphic relation 20: Concatenating str1 with str2 should not increase the edit distance between str1 and str2.
 *
 */
TEST_P(EditingdistanceParamTest, MR20) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input by concatenating str1 with str2 */
    string follow_str1 = str1 + str2;

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str2);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 21: Replacing a character in str1 with the same character should not change the edit distance.
 *
 */
TEST_P(EditingdistanceParamTest, MR21) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Ensure str1 has at least one character */
    if (str1.empty()) return;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input by replacing a character in str1 with the same character */
    // For simplicity, let's replace the first character
    string follow_str1 = str1;
    follow_str1[0] = str1[0];

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 22: Given two strings with a known edit distance, adding the same character to the end of each should increase the distance by at most one.
 *
 */
TEST_P(EditingdistanceParamTest, MR22) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input by appending the same character to both strings */
    char c = 'x';  // Example character
    string follow_str1 = str1 + c;
    string follow_str2 = str2 + c;

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_LE(follow_out, source_out + 1);
}
/**
 * @brief Metamorphic relation 23: If str1 is an anagram of str2, then the edit distance should be less than or equal to the length of the strings.
 *
 */
TEST_P(EditingdistanceParamTest, MR23) {    // FIxed
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1;
    string str2 = input.str2;

    // Make str1 an anagram of str2 by reordering its characters
    std::random_shuffle(str1.begin(), str1.end());

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Verification */
    EXPECT_LE(source_out, str1.length());
}
/**
 * @brief Metamorphic relation 24: Clearing one of the strings should result in the edit distance being equal to the length of the other string.
 *
 */
TEST_P(EditingdistanceParamTest, MR24) {    // Fixed
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1;
    string str2 = input.str2;

    /* Clearing str1 to make the follow-up input */
    string follow_str1 = "";
    string follow_str2 = str2;

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_EQ(follow_out, follow_str2.length());
}
/**
 * @brief Metamorphic relation 25: Changing a character in str1 to match the corresponding character in str2 should decrease the edit distance by one, if they were different.
 *
 */
TEST_P(EditingdistanceParamTest, MR25) {    // Fixed
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1;
    string str2 = input.str2;

    /* Find the first position where characters differ */
    size_t idx;
    for (idx = 0; idx < str1.size() && idx < str2.size(); ++idx) {
        if (str1[idx] != str2[idx]) {
            break;
        }
    }

    /* If all characters in the compared length are the same or we've reached the end of one string, this relation doesn't apply */
    if (idx == str1.size() || idx == str2.size()) return;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input by making the differing characters the same */
    string follow_str1 = str1;
    follow_str1[idx] = str2[idx];

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out - 1);
}
/**
 * @brief Metamorphic relation 26: Swapping two different characters in str1 for two matching characters already in str2 at the same positions should decrease the edit distance by two when they were both mismatches.
 *
 */
TEST_P(EditingdistanceParamTest, MR26) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Identify positions where characters do not match */
    size_t mismatch_index1 = string::npos;
    size_t mismatch_index2 = string::npos;
    for (size_t i = 0; i < str1.length() && i < str2.length(); ++i) {
        if (str1[i] != str2[i]) {
            if (mismatch_index1 == string::npos) {
                mismatch_index1 = i;
            } else {
                mismatch_index2 = i;
                break;
            }
        }
    }

    /* Check if at least two mismatches are found */
    if (mismatch_index1 == string::npos || mismatch_index2 == string::npos) return;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input by resolving the mismatches */
    string follow_str1 = str1;
    follow_str1[mismatch_index1] = str2[mismatch_index1];
    follow_str1[mismatch_index2] = str2[mismatch_index2];

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str2);

    /* Verification */
    EXPECT_LE(follow_out, source_out - 2);
}
/**
 * @brief Metamorphic relation 27: If a character from str1 is moved to a different position, the edit distance should not decrease.
 *
 */
TEST_P(EditingdistanceParamTest, MR27) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Ensure str1 is long enough to move a character */
    if (str1.length() < 2) return;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input by moving a character within str1 */
    // For example, move the first character to the end
    string follow_str1 = str1.substr(1) + str1[0];

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 28: If str2 is a substring within str1, the edit distance is the difference in their lengths.
 *
 */
TEST_P(EditingdistanceParamTest, MR28) {    // Fixed, the length of prefix is shortened
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Enforce that str2 is a strict substring of str1 */
    if (str1.find(str2) == string::npos) {
        str1 = "pr" + str2 + "suffix";
    }

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Expected distance */
    int expected_dist = str1.length() - str2.length();

    /* Verification */
    EXPECT_EQ(source_out, expected_dist);
}
/**
 * @brief Metamorphic relation 29: The edit distance between any string and itself must be zero.
 *
 */
TEST_P(EditingdistanceParamTest, MR29) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1;

    /* Get source output */
    int source_out = edit_dist(str1, str1);

    /* Verification */
    EXPECT_EQ(source_out, 0);
}
/**
 * @brief Metamorphic relation 30: The edit distance between str1 and a concatenation of str2 and an arbitrary string str3 should be at least as large as the edit distance between str1 and str2.
 *
 */
TEST_P(EditingdistanceParamTest, MR30) {    // Fixed, the length of str3 is shortened
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2, str3 = "xx";

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input by appending str3 to str2 */
    string follow_str2 = str2 + str3;

    /* Get follow-up output */
    int follow_out = edit_dist(str1, follow_str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 31: If str1 contains consecutive duplicate characters and str2 does not, removing the duplicates from str1 should not increase the edit distance.
 *
 */
TEST_P(EditingdistanceParamTest, MR31) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input by removing consecutive duplicates from str1 */
    string follow_str1;
    std::unique_copy(str1.begin(), str1.end(), std::back_inserter(follow_str1), 
                     [](char a, char b) { return a == b; });

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str2);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 32: If str1 is empty and str2 consists of the same character repeated, the edit distance should be equal to the length of str2.
 *
 */
TEST_P(EditingdistanceParamTest, MR32) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = ""; // Empty string
    string str2 = string(10, 'a'); // String of 10 'a's

    /* Get follow-up output */
    int follow_out = edit_dist(str1, str2);

    /* Verification */
    EXPECT_EQ(follow_out, str2.length());
}
/**
 * @brief Metamorphic relation 33: If a character is inserted at a certain position in str1 and the same character is removed from the same position in str2, the edit distance should remain unchanged.
 *
 */
TEST_P(EditingdistanceParamTest, MR33) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Ensure that str2 is long enough for removal */
    if (str2.empty()) return;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input by modifying str1 and str2 as per the relation */
    // For simplicity, insert at the beginning of str1 and remove from the beginning of str2
    char char_to_insert_and_remove = 'x';
    string follow_str1 = char_to_insert_and_remove + str1;
    string follow_str2 = str2.substr(1);

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 34: Interchanging the positions of non-matching pairs of characters between str1 and str2 should not change the edit distance.
 *
 */
TEST_P(EditingdistanceParamTest, MR34) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Find mismatching character pairs */
    size_t pos1 = string::npos;
    size_t pos2 = string::npos;
    for (size_t i = 0; i < str1.length() && i < str2.length(); ++i) {
        if (str1[i] != str2[i]) {
            if (pos1 == string::npos) {
                pos1 = i;
            } else {
                pos2 = i;
                break;
            }
        }
    }

    /* Check if at least two non-matching positions are found */
    if (pos1 == string::npos || pos2 == string::npos) return;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input by exchanging the characters at pos1 and pos2 in both strings */
    string follow_str1 = str1;
    string follow_str2 = str2;
    std::swap(follow_str1[pos1], follow_str2[pos1]);
    std::swap(follow_str1[pos2], follow_str2[pos2]);

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 35: The edit distance between two distinct single-character strings should be one.
 *
 */
TEST_P(EditingdistanceParamTest, MR35) {
    /* Get source input */
    string str1 = "a";
    string str2 = "b";

    /* Get follow-up output */
    int follow_out = edit_dist(str1, str2);

    /* Verification */
    EXPECT_EQ(follow_out, 1);
}
/**
 * @brief Metamorphic relation 36: Inserting an arbitrary character at the beginning of str1 should never decrease the edit distance.
 *
 */
TEST_P(EditingdistanceParamTest, MR36) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input by inserting an arbitrary character at the beginning of str1 */
    char char_to_insert = 'z';
    string follow_str1 = char_to_insert + str1;

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 37: The edit distance between two strings should be the same regardless of case sensitivity, assuming the edit distance implementation is case-sensitive.
 *
 */
TEST_P(EditingdistanceParamTest, MR37) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Convert str1 and str2 to uppercase */
    for (char &c : str1) c = toupper(c);
    for (char &c : str2) c = toupper(c);

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Convert str1 and str2 to lowercase */
    for (char &c : str1) c = tolower(c);
    for (char &c : str2) c = tolower(c);

    /* Get follow-up output */
    int follow_out = edit_dist(str1, str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 38: Inserting a sequence of characters into str1 that appears in str2 at the respective position should not increase the edit distance.
 *
 */
TEST_P(EditingdistanceParamTest, MR38) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Identify insertion position */
    size_t insert_pos = 1; // For example, after the first character
    
    /* Ensure the insertion position is valid */
    if (insert_pos >= str2.size()) return;

    /* Get a sequence from str2 */
    string sequence = str2.substr(0, insert_pos);

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input by inserting sequence into str1 at insert_pos */
    string follow_str1 = str1.substr(0, insert_pos) + sequence + str1.substr(insert_pos);

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str2);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 39: Replace a single character in str2 with an arbitrary different character. If str1 is not the same as str2, this should not decrease the edit distance.
 *
 */
TEST_P(EditingdistanceParamTest, MR39) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);
    
    /* Ensure that str2 can be altered */
    if (str2.empty()) return;

    /* Construct follow-up input by replacing a character in str2 */
    str2[0] = str2[0] == 'z' ? 'y' : 'z'; // Swap the first character for a different character

    /* Get follow-up output */
    int follow_out = edit_dist(str1, str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 40: If we concatenate str2 onto itself to form str2str2, the edit distance between str1 and this new string should be at least as large as the edit distance between str1 and str2.
 *
 */
TEST_P(EditingdistanceParamTest, MR40) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input by concatenating str2 on itself */
    string follow_str2 = str2 + str2;

    /* Get follow-up output */
    int follow_out = edit_dist(str1, follow_str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 41: Modifying both str1 and str2 by the same rule that doesn't change their existing relative characters (like Caesar cipher) should keep the edit distance unchanged.
 *
 */
TEST_P(EditingdistanceParamTest, MR41) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Apply a simple Caesar cipher shift by 1 for a demonstration. */
    auto shift_char = [](char c) -> char {
        if (std::isalpha(c)) {
            char base = std::islower(c) ? 'a' : 'A';
            return (c - base + 1) % 26 + base;
        }
        return c;
    };

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    string follow_str1(str1.size(), ' ');
    string follow_str2(str2.size(), ' ');
    std::transform(str1.begin(), str1.end(), follow_str1.begin(), shift_char);
    std::transform(str2.begin(), str2.end(), follow_str2.begin(), shift_char);

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 42: Incrementing all char codes in str2 should not change the edit distance if we also increment all char codes in str1 by the same amount.
 *
 */
TEST_P(EditingdistanceParamTest, MR42) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input by incrementing char codes */
    string follow_str1(str1.size(), ' '), follow_str2(str2.size(), ' ');
    std::transform(str1.begin(), str1.end(), follow_str1.begin(), [](char c) { return c + 1; });
    std::transform(str2.begin(), str2.end(), follow_str2.begin(), [](char c) { return c + 1; });

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 43: If str1 is a prefix of str2, the edit distance should be the difference between their lengths.
 *
 */
TEST_P(EditingdistanceParamTest, MR43) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = "prefix", str2 = "prefixsuffix";

    /* Expected edit distance is the length difference between str2 and str1 */
    int expected_distance = str2.length() - str1.length();

    /* Get follow-up output */
    int follow_out = edit_dist(str1, str2);

    /* Verification */
    EXPECT_EQ(follow_out, expected_distance);
}
/**
 * @brief Metamorphic relation 44: Swapping the first half and the second half of str1 should not decrease the edit distance when neither of the halves is a substring of str2.
 *
 */
TEST_P(EditingdistanceParamTest, MR44) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Ensure str1 is long enough and its parts are not substrings of str2 */
    if (str1.size() < 4 || str2.find(str1.substr(0, str1.size() / 2)) != string::npos ||
        str2.find(str1.substr(str1.size() / 2)) != string::npos) {
        return;
    }

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    string follow_str1 = str1.substr(str1.size() / 2) + str1.substr(0, str1.size() / 2);

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}
/**
 * @brief Metamorphic relation 45: If str2 is formed by inserting arbitrary text into str1, then the edit distance should not exceed the length of the inserted text.
 *
 */
TEST_P(EditingdistanceParamTest, MR45) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, inserted_text = "arbitraryText";
    string str2 = str1.substr(0, str1.size() / 2) + inserted_text + str1.substr(str1.size() / 2);

    /* Expected edit distance is the length of inserted_text */
    int expected_distance = inserted_text.length();

    /* Get follow-up output */
    int follow_out = edit_dist(str1, str2);

    /* Verification */
    EXPECT_LE(follow_out, expected_distance);
}


INSTANTIATE_TEST_CASE_P(TrueReturn, EditingdistanceParamTest, testing::ValuesIn(gen_tcs_randomly()));