package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.util.stream.Stream;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import src.BillCalculation;

public class CUBSTestGPT3D5 {
    /**
     * Metamorphic Relation 1: If the plan fee increases, the bill should not decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(String planType, int planFee, int talkTime, int flow) {
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
     * Metamorphic Relation 2: If the plan fee decreases, the bill should not increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(String planType, int planFee, int talkTime, int flow) {
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
     * Metamorphic Relation 3: If the talk time increases, the bill should not decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(String planType, int planFee, int talkTime, int flow) {
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
     * Metamorphic Relation 4: If the talk time decreases, the bill should not increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(String planType, int planFee, int talkTime, int flow) {
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

    /**
     * Metamorphic Relation 5: If the data usage increases, the bill should not decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(String planType, int planFee, int talkTime, int flow) {
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
     * Metamorphic Relation 6: If the data usage decreases, the bill should not increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(String planType, int planFee, int talkTime, int flow) {
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
     * Metamorphic Relation 7: If the plan type changes, the bill should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        String follow_planType;
        if (planType.equals("A")) {
            follow_planType = "B";
        } else {
            follow_planType = "A";
        }

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(follow_planType, planFee, talkTime, flow);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 8: If the talk time and data usage are both increased, the bill should
     * not decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_talkTime = talkTime * 2;
        int follow_flow = flow * 2;

        /* Get follow-up output */
        double follow_out =
                CUBS.phoneBillCalculation(planType, planFee, follow_talkTime, follow_flow);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 9: If the talk time and data usage are both decreased, the bill should
     * not increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_talkTime = talkTime / 2;
        int follow_flow = flow / 2;

        /* Get follow-up output */
        double follow_out =
                CUBS.phoneBillCalculation(planType, planFee, follow_talkTime, follow_flow);

        /* Verification */
        assertTrue(follow_out <= source_out);
    }

    /**
     * Metamorphic Relation 10: If the plan fee and data usage are both increased, the bill should
     * not decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_planFee = planFee * 2;
        int follow_flow = flow * 2;

        /* Get follow-up output */
        double follow_out =
                CUBS.phoneBillCalculation(planType, follow_planFee, talkTime, follow_flow);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 11: If the plan fee and data usage are both decreased, the bill should
     * not increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_planFee = planFee / 2;
        int follow_flow = flow / 2;

        /* Get follow-up output */
        double follow_out =
                CUBS.phoneBillCalculation(planType, follow_planFee, talkTime, follow_flow);

        /* Verification */
        assertTrue(follow_out <= source_out);
    }

    /**
     * Metamorphic Relation 12: If the talk time, plan fee, and data usage are all increased, the
     * bill should not decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_planFee = planFee * 2;
        int follow_talkTime = talkTime * 2;
        int follow_flow = flow * 2;

        /* Get follow-up output */
        double follow_out =
                CUBS.phoneBillCalculation(planType, follow_planFee, follow_talkTime, follow_flow);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 13: If the talk time, plan fee, and data usage are all decreased, the
     * bill should not increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_planFee = planFee / 2;
        int follow_talkTime = talkTime / 2;
        int follow_flow = flow / 2;

        /* Get follow-up output */
        double follow_out =
                CUBS.phoneBillCalculation(planType, follow_planFee, follow_talkTime, follow_flow);

        /* Verification */
        assertTrue(follow_out <= source_out);
    }

    /**
     * Metamorphic Relation 14: If the plan fee is increased and the talk time is decreased, the
     * bill should not strictly increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_planFee = planFee * 2;
        int follow_talkTime = talkTime / 2;

        /* Get follow-up output */
        double follow_out =
                CUBS.phoneBillCalculation(planType, follow_planFee, follow_talkTime, flow);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 15: If the talk time is increased and the plan fee is decreased, the
     * bill should not strictly decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_planFee = planFee / 2;
        int follow_talkTime = talkTime * 2;

        /* Get follow-up output */
        double follow_out =
                CUBS.phoneBillCalculation(planType, follow_planFee, follow_talkTime, flow);

        /* Verification */
        assertTrue(follow_out <= source_out);
    }

    /**
     * Metamorphic Relation 16: If the talk time is increased and the plan fee is decreased, the
     * bill should not strictly decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_talkTime = talkTime * 2;
        int follow_planFee = planFee / 2;

        /* Get follow-up output */
        double follow_out =
                CUBS.phoneBillCalculation(planType, follow_planFee, follow_talkTime, flow);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 17: If the talk time is decreased and the plan fee is increased, the
     * bill should not strictly increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_talkTime = talkTime / 2;
        int follow_planFee = planFee * 2;

        /* Get follow-up output */
        double follow_out =
                CUBS.phoneBillCalculation(planType, follow_planFee, follow_talkTime, flow);

        /* Verification */
        assertTrue(follow_out <= source_out);
    }

    /**
     * Metamorphic Relation 18: If the plan type and talk time are both increased, the bill should
     * not decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_talkTime = talkTime * 2;
        String follow_planType;
        if (planType.equals("A")) {
            follow_planType = "B";
        } else {
            follow_planType = "A";
        }

        /* Get follow-up output */
        double follow_out =
                CUBS.phoneBillCalculation(follow_planType, planFee, follow_talkTime, flow);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 19: If the plan type and data usage are both increased, the bill should
     * not decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_flow = flow * 2;
        String follow_planType;
        if (planType.equals("A")) {
            follow_planType = "B";
        } else {
            follow_planType = "A";
        }

        /* Get follow-up output */
        double follow_out =
                CUBS.phoneBillCalculation(follow_planType, planFee, talkTime, follow_flow);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 20: If the plan type, plan fee, talk time, and data usage are all
     * increased, the bill should not strictly decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_flow = flow * 2;
        int follow_planFee = planFee * 2;
        int follow_talkTime = talkTime * 2;
        String follow_planType;
        if (planType.equals("A")) {
            follow_planType = "B";
        } else {
            follow_planType = "A";
        }

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(follow_planType, follow_planFee,
                follow_talkTime, follow_flow);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 21: If the plan type and plan fee are both increased, the bill should
     * not necessarily decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_planFee = planFee * 2;
        String follow_planType;
        if (planType.equals("A")) {
            follow_planType = "B";
        } else {
            follow_planType = "A";
        }

        /* Get follow-up output */
        double follow_out =
                CUBS.phoneBillCalculation(follow_planType, follow_planFee, talkTime, flow);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 22: If the plan type, plan fee, talk time, and data usage are all
     * increased, the bill should not strictly decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_flow = flow * 2;
        int follow_planFee = planFee * 2;
        int follow_talkTime = talkTime * 2;
        String follow_planType;
        if (planType.equals("A")) {
            follow_planType = "B";
        } else {
            follow_planType = "A";
        }

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(follow_planType, follow_planFee,
                follow_talkTime, follow_flow);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }


    /**
     * Metamorphic Relation 23: If the plan type, plan fee, talk time, and data usage are all
     * increased, the bill should not strictly decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_flow = flow * 2;
        int follow_planFee = planFee * 2;
        int follow_talkTime = talkTime * 2;
        String follow_planType;
        if (planType.equals("A")) {
            follow_planType = "B";
        } else {
            follow_planType = "A";
        }

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(follow_planType, follow_planFee,
                follow_talkTime, follow_flow);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 24: If the plan type, plan fee, talk time, and data usage are all
     * increased, the bill should not strictly decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_flow = flow * 2;
        int follow_planFee = planFee * 2;
        int follow_talkTime = talkTime * 2;
        String follow_planType;
        if (planType.equals("A")) {
            follow_planType = "B";
        } else {
            follow_planType = "A";
        }

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(follow_planType, follow_planFee,
                follow_talkTime, follow_flow);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 25: If the plan type, plan fee, talk time, and data usage are all
     * increased, the bill should not strictly decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_flow = flow * 2;
        int follow_planFee = planFee * 2;
        int follow_talkTime = talkTime * 2;
        String follow_planType;
        if (planType.equals("A")) {
            follow_planType = "B";
        } else {
            follow_planType = "A";
        }

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(follow_planType, follow_planFee,
                follow_talkTime, follow_flow);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 26: If the plan type and plan fee are both increased, the bill should
     * not strictly decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_planFee = planFee * 2;
        String follow_planType;
        if (planType.equals("A")) {
            follow_planType = "B";
        } else {
            follow_planType = "A";
        }

        /* Get follow-up output */
        double follow_out =
                CUBS.phoneBillCalculation(follow_planType, follow_planFee, talkTime, flow);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 27: If the plan type and data usage are both increased, the bill should
     * not strictly decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_flow = flow * 2;
        String follow_planType;
        if (planType.equals("A")) {
            follow_planType = "B";
        } else {
            follow_planType = "A";
        }

        /* Get follow-up output */
        double follow_out =
                CUBS.phoneBillCalculation(follow_planType, planFee, talkTime, follow_flow);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 28: If the plan fee and data usage are both increased, the bill should
     * not strictly decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_flow = flow * 2;
        int follow_planFee = planFee * 2;

        /* Get follow-up output */
        double follow_out =
                CUBS.phoneBillCalculation(planType, follow_planFee, talkTime, follow_flow);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 29: If all input values remain unchanged, the bill should remain
     * unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Get follow-up output with the same input values */
        double follow_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 30: If the talk time decreases, and the data usage remains the same, the
     * bill should decrease or remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(String planType, int planFee, int talkTime, int flow) {
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

    /**
     * Metamorphic Relation 31: If the plan fee is decreased, and the talk time remains the same,
     * the bill should decrease or remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(String planType, int planFee, int talkTime, int flow) {
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
     * Metamorphic Relation 32: If the plan type changes from A to B, and the talk time and data
     * usage remain the same, the bill should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        String follow_planType = planType.equalsIgnoreCase("A") ? "B" : "A";

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(follow_planType, planFee, talkTime, flow);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 33: If the plan fee changes from 46 to 96, and the talk time and data
     * usage remain the same, the bill should increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_planFee = 96;

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(planType, follow_planFee, talkTime, flow);

        /* Verification */
        assertTrue(follow_out > source_out);
    }

    /**
     * Metamorphic Relation 34: If the plan type changes from A to B, and the plan fee, talk time,
     * and data usage all remain the same, the bill should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        String follow_planType = planType.equalsIgnoreCase("A") ? "B" : "A";

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(follow_planType, planFee, talkTime, flow);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 35: If the talk time, plan fee, and data usage are all 0, the bill
     * should be 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, 0, 0);

        /* Verification */
        assertEquals(0, source_out);
    }

    /**
     * Metamorphic Relation 36: If the plan fee is 0, the bill should be 0 regardless of the plan
     * type and usage.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, 0, talkTime, flow);

        /* Verification */
        assertEquals(0, source_out);
    }

    /**
     * Metamorphic Relation 37: If the plan type is invalid, the bill should not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_outA = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        String follow_planType = "invalid";

        /* Get follow-up output */
        double follow_out = CUBS.phoneBillCalculation(follow_planType, planFee, talkTime, flow);

        /* Verification */
        assertEquals(source_outA, follow_out);
    }

    /**
     * Metamorphic Relation 38: If the plan type is valid, the bill should remain the same
     * regardless of the plan fee and usage.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_outA = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_planFee = 100;
        int follow_talkTime = 200;
        int follow_flow = 300;

        /* Get follow-up output */
        double follow_out =
                CUBS.phoneBillCalculation(planType, follow_planFee, follow_talkTime, follow_flow);

        /* Verification */
        assertEquals(source_outA, follow_out);
    }

    /**
     * Metamorphic Relation 39: If the plan type and plan fee are both increased, the bill should
     * not strictly decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int follow_planFee = planFee * 2;
        String follow_planType;
        if (planType.equals("A")) {
            follow_planType = "B";
        } else {
            follow_planType = "A";
        }

        /* Get follow-up output */
        double follow_out =
                CUBS.phoneBillCalculation(follow_planType, follow_planFee, talkTime, flow);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 40: If the plan type and plan fee are both increased, and the talk time
     * and data usage remain the same, the bill should not strictly decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(String planType, int planFee, int talkTime, int flow) {
        /* Get source output */
        BillCalculation CUBS = new BillCalculation();
        double sourceOut = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

        /* Construct follow-up input */
        int followPlanFee = planFee * 2;
        String followPlanType;
        if (planType.equals("A")) {
            followPlanType = "B";
        } else {
            followPlanType = "A";
        }

        /* Get follow-up output */
        double followOut = CUBS.phoneBillCalculation(followPlanType, followPlanFee, talkTime, flow);

        /* Verification */
        assertTrue(followOut >= sourceOut);
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
