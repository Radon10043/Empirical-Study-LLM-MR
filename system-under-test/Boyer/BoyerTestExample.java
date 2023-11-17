import static org.junit.Assert.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.util.stream.Stream;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.MethodSource;


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
        int origin_res = Boyer.indexOf(text, pattern);
        int follow_res = Boyer.indexOf(text + "xxxxx", pattern);
        assertTrue(follow_res >= origin_res);
    }

    static Stream<Arguments> testcaseProvider() {
        return Stream.of(Arguments.of("abcdefg", "abc"), Arguments.of("abcdefg", "xyz"));
    }
}
