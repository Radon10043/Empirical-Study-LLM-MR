package test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assumptions.assumeFalse;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.security.SecureRandom;
import java.util.Base64;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.regex.Pattern;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import org.apache.commons.lang3.RandomStringUtils;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import src.Boyer;

public class BoyerTestGPT4NoSpec {

    /**
     * Metamorphic Relation 3: If the pattern does not occur in the original text,
     * appending the pattern itself or any suffix of the pattern at the end of the
     * text should result in the pattern being found at the new end of the text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(String text, String pattern) {
        if (text.indexOf(pattern) != -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);
        assertTrue(origin_res == -1);

        /* Construct follow-up inputs with suffix of pattern */
        String suffix = pattern.substring(1); // Assuming pattern length > 1 for non-empty suffix
        String follow_text = text + suffix;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertEquals(follow_text.length() - suffix.length(), follow_res);
    }

    /**
     * Metamorphic Relation 4: If the pattern occurred in the original text,
     * reversing the text and the pattern should result in the original output index
     * commencing from the end of the text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Reverse inputs */
        String reversedText = new StringBuilder(text).reverse().toString();
        String reversedPattern = new StringBuilder(pattern).reverse().toString();

        /* Get follow-up output */
        int reversed_res = Boyer.indexOf(reversedText, reversedPattern);

        /* Verification */
        assertTrue(reversed_res == (text.length() - origin_res - pattern.length()));
    }

    /**
     * Metamorphic Relation 5: If the pattern occurred in the original text,
     * changing the case of the text and pattern should not alter the index of the
     * first occurrence of the pattern if the Boyer-Moore implementation is
     * case-insensitive.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(String text, String pattern) {
        if (text.indexOf(pattern) == -1 || !text.equals(text.toLowerCase())) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Change case of inputs */
        String upperText = text.toUpperCase();
        String upperPattern = pattern.toUpperCase();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(upperText, upperPattern);

        /* Verification */
        assertEquals(origin_res, follow_res);
    }

    /**
     * Metamorphic Relation 6: If the pattern occurred in the original text, when
     * adding a non-overlapping prefix to the pattern, the output should be -1
     * indicating the pattern is not found.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Construct follow-up input */
        String follow_pattern = "not" + pattern; // 'not' is a non-overlapping string

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertEquals(-1, follow_res);
    }

    /**
     * Metamorphic Relation 7: If the pattern occurred in the original text, when
     * the same non-empty string is appended to both the text and the pattern, the
     * output should increase by the length of that string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up inputs */
        String appendString = "ABC"; // Non-empty string
        String follow_text = text + appendString;
        String follow_pattern = pattern + appendString;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, follow_pattern);

        /* Verification */
        assertEquals(origin_res + appendString.length(), follow_res);
    }

    /**
     * Metamorphic Relation 8: If the pattern occurred at the end of the original
     * text, when the pattern is removed from the end of the text, the pattern
     * should not be found.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(String text, String pattern) {
        int lastIndex = text.lastIndexOf(pattern);
        if (lastIndex == -1 || (lastIndex + pattern.length()) != text.length()) {
            return; // Pattern does not occur at the end
        }

        /* Construct follow-up input */
        String follow_text = text.substring(0, lastIndex);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertEquals(-1, follow_res);
    }

    /**
     * Metamorphic Relation 9: If the text is non-empty and the pattern is empty,
     * the Boyer-Moore algorithm should return 0 as the index where the empty
     * pattern trivially occurs at the beginning of any text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(String text, String pattern) {
        if (text.isEmpty()) {
            return; // Skip empty text cases
        }

        /* Use an empty pattern */
        String emptyPattern = "";

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, emptyPattern);

        /* Verification */
        assertEquals(0, follow_res);
    }

    /**
     * Metamorphic Relation 10: If the pattern occurs multiple times in the text,
     * prepending or appending any string to the text should not affect the relative
     * distances between the occurrences.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String text, String pattern) {
        // Find the first two occurrences
        int firstOccurrence = text.indexOf(pattern);
        int secondOccurrence = text.indexOf(pattern, firstOccurrence + pattern.length());

        // Check if there is more than one occurrence
        if (firstOccurrence == -1 || secondOccurrence == -1) {
            return; // Pattern does not occur multiple times
        }

        // Prepend a string to the text
        String prependString = "prepend";
        String follow_text = prependString + text;

        // Get follow-up outputs
        int follow_firstOccurrence = Boyer.indexOf(follow_text, pattern);
        int follow_secondOccurrence = Boyer.indexOf(follow_text, pattern, follow_firstOccurrence + pattern.length());

        // Verification
        assertEquals(firstOccurrence, follow_firstOccurrence - prependString.length());
        assertEquals(secondOccurrence, follow_secondOccurrence - prependString.length());
    }

    /**
     * Metamorphic Relation 11: If the pattern occurred in the original text, when
     * inserting a string into the text before the pattern occurrence, the output
     * index should shift right by the length of the inserted string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(String text, String pattern) {
        int index = Boyer.indexOf(text, pattern);
        if (index == -1) {
            return; // Pattern doesn't occur in the text
        }

        /* Construct follow-up input by inserting a string */
        String insertString = "insert";
        String follow_text = text.substring(0, index) + insertString + text.substring(index);

        /* Get follow-up output */
        int follow_index = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertEquals(index + insertString.length(), follow_index);
    }

    /**
     * Metamorphic Relation 12: If the pattern and text are identical (and
     * non-empty), then replacing any character in the pattern and the identical
     * position in the text should still result in an index of 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(String text, String pattern) {
        if (text.isEmpty() || !text.equals(pattern)) {
            return;
        }

        /* Modify input by replacing a character */
        char replacement = 'Z'; // Assuming the replacement character is not already in the
                                // text/pattern
        String modifiedText = text.substring(0, 1) + replacement + text.substring(2);
        String modifiedPattern = pattern.substring(0, 1) + replacement + pattern.substring(2);

        /* Get follow-up output */
        int follow_index = Boyer.indexOf(modifiedText, modifiedPattern);

        /* Verification */
        assertEquals(0, follow_index);
    }

    /**
     * Metamorphic Relation 13: If the original text contains the pattern multiple
     * times, then removing all occurrences of the pattern except the first should
     * result in the same output index.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(String text, String pattern) {
        int index = Boyer.indexOf(text, pattern);
        if (index == -1) {
            return; // Pattern doesn't occur in the text
        }

        /*
         * Construct follow-up input by removing all occurrences of the pattern except
         * the first
         */
        String firstPart = text.substring(0, index + pattern.length());
        String remainingPart = text.substring(index + pattern.length()).replace(pattern, "");
        String follow_text = firstPart + remainingPart;

        /* Get follow-up output */
        int follow_index = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertEquals(index, follow_index);
    }

    /**
     * Metamorphic Relation 14: If the text and pattern are such that the pattern
     * does not occur in the text, swapping the two should also result in the
     * pattern (now the text) not being found within the text (now the pattern).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(String text, String pattern) {
        if (Boyer.indexOf(text, pattern) != -1) {
            return; // Pattern occurs in the text, so we skip this case
        }

        /* Swap text and pattern */
        String temp = text;
        text = pattern;
        pattern = temp;

        /* Get follow-up output */
        int follow_index = Boyer.indexOf(text, pattern);

        /* Verification */
        assertEquals(-1, follow_index);
    }

    /**
     * Metamorphic Relation 15: If the pattern occurred in the original text, and
     * the text is duplicated, the pattern should still be found at the same index
     * in the duplicated text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String text, String pattern) {
        int index = Boyer.indexOf(text, pattern);
        if (index == -1) {
            return; // Pattern doesn't occur in the text
        }

        /* Duplicate the text */
        String duplicateText = text + text;

        /* Get follow-up output */
        int follow_index = Boyer.indexOf(duplicateText, pattern);

        /* Verification */
        assertEquals(index, follow_index);
    }

    /**
     * Metamorphic Relation 16: If the text and the pattern are such that the
     * pattern occurs in the text, doubling the pattern should cause the Booyer
     * Moore to either not find the pattern (if it only occurred once) or return the
     * first occurrence of the doubled pattern.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(String text, String pattern) { // Fixed
        int firstOccurrence = Boyer.indexOf(text, pattern);
        if (firstOccurrence == -1) {
            return; // Pattern does not occur
        }

        /* Double the pattern */
        String doublePattern = pattern + pattern;

        /* Get follow-up output */
        int follow_index = Boyer.indexOf(text, doublePattern);

        /* Verification */
        assertTrue(follow_index == -1 || follow_index == firstOccurrence);
    }

    /**
     * Metamorphic Relation 17: If the pattern does not occur in the original text,
     * prepending the pattern to the text should result in the pattern being found
     * at the beginning of the text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String text, String pattern) {
        if (Boyer.indexOf(text, pattern) != -1) {
            return; // Skip this case if the pattern is found
        }

        /* Prepend the pattern to the text */
        String newText = pattern + text;

        /* Get new occurrence index */
        int newIndex = Boyer.indexOf(newText, pattern);

        /* Verify that the pattern is found at the beginning */
        assertEquals(0, newIndex);
    }

    /**
     * Metamorphic Relation 18: If the pattern occurs in the original text,
     * replacing a middle occurrence of the pattern in the text with a
     * non-overlapping string should not affect the first occurrence index.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String text, String pattern) {
        // Find the first two occurrences to ensure there's a middle occurrence to
        // replace
        int firstOccurrence = text.indexOf(pattern);
        int secondOccurrence = text.indexOf(pattern, firstOccurrence + pattern.length());

        if (firstOccurrence == -1 || secondOccurrence == -1) {
            return; // Pattern does not occur multiple times
        }

        /* Replace middle occurrence */
        String replacement = "REP"; // A non-overlapping string
        StringBuilder newTextBuilder = new StringBuilder(text);
        newTextBuilder.replace(secondOccurrence, secondOccurrence + pattern.length(), replacement);
        String newText = newTextBuilder.toString();

        /* Get new first occurrence index */
        int newFirstOccurrence = Boyer.indexOf(newText, pattern);

        /* Verify that the first occurrence index is unchanged */
        assertEquals(firstOccurrence, newFirstOccurrence);
    }

    /**
     * Metamorphic Relation 19: If the pattern occurs in the original text,
     * interleaving the text with a non-overlapping string should not change the
     * result of whether the pattern is found in the text or not.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String text, String pattern) {
        boolean patternExists = Boyer.indexOf(text, pattern) != -1;

        /* Interleave the text with a non-overlapping string */
        String interleavingString = "INTER";
        StringBuilder newTextBuilder = new StringBuilder();
        int blockSize = pattern.length();
        for (int i = 0; i < text.length(); i += blockSize) {
            newTextBuilder.append(text.substring(i, Math.min(i + blockSize, text.length())));
            newTextBuilder.append(interleavingString);
        }
        String newText = newTextBuilder.toString();

        /* Check if pattern exists in the new text */
        boolean newPatternExists = Boyer.indexOf(newText, pattern) != -1;

        /* Verify that the pattern existence is consistent */
        assertEquals(patternExists, newPatternExists);
    }

    /**
     * Metamorphic Relation 20: If the pattern occurred in the original text, and we
     * rotate the text to the right by n, the pattern should be found or not found
     * correspondingly in the rotated text, and its new index should be adjusted
     * according to the rotation if found.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(String text, String pattern) {
        int index = Boyer.indexOf(text, pattern);
        if (index == -1) {
            return; // Pattern doesn't occur in the text
        }

        /* Rotate the text right by n characters */
        int n = pattern.length(); // Rotate by the length of the pattern
        String rotatedText = text.substring(text.length() - n) + text.substring(0, text.length() - n);

        /* Get the index in the rotated text */
        int rotatedIndex = Boyer.indexOf(rotatedText, pattern);

        /* Calculate the expected new index */
        int newIndex = (index - n + text.length()) % text.length();

        /* Verification */
        assertEquals(newIndex, rotatedIndex);
    }

    /**
     * Metamorphic Relation 21: If the text contains the pattern, replacing a
     * character within the pattern not at an occurrence with a character not
     * present in the text should result in the pattern not being found.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(String text, String pattern) {
        // Verify the pattern exists in the text
        if (Boyer.indexOf(text, pattern) == -1) {
            return; // Skip cases where pattern doesn't exist
        }

        /* Modify pattern by replacing a character not at an occurrence */
        int nonOccurrenceIndex = pattern.length() / 2; // For simplicity, take the middle character
        char uniqueChar = 'ß'; // Assume 'ß' is not present in the original text or pattern
        String modifiedPattern = pattern.substring(0, nonOccurrenceIndex) + uniqueChar
                + pattern.substring(nonOccurrenceIndex + 1);

        /* Get follow-up output */
        int follow_index = Boyer.indexOf(text, modifiedPattern);

        /* Verification */
        assertEquals(-1, follow_index); // Modified pattern should not be found
    }

    /**
     * Metamorphic Relation 22: If the text contains only a single occurrence of the
     * pattern, replacing the pattern occurrence with another pattern of equal
     * length should result in the new pattern being found at the same index.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(String text, String pattern) {
        int index = Boyer.indexOf(text, pattern);
        // Check that the pattern occurs exactly once
        if (index == -1 || Boyer.indexOf(text, pattern, index + 1) != -1) {
            return; // Pattern does not occur, or it occurs multiple times
        }

        /* Replace the single pattern occurrence with a new pattern */
        String newPattern = new String(new char[pattern.length()]).replace("\0", "N"); // 'N'
                                                                                       // repeated
        String newText = text.substring(0, index) + newPattern + text.substring(index + pattern.length());

        /* Get follow-up output */
        int newPatternIndex = Boyer.indexOf(newText, newPattern);

        /* Verification */
        assertEquals(index, newPatternIndex);
    }

    /**
     * Metamorphic Relation 23: If deleting characters from the text at positions
     * not overlapping any occurrence of the pattern, then the index of occurrences
     * of the pattern should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(String text, String pattern) {
        int index = Boyer.indexOf(text, pattern);
        if (index == -1) {
            return; // Skip cases where the pattern doesn't occur
        }

        // Choose a remove index which is outside the occurrence
        int removeIndex = index > 0 ? index - 1 : index + pattern.length();
        if (removeIndex >= text.length()) {
            return; // This would only happen for malformed inputs
        }

        /* Remove a character from the text */
        String newText = text.substring(0, removeIndex) + text.substring(removeIndex + 1);

        /* Get follow-up output */
        int newIndex = Boyer.indexOf(newText, pattern);

        /* Verification */
        // If the removeIndex is before the pattern, the index should decrease by one.
        // Otherwise, the index should stay the same.
        assertEquals(removeIndex < index ? index - 1 : index, newIndex);
    }

    /**
     * Metamorphic Relation 24: If the pattern occurs in the text and both text and
     * pattern are reversed, the new index should be adjusted to point to the
     * equivalent occurrence in the reversed text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(String text, String pattern) {
        int index = Boyer.indexOf(text, pattern);
        if (index == -1) {
            return; // Skip cases where the pattern doesn't occur
        }

        /* Reverse both text and pattern */
        String reversedText = new StringBuilder(text).reverse().toString();
        String reversedPattern = new StringBuilder(pattern).reverse().toString();

        /* Get follow-up output */
        int reversedIndex = Boyer.indexOf(reversedText, reversedPattern);

        /* Verification */
        int expectedIndex = text.length() - index - pattern.length();
        assertEquals(expectedIndex, reversedIndex);
    }

    /**
     * Metamorphic Relation 25: If the pattern is not found in the original text,
     * and a copy of a portion of text which does not contain the pattern is
     * appended/prepended to the text, the pattern should still not be found.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(String text, String pattern) {
        int firstIndex = text.indexOf(pattern);
        if (firstIndex != -1) {
            return; // Skip cases where the pattern occurs
        }

        // Create a substring from the original text that doesn't contain the pattern
        String partOfText = text.substring(0, Math.min(text.length(), pattern.length()));

        /* Append and prepend a portion of text */
        String newText = partOfText + text + partOfText;

        /* Get follow-up output from both operations */
        int newIndexAfterAppend = Boyer.indexOf(newText, pattern);
        int newIndexAfterPrepend = Boyer.indexOf(newText, pattern);

        /* Verification */
        assertEquals(-1, newIndexAfterAppend);
        assertEquals(-1, newIndexAfterPrepend);
    }

    /**
     * Metamorphic Relation 26: If the pattern occurs in the original text, then
     * interchanging the occurrences of two characters in the pattern should either
     * produce the same results or return -1 if the order of characters is vital for
     * occurrences.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1 || pattern.length() < 2) {
            return; // Skip case where pattern is not present or too short to interchange
                    // characters.
        }

        // Interchange characters in the pattern
        char ch1 = pattern.charAt(0);
        char ch2 = pattern.charAt(1);
        StringBuilder newPatternBuilder = new StringBuilder(pattern);
        newPatternBuilder.setCharAt(0, ch2);
        newPatternBuilder.setCharAt(1, ch1);
        String newPattern = newPatternBuilder.toString();

        // Find the pattern in the text
        int newIndex = Boyer.indexOf(text, newPattern);

        // Verify the results remain the same or -1
        assertTrue(newIndex == originalIndex || newIndex == -1);
    }

    /**
     * Metamorphic Relation 27: If a non-empty sequence is removed from the text in
     * such a way that it includes the pattern, then the pattern must not be found
     * in the resulting text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(String text, String pattern) {
        int index = Boyer.indexOf(text, pattern);
        if (index == -1) {
            return; // Skip case where pattern is not found
        }

        // Remove a sequence that includes the pattern from the text
        String modifiedText = text.substring(0, index) + text.substring(index + pattern.length());

        // Verify the pattern is not found
        int modifiedIndex = Boyer.indexOf(modifiedText, pattern);
        assertEquals(-1, modifiedIndex);
    }

    /**
     * Metamorphic Relation 28: If the pattern is found in the text, then replacing
     * the entirety of the text with the pattern should result in the pattern being
     * found at the start of the text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(String text, String pattern) {
        if (Boyer.indexOf(text, pattern) == -1) {
            return; // Skip case where pattern is not found
        }

        // Replace text with pattern
        String newText = pattern;

        // Verify the pattern is found at the start
        int newIndex = Boyer.indexOf(newText, pattern);
        assertEquals(0, newIndex);
    }

    /**
     * Metamorphic Relation 29: If the pattern is not found in the text, then
     * concatenating the reversed text and the original text should still not find
     * the pattern.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(String text, String pattern) {
        if (Boyer.indexOf(text, pattern) != -1) {
            return; // Skip case where pattern is found
        }

        // Concatenate reversed text with the original text
        String reversedText = new StringBuilder(text).reverse().toString();
        String concatenatedText = reversedText + text;

        // Verify the pattern is not found in the concatenated text
        int newIndex = Boyer.indexOf(concatenatedText, pattern);
        assertEquals(-1, newIndex);
    }

    /**
     * Metamorphic Relation 30: If the pattern is not found in the original text,
     * then replacing all characters in both the text and pattern with a single
     * repeating character should return 0, since the repeated character pattern
     * should occur immediately.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(String text, String pattern) {
        if (Boyer.indexOf(text, pattern) != -1) {
            return; // Skip case where pattern is found
        }

        // Replace all characters in text and pattern with a singe repeating character
        String newText = text.replaceAll(".", "x"); // Replace with 'x'
        String newPattern = pattern.replaceAll(".", "x");

        // Pattern should be found immediately
        int newIndex = Boyer.indexOf(newText, newPattern);
        assertEquals(0, newIndex);
    }

    /**
     * Metamorphic Relation 31: If the pattern occurs in the original text, then any
     * permutation of the characters in the pattern should result in either the same
     * index of occurrence or -1 if the permutation disrupts a match.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1 || pattern.length() <= 1) {
            return; // Skip cases where the pattern doesn't exist or is of length 1.
        }

        // Permute characters in the pattern
        String permutedPattern = new StringBuilder(pattern.substring(1)).reverse().toString() + pattern.charAt(0);

        // Find the pattern in the text
        int newIndex = Boyer.indexOf(text, permutedPattern);

        // Verify the results remain the same or -1
        assertTrue(newIndex == originalIndex || newIndex == -1);
    }

    /**
     * Metamorphic Relation 32: If the text consists of repeated sequences of the
     * pattern and the text is truncated before the final complete pattern sequence,
     * the index of the last occurrence of the pattern should be unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(String text, String pattern) {
        if (pattern.isEmpty() || text.isEmpty() || text.length() % pattern.length() != 0) {
            return; // Skip if the pattern or text is empty or if the text length isn't a multiple
                    // of the pattern length
        }

        // Truncate the text before the final complete pattern sequence
        String truncatedText = text.substring(0, text.length() - pattern.length());

        // Verify the last occurrence of the pattern index is unchanged
        int lastIndexInOriginal = text.lastIndexOf(pattern);
        int lastIndexInTruncated = truncatedText.lastIndexOf(pattern);
        assertEquals(lastIndexInOriginal, lastIndexInTruncated + pattern.length());
    }

    /**
     * Metamorphic Relation 33: If the pattern is found in the text and the pattern
     * is appended with a string that does not interfere with existing occurrences,
     * then occurrences of the original pattern should still be valid.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(String text, String pattern) {
        int firstIndex = Boyer.indexOf(text, pattern);
        if (firstIndex == -1) {
            return; // Skip if the pattern is not found
        }

        // Append a non-interfering string to the pattern
        String newPattern = pattern + "#"; // Append with a character not present in the text.

        // Find the pattern in the text
        int newIndex = Boyer.indexOf(text, newPattern);

        // Verify the original pattern occurrences remain valid
        assertTrue(firstIndex == newIndex || newIndex == -1);
    }

    /**
     * Metamorphic Relation 34: If the pattern occurs in the text, then formatting
     * both the text and pattern should not affect the occurrence of the pattern,
     * assuming the formatting operation is invertible (e.g., rot13, base64
     * encoding/decoding).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(String text, String pattern) {
        // Only continue if the pattern is found
        if (Boyer.indexOf(text, pattern) == -1) {
            return;
        }

        // Apply an invertible formatting operation (rot13 shown here for simplicity)
        String formattedText = rot13(text);
        String formattedPattern = rot13(pattern);

        // Find the pattern in the formatted text
        int newIndex = Boyer.indexOf(formattedText, formattedPattern);

        // Verify that the pattern occurrence is consistent
        int originalIndex = Boyer.indexOf(text, pattern);
        assertEquals(originalIndex, Boyer.indexOf(rot13(formattedText), rot13(formattedPattern)));
    }

    /**
     * Metamorphic Relation 35: If the original text and pattern are both prefixed
     * with an identical string, then the pattern's index in the text should be
     * increased by the length of the prefix, assuming the prefix does not create
     * new occurrences of the pattern.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return; // Skip cases where the pattern isn't found.
        }

        String prefix = "prefix"; // A prefix that doesn't contain pattern characters.
        String newText = prefix + text;
        String newPattern = prefix + pattern;

        // Find the pattern in the prefixed text
        int newIndex = Boyer.indexOf(newText, newPattern);

        // Verify the updated index of the pattern in the prefixed text
        assertEquals(originalIndex + prefix.length(), newIndex);
    }

    // Utility function for MR34, just for demonstration.
    private String rot13(String input) {
        StringBuilder result = new StringBuilder();
        for (char c : input.toCharArray()) {
            if (c >= 'a' && c <= 'z') {
                result.append((char) ((c - 'a' + 13) % 26 + 'a'));
            } else if (c >= 'A' && c <= 'Z') {
                result.append((char) ((c - 'A' + 13) % 26 + 'A'));
            } else {
                result.append(c);
            }
        }
        return result.toString();
    }

    /**
     * Metamorphic Relation 36: If the pattern occurs in the original text, then
     * shifting both the text and pattern by the same set of characters should not
     * alter the presence or index of the pattern within the text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return; // Skip this test if the pattern does not initially occur within the text.
        }

        String shiftedText = shiftCharacters(text, 1);
        String shiftedPattern = shiftCharacters(pattern, 1);

        int newIndex = Boyer.indexOf(shiftedText, shiftedPattern);
        assertEquals(originalIndex, newIndex);
    }

    /**
     * Metamorphic Relation 37: If the pattern occurs in the original text multiple
     * times, then repeating the text consecutively should double the number of
     * occurrences while retaining the positions of the original ones relative to
     * their repetitions.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(String text, String pattern) {
        int initialCount = countOccurrences(text, pattern);
        if (initialCount == 0) {
            return;
        }

        String doubledText = text + text;
        int doubledCount = countOccurrences(doubledText, pattern);

        assertEquals(2 * initialCount, doubledCount);
    }

    /**
     * Metamorphic Relation 38: If the pattern is a palindrome and occurs in the
     * original text, reversing the pattern should not change its positions of
     * occurrence within the text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(String text, String pattern) {
        // Check if the pattern is a palindrome
        String reversedPattern = new StringBuilder(pattern).reverse().toString();
        if (!pattern.equals(reversedPattern)) {
            return; // Skip if pattern is not a palindrome
        }

        int originalIndex = Boyer.indexOf(text, pattern);
        int reversedIndex = Boyer.indexOf(text, reversedPattern);

        assertEquals(originalIndex, reversedIndex);
    }

    /**
     * Metamorphic Relation 39: If the pattern does not occur in the text,
     * concatenate the text to itself with a separating unique character should not
     * create new occurrences of the pattern.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(String text, String pattern) {
        if (Boyer.indexOf(text, pattern) != -1) {
            return; // Pattern occurs in the text, so we skip this case
        }

        String concatenatedText = text + "#" + text; // Use a unique separator that does not exist
                                                     // in text or pattern

        int concatenatedIndex = Boyer.indexOf(concatenatedText, pattern);
        assertEquals(-1, concatenatedIndex);
    }

    /**
     * Metamorphic Relation 40: If the text and the pattern have a certain number of
     * occurrences, replacing all instances of a specific character to another
     * across both text and pattern should not change the number of occurrences.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(String text, String pattern) {
        int originalCount = countOccurrences(text, pattern);

        // Replace a character in text and pattern
        String newText = text.replace('a', '@'); // Assume 'a' exists in both text and pattern
        String newPattern = pattern.replace('a', '@');

        int newCount = countOccurrences(newText, newPattern);
        assertEquals(originalCount, newCount);
    }

    // Helper methods for the above tests:
    private String shiftCharacters(String input, int shiftCount) {
        StringBuilder sb = new StringBuilder();
        input.chars().forEach(c -> sb.append(Character.toChars(c + shiftCount)));
        return sb.toString();
    }

    private int countOccurrences(String text, String pattern) {
        int count = 0;
        int index = 0;

        while ((index = Boyer.indexOf(text, pattern, index)) != -1) {
            count++;
            index += pattern.length(); // Move past last occurrence
        }

        return count;
    }

    /**
     * Metamorphic Relation 41: If the pattern occurred in the original text,
     * inverting the case of characters in both text and pattern should not change
     * the occurrence index if the Boyer-Moore function is case-insensitive.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test41(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);

        String invertedCaseText = invertCase(text);
        String invertedCasePattern = invertCase(pattern);

        int invertedCaseIndex = Boyer.indexOf(invertedCaseText, invertedCasePattern);
        assertEquals(originalIndex, invertedCaseIndex);
    }

    /**
     * Metamorphic Relation 42: If appending the text to itself causes the pattern
     * to be found at the beginning of the new text, then appending any text that
     * doesn't contain the pattern should still result in the pattern being found at
     * the same indexes as before.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test42(String text, String pattern) {   // Fixed
        if (Boyer.indexOf(text, pattern) == -1) {
            return; // Skip if the pattern does not occur in the original text
        }

        // Append text to itself
        String appendedText = text + text;

        String extraText = "nonOverlap";
        SecureRandom rand = new SecureRandom();
        while (extraText.contains(pattern)) {
            extraText = RandomStringUtils.randomAlphabetic(rand.nextInt(1, 10));
        }

        // Append non-overlapping text
        String nonOverlappingText = extraText + appendedText; // Ensure "nonOverlap" does not
                                                                 // contain the pattern

        // The indexes should be the same, just shifted by the length of "nonOverlap"
        int indexInAppendedText = Boyer.indexOf(appendedText, pattern);
        int indexInNonOverlappingText = Boyer.indexOf(nonOverlappingText, pattern);
        assertEquals(indexInAppendedText + extraText.length(), indexInNonOverlappingText);
    }

    private String invertCase(String input) {
        return input.chars().mapToObj(
                c -> Character.isUpperCase(c) ? Character.toLowerCase(c) : Character.toUpperCase(c))
                .collect(StringBuilder::new, StringBuilder::appendCodePoint, StringBuilder::append)
                .toString();
    }

    static Stream<Arguments> testcaseProvider() throws IOException {
        return testcaseGenerator.generate_ss(1000);
    }

}
