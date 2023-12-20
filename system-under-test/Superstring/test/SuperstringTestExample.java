package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
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
     *
     * @param arr
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
        File tc_dir = new File(System.getProperty("user.dir") + File.separator + "testcases");
        File[] files = tc_dir.listFiles();
        Arguments[] testcases = new Arguments[files.length];

        for (int i = 0; i < files.length; i++) {
            BufferedReader buf = new BufferedReader(new FileReader(files[i]));
            String line;
            ArrayList<String> arr = new ArrayList<String>();
            while ((line = buf.readLine()) != null) {
                arr.add(line);
            }
            testcases[i] = Arguments.of(arr);
            buf.close();
        }

        return Stream.of(testcases);
    }
}
