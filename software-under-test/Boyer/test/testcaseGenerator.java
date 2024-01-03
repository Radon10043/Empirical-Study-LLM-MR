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

    /**
     * 随机生成num个测试用例, 每个测试用例包含2个String数据和1个int数据. 主要是针对BoyerTestGPT3P5.java中的test2和test24生成数据
     *
     * @param num
     * @return
     * @throws IOException
     */
    public static Stream<Arguments> generate_ssi(int num) throws IOException {

        int tcs_num = num;
        int lower = 1, upper = 101; // Include lower but exclude upper
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        for (int i = 0; i < tcs_num; i++) {
            int len_text = rand.nextInt(lower, upper);
            int len_pattern = rand.nextInt(lower, upper);
            String text = RandomStringUtils.randomAscii(len_text);
            String pattern = RandomStringUtils.randomAscii(len_pattern);
            int index = rand.nextInt(0, text.length());

            tcs[i] = Arguments.of(text, pattern, index);
        }

        /* 将生成的测试用例保存到文件中, 方便调试用 */
        File file = new File("testcases.ssi.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            String text = tcs[i].get()[0].toString(), pattern = tcs[i].get()[1].toString();
            int index = (int) tcs[i].get()[2];
            writer.write(String.valueOf(i)
                    + "\n----------------------------------------------------------------\n");
            writer.write("text   : " + text + "\n");
            writer.write("pattern: " + pattern + "\n");
            writer.write("index  : " + String.valueOf(index) + "\n\n");
        }
        writer.close();

        return Stream.of(tcs);

    }

    /**
     * 生成num个测试用例, 每个测试用例包含1个String数据. 主要是针对BoyerTestGPT3P5.java中的test15, test18和test39生成测试数据
     *
     * @param num
     * @return
     * @throws IOException
     */
    public static Stream<Arguments> generate_s(int num) throws IOException {

        int tcs_num = num;
        int lower = 1, upper = 101; // Include lower but exclude upper
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        for (int i = 0; i < tcs_num; i++) {
            int len_text = rand.nextInt(lower, upper);
            String s = RandomStringUtils.randomAscii(len_text);

            tcs[i] = Arguments.of(s);
        }

        /* 将生成的测试用例保存到文件中, 方便调试用 */
        File file = new File("testcases.s.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            String s = tcs[i].get()[0].toString();
            writer.write(String.valueOf(i)
                    + "\n----------------------------------------------------------------\n");
            writer.write("s : " + s + "\n");
        }
        writer.close();

        return Stream.of(tcs);

    }
}
