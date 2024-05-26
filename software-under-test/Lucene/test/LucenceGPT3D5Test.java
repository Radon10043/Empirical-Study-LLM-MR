package test;

import static org.junit.Assume.assumeTrue;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.io.File;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.stream.Stream;

import org.apache.lucene.analysis.StopAnalyzer;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

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
     * Metamorphic Relation 1: Adding additional terms to the query should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Construct follow-up input */
        ArrayList<String> follow_search_terms = new ArrayList<String>();
        follow_search_terms.addAll(search_terms);
        follow_search_terms.add("additionalTerm");

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 2: Reordering the terms in the query should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Construct follow-up input */
        ArrayList<String> follow_search_terms = new ArrayList<String>();
        follow_search_terms.addAll(search_terms);
        Collections.shuffle(follow_search_terms);

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 3: Repeating the terms in the query should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(String index_dir, ArrayList<String> search_terms) throws Exception {  // Fixed
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Construct follow-up input */
        ArrayList<String> follow_search_terms = new ArrayList<String>();
        follow_search_terms.addAll(search_terms);
        follow_search_terms.addAll(search_terms);

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        Collections.sort(source_out);
        Collections.sort(follow_out);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 4: Using the same query with different cases of characters
     * (e.g., uppercase and lowercase) should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Construct follow-up input with terms in different cases */
        ArrayList<String> follow_search_terms = new ArrayList<String>();
        for (String term : search_terms) {
            follow_search_terms.add(term.toUpperCase());
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 5: Removing a term from the query and searching with the
     * modified query should not affect the results if the removed term does not exist.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(String index_dir, ArrayList<String> search_terms) throws Exception {
        assumeTrue(search_terms.size() > 1);

        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Construct follow-up input by removing a term */
        HashSet<String> keywords = new HashSet<String>();
        keywords.add("AND");
        keywords.add("OR");
        keywords.add("NOT");
        ArrayList<String> follow_search_terms = new ArrayList<String>();
        follow_search_terms.addAll(search_terms);
        for (int i = 0; i < search_terms.size(); i++) {
            if (i == 1 && keywords.contains(search_terms.get(i))) {
                continue;
            }
            ArrayList<String> temp = new ArrayList<String>();
            temp.add(search_terms.get(i));
            if (Utils.fullTextSearch(index_dir, temp).isEmpty()) {
                follow_search_terms.remove(i);
                break;
            }
        }
        if (!follow_search_terms.isEmpty() && keywords.contains(follow_search_terms.get(0))) {
            follow_search_terms.remove(0);
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 6: Adding special characters or punctuation to the query
     * should not affect the results if those characters are not part of the indexed text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Construct follow-up input by adding special characters or punctuation */
        ArrayList<String> follow_search_terms = new ArrayList<String>();
        follow_search_terms.addAll(search_terms);
        follow_search_terms.add("!@#$%^&*()");

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 7: Prepending or appending common words or phrases to the query
     * should not affect the results if those words or phrases are not rare or significant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Construct follow-up input by appending common words */
        ArrayList<String> follow_search_termsAppend = new ArrayList<String>();
        follow_search_termsAppend.addAll(search_terms);
        follow_search_termsAppend.add("common words example");

        /* Get follow-up output using appended query */
        ArrayList<String> follow_outAppend = Utils.fullTextSearch(index_dir, follow_search_termsAppend);

        /* Construct follow-up input by prepending common words */
        ArrayList<String> follow_search_termsPrepend = new ArrayList<String>();
        follow_search_termsPrepend.add("common words example");
        follow_search_termsPrepend.addAll(search_terms);

        /* Get follow-up output using prepended query */
        ArrayList<String> follow_outPrepend = Utils.fullTextSearch(index_dir, follow_search_termsPrepend);

        /* Verification */
        assertEquals(source_out, follow_outAppend);
        assertEquals(follow_outAppend, follow_outPrepend);
    }

    /**
     * Metamorphic Relation 8: Querying with synonymous terms should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(String index_dir, ArrayList<String> search_terms) throws Exception {
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // /* Construct follow-up input with synonymous terms */
        // ArrayList<String> follow_search_terms = new ArrayList<String>();
        // for (String term : search_terms) {
        //     List<String> synonyms = getSynonyms(term); // Custom function to get synonyms of a term
        //     if (!synonyms.isEmpty()) {
        //         follow_search_terms.add(synonyms.get(0)); // Using only the first synonym
        //     } else {
        //         follow_search_terms.add(term); // Use the original term if no synonyms found
        //     }
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 9: Using a substring of a search term should return the same results as the original term.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Construct follow-up input with a substring of search terms */
        ArrayList<String> follow_search_terms = new ArrayList<String>();
        for (String term : search_terms) {
            if (term.length() > 3) {
                follow_search_terms.add(term.substring(0, 3));
            } else {
                follow_search_terms.add(term);
            }
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Custom function to check if the term is a stop word
     *
     * @param term
     * @return
     */
    boolean isStopword(String term) {
        HashSet<String> stop_words = new HashSet<String>(Arrays.asList(StopAnalyzer.ENGLISH_STOP_WORDS));
        return stop_words.contains(term);
    }

    /**
     * Custom function to check if the term is a keyword
     * @param term
     * @return
     */
    boolean isKeyword(String term) {
        HashSet<String> keywords = new HashSet<String>();
        keywords.add("AND");
        keywords.add("OR");
        keywords.add("NOT");
        return keywords.contains(term);
    }

    /**
     * Metamorphic Relation 10: Removing stopwords from the query should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String index_dir, ArrayList<String> search_terms) throws Exception { // Fixed
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Construct follow-up input by removing stopwords */
        ArrayList<String> follow_search_terms = new ArrayList<String>();
        for (String term : search_terms) {
            if (!isStopword(term.toLowerCase())) {
                follow_search_terms.add(term);
            }
        }

        assumeTrue(follow_search_terms.size() > 0);

        if (isKeyword(follow_search_terms.get(0))) {
            follow_search_terms.remove(0);
        }

        assumeTrue(follow_search_terms.size() > 0);

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 11: Adding noise to the query where noise is defined as uncommon or irrelevant words
     * should not affect the results if the added noise itself does not exist in the indexed text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Construct follow-up input by adding noise to the query */
        ArrayList<String> follow_search_terms = new ArrayList<String>();
        follow_search_terms.addAll(search_terms);
        follow_search_terms.add("uncommonword");
        follow_search_terms.add("irrelevantphrase");

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 12: Replacing a term in the query with its antonym should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(String index_dir, ArrayList<String> search_terms) throws Exception {
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // /* Construct follow-up input by replacing a term with its antonym */
        // ArrayList<String> follow_search_terms = new ArrayList<String>();
        // for (String term : search_terms) {
        //     String antonym = getAntonym(term); // Custom function to get the antonym of a term
        //     follow_search_terms.add(antonym != null ? antonym : term);
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 13: Using a subset of fields in the query should not affect the results if the omitted fields are not relevant to the search.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(String index_dir, ArrayList<String> search_terms) throws Exception {
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // /* Construct follow-up input using a subset of fields */
        // ArrayList<String> follow_search_terms = new ArrayList<String>();
        // for (String term : search_terms) {
        //     if (isRelevantField(term)) { // Custom function to check if the field is relevant
        //         follow_search_terms.add(term);
        //     }
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 14: Querying with partially incomplete or fuzzy terms should still return relevant results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Construct follow-up input by using incomplete or fuzzy terms */
        ArrayList<String> follow_search_terms = new ArrayList<String>();
        for (String term : search_terms) {
            if (term.length() > 3) {
                follow_search_terms.add(term.substring(0, 3) + "*"); // Using fuzzy matching with wildcards
            } else {
                follow_search_terms.add(term);
            }
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 15: Querying with a combination of stop words and non-stop words should return results based on the non-stop words.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String index_dir, ArrayList<String> search_terms) throws Exception { // Fixed
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Construct follow-up input by combining stop words and non-stop words */
        ArrayList<String> follow_search_terms = new ArrayList<String>();
        for (String term : search_terms) {
            if (!isStopword(term)) { // Custom function to check if the term is a stop word
                follow_search_terms.add(term);
            }
        }

        assumeTrue(follow_search_terms.size() > 0);

        if (follow_search_terms.size() == 2 && isKeyword(follow_search_terms.get(1))) {
            follow_search_terms.remove(1);
        }

        if (isKeyword(follow_search_terms.get(0))) {
            follow_search_terms.remove(0);
        }

        assumeTrue(follow_search_terms.size() > 0);

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 16: Using synonyms and their hypernyms in the query should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(String index_dir, ArrayList<String> search_terms) throws Exception {
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // /* Construct follow-up input using synonyms and hypernyms */
        // ArrayList<String> follow_search_terms = new ArrayList<String>();
        // for (String term : search_terms) {
        //     List<String> synonyms = getSynonyms(term); // Custom function to get synonyms of a term
        //     synonyms.addAll(getHypernyms(term)); // Custom function to get hypernyms of a term
        //     follow_search_terms.addAll(synonyms);
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 17: Searching with a negation of the original query should return non-matching results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Construct follow-up input using negation of the original query */
        ArrayList<String> follow_search_terms = new ArrayList<String>();
        for (String term : search_terms) {
            follow_search_terms.add("-" + term); // Adding negation symbol to each term
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertNotEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 18: Searching a subset of documents retrieved by the original query should return a subset of the original results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String index_dir, ArrayList<String> search_terms) throws Exception {
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // // Assuming that we have a function getSubsetOfDocuments() that retrieves a subset of the documents
        // List<Document> subsetDocuments = getSubsetOfDocuments(index_dir, search_terms);

        // /* Construct follow-up input using subset of documents */
        // ArrayList<String> follow_search_terms = new ArrayList<String>();
        // for (Document doc : subsetDocuments) {
        //     follow_search_terms.add(doc.getContent());
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertTrue(source_out.containsAll(follow_out));
    }

    /**
     * Metamorphic Relation 19: Searching using a query with synonyms and antonyms should return results consistent with the original query.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String index_dir, ArrayList<String> search_terms) throws Exception {
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // // Assuming that we have a function getAntonyms() that retrieves antonyms of the terms
        // // and getSynonyms() that retrieves synonyms of the terms
        // ArrayList<String> follow_search_terms = new ArrayList<String>();
        // for (String term : search_terms) {
        //     List<String> synonyms = getSynonyms(term);
        //     synonyms.addAll(getAntonyms(term));
        //     follow_search_terms.addAll(synonyms);
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 20: Searching using a query with similar words with spelling errors should return the same results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(String index_dir, ArrayList<String> search_terms) throws Exception {
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // // Assuming that we have a function getSimilarWordsWithSpellingErrors() to get similar words
        // ArrayList<String> follow_search_terms = new ArrayList<String>();
        // for (String term : search_terms) {
        //     List<String> similarWords = getSimilarWordsWithSpellingErrors(term);
        //     follow_search_terms.addAll(similarWords);
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 21: Searching for a subset of terms within the original query should return a subset of the original results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(String index_dir, ArrayList<String> search_terms) throws Exception {
        assumeTrue(search_terms.size() > 1);

        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Construct follow-up input with a subset of terms */
        ArrayList<String> follow_search_terms = new ArrayList<String>();
        for (int i = 0; i < search_terms.size()/2; i++) {
            follow_search_terms.add(search_terms.get(i));
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertTrue(source_out.containsAll(follow_out));
    }

    /**
     * Metamorphic Relation 22: Searching with a query and its variant of a different language should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(String index_dir, ArrayList<String> search_terms) throws Exception {
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // // Assuming we have a function translateToFrench() to get the French translation of the terms
        // ArrayList<String> follow_search_terms = translateToFrench(search_terms);

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 23: Searching with wildcards added to the query should not affect the results if the wildcard symbol is not part of the indexed text.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Construct follow-up input by adding wildcard symbol to the query */
        ArrayList<String> follow_search_terms = new ArrayList<String>();
        for (String term : search_terms) {
            if (isKeyword(term)) continue;
            follow_search_terms.add(term + "*"); // Adding wildcard symbol to each term
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 24: Searching with a query containing word reordering should not affect the results if the words being reordered are not part of a phrase or conjunction.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Construct follow-up input with word reordering in the query */
        Collections.shuffle(search_terms);

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 25: Searching with a query containing duplicate words should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(String index_dir, ArrayList<String> search_terms) throws Exception { // Fixed
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Construct follow-up input with duplicate words in the query */
        ArrayList<String> follow_search_terms = new ArrayList<>(search_terms);
        follow_search_terms.addAll(search_terms); // Adding duplicate words

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        Collections.sort(source_out);
        Collections.sort(follow_out);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 26: Searching with a query term in singular and plural forms should not affect the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(String index_dir, ArrayList<String> search_terms) throws Exception {
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // /* Construct follow-up input with singular and plural forms of the query terms */
        // ArrayList<String> follow_search_terms = new ArrayList<>();
        // for (String term : search_terms) {
        //     follow_search_terms.add(term); // Adding original term
        //     follow_search_terms.add(getPluralForm(term)); // Assuming we have a function to get plural form of a term
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 27: Searching with a subset of terms from the original query should return a subset of the original results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(String index_dir, ArrayList<String> search_terms) throws Exception {
        assumeTrue(search_terms.size() > 1);

        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Randomly select a subset of terms */
        ArrayList<String> follow_search_terms = new ArrayList<>();
        int subsetSize = search_terms.size() / 2;
        SecureRandom rand = new SecureRandom();
        for (int i = 0; i < subsetSize; i++) {
            int index = rand.nextInt(search_terms.size());
            follow_search_terms.add(search_terms.get(index));
        }

        if (isKeyword(follow_search_terms.get(0))) {
            follow_search_terms.remove(0);
        }
        assumeTrue(follow_search_terms.size() > 0);

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertTrue(source_out.containsAll(follow_out));
    }

    /**
     * Metamorphic Relation 28: Searching with a query term and its acronym should return results consistent with the original query.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(String index_dir, ArrayList<String> search_terms) throws Exception {
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // /* Construct follow-up input with acronym forms of the query terms */
        // ArrayList<String> follow_search_terms = new ArrayList<>();
        // for (String term : search_terms) {
        //     follow_search_terms.add(term); // Adding original term
        //     follow_search_terms.add(getAcronym(term)); // Assuming we have a function to get acronym form of a term
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 29: Searching with a query containing word synonyms and their abbreviations should return results consistent with the original query.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(String index_dir, ArrayList<String> search_terms) throws Exception {
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // /* Construct follow-up input with synonyms and their abbreviations */
        // ArrayList<String> follow_search_terms = new ArrayList<>();
        // for (String term : search_terms) {
        //     follow_search_terms.add(term); // Adding original term
        //     List<String> synonyms = getSynonyms(term); // Assuming we have a function to get synonyms of a term
        //     follow_search_terms.addAll(synonyms);
        //     List<String> abbreviations = getAbbreviations(term); // Assuming we have a function to get abbreviations of a term
        //     follow_search_terms.addAll(abbreviations);
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 30: Searching with a query containing domain-specific terms and their general synonyms should return results consistent with the original query.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(String index_dir, ArrayList<String> search_terms) throws Exception {
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // /* Construct follow-up input with domain-specific terms and their general synonyms */
        // ArrayList<String> follow_search_terms = new ArrayList<>();
        // for (String term : search_terms) {
        //     follow_search_terms.add(term); // Adding original term
        //     List<String> domainSpecificSynonyms = getDomainSpecificSynonyms(term); // Assuming we have a function to get domain-specific synonyms of a term
        //     follow_search_terms.addAll(domainSpecificSynonyms);
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 31: Searching with a query containing common misspellings should return results consistent with the original query.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(String index_dir, ArrayList<String> search_terms) throws Exception {
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // /* Construct follow-up input with common misspellings of the query terms */
        // ArrayList<String> follow_search_terms = new ArrayList<>();
        // for (String term : search_terms) {
        //     follow_search_terms.add(term); // Adding the original term
        //     List<String> misspellings = getCommonMisspellings(term); // Custom function to get common misspellings of a term
        //     follow_search_terms.addAll(misspellings);
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 32: Searching with a query containing common synonyms in different languages should return results consistent with the original query.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(String index_dir, ArrayList<String> search_terms) throws Exception {
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // /* Construct follow-up input with synonyms in a different language */
        // ArrayList<String> follow_search_terms = new ArrayList<>();
        // for (String term : search_terms) {
        //     follow_search_terms.add(term); // Adding original term
        //     List<String> foreignSynonyms = getForeignSynonyms(term); // Assuming we have a function to get synonyms in a different language
        //     follow_search_terms.addAll(foreignSynonyms);
        // }

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 33: Searching with a query containing multiple phrases in different orders should return consistent results with the original query.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Construct follow-up input with phrases in different order */
        for (int i = 0; i < search_terms.size() - 1; i++) {
            ArrayList<String> follow_search_terms = new ArrayList<>(search_terms);
            Collections.swap(follow_search_terms, i, i+1); // Swap the order of adjacent terms
            /* Get follow-up output */
            ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);
            /* Verification */
            assertEquals(source_out, follow_out);
        }
    }

    /**
     * Metamorphic Relation 34: Searching with a specific subset of content fields should return consistent results with the original query.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Randomly select a subset of content fields */
        ArrayList<String> follow_search_terms = new ArrayList<>(search_terms);

        SecureRandom rand = new SecureRandom();
        boolean useContentField1 = rand.nextBoolean();
        boolean useContentField2 = rand.nextBoolean();

        if (!useContentField1) {
            follow_search_terms.remove("contentField1");
        }
        if (!useContentField2) {
            follow_search_terms.remove("contentField2");
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 35: Searching with a query using different logical combinations of terms joined by AND, OR, and NOT should return consistent results with the original query.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        /* Construct different logical combinations of terms */
        ArrayList<String> follow_search_terms = new ArrayList<>();
        follow_search_terms.addAll(search_terms); // Original query
        follow_search_terms.add("AND");
        follow_search_terms.addAll(search_terms); // Logical combination with AND
        follow_search_terms.add("OR");
        follow_search_terms.addAll(search_terms); // Logical combination with OR
        follow_search_terms.add("NOT");
        follow_search_terms.addAll(search_terms); // Logical combination with NOT

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 36: Searching the same query with different subsetting strategies should return consistent results with the original query.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(String index_dir, ArrayList<String> search_terms) throws Exception {
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // // Assuming we have a function for multiple subsetting
        // List<List<String>> subsets = performDifferentSubsetting(search_terms);

        // for (List<String> subset : subsets) {
        //     /* Get follow-up output */
        //     ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, subset);
        //     /* Verification */
        //     assertEquals(source_out, follow_out);
        // }
    }

    /**
     * Metamorphic Relation 37: Searching with a query should return the same results when the order of the documents in the index is shuffled.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(String index_dir, ArrayList<String> search_terms) throws Exception {
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // // Shuffle the order of documents in the index
        // shuffleIndexDocuments(index_dir);

        // /* Construct follow-up input */
        // ArrayList<String> follow_search_terms = new ArrayList<>(search_terms);

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_search_terms);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 38: Searching with a query should return consistent results when the index is divided into segments and the search is performed on these segments individually, combining the results afterward.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(String index_dir, ArrayList<String> search_terms) throws Exception {
        // // Divide the index into segments
        // divideIndexIntoSegments(index_dir);

        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // // Perform search on individual segments and combine the results afterward
        // ArrayList<String> combinedResults = new ArrayList<>();
        // for (int i = 0; i < numSegments; i++) {
        //     String segmentPath = getSegmentPath(index_dir, i); // Get the path of the segment
        //     ArrayList<String> segmentResults = Utils.fullTextSearch(segmentPath, search_terms);
        //     combinedResults.addAll(segmentResults);
        // }

        // /* Verification */
        // assertEquals(source_out, combinedResults);
    }

    /**
     * Metamorphic Relation 39: Searching with a query should return consistent results when concurrent searches are performed in parallel and then the results are combined.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(String index_dir, ArrayList<String> search_terms) throws Exception {
        search_terms.add("fuzz");

        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // Perform concurrent searches in parallel
        int numThreads = 3;
        ExecutorService executor = Executors.newFixedThreadPool(numThreads);
        List<Future<ArrayList<String>>> futures = new ArrayList<>();
        for (int i = 0; i < numThreads; i++) {
            Callable<ArrayList<String>> searchTask = () -> Utils.fullTextSearch(index_dir, search_terms);
            Future<ArrayList<String>> future = executor.submit(searchTask);
            futures.add(future);
        }

        // Combine the results from concurrent searches
        ArrayList<String> combinedResults = new ArrayList<>();
        for (Future<ArrayList<String>> future : futures) {
            combinedResults.addAll(future.get());
        }

        /* Verification */
        assertEquals(source_out, combinedResults);
        executor.shutdown();
    }

    /**
     * Metamorphic Relation 40: Searching with a query should return consistent results when the index is replicated and the search is performed on each replica independently.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(String index_dir, ArrayList<String> search_terms) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, search_terms);

        // Replicate the index
        String replica1 = index_dir;
        String replica2 = index_dir;

        // Perform search on each replica independently
        ArrayList<String> resultReplica1 = Utils.fullTextSearch(replica1, search_terms);
        ArrayList<String> resultReplica2 = Utils.fullTextSearch(replica2, search_terms);

        /* Verification */
        assertEquals(source_out, resultReplica1);
        assertEquals(source_out, resultReplica2);
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
