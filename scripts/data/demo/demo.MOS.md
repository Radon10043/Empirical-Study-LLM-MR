```java
/**
 * Metamorphic Relation 1: keeping other attributes unchanged, double the
 * numberofrequestedbundlesofflowers input, the numberOfRequestedBundlesOfFlowers attributes in
 * output should also double.
 */
@ParameterizedTest
@MethodSource("testcaseProvider")
public void test1(String aircraftmodel, String changeinthenumberofcrewmembers,
        int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
        int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
    /* Get source output */
    MealOrderingSystem MOS = new MealOrderingSystem();
    MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
            newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
            numberofchildpassengers, numberofrequestedbundlesofflowers);

    /* Construct follow-up input */
    int follow_numberofrequestedbundlesofflowers = numberofrequestedbundlesofflowers * 2;

    /* Get follow-up output */
    MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
            newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
            numberofchildpassengers, follow_numberofrequestedbundlesofflowers);

    /* Verification */
    assertTrue(source_out.numberOfBundlesOfFlowers * 2 == follow_out.numberOfBundlesOfFlowers);
}
```