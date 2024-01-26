package test;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.security.SecureRandom;
import java.util.stream.Stream;

import org.junit.jupiter.params.provider.Arguments;

import flanagan.complex.Complex;
import flanagan.complex.ComplexMatrix;
import flanagan.math.Matrix;

public class testcaseGenerator {
    /**
     * 随机生成num个测试用例, 并保存到文件中
     *
     * @param num
     * @return
     * @throws IOException
     */
    public static Stream<Arguments> generate_m(int num) throws IOException {
        int tcs_num = num;
        int[] range_size = { 1, 5 }; // 矩阵大小的范围, [1, 5)
        int[] range_value = { 1, 5 }; // 矩阵元素的范围, [1, 5)
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        /* 随机生成方阵 */
        for (int i = 0; i < tcs_num; i++) {
            int size = rand.nextInt(range_size[0], range_size[1]);
            Matrix m = new Matrix(size, size);
            for (int r = 0; r < size; r++) {
                for (int c = 0; c < size; c++) {
                    m.setElement(r, c, rand.nextInt(range_value[0], range_value[1]));
                }
            }
            tcs[i] = Arguments.of(m);
        }

        /* 将生成的测试用例保存到文件, 方便调试 */
        File file = new File("testcases.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            Matrix m = (Matrix) tcs[i].get()[0];
            int size = m.getNumberOfRows();
            writer.write("Testcase " + String.valueOf(i) + ":\n");
            writer.write("----------------------------------------------------------------\n");
            for (int r = 0; r < size; r++) {
                for (int c = 0; c < size; c++) {
                    writer.write(String.valueOf((int) m.getElement(r, c)) + ",");
                }
                writer.write("\n");
            }
            writer.write("\n");
        }
        writer.close();

        return Stream.of(tcs);
    }

    public static Stream<Arguments> generate_mm(int num) throws IOException {
        int tcs_num = num;
        int[] range_size = { 1, 5 }; // 矩阵大小的范围, [1, 11)
        int[] range_value = { 1, 5 }; // 矩阵元素的范围, [0, 5)
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        /* 随机生成方阵 */
        for (int i = 0; i < tcs_num; i++) {
            int size = rand.nextInt(range_size[0], range_size[1]);
            Matrix m1 = new Matrix(size, size), m2 = new Matrix(size, size);
            for (int r = 0; r < size; r++) {
                for (int c = 0; c < size; c++) {
                    m1.setElement(r, c, rand.nextInt(range_value[0], range_value[1]));
                    m2.setElement(r, c, rand.nextInt(range_value[0], range_value[1]));
                }
            }
            tcs[i] = Arguments.of(m1, m2);
        }

        /* 将生成的测试用例保存到文件, 方便调试 */
        File file = new File("testcases.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            Matrix m = (Matrix) tcs[i].get()[0];
            int size = m.getNumberOfRows();
            writer.write("Testcase " + String.valueOf(i) + ":\n");
            writer.write("----------------------------------------------------------------\n");
            for (int r = 0; r < size; r++) {
                for (int c = 0; c < size; c++) {
                    writer.write(String.valueOf((int) m.getElement(r, c)) + ",");
                }
                writer.write("\n");
            }
            writer.write("\n");
        }
        writer.close();

        return Stream.of(tcs);
    }

    public static Stream<Arguments> generate_cm(int num) throws IOException {
        int tcs_num = num;
        int[] range_size = { 1, 5 }; // 矩阵大小的范围, [1, 11)
        int[] range_value = { 1, 5 }; // 矩阵元素的范围, [0, 5)
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        /* 随机生成方阵 */
        for (int i = 0; i < tcs_num; i++) {
            int size = rand.nextInt(range_size[0], range_size[1]);
            ComplexMatrix m = new ComplexMatrix(size, size);
            for (int r = 0; r < size; r++) {
                for (int c = 0; c < size; c++) {
                    Complex val = new Complex(rand.nextInt(range_value[0], range_value[1]),
                            rand.nextInt(range_value[0], range_value[1]));
                    m.setElement(r, c, val);
                }
            }
            tcs[i] = Arguments.of(m);
        }

        /* 将生成的测试用例保存到文件, 方便调试 */
        File file = new File("testcases.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            ComplexMatrix m = (ComplexMatrix) tcs[i].get()[0];
            int size = m.getNrow();
            writer.write("Testcase " + String.valueOf(i) + ":\n");
            writer.write("----------------------------------------------------------------\n");
            for (int r = 0; r < size; r++) {
                for (int c = 0; c < size; c++) {
                    Complex val = m.getElementCopy(r, c);
                    writer.write(String.valueOf("(" + val.getReal() + "," + val.getImag() + ")" + ","));
                }
                writer.write("\n");
            }
            writer.write("\n");
        }
        writer.close();

        return Stream.of(tcs);
    }
}
