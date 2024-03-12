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
    public static Stream<Arguments> generate_ss(int num) throws IOException {

        int tcs_num = num;
        int lower = 1, upper = 101; // Include lower but exclude upper
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        for (int i = 0; i < tcs_num; i++) {
            int len_text = rand.nextInt(lower, upper);
            int len_pattern = rand.nextInt(lower, upper);
            String text = RandomStringUtils.randomAscii(len_text);
            String pattern = RandomStringUtils.randomAscii(len_pattern);

            // 50%的概率将pattern转变为text的子串
            if (len_text >= 2 && rand.nextInt(0, 99) < 50) {
                int start = rand.nextInt(0, len_text / 2);
                int end = rand.nextInt(len_text / 2, len_text);
                pattern = text.substring(start, end);
            }

            tcs[i] = Arguments.of(text, pattern);
        }

        /* 将生成的测试用例保存到文件中, 方便调试用 */
        File file = new File("testcases.ss.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            String text = tcs[i].get()[0].toString(), pattern = tcs[i].get()[1].toString();
            writer.write(String.valueOf(i)
                    + "\n----------------------------------------------------------------\n");
            writer.write("text   : " + text + "\n");
            writer.write("pattern: " + pattern + "\n\n");
        }
        writer.close();

        return Stream.of(tcs);

    }
}
