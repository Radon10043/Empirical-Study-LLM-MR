package test;

import static org.junit.Assert.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.io.File;
import java.util.Set;
import java.util.stream.Stream;

import org.apache.commons.io.FileUtils;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import com.alibaba.fastjson2.JSON;
import com.alibaba.fastjson2.JSONObject;
import src.BillCalculation;

public class CUBSTestExample {
    /**
     * Metamorphic Relation 1: If the talk time increases, the bill should not decrease.
     *
     * @param planType
     * @param planFee
     * @param talkTime
     * @param flow
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
     *
     * @param planType
     * @param planFee
     * @param talkTime
     * @param flow
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
        /* 读取存储了测试用例的json文件 */
        File tc_file = new File("testcases" + File.separator + "testcases.json");
        String json_text = FileUtils.readFileToString(tc_file, "UTF-8");
        JSONObject json_data = JSON.parseObject(json_text);

        /* 统计测试用例数量 */
        int n = json_data.size();
        Arguments[] testcases = new Arguments[n];
        Set<String> keys = json_data.keySet();

        /* 遍历所有测试用例并存储至testcases */
        int cnt = 0;
        for (String key : keys) {

            String planType;
            int planFee, talkTime, flow;

            JSONObject data = JSON.parseObject(json_data.get(key).toString());
            planType = data.getString("planType");
            planFee = data.getIntValue("planFee");
            talkTime = data.getIntValue("talkTime");
            flow = data.getIntValue("flow");

            testcases[cnt++] = Arguments.of(planType, planFee, talkTime, flow);

        }

        return Stream.of(testcases);
    }
}
