# Template 1

## Chat 1

Assume there is a trigonometric function sin(x), a source input x1, and a corresponding source output y1. If follow-up input x2=pi-x1 and corresponding follow-up output y2=y1, we say there is a metamorphic relation sin(x)=sin(pi-x).

Next, you need to identify the metamorphic relation of a function. There is a function that implements the Boyer-Moore algorithm to find the first occurrence index of the substring in the origin string. Its inputs are 2 string variables: ```text``` and ```pattern```, representing the origin string and substring, respectively. Its return value is an integer representing the occurrence index of ```pattern``` in ```text```. If ```pattern```does not occur in ```text```, the function returns -1. Please identify the metamorphic relation of this function as much as possible and output them as text. Each metamorphic relation should be named MR[x], where [x] is the test case number.

Here is an example:

MR1: Add string to the end of the origin string; the algorithm's output should be the same or greater.

## Chat 2

Please generate more different metamorphic relations.

# Template 2

## Chat 1

Assume there is a trigonometric function sin(x), a source input x1, and a corresponding source output y1. If follow-up input x2=pi-x1 and corresponding follow-up output y2=y1, we say there is a metamorphic relation sin(x)=sin(pi-x).

Next, you need to identify the metamorphic relation of a function. There is a function that implements the Boyer-Moore algorithm to find the first occurrence index of the string to be searched in the origin string. Its inputs are 2 string variables: ```text``` and ```pattern```, representing the origin string and the string to be searched, respectively. Its return value is an integer representing the first occurrence index of ```pattern``` in ```text```. If ```pattern```does not occur in ```text```, the function returns -1. Please identify the metamorphic relation of this function as much as possible and output them as java code. Each metamorphic relation should be named test[x], where [x] is the test case number.

Here is an example:

```java
/**
 * Metamorphic Relation 1: Add a string to the end of the origin string, the output of the
 * algorithm should be same or greater.
 *
 * @param text
 * @param pattern
 */
@ParameterizedTest
@MethodSource("testcaseProvider")
public void test1(String text, String pattern) {
    /* Get origin output */
    int origin_res = Boyer.indexOf(text, pattern);

    /* Construct follow-up input */
    String follow_text = text + "xxx";

    /* Get follow-up output */
    int follow_res = Boyer.indexOf(follow_text, pattern);

    /* Verification */
    assertTrue(follow_res >= origin_res);
}
```

## Chat 2

Please generate more different metamorphic relations.