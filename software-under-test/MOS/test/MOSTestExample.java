package test;

import static org.junit.Assert.assertTrue;
import java.util.stream.Stream;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import src.MSR;
import src.MealOrderingSystem;

public class MOSTestExample {
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

    /**
     * Metamorphic Relation 2: If the aircraftmodel parameter remains the same while other
     * parameters change, the values related to seat configuration (numberOfFirstClassMeals,
     * numberOfBusinessClassMeals, numberOfEconomicClassMeals) should remain constant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Get source output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Construct follow-up input */
        String follow_changeinthenumberofpilots;
        if (changeinthenumberofpilots.equals("y")) {
            follow_changeinthenumberofpilots = "n";
        } else {
            follow_changeinthenumberofpilots = "y";
        }
        int follow_newnumberofpilots = newnumberofpilots * 2;
        int follow_numberofchildpassengers = numberofchildpassengers * 2;

        /* Get follow-up output */
        MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, follow_changeinthenumberofpilots, follow_newnumberofpilots,
                follow_numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Verification */
        assertTrue(source_out.numberOfFirstClassMeals == follow_out.numberOfFirstClassMeals);
        assertTrue(source_out.numberOfBusinessClassMeals == follow_out.numberOfBusinessClassMeals);
        assertTrue(source_out.numberOfEconomicClassMeals == follow_out.numberOfEconomicClassMeals);
    }

    /**
     * 随机生成测试用例
     *
     * @return
     * @throws Exception
     */
    public static Stream<Arguments> testcaseProvider() throws Exception {
        return testcaseGenerator.generate(1000);
    }
}
