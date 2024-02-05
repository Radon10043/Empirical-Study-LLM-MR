```java
/**
 * Metamorphic Relation 1: If the talk time increases, the bill should not decrease.
 */
@ParameterizedTest
@MethodSource("testcaseProvider")
public void test1(String planType, int planFee, int talkTime, int flow) {
    /* Get source output */
    BillCalculation CUBS = new BillCalculation();
    double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

    /* Construct follow-up input */
    int follow_talkTime = talkTime * 2;

    /* Get follow-up output */
    double follow_out = CUBS.phoneBillCalculation(planType, planFee, follow_talkTime, flow);

    /* Verification */
    assertTrue(follow_out >= source_out);
}

/**
 * Metamorphic Relation 2: If the talk time decreases, the bill should not increase.
 */
@ParameterizedTest
@MethodSource("testcaseProvider")
public void test2(String planType, int planFee, int talkTime, int flow) {
    /* Get source output */
    BillCalculation CUBS = new BillCalculation();
    double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

    /* Construct follow-up input */
    int follow_talkTime = talkTime / 2;

    /* Get follow-up output */
    double follow_out = CUBS.phoneBillCalculation(planType, planFee, follow_talkTime, flow);

    /* Verification */
    assertTrue(follow_out <= source_out);
}
```