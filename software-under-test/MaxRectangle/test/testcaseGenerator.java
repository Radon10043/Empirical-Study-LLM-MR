package test;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.stream.Stream;
import org.junit.jupiter.params.provider.Arguments;

public class testcaseGenerator {
    /**
     * 随机生成num个测试用例, 并保存到文件中
     *
     * @param num
     * @return
     * @throws IOException
     */
    public static Stream<Arguments> generate(int num) throws IOException {
        int tcs_num = num;
        int[] range_row = {1, 11}; // 行大小范围, [1, 11)
        int[] range_col = {1, 11}; // 列大小范围, [1, 11)
        int[] range_value = {0, 2}; // 矩阵元素范围[0, 2)
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        /* 随机生成矩阵 */
        for (int i = 0; i < tcs_num; i++) {
            ArrayList<ArrayList<Integer>> matrix = new ArrayList<>();
            int num_r = rand.nextInt(range_row[0], range_row[1]);
            int num_c = rand.nextInt(range_col[0], range_col[1]);
            for (int j = 0; j < num_r; j++) {
                ArrayList<Integer> row = new ArrayList<Integer>();
                for (int k = 0; k < num_c; k++) {
                    row.add(rand.nextInt(range_value[0], range_value[1]));
                }
                matrix.add(row);
            }
            tcs[i] = Arguments.of(matrix);
        }

        /* 写入文件, 方便调试 */
        File file = new File("testcases.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            ArrayList<ArrayList<Integer>> matrix = (ArrayList<ArrayList<Integer>>) tcs[i].get()[0];
            int num_r = matrix.size(), num_c = matrix.get(0).size();
            writer.write("Testcase " + String.valueOf(i) + ":\n");
            writer.write("----------------------------------------------------------------\n");
            for (int r = 0; r < num_r; r++) {
                for (int c = 0; c < num_c; c++) {
                    writer.write(String.valueOf(matrix.get(r).get(c)) + ",");
                }
                writer.write("\n");
            }
            writer.write("\n");
        }
        writer.close();

        return Stream.of(tcs);
    }
}
