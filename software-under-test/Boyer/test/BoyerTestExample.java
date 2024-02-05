package test;

import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.IOException;
import java.util.stream.Stream;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.MethodSource;
import src.Boyer;

public class BoyerTestExample {
    /**
     * Metamorphic Relation 1: If the pattern occurred in the original text, when adding one
     * character to the end of the source text, the output should be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text + "x";

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res == origin_res);
    }

    /**
     * Metamorphic Relation 2: If the pattern occurred in the original text, when deleting one
     * character from the end of the pattern, the output should be the same as or less than the
     * original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(String text, String pattern) {
        if (text.indexOf(pattern) == -1) {
            return;
        }

        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text.substring(0, text.length() - 1);

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res <= origin_res);
    }

    static Stream<Arguments> testcaseProvider() throws IOException {
        return testcaseGenerator.generate_ss(1000);
    }
}
