package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.util.stream.Stream;
import org.junit.jupiter.api.function.Executable;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import src.AirlinesBaggageBillingService;

public class ACMSTestGPT4 {
    /**
     * Metamorphic Relation 4: Doubling the economic fee should double the luggage fee when luggage
     * exceeds the benchmark weight.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(int airClass, int area, boolean isStudent, double luggage,
            double baseEconomicFee) {
        // Ensure the luggage exceeds the benchmark such that the fee is not zero
        double luggageBenchmark = 20; // Let's assume 20 is the benchmark for the test
        if (luggage <= luggageBenchmark)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out =
                ACMS.feeCalculation(airClass, area, isStudent, luggage, baseEconomicFee);

        /* Construct follow-up input */
        double follow_economicFee = baseEconomicFee * 2;

        /* Get follow-up output */
        double follow_out =
                ACMS.feeCalculation(airClass, area, isStudent, luggage, follow_economicFee);

        /* Verification */
        assertEquals(source_out * 2, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 5: If the economic fee is zero, the luggage fee should also be zero
     * regardless of luggage weight.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(int airClass, int area, boolean isStudent, double luggage) {
        /* Get source output with economic fee being zero */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, 0.0);

        /* Verification */
        assertEquals(0.0, source_out, 1e-6);
    }

    /**
     * Metamorphic Relation 6: If the luggage weight is equal to or less than the benchmark,
     * increasing the economic fee should not change the luggage fee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        double luggageBenchmark = 20; // Let's assume 20 is the benchmark for the test
        if (luggage > luggageBenchmark)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        double follow_economicFee = economicfee + 10.0; // Increase economic fee

        /* Get follow-up output */
        double follow_out =
                ACMS.feeCalculation(airClass, area, isStudent, luggage, follow_economicFee);

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 7: Given two air classes that result in the same normalized value, with
     * other parameters kept constant, the luggage fee should be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        int follow_airClass = airClass + 4; // Since normalization is airClass % 4

        /* Get follow-up output */
        double follow_out =
                ACMS.feeCalculation(follow_airClass, area, isStudent, luggage, economicfee);

        /* Verification */
        assertEquals(source_out, follow_out, 1e-6);
    }

    /**
     * Metamorphic Relation 8: If a student status results in a different luggage weight allowance,
     * toggling the student status should change the luggage fee when luggage exceeds the benchmark.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        double luggageBenchmark = 20; // Let's assume 20 is the benchmark for the test
        if (luggage <= luggageBenchmark)
            return;

        /* Assume student status changes the benchmark in some areas */
        boolean studentDiscountApplies = (area == 0); // Hypothetical condition for discount
        if (!studentDiscountApplies)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input toggling the student status */
        boolean follow_isStudent = !isStudent;

        /* Get follow-up output */
        double follow_out =
                ACMS.feeCalculation(airClass, area, follow_isStudent, luggage, economicfee);

        /* Verification */
        if (isStudent) {
            assertTrue(follow_out > source_out); // Fee should increase if student discount is
                                                 // removed
        } else {
            assertTrue(follow_out < source_out); // Fee should decrease if student discount is
                                                 // applied
        }
    }

    /**
     * Metamorphic Relation 9: If a non-student's luggage fee is calculated for a given weight, then
     * recalculating the fee for the same weight with student status should result in a fee that is
     * the same or lower, assuming student status can give benefits.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        // First test as non-student
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double nonStudentFee = ACMS.feeCalculation(airClass, area, false, luggage, economicfee);

        // Now test as a student
        double studentFee = ACMS.feeCalculation(airClass, area, true, luggage, economicfee);

        // Verify the student fee is not greater than the non-student fee
        assertTrue(studentFee <= nonStudentFee);
    }

    /**
     * Metamorphic Relation 10: Changing the air class by multiples of 4 should not affect the fee,
     * as the air class input is normalized with modulo 4.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double originalFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Change air class by a multiple of 4 (as per preairclass normalization)
        int newAirClass = airClass + (4 * 2); // Arbitrary multiple of 4

        double modifiedFee =
                ACMS.feeCalculation(newAirClass, area, isStudent, luggage, economicfee);

        // Verify fees should be equal since the air class input is normalized with modulo 4
        assertEquals(originalFee, modifiedFee, 1e-6);
    }

    /**
     * Metamorphic Relation 11: The luggage fee should be invariant to adding multiples of 2 to the
     * area, as it is normalized by modulo 2.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double originalFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Change area by a multiple of 2 (as per prearea normalization)
        int newArea = area + (2 * 3); // Arbitrary multiple of 2

        double modifiedFee =
                ACMS.feeCalculation(airClass, newArea, isStudent, luggage, economicfee);

        // Verify fees should be equal since the area input is normalized with modulo 2
        assertEquals(originalFee, modifiedFee, 1e-6);
    }

    /**
     * Metamorphic Relation 12: The luggage fee should not change when luggage weight is less than
     * or equal to the benchmark, regardless of student status.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        double luggageBenchmark = 20; // Let's assume the benchmark for the test
        if (luggage > luggageBenchmark)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double feeWithStudentStatus =
                ACMS.feeCalculation(airClass, area, true, luggage, economicfee);
        double feeWithoutStudentStatus =
                ACMS.feeCalculation(airClass, area, false, luggage, economicfee);

        // Verify the fees are the same when luggage is within the benchmark, irrespective of
        // student status
        assertEquals(feeWithStudentStatus, feeWithoutStudentStatus, 1e-6);
    }

    /**
     * Metamorphic Relation 13: If luggage weight is within the free allowance, any adjustment to
     * the base economic fee should not affect the calculated fee which should remain zero.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(int airClass, int area, boolean isStudent, double luggage) {
        // Assume the luggage is within the free allowance limit
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double originalFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, 10.0); // Arbitrary
                                                                                            // economic
                                                                                            // fee

        // Verify the fee should be zero
        assertEquals(0.0, originalFee, 1e-6);

        // Recalculate with a different economic fee rate
        double modifiedFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, 20.0); // Different
                                                                                            // arbitrary
                                                                                            // fee

        // Verify the fee should still be zero
        assertEquals(0.0, modifiedFee, 1e-6);
    }

    /**
     * Metamorphic Relation 14: If we keep everything constant except for the luggage weight, which
     * we reduce by a certain amount that still exceeds the benchmark, the fee should be
     * proportionately less by that amount multiplied by the base economic fee and the factor of
     * 0.015.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        // Ensure initial luggage exceeds benchmark for fee to be applied
        double luggageBenchmark = 20; // Hypothetical benchmark, this should ideally come from the
                                      // business rule or be calculated
        if (luggage <= luggageBenchmark)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double originalFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Deduct an amount from the luggage weight that still results in excess weight
        double weightDeduction = 5; // Assure this does not make luggage fall below benchmark
        double newLuggageWeight = luggage - weightDeduction;
        if (newLuggageWeight <= luggageBenchmark)
            return;

        double newFee =
                ACMS.feeCalculation(airClass, area, isStudent, newLuggageWeight, economicfee);

        // Verify that the fee is reduced correctly
        double feeDeduction = weightDeduction * economicfee * 0.015;
        assertEquals(originalFee - feeDeduction, newFee, 1e-6);
    }

    /**
     * Metamorphic Relation 15: If the base economic fee is reduced by a certain percentage, the
     * luggage fee for weight exceeding the benchmark should be reduced by the same percentage.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        // Ensure initial luggage exceeds benchmark for fee to be applied
        double luggageBenchmark = 20; // Hypothetical benchmark, this should ideally come from the
                                      // business rule or be calculated
        if (luggage <= luggageBenchmark)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double originalFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Reduce economic fee by a certain percentage
        double feeReductionPercentage = 0.1; // 10% reduction
        double reducedEconomicFee = economicfee * (1 - feeReductionPercentage);
        double reducedFee =
                ACMS.feeCalculation(airClass, area, isStudent, luggage, reducedEconomicFee);

        // Verify the luggage fee is reduced by the same percentage
        double expectedReducedFee = originalFee * (1 - feeReductionPercentage);
        assertEquals(expectedReducedFee, reducedFee, 1e-6);
    }

    /**
     * Metamorphic Relation 16: Adding a piece of luggage that does not exceed the benchmark to
     * existing luggage should not change the fee, assuming the total still does not exceed the
     * benchmark.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        // Start with luggage weight that does not exceed the benchmark
        double luggageBenchmark = 20; // Hypothetical benchmark, this should ideally come from the
                                      // business rule or be calculated
        if (luggage > luggageBenchmark)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double originalFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Add more luggage that still does not exceed the benchmark
        double additionalLuggage = 5;
        double newLuggageWeight = luggage + additionalLuggage;
        if (newLuggageWeight > luggageBenchmark)
            return;

        double newFee =
                ACMS.feeCalculation(airClass, area, isStudent, newLuggageWeight, economicfee);

        // Verify the fee has not changed
        assertEquals(originalFee, newFee, 1e-6);
    }

    /**
     * Metamorphic Relation 17: If the luggage weight is less than the benchmark and the economic
     * fee increases, the luggage fee should remain the same since the luggage weight doesn't exceed
     * the benchmark.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        double luggageBenchmark = 20; // Hypothetical benchmark, should be obtained from actual
                                      // business rules
        if (luggage > luggageBenchmark)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double originalFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Increase economic fee
        double increasedEconomicFee = economicfee + 10.0;
        double newFee =
                ACMS.feeCalculation(airClass, area, isStudent, luggage, increasedEconomicFee);

        // Verify the fee does not change
        assertEquals(originalFee, newFee, 1e-6);
    }

    /**
     * Metamorphic Relation 18: For luggage that exceeds the benchmark, if both the luggage weight
     * and economic fee are doubled, the luggage fee should also be doubled.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        double luggageBenchmark = 20; // Hypothetical benchmark, should be obtained from actual
                                      // business rules
        if (luggage <= luggageBenchmark)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double originalFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Double luggage weight and economic fee
        double newLuggage = luggage * 2;
        double newEconomicFee = economicfee * 2;
        double newFee = ACMS.feeCalculation(airClass, area, isStudent, newLuggage, newEconomicFee);

        // Verify the new fee is double the original fee
        assertEquals(2 * originalFee, newFee, 1e-6);
    }

    /**
     * Metamorphic Relation 19: If the luggage weight equals the benchmark, and we incrementally
     * increase the luggage weight just above the benchmark, the fee should start to be applied and
     * increase in a linear manner based on the additional weight.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        double luggageBenchmark = 20; // Hypothetical benchmark, should be obtained from actual
                                      // business rules
        if (luggage != luggageBenchmark)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();

        // Calculate fee with luggage exactly at benchmark (expected to be zero)
        double originalFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Slightly increase luggage so it is just above the benchmark
        double slightIncrease = 1.0; // Small increase to exceed the benchmark
        double newLuggage = luggageBenchmark + slightIncrease;
        double newFee = ACMS.feeCalculation(airClass, area, isStudent, newLuggage, economicfee);

        // Fee should now be calculated as slightIncrease * economicfee * 0.015 as per
        // the fee calculation logic provided in the specification
        double expectedFee = slightIncrease * economicfee * 0.015;

        // Verify that the fee increases linearly once the luggage exceeds the benchmark
        assertEquals(expectedFee, newFee, 1e-6);
        assertTrue(newFee > originalFee);
    }

    /**
     * Metamorphic Relation 20: For the same flight and luggage, students should have the same or a
     * lower fee than non-students, assuming student discounts are available for the area.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(int airClass, int area, boolean isStudent, double luggage, double economicfee) {
        // Logic here assumes students might only get discounts in certain areas
        boolean studentDiscountApplies = (area == 0); // Hypothetical discount application condition
        if (!studentDiscountApplies)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double feeForNonStudent = ACMS.feeCalculation(airClass, area, false, luggage, economicfee);
        double feeForStudent = ACMS.feeCalculation(airClass, area, true, luggage, economicfee);

        // Verify that the fee for a student is the same or less than that of a non-student
        assertTrue(feeForStudent <= feeForNonStudent);
    }

    /**
     * Metamorphic Relation 21: For any luggage weight, if the input parameters of airClass and area
     * return the same normalized values, the resulting fee should be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        // First calculate the fee with the given parameters
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double originalFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Calculate the normalized values to construct equivalent inputs
        int equivalentAirClass = (airClass % 4) + 4; // The same normalized value
        int equivalentArea = (area % 2) + 2; // The same normalized value

        // Recalculate the fee with the equivalent inputs
        double equivalentFee = ACMS.feeCalculation(equivalentAirClass, equivalentArea, isStudent,
                luggage, economicfee);

        // The fee should be the same since the normalized inputs are the same
        assertEquals(originalFee, equivalentFee, 1e-6);
    }

    /**
     * Metamorphic Relation 22: If the economic fee is negative, the resulting fee calculation
     * should be considered invalid, and an exception is expected to be thrown or fee should be zero
     * according to behavior.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(int airClass, int area, boolean isStudent, double luggage) {
        // We do not support negative fees, thus an exception or another form of error handling is
        // expected
        double negativeEconomicFee = -10.0; // Negative base economic fee

        // Attempt to calculate the fee with the negative economic fee
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        Executable feeCalculationExecutable =
                () -> ACMS.feeCalculation(airClass, area, isStudent, luggage, negativeEconomicFee);

        // Verify that an exception is thrown or fee should be zero according to behavior
        // This assumes the business logic dictates that negative fees are invalid and an exception
        // is thrown.
        assertThrows(IllegalArgumentException.class, feeCalculationExecutable);
        // Alternatively, if the logic states that the fee should be 0 in case of negative economic
        // fee:
        // double feeWithNegativeEconomic = ACMS.feeCalculation(airClass, area, isStudent, luggage,
        // negativeEconomicFee);
        // assertEquals(0.0, feeWithNegativeEconomic, 1e-6);
    }

    /**
     * Metamorphic Relation 23: Increasing or decreasing the luggage weight by a value that is less
     * than the allowed benchmark should not change the fee, provided the final weight is still
     * within the allowance.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        double luggageBenchmark = 20; // Hypothetical benchmark for a given air class and area
        if (luggage > luggageBenchmark)
            return;

        // Calculate the fee for the original luggage weight
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double originalFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Adjust the luggage weight just within the benchmark
        double adjustment = 5; // Adjust by 5 units
        double adjustedLuggageWeight =
                luggage + adjustment > luggageBenchmark ? luggageBenchmark : luggage + adjustment;

        // Calculate the fee for the adjusted luggage weight
        double adjustedFee =
                ACMS.feeCalculation(airClass, area, isStudent, adjustedLuggageWeight, economicfee);

        // Verify that the fee has not changed
        assertEquals(originalFee, adjustedFee, 1e-6);
    }

    /**
     * Metamorphic Relation 24: If luggage weight is within the allowance, changing the student
     * status should not have any effect on the fee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        double luggageBenchmark = 20; // Hypothetical benchmark for a given air class and area
        if (luggage > luggageBenchmark)
            return;

        // Calculate the fee for a student
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double feeAsStudent = ACMS.feeCalculation(airClass, area, true, luggage, economicfee);

        // Calculate the fee for a non-student
        double feeAsNonStudent = ACMS.feeCalculation(airClass, area, false, luggage, economicfee);

        // Verify that both fees are the same since the luggage weight is within the allowance
        assertEquals(feeAsStudent, feeAsNonStudent, 1e-6);
    }

    /**
     * Metamorphic Relation 25: The luggage fee should be invariant to air classes that are
     * equivalent modulo the pre-processing step, which normalizes airClass by airClass % 4.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double originalFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Find an equivalent airClass after the modulus operation
        int equivalentAirClass = (airClass % 4) + 4 * 3; // Adding 3 times the modulus base to
                                                         // ensure it's different but equivalent
                                                         // after pre-processing

        // Calculate fee with an equivalent airClass
        double newFee =
                ACMS.feeCalculation(equivalentAirClass, area, isStudent, luggage, economicfee);

        // Verify that the fees are equivalent since the pre-processed airClass should match
        assertEquals(originalFee, newFee, 1e-6);
    }

    /**
     * Metamorphic Relation 26: Doubling the base economic fee rate while halving the luggage weight
     * that is above the benchmark should result in the same luggage fee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        double luggageBenchmark = 20; // Hypothetical benchmark, should be obtained from actual
                                      // business rules
        if (luggage <= luggageBenchmark)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double excessWeight = luggage - luggageBenchmark;
        double originalFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Halve the luggage weight above the benchmark and double the economic fee
        double newLuggage = luggageBenchmark + (excessWeight / 2);
        double newEconomicFee = economicfee * 2;

        double newFee = ACMS.feeCalculation(airClass, area, isStudent, newLuggage, newEconomicFee);

        // Verify that the fees are equivalent
        assertEquals(originalFee, newFee, 1e-6);
    }

    /**
     * Metamorphic Relation 27: For any fixed luggage weight, fees should increase or stay the same
     * as air class level increases because a higher class is likely to have a higher luggage
     * allowance.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        // Assume airClass corresponds to specific allowance levels
        if (airClass >= 3) // Assuming we have 4 air classes (0-3)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double lowerClassFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Calculate fee for a higher air class
        int higherAirClass = airClass + 1;
        double higherClassFee =
                ACMS.feeCalculation(higherAirClass, area, isStudent, luggage, economicfee);

        // Verify that the fee increases or stays the same with higher air class
        assertTrue(higherClassFee >= lowerClassFee);
    }

    /**
     * Metamorphic Relation 28: When reducing luggage weight from a weight that incurs a fee to a
     * weight that does not incur a fee, the luggage fee should change from a positive value to
     * zero.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        double luggageBenchmark = 20; // Hypothetical benchmark for the test
        if (luggage <= luggageBenchmark)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double feeWithExcessWeight =
                ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Reduce luggage weight to below the benchmark
        double newLuggageWeight = luggageBenchmark * 0.9; // 10% reduction to ensure it's below the
                                                          // benchmark

        double feeWithReducedWeight =
                ACMS.feeCalculation(airClass, area, isStudent, newLuggageWeight, economicfee);

        // Verify that the fee has changed from a positive value to zero
        assertTrue(feeWithExcessWeight > 0);
        assertEquals(0.0, feeWithReducedWeight, 1e-6);
    }

    /**
     * Metamorphic Relation 29: For any luggage weight below the benchmark, incurring no fee,
     * switching geographic areas should not result in a fee provided that the areas have the same
     * luggage allowance policies.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        double luggageBenchmark = 20; // Hypothetical benchmark for the test
        if (luggage > luggageBenchmark)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double originalFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Change to a different area that has an equivalent allowance policy (same modulo 2 result)
        int newArea = (area == 0) ? 1 : 0;

        double newAreaFee = ACMS.feeCalculation(airClass, newArea, isStudent, luggage, economicfee);

        // Verify that no fee is incurred in the new area, assuming identical luggage allowance
        // policies
        assertEquals(0.0, newAreaFee, 1e-6);
        assertEquals(originalFee, newAreaFee, 1e-6);
    }

    /**
     * Metamorphic Relation 30: If the base economic fee changes, but the luggage weight is such
     * that no fee should be incurred, the final luggage fee should always stay the same (presumably
     * zero).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        double luggageBenchmark = 20; // Hypothetical benchmark for the test
        if (luggage > luggageBenchmark)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double originalFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Change the economic fee
        double newEconomicFee = economicfee * 1.5; // Increase by 50%

        double newFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, newEconomicFee);

        // Verify that the fees are the same since no fee should be incurred for luggage within the
        // benchmark
        assertEquals(originalFee, newFee, 1e-6);
    }

    /**
     * Metamorphic Relation 31: If the luggage weight is at the benchmark and we add a small weight
     * that does not lead to exceeding the benchmark after normalization, the fee should remain the
     * same (i.e., it should be zero if just at the benchmark).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        // Assuming the function has internally defined a benchmark weight, for testing purposes we
        // set 20 units
        double luggageBenchmark = 20; // Hypothetical benchmark for the test
        if (luggage != luggageBenchmark)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double originalFee =
                ACMS.feeCalculation(airClass, area, isStudent, luggageBenchmark, economicfee);

        // Adjust luggage weight by a small amount (e.g., rounding errors)
        double adjustedWeight = luggageBenchmark + 0.01;
        double adjustedFee =
                ACMS.feeCalculation(airClass, area, isStudent, adjustedWeight, economicfee);

        // Verify that the fee has not changed
        assertEquals(originalFee, adjustedFee, 1e-6);
    }

    /**
     * Metamorphic Relation 32: Switching between different areas that have the same modulo value
     * for pre-processing should not change the calculated fee if all other parameters are held
     * static.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double originalFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Change area code to another that has the same normalized value (e.g., area % 2 gives the
        // same result)
        int equivalentArea = (area + 2) % 2; // Assumes only two values for area after normalization

        double equivalentFee =
                ACMS.feeCalculation(airClass, equivalentArea, isStudent, luggage, economicfee);

        // Verify that the fees are equivalent
        assertEquals(originalFee, equivalentFee, 1e-6);
    }

    /**
     * Metamorphic Relation 33: Since the luggage fee is calculated linearly based on the difference
     * between actual luggage weight and the benchmark, if the luggage weight and benchmark weight
     * are both doubled, the fee should also double.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        // Assuming 20 units is the benchmark weight
        double luggageBenchmark = 20; // Hypothetical benchmark for the test
        if (luggage <= luggageBenchmark)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double originalFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        double doubledLuggage = luggage * 2;
        double doubledBenchmark = luggageBenchmark * 2;
        double adjustedFee =
                ACMS.feeCalculation(airClass, area, isStudent, doubledLuggage, economicfee);

        // Expect the fee to double as the excess weight is also doubled
        assertEquals(2 * originalFee, adjustedFee, 1e-6);
    }

    /**
     * Metamorphic Relation 34: A zero or negative luggage weight should result in zero fee, as it
     * does not make sense to charge for non-existent or conceptually "negative" luggage.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(int airClass, int area, boolean isStudent, double economicfee) {
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();

        // Check for zero luggage weight
        double feeForZeroLuggage = ACMS.feeCalculation(airClass, area, isStudent, 0.0, economicfee);
        assertEquals(0.0, feeForZeroLuggage, 1e-6);

        // Check for negative luggage weight
        double feeForNegativeLuggage =
                ACMS.feeCalculation(airClass, area, isStudent, -1.0, economicfee);
        assertEquals(0.0, feeForNegativeLuggage, 1e-6);
    }

    /**
     * Metamorphic Relation 35: If the luggage weight before and after an incremental increase
     * remains under the benchmark, there should not be any difference in the fee calculated.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        double luggageBenchmark = 20; // Hypothetical benchmark for the test
        if (luggage >= luggageBenchmark)
            return;

        double increment = 1.0; // Increment that keeps the total luggage under the benchmark
        if (luggage + increment >= luggageBenchmark)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double initialFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);
        double incrementedFee =
                ACMS.feeCalculation(airClass, area, isStudent, luggage + increment, economicfee);

        // Verify there's no change in fee after increment
        assertEquals(initialFee, incrementedFee, 1e-6);
    }

    /**
     * Metamorphic Relation 36: If a follow-up luggage weight is reduced to be within the free
     * allowance limit from an original weight that exceeded the limit, the fee for the follow-up
     * test case should be zero.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        double luggageBenchmark = 20; // Hypothetical benchmark for the test
        if (luggage <= luggageBenchmark)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double feeWithExcessLuggage =
                ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Reduce luggage to be within the free allowance limit
        double reducedLuggage = luggageBenchmark - 1; // Ensure it's under the benchmark
        double feeWithReducedLuggage =
                ACMS.feeCalculation(airClass, area, isStudent, reducedLuggage, economicfee);

        // The fee for reduced luggage should be zero
        assertEquals(0.0, feeWithReducedLuggage, 1e-6);
        assertTrue(feeWithExcessLuggage > feeWithReducedLuggage);
    }

    /**
     * Metamorphic Relation 37: Tripling the luggage weight that exceeds the benchmark should triple
     * the calculated fee, given a linear fee calculation.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        double luggageBenchmark = 20; // Hypothetical benchmark for the test
        if (luggage <= luggageBenchmark)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double originalFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Triple the luggage weight
        double tripledLuggage = luggage * 3;
        double tripledFee =
                ACMS.feeCalculation(airClass, area, isStudent, tripledLuggage, economicfee);

        // Expect the fee to triple since the excess weight is also tripled
        assertEquals(3 * originalFee, tripledFee, 1e-6);
    }

    /**
     * Metamorphic Relation 38: If the additional weight over the allowance is partitioned across
     * two luggage items, the total fee should equal the fee if the weight were calculated as one.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        double luggageBenchmark = 20; // Hypothetical benchmark for the test
        if (luggage <= luggageBenchmark)
            return;

        // Assume each luggage is charged separately
        double excessWeight = luggage - luggageBenchmark;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double originalFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Split the excess weight across two luggage items
        double halfExcessWeight = excessWeight / 2;
        double firstLuggage = luggageBenchmark + halfExcessWeight;
        double secondLuggage = luggageBenchmark + halfExcessWeight;
        double firstFee = ACMS.feeCalculation(airClass, area, isStudent, firstLuggage, economicfee);
        double secondFee =
                ACMS.feeCalculation(airClass, area, isStudent, secondLuggage, economicfee);

        // Combine fees from the two items
        double combinedFee = firstFee + secondFee;

        // Verify combined fee is equal to the original fee
        assertEquals(originalFee, combinedFee, 1e-6);
    }

    /**
     * Metamorphic Relation 39: If the economic fee is increased by a fixed percentage, the computed
     * fee for luggage exceeding the benchmark should increase by the same percentage.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        double luggageBenchmark = 20; // Hypothetical benchmark for the test
        if (luggage <= luggageBenchmark)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double originalFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Increase the economic fee by a fixed percentage (let's say 20%)
        double increasePercentage = 0.2;
        double increasedEconomicFee = economicfee * (1 + increasePercentage);
        double increasedFee =
                ACMS.feeCalculation(airClass, area, isStudent, luggage, increasedEconomicFee);

        // The increased fee should be 20% higher than the original fee
        assertEquals(originalFee * (1 + increasePercentage), increasedFee, 1e-6);
    }

    /**
     * Metamorphic Relation 40: Changing the order of processing multiple luggage pieces should not
     * affect the total luggage fee calculation, assuming the fees are calculated per piece and then
     * summed.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(int airClass, int area, boolean isStudent, double economicfee) {
        double luggageBenchmark = 20; // Hypothetical benchmark for the test

        // Define two pieces of luggage that will exceed the benchmark when combined
        double luggage1 = luggageBenchmark + 5;
        double luggage2 = luggageBenchmark + 10;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double feeFirstOrder1 =
                ACMS.feeCalculation(airClass, area, isStudent, luggage1, economicfee);
        double feeFirstOrder2 =
                ACMS.feeCalculation(airClass, area, isStudent, luggage2, economicfee);
        double totalFeeFirstOrder = feeFirstOrder1 + feeFirstOrder2;

        // Calculate fees in reverse order
        double feeSecondOrder1 =
                ACMS.feeCalculation(airClass, area, isStudent, luggage2, economicfee);
        double feeSecondOrder2 =
                ACMS.feeCalculation(airClass, area, isStudent, luggage1, economicfee);
        double totalFeeSecondOrder = feeSecondOrder1 + feeSecondOrder2;

        // Total fees should be equal regardless of the order
        assertEquals(totalFeeFirstOrder, totalFeeSecondOrder, 1e-6);
    }

    /**
     * Metamorphic Relation 41: If the luggage weight is well below the benchmark such that no fee
     * is applied, then changing the isStudent flag should not affect the resulting fee, which
     * should remain zero.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test41(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        double luggageBenchmark = 15; // Assume a lower benchmark for this test
        if (luggage >= luggageBenchmark)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double feeForNonStudent = ACMS.feeCalculation(airClass, area, false, luggage, economicfee);
        double feeForStudent = ACMS.feeCalculation(airClass, area, true, luggage, economicfee);

        // Since no fee is applied for both cases, fees should be identical and equal to zero
        assertEquals(feeForNonStudent, feeForStudent);
        assertEquals(0.0, feeForNonStudent, 1e-6);
    }

    /**
     * Metamorphic Relation 42: Changing the base economic fee by a constant amount should not
     * affect the fee calculation for luggage that is below or at the benchmark weight.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test42(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        double luggageBenchmark = 20; // Hypothetical benchmark for the test
        if (luggage > luggageBenchmark)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double initialFee = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        // Increase the economic fee by a constant amount
        double feeIncrease = 5.0;
        double increasedEconomicFee = economicfee + feeIncrease;
        double feeWithIncreasedEconomic =
                ACMS.feeCalculation(airClass, area, isStudent, luggage, increasedEconomicFee);

        // Verify the fee remains the same (expected zero)
        assertEquals(initialFee, feeWithIncreasedEconomic, 1e-6);
    }

    /**
     * Metamorphic Relation 43: For a passenger with no student status, applying a student discount
     * after recalculating should not increase the fee and should only decrease or maintain the same
     * fee if the luggage weight exceeds the allowance and student discounts are applicable to the
     * area.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test43(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        if (isStudent)
            return; // Test is only valid for non-student to student comparison

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double feeForNonStudent = ACMS.feeCalculation(airClass, area, false, luggage, economicfee);
        double feeForStudent = ACMS.feeCalculation(airClass, area, true, luggage, economicfee);

        // If student discounts are applicable, fee for students should be less or equal
        assertTrue(feeForStudent <= feeForNonStudent);
    }

    /**
     * Metamorphic Relation 44: For two pieces of luggage where neither exceed the benchmark
     * individually, the total fee for both should be no different than for each piece alone if
     * processed separately.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test44(int airClass, int area, boolean isStudent, double economicfee) {
        double luggageBenchmark = 20; // Hypothetical benchmark for the test
        double luggage1 = luggageBenchmark - 5; // Both luggages are under the benchmark
        double luggage2 = luggageBenchmark - 10;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double feeForLuggage1 =
                ACMS.feeCalculation(airClass, area, isStudent, luggage1, economicfee);
        double feeForLuggage2 =
                ACMS.feeCalculation(airClass, area, isStudent, luggage2, economicfee);

        // Both should be zero, and the sum should also be zero
        assertEquals(feeForLuggage1, 0.0, 1e-6);
        assertEquals(feeForLuggage2, 0.0, 1e-6);
        assertEquals(feeForLuggage1 + feeForLuggage2, 0.0, 1e-6);
    }

    /**
     * Metamorphic Relation 45: If a luggage is exactly at the weight benchmark and another test
     * with the same luggage with an added negligible weight (still within a reasonable threshold of
     * the benchmark) should result in the same fee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test45(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        double luggageBenchmark = 20; // Hypothetical benchmark for the test
        if (luggage != luggageBenchmark)
            return;

        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double baseFee =
                ACMS.feeCalculation(airClass, area, isStudent, luggageBenchmark, economicfee);

        double negligibleWeight = 0.5; // Assume this weight is negligible and doesn't affect the
                                       // benchmark
        double feeWithNegligibleAddition = ACMS.feeCalculation(airClass, area, isStudent,
                luggageBenchmark + negligibleWeight, economicfee);

        assertEquals(baseFee, feeWithNegligibleAddition, 1e-6);
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
