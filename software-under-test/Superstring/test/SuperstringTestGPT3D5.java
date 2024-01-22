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

public class SuperstringTestGPT3D5 {
    /**
     * Metamorphic Relation 2: Re-ordering the strings in the array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input */
        Collections.shuffle(arr);

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 3: Removing one string A from the array, and the output should be no
     * longer than the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input */
        ArrayList<String> follow_arr = new ArrayList<String>();
        follow_arr.addAll(arr);
        follow_arr.remove(0);

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertTrue(follow_out.length() <= source_out.length());
    }

    /**
     * Metamorphic Relation 4: Adding duplicate strings to the array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input */
        ArrayList<String> follow_arr = new ArrayList<String>();
        follow_arr.addAll(arr);
        follow_arr.add(arr.get(0));

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 5: Replacing one string A with another string B, the output should not
     * necessarily be shorter.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input */
        ArrayList<String> follow_arr = new ArrayList<String>();
        follow_arr.addAll(arr);
        follow_arr.set(0, "replacement_string");

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        // The output should be no longer than the original output, but not necessarily shorter
        assertTrue(follow_out.length() <= source_out.length());
    }

    /**
     * Metamorphic Relation 6: The output should remain the same when all strings in the array are
     * empty or null.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input with all empty or null strings */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String s : arr) {
            follow_arr.add("");
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 7: Adding or removing whitespace characters in the strings should not
     * change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input with whitespace changes */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String s : arr) {
            follow_arr.add(s + " "); // add whitespace at the end of each string
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 8: Repeating the strings in the array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input with repeated strings */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String s : arr) {
            follow_arr.add(s);
            follow_arr.add(s); // add the same string twice
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 9: The order of the strings in the array does not affect the output if
     * all strings have the same content.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input with reordered strings */
        ArrayList<String> follow_arr = new ArrayList<String>(arr);
        Collections.shuffle(follow_arr);

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 10: Adding an empty string to the array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input by adding an empty string */
        ArrayList<String> follow_arr = new ArrayList<String>(arr);
        follow_arr.add("");

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 11: Repeating the entire array should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input by repeating the entire array */
        ArrayList<String> follow_arr = new ArrayList<String>(arr);
        follow_arr.addAll(arr);

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 12: Appending the entire array to itself in reverse order should result
     * in the same output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input by appending the entire array to itself in reverse order */
        ArrayList<String> follow_arr = new ArrayList<String>(arr);
        Collections.reverse(arr);
        follow_arr.addAll(arr);

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 13: If all strings in the input array are identical, the output should
     * be the same as any single input string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input with all identical strings */
        ArrayList<String> follow_arr =
                new ArrayList<String>(Collections.nCopies(arr.size(), arr.get(0)));

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 14: If the input array contains a single string, the output should be
     * the same as that string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(ArrayList<String> arr) {
        /* Assuming that the input array contains only one string */

        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Verification */
        assertEquals(source_out, arr.get(0));
    }

    /**
     * Metamorphic Relation 15: If the input array is empty, the output should also be empty or
     * null.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(ArrayList<String> arr) {
        /* Assuming that the input array is empty */

        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Verification */
        assertTrue(source_out.isEmpty() || source_out == null);
    }

    /**
     * Metamorphic Relation 16: If the input array contains strings with common prefixes, the output
     * should not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(ArrayList<String> arr) {
        for (String s : arr) {
            // Construct follow-up input with common prefixes
            String prefix = s.substring(0, s.length() / 2);
            ArrayList<String> follow_arr = new ArrayList<String>(arr.size());
            for (int i = 0; i < arr.size(); i++) {
                follow_arr.add(prefix + arr.get(i));
            }

            // Get source and follow-up outputs
            String source_out = Superstring.shortest_superstring(arr);
            String follow_out = Superstring.shortest_superstring(follow_arr);

            // Verification
            assertEquals(source_out, follow_out);
        }
    }

    /**
     * Metamorphic Relation 17: If all strings in the array are substrings of each other, the output
     * should be the same as any of the strings.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(ArrayList<String> arr) {
        for (String s : arr) {
            // Construct follow-up input with all strings as substrings of each other
            ArrayList<String> follow_arr = new ArrayList<>(arr.size());
            String combinedString = String.join("", arr);
            for (int i = 0; i < arr.size(); i++) {
                follow_arr.add(combinedString.replace(arr.get(i), ""));
            }

            // Get source and follow-up outputs
            String source_out = Superstring.shortest_superstring(arr);
            String follow_out = Superstring.shortest_superstring(follow_arr);

            // Verification
            assertEquals(source_out, follow_out);
        }
    }

    /**
     * Metamorphic Relation 18: If the input array contains duplicate strings, removing the
     * duplicates should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(ArrayList<String> arr) {
        HashSet<String> uniqueStrings = new HashSet<>(arr);
        if (uniqueStrings.size() < arr.size()) {
            ArrayList<String> uniqueArr = new ArrayList<>(uniqueStrings);

            // Get source output
            String source_out = Superstring.shortest_superstring(arr);

            // Get follow-up output
            String follow_out = Superstring.shortest_superstring(uniqueArr);

            // Verification
            assertEquals(source_out, follow_out);
        }
    }

    /**
     * Metamorphic Relation 19: If the input array is null, the output should also be null.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(ArrayList<String> arr) {
        /* Assuming that the input array is null */

        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Verification */
        assertNull(source_out);
    }

    /**
     * Metamorphic Relation 20: If the input array contains strings with common suffixes, the output
     * should not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(ArrayList<String> arr) {
        for (String s : arr) {
            // Construct follow-up input with common suffixes
            String suffix = s.substring(s.length() / 2);
            ArrayList<String> follow_arr = new ArrayList<String>(arr.size());
            for (int i = 0; i < arr.size(); i++) {
                follow_arr.add(arr.get(i) + suffix);
            }

            // Get source and follow-up outputs
            String source_out = Superstring.shortest_superstring(arr);
            String follow_out = Superstring.shortest_superstring(follow_arr);

            // Verification
            assertEquals(source_out, follow_out);
        }
    }

    /**
     * Metamorphic Relation 21: If the input array contains strings that are permutations of each
     * other, the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(ArrayList<String> arr) {
        ArrayList<String> permutations = new ArrayList<>();

        // Generate permutations of the first string
        permute(arr.get(0), 0, arr.get(0).length(), permutations);

        for (String permuted : permutations) {
            // Construct follow-up input with permutations
            ArrayList<String> follow_arr = new ArrayList<>(arr);
            follow_arr.set(0, permuted);

            // Get source and follow-up outputs
            String source_out = Superstring.shortest_superstring(arr);
            String follow_out = Superstring.shortest_superstring(follow_arr);

            // Verification
            assertEquals(source_out, follow_out);
        }
    }

    // Helper function to generate permutations
    private void permute(String str, int l, int r, ArrayList<String> permutations) {
        if (l == r) {
            permutations.add(str);
        } else {
            for (int i = l; i < r; i++) {
                str = swap(str, l, i);
                permute(str, l + 1, r, permutations);
                str = swap(str, l, i);
            }
        }
    }

    // Helper function to swap characters in a string
    private String swap(String a, int i, int j) {
        char[] charArray = a.toCharArray();
        char temp = charArray[i];
        charArray[i] = charArray[j];
        charArray[j] = temp;
        return String.valueOf(charArray);
    }

    /**
     * Metamorphic Relation 22: If all strings in the input array are reverse of each other or
     * palindromes, the output should also be palindrome.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(ArrayList<String> arr) {
        boolean allPalindromes = true;
        for (String s : arr) {
            String reverse = new StringBuilder(s).reverse().toString();
            if (!s.equals(reverse)) {
                allPalindromes = false;
                break;
            }
        }

        if (allPalindromes) {
            // Get source output
            String source_out = Superstring.shortest_superstring(arr);

            // Verification
            assertTrue(isPalindrome(source_out));
        }
    }

    // Helper function to check if a string is a palindrome
    private boolean isPalindrome(String str) {
        int i = 0, j = str.length() - 1;
        while (i < j) {
            if (str.charAt(i) != str.charAt(j)) {
                return false;
            }
            i++;
            j--;
        }
        return true;
    }

    /**
     * Metamorphic Relation 23: If the input array contains strings with a common substring, the
     * output should not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(ArrayList<String> arr) {
        for (String s : arr) {
            // Construct follow-up input with common substrings
            String commonSubstring = s.substring(1, s.length() - 1);
            ArrayList<String> follow_arr = new ArrayList<String>(arr.size());
            for (int i = 0; i < arr.size(); i++) {
                follow_arr.add(arr.get(i) + commonSubstring + arr.get(i));
            }

            // Get source and follow-up outputs
            String source_out = Superstring.shortest_superstring(arr);
            String follow_out = Superstring.shortest_superstring(follow_arr);

            // Verification
            assertEquals(source_out, follow_out);
        }
    }

    /**
     * Metamorphic Relation 24: If the input array is sorted in ascending order, the output should
     * not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(ArrayList<String> arr) {
        // Get source output
        String source_out = Superstring.shortest_superstring(arr);

        // Construct follow-up input by sorting the array
        ArrayList<String> follow_arr = new ArrayList<String>(arr);
        Collections.sort(follow_arr);

        // Get follow-up output
        String follow_out = Superstring.shortest_superstring(follow_arr);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 25: If the input array is sorted in descending order, the output should
     * not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(ArrayList<String> arr) {
        // Get source output
        String source_out = Superstring.shortest_superstring(arr);

        // Construct follow-up input by sorting the array in descending order
        ArrayList<String> follow_arr = new ArrayList<String>(arr);
        Collections.sort(follow_arr, Collections.reverseOrder());

        // Get follow-up output
        String follow_out = Superstring.shortest_superstring(follow_arr);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 26: If the input array contains strings in all uppercase or all
     * lowercase, the output should not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(ArrayList<String> arr) {
        // Get source output
        String source_out = Superstring.shortest_superstring(arr);

        // Construct follow-up input by converting all strings to uppercase
        ArrayList<String> follow_arrUppercase = new ArrayList<>();
        for (String s : arr) {
            follow_arrUppercase.add(s.toUpperCase());
        }

        // Get follow-up output
        String follow_outUppercase = Superstring.shortest_superstring(follow_arrUppercase);

        // Verification
        assertEquals(source_out, follow_outUppercase);

        // Construct follow-up input by converting all strings to lowercase
        ArrayList<String> follow_arrLowercase = new ArrayList<>();
        for (String s : arr) {
            follow_arrLowercase.add(s.toLowerCase());
        }

        // Get follow-up output
        String follow_outLowercase = Superstring.shortest_superstring(follow_arrLowercase);

        // Verification
        assertEquals(source_out, follow_outLowercase);
    }

    /**
     * Metamorphic Relation 27: If the length of the strings in the input array is all the same, the
     * output should not be longer than the length of the strings.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(ArrayList<String> arr) {
        // Check if the length of all strings in the array is the same
        int length = arr.get(0).length();
        boolean sameLength = arr.stream().allMatch(s -> s.length() == length);

        if (sameLength) {
            // Get source output
            String source_out = Superstring.shortest_superstring(arr);

            // Verify that the output is not longer than the length of the strings
            assertTrue(source_out.length() <= length);
        }
    }

    /**
     * Metamorphic Relation 28: If the input array contains strings with a common prefix and a
     * common suffix, the output should not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(ArrayList<String> arr) {
        // Construct follow-up input with common prefix and suffix
        String prefix = arr.get(0).substring(0, 2);
        String suffix = arr.get(0).substring(arr.get(0).length() - 2);
        ArrayList<String> follow_arr = new ArrayList<String>(arr.size());
        for (String s : arr) {
            follow_arr.add(prefix + s + suffix);
        }

        // Get source and follow-up outputs
        String source_out = Superstring.shortest_superstring(arr);
        String follow_out = Superstring.shortest_superstring(follow_arr);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 29: If the input array contains strings in a different language
     * encoding, the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input with strings in a different language encoding */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String s : arr) {
            follow_arr.add(
                    new String(s.getBytes(StandardCharsets.UTF_8), StandardCharsets.ISO_8859_1));
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 30: If the input array contains strings with special characters, the
     * output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input with strings containing special characters */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String s : arr) {
            follow_arr.add(s + "!@#$%^&*()");
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 31: If the input array contains strings with different types of line
     * breaks (e.g., Unix vs. Windows style line breaks), the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input with strings containing different types of line breaks */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String s : arr) {
            follow_arr.add(s + "\r\n"); // Windows line breaks
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 32: If the input array contains strings with different combinations of
     * new lines and spaces, the output should not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input with strings containing new lines and spaces */
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String s : arr) {
            follow_arr.add(" " + s + "\n"); // add spaces and new lines
        }

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 33: If all strings in the input array are consecutive numbers, the
     * output should not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(ArrayList<String> arr) {
        boolean areConsecutiveNumbers = true;
        try {
            int start = Integer.parseInt(arr.get(0));
            for (int i = 1; i < arr.size(); i++) {
                if (Integer.parseInt(arr.get(i)) != start + i) {
                    areConsecutiveNumbers = false;
                    break;
                }
            }
        } catch (NumberFormatException e) {
            areConsecutiveNumbers = false;
        }

        if (areConsecutiveNumbers) {
            // Get source output
            String source_out = Superstring.shortest_superstring(arr);

            // Verify the output remains the same
            String follow_out = Superstring.shortest_superstring(arr);
            assertEquals(source_out, follow_out);
        }
    }

    /**
     * Metamorphic Relation 34: If the input array contains numbers in a different format (e.g.,
     * decimal vs. octal), the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(ArrayList<String> arr) {
        // Get source output
        String source_out = Superstring.shortest_superstring(arr);

        // Construct follow-up input with numbers in a different format
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String s : arr) {
            if (s.startsWith("0")) {
                follow_arr.add(Integer.toOctalString(Integer.parseInt(s)));
            } else {
                follow_arr.add("0" + Integer.toOctalString(Integer.parseInt(s)));
            }
        }

        // Get follow-up output
        String follow_out = Superstring.shortest_superstring(follow_arr);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 35: If the input array contains strings with leading or trailing spaces,
     * the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(ArrayList<String> arr) {
        // Get source output
        String source_out = Superstring.shortest_superstring(arr);

        // Construct follow-up input with strings containing leading or trailing spaces
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String s : arr) {
            follow_arr.add(" " + s + " ");
        }

        // Get follow-up output
        String follow_out = Superstring.shortest_superstring(follow_arr);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 36: If the input array contains strings with unicode escape sequences,
     * the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(ArrayList<String> arr) {
        // Get source output
        String source_out = Superstring.shortest_superstring(arr);

        // Construct follow-up input with strings containing unicode escape sequences
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String s : arr) {
            follow_arr.add("\\u" + Integer.toHexString(s.codePointAt(0)));
        }

        // Get follow-up output
        String follow_out = Superstring.shortest_superstring(follow_arr);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 37: If the input array contains strings with emojis or special
     * characters, the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(ArrayList<String> arr) {
        // Get source output
        String source_out = Superstring.shortest_superstring(arr);

        // Construct follow-up input with strings containing emojis or special characters
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String s : arr) {
            follow_arr.add(s + "😊"); // add emojis
        }

        // Get follow-up output
        String follow_out = Superstring.shortest_superstring(follow_arr);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 38: If the input array contains strings with different date formats, the
     * output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(ArrayList<String> arr) {
        // Get source output
        String source_out = Superstring.shortest_superstring(arr);

        // Construct follow-up input with strings in different date formats
        ArrayList<String> follow_arr = new ArrayList<String>();
        for (String s : arr) {
            LocalDate date = LocalDate.parse(s, DateTimeFormatter.ofPattern("yyyy-MM-dd"));
            follow_arr.add(date.format(DateTimeFormatter.ofPattern("dd/MM/yyyy")));
        }

        // Get follow-up output
        String follow_out = Superstring.shortest_superstring(follow_arr);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 39: If the input array contains strings representing numerical values,
     * the output should remain the same when the string representations are transformed into their
     * corresponding numerical values.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(ArrayList<String> arr) {
        // Get source output
        String source_out = Superstring.shortest_superstring(arr);

        // Construct follow-up input with strings transformed into their numerical values
        ArrayList<String> follow_arr = new ArrayList<>();
        for (String s : arr) {
            int numericalValue = Integer.parseInt(s);
            follow_arr.add(String.valueOf(numericalValue));
        }

        // Get follow-up output
        String follow_out = Superstring.shortest_superstring(follow_arr);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 40: If the input array contains strings that are anagrams of each other,
     * the output should be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(ArrayList<String> arr) {
        // Get source output
        String source_out = Superstring.shortest_superstring(arr);

        // Construct follow-up input with anagrams
        ArrayList<String> follow_arr = new ArrayList<>(arr.size());
        for (String s : arr) {
            char[] charArray = s.toCharArray();
            Arrays.sort(charArray); // sort the characters in the string
            follow_arr.add(new String(charArray));
        }

        // Get follow-up output
        String follow_out = Superstring.shortest_superstring(follow_arr);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 41: If the input array contains strings that are permutations of each
     * other, the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test41(ArrayList<String> arr) {
        ArrayList<String> permutations = new ArrayList<>();

        // Generate permutations of the first string
        permute(arr.get(0), 0, arr.get(0).length(), permutations);

        for (String permuted : permutations) {
            // Construct follow-up input with permutations
            ArrayList<String> follow_arr = new ArrayList<>(arr);
            follow_arr.set(0, permuted);

            // Get source and follow-up outputs
            String source_out = Superstring.shortest_superstring(arr);
            String follow_out = Superstring.shortest_superstring(follow_arr);

            // Verification
            assertEquals(source_out, follow_out);
        }
    }

    public static Stream<Arguments> testcaseProvider() throws Exception {
        return testcaseGenerator.generate(1000);
    }
}
