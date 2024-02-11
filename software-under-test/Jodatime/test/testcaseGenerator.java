package test;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Set;
import java.util.stream.Stream;

import org.joda.time.Chronology;
import org.joda.time.DateTime;
import org.joda.time.DateTimeZone;
import org.joda.time.Duration;
import org.joda.time.Interval;
import org.joda.time.LocalDate;
import org.joda.time.LocalDateTime;
import org.joda.time.LocalTime;
import org.joda.time.Period;
import org.junit.jupiter.params.provider.Arguments;

public class testcaseGenerator {
    /**
     * 随机生成一个日期
     *
     * @return
     */
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

    /**
     * 生成一个随机整数, 范围[min, max)
     * 
     * @param min
     * @param max
     * @return
     */
    public static int genInt(int min, int max) {
        SecureRandom rand = new SecureRandom();
        return rand.nextInt(min, max);
    }

    /**
     * 生成一个随机的时间间隔, 范围[min, max), 单位为毫秒
     *
     * @param min
     * @param max
     * @return
     */
    public static Duration genDuration(int min, int max) {
        Duration duration = new Duration(genInt(min, max));
        return duration;
    }

    /**
     * 随机生成一个时间
     *
     * @return
     */
    public static LocalTime genLocalTime() {
        int[] range_hour = {0, 24}; // 小时范围 [0, 24)
        int[] range_minute = {0, 60}; // 分钟范围 [0, 60)
        int[] range_second = {0, 60}; // 秒范围 [0, 60)
        int[] range_millis = {0, 1000}; // 毫秒范围 [0, 1000)
        SecureRandom rand = new SecureRandom();

        int hour = rand.nextInt(range_hour[0], range_hour[1]);
        int minute = rand.nextInt(range_minute[0], range_minute[1]);
        int second = rand.nextInt(range_second[0], range_second[1]);
        int millis = rand.nextInt(range_millis[0], range_millis[1]);

        LocalTime time = new LocalTime(hour, minute, second, millis);
        return time;
    }

    /**
     * 随机生成一个时区
     *
     * @return
     */
    public static DateTimeZone genDateTimeZone() {
        SecureRandom rand = new SecureRandom();
        String sign = rand.nextBoolean() ? "+" : "-";
        int hour = rand.nextInt(0, 24);
        int minute = rand.nextInt(0, 60);
        String id = sign + String.format("%02d", hour) + ":" + String.format("%02d", minute);
        DateTimeZone zone = DateTimeZone.forID(id);
        return zone;
    }

    /**
     * 随机生成一个日期
     *
     * @return
     */
    public static LocalDate genLocalDate() {
        int[] range_year = {1970, 2100}; // 年份范围 [1970, 2100)
        int[] range_month = {1, 13}; // 月份范围 [1, 13)
        int[][] range_day = {{1, 31}, {1, 28}, {1, 31}, {1, 30}, {1, 31}, {1, 30}, {1, 31}, {1, 31},
                {1, 30}, {1, 31}, {1, 30}, {1, 31}}; // 日期范围, 左右均为闭
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

        LocalDate date = new LocalDate(year, month, day);
        return date;
    }

    /**
     * 随机生成一个时间间隔
     *
     * @return
     */
    public static Period genPeriod() {
        int[] range_year = {0, 10}; // 年份范围 [0, 10)
        int[] range_month = {0, 10}; // 月份范围 [0, 10)
        int[] range_week = {0, 10}; // 周范围 [0, 10)
        int[] range_day = {0, 10}; // 天范围 [0, 10)
        int[] range_hour = {0, 24}; // 小时范围 [0, 24)
        int[] range_minute = {0, 60}; // 分钟范围 [0, 60)
        int[] range_second = {0, 60}; // 秒范围 [0, 60)
        int[] range_millis = {0, Integer.MAX_VALUE}; // 毫秒范围 [0, INT_MAX)

        SecureRandom rand = new SecureRandom();

        int year = rand.nextInt(range_year[0], range_year[1]);
        int month = rand.nextInt(range_month[0], range_month[1]);
        int week = rand.nextInt(range_week[0], range_week[1]);
        int day = rand.nextInt(range_day[0], range_day[1]);
        int hour = rand.nextInt(range_hour[0], range_hour[1]);
        int minute = rand.nextInt(range_minute[0], range_minute[1]);
        int second = rand.nextInt(range_second[0], range_second[1]);
        int millis = rand.nextInt(range_millis[0], range_millis[1]);

        Period period = new Period(year, month, week, day, hour, minute, second, millis);
        return period;
    }

    /**
     * 随机生成一个Chronology
     * 
     * @return
     */
    public static Chronology genChronology() {
        return genDateTime().getChronology();
    }

    public static Interval genInterval() {
        DateTime start = genDateTime();
        DateTime end = genDateTime();

        if (start.isAfter(end)) {
            DateTime temp = start;
            start = end;
            end = temp;
        }

        Interval interval = new Interval(start, end);
        return interval;
    }

    public static LocalDateTime genLocalDateTime() {
        int[] range_year = {1970, 2100}; // 年份范围 [1970, 2100)
        int[] range_month = {1, 13}; // 月份范围 [1, 13)
        int[][] range_day = {{1, 31}, {1, 28}, {1, 31}, {1, 30}, {1, 31}, {1, 30}, {1, 31}, {1, 31},
                {1, 30}, {1, 31}, {1, 30}, {1, 31}}; // 日期范围, 左右均为闭
        int[] range_hour = {0, 24}; // 小时范围 [0, 24)
        int[] range_minute = {0, 60}; // 分钟范围 [0, 60)
        int[] range_second = {0, 60}; // 秒范围 [0, 60)
        int[] range_millis = {0, 1000}; // 毫秒范围 [0, 1000)
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
        int second = rand.nextInt(range_second[0], range_second[1]);
        int millis = rand.nextInt(range_millis[0], range_millis[1]);

        LocalDateTime time = new LocalDateTime(year, month, day, hour, minute, second, millis);
        return time;
    }

    /**
     * 将生成的测试用例写入文件, 方便调试
     *
     * @param tcs
     * @throws IOException
     */
    public static void writeToFile(Arguments[] tcs) throws IOException {
        File file = new File("testcases.txt");
        FileWriter writer = new FileWriter(file);
        int tcs_num = tcs.length;
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
}
