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
     * Metamorphic Relation 1: Add a string to the end of the origin string, the output of the
     * algorithm should be same or greater.
     *
     * @param text
     * @param pattern
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(String text, String pattern) {
        /* Get origin output */
        int origin_res = Boyer.indexOf(text, pattern);

        /* Construct follow-up input */
        String follow_text = text + "xxx";

        /* Get follow-up output */
        int follow_res = Boyer.indexOf(follow_text, pattern);

        /* Verification */
        assertTrue(follow_res >= origin_res);
    }

    static Stream<Arguments> testcaseProvider() throws IOException {
        return testcaseGenerator.generate_ss(1000);
    }
}
