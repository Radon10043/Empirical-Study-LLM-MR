package test;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.security.SecureRandom;
import java.util.stream.Stream;
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
        String[] cand_planType = {"A", "a", "B", "b"};
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        for (int i = 0; i < tcs_num; i++) {
            String planType;
            int planFee, talkTime, flow;
            planType = cand_planType[rand.nextInt(0, 4)];
            planFee = rand.nextInt(0, 1000);
            talkTime = rand.nextInt(0, 10000);
            flow = rand.nextInt(0, 10000);

            tcs[i] = Arguments.of(planType, planFee, talkTime, flow);
        }

        /* 将生成的测试用例保存到文件中, 方便调试用 */
        File file = new File("testcases.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            writer.write(String.valueOf(i)
                    + "\n----------------------------------------------------------------\n");
            writer.write("planType: " + tcs[i].get()[0].toString() + "\n");
            writer.write("planFee : " + tcs[i].get()[1].toString() + "\n");
            writer.write("talkTime: " + tcs[i].get()[2].toString() + "\n");
            writer.write("flow    : " + tcs[i].get()[3].toString() + "\n\n");
        }
        writer.close();

        return Stream.of(tcs);

    }
}
