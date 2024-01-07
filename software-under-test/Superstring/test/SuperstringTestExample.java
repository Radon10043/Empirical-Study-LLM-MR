package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import java.util.ArrayList;
import java.util.stream.Stream;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import src.Superstring;

public class SuperstringTestExample {
    /**
     * Metamorphic Relation 1: Adding one string A to the array, and A must be contained in the
     * original array, then the output should be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(ArrayList<String> arr) {
        /* Get source output */
        String source_out = Superstring.shortest_superstring(arr);

        /* Construct follow-up input */
        ArrayList<String> follow_arr = new ArrayList<String>();
        follow_arr.addAll(arr);
        follow_arr.add(follow_arr.getFirst());

        /* Get follow-up output */
        String follow_out = Superstring.shortest_superstring(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    public static Stream<Arguments> testcaseProvider() throws Exception {
        return testcaseGenerator.generate(1000);
    }
}
