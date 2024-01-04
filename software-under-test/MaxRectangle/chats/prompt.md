# Prompt

## Chat 1

Metamorphic testing is usually used to check whether the software under test satisfies specific properties. Among them, metamorphic relation is the core concept of metamorphic testing. The metamorphic relation can be considered a formal expression of the properties of the software under test and usually consists of two parts, namely the input relation and the output relation.

## Chat 2

For the function $sin(x)$, assuming there is an origin input $x1$, the corresponding origin output is $y1$, $x2$ is a follow-up input, and the corresponding follow-up output is $y2$. $x2$ is transformed from $x1$, and there is an input relation between $x2$ and $x1$: $x2=\pi-x1$, an output relation between $y1$ and $y2$: $y1=y2$. Therefore, there is a metamorphic relation $sin(x)=sin(\pi-x)$.

## Chat 3

You are an expert on metamorphic testing. Based on the above case, please identify the metamorphic relation of this program: There is a function that implements an algorithm to find the largest rectangle containing all 1s. Its input is a binary matrix that is filled with 0s and 1s. Its output is an integer representing the largest rectangle area that contains all 1s. Please identify the metamorphic relation of this function as much as possible and output them as java code. Each metamorphic relation should be named test[x], where [x] is the test case number. Here are some examples:

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

## Chat 4...n

Please identify more different metamorphic relations of this program and codify them as java code.