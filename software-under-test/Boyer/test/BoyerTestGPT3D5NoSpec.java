package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import src.Boyer;

public class BoyerTestGPT3D5NoSpec {
    /**
     * Metamorphic Relation 3: If the pattern occurred in the original text, when reversing the pattern,
     * the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int originRes = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String followPattern = new StringBuilder(pattern).reverse().toString();

        /* Get follow-up output */
        int followRes = Boyer.indexOf(text, followPattern);

        /* Verification */
        assertEquals(originRes, followRes);
    }

    /**
     * Metamorphic Relation 4: If the pattern occurred in the original text, when changing all characters
     * to uppercase in the pattern, the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int originRes = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String followPattern = pattern.toUpperCase();

        /* Get follow-up output */
        int followRes = Boyer.indexOf(text, followPattern);

        /* Verification */
        assertEquals(originRes, followRes);
    }

    /**
     * Metamorphic Relation 5: If the pattern occurred in the original text, when changing all characters
     * to lowercase in the pattern, the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int originRes = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String followPattern = pattern.toLowerCase();

        /* Get follow-up output */
        int followRes = Boyer.indexOf(text, followPattern);

        /* Verification */
        assertEquals(originRes, followRes);
    }

    /**
     * Metamorphic Relation 6: If the pattern occurred in the original text, when replacing a character
     * with another character in the pattern, the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int originRes = Boyer.indexOf(text, pattern);

        if (pattern.length() < 2) {
            return; // Not enough characters to perform replacement
        }

        char replacementChar = (char) (pattern.charAt(0) + 1);

        /* Construct follow-up input */
        String followPattern = pattern.replace(pattern.charAt(0), replacementChar);

        /* Get follow-up output */
        int followRes = Boyer.indexOf(text, followPattern);

        /* Verification */
        assertEquals(originRes, followRes);
    }

    /**
     * Metamorphic Relation 7: If the pattern occurred in the original text, when doubling the pattern by
     * concatenating it with itself, the output should remain the same or increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int originRes = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String followPattern = pattern + pattern;

        /* Get follow-up output */
        int followRes = Boyer.indexOf(text, followPattern);

        /* Verification */
        assertTrue(followRes == originRes || followRes > originRes);
    }

    /**
     * Metamorphic Relation 8: If the pattern occurred in the original text, when replacing the pattern with
     * a substring of the text, the output should remain the same or decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int originRes = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String followPattern = text.substring(0, pattern.length());

        /* Get follow-up output */
        int followRes = Boyer.indexOf(text, followPattern);

        /* Verification */
        assertTrue(followRes == originRes || followRes < originRes);
    }

    /**
     * Metamorphic Relation 9: If the pattern occurred in the original text, when the text is reversed,
     * the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int originRes = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String followText = new StringBuilder(text).reverse().toString();

        /* Get follow-up output */
        int followRes = Boyer.indexOf(followText, pattern);

        /* Verification */
        assertEquals(originRes, followRes);
    }

    /**
     * Metamorphic Relation 10: If the pattern occurred in the original text, when the pattern is repeated,
     * the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int originRes = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String followPattern = pattern + pattern + pattern;

        /* Get follow-up output */
        int followRes = Boyer.indexOf(text, followPattern);

        /* Verification */
        assertEquals(originRes, followRes);
    }

    /**
     * Metamorphic Relation 11: If the pattern occurred in the original text, when the pattern is appended at
     * the beginning of the text, the output should remain the same or increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int originRes = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String followText = pattern + text;

        /* Get follow-up output */
        int followRes = Boyer.indexOf(followText, pattern);

        /* Verification */
        assertTrue(followRes == originRes || followRes > originRes);
    }

    /**
     * Metamorphic Relation 12: If the pattern occurred in the original text, when the pattern is replaced
     * with a different pattern, the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int originRes = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String followPattern = "different";

        /* Get follow-up output */
        int followRes = Boyer.indexOf(text, followPattern);

        /* Verification */
        assertEquals(originRes, followRes);
    }

    /**
     * Metamorphic Relation 13: If the pattern did not occur in the original text, when the text is doubled
     * by concatenating it with itself, the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(String text, String pattern) {
        if (text.indexOf(pattern) != -1) {
            return;
        }

        /* Get origin output */
        int originRes = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String followText = text + text;

        /* Get follow-up output */
        int followRes = Boyer.indexOf(followText, pattern);

        /* Verification */
        assertEquals(originRes, followRes);
    }

    /**
     * Metamorphic Relation 14: If the pattern did not occur in the original text, when the pattern is
     * repeated, the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(String text, String pattern) {
        if (text.indexOf(pattern) != -1) {
            return;
        }

        /* Get origin output */
        int originRes = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String followPattern = pattern + pattern + pattern;

        /* Get follow-up output */
        int followRes = Boyer.indexOf(text, followPattern);

        /* Verification */
        assertEquals(originRes, followRes);
    }

    /**
     * Metamorphic Relation 15: If the pattern did not occur in the original text, when the pattern is removed
     * from the text, the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String text, String pattern) {   // Fixed
        if (text.indexOf(pattern) != -1) {
            return;
        }

        /* Get origin output */
        int originRes = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String followText = text.replace(pattern, "");

        /* Get follow-up output */
        int followRes = Boyer.indexOf(followText, pattern);

        /* Verification */
        assertEquals(originRes, followRes);
    }

    /**
     * Metamorphic Relation 16: If the pattern did not occur in the original text, when the pattern is appended
     * at the end of the text, the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(String text, String pattern) {
        if (text.indexOf(pattern) != -1) {
            return;
        }

        /* Get origin output */
        int originRes = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String followText = text + pattern;

        /* Get follow-up output */
        int followRes = Boyer.indexOf(followText, pattern);

        /* Verification */
        assertEquals(originRes, followRes);
    }

    /**
     * Metamorphic Relation 17: If the pattern did not occur in the original text, when the pattern is replaced
     * with another pattern, the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String text, String pattern) {
        if (text.indexOf(pattern) != -1) {
            return;
        }

        /* Get origin output */
        int originRes = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String followPattern = "another_pattern";

        /* Get follow-up output */
        int followRes = Boyer.indexOf(text, followPattern);

        /* Verification */
        assertEquals(originRes, followRes);
    }

    /**
     * Metamorphic Relation 18: If the pattern is an empty string, the output should always be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String text, String pattern) {
        String emptyPattern = "";

        /* Get output for the empty pattern */
        int output = Boyer.indexOf(text, emptyPattern);

        /* Verification */
        assertEquals(0, output);
    }

    /**
     * Metamorphic Relation 19: If the pattern occurred in the original text, when the text is an empty string,
     * the output should always be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String text, String pattern) {
        String emptyText = "";

        if (emptyText.equals(text) || emptyText.indexOf(pattern) != -1) {
            return;
        }

        /* Get output for the empty text */
        int output = Boyer.indexOf(emptyText, pattern);

        /* Verification */
        assertEquals(-1, output);
    }

    /**
     * Metamorphic Relation 20: If the pattern did not occur in the original text, when the text is an empty string,
     * the output should always be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(String text, String pattern) {
        String emptyText = "";

        if (emptyText.equals(text) || text.indexOf(pattern) != -1) {
            return;
        }

        /* Get output for the empty text */
        int output = Boyer.indexOf(emptyText, pattern);

        /* Verification */
        assertEquals(-1, output);
    }

    /**
     * Metamorphic Relation 21: If the pattern is longer than the text, the output should always be -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(String text, String pattern) {
        if (pattern.length() <= text.length() || text.indexOf(pattern) != -1) {
            return;
        }

        /* Get output when pattern is longer than the text */
        int output = Boyer.indexOf(text, pattern);

        /* Verification */
        assertEquals(-1, output);
    }

    /**
     * Metamorphic Relation 22: If the pattern and text are both empty strings, the output should always be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(String text, String pattern) {
        String emptyText = "";
        String emptyPattern = "";

        if (emptyText.equals(text) || emptyPattern.equals(pattern)) {
            return;  // Skip if text or pattern is not empty
        }

        /* Get output for both empty text and pattern */
        int output = Boyer.indexOf(emptyText, emptyPattern);

        /* Verification */
        assertEquals(0, output);
    }

    /**
     * Metamorphic Relation 23: If the pattern is not found in the text, then reversing both the pattern and the text
     * should not affect the output (i.e., still not found).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(String text, String pattern) {
        if (text.indexOf(pattern) != -1) {
            return;
        }

        /* Get original output */
        int originalOutput = Boyer.indexOf(text, pattern);

        /* Construct follow-up input by reversing both the text and the pattern */
        String reversedText = new StringBuilder(text).reverse().toString();
        String reversedPattern = new StringBuilder(pattern).reverse().toString();

        /* Get follow-up output */
        int followUpOutput = Boyer.indexOf(reversedText, reversedPattern);

        /* Verification */
        assertEquals(originalOutput, followUpOutput);
    }

    /**
     * Metamorphic Relation 24: If the pattern is not found in the text, replacing all occurrences of a character
     * in the pattern with a different character should not affect the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(String text, String pattern) {
        if (text.indexOf(pattern) != -1) {
            return;
        }

        /* Get original output */
        int originalOutput = Boyer.indexOf(text, pattern);

        /* Replace all occurrences of a character in the pattern with a different character */
        String modifiedPattern = pattern.replace('a', 'b'); // Replace 'a' with 'b' for example

        /* Get follow-up output */
        int followUpOutput = Boyer.indexOf(text, modifiedPattern);

        /* Verification */
        assertEquals(originalOutput, followUpOutput);
    }

    /**
     * Metamorphic Relation 25: If the pattern is not found in the text, then replacing the first character in the pattern
     * with a different character should not affect the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(String text, String pattern) {
        if (text.indexOf(pattern) != -1) {
            return;
        }

        /* Get original output */
        int originalOutput = Boyer.indexOf(text, pattern);

        if (pattern.isEmpty()) {
            return; // Skip for empty pattern
        }

        /* Replace the first character in the pattern with a different character */
        char firstChar = pattern.charAt(0);
        char modifiedFirstChar = (char) (firstChar + 1); // Replace with next character for example
        String modifiedPattern = modifiedFirstChar + pattern.substring(1);

        /* Get follow-up output */
        int followUpOutput = Boyer.indexOf(text, modifiedPattern);

        /* Verification */
        assertEquals(originalOutput, followUpOutput);
    }

    /**
     * Metamorphic Relation 26: If the pattern is not found in the text, then if a character is appended to the beginning
     * of the pattern, the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(String text, String pattern) {
        if (text.indexOf(pattern) != -1) {
            return;
        }

        /* Get original output */
        int originalOutput = Boyer.indexOf(text, pattern);

        /* Construct follow-up input by appending a character to the beginning of the pattern */
        String modifiedPattern = "x" + pattern;

        /* Get follow-up output */
        int followUpOutput = Boyer.indexOf(text, modifiedPattern);

        /* Verification */
        assertEquals(originalOutput, followUpOutput);
    }

    /**
     * Metamorphic Relation 27: If the pattern is found at index i in the original text, then it should also be found
     * at (i + k) in the follow-up text, where k is the same for all occurrences of the pattern.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(String text, String pattern) {
        int k = 3; // This can be any positive number

        /* Retrieve the indices of the pattern in the original text */
        List<Integer> originalIndices = new ArrayList<>();
        int index = text.indexOf(pattern);
        while (index >= 0) {
            originalIndices.add(index);
            index = text.indexOf(pattern, index + 1);
        }

        /* Verify the occurrence of the pattern in the original text */
        assertTrue(!originalIndices.isEmpty());

        /* Construct follow-up input by adding k to all indices of the pattern in the original text */
        String followText = text + text;  // Concatenating text with itself for illustrative purposes
        List<Integer> followupIndices = new ArrayList<>();
        int followIndex = followText.indexOf(pattern);
        while (followIndex >= 0) {
            followupIndices.add(followIndex);
            followIndex = followText.indexOf(pattern, followIndex + 1);
        }

        /* Verify the occurrence of the pattern in the follow-up text */
        assertTrue(!followupIndices.isEmpty());

        /* Verification - check if indices in the follow-up match the expected */
        for (int i = 0; i < originalIndices.size(); i++) {
            assertEquals(originalIndices.get(i) + k, followupIndices.get(i));
        }
    }

    /**
     * Metamorphic Relation 28: If the pattern is not found in the text, then adding the pattern at the start and end
     * of the text should result in the pattern being found once in the follow-up text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(String text, String pattern) {
        if (text.indexOf(pattern) != -1) {
            return;
        }

        /* Construct follow-up input by adding the pattern at the beginning and end of the text */
        String followText = pattern + text + pattern;

        /* Get follow-up output */
        int followUpOutput = Boyer.indexOf(followText, pattern);

        /* Verification */
        assertEquals(text.length(), followUpOutput);
    }

    /**
     * Metamorphic Relation 29: If the pattern is found at index i in the original text, then the pattern will not be found
     * at index (i - m), where m is the length of the pattern.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(String text, String pattern) {
        /* Retrieve the indices of the pattern in the original text */
        List<Integer> originalIndices = new ArrayList<>();
        int index = text.indexOf(pattern);
        while (index >= 0) {
            originalIndices.add(index);
            index = text.indexOf(pattern, index + 1);
        }

        /* Verify the occurrence of the pattern in the original text */
        assertTrue(!originalIndices.isEmpty());

        /* Construct follow-up input by checking indices before the pattern */
        int patternLength = pattern.length();
        List<Integer> followupIndices = new ArrayList<>();
        for (int i : originalIndices) {
            if (i - patternLength >= 0) {
                followupIndices.add(i - patternLength);
            }
        }

        /* Verify the indices in the follow-up text are not found */
        for (int i : followupIndices) {
            assertFalse(text.substring(i, i + patternLength).equals(pattern));
        }
    }

    /**
     * Metamorphic Relation 30: If the pattern is found at index i in the original text, then the pattern will be found
     * at index i in the follow-up text consisting of the same text appended with itself.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(String text, String pattern) {
        /* Retrieve the indices of the pattern in the original text */
        List<Integer> originalIndices = new ArrayList<>();
        int index = text.indexOf(pattern);
        while (index >= 0) {
            originalIndices.add(index);
            index = text.indexOf(pattern, index + 1);
        }

        /* Verify the occurrence of the pattern in the original text */
        assertTrue(!originalIndices.isEmpty());

        /* Construct follow-up input by adding the same text to itself */
        String followText = text + text;

        /* Get follow-up output */
        List<Integer> followupIndices = new ArrayList<>();
        int followIndex = followText.indexOf(pattern);
        while (followIndex >= 0) {
            followupIndices.add(followIndex);
            followIndex = followText.indexOf(pattern, followIndex + 1);
        }

        /* Verify the occurrence of the pattern in the follow-up text */
        for (int i = 0; i < originalIndices.size(); i++) {
            assertTrue(followupIndices.contains(originalIndices.get(i) + text.length()));
        }
    }

    /**
     * Metamorphic Relation 31: If the pattern P is found in the original text T, then the pattern should also be found
     * in a subsequence of T.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(String text, String pattern) {   // Fixed
        /* Verify the occurrence of the pattern in the original text */
        if (text.indexOf(pattern) == -1) {
            return;
        }

        Boolean source_out = Boyer.indexOf(text, pattern) != -1;

        /* Construct a subsequence of the original text */
        int start = text.length() / 4;
        int end = text.length() * 3 / 4;
        String subsequence = text.substring(start, end);

        /* Get output for the subsequence */
        Boolean follow_out = Boyer.indexOf(subsequence, pattern) != -1;

        /* Verification */
        assertEquals(source_out, follow_out);  // The pattern should be found in the subsequence
    }

    /**
     * Metamorphic Relation 32: If the pattern P is found in the original text T, then the pattern should also be found
     * in a circularly shifted version of T.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(String text, String pattern) {
        /* Verify the occurrence of the pattern in the original text */
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Construct follow-up input by shifting the characters of the original text */
        String circularShiftedText = text.substring(1) + text.substring(0, 1);

        /* Get follow-up output */
        int circularShiftedOutput = Boyer.indexOf(circularShiftedText, pattern);

        /* Verification */
        assertTrue(circularShiftedOutput != -1);  // The pattern should be found in the circularly shifted text
    }

    /**
     * Metamorphic Relation 33: If the pattern P is found in the original text T, then swapping a pair of characters
     * in the pattern should not affect the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(String text, String pattern) {
        /* Verify the occurrence of the pattern in the original text */
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get original output */
        int originalOutput = Boyer.indexOf(text, pattern);

        if (pattern.length() < 2) {
            return; // Skip if the pattern length is less than 2
        }

        /* Swap a pair of characters in the pattern */
        int swapIndex = Math.min(1, pattern.length() - 2);
        char[] swappedPatternChars = pattern.toCharArray();
        char temp = swappedPatternChars[swapIndex];
        swappedPatternChars[swapIndex] = swappedPatternChars[swapIndex + 1];
        swappedPatternChars[swapIndex + 1] = temp;
        String swappedPattern = new String(swappedPatternChars);

        /* Get follow-up output */
        int followUpOutput = Boyer.indexOf(text, swappedPattern);

        /* Verification */
        assertEquals(originalOutput, followUpOutput);
    }

    /**
     * Metamorphic Relation 34: If the pattern P is found in the original text T, then adding or removing spaces
     * within the pattern should not affect the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(String text, String pattern) {
        /* Verify the occurrence of the pattern in the original text */
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get original output */
        int originalOutput = Boyer.indexOf(text, pattern);

        /* Add or remove spaces within the pattern */
        String modifiedPattern = pattern.replaceAll("\\s+", "");

        /* Get follow-up output */
        int followUpOutput = Boyer.indexOf(text, modifiedPattern);

        /* Verification */
        assertEquals(originalOutput, followUpOutput);
    }

    /**
     * Metamorphic Relation 35: If the pattern P is found in the original text T, then replacing the pattern with a longer
     * substring should result in the new substring also being found in the text at or after the original index.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(String text, String pattern) {
        /* Verify the occurrence of the pattern in the original text */
        int origIndex = Boyer.indexOf(text, pattern);
        if (origIndex < 0) {
            return;
        }

        /* Construct follow-up input by replacing the pattern with a longer substring */
        String longSubstring = "longsubstring";
        String followText = text.substring(0, origIndex) + longSubstring + text.substring(origIndex + pattern.length());

        /* Get follow-up output */
        int followIndex = Boyer.indexOf(followText, longSubstring);

        /* Verification */
        assertTrue(followIndex >= origIndex);
    }

    /**
     * Metamorphic Relation 36: If the pattern P is found in the original text T, then replacing the pattern with a shorter
     * substring should result in the new substring also being found in the text at or after the original index.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(String text, String pattern) {
        /* Verify the occurrence of the pattern in the original text */
        int origIndex = Boyer.indexOf(text, pattern);
        if (origIndex < 0) {
            return;
        }

        /* Construct follow-up input by replacing the pattern with a shorter substring */
        String shortSubstring = "short";
        String followText = text.substring(0, origIndex) + shortSubstring + text.substring(origIndex + pattern.length());

        /* Get follow-up output */
        int followIndex = Boyer.indexOf(followText, shortSubstring);

        /* Verification */
        assertTrue(followIndex >= origIndex);
    }

    /**
     * Metamorphic Relation 37: If the pattern P is found in the original text T, then replacing a character in the pattern
     * with a different character should not affect the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(String text, String pattern) {
        /* Verify the occurrence of the pattern in the original text */
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get original output */
        int originalOutput = Boyer.indexOf(text, pattern);

        /* Replace a character in the pattern with a different character */
        int replaceIndex = Math.min(1, pattern.length() - 1);
        char[] replacedPatternChars = pattern.toCharArray();
        char replacedChar = (char)(replacedPatternChars[replaceIndex] + 1);  // Replace character with next character
        replacedPatternChars[replaceIndex] = replacedChar;
        String replacedPattern = new String(replacedPatternChars);

        /* Get follow-up output */
        int followUpOutput = Boyer.indexOf(text, replacedPattern);

        /* Verification */
        assertEquals(originalOutput, followUpOutput);
    }

    /**
     * Metamorphic Relation 38: If the pattern P is not found in the original text T, then replacing all occurrences of a
     * character in the text with a different character should not affect the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(String text, String pattern) {
        /* Verify the occurrence of the pattern in the original text */
        if (text.indexOf(pattern) != -1) {
            return;
        }

        /* Get original output */
        int originalOutput = Boyer.indexOf(text, pattern);

        /* Replace all occurrences of a character in the text with a different character */
        char originalChar = text.charAt(0);  // Consider the first character, for example
        char replacedChar = (char)(originalChar + 1);   // Replace with next character
        String replacedText = text.replace(originalChar, replacedChar);

        /* Get follow-up output */
        int followUpOutput = Boyer.indexOf(replacedText, pattern);

        /* Verification */
        assertEquals(originalOutput, followUpOutput);
    }

    /**
     * Metamorphic Relation 39: If the pattern P is found in the original text T, then searching the reversed text
     * for the reversed pattern should yield the same output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(String text, String pattern) {
        /* Verify the occurrence of the pattern in the original text */
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get output for the reversed pattern in the reversed text */
        String reversedText = new StringBuilder(text).reverse().toString();
        String reversedPattern = new StringBuilder(pattern).reverse().toString();
        int originalOutput = Boyer.indexOf(text, pattern);
        int reversedOutput = Boyer.indexOf(reversedText, reversedPattern);

        /* Verification */
        assertEquals(originalOutput, reversedOutput);
    }

    /**
     * Metamorphic Relation 40: If the pattern P is found in the original text T, then replacing it with a substring of the
     * original text should yield a different output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(String text, String pattern) {
        /* Verify the occurrence of the pattern in the original text */
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get output for the substring in the original text */
        int originalOutput = Boyer.indexOf(text, pattern);
        int length = Math.min(pattern.length(), text.length());
        String substring = text.substring(0, length);
        int substringOutput = Boyer.indexOf(text, substring);

        /* Verification */
        assertNotEquals(originalOutput, substringOutput);
    }

    /**
     * Metamorphic Relation 41: If a portion of the text T1 is found in the original text T, then replacing that portion
     * with a different string should yield a different output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test41(String text, String pattern) {
        /* Verify the occurrence of a portion of the text in the original text */
        if (text.length() < 2) {
            return;
        }

        String subtext = text.substring(0, 2);
        if (text.indexOf(subtext) == -1) {
            return;
        }

        /* Get output for the modified text */
        String replacementText = "new";
        String modifiedText = text.replace(subtext, replacementText);
        int originalOutput = Boyer.indexOf(text, pattern);
        int modifiedOutput = Boyer.indexOf(modifiedText, pattern);

        /* Verification */
        assertNotEquals(originalOutput, modifiedOutput);
    }

    /**
     * Metamorphic Relation 42: If the pattern P is not found in the original text T, then replacing the text with a
     * different text should yield the same output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test42(String text, String pattern) {
        /* Verify the occurrence of the pattern in the original text */
        if (text.indexOf(pattern) != -1) {
            return;
        }

        /* Get output for the modified text */
        String modifiedText = "This is a different text.";
        int originalOutput = Boyer.indexOf(text, pattern);
        int modifiedOutput = Boyer.indexOf(modifiedText, pattern);

        /* Verification */
        assertEquals(originalOutput, modifiedOutput);
    }

    static Stream<Arguments> testcaseProvider() throws IOException {
        return testcaseGenerator.generate_ss(1000);
    }
}