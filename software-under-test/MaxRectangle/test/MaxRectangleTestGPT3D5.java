package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static src.MaxRectangle.maximalRectangle;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.stream.Stream;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

public class MaxRectangleTestGPT3D5 {
    /**
     * Metamorphic Relation 1: Scaling all elements in the matrix by a positive constant factor should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Scale the matrix by a constant factor */
        int scaleFactor = 2;
        ArrayList<ArrayList<Integer>> scaled_matrix = new ArrayList<ArrayList<Integer>>();
        for (var row : matrix) {
            ArrayList<Integer> scaled_row = new ArrayList<Integer>();
            for (int elem : row) {
                scaled_row.add(elem * scaleFactor);
            }
            scaled_matrix.add(scaled_row);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(scaled_matrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Mrtamorphic Relation 2: Reversing the order of rows in the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Reverse the order of rows in the matrix */
        Collections.reverse(matrix);

        /* Get follow-up output */
        int follow_out = maximalRectangle(matrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 3: Transposing the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Transpose the matrix */
        ArrayList<ArrayList<Integer>> transposed_matrix = new ArrayList<>();
        for (int i = 0; i < matrix.get(0).size(); i++) {
            ArrayList<Integer> transposed_row = new ArrayList<>();
            for (ArrayList<Integer> row : matrix) {
                transposed_row.add(row.get(i));
            }
            transposed_matrix.add(transposed_row);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(transposed_matrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 4: Replacing all occurrences of 0 with 1 and 1 with 0 in the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Negate the matrix */
        ArrayList<ArrayList<Integer>> negated_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> negated_row = new ArrayList<>();
            for (int elem : row) {
                negated_row.add(1 - elem);
            }
            negated_matrix.add(negated_row);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(negated_matrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 5: Adding a constant value to all elements in the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Add a constant to all elements in the matrix */
        int constant = 2;
        ArrayList<ArrayList<Integer>> altered_matrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> altered_row = new ArrayList<>();
            for (int elem : row) {
                altered_row.add(elem + constant);
            }
            altered_matrix.add(altered_row);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(altered_matrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 6: Adding the same constant value to all columns in the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Add a constant to all columns in the matrix */
        int constant = 2;
        ArrayList<ArrayList<Integer>> altered_matrix = new ArrayList<>();
        for (int j = 0; j < matrix.get(0).size(); j++) {
            ArrayList<Integer> altered_col = new ArrayList<>();
            for (var row : matrix) {
                altered_col.add(row.get(j) + constant);
            }
            altered_matrix.add(altered_col);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(altered_matrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 7: Swapping any two rows in the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Swap two rows in the matrix */
        int row1 = 0;  // Choose the indices of the rows to swap
        int row2 = 1;
        Collections.swap(matrix, row1, row2);

        /* Get follow-up output */
        int follow_out = maximalRectangle(matrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 8: Shuffling the columns in the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Shuffle the columns in the matrix */
        ArrayList<ArrayList<Integer>> shuffled_matrix = new ArrayList<>();
        for (var row : matrix) {
            List<Integer> rowCopy = new ArrayList<>(row);
            Collections.shuffle(rowCopy);
            shuffled_matrix.add(new ArrayList<>(rowCopy));
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(shuffled_matrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 9: Adding a diagonal mirror image of the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Add a diagonal mirror image of the matrix */
        int rows = matrix.size();
        int cols = matrix.get(0).size();
        ArrayList<ArrayList<Integer>> mirrorMatrix = new ArrayList<>();
        for (int i = 0; i < rows; i++) {
            ArrayList<Integer> newRow = new ArrayList<>(Collections.nCopies(i, 0));
            for (int j = 0; j < cols; j++) {
                newRow.add(matrix.get(i).get(j));
            }
            for (int j = cols - 1; j >= 0; j--) {
                newRow.add(matrix.get(i).get(j));
            }
            for (int j = 0; j < cols - i - 1; j++) {
                newRow.add(0);
            }
            mirrorMatrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(mirrorMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 10: Reversing the order of columns in the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Reverse the order of columns in the matrix */
        ArrayList<ArrayList<Integer>> reversedColumnsMatrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> reversedRow = new ArrayList<>(row);
            Collections.reverse(reversedRow);
            reversedColumnsMatrix.add(reversedRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(reversedColumnsMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 11: Multiplying all elements in the matrix by -1 should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Multiply all elements in the matrix by -1 */
        ArrayList<ArrayList<Integer>> negatedMatrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> negatedRow = new ArrayList<>();
            for (int elem : row) {
                negatedRow.add(elem * -1);
            }
            negatedMatrix.add(negatedRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(negatedMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 12: Adding a row of all 0s to the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Add a row of all 0s to the matrix */
        int cols = matrix.get(0).size();
        ArrayList<Integer> zerosRow = new ArrayList<>(Collections.nCopies(cols, 0));
        ArrayList<ArrayList<Integer>> zerosMatrix = new ArrayList<>(matrix);
        zerosMatrix.add(zerosRow);

        /* Get follow-up output */
        int follow_out = maximalRectangle(zerosMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 13: Multiplying all elements in the matrix by a positive constant factor should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Scale the matrix by a constant factor */
        int scaleFactor = 2;
        ArrayList<ArrayList<Integer>> scaledMatrix = new ArrayList<>(matrix);
        for (int i = 0; i < scaledMatrix.size(); i++) {
            ArrayList<Integer> row = scaledMatrix.get(i);
            for (int j = 0; j < row.size(); j++) {
                row.set(j, row.get(j) * scaleFactor);
            }
            scaledMatrix.set(i, row);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(scaledMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 14: Adding the transpose of the matrix to itself should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Add the transpose of the matrix to itself */
        int rows = matrix.size();
        int cols = matrix.get(0).size();
        ArrayList<ArrayList<Integer>> addedMatrix = new ArrayList<>(matrix);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                addedMatrix.get(i).set(j, matrix.get(i).get(j) + matrix.get(j).get(i));
            }
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(addedMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 15: Multiplying a constant to all elements in the matrix and then adding another constant should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Multiply a constant to all elements in the matrix and then add another constant */
        int constant1 = 2;
        int constant2 = 3;
        ArrayList<ArrayList<Integer>> alteredMatrix = new ArrayList<>(matrix);
        for (int i = 0; i < alteredMatrix.size(); i++) {
            ArrayList<Integer> row = alteredMatrix.get(i);
            for (int j = 0; j < row.size(); j++) {
                row.set(j, row.get(j) * constant1 + constant2);
            }
            alteredMatrix.set(i, row);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(alteredMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 16: Flipping the elements of each row in the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Flip the elements of each row in the matrix */
        ArrayList<ArrayList<Integer>> flippedMatrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> flippedRow = new ArrayList<>(row);
            Collections.reverse(flippedRow);
            flippedMatrix.add(flippedRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(flippedMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 17: Reversing the order of elements in each row of the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Reverse the order of elements in each row of the matrix */
        ArrayList<ArrayList<Integer>> reversedElementsMatrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> reversedElementsRow = new ArrayList<>(row);
            Collections.reverse(reversedElementsRow);
            reversedElementsMatrix.add(reversedElementsRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(reversedElementsMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 18: Multiplying a constant to all elements in the matrix and then subtracting another constant should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Multiply a constant to all elements in the matrix and then subtract another constant */
        int constant1 = 3;
        int constant2 = 2;
        ArrayList<ArrayList<Integer>> alteredMatrix = new ArrayList<>(matrix);
        for (int i = 0; i < alteredMatrix.size(); i++) {
            ArrayList<Integer> row = alteredMatrix.get(i);
            for (int j = 0; j < row.size(); j++) {
                row.set(j, row.get(j) * constant1 - constant2);
            }
            alteredMatrix.set(i, row);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(alteredMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 19: Adding a constant value to all columns and rows in the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Add a constant to all columns and rows in the matrix */
        int constant = 2;
        ArrayList<ArrayList<Integer>> alteredMatrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> alteredRow = new ArrayList<>();
            for (int elem : row) {
                alteredRow.add(elem + constant);
            }
            alteredMatrix.add(alteredRow);
        }

        for (var row : alteredMatrix) {
            for (int i = 0; i < row.size(); i++) {
                row.set(i, row.get(i) + constant);
            }
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(alteredMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 20: Adding a row filled with the same constant should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Add a row filled with a constant to the matrix */
        int rows = matrix.size();
        int cols = matrix.get(0).size();
        int constant = 1;
        ArrayList<ArrayList<Integer>> alteredMatrix = new ArrayList<>(matrix);
        ArrayList<Integer> newRow = new ArrayList<>(Collections.nCopies(cols, constant));
        alteredMatrix.add(newRow);

        /* Get follow-up output */
        int follow_out = maximalRectangle(alteredMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 21: Adding a column filled with the same constant should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Add a column filled with a constant to the matrix */
        int constant = 1;
        ArrayList<ArrayList<Integer>> alteredMatrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> alteredRow = new ArrayList<>(row);
            alteredRow.add(constant);
            alteredMatrix.add(alteredRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(alteredMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 22: Multiplying the elements of each row by a constant should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Multiply the elements of each row by a constant */
        int constant = 2;
        ArrayList<ArrayList<Integer>> alteredMatrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> alteredRow = new ArrayList<>();
            for (int elem : row) {
                alteredRow.add(elem * constant);
            }
            alteredMatrix.add(alteredRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(alteredMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 23: Multiplying the elements of each column by a constant should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Multiply the elements of each column by a constant */
        int constant = 2;
        ArrayList<ArrayList<Integer>> alteredMatrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> alteredRow = new ArrayList<>();
            for (int elem : row) {
                alteredRow.add(elem);
            }
            alteredMatrix.add(alteredRow);
        }
        for (int j = 0; j < alteredMatrix.get(0).size(); j++) {
            for (int i = 0; i < alteredMatrix.size(); i++) {
                alteredMatrix.get(i).set(j, alteredMatrix.get(i).get(j) * constant);
            }
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(alteredMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 24: Doubling the size of the matrix by repeating the rows and columns should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Double the size of the matrix by repeating the rows and columns */
        int n = matrix.size();
        int m = matrix.get(0).size();
        ArrayList<ArrayList<Integer>> doubledMatrix = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            ArrayList<Integer> row = new ArrayList<>();
            for (int j = 0; j < m; j++) {
                row.add(matrix.get(i % n).get(j % m));
            }
            doubledMatrix.add(row);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(doubledMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 25: Rotating the matrix by 90 degrees in the clockwise direction should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Rotate the matrix by 90 degrees in the clockwise direction */
        int n = matrix.size();
        int m = matrix.get(0).size();
        ArrayList<ArrayList<Integer>> rotatedMatrix = new ArrayList<>();
        for (int j = 0; j < m; j++) {
            ArrayList<Integer> row = new ArrayList<>();
            for (int i = n - 1; i >= 0; i--) {
                row.add(matrix.get(i).get(j));
            }
            rotatedMatrix.add(row);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(rotatedMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 26: Replacing all occurrences of 0 with 1 and 1 with 0 in the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Replace all occurrences of 0 with 1 and 1 with 0 in the matrix */
        ArrayList<ArrayList<Integer>> alteredMatrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int elem : row) {
                if (elem == 0) {
                    newRow.add(1);
                } else {
                    newRow.add(0);
                }
            }
            alteredMatrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(alteredMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 27: Transforming the matrix by replacing each element with its square should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Transform the matrix by replacing each element with its square */
        ArrayList<ArrayList<Integer>> transformedMatrix = new ArrayList<>();
        for (var row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int elem : row) {
                newRow.add(elem * elem);
            }
            transformedMatrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(transformedMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 28: Adding an inverted diagonal mirror image of the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Add an inverted diagonal mirror image of the matrix */
        int rows = matrix.size();
        int cols = matrix.get(0).size();
        ArrayList<ArrayList<Integer>> invertedMirrorMatrix = new ArrayList<>();
        for (int i = 0; i < rows; i++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int j = 0; j < cols; j++) {
                if (i + j < rows) {
                    newRow.add(matrix.get(i + j).get(j));
                } else {
                    newRow.add(0);
                }
            }
            invertedMirrorMatrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(invertedMirrorMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 29: Adding a scalar product of the matrix with itself should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Add a scalar product of the matrix with itself */
        ArrayList<ArrayList<Integer>> scalarProductMatrix = new ArrayList<>();
        for (int i = 0; i < matrix.size(); i++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int j = 0; j < matrix.get(i).size(); j++) {
                newRow.add(matrix.get(i).get(j) * matrix.get(i).get(j));
            }
            scalarProductMatrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(scalarProductMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 30: Adding a row-wise running sum of the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Add a row-wise running sum of the matrix */
        ArrayList<ArrayList<Integer>> runningSumMatrix = new ArrayList<>();
        for (int i = 0; i < matrix.size(); i++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            int sum = 0;
            for (int j = 0; j < matrix.get(i).size(); j++) {
                sum += matrix.get(i).get(j);
                newRow.add(sum);
            }
            runningSumMatrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(runningSumMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 31: Sorting the elements of each row in the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Sort the elements of each row in the matrix */
        ArrayList<ArrayList<Integer>> sortedMatrix = new ArrayList<>();
        for (ArrayList<Integer> row : matrix) {
            ArrayList<Integer> sortedRow = new ArrayList<>(row);
            Collections.sort(sortedRow);
            sortedMatrix.add(sortedRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(sortedMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 32: Shifting all elements in the matrix row-wise should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Shift all elements in the matrix row-wise */
        ArrayList<ArrayList<Integer>> shiftedMatrix = new ArrayList<>();
        for (ArrayList<Integer> row : matrix) {
            int n = row.size();
            ArrayList<Integer> shiftedRow = new ArrayList<>(n);
            for (int i = 0; i < n; i++) {
                shiftedRow.add(row.get((i + 1) % n));
            }
            shiftedMatrix.add(shiftedRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(shiftedMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 33: Adding a symmetrical reflection of the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Add a symmetrical reflection of the matrix */
        int rows = matrix.size();
        int cols = matrix.get(0).size();
        ArrayList<ArrayList<Integer>> reflectedMatrix = new ArrayList<>();
        for (int i = 0; i < rows; i++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int j = 0; j < cols; j++) {
                newRow.add(matrix.get(i).get(j));
            }
            reflectedMatrix.add(newRow);
        }
        for (int i = rows-1; i >= 0; i--) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int j = cols-1; j >= 0; j--) {
                newRow.add(matrix.get(i).get(j));
            }
            reflectedMatrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(reflectedMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 34: Adding a horizontal flip of the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Add a horizontal flip of the matrix */
        int rows = matrix.size();
        int cols = matrix.get(0).size();
        ArrayList<ArrayList<Integer>> flippedMatrix = new ArrayList<>();
        for (int i = 0; i < rows; i++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int j = cols-1; j >= 0; j--) {
                newRow.add(matrix.get(i).get(j));
            }
            flippedMatrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(flippedMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 35: Adding a vertical flip of the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Add a vertical flip of the matrix */
        int rows = matrix.size();
        int cols = matrix.get(0).size();
        ArrayList<ArrayList<Integer>> flippedMatrix = new ArrayList<>();
        for (int i = rows-1; i >= 0; i--) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int j = 0; j < cols; j++) {
                newRow.add(matrix.get(i).get(j));
            }
            flippedMatrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(flippedMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 36: Adding a negative diagonal mirror image of the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Add a negative diagonal mirror image of the matrix */
        int rows = matrix.size();
        int cols = matrix.get(0).size();
        ArrayList<ArrayList<Integer>> negativeMirrorMatrix = new ArrayList<>();
        for (int i = 0; i < rows; i++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int j = 0; j < cols; j++) {
                if (i == j) {
                    newRow.add(matrix.get(i).get(j));
                } else {
                    newRow.add(-matrix.get(i).get(j));
                }
            }
            negativeMirrorMatrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(negativeMirrorMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 37: Multiplying each element in the matrix by the row number and column number should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Multiply each element in the matrix by the row number and column number */
        int rows = matrix.size();
        int cols = matrix.get(0).size();
        ArrayList<ArrayList<Integer>> transformedMatrix = new ArrayList<>();
        for (int i = 0; i < rows; i++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int j = 0; j < cols; j++) {
                newRow.add(matrix.get(i).get(j) * i * j);
            }
            transformedMatrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(transformedMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 38: Replacing all elements in the matrix with their absolute values should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Replace all elements in the matrix with their absolute values */
        ArrayList<ArrayList<Integer>> absMatrix = new ArrayList<>();
        for (ArrayList<Integer> row : matrix) {
            ArrayList<Integer> absRow = new ArrayList<>();
            for (int val : row) {
                absRow.add(Math.abs(val));
            }
            absMatrix.add(absRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(absMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 39: Adding a right diagonal mirror image of the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Add a right diagonal mirror image of the matrix */
        int rows = matrix.size();
        int cols = matrix.get(0).size();
        ArrayList<ArrayList<Integer>> rightMirrorMatrix = new ArrayList<>(Collections.nCopies(cols, new ArrayList<>(Collections.nCopies(rows, 0))));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                rightMirrorMatrix.get(j).set(i, matrix.get(i).get(j));
            }
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(rightMirrorMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 40: Adding a counter-diagonal mirror image of the matrix should not change the output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = maximalRectangle(matrix);

        /* Add a counter-diagonal mirror image of the matrix */
        int rows = matrix.size();
        int cols = matrix.get(0).size();
        ArrayList<ArrayList<Integer>> counterDiagonalMirrorMatrix = new ArrayList<>();
        for (int i = 0; i < rows; i++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int j = 0; j < cols; j++) {
                newRow.add(matrix.get(rows - i - 1).get(cols - j - 1));
            }
            counterDiagonalMirrorMatrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = maximalRectangle(counterDiagonalMirrorMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
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

