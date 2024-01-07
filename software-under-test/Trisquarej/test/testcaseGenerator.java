package test;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.security.SecureRandom;
import java.util.stream.Stream;

import org.junit.jupiter.params.provider.Arguments;

public class testcaseGenerator {
    /**
     * 随机生成num个测试用例并写入文件
     *
     * @param num
     * @return
     * @throws IOException
     */
    public static Stream<Arguments> generate(int num) throws IOException {
        int tcs_num = num;
        int[] range_value = { 1, 1001 };
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        /* 随机生成三个整数, 表示三角形的三条边 */
        for (int i = 0; i < tcs_num; i++) {
            int a, b, c;
            a = rand.nextInt(range_value[0], range_value[1]);
            b = rand.nextInt(range_value[0], range_value[1]);
            c = rand.nextInt(range_value[0], range_value[1]);
            tcs[i] = Arguments.of(a, b, c);
        }

        /* 写入文件, 方便调试 */
        File file = new File("testcases.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            writer.write("Testcase " + String.valueOf(i) + ":\n");
            writer.write("----------------------------------------------------------------\n");
            writer.write(tcs[i].get()[0].toString() + ", " + tcs[i].get()[1].toString() + ", "
                    + tcs[i].get()[2].toString() + "\n\n");
        }
        writer.close();

        return Stream.of(tcs);
    }
}