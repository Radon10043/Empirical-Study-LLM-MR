package test;

import static org.junit.Assert.assertNull;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.nio.charset.StandardCharsets;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.stream.Stream;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import src.Superstring;
import java.util.Random;


public class SuperstringTestGPT3D5New {
    /**
     * Metamorphic Relation 1: Permuting the order of the strings in the input array should not change the output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testPermutation(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Permute the input array */
        Collections.shuffle(arr, new Random(123));

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 2: Reversing the order of the strings in the input array should not change the output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testReversal(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Reverse the input array */
        Collections.reverse(arr);

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 3: Adding duplicate strings to the input array should not change the output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testDuplicateStrings(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Add duplicate strings to the input array */
        ArrayList<String> follow_arr = new ArrayList<String>(arr);
        follow_arr.addAll(arr.subList(0, Math.min(arr.size(), 2))); // Add the first two strings as duplicates

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 4: Adding an empty string to the input array should not change the output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testEmptyString(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Add an empty string to the input array */
        ArrayList<String> follow_arr = new ArrayList<String>(arr);
        follow_arr.add("");

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 5: Concatenating the output superstring with any string from the input array
     * (excluding the first and last strings) should yield a superstring that contains the original
     * array of strings.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testSuperstringConcatenation(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Choose a string from the input array to concatenate with the output */
        String concatenatedString = arr.get(arr.size() / 2);

        /* Concatenate the output with the chosen string */
        String concatenatedOutput = source_out + concatenatedString;

        /* Verification */
        assertTrue(stringContainsAllSubstrings(concatenatedOutput, arr));
    }

    /**
     * Utility function to check if a string contains all substrings from an array
     */
    private boolean stringContainsAllSubstrings(String superstring, ArrayList<String> substrings) {
        for (String substring : substrings) {
            if (!superstring.contains(substring)) {
                return false;
            }
        }
        return true;
    }

    /**
     * Metamorphic Relation 6: Removing a string from the input array should result in a superstring that is longer or equal in length to the original superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testStringRemoval(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Remove a string from the input array */
        ArrayList<String> follow_arr = new ArrayList<String>(arr);
        follow_arr.remove(follow_arr.size() / 2);

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(follow_out.length() >= source_out.length());
    }

    //fixed
    /**
     * Metamorphic Relation 7: Replacing a substring in the input strings with a different substring should not change the output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Replace a substring in each string in the input array */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String str : arr) {
            String replacedStr = str.replace("a", "b");  // Replace 'a' with 'b' in each string
            follow_arr.add(replacedStr);
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 8: Rotating the order of the strings in the input array should not change the output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testRotation(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Rotate the input array */
        Collections.rotate(arr, 1);

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 9: Adding a prefix to each string in the input array should result in a superstring that contains the original array of strings.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testPrefixAddition(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Add a prefix to each string in the input array */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String str : arr) {
            follow_arr.add("prefix_" + str);
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(stringContainsAllSubstrings(follow_out, arr));
    }

    /**
     * Metamorphic Relation 10: Adding a suffix to each string in the input array should result in a superstring that contains the original array of strings.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testSuffixAddition(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Add a suffix to each string in the input array */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String str : arr) {
            follow_arr.add(str + "_suffix");
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(stringContainsAllSubstrings(follow_out, arr));
    }

    //fixed
    /**
     * Metamorphic Relation 11: Reversing each string in the input array should result in a superstring that contains the original array of strings.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Reverse each string in the input array */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String str : arr) {
            follow_arr.add(new StringBuilder(str).reverse().toString());
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(stringContainsAllSubstrings(follow_out, arr));
    }

    //fixed
    /**
     * Metamorphic Relation 12: Multiplying the occurrence of a string in the input array should not change the output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Duplicate the occurrence of a string in the input array */
        ArrayList<String> follow_arr = new ArrayList<String>(arr);
        follow_arr.addAll(arr.subList(0, Math.min(arr.size(), 2))); // Duplicate the first two strings

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 13: Adding a string at both the beginning and end of the input array should not change the output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testBeginningEndStringAddition(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Add a string at the beginning and end of the input array */
        ArrayList<String> follow_arr = new ArrayList<String>(arr);
        String firstString = arr.get(0);
        String lastString = arr.get(arr.size() - 1);
        follow_arr.add(0, firstString + "_beginning");
        follow_arr.add(lastString + "_end");

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 14: Adding the same unique string to the input array multiple times should result in a superstring that contains the original array of strings.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testUniqueStringAddition(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Create a unique string to add to the input array */
        String uniqueString = "unique_string";

        /* Add the unique string multiple times to the input array */
        ArrayList<String> follow_arr = new ArrayList<String>(arr);
        for (int i = 0; i < 3; i++) {
            follow_arr.add(uniqueString);
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(stringContainsAllSubstrings(follow_out, arr));
    }

    /**
     * Metamorphic Relation 15: Replacing all occurrences of a specific character or substring in the input strings with another character or substring should not change the output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testCharacterSubstringReplacement(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Replace all occurrences of a character or substring in each string in the input array */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String str : arr) {
            String replacedStr = str.replace("a", "b");  // Replace 'a' with 'b' in each string
            follow_arr.add(replacedStr);
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 16: Combining two strings in the input array and recalculating the superstring using the combined string should result in a superstring that is shorter or equal in length to the original superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testCombinedString(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Combine two strings in the input array */
        ArrayList<String> follow_arr = new ArrayList<String>(arr);
        follow_arr.add(arr.get(0) + arr.get(1));  // Combine the first two strings

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(follow_out.length() <= source_out.length());
    }

    /**
     * Metamorphic Relation 17: Removing one occurrence of a string from the input array should result in a superstring that is longer or equal in length to the original superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testOccurrenceRemoval(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Remove one occurrence of a string from the input array */
        ArrayList<String> follow_arr = new ArrayList<String>(arr);
        follow_arr.remove(arr.get(0));  // Remove the first string

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(follow_out.length() >= source_out.length());
    }

    /**
     * Metamorphic Relation 18: Uppercasing or lowercasing all strings in the input array should result in the same output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testStringCasing(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Uppercase or lowercase all strings in the input array */
        ArrayList<String> follow_arrUpper = new ArrayList<String>();
        ArrayList<String> follow_arrLower = new ArrayList<String>();
        for (String str : arr) {
            follow_arrUpper.add(str.toUpperCase());
            follow_arrLower.add(str.toLowerCase());
        }

        /* Get follow-up outputs */
        String follow_outUpper = Superstring.shortest_superstring(follow_arrUpper);
        String follow_outLower = Superstring.shortest_superstring(follow_arrLower);

        /* Verification */
        assertEquals(source_out, follow_outUpper);
        assertEquals(source_out, follow_outLower);
    }

    /**
     * Metamorphic Relation 19: Prepending a common prefix to all strings in the input array should result in a superstring that contains the original array of strings.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testCommonPrefixAddition(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Prepend a common prefix to all strings in the input array */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String str : arr) {
            follow_arr.add("common_" + str);
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(stringContainsAllSubstrings(follow_out, arr));
    }

    /**
     * Metamorphic Relation 20: Sorting the input array of strings lexicographically should not change the output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testStringSorting(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Sort the input array lexicographically */
        ArrayList<String> follow_arr = new ArrayList<String>(arr);
        Collections.sort(follow_arr);

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 21: Applying a specific manipulation (e.g., encoding, encryption, or obfuscation) to all strings in the input array should not change the output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testStringManipulation(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Apply a specific manipulation to all strings in the input array */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String str : arr) {
            String manipulatedStr = applySpecificManipulation(str); // Apply a hypothetical manipulation function
            follow_arr.add(manipulatedStr);
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    private String applySpecificManipulation(String str) {
        // Implementation of the hypothetical manipulation function
        return str.replace("a", "x");  // Example: replacing 'a' with 'x'
    }

    /**
     * Metamorphic Relation 22: Adding a different character or substring to each string in the input array should result in a superstring that contains the original array of strings.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testUniqueCharacterAddition(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Add a unique character or substring to each string in the input array */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String str : arr) {
            follow_arr.add(str + "_uniqueChar");
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(stringContainsAllSubstrings(follow_out, arr));
    }

    //fixed
    /**
     * Metamorphic Relation 23: Adding common suffixes to each string in the input array should result in a superstring that contains the original array of strings.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Add a common suffix to each string in the input array */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String str : arr) {
            follow_arr.add(str + "_commonSuffix");
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(stringContainsAllSubstrings(follow_out, arr));
    }

    /**
     * Metamorphic Relation 24: Repeating each string in the input array a specific number of times should not change the output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testStringRepetition(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Repeat each string in the input array */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String str : arr) {
            follow_arr.add(str.repeat(3)); // Repeat each string 3 times
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 25: Appending a common suffix to the output superstring should result in a superstring that contains the original array of strings.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testSuperstringSuffixAddition(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Append a common suffix to the output superstring */
        String suffix = "_completeSuperstring";
        String follow_out = source_out + suffix;

        /* Verification */
        assertTrue(stringContainsAllSubstrings(follow_out, arr));
    }

    /**
     * Metamorphic Relation 26: Truncating the output superstring or removing a specific substring from the output superstring should result in a superstring that contains the original array of strings.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testSuperstringTruncation(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Truncate the output superstring or remove a specific substring */
        String follow_out = source_out.substring(0, source_out.length() - 3); // Truncate the last 3 characters

        /* Verification */
        assertTrue(stringContainsAllSubstrings(follow_out, arr));
    }

    /**
     * Metamorphic Relation 27: Reversing the order of the substrings in the superstring should result in the reverse order of strings in the input array.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testSuperstringReversal(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Reverse the order of substrings in the superstring */
        String[] substrings = divideSuperstringIntoSubstrings(source_out);
        Collections.reverse(Arrays.asList(substrings));
        String reversed_superstring = String.join("", substrings);

        /* Verification */
        ArrayList<String> originalReversed = new ArrayList<>(arr);
        Collections.reverse(originalReversed);
        assertEquals(reversed_superstring, Superstring.shortest_superstring(originalReversed));
    }

    /**
     * Utility function to divide the superstring into substrings
     */
    private String[] divideSuperstringIntoSubstrings(String superstring) {
        ArrayList<String> substrings = new ArrayList<>();
        for (int i = 0; i < superstring.length(); i++) {
            for (int j = i + 1; j <= superstring.length(); j++) {
                substrings.add(superstring.substring(i, j));
            }
        }
        return substrings.toArray(new String[0]);
    }

    /**
     * Metamorphic Relation 28: Adding the concatenation of two substrings from the superstring to the input array at arbitrary positions should not change the output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testConcatenationAddition(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Extract two substrings from the superstring */
        String superstring = Superstring.shortest_superstring(arr);
        String[] substrings = divideSuperstringIntoSubstrings(superstring);
        String combinedSubstring = substrings[0] + substrings[1];  // Concatenate the first two substrings

        /* Add the combined substring to the input array at arbitrary positions */
        ArrayList<String> follow_arr = new ArrayList<>(arr);
        follow_arr.add(1, combinedSubstring); // Add the substring at index 1

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 29: Merging two strings in the input array and then recalculating the superstring using the merged string should result in a superstring that is longer or equal in length to the original superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testStringMerging(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Merge two strings in the input array */
        ArrayList<String> follow_arr = new ArrayList<String>(arr);
        String mergedString = arr.get(0) + arr.get(1);  // Merge the first two strings
        follow_arr.set(0, mergedString);
        follow_arr.remove(1);

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(follow_out.length() >= source_out.length());
    }

    /**
     * Metamorphic Relation 30: Extracting a substring from the output superstring and replacing it with a different substring should result in a superstring that contains the original array of strings.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testSubstringReplacement(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Extract a substring from the output superstring */
        String extractedSubstring = source_out.substring(2, 6); // Extract a specific substring

        /* Replace the extracted substring with a different substring */
        String modifiedSuperstring = source_out.replace(extractedSubstring, "different");

        /* Verification */
        assertTrue(stringContainsAllSubstrings(modifiedSuperstring, arr));
    }

    /**
     * Metamorphic Relation 31: Appending or prepending a common suffix to all strings in the input array should not change the output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testCommonSuffixAddition(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Append a common suffix to all strings in the input array */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String str : arr) {
            follow_arr.add(str + "_common_suffix");
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 32: Truncating the input array by removing specific substrings and then recalculating the superstring should result in a superstring that is longer or equal in length to the original superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testArrayTruncation(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Remove specific substrings from the input array */
        ArrayList<String> follow_arr = new ArrayList<String>(arr);
        follow_arr.remove(0); // Remove the first string

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(follow_out.length() >= source_out.length());
    }

    /**
     * Metamorphic Relation 33: Applying a reversible transformation to all strings in the input array should result in a superstring that is invariant with respect to the reversible transformation.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testReversibleTransformation(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Apply a reversible transformation to all strings in the input array */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String str : arr) {
            String transformedStr = reverseString(str); // Reversible transformation
            follow_arr.add(transformedStr);
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 34: Alternating the case of characters in all strings of the input array should result in the same output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testStringCaseAlternation(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Alternating the case of characters in all strings of the input array */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String str : arr) {
            String alternatedCaseStr = alternateCase(str);
            follow_arr.add(alternatedCaseStr);
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Utility function to reverse a string
     */
    private String reverseString(String str) {
        // Implementation of the reversible transformation
        return new StringBuilder(str).reverse().toString();
    }

    /**
     * Utility function to alternate the case of characters in a string
     */
    private String alternateCase(String str) {
        // Implementation of alternating the case of characters
        char[] charArray = str.toCharArray();
        for (int i = 0; i < charArray.length; i++) {
            if (Character.isUpperCase(charArray[i])) {
                charArray[i] = Character.toLowerCase(charArray[i]);
            } else if (Character.isLowerCase(charArray[i])) {
                charArray[i] = Character.toUpperCase(charArray[i]);
            }
        }
        return new String(charArray);
    }

    /**
     * Metamorphic Relation 35: Adding or removing leading or trailing whitespaces in all strings of the input array should not change the output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testWhitespaceModification(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Add or remove leading/trailing whitespaces in all strings of the input array */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String str : arr) {
            String modifiedStr = "  " + str.trim() + "  "; // Add leading/trailing whitespaces
            follow_arr.add(modifiedStr);
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 36: Adding or removing line breaks in all strings of the input array should not change the output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testLineBreakModification(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Add or remove line breaks in all strings of the input array */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String str : arr) {
            String modifiedStr = str.replace("\n", "") + "\n"; // Add or remove line breaks
            follow_arr.add(modifiedStr);
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 37: Swapping adjacent strings in the input array should result in the same output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testAdjacentStringSwap(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Swap adjacent strings in the input array */
        ArrayList<String> follow_arr = new ArrayList<>(arr);
        for (int i = 0; i < follow_arr.size() - 1; i += 2) {
            String temp = follow_arr.get(i);
            follow_arr.set(i, follow_arr.get(i + 1));
            follow_arr.set(i + 1, temp);
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 38: Multiplying the occurrence of a string in the input array should not change the output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testStringDuplication(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Duplicate the occurrence of a string in the input array */
        ArrayList<String> follow_arr = new ArrayList<>(arr);
        follow_arr.addAll(arr.subList(0, Math.min(arr.size(), 2))); // Duplicate the first two strings in the array

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 39: Reversing the characters of each string in the input array should not change the output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testStringReversal(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Reverse the characters of each string in the input array */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String str : arr) {
            String reversedStr = new StringBuilder(str).reverse().toString();
            follow_arr.add(reversedStr);
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 40: Adding a common prefix and suffix to each string in the input array should not change the output superstring.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testCommonPrefixSuffixAddition(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Add a common prefix and suffix to each string in the input array */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String str : arr) {
            follow_arr.add("prefix_" + str + "_suffix");
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    public static Stream<Arguments> testcaseProvider() throws Exception {
        return testcaseGenerator.generate(1000);
    }
}
