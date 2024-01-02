package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.util.stream.Stream;
import org.junit.Ignore;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import src.Boyer;

public class BoyerTestGPT3P5 {
    /**
     * Metamorphic Relation 1: Add a string to the beginning of the origin string, the output of the
     * algorithm should be different or -1.
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
        String follow_text = "xxx" + text;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == -1 || follow_res != origin_res);
    }

    /**
     * Metamorphic Relation 2: Search for the pattern in a substring of the origin string, the
     * output of the algorithm should be -1 or an integer less than the original output.
     *
     * @param text
     * @param pattern
     * @param index
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(String text, String pattern, int index) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text.substring(index);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == -1 || follow_res < origin_res);
    }

    /**
     * Metamorphic Relation 3: Search for a pattern string with characters in uppercase, the output
     * of the algorithm should be the same.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = pattern.toUpperCase();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 4: Duplicate the origin string, the output of the algorithm should be
     * the same.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text + text;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 5: Search for an empty pattern in the origin string, the output of the
     * algorithm should be 0.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String emptyString = "";
        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, emptyString);

        /* Verification */
        assertTrue(follow_res == 0);
    }

    /**
     * Metamorphic Relation 6: Swap the two input strings, the output of the algorithm should be the
     * same or -1.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        int follow_res = Boyer.indexOf(pattern, text);

        /* Verification */
        assertTrue(follow_res == origin_res || follow_res == -1);
    }

    /**
     * Metamorphic Relation 7: If the pattern is not found in the original text, then swapping the
     * text and pattern should also result in the pattern not being found.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        int follow_res = Boyer.indexOf(pattern, text);

        /* Verification */
        assertTrue(
                (origin_res == -1 && follow_res == -1) || (origin_res != -1 && follow_res != -1));
    }

    /**
     * Metamorphic Relation 8: If the pattern is found in the original text, then swapping the text
     * and pattern should still result in the pattern being found.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        int follow_res = Boyer.indexOf(pattern, text);

        /* Verification */
        assertTrue(origin_res != -1 && follow_res != -1);
    }

    /**
     * Metamorphic Relation 9: If the pattern is found in the original text, then removing the
     * pattern from the text should result in the pattern not being found.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text.replace(pattern, "");

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == -1);
    }

    /**
     * Metamorphic Relation 10: If the pattern is not found in the original text, then reversing the
     * pattern should not result in the pattern being found.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String reversedPattern = new StringBuilder(pattern).reverse().toString();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, reversedPattern);

        /* Verification */
        assertTrue(origin_res == -1 && follow_res == -1);
    }

    /**
     * Metamorphic Relation 11: If the pattern is found in the original text, then reversing the
     * pattern should result in the pattern also being found.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String reversedPattern = new StringBuilder(pattern).reverse().toString();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, reversedPattern);

        /* Verification */
        assertTrue(origin_res != -1 && follow_res != -1);
    }

    /**
     * Metamorphic Relation 12: Searching for an empty text should always result in the pattern not
     * being found.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(String text, String pattern) {
        /* Get follow-up output */
        int follow_res = Boyer.indexOf("", pattern);

        /* Verification */
        assertTrue(follow_res == -1);
    }

    /**
     * Metamorphic Relation 13: Adding spaces within the text shouldn't affect the output of the
     * pattern search.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text.replaceAll(" ", "  "); // Adding additional spaces

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 14: Inserting a pattern within the text results in the pattern no longer
     * being found.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(String text, String pattern) {
        /* Get follow-up output */
        String follow_text =
                text.substring(0, text.length() / 2) + pattern + text.substring(text.length() / 2);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == -1);
    }

    /**
     * Metamorphic Relation 15: If the entire text is replaced by the pattern, the result should be
     * found at index 0.
     * 
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String pattern) {
        /* Get follow-up output */
        String follow_text = pattern + pattern + pattern; // Replace entire text with pattern

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == 0);
    }

    /**
     * Metamorphic Relation 16: Concatenating two instances of the text should result in the same
     * output as the original text.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text + text;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 17: Prepending and appending to the text with the same string should
     * result in the original output or a modified output.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = "xyz" + text + "xyz"; // Prepending and appending

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res || follow_res != origin_res);
    }

    /**
     * Metamorphic Relation 18: Searching for a text within an empty pattern should result in an
     * invalid match.
     * 
     * @param text
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String text) {
        String pattern = "";
        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, pattern);

        /* Verification */
        assertTrue(follow_res == -1);
    }

    /**
     * Metamorphic Relation 19: Adding a prefix to the pattern doesn't change the search result.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = "abc" + pattern; // Adding prefix

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 20: Replacing occurrences of a character within the text doesn't change
     * the search result.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text.replace('a', 'x'); // Replace 'a' with 'x'

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 21: If the pattern contains duplicated characters, finding the pattern
     * in the text should yield the same result.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = "testtest"; // Duplicated characters in pattern

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 22: If the pattern is not found in the original text, changing all
     * characters to uppercase should still result in the pattern not being found.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String upperCaseText = text.toUpperCase();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(upperCaseText, pattern);

        /* Verification */
        assertTrue(origin_res == -1 && follow_res == -1);
    }

    /**
     * Metamorphic Relation 23: If the pattern is found in the original text, changing the pattern
     * to uppercase should still result in the pattern being found.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String upperCasePattern = pattern.toUpperCase();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, upperCasePattern);

        /* Verification */
        assertTrue(origin_res != -1 && follow_res != -1);
    }

    /**
     * Metamorphic Relation 24: Rotate the text by N positions and keeping the pattern the same
     * should result in the same output or -1.
     *
     * @param text
     * @param pattern
     * @param n
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(String text, String pattern, int n) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text.substring(n) + text.substring(0, n); // Rotate by N positions

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res || follow_res == -1);
    }

    /**
     * Metamorphic Relation 25: Shifting the pattern to the right within the text should not change
     * the output if the pattern is not found.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = "xxx" + text; // Shifting the pattern to the right

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(origin_res == -1 && follow_res == -1);
    }

    /**
     * Metamorphic Relation 26: Searching for the same pattern in a longer text that contains the
     * original text should yield the same result.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text + "xxx" + text; // A longer text that contains the original text

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 27: If the pattern is found in the original text, removing occurrences
     * of the pattern in the text should result in the pattern not being found.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text.replace(pattern, ""); // Remove occurrences of the pattern

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == -1);
    }

    /**
     * Metamorphic Relation 28: Repeating the pattern within the text should result in the pattern
     * being found at multiple indices.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input with repeated pattern */
        String follow_text = pattern + text + pattern;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res != -1 && follow_res != origin_res);
    }

    /**
     * Metamorphic Relation 29: Searching for a longer pattern within the text should yield the same
     * result as searching for the original pattern.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input with a longer pattern */
        String follow_pattern = pattern + "x"; // Longer pattern

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 30: Searching for the empty string as the pattern within the text should
     * yield the same result as the original pattern.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input with an empty pattern */
        String follow_pattern = ""; // Empty pattern

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 31: Reversing the pattern and the text should result in finding the
     * pattern at the same index or not finding it at all.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input with reversed pattern and text */
        String reversedText = new StringBuilder(text).reverse().toString();
        String reversedPattern = new StringBuilder(pattern).reverse().toString();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(reversedText, reversedPattern);

        /* Verification */
        assertTrue(follow_res == -1 || follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 32: Using a different pattern with the same characters as the original
     * pattern should not affect the result.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input with a similar pattern */
        String follow_pattern = "test"; // Similar characters as original pattern

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 33: Rotating the pattern within the text should result in finding the
     * pattern at a different index or not finding it at all.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input with pattern rotated within the text */
        String follow_text = text.substring(3) + text.substring(0, 3); // Rotating pattern within
                                                                       // the text

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == -1 || follow_res != origin_res);
    }

    /**
     * Metamorphic Relation 34: If the entire text is replaced by a different text, the search
     * should yield the same result as the original text.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = "differenttext"; // Replace entire text with different text

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 35: Replacing the pattern with a different pattern should result in a
     * different output or -1.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = "xdif"; // Different pattern

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == -1 || follow_res != origin_res);
    }

    /**
     * Metamorphic Relation 36: Searching for the last character of the pattern in the text should
     * yield the same result as the original pattern.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        char lastChar = pattern.charAt(pattern.length() - 1);
        String follow_text = text.replace(lastChar, 'x'); // Replace last character of the pattern
                                                          // in the text

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 37: If the pattern is found in the original text, searching for a
     * substring of the pattern within the text should yield the same result.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input with a substring of the pattern */
        String follow_pattern = pattern.substring(0, pattern.length() - 1); // Substring of the
                                                                            // pattern

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 38: If the pattern is not found in the original text, reversing the text
     * should also result in not finding the pattern.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(String text, String pattern) {
        /* Construct follow-up input by reversing the original text */
        String follow_text = new StringBuilder(text).reverse().toString();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == -1);
    }

    /**
     * Metamorphic Relation 39: Searching for a pattern in an empty text should always result in not
     * finding the pattern.
     * 
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(String pattern) {
        String emptyText = "";
        /* Get follow-up output */
        int follow_res = Boyer.indexOf(emptyText, pattern);

        /* Verification */
        assertTrue(follow_res == -1);
    }

    /**
     * Metamorphic Relation 40: Searching for a pattern in a text with all characters replaced with
     * a different character should result in not finding the pattern.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(String text, String pattern) {
        /* Get follow-up output */
        String follow_text = text.replaceAll(".", "x");

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == -1);
    }

    /**
     * Metamorphic Relation 41: Searching for a pattern in a text with characters scrambled should
     * result in not finding the pattern.
     *
     * Error
     * 
     * @param text
     * @param pattern
     */
    // @ParameterizedTest
    // @MethodSource("testcaseProvider")
    // public void test41(String text, String pattern) {
    // /* Get follow-up output */
    // String follow_text = new String(text.chars().mapToObj(c -> String.valueOf((char)
    // c)).sorted().toArray(String[]::new));

    // /* Get follow-up output */
    // int follow_res = Boyer.indexOf(follow_text, pattern);

    // /* Verification */
    // assertTrue(follow_res == -1);
    // }

    /**
     * Metamorphic Relation 42: Searching for a pattern in a text with parts of the pattern removed
     * should result in not finding the pattern.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test42(String text, String pattern) {
        /* Get follow-up output */
        String follow_text = text.replace(pattern, "");

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == -1);
    }

    /**
     * Metamorphic Relation 43: If the pattern is not found in the original text, replacing a
     * portion of the text with the pattern itself should result in finding the pattern.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test43(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Replace a portion of the original text with the pattern */
        String follow_text = text.replace(text.substring(2, 5), pattern);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res != -1);
    }

    /**
     * Metamorphic Relation 44: Searching for a pattern in a text with additional arbitrary
     * characters inserted should not affect the result.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test44(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Insert additional arbitrary characters into the original text */
        String follow_text = text.substring(0, 3) + "xyz" + text.substring(3);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 45: Searching for a pattern in a text with a repeated substring should
     * yield the same result.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test45(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Repeat a substring in the original text */
        String follow_text = text + text.substring(2, 5);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 46: Replacing the pattern within the text with a permutation of the
     * pattern should not affect the result.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test46(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        // Construct follow-up input with a permutation of the pattern
        char[] charArray = pattern.toCharArray();
        // Perform permutation
        for (int i = 0; i < charArray.length; i++) {
            char temp = charArray[i];
            int randomIndex = (int) (Math.random() * charArray.length);
            charArray[i] = charArray[randomIndex];
            charArray[randomIndex] = temp;
        }
        String follow_pattern = new String(charArray);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 47: Adding extra occurrences of the last character of the pattern to the
     * text should not affect the result.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test47(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        // Construct follow-up input with extra occurrences of the last character of the pattern
        char lastChar = pattern.charAt(pattern.length() - 1);
        String follow_text = text + lastChar + lastChar;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 48: Adding a prefix and a suffix to the pattern should not affect the
     * search result.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test48(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        // Construct follow-up input with a prefix and a suffix added to the pattern
        String follow_pattern = "x" + pattern + "y";

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 49: If the pattern is found in the original text, repeating the pattern
     * within the text should result in finding the pattern at multiple indices.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test49(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        // Repeat the pattern within the original text
        String follow_text = text + pattern + text + pattern;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res != -1 && follow_res != origin_res);
    }

    /**
     * Metamorphic Relation 50: Replacing spaces within the text or pattern with a different
     * character should yield the same result.
     * 
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test50(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        // Replace spaces with a different character within the original text and pattern
        String follow_text = text.replace(' ', '-');
        String follow_pattern = pattern.replace(' ', '-');

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    static Stream<Arguments> testcaseProvider() {
        return Stream.of(Arguments.of("abcdefg", "abc"), Arguments.of("abcdefg", "xyz"));
    }
}
