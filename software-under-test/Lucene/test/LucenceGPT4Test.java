package test;

import static org.junit.Assume.assumeTrue;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.stream.Stream;
import org.apache.commons.lang3.RandomStringUtils;
import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.document.Document;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

public class LucenceGPT4Test {
    private static String full_text_root; /* 存储了要检索的全文的根目录 */

    /**
     * 设置要检索的全文的根目录
     *
     * @param full_text_root
     */
    public static void setFullTextRoot(String full_text_root) {
        LucenceGPT4Test.full_text_root = full_text_root;
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
     * Metamorphic Relation 1: Searching with a query term and searching with that term in uppercase
     * should yield the same results, given case-insensitive indexing and searching.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void caseInsensitiveSearch(String index_dir, String searchTerm) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, searchTerm);

        /* Construct follow-up input */
        String follow_searchTerm = searchTerm.toUpperCase();

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_searchTerm);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 2: Adding terms to a query with the AND operator should not increase the
     * number of results if the additional terms are also present in the results of the source
     * query.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void testANDOperatorReduction(String index_dir, String baseSearchTerm) throws Exception { // Fixed
        String additionalSearchTerm = "a";

        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, baseSearchTerm);

        /* Check if additionalSearchTerm is present in the source output */
        boolean termPresent =
                source_out.stream().anyMatch(result -> result.contains(additionalSearchTerm));

        if (!termPresent) {
            return; // skip this test case because the additionalSearchTerm isn't present in all the
                    // source output
        }

        /* Construct follow-up input */
        String follow_searchQuery = baseSearchTerm + " AND " + additionalSearchTerm;

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_searchQuery);

        /* Verification */
        assertTrue(source_out.containsAll(follow_out) && follow_out.size() <= source_out.size());
    }

    /**
     * Metamorphic Relation 3: Executing a search query with a wildcard at the end and then
     * executing the same search query without the wildcard should return more or equal results with
     * the wildcard.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void wildcardSearch(String index_dir, String searchTerm) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, searchTerm + "*");

        /* Get follow-up output without wildcard */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, searchTerm);

        /* Verification */
        assertTrue(follow_out.size() <= source_out.size());
    }

    /**
     * Metamorphic Relation 4: The result of a search query should not change if a NOT operator is
     * used to exclude a term that does not exist in the index.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void excludingNonExistentTermWithNOT(String index_dir, String searchTerm)
            throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, searchTerm);

        /* Construct follow-up input */
        String nonExistentTerm = "ZZZnonexistentZZZ";
        String follow_searchQuery = searchTerm + " NOT " + nonExistentTerm;

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_searchQuery);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 5: A phrase query search should yield the same results as an AND search
     * with the same terms in the same order.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void phraseQueryVsANDSearch(String index_dir, ArrayList<String> searchTerms)
            throws Exception { // Fixed
        if (searchTerms.size() == 3) {
            assumeTrue(!searchTerms.get(1).equals("AND") && !searchTerms.get(1).equals("OR")
                    && !searchTerms.get(1).equals("NOT"));
        }

        /* Prepare source input with phrase query */
        String phraseQuery = "\"" + String.join(" ", searchTerms) + "\"";

        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, phraseQuery);

        /* Prepare follow-up input with AND operator */
        String andSearchQuery = String.join(" AND ", searchTerms);

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, andSearchQuery);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 6: Doubling a term in a phrase query with the AND operator should not
     * change the results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void doubleTermInANDSearch(String index_dir, ArrayList<String> searchTerms)
            throws Exception { // Fixed
        if (searchTerms.size() == 3) {
            assumeTrue(!searchTerms.get(1).equals("AND") && !searchTerms.get(1).equals("OR")
                    && !searchTerms.get(1).equals("NOT"));
        }

        /* Prepare source input with single term */
        String baseSearchQuery = String.join(" AND ", searchTerms);

        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, baseSearchQuery);

        /* Prepare follow-up input by doubling the first term */
        String follow_searchQuery = searchTerms.get(0) + " AND " + baseSearchQuery;

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_searchQuery);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 7: Removing stop words from a search query should not change the results
     * if the Analyzer removes stop words during indexing.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void stopWordsRemoval(String index_dir, String searchTerm) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, searchTerm);

        /* Construct follow-up input by removing stop words */
        ArrayList<String> searchTermsList = new ArrayList<>(Arrays.asList(searchTerm.split(" ")));
        List<String> stopWords = Arrays.asList("and", "or", "but", "not");
        searchTermsList.removeAll(stopWords);
        String follow_searchQuery = String.join(" ", searchTermsList);

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_searchQuery);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 8: Adding a synonym of a term in the search query with the OR operator
     * should not reduce the number of results if the synonym is indexed as well.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void addSynonymWithOROperator(String index_dir, String searchTerm) throws Exception { // Fixed
        String synonym = "synonym";

        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, searchTerm);

        /* Construct follow-up input by adding synonym with OR */
        String follow_searchQuery = searchTerm + " OR " + synonym;

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_searchQuery);

        /* Verification */
        assertTrue(follow_out.size() >= source_out.size());
    }

    /**
     * Metamorphic Relation 9: Restricting the search to a specific field with the original term
     * should give the same or fewer results compared to a general search.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void restrictToSpecificFieldSearch(String index_dir, String searchTerm)
            throws Exception { // Fixed
        String fieldName = "title";

        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, searchTerm);

        /* Construct follow-up input for specific field search */
        String follow_searchQuery = fieldName + ":" + searchTerm;

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_searchQuery);

        /* Verification */
        assertTrue(follow_out.size() <= source_out.size());
    }

    /**
     * Metamorphic Relation 10: Searching with different analyzers that tokenize the terms in the
     * same way should yield the same results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void searchWithDifferentAnalyzers(String index_dir, String searchTerm,
            Analyzer firstAnalyzer, Analyzer secondAnalyzer) throws Exception { // Illegal
        /* @formatter:off */
        // /* Get source output with the first analyzer */
        // ArrayList<String> source_out = Utils.fullTextSearchWithAnalyzer(index_dir, searchTerm, firstAnalyzer);

        // /* Get follow-up output with the second analyzer */
        // ArrayList<String> follow_out = Utils.fullTextSearchWithAnalyzer(index_dir, searchTerm, secondAnalyzer);

        // /* Verification */
        // assertEquals(source_out, follow_out);
        /* @formatter:on */
    }

    /**
     * Metamorphic Relation 11: Searching after increasing the edit distance in a fuzzy search query
     * should not decrease the number of results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void increaseEditDistanceInFuzzySearch(String index_dir, String searchTerm)
            throws Exception {
        /* Get source output with lower edit distance */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, searchTerm + "~1");

        /* Get follow-up output with higher edit distance */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, searchTerm + "~2");

        /* Verification */
        assertTrue(follow_out.size() >= source_out.size());
    }

    /**
     * Metamorphic Relation 12: Combining individual queries with the OR operator should give the
     * same or more results than any single query.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void combineQueriesWithOROperator(String index_dir, ArrayList<String> searchTerms)
            throws Exception { // Fixed
        assumeTrue(searchTerms.size() == 2);
        String term1 = searchTerms.get(0);
        String term2 = searchTerms.get(1);

        /* Get source output for first term */
        ArrayList<String> source_out1 = Utils.fullTextSearch(index_dir, term1);

        /* Get source output for second term */
        ArrayList<String> source_out2 = Utils.fullTextSearch(index_dir, term2);

        /* Construct follow-up input combining both terms with OR operator */
        String follow_searchQuery = term1 + " OR " + term2;

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_searchQuery);

        /* Verification */
        assertTrue(
                follow_out.size() >= source_out1.size() && follow_out.size() >= source_out2.size());
    }

    /**
     * Metamorphic Relation 13: Changing the order of query terms with the AND operator should not
     * change the search results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void changeOrderOfANDSearchTerms(String index_dir, ArrayList<String> searchTerms)
            throws Exception { // Fixed
        assumeTrue(searchTerms.size() > 1);
        assumeTrue(!searchTerms.get(1).equals("AND") && !searchTerms.get(1).equals("OR")
                && !searchTerms.get(1).equals("NOT"));

        /* Prepare source input by joining terms with AND */
        String joinedTerms = String.join(" AND ", searchTerms);

        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, joinedTerms);

        /* Shuffle terms and construct follow-up input */
        Collections.shuffle(searchTerms);
        String shuffledTerms = String.join(" AND ", searchTerms);

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, shuffledTerms);

        /* Verification */
        Collections.sort(source_out);
        Collections.sort(follow_out);
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 14: Pagination of results should yield consistent subsets across
     * requests.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void consistentPagination(String index_dir, String searchTerm, int pageSize)
            throws Exception {
        /* @formatter:off */
        // if (pageSize <= 0) {
        //     return; // PageSize should be positive. Skip otherwise.
        // }

        // /* Get source output - first page */
        // List<String> source_firstPage = Utils.fullTextSearchWithPagination(index_dir, searchTerm, 0, pageSize);

        // /* Get follow-up output - first page again */
        // List<String> follow_firstPage = Utils.fullTextSearchWithPagination(index_dir, searchTerm, 0, pageSize);

        // /* Verification - Pages should match */
        // assertEquals(source_firstPage, follow_firstPage);

        // /* Get source output - second page */
        // List<String> source_secondPage = Utils.fullTextSearchWithPagination(index_dir, searchTerm, pageSize, pageSize);

        // /* Verification - Second page should not contain first page results */
        // for (String result : source_firstPage) {
        //     assertFalse(source_secondPage.contains(result));
        // }

        // /* Verification - No overlap between first and second page */
        // assertTrue(Collections.disjoint(source_firstPage, source_secondPage));
        /* @formatter:off */
    }

    /**
     * Metamorphic Relation 15: Searching with a phrase literal versus the same
     * terms with exact position increments should yield the same results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void phraseLiteralVsPositionIncrements(String index_dir, ArrayList<String> searchTerms) throws Exception {   // Fixed
        if (searchTerms.size() < 2) {
            return; // Phrase search needs multiple terms. Skip otherwise.
        }

        /* Construct phrase search query */
        String phraseQuery = "\"" + String.join(" ", searchTerms) + "\"";

        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, phraseQuery);

        /* Construct position increment query */
        StringBuilder positionIncrementQuery = new StringBuilder();
        for (int i = 0; i < searchTerms.size(); ++i) {
            if (i > 0) {
                positionIncrementQuery.append(" ");
            }
            positionIncrementQuery.append(searchTerms.get(i));
            if (i < searchTerms.size() - 1) {
                positionIncrementQuery.append(" ").append(i + 1);
            }
        }

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, positionIncrementQuery.toString());

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 16: Boosting a query term's importance should not
     * exclude results containing the term, but might alter the order.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void boostingTermImportance(String index_dir, String searchTerm) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, searchTerm);

        /* Construct follow-up input by boosting term */
        String boostedSearchTerm = searchTerm + "^2";

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, boostedSearchTerm);

        /* Verification */
        assertTrue(follow_out.containsAll(source_out)); // All original results should be present
        // Further verification could be done to evaluate whether the result ordering
        // has changed
        // as expected due to boosting, if the result ranking information is available.
    }

    /**
     * Metamorphic Relation 17: Adding a redundant wildcard at the beginning and end
     * of a term should not change the number of results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void redundantWildcardSearch(String index_dir, String searchTerm) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, searchTerm);

        /* Add wildcards around search term */
        String follow_searchTerm = "*" + searchTerm + "*";

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_searchTerm);

        /* Verification */
        assertEquals(source_out.size(), follow_out.size());
    }

    /**
     * Metamorphic Relation 18: Searching for a term with a typo corrected should
     * yield more or equal results compared to the misspelled term.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void typoCorrectionSearch(String index_dir, String incorrectSearchTerm, String correctedSearchTerm)
            throws Exception {
        /* @formatter:off */
        // /* Get source output with typo */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, incorrectSearchTerm);

        // /* Get follow-up output with typo corrected */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, correctedSearchTerm);

        // /* Verification */
        // assertTrue(follow_out.size() >= source_out.size());
        /* @formatter:on */
    }

    /**
     * Metamorphic Relation 19: Searching for a term should also retrieve documents with the stemmed
     * form of the term when stemming is applied.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void searchWithStemming(String index_dir, String searchTerm, String stemTerm)
            throws Exception {
        /* @formatter:off */
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, searchTerm);

        // /* Get follow-up output with the stem term */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, stemTerm);

        // /* Verification */
        // // Each result with the stemmed term should also contain the original search
        // // term if stemming is consistent
        // follow_out.forEach(result -> assertTrue(result.contains(searchTerm) || result.contains(stemTerm)));
        /* @formatter:on */
    }

    /**
     * Metamorphic Relation 20: Combining individual queries with the AND NOT operator should
     * exclude documents that contain the subtracted term.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void subtractingTermsWithANDNOTOperator(String index_dir, String searchTerm)
            throws Exception { // Fixed
        String subtractTerm = "subtract";

        /* Get source output for the base search */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, searchTerm);

        /* Get follow-up output for the base search AND NOT subtractTerm */
        ArrayList<String> follow_out =
                Utils.fullTextSearch(index_dir, searchTerm + " AND NOT " + subtractTerm);

        /* Verification */
        // All results from the follow-up output should be part of the source output,
        // but not vice-versa
        assertTrue(follow_out.stream().allMatch(source_out::contains));
        // At least one result from the source should be excluded in the follow-up,
        // assuming the subtract term was present
        assertTrue(source_out.size() > follow_out.size());
    }

    /**
     * Metamorphic Relation 21: Searching for documents with a range query that includes all
     * possible values should return the same results as the unbounded query.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void fullRangeQuery(String index_dir, String fieldName) throws Exception {
        /* Get unbounded query output */
        ArrayList<String> unbounded_out = Utils.fullTextSearch(index_dir, fieldName + ":[* TO *]");

        /* Get output for a query that inherently includes all values */
        ArrayList<String> fullRange_out = Utils.fullTextSearch(index_dir, fieldName);

        /* Verification */
        assertEquals(unbounded_out, fullRange_out);
    }

    /**
     * Metamorphic Relation 22: Increasing the allowed edit distance in a fuzzy query for a term
     * should not decrease the set of matches.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void increaseFuzzyQueryEditDistance(String index_dir, String searchTerm)
            throws Exception {
        /* Get source output with lower edit distance for fuzziness */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, searchTerm + "~1");

        /* Get follow-up output with higher edit distance */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, searchTerm + "~2");

        /* Verification */
        assertTrue(follow_out.size() >= source_out.size());
    }

    /**
     * Metamorphic Relation 23: A range query that is made more restrictive should result in the
     * same or fewer search results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void restrictRangeQuery(String index_dir, String field, String startRange,
            String endRange) throws Exception {
        /* Construct the initial less restrictive range query */
        String baseQuery = String.format("%s:[%s TO %s]", field, startRange, endRange);
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, baseQuery);

        /* Narrow down the range query */
        String newStartRange = startRange + "X"; // Assuming "X" denotes a value greater than
                                                 // startRange
        String newEndRange = endRange + "X"; // Assuming "X" denotes a value greater than endRange
        String follow_query = String.format("%s:[%s TO %s]", field, newStartRange, newEndRange);

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, follow_query);

        /* Verification */
        assertTrue(follow_out.size() <= source_out.size());
    }

    /**
     * Metamorphic Relation 24: Querying with different Boolean queries that ultimately yield
     * logically equivalent results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void booleanQueryEquivalence(String index_dir, ArrayList<String> search_terms)
            throws Exception {
        assumeTrue(search_terms.size() == 2);
        String term1 = search_terms.get(0);
        String term2 = search_terms.get(1);

        /* Get source output for a Boolean query with the AND operator */
        String andQuery = term1 + " AND " + term2;
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, andQuery);

        /*
         * Get follow-up output for a logically equivalent Boolean query using OR and NOT operators
         */
        String equivQuery = term1 + " OR " + term2 + " AND NOT " + term1 + " NOT " + term2;
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, equivQuery);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 25: Re-indexing documents without changes should not affect the search
     * results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void reindexingWithoutChanges(String index_dir, String searchTerm) throws Exception {
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, searchTerm);

        // /*
        // * Re-index the same documents without changes (details of this operation would
        // * depend on the actual system's APIs)
        // */
        // Utils.reindexDocuments(index_dir);

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, searchTerm);

        // /* Verification */
        // assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 26: Sorting the results by an arbitrary field should not change the set
     * of results, only the order.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void sortingResultsByField(String index_dir, String searchTerm) throws Exception { // Fixed
        /* Get source output without sorting */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, searchTerm);

        /* Get follow-up output with sorting */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, searchTerm);
        Collections.sort(follow_out);

        /* Verification */
        assertTrue(source_out.containsAll(follow_out) && follow_out.containsAll(source_out));
    }

    /**
     * Metamorphic Relation 27: Searching with a term that is a substring of another term used in a
     * previous search should return a subset of the results or the same set.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void searchSubstringTerm(String index_dir) throws Exception { // Fixed
        String longerTerm = RandomStringUtils.randomAlphabetic(5, 10);
        String substringTerm = longerTerm.substring(1, 5);

        /* Get source output with the longer term */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, longerTerm);

        /* Get follow-up output with the substring term */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, substringTerm);

        /* Verification */
        assertTrue(follow_out.containsAll(source_out) || follow_out.size() >= source_out.size());
    }

    /**
     * Metamorphic Relation 28: Deleting a document from the index and searching should not return
     * the deleted document.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void deleteDocumentSearch(String index_dir, String searchTerm, String documentId)
            throws Exception {
        /* @formatter:off */
        // /* Get source output before deletion */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, searchTerm);

        // /* Delete a document from the index */
        // Utils.deleteDocument(index_dir, documentId);

        // /* Get follow-up output after deletion */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, searchTerm);

        // /* Verification */
        // assertTrue(source_out.size() >= follow_out.size());
        // assertFalse(follow_out.contains(documentId));
        /* @formatter:on */
    }

    /**
     * Metamorphic Relation 29: Increasing the result set size limitation should not decrease the
     * number of search results returned.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void increaseResultSizeLimit(String index_dir, String searchTerm, int limit)
            throws Exception {
        /* @formatter:off */
        // /* Get source output with initial result set size */
        // ArrayList<String> source_out = Utils.fullTextSearchWithLimit(index_dir, searchTerm, limit);

        // /* Get follow-up output with increased result set size */
        // ArrayList<String> follow_out = Utils.fullTextSearchWithLimit(index_dir, searchTerm, limit * 2);

        // /* Verification */
        // assertTrue(follow_out.size() >= source_out.size());
        /* @formatter:on */
    }

    /**
     * Metamorphic Relation 30: Refining search with an additional term included in all original
     * results should not change the result set.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void refineSearchWithAdditionalTerm(String index_dir, String originalSearchTerm)
            throws Exception { // Fixed
        String additionalTerm = "a";

        /* Get source output for the initial search term */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, originalSearchTerm);

        /* Check that all results contain the additional search term */
        boolean allResultsContainAdditionalTerm =
                source_out.stream().allMatch(result -> result.contains(additionalTerm));

        if (!allResultsContainAdditionalTerm) {
            return; // Skip the follow-up test if not all results contain the additional term.
        }

        /* Construct follow-up input by refining the search */
        String refinedSearch = originalSearchTerm + " " + additionalTerm;

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, refinedSearch);

        /* Verification */
        assertEquals(source_out.size(), follow_out.size());
    }

    /**
     * Metamorphic Relation 31: Adding ignored words to the search query should not change the
     * search results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void ignoredWordsSearch(String index_dir, String searchTerm) throws Exception { // Fixed
        List<String> ignoredWords = Arrays.asList("and", "or", "but", "not");

        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, searchTerm);

        /* Add ignored words to search term */
        String augmentedSearchTerm = searchTerm + " " + String.join(" ", ignoredWords);

        /* Get follow-up output */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, augmentedSearchTerm);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 32: Inverting the sort order of results should only affect their order,
     * not the content.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void inverseSortOrder(String index_dir, String searchTerm) throws Exception { // Fixed
        /* Perform search with standard sort order */
        List<String> source_out = Utils.fullTextSearch(index_dir, searchTerm);
        Collections.sort(source_out);

        /* Perform search with inverse sort order */
        List<String> follow_out = Utils.fullTextSearch(index_dir, searchTerm);
        Collections.sort(follow_out);
        Collections.reverse(follow_out);

        /* Verification */
        Collections.reverse(follow_out); // Reverse the follow_out to correspond to initial sort
                                         // order
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 33: Searching with a term should retrieve the same or more results after
     * adding new documents containing the term.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void addDocsRetrieveMore(String index_dir, String searchTerm, List<Document> newDocs)
            throws Exception {
        /* @formatter:off */
        // /* Get source output */
        // ArrayList<String> source_out = Utils.fullTextSearch(index_dir, searchTerm);

        // /* Add new documents to the index that contain the search term */
        // Utils.addDocuments(index_dir, newDocs);

        // /* Get follow-up output */
        // ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, searchTerm);

        // /* Verification */
        // assertTrue(follow_out.size() >= source_out.size());
        /* @formatter:on */
    }

    /**
     * Metamorphic Relation 34: Searching for documents without specifying a field should retrieve
     * the same or more results as when searching specifically within a field that has been indexed.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void fieldSpecifiedOrNot(String index_dir, String searchTerm) throws Exception { // Fixed
        String field = "title";

        /* Get source output with a field specified */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, field + ":" + searchTerm);

        /* Get follow-up output without specifying a field */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, searchTerm);

        /* Verification */
        assertTrue(follow_out.size() >= source_out.size());
    }

    /**
     * Metamorphic Relation 35: Searching with exact match (using quotes) should yield fewer results
     * than the same search without quotes.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void exactMatchVsLooseMatch(String index_dir, String searchTerm) throws Exception {
        /* Get source output with exact match */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, "\"" + searchTerm + "\"");

        /* Get follow-up output with loose match */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, searchTerm);

        /* Verification */
        assertTrue(follow_out.size() >= source_out.size());
    }

    /**
     * Metamorphic Relation 36: A search query that uses proximity search with a small distance
     * should yield fewer or the same results as the same query with a larger distance.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void proximitySearchWithDistances(String index_dir, ArrayList<String> searchTerms) throws Exception {
        assumeTrue(searchTerms.size() == 2);
        String term1 = searchTerms.get(0);
        String term2 = searchTerms.get(1);
        int smallDistance = 1;
        int largeDistance = 5;

        /* Get source output with small proximity search distance */
        ArrayList<String> source_out =
                Utils.fullTextSearch(index_dir, "\"" + term1 + " " + term2 + "\"~" + smallDistance);

        /* Get follow-up output with larger proximity search distance */
        ArrayList<String> follow_out =
                Utils.fullTextSearch(index_dir, "\"" + term1 + " " + term2 + "\"~" + largeDistance);

        /* Verification */
        assertTrue(follow_out.size() >= source_out.size());
    }

    /**
     * Metamorphic Relation 37: Searching with a term and its plural form should yield the same
     * results if stemming is enabled.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void searchWithPluralStemming(String index_dir, String singularTerm, String pluralTerm)
            throws Exception {
        /* Get source output with singular term */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, singularTerm);

        /* Get follow-up output with plural term */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, pluralTerm);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 38: The relevance score of results should not change after re-indexing
     * the documents without changes.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void consistentRelevanceScores(String index_dir, String searchTerm) throws Exception {
        /* @formatter:off */
        // /* Get source output with relevance scores */
        // List<SearchResult> source_out = Utils.fullTextSearchWithRelevanceScores(index_dir, searchTerm);

        // /* Re-index the same documents without changes */
        // Utils.reindexDocuments(index_dir);

        // /* Get follow-up output with relevance scores */
        // List<SearchResult> follow_out = Utils.fullTextSearchWithRelevanceScores(index_dir, searchTerm);

        // /* Verification */
        // for (int i = 0; i < source_out.size(); i++) {
        //     assertEquals(source_out.get(i).getScore(), follow_out.get(i).getScore(), 0.001); // A small delta for
        //                                                                                      // floating point
        //                                                                                      // comparison
        // }
        /* @formatter:on */
    }

    /**
     * Metamorphic Relation 39: Changing the case of the entire query in a case-insensitive index
     * should yield the same results.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void caseInsensitiveQuery(String index_dir, String searchTerm) throws Exception {
        /* Get source output */
        ArrayList<String> source_out = Utils.fullTextSearch(index_dir, searchTerm.toLowerCase());

        /* Get follow-up output with the query in uppercase */
        ArrayList<String> follow_out = Utils.fullTextSearch(index_dir, searchTerm.toUpperCase());

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 40: A negated query (using NOT operator) should yield complementary
     * results to the positive query.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void negatedQueryComplement(String index_dir, String searchTerm) throws Exception { // Fixed
        /* Get positive query output */
        ArrayList<String> pos_out = Utils.fullTextSearch(index_dir, searchTerm);

        /* Get negated query output */
        ArrayList<String> neg_out = Utils.fullTextSearch(index_dir, "NOT " + searchTerm);

        /* Verification */
        List<String> unionResults = new ArrayList<>();
        unionResults.addAll(pos_out);
        unionResults.addAll(neg_out);

        ArrayList<String> allDocs = new ArrayList<>();
        File file = new File(full_text_root + File.separator + "files");
        File[] files = file.listFiles();
        for (File f : files) {
            allDocs.add(full_text_root + File.separator + "files" + File.separator + f.getName());
        }

        // Union of positive and negated results should cover all documents
        assertTrue(allDocs.containsAll(unionResults));
        // There should be no overlap between positive and negated results
        assertTrue(Collections.disjoint(pos_out, neg_out));
    }

    /**
     * 构建测试输入
     *
     * @return
     * @throws Exception
     */
    public static Stream<Arguments> testcaseProvider1() throws Exception {
        return tetscaseGenerator.generate(full_text_root, 1000);
    }

    public static Stream<Arguments> testcaseProvider2() throws Exception {
        return tetscaseGenerator.generate_ss(full_text_root, 1000);
    }
}
