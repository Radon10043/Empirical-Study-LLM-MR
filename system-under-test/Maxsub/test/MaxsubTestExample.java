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
     *
     * @param arr
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
        /* @formatter:off */
        File        tc_dir      = new File(System.getProperty("user.dir") + File.separator + "testcases");  /* 测试用例文件所在根目录 */
        File[]      files       = tc_dir.listFiles();                                                           /* 测试用例文件 */
        Arguments[] testcases   = new Arguments[files.length];                                                  /* 所有测试用例 */
        int         cnt         = 0;                                                                            /* 计数用 */
        /* @formatter:on */

        /* 依次读取测试用例的内容, 存入testcases */
        for (File file : files) {

            BufferedReader buf = new BufferedReader(new FileReader(file));
            ArrayList<Integer> arr = new ArrayList<Integer>();
            String line;

            while ((line = buf.readLine()) != null) {
                String[] tmp = line.split(",");
                for (String val : tmp) {
                    arr.add(Integer.parseInt(val));
                }
            }

            testcases[cnt++] = Arguments.of(arr);
            buf.close();

        }

        return Stream.of(testcases);
    }
}
