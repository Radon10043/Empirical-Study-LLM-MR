package test;

import static org.junit.jupiter.api.Assertions.assertTrue;
import java.util.stream.Stream;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import src.BillCalculation;

public class CUBSTestExample {
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
