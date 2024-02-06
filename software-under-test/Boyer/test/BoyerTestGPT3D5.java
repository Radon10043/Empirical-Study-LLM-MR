package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.IOException;
import java.util.Collections;
import java.util.stream.Stream;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import org.junit.runners.Parameterized.Parameter;
import src.Boyer;

public class BoyerTestGPT3D5 {
    /**
     * Metamorphic Relation 1: If the pattern occurred in the original text, when a prefix is added
     * to the source text, the output should be the same or greater than the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = "prefix" + text;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res >= origin_res);
    }

    /**
     * Metamorphic Relation 2: If the pattern occurred in the original text, when deleting one
     * character from the end of the pattern, the output should be the same as or less than the
     * original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = pattern.substring(0, pattern.length() - 1);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res <= origin_res);
    }

    /**
     * Metamorphic Relation 3: If the pattern occurred in the original text, when we reverse the
     * pattern, the output should be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = new StringBuilder(pattern).reverse().toString();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 4: If the pattern occurred in the original text, when replacing one
     * character with another character in the pattern, the output should be the same or less than
     * the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = pattern.replace('a', 'b'); // Replace 'a' with 'b' in the pattern

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res <= origin_res);
    }

    /**
     * Metamorphic Relation 5: If the pattern occurred in the original text, when adding spaces to the pattern's
     * beginning or end, the output should be the same as the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = " " + pattern + " ";  // Add spaces to the pattern's beginning and end

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 6: If the pattern occurred in the original text, when the pattern is converted to uppercase,
     * the output should be the same as the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = pattern.toUpperCase();  // Convert pattern to uppercase

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 7: If the pattern occurred in the original text, when the pattern is duplicated,
     * the output should be the same or less than the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = pattern + pattern;  // Duplicate the pattern

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res <= origin_res);
    }

    /**
     * Metamorphic Relation 8: If the pattern occurred in the original text, when the pattern is empty,
     * the output should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = "";  // Empty pattern

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == 0);
    }

    /**
     * Metamorphic Relation 9: If the pattern occurred in the original text, when the pattern is a substring of itself,
     * the output should be the same as the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern;
        if (pattern.length() > 1) {
            follow_pattern = pattern.substring(0, pattern.length() / 2);  // Pattern is a substring of itself
        } else {
            follow_pattern = pattern;
        }

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 10: If the pattern did not occur in the original text, when the pattern is reversed,
     * the output should be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String text, String pattern) {
        if (text.indexOf(pattern) != -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = new StringBuilder(pattern).reverse().toString();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == -1);
    }

    /**
     * Metamorphic Relation 11: When text is an empty string and pattern is also an empty string, the output should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(String text, String pattern) {
        String emptyText = "";
        String emptyPattern = "";

        /* Get origin output */
        int origin_res = Boyer.indexOf(emptyText, emptyPattern);

        /* Verification */
        assertTrue(origin_res == 0);
    }

    /**
     * Metamorphic Relation 12: If the pattern occurred in the original text, when the text and pattern are switched,
     * the output should be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        int follow_res = Boyer.indexOf(pattern, text);

        /* Verification */
        assertTrue(origin_res == follow_res);
    }

    /**
     * Metamorphic Relation 13: When the pattern occurred in the original text, and the text is duplicated, the output should be the same or greater than the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text + text;  // Duplicate the text

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res >= origin_res);
    }

    /**
     * Metamorphic Relation 14: When the pattern occurred in the original text, and the pattern is a substring of the text, the output should be the same or less than the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = text.substring(0, text.length() - 1);  // Pattern is a substring of the text

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res <= origin_res);
    }

    /**
     * Metamorphic Relation 15: If the pattern occurred in the original text, when the text is the same as the pattern, the output should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = pattern;  // Text is the same as the pattern

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == 0);
    }

    /**
     * Metamorphic Relation 16: If the pattern occurred in the original text, when the text is in uppercase, the output should be the same as the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text.toUpperCase();  // Convert text to uppercase

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 17: If the pattern occurred in the original text, when the pattern is a substring of the original pattern, the output should be the same as the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = pattern.substring(1);  // Pattern is a substring of the original pattern

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 18: If the pattern occurred in the original text, when the pattern is replaced with an empty string,
     * the output should be the same as the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = "";  // Replace pattern with an empty string

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 19: If the pattern occurred in the original text, when the pattern and text are concatenated,
     * the output should be the same or greater than the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String combined = text + pattern;  // Concatenate the pattern and the text

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(combined, pattern);

        /* Verification */
        assertTrue(follow_res >= origin_res);
    }

    /**
     * Metamorphic Relation 20: If the pattern occurred in the original text, when the pattern is null, the output should be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, "");  // Pattern is null

        /* Verification */
        assertTrue(follow_res == -1);
    }

    /**
     * Metamorphic Relation 21: If the pattern occurred in the original text, when the pattern is replaced with a longer substring, the output should be the same or less than the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = pattern + "xyz";  // Replace pattern with a longer substring

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res <= origin_res);
    }

    /**
     * Metamorphic Relation 22: If the pattern occurred in the original text, when the entire text and pattern are both put inside an additional string, the output should be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = "abcd" + text + "efgh";  // Entire text wrapped inside an additional string
        String follow_pattern = "ijkl" + pattern + "mnop";  // Entire pattern wrapped inside an additional string

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 23: If the pattern occurred in the original text, when the pattern contains special characters or escape sequences, the output should be the same as the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input with special characters or escape sequences in the pattern */
        String follow_pattern = "a*b.[c]";  // Pattern contains special characters

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 24: If the pattern occurred in the original text, when the text has leading or trailing whitespace, the output should be the same as the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input with leading and trailing whitespace in the text */
        String follow_text = "  " + text + "  ";  // Text with leading and trailing whitespace

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 25: When the pattern occurred in the original text, if the text and pattern both have leading or trailing whitespace, the output should be the same as the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input with leading and trailing whitespace in both text and pattern */
        String follow_text = "  " + text + "  ";  // Text with leading and trailing whitespace
        String follow_pattern = "  " + pattern + "  ";  // Pattern with leading and trailing whitespace

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 26: If the pattern occurred in the original text, when the pattern and text are inverted, the output should be the same as the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input with inverted text and pattern */
        String follow_text = new StringBuilder(text).reverse().toString();  // Inverted text
        String follow_pattern = new StringBuilder(pattern).reverse().toString();  // Inverted pattern

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 27: If the pattern occurred in the original text, when the pattern and text are reversed, the output should be the same as the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input with reversed text and pattern */
        String follow_text = new StringBuilder(text).reverse().toString();  // Reversed text
        String follow_pattern = new StringBuilder(pattern).reverse().toString();  // Reversed pattern

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 28: If the pattern occurred in the original text, when the pattern is the same as the text, the output should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input with pattern the same as the text */
        String follow_pattern = text;  // Pattern is the same as the text

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == 0);
    }

    /**
     * Metamorphic Relation 29: If the pattern occurred in the original text, when the pattern is appended with the first character of the text, the output should be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (text.length() > 0) {
            /* Construct follow-up input */
            String follow_pattern = pattern + text.charAt(0);  // Append the first character of the text to the pattern

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, follow_pattern);

            /* Verification */
            assertTrue(follow_res == -1);
        }
    }

    /**
     * Metamorphic Relation 30: If the pattern occurred in the original text, when the pattern is replaced with a different pattern of the same length, the output should be the same or less than the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (pattern.length() > 3) {
            /* Construct follow-up input */
            String follow_pattern = "abc" + pattern.substring(3);  // Replace the first three characters of the pattern with "abc"

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, follow_pattern);

            /* Verification */
            assertTrue(follow_res <= origin_res);
        }
    }

    /**
     * Metamorphic Relation 31: For any text and pattern, replacing the text with an empty string should result in the same output as replacing the pattern with an empty string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(String text, String pattern) {
        /* Get output with original text and pattern */
        int original_output = Boyer.indexOf(text, pattern);

        /* Get output with an empty pattern */
        int empty_pattern_output = Boyer.indexOf(text, "");

        /* Get output with an empty text */
        int empty_text_output = Boyer.indexOf("", pattern);

        /* Verification */
        assertEquals(empty_pattern_output, empty_text_output);
        assertEquals(original_output, empty_pattern_output);
    }

    /**
     * Metamorphic Relation 32: For any text and pattern, replacing the text with a null string should result in -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(String text, String pattern) {
        if (text != null && pattern != null) {
            /* Get output with original text and pattern */
            int original_output = Boyer.indexOf(text, pattern);

            /* Get output with a null text */
            int null_text_output = Boyer.indexOf("", pattern);

            /* Verification */
            assertEquals(-1, null_text_output);
        }
    }

    /**
     * Metamorphic Relation 33: If the pattern occurred in the original text, when the pattern is longer than the text, the output should be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get original output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (pattern.length() + 5 > text.length()) {
            /* Construct follow-up input */
            String follow_pattern = pattern + "abcde";  // Pattern is longer than the text

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, follow_pattern);

            /* Verification */
            assertTrue(follow_res == -1);
        }
    }

    /**
     * Metamorphic Relation 34: If the pattern occurred in the original text, when the text is null, the output should be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get original output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf("", pattern);

        /* Verification */
        assertTrue(follow_res == -1);
    }

    /**
     * Metamorphic Relation 35: If the pattern occurred in the original text, when the text and pattern are swapped, the output should be the same as the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get original output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        int follow_res = Boyer.indexOf(pattern, text); // Swapping the text and pattern

        /* Verification */
        assertEquals(origin_res, follow_res);
    }

    /**
     * Metamorphic Relation 36: If the pattern occurred in the original text, when the pattern is replaced with a different pattern, the output should be the same or less than the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get original output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = pattern.substring(1) + "x";  // Replace the first character of pattern with 'x'

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res <= origin_res);
    }

    /**
     * Metamorphic Relation 37: If the pattern occurred in the original text, when the pattern is replaced with a substring, the output should be the same or less than the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get original output */
        int originalOutput = Boyer.indexOf(text, pattern);

        /* Replace pattern with a substring */
        if (pattern.length() <= 3) {
            return;
        }
        String newPattern = "abc" + pattern.substring(3);

        /* Get output with the new pattern */
        int newOutput = Boyer.indexOf(text, newPattern);

        /* Verification */
        assertTrue(newOutput <= originalOutput);
    }

    /**
     * Metamorphic Relation 38: If the pattern occurred in the original text, when the pattern and text are empty strings, the output should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(String text, String pattern) {
        String emptyText = "";
        String emptyPattern = "";

        /* Get output with both empty text and empty pattern */
        int output = Boyer.indexOf(emptyText, emptyPattern);

        /* Verification */
        assertEquals(0, output);
    }

    /**
     * Metamorphic Relation 39: If the pattern occurred in the original text, when the first and last characters of the pattern are swapped, the output should be the same as the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get original output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (pattern.length() >= 2) {
            // Swap first and last characters of the pattern
            char[] charArray = pattern.toCharArray();
            char temp = charArray[0];
            charArray[0] = charArray[pattern.length() - 1];
            charArray[pattern.length() - 1] = temp;
            String follow_pattern = new String(charArray);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, follow_pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 40: If the pattern occurred in the original text, when the pattern contains uppercase letters, the output should be the same as the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get original output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (pattern.toUpperCase().equals(pattern)) {
            /* Construct follow-up input */
            String follow_pattern = pattern.toLowerCase();  // Convert the pattern to lowercase

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, follow_pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    static Stream<Arguments> testcaseProvider() throws IOException {
        return testcaseGenerator.generate_ss(1000);
    }
}
