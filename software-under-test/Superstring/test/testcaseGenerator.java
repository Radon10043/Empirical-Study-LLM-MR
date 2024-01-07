package test;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.stream.Stream;
import org.apache.commons.lang3.RandomStringUtils;
import org.junit.jupiter.params.provider.Arguments;

public class testcaseGenerator {
    public static Stream<Arguments> generate(int num) throws IOException {
        int tcs_num = num;
        int[] range_size = {1, 11}; // 数组长度范围, [1, 11)
        int[] range_len = {1, 11}; // 字符串长度范围, [1, 11)
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        /* 随机生成字符串数组 */
        for (int i = 0; i < tcs_num; i++) {
            int size = rand.nextInt(range_size[0], range_size[1]);
            ArrayList<String> arr = new ArrayList<String>();
            for (int j = 0; j < size; j++) {
                int len = rand.nextInt(range_len[0], range_len[1]);
                arr.add(RandomStringUtils.randomAlphabetic(len));
            }
            tcs[i] = Arguments.of(arr);
        }

        /* 将生成的测试用例保存到文件, 方便调试 */
        File file = new File("testcases.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            ArrayList<String> arr = (ArrayList<String>) tcs[i].get()[0];
            writer.write("Testcase " + String.valueOf(i) + ":\n");
            writer.write("----------------------------------------------------------------\n");
            writer.write(arr.toString());
            writer.write("\n\n");
        }
        writer.close();

        return Stream.of(tcs);
    }
}
