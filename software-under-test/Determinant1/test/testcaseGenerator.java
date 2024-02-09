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
     * 随机生成一个方阵, 大小为size*size, 元素范围为[1, 5)
     *
     * @param size
     * @return
     */
    public static Matrix genMatrix(int size, int[] range_value) {
        SecureRandom rand = new SecureRandom();
        Matrix m = new Matrix(size, size);

        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                m.setElement(r, c, rand.nextInt(range_value[0], range_value[1]));
            }
        }

        return m;
    }

    /**
     * 随机生成num个测试用例, 并保存到文件中 测试用例的内容为一个方阵
     *
     * @param num
     * @return
     * @throws IOException
     */
    public static Stream<Arguments> generate_m(int num) throws IOException {
        int tcs_num = num;
        int[] range_size = {1, 5}; // 矩阵大小的范围, [1, 5)
        int[] range_value = {1, 5}; // 矩阵元素的范围, [1, 5)
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        /* 随机生成方阵 */
        for (int i = 0; i < tcs_num; i++) {
            int size = rand.nextInt(range_size[0], range_size[1]);
            Matrix m = genMatrix(size, range_value);
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

    /**
     * 随机生成num个测试用例, 并保存到文件中 测试用例的内容为两个方阵
     *
     * @param num
     * @return
     * @throws IOException
     */
    public static Stream<Arguments> generate_mm(int num) throws IOException {
        int tcs_num = num;
        int[] range_size = {1, 5}; // 矩阵大小的范围, [1, 11)
        int[] range_value = {1, 5}; // 矩阵元素的范围, [0, 5)
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        /* 随机生成方阵 */
        for (int i = 0; i < tcs_num; i++) {
            int size = rand.nextInt(range_size[0], range_size[1]);
            Matrix m1 = genMatrix(size, range_value);
            Matrix m2 = genMatrix(size, range_value);
            tcs[i] = Arguments.of(m1, m2);
        }

        /* 将生成的测试用例保存到文件, 方便调试 */
        File file = new File("testcases.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            Matrix m1 = (Matrix) tcs[i].get()[0];
            Matrix m2 = (Matrix) tcs[i].get()[1];
            int size = m1.getNumberOfRows();

            writer.write("Testcase " + String.valueOf(i) + ":\n");
            writer.write("----------------------------------------------------------------\n");
            writer.write("Matrix 1:\n");
            for (int r = 0; r < size; r++) {
                for (int c = 0; c < size; c++) {
                    writer.write(String.valueOf((int) m1.getElement(r, c)) + ",");
                }
                writer.write("\n");
            }
            writer.write("\n");

            writer.write("Matrix 2:\n");
            for (int r = 0; r < size; r++) {
                for (int c = 0; c < size; c++) {
                    writer.write(String.valueOf((int) m2.getElement(r, c)) + ",");
                }
                writer.write("\n");
            }
            writer.write("\n");
        }
        writer.close();

        return Stream.of(tcs);
    }

    /**
     * 随机生成num个测试用例, 保存倒文件中, 测试用例的内容为4个方阵
     *
     * @param num
     * @return
     * @throws IOException
     */
    public static Stream<Arguments> generate_m4(int num) throws IOException {
        int tcs_num = num;
        int[] range_size = {1, 5}; // 矩阵大小的范围, [1, 11)
        int[] range_value = {1, 5}; // 矩阵元素的范围, [1, 5)
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        /* 随机生成方阵 */
        for (int i = 0; i < tcs_num; i++) {
            int size = rand.nextInt(range_size[0], range_size[1]);
            Matrix m1 = genMatrix(size, range_value);
            Matrix m2 = genMatrix(size, range_value);
            Matrix m3 = genMatrix(size, range_value);
            Matrix m4 = genMatrix(size, range_value);
            tcs[i] = Arguments.of(m1, m2, m3, m4);
        }

        /* 将生成的测试用例保存到文件, 方便调试 */
        File file = new File("testcases.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            Matrix m1 = (Matrix) tcs[i].get()[0];
            Matrix m2 = (Matrix) tcs[i].get()[1];
            Matrix m3 = (Matrix) tcs[i].get()[1];
            Matrix m4 = (Matrix) tcs[i].get()[1];
            int size = m1.getNumberOfRows();

            writer.write("Testcase " + String.valueOf(i) + ":\n");
            writer.write("----------------------------------------------------------------\n");
            writer.write("Matrix 1:\n");
            for (int r = 0; r < size; r++) {
                for (int c = 0; c < size; c++) {
                    writer.write(String.valueOf((int) m1.getElement(r, c)) + ",");
                }
                writer.write("\n");
            }
            writer.write("\n");

            writer.write("Matrix 2:\n");
            for (int r = 0; r < size; r++) {
                for (int c = 0; c < size; c++) {
                    writer.write(String.valueOf((int) m2.getElement(r, c)) + ",");
                }
                writer.write("\n");
            }
            writer.write("\n");

            writer.write("Matrix 3:\n");
            for (int r = 0; r < size; r++) {
                for (int c = 0; c < size; c++) {
                    writer.write(String.valueOf((int) m3.getElement(r, c)) + ",");
                }
                writer.write("\n");
            }
            writer.write("\n");

            writer.write("Matrix 4:\n");
            for (int r = 0; r < size; r++) {
                for (int c = 0; c < size; c++) {
                    writer.write(String.valueOf((int) m4.getElement(r, c)) + ",");
                }
                writer.write("\n");
            }
            writer.write("\n");
        }
        writer.close();

        return Stream.of(tcs);
    }

    /**
     * 随机生成num个测试用例, 并保存到文件中 生成的测试用例为置换矩阵, 即元素只有0和1
     *
     * @param num
     * @return
     * @throws IOException
     */
    public static Stream<Arguments> generate_mpm(int num) throws IOException {
        int tcs_num = num;
        int[] range_size = {1, 5}; // 矩阵大小的范围, [1, 5)
        int[] range_value = {1, 5}; // 矩阵元素的范围, [1, 5)
        SecureRandom rand = new SecureRandom();
        Arguments[] tcs = new Arguments[tcs_num];

        /* 随机生成方阵 */
        for (int i = 0; i < tcs_num; i++) {
            int size = rand.nextInt(range_size[0], range_size[1]);
            Matrix m = genMatrix(size, range_value);
            Matrix pm = genMatrix(size, new int[] {0, 2});
            tcs[i] = Arguments.of(m, pm);
        }

        /* 将生成的测试用例保存到文件, 方便调试 */
        File file = new File("testcases.txt");
        FileWriter writer = new FileWriter(file);
        for (int i = 0; i < tcs_num; i++) {
            Matrix m = (Matrix) tcs[i].get()[0];
            Matrix pm = (Matrix) tcs[i].get()[1];

            int size = m.getNumberOfRows();
            writer.write("Testcase " + String.valueOf(i) + ":\n");
            writer.write("----------------------------------------------------------------\n");

            writer.write("Matrix:\n");
            for (int r = 0; r < size; r++) {
                for (int c = 0; c < size; c++) {
                    writer.write(String.valueOf((int) m.getElement(r, c)) + ",");
                }
                writer.write("\n");
            }
            writer.write("\n");

            writer.write("Permutation Matrix:\n");
            for (int r = 0; r < size; r++) {
                for (int c = 0; c < size; c++) {
                    writer.write(String.valueOf((int) pm.getElement(r, c)) + ",");
                }
                writer.write("\n");
            }
            writer.write("\n");
        }
        writer.close();

        return Stream.of(tcs);
    }

    /**
     * 随机生成num个测试用例, 保存到文件中 测试用例的内容为一个复数矩阵
     *
     * @param num
     * @return
     * @throws IOException
     */
    public static Stream<Arguments> generate_cm(int num) throws IOException {
        int tcs_num = num;
        int[] range_size = {1, 5}; // 矩阵大小的范围, [1, 5)
        int[] range_value = {1, 5}; // 矩阵元素的范围, [0, 5)
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
                    writer.write(
                            String.valueOf("(" + val.getReal() + "," + val.getImag() + ")" + ","));
                }
                writer.write("\n");
            }
            writer.write("\n");
        }
        writer.close();

        return Stream.of(tcs);
    }
}
