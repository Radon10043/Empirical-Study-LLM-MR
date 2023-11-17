import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;
import org.junit.jupiter.params.provider.Arguments;
import org.apache.commons.lang3.RandomStringUtils;
import org.apache.commons.rng.UniformRandomProvider;
import org.apache.commons.rng.simple.RandomSource;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.MethodSource;


public class BoyerTestGPT {
    /**
     * MR1: Addition of String to the End
     *
     * If you append a string to the end of the original string (e.g., text + "additional"), the
     * output of the algorithm should be the same or greater. This is based on the fact that adding
     * characters to the end of the text doesn't affect the position of the pattern within the
     * original text.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(String text, String pattern) {
        int origin_out = Boyer.indexOf(text, pattern);

        /* Generate random string and append to text */
        UniformRandomProvider rng = RandomSource.XO_RO_SHI_RO_128_PP.create();
        int rand_num = rng.nextInt(1, 101);
        String add_str = RandomStringUtils.randomAlphanumeric(rand_num);

        int follow_out = Boyer.indexOf(text + add_str, pattern);
        assertTrue(follow_out >= origin_out);
    }

    /**
     * MR2: Addition of String to the Beginning
     *
     * If you prepend a string to the beginning of the original string (e.g., "additional" + text),
     * the output of the algorithm should remain unchanged or increase. Similar to MR1, adding
     * characters to the beginning of the text should not affect the position of the pattern.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(String text, String pattern) {
        int origin_out = Boyer.indexOf(text, pattern);

        /* Generate random string and append to text */
        UniformRandomProvider rng = RandomSource.XO_RO_SHI_RO_128_PP.create();
        int rand_num = rng.nextInt(1, 101);
        String add_str = RandomStringUtils.randomAlphanumeric(rand_num);

        int follow_out = Boyer.indexOf(add_str + text, pattern);
        assertTrue(follow_out >= origin_out);
    }

    /**
     * MR3: Reversal of the Original String
     *
     * If you reverse the characters of the original string, the output of the algorithm should
     * remain unchanged. The Boyer-Moore algorithm is not sensitive to the order of characters in
     * the text; it focuses on efficiently skipping unnecessary comparisons based on the pattern.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(String text, String pattern) {
        int origin_out = Boyer.indexOf(text, pattern);

        /* Reverse string */
        String rev_text = new StringBuffer(text).reverse().toString();

        int follow_out = Boyer.indexOf(rev_text, pattern);
        assertEquals(origin_out, follow_out);
    }

    /**
     * MR4: Reversal of the Pattern
     *
     * If you reverse the characters of the pattern, the output of the algorithm should remain
     * unchanged. The Boyer-Moore algorithm is designed to handle pattern reversals efficiently.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(String text, String pattern) {
        int origin_out = Boyer.indexOf(text, pattern);

        /* Reverse string */
        String rev_pattern = new StringBuffer(pattern).reverse().toString();

        int follow_out = Boyer.indexOf(text, rev_pattern);
        assertEquals(origin_out, follow_out);
    }

    /**
     * MR5: Replacement of Characters in the Original String
     *
     * If you replace some characters in the original string with different characters, the output
     * of the algorithm should remain unchanged or increase. This is because the Boyer-Moore
     * algorithm is not affected by changes in characters unrelated to the pattern.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(String text, String pattern) {
        int origin_out = Boyer.indexOf(text, pattern);

        /* Random replace */
        int n = text.length(), threshold = 50;
        StringBuilder sb = new StringBuilder(text);
        UniformRandomProvider rng = RandomSource.XO_RO_SHI_RO_128_PP.create();
        for (int i = 0; i < n; i++) {
            int rand_num = rng.nextInt(1, 101);
            char rand_c = RandomStringUtils.randomAlphanumeric(1).charAt(0);
            if (rand_num <= threshold)
                sb.setCharAt(i, rand_c);
        }

        String bad_text = sb.toString();
        int follow_out = Boyer.indexOf(bad_text, pattern);

        assertEquals(origin_out, follow_out);
    }

    /**
     * MR6: Replacement of Characters in the Pattern
     *
     * If you replace some characters in the pattern with different characters, the output of the
     * algorithm should remain unchanged. The Boyer-Moore algorithm accounts for variations in the
     * pattern.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(String text, String pattern) {
        int origin_out = Boyer.indexOf(text, pattern);

        /* Random replace */
        int n = pattern.length(), threshold = 50;
        StringBuilder sb = new StringBuilder(pattern);
        UniformRandomProvider rng = RandomSource.XO_RO_SHI_RO_128_PP.create();
        for (int i = 0; i < n; i++) {
            int rand_num = rng.nextInt(1, 101);
            char rand_c = RandomStringUtils.randomAlphanumeric(1).charAt(0);
            if (rand_num <= threshold)
                sb.setCharAt(i, rand_c);
        }

        String bad_pattern = sb.toString();
        int follow_out = Boyer.indexOf(pattern, bad_pattern);

        assertEquals(origin_out, follow_out);
    }

    /**
     * MR7: Empty Pattern
     *
     * If the pattern is an empty string, the algorithm should return 0, indicating a match at the
     * beginning of the text.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(String text, String pattern) {
        pattern = "";
        assertEquals(0, Boyer.indexOf(text, pattern));
    }

    /**
     * MR8: Empty Text
     *
     * If the text is an empty string, the algorithm should return -1, indicating that no match is
     * found.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(String text, String pattern) {
        text = "";
        assertEquals(-1, Boyer.indexOf(text, pattern));
    }

    /**
     * MR9: Multiple Occurrences
     *
     * If there are multiple occurrences of the pattern in the text, the algorithm should return the
     * index of the first occurrence.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(String text, String pattern) {
        int origin_out = Boyer.indexOf(text, pattern);

        ArrayList<Integer> al = new ArrayList<Integer>();
        int loc = text.indexOf(pattern);
        while (loc != -1) {
            al.add(loc);
            loc = text.indexOf(pattern, loc + 1);
        }

        assertEquals(origin_out, al.get(0));
    }

    /**
     * MR10: No Occurrence
     *
     * If the pattern does not occur in the text, the algorithm should return -1.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String text, String pattern) {
        /* pattern + text + text will not occur in text ? */
        int out = Boyer.indexOf(text, pattern + text + text);
        assertEquals(-1, out);
    }

    /**
     * MR11: Case Insensitivity
     *
     * If you change the case of characters in both the original string and the pattern (e.g.,
     * convert all characters to lowercase), the output of the algorithm should remain unchanged.
     * The Boyer-Moore algorithm is case-sensitive, and this metamorphic relation checks if the
     * algorithm can handle case-insensitive searches.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(String text, String pattern) {
        int origin_out = Boyer.indexOf(text, pattern);

        /* To lower */
        String l_text = text.toLowerCase(), l_pattern = pattern.toLowerCase();
        int follow_out = Boyer.indexOf(l_text, l_pattern);

        assertEquals(origin_out, follow_out);
    }

    /**
     * MR12: Duplicate Occurrences
     *
     * If you duplicate occurrences of the pattern within the original string, the output of the
     * algorithm should remain unchanged, or the index should increase. This is to ensure the
     * algorithm can handle multiple occurrences of the pattern.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(String text, String pattern) {
        int origin_out = Boyer.indexOf(text, pattern);

        /* 让pattern重复出现, 也没说在哪重复 */
        String follow_text = text + pattern + pattern;
        int follow_out = Boyer.indexOf(follow_text, pattern);

        assertTrue(follow_out >= origin_out);
    }

    /**
     * MR13: Partial Overlap
     *
     * If you overlap a part of the pattern with the end of the original string, the algorithm
     * should still find the pattern at the overlapping position. This tests the robustness of the
     * algorithm when the pattern partially extends beyond the end of the text.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(String text, String pattern) {
        /* TODO */
    }

    /**
     * MR14: Remove Characters from the Original String
     *
     * If you remove characters from the original string, the output of the algorithm should remain
     * unchanged or decrease. The algorithm should still correctly locate the pattern even if some
     * characters are removed.
     *
     * @param text
     * @param pattern
     */
    public void test14(String text, String pattern) {
        int origin_out = Boyer.indexOf(text, pattern);

        /* Remove randomly */
        UniformRandomProvider rng = RandomSource.XO_RO_SHI_RO_128_PP.create();
        String follow_text = "";
        int n = text.length();
        int threshold = 50; /* Delete probability */
        for (int i = 0; i < n; i++) {
            int rand_num = rng.nextInt(1, 101);
            if (rand_num <= threshold)
                continue;
            follow_text += text.charAt(i);
        }

        int follow_out = Boyer.indexOf(follow_text, pattern);
        assertTrue(follow_out <= origin_out);
    }

    /**
     * MR15: Remove Characters from the Pattern
     *
     * If you remove characters from the pattern, the output of the algorithm should remain
     * unchanged or decrease. The algorithm should correctly find occurrences of the modified
     * pattern within the text.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String text, String pattern) {
        int origin_out = Boyer.indexOf(text, pattern);

        UniformRandomProvider rng = RandomSource.XO_RO_SHI_RO_128_PP.create();
        String follow_pattern = "";
        int n = pattern.length();
        int threshold = 50;
        for (int i = 0; i < n; i++) {
            int rand_num = rng.nextInt(1, 101);
            if (rand_num <= threshold)
                continue;
            follow_pattern += pattern.charAt(i);
        }

        int follow_out = Boyer.indexOf(text, follow_pattern);
        assertTrue(follow_out <= origin_out);
    }

    /**
     * MR16: Add Special Characters
     *
     * If you add special characters to both the original string and the pattern, the output of the
     * algorithm should remain unchanged. This tests the algorithm's ability to handle special
     * characters without affecting the matching process.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(String text, String pattern) {
        int origin_out = Boyer.indexOf(text, pattern);

        UniformRandomProvider rng = RandomSource.XO_RO_SHI_RO_128_PP.create();
        int rand_num = rng.nextInt(1, 101);
        String add_str = RandomStringUtils.randomAlphanumeric(rand_num);
        int follow_out = Boyer.indexOf(text + add_str, pattern + add_str);

        assertEquals(origin_out, follow_out);
    }

    /**
     * MR17: Pattern as a Prefix of the Text
     *
     * If the pattern is a prefix of the text, the algorithm should return 0, indicating a match at
     * the beginning of the text.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String text, String pattern) {
        String follow_text = pattern + text;
        int follow_out = Boyer.indexOf(follow_text, pattern);
        assertEquals(0, follow_out);
    }

    /**
     * MR18: Pattern as a Suffix of the Text
     *
     * If the pattern is a suffix of the text, the algorithm should return the length difference
     * between the text and the pattern, indicating a match at the end of the text.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String text, String pattern) {
        String follow_text = text + pattern;
        int follow_out = Boyer.indexOf(follow_text, pattern);

        /* FIXME: Please confirm */
        assertEquals(text.length(), follow_out);
    }

    /**
     * MR19: Random Shuffling of Characters
     *
     * If you randomly shuffle the characters in both the original string and the pattern, the
     * output of the algorithm should remain unchanged. This tests the algorithm's resilience to
     * arbitrary character arrangements.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String text, String pattern) {
        int origin_out = Boyer.indexOf(text, pattern);

        String follow_text = shuffle_str(text);
        String follow_pattern = shuffle_str(pattern);
        int follow_out = Boyer.indexOf(follow_text, follow_pattern);

        assertEquals(origin_out, follow_out);
    }

    public String shuffle_str(String input) {
        UniformRandomProvider rng = RandomSource.XO_RO_SHI_RO_128_PP.create();
        List<Character> chars = new ArrayList<Character>();
        for (char c : input.toCharArray())
            chars.add(c);
        StringBuilder sb = new StringBuilder(input.length());
        while (chars.size() != 0) {
            int rand_num = rng.nextInt(0, chars.size());
            sb.append(chars.remove(rand_num));
        }
        return sb.toString();
    }

    /**
     * MR20: Repeated Patterns
     *
     * If you repeat the pattern multiple times within the text, the algorithm should return the
     * index of the first occurrence. This checks if the algorithm correctly handles repeated
     * patterns.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(String text, String pattern) {
        /* Same as MR12 */
    }

    static Stream<Arguments> testcaseProvider() {
        return Stream.of(Arguments.of("abcdefg", "abc"), Arguments.of("abcdefg", "xyz"));
    }
}
