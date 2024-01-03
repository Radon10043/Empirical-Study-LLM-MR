package test;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.security.SecureRandom;
import java.util.stream.Stream;
import org.apache.commons.lang3.RandomStringUtils;
import org.junit.jupiter.params.provider.Arguments;

public class testcaseGenerator {
    /**
     * 随机生成num个测试用例
     *
     * @param num
     * @return
     * @throws IOException
     */
    public static Stream<Arguments> generate(int num) throws IOException {

        int tcs_num = num;
        int lower = 1, upper = 101; // Include lower but exclude upper
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        for (int i = 0; i < tcs_num; i++) {
            int len_text = rand.nextInt(lower, upper);
            int len_pattern = rand.nextInt(lower, upper);
            String text = RandomStringUtils.randomAscii(len_text);
            String pattern = RandomStringUtils.randomAscii(len_pattern);

            if (text.contains(pattern)) {
                System.out.println(text + "," + pattern);
            }

            tcs[i] = Arguments.of(text, pattern);
        }

        /* 将生成的测试用例保存到文件中, 方便调试用 */
        File file = new File("testcases.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            String text = tcs[i].get()[0].toString(), pattern = tcs[i].get()[1].toString();
            writer.write(String.valueOf(i) + "\n----------------------------------------------------------------\n");
            writer.write("text   : " + text + "\n");
            writer.write("pattern: " + pattern + "\n\n");
        }
        writer.close();

        return Stream.of(tcs);

    }
}
