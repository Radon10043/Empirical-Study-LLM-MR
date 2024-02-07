package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.io.IOException;
import java.util.stream.Stream;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import src.BillCalculation;

public class CUBSTestGPT3D5 {
    /**
     * Metamorphic Relation 1: If the data usage increases, the bill should not decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_flow = flow * 2;

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, follow_flow);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 2: If the data usage decreases, the bill should not increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_flow = flow / 2;

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, follow_flow);

        /* Verification */
        assertTrue(follow_out <= source_out);
    }

/**
     * Metamorphic Relation 3: If the plan fee increases, the bill should not decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_planFee = planFee * 2;

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, follow_planFee, talkTime, flow);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 4: If the plan fee decreases, the bill should not increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_planFee = planFee / 2;

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, follow_planFee, talkTime, flow);

        /* Verification */
        assertTrue(follow_out <= source_out);
    }

    /**
     * Metamorphic Relation 5: If the talk time and data usage are the same, the bill should be the same regardless of the plan type.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(String planType, int planFee, int talkTime, int flow) {
        /* Get source output for planType A */
        BillCalculation CUBS = new BillCalculation();
        double source_out_A = CUBS.phoneBillCalculation("A", planFee, talkTime, flow);

        /* Get source output for planType B */
        double source_out_B = CUBS.phoneBillCalculation("B", planFee, talkTime, flow);

        /* Verification */
        assertEquals(source_out_A, source_out_B);
    }

    /**
     * Metamorphic Relation 6: If the talk time threshold is exceeded, the extra charge should be proportional to the excess talk time.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_talkTime = talkTime + 100; // Exceeding the talk time threshold

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, planFee, follow_talkTime, flow);

        /* Verification */
        double extraCharge = follow_out - source_out;
        double excessTalkTime = follow_talkTime - talkTime;
        assertEquals(extraCharge, (excessTalkTime * CUBS.getTalkTimePer()), 1e-6);
    }

    /**
     * Metamorphic Relation 7: If the data flow threshold is exceeded, the extra charge should be fixed according to the excess data flow.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_flow = flow + 500; // Exceeding the data flow threshold

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, follow_flow);

        /* Verification */
        assertEquals(follow_out - source_out, CUBS.getFlowPer(), 1e-6);
    }

    /**
     * Metamorphic Relation 8: If the plan type is changed from A to B or vice versa but the usage remains the same, the bill should change accordingly based on the new plan benchmarks and rates.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(String planType, int planFee, int talkTime, int flow) {
        /* Get source output for planType A */
        BillCalculation CUBS = new BillCalculation();
        double source_out_A = CUBS.phoneBillCalculation("A", planFee, talkTime, flow);

        /* Get source output for planType B */
        double source_out_B = CUBS.phoneBillCalculation("B", planFee, talkTime, flow);

        /* Verification */
        assertNotEquals(source_out_A, source_out_B);
    }

    /**
     * Metamorphic Relation 9: If the plan fee is changed, but the talk time and flow remain the same, the bill should change accordingly based on the new plan fee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(String planType, int planFee, int talkTime, int flow) {
        /* Get source output for original plan fee */
        BillCalculation CUBS = new BillCalculation();
        double source_out_original = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Get follow-up output for a different plan fee */
        int follow_planFee = planFee + 10;
        double follow_out = CUBS.phoneBillCalculation(planType, follow_planFee, talkTime, flow);

        /* Verification */
        assertNotEquals(source_out_original, follow_out);
    }

    /**
     * Metamorphic Relation 10: If the talk time is equal to the talk time benchmark, there should be no extra charge for talk time.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_talkTime = CUBS.getTalkTimeBench(); // Equal to the talk time benchmark

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, planFee, follow_talkTime, flow);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 11: If the data flow is equal to the data flow benchmark, there should be no extra charge for data flow.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_flow = CUBS.getFlowBench(); // Equal to the data flow benchmark

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, follow_flow);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 12: If a negative plan fee is provided, the method should throw an IOException without affecting the program flow.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();

        /* Verification */
        assertThrows(IOException.class, () -> {
            CUBS.phoneBillCalculation(planType, -planFee, talkTime, flow);
        });
    }

    /**
     * Metamorphic Relation 13: If an invalid plan type is provided, the method should throw an IOException without affecting the program flow.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();

        /* Verification */
        assertThrows(IOException.class, () -> {
            CUBS.phoneBillCalculation("C", planFee, talkTime, flow);
        });
    }

    /**
     * Metamorphic Relation 14: If the user exceeds both the talk time and data usage thresholds, the extra charges for both should be applied to the total bill.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_talkTime = talkTime + 100; // Exceeding talk time threshold
        int follow_flow = flow + 500; // Exceeding data usage threshold

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, planFee, follow_talkTime, follow_flow);

        /* Verification */
        double expectedExtraCharge = (follow_talkTime - talkTime) * CUBS.getTalkTimePer() + CUBS.getFlowPer();
        assertEquals(follow_out - source_out, expectedExtraCharge);
    }

    /**
     * Metamorphic Relation 15: If the talk time and data flow are both zero, the bill should only consist of the plan fee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_talkTime = 0;
        int follow_flow = 0;

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, planFee, follow_talkTime, follow_flow);

        /* Verification */
        assertEquals(follow_out, planFee);
    }

    /**
     * Metamorphic Relation 16: If the talk time and data flow are both at the benchmarks, the bill should consist of the plan fee without any additional charges.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_talkTime = CUBS.getTalkTimeBench();
        int follow_flow = CUBS.getFlowBench();

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, planFee, follow_talkTime, follow_flow);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 17: If the talk time and data flow are both below the benchmarks, there should be no extra charges for talk time and data flow.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation billCalculation = new BillCalculation();
        double sourceOut = billCalculation.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int followTalkTime = billCalculation.getTalkTimeBench() - 1;
        int followFlow = billCalculation.getFlowBench() - 1;

        /* Get follow-up output */
        double followOut = billCalculation.phoneBillCalculation(planType, planFee, followTalkTime, followFlow);

        /* Verification */
        assertEquals(sourceOut, followOut);
    }

    /**
     * Metamorphic Relation 18: If the plan type is null, the method should throw an IOException without affecting the program flow.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String planType, int planFee, int talkTime, int flow) {
        /* Get bill calculation */
        BillCalculation billCalculation = new BillCalculation();

        /* Verification */
        assertThrows(IOException.class, () -> {
            billCalculation.phoneBillCalculation(null, 100, 200, 300);
        });
    }

    /**
     * Metamorphic Relation 19: If the planFee, talkTime, and flow are all zero, the total bill should be zero.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation billCalculation = new BillCalculation();
        double sourceOut = billCalculation.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Verification */
        assertEquals(0, sourceOut);
    }

    /**
     * Metamorphic Relation 20: If the planFee, talkTime, and flow are all negative, the method should throw an IOException without affecting the program flow.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(String planType, int planFee, int talkTime, int flow) {
        /* Get bill calculation */
        BillCalculation billCalculation = new BillCalculation();

        /* Verification */
        assertThrows(IOException.class, () -> {
            billCalculation.phoneBillCalculation(planType, -planFee, -talkTime, -flow);
        });
    }

    /**
     * Metamorphic Relation 21: If the planType is 'A' and the planFee is greater than 100, the benchmark for talk time should be greater than the benchmark for flow.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(String planType, int planFee, int talkTime, int flow) {
        BillCalculation billCalculation = new BillCalculation();

        /* Verification */
        if (planType.equalsIgnoreCase("A") && planFee > 100) {
            assertTrue(billCalculation.getTalkTimeBench() > billCalculation.getFlowBench());
        }
    }

    /**
     * Metamorphic Relation 22: If the planType is 'B' and the planFee is greater than 200, the benchmark for flow should be greater than the benchmark for talk time.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(String planType, int planFee, int talkTime, int flow) {
        BillCalculation billCalculation = new BillCalculation();

        /* Verification */
        if (planType.equalsIgnoreCase("B") && planFee > 200) {
            assertTrue(billCalculation.getFlowBench() > billCalculation.getTalkTimeBench());
        }
    }

    /**
     * Metamorphic Relation 23: If the user's plan fee is different but their talk time and data usage remain the same, the bill should change based on the new plan fee without any additional charges for talk time and data flow.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double sourceOut = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int newPlanFee = planFee + 100;

        /* Get follow-up output */
        double followOut = CUBS.phoneBillCalculation(planType, newPlanFee, talkTime, flow);

        /* Verification */
        assertNotEquals(sourceOut, followOut);
    }

    /**
     * Metamorphic Relation 24: If the planType provided in lowercase is equivalent to the planType provided in uppercase, the output should be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(String planType, int planFee, int talkTime, int flow) {
        /* Get source output for planType in uppercase */
        BillCalculation CUBS = new BillCalculation();
        double sourceOut_UpperCase = CUBS.phoneBillCalculation(planType.toUpperCase(), planFee, talkTime, flow);

        /* Get source output for planType in lowercase */
        double sourceOut_LowerCase = CUBS.phoneBillCalculation(planType.toLowerCase(), planFee, talkTime, flow);

        /* Verification */
        assertEquals(sourceOut_UpperCase, sourceOut_LowerCase);
    }

    /**
     * Metamorphic Relation 25: If the talk time benchmark is less than the data flow benchmark for a plan type, the user's talk time should be expected to be less than the data flow usage for that plan type.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(String planType, int planFee, int talkTime, int flow) {
        BillCalculation billCalculation = new BillCalculation();

        /* Verification */
        if (billCalculation.getTalkTimeBench() < billCalculation.getFlowBench()) {
            assertTrue(talkTime < flow);
        }
    }

    /**
     * Metamorphic Relation 26: If the planType is 'A' and there is no additional charge due to exceeding the data flow threshold, the talk time should influence the total bill.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double sourceOut = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int followFlow = CUBS.getFlowBench() - 100; // Below the data flow threshold

        /* Get follow-up output */
        double followOut = CUBS.phoneBillCalculation(planType, planFee, talkTime, followFlow);

        /* Verification */
        assertTrue(followOut > sourceOut);
    }

    /**
     * Metamorphic Relation 27: If the talk time and data flow are the same, but the plan fee is different, the bill should change according to the new plan fee.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double sourceOut = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int followPlanFee = planFee + 50; // Different plan fee

        /* Get follow-up output */
        double followOut = CUBS.phoneBillCalculation(planType, followPlanFee, talkTime, flow);

        /* Verification */
        assertNotEquals(sourceOut, followOut);
    }

    /**
     * Metamorphic Relation 28: If the talk time and data flow stay the same, the bill should remain unchanged for different requests within a short period, accounting for system consistency.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double sourceOut = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* A short pause to create a request within a short period */
        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        /* Get follow-up output */
        double followOut = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Verification */
        assertEquals(sourceOut, followOut);
    }

    /**
     * Metamorphic Relation 29: If the talk time and data flow are interchanged but the plan fee remains the same, the bill should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double sourceOut = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Get follow-up output with interchanged talk time and data flow */
        double followOut = CUBS.phoneBillCalculation(planType, planFee, flow, talkTime);

        /* Verification */
        assertEquals(sourceOut, followOut);
    }

    /**
     * Metamorphic Relation 30: If the plan fee is zero, the bill should not have any additional charges for talk time or data flow.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(String planType, int planFee, int talkTime, int flow) {
        BillCalculation billCalculation = new BillCalculation();

        /* Verification */
        if (planFee == 0) {
            double expectedBill = Math.max(0, billCalculation.getTalkTimeBench() - talkTime) + Math.max(0, billCalculation.getFlowBench() - flow);
            assertEquals(expectedBill, new BillCalculation().phoneBillCalculation(planType, planFee, talkTime, flow));
        }
    }

    /**
     * Metamorphic Relation 31: If the planType and planFee are kept the same, increasing talk time or data flow should increase the total bill.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(String planType, int planFee, int talkTime, int flow) {
        planType = "A";
        planFee = 886;
        talkTime = 595;
        flow = 1000;

        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double sourceOut = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int followTalkTime = talkTime + 50;
        int followFlow = flow + 100;

        /* Get follow-up output */
        double followOut = CUBS.phoneBillCalculation(planType, planFee, followTalkTime, followFlow);

        /* Verification */
        assertTrue(followOut > sourceOut);
    }

    /**
     * Metamorphic Relation 32: If the plan fee is negative, the method should throw an IOException without affecting the program flow.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(String planType, int planFee, int talkTime, int flow) {
        /* Get bill calculation */
        BillCalculation billCalculation = new BillCalculation();

        /* Verification */
        assertThrows(IOException.class, () -> {
            billCalculation.phoneBillCalculation(planType, planFee, talkTime, flow);
        });
    }

    /**
     * Metamorphic Relation 33: If the planType is unknown, the behavior should be equivalent to providing an invalid plan type and should not affect the program flow.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();

        /* Verification */
        assertThrows(IOException.class, () -> {
            CUBS.phoneBillCalculation("UNKNOWN", planFee, talkTime, flow);
        });
    }

    /**
     * Metamorphic Relation 34: If the user exceeds both the talk time and data usage thresholds, the extra charges for both should be added to the total bill separately.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_talkTime = talkTime + 100; // Exceeding the talk time threshold
        int follow_flow = flow + 500; // Exceeding the data usage threshold

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, planFee, follow_talkTime, follow_flow);

        /* Verification */
        double expectedExtraCharge = (follow_talkTime - talkTime) * CUBS.getTalkTimePer() + (follow_flow - flow) * CUBS.getFlowPer();
        assertEquals(follow_out - source_out, expectedExtraCharge);
    }

    /**
     * Metamorphic Relation 35: If the talk time is less than or equal to the benchmark, there should be no extra charge for talk time regardless of the plan type.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_talkTime = CUBS.getTalkTimeBench(); // Less than or equal to the talk time benchmark

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, planFee, follow_talkTime, flow);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 36: If the data usage is less than or equal to the benchmark, there should be no extra charge for data usage regardless of the plan type.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_flow = CUBS.getFlowBench(); // Less than or equal to the data flow benchmark

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, follow_flow);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 37: If the talk time and data usage follow the relation talkTime = f(flow), then every valid pair of (talk time, data usage) should produce the same bill.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(String planType, int planFee, int talkTime, int flow) {
        /* Get source output for original input */
        BillCalculation CUBS = new BillCalculation();
        double source_out_original = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input where talk time is a function of flow */
        int follow_talkTime = 2*flow; // An example relation talkTime = f(flow)

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, planFee, follow_talkTime, flow);

        /* Verification */
        assertEquals(source_out_original, follow_out);
    }

    /**
     * Metamorphic Relation 38: If the base plan fee is discounted by a certain percentage, the resulting bill should also be discounted by the same percentage.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(String planType, int planFee, int talkTime, int flow) {
        /* Get source output for original input */
        BillCalculation CUBS = new BillCalculation();
        double source_out_original = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input with a discounted plan fee */
        int follow_planFee = (int) (planFee * 0.8); // 20% discount

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, follow_planFee, talkTime, flow);

        /* Verification */
        assertEquals(source_out_original*0.8, follow_out);
    }

    /**
     * Metamorphic Relation 39: If the talk time and data flow exceed the defined thresholds, then the total bill should always increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double sourceOut = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int followTalkTime = CUBS.getTalkTimeBench() + 50;
        int followFlow = CUBS.getFlowBench() + 100;

        /* Get follow-up output */
        double followOut = CUBS.phoneBillCalculation(planType, planFee, followTalkTime, followFlow);

        /* Verification */
        assertTrue(followOut > sourceOut);
    }

    /**
     * Metamorphic Relation 40: If the talk time and data flow are kept constant, increasing the plan fee should always increase the total bill.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double sourceOut = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int newPlanFee = planFee + 50;

        /* Get follow-up output */
        double followOut = CUBS.phoneBillCalculation(planType, newPlanFee, talkTime, flow);

        /* Verification */
        assertTrue(followOut > sourceOut);
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
