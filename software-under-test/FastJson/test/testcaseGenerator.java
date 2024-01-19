package test;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.security.SecureRandom;
import java.util.HashMap;
import java.util.stream.Stream;
import org.apache.commons.lang3.RandomStringUtils;
import org.junit.jupiter.params.provider.Arguments;

public class testcaseGenerator {
    public static Stream<Arguments> generate_s(int num) throws IOException {
        int tcs_num = num;
        int[] range_size = {1, 101};
        int[] range_len = {1, 101};
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        /* 构建测试用例 */
        for (int i = 0; i < tcs_num; i++) {
            int size = rand.nextInt(range_size[0], range_size[1]);
            String json_s = "{";
            for (int j = 0; j < size; j++) {
                int len_k = rand.nextInt(range_len[0], range_len[1]);
                int len_v = rand.nextInt(range_len[0], range_len[1]);
                String key = RandomStringUtils.randomAlphanumeric(len_k);
                String value = RandomStringUtils.randomAlphanumeric(len_v);
                json_s = json_s + "\"" + key + "\":\"" + value + "\"";
                if (j < size - 1) {
                    json_s = json_s + ",";
                }
            }
            json_s += "}";
            tcs[i] = Arguments.of(json_s);
        }

        /* 保存到文件, 方便调试 */
        File file = new File("testcases.s.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            writer.write("Testcase " + String.valueOf(i) + "\n");
            writer.write("------------------------------\n");
            writer.write(tcs[i].get()[0].toString() + "\n\n");
        }
        writer.close();

        return Stream.of(tcs);
    }

    public static Stream<Arguments> generate_s_arr(int num) throws IOException {
        int tcs_num = num;
        int[] range_size = {1, 101};
        int[] range_len = {1, 101};
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        /* 构建测试用例 */
        for (int i = 0; i < tcs_num; i++) {
            int size = rand.nextInt(range_size[0], range_size[1]);
            String json_s = "[";
            for (int j = 0; j < size; j++) {
                int len = rand.nextInt(range_len[0], range_len[1]);
                String val = RandomStringUtils.randomAlphanumeric(len);
                json_s = json_s + "\"" + val + "\"";
                if (j < size - 1) {
                    json_s = json_s + ",";
                }
            }
            json_s += "]";
            tcs[i] = Arguments.of(json_s);
        }

        /* 保存到文件, 方便调试 */
        File file = new File("testcases.s.arr.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            writer.write("Testcase " + String.valueOf(i) + "\n");
            writer.write("------------------------------\n");
            writer.write(tcs[i].get()[0].toString() + "\n\n");
        }
        writer.close();

        return Stream.of(tcs);
    }

    public static Stream<Arguments> generate_hm(int num) throws IOException {
        int tcs_num = num;
        int[] range_size = {1, 101};
        int[] range_len = {1, 101};
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        /* 构建测试用例 */
        for (int i = 0; i < tcs_num; i++) {
            int size = rand.nextInt(range_size[0], range_size[1]);
            HashMap<Object, Object> hm = new HashMap<Object, Object>();
            for (int j = 0; j < size; j++) {
                int len_k = rand.nextInt(range_len[0], range_len[1]);
                int len_v = rand.nextInt(range_len[0], range_len[1]);
                String key = RandomStringUtils.randomAlphanumeric(len_k);
                String value = RandomStringUtils.randomAlphanumeric(len_v);
                hm.put(key, value);
            }
            tcs[i] = Arguments.of(hm);
        }

        /* 保存到文件, 方便调试 */
        File file = new File("testcases.hm.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            writer.write("Testcase " + String.valueOf(i) + "\n");
            writer.write("------------------------------\n");
            writer.write(tcs[i].get()[0].toString() + "\n\n");
        }
        writer.close();

        return Stream.of(tcs);
    }
}
