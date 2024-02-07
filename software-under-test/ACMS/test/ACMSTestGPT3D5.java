package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.stream.Stream;

import org.junit.Ignore;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import src.AirlinesBaggageBillingService;

public class ACMSTestGPT3D5 {
    /**
     * Metamorphic Relation 4: If isStudent is true, increasing the economicfee
     * should increase the luggage fee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        if (!isStudent)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        double follow_economicfee = economicfee * 2;

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, follow_economicfee);

        /* Verification */
        assertTrue(follow_out > source_out);
    }

    /**
     * Metamorphic Relation 5: The fee should increase when the luggage weight
     * exceeds the benchmark.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        double follow_luggage = luggage + 10;

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, isStudent, follow_luggage, economicfee);

        /* Verification */
        assertTrue(follow_out > source_out);
    }

    /**
     * Metamorphic Relation 6: The luggage fee should not change if the luggage
     * weight exactly matches the benchmark.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        double follow_luggage = luggage;

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, isStudent, follow_luggage, economicfee);

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /* Helper method */
    private double calculateBenchmarkWeight(int airClass, int area, boolean isStudent) {
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        ACMS.feeCalculation(airClass, area, isStudent, 0, 0);
        return ACMS.getBenchmark();
    }

    /**
     * Metamorphic Relation 7: Changing the airClass should only affect the luggage
     * fee if the luggage weight exceeds the benchmark.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        int follow_airClass = (airClass + 1) % 4;

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(follow_airClass, area, isStudent, luggage, economicfee);

        /* Verification */
        if (luggage > calculateBenchmarkWeight(airClass, area, isStudent)) {
            assertTrue(follow_out != source_out);
        } else {
            assertEquals(source_out, follow_out, 1e-6);
        }
    }

    /**
     * Metamorphic Relation 8: Changing the area code should only affect the luggage
     * fee if the luggage weight exceeds the benchmark.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        int follow_area = (area + 1) % 2;

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, follow_area, isStudent, luggage, economicfee);

        /* Verification */
        if (luggage > calculateBenchmarkWeight(airClass, area, isStudent)) {
            assertTrue(follow_out != source_out);
        } else {
            assertEquals(source_out, follow_out, 1e-6);
        }
    }

    /**
     * Metamorphic Relation 9: When both the area and airClass change, the luggage
     * fee changes if the luggage weight exceeds the benchmark.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        int follow_airClass = (airClass + 1) % 4;
        int follow_area = (area + 1) % 2;

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(follow_airClass, follow_area, isStudent, luggage, economicfee);

        /* Verification */
        if (luggage > calculateBenchmarkWeight(airClass, area, isStudent)) {
            assertTrue(follow_out != source_out);
        } else {
            assertEquals(source_out, follow_out, 1e-6);
        }
    }

    /**
     * Metamorphic Relation 10: If the luggage weight is increased by a certain
     * factor, the luggage fee should also increase by a certain factor.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        double follow_luggage = luggage * 1.5;

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, isStudent, follow_luggage, economicfee);

        /* Verification */
        double expectedIncreasedFee = source_out * 1.5; // Assuming a linear relationship between luggage weight and fee
        assertEquals(expectedIncreasedFee, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 11: If the luggage weight is doubled and the economic
     * fee is halved, the luggage fee should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        double follow_luggage = luggage * 2;
        double follow_economicfee = economicfee / 2;

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, isStudent, follow_luggage, follow_economicfee);

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 12: If the area changes and the student status changes,
     * the luggage fee should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        int follow_area = (area + 1) % 2;
        boolean follow_isStudent = !isStudent;

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, follow_area, follow_isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 13: Changing the economic fee should proportionally
     * change the luggage fee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        double follow_economicfee = economicfee * 1.1; // 10% increase

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, follow_economicfee);

        /* Verification */
        double expectedIncreasedFee = source_out * 1.1; // Assuming a linear relationship between economic fee and
                                                        // luggage fee
        assertEquals(expectedIncreasedFee, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 14: If the luggage weight is 0, changing the student
     * status should not affect the luggage fee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not 0 */
        if (luggage != 0) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        boolean follow_isStudent = !isStudent;

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, follow_isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 15: The luggage fee should increase if the luggage
     * weight exceeds the benchmark and the economic fee is increased.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not greater than the benchmark */
        if (luggage <= calculateBenchmarkWeight(airClass, area, isStudent)) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        double follow_luggage = luggage + 10; // increase luggage weight
        double follow_economicfee = economicfee * 1.1; // 10% increase in economic fee

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, isStudent, follow_luggage, follow_economicfee);

        /* Verification */
        assertTrue(follow_out > source_out);
    }

    /**
     * Metamorphic Relation 16: Changing the area and airClass should not affect the
     * luggage fee if the luggage weight is 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not 0 */
        if (luggage != 0) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        int follow_airClass = (airClass + 1) % 4;
        int follow_area = (area + 1) % 2;

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(follow_airClass, follow_area, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 17: If the luggage weight is zero and the economic fee
     * is doubled, the luggage fee should also be doubled.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not 0 */
        if (luggage != 0) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        double follow_economicfee = economicfee * 2; // Double the economic fee

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, follow_economicfee);

        /* Verification */
        double expectedDoubledFee = source_out * 2;
        assertEquals(expectedDoubledFee, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 18: If the luggage weight is zero and the airClass is
     * changed, the luggage fee should not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not 0 */
        if (luggage != 0) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        int follow_airClass = (airClass + 1) % 4; // Change airClass

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(follow_airClass, area, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 19: The luggage fee should not change when the economic
     * fee is doubled and the luggage weight is zero.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not 0 */
        if (luggage != 0) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        double follow_economicfee = economicfee * 2; // Double the economic fee

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, follow_economicfee);

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 20: If the luggage weight is increased and the economic
     * fee is decreased, the luggage fee should stay the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        double follow_luggage = luggage * 2; // Double the luggage weight
        double follow_economicfee = economicfee / 2; // Halve the economic fee

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, isStudent, follow_luggage, follow_economicfee);

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 21: If the economic fee is increased, the luggage fee
     * should increase proportionally.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        double increasedEconomicFee = economicfee * 1.1; // 10% increase

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, increasedEconomicFee);

        /* Verification */
        double expectedIncreasedFee = sourceOut * 1.1; // Assuming a linear relationship between economic fee and
                                                       // luggage fee
        assertEquals(expectedIncreasedFee, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 22: If the student status changes, the luggage fee
     * should remain the same when the luggage weight is 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not 0 */
        if (luggage != 0) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        boolean changedStudentStatus = !isStudent;

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, area, changedStudentStatus, luggage, economicfee);

        /* Verification */
        assertEquals(sourceOut, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 23: If the airClass changes, the luggage fee should
     * change only if the luggage weight exceeds the benchmark weight.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        int changedAirClass = (airClass + 1) % 4;

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(changedAirClass, area, isStudent, luggage, economicfee);

        /* Verification */
        if (luggage > calculateBenchmarkWeight(changedAirClass, area, isStudent)) {
            assertTrue(sourceOut != followOut);
        } else {
            assertEquals(sourceOut, followOut, 1e-6);
        }
    }

    /**
     * Metamorphic Relation 24: Changing the area and economicfee should affect the
     * luggage fee if the luggage weight exceeds the benchmark weight.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        int changedArea = (area + 1) % 2;
        double changedEconomicFee = economicfee * 1.1; // 10% increase

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, changedArea, isStudent, luggage, changedEconomicFee);

        /* Verification */
        if (luggage > calculateBenchmarkWeight(airClass, area, isStudent)) {
            assertTrue(sourceOut != followOut);
        } else {
            assertEquals(sourceOut, followOut, 1e-6);
        }
    }

    /**
     * Metamorphic Relation 25: If the weight of luggage is doubled and the area is
     * changed, the luggage fee should not change if the passenger is a student.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        double doubledLuggage = luggage * 2; // Double the luggage weight
        int changedArea = (area + 1) % 2;

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, changedArea, isStudent, doubledLuggage, economicfee);

        /* Verification */
        if (isStudent) {
            assertEquals(sourceOut, followOut, 1e-6);
        }
    }

    /**
     * Metamorphic Relation 26: If the air class is incremented by 1, and the
     * student status changes, then the luggage fee should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        int changedAirClass = (airClass + 1) % 4; // Increment air class by 1
        boolean studentStatusChanged = !isStudent; // Change student status

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(changedAirClass, area, studentStatusChanged, luggage, economicfee);

        /* Verification */
        assertEquals(sourceOut, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 27: If the area changes and the luggage weight is
     * doubled, the luggage fee should change if the student status is true.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        int changedArea = (area + 1) % 2; // Change area
        double doubledLuggage = luggage * 2; // Double the luggage weight

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, changedArea, isStudent, doubledLuggage, economicfee);

        /* Verification */
        if (isStudent) {
            assertTrue(sourceOut != followOut);
        }
    }

    /**
     * Metamorphic Relation 28: If the luggage weight is zero and the air class
     * changes, the luggage fee should not change if the student status is false.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not 0 or student status is true */
        if (luggage != 0 || isStudent) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        int changedAirClass = (airClass + 1) % 4; // Change air class

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(changedAirClass, area, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(sourceOut, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 29: If the luggage weight exceeds the benchmark, then
     * doubling both the luggage weight and the economic fee should quadruple the
     * luggage fee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not greater than the benchmark */
        if (luggage <= calculateBenchmarkWeight(airClass, area, isStudent)) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        double doubledLuggage = luggage * 2; // Double the luggage weight
        double doubledEconomicFee = economicfee * 2; // Double the economic fee

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, area, isStudent, doubledLuggage, doubledEconomicFee);

        /* Verification */
        double expectedQuadrupledFee = sourceOut * 4;
        assertEquals(expectedQuadrupledFee, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 30: If the luggage weight exceeds the benchmark and the
     * economic fee is increased, the luggage fee should increase nonlinearly.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not greater than the benchmark */
        if (luggage <= calculateBenchmarkWeight(airClass, area, isStudent)) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        double increasedEconomicFee = economicfee * 1.5; // 50% increase in economic fee

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, increasedEconomicFee);

        /* Verification */
        assertTrue(followOut > sourceOut);
    }

    /**
     * Metamorphic Relation 31: If the luggage weight exceeds the benchmark,
     * changing the area and doubling the economic fee should increase the luggage
     * fee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not greater than the benchmark */
        if (luggage <= calculateBenchmarkWeight(airClass, area, isStudent)) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        int changedArea = (area + 1) % 2; // Change area
        double doubledEconomicFee = economicfee * 2; // Double the economic fee

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, changedArea, isStudent, luggage, doubledEconomicFee);

        /* Verification */
        assertTrue(followOut > sourceOut);
    }

    /**
     * Metamorphic Relation 32: If the luggage weight exceeds the benchmark,
     * increasing the economic fee and doubling the luggage weight should greatly
     * increase the luggage fee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not greater than the benchmark */
        if (luggage <= calculateBenchmarkWeight(airClass, area, isStudent)) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        double increasedEconomicFee = economicfee * 1.5; // Increase the economic fee
        double doubledLuggage = luggage * 2; // Double the luggage weight

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, area, isStudent, doubledLuggage, increasedEconomicFee);

        /* Verification */
        assertTrue(followOut > sourceOut);
    }

    /**
     * Metamorphic Relation 33: If the luggage weight exceeds the benchmark,
     * increasing the economic fee and changing the area should proportionately
     * increase the luggage fee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not greater than the benchmark */
        if (luggage <= calculateBenchmarkWeight(airClass, area, isStudent)) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        double increasedEconomicFee = economicfee * 1.5; // Increase the economic fee
        int changedArea = (area + 1) % 2; // Change area

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, changedArea, isStudent, luggage, increasedEconomicFee);

        /* Verification */
        double expectedIncreasedFee = sourceOut * 1.5; // Assuming a linear relationship between economic fee and
                                                       // luggage fee
        assertEquals(expectedIncreasedFee, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 34: If the luggage weight is 0 and the student status
     * changes, the luggage fee should not change, even if the economic fee is
     * doubled.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not 0 */
        if (luggage != 0) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        boolean changedStudentStatus = !isStudent; // Change student status
        double doubledEconomicFee = economicfee * 2; // Double the economic fee

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, area, changedStudentStatus, luggage, doubledEconomicFee);

        /* Verification */
        assertEquals(sourceOut, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 35: If the luggage weight is 0 and the area changes, the
     * luggage fee should not change, even if the economic fee is doubled.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not 0 */
        if (luggage != 0) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        int changedArea = (area + 1) % 2; // Change area
        double doubledEconomicFee = economicfee * 2; // Double the economic fee

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, changedArea, isStudent, luggage, doubledEconomicFee);

        /* Verification */
        assertEquals(sourceOut, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 36: If the luggage weight exceeds the benchmark,
     * changing the airClass and multiplying the economic fee by 1.5 should
     * proportionately increase the luggage fee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not greater than the benchmark */
        if (luggage <= calculateBenchmarkWeight(airClass, area, isStudent)) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        int changedAirClass = (airClass + 1) % 4; // Change air class
        double increasedEconomicFee = economicfee * 1.5; // Increase the economic fee by 50%

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(changedAirClass, area, isStudent, luggage, increasedEconomicFee);

        /* Verification */
        double expectedIncreasedFee = sourceOut * 1.5; // Assuming a linear relationship between economic fee and
                                                       // luggage fee
        assertEquals(expectedIncreasedFee, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 37: If the luggage weight is 0 and the student status
     * changes, the luggage fee should remain the same even if the area is changed
     * and the economic fee is doubled.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not 0 */
        if (luggage != 0) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        boolean changedStudentStatus = !isStudent; // Change student status
        int changedArea = (area + 1) % 2; // Change area
        double doubledEconomicFee = economicfee * 2; // Double the economic fee

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, changedArea, changedStudentStatus, luggage,
                doubledEconomicFee);

        /* Verification */
        assertEquals(sourceOut, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 38: If the luggage weight exceeds the benchmark, the
     * luggage fee should change when the airClass, area, and economic fee are all
     * changed.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not greater than the benchmark */
        if (luggage <= calculateBenchmarkWeight(airClass, area, isStudent)) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        int changedAirClass = (airClass + 1) % 4; // Change air class
        int changedArea = (area + 1) % 2; // Change area
        double doubledEconomicFee = economicfee * 2; // Double the economic fee

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(changedAirClass, changedArea, isStudent, luggage, doubledEconomicFee);

        /* Verification */
        assertTrue(sourceOut != followOut);
    }

    /**
     * Metamorphic Relation 39: If the luggage weight exceeds the benchmark,
     * doubling the luggage weight and increasing the economic fee should
     * substantially increase the luggage fee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not greater than the benchmark */
        if (luggage <= calculateBenchmarkWeight(airClass, area, isStudent)) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        double doubledLuggage = luggage * 2; // Double the luggage weight
        double increasedEconomicFee = economicfee * 1.5; // Increase the economic fee

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, area, isStudent, doubledLuggage, increasedEconomicFee);

        /* Verification */
        assertTrue(followOut > sourceOut);
    }

    /**
     * Metamorphic Relation 40: If the luggage weight exceeds the benchmark, the
     * luggage fee should change proportionally when the economic fee is increased
     * and the area is changed.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not greater than the benchmark */
        if (luggage <= calculateBenchmarkWeight(airClass, area, isStudent)) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        double increasedEconomicFee = economicfee * 1.5; // Increase the economic fee
        int changedArea = (area + 1) % 2; // Change area

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, changedArea, isStudent, luggage, increasedEconomicFee);

        /* Verification */
        double expectedIncreasedFee = sourceOut * 1.5; // Assuming a linear relationship between economic fee and
                                                       // luggage fee
        assertEquals(expectedIncreasedFee, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 41: If the luggage exceeds the benchmark, changing the
     * area and airClass should proportionally affect the luggage fee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test41(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not greater than the benchmark */
        if (luggage <= calculateBenchmarkWeight(airClass, area, isStudent)) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        int changedAirClass = (airClass + 1) % 4; // Change air class
        int changedArea = (area + 1) % 2; // Change area

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(changedAirClass, changedArea, isStudent, luggage, economicfee);

        /* Verification */
        double expectedIncreasedFee = sourceOut * 1.1; // Assuming a linear relationship between area and luggage fee
        assertEquals(expectedIncreasedFee, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 42: If the luggage exceeds the benchmark, changing the
     * airClass should affect the luggage fee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test42(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not greater than the benchmark */
        if (luggage <= calculateBenchmarkWeight(airClass, area, isStudent)) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        int changedAirClass = (airClass + 1) % 4; // Change air class

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(changedAirClass, area, isStudent, luggage, economicfee);

        /* Verification */
        assertTrue(sourceOut != followOut);
    }

    /**
     * Metamorphic Relation 43: Changing the airClass and increasing the economic
     * fee should proportionally increase the luggage fee if the luggage weight
     * exceeds the benchmark.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test43(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Skip if luggage weight is not greater than the benchmark */
        if (luggage <= calculateBenchmarkWeight(airClass, area, isStudent)) {
            return;
        }

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs */
        int changedAirClass = (airClass + 1) % 4; // Change air class
        double increasedEconomicFee = economicfee * 1.5; // Increase the economic fee

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(changedAirClass, area, isStudent, luggage, increasedEconomicFee);

        /* Verification */
        double expectedIncreasedFee = sourceOut * 1.5; // Assuming a linear relationship between economic fee and
                                                       // luggage fee
        assertEquals(expectedIncreasedFee, followOut, 1e-6);
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
