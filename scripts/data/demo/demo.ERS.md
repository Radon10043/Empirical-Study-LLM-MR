```java
/**
 * Metamorphic Relation 1: If stafflevel is changed from "seniormanager" to "manager", with
 * other inputs constant, the total reimbursement amount should not increase.
 */
@ParameterizedTest
@MethodSource("testcaseProvider")
public void test1(String stafflevel, double actualmonthlymileage, double monthlysalesamount,
        double airfareamount, double otherexpensesamount) {
    if (!stafflevel.equals("seniormanager"))
        return;

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
    assertTrue(source_out >= follow_out);
}

/**
 * Metamorphic Relation 2: If monthlysalesamount is increased, the total reimbursement amount
 * should either stay the same or increase.
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
```