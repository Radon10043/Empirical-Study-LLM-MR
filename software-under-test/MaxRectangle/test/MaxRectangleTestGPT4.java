package test;

import static org.junit.Assume.assumeTrue;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.util.ArrayList;
import java.util.Collections;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import src.MaxRectangle;

public class MaxRectangleTestGPT4 {
    /**
     * Metamorphic Relation 3: Flipping 0s to 1s within a row should result in the same or larger
     * output because the largest rectangle area can only increase or stay the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by flipping 0s to 1s in one row */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<ArrayList<Integer>>();
        for (ArrayList<Integer> row : matrix) {
            ArrayList<Integer> new_row = new ArrayList<Integer>();
            for (Integer cell : row) {
                // Flip 0 to 1, leave 1 unchanged
                new_row.add(cell.equals(0) ? 1 : cell);
            }
            follow_matrix.add(new_row);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 4: Permuting the order of the rows should not affect the output; the
     * area of the largest rectangle remains the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by permuting the rows */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<ArrayList<Integer>>(matrix);
        Collections.shuffle(follow_matrix);

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(follow_out, source_out);
    }

    /**
     * Metamorphic Relation 5: Scaling the matrix by duplicating each row and column should result
     * in a new area that is exactly four times the original one, as each 1x1 rectangle is
     * transformed into a 2x2 rectangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by scaling the matrix */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<ArrayList<Integer>>();
        for (ArrayList<Integer> row : matrix) {
            // Duplicate each row
            ArrayList<Integer> new_row = new ArrayList<Integer>();
            for (Integer element : row) {
                new_row.add(element);
                new_row.add(element); // Duplicate each column element
            }
            follow_matrix.add(new_row);
            follow_matrix.add(new ArrayList<Integer>(new_row)); // Duplicate the duplicated row
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(follow_out, 4 * source_out);
    }

    /**
     * Metamorphic Relation 6: Transposing the matrix should not affect the output; the area of the
     * largest rectangle is preserved through the transpose operation.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by transposing the matrix */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (int i = 0; i < matrix.get(0).size(); i++) { // Iterate over columns
            ArrayList<Integer> newRow = new ArrayList<>();
            for (ArrayList<Integer> row : matrix) { // Iterate over rows
                newRow.add(row.get(i)); // Add the element at current column from each row
            }
            follow_matrix.add(newRow); // Add new row to the transposed matrix
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(follow_out, source_out);
    }

    /**
     * Metamorphic Relation 7: Removing a row containing only zeros should not affect the output;
     * the area of the largest rectangle remains the same as zero-rows do not contribute to it.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by removing a row of zeros (if exists) */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<ArrayList<Integer>>();
        for (ArrayList<Integer> row : matrix) {
            if (!row.contains(1)) {
                // Skip the row if it contains only zeros
                continue;
            }
            follow_matrix.add(new ArrayList<Integer>(row));
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(follow_out, source_out);
    }

    /**
     * Metamorphic Relation 8: Inverting the values in the matrix (0s to 1s and 1s to 0s) in a fully
     * filled row or column should not change the output as the largest rectangle should include the
     * entire row or column, respectively.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /*
         * Construct follow-up input by inverting values in rows or columns that are fully filled
         */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<ArrayList<Integer>>();
        for (ArrayList<Integer> row : matrix) {
            ArrayList<Integer> new_row = new ArrayList<Integer>();
            boolean isRowFullyFilled = !row.contains(0);
            for (Integer cell : row) {
                new_row.add((isRowFullyFilled ? 0 : cell));
            }
            follow_matrix.add(new_row);
        }

        // Check and invert the columns
        for (int i = 0; i < matrix.get(0).size(); i++) {
            boolean isColumnFullyFilled = true;
            for (ArrayList<Integer> row : follow_matrix) {
                if (row.get(i).equals(0)) {
                    isColumnFullyFilled = false;
                    break;
                }
            }
            if (isColumnFullyFilled) {
                for (ArrayList<Integer> row : follow_matrix) {
                    row.set(i, 0); // Invert column values
                }
            }
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(follow_out, source_out);
    }

    /**
     * Metamorphic Relation 9: Reflecting the matrix horizontally (i.e., reversing the order in each
     * row) should not affect the output; the area of the largest rectangle remains unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by reflecting the matrix horizontally */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<ArrayList<Integer>>();
        for (ArrayList<Integer> row : matrix) {
            ArrayList<Integer> reflected_row = new ArrayList<Integer>(row);
            Collections.reverse(reflected_row);
            follow_matrix.add(reflected_row);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(follow_out, source_out);
    }

    /**
     * Metamorphic Relation 10: Reflecting the matrix vertically (i.e., reversing the order of the
     * rows) should not affect the output; the area of the largest rectangle remains unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by reflecting the matrix vertically */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<ArrayList<Integer>>(matrix);
        Collections.reverse(follow_matrix);

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(follow_out, source_out);
    }

    /**
     * Metamorphic Relation 11: Exchanging the rows of the matrix with the columns (i.e., reshaping
     * the matrix) but keeping the total number of 1s the same should result in the output being
     * either the same or different, but it cannot exceed the number of 1s as this represents the
     * maximal area that can be achieved.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by exchanging rows with columns */
        int numberOfOnes = 0;
        for (ArrayList<Integer> row : matrix) {
            numberOfOnes += Collections.frequency(row, 1);
        }
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<ArrayList<Integer>>();
        for (int i = 0; i < matrix.get(0).size(); i++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (ArrayList<Integer> row : matrix) {
                newRow.add(row.get(i));
            }
            follow_matrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertTrue(follow_out == source_out || follow_out <= numberOfOnes);
    }

    /**
     * Metamorphic Relation 12: Carving a "path" of 0s from the lower right to the upper left should
     * not create a larger area than the original output as the largest rectangle cannot traverse a
     * path of 0s.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input */
        int height = matrix.size();
        int width = matrix.get(0).size();
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<ArrayList<Integer>>();
        for (int i = 0; i < height; i++) {
            ArrayList<Integer> newRow = new ArrayList<Integer>(matrix.get(i));
            if (width - i - 1 < width) {
                newRow.set(width - i - 1, 0); // Carving a path starting from bottom-right to
                                              // top-left
            }
            follow_matrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertTrue(follow_out <= source_out);
    }

    /**
     * Metamorphic Relation 13: Adding a border of zeros around the matrix should not affect the
     * output. The area of the largest rectangle remains the same as the zeros do not contribute to
     * it.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /*
         * Construct follow-up input by adding a border of zeros around the original matrix
         */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<ArrayList<Integer>>();

        // Add the top border
        follow_matrix.add(new ArrayList<Integer>(Collections.nCopies(matrix.get(0).size() + 2, 0)));

        for (ArrayList<Integer> row : matrix) {
            ArrayList<Integer> new_row = new ArrayList<Integer>();
            new_row.add(0); // left border
            new_row.addAll(row);
            new_row.add(0); // right border
            follow_matrix.add(new_row);
        }

        // Add the bottom border
        follow_matrix.add(new ArrayList<Integer>(Collections.nCopies(matrix.get(0).size() + 2, 0)));

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(follow_out, source_out);
    }

    /**
     * Metamorphic Relation 14: Doubling each cell in the matrix should double the length and width
     * of the largest rectangle, resulting in a new area that is exactly four times the original
     * area.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by doubling each cell in the matrix */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<ArrayList<Integer>>();
        for (ArrayList<Integer> row : matrix) {
            ArrayList<Integer> new_row = new ArrayList<Integer>();
            for (Integer cell : row) {
                new_row.add(cell);
                new_row.add(cell); // Double the cell horizontally
            }
            follow_matrix.add(new_row); // Add the original cells
            follow_matrix.add(new ArrayList<Integer>(new_row)); // Double the cell vertically
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(follow_out, 4 * source_out);
    }

    /**
     * Metamorphic Relation 15: In a matrix with at least one rectangle of ones, removing a single
     * '1' would either decrease the area of the largest rectangle or leave it unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Ensure matrix has at least one '1' to remove
        boolean containsOne = matrix.stream().anyMatch(row -> row.contains(1));

        if (!containsOne) {
            return; // Skip this test as it requires at least one '1' in the matrix
        }

        /* Construct follow-up input by removing a single '1' from the matrix */
        boolean removed = false;
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<ArrayList<Integer>>();
        for (ArrayList<Integer> row : matrix) {
            ArrayList<Integer> new_row = new ArrayList<Integer>();
            for (Integer cell : row) {
                if (cell.equals(1) && !removed) {
                    // Remove one '1'
                    new_row.add(0);
                    removed = true;
                } else {
                    new_row.add(cell);
                }
            }
            follow_matrix.add(new_row);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertTrue(follow_out <= source_out);
    }

    /**
     * Metamorphic Relation 16: Concatenating two matrices horizontally with a column of zeros
     * between them, the new output should be the same as the maximum of the output of the
     * individual matrices.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out_matrix1 = MaxRectangle.maximalRectangle(matrix);
        int source_out_matrix2 = MaxRectangle.maximalRectangle(matrix); // Assume a duplicate of the
                                                                        // matrix for
                                                                        // demonstration

        /*
         * Construct follow-up input by concatenating two matrices horizontally with a column of
         * zeros between
         */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<ArrayList<Integer>>();
        for (int i = 0; i < matrix.size(); i++) {
            ArrayList<Integer> new_row = new ArrayList<>(matrix.get(i)); // First matrix
            new_row.add(0); // Column of zeros
            new_row.addAll(matrix.get(i)); // Second matrix
            follow_matrix.add(new_row);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(follow_out, Math.max(source_out_matrix1, source_out_matrix2));
    }

    /**
     * Metamorphic Relation 17: For a non-empty matrix, setting all cells to 1 should result in an
     * area equal to the product of the number of rows and columns since the largest rectangle would
     * cover the entire matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(ArrayList<ArrayList<Integer>> matrix) {
        int rows = matrix.size();
        int columns = matrix.get(0).size();

        /* Construct follow-up input where all cells are set to 1 */
        ArrayList<ArrayList<Integer>> allOnesMatrix = new ArrayList<>();
        for (int i = 0; i < rows; i++) {
            ArrayList<Integer> newRow = new ArrayList<>(Collections.nCopies(columns, 1));
            allOnesMatrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(allOnesMatrix);

        /* Verification */
        assertEquals(follow_out, rows * columns);
    }

    /**
     * Metamorphic Relation 18: Removing any row from the matrix should result in the output being
     * the same as or smaller than the original output, as the potential largest rectangle could
     * either remain unchanged or be reduced in size.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(ArrayList<ArrayList<Integer>> matrix) {
        if (matrix.size() <= 1) {
            return; // Skip the test if the matrix has one or fewer rows
        }

        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by removing a single row */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>(matrix);
        follow_matrix.remove(0); // Remove the first row for simplicity

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertTrue(follow_out <= source_out);
    }

    /**
     * Metamorphic Relation 19: Swapping any two rows in the matrix should not affect the output, as
     * the area calculation is indifferent to the order of the rows.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(ArrayList<ArrayList<Integer>> matrix) {
        if (matrix.size() < 2) {
            return; // Skip the test if the matrix has fewer than 2 rows
        }

        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by swapping two rows */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>(matrix);
        // Swap the first two rows for simplicity
        Collections.swap(follow_matrix, 0, 1);

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(follow_out, source_out);
    }

    /**
     * Metamorphic Relation 20: Inverting the value of all cells in the matrix (0s to 1s, 1s to 0s)
     * should not result in a larger area than the total number of 1s in the original matrix. This
     * is because the largest rectangle of 1s is limited by the number of 1s before inversion.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);
        int numberOfOnes = 0;

        /* Count the number of ones in the original matrix */
        for (ArrayList<Integer> row : matrix) {
            numberOfOnes += Collections.frequency(row, 1);
        }

        /* Construct follow-up input by inverting all cell values */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (ArrayList<Integer> row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (Integer cell : row) {
                newRow.add(cell.equals(1) ? 0 : 1);
            }
            follow_matrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertTrue(follow_out <= numberOfOnes);
    }

    /**
     * Metamorphic Relation 21: Rotating the matrix 90 degrees clockwise should not change the
     * output, as the area of the largest rectangle is preserved through the rotation.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by rotating the matrix 90 degrees clockwise */
        int totalRows = matrix.size();
        int totalCols = (totalRows > 0) ? matrix.get(0).size() : 0;
        ArrayList<ArrayList<Integer>> rotated_matrix = new ArrayList<ArrayList<Integer>>();

        for (int col = 0; col < totalCols; col++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int row = totalRows - 1; row >= 0; row--) {
                newRow.add(matrix.get(row).get(col));
            }
            rotated_matrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(rotated_matrix);

        /* Verification */
        assertEquals(follow_out, source_out);
    }

    /**
     * Metamorphic Relation 22: Inverting a single row's elements from 0 to 1 and vice versa should
     * not result in an area larger than a rectangle that covers the entire inverted row plus the
     * area of the original output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by inverting a single row's elements */
        ArrayList<ArrayList<Integer>> inverted_matrix = new ArrayList<>(matrix);
        for (int col = 0; col < inverted_matrix.get(0).size(); col++) {
            Integer currentValue = inverted_matrix.get(0).get(col);
            inverted_matrix.get(0).set(col, currentValue.equals(0) ? 1 : 0); // Invert the first row
                                                                             // for simplicity
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(inverted_matrix);

        /* Verification */
        int expected_max_area = matrix.get(0).size() + source_out; // Area of the entire row plus
                                                                   // original area
        assertTrue(follow_out <= expected_max_area);
    }

    /**
     * Metamorphic Relation 23: If the input matrix is a square (number of rows equals the number of
     * columns) and consists entirely of 1s, then partitioning it into four equal smaller squares
     * should give an output four times smaller than the input's output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(ArrayList<ArrayList<Integer>> matrix) { // Fixed
        int totalRows = matrix.size();
        int totalCols = matrix.get(0).size();
        matrix.clear();
        for (int col = 0; col < totalCols; col++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int row = 0; row < totalRows; row++) {
                newRow.add(1);
            }
            matrix.add(newRow);
        }

        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        // Check if the matrix is a square and full of 1s
        boolean isSquareFullOfOnes = (matrix.size() == matrix.get(0).size()
                && source_out == (matrix.size() * matrix.size()));

        if (!isSquareFullOfOnes) {
            return; // Skip the test if the matrix is not a square full of 1s
        }

        /*
         * Construct follow-up input by partitioning the square matrix into four equal squares
         */
        int newSize = matrix.size() / 2; // half the size of the original matrix
        ArrayList<ArrayList<Integer>> partitioned_matrix = new ArrayList<>();
        for (int i = 0; i < newSize; i++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int j = 0; j < newSize; j++) {
                newRow.add(matrix.get(i).get(j));
            }
            partitioned_matrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(partitioned_matrix);

        /* Verification */
        assertEquals(follow_out, source_out / 4);
    }

    /**
     * Metamorphic Relation 24: Reducing the size of the input matrix by removing trailing rows and
     * columns filled only with 0s should not affect the output, as those elements do not contribute
     * to the area of the largest rectangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(ArrayList<ArrayList<Integer>> matrix) { // Fixed
        assumeTrue(matrix.size() > 1);

        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /*
         * Construct follow-up input by removing trailing rows and columns filled with 0s
         */
        while (!matrix.isEmpty() && Collections.frequency(matrix.get(matrix.size() - 1),
                0) == matrix.get(0).size()) {
            // Remove trailing row if it's full of 0s
            matrix.remove(matrix.size() - 1);
        }
        if (!matrix.isEmpty()) {
            while (Collections.frequency(matrix.stream().map(row -> row.get(row.size() - 1))
                    .collect(Collectors.toList()), 0) == matrix.size()) {
                // Remove trailing column if it's full of 0s
                for (ArrayList<Integer> row : matrix) {
                    row.remove(row.size() - 1);
                }
            }
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(matrix);

        /* Verification */
        assertEquals(follow_out, source_out);
    }

    /**
     * Metamorphic Relation 25: Expanding the matrix by adding rows and columns of zeros should not
     * affect the output. The area of the largest rectangle remains the same as the zeros do not
     * contribute to it.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by adding rows and columns of zeros */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        int additionalSize = 2; // Number of rows/columns to add

        for (ArrayList<Integer> row : matrix) {
            ArrayList<Integer> new_row = new ArrayList<>(row);
            for (int i = 0; i < additionalSize; i++) {
                new_row.add(0); // Add zeros at the end of the row
            }
            follow_matrix.add(new_row);
        }

        ArrayList<Integer> zeroRow =
                new ArrayList<>(Collections.nCopies(matrix.get(0).size() + additionalSize, 0));
        for (int i = 0; i < additionalSize; i++) {
            follow_matrix.add(zeroRow); // Add full rows of zeros at the bottom
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(follow_out, source_out);
    }

    /**
     * Metamorphic Relation 26: Concatenating a matrix with itself (side by side) without any
     * separation should result in the largest area being at most double the original area if and
     * only if the largest rectangle does not span the entire width of the original matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        int matrixWidth = matrix.get(0).size();

        /* Construct follow-up input by concatenating the matrix with itself */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>();
        for (ArrayList<Integer> row : matrix) {
            ArrayList<Integer> new_row = new ArrayList<>(row);
            new_row.addAll(row);
            follow_matrix.add(new_row);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        if (source_out < matrixWidth) {
            assertTrue(follow_out <= 2 * source_out);
        } else {
            assertEquals(follow_out, source_out);
        }
    }

    /**
     * Metamorphic Relation 27: Subtracting a rectangle of '1's within the matrix should result in
     * the output area being at least the size of subtracted rectangle less than the original
     * output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Define the size and position of the rectangle of '1's to remove */
        int removeRowCount = 1; // Number of rows to remove '1's
        int removeColumnCount = 2; // Number of columns to remove '1's

        /* Construct follow-up input by subtracting a rectangle of '1's */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>(matrix);
        int rows = follow_matrix.size();
        // Remove '1's starting from (1,1) position
        for (int i = 1; i < 1 + removeRowCount && i < rows; i++) {
            ArrayList<Integer> newRow = new ArrayList<>(follow_matrix.get(i));
            for (int j = 1; j < 1 + removeColumnCount && j < newRow.size(); j++) {
                newRow.set(j, 0);
            }
            follow_matrix.set(i, newRow);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertTrue(follow_out <= source_out - (removeRowCount * removeColumnCount));
    }

    /**
     * Metamorphic Relation 28: Applying a NOT operation (1s to 0s, 0s to 1s) to part of a row
     * should either decrease the area or keep it the same, but not increase it.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by applying NOT operation to part of a row */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>(matrix);
        ArrayList<Integer> modifiedRow = new ArrayList<>(follow_matrix.get(0));
        for (int i = 0; i < modifiedRow.size(); i++) {
            modifiedRow.set(i, modifiedRow.get(i) == 0 ? 1 : 0);
        }
        follow_matrix.set(0, modifiedRow);

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertTrue(follow_out <= source_out);
    }

    /**
     * Metamorphic Relation 29: Mirroring the matrix vertically and then horizontally should not
     * change the output, since these operations are essentially equivalent to a 180-degree
     * rotation.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Perform vertical mirror */
        ArrayList<ArrayList<Integer>> verticallyMirrored = new ArrayList<>(matrix);
        Collections.reverse(verticallyMirrored);

        /* Perform horizontal mirror */
        ArrayList<ArrayList<Integer>> mirroredMatrix = new ArrayList<>();
        for (ArrayList<Integer> row : verticallyMirrored) {
            ArrayList<Integer> mirroredRow = new ArrayList<>(row);
            Collections.reverse(mirroredRow);
            mirroredMatrix.add(mirroredRow);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(mirroredMatrix);

        /* Verification */
        assertEquals(follow_out, source_out);
    }

    /**
     * Metamorphic Relation 30: Extracting a submatrix and testing it should yield an area less than
     * or equal to the source output, assuming the submatrix contains part of the source’s largest
     * rectangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(ArrayList<ArrayList<Integer>> matrix) {
        /* Check if matrix is suitable for submatrix extraction */
        if (matrix.size() <= 1 || matrix.get(0).size() <= 1) {
            return; // Skip test if matrix is too small
        }

        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Define submatrix bounds */
        int startRow = matrix.size() / 2;
        int endRow = Math.min(matrix.size(), startRow + 2);
        int startCol = matrix.get(0).size() / 2;
        int endCol = Math.min(matrix.get(0).size(), startCol + 2);

        /* Extract submatrix */
        ArrayList<ArrayList<Integer>> submatrix = new ArrayList<>();
        for (int i = startRow; i < endRow; i++) {
            ArrayList<Integer> newRow = new ArrayList<>(matrix.get(i).subList(startCol, endCol));
            submatrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(submatrix);

        /* Verification */
        assertTrue(follow_out <= source_out);
    }

    /**
     * Metamorphic Relation 31: Replicating a row to the bottom of the matrix should only maintain
     * or increase the output area, depending on whether the duplicated row contains a portion of
     * the maximal rectangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Replicate a row */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>(matrix);
        follow_matrix.add(new ArrayList<>(matrix.get(matrix.size() - 1))); // Duplicate the last row

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 32: Exchanging the contents of two columns should not affect the output,
     * since the area calculation is indifferent to the order of columns.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(ArrayList<ArrayList<Integer>> matrix) {
        if (matrix.get(0).size() < 2) {
            return; // Skip the test if the matrix has fewer than 2 columns
        }

        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by swapping two columns */
        ArrayList<ArrayList<Integer>> follow_matrix = new ArrayList<>(matrix);
        for (ArrayList<Integer> row : follow_matrix) {
            // Swap the first two columns for simplicity
            Integer temp = row.get(0);
            row.set(0, row.get(1));
            row.set(1, temp);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(follow_matrix);

        /* Verification */
        assertEquals(follow_out, source_out);
    }

    /**
     * Metamorphic Relation 33: Multiply all values in the matrix by a non-zero scalar (e.g., 2).
     * Since the matrix is binary, all positive scalars will yield the same result as 1, so the
     * output should remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by multiplying all entries by a non-zero scalar */
        int scalar = 2;
        ArrayList<ArrayList<Integer>> scaled_matrix = new ArrayList<>();
        for (ArrayList<Integer> row : matrix) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (Integer cell : row) {
                newRow.add(cell * scalar);
            }
            scaled_matrix.add(newRow);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(scaled_matrix);

        /* Verification */
        assertEquals(follow_out, source_out);
    }

    /**
     * Metamorphic Relation 34: Insert a row full of '0's in the middle of the matrix. This does not
     * contribute to the largest rectangle, so the area should remain unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by inserting a row of zero */
        ArrayList<ArrayList<Integer>> modified_matrix = new ArrayList<>(matrix);
        ArrayList<Integer> zeroRow = new ArrayList<>(Collections.nCopies(matrix.get(0).size(), 0));
        // Insert in the middle for demonstration purposes
        modified_matrix.add(matrix.size() / 2, zeroRow);

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(modified_matrix);

        /* Verification */
        assertEquals(follow_out, source_out);
    }

    /**
     * Metamorphic Relation 35: Cutting a matrix diagonally from the top left corner to the bottom
     * right corner replacing all values below the diagonal with 0 should either maintain or reduce
     * the area of the maximal rectangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by cutting the matrix diagonally */
        ArrayList<ArrayList<Integer>> cut_matrix = new ArrayList<>();
        for (int i = 0; i < matrix.size(); i++) {
            ArrayList<Integer> cut_row = new ArrayList<>(matrix.get(i));
            for (int j = 0; j < cut_row.size(); j++) {
                if (j < i) {
                    cut_row.set(j, 0); // Replace below diagonal with 0
                }
            }
            cut_matrix.add(cut_row);
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(cut_matrix);

        /* Verification */
        assertTrue(follow_out <= source_out);
    }

    /**
     * Metamorphic Relation 36: Adding a mirrored copy of the matrix to its bottom should result in
     * an area output that is at least the same as the original's and potentially larger, depending
     * on the structure of the 1's in the matrix.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by mirroring the matrix at the bottom */
        ArrayList<ArrayList<Integer>> mirrored_matrix = new ArrayList<>(matrix);
        ArrayList<ArrayList<Integer>> reversed_matrix = new ArrayList<>(matrix);
        Collections.reverse(reversed_matrix);
        mirrored_matrix.addAll(reversed_matrix);

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(mirrored_matrix);

        /* Verification */
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 37: Interchange rows and columns (transposition) multiple times should
     * not change the outcome.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Perform multiple transpositions */
        ArrayList<ArrayList<Integer>> transposed_matrix = transposeMatrix(matrix);
        transposed_matrix = transposeMatrix(transposed_matrix); // Transpose the matrix twice

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(transposed_matrix);

        /* Verification */
        assertEquals(follow_out, source_out);
    }

    /**
     * Metamorphic Relation 38: Repeating the matrix along the vertical and horizontal axis (tiling)
     * should result in an area that is proportional to the repetition based on the original
     * matrix's maximal rectangle positioning.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Repeat (tile) the matrix */
        ArrayList<ArrayList<Integer>> tiled_matrix = new ArrayList<>();
        for (int k = 0; k < 2; k++) { // Duplicate the matrix rows
            for (ArrayList<Integer> row : matrix) {
                ArrayList<Integer> new_row = new ArrayList<>();
                for (int l = 0; l < 2; l++) { // Duplicate the matrix columns
                    new_row.addAll(row);
                }
                tiled_matrix.add(new_row);
            }
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(tiled_matrix);

        /* Verification */
        // The maximal area in the tiled version depends on where the repeating pattern
        // falls relative to the maximal rectangle in the source version.
        // Hence, while there's an expected relation, the outcome needs contextual
        // understanding of the source matrix to make precise assertions.

        // For simplicity, let's assert that the follow-up area should not be less than
        // the source area.
        assertTrue(follow_out >= source_out);
    }

    // Helper function for MR 37 - Transpose a matrix
    private static ArrayList<ArrayList<Integer>> transposeMatrix(
            ArrayList<ArrayList<Integer>> matrix) {
        ArrayList<ArrayList<Integer>> transposed_matrix = new ArrayList<>();
        int totalRows = matrix.size();
        int totalCols = matrix.get(0).size();
        for (int col = 0; col < totalCols; col++) {
            ArrayList<Integer> newRow = new ArrayList<>();
            for (int row = 0; row < totalRows; row++) {
                newRow.add(matrix.get(row).get(col));
            }
            transposed_matrix.add(newRow);
        }
        return transposed_matrix;
    }

    /**
     * Metamorphic Relation 39: Reversing the order of elements in each column should not change the
     * output, as the area of the largest rectangle remains the same irrespective of vertical order
     * of elements.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /*
         * Construct follow-up input by reversing the order of elements in each column
         */
        ArrayList<ArrayList<Integer>> columnReversedMatrix = new ArrayList<>(matrix.size());
        for (int i = 0; i < matrix.size(); i++) {
            columnReversedMatrix.add(new ArrayList<>(matrix.get(i).size()));
        }
        for (int col = 0; col < matrix.get(0).size(); col++) {
            for (int row = 0; row < matrix.size(); row++) {
                columnReversedMatrix.get(row).add(matrix.get(matrix.size() - row - 1).get(col));
            }
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(columnReversedMatrix);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 40: In a non-empty matrix, setting a single element from 1 to 0 should
     * either decrease the area of the maximal rectangle or keep the output the same, it should not
     * increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(ArrayList<ArrayList<Integer>> matrix) {
        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Ensure that the matrix has at least one '1' to be set to '0' */
        boolean foundOne = false;
        for (ArrayList<Integer> row : matrix) {
            if (row.contains(1)) {
                foundOne = true;
                break;
            }
        }
        if (!foundOne) {
            return; // Skip the test if the matrix has no '1's
        }

        /* Construct follow-up input by setting a single '1' to '0' */
        ArrayList<ArrayList<Integer>> modified_matrix = new ArrayList<>(matrix);
        outerloop: for (int row = 0; row < modified_matrix.size(); row++) {
            for (int col = 0; col < modified_matrix.get(row).size(); col++) {
                if (modified_matrix.get(row).get(col) == 1) {
                    modified_matrix.get(row).set(col, 0);
                    break outerloop;
                }
            }
        }

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(modified_matrix);

        /* Verification */
        assertTrue(follow_out <= source_out);
    }

    /**
     * Metamorphic Relation 41: Shuffling the elements within one row should not change the output,
     * since the order of '1's within a single row does not affect the area of the largest
     * rectangle.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test41(ArrayList<ArrayList<Integer>> matrix) {
        if (matrix.isEmpty()) {
            return; // Skip the test for an empty matrix
        }

        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by shuffling elements within one row */
        ArrayList<ArrayList<Integer>> shuffle_matrix = new ArrayList<>(matrix);
        Collections.shuffle(shuffle_matrix.get(0)); // Shuffle the elements in the first row

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(shuffle_matrix);

        /* Verification */
        assertEquals(follow_out, source_out);
    }

    /**
     * Metamorphic Relation 42: Switching two elements within the same row should not change the
     * output, as this does not affect the integrity of the histogram each row represents.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test42(ArrayList<ArrayList<Integer>> matrix) {
        if (matrix.isEmpty() || matrix.get(0).size() < 2) {
            return; // Skip the test if the matrix is empty or the row has only one element
        }

        /* Get source output */
        int source_out = MaxRectangle.maximalRectangle(matrix);

        /* Construct follow-up input by switching two elements within the same row */
        ArrayList<ArrayList<Integer>> switched_matrix = new ArrayList<>(matrix);
        // Switch two elements in the first row
        Integer temp = switched_matrix.get(0).get(0);
        switched_matrix.get(0).set(0, switched_matrix.get(0).get(1));
        switched_matrix.get(0).set(1, temp);

        /* Get follow-up output */
        int follow_out = MaxRectangle.maximalRectangle(switched_matrix);

        /* Verification */
        assertEquals(follow_out, source_out);
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
