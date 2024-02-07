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
        String[] cand = { "seniormanager", "manager", "supervisor" };
        int[] range = {1000, 200000};
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        /* 随机构建一定数量的测试用例 */
        for (int i = 0; i < tcs_num; i++) {
            String stafflevel;
            double actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount;
            stafflevel = cand[rand.nextInt(cand.length)];
            actualmonthlymileage = rand.nextInt(range[1] - range[0]) + range[0];
            monthlysalesamount = rand.nextInt(range[1] - range[0]) + range[0];
            airfareamount = rand.nextInt(range[1] - range[0]) + range[0];
            otherexpensesamount = rand.nextInt(range[1] - range[0]) + range[0];
            tcs[i] = Arguments.of(stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);
        }

        /* 将测试用例写入文件, 方便调试 */
        File file = new File("testcases.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            writer.write("Testcase " + String.valueOf(i) + ":\n");
            writer.write("----------------------------------------------------------------\n");
            writer.write("stafflevel          : " + tcs[i].get()[0].toString() + "\n");
            writer.write("actualmonthlymileage: " + tcs[i].get()[1].toString() + "\n");
            writer.write("monthlysalesamount  : " + tcs[i].get()[2].toString() + "\n");
            writer.write("airfareamount       : " + tcs[i].get()[3].toString() + "\n");
            writer.write("otherexpenseamount  : " + tcs[i].get()[4].toString() + "\n\n");
        }
        writer.close();

        return Stream.of(tcs);
    }
}
