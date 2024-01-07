package test;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.stream.Stream;

import static org.junit.Assert.assertTrue;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import src.MaxRectangle;

public class MaxRectangleTestExample {
    /**
     * Metamorphic Relation 1: Adding one row, the output should be the same as or larger than the
     * original one.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input */
        int col_num = matrix.get(0).size();
        ArrayList<Integer> nrow = new ArrayList<Integer>(Collections.nCopies(col_num, 1));
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<ArrayList<Integer>>();
        follow_matrix.addAll(matrix);
        follow_matrix.add(nrow);

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Mrtamorphic Relation 2: Adding one column, the output should be the same as or larger than
     * the original one.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up output */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<ArrayList<Integer>>();
        follow_matrix.addAll(matrix);
        for (var row : follow_matrix) {
            row.add(1);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * 从文件读取测试用例内容
     *
     * @return
     * @throws Exception
     */
    public static Stream<Arguments> testcaseProvider() throws Exception {
        return testcaseGenerator.generate(1000);
    }
}
