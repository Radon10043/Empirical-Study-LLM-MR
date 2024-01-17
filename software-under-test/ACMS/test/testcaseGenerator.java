package test;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.security.SecureRandom;
import java.util.stream.Stream;

import org.junit.jupiter.params.provider.Arguments;

public class testcaseGenerator {
    /**
     * 随机生成num个测试用例, 并保存到文件中
     *
     * @param num
     * @return
     * @throws IOException
     */
    public static Stream<Arguments> generate(int num) throws IOException {
        int tcs_num = num;
        int[] range1 = { 0, 1001 };
        double[] range2 = { 0, 1001 };
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        /* 随机构建一定数量的测试用例 */
        for (int i = 0; i < tcs_num; i++) {
            int airClass, area;
            boolean isStudent;
            double luggage, economicFee;

            airClass = rand.nextInt(range1[0], range1[1]);
            area = rand.nextInt(range1[0], range1[1]);
            isStudent = rand.nextBoolean();
            luggage = rand.nextDouble(range2[0], range2[1]);
            economicFee = rand.nextDouble(range2[0], range2[1]);
            tcs[i] = Arguments.of(airClass, area, isStudent, luggage, economicFee);
        }

        /* 将测试用例写入文件, 方便调试 */
        File file = new File("testcases.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            writer.write("Testcase " + String.valueOf(i) + ":\n");
            writer.write("----------------------------------------------------------------\n");
            writer.write("airClass   : " + tcs[i].get()[0].toString() + "\n");
            writer.write("area       : " + tcs[i].get()[1].toString() + "\n");
            writer.write("isStudent  : " + tcs[i].get()[2].toString() + "\n");
            writer.write("luggage    : " + tcs[i].get()[3].toString() + "\n");
            writer.write("economicFee: " + tcs[i].get()[4].toString() + "\n\n");
        }
        writer.close();

        return Stream.of(tcs);
    }
}
