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

public class BoyerTestGPT4NoSystem {
    /**
     * Metamorphic Relation 3: If the pattern does not occur in the original text,
     * adding a prefix to both the text and the pattern should not change the
     * outcome (-1).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(String text, String pattern) { // Fixed
        /* Check initial condition */
        if (Boyer.indexOf(text, pattern) != -1) {
            return;
        }

        /* Construct follow-up input */
        String prefix = "prefix";
        String follow_text = prefix + text;
        String follow_pattern = prefix + pattern;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, follow_pattern);

        /* Verification */
        assertEquals(-1, follow_res);
    }

    /**
     * Metamorphic Relation 4: If the pattern is found in the original text,
     * appending the same pattern again at the end of the original text should
     * return the index of the first occurrence which is no greater than in the
     * original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(String text, String pattern) {
        /* Check initial condition */
        int origin_res = Boyer.indexOf(text, pattern);
        if (origin_res == -1) {
            return;
        }

        /* Construct follow-up input */
        String follow_text = text + pattern;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res <= origin_res);
    }

    /**
     * Metamorphic Relation 5: Reversing both the text and the pattern should
     * preserve the distance of the pattern's first occurrence from the end of the
     * text if it exists.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(String text, String pattern) {
        int origin_res = Boyer.indexOf(text, pattern);
        if (origin_res == -1) {
            return;
        }

        /* Construct follow-up input */
        String reversedText = new StringBuilder(text).reverse().toString();
        String reversedPattern = new StringBuilder(pattern).reverse().toString();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(reversedText, reversedPattern);

        /* Verification */
        assertEquals(follow_res, text.length() - origin_res - pattern.length());
    }

    /**
     * Metamorphic Relation 6: Concatenating the text with itself should result in
     * double occurrences of the pattern if there is at least one occurrence in the
     * original text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(String text, String pattern) {
        /* Check initial condition */
        int origin_res = Boyer.indexOf(text, pattern);
        if (origin_res == -1) {
            return;
        }

        /* Construct follow-up input */
        String doubleText = text + text;

        /* Get follow-up output */
        int followFirstRes = Boyer.indexOf(doubleText, pattern);
        int followSecondRes = Boyer.indexOf(doubleText.substring(followFirstRes + pattern.length()), pattern);

        /* Verification */
        assertEquals(followFirstRes, origin_res); // First occurrence should be at the same position
        assertTrue(followSecondRes > 0); // There should be a second occurrence
    }

    /**
     * Metamorphic Relation 7: If the pattern occurs in the original text, the
     * occurrence should still be found (with a modified index) if a prefix is added
     * only to the text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(String text, String pattern) {    // Fixed
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return;
        }

        /* Construct follow-up input */
        String prefix = "extra";

        SecureRandom rand = new SecureRandom();
        while (prefix.indexOf(pattern) != -1) {
            prefix = RandomStringUtils.randomAscii(rand.nextInt(1, 10));
        }

        String followText = prefix + text;

        /* Get follow-up output */
        int followIndex = Boyer.indexOf(followText, pattern);

        /* Verification */
        assertEquals(originalIndex + prefix.length(), followIndex);
    }

    /**
     * Metamorphic Relation 8: Searching for a substring in a text made up by
     * repeating the substring should return the index of the very first occurrence
     * which should be zero.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(String text, String pattern) {
        // Skip cases where pattern length is greater than text or when pattern is not
        // found
        if (pattern.length() > text.length() || Boyer.indexOf(text, pattern) == -1) {
            return;
        }

        /* Construct follow-up input */
        String repeatPatternText = pattern;
        while (repeatPatternText.length() < text.length()) {
            repeatPatternText += pattern;
        }

        /* Get follow-up output */
        int followIndex = Boyer.indexOf(repeatPatternText, pattern);

        /* Verification */
        assertEquals(0, followIndex);
    }

    /**
     * Metamorphic Relation 9: For a given text where the pattern is found, if we
     * replace all occurrences of the pattern with another string that does not
     * contain the pattern, the pattern should no longer be found.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(String text, String pattern) {
        // Skip cases where pattern is not found
        if (Boyer.indexOf(text, pattern) == -1) {
            return;
        }

        /* Construct follow-up input */
        String replacement = "REPL";
        String modifiedText = text.replaceAll(Pattern.quote(pattern), replacement);

        /* Check that replacement doesn't contain the pattern */
        assumeFalse(replacement.contains(pattern));

        /* Get follow-up output */
        int followIndex = Boyer.indexOf(modifiedText, pattern);

        /* Verification */
        assertEquals(-1, followIndex);
    }

    /**
     * Metamorphic Relation 10: If a pattern is found in a text, searching for that
     * pattern in only a subset of the text that excludes the found instance should
     * result in -1 (not found).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return;
        }

        /* Define a subset of the original text excluding the found pattern */
        String subsetText = text.substring(originalIndex + pattern.length());

        /* Get follow-up output */
        int followIndex = Boyer.indexOf(subsetText, pattern);

        /* Verification */
        assertEquals(-1, followIndex);
    }

    /**
     * Metamorphic Relation 11: If the pattern is not found in the original text,
     * shifting the text by removing the first character should not affect the
     * outcome of the pattern not being found.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(String text, String pattern) {
        // Skip if the pattern occurs in the text
        if (Boyer.indexOf(text, pattern) != -1) {
            return;
        }

        /* Construct follow-up input by removing the first character */
        String shiftedText = text.substring(1);

        /* Get follow-up output */
        int followIndex = Boyer.indexOf(shiftedText, pattern);

        /* Verification */
        assertEquals(-1, followIndex);
    }

    /**
     * Metamorphic Relation 12: If both the text and pattern are reversed, finding
     * the pattern in the text should give a result that is consistent with a
     * re-mapping to the original text orientation.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        // Perform the test only if pattern exists in the text
        if (originalIndex == -1) {
            return;
        }

        /* Construct follow-up input by reversing both text and pattern */
        String reversedText = new StringBuilder(text).reverse().toString();
        String reversedPattern = new StringBuilder(pattern).reverse().toString();

        /* Get follow-up output */
        int reversedIndex = Boyer.indexOf(reversedText, reversedPattern);

        /* Verification */
        assertEquals(reversedIndex, text.length() - originalIndex - pattern.length());
    }

    /**
     * Metamorphic Relation 13: Concatenating a string to the pattern that does not
     * exist in the text should result in the modified pattern not being found.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(String text, String pattern) {
        // Construct an input that is guaranteed not to be found in the original text
        String uniqueString = "XYZXYZ";
        while (text.contains(uniqueString)) {
            uniqueString += "Z";
        }

        /* Get original output */
        int originalIndex = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String modifiedPattern = pattern + uniqueString;

        /* Get follow-up output */
        int followIndex = Boyer.indexOf(text, modifiedPattern);

        /* Verification */
        if (originalIndex != -1) {
            assertEquals(-1, followIndex);
        }
        // If the original pattern wasn't found, the modified shouldn't be found either
        else {
            assertEquals(originalIndex, followIndex);
        }
    }

    /**
     * Metamorphic Relation 14: If there are multiple occurrences of a pattern in
     * the text, removing the first occurrence should return the index of the second
     * occurrence when searching again.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(String text, String pattern) {   // Fixed
        int firstIndex = Boyer.indexOf(text, pattern);
        if (firstIndex == -1) {
            return; // There's no occurrence of the pattern, so skip this case.
        }
        // Ensure there's a second occurrence
        if (Boyer.indexOf(text.substring(firstIndex + pattern.length()), pattern) == -1) {
            return; // No second occurrence to test for, so skip this case.
        }

        /* Construct follow-up input by removing the first occurrence */
        String textWithoutFirstOccurrence = text.substring(0, firstIndex)
                + text.substring(firstIndex + pattern.length());

        /* Get follow-up output */
        int newIndex = Boyer.indexOf(textWithoutFirstOccurrence, pattern);

        /* Verification */
        // The new index in the modified text should map to the second occurrence's
        // index in the original text
        assertEquals(newIndex + pattern.length(),
                Boyer.indexOf(text.substring(firstIndex + pattern.length()), pattern) + firstIndex + pattern.length());
    }

    /**
     * Metamorphic Relation 15: Doubling the pattern and searching within the
     * original text should not return a valid index if the pattern only occurs once
     * in the original text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String text, String pattern) {
        // Skip if the pattern is not found in the text or if it's found more than once
        int firstOccurrence = Boyer.indexOf(text, pattern);
        if (firstOccurrence == -1 || Boyer.indexOf(text.substring(firstOccurrence + pattern.length()), pattern) != -1) {
            return;
        }

        /* Construct follow-up input by doubling the pattern */
        String doubledPattern = pattern + pattern;

        /* Get follow-up output */
        int followIndex = Boyer.indexOf(text, doubledPattern);

        /* Verification */
        assertEquals(-1, followIndex);
    }

    /**
     * Metamorphic Relation 16: If a pattern is prefixed with any character and the
     * text remains unchanged, the original index of the pattern should increment by
     * one if the pattern still exists.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(String text, String pattern) {   // Fixed
        // Skip if the pattern does not exist in the text
        if (Boyer.indexOf(text, pattern) == -1) {
            return;
        }

        /* Get original output */
        int originalIndex = Boyer.indexOf(text, pattern);

        /* Construct follow-up input by adding a prefix to the pattern */
        String prefixedPattern = "a" + pattern; // Assume 'a' is not a leading char in pattern

        /* Get follow-up output */
        int followIndex = Boyer.indexOf(text, prefixedPattern);

        /* Verification */
        if (originalIndex == 0 || originalIndex == -1) {
            assertEquals(-1, followIndex); // If the pattern starts at index 0, it shouldn't be found
        } else {
            assertEquals(originalIndex - 1, followIndex);
        }
    }

    /**
     * Metamorphic Relation 17: Inverting the case of the pattern and text should
     * not change the index of the pattern's occurrence considering case-insensitive
     * search.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String text, String pattern) {
        // Skip if the pattern does not exist in the text
        int originalIndex = Boyer.indexOf(text.toLowerCase(), pattern.toLowerCase());
        if (originalIndex == -1) {
            return;
        }

        /* Get follow-up output */
        int invertedIndex = Boyer.indexOf(text.toUpperCase(), pattern.toUpperCase());

        /* Verification */
        assertEquals(originalIndex, invertedIndex);
    }

    /**
     * Metamorphic Relation 18: For a non-empty pattern, the indexOf result of a
     * substring created by repeating the pattern should be zero, since the
     * substring starts with the pattern.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String text, String pattern) {
        // Skip if the pattern is empty
        if (pattern.isEmpty()) {
            return;
        }

        /* Construct follow-up input by repeating the pattern */
        String repeatedPatternText = String.join("", Collections.nCopies(3, pattern)); // repeat pattern 3 times

        /* Get follow-up output */
        int followIndex = Boyer.indexOf(repeatedPatternText, pattern);

        /* Verification */
        assertEquals(0, followIndex);
    }

    /**
     * Metamorphic Relation 19: Shuffling the characters in the pattern without
     * repetition and searching for the shuffled pattern should return -1 as the
     * shuffled pattern is not present in the original text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String text, String pattern) {
        // Skip if the pattern does not exist in the text
        if (Boyer.indexOf(text, pattern) == -1 || pattern.length() < 2) {
            return;
        }

        /* Shuffle the pattern characters */
        List<Character> characters = pattern.chars().mapToObj(c -> (char) c).collect(Collectors.toList());
        Collections.shuffle(characters);
        String shuffledPattern = characters.stream()
                .map(String::valueOf)
                .collect(Collectors.joining());

        // Skip if by coincidence the shuffled pattern equals the original pattern
        if (shuffledPattern.equals(pattern)) {
            return;
        }

        /* Get follow-up output */
        int followIndex = Boyer.indexOf(text, shuffledPattern);

        /* Verification */
        assertEquals(-1, followIndex);
    }

    /**
     * Metamorphic Relation 20: If the pattern is found within the text, replacing
     * all occurrences of a character in the pattern with another unused character
     * in the text should maintain the index.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1 || pattern.isEmpty()) {
            return; // Return if the pattern is not found or is empty
        }

        // Identify a character unused in the text to replace a character in the pattern
        char replacementChar = (char) (text.chars().max().orElse(0) + 1);
        char patternCharToReplace = pattern.charAt(0); // Choose the first character for replacement

        /* Replace character in pattern */
        String modifiedPattern = pattern.replace(patternCharToReplace, replacementChar);

        // Ensure the modified pattern does not already exist in the text
        if (text.contains(modifiedPattern)) {
            return; // Return if the modified pattern exists in the text
        }

        /*
         * Construct follow-up input by replacing the occurrences of the character in
         * the text
         */
        String modifiedText = text.replace(patternCharToReplace, replacementChar);

        /* Get follow-up output */
        int modifiedIndex = Boyer.indexOf(modifiedText, modifiedPattern);

        /* Verification */
        assertEquals(originalIndex, modifiedIndex);
    }

    /**
     * Metamorphic Relation 21: Searching for a pattern in a subset of the text that
     * starts from the original occurrence index should return zero, indicating the
     * beginning of the subset.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return; // Pattern not found in the original text, so skip this test
        }

        /*
         * Construct follow-up input by taking a substring of text starting from the
         * original index
         */
        String subsetText = text.substring(originalIndex);

        /* Get follow-up output */
        int followIndex = Boyer.indexOf(subsetText, pattern);

        /* Verification */
        assertEquals(0, followIndex); // Pattern should be found at start of new text (index 0)
    }

    /**
     * Metamorphic Relation 22: If the pattern and its reverse are both found within
     * the text, then the relative order of the first occurrences should remain
     * consistent when the entire text is reversed.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        String reversedPattern = new StringBuilder(pattern).reverse().toString();
        int reversedPatternIndex = Boyer.indexOf(text, reversedPattern);

        // Only proceed if both pattern and its reverse are found
        if (originalIndex == -1 || reversedPatternIndex == -1) {
            return;
        }

        /* Reverse the text */
        String reversedText = new StringBuilder(text).reverse().toString();

        /* Get follow-up output for original and reversed patterns respectively */
        int followOriginalIndex = Boyer.indexOf(reversedText, reversedPattern);
        int followReversedIndex = Boyer.indexOf(reversedText, pattern);

        /* Verification */
        assertTrue(followOriginalIndex < followReversedIndex);
    }

    /**
     * Metamorphic Relation 23: Inserting the pattern in the middle of the text
     * should result in the new index being at least the length of the first half of
     * the text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(String text, String pattern) {
        // Skip if the pattern does not exist or if it's already at the start of the
        // text
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex <= 0) {
            return;
        }

        // Split the text into two halves
        int mid = text.length() / 2;
        String firstHalf = text.substring(0, mid);
        String secondHalf = text.substring(mid);

        /*
         * Construct follow-up input by inserting the pattern in the middle of the text
         */
        String newText = firstHalf + pattern + secondHalf;

        /* Get follow-up output */
        int newIndex = Boyer.indexOf(newText, pattern);

        /* Verification */
        assertTrue(newIndex >= firstHalf.length());
    }

    /**
     * Metamorphic Relation 24: If the pattern is right-centered in the original
     * text, adding arbitrary characters to the center should push the pattern's
     * index further right.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(String text, String pattern) {   // Fixed
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1 || originalIndex < text.length() / 2) {
            return; // Pattern is not found or is already at the end of the text
        }

        // Identify a unique substring that is not found in the text to insert in the
        // center
        SecureRandom rand = new SecureRandom();
        String uniqueString = RandomStringUtils.randomAscii(rand.nextInt(1, 10));
        while (text.contains(uniqueString) || uniqueString.contains(pattern)) {
            uniqueString = RandomStringUtils.randomAscii(rand.nextInt(1, 10));
        }

        // Insert the unique string in the middle of text
        int insertPosition = text.length() / 2; // Position before pattern start
        String newText = text.substring(0, insertPosition) + uniqueString + text.substring(insertPosition);

        /* Get follow-up output */
        int newIndex = Boyer.indexOf(newText, pattern);

        /* Verification */
        assertTrue(newIndex > originalIndex);
    }

    /**
     * Metamorphic Relation 25: If a pattern is found in the text, reversing the
     * substring from the start of the text to the index of pattern's occurrence
     * should not change the index of occurrence.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return;
        }

        /* Construct follow-up input by reversing substring up to the originalIndex */
        String reversedSubstring = new StringBuilder(text.substring(0, originalIndex)).reverse().toString();
        String newText = reversedSubstring + text.substring(originalIndex);

        /* Get follow-up output */
        int newIndex = Boyer.indexOf(newText, pattern);

        /* Verification */
        assertEquals(originalIndex, newIndex);
    }

    /**
     * Metamorphic Relation 26: Introducing typos by randomly altering characters in
     * the pattern should result in the altered pattern not being found in the
     * original text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(String text, String pattern) {
        if (pattern.isEmpty()) {
            return; // Skip if the pattern is empty as we cannot introduce typos.
        }

        /* Create a randomized altered pattern with one typo */
        Random random = new Random();
        char[] chars = pattern.toCharArray();
        char originalChar = chars[random.nextInt(chars.length)];
        char alteredChar = (char) ('a' + random.nextInt(26)); // Assuming only lower-case letters
        while (alteredChar == originalChar) { // Ensure a different character is chosen
            alteredChar = (char) ('a' + random.nextInt(26));
        }
        chars[random.nextInt(chars.length)] = alteredChar;
        String alteredPattern = new String(chars);

        /* Get follow-up output */
        int alteredIndex = Boyer.indexOf(text, alteredPattern);

        /* Verification */
        assertEquals(-1, alteredIndex);
    }

    /**
     * Metamorphic Relation 27: Swapping the halves of the pattern should result in
     * the swapped pattern not being found in the original text assuming the pattern
     * doesn't contain repetitive halves.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(String text, String pattern) {
        if (pattern.length() < 2) {
            return;
        }

        /* Split pattern into two halves */
        int mid = pattern.length() / 2;
        String firstHalf = pattern.substring(0, mid);
        String secondHalf = pattern.substring(mid);

        /* Only valid if the two halves are different */
        if (firstHalf.equals(secondHalf)) {
            return;
        }

        /* Construct follow-up input by swapping halves */
        String swappedPattern = secondHalf + firstHalf;

        /* Get follow-up output */
        int swappedIndex = Boyer.indexOf(text, swappedPattern);

        /* Verification */
        assertEquals(-1, swappedIndex);
    }

    /**
     * Metamorphic Relation 28: Concatenating a string to the beginning and end of
     * the text should change the index of the pattern's occurrence by the length of
     * the string if the string does not contain the pattern.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return;
        }

        /*
         * Construct follow-up input by adding a non-overlapping string to the beginning
         * and end
         */
        String nonOverlappingString = "nonoverlap";
        String modifiedText = nonOverlappingString + text + nonOverlappingString;

        // Ensure the added string does not contain the pattern
        if (nonOverlappingString.contains(pattern)) {
            return;
        }

        /* Get follow-up output */
        int modifiedIndex = Boyer.indexOf(modifiedText, pattern);

        /* Verification */
        assertEquals(originalIndex + nonOverlappingString.length(), modifiedIndex);
    }

    /**
     * Metamorphic Relation 29: If the pattern is found in text and then all
     * characters of the text are capitalized, the pattern should still be found at
     * the same index (if case-insensitive).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(String text, String pattern) {   // Fixed
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return;
        }

        /* Capitalize all characters of text */
        String capitalizedText = text.toUpperCase();

        /* Capitalize characters of pattern */
        String capitalizedPattern = pattern.toUpperCase();

        /* Get follow-up output (assuming case-insensitive search) */
        int capitalizedIndex = Boyer.indexOf(capitalizedText, pattern);

        /* Verification */
        assertEquals(originalIndex, capitalizedIndex);
    }

    /**
     * Metamorphic Relation 30: If a pattern is found in the text, inserting a
     * string in the text before the pattern occurrence should increase the index by
     * the length of the inserted string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return; // Pattern not found in the original text, so skip this test
        }

        /*
         * Construct follow-up input by inserting a string before the pattern occurrence
         */
        String insertString = "!insert!";
        SecureRandom rand = new SecureRandom();
        while (insertString.contains(pattern)) {
            insertString = RandomStringUtils.randomAscii(rand.nextInt(1, 10));
        }
        String followText = text.substring(0, originalIndex) + insertString + text.substring(originalIndex);

        /* Get follow-up output */
        int followIndex = Boyer.indexOf(followText, pattern);

        /* Verification */
        assertEquals(originalIndex + insertString.length(), followIndex);
    }

    /**
     * Metamorphic Relation 31: If the pattern consists of repeated characters,
     * reversing the pattern should not change the result of its occurrence index in
     * the text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(String text, String pattern) {
        if (!pattern.equals(new String(new char[pattern.length()]).replace("\0", String.valueOf(pattern.charAt(0))))) {
            return; // Pattern is not made of repeated characters, so skip this test
        }

        /* Get original output */
        int originalIndex = Boyer.indexOf(text, pattern);

        /* Construct reversed pattern */
        String reversedPattern = new StringBuilder(pattern).reverse().toString();

        /* Get follow-up output */
        int reversedIndex = Boyer.indexOf(text, reversedPattern);

        /* Verification */
        assertEquals(originalIndex, reversedIndex);
    }

    /**
     * Metamorphic Relation 32: Increasing the length of the text by duplication
     * should not change the index of the first occurrence of the pattern.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return; // Pattern not found in the original text, so skip this test
        }

        /* Construct follow-up input by duplicating the text */
        String duplicatedText = text + text;

        /* Get follow-up output */
        int duplicatedTextIndex = Boyer.indexOf(duplicatedText, pattern);

        /* Verification */
        assertEquals(originalIndex, duplicatedTextIndex);
    }

    /**
     * Metamorphic Relation 33: Trimming the text from both ends (if it contains
     * whitespaces) should not alter the occurrence index of the pattern if it's not
     * adjacent to the whitespace.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(String text, String pattern) {
        if (text.trim().equals(text)) {
            return; // Text is already trimmed or does not have leading/trailing whitespaces, so
                    // skip this test
        }

        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex <= text.indexOf(' ') || originalIndex >= text.lastIndexOf(' ')) {
            return; // Pattern occurrence index is adjacent to the whitespace, so skip this test
        }

        /* Trim the text */
        String trimmedText = text.trim();

        /* Get follow-up output */
        int trimmedTextIndex = Boyer.indexOf(trimmedText, pattern);

        /* Compute the expected new index after trimming */
        int expectedIndex = originalIndex - text.indexOf(trimmedText);

        /* Verification */
        assertEquals(expectedIndex, trimmedTextIndex);
    }

    /**
     * Metamorphic Relation 34: If text and pattern are both converted to lowercase
     * and the pattern is present in the original mixed case text, the index should
     * remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(String text, String pattern) {
        int mixedCaseIndex = Boyer.indexOf(text, pattern);
        if (mixedCaseIndex == -1) {
            return; // Pattern not found in the mixed case original text, so skip this test
        }

        /* Convert text and pattern to lowercase */
        String lowerText = text.toLowerCase();
        String lowerPattern = pattern.toLowerCase();

        /* Get follow-up output */
        int lowerCaseIndex = Boyer.indexOf(lowerText, lowerPattern);

        /* Verification */
        assertEquals(mixedCaseIndex, lowerCaseIndex);
    }

    /**
     * Metamorphic Relation 35: If both text and pattern are encoded (e.g., base64)
     * and the pattern is found in the original text, the occurrence index should
     * change according to the encoding transformation.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(String text, String pattern) throws UnsupportedEncodingException {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return; // Pattern not found in the original text, so skip this test
        }

        /* Encode text and pattern using base64 encoding */
        String encodedText = Base64.getEncoder().encodeToString(text.getBytes("UTF-8"));
        String encodedPattern = Base64.getEncoder().encodeToString(pattern.getBytes("UTF-8"));

        /* Get follow-up output */
        int encodedIndex = Boyer.indexOf(encodedText, encodedPattern);

        /*
         * The encoded pattern index should be different due to the nature of the
         * encoding
         */
        assertNotEquals(originalIndex, encodedIndex);

        /* Convert the encoded index back to see if it aligns with the original text */
        if (encodedIndex != -1) {
            String decodedSubstring = new String(
                    Base64.getDecoder().decode(encodedText.substring(0, encodedIndex + encodedPattern.length())),
                    "UTF-8");
            assertEquals(originalIndex, decodedSubstring.length() - pattern.length());
        }
    }

    /**
     * Metamorphic Relation 36: Replacing all occurrences of a specific character in
     * the pattern with a different character (not present in the text) should
     * change the outcome to "-1" as the pattern should not be found.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1 || pattern.isEmpty()) {
            return; // Pattern not found or is empty, so skip this test
        }

        /* Find a character that is not used in the text */
        char replacementChar = 'A'; // Start with 'A'
        while (text.indexOf(replacementChar) != -1) {
            replacementChar++;
        }

        /* Create the modified pattern */
        char charToReplace = pattern.charAt(0); // Use the first character of the pattern
        String modifiedPattern = pattern.replace(charToReplace, replacementChar);

        /* Ensure the modified pattern does not exist in the original text */
        if (text.contains(modifiedPattern)) {
            return;
        }

        /* Get follow-up output */
        int followIndex = Boyer.indexOf(text, modifiedPattern);

        /* Verification */
        assertEquals(-1, followIndex);
    }

    /**
     * Metamorphic Relation 37: If the text is concatenated with itself in reverse
     * order and the pattern exists, the pattern's index should be either the same
     * or be present after the halfway mark of the new text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return; // Pattern not found, so skip this test
        }

        /* Create new text by concatenating with its reverse */
        String reversedText = new StringBuilder(text).reverse().toString();
        String newText = text + reversedText;

        /* Get follow-up output */
        int newIndex = Boyer.indexOf(newText, pattern);

        /* Verification */
        assertTrue(newIndex == originalIndex || newIndex > text.length());
    }

    /**
     * Metamorphic Relation 38: If the pattern consists of a single character,
     * doubling that character in the pattern should either find the pattern twice
     * in succession or not at all.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(String text, String pattern) {
        if (pattern.length() != 1) {
            return; // Pattern length is not 1, so skip this test
        }

        /* Double the character in the pattern */
        String doubledPattern = pattern + pattern;

        /* Get follow-up output */
        int followIndex = Boyer.indexOf(text, doubledPattern);

        /* Verification */
        if (followIndex != -1) {
            // The character after the doubled pattern index should be the same if the
            // pattern exists twice in succession
            assertEquals(text.charAt(followIndex + 1), pattern.charAt(0));
        } else {
            // The doubled character pattern is not found
            assertTrue(true);
        }
    }

    /**
     * Metamorphic Relation 39: Converting the text and pattern to upper case should
     * not change the index of occurrence if both original text and pattern contain
     * only alphabetical characters and the search is case-insensitive.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(String text, String pattern) {
        // Skip if the pattern does not exist or contains non-alphabetical characters
        if (Boyer.indexOf(text, pattern) == -1 || !text.matches("[a-zA-Z]+") || !pattern.matches("[a-zA-Z]+")) {
            return;
        }

        /* Convert text and pattern to upper case */
        String upperText = text.toUpperCase();
        String upperPattern = pattern.toUpperCase();

        /* Get follow-up output */
        int upperCaseIndex = Boyer.indexOf(upperText, upperPattern);

        /* Verification */
        assertEquals(Boyer.indexOf(text, pattern), upperCaseIndex);
    }

    /**
     * Metamorphic Relation 40: If the pattern is found in the original text,
     * removing a random subset of characters from the text that excludes the
     * pattern occurrence should not change the occurrence index.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return; // Pattern not found, so skip this test
        }

        /*
         * Randomly remove characters that do not overlap with the pattern's occurrence
         */
        Random rand = new Random();
        StringBuilder sb = new StringBuilder(text);
        for (int i = sb.length() - 1; i >= 0; i--) {
            if (i < originalIndex || i >= originalIndex + pattern.length()) {
                if (rand.nextBoolean()) { // Randomly decide to remove each character
                    sb.deleteCharAt(i);
                }
            }
        }
        String modifiedText = sb.toString();

        /* Get follow-up output */
        int followIndex = Boyer.indexOf(modifiedText, pattern);

        /* Verification */
        assertEquals(originalIndex, followIndex);
    }

    /**
     * Metamorphic Relation 41: If the pattern is found in the text, swapping the
     * pattern with an adjacent section of the text should not change the overall
     * occurrence of pattern sections.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test41(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1 || originalIndex + pattern.length() >= text.length()) {
            return; // Pattern not found or no adjacent section to swap with, so skip this test
        }

        /*
         * Construct follow-up input by swapping the pattern with adjacent section of
         * text
         */
        String adjacentSection = text.substring(originalIndex + pattern.length(),
                Math.min(text.length(), originalIndex + 2 * pattern.length()));
        String modifiedText = text.substring(0, originalIndex) + adjacentSection
                + pattern + text.substring(originalIndex + pattern.length() + adjacentSection.length());

        /* Get follow-up output */
        int modifiedIndex = Boyer.indexOf(modifiedText, pattern);

        /* Verification */
        // The pattern should still be found at least once in the modified text
        assertTrue(modifiedIndex != -1);
        // The first occurrence in the modified text should be no later than in the
        // original text
        assertTrue(modifiedIndex <= originalIndex + adjacentSection.length());
    }

    /**
     * Metamorphic Relation 42: If a pattern is found at the end of the text,
     * appending the text to itself should result in the new occurrence index being
     * exactly twice the original.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test42(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1 || !text.endsWith(pattern)) {
            return; // Pattern not found or not at the end, so skip this test
        }

        /* Append text to itself */
        String newText = text + text;

        /* Get follow-up output */
        int newIndex = Boyer.indexOf(newText, pattern);

        /* Verification */
        assertEquals(2 * originalIndex, newIndex);
    }

    static Stream<Arguments> testcaseProvider() throws IOException {
        return testcaseGenerator.generate_ss(1000);
    }

}
