```java
/**
 * Metamorphic Relation 1: The determinant of the matrix is equal to the determinant of the
 * transposed matrix, i.e., det(A)=det(A^T)
 */
@ParameterizedTest
@MethodSource("testcaseProvider")
public void test1(Matrix m) {
    /* Get source output */
    double source_out = m.det();

    /* Construct follow-up input */
    Matrix follow_m = m.transpose();

    /* Get follow-up output */
    double follow_out = follow_m.det();

    /* Verification */
    assertEquals(source_out, follow_out, 1e-6);
}

/**
 * Metamorphic Relation 2: The determinant of the matrix multiply a constant equals to the
 * determinant of the matrix which elements in a row multiply the same constant.
 */
@ParameterizedTest
@MethodSource("testcaseProvider")
public void test2(Matrix m) {
    int constant = 3;

    /* Get source output */
    double source_out = constant * m.det();

    /* Construct follow-up input */
    Matrix follow_m = m.copy();
    int k = rand.nextInt(m.getRowDimension()); // Select a row randomly
    for (int i = 0; i < follow_m.getRowDimension(); i++)
        follow_m.set(k, i, follow_m.get(k, i) * constant);

    /* Get follow-up output */
    double follow_out = follow_m.det();

    /* Verification */
    assertEquals(source_out, follow_out, 1e-6);
}
```