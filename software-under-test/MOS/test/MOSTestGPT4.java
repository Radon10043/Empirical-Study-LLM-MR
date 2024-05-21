package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;
import java.security.SecureRandom;
import java.util.stream.Stream;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import src.MSR;
import src.MealOrderingSystem;

public class MOSTestGPT4 {

    public boolean MSREquals(MSR msr1, MSR msr2) {
        return msr1.numberOfFirstClassMeals == msr2.numberOfFirstClassMeals
                && msr1.numberOfBusinessClassMeals == msr2.numberOfBusinessClassMeals
                && msr1.numberOfEconomicClassMeals == msr2.numberOfEconomicClassMeals
                && msr1.numberOfMealsForCrewMembers == msr2.numberOfMealsForCrewMembers
                && msr1.numberOfMealsForPilots == msr2.numberOfMealsForPilots
                && msr1.numberOfChildMeals == msr2.numberOfChildMeals
                && msr1.numberOfBundlesOfFlowers == msr2.numberOfBundlesOfFlowers;
    }

    /**
     * Metamorphic Relation 2: keeping other attributes unchanged, if the input for
     * changeinthenumberofcrewmembers is "y" and there is an increase in the number of crew members,
     * the number of crew meals should increase accordingly.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        /* Get source output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, "n", // no change originally
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Construct follow-up input indicating a change in the number of crew members */
        String follow_changeinthenumberofcrewmembers = "y"; // indicate change now
        // Ensure an increase
        int follow_newnumberofcrewmembers = newnumberofcrewmembers + 1;

        /* Get follow-up output */
        MSR follow_out = MOS.generateMSR(aircraftmodel, follow_changeinthenumberofcrewmembers,
                follow_newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Verification */
        assertTrue(follow_out.numberOfMealsForCrewMembers > source_out.numberOfMealsForCrewMembers);
    }

    /**
     * Metamorphic Relation 3: keeping other parameters constant, doubling the number of child
     * passengers should result in double the number of child meals.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Get source output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Construct follow-up input */
        int follow_numberofchildpassengers = numberofchildpassengers * 2;

        /* Get follow-up output */
        MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                follow_numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Verification */
        assertTrue(source_out.numberOfChildMeals * 2 == follow_out.numberOfChildMeals);
    }

    /**
     * Metamorphic Relation 4: keeping other parameters constant, changing the aircraft model to a
     * larger or smaller model (assuming such models exist) should increase or decrease the number
     * of meals for first, business, and economic classes accordingly. This assumes that the
     * implementation details to get a largerOrSmallerModel are provided.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Illegal
        // /* Get source output */
        // MealOrderingSystem MOS = new MealOrderingSystem();
        // MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
        // newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
        // numberofchildpassengers, numberofrequestedbundlesofflowers);

        // /* Construct follow-up input with a different aircraft model */
        // String largerOrSmallerModel = getLargerOrSmallerModel(aircraftmodel); //
        // Implementation-specific
        // MSR follow_out = MOS.generateMSR(largerOrSmallerModel, changeinthenumberofcrewmembers,
        // newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
        // numberofchildpassengers, numberofrequestedbundlesofflowers);

        // /* Verification */
        // // Assuming largerOrSmallerModel returns a larger model
        // assertTrue(follow_out.numberOfFirstClassMeals > source_out.numberOfFirstClassMeals);
        // assertTrue(follow_out.numberOfBusinessClassMeals >
        // source_out.numberOfBusinessClassMeals);
        // assertTrue(follow_out.numberOfEconomicClassMeals >
        // source_out.numberOfEconomicClassMeals);

        // You would also need a similar test case where a smaller model is chosen
        // to ensure number of meals decreases.
    }

    /**
     * Metamorphic Relation 5: If the number of crew members is changed from one non-zero number to
     * another while keeping the rest of the inputs constant, the number of crew meals in the MSR
     * should reflect the change proportionately.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        /* Original output */
        MealOrderingSystem MOS = new MealOrderingSystem();

        assumeTrue(newnumberofcrewmembers > 5); // Assuming the new number is greater than 5
        int originalNumberOfCrewMembers = newnumberofcrewmembers - 5; // Any non-zero number

        MSR original_out = MOS.generateMSR(aircraftmodel, "y", originalNumberOfCrewMembers, "n", 0,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* New output with updated number of crew members */
        MSR new_out = MOS.generateMSR(aircraftmodel, "y", newnumberofcrewmembers, "n", 0,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Verification */
        assertEquals(new_out.numberOfMealsForCrewMembers / original_out.numberOfMealsForCrewMembers,
                (double) newnumberofcrewmembers / originalNumberOfCrewMembers);
    }

    /**
     * Metamorphic Relation 6: Regardless of any changes in the number of crew members or pilots,
     * the number of child meals should remain unchanged if the number of child passengers remains
     * constant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        /* Original output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR original_out = MOS.generateMSR(aircraftmodel, "n", 0, "n", 0, numberofchildpassengers,
                numberofrequestedbundlesofflowers);

        /* Updated output with changed number of crew members and pilots */
        MSR updated_out = MOS.generateMSR(aircraftmodel, "y", 10, "y", 4, numberofchildpassengers,
                numberofrequestedbundlesofflowers);

        /* Verification */
        assertEquals(original_out.numberOfChildMeals, updated_out.numberOfChildMeals);
    }

    /**
     * Metamorphic Relation 7: If no parameter changes (crew members, pilots), the generateMSR
     * function should be idempotent, meaning that multiple invocations with the same inputs produce
     * the same result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        /* First invocation */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR first_out = MOS.generateMSR(aircraftmodel, "n", 0, "n", 0, numberofchildpassengers,
                numberofrequestedbundlesofflowers);

        /* Second invocation */
        MSR second_out = MOS.generateMSR(aircraftmodel, "n", 0, "n", 0, numberofchildpassengers,
                numberofrequestedbundlesofflowers);

        /* Verification */
        assertTrue(MSREquals(first_out, second_out));
    }

    /**
     * Metamorphic Relation 8: If the number of requested bundles of flowers is set to zero and
     * later a non-zero value, the only change in the MSR result should be the reflection of the new
     * number of flower bundles.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers) { // Fixed
        /* Output with zero bundles of flowers */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR zero_bundles_of_flowers_out = MOS.generateMSR(aircraftmodel,
                changeinthenumberofcrewmembers, newnumberofcrewmembers, changeinthenumberofpilots,
                newnumberofpilots, numberofchildpassengers, 0);

        /* Output with non-zero bundles of flowers */
        int numberOfRequestedBundlesOfFlowers = 5; // Non-zero value
        MSR non_zero_bundles_of_flowers_out = MOS.generateMSR(aircraftmodel,
                changeinthenumberofcrewmembers, newnumberofcrewmembers, changeinthenumberofpilots,
                newnumberofpilots, numberofchildpassengers, numberOfRequestedBundlesOfFlowers);

        /* Verification: check only the flower count changed */
        assertEquals(zero_bundles_of_flowers_out.numberOfFirstClassMeals,
                non_zero_bundles_of_flowers_out.numberOfFirstClassMeals);
        assertEquals(zero_bundles_of_flowers_out.numberOfBusinessClassMeals,
                non_zero_bundles_of_flowers_out.numberOfBusinessClassMeals);
        assertEquals(zero_bundles_of_flowers_out.numberOfEconomicClassMeals,
                non_zero_bundles_of_flowers_out.numberOfEconomicClassMeals);
        assertEquals(zero_bundles_of_flowers_out.numberOfMealsForCrewMembers,
                non_zero_bundles_of_flowers_out.numberOfMealsForCrewMembers);
        assertEquals(zero_bundles_of_flowers_out.numberOfMealsForPilots,
                non_zero_bundles_of_flowers_out.numberOfMealsForPilots);
        assertEquals(zero_bundles_of_flowers_out.numberOfChildMeals,
                non_zero_bundles_of_flowers_out.numberOfChildMeals);
        assertEquals(numberOfRequestedBundlesOfFlowers,
                non_zero_bundles_of_flowers_out.numberOfBundlesOfFlowers);
    }

    /**
     * Metamorphic Relation 9: If the change in the number of pilots is "y" with an increase in the
     * new number of pilots, while keeping the rest of the inputs constant, the number of pilot
     * meals in the MSR should increase proportionately.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        assumeTrue(newnumberofpilots > 5); // Assuming the new number is greater than 0
        int originalNumberOfPilots = newnumberofpilots - 5; // Any non-zero number

        /* Original output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR original_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, "n", // no change in number of pilots
                originalNumberOfPilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* New output with updated number of pilots */
        changeinthenumberofpilots = "y"; // indicating change in number of pilots
        MSR new_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Verification: Check that pilot meals increased proportionally */
        assertTrue(new_out.numberOfMealsForPilots > original_out.numberOfMealsForPilots);
        assertEquals(new_out.numberOfMealsForPilots / original_out.numberOfMealsForPilots,
                (double) newnumberofpilots / originalNumberOfPilots);
    }

    /**
     * Metamorphic Relation 10: Given a fixed aircraft model, the ratio of crew meals to pilot meals
     * should stay approximately the same if the ratios of their respective numbers do not change,
     * regardless of the absolute numbers.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        /* Original output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR original_out = MOS.generateMSR(aircraftmodel, "y", 5, "y", 2, numberofchildpassengers,
                numberofrequestedbundlesofflowers);

        /* Increased crews and pilots but maintaining the same ratio */
        MSR scaled_up_out = MOS.generateMSR(aircraftmodel, "y", 10, "y", 4, numberofchildpassengers,
                numberofrequestedbundlesofflowers);

        /* Verification: ratio of meals should remain approximately the same */
        assertEquals(
                (double) original_out.numberOfMealsForCrewMembers
                        / original_out.numberOfMealsForPilots,
                (double) scaled_up_out.numberOfMealsForCrewMembers
                        / scaled_up_out.numberOfMealsForPilots,
                0.1 /* Tolerance for potential rounding issues */
        );
    }

    /**
     * Metamorphic Relation 11: Given the same aircraft model and number of passengers, if the flag
     * for changing the number of crew members or pilots is toggled from "n" to "y" but without
     * actually changing the numbers (new number is the same as the default), the MSR should remain
     * unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        /* Original output with no change in crew or pilot numbers */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR original_out = MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "n",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Supposed 'change' in crew and pilot numbers that is the same as the original */
        MSR no_actual_change_out = MOS.generateMSR(aircraftmodel, "y", newnumberofcrewmembers, "y",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Verification */
        assertEquals(original_out.numberOfMealsForCrewMembers,
                no_actual_change_out.numberOfMealsForCrewMembers);
        assertEquals(original_out.numberOfMealsForPilots,
                no_actual_change_out.numberOfMealsForPilots);
    }

    /**
     * Metamorphic Relation 12: If the number of requested bundles of flowers is increased or
     * decreased, other meal-related outputs should remain constant, only the number of requested
     * flower bundles should reflect the change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers) { // Fixed
        /* Original output with certain number of flower bundles */
        int originalBundlesOfFlowers = 3;
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR original_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, originalBundlesOfFlowers);

        /* Updated output with increased flower bundles */
        int updatedBundlesOfFlowers = 5;
        MSR updated_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, updatedBundlesOfFlowers);

        /* Verification that only flower bundles count has changed */
        assertEquals(original_out.numberOfFirstClassMeals, updated_out.numberOfFirstClassMeals);
        assertEquals(original_out.numberOfBusinessClassMeals,
                updated_out.numberOfBusinessClassMeals);
        assertEquals(original_out.numberOfEconomicClassMeals,
                updated_out.numberOfEconomicClassMeals);
        assertEquals(original_out.numberOfMealsForCrewMembers,
                updated_out.numberOfMealsForCrewMembers);
        assertEquals(original_out.numberOfMealsForPilots, updated_out.numberOfMealsForPilots);
        assertEquals(original_out.numberOfChildMeals, updated_out.numberOfChildMeals);
        assertNotEquals(original_out.numberOfBundlesOfFlowers,
                updated_out.numberOfBundlesOfFlowers);
    }

    /**
     * Metamorphic Relation 13: For a consistent aircraft model, if the status of crew member or
     * pilot change is toggled but the actual numbers remain unchanged, the resulting number of
     * meals for crew members and pilots should remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        /* Original output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR original_out = MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "n",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Output with toggled change status but same numbers */
        MSR toggled_change_out = MOS.generateMSR(aircraftmodel, "y", newnumberofcrewmembers, "y",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Verification */
        assertEquals(original_out.numberOfMealsForCrewMembers,
                toggled_change_out.numberOfMealsForCrewMembers);
        assertEquals(original_out.numberOfMealsForPilots,
                toggled_change_out.numberOfMealsForPilots);
    }

    /**
     * Metamorphic Relation 14: If given a fixed aircraft model, doubling the number of pilots while
     * keeping other parameters constant should result in twice as many pilot meals.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        /* Original output with a given number of pilots */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR original_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, "y", newnumberofcrewmembers, numberofchildpassengers,
                numberofrequestedbundlesofflowers);

        /* New output with doubled number of pilots */
        int doubledNumberOfPilots = newnumberofcrewmembers * 2;
        MSR new_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, "y", doubledNumberOfPilots, numberofchildpassengers,
                numberofrequestedbundlesofflowers);

        /* Verification */
        assertEquals(original_out.numberOfMealsForPilots * 2, new_out.numberOfMealsForPilots);
    }

    /**
     * Metamorphic Relation 15: If the number of child passengers is increased or decreased, the
     * number of meals for all adult classes should stay constant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int originalNumberOfChildPassengers, int numberofrequestedbundlesofflowers) { // Fixed
        /* Original output with a given number of child passengers */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR original_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                originalNumberOfChildPassengers, numberofrequestedbundlesofflowers);

        /* New output with changed number of child passengers */
        int changedNumberOfChildPassengers = originalNumberOfChildPassengers + 5; // or any other
                                                                                  // positive or
                                                                                  // negative
                                                                                  // integer
        MSR new_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                changedNumberOfChildPassengers, numberofrequestedbundlesofflowers);

        /* Verification */
        assertEquals(original_out.numberOfFirstClassMeals, new_out.numberOfFirstClassMeals);
        assertEquals(original_out.numberOfBusinessClassMeals, new_out.numberOfBusinessClassMeals);
        assertEquals(original_out.numberOfEconomicClassMeals, new_out.numberOfEconomicClassMeals);
        assertEquals(original_out.numberOfMealsForCrewMembers, new_out.numberOfMealsForCrewMembers);
        assertEquals(original_out.numberOfMealsForPilots, new_out.numberOfMealsForPilots);
        // Note: The number of child meals will differ based on the number of child passengers
    }

    /**
     * Metamorphic Relation 16: Changing the number of crew members without changing the number of
     * pilots or passengers should not affect the number of passenger meals calculated for each
     * class.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Initial MSR calculation */
        MealOrderingSystem MOS = new MealOrderingSystem();
        assumeTrue(newnumberofcrewmembers > 5); // Assuming the new number is greater than 5
        int originalNumberofCrewMembers = newnumberofcrewmembers - 5; // Any non-zero number

        MSR initialMSR = MOS.generateMSR(aircraftmodel, "y", originalNumberofCrewMembers, "n",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Follow-up MSR calculation with updated crew members */
        MSR updatedMSR = MOS.generateMSR(aircraftmodel, "y", newnumberofpilots, "n",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Verification */
        assertEquals(initialMSR.numberOfFirstClassMeals, updatedMSR.numberOfFirstClassMeals);
        assertEquals(initialMSR.numberOfBusinessClassMeals, updatedMSR.numberOfBusinessClassMeals);
        assertEquals(initialMSR.numberOfEconomicClassMeals, updatedMSR.numberOfEconomicClassMeals);
        // Note: The number of crew meals will differ as we have changed the number of crew members.
    }

    /**
     * Metamorphic Relation 17: If the input parameters remain constant except for the number of
     * crew members which are halved, the number of crew meals in the MSR should also be halved,
     * assuming the original number of crew members was even.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        assumeTrue(newnumberofcrewmembers > 5); // Assuming the new number is greater than 5
        int originalNumberofCrewMembers = newnumberofcrewmembers - 5; // Any non-zero number

        /* Assuming the original number of crew members is even and greater than 0 */
        if (originalNumberofCrewMembers > 0 && originalNumberofCrewMembers % 2 == 0) {
            /* Initial MSR calculation */
            MealOrderingSystem MOS = new MealOrderingSystem();
            MSR initialMSR = MOS.generateMSR(aircraftmodel, "y", originalNumberofCrewMembers, "n",
                    newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            /* Follow-up MSR calculation with halved crew members */
            int halvedNumberOfCrew = originalNumberofCrewMembers / 2;
            MSR halvedMSR = MOS.generateMSR(aircraftmodel, "y", halvedNumberOfCrew, "n",
                    newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            /* Verification */
            assertEquals(initialMSR.numberOfMealsForCrewMembers / 2,
                    halvedMSR.numberOfMealsForCrewMembers);
        }
    }

    /**
     * Metamorphic Relation 18: Varying the aircraft model while keeping other parameters constant
     * should result in a discernible change in the number of meals for each class when the aircraft
     * models have different capacities.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Assuming that originalAircraftModel and newAircraftModel have different capacities */
        String newAircraftModel = aircraftmodel.equals("747200") ? "747300" : "747200"; // Any new
                                                                                        // model
                                                                                        // name

        /* Initial MSR calculation with original aircraft model */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR initialMSR = MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "n",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Follow-up MSR calculation with new aircraft model */
        MSR newModelMSR = MOS.generateMSR(newAircraftModel, "n", newnumberofcrewmembers, "n",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Verification: Check for changes in the number of meals for each class */
        assertNotEquals(initialMSR.numberOfFirstClassMeals, newModelMSR.numberOfFirstClassMeals);
        assertNotEquals(initialMSR.numberOfBusinessClassMeals,
                newModelMSR.numberOfBusinessClassMeals);
        assertNotEquals(initialMSR.numberOfEconomicClassMeals,
                newModelMSR.numberOfEconomicClassMeals);
        // Note: Depending on the relation between capacity of models, you will need more
        // assertions.
    }

    /**
     * Metamorphic Relation 19: If all input parameters are the same, except for updating the number
     * of crew members to be a fraction (e.g., half) of the original assuming the original is even,
     * the number of crew meals should update to be proportional to the fraction of the change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        assumeTrue(newnumberofcrewmembers > 5); // Assuming the new number is greater than 5
        int originalNumberofCrewMembers = newnumberofcrewmembers - 5; // Any non-zero number

        // Ensure the original number of crew members is even and greater than 0
        if (originalNumberofCrewMembers % 2 == 0 && originalNumberofCrewMembers > 0) {
            int halvedNumberofCrewMembers = originalNumberofCrewMembers / 2;

            /* Get source output */
            MealOrderingSystem MOS = new MealOrderingSystem();
            MSR source_out = MOS.generateMSR(aircraftmodel, "n", originalNumberofCrewMembers, "n",
                    newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            /* Get follow-up output with halved crew members */
            MSR follow_out = MOS.generateMSR(aircraftmodel, "y", halvedNumberofCrewMembers, "n",
                    newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            /* Verification */
            assertEquals(source_out.numberOfMealsForCrewMembers / 2,
                    follow_out.numberOfMealsForCrewMembers);
        }
    }

    /**
     * Metamorphic Relation 20: Given the same inputs for aircraft model, crew and pilot numbers,
     * and number of child passengers, incrementing the number of requested bundles of flowers by a
     * fixed amount should always increment the MSR's corresponding flower count by that amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        int incrementBundlesOfFlowers = 10;

        /* Get source output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "n",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Get follow-up output with incremented bundles of flowers */
        MSR follow_out = MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "n",
                newnumberofpilots, numberofchildpassengers,
                numberofrequestedbundlesofflowers + incrementBundlesOfFlowers);

        /* Verification */
        assertEquals(source_out.numberOfBundlesOfFlowers + incrementBundlesOfFlowers,
                follow_out.numberOfBundlesOfFlowers);
    }

    /**
     * Metamorphic Relation 21: For the same aircraft model and constant numbers of crew, pilots,
     * and child passengers, the ratio of first class to business class meals should remain constant
     * when the number of requested bundles of flowers is varied.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        int changedNumberofrequestedbundlesofflowers = numberofrequestedbundlesofflowers + 5;

        /* Get source output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "n",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Get follow-up output with updated bundles of flowers */
        MSR follow_out =
                MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "n", newnumberofpilots,
                        numberofchildpassengers, changedNumberofrequestedbundlesofflowers);

        /* Verification */
        double sourceRatio =
                (double) source_out.numberOfFirstClassMeals / source_out.numberOfBusinessClassMeals;
        double followRatio =
                (double) follow_out.numberOfFirstClassMeals / follow_out.numberOfBusinessClassMeals;
        assertEquals(sourceRatio, followRatio, 0.001); // Allowing for a small floating-point error
                                                       // tolerance
    }

    /**
     * Metamorphic Relation 22: If the number of pilots changes while everything else remains
     * constant, it should not affect the number of meals calculated for child passengers.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        assumeTrue(newnumberofpilots > 5); // Assuming the new number is greater than 5
        int originalNumberOfPilots = newnumberofpilots - 5; // Any non-zero number

        /* Initial conditions */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR initialMSR = MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "n",
                originalNumberOfPilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* After changing the number of pilots */
        MSR newPilotMSR = MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "y",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Verification */
        assertEquals(initialMSR.numberOfChildMeals, newPilotMSR.numberOfChildMeals);
    }

    /**
     * Metamorphic Relation 23: If all parameters remain constant except for a change in the number
     * of economic class seats (simulated by changing the aircraft model to one with a different
     * capacity), the number of meals for the economic class should change in accordance with the
     * new seat count.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        String modifiedAircraftModel = aircraftmodel.equals("747200") ? "747300" : "747200";

        // Here, it's assumed that modifiedAircraftModel has a different economic class capacity
        // from initialAircraftModel
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR initialMSR = MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "n",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        MSR modifiedMSR = MOS.generateMSR(modifiedAircraftModel, "n", newnumberofcrewmembers, "n",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Assertion would depend on whether modifiedAircraftModel has more or fewer economic class
        // seats than initialAircraftModel
        assertTrue(modifiedMSR.numberOfEconomicClassMeals != initialMSR.numberOfEconomicClassMeals);
    }

    /**
     * Metamorphic Relation 24: Independent of changes in any other parameter, if the aircraft model
     * remains the same, the number of requested bundles of flowers should always exactly match the
     * input value.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR output = MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "n",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        assertEquals(numberofrequestedbundlesofflowers, output.numberOfBundlesOfFlowers);
    }

    /**
     * Metamorphic Relation 25: Swapping the number of crew members with the number of pilots while
     * keeping the total sum of both constants should not change the summed meals provided for both
     * roles, assuming a 1:1 meal ratio between crew members and pilots.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        int totalCrewAndPilots = newnumberofcrewmembers + newnumberofpilots;

        // Initial MSR calculation with original crew and pilot numbers
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR initialMSR = MOS.generateMSR(aircraftmodel, "y", newnumberofcrewmembers, "y",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        // MSR calculation after swapping the numbers
        MSR swappedMSR = MOS.generateMSR(aircraftmodel, "y", newnumberofpilots, "y",
                newnumberofcrewmembers, numberofchildpassengers, numberofrequestedbundlesofflowers);

        int summedInitialMeals =
                initialMSR.numberOfMealsForCrewMembers + initialMSR.numberOfMealsForPilots;
        int summedSwappedMeals =
                swappedMSR.numberOfMealsForCrewMembers + swappedMSR.numberOfMealsForPilots;

        assertEquals(totalCrewAndPilots, (newnumberofpilots + newnumberofcrewmembers));
        assertEquals(summedInitialMeals, summedSwappedMeals);
    }

    /**
     * Metamorphic Relation 26: If the aircraft model and number of child passengers remain
     * constant, changes in the number of crew members and pilots should affect only their
     * respective meals and not the number of child meals provided.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        // Initial calculation with some default number of crew and pilots
        assumeTrue(newnumberofcrewmembers > 5); // Assuming the new number is greater than 5
        assumeTrue(newnumberofpilots > 2); // Assuming the new number is greater than 2
        int defaultNumberofCrewMembers = newnumberofcrewmembers - 5;
        int defaultNumberofPilots = newnumberofpilots - 2;

        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR initialMSR = MOS.generateMSR(aircraftmodel, "y", defaultNumberofCrewMembers, "y",
                defaultNumberofPilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Updated calculation with new numbers
        MSR updatedMSR = MOS.generateMSR(aircraftmodel, "y", newnumberofcrewmembers, "y",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        assertEquals(initialMSR.numberOfChildMeals, updatedMSR.numberOfChildMeals);
    }

    /**
     * Metamorphic Relation 27: Given the same aircraft model, increasing the number of child
     * passengers while reducing the number of adult passengers (crew or pilot) in such a way that
     * the total number of passengers remains constant, should only reflect in an increase in the
     * child meals and a decrease in the respective adult meals.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(String aircraftmodel, String changeinthenumberofcrewmembers,
            int numberofcrewmembers, String changeinthenumberofpilots, int numberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { //
        int offset = 5;

        // Only perform test if there's enough room to adjust crew and child numbers
        if (numberofcrewmembers > offset && numberofchildpassengers > offset) {
            int newNumberofchildpassengers = numberofchildpassengers + offset;
            int newNumberofCrewMembers = numberofcrewmembers - offset;

            MealOrderingSystem MOS = new MealOrderingSystem();
            MSR initialMSR = MOS.generateMSR(aircraftmodel, "y", numberofcrewmembers, "n", 0,
                    numberofchildpassengers, numberofrequestedbundlesofflowers);

            MSR adjustedMSR = MOS.generateMSR(aircraftmodel, "y", newNumberofCrewMembers, "n", 0,
                    newNumberofchildpassengers, numberofrequestedbundlesofflowers);

            // Check child meals increased and adult (crew) meals decreased
            assertTrue(adjustedMSR.numberOfChildMeals > initialMSR.numberOfChildMeals);
            assertTrue(
                    adjustedMSR.numberOfMealsForCrewMembers < initialMSR.numberOfMealsForCrewMembers);
            // Total meals for passengers stays constant
            assertEquals((initialMSR.numberOfChildMeals + initialMSR.numberOfMealsForCrewMembers),
                    (adjustedMSR.numberOfChildMeals + adjustedMSR.numberOfMealsForCrewMembers));
        }
    }

    /**
     * Metamorphic Relation 28: Maintaining the number of child passengers and requested bundles of
     * flowers, increase in new pilots without changing crew members should only affect pilot meals.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(String aircraftmodel, String changeinthenumberofcrewmembers,
            int numberofcrewmembers, String changeinthenumberofpilots, int numberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        SecureRandom rand = new SecureRandom();
        int increaseAmountPilots = rand.nextInt(10) + 1;

        /* Make sure increaseAmountPilots is not zero */
        int newNumberofPilots = numberofpilots + increaseAmountPilots;

        /* Original MSR output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR originalMSR = MOS.generateMSR(aircraftmodel, "n", numberofcrewmembers, "y",
                numberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Follow-up MSR with increased pilots */
        MSR updatedMSR = MOS.generateMSR(aircraftmodel, "n", numberofcrewmembers, "y",
                newNumberofPilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Verification */
        assertTrue(updatedMSR.numberOfMealsForPilots > originalMSR.numberOfMealsForPilots);
        assertEquals(updatedMSR.numberOfMealsForCrewMembers,
                originalMSR.numberOfMealsForCrewMembers);
        assertEquals(updatedMSR.numberOfChildMeals, originalMSR.numberOfChildMeals);
        assertEquals(updatedMSR.numberOfBundlesOfFlowers, originalMSR.numberOfBundlesOfFlowers);
    }

    /**
     * Metamorphic Relation 29: For a fixed number of pilots and crew members, an increase in child
     * passengers should leave adult meals unchanged while increasing child meals proportionally.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        SecureRandom rand = new SecureRandom();
        int increaseAmountChildPassengers = rand.nextInt(10) + 1;

        /* Make sure increaseAmountChildPassengers is not zero */
        int newNumberofChildPassengers = numberofchildpassengers + increaseAmountChildPassengers;

        /* Original MSR output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR originalMSR = MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "n",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Follow-up MSR with increased child passengers */
        MSR updatedMSR = MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "n",
                newnumberofpilots, newNumberofChildPassengers, numberofrequestedbundlesofflowers);

        /* Verification */
        assertTrue(updatedMSR.numberOfChildMeals > originalMSR.numberOfChildMeals);
        assertEquals(updatedMSR.numberOfFirstClassMeals, originalMSR.numberOfFirstClassMeals);
        assertEquals(updatedMSR.numberOfBusinessClassMeals, originalMSR.numberOfBusinessClassMeals);
        assertEquals(updatedMSR.numberOfEconomicClassMeals, originalMSR.numberOfEconomicClassMeals);
        assertEquals(updatedMSR.numberOfMealsForCrewMembers,
                originalMSR.numberOfMealsForCrewMembers);
        assertEquals(updatedMSR.numberOfMealsForPilots, originalMSR.numberOfMealsForPilots);
    }

    /**
     * Metamorphic Relation 30: Swapping the increased amount of crew members with an equivalent
     * decrease in the number of child passengers should result in analogous changes in the
     * corresponding meal counts while maintaining the total meals tally constant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(String aircraftmodel, String changeinthenumberofcrewmembers,
            int numberofcrewmembers, String changeinthenumberofpilots, int numberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        SecureRandom rand = new SecureRandom();
        int increaseAmountCrew = rand.nextInt(1, numberofchildpassengers);

        /*
         * The increase in crew members should be equal to decrease in child passengers for a swap
         */
        assumeTrue(increaseAmountCrew > 0 && increaseAmountCrew <= numberofchildpassengers);
        int newNumberofCrewMembers = numberofcrewmembers + increaseAmountCrew;
        int newNumberofChildPassengers = numberofchildpassengers - increaseAmountCrew;

        /* Original MSR output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR originalMSR = MOS.generateMSR(aircraftmodel, "n", numberofcrewmembers, "n",
                numberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Follow-up MSR with increased crew and decreased child passengers */
        MSR updatedMSR = MOS.generateMSR(aircraftmodel, "y", newNumberofCrewMembers, "n",
                numberofpilots, newNumberofChildPassengers, numberofrequestedbundlesofflowers);

        /* Total meals calculation */
        int originalTotalMeals =
                originalMSR.numberOfMealsForCrewMembers + originalMSR.numberOfChildMeals;
        int updatedTotalMeals =
                updatedMSR.numberOfMealsForCrewMembers + updatedMSR.numberOfChildMeals;

        /* Verification */
        assertTrue(
                updatedMSR.numberOfMealsForCrewMembers > originalMSR.numberOfMealsForCrewMembers);
        assertTrue(updatedMSR.numberOfChildMeals < originalMSR.numberOfChildMeals);
        assertEquals(originalTotalMeals, updatedTotalMeals);
    }

    /**
     * Metamorphic Relation 31: The sum of meals for all passengers should scale linearly with the
     * increase or decrease in the number of seats in each passenger class, assuming aircraft model
     * changes reflect changes in passenger class capacities.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        String updatedAircraftModel = aircraftmodel.equals("747200") ? "747300" : "747200";

        // aircraftModel changes should mean different numbers of available seats per class
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR originalMSR = MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "n",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        MSR updatedMSR = MOS.generateMSR(updatedAircraftModel, "n", newnumberofcrewmembers, "n",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        int originalTotalPassengerMeals = originalMSR.numberOfFirstClassMeals
                + originalMSR.numberOfBusinessClassMeals + originalMSR.numberOfEconomicClassMeals;

        int updatedTotalPassengerMeals = updatedMSR.numberOfFirstClassMeals
                + updatedMSR.numberOfBusinessClassMeals + updatedMSR.numberOfEconomicClassMeals;

        // The exact relation will depend on the specifics of the aircraft model capacities.
        // Generally, if updatedAircraftModel has more capacity in all classes, one would expect:
        assertTrue(updatedTotalPassengerMeals > originalTotalPassengerMeals);
        // And vice versa, if updatedAircraftModel has less capacity, one would expect:
        // assertTrue(updatedTotalPassengerMeals < originalTotalPassengerMeals);
    }

    /**
     * Metamorphic Relation 32: Incrementing both the number of crew members and pilots in equal
     * proportion while holding other factors constant should result in a combined meal count for
     * crew and pilots that increases in direct proportion to the increment factor.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(String aircraftmodel, String changeinthenumberofcrewmembers,
            int numberofcrewmembers, String changeinthenumberofpilots, int numberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        int incrementFactor = 2;

        // Assume incrementFactor is valid
        assumeTrue(incrementFactor > 0);

        int updatedNumberOfCrewMembers = numberofcrewmembers * incrementFactor;
        int updatedNumberOfPilots = numberofpilots * incrementFactor;

        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR originalMSR = MOS.generateMSR(aircraftmodel, "y", numberofcrewmembers, "y",
                numberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        MSR updatedMSR = MOS.generateMSR(aircraftmodel, "y", updatedNumberOfCrewMembers, "y",
                updatedNumberOfPilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        int originalCombinedMeals =
                originalMSR.numberOfMealsForCrewMembers + originalMSR.numberOfMealsForPilots;
        int updatedCombinedMeals =
                updatedMSR.numberOfMealsForCrewMembers + updatedMSR.numberOfMealsForPilots;

        assertEquals(originalCombinedMeals * incrementFactor, updatedCombinedMeals);
    }

    /**
     * Metamorphic Relation 33: A proportional change in the number of child passengers and
     * requested bundles of flowers should affect the respective outputs proportionally and
     * independently from each other.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(String aircraftmodel, String changeinthenumberofcrewmembers,
            int numberofcrewmembers, String changeinthenumberofpilots, int numberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        int changeFactor = 2;

        // Assume the changeFactor is a valid multiplier
        assumeTrue(changeFactor > 1);

        int updatedNumberOfChildPassengers = numberofchildpassengers * changeFactor;
        int updatedNumberOfBundlesofFlowers = numberofrequestedbundlesofflowers * changeFactor;

        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR originalMSR = MOS.generateMSR(aircraftmodel, "n", numberofcrewmembers, "n",
                numberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        MSR updatedMSR = MOS.generateMSR(aircraftmodel, "n", numberofcrewmembers, "n",
                numberofpilots, updatedNumberOfChildPassengers, updatedNumberOfBundlesofFlowers);

        assertTrue(originalMSR.numberOfChildMeals * changeFactor == updatedMSR.numberOfChildMeals);
        assertTrue(originalMSR.numberOfBundlesOfFlowers
                * changeFactor == updatedMSR.numberOfBundlesOfFlowers);
    }

    /**
     * Metamorphic Relation 34: Equivalently scaling the number of crew members and pilots by the
     * same factor while keeping the number of passengers constant should scale the number of meals
     * for crew and pilots by the same factor, without affecting the number of passenger meals.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(String aircraftmodel, String changeinthenumberofcrewmembers,
            int numberofcrewmembers, String changeinthenumberofpilots, int numberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        int scaleFactor = 2;

        int newNumberOfCrewMembers = numberofcrewmembers * scaleFactor;
        int newNumberOfPilots = numberofpilots * scaleFactor;

        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR originalMSR = MOS.generateMSR(aircraftmodel, "y", numberofcrewmembers, "y",
                numberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        MSR scaledMSR = MOS.generateMSR(aircraftmodel, "y", newNumberOfCrewMembers, "y",
                newNumberOfPilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        assertEquals(scaledMSR.numberOfMealsForCrewMembers,
                originalMSR.numberOfMealsForCrewMembers * scaleFactor);
        assertEquals(scaledMSR.numberOfMealsForPilots,
                originalMSR.numberOfMealsForPilots * scaleFactor);
        assertEquals(scaledMSR.numberOfFirstClassMeals, originalMSR.numberOfFirstClassMeals);
        assertEquals(scaledMSR.numberOfBusinessClassMeals, originalMSR.numberOfBusinessClassMeals);
        assertEquals(scaledMSR.numberOfEconomicClassMeals, originalMSR.numberOfEconomicClassMeals);
    }

    /**
     * Metamorphic Relation 35: If the number of crew members and pilots remain unchanged and only
     * the child passenger count doubles, then the number of child meals should exactly double.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {

        int doubledNumberOfChildPassengers = numberofchildpassengers * 2;

        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR originalMSR = MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "n",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        MSR doubledMSR =
                MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "n", newnumberofpilots,
                        doubledNumberOfChildPassengers, numberofrequestedbundlesofflowers);

        assertEquals(doubledMSR.numberOfChildMeals, originalMSR.numberOfChildMeals * 2);
    }

    /**
     * Metamorphic Relation 36: Swapping the increase and decrease of the same amount in the number
     * of crew members and pilots should not alter the sum of meals prepared for them.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(String aircraftmodel, String changeinthenumberofcrewmembers,
            int numberofcrewmembers, String changeinthenumberofpilots, int numberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed
        SecureRandom rand = new SecureRandom();
        int increaseAmountCrewMembers = rand.nextInt(10) + 1;
        int decreaseAmountPilots = rand.nextInt(10) + 1;

        int swappedNumberOfCrewMembers = numberofcrewmembers + increaseAmountCrewMembers;
        int swappedNumberOfPilots = numberofpilots - decreaseAmountPilots;

        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR originalMSR = MOS.generateMSR(aircraftmodel, "y", numberofcrewmembers, "y",
                numberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        MSR swappedMSR = MOS.generateMSR(aircraftmodel, "y", swappedNumberOfCrewMembers, "y",
                swappedNumberOfPilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        int originalTotal =
                originalMSR.numberOfMealsForCrewMembers + originalMSR.numberOfMealsForPilots;
        int swappedTotal =
                swappedMSR.numberOfMealsForCrewMembers + swappedMSR.numberOfMealsForPilots;

        assertEquals(originalTotal, swappedTotal);
    }

    /**
     * Metamorphic Relation 37: When the number of requested bundles of flowers is tripled while
     * maintaining the aircraft model and other passenger numbers, then the total number of bundles
     * of flowers listed in the MSR should triple, without affecting the count of any meals.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed

        int tripledNumberOfRequestedBundlesofFlowers = numberofrequestedbundlesofflowers * 3;

        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR originalMSR = MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "n",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        MSR tripledBundlesMSR =
                MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "n", newnumberofpilots,
                        numberofchildpassengers, tripledNumberOfRequestedBundlesofFlowers);

        assertEquals(tripledBundlesMSR.numberOfBundlesOfFlowers,
                originalMSR.numberOfBundlesOfFlowers * 3);
        assertEquals(tripledBundlesMSR.numberOfFirstClassMeals,
                originalMSR.numberOfFirstClassMeals);
        assertEquals(tripledBundlesMSR.numberOfBusinessClassMeals,
                originalMSR.numberOfBusinessClassMeals);
        assertEquals(tripledBundlesMSR.numberOfEconomicClassMeals,
                originalMSR.numberOfEconomicClassMeals);
        assertEquals(tripledBundlesMSR.numberOfMealsForCrewMembers,
                originalMSR.numberOfMealsForCrewMembers);
        assertEquals(tripledBundlesMSR.numberOfMealsForPilots, originalMSR.numberOfMealsForPilots);
        assertEquals(tripledBundlesMSR.numberOfChildMeals, originalMSR.numberOfChildMeals);
    }

    /**
     * Metamorphic Relation 38: If both the number of child passengers and the number of requested
     * bundles of flowers are set to zero, the MSR should calculate zero child meals and bundles of
     * flowers, without affecting the other meal counts.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed

        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR zeroChildrenAndFlowersMSR = MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers,
                "n", newnumberofpilots, 0, 0);

        assertEquals(zeroChildrenAndFlowersMSR.numberOfChildMeals, 0);
        assertEquals(zeroChildrenAndFlowersMSR.numberOfBundlesOfFlowers, 0);
        assertNotEquals(zeroChildrenAndFlowersMSR.numberOfFirstClassMeals, 0);
        assertNotEquals(zeroChildrenAndFlowersMSR.numberOfBusinessClassMeals, 0);
        assertNotEquals(zeroChildrenAndFlowersMSR.numberOfEconomicClassMeals, 0);
        assertNotEquals(zeroChildrenAndFlowersMSR.numberOfMealsForCrewMembers, 0);
        assertNotEquals(zeroChildrenAndFlowersMSR.numberOfMealsForPilots, 0);
    }

    /**
     * Metamorphic Relation 39: If the change in the number of pilots is to zero (meaning no
     * pilots), while keeping the aircraft model and number of crew members and child passengers
     * same, the resultant pilot meals should be zero and crew meals unchanged.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {

        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR zeroPilotsMSR = MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "y", 0,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        assertEquals(zeroPilotsMSR.numberOfMealsForPilots, 0);
        // Assuming there was at least one crew member
        assertNotEquals(zeroPilotsMSR.numberOfMealsForCrewMembers, 0);
    }

    /**
     * Metamorphic Relation 40: When an identical function call with identical parameters is made
     * twice (and the parameters imply there has been some initial state change), the same results
     * should be provided by both calls if the system state is not supposed to persist changes
     * between calls.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) { // Fixed

        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR firstCallMSR = MOS.generateMSR(aircraftmodel, "y", newnumberofcrewmembers, "y",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        MSR secondCallMSR = MOS.generateMSR(aircraftmodel, "y", newnumberofcrewmembers, "y",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        assertTrue(MSREquals(firstCallMSR, secondCallMSR));
    }

    /**
     * Metamorphic Relation 41: Doubling the number of requested bundles of flowers while keeping
     * all other parameters the same should result in doubling the output related to the number of
     * bundles of flowers without affecting meal counts.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test41(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {

        int doubledNumberOfRequestedBundlesofFlowers = numberofrequestedbundlesofflowers * 2;

        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR originalMSR = MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "n",
                newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        MSR doubledFlowersMSR =
                MOS.generateMSR(aircraftmodel, "n", newnumberofcrewmembers, "n", newnumberofpilots,
                        numberofchildpassengers, doubledNumberOfRequestedBundlesofFlowers);

        assertEquals(doubledFlowersMSR.numberOfBundlesOfFlowers,
                originalMSR.numberOfBundlesOfFlowers * 2);
        assertEquals(doubledFlowersMSR.numberOfFirstClassMeals,
                originalMSR.numberOfFirstClassMeals);
        assertEquals(doubledFlowersMSR.numberOfBusinessClassMeals,
                originalMSR.numberOfBusinessClassMeals);
        assertEquals(doubledFlowersMSR.numberOfEconomicClassMeals,
                originalMSR.numberOfEconomicClassMeals);
        assertEquals(doubledFlowersMSR.numberOfMealsForCrewMembers,
                originalMSR.numberOfMealsForCrewMembers);
        assertEquals(doubledFlowersMSR.numberOfMealsForPilots, originalMSR.numberOfMealsForPilots);
        assertEquals(doubledFlowersMSR.numberOfChildMeals, originalMSR.numberOfChildMeals);
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
