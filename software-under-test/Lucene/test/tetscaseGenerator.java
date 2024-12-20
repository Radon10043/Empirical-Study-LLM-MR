package test;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.stream.Stream;
import org.apache.commons.lang3.RandomStringUtils;
import org.junit.jupiter.params.provider.Arguments;

public class tetscaseGenerator {
    /**
     * 随机生成一个term
     *
     * @return
     */
    public static String generate_term() {
        SecureRandom rand = new SecureRandom();
        int len_term = rand.nextInt(1, 10);
        String term = RandomStringUtils.randomAlphabetic(len_term);

        /* 防止生成的字符串是关键字 */
        while (term.toUpperCase().equals("OR") || term.toUpperCase().equals("AND")
                || term.toUpperCase().equals("NOT")) {
            term = RandomStringUtils.randomAlphabetic(len_term);
        }

        return term;
    }

    /**
     * 随机抽取一个关键词
     *
     * @return
     */
    public static String generate_keyword() {
        ArrayList<String> keywords = new ArrayList<String>();
        SecureRandom rand = new SecureRandom();

        /* 关键词列表 */
        keywords.add("OR");
        keywords.add("AND");
        keywords.add("NOT");

        /* 随机抽取一个关键词 */
        return keywords.get(rand.nextInt(0, keywords.size()));
    }

    /**
     * 随机生成指定数量的测试用例
     *
     * @param num
     * @return
     */
    public static Stream<Arguments> generate(String full_text_root, int num) throws IOException {
        int tcs_num = num;
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];
        String index_dir = full_text_root + File.separator + "index";

        /* 构建测试用例 */
        for (int i = 0; i < tcs_num; i++) {

            int size = rand.nextInt(1, 4);
            ArrayList<String> search_terms = new ArrayList<String>();

            for (int j = 0; j < size; j++) {

                if (j == 1 && size == 3) {

                    /* 在构建第二个搜索项时, 如果搜索项的数量为3, 则有一定概率生成关键词 */
                    /* 生成关键词和普通字符串的概率是一半一半 */
                    if (rand.nextInt(0, 100) < 50) {
                        search_terms.add(generate_keyword());
                    } else {
                        search_terms.add(generate_term());
                    }

                } else {

                    /* 对于其余搜索项, 生成普通字符串 */
                    search_terms.add(generate_term());

                }

            }

            tcs[i] = Arguments.of(index_dir, search_terms);

        }

        /* 将测试用例保存到文件, 方便调试 */
        File file = new File("testcases.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            writer.write("Testcase " + String.valueOf(i) + "\n");
            writer.write("------------------------------\n");
            writer.write("index_dir   : " + tcs[i].get()[0].toString() + "\n");
            writer.write("search_terms: " + tcs[i].get()[1].toString() + "\n\n");
        }
        writer.close();

        return Stream.of(tcs);
    }

    /**
     * 随机生成指定数量的测试用例
     *
     * @param num
     * @return
     */
    public static Stream<Arguments> generate_ss(String full_text_root, int num) throws IOException {
        int tcs_num = num;
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];
        String index_dir = full_text_root + File.separator + "index";

        /* 构建测试用例 */
        for (int i = 0; i < tcs_num; i++) {

            int size = rand.nextInt(1, 4);
            ArrayList<String> search_terms = new ArrayList<String>();

            for (int j = 0; j < size; j++) {

                if (j == 1 && size == 3) {

                    /* 在构建第二个搜索项时, 如果搜索项的数量为3, 则有一定概率生成关键词 */
                    /* 生成关键词和普通字符串的概率是一半一半 */
                    if (rand.nextInt(0, 100) < 50) {
                        search_terms.add(generate_keyword());
                    } else {
                        search_terms.add(generate_term());
                    }

                } else {

                    /* 对于其余搜索项, 生成普通字符串 */
                    search_terms.add(generate_term());

                }

            }

            tcs[i] = Arguments.of(index_dir, String.join(" ", search_terms));

        }

        /* 将测试用例保存到文件, 方便调试 */
        File file = new File("testcases.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            writer.write("Testcase " + String.valueOf(i) + "\n");
            writer.write("------------------------------\n");
            writer.write("index_dir   : " + tcs[i].get()[0].toString() + "\n");
            writer.write("search_terms: " + tcs[i].get()[1].toString() + "\n\n");
        }
        writer.close();

        return Stream.of(tcs);
    }
}
