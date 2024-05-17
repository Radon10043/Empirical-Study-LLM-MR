package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.util.Random;
import java.util.stream.Stream;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import src.BillCalculation;

public class CUBSGPT4Test {

    /**
     * Metamorphic Relation 1: Changing the case of planType should not change the
     * output (since
     * it's case-insensitive).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testChangingPlanTypeCase(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input by changing the case of planType */
        String follow_planType = planType.equalsIgnoreCase("A") ? "a" : "b";

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(follow_planType, planFee, talkTime, flow);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 2: For the same planType, if the flow increases without
     * exceeding the bench value, then the bill should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testSameFlowUnderBench(String planType, int planFee, int talkTime, int flow) { // Fixed
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input with increased flow but under the bench value */
        // Assuming that bench values are accessible or can be estimated
        int benchFlow = CUBS.getFlowBench(); // Placeholder, actual value needed
        if (flow < benchFlow) {
            int follow_flow = flow + 1; // Still under the bench

            /* Get follow-up output */
            double follow_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, follow_flow);

            /* Verification */
            assertEquals(source_out, follow_out);
        }
    }

    /**
     * Metamorphic Relation 3: If the flow increases beyond the benchmark, the bill
     * should increase as per flowPer rate.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testIncreasedFlowOverBench(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input with increased flow beyond the bench value */
        // Assuming that bench values and per-extra-mb rate are accessible or can be
        // estimated
        int benchFlow = CUBS.getFlowBench(); // Placeholder, actual value needed
        double flowPerRate = CUBS.getFlowPer(); // Placeholder, actual value needed
        if (flow > benchFlow) {
            int additionalFlow = 1; // Increase by 1 MB to incur extra charge
            int follow_flow = flow + additionalFlow; // Should exceed the bench

            /* Get follow-up output */
            double follow_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, follow_flow);

            /* Verification */
            double expected_increase = additionalFlow * flowPerRate;
            assertEquals(source_out + expected_increase, follow_out);
        }
    }

    /**
     * Metamorphic Relation 4: If the same input is used, the output must be
     * identical (idempotency property).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testIdempotentBehavior(String planType, int planFee, int talkTime, int flow) { // Fixed
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double first_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Get follow-up output using the same input */
        double second_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Verification */
        assertEquals(first_out, second_out);
    }

    /**
     * Metamorphic Relation 5: Doubling the talkTime and data usage should double
     * the charges for those units only if they exceed the benchmarks.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testDoubleUsageExceedingBenchmarks(String planType, int planFee, int talkTime, int flow) { // Fixed
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Get source output */
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int double_talkTime = talkTime * 2;
        int double_flow = flow * 2;

        /* Calculating the expected additional charges */
        // Assuming bench values and rates are accessible or can be estimated
        int talkTimeBench = CUBS.getTalkTimeBench(); // Placeholder, actual value needed
        double talkTimeRate = CUBS.getTalkTimePer(); // Placeholder, actual value needed
        int flowBench = CUBS.getFlowBench(); // Placeholder, actual value needed
        double flowRate = CUBS.getFlowPer(); // Placeholder, actual value needed

        double expected_additional_talkTime_cost = (talkTime > talkTimeBench)
                ? (double_talkTime - talkTimeBench) * talkTimeRate
                : 0;
        double expected_additional_flow_cost = (flow > flowBench) ? (double_flow - flowBench) * flowRate : 0;

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, planFee, double_talkTime, double_flow);

        /* Verification */
        double expected_out = source_out + expected_additional_talkTime_cost + expected_additional_flow_cost;
        assertEquals(expected_out, follow_out);
    }

    /**
     * Metamorphic Relation 6: Increasing planFee within the same planType should
     * not decrease benchmarks and subsequently should not reduce the bill if usage
     * exceeds benchmarks.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testIncreasedPlanFee(String planType, int planFee, int talkTime, int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Get source output */
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input with increased planFee */
        int increased_planFee = planFee + 10;

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, increased_planFee, talkTime, flow);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 7: If planType remains the same and talkTime and data
     * usage are within their benchmarks, increasing the planFee alone should
     * increase the bill by exactly the planFee difference.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testPlanFeeIncreaseWithinBenchmark(String planType, int planFee, int talkTime, int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Get source output */
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int increased_planFee = planFee + 10;

        /* Assuming benchmarks are known or can be deduced */
        int talkTimeBench = CUBS.getTalkTimeBench(); // Placeholder, actual value needed
        int flowBench = CUBS.getFlowBench(); // Placeholder, actual value needed

        if (talkTime <= talkTimeBench && flow <= flowBench) {
            /* Get follow-up output */
            double follow_out = CUBS.phoneBillCalculation(planType, increased_planFee, talkTime, flow);

            /* Verification */
            assertEquals(source_out + 10, follow_out);
        }
    }

    /**
     * Metamorphic Relation 8: Swapping planTypes A and B with same usage and
     * planFee should not lead to the same bill if rate structures are different.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testSwappingPlanTypes(String planType, int planFee, int talkTime, int flow) {
        /* Only apply this test if planType is either A or B */
        if (!planType.equalsIgnoreCase("A") && !planType.equalsIgnoreCase("B")) {
            return;
        }

        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Get source output for planType A */
        double source_out_A = CUBS.phoneBillCalculation("A", planFee, talkTime, flow);

        /* Get source output for planType B */
        double source_out_B = CUBS.phoneBillCalculation("B", planFee, talkTime, flow);

        /* Verification */
        assertNotEquals(source_out_A, source_out_B);
    }

    /**
     * Metamorphic Relation 9: For a fixed planType and planFee, increasing both
     * talkTime and flow proportionally beyond benchmarks should increase the bill
     * linearly according to talkTimePer and flowPer rates.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testProportionalIncreaseBeyondBenchmarks(String planType, int planFee, int talkTime, int flow) { // Fixed
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Get source output */
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input with increased talkTime and flow */
        int increased_talkTime = talkTime + 50; // Increase by 50 minutes
        int increased_flow = flow + 200; // Increase by 200 MB

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, planFee, increased_talkTime, increased_flow);

        /* Verification */
        // Assuming rate information is available (placeholders used here)
        int talkTimeBench = CUBS.getTalkTimeBench(); // Placeholder, actual value needed
        double talkTimeRate = CUBS.getTalkTimeBench(); // Placeholder, actual value needed
        int flowBench = CUBS.getFlowBench(); // Placeholder, actual value needed
        double flowRate = CUBS.getFlowPer(); // Placeholder, actual value needed

        double expected_talkTime_cost = ((increased_talkTime > talkTimeBench)
                ? (increased_talkTime - talkTimeBench) * talkTimeRate
                : 0);
        double expected_flow_cost = ((increased_flow > flowBench) ? (increased_flow - flowBench) * flowRate : 0);
        double expected_additional_cost = expected_talkTime_cost + expected_flow_cost;

        assertEquals(source_out + expected_additional_cost, follow_out);
    }

    /**
     * Metamorphic Relation 10: If the planType is changed with the same talkTime
     * and flow within benchmarks, the difference in bill should only be based on
     * the difference in base planFee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testPlanTypeChangeWithinBenchmarks(String planType, int planFee, int talkTime, int flow) { // Fixed
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        int planFeePlanA = 0;
        int planFeePlanB = 0;

        /* Assuming we have only two plan types: A and B */
        String oppositePlanType = planType.equalsIgnoreCase("A") ? "B" : "A";

        /* Get source output */
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        if (planType.equalsIgnoreCase("A")) {
            planFeePlanA = planFee;
        } else {
            planFeePlanB = planFee;
        }

        /* Get follow-up output with different planType */
        double follow_out = CUBS.phoneBillCalculation(oppositePlanType, planFee, talkTime, flow);

        /* Verify that the difference in bill is based on the difference in planFee */
        if (oppositePlanType.equalsIgnoreCase("A")) {
            planFeePlanA = planFee;
        } else {
            planFeePlanB = planFee;
        }
        double expected_difference = (planType.equalsIgnoreCase("A") ? planFeePlanB - planFeePlanA
                : planFeePlanA - planFeePlanB);

        assertEquals(Math.abs(follow_out - source_out), expected_difference);
    }

    /**
     * Metamorphic Relation 11: For invalid planType or planFee inputs, the program
     * should not compute a higher bill than the highest possible valid planFee,
     * since it does not handle exceptions correctly.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testInvalidInputs(String planType, int planFee, int talkTime, int flow) {
        // /* Instantiate the object to test */
        // BillCalculation CUBS = new BillCalculation();

        // /* Get output for invalid input */
        // double invalid_out = CUBS.phoneBillCalculation("InvalidType", planFee,
        // talkTime, flow);

        // /* Verify that the bill does not exceed the highest valid planFee */
        // int highestValidPlanFee = ...; // Placeholder for the highest valid plan fee

        // assertTrue(invalid_out <= highestValidPlanFee);
    }

    /**
     * Metamorphic Relation 12: Increasing talkTime and flow but keeping total cost
     * per unit constant (by modifying planFee or assuming unit rates) should result
     * in a linearly scaled bill.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testLinearScalingWithConstantCostPerUnit(String planType, int planFee, int talkTime,
            int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Get source output */
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Specify the scale factor */
        double scaleFactor = 1.5; // Arbitrary scale factor

        /* Construct follow-up input with increased talkTime and flow */
        int scaled_talkTime = (int) (talkTime * scaleFactor);
        int scaled_flow = (int) (flow * scaleFactor);

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, planFee, scaled_talkTime, scaled_flow);

        /* Calculate expected output */
        double expected_output = source_out * scaleFactor;

        assertEquals(expected_output, follow_out, 0.01); // Allowing a small error margin for
                                                         // floating point calculations
    }

    /**
     * Metamorphic Relation 13: Regardless of talkTime and flow, for the same
     * planType if planFee is the same, the resulting bill should also be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testBillEqualityWithSamePlanFee(String planType, int planFee, int talkTime,
            int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Get source output */
        double originalBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Get output with varying talkTime and flow but same planFee */
        double newBillWithSamePlanFee = CUBS.phoneBillCalculation(planType, planFee, talkTime + 100, flow + 500);

        /* Verification that the bill is the same since planFee is the same */
        assertEquals(originalBill, newBillWithSamePlanFee);
    }

    /**
     * Metamorphic Relation 14: For the same planType and planFee, swapping the
     * values of talkTime and flow while keeping the sum constant should not affect
     * the bill if the sum is within benchmarks.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testSwapTalkTimeAndFlowWithConstantSum(String planType, int planFee, int talkTime, int flow) {
        /*
         * Sum preservation assumes the cost rate per minute equals the cost rate per
         * MB.
         */

        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Get source output */
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Assuming benchmarks are known or can be deduced */
        int talkTimeBench = CUBS.getTalkTimeBench(); // Placeholder, actual value needed
        int flowBench = CUBS.getFlowBench(); // Placeholder, actual value needed

        /* Only perform this MR if the total talkTime and flow are within benchmarks */
        if (talkTime + flow <= talkTimeBench + flowBench) {

            /* Swap talkTime and flow while keeping the sum constant */
            int newTalkTime = flow;
            int newFlow = talkTime;

            /* Get follow-up output */
            double follow_out = CUBS.phoneBillCalculation(planType, planFee, newTalkTime, newFlow);

            /* Verification */
            assertEquals(source_out, follow_out);
        }
    }

    /**
     * Metamorphic Relation 15: Increasing only talkTime or only flow while keeping
     * the other parameter constant should not decrease the bill.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testIncreaseInOnlyOneParameter(String planType, int planFee, int talkTime,
            int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Increase talkTime only */
        /* Get source output */
        double originalBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);
        /* Get follow-up output with increased talkTime */
        double updatedBillWithIncreasedTalkTime = CUBS.phoneBillCalculation(planType, planFee, talkTime + 50, flow);
        /* Verification */
        assertTrue(updatedBillWithIncreasedTalkTime >= originalBill);

        /* Increase flow only */
        /* Get follow-up output with increased flow */
        double updatedBillWithIncreasedFlow = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow + 500);
        /* Verification */
        assertTrue(updatedBillWithIncreasedFlow >= originalBill);
    }

    /**
     * Metamorphic Relation 16: If planFee is zero and talkTime and flow are within
     * their free benchmarks, then the bill should also be zero.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testZeroBillForZeroPlanFeeWithinBenchmarks(String planType, int planFee, int talkTime, int flow) { // Fixed
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Assuming benchmarks are known or can be deduced */
        int talkTimeBench = CUBS.getTalkTimeBench(); // Placeholder, actual value needed
        int flowBench = CUBS.getFlowBench(); // Placeholder, actual value needed

        /* Check if talkTime and flow do not exceed benchmarks */
        if (talkTime <= talkTimeBench && flow <= flowBench) {
            /* Get bill output for zero planFee */
            double billForZeroPlanFee = CUBS.phoneBillCalculation(planType, 0, talkTime, flow);

            /* Verification */
            assertEquals(0.0, billForZeroPlanFee);
        }
    }

    /**
     * Metamorphic Relation 17: Reducing the talkTime and/or flow to zero should
     * result in a bill
     * that is equal to the base planFee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testReductionToZeroUsage(String planType, int planFee, int talkTime, int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Set talkTime and flow to zero */
        double billWithZeroUsage = CUBS.phoneBillCalculation(planType, planFee, 0, 0);

        /* Verification - bill should be equal to planFee as there is no usage */
        assertEquals(planFee, billWithZeroUsage,
                "The bill should only include the base plan fee when there is no usage.");
    }

    /**
     * Metamorphic Relation 18: Keeping talkTime and flow constant, for any
     * planType, if planFee is incremented by a certain amount, the bill should also
     * increment by that amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testIncrementPlanFee(String planType, int planFee, int talkTime, int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Get original bill */
        double originalBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Increment planFee by arbitrary amount */
        int incrementAmount = 15;
        double billWithIncrementedPlanFee = CUBS.phoneBillCalculation(planType, planFee + incrementAmount, talkTime,
                flow);

        /* Verification - bill should be originalBill + incrementAmount */
        assertEquals(originalBill + incrementAmount, billWithIncrementedPlanFee, 0.01,
                "The bill should increment by the exact amount that the plan fee is incremented.");
    }

    /**
     * Metamorphic Relation 19: For any valid planType and planFee, swapping
     * talkTime with flow (if equated to same cost units) should not alter the bill.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testSwappingTalkTimeWithFlow(String planType, int planFee, int talkTime, int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Get original bill */
        double originalBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Swap talkTime with flow, assuming the same cost unit for simplicity */
        double billWithSwappedParameters = CUBS.phoneBillCalculation(planType, planFee, flow, talkTime);

        /* Verification */
        assertEquals(originalBill, billWithSwappedParameters, 0.01,
                "The bill should remain the same when talk time and flow are swapped, assuming equal cost units.");
    }

    /**
     * Metamorphic Relation 20: For the same planType and planFee, multiplying both
     * talkTime and flow by the same scalar should result in the bill being scaled
     * by the same factor, provided both original talkTime and flow are above their
     * respective benchmarks.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testScalingUsageAboveBenchmarks(String planType, int planFee, int talkTime,
            int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Get original bill */
        double originalBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Assuming the original talkTime and flow are above the benchmarks */
        double scaleFactor = 2.0; // scale factor
        double billWithScaledUsage = CUBS.phoneBillCalculation(planType, planFee,
                (int) (talkTime * scaleFactor), (int) (flow * scaleFactor));

        /* Verification - Ensure the bill scales according to the scaleFactor */
        assertEquals(originalBill * scaleFactor, billWithScaledUsage, 0.01,
                "The bill should scale by the same factor as the usage.");
    }

    /**
     * Metamorphic Relation 21: If both talkTime and flow are reduced, but still
     * remain above their respective benchmarks, the bill should decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testReductionBothAboveBenchmarks(String planType, int planFee, int talkTime,
            int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Get original bill */
        double originalBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        // Here we would need to know the benchmarks to ensure we are above them after
        // reduction,
        // but for demonstration let's assume a number below which we should not go to
        // ensure we are
        // above benchmarks.
        int minTalkTime = 100; // Placeholder
        int minFlow = 500; // Placeholder

        if (talkTime > minTalkTime && flow > minFlow) {
            /* Reduce talkTime and flow */
            int reducedTalkTime = talkTime - minTalkTime;
            int reducedFlow = flow - minFlow;

            /* Get bill with reduced usage */
            double billWithReducedUsage = CUBS.phoneBillCalculation(planType, planFee, reducedTalkTime, reducedFlow);

            /* Verification */
            assertTrue(billWithReducedUsage < originalBill,
                    "The bill should decrease when both talk time and flow decrease but remain above benchmarks.");
        }
    }

    /**
     * Metamorphic Relation 22: Increasing talkTime and/or flow beyond their
     * benchmarks should result in a bill increase proportional to the rate for each
     * unit above the benchmark.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testIncreaseBeyondBenchmarks(String planType, int planFee, int talkTime, int flow) { // Fixed
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Get original bill */
        double originalBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Get follow-up output with increased talkTime and flow beyond benchmarks */
        // Assuming rate and benchmark values are accessible (placeholders used here)
        int talkTimeBench = CUBS.getTalkTimeBench(); // Placeholder
        double talkTimeRate = CUBS.getTalkTimePer(); // Placeholder
        int flowBench = CUBS.getFlowBench(); // Placeholder
        double flowRate = CUBS.getFlowPer(); // Placeholder

        // Increasing talkTime and flow to ensure they are beyond the benchmark.
        int increasedTalkTime = talkTimeBench + 30;
        int increasedFlow = flowBench + 300;

        double billWithIncreasedUsage = CUBS.phoneBillCalculation(planType, planFee, increasedTalkTime, increasedFlow);

        /* Verification */
        double extraTalkTimeCharges = (increasedTalkTime - talkTimeBench) * talkTimeRate;
        double extraFlowCharges = (increasedFlow - flowBench) * flowRate;
        double expectedIncrease = extraTalkTimeCharges + extraFlowCharges;

        assertEquals(originalBill + expectedIncrease, billWithIncreasedUsage, 0.01,
                "The bill should increase proportional to the rate for each unit above their benchmarks.");
    }

    /**
     * Metamorphic Relation 23: For the same planFee, halving the used talkTime and
     * flow while staying above the benchmarks should result in a reduced bill that
     * is predictable based on the excess usage costs.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testHalvingUsageAboveBenchmarks(String planType, int planFee, int talkTime, int flow) { // Fixed
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Get original bill */
        double originalBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Halve talkTime and flow */
        int halfTalkTime = talkTime / 2;
        int halfFlow = flow / 2;

        // Assuming that benchmarks for talkTime and flow are known (placeholders used
        // here)
        int talkTimeBench = CUBS.getTalkTimeBench(); // Placeholder
        double talkTimeRate = CUBS.getTalkTimePer(); // Placeholder
        int flowBench = CUBS.getFlowBench(); // Placeholder
        double flowRate = CUBS.getFlowPer(); // Placeholder

        // Check if halved talkTime and flow are still above benchmarks
        if (halfTalkTime > talkTimeBench && halfFlow > flowBench) {

            /* Get bill with halved usage */
            double billWithHalvedUsage = CUBS.phoneBillCalculation(planType, planFee, halfTalkTime, halfFlow);

            /* Calculate expected decrease in the bill */
            double exceedTalkTimeBefore = talkTime - talkTimeBench;
            double exceedTalkTimeAfter = halfTalkTime - talkTimeBench;
            double exceedFlowBefore = flow - flowBench;
            double exceedFlowAfter = halfFlow - flowBench;

            double savedTalkTime = (exceedTalkTimeBefore - exceedTalkTimeAfter) * talkTimeRate;
            double savedFlow = (exceedFlowBefore - exceedFlowAfter) * flowRate;
            double expectedBillReduction = savedTalkTime + savedFlow;

            /* Verification */
            assertEquals(originalBill - expectedBillReduction, billWithHalvedUsage, 0.01,
                    "The bill should decrease by a predictable amount based on halved usage costs.");
        }
    }

    /**
     * Metamorphic Relation 24: Adding a fixed amount to both talkTime and flow
     * should result in a predictable increase in the bill if both parameters exceed
     * their respective benchmarks.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testAddingFixedAmountToUsage(String planType, int planFee, int talkTime, int flow) { // Fixed
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Assuming rate and benchmark values are accessible (placeholders used here) */
        int talkTimeBench = CUBS.getTalkTimeBench(); // Placeholder
        double talkTimeRate = CUBS.getTalkTimePer(); // Placeholder
        int flowBench = CUBS.getFlowBench(); // Placeholder
        double flowRate = CUBS.getFlowPer(); // Placeholder

        /* Get original bill */
        double originalBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Add fixed amount to exceed the benchmarks */
        int addTalkTime = 20; // Fixed talk time to add
        int addFlow = 50; // Fixed data usage to add

        /* Get bill with increased usage */
        double billWithAddedUsage = CUBS.phoneBillCalculation(planType, planFee, talkTime + addTalkTime,
                flow + addFlow);

        /* Calculate the expected additional charge */
        double additionalCharge = (addTalkTime * talkTimeRate) + (addFlow * flowRate);

        /* Verification */
        assertEquals(originalBill + additionalCharge, billWithAddedUsage, 0.01,
                "The bill should increase by the additional charge for the added usage.");
    }

    /**
     * Metamorphic Relation 25: Increasing only the talkTime when it is below the
     * benchmark should not change the bill, as long as it does not exceed the
     * benchmark.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testIncreaseTalkTimeBelowBenchmark(String planType, int planFee, int talkTime, int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /*
         * Assuming benchmark values for talkTime and flow are known/scalable based on
         * planType and planFee (placeholders used here)
         */
        int talkTimeBench = CUBS.getTalkTimeBench(); // Placeholder
        int flowBench = CUBS.getFlowBench(); // Placeholder

        /* Verify that we are initially below the benchmark */
        if (talkTime < talkTimeBench) {
            /* Get original bill */
            double originalBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

            /* Increase talkTime but ensure it does not exceed benchmark */
            int newTalkTime = talkTimeBench - 1;

            /* Get bill with increased talkTime that's still below benchmark */
            double billWithIncreasedTalkTime = CUBS.phoneBillCalculation(planType, planFee, newTalkTime, flow);

            /*
             * Verification - Bill should not change since talkTime increase is within the
             * free benchmark
             */
            assertEquals(originalBill, billWithIncreasedTalkTime,
                    "Bill should remain unchanged when increasing talkTime that's below the benchmark.");
        }
    }

    /**
     * Metamorphic Relation 26: Decreasing flow when it is above the benchmark
     * should result in a proportional decrease in the bill according to the per-MB
     * rate.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testDecreaseFlowAboveBenchmark(String planType, int planFee, int talkTime, int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Assuming benchmark values and flow rate are known (placeholders used here) */
        int flowBench = CUBS.getFlowBench(); // Placeholder
        double flowRate = CUBS.getFlowPer(); // Placeholder

        /* Verify that we are initially above the benchmark */
        if (flow > flowBench) {
            /* Get original bill */
            double originalBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

            /* Decrease flow but ensure it is still above benchmark */
            int decreasedFlow = flowBench + 1;

            /* Get bill with decreased flow */
            double billWithDecreasedFlow = CUBS.phoneBillCalculation(planType, planFee, talkTime, decreasedFlow);

            /* Calculate the expected reduction in the bill based on the decreased flow */
            double expectedBillReduction = (flow - decreasedFlow) * flowRate;

            /* Verification */
            assertEquals(originalBill - expectedBillReduction, billWithDecreasedFlow,
                    "Bill should decrease proportionally to the reduction in flow above the benchmark.");
        }
    }

    /**
     * Metamorphic Relation 27: If the planType and planFee remain constant and
     * talkTime and flow are both increased by an amount that keeps them within
     * their respective benchmarks, the final bill should not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testIncreaseWithinFreeBenchmarkLimits(String planType, int planFee, int talkTime, int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /*
         * Assuming benchmark values for talkTime and flow are known (placeholders used
         * here)
         */
        int talkTimeBench = CUBS.getTalkTimeBench(); // Placeholder
        int flowBench = CUBS.getFlowBench(); // Placeholder

        /* Verify that we are initially below the benchmarks */
        if (talkTime < talkTimeBench && flow < flowBench) {
            /* Calculate increases that keep us within benchmarks */
            int increaseTalkTime = talkTimeBench - talkTime - 1;
            int increaseFlow = flowBench - flow - 1;

            /* Get original bill */
            double originalBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

            /* Get bill with increased usage within benchmark limits */
            double billWithIncreasedUsage = CUBS.phoneBillCalculation(planType, planFee, talkTime + increaseTalkTime,
                    flow + increaseFlow);

            /*
             * Verification - Bill should not change since usage increase is within the free
             * benchmarks
             */
            assertEquals(originalBill, billWithIncreasedUsage,
                    "Bill should remain unchanged when increasing talkTime and flow within benchmark limits.");
        }
    }

    /**
     * Metamorphic Relation 28: For a fixed planFee, reducing talkTime and/or flow
     * to amounts below their free benchmarks should not result in a bill exceeding
     * that with the original usage, regardless of whether the original usage was
     * above the benchmarks.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testReductionToBelowFreeBenchmark(String planType, int planFee, int talkTime, int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /*
         * Assuming benchmark values for talkTime and flow are known (placeholders used
         * here)
         */
        int talkTimeBench = CUBS.getTalkTimeBench(); // Placeholder
        int flowBench = CUBS.getFlowBench(); // Placeholder

        /* Get original bill */
        double originalBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Reduce usage to below benchmarks */
        int newTalkTime = talkTimeBench - 1;
        int newFlow = flowBench - 1;

        /* Get adjusted bill */
        double adjustedBill = CUBS.phoneBillCalculation(planType, planFee, newTalkTime, newFlow);

        /* Verification */
        assertTrue(adjustedBill <= originalBill,
                "Reducing usage to below free benchmarks should not result in a higher bill than the original usage.");
    }

    /**
     * Metamorphic Relation 29: Given a constant planType and talkTime, increasing
     * planFee while reducing flow such that the combined extra costs cancel each
     * other out, the bill should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testOffsettingPlanFeeAndFlowChange(String planType, int planFee, int talkTime, int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /*
         * Assuming benchmark values and rates per unit are known (placeholders used
         * here)
         */
        int flowBench = CUBS.getFlowBench(); // Placeholder
        double flowRate = CUBS.getFlowPer(); // Placeholder

        /* Get original bill */
        double originalBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /*
         * Check if original flow is above benchmark and calculate the rate difference
         */
        if (flow > flowBench) {
            // Calculate the extra flow cost
            double extraFlowCost = (flow - flowBench) * flowRate;

            // Increase the planFee to offset the decreased flow
            int newPlanFee = planFee + (int) Math.ceil(extraFlowCost);

            // Calculate new flow to be at the benchmark, removing the extra flow cost
            int newFlow = flowBench;

            /* Get adjusted bill with new planFee and decreased flow */
            double adjustedBill = CUBS.phoneBillCalculation(planType, newPlanFee, talkTime, newFlow);

            /* Verification */
            assertEquals(originalBill, adjustedBill,
                    "Bill should remain the same when increase in planFee offsets the decrease in flow cost.");
        }
    }

    /**
     * Metamorphic Relation 30: For any planType, randomly shuffling values between
     * planFee, talkTime, and flow, while keeping them valid, should result in a
     * different bill unless they perfectly compensate each other according to the
     * plan's rate structure.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testRandomShuffleOfInputValues(String planType, int planFee, int talkTime,
            int flow) {
        BillCalculation CUBS = new BillCalculation();

        double originalBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        // Introducing randomness without knowing the rate structure is speculative
        // and may result in natural violations of the metamorphic relation.
        // However, assuming incremental increases/decreases within a controlled range
        // could suffice for this relation's purposes:
        Random random = new Random();

        // Shuffling values around with incremental randomness within a valid range
        int shuffledPlanFee = Math.max(0, planFee + random.nextInt(20) - 10); // ±10 units on the
                                                                              // plan fee, not going
                                                                              // below 0
        int shuffledTalkTime = Math.max(0, talkTime + random.nextInt(60) - 30); // ±30 minutes on
                                                                                // talk time, not
                                                                                // going below 0
        int shuffledFlow = Math.max(0, flow + random.nextInt(1000) - 500); // ±500 MB on flow, not
                                                                           // going below 0

        double shuffledBill = CUBS.phoneBillCalculation(planType, shuffledPlanFee, shuffledTalkTime,
                shuffledFlow);

        // The assertion here is not clear-cut; it can either be assertTrue or
        // assertFalse depending on what kind of result we intend to find. Here, we test
        // that the shuffled bill is 'usually' not the same as the original bill,
        // asserting the expectancy of a different result, yet aware that certain
        // shuffles might lead to the same bill.
        assertNotEquals(originalBill, shuffledBill,
                "Shuffled bill is expected to be different unless new values perfectly compensate according to the rate structure.");
    }

    /**
     * Metamorphic Relation 31: Swapping the values of planFee with talkTime or flow
     * while keeping the other parameters constant should result in different bills,
     * assuming talkTime and flow have different cost rates.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testSwapPlanFeeWithUsage(String planType, int planFee, int talkTime, int flow) { // Fixed
        // For simplicity, consider planFee, talkTime, and flow are interchangeable,
        // which might not be the case. In reality, each has different implications on
        // cost calculation. This relation assumes that we can somehow convert between
        // them while keeping the cost consistent.
        BillCalculation CUBS = new BillCalculation();

        double originalBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        // Swap planFee with talkTime, treating planFee as equivalent talkTime for the
        // purposes of this relation
        double billAfterPlanFeeTalkTimeSwap = CUBS.phoneBillCalculation(planType, talkTime, planFee, flow);

        // Swap planFee with flow, treating planFee as equivalent flow for the purposes
        // of this relation
        double billAfterPlanFeeFlowSwap = CUBS.phoneBillCalculation(planType, flow, talkTime, planFee);

        // Since planFee, talkTime, and flow likely contribute differently to the cost,
        // the resulting bills should be different from the original
        assertFalse(originalBill == billAfterPlanFeeTalkTimeSwap && originalBill == billAfterPlanFeeFlowSwap,
                "Swapping planFee with talkTime or flow should result in different bills if they have different cost rates.");
    }

    /**
     * Metamorphic Relation 32: For the same planType, if planFee is doubled and
     * talkTime and flow are also doubled, the bill should also double provided the
     * original talkTime and flow are both above their free benchmarks.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testDoublingAllParametersAboveBenchmark(String planType, int planFee, int talkTime, int flow) {
        BillCalculation CUBS = new BillCalculation();

        // Assuming benchmark limits are accessible and known (placeholders used here)
        int talkTimeBench = CUBS.getTalkTimeBench(); // talkTime benchmark placeholder
        int flowBench = CUBS.getFlowBench(); // flow benchmark placeholder

        if (talkTime > talkTimeBench && flow > flowBench) {
            double originalBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

            // Double all parameters
            double doubledBill = CUBS.phoneBillCalculation(planType, 2 * planFee, 2 * talkTime, 2 * flow);

            assertEquals(2 * originalBill, doubledBill,
                    "Doubling all parameters should double the bill when original usage is above benchmarks.");
        }
    }

    /**
     * Metamorphic Relation 33: For a fixed planType, maintaining the ratio of
     * talkTime to flow while adjusting the absolute values should result in a
     * predictable change in the bill based on the cost rates and benchmarks.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testMaintainProportionAdjustTotal(String planType, int planFee, int talkTime, int flow) {
        // This test assumes that we have access to the cost rates per unit for talkTime
        // and flow, as well as the benchmarks.
        BillCalculation CUBS = new BillCalculation();

        double originalBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        // Retrieve rates and benchmarks (placeholders used here)
        double talkTimeRate = CUBS.getTalkTimePer(); // Placeholder
        double flowRate = CUBS.getFlowPer(); // Placeholder
        int talkTimeBench = CUBS.getTalkTimeBench(); // Placeholder
        int flowBench = CUBS.getFlowBench(); // Placeholder

        // Maintain the ratio of talkTime to flow, but multiply each by a constant
        // factor.
        double scaleFactor = 1.5; // Arbitrary scale factor
        int newTalkTime = (int) (talkTime * scaleFactor);
        int newFlow = (int) (flow * scaleFactor);

        // Only apply this MR if newTalkTime and newFlow will go beyond their benchmarks
        // after scaling
        if (newTalkTime > talkTimeBench || newFlow > flowBench) {
            double newBill = CUBS.phoneBillCalculation(planType, planFee, newTalkTime, newFlow);

            // Calculate expected change
            double expectedExtraTalkTimeCost = (newTalkTime > talkTimeBench)
                    ? (newTalkTime - talkTimeBench) * talkTimeRate
                    : 0;
            double expectedExtraFlowCost = (newFlow > flowBench) ? (newFlow - flowBench) * flowRate : 0;

            double expectedBillChange = expectedExtraTalkTimeCost + expectedExtraFlowCost;

            assertEquals(originalBill + expectedBillChange, newBill, 0.01,
                    "Bill should change predictably when maintaining proportion and adjusting total usage.");
        }
    }

    /**
     * Metamorphic Relation 34: For the same planFee and planType, if we distribute
     * some amount of talkTime to flow or vice versa, the bill should only change if
     * the redistribution causes or alleviates exceeding their benchmarks.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testRedistributeUsageBetweenTalkTimeAndFlow(String planType, int planFee, int talkTime, int flow) {
        // This test assumes the conversion between talkTime and flow is not 1:1 due to
        // different rates.
        BillCalculation CUBS = new BillCalculation();

        double originalBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        // Retrieve talkTime and flow benchmarks and rates (placeholders used here)
        int talkTimeBench = CUBS.getTalkTimeBench(); // Placeholder
        double talkTimeRate = CUBS.getTalkTimePer(); // Placeholder
        int flowBench = CUBS.getFlowBench(); // Placeholder
        double flowRate = CUBS.getFlowPer(); // Placeholder

        // Redistribute a fixed amount of talkTime to flow
        int redistributionAmountTalkTimeToFlow = 10; // Chooses an arbitrary amount to redistribute
        // Ensure not reducing below zero
        int adjustedTalkTime = Math.max(talkTime - redistributionAmountTalkTimeToFlow, 0);
        // Determine the equivalent flow for the redistributed amount
        int equivalentFlowIncrease = (int) (redistributionAmountTalkTimeToFlow * (talkTimeRate / flowRate));
        int adjustedFlow = flow + equivalentFlowIncrease;

        double adjustedBill = CUBS.phoneBillCalculation(planType, planFee, adjustedTalkTime, adjustedFlow);

        // Verify that bill changes only if redistribution crosses benchmark thresholds
        if ((talkTime <= talkTimeBench && adjustedTalkTime <= talkTimeBench)
                || (flow >= flowBench && adjustedFlow >= flowBench)) {
            assertEquals(originalBill, adjustedBill,
                    "Bill should not change if redistribution does not cross benchmarks.");
        } else {
            assertNotEquals(originalBill, adjustedBill,
                    "Bill should change if redistribution causes or alleviates exceeding benchmarks.");
        }
    }

    /**
     * Metamorphic Relation 35: Adding the same amount to talkTime and flow should
     * result in the same bill if either both are below their benchmarks or both
     * above their benchmarks.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testSymmetricIncreaseOfUsage(String planType, int planFee, int talkTime, int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Retrieve talkTime and flow benchmarks (placeholders used here) */
        int talkTimeBench = CUBS.getTalkTimeBench(); // Placeholder
        int flowBench = CUBS.getFlowBench(); // Placeholder

        /* Get the initial bill */
        double initialBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /*
         * Determine the amount to add such that if one is below the benchmark, it
         * remains below after addition
         */
        int addition = Math.min(talkTimeBench - talkTime, flowBench - flow) - 1;
        if (addition < 0) {
            // If both talkTime and flow are already above their benchmarks,
            // choose an arbitrary positive addition that ensures both stay above their
            // benchmarks
            addition = 10;
        }

        /* Get the bill after adding the same amount to talkTime and flow */
        double updatedBill = CUBS.phoneBillCalculation(planType, planFee, talkTime + addition, flow + addition);

        /*
         * Verification: The initial and updated bill should be the same if the addition
         * does not cross the benchmarks
         */
        if ((talkTime + addition <= talkTimeBench && flow + addition <= flowBench) ||
                (talkTime > talkTimeBench && flow > flowBench)) {
            assertEquals(initialBill, updatedBill,
                    "The bill should not change if both talkTime and flow are modified symmetrically.");
        }
    }

    /**
     * Metamorphic Relation 36: Increasing only planFee should result in a linearly
     * increased bill while keeping talkTime and flow constant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testPlanFeeIncreaseOnly(String planType, int planFee, int talkTime, int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Get the initial bill */
        double initialBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Increase planFee */
        int increasedPlanFee = planFee + 20; // Increment planFee by 20 units

        /* Get the bill after increasing planFee */
        double updatedBill = CUBS.phoneBillCalculation(planType, increasedPlanFee, talkTime, flow);

        /* Verification: The updated bill should reflect the increase in planFee */
        assertEquals(initialBill + 20, updatedBill,
                "The bill should linearly increase with the planFee while keeping talkTime and flow constant.");
    }

    /**
     * Metamorphic Relation 37: For a given planType, doubling the talkTime while
     * maintaining the flow constant should either result in the same bill if the
     * original talkTime is below the benchmark or a doubled extra charge if the
     * original talkTime is above the benchmark.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testDoubleTalkTime(String planType, int planFee, int talkTime, int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /*
         * Retrieve talkTime benchmark and rate per minute over benchmark (placeholders
         * used here)
         */
        int talkTimeBench = CUBS.getTalkTimeBench(); // Placeholder
        double talkTimeRate = CUBS.getTalkTimePer(); // Placeholder

        /* Get the initial bill */
        double initialBill = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Double the talkTime */
        int doubledTalkTime = talkTime * 2;

        /* Get the bill after doubling talkTime */
        double updatedBill = CUBS.phoneBillCalculation(planType, planFee, doubledTalkTime, flow);

        if (talkTime <= talkTimeBench) {
            /*
             * If original talkTime is below the benchmark, the bill should remain the same
             */
            assertEquals(initialBill, updatedBill,
                    "The bill should remain the same if talkTime is doubled but originally below the benchmark.");
        } else {
            /* If the original talkTime is above the benchmark, additional charges apply */
            double additionalCharge = (doubledTalkTime - talkTimeBench) * talkTimeRate;
            assertEquals(initialBill + additionalCharge, updatedBill,
                    "The bill should reflect the additional charge if talkTime is doubled above the benchmark.");
        }
    }

    /**
     * Metamorphic Relation 38: For a given planType, given an initially valid
     * planFee, setting talkTime and flow to their benchmarks should result in the
     * bill being equal to the planFee, assuming no additional charges apply at the
     * benchmark.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testUsageEqualsBenchmark(String planType, int planFee, int talkTime, int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /*
         * Retrieve talkTime and flow benchmarks applicable to the given planFee
         * (placeholders used here)
         */
        int talkTimeBench = CUBS.getTalkTimeBench(); // Placeholder
        int flowBench = CUBS.getFlowBench(); // Placeholder

        /* Get the bill when talkTime and flow are exactly at their benchmarks */
        double billAtBenchmarks = CUBS.phoneBillCalculation(planType, planFee, talkTimeBench, flowBench);

        /*
         * The bill should be equal to the plan fee alone, as no overage charges should
         * apply
         */
        assertEquals(planFee, billAtBenchmarks,
                "The bill should be equal to the plan fee if talkTime and flow are exactly at their benchmarks.");
    }

    /**
     * Metamorphic Relation 39: For any planType, reducing talkTime and flow to zero
     * should result
     * in the total bill being equal to the planFee, independent of what the
     * original talkTime and
     * flow were.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testZeroUsageResultsInPlanFeeOnly(String planType, int planFee, int talkTime,
            int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Get the bill when talkTime and flow are reduced to zero */
        double billForNoUsage = CUBS.phoneBillCalculation(planType, planFee, 0, 0);

        /* The bill should be equal to the plan fee alone */
        assertEquals(planFee, billForNoUsage,
                "The bill should be the plan fee if there is no usage.");
    }

    /**
     * Metamorphic Relation 40: For any planType, swapping the amounts of talkTime
     * and flow should not affect the bill if the cost rate for talkTime and flow is
     * identical and they are both either below or above their respective
     * benchmarks.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void testSwapTalkTimeAndFlowWithIdenticalRate(String planType, int planFee, int talkTime, int flow) {
        /* Instantiate the object to test */
        BillCalculation CUBS = new BillCalculation();

        /* Assuming benchmarks and rates are accessible (placeholders used here) */
        int talkTimeBench = CUBS.getTalkTimeBench(); // Placeholder
        double talkTimeRate = CUBS.getTalkTimePer(); // Placeholder
        int flowBench = CUBS.getFlowBench(); // Placeholder
        double flowRate = CUBS.getFlowPer(); // Placeholder

        /* Get the initial bill */
        double initialBill = CUBS.phoneBillCalculation(planType, planFee, talkTime,
                flow);

        /* Swap the amounts of talkTime and flow */
        double billAfterSwap = CUBS.phoneBillCalculation(planType, planFee, flow,
                talkTime);

        /* Verify if the bill remains the same after swapping */
        if ((talkTime <= talkTimeBench && flow <= flowBench) ||
                (talkTime > talkTimeBench && flow > flowBench && talkTimeRate == flowRate)) {
            assertEquals(initialBill, billAfterSwap,
                    "The bill should not change if talkTime and flow are swapped and either both are below their benchmarks, or both are above and have identical rates.");
        }
    }

    /**
     * 读取测试用例
     *
     * @return
     * @throws Exception
     */
    public static Stream<Arguments> testcaseProvider() throws Exception {
        return testcaseGenerator.generate(1000);
    }

}
