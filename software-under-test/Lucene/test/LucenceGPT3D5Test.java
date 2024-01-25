package test;

import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Stream;

import org.apache.commons.lang3.RandomStringUtils;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import static org.junit.Assert.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class LucenceGPT3D5Test {
    private static String full_text_root; /* 存储了要检索的全文的根目录 */

    /**
     * 设置要检索的全文的根目录
     *
     * @param full_text_root
     */
    public static void setFullTextRoot(String full_text_root) {
        LucenceGPT3D5Test.full_text_root = full_text_root;
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
     * Metamorphic Relation 1: Reversing the order of the search terms should not
     * affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        ArrayList<String> follow_search_terms = new ArrayList<>(search_terms);  // Fix
        Collections.reverse(follow_search_terms);

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 2: Negating the query terms should not affect the
     * results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        ArrayList<String> follow_search_terms = new ArrayList<>();  // Fix
        for (String term : search_terms) {
            follow_search_terms.add("NOT " + term);
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 3: Adding a wildcard character at the end of each search
     * term should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        ArrayList<String> follow_search_terms = new ArrayList<>();  // Fix
        for (String term : search_terms) {
            follow_search_terms.add(term + "*");
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 4: Adding a placeholder term to the query should not
     * affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        ArrayList<String> follow_search_terms = new ArrayList<>(search_terms);  // Fix
        follow_search_terms.add("placeholder");

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 5: Removing a term from the query should not affect the
     * results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(String index_dir, ArrayList<String> search_terms) throws Exception {
        if (search_terms.size() < 2) {
            return;
        }

        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        ArrayList<String> follow_search_terms = new ArrayList<>(search_terms);  // Fix
        follow_search_terms.remove(0);

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 6: Using different boolean operators in the query should
     * not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        ArrayList<String> follow_search_terms = new ArrayList<>(search_terms);  // Fix
        if (search_terms.size() > 2 && search_terms.get(1).equals("AND")) {
            follow_search_terms.set(1, "OR");
        } else if (search_terms.size() > 2 && search_terms.get(1).equals("OR")) {
            follow_search_terms.set(1, "AND");
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 7: Applying the same query terms multiple times should
     * not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        ArrayList<String> follow_search_terms = new ArrayList<>(search_terms);
        follow_search_terms.addAll(search_terms);

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 8: Using synonyms or similar terms in the query should
     * not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(String index_dir, ArrayList<String> search_terms) throws Exception {
        // TODO
        // if (search_terms.isEmpty()) {
        //     return;
        // }

        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // List<String> follow_search_terms = new ArrayList<>();
        // for (String term : search_terms) {
        //     follow_search_terms.add(term);
        //     String synonym = findSynonym(term); // Find a synonym or similar term
        //     if (synonym != null) {
        //         follow_search_terms.add(synonym);
        //     }
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 9: Applying the same query terms in different letter
     * cases should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        ArrayList<String> follow_search_terms = new ArrayList<>();
        for (String term : search_terms) {
            follow_search_terms.add(term.toLowerCase());
            follow_search_terms.add(term.toUpperCase());
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 10: Applying the same query terms with different
     * language settings should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String index_dir, ArrayList<String> search_terms) throws Exception {
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // ArrayList<String> follow_search_terms = new ArrayList<>();
        // for (String term : search_terms) {
        //     follow_search_terms.add(term); // Keep the original term
        //     String translatedTerm = translateToDifferentLanguage(term); // Translate the term to a different language
        //     follow_search_terms.add(translatedTerm);
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 11: Applying a truncated version of the search terms
     * should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        ArrayList<String> follow_search_terms = new ArrayList<>();
        for (String term : search_terms) {
            follow_search_terms.add(term);
            follow_search_terms.add(term.substring(0, Math.max(1, term.length() - 2))); // Truncate the term
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 12: Applying alternative spellings or misspelled
     * versions of the search terms should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(String index_dir, ArrayList<String> search_terms) throws Exception {
        // TODO
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // ArrayList<String> follow_search_terms = new ArrayList<>();
        // for (String term : search_terms) {
        //     follow_search_terms.add(term);
        //     String misspelledTerm = generateMisspelledVersion(term); // Generate a misspelled version of the term
        //     if (misspelledTerm != null) {
        //         follow_search_terms.add(misspelledTerm);
        //     }
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 13: Adding a common stop-word to the query should not
     * affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        ArrayList<String> follow_search_terms = new ArrayList<>(search_terms);
        follow_search_terms.add("the"); // Adding a common stop-word to the query

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 14: Applying a subset of the original query terms should
     * not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(String index_dir, ArrayList<String> search_terms) throws Exception {
        if (search_terms.size() <= 1) {
            return;
        }

        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // Applying a subset of the original query terms
        ArrayList<String> follow_search_terms = new ArrayList<>(search_terms.subList(0, search_terms.size() / 2));

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 15: Applying a combination of original and modified
     * query terms should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String index_dir, ArrayList<String> search_terms) throws Exception {
        if (search_terms.size() < 2) {
            return;
        }

        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        ArrayList<String> follow_search_terms = new ArrayList<>(search_terms);  // Fix
        follow_search_terms.set(0, "modifiedTerm"); // Applying a modified version of the first query term

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 16: Reordering the query terms should not affect the
     * results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        ArrayList<String> follow_search_terms = new ArrayList<>(search_terms);
        Collections.shuffle(follow_search_terms); // Reordering the query terms

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 17: Applying a combination of original query terms with
     * synonyms should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String index_dir, ArrayList<String> search_terms) throws Exception {
        // TODO
        // if (search_terms.size() < 2) {
        //     return;
        // }

        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // List<String> follow_search_terms = new ArrayList<>(search_terms);
        // for (int i = 0; i < search_terms.size(); i += 2) {
        //     String synonym = findSynonym(search_terms.get(i)); // Find a synonym for every other term
        //     if (synonym != null) {
        //         follow_search_terms.set(i, synonym);
        //     }
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 18: Applying the same query terms with punctuation
     * variations should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String index_dir, ArrayList<String> search_terms) throws Exception {
        // TODO
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // List<String> follow_search_terms = new ArrayList<>();
        // for (String term : search_terms) {
        //     String termWithPunctuation = addPunctuation(term); // Add punctuation variations to the term
        //     follow_search_terms.add(term);
        //     follow_search_terms.add(termWithPunctuation);
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 19: Applying a partial phrase of the original query
     * should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String index_dir, ArrayList<String> search_terms) throws Exception {
        if (search_terms.size() < 2) {
            return;
        }

        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        ArrayList<String> follow_search_terms = new ArrayList<>();
        String phrase = String.join(" ", search_terms);

        for (int i = 2; i <= phrase.length(); i++) {
            String partialPhrase = phrase.substring(0, i);
            follow_search_terms.add(partialPhrase);
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 20: Applying a combination of original query terms with
     * spelling variations should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(String index_dir, ArrayList<String> search_terms) throws Exception {
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // List<String> follow_search_terms = new ArrayList<>(search_terms);
        // for (int i = 0; i < search_terms.size(); i++) {
        //     String term = search_terms.get(i);
        //     List<String> spellingVariations = findSpellingVariations(term); // Find spelling variations for each term
        //     if (!spellingVariations.isEmpty()) {
        //         follow_search_terms.addAll(spellingVariations);
        //     }
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 21: Applying the same query terms with additional prefix
     * or suffix variations should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(String index_dir, ArrayList<String> search_terms) throws Exception {
        // TODO
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // List<String> follow_search_terms = new ArrayList<>();
        // for (String term : search_terms) {
        //     String termWithPrefix = addPrefixVariation(term); // Add prefix variation to the term
        //     String termWithSuffix = addSuffixVariation(term); // Add suffix variation to the term
        //     follow_search_terms.add(term);
        //     follow_search_terms.add(termWithPrefix);
        //     follow_search_terms.add(termWithSuffix);
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 22: Applying the same query terms with synonym
     * replacements should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(String index_dir, ArrayList<String> search_terms) throws Exception {
        // TODO
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // List<String> follow_search_terms = new ArrayList<>(search_terms);
        // for (int i = 0; i < search_terms.size(); i++) {
        //     String term = search_terms.get(i);
        //     List<String> synonyms = findSynonyms(term); // Find synonyms for each term
        //     if (!synonyms.isEmpty()) {
        //         follow_search_terms.addAll(synonyms);
        //     }
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 23: Combining separate searches using AND operator
     * should return a subset of the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(String index_dir, ArrayList<String> search_terms1, ArrayList<String> search_terms2)
            throws Exception {
        // TODO
        /* Get source output for the combined search */
        ArrayList<String> combined_search = new ArrayList<>(search_terms1);
        combined_search.add("AND");
        combined_search.addAll(search_terms2);
        ArrayList<String> source_out_combined = Utils.fullTextSearch(index_dir, combined_search);

        /* Get source output for individual searches */
        ArrayList<String> source_out1 = Utils.fullTextSearch(index_dir, search_terms1);
        ArrayList<String> source_out2 = Utils.fullTextSearch(index_dir, search_terms2);

        /* Verification */
        assertTrue(source_out_combined.containsAll(source_out1));
        assertTrue(source_out_combined.containsAll(source_out2));
    }

    /**
     * Metamorphic Relation 24: Combining separate searches using OR operator should
     * return a superset of the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(String index_dir, ArrayList<String> search_terms1, ArrayList<String> search_terms2)
            throws Exception {
        // TODO
        /* Get source output for the combined search */
        ArrayList<String> combined_search = new ArrayList<>(search_terms1);
        combined_search.add("OR");
        combined_search.addAll(search_terms2);
        ArrayList<String> source_out_combined = Utils.fullTextSearch(index_dir, combined_search);

        /* Get source output for individual searches */
        ArrayList<String> source_out1 = Utils.fullTextSearch(index_dir, search_terms1);
        ArrayList<String> source_out2 = Utils.fullTextSearch(index_dir, search_terms2);

        /* Verification */
        assertTrue(source_out_combined.containsAll(source_out1) && source_out_combined.containsAll(source_out2));
    }

    /**
     * Metamorphic Relation 25: Applying a subset of the original query terms in
     * alternating order should lead to consistent results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(String index_dir, ArrayList<String> search_terms) throws Exception {
        if (search_terms.size() < 3) {
            return;
        }

        /* Get source output for the original search */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // Applying a subset of the original query terms in alternating order
        ArrayList<String> follow_search_terms = new ArrayList<>();
        for (int i = 0; i < search_terms.size(); i += 2) {
            follow_search_terms.add(search_terms.get(i));
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 26: Applying a combination of original and modified
     * query terms in alternating order should lead to consistent results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(String index_dir, ArrayList<String> search_terms) throws Exception {
        // TODO
        // if (search_terms.size() < 3) {
        //     return;
        // }

        // /* Get source output for the original search */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // // Applying a combination of original and modified query terms in alternating
        // // order
        // List<String> follow_search_terms = new ArrayList<>(search_terms);
        // for (int i = 0; i < search_terms.size(); i += 2) {
        //     if (i < search_terms.size() - 1) {
        //         String modified = modifyQueryTerm(search_terms.get(i));
        //         follow_search_terms.set(i, modified);
        //     }
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 27: Applying a series of nested AND and OR operators in
     * the query should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(String index_dir, ArrayList<String> search_terms) throws Exception {
        if (search_terms.size() < 5) {
            return;
        }

        /* Get source output for the original search */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // Applying nested AND and OR operators in the query
        ArrayList<String> follow_search_terms = new ArrayList<>(search_terms);
        follow_search_terms.add(2, "OR");
        follow_search_terms.add(4, "AND");
        follow_search_terms.add(6, "OR");
        follow_search_terms.add(8, "AND");

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 28: Applying the same search terms while changing the
     * order of Boolean operators should lead to consistent results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(String index_dir, ArrayList<String> search_terms) throws Exception {
        if (search_terms.size() < 3) {
            return;
        }

        /* Get source output for the original search */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // Changing the order of Boolean operators in the query
        ArrayList<String> follow_search_terms = new ArrayList<>(search_terms);
        for (int i = 1; i < search_terms.size() - 1; i += 2) {
            Collections.swap(follow_search_terms, i, i + 1);
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 29: Applying the same search terms with parentheses
     * rearranged should lead to consistent results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(String index_dir, ArrayList<String> search_terms) throws Exception {
        if (search_terms.size() < 5 || search_terms.size() % 2 == 0) {
            return;
        }

        /* Get source output for the original search */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // Rearranging the parentheses in the query
        ArrayList<String> follow_search_terms = new ArrayList<>(search_terms);
        for (int i = 1; i < search_terms.size() - 1; i += 2) {
            if ("(".equals(search_terms.get(i)) && ")".equals(search_terms.get(i + 1))) {
                if (i < search_terms.size() - 3) {
                    Collections.swap(follow_search_terms, i + 2, i + 3);
                }
            }
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 30: Applying the same search terms while removing
     * redundant parentheses should lead to consistent results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(String index_dir, ArrayList<String> search_terms) throws Exception {
        // TODO
        // if (search_terms.size() < 5 || search_terms.size() % 2 == 0) {
        //     return;
        // }

        // /* Get source output for the original search */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // // Removing redundant parentheses in the query
        // List<String> follow_search_terms = new ArrayList<>(search_terms);
        // Iterator<String> it = follow_search_terms.iterator();
        // while (it.hasNext()) {
        //     String term = it.next();
        //     if ("(".equals(term)) {
        //         it.remove();
        //         if (it.hasNext() && ")".equals(it.next())) {
        //             it.remove();
        //         }
        //     }
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 31: Applying a repeated subset of the query terms should
     * lead to consistent results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(String index_dir, ArrayList<String> search_terms) throws Exception {
        if (search_terms.size() < 4) {
            return;
        }

        /* Get source output for the original search */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // Repeating a subset of the query terms
        ArrayList<String> follow_search_terms = new ArrayList<>(search_terms);
        follow_search_terms.addAll(search_terms.subList(1, 3));

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 32: Applying a negation of the entire query should lead
     * to a complementary result set.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(String index_dir, ArrayList<String> search_terms) throws Exception {
        // if (search_terms.isEmpty()) {
        //     return;
        // }

        // /* Get source output for the original search */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // // Applying negation of the entire query
        // List<String> negated_search_terms = new ArrayList<>(search_terms);
        // negated_search_terms.add(0, "NOT");

        // /* Get follow-up output */
        // ArrayList<String> negated_out = Utils.fullTextSearch(index_dir, negated_search_terms);

        // /* Verification */
        // Set<String> sourceSet = new HashSet<>(source_out);
        // Set<String> negatedSet = new HashSet<>(negated_out);
        // assertEquals(sourceSet.size() + negatedSet.size(), new HashSet<>(source_out).addAll(negated_out).size());
    }

    /**
     * Metamorphic Relation 33: Applying the same search terms with additional fuzzy
     * variations should lead to consistent results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output for the original search */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // Applying additional fuzzy variations to the query terms
        ArrayList<String> fuzzy_search_terms = new ArrayList<>(search_terms);
        for (int i = 0; i < search_terms.size(); i++) {
            fuzzy_search_terms.add(search_terms.get(i) + "~");
        }

        /* Get follow-up output */
        ArrayList<String> fuzzy_out = Utils.fullTextSearch(index_dir, fuzzy_search_terms);

        /* Verification */
        assertEquals(source_out, fuzzy_out);
    }

    /**
     * Metamorphic Relation 34: Applying synonymous terms in the query should return
     * the same or a superset of the original results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(String index_dir, ArrayList<String> search_terms) throws Exception {
        // TODO
        // /* Get source output for the original search */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // // Applying synonymous terms in the query
        // List<String> synonym_search_terms = new ArrayList<>(search_terms);
        // for (int i = 0; i < search_terms.size(); i++) {
        //     List<String> synonyms = findSynonyms(search_terms.get(i)); // Find synonyms for each term
        //     if (synonyms != null && synonyms.size() > 0) {
        //         synonym_search_terms.addAll(synonyms);
        //     }
        // }

        // /* Get follow-up output */
        // ArrayList<String> synonym_out = Utils.fullTextSearch(index_dir, synonym_search_terms);

        // /* Verification */
        // assertTrue(source_out.containsAll(synonym_out));
    }

    /**
     * Metamorphic Relation 35: Appending optional terms should not affect the
     * results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output for the original search */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // Appending optional terms to the query
        ArrayList<String> optional_search_terms = new ArrayList<>(search_terms);
        for (int i = 0; i < search_terms.size(); i++) {
            optional_search_terms.add(search_terms.get(i) + "?");
        }

        /* Get follow-up output */
        ArrayList<String> optional_out = Utils.fullTextSearch(index_dir, optional_search_terms);

        /* Verification */
        assertEquals(source_out, optional_out);
    }

    /**
     * Metamorphic Relation 36: Applying different text representations of the same
     * numbers in the query should lead to consistent results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(String index_dir, ArrayList<String> search_terms) throws Exception {
        // TODO
        // // Get source output for the original search
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // // Applying different text representations of the same numbers in the query
        // List<String> number_search_terms = new ArrayList<>(search_terms);
        // for (int i = 0; i < search_terms.size(); i++) {
        //     if (isNumeric(search_terms.get(i))) {
        //         String textRepresentation = convertNumberToText(search_terms.get(i));
        //         number_search_terms.add(textRepresentation);
        //     }
        // }

        // // Get follow-up output
        // ArrayList<String> number_out = Utils.fullTextSearch(index_dir, number_search_terms);

        // // Verification
        // assertEquals(source_out, number_out);
    }

    /**
     * Metamorphic Relation 37: Applying a subset of the original query terms along
     * with negated versions should lead to consistent results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(String index_dir, ArrayList<String> search_terms) throws Exception {
        if (search_terms.size() < 3) {
            return;
        }

        /* Get source output for the original search */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // Applying a subset of the original query terms along with negated versions
        ArrayList<String> follow_search_terms = new ArrayList<>(search_terms.subList(0, 3));
        for (int i = 0; i < 3; i++) {
            follow_search_terms.add("NOT");
            follow_search_terms.add(search_terms.get(i));
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 38: Applying the same query terms with differently cased
     * Boolean operators should lead to consistent results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(String index_dir, ArrayList<String> search_terms) throws Exception {
        if (search_terms.size() < 3) {
            return;
        }

        /* Get source output for the original search */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // Applying the same query terms with differently cased Boolean operators
        ArrayList<String> follow_search_terms = new ArrayList<>(search_terms);
        for (int i = 1; i < search_terms.size(); i += 2) {
            String operator = search_terms.get(i);
            follow_search_terms.set(i, operator.toLowerCase().equals("and") ? "OR" : "AND");
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 39: Applying the same search terms with additional
     * variations such as wildcards should lead to consistent results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output for the original search */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // Applying the same search terms with additional variations such as wildcards
        ArrayList<String> variation_search_terms = new ArrayList<>(search_terms);
        for (int i = 0; i < search_terms.size(); i++) {
            variation_search_terms.add(search_terms.get(i) + "*");
        }

        /* Get follow-up output */
        ArrayList<String> variation_out = Utils.fullTextSearch(index_dir, variation_search_terms);

        /* Verification */
        assertEquals(source_out, variation_out);
    }

    /**
     * Metamorphic Relation 40: Reversing the order of search terms combined with
     * AND operator should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(String index_dir, ArrayList<String> search_terms) throws Exception {
        if (search_terms.size() < 3) {
            return;
        }

        /* Get source output for the original search */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // Reversing the order of search terms combined with AND operator
        if ("AND".equals(search_terms.get(1))) {
            ArrayList<String> follow_search_terms = new ArrayList<>(search_terms);
            Collections.reverse(follow_search_terms.subList(0, 3));

            /* Get follow-up output */
            ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

            /* Verification */
            assertEquals(source_out, follow_out);
        }
    }

    // /**
    //  * Metamorphic Relation 41: Adding a placeholder term in the query should not
    //  * affect the results.
    //  */
    // @ParameterizedTest
    // @MethodSource("testcaseProvider")
    // public void test41(String index_dir, ArrayList<String> search_terms) throws Exception {
    //     /* Get source output for the original search */
    //     ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

    //     // Adding a placeholder term in the query
    //     List<String> follow_search_terms = new ArrayList<>(search_terms);
    //     follow_search_terms.add("placeholder");

    //     /* Get follow-up output */
    //     ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

    //     /* Verification */
    //     assertEquals(source_out, follow_out);
    // }

    // /**
    //  * Metamorphic Relation 42: Excluding a term from the query should not affect
    //  * the results.
    //  */
    // @ParameterizedTest
    // @MethodSource("testcaseProvider")
    // public void test42(String index_dir, ArrayList<String> search_terms) throws Exception {
    //     if (search_terms.isEmpty()) {
    //         return;
    //     }

    //     /* Get source output for the original search */
    //     ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

    //     // Excluding a term from the query
    //     List<String> follow_search_terms = new ArrayList<>(search_terms);
    //     follow_search_terms.remove(0);

    //     /* Get follow-up output */
    //     ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

    //     /* Verification */
    //     assertEquals(source_out, follow_out);
    // }

    // /**
    //  * Metamorphic Relation 43: Combining separate searches using AND operator
    //  * should return a subset of the results.
    //  */
    // @ParameterizedTest
    // @MethodSource("testcaseProvider")
    // public void test43(String index_dir, ArrayList<String> search_terms1, ArrayList<String> search_terms2)
    //         throws Exception {
    //     /* Get source output for the combined search */
    //     ArrayList<String> combined_search = new ArrayList<>(search_terms1);
    //     combined_search.add("AND");
    //     combined_search.addAll(search_terms2);
    //     ArrayList<String> source_out_combined = Utils.fullTextSearch(index_dir, combined_search);

    //     /* Get source output for individual searches */
    //     ArrayList<String> source_out1 = Utils.fullTextSearch(index_dir, search_terms1);
    //     ArrayList<String> source_out2 = Utils.fullTextSearch(index_dir, search_terms2);

    //     /* Verification */
    //     assertTrue(source_out_combined.containsAll(source_out1) && source_out_combined.containsAll(source_out2));
    // }

    // /**
    //  * Metamorphic Relation 44: Combining separate searches using OR operator should
    //  * return a superset of the results.
    //  */
    // @ParameterizedTest
    // @MethodSource("testcaseProvider")
    // public void test44(String index_dir, ArrayList<String> search_terms1, ArrayList<String> search_terms2)
    //         throws Exception {
    //     /* Get source output for the combined search */
    //     ArrayList<String> combined_search = new ArrayList<>(search_terms1);
    //     combined_search.add("OR");
    //     combined_search.addAll(search_terms2);
    //     ArrayList<String> source_out_combined = Utils.fullTextSearch(index_dir, combined_search);

    //     /* Get source output for individual searches */
    //     ArrayList<String> source_out1 = Utils.fullTextSearch(index_dir, search_terms1);
    //     ArrayList<String> source_out2 = Utils.fullTextSearch(index_dir, search_terms2);

    //     /* Verification */
    //     assertTrue(source_out_combined.containsAll(source_out1));
    //     assertTrue(source_out_combined.containsAll(source_out2));
    // }

    // /**
    //  * Metamorphic Relation 45: Applying a combination of original query terms with
    //  * spelling variations should not affect the results.
    //  */
    // @ParameterizedTest
    // @MethodSource("testcaseProvider")
    // public void test45(String index_dir, ArrayList<String> search_terms) throws Exception {
    //     /* Get source output */
    //     ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

    //     List<String> follow_search_terms = new ArrayList<>();
    //     for (String term : search_terms) {
    //         follow_search_terms.add(term);
    //         String misspelledTerm = generateMisspelledVersion(term); // Generate a misspelled version of the term
    //         if (misspelledTerm != null) {
    //             follow_search_terms.add(misspelledTerm);
    //         }
    //     }

    //     /* Get follow-up output */
    //     ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

    //     /* Verification */
    //     assertEquals(source_out, follow_out);
    // }

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
