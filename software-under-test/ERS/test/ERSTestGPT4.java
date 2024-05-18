package test;

import static org.junit.Assume.assumeFalse;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.stream.Stream;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import src.ExpenseReimbursementSystem;

public class ERSTestGPT4 {
    /**
     * Metamorphic Relation 1: Increasing actualmonthlymileage should not decrease
     * the total reimbursement amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input with increased mileage */
        double follow_actualmonthlymileage = actualmonthlymileage + 100;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, follow_actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out <= follow_out);
    }

    /**
     * Metamorphic Relation 2: If airfareamount is increased, the total
     * reimbursement amount for a "seniormanager" should increase by the same
     * amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        if (!stafflevel.equals("seniormanager"))
            return;

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input with increased airfare */
        double increaseAmount = 500.00;
        double follow_airfareamount = airfareamount + increaseAmount;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, follow_airfareamount, otherexpensesamount);

        /* Verification */
        assertEquals(source_out + increaseAmount, follow_out);
    }

    /**
     * Metamorphic Relation 3: Keeping actualmonthlymileage constant, increasing
     * otherexpensesamount by a fixed amount should increase the total reimbursement
     * amount by the same amount if monthlysalesamount exceeds the specific
     * threshold for other expenses reimbursement.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        // Assumed specific threshold is known
        final double otherExpensesThreshold = 20000.00;
        if (monthlysalesamount <= otherExpensesThreshold) {
            return;
        }

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input with increased other expenses */
        double increaseAmount = 300.00;
        double follow_otherexpensesamount = otherexpensesamount + increaseAmount;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, follow_otherexpensesamount);

        /* Verification */
        assertEquals(source_out + increaseAmount, follow_out);
    }

    /**
     * Metamorphic Relation 4: Doubling the airfareamount for managers or
     * supervisors with monthly sales at or above the threshold should double the
     * airfare reimbursement part of the total reimbursement calculation. (Assuming
     * threshold for managers/supervisors is known).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        // Assumed airfare threshold is known
        final double airfareThreshold = 15000.00;
        if (!stafflevel.equals("manager") && !stafflevel.equals("supervisor")
                || monthlysalesamount < airfareThreshold) {
            return;
        }

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Double the airfare amount */
        double follow_airfareamount = 2 * airfareamount;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, follow_airfareamount, otherexpensesamount);

        /*
         * Assuming airfare is the only reimbursement affected by this change (isolate
         * airfare reimbursement calculation)
         */
        assertEquals(source_out * 2, follow_out, 0.01); // Allow for floating point inaccuracies
    }

    /**
     * Metamorphic Relation 5: The total reimbursement amount should be invariant to
     * permutations of otherexpensesamount and airfareamount if monthlysalesamount
     * exceeds the specific threshold for both and stafflevel is "seniormanager".
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        if (!stafflevel.equals("seniormanager")) {
            return;
        }

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Swap airfareamount and otherexpensesamount */
        double temp = airfareamount;
        airfareamount = otherexpensesamount;
        otherexpensesamount = temp;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 6: For any stafflevel, reducing actualmonthlymileage to
     * zero should not increase the total reimbursement amount due to the adjustment
     * to the allowable mileage.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {

        if (actualmonthlymileage == 0) {
            return;
        }

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Set actualmonthlymileage to zero */
        double follow_actualmonthlymileage = 0;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, follow_actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out >= follow_out);
    }

    /**
     * Metamorphic Relation 7: Increasing monthlysalesamount to meet or exceed the
     * airfare reimbursement threshold for managers and supervisors, who initially
     * did not meet the threshold, should result in an increase in the total
     * reimbursement amount that is at least equal to the airfare amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        // Assumed airfare threshold is known
        final double airfareThreshold = 15000.00;
        if (!stafflevel.equals("manager") && !stafflevel.equals("supervisor")
                || monthlysalesamount >= airfareThreshold) {
            return;
        }

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Increase monthlysalesamount to exceed the threshold */
        double follow_monthlysalesamount = airfareThreshold + 1.00; // Just over the threshold

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                follow_monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(follow_out >= source_out + airfareamount);
    }

    /**
     * Metamorphic Relation 8: If the actualmonthlymileage is decreased but still
     * above the allowable mileage for a given staff level, and other inputs remain
     * constant, the total reimbursement amount should decrease proportionally to
     * the reduction in actualmonthlymileage.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        // Assumed allowable mileage per stafflevel is known
        double allowableMileage = staffAllowableMileage(stafflevel); // placeholder method to obtain allowable mileage
        if (actualmonthlymileage <= allowableMileage) {
            return;
        }

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Decrease actualmonthlymileage between allowableMileage and current mileage */
        double follow_actualmonthlymileage = allowableMileage + (actualmonthlymileage - allowableMileage) / 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, follow_actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(follow_out < source_out);
    }

    /**
     * Metamorphic Relation 9: The same reimbursement amount should be calculated if
     * stafflevel, actualmonthlymileage, monthlysalesamount, and sum of
     * airfareamount plus otherexpensesamount are kept the same, regardless of how
     * airfareamount and otherexpensesamount are distributed.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        double totalExpenses = airfareamount + otherexpensesamount;

        /*
         * Arbitrarily redistribute airfare and other expenses while keeping the total
         * same
         */
        double follow_airfareamount = totalExpenses / 3;
        double follow_otherexpensesamount = totalExpenses - follow_airfareamount;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, follow_airfareamount, follow_otherexpensesamount);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    // Placeholder method to determine allowable mileage based on stafflevel
    private double staffAllowableMileage(String stafflevel) { // Fixed
        switch (stafflevel) {
            case "seniormanager":
                return 4000.00;
            case "manager":
                return 3000.00;
            case "supervisor":
                return 0.00;
            default:
                return 0.00;
        }
    }

    /**
     * Metamorphic Relation 10: If actualmonthlymileage is always less than
     * allowable mileage, then any constant increase in the actualmonthlymileage
     * should not change the total reimbursement amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        double allowableMileage = staffAllowableMileage(stafflevel);
        if (actualmonthlymileage >= allowableMileage) {
            return;
        }

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Increase actualmonthlymileage but keep it below allowable mileage */
        double follow_actualmonthlymileage = actualmonthlymileage
                + Math.min(10, allowableMileage - actualmonthlymileage - 1);

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, follow_actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 11: Switching from a stafflevel with a lower allowable
     * mileage to one with a higher allowable mileage, when actualmonthlymileage is
     * between the two allowable mileages, should not increase total reimbursement
     * amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {

        /*
         * Check that stafflevel is not seniormanager, as it presumably has the highest
         * allowable mileage.
         */
        if (stafflevel.equals("seniormanager")) {
            return;
        }

        double supervisorAllowableMileage = staffAllowableMileage("supervisor");
        double managerAllowableMileage = staffAllowableMileage("manager");

        /*
         * Ensure that the actual mileage is above the supervisor mileage, but below or
         * equal to manager mileage if applicable.
         */
        if (stafflevel.equals("supervisor") || actualmonthlymileage <= supervisorAllowableMileage
                || (stafflevel.equals("manager") && actualmonthlymileage > managerAllowableMileage)) {
            return;
        }

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Upgrade staff level */
        String follow_stafflevel = stafflevel.equals("supervisor") ? "manager" : "seniormanager";

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(follow_stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(follow_out <= source_out);
    }

    /**
     * Metamorphic Relation 12: Given any permissible increase in both
     * monthlysalesamount and airfareamount for a manager or supervisor, where the
     * monthlysalesamount initially did not meet the airfare reimbursement
     * threshold, the follow-up output should not be lower than the source output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) { // Fixed
        final double airfareThreshold = 15000.00; // Assumed threshold for airfare reimbursement
        assumeFalse("seniormanager".equals(stafflevel) || monthlysalesamount >= airfareThreshold);

        double source_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // Increase the monthly sales amount to cross the threshold and airfare amount
        // by any positive number
        double follow_monthlysalesamount = airfareThreshold + 1000.00;
        double follow_airfareamount = airfareamount + 500.00;

        double follow_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, follow_monthlysalesamount, follow_airfareamount, otherexpensesamount);

        // Verify the follow-up output is not less than the source output
        assertTrue(follow_out >= source_out);
    }

    /**
     * Metamorphic Relation 13: Increasing otherexpensesamount while decreasing
     * airfareamount by the same amount, where the monthlysalesamount exceeds the
     * specific threshold for both expenses, should not change the total
     * reimbursement amount for any staff level.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        final double expensesThreshold = 10000.00; // Assumed threshold for other expenses reimbursement
        if (monthlysalesamount < expensesThreshold) {
            return;
        }

        double source_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        double deltaAmount = 100.00; // The amount by which the airfare is decreased and other expenses are increased

        double follow_airfareamount = airfareamount - deltaAmount;
        double follow_otherexpensesamount = otherexpensesamount + deltaAmount;

        double follow_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, follow_airfareamount, follow_otherexpensesamount);

        // Verify the follow-up output is the same as the source output
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 14: For a constant total expense amount, the
     * distribution of that total between
     * airfareamount and otherexpensesamount should not affect the reimbursement
     * amount if monthlysalesamount
     * does not meet the threshold for reimbursement.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        final double salesThreshold = 15000.00; // Assumed threshold for airfare and other expenses reimbursement
        if (monthlysalesamount >= salesThreshold) {
            return; // This test case only applies if the threshold is not met
        }

        double totalExpenses = airfareamount + otherexpensesamount;

        double source_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // Split the total expenses in a different way
        double follow_airfareamount = totalExpenses * 0.25;
        double follow_otherexpensesamount = totalExpenses - follow_airfareamount;

        double follow_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, follow_airfareamount, follow_otherexpensesamount);

        // Verify that the output should not change despite redistributing expenses
        // under the threshold
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 15: The total reimbursement amount should remain
     * constant when the sum of
     * actualmonthlymileage, monthlysalesamount, airfareamount, and
     * otherexpensesamount remain the same
     * but their individual values change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        double initial_sum = actualmonthlymileage + monthlysalesamount + airfareamount + otherexpensesamount;

        double source_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        double delta = 100.0; // Amount to shift between the components

        // Adjust the values while keeping the sum constant
        double follow_actualmonthlymileage = actualmonthlymileage + delta;
        double follow_monthlysalesamount = monthlysalesamount - delta;
        double follow_airfareamount = airfareamount + delta;
        double follow_otherexpensesamount = otherexpensesamount - delta;

        double follow_sum = follow_actualmonthlymileage + follow_monthlysalesamount + follow_airfareamount
                + follow_otherexpensesamount;

        // If the initial and follow-up sums do not match, skip this test
        if (initial_sum != follow_sum) {
            return;
        }

        double follow_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                stafflevel, follow_actualmonthlymileage, follow_monthlysalesamount, follow_airfareamount,
                follow_otherexpensesamount);

        // The total reimbursement should remain constant as the overall sum did not
        // change
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 16: Distributing the airfareamount in parts over
     * multiple calls while keeping other parameters same should result in the same
     * total reimbursement amount for a "seniormanager", since they get full airfare
     * reimbursement regardless of the sales amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        if (!"seniormanager".equals(stafflevel)) {
            return; // This test applies only to senior managers
        }

        double source_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // Make multiple calls with partial airfare amounts that sum to the original
        // airfare amount
        double halfAirfare = airfareamount / 2;
        double first_half_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, halfAirfare, otherexpensesamount);
        double second_half_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, halfAirfare, otherexpensesamount);

        // The total reimbursement from both calls should add up to the original
        // reimbursement
        assertEquals(source_out, first_half_out + second_half_out - otherexpensesamount);
    }

    /**
     * Metamorphic Relation 17: Doubling all financial input parameters
     * (actualmonthlymileage, monthlysalesamount, airfareamount, and
     * otherexpensesamount) should not double the total reimbursement amount due to
     * the fixed limits on reimbursement rates and cap on mileage.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        double source_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // Doubles the financial input parameters
        double double_actualmonthlymileage = 2 * actualmonthlymileage;
        double double_monthlysalesamount = 2 * monthlysalesamount;
        double double_airfareamount = 2 * airfareamount;
        double double_otherexpensesamount = 2 * otherexpensesamount;

        double double_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                stafflevel, double_actualmonthlymileage, double_monthlysalesamount, double_airfareamount,
                double_otherexpensesamount);

        // Due to the fixed allowances and thresholds, the reimbursement should not
        // double
        assertTrue(double_out < 2 * source_out);
    }

    /**
     * Metamorphic Relation 18: Increments in monthlysalesamount that do not cross
     * any reimbursement thresholds should not affect the total reimbursement
     * amount. (Assuming that there are set thresholds for monthlysalesamount
     * regarding reimbursements.)
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        double source_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // Increment sales amount without crossing any thresholds
        double increment = 100.00; // Assuming this increment doesn’t cross any threshold
        double incremented_sales = monthlysalesamount + increment;

        double incremented_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, incremented_sales, airfareamount, otherexpensesamount);

        // Verify the reimbursement amount does not change with this increment in sales
        assertEquals(source_out, incremented_out);
    }

    /**
     * Metamorphic Relation 19: Assuming there exists a cost per kilometer that does
     * not vary by staff level, if allowableMileage is subtracted from the
     * actualmonthlymileage for two different staff levels with the same cost per
     * kilometer, the differences in reimbursement amounts should be proportional to
     * the differences in mileage overages.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) { // Fixed
        if (actualmonthlymileage <= staffAllowableMileage(stafflevel)) {
            return; // No overage, so skip this test case
        }

        double source_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        String otherStaffLevel = "seniormanager".equals(stafflevel) ? "manager" : "seniormanager";
        double allowableMileageDiff = staffAllowableMileage(otherStaffLevel) - staffAllowableMileage(stafflevel);
        double modified_actualmonthlymileage = actualmonthlymileage + allowableMileageDiff;

        double modified_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                otherStaffLevel, modified_actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // The difference in reimbursement between the original and modified case should
        // be proportional to the mileage overage difference
        double diff_in_reimbursement = modified_out - source_out;
        double expected_difference = costPerKilometer(otherStaffLevel) * allowableMileageDiff; // costPerKilometer is a
                                                                                               // placeholder
        // method to get cost per kilometer
        assertEquals(expected_difference, diff_in_reimbursement, 0.01); // Allow for some floating point rounding errors
    }

    // Placeholder method to get cost per kilometer. Must be defined according to
    // actual values used by the software
    private double costPerKilometer(String stafflevel) {
        switch (stafflevel) {
            case "seniormanager":
                return 5.00;
            case "manager":
                return 8.00;
            case "supervisor":
                return 0.00;
            default:
                return 0.00;
        }
    }

    /**
     * Metamorphic Relation 20: For any staff level with a sales amount below the
     * threshold,
     * increasing the sales amount to meet the threshold should result in an
     * increased reimbursement
     * that includes the airfareamount and otherexpensesamount, assuming they were
     * not included initially.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        // Placeholder thresholds
        final double airfareSalesThreshold = 25000.00;
        final double otherExpensesSalesThreshold = 20000.00;

        if (stafflevel.equals("seniormanager") || monthlysalesamount >= airfareSalesThreshold) {
            return; // This test is not applicable for senior managers or sales above threshold
        }

        double source_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // Increase sales to meet the threshold
        double adjusted_salesamount = Math.max(airfareSalesThreshold, otherExpensesSalesThreshold);

        double adjusted_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, adjusted_salesamount, airfareamount, otherexpensesamount);

        // Verify that reimbursement amount increases at least by the airfare and other
        // expenses amount
        double minimumIncrease = airfareamount + otherexpensesamount;
        assertTrue(adjusted_out >= source_out + minimumIncrease);
    }

    /**
     * Metamorphic Relation 21: If the mileage overuse fee is calculated correctly,
     * halving the costPerKilometer while doubling the actualmonthlymileage should
     * result in the same total reimbursement amount if the actual monthly mileage
     * is above the allowable limit.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        /*
         * double allowableMileage = staffAllowableMileage(stafflevel);
         * if (actualmonthlymileage <= allowableMileage) {
         * return; // Skip test if below or at allowable mileage
         * }
         * 
         * ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
         * 
         * // Original cost
         * double source_out = ERS.calculateReimbursementAmount(
         * stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount,
         * otherexpensesamount);
         * 
         * // Adjust mileage and cost per kilometer
         * double adjustedMileage = actualmonthlymileage * 2;
         * double adjustedCostPerKilometer = costPerKilometer() / 2;
         * 
         * // Function to calculate reimbursement with adjusted cost per kilometer: this
         * is
         * // a placeholder and would require an additional interface to the
         * // ExpenseReimbursementSystem allowing for such adjustments
         * double adjusted_out =
         * ERS.calculateReimbursementAmountWithAdjustedCostPerKilometer(
         * stafflevel, adjustedMileage, monthlysalesamount, airfareamount,
         * otherexpensesamount,
         * adjustedCostPerKilometer);
         * 
         * // Verify that the adjustment does not change reimbursement
         * assertEquals(source_out, adjusted_out);
         */
    }

    /**
     * Metamorphic Relation 22: Swapping the actualmonthlymileage and
     * monthlysalesamount should not affect the total reimbursement amount, provided
     * that both are below their respective thresholds and actualmonthlymileage is
     * within the allowable mileage limit.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) { // Fixed
        // Placeholder thresholds
        final double mileageThreshold = staffAllowableMileage(stafflevel);
        final double salesThreshold = 10000.00; // Assumed sales threshold for demonstration

        assumeFalse(actualmonthlymileage > mileageThreshold || monthlysalesamount > salesThreshold);

        double source_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // Swap the mileage and sales amount
        // Not a realistic use case; serves as a hypothetical transformation
        double swapped_out = new ExpenseReimbursementSystem().calculateReimbursementAmount(
                stafflevel, monthlysalesamount, actualmonthlymileage, airfareamount, otherexpensesamount);

        assertEquals(source_out, swapped_out);
    }

    /**
     * Metamorphic Relation 23: For a fixed total expense (airfareamount +
     * otherexpensesamount), increasing airfareamount while decreasing
     * otherexpensesamount by the same amount should not change the total
     * reimbursement amount for a "seniormanager" as they have full reimbursement
     * for both expenses.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        if (!"seniormanager".equals(stafflevel)) {
            return; // This relation is specific to senior managers
        }
        double totalExpenses = airfareamount + otherexpensesamount;

        // Calculating the original reimbursement
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // Increasing airfare and decreasing other expenses
        double delta = 500; // Assumed change
        double adjustedAirfareAmount = airfareamount + delta;
        double adjustedOtherExpensesAmount = otherexpensesamount - delta;

        // The total expenses should remain constant
        assertTrue(adjustedAirfareAmount + adjustedOtherExpensesAmount == totalExpenses);

        double adjusted_out = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, adjustedAirfareAmount,
                adjustedOtherExpensesAmount);

        // Verifying the adjusted reimbursement amount is equal to the original
        // reimbursement amount
        assertEquals(source_out, adjusted_out);
    }

    /**
     * Metamorphic Relation 24: If all inputs except stafflevel are held constant,
     * changing the stafflevel from a lower rank to a higher rank should not
     * decrease the total reimbursement amount given the general business practice
     * that higher ranks have equal or greater benefits.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        if ("seniormanager".equals(stafflevel)) {
            return; // Highest staff level, cannot be promoted further
        }

        // Calculating the original reimbursement
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        String promotedStaffLevel = promoteStaffLevel(stafflevel);

        // Calculating the reimbursement amount for the promoted staff level
        double adjusted_out = ERS.calculateReimbursementAmount(
                promotedStaffLevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // Verify that the promoted staff level does not receive less reimbursement than
        // the original
        assertTrue(adjusted_out >= source_out);
    }

    /**
     * Metamorphic Relation 25: Setting actualmonthlymileage to a negative value
     * (which should be invalid) would ideally not change the outcome assuming the
     * business logic resets any negative mileage to zero, as indicated by the
     * intent of accounting for mileage at a minimum as the allowable mileage.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        if (actualmonthlymileage < 0) {
            return; // Skip test if already negative, this relation introduces a negative value
        }

        // Calculating the original reimbursement
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(
                stafflevel, Math.max(actualmonthlymileage, 0), monthlysalesamount, airfareamount, otherexpensesamount);

        double negativeMileage = -50; // Any arbitrary negative value

        // Calculating the reimbursement amount with negative mileage
        double adjusted_out = ERS.calculateReimbursementAmount(
                stafflevel, negativeMileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // Verify that the reimbursement amount is the same assuming negative mileage is
        // effectively zero
        assertEquals(source_out, adjusted_out);
    }

    // Helper method to promote a staff level (assuming a fixed order of levels)
    private String promoteStaffLevel(String stafflevel) {
        switch (stafflevel) {
            case "supervisor":
                return "manager";
            case "manager":
                return "seniormanager";
            default:
                return stafflevel; // No promotion possible
        }
    }

    /**
     * Metamorphic Relation 26: When a staff member's actualmonthlymileage is at the
     * allowable mileage threshold, increasing the actualmonthlymileage should
     * result in an increase in the total reimbursement amount according to the cost
     * per kilometer (assuming no changes in other parameters).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) { // Fixed
        double allowableMileage = staffAllowableMileage(stafflevel);
        actualmonthlymileage = allowableMileage;

        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        double additionalMileage = 100; // fixed increase
        double follow_actualmonthlymileage = actualmonthlymileage + additionalMileage;

        double follow_out = ERS.calculateReimbursementAmount(
                stafflevel, follow_actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // Verify that the reimbursement increases proportionally to the mileage
        // increase
        double expected_increase = additionalMileage * costPerKilometer(stafflevel);
        assertEquals(source_out + expected_increase, follow_out, 0.01); // Consider some precision tolerance
    }

    /**
     * Metamorphic Relation 27: Decreasing monthlysalesamount should never increase
     * the airfare reimbursement for "manager" and "supervisor" stafflevels assuming
     * the reduced amount falls below the airfare threshold.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) { // Fixed
        final double airfareThreshold = 15000.00; // Assumed threshold for airfare reimbursement
        assumeFalse(monthlysalesamount <= airfareThreshold || "seniormanager".equals(stafflevel));

        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        double reducedSales = monthlysalesamount - 1000; // Decrease monthly sales to fall below the threshold

        double follow_out = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, reducedSales, airfareamount, otherexpensesamount);

        // Verify that reducing the sales below the threshold does not increase the
        // reimbursement amount
        assertTrue(follow_out <= source_out);
    }

    /**
     * Metamorphic Relation 28: For a non-senior manager whose monthly sales are
     * below the airfare reimbursement threshold, keeping all other parameters
     * constant, their total reimbursement amount should be less than or equal to
     * that of a senior manager when airfare is added to the total.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) { // Fixed
        final double airfareThreshold = 15000.00; // Assumed threshold for airfare reimbursement
        assumeFalse("seniormanager".equals(stafflevel) || monthlysalesamount >= airfareThreshold);

        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double nonSeniorManager_out = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        double seniorManager_out = ERS.calculateReimbursementAmount(
                "seniormanager", actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // Validate that a senior manager's reimbursement, which includes airfare, is
        // not less than another staff level's reimbursement
        assertTrue(seniorManager_out >= nonSeniorManager_out);
    }

    /**
     * Metamorphic Relation 29: If an employee's total reimbursement is not affected
     * by airfare (due to not meeting the sales threshold), then varying the
     * airfareamount while keeping other parameters constant should not change the
     * total reimbursement amount for both manager and supervisor levels.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) { // Fixed
        final double airfareSalesThreshold = 15000.00; // Assumed threshold for airfare reimbursement
        assumeFalse(!stafflevel.equals("manager") && !stafflevel.equals("supervisor"));
        assumeFalse(monthlysalesamount >= airfareSalesThreshold);

        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double original_reimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        double varied_airfareamount = airfareamount + 1000.00; // Arbitrary increase in airfare amount

        double varied_reimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, varied_airfareamount, otherexpensesamount);

        // The total reimbursement should remain unchanged since airfare should not be
        // considered.
        assertEquals(original_reimbursement, varied_reimbursement);
    }

    /**
     * Metamorphic Relation 30: If actual monthly mileage equals zero, which is
     * below the allowable mileage, increasing other input parameters
     * (monthlysalesamount, airfareamount, or otherexpensesamount) by any positive
     * amount should not decrease the total reimbursement amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) { // Fixed
        actualmonthlymileage = 0;

        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double original_reimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // Increment each other input parameter by an arbitrary positive amount
        double increment = 1000.00; // Could be anything positive
        double new_sales = monthlysalesamount + increment;
        double new_airfare = airfareamount + increment;
        double new_other_expenses = otherexpensesamount + increment;

        double new_reimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, new_sales, new_airfare, new_other_expenses);

        // Verify that increasing sales, airfare, or other expenses does not decrease
        // total reimbursement
        assertTrue(new_reimbursement >= original_reimbursement);
    }

    /**
     * Metamorphic Relation 31: For any staff level, increasing monthly sales
     * without passing the threshold should not affect the eligibility for airfare
     * and other expenses reimbursement. Therefore, the relative difference in the
     * total reimbursement amount should only be due to overuse of the car if
     * applicable.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) { // Fixed
        final double airfareSalesThreshold = 15000.00; // Assumed threshold for airfare reimbursement
        final double otherExpensesThreshold = 20000.00; // Assumed threshold for other expenses reimbursement

        // Ensuring we are below both thresholds
        assumeFalse(monthlysalesamount >= airfareSalesThreshold || monthlysalesamount >= otherExpensesThreshold);

        double smallerIncrement = 500.00; // Increment smaller than what would cross the threshold
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();

        // Original reimbursement
        double original_reimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // Increment sales without crossing the thresholds
        double new_sales = monthlysalesamount + smallerIncrement;

        // Assuming overuse fee calculation is desired for this test case. If not,
        // adjust mileage accordingly.
        double new_reimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, new_sales, airfareamount, otherexpensesamount);

        // Assuming cost per kilometer is constant and the mileage does not change. The
        // difference in reimbursement
        // should be zero since the increment does not cross reimbursement eligibility
        // thresholds.
        assertEquals(original_reimbursement, new_reimbursement);
    }

    /**
     * Metamorphic Relation 32: If actualmonthlymileage is increased such that it
     * remains less than allowable mileage, then the total reimbursement amount
     * should remain unchanged given the mileage is adjusted to allowable mileage.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) { // Fixed
        double allowableMileage = staffAllowableMileage(stafflevel);
        actualmonthlymileage = allowableMileage - 1; // Ensure mileage is below allowable

        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double original_reimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // Increase the mileage, ensuring it's still below the allowable mileage
        double increased_mileage = actualmonthlymileage + (allowableMileage - actualmonthlymileage) / 2;

        double updated_reimbursement = ERS.calculateReimbursementAmount(
                stafflevel, increased_mileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // The total reimbursement amount should remain unchanged since mileage was
        // below allowable
        assertEquals(original_reimbursement, updated_reimbursement);
    }

    /**
     * Metamorphic Relation 33: For a "seniormanager", a reduction in
     * monthlysalesamount should not affect the total reimbursement amount as they
     * are eligible for full reimbursement regardless of sales.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) { // Fixed
        assumeFalse(!"seniormanager".equals(stafflevel));

        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double original_reimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        double reduced_sales = monthlysalesamount - 1000.00; // Reduction in sales amount

        double updated_reimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, reduced_sales, airfareamount, otherexpensesamount);

        // Reimbursement for senior managers should not be affected by reduced sales
        assertEquals(original_reimbursement, updated_reimbursement);
    }

    /**
     * Metamorphic Relation 34: Adding a constant amount to actualmonthlymileage,
     * monthlysalesamount, airfareamount, and otherexpensesamount separately should
     * have no negative impact on the total reimbursement amount, because an
     * increase in actual expenses or sales should generally lead to the same or
     * increased reimbursement.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {

        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double original_reimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        double increment = 500.00; // Arbitrary positive increment

        double mileage_reimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage + increment, monthlysalesamount, airfareamount, otherexpensesamount);
        double sales_reimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount + increment, airfareamount, otherexpensesamount);
        double airfare_reimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount + increment, otherexpensesamount);
        double otherexpenses_reimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount + increment);

        // Verify that the separate increments do not reduce the total reimbursement
        assertTrue(mileage_reimbursement >= original_reimbursement);
        assertTrue(sales_reimbursement >= original_reimbursement);
        assertTrue(airfare_reimbursement >= original_reimbursement);
        assertTrue(otherexpenses_reimbursement >= original_reimbursement);
    }

    /**
     * Metamorphic Relation 35: For any staff level, if the actual monthly mileage
     * remains constant and the monthly sales amount incrementally increases without
     * exceeding the other expenses threshold, the total reimbursement amount should
     * either stay the same or increase, but not decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) { // Fixed
        final double otherExpensesThreshold = 30000.00; // Assumed threshold for other expenses reimbursement
        assumeFalse(monthlysalesamount >= otherExpensesThreshold);

        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double originalReimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        double increasedSalesAmount = monthlysalesamount + 1000.00; // Incremental sales increase
        if (increasedSalesAmount > otherExpensesThreshold) {
            increasedSalesAmount = otherExpensesThreshold - 1.00; // Ensure we stay below the threshold
        }

        double updatedReimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, increasedSalesAmount, airfareamount, otherexpensesamount);

        // Verify that incrementally increasing sales, while below thresholds, does not
        // decrease reimbursement
        assertTrue(updatedReimbursement >= originalReimbursement);
    }

    /**
     * Metamorphic Relation 36: Reducing the otherexpensesamount to zero should not
     * increase the total reimbursement amount, assuming all other inputs remain
     * constant and the monthly sales amount is below the threshold for other
     * expenses reimbursement eligibility.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) { // Fixed
        final double otherExpensesThreshold = 30000.00; // Assumed threshold for other expenses reimbursement
        assumeFalse(monthlysalesamount >= otherExpensesThreshold);

        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double originalReimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        double zeroOtherExpensesAmount = 0.00;

        double updatedReimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, zeroOtherExpensesAmount);

        // Reducing other expenses to zero should not increase total reimbursement
        assertTrue(updatedReimbursement <= originalReimbursement);
    }

    /**
     * Metamorphic Relation 37: If the actualmonthlymileage is doubled for all staff
     * levels and the value exceeds the allowable mileage, the total reimbursement
     * for overuse of the car should double, assuming all other inputs remain
     * constant and the cost per kilometer is fixed.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) { // Fixed
        double allowableMileage = staffAllowableMileage(stafflevel);
        assumeFalse(actualmonthlymileage <= allowableMileage);

        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double originalReimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        double doubleMileage = actualmonthlymileage * 2;

        double updatedReimbursement = ERS.calculateReimbursementAmount(
                stafflevel, doubleMileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // Assuming that the cost per kilometer is the same for the overuse fee
        // calculation,
        // doubling the actual mileage should result in doubling the fee for overuse of
        // the car.
        double expectedIncreasedReimbursement = originalReimbursement +
                (doubleMileage - allowableMileage) * costPerKilometer(stafflevel);
        assertEquals(expectedIncreasedReimbursement, updatedReimbursement, 0.01); // Allowing for some floating-point
                                                                                  // imprecision
    }

    /**
     * Metamorphic Relation 38: For a "supervisor" transitioning to "manager" with
     * an increase in monthlysalesamount, while not exceeding the airfare threshold,
     * the total reimbursement amount should not decrease given managers have equal
     * or more privileges compared to supervisors.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) { // Fixed
        final double airfareThreshold = 20000.00; // Assumed threshold for airfare reimbursement
        stafflevel = "supervisor"; // Starting as a supervisor
        monthlysalesamount = airfareThreshold - 1000.00; // Below the threshold

        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double supervisorReimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // Introducing change: Supervisor becomes Manager and slightly increases sales
        double increasedSalesAmount = monthlysalesamount + 1000.00; // Incremental increase below threshold
        double managerReimbursement = ERS.calculateReimbursementAmount(
                "manager", actualmonthlymileage, increasedSalesAmount, airfareamount, otherexpensesamount);

        // Verify manager reimbursement is not less, given the promotion and increased
        // sales amount
        assertTrue(managerReimbursement >= supervisorReimbursement);
    }

    /**
     * Metamorphic Relation 39: If monthlysalesamount and airfareamount are swapped
     * (while the sales amount is less than the threshold), then the total
     * reimbursement amount should not change for a "seniormanager" who gets full
     * airfare reimbursement regardless of sales amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) { // Fixed
        final double airfareThreshold = 20000.00; // Assumed threshold for airfare reimbursement
        stafflevel = "seniormanager"; // Fixed to senior manager for this test
        monthlysalesamount = airfareThreshold - 1000.00; // Below the threshold

        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double originalReimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // Swapping sales and airfare amounts
        double swappedReimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, airfareamount, monthlysalesamount, otherexpensesamount);

        // Verify that for a "seniormanager" the total reimbursement remains the same
        // despite the swap
        assertEquals(originalReimbursement, swappedReimbursement);
    }

    /**
     * Metamorphic Relation 40: A modification in stafflevel from "seniormanager" to
     * "manager" or "supervisor" without changing other parameters should not result
     * in an increased total reimbursement amount since "seniormanager" is presumed
     * to have the highest reimbursement entitlements.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) { // Fixed
        stafflevel = "seniormanager"; // Fixed to senior manager for this test

        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double seniorManagerReimbursement = ERS.calculateReimbursementAmount(
                stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        // Different promotions (downgrades) to simulate
        String[] newStaffLevels = { "manager", "supervisor" };

        for (String newStaffLevel : newStaffLevels) {
            double newReimbursement = ERS.calculateReimbursementAmount(
                    newStaffLevel, actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

            // Confirm reimbursement did not increase after the downgrade
            assertTrue(newReimbursement <= seniorManagerReimbursement);
        }
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
