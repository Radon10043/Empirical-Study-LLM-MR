package test;

import static org.junit.Assume.assumeTrue;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.io.IOException;
import java.util.stream.Stream;
import org.apache.commons.lang3.RandomStringUtils;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import src.Boyer;

public class BoyerTestGPT3D5NoSystem {
    /**
     * Metamorphic Relation 3: If the pattern occurred in the original text, when reversing the pattern,
     * the output should be the same as the original output.
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
        String reverse_pattern = new StringBuilder(pattern).reverse().toString();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, reverse_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 4: If the pattern occurred in the original text, when changing all characters
     * in the pattern to uppercase, the output should be the same as the original output.
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
        String uppercase_pattern = pattern.toUpperCase();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, uppercase_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 5: If the pattern occurred in the original text, swapping the positions
     * of two characters in the pattern should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (pattern.length() < 2) {
            return;
        }

        /* Construct follow-up input */
        char[] charArray = pattern.toCharArray();
        char temp = charArray[0];
        charArray[0] = charArray[1];
        charArray[1] = temp;
        String swapped_pattern = new String(charArray);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, swapped_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 6: If the pattern occurred in the original text, doubling the pattern
     * should result in the same output as the original pattern.
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
        String doubled_pattern = pattern + pattern;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, doubled_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 7: If the pattern occurred in the original text, when removing all occurrences
     * of a specific character from the pattern, the output should be the same as the original output.
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
        String follow_pattern = pattern.replace("e", "");

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 8: If the pattern occurred in the original text, when changing all characters
     * in the text to uppercase, the output should be the same as the original output.
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
        String uppercase_text = text.toUpperCase();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(uppercase_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 9: If the pattern occurred in the original text, when replacing the pattern
     * with another pattern of the same length, the output should be the same position offset by the
     * difference in the patterns.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (pattern.length() < 2) {
            return;
        }

        /* Construct follow-up input */
        char[] charArray = pattern.toCharArray();
        char temp = charArray[0];
        charArray[0] = charArray[1];
        charArray[1] = temp;
        String replaced_pattern = new String(charArray);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, replaced_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res + 1 || follow_res == origin_res - 1);
    }

    /**
     * Metamorphic Relation 10: If the pattern occurred in the original text, when the same pattern is repeated
     * several times at the end of the text, it should still return the same pattern index.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text + pattern + pattern + pattern;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 11: If the pattern occurred in the original text, when the text is empty,
     * the output should always be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = "";

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == -1);
    }

    /**
     * Metamorphic Relation 12: When searching for an empty pattern in the text, the output should always be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (pattern.isEmpty()) {
            return;
        }

        /* Construct follow-up input */
        String follow_pattern = "";

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == 0);
    }

    /**
     * Metamorphic Relation 13: If the pattern occurred in the original text, when providing the pattern
     * as the text, the output should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(pattern, pattern);

        /* Verification */
        assertTrue(follow_res == 0);
    }

    /**
     * Metamorphic Relation 14: When the pattern is not found within the text, the output should be -1
     * for both the original and follow-up input.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(String text, String pattern) {
        if (text.indexOf(pattern) != -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, pattern);

        /* Verification */
        assertTrue(follow_res == -1 && origin_res == -1);
    }

    /**
     * Metamorphic Relation 15: If the pattern is longer than the text, the output should always be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String text, String pattern) {
        if (pattern.length() <= text.length()) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Verification */
        assertEquals(-1, origin_res);
    }

    /**
     * Metamorphic Relation 16: If the text and pattern are empty strings, the output should always be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16() {
        String text = "";
        String pattern = "";

        /* Get output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Verification */
        assertEquals(0, origin_res);
    }

    /**
     * Metamorphic Relation 17: If the pattern occurred in the original text, when using a null pattern,
     * the output should always be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, null);

        /* Verification */
        assertTrue(follow_res == -1);
    }

    /**
     * Metamorphic Relation 18: If the pattern occurred in the original text, when using a null text,
     * the output should always be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String text, String pattern) {   // Fixed
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Get follow-up output */
        text = null;
        int follow_res = Boyer.indexOf(text, pattern);

        /* Verification */
        assertTrue(follow_res == -1);
    }

    /**
     * Metamorphic Relation 19: If the pattern occurred in the original text, when using empty pattern,
     * the output should always be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, "");

        /* Verification */
        assertTrue(follow_res == 0);
    }

    /**
     * Metamorphic Relation 20: If the pattern occurred in the original text, when using empty text,
     * the output should always be -1.
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
        int follow_res = Boyer.indexOf("", pattern);

        /* Verification */
        assertTrue(follow_res == -1);
    }

    /**
     * Metamorphic Relation 21: If the pattern occurred in the original text, when using the same text and pattern,
     * the output should always be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, text);

        /* Verification */
        assertTrue(follow_res == 0);
    }

    /**
     * Metamorphic Relation 22: If the pattern occurred in the original text, when using the same text and pattern but reversed,
     * the output should always be -1 as the reversed pattern will not be found in the original text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Get follow-up output */
        String reversedPattern = new StringBuilder(pattern).reverse().toString();
        int follow_res = Boyer.indexOf(text, reversedPattern);

        /* Verification */
        assertTrue(follow_res == -1);
    }

    /**
     * Metamorphic Relation 23: If the pattern occurred in the original text, the output should be the same when using space padded
     * patterns compared to the original pattern.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Get follow-up output */
        String paddedPattern = " " + pattern + " ";
        int follow_res = Boyer.indexOf(text, paddedPattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 24: If the pattern occurred in the original text, when the pattern is padded with extra characters,
     * the output should be unaltered.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Get follow-up output */
        String paddedPattern = "z" + pattern + "z";
        int follow_res = Boyer.indexOf(text, paddedPattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 25: If the pattern occurred in the original text, replacing all occurrences of a specific character
     * in the text with a different character should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text.replace('t', 'x');

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 26: If the pattern occurred in the original text, reversing the order of the characters in the text
     * should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = new StringBuilder(text).reverse().toString();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 27: If the pattern occurred in the original text, appending the pattern to the end of the text should increase
     * the output index by the length of the original text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text + pattern;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertEquals(follow_res, origin_res + text.length());
    }

    /**
     * Metamorphic Relation 28: If the pattern occurred in the original text, prepending the text to the beginning of the pattern
     * should not change the output as long as the pattern remains matching the original text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_pattern = text + pattern;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 29: If the pattern occurred in the original text, when a single character is duplicated within the pattern,
     * the output should still be the same as the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(String text, String pattern) {   // Fixed
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        if (pattern.length() < 2) {
            return;
        }

        /* Construct follow-up input */
        String follow_pattern = new String();
        follow_pattern += pattern.charAt(0);
        follow_pattern += pattern.charAt(0);
        follow_pattern +=pattern.substring(1);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 30: If the pattern occurred in the original text, when reversing the pattern and the text,
     * the output should remain the same as the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String reversePattern = new StringBuilder(pattern).reverse().toString();
        String reverseText = new StringBuilder(text).reverse().toString();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(reverseText, reversePattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 31: If the pattern occurred in the original text, when using a text with all characters repeated within the original text,
     * the output should remain the same as the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text.replaceAll("(.)", "$1$1");

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 32: If the pattern occurred in the original text, when replacing the first occurrence of the pattern with another
     * pattern of the same length, the output should be the same as the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(String text, String pattern) {   // Fixed
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        StringBuilder follow_text = new StringBuilder(text);
        String another_pattern = RandomStringUtils.randomAscii(pattern.length());
        follow_text.replace(follow_text.indexOf(pattern), follow_text.indexOf(pattern) + pattern.length(), another_pattern);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text.toString(), pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 33: If the pattern occurred in the original text, when replacing the last occurrence of the pattern with another
     * pattern of the same length, the output should be the same as the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(String text, String pattern) {   // Fixed
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        StringBuilder follow_text = new StringBuilder(text);
        String another_pattern = RandomStringUtils.randomAscii(pattern.length());
        int lastIndex = follow_text.lastIndexOf(pattern);
        follow_text.replace(lastIndex, lastIndex + pattern.length(), another_pattern);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text.toString(), pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 34: If the pattern occurred in the original text, when using a text with all occurrences of the pattern replaced
     * with empty string, the output should be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text.replaceAll(pattern, "");

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertEquals(-1, follow_res);
    }

    /**
     * Metamorphic Relation 35: If the text is empty, the output should be -1 regardless of the pattern.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35() {
        String text = "";
        String pattern = "test";
        assertEquals(-1, Boyer.indexOf(text, pattern));
    }

    /**
     * Metamorphic Relation 36: If the pattern is empty, the output should always be 0 regardless of the text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(String text) {
        String pattern = "";
        assertEquals(0, Boyer.indexOf(text, pattern));
    }

    /**
     * Metamorphic Relation 37: If the specified pattern is not found within the text, changing the pattern to a different string 
     * should result in the same output of -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(String text, String pattern) {    // Fixed
        assumeTrue(text.indexOf(pattern) == -1);

        StringBuilder sb = new StringBuilder(pattern);
        if (sb.charAt(0) == 'a') {
            sb.setCharAt(0, 'b');
        } else {
            sb.setCharAt(0, 'a');
        }
        pattern = sb.toString();

        assertEquals(-1, Boyer.indexOf(text, pattern));
    }

    /**
     * Metamorphic Relation 38: If the given pattern is not found within the text, changing the text to a different string 
     * should result in the same output of -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(String text, String pattern) {    // Fixed
        assumeTrue(text.indexOf(pattern) == -1);

        StringBuilder sb = new StringBuilder(text);
        if (sb.charAt(0) == 'a') {
            sb.setCharAt(0, 'b');
        } else {
            sb.setCharAt(0, 'a');
        }
        text = sb.toString();

        assertEquals(-1, Boyer.indexOf(text, pattern));
    }

    /**
     * Metamorphic Relation 39: If the pattern occurs more than once in the original text, removing a single occurrence of the pattern 
     * should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(String text, String pattern) {   // Fixed
        text = text + pattern + pattern;
        int origin_res = Boyer.indexOf(text, pattern);
        String follow_text = text.replaceFirst(pattern, "");
        int follow_res = Boyer.indexOf(follow_text, pattern);
        assertEquals(origin_res, follow_res);
    }

    /**
     * Metamorphic Relation 40: If the pattern occurred in the original text, changing the text to have a different number of occurrences 
     * of the pattern should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(String text, String pattern) {   // Fixed
        assumeTrue(text.indexOf(pattern) != -1);
        int origin_res = Boyer.indexOf(text, pattern);
        String follow_text = text + pattern;
        int follow_res = Boyer.indexOf(follow_text, pattern);
        assertEquals(origin_res, follow_res);
    }

    /**
     * Metamorphic Relation 41: If the pattern occurred in the original text, when prepending and appending special characters to the text, 
     * the output should remain the same as the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test41(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get original output */
        int originalOutput = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String followUpText = "!" + text + "!";

        /* Get follow-up output */
        int followUpOutput = Boyer.indexOf(followUpText, pattern);

        /* Verification */
        assertEquals(originalOutput, followUpOutput);
    }

    /**
     * Metamorphic Relation 42: If the pattern occurred in the original text, replacing all instances of a character in the pattern with a different character 
     * should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test42(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get original output */
        int originalOutput = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        char charToBeReplaced = pattern.charAt(0);
        char replacementChar = 'x';
        String followUpPattern = pattern.replace(charToBeReplaced, replacementChar);

        /* Get follow-up output */
        int followUpOutput = Boyer.indexOf(text, followUpPattern);

        /* Verification */
        assertEquals(originalOutput, followUpOutput);
    }

    static Stream<Arguments> testcaseProvider() throws IOException {
        return testcaseGenerator.generate_ss(1000);
    }
}