package test;

import java.io.File;
import java.util.stream.Stream;

import src.AirlinesBaggageBillingService;

import com.alibaba.fastjson2.JSON;
import com.alibaba.fastjson2.JSONObject;

import org.apache.commons.io.FileUtils;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

public class ACMSTestExample {
    /**
     * Metamorphic Relation 1: Changing the isStudent flag from false to true should not increase
     * the fee and may decrease it in certain scenarios.
     *
     * @param airClass
     * @param area
     * @param isStudent
     * @param luggage
     * @param economicfee
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(int airClass, int area, boolean isStudent, double luggage,
            double economicfee) {
        if (isStudent)
            return;

        /* Get source output */
        AirlinesBaggageBillingService ACMS = new AirlinesBaggageBillingService();
        double source_out = ACMS.feeCalculation(airClass, area, isStudent, luggage, economicfee);

        /* Construct follow-up input */
        Boolean follow_isStudent = true;

        /* Get follow-up output */
        double follow_out =
                ACMS.feeCalculation(airClass, area, follow_isStudent, luggage, economicfee);

        /* Verification */
        assertTrue(follow_out <= source_out);
    }

    /**
     * Metamorphic Relation 2: If the luggage weight is 0, changing area should not affect the
     * luggagefee.
     *
     * @param airClass
     * @param area
     * @param isStudent
     * @param luggage
     * @param economicfee
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
     * Metamorphic Relation 3: If isStudent is false, changing the area should not affect the
     * luggage fee.
     *
     * @param airClass
     * @param area
     * @param isStudent
     * @param luggage
     * @param economicfee
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

        /* 遍历所有测试用例并存储至testcases */
        for (int i = 0; i < n; i++) {

            int airClass, area;
            boolean isStudent;
            double luggage, economicfee;

            JSONObject data = JSON.parseObject(json_data.get(String.valueOf(i)).toString());
            airClass = data.getIntValue("airClass");
            area = data.getIntValue("area");
            isStudent = data.getBooleanValue("isStudent");
            luggage = data.getDoubleValue("luggage");
            economicfee = data.getDoubleValue("economicfee");

            testcases[i] = Arguments.of(airClass, area, isStudent, luggage, economicfee);

        }

        return Stream.of(testcases);
    }
}
