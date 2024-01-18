package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.IOException;
import java.util.stream.Stream;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import src.ExpenseReimbursementSystem;

public class ERSTestGPT3D5 {
    /**
     * Metamorphic Relation 1: If stafflevel is changed, the total reimbursement
     * amount should not decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        String follow_stafflevel = "manager";

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(follow_stafflevel,
                actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out <= follow_out);
    }

    /**
     * Metamorphic Relation 2: If monthlysalesamount is increased, the total
     * reimbursement amount should not decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double follow_monthlysalesamount = monthlysalesamount * 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                follow_monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out <= follow_out);
    }

    /**
     * Metamorphic Relation 3: If actualmonthlymileage is increased, the total
     * reimbursement amount should not decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double follow_actualmonthlymileage = actualmonthlymileage * 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, follow_actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out <= follow_out);
    }

    /**
     * Metamorphic Relation 4: If airfareamount is increased, the total
     * reimbursement amount should not decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double follow_airfareamount = airfareamount * 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, follow_airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out <= follow_out);
    }

    /**
     * Metamorphic Relation 5: If otherexpensesamount is increased, the total
     * reimbursement amount should not decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double follow_otherexpensesamount = otherexpensesamount * 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, follow_otherexpensesamount);

        /* Verification */
        assertTrue(source_out <= follow_out);
    }

    /**
     * Metamorphic Relation 6: If the staff level is changed, the total
     * reimbursement amount should not decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        String follow_stafflevel = "supervisor";

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(follow_stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out <= follow_out);
    }

    /**
     * Metamorphic Relation 7: If the actual monthly mileage exceeds the allowable
     * mileage, the total reimbursement amount should not decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double follow_actualmonthlymileage = 5000; // Assuming allowable mileage is 4000

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, follow_actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out <= follow_out);
    }

    /**
     * Metamorphic Relation 8: If the monthly sales amount is less than 100000, the
     * total reimbursement amount should not exceed the total amount of all
     * expenses.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out <= airfareamount + otherexpensesamount);
    }

    /**
     * Metamorphic Relation 9: If the staff level is invalid, the program should
     * throw an exception.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        /* Get source output */
        boolean exceptionThrown = false;
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        try {
            double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                    monthlysalesamount, airfareamount, otherexpensesamount);
        } catch (Exception e) {
            exceptionThrown = true;
        }

        /* Verification */
        assertTrue(exceptionThrown);
    }

    /**
     * Metamorphic Relation 10: If the cost per kilometer is increased, the total
     * reimbursement amount should decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double follow_costPerKilometer = 10; // Assuming cost per kilometer is 5

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out >= follow_out);
    }

    /**
     * Metamorphic Relation 11: If the airfare reimbursement is set to 0, the total
     * reimbursement amount should decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double follow_airfare = 0;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, follow_airfare, otherexpensesamount);

        /* Verification */
        assertTrue(source_out >= follow_out);
    }

    /**
     * Metamorphic Relation 12: If the cost per kilometer is decreased, the total
     * reimbursement amount should increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double follow_costPerKilometer = 2; // Assuming cost per kilometer is 5

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out <= follow_out);
    }

    /**
     * Metamorphic Relation 13: If the allowable mileage is increased, the total
     * reimbursement amount should decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double follow_allowableMileage = 5000; // Assuming allowableMileage is 4000

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out >= follow_out);
    }

    /**
     * Metamorphic Relation 14: If the monthlysalesamount is equal to 80000, and the
     * staff level is "supervisor", then the airfare reimbursement should be equal
     * to the airfare amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        if (!stafflevel.equals("supervisor") || monthlysalesamount != 80000) {
            return;
        }
        /* Get actual airfare reimbursement */
        double airfareReimbursement = Math.min(airfareamount,
                calculateStandardAirfareReimbursement(monthlysalesamount));

        /* Verification */
        assertEquals(airfareReimbursement, airfareamount);
    }

    private double calculateStandardAirfareReimbursement(double monthlysalesamount) {
        if (monthlysalesamount >= 80000) {
            return Double.POSITIVE_INFINITY; // supervisor can take any amount of airfare
        } else {
            return 0;
        }
    }

    /**
     * Metamorphic Relation 15: If the staff level is invalid, the program should
     * throw an exception.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        boolean validStaffLevel = stafflevel.equals("seniormanager") || stafflevel.equals("manager")
                || stafflevel.equals("supervisor");
        if (validStaffLevel) {
            return;
        }

        /* Verification */
        assertThrows(Exception.class, () -> {
            ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
            ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage, monthlysalesamount, airfareamount,
                    otherexpensesamount);
        });
    }

    /**
     * Metamorphic Relation 16: If the monthly sales amount is between 50000 and
     * 80000 and the staff level is "manager", the airfare reimbursement should be
     * equal to the airfare amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        if (!stafflevel.equals("manager") || (monthlysalesamount <= 50000 || monthlysalesamount >= 80000)) {
            return;
        }
        /* Get actual airfare reimbursement */
        double airfareReimbursement = Math.min(airfareamount,
                calculateStandardAirfareReimbursement(monthlysalesamount));

        /* Verification */
        assertEquals(airfareReimbursement, airfareamount);
    }

    /**
     * Metamorphic Relation 17: If the monthly sales amount is less than 50000 and
     * the staff level is "manager", the airfare reimbursement should be equal to 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        if (!stafflevel.equals("manager") || monthlysalesamount >= 50000) {
            return;
        }
        /* Get actual airfare reimbursement */
        double airfareReimbursement = Math.min(airfareamount,
                calculateStandardAirfareReimbursement(monthlysalesamount));

        /* Verification */
        assertEquals(airfareReimbursement, 0);
    }

    /**
     * Metamorphic Relation 18: If the annual sales amount for a staff member is
     * doubled, the total reimbursement amount should increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double follow_monthlysalesamount = monthlysalesamount * 12; // Assume annual sales amount

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                follow_monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out <= follow_out);
    }

    /**
     * Metamorphic Relation 19: If the monthly mileage is increased, and the staff
     * level is "seniormanager", the fee for overuse of the car should increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        if (!stafflevel.equals("seniormanager")) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double follow_actualmonthlymileage = actualmonthlymileage * 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, follow_actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(follow_out > source_out);
    }

    /**
     * Metamorphic Relation 20: If the monthly sales amount is increased, and the
     * staff level is "supervisor", the total reimbursement amount should increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        if (!stafflevel.equals("supervisor")) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double follow_monthlysalesamount = monthlysalesamount * 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                follow_monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(follow_out > source_out);
    }

    /**
     * Metamorphic Relation 21: If the staff level is "seniormanager", and the
     * actual monthly mileage is less than the allowable mileage, the total
     * reimbursement amount should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        if (!stafflevel.equals("seniormanager")) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /*
         * Construct follow-up input with actual monthly mileage below the allowable
         * mileage
         */
        double follow_actualmonthlymileage = 3000; // Assuming allowable mileage is 4000

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, follow_actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 22: If the staff level is "manager" and the monthly
     * sales amount is less than 50000, the total reimbursement amount should not
     * include airfare reimbursement.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        if (!stafflevel.equals("manager") || monthlysalesamount >= 50000) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out == Math.min(airfareamount, calculateStandardAirfareReimbursement1(monthlysalesamount))
                + otherexpensesamount);
    }

    private double calculateStandardAirfareReimbursement1(double monthlysalesamount) {
        if (monthlysalesamount >= 50000) {
            return Double.POSITIVE_INFINITY; // manager can take any amount of airfare
        } else {
            return 0;
        }
    }

    /**
     * Metamorphic Relation 23: If the staff level is 'seniormanager' and the
     * monthly sales amount is less than 50000, the total reimbursement amount
     * should not include airfare reimbursement.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(String stafflevel, double actualmonthlymileage, double monthlysalesamount, double airfareamount,
            double otherexpensesamount) {
        if (!stafflevel.equals("seniormanager") || monthlysalesamount >= 50000) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage, monthlysalesamount,
                airfareamount, otherexpensesamount);

        /* Verification */
        assertEquals(source_out, otherexpensesamount - (actualmonthlymileage - 4000) * 5);
    }

    /**
     * Metamorphic Relation 24: If monthly mileage is increased, and staff level is
     * 'supervisor', the fee for overuse of the car should increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(String stafflevel, double actualmonthlymileage, double monthlysalesamount, double airfareamount,
            double otherexpensesamount) {
        if (!stafflevel.equals("supervisor")) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage, monthlysalesamount,
                airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double increasedMonthlyMileage = actualmonthlymileage * 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, increasedMonthlyMileage, monthlysalesamount,
                airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out < follow_out);
    }

    /**
     * Metamorphic Relation 25: If the staff level is 'manager' and the monthly
     * sales amount is greater than or equal to 50000, the total reimbursement
     * amount should not increase with an increase in the actual monthly mileage.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(String stafflevel, double actualmonthlymileage, double monthlysalesamount, double airfareamount,
            double otherexpensesamount) {
        if (!stafflevel.equals("manager") || monthlysalesamount < 50000) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage, monthlysalesamount,
                airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double increasedMonthlyMileage = actualmonthlymileage * 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, increasedMonthlyMileage, monthlysalesamount,
                airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out >= follow_out);
    }

    /**
     * Metamorphic Relation 26: If the staff level is 'seniormanager' and the
     * monthly sales amount is less than 80000, the total reimbursement amount
     * should not exceed the airfare amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(String stafflevel, double actualmonthlymileage, double monthlysalesamount, double airfareamount,
            double otherexpensesamount) {
        if (!stafflevel.equals("seniormanager") || monthlysalesamount >= 80000) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage, monthlysalesamount,
                airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out <= airfareamount + otherexpensesamount);
    }

    /**
     * Metamorphic Relation 27: If the staff level is 'supervisor' and the monthly
     * sales amount is greater than or equal to 80000, the airfare reimbursement
     * should be equal to the airfare amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(String stafflevel, double actualmonthlymileage, double monthlysalesamount, double airfareamount,
            double otherexpensesamount) {
        if (!stafflevel.equals("supervisor") || monthlysalesamount < 80000) {
            return;
        }
        /* Get actual airfare reimbursement */
        double airfareReimbursement = Math.min(airfareamount, calculateAirfareReimbursement2(monthlysalesamount));

        /* Verification */
        assertEquals(airfareReimbursement, airfareamount);
    }

    private double calculateAirfareReimbursement2(double monthlysalesamount) {
        return monthlysalesamount >= 80000 ? Double.POSITIVE_INFINITY : 0;
    }

    /**
     * Metamorphic Relation 28: If the staff level is not valid, an exception should
     * be thrown.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(String stafflevel, double actualmonthlymileage, double monthlysalesamount, double airfareamount,
            double otherexpensesamount) {
        String invalidStafflevel = "invalidstafflevel";

        /* Verification */
        assertThrows(IOException.class, () -> {
            ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
            ERS.calculateReimbursementAmount(invalidStafflevel, 3000, 50000, 200, 100);
        });
    }

    /**
     * Metamorphic Relation 29: If the staff level is 'seniormanager', and the
     * monthly sales amount is greater than or equal to 100000, the other expenses
     * reimbursement should be equal to the other expenses amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(String stafflevel, double actualmonthlymileage, double monthlysalesamount, double airfareamount,
            double otherexpensesamount) {
        if (!stafflevel.equals("seniormanager") || monthlysalesamount < 100000) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel,
                actualmonthlymileage, monthlysalesamount,
                airfareamount, otherexpensesamount);

        /* Verification */
        assertEquals(source_out, otherexpensesamount);
    }

    /**
     * Metamorphic Relation 30: If the staff level is 'manager', and the monthly
     * sales amount is less than 80000, the airfare reimbursement should be equal
     * to
     * 0.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(String stafflevel, double actualmonthlymileage, double monthlysalesamount, double airfareamount,
            double otherexpensesamount) {
        if (!stafflevel.equals("manager") || monthlysalesamount >= 80000) {
            return;
        }
        /* Get actual airfare reimbursement */
        double airfareReimbursement = calculateAirfareReimbursement(monthlysalesamount);

        /* Verification */
        assertEquals(airfareReimbursement, 0);
    }

    private double calculateAirfareReimbursement(double monthlysalesamount) {
        return monthlysalesamount >= 80000 ? Double.POSITIVE_INFINITY : 0;
    }

    /**
     * Metamorphic Relation 31: If the monthlysalesamount is multiplied by a
     * positive constant, the total reimbursement amount should also be multiplied
     * by the same constant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(String stafflevel, double actualmonthlymileage, double monthlysalesamount, double airfareamount,
            double otherexpensesamount) {
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel,
                actualmonthlymileage, monthlysalesamount,
                airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double constant = 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel,
                actualmonthlymileage,
                monthlysalesamount * constant, airfareamount, otherexpensesamount *
                        constant);

        /* Verification */
        assertEquals(source_out * constant, follow_out);
    }

    /**
     * Metamorphic Relation 32: If the staff level is 'manager' and the monthly
     * sales amount is less than 50000, the total reimbursement amount should not
     * exceed the airfare amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(String stafflevel, double actualmonthlymileage, double monthlysalesamount, double airfareamount,
            double otherexpensesamount) {
        if (!stafflevel.equals("manager") || monthlysalesamount >= 50000) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel,
                actualmonthlymileage, monthlysalesamount,
                airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out <= airfareamount + otherexpensesamount);
    }

    /**
     * Metamorphic Relation 33: If the staff level is 'seniormanager' and the
     * actual
     * monthly mileage is more than the allowable mileage, the total reimbursement
     * amount should increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(String stafflevel, double actualmonthlymileage, double monthlysalesamount, double airfareamount,
            double otherexpensesamount) {
        if (!stafflevel.equals("seniormanager")) {
            return;
        }

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, 5000,
                monthlysalesamount, airfareamount,
                otherexpensesamount);

        /* Construct follow-up input */
        double increasedMonthlyMileage = 6000; // Assuming allowable mileage is 4000

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel,
                increasedMonthlyMileage, monthlysalesamount,
                airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out < follow_out);
    }

    /**
     * Metamorphic Relation 34: If the staff level is 'seniormanager', and the
     * monthly sales amount is greater than or equal to 100000, then the total
     * reimbursement amount should be equal to airfare amount plus other expenses
     * amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(String stafflevel, double actualmonthlymileage, double monthlysalesamount, double airfareamount,
            double otherexpensesamount) {
        if (!stafflevel.equals("seniormanager") || monthlysalesamount < 100000) {
            return;
        }

        /* Calculation of source output */
        double sourceTotalReimbursementAmount = airfareamount + otherexpensesamount;

        /* Get actual output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double actualTotalReimbursementAmount = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertEquals(sourceTotalReimbursementAmount, actualTotalReimbursementAmount);
    }

    /**
     * Metamorphic Relation 35: If the staff level is 'supervisor' and the monthly
     * sales amount is increased, the airfare reimbursement should also increase
     * or
     * remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(String stafflevel, double actualmonthlymileage, double monthlysalesamount, double airfareamount,
            double otherexpensesamount) {
        if (!stafflevel.equals("supervisor")) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel,
                actualmonthlymileage, monthlysalesamount,
                airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double increasedMonthlySalesAmount = monthlysalesamount * 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel,
                actualmonthlymileage,
                increasedMonthlySalesAmount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out <= follow_out);
    }

    /**
     * Metamorphic Relation 36: If the staff level is 'manager' and the monthly
     * sales amount is less than 50000, the fee for overuse of the car should not
     * exceed the total reimbursement amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(String stafflevel, double actualmonthlymileage, double monthlysalesamount, double airfareamount,
            double otherexpensesamount) {
        if (!stafflevel.equals("manager") || monthlysalesamount >= 50000) {
            return;
        }

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel,
                actualmonthlymileage, monthlysalesamount,
                airfareamount, otherexpensesamount);
        double overUseFee = ERS.calculateOveruseFee(stafflevel, actualmonthlymileage,
                monthlysalesamount);

        /* Verification */
        assertTrue(source_out >= overUseFee);
    }

    /**
     * Metamorphic Relation 37: If the sales staff level is changed, the total
     * reimbursement amount should not decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(String stafflevel, double actualmonthlymileage, double monthlysalesamount, double airfareamount,
            double otherexpensesamount) {
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double sourceOut = ERS.calculateReimbursementAmount(stafflevel,
                actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        String newStafflevel = "seniormanager";

        /* Get follow-up output */
        double followUpOut = ERS.calculateReimbursementAmount(newStafflevel,
                actualmonthlymileage, monthlysalesamount,
                airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(sourceOut <= followUpOut);
    }

    /**
    * Metamorphic Relation 38: If the monthly mileage is increased, the total
    * reimbursement amount should not decrease if the staff level is
    "supervisor".
    */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(String stafflevel, double actualmonthlymileage, double
    monthlysalesamount,
    double airfareamount, double otherexpensesamount) {
    if (!stafflevel.equals("supervisor")) {
    return;
    }
    /* Get source output */
    ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
    double source_out = ERS.calculateReimbursementAmount(stafflevel,
    actualmonthlymileage,
    monthlysalesamount, airfareamount, otherexpensesamount);

    /* Construct follow-up input */
    double follow_actualmonthlymileage = actualmonthlymileage + 500; // Assuming monthly mileage is increased by 500

    /* Get follow-up output */
    double follow_out = ERS.calculateReimbursementAmount(stafflevel,
    follow_actualmonthlymileage,
    monthlysalesamount, airfareamount, otherexpensesamount);

    /* Verification */
    assertTrue(source_out <= follow_out);
    }

    /**
     * Metamorphic Relation 39: If the staff level is 'seniormanager', and the
     * actual monthly mileage is increased, the fee for overuse of the car should
     * also increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(String stafflevel, double actualmonthlymileage, double monthlysalesamount, double airfareamount,
            double otherexpensesamount) {
        if (!stafflevel.equals("seniormanager")) {
            return;
        }

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel,
                actualmonthlymileage, monthlysalesamount,
                airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double increasedMonthlymileage = actualmonthlymileage + 1000;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel,
                increasedMonthlymileage, monthlysalesamount,
                airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out < follow_out);
    }

    /**
     * Metamorphic Relation 40: If the staff level is 'manager' and the actual
     * monthly mileage is increased, the total reimbursement amount should
     * increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(String stafflevel, double actualmonthlymileage, double monthlysalesamount, double airfareamount,
            double otherexpensesamount) {
        if (!stafflevel.equals("manager")) {
            return;
        }

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel,
                actualmonthlymileage, monthlysalesamount,
                airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double increasedMonthlyMileage = actualmonthlymileage + 100;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel,
                increasedMonthlyMileage, monthlysalesamount,
                airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out < follow_out);
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
