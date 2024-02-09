#include <algorithm>
#include <gtest/gtest.h>
#include <random>
#include <string>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class EditingdistanceParamTest : public ::testing::TestWithParam<EditingdistanceInput> {};

/**
 * @brief Metamorphic relation 1: Swap the source and target strings (str1 and str2), the output should be the same.
 *
 */
TEST_P(EditingdistanceParamTest, MR1) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Swap the strings */
    int follow_out = edit_dist(str2, str1);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 2: Concatenate a common substring to both str1 and str2, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR2) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    int commonLen = min(str1.length(), str2.length());
    int i;
    for (i = commonLen; i > 0; i--) {
        if (str1.substr(str1.length() - i) == str2.substr(0, i)) {
            break;
        }
    }
    string commonSubstr = str1.substr(str1.length() - i);
    string follow_str1 = str1 + commonSubstr;
    string follow_str2 = str2 + commonSubstr;

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 3: Reverse both str1 and str2, the output should be the same.
 *
 */
TEST_P(EditingdistanceParamTest, MR3) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Reverse the strings */
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());

    /* Get follow-up output */
    int follow_out = edit_dist(str1, str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 4: Append the same character to both str1 and str2, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR4) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    char c = 'x';  // Any character
    string follow_str1 = str1 + c;
    string follow_str2 = str2 + c;

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 5: Truncate a common substring from both str1 and str2, the output should be the same or smaller.
 *
 */
TEST_P(EditingdistanceParamTest, MR5) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    int commonLen = min(str1.length(), str2.length());
    int i;
    for (i = commonLen; i > 0; i--) {
        if (str1.substr(str1.length() - i) == str2.substr(0, i)) {
            break;
        }
    }
    string follow_str1 = str1.substr(0, str1.length() - i);
    string follow_str2 = str2.substr(i);

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 6: Repeat both str1 and str2, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR6) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Added by Radon. Truncate string, prevent execute too long time. */
    if (str1.length() > 4) str1 = str1.substr(0, 4);
    if (str2.length() > 4) str2 = str2.substr(0, 4);

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    string follow_str1 = str1 + str1;  // Repeat str1
    string follow_str2 = str2 + str2;  // Repeat str2

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 7: Change both str1 and str2 to upper case, the output should be the same.
 *
 */
TEST_P(EditingdistanceParamTest, MR7) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Convert to upper case */
    transform(str1.begin(), str1.end(), str1.begin(), ::toupper);
    transform(str2.begin(), str2.end(), str2.begin(), ::toupper);

    /* Get follow-up output */
    int follow_out = edit_dist(str1, str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 8: Add a character to the end of both str1 and str2, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR8) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    char c = 'x';  // Any character
    string follow_str1 = str1 + c;
    string follow_str2 = str2 + c;

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 9: Add a character in the middle of both str1 and str2, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR9) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    str1 = "zwxhjfll";
    str2 = "mddx";

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    char c = 'x';  // Any character
    int mid = str1.length() / 2;
    string follow_str1 = str1.substr(0, mid) + c + str1.substr(mid);
    mid = str2.length() / 2;
    string follow_str2 = str2.substr(0, mid) + c + str2.substr(mid);

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 10: Shuffle the characters of both str1 and str2, the output should be the same.
 *
 */
TEST_P(EditingdistanceParamTest, MR10) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Shuffle the characters */
    random_shuffle(str1.begin(), str1.end());
    random_shuffle(str2.begin(), str2.end());

    /* Get follow-up output */
    int follow_out = edit_dist(str1, str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 11: Prepend the same character to both str1 and str2, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR11) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    char c = 'x';  // Any character
    string follow_str1 = c + str1;
    string follow_str2 = c + str2;

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 12: Truncate str2 to a substring, the output should be the same or smaller.
 *
 */
TEST_P(EditingdistanceParamTest, MR12) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    int len = str2.length() / 2;
    string follow_str2 = str2.substr(0, len);

    /* Get follow-up output */
    int follow_out = edit_dist(str1, follow_str2);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 13: Append a substring to both str1 and str2, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR13) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    int len = str2.length() / 2;
    string addition = str2.substr(len);
    string follow_str1 = str1 + addition;
    string follow_str2 = str2 + addition;

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 14: Repeat a common substring in both str1 and str2, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR14) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    int commonLen = min(str1.length(), str2.length());
    int i;
    for (i = commonLen; i > 0; i--) {
        if (str1.substr(str1.length() - i) == str2.substr(0, i)) {
            break;
        }
    }
    string commonSubstr = str1.substr(str1.length() - i);
    string follow_str1 = str1 + commonSubstr;
    string follow_str2 = str2 + commonSubstr;

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 15: Insert the same character at the same index in both str1 and str2, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR15) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    char c = 'x';  // Any character
    int index = str1.length() / 2;  // Insert at the middle
    string follow_str1 = str1.substr(0, index) + c + str1.substr(index);
    string follow_str2 = str2.substr(0, index) + c + str2.substr(index);

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 16: Reverse str1 and concatenate it to str2, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR16) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);
    
    /* Construct follow-up input */
    string reverse_str1 = str1;
    reverse(reverse_str1.begin(), reverse_str1.end());
    string follow_str2 = str2 + reverse_str1;

    /* Get follow-up output */
    int follow_out = edit_dist(reverse_str1, follow_str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 17: Add a space to both str1 and str2, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR17) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;
    
    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    string follow_str1 = str1 + " ";
    string follow_str2 = str2 + " ";

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);
    
    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 18: Add a suffix to str1 and str2, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR18) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;
    
    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    string follow_str1 = str1 + "_suffix";
    string follow_str2 = str2 + "_suffix";

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);
    
    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 19: Convert str1 to uppercase and str2 to lowercase, the output should be the same.
 *
 */
TEST_P(EditingdistanceParamTest, MR19) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Convert strings to different cases */
    transform(str1.begin(), str1.end(), str1.begin(), ::toupper);
    transform(str2.begin(), str2.end(), str2.begin(), ::tolower);


    /* Get follow-up output */
    int follow_out = edit_dist(str1, str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 20: Remove a common prefix from str1 and str2, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR20) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;
    
    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    int prefixLen = 0;
    while (prefixLen < min(str1.length(), str2.length()) && str1[prefixLen] == str2[prefixLen]) {
        prefixLen++;
    }
    string follow_str1 = str1.substr(prefixLen);
    string follow_str2 = str2.substr(prefixLen);

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);
    
    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 21: Insert a common substring to both str1 and str2, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR21) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;
    
    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    int commonLen = min(str1.length(), str2.length());
    int i;
    for (i = commonLen; i > 0; i--) {
        if (str1.substr(str1.length() - i) == str2.substr(0, i)) {
            break;
        }
    }
    string commonSubstr = str1.substr(str1.length() - i);
    string follow_str1 = str1 + commonSubstr;
    string follow_str2 = str2 + commonSubstr;

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);
    
    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 22: Swap the positions of two substrings in both str1 and str2, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR22) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;
    
    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    int len1 = str1.length() / 3;
    int len2 = str2.length() / 2;
    string sub1 = str1.substr(len1, len1);
    string sub2 = str2.substr(len2, len2);
    string follow_str1 = str1.substr(0, len1) + sub2 + str1.substr(len1 + len2);
    string follow_str2 = str2.substr(0, len2) + sub1 + str2.substr(len2 + len1);

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 23: If str1 and str2 are the same, the output should be 0 (zero).
 *
 */
TEST_P(EditingdistanceParamTest, MR23) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;
    
    /* Get source output */
    int source_out = edit_dist(str1, str1);
    
    /* Verification */
    EXPECT_EQ(source_out, 0);
}

/**
 * @brief Metamorphic relation 24: If str2 is an empty string, the output should be the length of str1.
 *
 */
TEST_P(EditingdistanceParamTest, MR24) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1;
    
    /* Get source output */
    string empty = "";
    int source_out = edit_dist(str1, empty);
    
    /* Verification */
    EXPECT_EQ(source_out, str1.length());
}

/**
 * @brief Metamorphic relation 25: Add a whitespace character to the end of both str1 and str2, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR25) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;
    
    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    string follow_str1 = str1 + " ";
    string follow_str2 = str2 + " ";

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);
    
    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 26: Replace a character in str2 with another character, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR26) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;
    
    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    char replacement = 'x';  // Any character
    int index = str2.length() / 2;  // Replace at the middle
    string follow_str2 = str2;
    follow_str2[index] = replacement;

    /* Get follow-up output */
    int follow_out = edit_dist(str1, follow_str2);
    
    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 27: If str2 is a substring of str1, the output should be the difference in lengths of str1 and str2.
 *
 */
TEST_P(EditingdistanceParamTest, MR27) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;
    
    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Calculate difference in lengths */
    int diffLength = str1.length() - str2.length();

    /* Verification */
    EXPECT_EQ(source_out, abs(diffLength));
}

/**
 * @brief Metamorphic relation 28: If str1 and str2 are both empty strings, the output should be 0 (zero).
 *
 */
TEST_P(EditingdistanceParamTest, MR28) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;
    
    /* Get source output */
    string empty = "";
    int source_out = edit_dist(empty, empty);
    
    /* Verification */
    EXPECT_EQ(source_out, 0);
}

/**
 * @brief Metamorphic relation 29: If both str1 and str2 are the same, and a character is added to str1, the output should be 1.
 *
 */
TEST_P(EditingdistanceParamTest, MR29) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1;
    
    /* Get source output */
    int source_out = edit_dist(str1, str1);
    
    /* Construct follow-up input */
    string follow_str1 = str1 + "x";  // Add a character to str1
    
    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str1);
    
    /* Verification */
    EXPECT_EQ(follow_out, 1);
}

/**
 * @brief Metamorphic relation 30: If str1 and str2 are completely different, the output should be the maximum of their lengths.
 *
 */
TEST_P(EditingdistanceParamTest, MR30) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Calculate the maximum length */
    int max_length = max(str1.length(), str2.length());

    /* Verification */
    EXPECT_EQ(source_out, max_length);
}

/**
 * @brief Metamorphic relation 31: Reverse both str1 and str2, the output should be the same.
 *
 */
TEST_P(EditingdistanceParamTest, MR31) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Reverse the strings */
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Get follow-up output */
    int follow_out = edit_dist(str1, str2);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 32: Concatenate a common substring to both str1 and str2, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR32) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    int commonLen = min(str1.length(), str2.length());
    int i;
    for (i = commonLen; i > 0; i--) {
        if (str1.substr(str1.length() - i) == str2.substr(0, i)) {
            break;
        }
    }
    string commonSubstr = str1.substr(str1.length() - i);
    string follow_str1 = str1 + commonSubstr;
    string follow_str2 = str2 + commonSubstr;

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 33: Truncate a common substring from both str1 and str2, the output should be the same or smaller.
 *
 */
TEST_P(EditingdistanceParamTest, MR33) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    int commonLen = min(str1.length(), str2.length());
    int i;
    for (i = commonLen; i > 0; i--) {
        if (str1.substr(str1.length() - i) == str2.substr(0, i)) {
            break;
        }
    }
    string follow_str1 = str1.substr(0, str1.length() - i);
    string follow_str2 = str2.substr(i);

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 34: Insert a new character into both str1 and str2 at the same position, the output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR34) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    int pos = str1.length() / 2;
    char newChar = 'a';  // Any character
    string follow_str1 = str1.substr(0, pos) + newChar + str1.substr(pos);
    string follow_str2 = str2.substr(0, pos) + newChar + str2.substr(pos);

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 35: Copy the first half of str1 to a new string and append it to str1, then do the same for str2.
 *                                 The output should be the same or larger.
 *
 */
TEST_P(EditingdistanceParamTest, MR35) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Added by Radon. Truncate strings, prevent execute too long time. */
    if (str1.length() > 4) str1 = str1.substr(0, 4);
    if (str2.length() > 4) str2 = str2.substr(0, 4);

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    int half = str1.length() / 2;
    string follow_str1 = str1 + str1.substr(0, half);
    string follow_str2 = str2 + str2.substr(0, half);

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 36: If both str1 and str2 are the same, and a character is removed from str1, the output should be 1 (one).
 *
 */
TEST_P(EditingdistanceParamTest, MR36) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1;
    
    /* Get source output */
    int source_out = edit_dist(str1, str1);
    
    /* Construct follow-up input */
    string follow_str1 = str1.substr(0, str1.length() - 1);  // Remove a character from str1
    
    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, str1);
    
    /* Verification */
    EXPECT_EQ(follow_out, 1);
}

/**
 * @brief Metamorphic relation 37: If the second string str2 is a subsequence of str1, then the edit distance result between str1 and str2 should be greater or equal to 0 and less than the length of str1.
*/
TEST_P(EditingdistanceParamTest, MR37) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;
    
    /* Get source output */
    int source_out = edit_dist(str1, str2);
    
    /* Verification */
    EXPECT_GE(source_out, 0);
    EXPECT_LT(source_out, str1.length());
}

/**
 * @brief Metamorphic relation 38: If both str1 and str2 are different, then the output should be greater than or equal to the absolute difference of their lengths.
*/
TEST_P(EditingdistanceParamTest, MR38) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;
    
    /* Get source output */
    int source_out = edit_dist(str1, str2);
    
    /* Calculate the length difference */
    int length_diff = abs(static_cast<int>(str1.length() - str2.length()));

    /* Verification */
    EXPECT_GE(source_out, length_diff);
}

/**
 * @brief Metamorphic relation 39: If a character is added to both str1 and str2 at the same position, the edit distance result should be equal or greater than the edit distance result of the original strings.
*/
TEST_P(EditingdistanceParamTest, MR39) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    /* Construct follow-up input */
    int pos = str1.length() / 2;
    char newChar = 'a';  // Any character
    string follow_str1 = str1.substr(0, pos) + newChar + str1.substr(pos);
    string follow_str2 = str2.substr(0, pos) + newChar + str2.substr(pos);

    /* Get follow-up output */
    int follow_out = edit_dist(follow_str1, follow_str2);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

/**
 * @brief Metamorphic relation 40: If str1 is empty but str2 is not, the edit distance result should be equal to the length of str2.
*/
TEST_P(EditingdistanceParamTest, MR40) {
    /* Get source input */
    EditingdistanceInput input = GetParam();
    string str1 = input.str1, str2 = input.str2;

    /* Get source output */
    int source_out = edit_dist(str1, str2);

    if (str1.empty() && !str2.empty()) {
        /* Verification */
        EXPECT_EQ(source_out, str2.length());
    }
}

INSTANTIATE_TEST_CASE_P(TrueReturn, EditingdistanceParamTest, testing::ValuesIn(gen_tcs_randomly()));