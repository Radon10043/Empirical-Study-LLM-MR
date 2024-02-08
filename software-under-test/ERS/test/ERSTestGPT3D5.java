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
     * Metamorphic Relation 1: If actualmonthlymileage is increased, with stafflevel and other inputs
     * constant, the total reimbursement amount should either stay the same or decrease.
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
        double follow_actualmonthlymileage = actualmonthlymileage * 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, follow_actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out >= follow_out);
    }

    /**
     * Metamorphic Relation 2: If airfareamount is increased, with stafflevel and other inputs constant,
     * the total reimbursement amount should either stay the same or increase.
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
        double follow_airfareamount = airfareamount * 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, follow_airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out <= follow_out);
    }

    /**
     * Metamorphic Relation 3: If otherexpensesamount is increased, with stafflevel and other inputs
     * constant, the total reimbursement amount should increase.
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
        double follow_otherexpensesamount = otherexpensesamount * 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, follow_otherexpensesamount);

        /* Verification */
        assertTrue(source_out < follow_out);
    }

    /**
     * Metamorphic Relation 4: If stafflevel is changed from "manager" to "supervisor", with other inputs
     * constant, the total reimbursement amount should either stay the same or decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        if (!stafflevel.equals("manager"))
            return;

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        String follow_stafflevel = "supervisor";

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(follow_stafflevel,
                actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out >= follow_out);
    }

    /**
     * Metamorphic Relation 5: If actualmonthlymileage is decreased, with stafflevel and other inputs
     * constant, the total reimbursement amount should increase.
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
        double follow_actualmonthlymileage = actualmonthlymileage / 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, follow_actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out < follow_out);
    }

    /**
     * Metamorphic Relation 6: If monthlysalesamount is decreased, the total reimbursement amount
     * should either stay the same or decrease.
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
        double follow_monthlysalesamount = monthlysalesamount / 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                follow_monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out >= follow_out);
    }

    /**
     * Metamorphic Relation 7: If airfareamount is decreased, with stafflevel and other inputs constant,
     * the total reimbursement amount should either stay the same or decrease.
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
        double follow_airfareamount = airfareamount / 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, follow_airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out >= follow_out);
    }

    /**
     * Metamorphic Relation 8: If otherexpensesamount is decreased, with stafflevel and other inputs
     * constant, the total reimbursement amount should decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double follow_otherexpensesamount = otherexpensesamount / 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, follow_otherexpensesamount);

        /* Verification */
        assertTrue(source_out > follow_out);
    }

    /**
     * Metamorphic Relation 9: If stafflevel is changed from "seniormanager" to "seniormanager",
     * with other inputs constant, the total reimbursement amount should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
            double airfareamount, double otherexpensesamount) {
        if (!stafflevel.equals("seniormanager"))
            return;

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input (same as source input) */
        String follow_stafflevel = stafflevel;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(follow_stafflevel,
                actualmonthlymileage, monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 10: If actualmonthlymileage is set to the maximum allowable mileage for the staff level
     * and sales amount, airfare amount, and other expenses amount are constant, the total reimbursement amount
     * should not increase.
     * @throws IOException 
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String stafflevel, double actualmonthlymileage, double monthlysalesamount, 
            double airfareamount, double otherexpensesamount) throws IOException {
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double allowableMileage = ERS.getAllowableMileageForStaffLevel(stafflevel);
        double costPerKilometer = ERS.getCostPerKilometerForStaffLevel(stafflevel);
        double adjustedMileage = Math.min(actualmonthlymileage, allowableMileage);
        double feeForOveruse = (actualmonthlymileage - adjustedMileage) * costPerKilometer;

        double source_out = ERS.calculateReimbursementAmount(stafflevel, allowableMileage, 
            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double follow_actualmonthlymileage = allowableMileage;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, follow_actualmonthlymileage, 
            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out >= follow_out);
    }

    /**
     * Metamorphic Relation 11: If the sales amount is set to zero, with input stafflevel, 
     * actualmonthlymileage, airfareamount, and otherexpensesamount constant, the total 
     * reimbursement amount should be zero.
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
        double follow_monthlysalesamount = 0;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage, 
            follow_monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertEquals(0.0, follow_out);
    }

    /**
     * Metamorphic Relation 12: If actualmonthlymileage is increased and monthlysalesamount is also increased, 
     * with stafflevel, airfareamount, and otherexpensesamount constant, the total reimbursement amount 
     * should either stay the same or increase.
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
        double follow_actualmonthlymileage = actualmonthlymileage * 2;
        double follow_monthlysalesamount = monthlysalesamount * 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, follow_actualmonthlymileage,
                follow_monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out <= follow_out);
    }

    /**
     * Metamorphic Relation 13: If the stafflevel is changed for higher tier levels (e.g., "supervisor" to "manager"),
     * with other inputs constant, the total reimbursement amount should either stay the same or increase.
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
        String follow_stafflevel = "seniormanager";

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(follow_stafflevel, actualmonthlymileage, 
            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out <= follow_out);
    }

    /**
     * Metamorphic Relation 14: If the airfare amount is zero, with stafflevel, actualmonthlymileage, 
     * monthlysalesamount, and otherexpensesamount constant, the total reimbursement amount should either 
     * stay the same or decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(String stafflevel, double actualmonthlymileage, double monthlysalesamount, 
            double airfareamount, double otherexpensesamount) {
        if (airfareamount == 0) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage, 
            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double follow_airfareamount = 0;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage, 
            monthlysalesamount, follow_airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out >= follow_out);
    }

    /**
     * Metamorphic Relation 15: If the monthly sales amount is increased for a staff level "seniormanager"
     * with other inputs constant, the total reimbursement amount should increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String stafflevel, double actualmonthlymileage, double monthlysalesamount, 
            double airfareamount, double otherexpensesamount) {
        if (!stafflevel.equals("seniormanager")) {
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
        assertTrue(source_out < follow_out);
    }

    /**
     * Metamorphic Relation 16: If other expenses amount is zero, with stafflevel, actualmonthlymileage, 
     * monthlysalesamount, and airfareamount constant, the total reimbursement amount should either 
     * stay the same or decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(String stafflevel, double actualmonthlymileage, double monthlysalesamount, 
            double airfareamount, double otherexpensesamount) {
        if (otherexpensesamount == 0) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage, 
            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double follow_otherexpensesamount = 0;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage, 
            monthlysalesamount, airfareamount, follow_otherexpensesamount);

        /* Verification */
        assertTrue(source_out >= follow_out);
    }

    /**
     * Metamorphic Relation 17: If stafflevel is changed to an invalid level, with other inputs constant, 
     * the method should not throw an exception, and the total reimbursement amount should remain 
     * unaffected (equal to zero).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String stafflevel, double actualmonthlymileage, double monthlysalesamount, 
            double airfareamount, double otherexpensesamount) {
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage, 
            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        String follow_stafflevel = "invalidlevel";

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(follow_stafflevel, actualmonthlymileage, 
            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertEquals(0.0, follow_out);
    }

    /**
     * Metamorphic Relation 18: If stafflevel is "seniormanager" and monthlysalesamount is zero, 
     * with other inputs constant, the total reimbursement amount should be equal to airfare amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String stafflevel, double actualmonthlymileage, double monthlysalesamount, 
            double airfareamount, double otherexpensesamount) {
        if (!stafflevel.equals("seniormanager") || monthlysalesamount != 0) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage, 
            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertEquals(airfareamount, source_out);
    }

    /**
     * Metamorphic Relation 19: If actualmonthlymileage is zero, with a valid stafflevel and other 
     * inputs constant, the total reimbursement amount should not include any car overuse fees.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String stafflevel, double actualmonthlymileage, double monthlysalesamount, 
            double airfareamount, double otherexpensesamount) {
        if (actualmonthlymileage != 0) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage, 
            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out <= (airfareamount + otherexpensesamount));
    }

    /**
     * Metamorphic Relation 20: If monthlysalesamount is equal to the threshold for airfare reimbursement, 
     * then the total reimbursement amount should be at least the airfare amount.
     * @throws IOException 
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(String stafflevel, double actualmonthlymileage, double monthlysalesamount, 
            double airfareamount, double otherexpensesamount) throws IOException {
        if (monthlysalesamount < ExpenseReimbursementSystem.getThresholdForAirfareReimbursement(stafflevel)) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage, 
            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out >= airfareamount);
    }

    /**
     * Metamorphic Relation 21: If the stafflevel is "seniormanager", and the total reimbursement amount is calculated, 
     * then changing the stafflevel to "manager" should not increase the reimbursement amount.
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
    
        /* Construct follow-up input */
        String follow_stafflevel = "manager";

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(follow_stafflevel, actualmonthlymileage, 
            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out >= follow_out);
    }

    /**
     * Metamorphic Relation 22: If the stafflevel is "supervisor", and the total reimbursement amount is calculated, 
     * then increasing the actual monthly mileage should not decrease the reimbursement amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(String stafflevel, double actualmonthlymileage, double monthlysalesamount, 
            double airfareamount, double otherexpensesamount) {
        if (!stafflevel.equals("supervisor")) {
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
        assertTrue(source_out <= follow_out);
    }

    /**
     * Metamorphic Relation 23: If the monthly sales amount is zero, then changing the stafflevel should not 
     * affect the reimbursement amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(String stafflevel, double actualmonthlymileage, double monthlysalesamount, 
            double airfareamount, double otherexpensesamount) {
        if (monthlysalesamount != 0) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage, 
            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        String follow_stafflevel = "seniormanager";

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(follow_stafflevel, actualmonthlymileage, 
            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 24: If the stafflevel is "seniormanager" and the airfare amount is zero, with other inputs constant,
     * the total reimbursement amount should either stay the same or decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
                    double airfareamount, double otherexpensesamount) {
        if (!stafflevel.equals("seniormanager") || airfareamount != 0) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        String follow_stafflevel = "manager";

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(follow_stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out >= follow_out);
    }

    /**
     * Metamorphic Relation 25: If the monthly sales amount exceeds a certain threshold, then changing the stafflevel to "manager" 
     * should not decrease the total reimbursement amount, with other inputs constant.
     * @throws IOException 
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
                    double airfareamount, double otherexpensesamount) throws IOException {
        if (monthlysalesamount < ExpenseReimbursementSystem.getThresholdForAirfareReimbursement("seniormanager")) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        String follow_stafflevel = "manager";

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(follow_stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out <= follow_out);
    }

    /**
     * Metamorphic Relation 26: If other expenses amount is set to zero, with stafflevel, actualmonthlymileage, 
     * monthlysalesamount, and airfareamount constant, the total reimbursement amount should decrease.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
                    double airfareamount, double otherexpensesamount) {
        if (otherexpensesamount != 0) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Construct follow-up input */
        double follow_otherexpensesamount = 0;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, follow_otherexpensesamount);

        /* Verification */
        assertTrue(source_out > follow_out);
    }

    /**
     * Metamorphic Relation 27: If the actual monthly mileage is equal to the allowable mileage for the staff level,
     * and the monthly sales amount is zero, with other inputs constant, the total reimbursement amount should only include
     * the reimbursement for car overuse fee.
     * @throws IOException 
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
                    double airfareamount, double otherexpensesamount) throws IOException {
        if (monthlysalesamount != 0 || actualmonthlymileage != ExpenseReimbursementSystem.getAllowableMileageForStaffLevel(stafflevel)) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertEquals(source_out, ExpenseReimbursementSystem.calculateCarOveruseFee(stafflevel, actualmonthlymileage));
    }

    /**
     * Metamorphic Relation 28: If monthly sales amount is increased for a staff level "seniormanager" and actual monthly mileage 
     * remains zero, with other inputs constant, the total reimbursement amount should be zero.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
                    double airfareamount, double otherexpensesamount) {
        if (actualmonthlymileage != 0 || !stafflevel.equals("seniormanager")) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertEquals(0, source_out);
    }

    /**
     * Metamorphic Relation 29: If monthly sales amount is increased for a staff level "seniormanager" and airfare amount is zero,
     * with other inputs constant, the total reimbursement amount should only include the reimbursement for car overuse fee.
     * @throws IOException 
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
                    double airfareamount, double otherexpensesamount) throws IOException {
        if (airfareamount != 0 || !stafflevel.equals("seniormanager")) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertEquals(source_out, ExpenseReimbursementSystem.calculateCarOveruseFee(stafflevel, actualmonthlymileage));
    }

    /**
     * Metamorphic Relation 30: If the monthly sales amount is increased and the airfare amount is increased, 
     * the total reimbursement amount should either stay the same or increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
                    double airfareamount, double otherexpensesamount) {
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, otherexpensesamount);
    
        /* Construct follow-up input */
        double follow_monthlysalesamount = monthlysalesamount * 2;
        double follow_airfareamount = airfareamount * 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                                                            follow_monthlysalesamount, follow_airfareamount, otherexpensesamount);

        /* Verification */
        assertTrue(source_out <= follow_out);
    }

    /**
     * Metamorphic Relation 31: If the stafflevel is "seniormanager" and other expenses amount is zero, with other inputs constant, 
     * the total reimbursement amount should equal the sum of the reimbursement for car overuse fee and airfare amount.
     * @throws IOException 
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
                    double airfareamount, double otherexpensesamount) throws IOException {
        if (otherexpensesamount != 0 || !stafflevel.equals("seniormanager")) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, otherexpensesamount);

        /* Verification */
        assertEquals(source_out, ExpenseReimbursementSystem.calculateCarOveruseFee(stafflevel, actualmonthlymileage) + airfareamount);
    }

    /**
     * Metamorphic Relation 32: If the stafflevel is "manager" and the actual monthly mileage is less than the allowable mileage, 
     * while monthly sales amount, airfare amount, and other expenses amount remain constant, the total reimbursement amount should 
     * include the reimbursement for car overuse fee.
     * @throws IOException 
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
                    double airfareamount, double otherexpensesamount) throws IOException {
        if (!stafflevel.equals("manager")) {
            return;
        }

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, otherexpensesamount);

        double allowableMileage = ExpenseReimbursementSystem.getAllowableMileageForStaffLevel(stafflevel);
        if (actualmonthlymileage < allowableMileage) {
            double overuseFee = (allowableMileage - actualmonthlymileage) * ExpenseReimbursementSystem.getCostPerKilometerForStaffLevel(stafflevel);
            /* Verification */
            assertEquals(overuseFee, source_out);
        }
    }

    /**
     * Metamorphic Relation 33: If the stafflevel is "seniormanager" and the actual monthly mileage is greater than the allowable mileage, 
     * while monthly sales amount, airfare amount, and other expenses amount remain constant, the total reimbursement amount 
     * should include the reimbursement for car overuse fee, airfare amount, and other expenses amount.
     * @throws IOException 
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
                    double airfareamount, double otherexpensesamount) throws IOException {
        if (!stafflevel.equals("seniormanager")) {
            return;
        }

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, otherexpensesamount);

        double allowableMileage = ExpenseReimbursementSystem.getAllowableMileageForStaffLevel(stafflevel);
        if (actualmonthlymileage > allowableMileage) {
            double overuseFee = (actualmonthlymileage - allowableMileage) * ExpenseReimbursementSystem.getCostPerKilometerForStaffLevel(stafflevel);
            /* Verification */
            assertEquals(overuseFee + airfareamount + otherexpensesamount, source_out);
        }
    }

    /**
     * Metamorphic Relation 34: If the stafflevel is "supervisor" and the monthly sales amount exceeds the threshold for other expenses reimbursement, 
     * while actual monthly mileage and airfare amount remain constant, the total reimbursement amount 
     * should include the reimbursement for car overuse fee, airfare amount, and other expenses amount.
     * @throws IOException 
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
                    double airfareamount, double otherexpensesamount) throws IOException {
        if (!stafflevel.equals("supervisor")) {
            return;
        }

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, otherexpensesamount);

        double thresholdForOtherExpenses = ExpenseReimbursementSystem.getThresholdForOtherExpensesReimbursement();
        if (monthlysalesamount > thresholdForOtherExpenses) {
            double overuseFee = (actualmonthlymileage - ExpenseReimbursementSystem.getAllowableMileageForStaffLevel(stafflevel)) 
                * ExpenseReimbursementSystem.getCostPerKilometerForStaffLevel(stafflevel);
            /* Verification */
            assertTrue(source_out >= (overuseFee + airfareamount + otherexpensesamount));
        }
    }

    /**
     * Metamorphic Relation 35: If the stafflevel is "manager" and the actual monthly mileage is equal to the allowable mileage,
     * while monthly sales amount, airfare amount, and other expenses amount remain constant, the total reimbursement amount 
     * should include the reimbursement for car overuse fee and airfare amount.
     * @throws IOException 
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
                    double airfareamount, double otherexpensesamount) throws IOException {
        if (!stafflevel.equals("manager")) {
            return;
        }

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, otherexpensesamount);

        double allowableMileage = ExpenseReimbursementSystem.getAllowableMileageForStaffLevel(stafflevel);
        if (actualmonthlymileage == allowableMileage) {
            double overuseFee = (actualmonthlymileage - allowableMileage) * ExpenseReimbursementSystem.getCostPerKilometerForStaffLevel(stafflevel);
            /* Verification */
            assertEquals(overuseFee + airfareamount, source_out);
        }
    }

    /**
     * Metamorphic Relation 36: If monthly sales amount and other expenses amount are both zero, 
     * the total reimbursement amount should only include the reimbursement for car overuse fee, 
     * and the airfare amount for a senior manager.
     * @throws IOException 
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
                    double airfareamount, double otherexpensesamount) throws IOException {
        if (monthlysalesamount != 0 || otherexpensesamount != 0 || !stafflevel.equals("seniormanager")) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, otherexpensesamount);
        double overuseFee = Math.max(actualmonthlymileage - ExpenseReimbursementSystem.getAllowableMileageForStaffLevel(stafflevel), 0) 
            * ExpenseReimbursementSystem.getCostPerKilometerForStaffLevel(stafflevel);
        /* Verification */
        assertEquals(overuseFee + airfareamount, source_out);
    }

    /**
     * Metamorphic Relation 37: If the stafflevel is "manager" and the monthly sales amount is equal to the threshold for airfare reimbursement, 
     * then the total reimbursement amount should be at least the airfare amount.
     * @throws IOException 
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
                    double airfareamount, double otherexpensesamount) throws IOException {
        if (!stafflevel.equals("manager") || monthlysalesamount < ExpenseReimbursementSystem.getThresholdForAirfareReimbursement(stafflevel)) {
            return;
        }
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, otherexpensesamount);
        /* Verification */
        assertTrue(source_out >= airfareamount);
    }

    /**
     * Metamorphic Relation 38: If other expenses amount is increased, while actual monthly mileage, monthly sales amount, 
     * and airfare amount remain constant, the total reimbursement amount should increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
                    double airfareamount, double otherexpensesamount) {
        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, otherexpensesamount);
    
        /* Construct follow-up input */
        double increasedOtherExpensesAmount = otherexpensesamount * 2;

        /* Get follow-up output */
        double follow_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, increasedOtherExpensesAmount);

        /* Verification */
        assertTrue(source_out < follow_out);
    }

    /**
     * Metamorphic Relation 39: If both airfare amount and other expenses amount are zero, 
     * the total reimbursement amount should only include the reimbursement for car overuse fee, 
     * given that the monthly sales amount exceeds the threshold for other expenses reimbursement.
     * @throws IOException 
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
                    double airfareamount, double otherexpensesamount) throws IOException {
        if (airfareamount !=0 || otherexpensesamount !=0) {
            return;
        }

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, otherexpensesamount);
    
        double thresholdForOtherExpenses = ExpenseReimbursementSystem.getThresholdForOtherExpensesReimbursement();
        if (monthlysalesamount > thresholdForOtherExpenses) {
            double overuseFee = Math.max(actualmonthlymileage - ExpenseReimbursementSystem.getAllowableMileageForStaffLevel(stafflevel), 0) 
                * ExpenseReimbursementSystem.getCostPerKilometerForStaffLevel(stafflevel);
        
            /* Verification */
            assertEquals(overuseFee, source_out);
        }
    }

    /**
     * Metamorphic Relation 40: If the stafflevel is "seniormanager" and the actual monthly mileage is equal to the allowable mileage, 
     * while monthly sales amount, airfare amount, and other expenses amount remain constant, the total reimbursement amount 
     * should include the reimbursement for car overuse fee and airfare amount.
     * @throws IOException 
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
                    double airfareamount, double otherexpensesamount) throws IOException {
        if (!stafflevel.equals("seniormanager")) {
            return;
        }

        /* Get source output */
        ExpenseReimbursementSystem ERS = new ExpenseReimbursementSystem();
        double source_out = ERS.calculateReimbursementAmount(stafflevel, actualmonthlymileage,
                                                            monthlysalesamount, airfareamount, otherexpensesamount);

        double allowableMileage = ExpenseReimbursementSystem.getAllowableMileageForStaffLevel(stafflevel);
        if (actualmonthlymileage == allowableMileage) {
            double overuseFee = (actualmonthlymileage - allowableMileage) * ExpenseReimbursementSystem.getCostPerKilometerForStaffLevel(stafflevel);
            /* Verification */
            assertEquals(overuseFee + airfareamount, source_out);
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
