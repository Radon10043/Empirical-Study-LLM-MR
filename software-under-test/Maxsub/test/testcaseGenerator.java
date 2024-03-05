package test;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.stream.Stream;
import org.junit.jupiter.params.provider.Arguments;

public class testcaseGenerator {
    public static Stream<Arguments> generate(int num) throws IOException {
        int tcs_num = num;
        int[] range_size = {1, 1001};   // 数组长度, [1, 1001)
        int[] range_value = {-1001, 1001};  // 数组元素值, [-1001, 1001)
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        /* 随机生成数组 */
        for (int i = 0; i < tcs_num; i++) {
            int size = rand.nextInt(range_size[0], range_size[1]);
            ArrayList<Integer> arr = new ArrayList<Integer>();
            for (int j = 0; j < size; j++) {
                arr.add(rand.nextInt(range_value[0], range_value[1]));
            }
            tcs[i] = Arguments.of(arr);
        }

        /* 生成的测试用例保存到文件, 方便调试 */
        File file = new File("testcases.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            writer.write("Testcase " + String.valueOf(i) + ":\n");
            writer.write("----------------------------------------------------------------\n");
            writer.write(tcs[i].get()[0].toString() + "\n\n");
        }
        writer.close();

        return Stream.of(tcs);
    }
}