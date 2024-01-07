import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.security.SecureRandom;
import java.util.stream.Stream;
import org.joda.time.DateTime;
import org.junit.jupiter.params.provider.Arguments;

public class testcaseGenerator {
    public static Stream<Arguments> generate(int num) throws IOException {
        int tcs_num = num;
        int[] range_year = {1970, 2100}; // 年份范围 [1970, 2100)
        int[] range_month = {1, 13}; // 月份范围 [1, 13)
        int[][] range_day = {{1, 31}, {1, 28}, {1, 31}, {1, 30}, {1, 31}, {1, 30}, {1, 31}, {1, 31},
                {1, 30}, {1, 31}, {1, 30}, {1, 31}}; // 日期范围, 左右均为闭
        int[] range_hour = {0, 24}; // 小时范围 [0, 24)
        int[] range_minute = {0, 60}; // 分钟范围 [0, 60)
        int[] range_incr = {0, 100}; // 增量范围 [0, 100)
        SecureRandom rand = new SecureRandom();
        Arguments tcs[] = new Arguments[tcs_num];

        /* 随机生成日期 */
        for (int i = 0; i < tcs_num; i++) {
            int year = rand.nextInt(range_year[0], range_year[1]);
            int month = rand.nextInt(range_month[0], range_month[1]);
            if (month == 2) {
                if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
                    range_day[1][1] = 29;
                } else {
                    range_day[1][1] = 28;
                }
            }
            int day = rand.nextInt(range_day[month - 1][0], range_day[month - 1][1] + 1);
            int hour = rand.nextInt(range_hour[0], range_hour[1]);
            int minute = rand.nextInt(range_minute[0], range_minute[1]);
            int incr = rand.nextInt(range_incr[0], range_incr[1]);

            DateTime time = new DateTime(year, month, day, hour, minute);
            tcs[i] = Arguments.of(time, incr);
        }

        /* 将生成的测试用例写入文件, 方便调试 */
        File file = new File("testcases.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            writer.write("Testcase " + String.valueOf(i) + ":\n");
            writer.write("----------------------------------------------------------------\n");
            writer.write("time: " + tcs[i].get()[0].toString() + "\n");
            writer.write("incr: " + tcs[i].get()[1].toString() + "\n\n");
        }
        writer.close();

        return Stream.of(tcs);
    }
}
