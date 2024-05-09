package test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import org.apache.commons.lang3.RandomStringUtils;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import src.Boyer;

public class BoyerTestGPT4 {
    /**
     * Metamorphic Relation 1: If the pattern is found in the text, appending any string to both the
     * pattern and the text should not change the outcome of the original index.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        String suffix = "suffix";

        /* Get original output */
        int originalIndex = Boyer.indexOf(text, pattern);

        /* Construct follow-up inputs */
        String newText = text + suffix;
        String newPattern = pattern + suffix;

        /* Get follow-up output */
        int followUpIndex = Boyer.indexOf(newText, newPattern);

        /* Verify the relation */
        assertEquals(originalIndex, followUpIndex);
    }

    /**
     * Metamorphic Relation 2: If a pattern is found in the text, inserting a string that does not
     * contain the pattern anywhere in the text should not affect the original index of the pattern
     * found in the text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        String insertString = "XYZ";

        /* Get original output */
        int originalIndex = Boyer.indexOf(text, pattern);

        /* Construct follow-up inputs */
        // Assume the insert position is at the beginning of the text
        String newText = insertString + text;

        /* Get follow-up output */
        int followUpIndex = Boyer.indexOf(newText, pattern);

        /* Verify the relation */
        assertEquals(originalIndex + insertString.length(), followUpIndex);
    }

    /**
     * Metamorphic Relation 3: If the pattern is found in the text, reversing both the text and the
     * pattern should result in the index being calculated from the end of the string, rather than
     * the beginning.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get original output */
        int originalIndex = Boyer.indexOf(text, pattern);

        /* Construct follow-up inputs */
        String reversedText = new StringBuilder(text).reverse().toString();
        String reversedPattern = new StringBuilder(pattern).reverse().toString();

        /* Get follow-up output */
        int reversedPatternIndex = Boyer.indexOf(reversedText, reversedPattern);

        /* Verify the relation */
        assertEquals(text.length() - originalIndex - pattern.length(), reversedPatternIndex);
    }

    /**
     * Metamorphic Relation 4: Searching for an empty pattern '' in any text should always return 0,
     * since the empty string is trivially at the beginning of every string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(String text, String pattern) {
        /* Get the result of searching for an empty pattern */
        int result = Boyer.indexOf(text, "");

        /* Verify the outcome */
        assertEquals(0, result);
    }

    /**
     * Metamorphic Relation 5: Searching for the same pattern in a text that has been duplicated
     * should return the same index for the first occurrence of the pattern.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get the original output */
        int originalIndex = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String duplicatedText = text + text;

        /* Get follow-up output */
        int followUpIndex = Boyer.indexOf(duplicatedText, pattern);

        /* Verify the relation */
        assertEquals(originalIndex, followUpIndex);
    }

    /**
     * Metamorphic Relation 6: If the pattern is found in the text, prepending a string to the text
     * should shift the index of occurrence by the length of the prepended string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(String text, String pattern) {
        if (text.indexOf(pattern) == -1 || text.startsWith(pattern)) {
            return; // Early return if the pattern is not found or is at the start of the text
        }

        String prefix = "prefix";

        /* Get original output */
        int originalIndex = Boyer.indexOf(text, pattern);

        /* Construct follow-up inputs */
        String newText = prefix + text;

        /* Get follow-up output */
        int followUpIndex = Boyer.indexOf(newText, pattern);

        /* Verify the relation */
        assertEquals(originalIndex + prefix.length(), followUpIndex);
    }

    /**
     * Metamorphic Relation 7: If the pattern is found in text, searching for the same pattern with
     * an additional character at the beginning should produce either -1 (not found) or an index
     * greater than or equal to the original.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get original output */
        int originalIndex = Boyer.indexOf(text, pattern);

        /* Construct follow-up inputs */
        String newPattern = "a" + pattern;

        /* Get follow-up output */
        int followUpIndex = Boyer.indexOf(text, newPattern);

        /* Verify the relation */
        assertTrue(followUpIndex == -1 || followUpIndex >= originalIndex);
    }

    /**
     * Metamorphic Relation 8: If the pattern is not found in the text, appending any non-empty
     * string to the pattern should still result in -1, as the extended pattern cannot be found in
     * the original text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(String text, String pattern) {
        if (text.indexOf(pattern) != -1) {
            return;
        }

        /* Find the pattern */
        int result = Boyer.indexOf(text, pattern);

        /* Extend the pattern */
        String extendedPattern = pattern + "b";

        /* Search again */
        int extendedResult = Boyer.indexOf(text, extendedPattern);

        /* Verify that the pattern is still not found */
        assertEquals(-1, extendedResult);
    }

    /**
     * Metamorphic Relation 9: Searching in a text substring that excludes the pattern occurrence
     * should result in -1, assuming the substring is taken from the start of the original text to a
     * character before the pattern begins.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(String text, String pattern) {
        int indexOfPatternInText = text.indexOf(pattern);
        if (indexOfPatternInText == -1) {
            return;
        }

        /* Construct a substring of the original text that ends before the pattern */
        String subText = text.substring(0, indexOfPatternInText);

        /* Search for the pattern in the substring */
        int result = Boyer.indexOf(subText, pattern);

        /* Verify that the pattern is not found in the substring */
        assertEquals(-1, result);
    }

    /**
     * Metamorphic Relation 10: If the pattern is found in the text and the text is prefixed with a
     * string that does not contain the pattern, the resulting index should be increased by the
     * length of the prefix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String text, String pattern) { // Fixed
        int index = Boyer.indexOf(text, pattern);
        if (index == -1) {
            return;
        }

        String prefix = "prefix_";

        /* Make sure prefixed text does not contain the pattern */
        while (prefix.indexOf(pattern) != -1) {
            prefix = RandomStringUtils.randomAlphabetic(6);
        }

        /* Get follow-up output */
        int followUpIndex = Boyer.indexOf(prefix + text, pattern);

        /* Verify the relation */
        assertEquals(index + prefix.length(), followUpIndex);
    }

    /**
     * Metamorphic Relation 11: If the pattern is found in the text, searching for it in an
     * all-uppercase or all-lowercase version of the text should yield -1 or an index not less than
     * the original, provided the pattern and text are not already in the same case.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(String text, String pattern) {
        int index = Boyer.indexOf(text, pattern);
        if (index == -1 || text.equals(text.toUpperCase())
                || pattern.equals(pattern.toUpperCase())) {
            return;
        }

        /* Get follow-up output for uppercase */
        int followUpUpperCaseIndex = Boyer.indexOf(text.toUpperCase(), pattern.toUpperCase());

        /* Verify the relation for uppercase */
        assertTrue(followUpUpperCaseIndex == -1 || followUpUpperCaseIndex >= index);

        /* Get follow-up output for lowercase */
        int followUpLowerCaseIndex = Boyer.indexOf(text.toLowerCase(), pattern.toLowerCase());

        /* Verify the relation for lowercase */
        assertTrue(followUpLowerCaseIndex == -1 || followUpLowerCaseIndex >= index);
    }

    /**
     * Metamorphic Relation 12: Replacing an occurrence of the pattern in the text with a different
     * string of the same length should not change the index of the first occurrence prior to the
     * replaced pattern.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(String text, String pattern) {
        int index = Boyer.indexOf(text, pattern);
        if (index == -1) {
            return;
        }
        String replacement = "repl";
        if (pattern.length() != replacement.length() || text.length() < index + pattern.length()) {
            return;
        }

        String newText =
                text.substring(0, index) + replacement + text.substring(index + pattern.length());

        /* Get follow-up output */
        int followUpIndex = Boyer.indexOf(newText, pattern);

        /* Verify the relation */
        assertEquals(index, followUpIndex);
    }

    /**
     * Metamorphic Relation 13: If the original text does not contain the pattern, then reversing
     * the text should still result in the pattern not being found.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(String text, String pattern) {
        if (text.indexOf(pattern) != -1) {
            return; // Pattern is found, relation does not apply.
        }

        /* Reverse the text */
        String reversedText = new StringBuilder(text).reverse().toString();

        /* Search for the pattern in the reversed text */
        int result = Boyer.indexOf(reversedText, pattern);

        /* Verify that the pattern is not found in the reversed text either */
        assertEquals(-1, result);
    }

    /**
     * Metamorphic Relation 14: If the pattern is found within the text, searching within a larger
     * scope by concatenating the text to itself multiple times should yield the same index for the
     * first occurrence or multiples of the original text's length if the occurrences repeat.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return;
        }

        String newText = text + text; // Doubling the text

        /* Get the index of the pattern in the new (doubled) text */
        int newIndex = Boyer.indexOf(newText, pattern);

        /* Verify the index is the same */
        assertEquals(originalIndex, newIndex);
    }

    /**
     * Metamorphic Relation 15: Searching for the concatenated pattern within a text that contains
     * the pattern followed by itself should return the index of the first pattern's first
     * occurrence.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String text, String pattern) throws Exception {
        int index = Boyer.indexOf(text, pattern);
        if (index == -1 || (index + pattern.length() * 2) > text.length()) {
            return;
        }

        String newPattern = pattern + pattern; // Concatenating the pattern with itself
        int newIndex = Boyer.indexOf(text, newPattern);
        int expectedIndex = text.indexOf(newPattern); // Expected index using String's native method

        /* Verify the new index is as expected and not -1 */
        assertEquals(expectedIndex, newIndex);
    }

    /**
     * Metamorphic Relation 16: If the pattern is found in the text, then searching for this pattern
     * within the last part of the text, starting from the original found index, should yield an
     * index of 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return;
        }

        String subtext = text.substring(originalIndex);
        int newIndex = Boyer.indexOf(subtext, pattern);

        /* Verify the pattern is found at index 0 in the substring */
        assertEquals(0, newIndex);
    }

    /**
     * Metamorphic Relation 17: If a non-empty pattern is not found within the text, appending the
     * pattern to the text should result in the pattern being found at the index that equals the
     * length of the original text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String text, String pattern) {
        if (pattern.isEmpty() || text.indexOf(pattern) != -1) {
            return;
        }

        String newText = text + pattern;
        int newIndex = Boyer.indexOf(newText, pattern);

        /* Verify the pattern is found at an index that equals the length of the original text */
        assertEquals(text.length(), newIndex);
    }

    /**
     * Metamorphic Relation 18: If the pattern is found in the text, searching for the combination
     * of text and the reversed pattern should lead to the result being -1 (unless the pattern is a
     * palindrome).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String text, String pattern) {
        if (text.indexOf(pattern) == -1
                || new StringBuilder(pattern).reverse().toString().equals(pattern)) {
            return; // The pattern is not found or is a palindrome.
        }

        String reversedPattern = new StringBuilder(pattern).reverse().toString();
        int result = Boyer.indexOf(text, reversedPattern);

        /* Verify that the reversed pattern is not found */
        assertEquals(-1, result);
    }

    /**
     * Metamorphic Relation 19: If the pattern is not found in the text, reversing the pattern and
     * searching again should still result in not finding the pattern (-1), unless the pattern is a
     * palindrome.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex != -1
                || new StringBuilder(pattern).reverse().toString().equals(pattern)) {
            return; // The pattern is found or is a palindrome.
        }

        String reversedPattern = new StringBuilder(pattern).reverse().toString();
        int newIndex = Boyer.indexOf(text, reversedPattern);

        /* Verify that the reversed pattern is not found */
        assertEquals(-1, newIndex);
    }

    /**
     * Metamorphic Relation 20: If the pattern is found in the text, inserting a string not
     * containing the pattern anywhere before the found pattern index, should increase the original
     * found index by the length of the inserted string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(String text, String pattern) {   // Fixed
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return;
        }

        String insertion = "insert";

        /* Make sure inserting string not containing the pattern */
        while (insertion.indexOf(pattern) != -1) {
            insertion = RandomStringUtils.randomAlphabetic(6);
        }

        String newText =
                text.substring(0, originalIndex) + insertion + text.substring(originalIndex);

        int newIndex = Boyer.indexOf(newText, pattern);

        /* Verify the index is increased by the length of the inserted string */
        assertEquals(originalIndex + insertion.length(), newIndex);
    }

    /**
     * Metamorphic Relation 21: If the pattern occurs multiple times in the text, and the text prior
     * to the second occurrence is removed, the index of the first occurrence in the modified text
     * should be the same as the index of the second occurrence in the original text minus the
     * length of the removed part.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(String text, String pattern) {
        int firstIndex = Boyer.indexOf(text, pattern);
        int secondIndex = text.indexOf(pattern, firstIndex + 1);
        if (firstIndex == -1 || secondIndex == -1) {
            return; // Pattern doesn't occur twice.
        }

        String modifiedText = text.substring(secondIndex);
        int newFirstIndex = Boyer.indexOf(modifiedText, pattern);

        /* Verify the altered text's first pattern index is correct */
        assertEquals(0, newFirstIndex);
    }

    /**
     * Metamorphic Relation 22: If the pattern is found at multiple indices, then adding a distinct
     * string at the beginning of the pattern should result in either not finding the pattern (-1)
     * or finding it at the same indices as the original occurrences.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(String text, String pattern) {
        List<Integer> originalIndices = new ArrayList<>();
        int index = text.indexOf(pattern);
        while (index >= 0) {
            originalIndices.add(index);
            index = text.indexOf(pattern, index + 1);
        }

        if (originalIndices.isEmpty()) {
            return; // Pattern does not occur.
        }

        String distinctString = "dist";
        String newPattern = distinctString + pattern;
        List<Integer> newIndices = new ArrayList<>();
        int newIndex = text.indexOf(newPattern);
        while (newIndex >= 0) {
            newIndices.add(newIndex);
            newIndex = text.indexOf(newPattern, newIndex + 1);
        }

        /* Verify the indices of occurrences are correct after modification */
        if (!newIndices.isEmpty()) {
            assertTrue(originalIndices.equals(newIndices.stream()
                    .map(i -> i - distinctString.length()).collect(Collectors.toList())));
        } else {
            assertEquals(-1, newIndex); // The pattern with prepended string was not found.
        }
    }

    /**
     * Metamorphic Relation 23: If the pattern and text are identical, the index of the first
     * occurrence of the pattern should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(String text) {
        int index = Boyer.indexOf(text, text);

        /* Verify that the pattern (which is identical to text) is found at index 0 */
        assertEquals(0, index);
    }

    /**
     * Metamorphic Relation 24: If the pattern is found in the text, searching for the pattern with
     * additional characters at its end within the text should yield -1 or an index greater than or
     * equal to the original index.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return;
        }

        /* Append extra characters to the pattern */
        String newPattern = pattern + "extra";

        /* Search for the new pattern */
        int newIndex = Boyer.indexOf(text, newPattern);

        /* Verify that the new pattern is either not found or found at an index >= original index */
        assertTrue(newIndex == -1 || newIndex >= originalIndex);
    }

    /**
     * Metamorphic Relation 25: If the pattern is found in the text, then any substring of the text
     * that includes the pattern occurrence should yield a valid index for the pattern, which is the
     * original index minus the start index of the substring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return;
        }

        /* Take a substring that includes the pattern occurrence */
        int substringStart = Math.max(0, originalIndex - 5); // Ensure that the start index is
                                                             // positive
        String subText = text.substring(substringStart);

        /* Search for the pattern in the substring */
        int newIndex = Boyer.indexOf(subText, pattern);

        /* Verify the index in substring is adjusted by the start index of substring */
        assertEquals(originalIndex - substringStart, newIndex);
    }

    /**
     * Metamorphic Relation 26: If the pattern is found in the text, and the text is partitioned
     * around the pattern, searching in the concatenated second and first parts should not find the
     * pattern.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1 || text.endsWith(pattern)) {
            return;
        }

        /* Partition text around the pattern */
        int partitionIndex = originalIndex + pattern.length();
        String firstPart = text.substring(0, partitionIndex);
        String secondPart = text.substring(partitionIndex);

        /* Concatenate the second part in front of the first */
        String rotatedText = secondPart + firstPart;

        /* Search for the pattern in the rotated text */
        int newIndex = Boyer.indexOf(rotatedText, pattern);

        /* The pattern should be split and therefore not found */
        assertEquals(-1, newIndex);
    }

    /**
     * Metamorphic Relation 27: If the pattern is found in the text, then any rotation of the text
     * should either not find the pattern or find it at different indices corresponding to the
     * rotation.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1 || originalIndex == 0 || text.length() == pattern.length()) {
            return;
        }

        /* Rotate the text one character to the left */
        String rotatedText = text.substring(1) + text.charAt(0);

        /* Search for the pattern in the rotated text */
        int newIndex = Boyer.indexOf(rotatedText, pattern);

        /*
         * The new index should be -1 (if the pattern was at the start of the original text), or the
         * original index should be decremented by 1 (due to left rotation).
         */
        if (originalIndex == 1) {
            assertEquals(rotatedText.length() - 1, newIndex);
        } else {
            assertTrue(newIndex == -1 || newIndex == originalIndex - 1);
        }
    }

    /**
     * Metamorphic Relation 28: If the text contains the pattern, reversing both the text and the
     * pattern should yield the index of the pattern in the reversed text which is equal to the
     * length of the original text minus the end index of the pattern in the original text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return;
        }

        /* Reverse both the text and the pattern */
        String reversedText = new StringBuilder(text).reverse().toString();
        String reversedPattern = new StringBuilder(pattern).reverse().toString();

        /* Search for the reversed pattern in the reversed text */
        int reversedIndex = Boyer.indexOf(reversedText, reversedPattern);

        /* Calculate the expected index in the reversed text */
        int expectedReversedIndex = text.length() - (originalIndex + pattern.length());

        /* Verify that the index matches the expected index in the reversed text */
        assertEquals(expectedReversedIndex, reversedIndex);
    }

    /**
     * Metamorphic Relation 29: If the pattern is not found in the text, changing the case (to
     * uppercase or lowercase) of both the text and pattern should still result in the pattern not
     * being found.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(String text, String pattern) {
        int index = Boyer.indexOf(text, pattern);
        // Proceed only if the pattern is not found in the original text
        if (index != -1) {
            return;
        }

        // Change text and pattern to uppercase
        int upperCaseIndex = Boyer.indexOf(text.toUpperCase(), pattern.toUpperCase());
        assertEquals(-1, upperCaseIndex);

        // Change text and pattern to lowercase
        int lowerCaseIndex = Boyer.indexOf(text.toLowerCase(), pattern.toLowerCase());
        assertEquals(-1, lowerCaseIndex);
    }

    /**
     * Metamorphic Relation 30: If the original text starts with the pattern, prepending the text
     * with any string should not change the occurrence index of the second (original) pattern.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(String text, String pattern) {
        if (!text.startsWith(pattern)) {
            return;
        }

        String prependString = "prepend";
        String newText = prependString + text;
        int newIndex = Boyer.indexOf(newText, pattern);
        // Original pattern occurrence index + length of the prepended string
        int expectedIndex = 0 + prependString.length();
        assertEquals(expectedIndex, newIndex);
    }

    /**
     * Metamorphic Relation 31: If the pattern is found at the end of the text, then appending any
     * string to the text should not affect the index of the first occurrence of the pattern.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(String text, String pattern) {
        if (!text.endsWith(pattern)) {
            return;
        }

        int originalIndex = Boyer.indexOf(text, pattern);
        String appendString = "append";
        String newText = text + appendString;
        int newIndex = Boyer.indexOf(newText, pattern);
        assertEquals(originalIndex, newIndex);
    }

    /**
     * Metamorphic Relation 32: If a pattern is found followed immediately by another instance, then
     * searching for two patterns concatenated should result in the index of the first occurrence.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(String text, String pattern) {
        String doublePattern = pattern + pattern;
        if (!text.contains(doublePattern)) {
            return; // Proceed only if the text contains two consecutive patterns
        }

        int index = Boyer.indexOf(text, doublePattern);
        // We expect to find the double pattern at the index of the first occurrence
        int expectedIndex = text.indexOf(pattern);
        assertEquals(expectedIndex, index);
    }

    /**
     * Metamorphic Relation 33: Adding any prefix to both the text and the pattern should not affect
     * the result of the search operation within the new, longer text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(String text, String pattern) {
        String prefix = "common_prefix_";
        String newText = prefix + text;
        String newPattern = prefix + pattern;
        // To apply this relation, we need to ensure that the new pattern is still within the new
        // text
        if (!newText.contains(newPattern)) {
            return;
        }

        int originalIndex = Boyer.indexOf(text, pattern);
        int newIndex = Boyer.indexOf(newText, newPattern);

        // Because the prefix was added to both text and pattern, we expect to find the new pattern
        // at the same index
        assertEquals(originalIndex, newIndex);
    }

    /**
     * Metamorphic Relation 34: If a pattern is searched within a substring of the text which
     * doesn't contain the pattern, the search should return -1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(String text, String pattern) {
        int index = Boyer.indexOf(text, pattern);
        // Create a substring that does not include the found pattern
        if (index >= 0 && index < text.length() - 1) {
            String nonContainingText = text.substring(index + 1);
            int nonContainingIndex = Boyer.indexOf(nonContainingText, pattern);
            assertEquals(-1, nonContainingIndex);
        }
    }

    /**
     * Metamorphic Relation 35: If the pattern is found in the text, removing a non-matching prefix
     * from the text should not affect the position of the pattern relative to the new start of the
     * text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(String text, String pattern) {
        int index = Boyer.indexOf(text, pattern);
        // Remove a non-matching prefix and perform the search again
        if (index > 0) {
            String modifiedText = text.substring(1);
            int newIndex = Boyer.indexOf(modifiedText, pattern);
            // The pattern should now be found one position earlier than before
            assertEquals(index - 1, newIndex);
        }
    }

    /**
     * Metamorphic Relation 36: If the text contains the pattern, searching for the same pattern
     * within the text padded with non-matching characters should yield the same index as the
     * unpadded text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(String text, String pattern) {
        int index = Boyer.indexOf(text, pattern);
        // Pad the text with non-matching characters
        if (index != -1) {
            String padding = "zzz";
            String paddedText = padding + text + padding;
            int newIndex = Boyer.indexOf(paddedText, pattern);
            // Index in the padded text should be increased by the length of the padding
            assertEquals(index + padding.length(), newIndex);
        }
    }

    /**
     * Metamorphic Relation 37: If the pattern is found within the text, searching for it again
     * after inverting the case of both the text and pattern should either result in the same index
     * or -1, depending on whether the case change affects matching.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return; // Skip cases where the pattern was not found
        }

        // Invert the case
        String newText = invertCase(text);
        String newPattern = invertCase(pattern);

        int newIndex = Boyer.indexOf(newText, newPattern);
        // If case inverts matching, index should stay the same or the pattern might not be found
        assertTrue(newIndex == -1 || newIndex == originalIndex);
    }

    /**
     * Metamorphic Relation 38: If the pattern is found within the text, searching for the pattern
     * after shuffling characters within the pattern (but not in text) should result in -1,
     * indicating the pattern does not match in its modified form.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(String text, String pattern) {
        if (pattern.length() <= 1) {
            return; // Shuffling a single character or empty string yields the same string
        }

        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex != -1) {
            String shuffledPattern = shuffleString(pattern);
            int shuffledIndex = Boyer.indexOf(text, shuffledPattern);
            // The search should fail since the pattern has been modified
            assertEquals(-1, shuffledIndex);
        }
    }

    // Auxiliary method to shuffle characters within a string
    private static String shuffleString(String input) {
        List<Character> characters =
                input.chars().mapToObj(c -> (char) c).collect(Collectors.toList());
        Collections.shuffle(characters);
        StringBuilder stringBuilder = new StringBuilder(input.length());
        for (char ch : characters) {
            stringBuilder.append(ch);
        }
        return stringBuilder.toString();
    }

    // Auxiliary method to invert case
    private static String invertCase(String input) {
        char[] chars = input.toCharArray();
        for (int i = 0; i < chars.length; i++) {
            chars[i] = Character.isUpperCase(chars[i]) ? Character.toLowerCase(chars[i])
                    : Character.toUpperCase(chars[i]);
        }
        return new String(chars);
    }

    /**
     * Metamorphic Relation 39: If the pattern is found in the text, and characters are inserted
     * between every character in the text (not affecting the pattern), the first occurrence index
     * should now be greater by a factor of the number of intervening characters.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex == -1) {
            return;
        }

        // Inserting characters between each character in the text
        String interveningChar = "#";
        String newText = insertBetweenEveryChar(text, interveningChar);

        int newIndex = Boyer.indexOf(newText, pattern);

        // Verify that the index adjusts according to the intervening characters
        assertEquals(originalIndex * (1 + interveningChar.length()), newIndex);
    }

    /**
     * Metamorphic Relation 40: If the pattern is at the start of the text, removing the first
     * occurrence of the pattern should result in the index of the next occurrence being 0 or not
     * found (-1) if pattern only occurred once.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(String text, String pattern) {
        int firstIndex = Boyer.indexOf(text, pattern);
        if (firstIndex != 0) {
            return; // Pattern not at the start
        }

        // Create new text with the first occurrence removed
        String newText = text.substring(pattern.length());

        int newIndex = Boyer.indexOf(newText, pattern);

        // If the pattern occurred only once, it should now yield -1, otherwise 0
        assertTrue(newIndex == -1 || newIndex == 0);
    }

    /**
     * Auxiliary method to insert a string between every character of text.
     */
    private static String insertBetweenEveryChar(String text, String insert) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < text.length(); i++) {
            if (i > 0) {
                sb.append(insert);
            }
            sb.append(text.charAt(i));
        }
        return sb.toString();
    }

    static Stream<Arguments> testcaseProvider() throws IOException {
        return testcaseGenerator.generate_ss(1000);
    }

}
