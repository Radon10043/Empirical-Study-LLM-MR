```java
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
```