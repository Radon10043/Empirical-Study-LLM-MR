```java
/**
 * Metamorphic Relation 1: Assume a', b', c' is the second triangle, if (a,b,c)=(b',a',c'), the
 * output will not change.
 */
@ParameterizedTest
@MethodSource("testcaseProvider")
public void test1(int a, int b, int c) {
    /* Get source out */
    Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

    /* Construct follow-up input */
    int follow_a = b, follow_b = a;

    /* Get follow-up output */
    Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, c);

    /* Verification */
    assertEquals(source_out, follow_out);
}

/**
 * Metamorphic Relation 2: Assume a', b', c' is the second triangle, if (a,b,c)=(a',c',b'), the
 * output will not change.
 */
@ParameterizedTest
@MethodSource("testcaseProvider")
public void test2(int a, int b, int c) {
    /* Get source output */
    Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

    /* Construct follow-up input */
    int follow_b = c, follow_c = b;

    /* Get follow-up output */
    Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(a, follow_b, follow_c);

    /* Verification */
    assertEquals(source_out, follow_out);
}

/**
 * Metamorphic Relation 3: Assume a', b', c' is the second triangle, if (a,b,c)=(c',b',a'), the
 * output will not change.
 */
@ParameterizedTest
@MethodSource("testcaseProvider")
public void test3(int a, int b, int c) {
    /* Get source output */
    Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

    /* Construct follow-up input */
    int follow_c = a, follow_a = c;

    /* Get follow-up output */
    Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, b, follow_c);

    /* Verification */
    assertEquals(source_out, follow_out);
}

/**
 * Metamorphic Relation 4: Assume a', b', c' is the second triangle, if (a,b,c)=(2a',2b',2c'),
 * then the type will not change, but the area of the first triangle is four times the second
 * triangle.
 */
@ParameterizedTest
@MethodSource("testcaseProvider")
public void test4(int a, int b, int c) {
    assumeTrue(a % 2 == 0 && b % 2 == 0 && c % 2 == 0);

    /* Get source output */
    Pair<Integer, Double> source_out = TriSquareJ.triangle_square(a, b, c);

    /* Construct follow-up input */
    int follow_a = a / 2, follow_b = b / 2, follow_c = c / 2;

    /* Get follow-up output */
    Pair<Integer, Double> follow_out = TriSquareJ.triangle_square(follow_a, follow_b, follow_c);

    /* Verification */
    int source_type = source_out.getKey().intValue(), follow_type = follow_out.getKey().intValue();
    double source_area = source_out.getValue().doubleValue(), follow_area = follow_out.getValue().doubleValue();
    assertEquals(source_type, follow_type);
    assertTrue(Math.abs(source_area - follow_area * 4) < 1e-6);
}
```