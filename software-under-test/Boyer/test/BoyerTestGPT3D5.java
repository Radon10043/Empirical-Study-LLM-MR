package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.IOException;
import java.util.Collections;
import java.util.stream.Stream;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import src.Boyer;

public class BoyerTestGPT3D5 {
    /**
     * Metamorphic Relation 1: Reverse the origin string, the output of the algorithm
     * should be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = new StringBuilder(text).reverse().toString();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertEquals(origin_res, follow_res);
    }

    /**
     * Metamorphic Relation 2: Add a character to the end of the origin pattern, the
     * output of the algorithm should be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = pattern + "x";

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertEquals(-1, follow_res);
    }
    /**
     * Metamorphic Relation 3: Replace all occurrences of a particular character
     * in the origin string with another character, the output of the algorithm
     * should be the same or -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        char oldChar = 'a';
        char newChar = 'x';
        String follow_text = text.replace(oldChar, newChar);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res || follow_res == -1);
    }

    /**
     * Metamorphic Relation 4: Append the origin pattern to the origin string, 
     * the output of the algorithm should be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text + pattern;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertEquals(-1, follow_res);
    }
    /**
     * Metamorphic Relation 5: Insert the origin string into another string as a substring,
     * the output of the algorithm should be the same or the first occurrence index in the
     * follow-up string minus the length of the inserted original string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        StringBuilder follow_text_builder = new StringBuilder("xyz");
        follow_text_builder.insert(1, text);
        String follow_text = follow_text_builder.toString();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res || follow_res == (origin_res == -1 ? -1 : follow_res - text.length()));
    }

    /**
     * Metamorphic Relation 6: Swap the position of two distinct characters in the origin string,
     * the output of the algorithm should be the same or -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        int index1 = text.indexOf('a');
        int index2 = text.indexOf('b');
        if (index1 != -1 && index2 != -1) {
            char[] charArray = text.toCharArray();
            char temp = charArray[index1];
            charArray[index1] = charArray[index2];
            charArray[index2] = temp;
            String follow_text = new String(charArray);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(follow_text, pattern);

            /* Verification */
            assertTrue(follow_res == origin_res || follow_res == -1);
        }
    }

    /**
     * Metamorphic Relation 7: Change the case of all characters in the origin string,
     * the output of the algorithm should be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text.toUpperCase();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertEquals(origin_res, follow_res);
    }

    /**
     * Metamorphic Relation 8: Add a prefix to the pattern, the output of the algorithm should be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = "abc" + pattern;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertEquals(-1, follow_res);
    }
    /**
     * Metamorphic Relation 9: Change the position of a character in the pattern,
     * the output of the algorithm should be the same or -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        char[] charArray = pattern.toCharArray();
        if (charArray.length > 1) {
            char temp = charArray[0];
            charArray[0] = charArray[charArray.length - 1];
            charArray[charArray.length - 1] = temp;
            String follow_pattern = new String(charArray);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, follow_pattern);

            /* Verification */
            assertTrue(follow_res == origin_res || follow_res == -1);
        }
    }

    /**
     * Metamorphic Relation 10: Truncate the origin string by removing all occurrences
     * of the pattern, the output of the algorithm should be the same or -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text.replace(pattern, "");

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res || follow_res == -1);
    }
    /**
     * Metamorphic Relation 11: Repeat the origin pattern, the output of the algorithm 
     * should be the same or an index that is a multiple of the original pattern length.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = pattern + pattern;

            /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res || (follow_res % pattern.length() == 0));
    }

    /**
     * Metamorphic Relation 12: Prepend, append, or insert the pattern into the origin string,
     * the output of the algorithm should be the same or -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        char[] textCharArray = text.toCharArray();
        char[] patternCharArray = pattern.toCharArray();
        int textLength = textCharArray.length;
        int patternLength = patternCharArray.length;

        // Construct follow-up input by prepending pattern to text
        char[] followPrependCharArray = new char[textLength + patternLength];
        System.arraycopy(patternCharArray, 0, followPrependCharArray, 0, patternLength);
        System.arraycopy(textCharArray, 0, followPrependCharArray, patternLength, textLength);
        String followPrependText = new String(followPrependCharArray);

        // Construct follow-up input by appending pattern to text
        char[] followAppendCharArray = new char[textLength + patternLength];
        System.arraycopy(textCharArray, 0, followAppendCharArray, 0, textLength);
        System.arraycopy(patternCharArray, 0, followAppendCharArray, textLength, patternLength);
        String followAppendText = new String(followAppendCharArray);

        // Construct follow-up input by inserting pattern into text
        char[] followInsertCharArray = new char[textLength + patternLength];
        System.arraycopy(textCharArray, 0, followInsertCharArray, 0, textLength / 2);
        System.arraycopy(patternCharArray, 0, followInsertCharArray, textLength / 2, patternLength);
        System.arraycopy(textCharArray, textLength / 2, followInsertCharArray, textLength / 2 + patternLength, textLength - textLength / 2);
        String followInsertText = new String(followInsertCharArray);

        /* Get follow-up outputs */
        int followPrependRes = Boyer.indexOf(followPrependText, pattern);
        int followAppendRes = Boyer.indexOf(followAppendText, pattern);
        int followInsertRes = Boyer.indexOf(followInsertText, pattern);

        /* Verification */
        assertTrue(followPrependRes == origin_res || followPrependRes == -1);
        assertTrue(followAppendRes == origin_res || followAppendRes == -1);
        assertTrue(followInsertRes == origin_res || followInsertRes == -1);
    }
    /**
     * Metamorphic Relation 13: Modify the case of characters in the pattern,
     * the output of the algorithm should be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = pattern.toUpperCase();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertEquals(origin_res, follow_res);
    }

    /**
     * Metamorphic Relation 14: Repeat the origin string, the output of the algorithm 
     * should be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text + text;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertEquals(origin_res, follow_res);
    }
    /**
     * Metamorphic Relation 15: Repeat the origin pattern n times, the output of the algorithm 
     * should be the same or the index should be n times the original occurrence.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String text, String pattern) {
        int n = 3; // Number of times to repeat the pattern
        int origin_res = Boyer.indexOf(text, pattern);

        // Construct follow-up input
        String follow_pattern = String.join("", Collections.nCopies(n, pattern));

        // Get follow-up output
        int follow_res = Boyer.indexOf(text, follow_pattern);

        // Verification
        assertTrue(follow_res == origin_res || follow_res == (origin_res * n));
    }

    /**
     * Metamorphic Relation 16: Remove all occurrences of a particular character
     * in the origin pattern, the output of the algorithm should be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        char removedChar = 'a'; // Character to be removed
        String follow_pattern = pattern.replace(String.valueOf(removedChar), "");

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertEquals(-1, follow_res);
    }
    /**
     * Metamorphic Relation 17: Add a suffix to the origin pattern, the output of the algorithm 
     * should be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = pattern + "xyz"; // Suffix added to the pattern

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertEquals(-1, follow_res);
    }

    /**
     * Metamorphic Relation 18: Add the origin pattern to the origin string, 
     * the output of the algorithm should be the origin text length minus the pattern length.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text + pattern;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertEquals(text.length() - pattern.length(), follow_res);
    }
    /**
     * Metamorphic Relation 19: Replace all occurrences of a substring in the origin string 
     * with another substring, the output of the algorithm should be the same or -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String replacedText = text.replace("abc", "xyz"); // Replace "abc" with "xyz" in the text

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(replacedText, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res || follow_res == -1);
    }

    /**
     * Metamorphic Relation 20: Modify the origin string by repeating a substring,
     * the output of the algorithm should be the same or a multiple of the original occurrence.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String repeatedText = text + pattern + text; // Repeat the pattern in the text

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(repeatedText, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res || (follow_res % pattern.length() == 0));
    }
    /**
     * Metamorphic Relation 21: Convert the origin string to uppercase, the output of the
     * algorithm should be the same or the first occurrence index of the original pattern.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text.toUpperCase();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res || follow_res == pattern.indexOf(text));
    }

    /**
     * Metamorphic Relation 22: Replace all occurrences of a particular substring
     * in the origin string with another substring, the output of the algorithm should
     * be the same or -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text.replace("abc", "def"); // Replace "abc" with "def" in the text

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res || follow_res == -1);
    }
    /**
     * Metamorphic Relation 23: Reverse the origin pattern, the output of the algorithm 
     * should be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = new StringBuilder(pattern).reverse().toString();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertEquals(origin_res, follow_res);
    }

    /**
     * Metamorphic Relation 24: Add a prefix to the origin string, the output of the 
     * algorithm should be the same or greater.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = "xyz" + text; // Add a prefix "xyz" to the text

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res >= origin_res);
    }
    /**
     * Metamorphic Relation 25: Modify the origin string by inserting the pattern at the beginning,
     * the output of the algorithm should be the same or the first occurrence index plus the pattern length.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = "123" + pattern + text; // Insert the pattern at the beginning of the text

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res || follow_res == (origin_res + pattern.length()));
    }

    /**
     * Metamorphic Relation 26: Remove all occurrences of the pattern in the origin string,
     * the output of the algorithm should be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text.replace(pattern, ""); // Remove all occurrences of the pattern in the text

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertEquals(-1, follow_res);
    }
    /**
     * Metamorphic Relation 27: Add a suffix to the origin string, the output of the algorithm 
     * should be the same or greater.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text + "xyz"; // Add a suffix "xyz" to the text

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res >= origin_res);
    }

    /**
     * Metamorphic Relation 28: Modify the case of characters in the origin string,
     * the output of the algorithm should be the same or the first occurrence index of the original pattern.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text.toUpperCase();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res || follow_res == text.indexOf(pattern));
    }
    /**
     * Metamorphic Relation 29: Add a suffix to the origin pattern, the output of the algorithm 
     * should still be the first occurrence index of the original pattern.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);
        
        /* Construct follow-up input */
        String follow_pattern = pattern + "xyz"; // Add a suffix "xyz" to the pattern

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertEquals(origin_res, follow_res);
    }

    /**
     * Metamorphic Relation 30: Modify the origin string by repeating the pattern,
     * the output of the algorithm should be the same or a multiple of the original index.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);
        
        /* Construct follow-up input */
        String follow_text = text + pattern + text; // Repeat the pattern in the text

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res || (follow_res % origin_res == 0));
    }
    /**
     * Metamorphic Relation 31: Rotate the origin pattern, the output of the algorithm 
     * should be the same or -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        int n = pattern.length();

        // Construct follow-up input by rotating the pattern
        String follow_pattern = pattern.substring(1, n) + pattern.charAt(0);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res || follow_res == -1);
    }

    /**
     * Metamorphic Relation 32: Remove all occurrences of a particular substring in the origin string, 
     * the output of the algorithm should be the same or -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        // Construct follow-up input by replacing the pattern with an empty string
        String follow_text = text.replace(pattern, "");

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res || follow_res == -1);
    }
    /**
     * Metamorphic Relation 33: Insert the origin string into another string as a substring, 
     * the output of the algorithm should be the same or greater.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        StringBuilder followTextBuilder = new StringBuilder("xyz");
        followTextBuilder.insert(1, text);
        String followText = followTextBuilder.toString();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(followText, pattern);

        /* Verification */
        assertTrue(follow_res >= origin_res);
    }

    /**
     * Metamorphic Relation 34: Swap the position of two distinct characters in the pattern, 
     * the output of the algorithm should be the same or -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        char[] patternArray = pattern.toCharArray();
        int length = patternArray.length;

        if (length > 1) {
            // Swap the first and last characters
            char temp = patternArray[0];
            patternArray[0] = patternArray[length - 1];
            patternArray[length - 1] = temp;
            String followPattern = new String(patternArray);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, followPattern);

            /* Verification */
            assertTrue(follow_res == origin_res || follow_res == -1);
        }
    }
    /**
     * Metamorphic Relation 35: Modify the origin pattern by inserting a character at the beginning,
     * the output of the algorithm should be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (pattern.length() > 0) {
            /* Construct follow-up input by inserting a character at the beginning of the pattern */
            String follow_pattern = "x" + pattern;

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, follow_pattern);

            /* Verification */
            assertEquals(-1, follow_res);
        }
    }

    /**
     * Metamorphic Relation 36: Modify the origin text by removing the pattern,
     * the output of the algorithm should be the same or -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input by removing the pattern from the text */
        String follow_text = text.replace(pattern, "");

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res || follow_res == -1);
    }

    /**
     * Metamorphic Relation 37: Modify the origin pattern by removing the first character, 
     * the output of the algorithm should be the same or -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (pattern.length() > 0) {
            /* Construct follow-up input by removing the first character of the pattern */
            String follow_pattern = pattern.substring(1);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, follow_pattern);

            /* Verification */
            assertTrue(follow_res == origin_res || follow_res == -1);
        }
    }

    /**
     * Metamorphic Relation 38: Modify the origin text by repeating the pattern n times,
     * the output of the algorithm should be the same or a multiple of the original index, n times.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(String text, String pattern) {
        int n = 3; // Number of times to repeat the pattern
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text + String.join("", Collections.nCopies(n, pattern));

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res || follow_res == (origin_res * n));
    }

    /**
     * Metamorphic Relation 39: Modify the origin pattern by adding a unique character at the end, 
     * the output of the algorithm should be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input by adding a unique character at the end of the pattern */
        char uniqueChar = 'x'; // Unique character
        String follow_pattern = pattern + uniqueChar;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertEquals(-1, follow_res);
    }

    /**
     * Metamorphic Relation 40: Add a prefix and a suffix to the origin pattern, the output 
     * of the algorithm should be the same or the first occurrence index minus the prefix length.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input by adding a prefix and a suffix to the pattern */
        String follow_pattern = "abc" + pattern + "xyz"; // Prefix "abc" and suffix "xyz"

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res || follow_res == (origin_res == -1 ? -1 : follow_res - "abc".length()));
    }

    static Stream<Arguments> testcaseProvider() throws IOException {
        return testcaseGenerator.generate_ss(1000);
    }
}
