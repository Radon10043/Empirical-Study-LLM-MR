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
     * Metamorphic Relation 4: If the economic fee is doubled, the luggage fee
     * should be doubled
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        double follow_economicfee = economicfee * 2;

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, follow_economicfee);

        /* Verification */
        assertEquals(source_out * 2, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 5: If the airClass is 3 (basic economy), the luggage fee
     * should be 0
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        if (airClass != 3)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(0, source_out, 1e-6);
    }

    /**
     * Metamorphic Relation 6: If the area is 1 (domestic), and isStudent is true,
     * the luggage fee should be equal to or less than the benchmark fee
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        if (area != 1 || !isStudent)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Verification */
        assertTrue(source_out <= 30);
    }

    /**
     * Metamorphic Relation 7: If the luggage weight exceeds the benchmark for the
     * given air class, the luggage fee should be greater than or equal to the
     * economic fee
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        double follow_luggage = luggage + 10; // Exceed the benchmark

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, isStudent, follow_luggage, economicfee);

        /* Verification */
        assertTrue(follow_out >= economicfee);
    }

    /**
     * Metamorphic Relation 8: If the area and air class are unchanged and the
     * luggage is zero, the luggage fee should be zero.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        if (luggage != 0)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(0, source_out, 1e-6);
    }

    /**
     * Metamorphic Relation 9: If the area is international, and air class is not
     * economy, the luggage fee should be reduced by the take-along discount
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        if (area != 0 || airClass == 3)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        double follow_luggage = luggage;

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, isStudent, follow_luggage, economicfee);

        /* Verification */
        assertTrue(source_out > follow_out);
    }

    /**
     * Metamorphic Relation 10: If the area is domestic and air class is not
     * economy, the luggage fee should be affected by the take-along discount
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        if (area != 1 || airClass == 3)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        double follow_luggage = luggage;

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, isStudent, follow_luggage, economicfee);

        /* Verification */
        assertTrue(source_out > follow_out);
    }

    /**
     * Metamorphic Relation 11: If the area is not valid (neither 0 nor 1), the
     * function should return -1
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        if (area == 0 || area == 1)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(-1, source_out, 1e-6);
    }

    /**
     * Metamorphic Relation 12: If the air class is not valid (should be between 0
     * and 3), the function should return -1
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        if (airClass >= 0 && airClass <= 3)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(-1, source_out, 1e-6);
    }

    /**
     * Metamorphic Relation 13: If the area and air class remain unchanged, and
     * isStudent is true, the luggage fee should be affected by the student discount
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        if (!isStudent)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        double follow_luggage = luggage;

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, isStudent, follow_luggage, economicfee);

        /* Verification */
        assertTrue(source_out > follow_out);
    }

    /**
     * Metamorphic Relation 14: If all parameters except economic fee are the same,
     * the luggage fee should not be affected
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        double follow_economicfee = economicfee + 10;

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, follow_economicfee);

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 15: If all parameters are the same, the luggage fee
     * should remain consistent
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 16: If luggage exceeds the benchmark and isStudent is
     * true, the luggage fee should be affected by the student discount
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        if (!isStudent || luggage <= 0)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        double follow_luggage = luggage + 10; // Exceed the benchmark

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, isStudent, follow_luggage, economicfee);

        /* Verification */
        assertTrue(source_out > follow_out);
    }

    /**
     * Metamorphic Relation 17: If the area and air class are both domestic, the
     * luggage fee should be consistent with take-along fees
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        if (area != 1)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        double follow_luggage = luggage;

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, isStudent, follow_luggage, economicfee);

        /* Verification */
        assertEquals(source_out - 7, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 18: If the economic fee is set to be 0, the luggage fee
     * should always be 0
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        if (economicfee != 0)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(0, source_out, 1e-6);
    }

    /**
     * Metamorphic Relation 19: If the luggage weight is less than benchmark, and
     * isStudent is false, the luggage fee should be less than or equal to the
     * benchmark
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        if (isStudent || luggage >= 40 || luggage <= 0)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Verification */
        assertTrue(source_out <= 40);
    }

    /**
     * Metamorphic Relation 20: If the airClass and area are unchanged, and
     * isStudent is true, the luggage fee should be greater than or equal to the
     * benchmark
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        if (!isStudent)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Verification */
        assertTrue(source_out >= 40);
    }

    /**
     * Metamorphic Relation 21: If the luggage weight is more than the benchmark and
     * the economic fee increases, the luggage fee should also increase
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        if (luggage <= 40)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        double follow_economicfee = economicfee * 2;

        /* Get follow-up output */
        double follow_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, follow_economicfee);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 22: If the area is domestic and isStudent is false, the
     * luggage fee should be affected by the take-along fee
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        if (area != 1 || isStudent)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        double followLuggage = luggage;

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, area, isStudent, followLuggage, economicfee);

        /* Verification */
        assertTrue(followOut < sourceOut);
    }

    /**
     * Metamorphic Relation 23: If the economic fee is negative, the function should
     * return -1
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        if (economicfee >= 0)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(-1, sourceOut, 1e-6);
    }

    /**
     * Metamorphic Relation 24: If the airClass is negative, the function should
     * return -1
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        if (airClass >= 0)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(-1, sourceOut, 1e-6);
    }

    /**
     * Metamorphic Relation 25: If the economic fee is zero, the luggage fee should
     * also be zero
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        if (economicfee != 0)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(0, sourceOut, 1e-6);
    }

    /**
     * Metamorphic Relation 26: If the luggage weight is zero, the luggage fee
     * should also be zero, regardless of other parameters
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        if (luggage != 0)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(0, sourceOut, 1e-6);
    }

    /**
     * Metamorphic Relation 27: If the air class and area remain unchanged, and the
     * economic fee is halved, the luggage fee should also be halved
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        double followEconomicFee = economicfee / 2;

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, followEconomicFee);

        /* Verification */
        assertEquals(sourceOut / 2, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 28: If the luggage weight is zero and the economic fee
     * is non-zero, the luggage fee should be consistent for different air classes
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        if (luggage != 0)
            return;

        /* Get source output for air class 0 */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOutAirClass0 = ACMS.feeCalculation(0, area, isStudent, luggage, economicfee);

        /* Get source output for air class 1 */
        double sourceOutAirClass1 = ACMS.feeCalculation(1, area, isStudent, luggage, economicfee);

        /* Get source output for air class 2 */
        double sourceOutAirClass2 = ACMS.feeCalculation(2, area, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(sourceOutAirClass0, sourceOutAirClass1, 1e-6);
        assertEquals(sourceOutAirClass1, sourceOutAirClass2, 1e-6);
    }

    /**
     * Metamorphic Relation 29: If luggage, economic fee, and area remain unchanged,
     * the luggage fee should be affected by the airClass
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(int airClass, int area, boolean isStudent, double luggage, double economicfee) {

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        int followAirClass = airClass + 1; // Increment the airClass

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(followAirClass, area, isStudent, luggage, economicfee);

        /* Verification */
        assertTrue(followOut > sourceOut); // As airClass increases, the luggage fee should also increase
    }

    /**
     * Metamorphic Relation 30: If all parameters remain unchanged and the area is
     * domestic, the luggage fee should be affected by the isStudent flag
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        if (area != 1)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs with and without isStudent flag */
        boolean followIsStudent = !isStudent;
        double followOutForIsStudent = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);
        double followOutWithoutIsStudent = ACMS.feeCalculation(airClass, area, followIsStudent, luggage, economicfee);

        /* Verification */
        assertTrue(followOutForIsStudent > followOutWithoutIsStudent);
    }

    /**
     * Metamorphic Relation 31: If all parameters except area are the same, the
     * luggage fee should not be affected by the area
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(int airClass, int area, boolean isStudent, double luggage, double economicfee) {

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        int followArea = area + 1; // Increment the area

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, followArea, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(sourceOut, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 32: If area, air class, and economic fee are constant
     * and luggage exceeds the benchmark, the luggage fee should be affected by the
     * isStudent flag
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        if (luggage <= 40)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up inputs with and without isStudent flag */
        boolean followIsStudent = !isStudent;
        double followOutForIsStudent = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);
        double followOutWithoutIsStudent = ACMS.feeCalculation(airClass, area, followIsStudent, luggage, economicfee);

        /* Verification */
        assertTrue(followOutForIsStudent < followOutWithoutIsStudent);
    }

    /**
     * Metamorphic Relation 33: If the economic fee is not affected, the luggage fee
     * should remain consistent for the same area and air class
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(int airClass, int area, boolean isStudent, double luggage, double economicfee) {

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        double followLuggage = luggage + 10;

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, area, isStudent, followLuggage, economicfee);

        /* Verification */
        assertEquals(sourceOut, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 34: If the luggage weight is less than the benchmark,
     * the luggage fee should be consistent if isStudent flag is true or false
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        if (luggage >= 40) // For luggage greater than or equal to the benchmark, the expected behavior may
                           // vary based on isStudent flag
            return;

        /* Get source output for isStudent true */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOutStudentTrue = ACMS.feeCalculation(airClass, area, true, luggage, economicfee);

        /* Get source output for isStudent false */
        double sourceOutStudentFalse = ACMS.feeCalculation(airClass, area, false, luggage, economicfee);

        /* Verification */
        assertEquals(sourceOutStudentTrue, sourceOutStudentFalse, 1e-6);
    }

    /**
     * Metamorphic Relation 35: If the luggage weight is greater than the benchmark
     * for a specific air class, the luggage fee should be consistent for different
     * areas
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        if (luggage <= 40) // For luggage less than or equal to benchmark, the expected behavior may vary
                           // based on area
            return;

        /* Get source output for area 0 */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOutArea0 = ACMS.feeCalculation(airClass, 0, isStudent, luggage, economicfee);

        /* Get source output for area 1 */
        double sourceOutArea1 = ACMS.feeCalculation(airClass, 1, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(sourceOutArea0, sourceOutArea1, 1e-6);
    }

    /**
     * Metamorphic Relation 36: If the luggage fee calculation is valid for a given
     * set of parameters, the result should be consistent regardless of the order of
     * parameter values
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    @Ignore
    public void test36(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        /* INVALID */
        // /* Get source output for ordered parameters */
        // AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        // double sourceOutOrderedParams = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // /* Get source output for shuffled parameters */
        // double sourceOutShuffledParams = ACMS.feeCalculation(area, isStudent, airClass, economicfee, luggage);

        // /* Verification */
        // assertEquals(sourceOutOrderedParams, sourceOutShuffledParams, 1e-6);
    }

    /**
     * Metamorphic Relation 37: If the luggage weight is 0, the luggage fee should
     * be consistent when the economic fee is changed
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        if (luggage != 0) // Tests are not meaningful when luggage weight is non-zero
            return;

        /* Get source output for economic fee */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input: increased economic fee */
        double followEconomicFee = economicfee * 2;

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, followEconomicFee);

        /* Verification */
        assertEquals(sourceOut, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 38: If the area is domestic and air class is 3, the
     * luggage fee should be 0
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        if (area != 1 || airClass != 3) // This metamorphic relation is only applicable for domestic flights with air
                                        // class 3
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(0, sourceOut, 1e-6);
    }

    /**
     * Metamorphic Relation 39: If area is not domestic, changing isStudent flag
     * should not affect the luggage fee
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        if (area == 1) // This relation only applies to non-domestic flights
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input: opposite of isStudent flag */
        boolean followIsStudent = !isStudent;

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, area, followIsStudent, luggage, economicfee);

        /* Verification */
        assertEquals(sourceOut, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 40: If the area and economic fee remain unchanged, and
     * the airClass is economy, the luggage fee should be consistent when isStudent
     * flag is changed
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        if (airClass != 3) // This relation only applies to flights with air class 'economy'
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input: opposite of isStudent flag */
        boolean followIsStudent = !isStudent;

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, area, followIsStudent, luggage, economicfee);

        /* Verification */
        assertEquals(sourceOut, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 41: If luggage weight is less than the benchmark, and
     * isStudent is true, the luggage fee should be consistent when the economic fee
     * is changed
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test41(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        if (luggage >= 40 || !isStudent) // This relation applies specifically when the luggage weight is less than the
                                         // benchmark and isStudent is true
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input: increased economic fee */
        double followEconomicFee = economicfee * 2;

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, followEconomicFee);

        /* Verification */
        assertEquals(sourceOut, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 42: If area, luggage, and economic fee are unchanged,
     * the luggage fee should be consistent when the airClass is changed
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test42(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        /* Get source output for current air class */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input: incremented air class */
        int followAirClass = airClass + 1;

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(followAirClass, area, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(sourceOut, followOut, 1e-6);
    }

    /**
     * Metamorphic Relation 43: If luggage weight is greater than the benchmark, the
     * luggage fee should be consistent when the area is changed
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test43(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        if (luggage <= 40) // This relation applies specifically when the luggage weight is greater than
                           // the benchmark
            return;

        /* Get source output for current area */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double sourceOut = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input: incremented area */
        int followArea = area + 1;

        /* Get follow-up output */
        double followOut = ACMS.feeCalculation(airClass, followArea, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(sourceOut, followOut, 1e-6);
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
