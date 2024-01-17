package test;

import java.util.stream.Stream;

import src.AirlinesBaggageBillingService;

import static org.junit.jupiter.api.Assertions.assertEquals;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

public class ACMSTestExample {
    /**
     * Metamorphic Relation 1: If the luggage weight is 0, changing area should not affect the
     * luggagefee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        if (luggage != 0)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        int follow_area = area + 1;

        /* Get follow-up output */
        double follow_out =
                ACMS.feeCalculation(airClass, follow_area, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 2: If isStudent is false, changing the area should not affect the
     * luggage fee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        if (isStudent)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        int follow_area = area + 1;

        /* Get follow-up output */
        double follow_out =
                ACMS.feeCalculation(airClass, follow_area, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * 随机生成一定数量的测试用例
     *
     * @return
     * @throws Exception
     */
    public static Stream<Arguments> testcaseProvider() throws Exception {
        return testcaseGenerator.generate(1000);
    }
}
