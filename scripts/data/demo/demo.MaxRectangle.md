```java
/**
 * Metamorphic Relation 1: Adding one row, the output should be the same as or larger than the
 * original one.
 */
@ParameterizedTest
@MethodSource("testcaseProvider")
public void test1(ArrayList<ArrayList<Integer>> matrix) {
    /* Get source output */
    int source_out = MaxRectangle.maximalRectangle(matrix);

    /* Construct follow-up input */
    int col_num = matrix.get(0).size();
    ArrayList<Integer> nrow = new ArrayList<Integer>(Collections.nCopies(col_num, 1));
    ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<ArrayList<Integer>>();
    follow_matrix.addAll(matrix);
    follow_matrix.add(nrow);

    /* Get follow-up output */
    int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

    /* Verification */
    assertTrue(follow_out >= source_out);
}

/**
 * Mrtamorphic Relation 2: Adding one column, the output should be the same as or larger than
 * the original one.
 */
@ParameterizedTest
@MethodSource("testcaseProvider")
public void test2(ArrayList<ArrayList<Integer>> matrix) {
    /* Get source output */
    int source_out = MaxRectangle.maximalRectangle(matrix);

    /* Construct follow-up output */
    ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<ArrayList<Integer>>();
    follow_matrix.addAll(matrix);
    for (var row : follow_matrix) {
        row.add(1);
    }

    /* Get follow-up output */
    int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

    /* Verification */
    assertTrue(follow_out >= source_out);
}
```