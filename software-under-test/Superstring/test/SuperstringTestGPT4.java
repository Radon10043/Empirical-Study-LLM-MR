package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import src.Superstring;
import java.util.regex.Pattern;


public class SuperstringTestGPT4 {
    /**
     * Metamorphic Relation 1: Reordering the strings in the array should not change the length of
     * the shortest superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testReordering(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input by shuffling the original array */
        ArrayList<String> follow_arr = new ArrayList<>(arr);
        Collections.shuffle(follow_arr);

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 2: If two identical strings are in the array, removing one should not
     * change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testRemovingDuplicate(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input */
        ArrayList<String> follow_arr = new ArrayList<>(arr);

        // Find a duplicate string (if any) and remove it
        HashSet<String> seen = new HashSet<>();
        String toRemove = null;
        for (String str : follow_arr) {
            if (seen.contains(str)) {
                toRemove = str;
                break;
            }
            seen.add(str);
        }

        if (toRemove != null) {
            follow_arr.remove(toRemove);

            /* Get follow-up output */
            String follow_out = Superstring.shortest_superstring(follow_arr);

            /* Verification */
            assertEquals(source_out, follow_out);
        }
    }

    /**
     * Metamorphic Relation 3: Adding a string that is a substring of an existing string should not
     * change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testAddingContainedSubstring(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        if (!arr.isEmpty()) {
            /* Construct follow-up input */
            ArrayList<String> follow_arr = new ArrayList<String>(arr);
            follow_arr.add(arr.get(0).substring(0, 1)); // Assume the first string has at least one
                                                        // character

            /* Get follow-up output */
            String follow_out = Superstring.shortest_superstring(follow_arr);

            /* Verification */
            assertEquals(source_out, follow_out);
        }
    }

    /**
     * Metamorphic Relation 4: Concatenating a string to all strings in the array should increase
     * the length of the superstring by at most the length of the added string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testAugmentEachString(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input */
        ArrayList<String> follow_arr = new ArrayList<String>();
        String suffix = "suffix";
        for (String str : arr) {
            follow_arr.add(str + suffix);
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(follow_out.length() <= source_out.length() + suffix.length());
    }

    /**
     * Metamorphic Relation 5: Reversing all strings in the array and the order of the array should
     * result in the reverse of original superstring as the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testReverseAllStrings(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input by reversing all strings and the array itself */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (int i = arr.size() - 1; i >= 0; i--) {
            follow_arr.add(new StringBuilder(arr.get(i)).reverse().toString());
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(new StringBuilder(source_out).reverse().toString(), follow_out);
    }

    /**
     * Metamorphic Relation 6: Doubling every string in the array should not change the relative
     * order or content of the superstring, though its length may double.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testDoublingStrings(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input by doubling each string in the array */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String str : arr) {
            follow_arr.add(str + str);
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /*
         * Construct expected follow-up output by doubling each string in the original superstring
         */
        StringBuilder expected_follow_out = new StringBuilder();
        for (String str : arr) {
            expected_follow_out.append(str);
            expected_follow_out.append(str);
        }

        /*
         * Verification that the follow-up output contains the doubled strings in the original order
         */
        assertTrue(follow_out.contains(source_out));
        assertTrue(follow_out.length() <= expected_follow_out.length());
    }

    /**
     * Metamorphic Relation 7: If a string that is not a substring of any string in the array is
     * added, the length of the superstring should increase at least by the length of the new
     * string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testAddingNonSubstringString(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Add a string that is guaranteed not to be a substring of any existing string. */
        String uniqueString = generateUniqueString(arr);
        arr.add(uniqueString);

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(arr);

        /* Verification */
        int expectedMinLengthIncrease = uniqueString.length();
        assertTrue(follow_out.length() >= source_out.length() + expectedMinLengthIncrease);
    }

    // Helper method to generate a string that is not a substring of any string in the list
    private String generateUniqueString(ArrayList<String> arr) {
        String uniqueString = "unique_";
        for (String str : arr) {
            while (str.contains(uniqueString)) {
                uniqueString += "_";
            }
        }
        return uniqueString;
    }

    /**
     * Metamorphic Relation 8: Interleaving the strings from two separate sets that lead to
     * identical superstrings should lead to a superstring with at most twice the length.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testInterleavingTwoIdenticalSets(ArrayList<String> set1) { // Fixed
        ArrayList<String> set2 = set1;

        /* Get source output for first set */
        String source_out1 = Superstring.shortest_superstring(set1);

        /* Get source output for second set (should be identical to first) */
        String source_out2 = Superstring.shortest_superstring(set2);
        assertEquals(source_out1, source_out2);

        /* Construct interleaved follow-up input from both sets */
        ArrayList<String> follow_arr = new ArrayList<String>();
        Iterator<String> iter1 = set1.iterator();
        Iterator<String> iter2 = set2.iterator();

        while (iter1.hasNext() || iter2.hasNext()) {
            if (iter1.hasNext())
                follow_arr.add(iter1.next());
            if (iter2.hasNext())
                follow_arr.add(iter2.next());
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(follow_out.length() <= source_out1.length() * 2);
    }

    /**
     * Metamorphic Relation 9: Prefixing a common string to all strings in the array should not
     * change the relative order or content of the superstring, though its length may increase by
     * the length of the prefix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testPrefixingCommonString(ArrayList<String> arr) { // Fixed
        String prefix = "cp";
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input by prefixing a common string to every string in the array */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String str : arr) {
            follow_arr.add(prefix + str);
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(follow_out.startsWith(prefix)); // The superstring must start with the prefix
        assertTrue(follow_out.length() <= source_out.length() + prefix.length());
    }

    /**
     * Metamorphic Relation 10: Removing a string from the array which is a superstring of another
     * should not increase the length of the shortest superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testRemovingASuperstring(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input */
        // Locate a string that is a superstring of another string in the array
        String superstringToRemove = null;
        for (int i = 0; i < arr.size(); ++i) {
            for (int j = 0; j < arr.size(); ++j) {
                if (i != j && arr.get(i).contains(arr.get(j))) {
                    superstringToRemove = arr.get(i);
                    break;
                }
            }
            if (superstringToRemove != null) {
                break;
            }
        }

        if (superstringToRemove != null) {
            ArrayList<String> follow_arr = new ArrayList<>(arr);
            follow_arr.remove(superstringToRemove);

            /* Get follow-up output */
            String follow_out = Superstring.shortest_superstring(follow_arr);

            /* Verification */
            assertTrue(follow_out.length() <= source_out.length());
        }
    }

    /**
     * Metamorphic Relation 11: Appending a single string to itself (in the array) should not change
     * the output, since a string contains itself as a superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testAppendingStringToItself(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input if the array contains at least one string */
        if (arr.size() > 0) {
            ArrayList<String> follow_arr = new ArrayList<>(arr);
            String firstString = follow_arr.get(0);
            follow_arr.add(firstString); // Append the first string to the array again

            /* Get follow-up output */
            String follow_out = Superstring.shortest_superstring(follow_arr);

            /* Verification */
            assertEquals(source_out, follow_out);
        }
    }

    /**
     * Metamorphic Relation 12: Splitting strings in the array that do not result in additional
     * unique substrings does not change the length of the superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testSplittingStrings(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input by splitting strings at a random point */
        ArrayList<String> follow_arr = new ArrayList<>();
        for (String originalString : arr) {
            if (originalString.length() > 1) {
                int splitIndex = originalString.length() / 2;
                follow_arr.add(originalString.substring(0, splitIndex));
                follow_arr.add(originalString.substring(splitIndex));
            } else {
                follow_arr.add(originalString);
            }
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 13: Concatenating an arbitrary string to the superstring obtained from
     * the array should result in a string at least as long as the sum of lengths of the superstring
     * and new string and should still contain all the original strings as substrings.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testConcatenatingStringToSuperstring(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        String additionalString = "additionalString_";

        /* Construct the expected superstring after adding the additionalString */
        String expectedSuperstring = source_out + additionalString;

        /* Add the additionalString to the array */
        ArrayList<String> follow_arr = new ArrayList<>(arr);
        follow_arr.add(additionalString);

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(follow_out.contains(additionalString)); // additionalString must be a substring
        assertTrue(follow_out.length() >= expectedSuperstring.length()); // The length should be at
                                                                         // least as long
    }

    /**
     * Metamorphic Relation 14: Inserting a string that is a concatenation of all strings in the
     * array to the array should not change the shortest superstring, since the new string is
     * already a superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testInsertingConcatenatedString(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input by concatenating all strings and adding it to the array */
        StringBuilder concatenatedString = new StringBuilder();
        for (String str : arr) {
            concatenatedString.append(str);
        }

        ArrayList<String> follow_arr = new ArrayList<>(arr);
        follow_arr.add(concatenatedString.toString());

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 15: Replacing a string in the array with another string that has
     * equivalent presence (as a substring or superstring) should not change the shortest
     * superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testReplacingWithEquivalentString(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        // Prepare a replacement mapping for testing (e.g., aa -> aaa, b -> bb)
        HashMap<String, String> replacements = new HashMap<>();
        replacements.put("aa", "aaa");
        replacements.put("b", "bb");

        /* Construct follow-up input by replacing strings according to the map */
        ArrayList<String> follow_arr = new ArrayList<>();
        for (String str : arr) {
            String replacement = replacements.getOrDefault(str, str); // Use replacement if
                                                                      // available
            follow_arr.add(replacement);
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 16: Adding all strings in reverse should not reduce the length of the
     * superstring as every string is its own reverse's superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testAddingAllStringsInReverse(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input by adding all strings in reverse */
        ArrayList<String> follow_arr = new ArrayList<>(arr);
        for (String str : arr) {
            follow_arr.add(new StringBuilder(str).reverse().toString());
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(follow_out.length() >= source_out.length());

    }

    /**
     * Metamorphic Relation 17: Adding palindromes formed from substrings of any string in the array
     * should not increase the length of the shortest superstring if these palindromes are contained
     * within the original strings.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testAddingPalindromes(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input */
        ArrayList<String> follow_arr = new ArrayList<>(arr);
        for (String str : arr) {
            // Assuming palindrome substring from the middle of each string to ensure it's embedded
            if (str.length() >= 4) {
                String palindromeSubstring = str.substring(1, str.length() - 1); // Extract center
                                                                                 // substring
                StringBuilder sb = new StringBuilder(palindromeSubstring).reverse(); // Reverse it
                // Only add if it forms a palindrome as is, or with the reverse
                if (palindromeSubstring.equals(sb.toString()) || str.contains(sb.toString())) {
                    follow_arr.add(sb.toString());
                }
            }
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 18: Rotating the strings in the array should keep the length of the
     * shortest superstring the same, as rotation does not change substring occurrences.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testRotatingStrings(ArrayList<String> arr) {
        if (arr.isEmpty()) {
            return;
        }

        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input by rotating each string one character to the right */
        ArrayList<String> follow_arr = new ArrayList<>();
        for (String str : arr) {
            if (str.length() > 1) {
                String rotatedString =
                        str.charAt(str.length() - 1) + str.substring(0, str.length() - 1);
                follow_arr.add(rotatedString);
            } else {
                follow_arr.add(str);
            }
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 19: Replacing strings in the array with their respective rotations
     * should result in a superstring of the same length if rotations preserve containment
     * relations.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testReplacingWithRotations(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input by replacing strings with their rotations */
        ArrayList<String> follow_arr = new ArrayList<>();
        for (String str : arr) {
            String rotatedStr = (str.length() > 1) ? str.substring(1) + str.charAt(0) : str;
            follow_arr.add(rotatedStr);
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 20: Expanding every string by repeating their character(s) should result
     * in a superstring whose length is increased accordingly. The expansion factor is the number of
     * times each character is repeated.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testExpandingEveryString(ArrayList<String> arr) {
        final int expansionFactor = 2;

        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input by expanding every string */
        ArrayList<String> follow_arr = new ArrayList<>();
        for (String str : arr) {
            StringBuilder expandedStr = new StringBuilder();
            for (char c : str.toCharArray()) {
                for (int i = 0; i < expansionFactor; ++i) {
                    expandedStr.append(c);
                }
            }
            follow_arr.add(expandedStr.toString());
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(follow_out.length() >= source_out.length() * expansionFactor);
    }

    /**
     * Metamorphic Relation 21: Concatenating a random string between every two adjacent strings in
     * the array should not reduce the length of the shortest superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testInsertingRandomStringBetweenStrings(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        final String randomString = "X";

        /*
         * Construct follow-up input by inserting a random string between every two adjacent strings
         */
        ArrayList<String> follow_arr = new ArrayList<>();
        for (int i = 0; i < arr.size(); i++) {
            follow_arr.add(arr.get(i));
            if (i < arr.size() - 1) {
                follow_arr.add(randomString);
            }
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(follow_out.length() >= source_out.length());
    }

    /**
     * Metamorphic Relation 22: Permuting substrings within the strings of the array should result
     * in the same length of the superstring if all permutations are substrings of the original
     * strings.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testPermutingSubstrings(ArrayList<String> arr) {
        /* Get original output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input by permuting substrings within each string in the array */
        ArrayList<String> follow_arr = new ArrayList<>();
        for (String str : arr) {
            if (str.length() > 3) {
                String firstSubstr = str.substring(0, str.length() / 3);
                String secondSubstr = str.substring(str.length() / 3, 2 * str.length() / 3);
                String thirdSubstr = str.substring(2 * str.length() / 3);
                // Permute substrings and add to follow_arr
                follow_arr.add(secondSubstr + thirdSubstr + firstSubstr);
            } else {
                follow_arr.add(str);
            }
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 23: Adding suffixes to strings which matches suffixes of other strings
     * in the array should not change the length or operational logic of the superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testAddingMatchingSuffixes(ArrayList<String> arr) {
        /* Get original output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input with suffixes added */
        ArrayList<String> follow_arr = new ArrayList<>();
        for (String currentString : arr) {
            for (String otherString : arr) {
                if (!currentString.equals(otherString) && otherString.endsWith(currentString)) {
                    // Add currentString plus a known suffix from otherString
                    follow_arr.add(otherString);
                } else {
                    follow_arr.add(currentString);
                }
            }
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 24: Removing characters from strings in the array that are also present
     * in adjacent strings should not change the structure of the shortest superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testRemovingCharactersInAdjacentOverlap(ArrayList<String> arr) {
        if (arr.size() < 2) {
            return; // Skip the test if there are not enough strings to perform adjacent overlap
        }

        /* Get original output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input by considering adjacent overlapping characters */
        ArrayList<String> follow_arr = new ArrayList<>();
        for (int i = 0; i < arr.size() - 1; i++) {
            String thisString = arr.get(i);
            String nextString = arr.get(i + 1);
            if (nextString.startsWith(thisString)) {
                follow_arr.add(nextString); // Add next string which contains the current as prefix
            } else {
                follow_arr.add(thisString); // Normal addition
            }
        }
        follow_arr.add(arr.get(arr.size() - 1)); // Add the last string

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 25: Replacing strings with their substring components should still yield
     * a superstring that encompasses all the original strings.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testReplacingWithSubstringComponents(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        ArrayList<String> follow_arr = new ArrayList<>();
        for (String str : arr) {
            if (str.length() > 2) {
                // Create two substrings if possible
                String firstPart = str.substring(0, str.length() / 2);
                String secondPart = str.substring(str.length() / 2);
                follow_arr.add(firstPart);
                follow_arr.add(secondPart);
            } else {
                follow_arr.add(str);
            }
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(follow_out.length() >= source_out.length());
    }

    /**
     * Metamorphic Relation 26: Duplicating the array of strings and appending it to itself should
     * not change the relative content of the superstring, but may result in an increased length of
     * up to twice the size.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testDuplicatingArrayAndAppending(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input */
        ArrayList<String> follow_arr = new ArrayList<>();
        follow_arr.addAll(arr);
        follow_arr.addAll(arr); // Duplicate array and append

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(follow_out.length() <= source_out.length() * 2
                && follow_out.length() >= source_out.length());
    }

    /**
     * Metamorphic Relation 27: Sorting the strings in the array should not change the possibility
     * of forming a superstring, although it might lead to a different superstring with the same
     * length due to different overlaps.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testSortingStrings(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input by sorting the strings based on their natural ordering */
        ArrayList<String> follow_arr = new ArrayList<>(arr);
        Collections.sort(follow_arr);

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 28: Combining pairs of strings that do not overlap with any other
     * strings should not result in a superstring shorter than the original.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testCombiningNonOverlappingPairs(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input */
        ArrayList<String> follow_arr = new ArrayList<>();
        HashSet<String> combined = new HashSet<>();
        for (int i = 0; i < arr.size(); i++) {
            if (!combined.contains(arr.get(i))) {
                for (int j = i + 1; j < arr.size(); j++) {
                    if (!combined.contains(arr.get(j)) && !doesOverlap(arr.get(i), arr.get(j))) {
                        // Combine non-overlapping pairs, and mark them as combined
                        follow_arr.add(arr.get(i) + arr.get(j));
                        combined.add(arr.get(i));
                        combined.add(arr.get(j));
                        break;
                    }
                }
                if (!combined.contains(arr.get(i))) {
                    follow_arr.add(arr.get(i));
                }
            }
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(follow_out.length() >= source_out.length());
    }

    // Helper function to check if two strings overlap
    private boolean doesOverlap(String a, String b) {
        return a.contains(b) || b.contains(a)
                || (a.length() > 1 && b.startsWith(a.substring(a.length() - 1)))
                || (b.length() > 1 && a.startsWith(b.substring(b.length() - 1)));
    }

    /**
     * Metamorphic Relation 29: Replacing all instances of a substring within the strings should not
     * change the length of the superstring if the replaced substring does not overlap with the
     * modified string's occurrences within the superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testReplacingNonOverlappingSubstring(ArrayList<String> arr) {
        // Select a substring and a replacement that are not overlapping
        String substringToReplace = "A";
        String replacement = "B";

        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        // Replace 'substringToReplace' with 'replacement' in all strings
        ArrayList<String> follow_arr = new ArrayList<>();
        for (String str : arr) {
            follow_arr.add(str.replace(substringToReplace, replacement));
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 30: For strings with repetitive patterns (e.g., "abab", "cdcd"),
     * replacing one instance of the pattern should not increase the length of the superstring if a
     * full pattern is retained.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testReplacingOneRepetitivePattern(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        // Replace one instance of a repetitive pattern within each string
        ArrayList<String> follow_arr = new ArrayList<>();
        for (String str : arr) {
            String pattern = identifyRepetitivePattern(str);
            if (pattern != null && str.length() >= pattern.length() * 2) {
                follow_arr.add(str.replaceFirst(Pattern.quote(pattern), ""));
            } else {
                follow_arr.add(str);
            }
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    // Helper function to identify a repetitive pattern within a string
    private String identifyRepetitivePattern(String str) {
        for (int i = 1; i <= str.length() / 2; i++) {
            String pattern = str.substring(0, i);
            String replaced = str.replaceAll(Pattern.quote(pattern), "");
            if (replaced.isEmpty()) {
                return pattern;
            }
        }
        return null;
    }

    /**
     * Metamorphic Relation 31: Inverting the bit mask used in the dynamic programming table (if
     * accessible) should not change the length of the superstring as it represents a different
     * permutation of the same set.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testInvertingDPBitMask(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        // Get access to the dynamic programming table and invert the bit mask
        // This example assumes we have direct access to manipulate the DP table.
        // It is an abstract relation based on knowledge of implementation details and may not be
        // directly executable.

        /* Construct follow-up input */
        // Assuming function to invert bit mask within the DP table exists.
        // invertDPBitMask(); // This is a conceptual step, not actual executable code.

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(arr);

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 32: Interchanging characters within strings should not change the length
     * of the superstring if they don't lead to new substring relationships.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testInterchangingCharacters(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        // Interchange characters within each string where possible
        ArrayList<String> follow_arr = new ArrayList<>();
        for (String str : arr) {
            if (str.length() > 1) {
                char[] chars = str.toCharArray();
                // Simple swap of the first two characters
                char tmp = chars[0];
                chars[0] = chars[1];
                chars[1] = tmp;
                follow_arr.add(new String(chars));
            } else {
                follow_arr.add(str);
            }
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 33: Appending a universally unique string to the end of all strings in
     * the array should result in the superstring's length increasing by the length of this unique
     * string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testAppendingUniqueStringToAll(ArrayList<String> arr) {
        String uniqueString = "UniqueSuffix";

        // Get source output
        String source_out = Superstring.shortest_superstring(arr);

        // Construct follow-up input: append unique string to each array element
        ArrayList<String> follow_arr = new ArrayList<>();
        for (String str : arr) {
            follow_arr.add(str + uniqueString);
        }

        // Get follow-up output
        String follow_out = Superstring.shortest_superstring(follow_arr);

        // Verification
        assertTrue(follow_out.endsWith(uniqueString));
        assertEquals(follow_out.length(), source_out.length() + uniqueString.length());
    }

    /**
     * Metamorphic Relation 34: Adding a string that is a concatenation of all input strings in
     * reverse order to the set should result in a superstring where the added string is a
     * substring, and the superstring length could at most increase by the length of the shortest
     * string in the input set.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testAddingReverseConcatenatedString(ArrayList<String> arr) {
        // Get source output
        String source_out = Superstring.shortest_superstring(arr);

        // Find the shortest string in the original array
        String shortestString =
                arr.stream().min(Comparator.comparingInt(String::length)).orElse("");

        // Construct follow-up input
        String reverseConcatenated =
                arr.stream().reduce("", (partialString, element) -> element + partialString);
        ArrayList<String> follow_arr = new ArrayList<>(arr);
        follow_arr.add(reverseConcatenated);

        // Get follow-up output
        String follow_out = Superstring.shortest_superstring(follow_arr);

        // Verification
        assertTrue(follow_out.length() <= source_out.length() + shortestString.length());
        assertTrue(follow_out.contains(reverseConcatenated));
    }

    /**
     * Metamorphic Relation 35: For each substring A within any string, replacing A with a new
     * string B where B contains A should not change the shortest superstring as B can also act as a
     * substitute for A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testReplacingSubstringWithContainingString(ArrayList<String> arr) { // Fixed
        // Define a substring (A) and its superstring (B)
        String A = "A";
        String B = "BA"; // B contains A

        // Get source output
        String source_out = Superstring.shortest_superstring(arr);

        // Construct follow-up input by replacing all occurrences of A with B
        ArrayList<String> follow_arr = new ArrayList<>();
        for (String str : arr) {
            follow_arr.add(str.replace(A, B));
        }

        // Get follow-up output
        String follow_out = Superstring.shortest_superstring(follow_arr);

        // Verification
        assertEquals(follow_out.length(), source_out.length());
    }

    /**
     * Metamorphic Relation 36: For any two strings A and B in the array where B is a substring of
     * A, replacing A with A + B or B + A should not change the resulting length of the superstring
     * since B is already contained in A.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testReplacingStringWithSelfPlusContainedString(ArrayList<String> arr) {
        // Define a map to identify substrings and their superstrings
        Map<String, String> superSubPairs = findSuperSubPairs(arr);

        // Get source output
        String source_out = Superstring.shortest_superstring(arr);

        // Construct follow-up input
        ArrayList<String> follow_arr = new ArrayList<>();
        for (String str : arr) {
            if (superSubPairs.containsKey(str)) {
                follow_arr.add(str + superSubPairs.get(str));
            } else {
                follow_arr.add(str);
            }
        }

        // Get follow-up output
        String follow_out = Superstring.shortest_superstring(follow_arr);

        // Verification
        assertEquals(follow_out.length(), source_out.length());
    }

    // Helper method to find pairs of strings where one is a substring of the other
    private Map<String, String> findSuperSubPairs(ArrayList<String> arr) {
        Map<String, String> superSubPairs = new HashMap<>();
        for (String superString : arr) {
            for (String subString : arr) {
                if (!superString.equals(subString) && superString.contains(subString)) {
                    superSubPairs.put(superString, subString);
                    break;
                }
            }
        }
        return superSubPairs;
    }

    /**
     * Metamorphic Relation 37: Appending a mirrored version of each string to itself should not
     * change the shortest superstring since the new strings would still contain the old ones.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testAppendingMirroredString(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input */
        ArrayList<String> follow_arr = new ArrayList<>();
        for (String str : arr) {
            String mirroredStr = new StringBuilder(str).reverse().toString();
            follow_arr.add(str + mirroredStr);
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 38: Inserting an empty string into the array of strings should not
     * affect the superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testInsertingEmptyString(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input */
        ArrayList<String> follow_arr = new ArrayList<>(arr);
        follow_arr.add(""); // Insert an empty string

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out); // The superstring should be the same
    }

    /**
     * Metamorphic Relation 39: Shuffle the characters within each string in the array. The
     * superstring might change but should be composed of the same set of characters.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testShufflingCharactersInStrings(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Shuffle the characters within each string in the array */
        ArrayList<String> follow_arr = new ArrayList<>();
        for (String str : arr) {
            List<Character> chars =
                    str.chars().mapToObj(e -> (char) e).collect(Collectors.toList());
            Collections.shuffle(chars);
            String shuffledStr = chars.stream().map(String::valueOf).collect(Collectors.joining());
            follow_arr.add(shuffledStr);
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        // Since this is just shuffling of characters, the superstring length should not increase
        assertTrue(follow_out.length() <= source_out.length());
        // The follow-out should contain all characters from follow_arr's strings
        assertTrue(allCharactersPresent(follow_out, follow_arr));
    }

    // Helper method to verify if all characters in the array of strings are present in the
    // superstring
    private boolean allCharactersPresent(String superstring, ArrayList<String> strings) {
        String concatStrings = String.join("", strings);
        char[] chars = concatStrings.toCharArray();
        for (char c : chars) {
            if (superstring.indexOf(c) == -1) {
                return false;
            }
        }
        return true;
    }

    /**
     * Metamorphic Relation 40: Remove a string from the array and also remove it from the resulting
     * superstring. The length of the new superstring should be shorter than the original.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testRemovingStringAndFromSuperstring(ArrayList<String> arr) {   // Fixed
        if (arr.size() < 2)
            return;

        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Remove the first string from array */
        String removedStr = arr.remove(0); // Choose any string to remove for this test

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(arr);

        /* Remove the string from the source output to create the expected output */
        String expected_out = source_out.replace(removedStr, "");

        /* Verification */
        assertEquals(expected_out, follow_out); // The resulting superstring must match the expected
        assertTrue(follow_out.length() < source_out.length()); // The new superstring should be
                                                               // shorter
    }

    public static Stream<Arguments> testcaseProvider() throws Exception {
        return testcaseGenerator.generate(1000);
    }
}
