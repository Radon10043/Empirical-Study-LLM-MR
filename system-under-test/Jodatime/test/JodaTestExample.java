import org.joda.time.DateTime;
import static org.junit.Assert.assertTrue;
import java.util.stream.Stream;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.MethodSource;

public class JodaTestExample {
    /**
     * Metamorphic Relation 1: Add the number of days and seconds with the same length of time to
     * the input time, the output will be the same.
     *
     * @param time
     * @param days
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test1(DateTime time, int days) {
        /* Get source output */
        DateTime source_out = time.plusDays(days);

        /* Construct follow-up input */
        int seconds = days * 24 * 60 * 60;

        /* Get follow-up output */
        DateTime follow_out = time.plusSeconds(seconds);

        /* Verification */
        assertTrue(source_out.equals(follow_out));
    }

    /**
     * Metamorphic Relation 2: Add the number of weeks and seconds with the same length of time to
     * the input time, the output will be the same.
     *
     * @param time
     * @param days
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test2(DateTime time, int weeks) {
        /* Get source output */
        DateTime source_out = time.plusWeeks(weeks);

        /* Construct follow-up input */
        int seconds = weeks * 7 * 24 * 60 * 60;

        /* Get follow-up output */
        DateTime follow_out = time.plusSeconds(seconds);

        /* Verification */
        assertTrue(source_out.equals(follow_out));
    }

    static Stream<Arguments> testcaseProvider1() {
        /* Testcase 1 */
        DateTime time = new DateTime(2023, 12, 18, 11, 10);
        int days = 3;

        return Stream.of(Arguments.of(time, days));
    }

    static Stream<Arguments> testcaseProvider2() {
        /* Testcase 1 */
        DateTime time = new DateTime(2023, 12, 18, 11, 10);
        int weeks = 3;

        return Stream.of(Arguments.of(time, weeks));
    }
}
