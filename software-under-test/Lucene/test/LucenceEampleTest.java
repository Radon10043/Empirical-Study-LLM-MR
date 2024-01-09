package test;

import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.stream.Stream;

import org.apache.commons.lang3.RandomStringUtils;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import static org.junit.Assert.assertEquals;

public class LucenceEampleTest {
    private static String full_text_root; /* 存储了要检索的全文的根目录 */

    /**
     * 设置要检索的全文的根目录
     *
     * @param full_text_root
     */
    public static void setFullTextRoot(String full_text_root) {
        LucenceEampleTest.full_text_root = full_text_root;
    }

    /**
     * 获取药检所的全文的根目录
     *
     * @return
     */
    public static String getFullTextRoot() {
        return full_text_root;
    }

    /**
     * 设置要检索的全文根目录, 为文件生成索引
     *
     * @throws Exception
     */
    @BeforeAll
    public static void prepare() throws Exception {
        setFullTextRoot(System.getProperty("user.dir") + File.separator + "full_text");
        Utils.generateIndex(full_text_root);
    }

    /**
     * Metamorphic Relation 1: Swapping the terms of a OR or AND operator in the query should not
     * affect the results.
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
     * Metamorphic Relation 2: Inserting an OR term in the query that does not exist in the text
     * should not affect the results.
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
     * Metamorphic Relation 3: Excluding an OR term in the query that does not exist in the text
     * should not affect the results.
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
        return tetscaseGenerator.generate(full_text_root, 1000);
    }

}
