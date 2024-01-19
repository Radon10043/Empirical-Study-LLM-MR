import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.security.SecureRandom;
import java.time.format.DateTimeFormatter;
import java.util.stream.Stream;

import org.joda.time.Chronology;
import org.joda.time.DateTime;
import org.joda.time.DateTimeZone;
import org.joda.time.Instant;
import org.joda.time.Period;
import org.junit.jupiter.params.provider.Arguments;

public class testcaseGenerator {
    public static DateTime genDateTime() {
        int[] range_year = {1970, 2100}; // 年份范围 [1970, 2100)
        int[] range_month = {1, 13}; // 月份范围 [1, 13)
        int[][] range_day = {{1, 31}, {1, 28}, {1, 31}, {1, 30}, {1, 31}, {1, 30}, {1, 31}, {1, 31},
                {1, 30}, {1, 31}, {1, 30}, {1, 31}}; // 日期范围, 左右均为闭
        int[] range_hour = {0, 24}; // 小时范围 [0, 24)
        int[] range_minute = {0, 60}; // 分钟范围 [0, 60)
        SecureRandom rand = new SecureRandom();

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

        DateTime time = new DateTime(year, month, day, hour, minute);
        return time;
    }

    public static int genInt() {
        int[] range = {1, 5};
        SecureRandom rand = new SecureRandom();
        return rand.nextInt(range[0], range[1]);
    }

    public static DateTimeZone genDateTimeZone() {
        int[] range = {-12, 12};
        SecureRandom rand = new SecureRandom();
        return DateTimeZone.forOffsetHours(rand.nextInt(range[0], range[1]));
    }

    public static long genLong() {
        SecureRandom rand = new SecureRandom();
        return rand.nextLong();
    }

    public static Instant genInstant() {
        SecureRandom rand = new SecureRandom();
        return Instant.ofEpochMilli(rand.nextLong());
    }

    public static Period genPeriod() {
        SecureRandom rand = new SecureRandom();
        return Period.hours(rand.nextInt(0, 24));
    }

    public static Chronology genChronology() {
        Chronology c = null;
        return c;
    }

    public static DateTimeFormatter genDateTimeFormatter() {
        String[] patterns = {"dd/MM/yyyy HH:mm:ss", "yyyy/MM/dd HH:mm:ss", "yyyy-MM-dd HH:mm:ss",
                "yyyy-MM-dd'T'HH:mm:ss"};
        SecureRandom rand = new SecureRandom();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern(patterns[rand.nextInt(0, 4)]);
        return formatter;
    }

    public static void writeToFile(Arguments[] tcs, int tcs_num) throws IOException {
        /* 将生成的测试用例写入文件, 方便调试 */
        File file = new File("testcases.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            writer.write("Testcase " + String.valueOf(i) + ":\n");
            writer.write("----------------------------------------------------------------\n");
            for (int j = 0; j < tcs[i].get().length; j++) {
                writer.write(
                        "param" + String.valueOf(j) + ": " + tcs[i].get()[j].toString() + "\n");
            }
            writer.write("\n");
        }
        writer.close();
    }

    public static Stream<Arguments> generate_di(int num) throws IOException {
        int tcs_num = num;
        Arguments tcs[] = new Arguments[tcs_num];

        /* 随机生成日期 */
        for (int i = 0; i < tcs_num; i++) {
            tcs[i] = Arguments.of(genDateTime(), genInt());
        }

        /* 将生成的测试用例写入文件, 方便调试 */
        writeToFile(tcs, tcs_num);

        return Stream.of(tcs);
    }

    public static Stream<Arguments> generate_dii(int num) throws IOException {
        int tcs_num = num;
        Arguments tcs[] = new Arguments[tcs_num];

        /* 随机生成日期 */
        for (int i = 0; i < tcs_num; i++) {
            tcs[i] = Arguments.of(genDateTime(), genInt(), genInt());
        }

        /* 将生成的测试用例写入文件, 方便调试 */
        writeToFile(tcs, tcs_num);

        return Stream.of(tcs);
    }

    public static Stream<Arguments> generate_dzz(int num) throws IOException {
        int tcs_num = num;
        Arguments tcs[] = new Arguments[tcs_num];

        /* 随机生成日期 */
        for (int i = 0; i < tcs_num; i++) {
            tcs[i] = Arguments.of(genDateTime(), genDateTimeZone(), genDateTimeZone());
        }

        /* 将生成的测试用例写入文件, 方便调试 */
        writeToFile(tcs, tcs_num);

        return Stream.of(tcs);
    }

    public static Stream<Arguments> generate_l(int num) throws IOException {
        int tcs_num = num;
        Arguments tcs[] = new Arguments[tcs_num];

        /* 随机生成日期 */
        for (int i = 0; i < tcs_num; i++) {
            tcs[i] = Arguments.of(genLong());
        }

        /* 将生成的测试用例写入文件, 方便调试 */
        writeToFile(tcs, tcs_num);

        return Stream.of(tcs);
    }

    public static Stream<Arguments> generate_iiiiiii(int num) throws IOException {
        int tcs_num = num;
        Arguments tcs[] = new Arguments[tcs_num];

        /* 随机生成日期 */
        for (int i = 0; i < tcs_num; i++) {
            tcs[i] = Arguments.of(genInt(), genInt(), genInt(), genInt(), genInt(), genInt(),
                    genInt());
        }

        /* 将生成的测试用例写入文件, 方便调试 */
        writeToFile(tcs, tcs_num);

        return Stream.of(tcs);
    }

    public static Stream<Arguments> generate_inszz(int num) throws IOException {
        int tcs_num = num;
        Arguments tcs[] = new Arguments[tcs_num];

        /* 随机生成日期 */
        for (int i = 0; i < tcs_num; i++) {
            tcs[i] = Arguments.of(genInstant(), genDateTimeZone(), genDateTimeZone());
        }

        /* 将生成的测试用例写入文件, 方便调试 */
        writeToFile(tcs, tcs_num);

        return Stream.of(tcs);
    }

    public static Stream<Arguments> generate_zz(int num) throws IOException {
        int tcs_num = num;
        Arguments tcs[] = new Arguments[tcs_num];

        /* 随机生成日期 */
        for (int i = 0; i < tcs_num; i++) {
            tcs[i] = Arguments.of(genDateTimeZone(), genDateTimeZone());
        }

        /* 将生成的测试用例写入文件, 方便调试 */
        writeToFile(tcs, tcs_num);

        return Stream.of(tcs);
    }

    public static Stream<Arguments> generate_ddp(int num) throws IOException {
        int tcs_num = num;
        Arguments tcs[] = new Arguments[tcs_num];

        /* 随机生成日期 */
        for (int i = 0; i < tcs_num; i++) {
            tcs[i] = Arguments.of(genDateTime(), genDateTime(), genPeriod());
        }

        /* 将生成的测试用例写入文件, 方便调试 */
        writeToFile(tcs, tcs_num);

        return Stream.of(tcs);
    }

    public static Stream<Arguments> generate_iiiiiiicc(int num) throws IOException {
        int tcs_num = num;
        Arguments tcs[] = new Arguments[tcs_num];

        /* 随机生成日期 */
        for (int i = 0; i < tcs_num; i++) {
            tcs[i] = Arguments.of(genInt(), genInt(), genInt(), genInt(), genInt(), genInt(),
                    genInt(), genChronology(), genChronology());
        }

        /* 将生成的测试用例写入文件, 方便调试 */
        writeToFile(tcs, tcs_num);

        return Stream.of(tcs);
    }

    public static Stream<Arguments> generate_dff(int num) throws IOException {
        int tcs_num = num;
        Arguments tcs[] = new Arguments[tcs_num];

        /* 随机生成日期 */
        for (int i = 0; i < tcs_num; i++) {
            tcs[i] = Arguments.of(genDateTime(), genDateTimeFormatter(), genDateTimeFormatter());
        }

        /* 将生成的测试用例写入文件, 方便调试 */
        writeToFile(tcs, tcs_num);

        return Stream.of(tcs);
    }

    public static Stream<Arguments> generate_iiiiiiiii(int num) throws IOException {
        int tcs_num = num;
        Arguments tcs[] = new Arguments[tcs_num];

        /* 随机生成日期 */
        for (int i = 0; i < tcs_num; i++) {
            tcs[i] = Arguments.of(genInt(), genInt(), genInt(), genInt(), genInt(), genInt(),
                    genInt(), genInt(), genInt());
        }

        /* 将生成的测试用例写入文件, 方便调试 */
        writeToFile(tcs, tcs_num);

        return Stream.of(tcs);
    }
}
