package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import src.MaxRectangle;

public class MaxRectangleTestGPT3D5 {

    /**
     * Metamorphic Relation 3: Reversing the rows should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>(matrix);
        Collections.reverse(follow_matrix);

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 4: Reversing the columns should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        int rowSize = matrix.size();
        int colSize = matrix.get(0).size();

        for (int i = 0; i < rowSize; i++) {
            ArrayList<Integer> newRow = new ArrayList<>(colSize);
            for (int j = colSize - 1; j >= 0; j--) {
                newRow.add(matrix.get(i).get(j));
            }
            follow_matrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 5: Scaling all elements in the matrix by a constant
     * factor should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input */
        double scaleFactor = 2.0;
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int val : row) {
                newRow.add((int) (val * scaleFactor));
            }
            follow_matrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 6: Shifting all elements in the matrix by a constant
     * value should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input */
        int shiftValue = 1;
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int val : row) {
                newRow.add(val + shiftValue);
            }
            follow_matrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 7: Replacing 0 with 1 and 1 with 0 in the matrix should
     * not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int val : row) {
                newRow.add(1 - val); // Replace 0 with 1 and 1 with 0
            }
            follow_matrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 8: Reordering the rows should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>(matrix);
        Collections.shuffle(follow_matrix);

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 9: Removing a row from the matrix should not increase
     * the output area.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input */
        if (matrix.size() > 1) {
            ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>(matrix);
            follow_matrix.remove(0); // Remove the first row

            /* Get follow-up output */
            int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

            /* Verification */
            assertTrue(follow_out <= source_out);
        }
    }

    /**
     * Metamorphic Relation 10: Removing a column from the matrix should not
     * increase the output area.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input */
        if (matrix.get(0).size() > 1) {
            ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
            for (var row : matrix) {
                ArrayList<Integer> newRow = new ArrayList<>(row);
                newRow.remove(0); // Remove the first column element
                follow_matrix.add(newRow);
            }

            /* Get follow-up output */
            int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

            /* Verification */
            assertTrue(follow_out <= source_out);
        }
    }

    /**
     * Metamorphic Relation 11: Swapping two rows in the matrix should not change
     * the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by swapping the first and last rows */
        if (matrix.size() >= 2) {
            ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>(matrix);
            Collections.swap(follow_matrix, 0, matrix.size() - 1);

            /* Get follow-up output */
            int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

            /* Verification */
            assertEquals(source_out, follow_out);
        }
    }

    /**
     * Metamorphic Relation 12: Replacing all elements with their absolute values
     * should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by taking absolute values of all elements */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int val : row) {
                newRow.add(Math.abs(val));
            }
            follow_matrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 13: Reversing the order of columns in the matrix should
     * not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by reversing the order of columns */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>(row);
            Collections.reverse(newRow);
            follow_matrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 14: Adding the transpose of the matrix to the original
     * matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /*
         * Construct follow-up input by adding the transpose of the matrix to the
         * original matrix
         */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        int rowSize = matrix.size();
        int colSize = matrix.get(0).size();

        for (int i = 0; i < rowSize; i++) {
            ArrayList<Integer> newRow = new ArrayList<>(colSize);
            for (int j = 0; j < colSize; j++) {
                newRow.add(matrix.get(i).get(j) + matrix.get(j).get(i)); // Add the transpose
            }
            follow_matrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 15: Adding a constant value to all elements in the
     * matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by adding a constant value to all elements
        int constantToAdd = 5;
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int val : row) {
                newRow.add(val + constantToAdd);
            }
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 16: Absolute value of the result should be the same when
     * all elements are negated.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = Math.abs(MaxRectangle.maximalRectangle(matrix));

        // Construct follow-up input by negating all elements
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int val : row) {
                newRow.add(-val);
            }
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = Math.abs(MaxRectangle.maximalRectangle(follow_matrix));

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 17: Multiplying all elements in the matrix by a constant
     * factor should result in the output being multiplied by the same factor.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by multiplying all elements in the matrix by a
        // constant factor
        int scaleFactor = 3;
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int val : row) {
                newRow.add(val * scaleFactor);
            }
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out * scaleFactor, follow_out);
    }

    /**
     * Metamorphic Relation 18: The result should be the same when the rows of the
     * matrix are sorted in ascending order based on the sum of their elements.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by sorting the rows based on the sum of their
        // elements
        ArrayList<ArrayList<Integer>> follow_matrix = matrix.stream()
                .sorted(Comparator.comparing(row -> row.stream().mapToInt(Integer::intValue).sum()))
                .collect(Collectors.toCollection(ArrayList::new));

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 19: Adding a constant value to each row in the matrix
     * should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by adding a constant value to each row
        int constantToAdd = 5;
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int val : row) {
                newRow.add(val + constantToAdd);
            }
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 20: The output should remain the same when removing
     * duplicates from each row in the matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by removing duplicates from each row
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = row.stream()
                    .distinct()
                    .collect(Collectors.toCollection(ArrayList::new));
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 21: If we shuffle the columns of the matrix, the output
     * should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by shuffling the columns of the matrix
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        int rows = matrix.size();
        int cols = matrix.get(0).size();
        ArrayList<Integer> columnIndexes = new ArrayList<>();
        for (int i = 0; i < cols; i++) {
            columnIndexes.add(i);
        }
        Collections.shuffle(columnIndexes);
        for (int i = 0; i < rows; i++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int j = 0; j < cols; j++) {
                newRow.add(matrix.get(i).get(columnIndexes.get(j)));
            }
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 22: Adding a constant value to all elements of the
     * matrix and then multiplying all elements by another constant should not
     * change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by adding a constant and then multiplying by
        // another constant
        int constantToAdd = 3;
        int multiplyBy = 2;
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int val : row) {
                newRow.add((val + constantToAdd) * multiplyBy);
            }
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 23: If we reverse the order of the elements in each row,
     * the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by reversing the elements in each row
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>(row);
            Collections.reverse(newRow);
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 24: If we apply a bitwise complement to every element in
     * the matrix, the output should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by applying bitwise complement to every element
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int val : row) {
                newRow.add(~val);
            }
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 25: Mirroring the matrix horizontally or vertically
     * should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by mirroring the matrix horizontally
        ArrayList<ArrayList<Integer>> mirrorHorizontal = new ArrayList<>();
        for (int i = matrix.size() - 1; i >= 0; i--) {
            mirrorHorizontal.add(matrix.get(i));
        }

        // Get follow-up output
        int follow_out1 = MaxRectangle.maximalRectangle(mirrorHorizontal);

        // Verification
        assertEquals(source_out, follow_out1);

        // Construct follow-up input by mirroring the matrix vertically
        ArrayList<ArrayList<Integer>> mirrorVertical = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>(row);
            Collections.reverse(newRow);
            mirrorVertical.add(newRow);
        }

        // Get follow-up output
        int follow_out2 = MaxRectangle.maximalRectangle(mirrorVertical);

        // Verification
        assertEquals(source_out, follow_out2);
    }

    /**
     * Metamorphic Relation 26: Dividing each element in the matrix by a constant
     * factor should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by dividing each element by a constant factor
        int divisor = 2;
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int val : row) {
                newRow.add(val / divisor);
            }
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 27: Multiplying a row by a constant factor should result
     * in the same scaled output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by multiplying a row by a constant factor
        int rowIndex = 0; // Choose the first row for demonstration
        int scaleFactor = 3;
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (int i = 0; i < matrix.size(); i++) {
            ArrayList<Integer> newRow = new ArrayList<>(matrix.get(i));
            if (i == rowIndex) {
                for (int j = 0; j < newRow.size(); j++) {
                    newRow.set(j, newRow.get(j) * scaleFactor);
                }
            }
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out * scaleFactor, follow_out);
    }

    /**
     * Metamorphic Relation 28: Rotating the matrix 90 degrees should not change the
     * output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by rotating the matrix 90 degrees
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        int rowSize = matrix.size();
        int colSize = matrix.get(0).size();

        for (int j = 0; j < colSize; j++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int i = rowSize - 1; i >= 0; i--) {
                newRow.add(matrix.get(i).get(j));
            }
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 29: Multiplying each column by a constant factor should
     * result in the same scaled output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by multiplying each column by a constant factor
        int scaleFactor = 2;
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (int j = 0; j < matrix.get(0).size(); j++) {
            ArrayList<Integer> newColumn = new ArrayList<>();
            for (int i = 0; i < matrix.size(); i++) {
                newColumn.add(matrix.get(i).get(j) * scaleFactor);
            }
            follow_matrix.add(newColumn);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out * scaleFactor, follow_out);
    }

    /**
     * Metamorphic Relation 30: Sorting the matrix in ascending order should not
     * change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by sorting the matrix in ascending order
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>(matrix);
        follow_matrix.sort(Comparator.comparing(Object::toString));

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 31: Transposing the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by transposing the matrix
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        int rowSize = matrix.size();
        int colSize = matrix.get(0).size();

        for (int j = 0; j < colSize; j++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int i = 0; i < rowSize; i++) {
                newRow.add(matrix.get(i).get(j));
            }
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 32: The output should remain unchanged when the matrix
     * is multiplied by its own transpose.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by multiplying the matrix by its own transpose
        ArrayList<ArrayList<Integer>> transpose = new ArrayList<>();
        int rowSize = matrix.size();
        int colSize = matrix.get(0).size();

        for (int j = 0; j < colSize; j++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int i = 0; i < rowSize; i++) {
                newRow.add(matrix.get(i).get(j));
            }
            transpose.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(multiplyMatrices(matrix, transpose));

        // Verification
        assertEquals(source_out, follow_out);
    }

    // Helper function for matrix multiplication
    private ArrayList<ArrayList<Integer>> multiplyMatrices(ArrayList<ArrayList<Integer>> A,
            ArrayList<ArrayList<Integer>> B) {
        int m1 = A.size();
        int n1 = A.get(0).size();
        int m2 = B.size();
        int n2 = B.get(0).size();
        assert n1 == m2;

        ArrayList<ArrayList<Integer>> result = new ArrayList<>();
        for (int i = 0; i < m1; i++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int j = 0; j < n2; j++) {
                int sum = 0;
                for (int k = 0; k < n1; k++) {
                    sum += A.get(i).get(k) * B.get(k).get(j);
                }
                newRow.add(sum);
            }
            result.add(newRow);
        }
        return result;
    }

    /**
     * Metamorphic Relation 33: Applying a constant value to the entire matrix
     * should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by adding a constant to the entire matrix
        int constantToAdd = 5;
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int val : row) {
                newRow.add(val + constantToAdd);
            }
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 34: Concatenating the matrix with itself should not
     * change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by concatenating the matrix with itself
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        follow_matrix.addAll(matrix);
        follow_matrix.addAll(matrix);

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 35: Replacing all elements with a constant value should
     * not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by replacing all elements with a constant value
        int constantValue = 2;
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (int i = 0; i < matrix.size(); i++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int j = 0; j < matrix.get(0).size(); j++) {
                newRow.add(constantValue);
            }
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 36: The result should remain the same when every element
     * is raised to a power.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by raising every element to the power of 2
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int val : row) {
                newRow.add((int) Math.pow(val, 2));
            }
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 37: Applying a scalar multiplication to a row should
     * affect the output in the same way.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by multiplying a specific row by a scalar
        int rowIndex = 0; // Choose the first row for demonstration
        int scalarMultiplier = 4;
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>(matrix);
        ArrayList<Integer> newRow = new ArrayList<>();
        for (int val : matrix.get(rowIndex)) {
            newRow.add(val * scalarMultiplier);
        }
        follow_matrix.set(rowIndex, newRow);

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out * scalarMultiplier, follow_out);
    }

    /**
     * Metamorphic Relation 38: Replacing all elements with their squares should not
     * change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by replacing all elements with their squares
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int val : row) {
                newRow.add(val * val);
            }
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 39: Flipping the signs of the elements in the matrix
     * should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by flipping the signs of the elements in the matrix
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int val : row) {
                newRow.add(-val);
            }
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 40: Taking the square root of each element in the matrix
     * and then squaring the results should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by taking the square root of each element and then
        // squaring the results
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int val : row) {
                newRow.add((int) Math.pow(Math.sqrt(val), 2));
            }
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 41: If we add a constant value to each element and then
     * subtract the same constant value, the output should remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test41(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input
        int constant = 5;
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int val : row) {
                newRow.add(val + constant - constant);
            }
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 42: Repeating the matrix multiple times (e.g.,
     * concatenating it with itself) should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test42(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input by repeating the matrix (concatenating it with
        // itself)
        int times = 3;
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (int i = 0; i < times; i++) {
            follow_matrix.addAll(matrix);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 43: If we add a matrix to its transposition, the output
     * should be the same as adding the transposed result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test43(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input
        ArrayList<ArrayList<Integer>> transposedMatrix = transposeMatrix(matrix);
        ArrayList<ArrayList<Integer>> follow_matrix = addMatrices(matrix, transposedMatrix);

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 44: Adding a constant value to each element of the
     * matrix and then multiplying the result by the same constant should not change
     * the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test44(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Construct follow-up input
        int constant = 3;
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int val : row) {
                newRow.add((val + constant) * constant);
            }
            follow_matrix.add(newRow);
        }

        // Get follow-up output
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        // Verification
        assertEquals(source_out, follow_out);
    }

    // Helper function for matrix transposition
    private ArrayList<ArrayList<Integer>> transposeMatrix(ArrayList<ArrayList<Integer>> matrix) {
        ArrayList<ArrayList<Integer>> transposedMatrix = new ArrayList<>();
        for (int i = 0; i < matrix.get(0).size(); i++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (ArrayList<Integer> integers : matrix) {
                newRow.add(integers.get(i));
            }
            transposedMatrix.add(newRow);
        }
        return transposedMatrix;
    }

    // Helper function for matrix addition
    private ArrayList<ArrayList<Integer>> addMatrices(ArrayList<ArrayList<Integer>> matrixA,
            ArrayList<ArrayList<Integer>> matrixB) {
        ArrayList<ArrayList<Integer>> result = new ArrayList<>();
        for (int i = 0; i < matrixA.size(); i++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int j = 0; j < matrixA.get(0).size(); j++) {
                newRow.add(matrixA.get(i).get(j) + matrixB.get(i).get(j));
            }
            result.add(newRow);
        }
        return result;
    }

    /**
     * Metamorphic Relation 45: If we apply a linear transformation on the matrix,
     * the output should be the same as applying the transformation on the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test45(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Apply a linear transformation to the matrix
        int a = 2;
        int b = 3;
        ArrayList<ArrayList<Integer>> transformedMatrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int val : row) {
                newRow.add(a * val + b);
            }
            transformedMatrix.add(newRow);
        }

        // Get output after transformation
        int transformed_out = MaxRectangle.maximalRectangle(transformedMatrix);

        // Verification
        assertEquals(source_out, a * transformed_out + b);
    }

    /**
     * Metamorphic Relation 46: Replacing all elements with their cube should not
     * change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test46(ArrayList<ArrayList<Integer>> matrix) {
        // Get source output
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Replace all elements with their cube
        ArrayList<ArrayList<Integer>> transformedMatrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int val : row) {
                newRow.add(val * val * val);
            }
            transformedMatrix.add(newRow);
        }

        // Get output after transformation
        int transformed_out = MaxRectangle.maximalRectangle(transformedMatrix);

        // Verification
        assertEquals(source_out, transformed_out);
    }

    /**
     * 随机生成测试用例
     *
     * @return
     * @throws Exception
     */
    public static Stream<Arguments> testcaseProvider() throws Exception {
        return testcaseGenerator.generate(1000);
    }
}
