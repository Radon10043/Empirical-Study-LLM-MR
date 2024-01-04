package test;

import java.util.ArrayList;
import java.util.Collections;
import java.util.stream.Stream;

import org.apache.commons.lang3.RandomStringUtils;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import static org.junit.Assert.assertEquals;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;

public class LucenceEampleTest {
    /* 存储了多个测试用例的根目录 */
    private static String[] testcase_roots = {
            "testcases\\tc1",
            "testcases\\tc2",
            "testcases\\tc3"
    };

    /**
     * 为测试用例中要全文检索的文件生成索引
     *
     * @throws Exception
     */
    @BeforeAll
    public static void generateIndex() throws Exception {
        for (String root : testcase_roots) {
            Utils.generateIndex(root);
        }
    }

    /**
     * Metamorphic Relation 1: Swapping the terms of a OR or AND operator in the
     * query should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Construct follow-up input */
        ArrayList<String> follow_search_terms = new ArrayList<String>();
        follow_search_terms.addAll(search_terms);
        if (search_terms.size() == 3 && (search_terms.get(1).equals("OR") || search_terms.get(1).equals("AND"))) {
            Collections.swap(follow_search_terms, 0, 2);
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 2: Inserting an OR term in the query that does not exist
     * in the text should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        if (search_terms.size() > 1) {
            return;
        }

        /* Construct follow-up input */
        ArrayList<String> follow_search_terms = new ArrayList<String>();
        ArrayList<String> tmp = new ArrayList<String>();
        follow_search_terms.addAll(search_terms);
        tmp.add("abcdefghij");
        while (!Utils.fullTextSearch(index_dir, tmp).isEmpty()) {
            String s = RandomStringUtils.randomAlphabetic(5);
            tmp.set(0, s);
        }
        follow_search_terms.add("OR");
        follow_search_terms.addAll(tmp);

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 3: Excluding an OR term in the query that does not exist
     * in the text should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        if (search_terms.size() != 3 || !search_terms.get(1).equals("OR")) {
            return;
        }

        /* Construct follow-up input */
        ArrayList<String> follow_search_terms = new ArrayList<String>();
        ArrayList<String> term1 = new ArrayList<String>();
        ArrayList<String> term2 = new ArrayList<String>();
        term1.add(search_terms.get(0));
        term2.add(search_terms.get(2));
        if (Utils.fullTextSearch(index_dir, term1).isEmpty()) {
            follow_search_terms.add(term2.get(0));
        } else if (Utils.fullTextSearch(index_dir, term2).isEmpty()) {
            follow_search_terms.add(term1.get(0));
        } else {
            return;
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * 构建测试输入
     *
     * @return
     * @throws Exception
     */
    public static Stream<Arguments> testcaseProvider() throws Exception {

        int n = testcase_roots.length;
        Arguments[] testcases = new Arguments[n];

        /* 依次构建测试输入 */
        for (int i = 0; i < n; i++) {

            /* @formatter:off */
            String              index_dir           = testcase_roots[i] + File.separator + "index";
            File                search_terms_file   = new File(testcase_roots[i] + File.separator + "search_terms.txt");
            InputStreamReader   read                = new InputStreamReader(new FileInputStream(search_terms_file), "UTF-8");
            BufferedReader      buf                 = new BufferedReader(read);
            String              line                = new String();
            ArrayList<String>   search_terms        = new ArrayList<String>();
            /* @formatter:on */

            /* 读取搜索项的内容, 存入search_terms */
            while ((line = buf.readLine()) != null) {
                search_terms.add(line);
            }
            buf.close();

            testcases[i] = Arguments.of(index_dir, search_terms);

        }

        return Stream.of(testcases);

    }

}
