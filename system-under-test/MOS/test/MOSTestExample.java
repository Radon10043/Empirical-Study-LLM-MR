package test;

import static org.junit.Assert.assertTrue;
import java.io.File;
import java.util.stream.Stream;
import org.apache.commons.io.FileUtils;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import com.alibaba.fastjson2.JSON;
import com.alibaba.fastjson2.JSONObject;

import src.MSR;
import src.MealOrderingSystem;

public class MOSTestExample {
    /**
     * Metamorphic Relation 1: keeping other attributes unchanged, double the
     * numberofrequestedbundlesofflowers input, the numberOfRequestedBundlesOfFlowers attributes in
     * output should also double.
     *
     * @param aircraftmodel
     * @param changeinthenumberofcrewmembers
     * @param newnumberofcrewmembers
     * @param changeinthenumberofpilots
     * @param newnumberofpilots
     * @param numberofchildpassengers
     * @param numberofrequestedbundlesofflowers
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Get source output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Construct follow-up input */
        int follow_numberofrequestedbundlesofflowers = numberofrequestedbundlesofflowers * 2;

        /* Get follow-up output */
        MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, follow_numberofrequestedbundlesofflowers);

        /* Verification */
        assertTrue(source_out.numberOfBundlesOfFlowers * 2 == follow_out.numberOfBundlesOfFlowers);
    }

    /**
     * Metamorphic Relation 2: If the aircraftmodel parameter remains the same while other
     * parameters change, the values related to seat configuration (numberOfFirstClassMeals,
     * numberOfBusinessClassMeals, numberOfEconomicClassMeals) should remain constant.
     *
     * @param aircraftmodel
     * @param changeinthenumberofcrewmembers
     * @param newnumberofcrewmembers
     * @param changeinthenumberofpilots
     * @param newnumberofpilots
     * @param numberofchildpassengers
     * @param numberofrequestedbundlesofflowers
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Get source output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Construct follow-up input */
        String follow_changeinthenumberofpilots;
        if (changeinthenumberofpilots.equals("y")) {
            follow_changeinthenumberofpilots = "n";
        } else {
            follow_changeinthenumberofpilots = "y";
        }
        int follow_newnumberofpilots = newnumberofpilots * 2;
        int follow_numberofchildpassengers = numberofchildpassengers * 2;

        /* Get follow-up output */
        MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, follow_changeinthenumberofpilots, follow_newnumberofpilots,
                follow_numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Verification */
        assertTrue(source_out.numberOfFirstClassMeals == follow_out.numberOfFirstClassMeals);
        assertTrue(source_out.numberOfBusinessClassMeals == follow_out.numberOfBusinessClassMeals);
        assertTrue(source_out.numberOfEconomicClassMeals == follow_out.numberOfEconomicClassMeals);
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

            String aircraftmodel, changeinthenumberofcrewmembers, changeinthenumberofpilots;
            int newnumberofcrewmembers, newnumberofpilots, numberofchildpassengers,
                    numberofrequestedbundlesofflowers;

            JSONObject data = JSON.parseObject(json_data.get(String.valueOf(i)).toString());
            aircraftmodel = data.getString("aircraftmodel");
            changeinthenumberofcrewmembers = data.getString("changeinthenumberofcrewmembers");
            newnumberofcrewmembers = data.getIntValue("newnumberofcrewmembers");
            changeinthenumberofpilots = data.getString("changeinthenumberofpilots");
            newnumberofpilots = data.getIntValue("newnumberofpilots");
            numberofchildpassengers = data.getIntValue("numberofchildpassengers");
            numberofrequestedbundlesofflowers =
                    data.getIntValue("numberofrequestedbundlesofflowers");

            testcases[i] = Arguments.of(aircraftmodel, changeinthenumberofcrewmembers,
                    newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                    numberofchildpassengers, numberofrequestedbundlesofflowers);

        }

        return Stream.of(testcases);
    }
}
