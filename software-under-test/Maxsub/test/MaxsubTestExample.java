package test;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.assertEquals;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import src.Maxsub;

public class MaxsubTestExample {
    /**
     * Metamorphic Relation 1: Reversing input array, the output should be same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(ArrayList<Integer> arr) {
        /* Get source output */
        int source_out = Maxsub.max_sub(arr);

        /* Construct follow-up input */
        ArrayList<Integer> follow_arr = new ArrayList<Integer>();
        follow_arr.addAll(arr);
        Collections.reverse(follow_arr);

        /* Get follow-up output */
        int follow_out = Maxsub.max_sub(follow_arr);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    public static Stream<Arguments> testcaseProvider() throws Exception {
        return testcaseGenerator.generate(1000);
    }
}
