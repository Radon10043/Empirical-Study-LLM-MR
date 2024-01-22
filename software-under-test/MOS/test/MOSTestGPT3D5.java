package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.util.stream.Stream;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import src.MSR;
import src.MealOrderingSystem;

public class MOSTestGPT3D5 {

    /**
     * Metamorphic Relation 2: change in the number of crew members should not
     * change the total
     * number of meals for crew members.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        // Get source output
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Construct follow-up input
        int follow_newnumberofcrewmembers = newnumberofcrewmembers + 5; // Change in the number of
                                                                        // crew members

        // Get follow-up output
        MSR follow_out = MOS.generateMSR(aircraftmodel, "y", follow_newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers,
                numberofrequestedbundlesofflowers);

        // Verification
        assertEquals(source_out.numberOfMealsForCrewMembers,
                follow_out.numberOfMealsForCrewMembers);
    }

    /**
     * Metamorphic Relation 3: the number of meals for different classes should be
     * proportional to
     * the respective number of seats for each class.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        // Get source output
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Calculate the expected number of meals for each class based on the number of
        // seats
        int expectedNumberOfFirstClassMeals = source_out.numberOfFirstClassMeals;
        int expectedNumberOfBusinessClassMeals = source_out.numberOfBusinessClassMeals;
        int expectedNumberOfEconomicClassMeals = source_out.numberOfEconomicClassMeals;

        if (aircraftmodel.equals("747200")) {
            expectedNumberOfFirstClassMeals = 0;
        } else if (aircraftmodel.equals("747300")) {
            expectedNumberOfFirstClassMeals = 5 * 2;
            expectedNumberOfBusinessClassMeals = 25 * 2;
            expectedNumberOfEconomicClassMeals = 200 * 2;
        } else if (aircraftmodel.equals("747400")) {
            expectedNumberOfFirstClassMeals = 10 * 2;
            expectedNumberOfBusinessClassMeals = 30 * 2;
            expectedNumberOfEconomicClassMeals = 240 * 2;
        } else if (aircraftmodel.equals("000200")) {
            expectedNumberOfBusinessClassMeals = 35 * 2;
            expectedNumberOfEconomicClassMeals = 210 * 2;
        } else if (aircraftmodel.equals("000300")) {
            expectedNumberOfFirstClassMeals = 10 * 2;
            expectedNumberOfBusinessClassMeals = 40 * 2;
            expectedNumberOfEconomicClassMeals = 215 * 2;
        }

        // Verification
        assertEquals(expectedNumberOfFirstClassMeals, source_out.numberOfFirstClassMeals);
        assertEquals(expectedNumberOfBusinessClassMeals, source_out.numberOfBusinessClassMeals);
        assertEquals(expectedNumberOfEconomicClassMeals, source_out.numberOfEconomicClassMeals);
    }

    /**
     * Metamorphic Relation 4: Increasing the number of child passengers should
     * increase the number
     * of child meals proportionally.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        // Get source output
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Increase the number of child passengers
        int increasedNumberOfChildPassengers = numberofchildpassengers + 5;

        // Get follow-up output
        MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                increasedNumberOfChildPassengers, numberofrequestedbundlesofflowers);

        // Verification
        assertEquals(increasedNumberOfChildPassengers * 2, follow_out.numberOfChildMeals);
    }

    /**
     * Metamorphic Relation 5: Doubling the number of pilots should double the
     * number of meals for
     * pilots.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        // Get source output
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Double the number of pilots
        int doubledNumberOfPilots = newnumberofpilots * 2;

        // Get follow-up output
        MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, doubledNumberOfPilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Verification
        assertEquals(source_out.numberOfMealsForPilots * 2, follow_out.numberOfMealsForPilots);
    }

    /**
     * Metamorphic Relation 6: Modifying the model to "747200" should result in 0
     * first class seats,
     * and modifying it to "747300" should result in 5 seats, and so on.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Fix by Radon */
        // Get source output
        MealOrderingSystem MOS1 = new MealOrderingSystem();
        MSR source_out = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Get follow-up output for "747300" model
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR follow_out_747300 = MOS2.generateMSR("747300", changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        switch (aircraftmodel) {
            case "747200":
                // Verification for 747200 model
                assertEquals(0, MOS1.getNumberOfFirstClassSeats());
                break;
            case "747300":
                // Verification for 747300 model
                assertEquals(5, MOS2.getNumberOfFirstClassSeats());
                break;
            // Add cases for other aircraft models as needed
        }
    }

    /**
     * Metamorphic Relation 7: Checking if the number of requested pilots, when
     * changed, affects the
     * number of pilots assigned.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Fix by Radon */
        // Get source output
        MealOrderingSystem MOS1 = new MealOrderingSystem();
        MSR source_out = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Modify the number of requested pilots
        int modifiedNumberofPilots = newnumberofpilots + 2;

        // Get follow-up output with modified number of requested pilots
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR follow_out = MOS2.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, "y", modifiedNumberofPilots, numberofchildpassengers,
                numberofrequestedbundlesofflowers);

        // Verification
        assertEquals(modifiedNumberofPilots, MOS2.getNumberOfPilots());
    }

    /**
     * Metamorphic Relation 8: The total number of meals should be proportional to
     * the total number
     * of passengers and crew members.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        // Get source output
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Calculate the total number of passengers and crew members
        int totalPersons = numberofchildpassengers + newnumberofcrewmembers + newnumberofpilots;

        // Calculate the expected total number of meals
        int expectedTotalMeals = source_out.numberOfFirstClassMeals
                + source_out.numberOfBusinessClassMeals + source_out.numberOfEconomicClassMeals
                + source_out.numberOfMealsForCrewMembers + source_out.numberOfMealsForPilots
                + source_out.numberOfChildMeals;

        // Verify the proportionality
        assertEquals(expectedTotalMeals, totalPersons * 2);
    }

    /**
     * Metamorphic Relation 9: If the crew members are increased, the number of
     * first class seats
     * should not impact the meals for the crew members.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        // Get source output
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Increase the number of crew members
        int increasedCrewMembers = newnumberofcrewmembers + 5;

        // Get follow-up output with increased crew members and modified first class
        // seats
        MSR follow_out = MOS.generateMSR(aircraftmodel, "y", increasedCrewMembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers,
                numberofrequestedbundlesofflowers);

        // Verification
        assertEquals(source_out.numberOfMealsForCrewMembers,
                follow_out.numberOfMealsForCrewMembers);
    }

    /**
     * Metamorphic Relation 10: If the number of child passengers and the number of
     * requested
     * bundles of flowers are doubled, the total number of child meals and the total
     * number of
     * requested bundles of flowers should also double.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        // Get source output
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Double the number of child passengers and requested bundles of flowers
        int doubledChildPassengers = numberofchildpassengers * 2;
        int doubledRequestedBundlesOfFlowers = numberofrequestedbundlesofflowers * 2;

        // Get follow-up output with doubled inputs
        MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                doubledChildPassengers, doubledRequestedBundlesOfFlowers);

        // Verification
        assertEquals(doubledChildPassengers * 2, follow_out.numberOfChildMeals);
        assertEquals(doubledRequestedBundlesOfFlowers, follow_out.numberOfBundlesOfFlowers);
    }

    /**
     * Metamorphic Relation 11: Increasing the number of crew members should not
     * impact the number
     * of first class seats.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Fix by Radon */
        // Get source output
        MealOrderingSystem MOS1 = new MealOrderingSystem();
        MSR source_out = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Increase the number of crew members
        int increasedCrewMembers = newnumberofcrewmembers + 5;

        // Get follow-up output with increased crew members and modified first class
        // seats
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR follow_out = MOS2.generateMSR(aircraftmodel, "y", increasedCrewMembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers,
                numberofrequestedbundlesofflowers);

        // Verification
        assertEquals(MOS1.getNumberOfFirstClassSeats(), MOS2.getNumberOfFirstClassSeats());
    }

    /**
     * Metamorphic Relation 12: If the aircraft model is changed, the total number
     * of meals should
     * also change accordingly.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {

        // Get source output
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Change the aircraft model
        String modifiedAircraftModel = "787";

        // Get follow-up output with modified aircraft model
        MSR follow_out = MOS.generateMSR(modifiedAircraftModel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Verification
        assertNotEquals(
                source_out.numberOfFirstClassMeals + source_out.numberOfBusinessClassMeals
                        + source_out.numberOfEconomicClassMeals,
                follow_out.numberOfFirstClassMeals + follow_out.numberOfBusinessClassMeals
                        + follow_out.numberOfEconomicClassMeals);
    }

    /**
     * Metamorphic Relation 13: Doubling the number of first class seats should
     * double the number of
     * first class meals.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Fix by Radon */
        // Get source output
        MealOrderingSystem MOS1 = new MealOrderingSystem();
        MSR source_out = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Double the number of first class seats
        int doubledFirstClassSeats = MOS1.getNumberOfFirstClassSeats() * 2;

        // Get follow-up output with doubled first class seats
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR follow_out = MOS2.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Verification
        assertEquals(source_out.numberOfFirstClassMeals * 2, follow_out.numberOfFirstClassMeals);
    }

    /**
     * Metamorphic Relation 14: Doubling the number of economic class seats should
     * double the number
     * of economic class meals.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Fix by Radon */
        // Get source output
        MealOrderingSystem MOS1 = new MealOrderingSystem();
        MSR source_out = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Double the number of economic class seats
        int doubledEconomicSeats = MOS1.getNumberOfEconomicClassSeats() * 2;

        // Get follow-up output with doubled economic class seats
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR follow_out = MOS2.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Verification
        assertEquals(source_out.numberOfEconomicClassMeals * 2,
                follow_out.numberOfEconomicClassMeals);
    }

    /**
     * Metamorphic Relation 15: Changing the number of child passengers and the
     * number of requested
     * bundles of flowers should not affect the number of first class seats.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Fix by Radon */
        // Get source output
        MealOrderingSystem MOS1 = new MealOrderingSystem();
        MSR source_out = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Modify the number of child passengers and the number of requested bundles of
        // flowers
        int modifiedChildPassengers = numberofchildpassengers + 10;
        int modifiedBundlesOfFlowers = numberofrequestedbundlesofflowers + 5;

        // Get follow-up output with modified inputs
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR follow_out = MOS2.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                modifiedChildPassengers, modifiedBundlesOfFlowers);

        // Verification
        assertEquals(MOS1.getNumberOfFirstClassSeats(), MOS2.getNumberOfFirstClassSeats());
    }

    /**
     * Metamorphic Relation 16: If the number of child passengers decreases, the
     * number of child
     * meals should also decrease proportionally.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        // Get source output
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Decrease the number of child passengers
        int decreasedChildPassengers = numberofchildpassengers - 5;

        // Get follow-up output with decreased child passengers
        MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                decreasedChildPassengers, numberofrequestedbundlesofflowers);

        // Verification
        assertEquals(2 * decreasedChildPassengers, follow_out.numberOfChildMeals);
    }

    /**
     * Metamorphic Relation 17: Changing the number of first class seats should not
     * impact the
     * number of meals for pilots.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Fix by Radon */
        // Get source output
        MealOrderingSystem MOS1 = new MealOrderingSystem();
        MSR source_out = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Modify the number of first class seats
        int modifiedFirstClassSeats = MOS1.getNumberOfFirstClassSeats() + 5;

        // Get follow-up output with modified first class seats
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR follow_out = MOS2.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Verification
        assertEquals(source_out.numberOfMealsForPilots, follow_out.numberOfMealsForPilots);
    }

    /**
     * Metamorphic Relation 18: Changing the number of first class seats should not
     * affect the total
     * number of requested bundles of flowers.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Fix by Radon */
        // Get source output
        MealOrderingSystem MOS1 = new MealOrderingSystem();
        MSR source_out = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Modify the number of first class seats
        int modifiedFirstClassSeats = MOS1.getNumberOfFirstClassSeats() + 5;

        // Get follow-up output with modified first class seats
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR follow_out = MOS2.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Verification
        assertEquals(MOS1.getNumberOfRequestedBundlesOfFlowers(),
                MOS2.getNumberOfRequestedBundlesOfFlowers());
    }

    /**
     * Metamorphic Relation 19: If the number of requested bundles of flowers
     * increases, the total
     * number of bundles of flowers should also increase by the same factor.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        // Get source output
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Increase the number of requested bundles of flowers
        int increasedRequestedBundlesOfFlowers = numberofrequestedbundlesofflowers * 2;

        // Get follow-up output with increased requested bundles of flowers
        MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, increasedRequestedBundlesOfFlowers);

        // Verification
        assertEquals(increasedRequestedBundlesOfFlowers, follow_out.numberOfBundlesOfFlowers);
    }

    /**
     * Metamorphic Relation 20: Changing the number of crew members and the number
     * of child
     * passengers will not affect the number of first class seats.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Fix by Radon */
        // Get source output
        MealOrderingSystem MOS1 = new MealOrderingSystem();
        MSR source_out = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Modify the number of crew members and the number of child passengers
        int modifiedCrewMembers = newnumberofcrewmembers + 2;
        int modifiedChildPassengers = numberofchildpassengers + 3;

        // Get follow-up output with modified crew members and child passengers
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR follow_out = MOS2.generateMSR(aircraftmodel, "y", modifiedCrewMembers,
                changeinthenumberofpilots, newnumberofpilots, modifiedChildPassengers,
                numberofrequestedbundlesofflowers);

        // Verification
        assertEquals(MOS1.getNumberOfFirstClassSeats(), MOS2.getNumberOfFirstClassSeats());
    }

    /**
     * Metamorphic Relation 21: Doubling the number of business class seats should
     * double the number
     * of business class meals.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Fix by Radon */
        // Get source output
        MealOrderingSystem MOS1 = new MealOrderingSystem();
        MSR sourceOut = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Double the number of business class seats
        int doubledBusinessClassSeats = MOS1.getNumberOfBusinessClassSeats() * 2;

        // Get follow-up output with doubled business class seats
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR followUpOut = MOS2.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Verification
        assertEquals(followUpOut.numberOfBusinessClassMeals,
                sourceOut.numberOfBusinessClassMeals * 2);
    }

    /**
     * Metamorphic Relation 22: If the number of child passengers and the number of
     * requested
     * bundles of flowers increase, the total number of meals and the total number
     * of flowers should
     * also increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        // Get source output
        MealOrderingSystem mos = new MealOrderingSystem();
        MSR sourceOut = mos.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Increase the number of child passengers and the number of requested bundles
        // of flowers
        int increasedChildPassengers = numberofchildpassengers * 2;
        int increasedRequestedBundlesOfFlowers = numberofrequestedbundlesofflowers * 2;

        // Get follow-up output with increased inputs
        MSR followUpOut = mos.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                increasedChildPassengers, increasedRequestedBundlesOfFlowers);

        // Verification
        assertEquals(followUpOut.numberOfMealsForCrewMembers,
                sourceOut.numberOfMealsForCrewMembers * 2);
        assertEquals(followUpOut.numberOfBundlesOfFlowers, sourceOut.numberOfBundlesOfFlowers * 2);
    }

    /**
     * Metamorphic Relation 23: Increasing the number of business class seats should
     * affect the
     * total number of meals for business class passengers.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Fix by Radon */
        // Get source output
        MealOrderingSystem MOS1 = new MealOrderingSystem();
        MSR sourceOut = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Increase the number of business class seats
        int increasedBusinessClassSeats = MOS1.getNumberOfBusinessClassSeats() + 10;

        // Get follow-up output with increased business class seats
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR followUpOut = MOS2.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Verification
        assertTrue(followUpOut.numberOfBusinessClassMeals >= sourceOut.numberOfBusinessClassMeals);
    }

    /**
     * Metamorphic Relation 24: Changing the number of requested bundles of flowers
     * should not
     * affect the number of meals for crew members.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Fix by Radon */
        // Get source output
        MealOrderingSystem MOS1 = new MealOrderingSystem();
        MSR sourceOut = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Increase the number of requested bundles of flowers
        int increasedRequestedBundlesOfFlowers = numberofrequestedbundlesofflowers + 5;

        // Get follow-up output with increased requested bundles of flowers
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR followUpOut = MOS2.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, increasedRequestedBundlesOfFlowers);

        // Verification
        assertEquals(sourceOut.numberOfMealsForCrewMembers,
                followUpOut.numberOfMealsForCrewMembers);
    }

    /**
     * Metamorphic Relation 25: Doubling the number of crew members should double
     * the total number
     * of meals for crew members.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        // Get source output
        MealOrderingSystem mos = new MealOrderingSystem();
        MSR sourceOut = mos.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Double the number of crew members
        int doubledCrewMembers = 2 * newnumberofcrewmembers;

        // Get follow-up output with doubled crew members
        MSR followUpOut = mos.generateMSR(aircraftmodel, "y", doubledCrewMembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers,
                numberofrequestedbundlesofflowers);

        // Verification
        assertEquals(2 * sourceOut.numberOfMealsForCrewMembers,
                followUpOut.numberOfMealsForCrewMembers);
    }

    /**
     * Metamorphic Relation 26: Adding more crew members should not change the
     * number of meals for
     * child passengers.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        // Get source output
        MealOrderingSystem mos = new MealOrderingSystem();
        MSR sourceOut = mos.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Add more crew members
        int moreCrewMembers = newnumberofcrewmembers + 5;

        // Get follow-up output with more crew members
        MSR followUpOut = mos.generateMSR(aircraftmodel, "y", moreCrewMembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers,
                numberofrequestedbundlesofflowers);

        // Verification
        assertEquals(sourceOut.numberOfChildMeals, followUpOut.numberOfChildMeals);
    }

    /**
     * Metamorphic Relation 27: Changing the number of economic class seats should
     * not affect the
     * total number of meals for pilots.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Fix by Radon */
        // Get source output
        MealOrderingSystem MOS1 = new MealOrderingSystem();
        MSR sourceOut = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Increase the number of economic class seats
        int increasedEconomicClassSeats = MOS1.getNumberOfEconomicClassSeats() + 10;

        // Get follow-up output with increased economic class seats
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR followUpOut = MOS2.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Verification
        assertEquals(sourceOut.numberOfMealsForPilots, followUpOut.numberOfMealsForPilots);
    }

    /**
     * Metamorphic Relation 28: Increasing the number of child passengers and the
     * number of meals
     * for child passengers proportionally.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        // Get source output
        MealOrderingSystem mos = new MealOrderingSystem();
        MSR sourceOut = mos.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Double the number of child passengers
        int doubledChildPassengers = 2 * numberofchildpassengers;

        // Get follow-up output with doubled child passengers
        MSR followUpOut = mos.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                doubledChildPassengers, numberofrequestedbundlesofflowers);

        // Verification
        assertEquals(2 * sourceOut.numberOfChildMeals, followUpOut.numberOfChildMeals);
    }

    /**
     * Metamorphic Relation 29: Doubling the number of first class seats should
     * double the total
     * number of first class meals.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Fix by Radon */
        // Get source output
        MealOrderingSystem MOS1 = new MealOrderingSystem();
        MSR source_out = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Double the number of first class seats
        int follow_numberoffirstclassseats = MOS1.getNumberOfFirstClassSeats() * 2;

        // Get follow-up output
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR follow_out = MOS2.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, follow_numberoffirstclassseats);

        // Verification
        assertEquals(source_out.numberOfFirstClassMeals * 2, follow_out.numberOfFirstClassMeals);
    }

    /**
     * Metamorphic Relation 30: Changing the number of requested bundles of flowers
     * should not
     * affect the total number of economic class meals.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        // Get source output
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Modify the number of requested bundles of flowers
        int follow_numberofrequestedbundlesofflowers = numberofrequestedbundlesofflowers + 5;

        // Get follow-up output
        MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, follow_numberofrequestedbundlesofflowers);

        // Verification
        assertEquals(source_out.numberOfEconomicClassMeals, follow_out.numberOfEconomicClassMeals);
    }

    /**
     * Metamorphic Relation 31: Increasing the number of child passengers should
     * increase the total
     * number of child meals.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        // Instantiate the MealOrderingSystem
        MealOrderingSystem mos = new MealOrderingSystem();

        // Get the source output
        MSR sourceOut = mos.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Increase the number of child passengers
        int increasedChildPassengers = numberofchildpassengers + 5;

        // Get the follow-up output with increased child passengers
        MSR followUpOut = mos.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                increasedChildPassengers, numberofrequestedbundlesofflowers);

        // Verification
        assertTrue(followUpOut.numberOfChildMeals > sourceOut.numberOfChildMeals);
        assertEquals(followUpOut.numberOfMealsForCrewMembers,
                sourceOut.numberOfMealsForCrewMembers);
    }

    /**
     * Metamorphic Relation 32: If the number of requested bundles of flowers is
     * increased, the
     * total number of meals for pilots should not change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        // Instantiate the MealOrderingSystem
        MealOrderingSystem mos = new MealOrderingSystem();

        // Get the source output
        MSR sourceOut = mos.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Increase the number of requested bundles of flowers
        int increasedRequestedBundlesOfFlowers = numberofrequestedbundlesofflowers + 10;

        // Get the follow-up output with increased requested bundles of flowers
        MSR followUpOut = mos.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, increasedRequestedBundlesOfFlowers);

        // Verification
        assertEquals(sourceOut.numberOfMealsForPilots, followUpOut.numberOfMealsForPilots);
    }

    /**
     * Metamorphic Relation 33: Increasing the number of crew members and child
     * passengers should
     * not affect the number of first class seats.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Fix by Radon */
        // Instantiate the MealOrderingSystem
        MealOrderingSystem MOS1 = new MealOrderingSystem();

        // Get the source output
        MSR sourceOut = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Increase the number of crew members and child passengers
        int increasedCrewMembers = newnumberofcrewmembers + 5;
        int increasedChildPassengers = numberofchildpassengers + 10;

        // Get the follow-up output with increased crew members and child passengers
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR followUpOut = MOS2.generateMSR(aircraftmodel, "y", increasedCrewMembers,
                changeinthenumberofpilots, newnumberofpilots, increasedChildPassengers,
                numberofrequestedbundlesofflowers);

        // Verification
        assertEquals(MOS1.getNumberOfFirstClassSeats(), MOS2.getNumberOfFirstClassSeats());
    }

    /**
     * Metamorphic Relation 34: Changing the number of first class seats should not
     * affect the total
     * number of crew meals and pilot meals.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Fix by Radon */
        // Instantiate the MealOrderingSystem
        MealOrderingSystem MOS1 = new MealOrderingSystem();

        // Get the source output
        MSR sourceOut = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Change the number of first class seats
        int modifiedFirstClassSeats = MOS1.getNumberOfFirstClassSeats() + 5;

        // Get the follow-up output with modified first class seats
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR followUpOut = MOS2.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Verification
        assertEquals(sourceOut.numberOfMealsForCrewMembers,
                followUpOut.numberOfMealsForCrewMembers);
        assertEquals(sourceOut.numberOfMealsForPilots, followUpOut.numberOfMealsForPilots);
    }

    /**
     * Metamorphic Relation 35: Keeping all other attributes unchanged, if the
     * number of child
     * passengers is doubled, the total number of child meals should also double.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        MealOrderingSystem mos = new MealOrderingSystem();
        MSR sourceOut = mos.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        int doubledChildPassengers = numberofchildpassengers * 2;

        MSR followUpOut = mos.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                doubledChildPassengers, numberofrequestedbundlesofflowers);

        assertEquals(sourceOut.numberOfChildMeals * 2, followUpOut.numberOfChildMeals);
    }

    /**
     * Metamorphic Relation 36: If the number of meals for crew members is
     * increased, the number of
     * crew members meeting the proposed numberofcrewmembers grows.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Fix by Radon */
        final MealOrderingSystem MOS1 = new MealOrderingSystem();
        final MSR sourceOut = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Increase meals for crew members */
        final int increasedMealsForCrewMembers = sourceOut.numberOfMealsForCrewMembers + 10;

        final MealOrderingSystem MOS2 = new MealOrderingSystem();
        final MSR followUpOut = MOS2.generateMSR(aircraftmodel, "y", // change in the number of crew
                                                                     // members
                newnumberofcrewmembers + 5, // proposed number of crew members
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers,
                numberofrequestedbundlesofflowers);

        assertTrue(MOS2.getNumberOfCrewMembers() > newnumberofcrewmembers);
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
