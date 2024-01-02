package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import org.apache.commons.lang3.StringUtils;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import src.Boyer;

public class BoyerTestGPT4 {

    /**
     * Metamorphic Relation 2: Add a prefix to the origin string that does not contain the pattern,
     * the index should be increased by the length of the prefix if the pattern is present in the
     * original text.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String prefix = "yyy";
        String follow_text = prefix + text;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        if (origin_res != -1) {
            assertEquals(follow_res, origin_res + prefix.length());
        } else {
            assertEquals(follow_res, -1);
        }
    }

    /**
     * Metamorphic Relation 3: Reverse the text and the pattern, the output should be text.length()
     * - pattern.length() - originIndex if the pattern is contained in the text.
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
        String follow_text = new StringBuilder(text).reverse().toString();
        String follow_pattern = new StringBuilder(pattern).reverse().toString();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, follow_pattern);

        /* Verification */
        if (origin_res != -1) {
            assertEquals(text.length() - pattern.length() - origin_res, follow_res);
        } else {
            assertEquals(-1, follow_res);
        }
    }

    /**
     * Metamorphic Relation 4: Concatenate the pattern to the end of the origin string, if the
     * pattern is not found initially, the new index should be the length of the origin string;
     * otherwise, it should remain unchanged.
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
        String follow_text = text + pattern;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        if (origin_res == -1) {
            assertEquals(text.length(), follow_res);
        } else {
            assertEquals(origin_res, follow_res);
        }
    }

    /**
     * Metamorphic Relation 5: Double the text, the index of the first occurrence should remain the
     * same.
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
        String follow_text = text + text;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertEquals(origin_res, follow_res);
    }

    /**
     * Metamorphic Relation 6: Remove instances of the pattern from within the text, not including
     * the first occurrence. The index of the first occurrence should not change.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input assuming origin_res is not last occurrence */
        int next_occurrence_index = origin_res;
        while (next_occurrence_index != -1) {
            next_occurrence_index =
                    Boyer.indexOf(text, pattern, next_occurrence_index + pattern.length());
            if (next_occurrence_index != -1) {
                // Remove the discovered occurrence
                text = text.substring(0, next_occurrence_index)
                        + text.substring(next_occurrence_index + pattern.length());
            }
        }

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, pattern);

        /* Verification */
        assertEquals(origin_res, follow_res);
    }

    /**
     * Metamorphic Relation 7: Append additional characters to the pattern from the text not
     * overlapping with the first occurrence of the pattern, the index of the first occurrence
     * should remain the same.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up pattern assuming the pattern is found and not at the end of text */
        String follow_pattern = origin_res != -1 && origin_res + pattern.length() < text.length()
                ? pattern + text.charAt(origin_res + pattern.length())
                : pattern;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(text, follow_pattern);

        /* Verification */
        assertEquals(origin_res, follow_res);
    }

    /**
     * Metamorphic Relation 8: Convert the text and pattern to upper or lower case, the index of the
     * first occurrence should remain the same assuming the algorithm is case insensitive.
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
        String follow_text = text.toUpperCase();
        String follow_pattern = pattern.toUpperCase();

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, follow_pattern);

        /* Verification */
        assertEquals(origin_res, follow_res);
    }

    /**
     * Metamorphic Relation 9: Insert a substring that does not contain the pattern into the text
     * before the pattern's first occurrence. If the pattern exists, the result should be increased
     * by the length of the inserted substring.
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
        String insert = "insertion";
        String follow_text = origin_res > insert.length()
                ? text.substring(0, origin_res / 2) + insert + text.substring(origin_res / 2)
                : text;

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        if (origin_res != -1) {
            assertEquals(origin_res + (origin_res > insert.length() ? insert.length() : 0),
                    follow_res);
        } else {
            assertEquals(-1, follow_res);
        }
    }

    /**
     * Metamorphic Relation 10: Shuffle substrings of text that don't overlap with the pattern's
     * first occurrence. Shuffle should not affect the pattern's occurrence index.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input, assuming sufficient length and that we found a match */
        String follow_text = text;
        if (origin_res > 0) {
            String shuffle_part = follow_text.substring(0, origin_res);
            follow_text = shuffle(shuffle_part) + follow_text.substring(origin_res);
        }

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertEquals(origin_res, follow_res);
    }

    /* Helper method to shuffle a string */
    private static String shuffle(String s) {
        List<Character> characters = s.chars().mapToObj(e -> (char) e).collect(Collectors.toList());
        Collections.shuffle(characters);
        StringBuilder shuffled = new StringBuilder();
        for (char ch : characters) {
            shuffled.append(ch);
        }
        return shuffled.toString();
    }

    /**
     * Metamorphic Relation 11: Repeat text and pattern. The pattern's first occurrence index should
     * be the same as the original, assuming the pattern exists in the text.
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
        String repeat_text = StringUtils.repeat(text, 2);
        String repeat_pattern = StringUtils.repeat(pattern, 2);

        // Only consider this MR valid if the pattern does not occur at end or is not repeated
        // within the text
        if (origin_res != -1 && origin_res + pattern.length() < text.length()
                && text.indexOf(pattern, origin_res + pattern.length()) == -1) {
            /* Get follow-up output */
            int follow_res = Boyer.indexOf(repeat_text, repeat_pattern);

            /* Verification */
            assertEquals(origin_res, follow_res);
        }
    }

    /**
     * Metamorphic Relation 12: Modify a non-matching part of text (e.g., before the first pattern
     * occurrence), the index of the first occurrence of the pattern should remain unchanged.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        // Ensure we have enough text before and after the found pattern
        if (origin_res > 2 && origin_res + pattern.length() < text.length() - 2) {
            String beforeMatch = text.substring(0, origin_res);
            // Randomly change a character in the text before the match
            int changeIndex = new Random().nextInt(beforeMatch.length());
            char newChar = (char) (beforeMatch.charAt(changeIndex) + 1); // Just some deterministic
                                                                         // change
            beforeMatch = beforeMatch.substring(0, changeIndex) + newChar
                    + beforeMatch.substring(changeIndex + 1);

            /* Construct follow-up input */
            String follow_text = beforeMatch + text.substring(origin_res);

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(follow_text, pattern);

            /* Verification */
            assertEquals(origin_res, follow_res);
        }
    }

    /**
     * Metamorphic Relation 13: Extend the pattern to the left, the index of the first occurrence of
     * the enlarged pattern should be the same or greater than the index of the original pattern.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(String text, String pattern) {
        if (!pattern.isEmpty() && text.contains(pattern)) {
            /* Get origin output */
            int origin_res = Boyer.indexOf(text, pattern);

            /* Construct follow-up input */
            String newPrefix = "new";
            String follow_pattern = newPrefix + pattern;

            /* Get follow-up output */
            int follow_res = Boyer.indexOf(text, follow_pattern);

            /* Verification */
            assertTrue(follow_res >= origin_res);
        }
    }

    /**
     * Metamorphic Relation 14: Partition text into two halves. If the pattern is fully in one half,
     * the index should be the same as the original; otherwise, it should not be found.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Partition the text into two halves */
        String firstHalf = text.substring(0, text.length() / 2);
        String secondHalf = text.substring(text.length() / 2);

        /* Get follow-up outputs */
        int follow_res1 = Boyer.indexOf(firstHalf, pattern);
        int follow_res2 = Boyer.indexOf(secondHalf, pattern);

        /* Verification */
        if (origin_res < text.length() / 2) {
            assertEquals(origin_res, follow_res1);
            assertEquals(-1, follow_res2);
        } else if (origin_res >= text.length() / 2) {
            assertEquals(-1, follow_res1);
            assertEquals(origin_res - text.length() / 2, follow_res2);
        } else {
            assertEquals(-1, follow_res1);
            assertEquals(-1, follow_res2);
        }
    }

    /**
     * Metamorphic Relation 15: Concatenate the pattern to itself and search within the doubled
     * text. The index should be unchanged if the pattern is not repeated within the text.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String doubleText = text + text;
        String doublePattern = pattern + pattern;

        /* Avoid applying the relation when the pattern occurs at the joining point */
        if (!text.endsWith(pattern) && !text.startsWith(pattern)) {
            /* Get follow-up output */
            int follow_res = Boyer.indexOf(doubleText, doublePattern);

            /* Verification */
            assertEquals(origin_res, follow_res);
        }
    }

    /**
     * Metamorphic Relation 16: If the pattern exists in the text, appending a random substring from
     * the text to the pattern makes the occurrence index either the same or nonexistent (-1).
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(String text, String pattern) {
        /* Get origin output */
        int originIndex = Boyer.indexOf(text, pattern);

        if (originIndex != -1) {
            // Append a substring from the text to the pattern
            String extra = text.substring(0, Math.min(text.length(), pattern.length()));
            String newPattern = pattern + extra;

            /* Get follow-up output */
            int newIndex = Boyer.indexOf(text, newPattern);

            /* Verification */
            assertTrue(newIndex == -1 || newIndex >= originIndex);
        }
    }

    /**
     * Metamorphic Relation 17: Swap two non-overlapping and non-matching substrings in the text.
     * This should not change the occurrence index of the pattern if it exists in the text.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String text, String pattern) {
        /* Get origin output */
        int originIndex = Boyer.indexOf(text, pattern);

        if (originIndex >= 0) {
            int subLength = pattern.length();
            // Choose two substrings to swap that do not contain the pattern occurrence
            if (originIndex >= 2 * subLength) {
                String sub1 = text.substring(subLength, 2 * subLength);
                String sub2 = text.substring(0, subLength);
                // Substrings are swapped in the text
                String newText = sub1 + text.substring(subLength, originIndex - subLength) + sub2
                        + text.substring(originIndex);

                /* Get follow-up output */
                int newIndex = Boyer.indexOf(newText, pattern);

                /* Verification */
                assertEquals(originIndex, newIndex);
            }
        }
    }

    /**
     * Metamorphic Relation 18: Append characters from the pattern itself to the end of the text.
     * The first occurrence index of the pattern should not change.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String text, String pattern) {
        /* Get origin output */
        int originalIndex = Boyer.indexOf(text, pattern);

        /* Append part of the pattern to the end of text */
        String newText = text + pattern.substring(0, 1);

        /* Get follow-up output */
        int newIndex = Boyer.indexOf(newText, pattern);

        /* Verification */
        assertEquals(originalIndex, newIndex);
    }

    /**
     * Metamorphic Relation 19: Replace characters outside the matching pattern in the text with
     * different characters. The first occurrence index of the pattern should not change.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String text, String pattern) {
        /* Get origin output */
        int originIndex = Boyer.indexOf(text, pattern);

        /* Replace characters outside of the matching pattern in the text */
        if (originIndex != -1 && pattern.length() < text.length()) {
            String newText = "A" + text.substring(1, originIndex) + "B"
                    + text.substring(originIndex + pattern.length(), text.length() - 1) + "C";

            /* Get follow-up output */
            int newIndex = Boyer.indexOf(newText, pattern);

            /* Verification */
            assertEquals(originIndex, newIndex);
        }
    }

    /**
     * Metamorphic Relation 20: When the pattern is found, replace it with a different pattern of
     * the same length. The occurrence index of the new pattern should be either -1 (not found) or
     * at the same index as the original pattern.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(String text, String pattern) {
        /* Get origin output */
        int originIndex = Boyer.indexOf(text, pattern);

        if (originIndex != -1) {
            String newText = text.substring(0, originIndex) + "different"
                    + text.substring(originIndex + pattern.length());
            /* New pattern is "different" which replaces the old pattern */
            String newPattern = "different";

            /* Get follow-up output */
            int newIndex = Boyer.indexOf(newText, newPattern);

            /* Verification */
            assertTrue(newIndex == originIndex || newIndex == -1);
        }
    }

    /**
     * Metamorphic Relation 21: If the pattern is found in the text, shuffle parts of the text that
     * don't contain the pattern. The occurrence index of the pattern should either remain unchanged
     * or -1 if the pattern crosses the shuffle boundary and becomes disjointed.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(String text, String pattern) {
        /* Get origin output */
        int originIndex = Boyer.indexOf(text, pattern);

        if (originIndex >= 0) {
            int subLength = pattern.length();
            // Divide the text into three parts: before, containing, and after the pattern
            String start = text.substring(0, originIndex);
            String matchingPart = text.substring(originIndex, originIndex + subLength);
            String end = text.substring(originIndex + subLength);

            // Shuffle the start and end parts
            start = shuffle2(start);
            end = shuffle2(end);

            // Reconstruct the text
            String shuffledText = start + matchingPart + end;

            /* Get follow-up output */
            int newIndex = Boyer.indexOf(shuffledText, pattern);

            /* Verification */
            assertTrue(newIndex == originIndex || newIndex == -1);
        }
    }

    /* Helper method to shuffle a string */
    private static String shuffle2(String s) {
        List<Character> characters = s.chars().mapToObj(e -> (char) e).collect(Collectors.toList());
        Collections.shuffle(characters);
        return characters.stream().map(String::valueOf).collect(Collectors.joining());
    }

    /**
     * Metamorphic Relation 22: Duplicate the text by appending itself. The occurrence index of the
     * pattern should remain the same as long as the pattern is not intersecting the boundary of
     * these two texts.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(String text, String pattern) {
        /* Get origin output */
        int originIndex = Boyer.indexOf(text, pattern);

        if (originIndex >= 0 && !text.endsWith(pattern)) {
            // Duplicate the text
            String expandedText = text + text;

            /* Get follow-up output */
            int newIndex = Boyer.indexOf(expandedText, pattern);

            /* Verification */
            assertEquals(originIndex, newIndex);
        }
    }

    /**
     * Metamorphic Relation 23: If the pattern is at the beginning of the text, reversing the text
     * should find the reversed pattern at the end. The occurrence index of the reversed pattern
     * should be adjusted accordingly.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(String text, String pattern) {
        /* Get origin output */
        int originIndex = Boyer.indexOf(text, pattern);

        // Only apply if the pattern is at the beginning
        if (originIndex == 0) {
            // Reverse text and pattern
            String reversedText = new StringBuilder(text).reverse().toString();
            String reversedPattern = new StringBuilder(pattern).reverse().toString();

            /* Get follow-up output */
            int newIndex = Boyer.indexOf(reversedText, reversedPattern);

            /* Verification */
            assertEquals(reversedText.length() - pattern.length(), newIndex);
        }
    }

    /**
     * Metamorphic Relation 24: Remove a non-matching prefix from the text. The occurrence index
     * should be reduced by the length of the removed prefix if the pattern is present.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(String text, String pattern) {
        /* Get origin output */
        int originalIndex = Boyer.indexOf(text, pattern);

        if (originalIndex != -1) {
            // Assume prefix length is less than the index of pattern's occurrence
            int prefixLength = Math.min(originalIndex, 3); // Choose 3 for prefix length arbitrarily
            String modifiedText = text.substring(prefixLength);

            /* Get follow-up output */
            int modifiedIndex = Boyer.indexOf(modifiedText, pattern);

            /* Verification */
            assertEquals(originalIndex - prefixLength, modifiedIndex);
        }
    }

    /**
     * Metamorphic Relation 25: Swap two non-overlapping substrings from before and after the
     * occurrence of the pattern. The occurrence index of the pattern should remain unchanged if the
     * pattern is present.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(String text, String pattern) {
        /* Get origin output */
        int originalIndex = Boyer.indexOf(text, pattern);
        // Ensure we have space before and after the occurrence for swapping
        if (originalIndex > 1 && (originalIndex + pattern.length() + 1) < text.length()) {
            String beforePattern = text.substring(0, originalIndex);
            String afterPattern = text.substring(originalIndex + pattern.length());
            // Swap the first character of the before and after substrings
            char firstBefore = beforePattern.charAt(0);
            char firstAfter = afterPattern.charAt(0);
            String newText = firstAfter + beforePattern.substring(1) + pattern + firstBefore
                    + afterPattern.substring(1);

            /* Get follow-up output */
            int newIndex = Boyer.indexOf(newText, pattern);

            /* Verification */
            assertEquals(originalIndex, newIndex);
        }
    }

    /**
     * Metamorphic Relation 26: Repeat the text and find additional occurrences of the pattern. Each
     * new occurrence should be at an interval of text's length from the last if the pattern doesn't
     * straddle the join.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(String text, String pattern) {
        /* Get origin output */
        int originalIndex = Boyer.indexOf(text, pattern);

        if (originalIndex != -1 && !text.endsWith(pattern)) {
            String repeatedText = text + text;
            /* Get follow-up output */
            int newIndex = Boyer.indexOf(repeatedText, pattern, originalIndex + 1);

            /* Verification */
            // Since Boyer-Moore usually finds the leftmost occurrence, we expect
            // the newIndex to be at text's length from the originalIndex.
            assertEquals(originalIndex + text.length(), newIndex);
        }
    }

    /**
     * Metamorphic Relation 27: Invert either a prefix or suffix of the text that doesn't contain
     * the pattern's occurrence. The occurrence index should remain unchanged.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(String text, String pattern) {
        /* Get origin output */
        int originalIndex = Boyer.indexOf(text, pattern);
        if (originalIndex > 0) {
            // Invert a prefix that does not reach the pattern
            int prefixLength = Math.min(originalIndex / 2, 3); // Arbitrary length for a short
                                                               // prefix
            String invertedPrefix =
                    new StringBuilder(text.substring(0, prefixLength)).reverse().toString();
            String newText = invertedPrefix + text.substring(prefixLength);

            /* Get follow-up output */
            int newIndex = Boyer.indexOf(newText, pattern);

            /* Verification */
            assertEquals(originalIndex, newIndex);
        }
    }

    /**
     * Metamorphic Relation 28: Append a non-matching suffix to both text and pattern. The
     * occurrence index of the pattern in the text should remain unchanged.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(String text, String pattern) {
        /* Get original output */
        int originalIndex = Boyer.indexOf(text, pattern);

        String nonMatchingSuffix = "suffix";
        // Make sure the suffix does not match any part of the pattern
        if (!pattern.contains(nonMatchingSuffix)) {
            String extendedText = text + nonMatchingSuffix;
            String extendedPattern = pattern + nonMatchingSuffix;

            /* Get follow-up output */
            int newIndex = Boyer.indexOf(extendedText, extendedPattern);

            /* Verification */
            assertEquals(originalIndex, newIndex);
        }
    }

    /**
     * Metamorphic Relation 29: Swap the first character of the pattern with a character not present
     * in the pattern, and search for this new pattern in the original text. The algorithm should
     * not find the pattern anymore.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(String text, String pattern) {
        if (!pattern.isEmpty()) {
            char newChar;
            for (newChar = 'a'; newChar <= 'z'; ++newChar) {
                if (!pattern.contains(String.valueOf(newChar))) {
                    break;
                }
            }

            String modifiedPattern = newChar + pattern.substring(1);
            int indexInOriginal = Boyer.indexOf(text, modifiedPattern);

            /* Verification */
            assertEquals(-1, indexInOriginal);
        }
    }

    /**
     * Metamorphic Relation 30: Remove characters from the start of the pattern. The occurrence
     * index should either move to the right in the text by the number of characters removed or not
     * be found at all.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);

        for (int charsRemoved = 1; charsRemoved < pattern.length(); charsRemoved++) {
            String trimmedPattern = pattern.substring(charsRemoved);
            int newIndex = Boyer.indexOf(text, trimmedPattern);

            assertTrue(newIndex >= originalIndex + charsRemoved || newIndex == -1);
        }
    }

    /**
     * Metamorphic Relation 31: Intersperse the text with a non-occurring character in the pattern
     * at regular intervals. If these do not disrupt the pattern, the index should remain unchanged.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(String text, String pattern) {
        /* Find a character that is not in the pattern */
        char insertChar = '\0';
        for (char c = 1; c < 128; c++) {
            if (pattern.indexOf(c) == -1) {
                insertChar = c;
                break;
            }
        }

        if (insertChar != '\0') {
            StringBuilder interspersedText = new StringBuilder(text.length() * 2);
            for (int i = 0; i < text.length(); i++) {
                interspersedText.append(text.charAt(i));
                interspersedText.append(insertChar); // intersperse
            }

            int originalIndex = Boyer.indexOf(text, pattern);
            int newIndex = Boyer.indexOf(interspersedText.toString(), pattern);

            /* Verification */
            assertEquals(originalIndex, newIndex);
        }
    }

    /**
     * Metamorphic Relation 32: Double the text with no modifications and the pattern, which is
     * found only once, should also be found exactly twice at predictable intervals in the new
     * doubled text.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(String text, String pattern) {
        /* Get original output */
        int originalIndex = Boyer.indexOf(text, pattern);

        // Ensure the pattern is found only once
        int secondOccurrenceIndex = Boyer.indexOf(text, pattern, originalIndex + 1);
        if (originalIndex != -1 && secondOccurrenceIndex == -1) {
            // Double the text
            String doubledText = text + text;

            /* Get follow-up output for the first and second occurrences */
            int firstNewIndex = Boyer.indexOf(doubledText, pattern);
            int secondNewIndex = Boyer.indexOf(doubledText, pattern, firstNewIndex + 1);

            /* Verification */
            assertEquals(originalIndex, firstNewIndex);
            assertEquals(text.length() + originalIndex, secondNewIndex);
        }
    }

    /**
     * Metamorphic Relation 33: Concatenate two instances of the pattern together. The search for
     * this new pattern should only succeed if the text contains at least two consecutive instances
     * of the original pattern.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(String text, String pattern) {
        /* Get original output */
        int originalIndex = Boyer.indexOf(text, pattern);

        // Check if the text has two consecutive instances
        if (originalIndex != -1 && originalIndex + pattern.length() * 2 <= text.length()) {
            // Verify the second occurrence starts right after the first
            boolean hasConsecutiveInstances = text.indexOf(pattern,
                    originalIndex + pattern.length()) == originalIndex + pattern.length();
            String doubledPattern = pattern + pattern;
            int newIndex = Boyer.indexOf(text, doubledPattern);

            /* Verification */
            if (hasConsecutiveInstances) {
                assertEquals(originalIndex, newIndex);
            } else {
                assertEquals(-1, newIndex);
            }
        }
    }

    /**
     * Metamorphic Relation 34: Substitute characters in the text at positions that don't overlap
     * with the pattern. If the pattern is found, this operation should not affect the index of its
     * occurrence in the text.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(String text, String pattern) {
        /* Get original output */
        int originalIndex = Boyer.indexOf(text, pattern);

        if (originalIndex != -1) {
            StringBuilder modifiedText = new StringBuilder(text);
            // Loop over the text and substitute characters that are not in the pattern's match
            for (int i = 0; i < modifiedText.length(); i++) {
                if ((i < originalIndex) || (i >= originalIndex + pattern.length())) {
                    modifiedText.setCharAt(i, '#'); // Substitute with a placeholder character
                }
            }

            /* Get follow-up output */
            int newIndex = Boyer.indexOf(modifiedText.toString(), pattern);

            /* Verification */
            assertEquals(originalIndex, newIndex);
        }
    }

    /**
     * Metamorphic Relation 35: Remove a non-overlapping substring from the text after the first
     * occurrence of the pattern, which should not change the occurrence index of the pattern in the
     * text.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(String text, String pattern) {
        /* Get original output */
        int originalIndex = Boyer.indexOf(text, pattern);

        if (originalIndex != -1 && originalIndex + pattern.length() < text.length()) {
            // Remove a substring that's not overlapping with the pattern's first occurrence
            String modifiedText = text.substring(0, originalIndex + pattern.length())
                    + text.substring(originalIndex + pattern.length() + 1);

            /* Get follow-up output */
            int newIndex = Boyer.indexOf(modifiedText, pattern);

            /* Verification */
            assertEquals(originalIndex, newIndex);
        }
    }

    /**
     * Metamorphic Relation 36: Trim whitespace or non-alphanumeric characters from the beginning
     * and end of text and pattern. If the pattern is found, the occurrence index should be the same
     * after trimming, provided the pattern did not include these characters.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(String text, String pattern) {
        /* Get original output */
        int originalIndex = Boyer.indexOf(text, pattern);

        // Trim text and pattern
        String trimmedText = text.trim().replaceAll("^[^a-zA-Z0-9]+|[^a-zA-Z0-9]+$", "");
        String trimmedPattern = pattern.trim().replaceAll("^[^a-zA-Z0-9]+|[^a-zA-Z0-9]+$", "");

        /* Get follow-up output */
        int newIndex = Boyer.indexOf(trimmedText, trimmedPattern);

        /* Verification */
        assertEquals(originalIndex, newIndex);
    }

    /**
     * Metamorphic Relation 37: If the pattern is found, changing characters in the text to
     * uppercase outside the range of the pattern's match should not affect the occurrence index.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(String text, String pattern) {
        /* Get original output */
        int originalIndex = Boyer.indexOf(text, pattern);

        StringBuilder newTextBuilder = new StringBuilder(text);
        // Capitalize all characters outside the match range
        for (int i = 0; i < originalIndex; i++) {
            newTextBuilder.setCharAt(i, Character.toUpperCase(newTextBuilder.charAt(i)));
        }
        for (int i = originalIndex + pattern.length(); i < newTextBuilder.length(); i++) {
            newTextBuilder.setCharAt(i, Character.toUpperCase(newTextBuilder.charAt(i)));
        }
        String newText = newTextBuilder.toString();

        /* Get follow-up output */
        int newIndex = Boyer.indexOf(newText, pattern);

        /* Verification */
        assertEquals(originalIndex, newIndex);
    }

    /**
     * Metamorphic Relation 38: Rotate the text by a length not exceeding the pattern length and
     * find the pattern. If the pattern is present and doesn't cross the rotation boundary, the
     * index should change predictably.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(String text, String pattern) {
        /* Get original output */
        int originalIndex = Boyer.indexOf(text, pattern);

        if (originalIndex != -1 && pattern.length() <= text.length() - originalIndex) {
            int rotationLength = pattern.length();
            String rotatedText = text.substring(rotationLength) + text.substring(0, rotationLength);

            /* Get follow-up output */
            int newIndex = Boyer.indexOf(rotatedText, pattern);

            /* Verification */
            if (originalIndex < rotationLength) {
                assertEquals(text.length() - rotationLength + originalIndex, newIndex);
            } else {
                assertEquals(originalIndex - rotationLength, newIndex);
            }
        }
    }

    /**
     * Metamorphic Relation 39: Replace a non-overlapping substring before the pattern match with
     * another of the same length. If the pattern is found, the occurrence index should remain
     * unchanged.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(String text, String pattern) {
        /* Get original output */
        int originalIndex = Boyer.indexOf(text, pattern);

        if (originalIndex > 3) {
            int replaceLength = 3; // Example replacement length
            String newText = text.substring(0, originalIndex - replaceLength) + "rep" + // New
                                                                                        // substring
                                                                                        // replacing
                                                                                        // an old
                                                                                        // one of
                                                                                        // the same
                                                                                        // length
                    text.substring(originalIndex - replaceLength + 3);

            /* Get follow-up output */
            int newIndex = Boyer.indexOf(newText, pattern);

            /* Verification */
            assertEquals(originalIndex, newIndex);
        }
    }

    /**
     * Metamorphic Relation 40: If the pattern is not at the beginning or end, appending the
     * reversed text to itself should not change the occurrence index of the pattern.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(String text, String pattern) {
        /* Get original output */
        int originalIndex = Boyer.indexOf(text, pattern);

        if (originalIndex != -1 && !text.startsWith(pattern) && !text.endsWith(pattern)) {
            String reversedText = new StringBuilder(text).reverse().toString();
            String newText = text + reversedText;

            /* Get follow-up output */
            int newIndex = Boyer.indexOf(newText, pattern);

            /* Verification */
            assertEquals(originalIndex, newIndex);
        }
    }

    /**
     * Metamorphic Relation 41: Insert a string that is not a substring of the pattern at intervals
     * in text. The occurrence index of the pattern should remain unchanged if the pattern is
     * present and these insertions do not cross the original match of the pattern in the text.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test41(String text, String pattern) {
        /* Get original output */
        int originalIndex = Boyer.indexOf(text, pattern);

        String insertString = "insert"; // Assume it's neither a prefix nor suffix of the pattern
        if (!pattern.contains(insertString)) {
            StringBuilder newText = new StringBuilder(text);
            for (int i = originalIndex - insertString.length(); i >= 0; i -=
                    insertString.length()) {
                newText.insert(i, insertString);
            }

            /* Get follow-up output */
            int newIndex = Boyer.indexOf(newText.toString(), pattern);

            /* Verification */
            assertEquals(originalIndex, newIndex);
        }
    }

    /**
     * Metamorphic Relation 42: Reverse the pattern, unless it is a palindrome. If the original
     * pattern is found, the reversed pattern's occurrence should be different, or it might not be
     * found at all.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test42(String text, String pattern) {
        String reversedPattern = new StringBuilder(pattern).reverse().toString();
        // Only apply this relation if the pattern is not a palindrome
        if (!reversedPattern.equals(pattern)) {
            int originalIndex = Boyer.indexOf(text, pattern);
            int newIndex = Boyer.indexOf(text, reversedPattern);

            /* Verification */
            assertTrue(newIndex != originalIndex);
        }
    }

    /**
     * Metamorphic Relation 43: Tile the text to repeat it multiple times. If the pattern is not
     * crossing the boundaries of the tiled text, the occurrences should appear at intervals equal
     * to the length of the original text.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test43(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        String tiledText = text + text + text; // Tile text three times

        // Indexes where the pattern should occur in the tiled text
        ArrayList<Integer> expectedIndexes = new ArrayList<>();
        if (originalIndex != -1 && !text.endsWith(pattern) && !text.startsWith(pattern)) {
            expectedIndexes.add(originalIndex);
            expectedIndexes.add(originalIndex + text.length());
            expectedIndexes.add(originalIndex + 2 * text.length());
        }

        // Collect the indexes where the pattern is actually found
        ArrayList<Integer> foundIndexes = new ArrayList<>();
        int currentIndex = originalIndex;
        while (currentIndex != -1 && currentIndex < tiledText.length()) {
            foundIndexes.add(currentIndex);
            currentIndex = Boyer.indexOf(tiledText, pattern, currentIndex + 1);
        }

        /* Verification */
        assertEquals(expectedIndexes, foundIndexes);
    }

    /**
     * Metamorphic Relation 44: Escape special characters in text and pattern assuming the search
     * function treats escaped characters as normal characters. This should not affect the
     * occurrence indices.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test44(String text, String pattern) {
        String escapedText = text.replace(".", "\\.").replace("*", "\\*");
        String escapedPattern = pattern.replace(".", "\\.").replace("*", "\\*");

        int originalIndex = Boyer.indexOf(text, pattern);
        int newIndex = Boyer.indexOf(escapedText, escapedPattern);

        /* Verification */
        assertEquals(originalIndex, newIndex);
    }

    /**
     * Metamorphic Relation 45: Change the dimension of the search by performing a reverse search.
     * This should either yield a different occurrence index or none, unless the pattern occurs at
     * the end of the text.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test45(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);
        String reverseText = new StringBuilder(text).reverse().toString();
        String reversePattern = new StringBuilder(pattern).reverse().toString();
        int reverseIndex = Boyer.indexOf(reverseText, reversePattern);

        /* Adjust reverseIndex to the equivalent index in the original text orientation */
        int adjustedReverseIndex = text.length() - reversePattern.length() - reverseIndex;

        // Verification should ensure either the pattern is not found or the index is the one at the
        // end of the text,
        // if it's present more than once this test case would not be valid.
        if (originalIndex != -1 && text.indexOf(pattern, originalIndex + 1) == -1) {
            assertEquals(originalIndex, adjustedReverseIndex);
        }
    }

    /**
     * Metamorphic Relation 46: Replace all but the first occurrence of a repeated substring within
     * the pattern with a unique placeholder. This should not affect the index of the first
     * occurrence of the pattern.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test46(String text, String pattern) {
        // Let's assume for simplicity that "ab" is our repeating substring in the pattern.
        String repeatedSubstring = "ab";
        String placeholder = "#"; // A unique placeholder not present in the text or pattern.

        // Check if our repeating substring occurs more than once.
        if (pattern.indexOf(repeatedSubstring) != pattern.lastIndexOf(repeatedSubstring)) {
            // Replace all but the first occurrence of the repeated substring in pattern with a
            // placeholder.
            String modifiedPattern = pattern.replaceFirst(repeatedSubstring, "")
                    .replace(repeatedSubstring, placeholder);
            modifiedPattern = repeatedSubstring + modifiedPattern;

            int originalIndex = Boyer.indexOf(text, pattern);
            int modifiedIndex = Boyer.indexOf(text, modifiedPattern);

            /* Verification */
            assertEquals(originalIndex, modifiedIndex);
        }
    }

    /**
     * Metamorphic Relation 47: Move the pattern to a different non-overlapping location within the
     * text. The new occurrence index should be correctly found or not found at all if it's moved to
     * a part of the text where it does not occur.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test47(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);

        // Find a non-overlapping new location for the pattern within the text
        int newLocation = (originalIndex + pattern.length() + 5) % text.length();

        // Craft new text with the pattern moved to the new location
        String newText = text.substring(0, newLocation) + pattern
                + text.substring(newLocation + pattern.length());

        // Get new index for the moved pattern
        int newIndex = Boyer.indexOf(newText, pattern);

        /* Verification */
        // If the pattern's occurrence is solely at the new location, the index should match the new
        // location.
        assertEquals(newLocation, newIndex);
    }

    /**
     * Metamorphic Relation 48: Surround the pattern with additional characters, which should only
     * affect the occurrence index based on the number of characters added before the pattern.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test48(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);

        if (originalIndex != -1) {
            String prefix = "pre";
            String suffix = "suf";
            String newPattern = prefix + pattern + suffix;

            String newText = text.substring(0, originalIndex) + newPattern
                    + text.substring(originalIndex + pattern.length());

            int newIndex = Boyer.indexOf(newText, pattern);

            /* Verification */
            assertEquals(originalIndex + prefix.length(), newIndex);
        }
    }

    /**
     * Metamorphic Relation 49: If the pattern is not originally found, replace a substring in text
     * with the pattern which should then result in finding the pattern at the index of the replaced
     * substring.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test49(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);

        if (originalIndex == -1) {
            int replacementIndex = 5; // Arbitrary replacement index
            String newText = text.substring(0, replacementIndex) + pattern
                    + text.substring(replacementIndex + pattern.length());

            int newIndex = Boyer.indexOf(newText, pattern);

            /* Verification */
            assertEquals(replacementIndex, newIndex);
        }
    }

    /**
     * Metamorphic Relation 50: Convert text and pattern to their respective hex string
     * representations. The occurrence index should scale appropriately with the increased lengths
     * of the representations.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test50(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);

        // Convert to hex representation
        String hexText =
                text.chars().mapToObj(c -> String.format("%02x", c)).collect(Collectors.joining());
        String hexPattern = pattern.chars().mapToObj(c -> String.format("%02x", c))
                .collect(Collectors.joining());

        // Adjust original index by multiplying by 2 (since hex string is double the size)
        int adjustedOriginalIndex = originalIndex * 2;

        int newHexIndex = Boyer.indexOf(hexText, hexPattern);

        /* Verification */
        assertEquals(adjustedOriginalIndex, newHexIndex);
    }

    /**
     * Metamorphic Relation 51: Intersperse characters that are not in the pattern into the text.
     * The occurrence index should remain unchanged if these characters are not added within the
     * pattern.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test51(String text, String pattern) {
        int originalIndex = Boyer.indexOf(text, pattern);

        if (originalIndex != -1) {
            // Find a character not present in the pattern
            char newChar = 'Z';
            while (pattern.contains(String.valueOf(newChar))) {
                newChar--;
            }

            // Intersperse the new character throughout the text, skipping the pattern
            StringBuilder interspersedText = new StringBuilder();
            for (int i = 0; i < originalIndex; i++) {
                interspersedText.append(text.charAt(i)).append(newChar);
            }
            interspersedText.append(pattern);
            for (int i = originalIndex + pattern.length(); i < text.length(); i++) {
                interspersedText.append(newChar).append(text.charAt(i));
            }

            int newIndex = Boyer.indexOf(interspersedText.toString(), pattern);

            /* Verification */
            assertEquals(originalIndex * 2, newIndex);
        }
    }

    static Stream<Arguments> testcaseProvider() {
        return Stream.of(Arguments.of("abcdefg", "abc"), Arguments.of("abcdefg", "xyz"));
    }
}
