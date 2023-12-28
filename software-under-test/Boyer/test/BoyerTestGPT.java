package test;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.util.stream.Stream;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import src.Boyer;

public class BoyerTestGPT {
    /**
     * Metamorphic Relation 1: Add a string to the end of the origin string, the output of the
     * algorithm should be the same or greater.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text + "xxx";

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res >= origin_res);
    }

    /**
     * Metamorphic Relation 2: If the pattern is an empty string, the output should be 0 for any
     * input text.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(String text, String pattern) {
        /* Get output for any input text with an empty pattern */
        int res = Boyer.indexOf(text, "");

        /* Verification */
        assertTrue(res == 0);
    }

    /**
     * Metamorphic Relation 3: If the pattern occurs in the text, removing any character from the
     * pattern should still result in a valid match.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1 && pattern.length() > 1) {
            /* Remove a character from the pattern */
            String modified_pattern = pattern.substring(0, pattern.length() - 1);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, modified_pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 4: Reversing the input text should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Reverse the input text */
        String reversed_text = new StringBuilder(text).reverse().toString();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(reversed_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 5: If the pattern is not present in the text, the output should be -1
     * regardless of any changes in the input.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res == -1) {
            /* Construct follow-up input */
            String follow_text = text + "xxx";

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(follow_text, pattern);

            /* Verification */
            assertTrue(follow_res == -1);
        }
    }

    /**
     * Metamorphic Relation 6: Searching for an empty pattern should result in the same output as
     * searching for the original pattern.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Get follow-up output with an empty pattern */
        int follow_res = Boyer.indexOf(text, "");

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 7: If the pattern occurs multiple times in the text, the output should
     * be the index of the first occurrence.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1) {
            /* Add the pattern multiple times to the text */
            String multi_occurrence_text = text + pattern + text + pattern;

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(multi_occurrence_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 8: Searching for a pattern with a space at the beginning or end should
     * produce the same output as searching for the original pattern.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (!pattern.isEmpty()) {
            /* Add a space at the beginning and end of the pattern */
            String spaced_pattern = " " + pattern + " ";

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, spaced_pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 9: If the pattern is longer than the text, the output should be -1,
     * indicating that the pattern cannot be found in the text.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(String text, String pattern) {
        if (pattern.length() > text.length()) {
            /* Get output for a pattern longer than the text */
            int res = Boyer.indexOf(text, pattern);

            /* Verification */
            assertTrue(res == -1);
        }
    }

    /**
     * Metamorphic Relation 10: If the pattern is an exact substring of the text, the output should
     * be 0, indicating the first occurrence at the beginning.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String text, String pattern) {
        /* Get output for a pattern that is an exact substring of the text */
        int res = Boyer.indexOf(text, pattern);

        if (text.contains(pattern)) {
            /* Verification */
            assertTrue(res == 0);
        }
    }

    /**
     * Metamorphic Relation 11: If the pattern is not present in the text, removing any character
     * from the text should still result in -1.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(String text, String pattern) {
        /* Get output for any modified input text without the pattern */
        int res = Boyer.indexOf(text.replaceFirst(String.valueOf(pattern.charAt(0)), ""), pattern);

        if (!text.contains(pattern)) {
            /* Verification */
            assertTrue(res == -1);
        }
    }

    /**
     * Metamorphic Relation 12: If the pattern is an empty string, the output should be 0 for any
     * input text.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(String text, String pattern) {
        /* Get output for any input text with an empty pattern */
        int res = Boyer.indexOf(text, "");

        /* Verification */
        assertTrue(res == 0);
    }

    /**
     * Metamorphic Relation 13: If the pattern is present in the text, inserting any character at
     * the beginning of the text should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1) {
            /* Insert a character at the beginning of the text */
            String modified_text = "x" + text;

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 14: If the pattern is not present in the text, appending any character
     * to the end of the text should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res == -1) {
            /* Append a character to the end of the text */
            String modified_text = text + "x";

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 15: If the pattern is not present in the text, reversing the order of
     * characters in the text should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res == -1) {
            /* Reverse the order of characters in the text */
            String reversed_text = new StringBuilder(text).reverse().toString();

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(reversed_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 16: If the pattern is not present in the text, replacing any character
     * in the text with the same character should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res == -1 && !text.isEmpty()) {
            /* Replace a character in the text with the same character */
            char replacementChar = text.charAt(0);
            String modified_text = text.replace(replacementChar, replacementChar);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 17: If the pattern is present in the text, replacing any character in
     * the pattern with the same character should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1 && !pattern.isEmpty()) {
            /* Replace a character in the pattern with the same character */
            char replacementChar = pattern.charAt(0);
            String modified_pattern = pattern.replace(replacementChar, replacementChar);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, modified_pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 18: If the pattern is not present in the text, replacing any character
     * in the text with a different character should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res == -1 && !text.isEmpty()) {
            /* Replace a character in the text with a different character */
            char replacementChar = text.charAt(0) == 'a' ? 'b' : 'a';
            String modified_text = text.replace(text.charAt(0), replacementChar);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 19: If the pattern is present in the text, prepending the pattern to the
     * text should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1) {
            /* Prepend the pattern to the text */
            String modified_text = pattern + text;

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 20: If the pattern is not present in the text, appending the text to the
     * pattern should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res == -1) {
            /* Append the text to the pattern */
            String modified_text = pattern + text;

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 21: If the pattern is not present in the text, inserting the pattern at
     * any position in the text should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res == -1) {
            /* Insert the pattern at a random position in the text */
            int insertPosition = Math.min(text.length(), 3);
            String modified_text =
                    text.substring(0, insertPosition) + pattern + text.substring(insertPosition);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 22: If the pattern is present in the text, replacing the first
     * occurrence of the pattern with a different pattern should result in a different output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1) {
            /* Replace the first occurrence of the pattern with a different pattern */
            String modified_text = text.replaceFirst(pattern, "different");

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res != origin_res);
        }
    }

    /**
     * Metamorphic Relation 23: If the pattern is present in the text, doubling the pattern in the
     * text should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1) {
            /* Double the pattern in the text */
            String modified_text = text + pattern;

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 24: If the pattern is present in the text, replacing all occurrences of
     * the pattern with a different pattern should result in a different output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1) {
            /* Replace all occurrences of the pattern with a different pattern */
            String modified_text = text.replaceAll(pattern, "different");

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res != origin_res);
        }
    }

    /**
     * Metamorphic Relation 25: If the pattern is present in the text, changing the case of the
     * pattern in the text should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1) {
            /* Change the case of the pattern in the text */
            String modified_text = text.replace(pattern, pattern.toUpperCase());

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 26: If the pattern is not present in the text, changing the case of the
     * text should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res == -1) {
            /* Change the case of the text */
            String modified_text = text.toUpperCase();

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 27: If the pattern is present in the text, removing all occurrences of
     * the pattern should result in an output of -1.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1) {
            /* Remove all occurrences of the pattern from the text */
            String modified_text = text.replaceAll(pattern, "");

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == -1);
        }
    }

    /**
     * Metamorphic Relation 28: If the pattern is present in the text, appending a different pattern
     * to the end of the text should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1) {
            /* Append a different pattern to the end of the text */
            String modified_text = text + "differentPattern";

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 29: If the pattern is not present in the text, inserting the pattern at
     * the beginning of the text should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res == -1) {
            /* Insert the pattern at the beginning of the text */
            String modified_text = pattern + text;

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 30: If the pattern is present in the text, replacing it with an empty
     * pattern should result in an output of -1.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1) {
            /* Replace the pattern with an empty pattern in the text */
            String modified_text = text.replace(pattern, "");

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == -1);
        }
    }

    /**
     * Metamorphic Relation 31: If the pattern is not present in the text, removing any character
     * from the pattern should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res == -1 && pattern.length() > 1) {
            /* Remove a character from the pattern */
            String modified_pattern = pattern.substring(0, pattern.length() - 1);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, modified_pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 32: If the pattern is not present in the text, replacing any character
     * in the pattern with a different character should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res == -1 && !pattern.isEmpty()) {
            /* Replace a character in the pattern with a different character */
            char replacementChar = pattern.charAt(0) == 'a' ? 'b' : 'a';
            String modified_pattern = pattern.replace(pattern.charAt(0), replacementChar);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, modified_pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 33: If the pattern is not present in the text, doubling the pattern in
     * the text should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res == -1) {
            /* Double the pattern in the text */
            String modified_text = text + pattern;

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 34: If the pattern is not present in the text, replacing any character
     * in the text with a character from the pattern should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res == -1 && !pattern.isEmpty()) {
            /* Replace a character in the text with a character from the pattern */
            char replacementChar = pattern.charAt(0);
            String modified_text = text.replace(text.charAt(0), replacementChar);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 35: If the pattern is not present in the text, replacing any character
     * in the pattern with a character from the text should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res == -1 && !pattern.isEmpty() && text.length() > 0) {
            /* Replace a character in the pattern with a character from the text */
            char replacementChar = text.charAt(0);
            String modified_pattern = pattern.replace(pattern.charAt(0), replacementChar);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, modified_pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 36: If the pattern is not present in the text, replacing any character
     * in the pattern with a character not present in the text should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res == -1 && !pattern.isEmpty() && text.length() > 0) {
            /* Replace a character in the pattern with a character not present in the text */
            char replacementChar = 'x';
            String modified_pattern = pattern.replace(pattern.charAt(0), replacementChar);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, modified_pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 37: If the pattern is present in the text, reversing the pattern in the
     * text should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1 && !pattern.isEmpty()) {
            /* Reverse the pattern in the text */
            String reversed_pattern = new StringBuilder(pattern).reverse().toString();
            String modified_text = text.replaceFirst(pattern, reversed_pattern);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 38: If the pattern is present in the text, appending a different pattern
     * to the end of the pattern in the text should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1 && !pattern.isEmpty()) {
            /* Append a different pattern to the end of the pattern in the text */
            String modified_text = text.replaceFirst(pattern, pattern + "differentPattern");

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 39: If the pattern is not present in the text, appending the pattern to
     * itself should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res == -1 && !pattern.isEmpty()) {
            /* Append the pattern to itself */
            String modified_text = text + pattern;

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 40: If the pattern is not present in the text, replacing any character
     * in the text with a different character from the pattern should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res == -1 && !pattern.isEmpty() && text.length() > 0) {
            /* Replace a character in the text with a different character from the pattern */
            char replacementChar = pattern.charAt(0) == 'a' ? 'b' : 'a';
            String modified_text = text.replace(text.charAt(0), replacementChar);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 41: If the pattern is present in the text, replacing any character in
     * the pattern with a different character from the text should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test41(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1 && !pattern.isEmpty() && text.length() > 0) {
            /* Replace a character in the pattern with a different character from the text */
            char replacementChar = text.charAt(0) == 'a' ? 'b' : 'a';
            String modified_pattern = pattern.replace(pattern.charAt(0), replacementChar);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, modified_pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 42: If the pattern is present in the text, replacing all occurrences of
     * the pattern with a different pattern containing characters not present in the text should not
     * affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test42(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1 && !pattern.isEmpty() && text.length() > 0) {
            /* Replace all occurrences of the pattern with a different pattern */
            char replacementChar = 'x';
            String modified_text = text.replaceAll(pattern, pattern + replacementChar);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 43: If the pattern is present in the text, replacing any character in
     * the pattern with a character not present in the pattern should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test43(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1 && !pattern.isEmpty()) {
            /* Replace a character in the pattern with a character not present in the pattern */
            char replacementChar = 'x';
            String modified_pattern = pattern.replace(pattern.charAt(0), replacementChar);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, modified_pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 44: If the pattern is present in the text, appending the pattern to
     * itself a certain number of times should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test44(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1 && !pattern.isEmpty()) {
            /* Append the pattern to itself a certain number of times */
            int repeatCount = 3;
            String modified_text = text.replaceFirst(pattern, pattern.repeat(repeatCount));

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 45: If the pattern is present in the text, replacing the last occurrence
     * of the pattern with a different pattern should result in a different output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test45(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1 && !pattern.isEmpty()) {
            /* Replace the last occurrence of the pattern with a different pattern */
            String modified_text = text.replace(pattern, "different");

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res != origin_res);
        }
    }

    /**
     * Metamorphic Relation 46: If the pattern is present in the text, appending the text to itself
     * should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test46(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1 && !pattern.isEmpty()) {
            /* Append the text to itself */
            String modified_text = text + text;

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 47: If the pattern is present in the text, replacing any character in
     * the pattern with a character not present in the text should result in an output of -1.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test47(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1 && !pattern.isEmpty() && text.length() > 0) {
            /* Replace a character in the pattern with a character not present in the text */
            char replacementChar = 'x';
            String modified_pattern = pattern.replace(pattern.charAt(0), replacementChar);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, modified_pattern);

            /* Verification */
            assertTrue(follow_res == -1);
        }
    }

    /**
     * Metamorphic Relation 48: If the pattern is not present in the text, replacing any character
     * in the text with a character not present in the pattern should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test48(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res == -1 && !pattern.isEmpty() && text.length() > 0) {
            /* Replace a character in the text with a character not present in the pattern */
            char replacementChar = 'x';
            String modified_text = text.replace(text.charAt(0), replacementChar);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 49: If the pattern is present in the text, swapping the positions of two
     * different characters in the pattern should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test49(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res != -1 && pattern.length() > 1) {
            /* Swap the positions of two different characters in the pattern */
            char char1 = pattern.charAt(0);
            char char2 = pattern.charAt(1);
            String modified_pattern = pattern.replace(char1, char2).replace(char2, char1);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, modified_pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    /**
     * Metamorphic Relation 50: If the pattern is not present in the text, swapping the positions of
     * two different characters in the text should not affect the output.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test50(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (origin_res == -1 && text.length() > 1) {
            /* Swap the positions of two different characters in the text */
            char char1 = text.charAt(0);
            char char2 = text.charAt(1);
            String modified_text = text.replace(char1, char2).replace(char2, char1);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(modified_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res);
        }
    }

    static Stream<Arguments> testcaseProvider() {
        return Stream.of(Arguments.of("abcdefg", "abc"), Arguments.of("abcdefg", "xyz"));
    }
}
