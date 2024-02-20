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
     * Metamorphic Relation 1: The MSR output should be the same regardless of the order of crew member and pilot changes.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test1(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        /* Get source output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Get follow-up output with reversed changes in crew members and pilots */
        MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofpilots, newnumberofpilots,
                changeinthenumberofcrewmembers, newnumberofcrewmembers, numberofchildpassengers,
                numberofrequestedbundlesofflowers);

        /* Verification */
        assertTrue(MSREquals(source_out, follow_out));
    }

    /**
     * Metamorphic Relation 2: If the number of child passengers doubles, the total number of child meals in the MSR output should also double.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test2(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
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
        assertEquals(source_out.numberOfChildMeals * 2, follow_out.numberOfChildMeals);
    }

    int getTotalMeals(MSR msr) {
        return msr.numberOfBusinessClassMeals + msr.numberOfEconomicClassMeals + msr.numberOfFirstClassMeals + msr.numberOfChildMeals
                + msr.numberOfMealsForCrewMembers + msr.numberOfMealsForPilots;
    }

    /**
     * Metamorphic Relation 3: For the same aircraft model and crew member/pilot changes, the total number of meals in the MSR output should always be greater than or equal to the total number of crew member and pilot meals.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test3(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        /* Get source output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        int totalMeals = getTotalMeals(source_out);

        /* Verification */
        assertTrue(totalMeals >= (source_out.numberOfMealsForCrewMembers + source_out.numberOfMealsForPilots));
    }

    /**
     * Metamorphic Relation 4: If the number of requested bundles of flowers increases, the difference in the total number of meals between source and follow-up outputs should be no less than the increase in the number of requested bundles of flowers.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test4(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        /* Get source output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Construct follow-up input */
        int follow_numberofrequestedbundlesofflowers = numberofrequestedbundlesofflowers + 1;

        /* Get follow-up output */
        MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, follow_numberofrequestedbundlesofflowers);

        int source_totalMeals = getTotalMeals(source_out);
        int follow_totalMeals = getTotalMeals(follow_out);

        /* Verification */
        assertTrue((source_totalMeals - follow_totalMeals) >= (follow_numberofrequestedbundlesofflowers - numberofrequestedbundlesofflowers));
    }

    /**
     * Metamorphic Relation 5: If the number of crew members increases, the total number of crew member meals in the MSR output should increase by the same amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test5(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Get source output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Construct follow-up input */
        int follow_newnumberofcrewmembers = newnumberofcrewmembers + 1;

        /* Get follow-up output */
        MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers,
                follow_newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots,
                numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Verification */
        assertTrue(follow_out.numberOfMealsForCrewMembers == source_out.numberOfMealsForCrewMembers + 2);
    }

    /**
     * Metamorphic Relation 6: If there is no change in the number of crew members and pilots, then for a different number of child passengers, the total number of child meals in the MSR output should increase linearly with the number of child passengers.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test6(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Get source output with no change in crew members and pilots */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, "n", 0, "n", 0, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Construct follow-up input with double the number of child passengers */
        int follow_numberofchildpassengers = numberofchildpassengers * 2;

        /* Get follow-up output */
        MSR follow_out = MOS.generateMSR(aircraftmodel, "n", 0, "n", 0, follow_numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Verification */
        assertTrue(follow_out.numberOfChildMeals == source_out.numberOfChildMeals * 2);
    }

    /**
     * Metamorphic Relation 7: Verifying the symmetry of the MSR output, i.e., for the same inputs, the MSR output should remain the same regardless of the order of specification.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test7(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        // /* Get output with regular input order */
        // MealOrderingSystem MOS1 = new MealOrderingSystem();
        // MSR output1 = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
        //         changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        // /* Get output with reversed input order */
        // MealOrderingSystem MOS2 = new MealOrderingSystem();
        // MSR output2 = MOS2.generateMSR(aircraftmodel, newnumberofcrewmembers, changeinthenumberofcrewmembers,
        //         newnumberofpilots, changeinthenumberofpilots, numberofrequestedbundlesofflowers, numberofchildpassengers);

        // /* Verification */
        // assertEquals(output1, output2);
    }

    /**
     * Metamorphic Relation 8: If there is a change in the number of crew members or pilots, and the number of child passengers is increased, the total number of meals in the output should correspondingly increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test8(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        /* Get source output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        if (changeinthenumberofcrewmembers == "y") {
            newnumberofcrewmembers++;
        }
        if (changeinthenumberofpilots == "y") {
            newnumberofpilots++;
        }
        int follow_numberofchildpassengers = numberofchildpassengers * 2;

        /* Get follow-up output */
        MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, follow_numberofchildpassengers, numberofrequestedbundlesofflowers);

        int source_totalMeals = getTotalMeals(source_out);
        int follow_totalMeals = getTotalMeals(follow_out);

        /* Verification */
        assertTrue(source_totalMeals < follow_totalMeals);
    }

    /**
     * Metamorphic Relation 9: The output MSR should remain the same regardless of the change in the order of model and crew/pilot attributes.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test9(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        // /* Get output with regular input order */
        // MealOrderingSystem MOS1 = new MealOrderingSystem();
        // MSR output1 = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
        //         changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        // /* Get output with reversed input order */
        // MealOrderingSystem MOS2 = new MealOrderingSystem();
        // MSR output2 = MOS2.generateMSR(changeinthenumberofcrewmembers, newnumberofcrewmembers,
        //         changeinthenumberofpilots, newnumberofpilots, aircraftmodel, numberofrequestedbundlesofflowers, 
        //         numberofchildpassengers);

        // /* Verification */
        // assertEquals(output1, output2);
    }

    /**
     * Metamorphic Relation 10: If the number of requested bundles of flowers is zero, then the number of bundles of flowers in the MSR output should also be zero.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test10(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        if (numberofrequestedbundlesofflowers == 0) {
            /* Get output */
            MealOrderingSystem MOS = new MealOrderingSystem();
            MSR output = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                    changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            /* Verification */
            assertEquals(0, output.numberOfBundlesOfFlowers);
        }
    }

    /**
     * Metamorphic Relation 11: If the number of crew members and pilots remains the same and the number of child passengers is increased, the total number of child meals in the MSR output should also increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test11(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        /* Get source output with no change in crew members and pilots */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, "n", 0, "n", 0, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Construct follow-up input with double the number of child passengers */
        int follow_numberofchildpassengers = numberofchildpassengers * 2;

        /* Get follow-up output */
        MSR follow_out = MOS.generateMSR(aircraftmodel, "n", 0, "n", 0, follow_numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Verification */
        assertTrue(follow_out.numberOfChildMeals > source_out.numberOfChildMeals);
    }

    /**
     * Metamorphic Relation 12: If the model changes, the MSR output for the new model should be equivalent to the original model after adjustment with the changes in crew members, pilots, number of child passengers and requested bundles of flowers.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test12(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        if (!aircraftmodel.equals("newPlaneModel")) {

            /* Follow-up input with "newPlaneModel" */
            String follow_aircraftmodel = "newPlaneModel";

            /* Get source output */
            MealOrderingSystem MOS = new MealOrderingSystem();
            MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                    changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            /* Get follow-up output */
            MSR follow_out = MOS.generateMSR(follow_aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                    changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            /* Verification */
            assertEquals(source_out, follow_out);
        }
    }

    /**
     * Metamorphic Relation 13: If the number of requested bundles of flowers is increased and the number of child passengers is doubled, then the total number of meals in the MSR output should correspondingly increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test13(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        /* Get source output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);
        
        /* Construct follow-up input */
        int follow_numberofrequestedbundlesofflowers = numberofrequestedbundlesofflowers + 1;
        int follow_numberofchildpassengers = numberofchildpassengers * 2;

        /* Get follow-up output */
        MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, follow_numberofchildpassengers, follow_numberofrequestedbundlesofflowers);
        
        int source_totalMeals = getTotalMeals(source_out);
        int follow_totalMeals = getTotalMeals(follow_out);

        /* Verification */
        assertTrue(follow_totalMeals > source_totalMeals);
    }

    /**
     * Metamorphic Relation 14: The MSR output for the same model with no changes in crew members, pilots, number of child passengers, and requested bundles of flowers should remain the same across multiple invocations.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test14(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Get output with regular input */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR output1 = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);
        
        /* Get output with the same regular input */
        MSR output2 = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);
        
        /* Verification */
        assertTrue(MSREquals(output1, output2));
    }

    /**
     * Metamorphic Relation 15: If the number of crew members and pilots remains the same, increasing the number of child passengers should proportionally increase the value of crewMeals and pilotMeals in the MSR output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test15(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        /* Get source output with no change in crew members and pilots */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, "n", 0, "n", 0, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Construct follow-up input with double the number of child passengers */
        int follow_numberofchildpassengers = numberofchildpassengers * 2;

        /* Get follow-up output */
        MSR follow_out = MOS.generateMSR(aircraftmodel, "n", 0, "n", 0, follow_numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Verification */
        assertTrue(follow_out.numberOfMealsForCrewMembers == source_out.numberOfMealsForCrewMembers * 2);
        assertTrue(follow_out.numberOfMealsForPilots == source_out.numberOfMealsForPilots * 2);
    }

    /**
     * Metamorphic Relation 16: If the number of requested bundles of flowers is zero, the total number of meals in the MSR output should be equal to the sum of crewMeals, pilotMeals, childMeals.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test16(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        if (numberofrequestedbundlesofflowers == 0) {
            /* Get source output */
            MealOrderingSystem MOS = new MealOrderingSystem();
            MSR output = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                    changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            /* Verification */
            int totalMeals = getTotalMeals(output);
            assertEquals(totalMeals, output.numberOfMealsForCrewMembers + output.numberOfMealsForPilots + output.numberOfChildMeals);
        }
    }

    /**
     * Metamorphic Relation 17: If the number of crew members and pilots are both unchanged, doubling the number of requested bundles of flowers should double the total number of meals in the MSR output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test17(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        /* Get source output with no change in crew members and pilots */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, "n", 0, "n", 0, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Construct follow-up input with double the number of requested bundles of flowers */
        int follow_numberofrequestedbundlesofflowers = numberofrequestedbundlesofflowers * 2;

        /* Get follow-up output */
        MSR follow_out = MOS.generateMSR(aircraftmodel, "n", 0, "n", 0, numberofchildpassengers, follow_numberofrequestedbundlesofflowers);

        int source_totalMeals = getTotalMeals(source_out);
        int follow_totalMeals = getTotalMeals(follow_out);

        /* Verification */
        assertTrue(follow_totalMeals == source_totalMeals * 2);
    }

    /**
     * Metamorphic Relation 18: If the number of child passengers and the number of requested bundles of flowers remain the same, the total number of meals should remain the same regardless of changes in crew members and pilots.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test18(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        /* Get output with regular input order */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR output1 = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Get output with reversed input order */
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR output2 = MOS2.generateMSR(aircraftmodel, changeinthenumberofpilots, newnumberofpilots,
                changeinthenumberofcrewmembers, newnumberofcrewmembers, numberofchildpassengers, numberofrequestedbundlesofflowers);

        int totalMeals1 = getTotalMeals(output1);
        int totalMeals2 = getTotalMeals(output2);

        /* Verification */
        assertEquals(totalMeals1, totalMeals2);
    }

    /**
     * Metamorphic Relation 19: If the number of requested bundles of flowers is non-zero, then the total number of meals should be equal to the sum of crew meals, pilot meals, child meals, and the number of requested bundles of flowers.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test19(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        if (numberofrequestedbundlesofflowers > 0) {
            /* Get source output */
            MealOrderingSystem MOS = new MealOrderingSystem();
            MSR output = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                    changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            int totalMeals = getTotalMeals(output);

            /* Verification */
            assertEquals(totalMeals, output.numberOfMealsForCrewMembers + output.numberOfMealsForPilots + output.numberOfChildMeals + numberofrequestedbundlesofflowers);
        }
    }

    /**
     * Metamorphic Relation 20: The MSR output should be the same regardless of the changes in the number of child passengers and the number of requested bundles of flowers, if the number of crew and pilots remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test20(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Get output with regular input */
        MealOrderingSystem MOS1 = new MealOrderingSystem();
        MSR output1 = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);
    
        /* Get output with regular input order */
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR output2 = MOS2.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);
        
        /* Verification */
        assertTrue(MSREquals(output1, output2));
    }

    /**
     * Metamorphic Relation 21: If the number of child passengers and the number of requested bundles of flowers are both zero, then the total number of meals should be equal to the sum of crew meals and pilot meals.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test21(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        if (numberofchildpassengers == 0 && numberofrequestedbundlesofflowers == 0) {
            /* Get source output */
            MealOrderingSystem MOS = new MealOrderingSystem();
            MSR output = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                    changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            int totalMeals = getTotalMeals(output);

            /* Verification */
            assertEquals(totalMeals, output.numberOfMealsForCrewMembers + output.numberOfMealsForPilots);
        }
    }

    /**
     * Metamorphic Relation 22: The output MSR should remain the same regardless of the changes in the number of child passengers and the number of requested bundles of flowers, if the aircraft model, crew members, and pilots remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test22(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Get output with regular input */
        MealOrderingSystem MOS1 = new MealOrderingSystem();
        MSR output1 = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Get output with regular input order */
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR output2 = MOS2.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Verification */
        assertTrue(MSREquals(output1, output2));
    }

    /**
     * Metamorphic Relation 23: If there is an increase in the number of crew members and the number of child passengers remains the same, the number of crew meals in the MSR output should increase by the same amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test23(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        if (changeinthenumberofcrewmembers.equals("y")) {
            /* Get source output */
            MealOrderingSystem MOS = new MealOrderingSystem();
            MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                    changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            /* Construct follow-up input */
            int follow_newnumberofcrewmembers = newnumberofcrewmembers + 1;

            /* Get follow-up output */
            MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, follow_newnumberofcrewmembers,
                    changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            /* Verification */
            assertTrue(follow_out.numberOfMealsForCrewMembers == source_out.numberOfMealsForCrewMembers + 2);
        }
    }

    /**
     * Metamorphic Relation 24: If there is no change in the number of crew members and pilots and the number of child passengers is increased, the total number of meals in the MSR output should proportionally increase.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test24(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Get source output with no change in crew members and pilots */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, "n", 0, "n", 0, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Construct follow-up input with double the number of child passengers */
        int follow_numberofchildpassengers = numberofchildpassengers * 2;

        /* Get follow-up output */
        MSR follow_out = MOS.generateMSR(aircraftmodel, "n", 0, "n", 0, follow_numberofchildpassengers, numberofrequestedbundlesofflowers);

        int source_totalMeals = getTotalMeals(source_out);
        int follow_totalMeals = getTotalMeals(follow_out);

        /* Verification */
        assertTrue(follow_totalMeals == source_totalMeals * 2);
    }

    /**
     * Metamorphic Relation 25: If there is a change in the number of pilots and the number of requested bundles of flowers remains the same, then the number of pilot meals in the MSR output should increase by the same amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test25(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        if (changeinthenumberofpilots.equals("y")) {
            /* Get source output */
            MealOrderingSystem MOS = new MealOrderingSystem();
            MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                    changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            /* Construct follow-up input */
            int follow_newnumberofpilots = newnumberofpilots + 1;

            /* Get follow-up output */
            MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                    changeinthenumberofpilots, follow_newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            /* Verification */
            assertTrue(follow_out.numberOfMealsForPilots == source_out.numberOfMealsForPilots + 2);
        }
    }

    /**
     * Metamorphic Relation 26: If the number of child passengers and the number of requested bundles of flowers remain the same, then the total number of meals in the MSR output should remain the same regardless of changes in crew members and pilots.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test26(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        /* Get output with regular input */
        MealOrderingSystem MOS1 = new MealOrderingSystem();
        MSR output1 = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Get output with reversed input order */
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR output2 = MOS2.generateMSR(aircraftmodel, changeinthenumberofpilots, newnumberofpilots,
                changeinthenumberofcrewmembers, newnumberofcrewmembers, numberofchildpassengers, numberofrequestedbundlesofflowers);

        int totalMeals1 = getTotalMeals(output1);
        int totalMeals2 = getTotalMeals(output2);

        /* Verification */
        assertEquals(totalMeals1, totalMeals2);
    }

    /**
     * Metamorphic Relation 27: If the number of child passengers is doubled, the total number of child meals in the MSR output should also double.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test27(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Get source output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Construct follow-up input */
        int follow_numberofchildpassengers = numberofchildpassengers * 2;
        
        /* Get follow-up output */
        MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, follow_numberofchildpassengers, numberofrequestedbundlesofflowers);
        
        /* Verification */
        assertTrue(follow_out.numberOfChildMeals == source_out.numberOfChildMeals * 2);
    }

    /**
     * Metamorphic Relation 28: The number of requested bundles of flowers should not affect the number of crew, pilot, and child meals in the MSR output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test28(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        /* Get output with regular input */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR output = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);
        
        int originalTotalMeals = output.numberOfMealsForCrewMembers + output.numberOfMealsForPilots + output.numberOfChildMeals;

        /* Change the number of requested bundles of flowers */
        int newNumberofrequestedbundlesofflowers = 5;
        MSR changedOutput = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, newNumberofrequestedbundlesofflowers);

        /* Verification */
        assertEquals(originalTotalMeals, changedOutput.numberOfMealsForCrewMembers + changedOutput.numberOfMealsForPilots + changedOutput.numberOfChildMeals);
    }

    /**
     * Metamorphic Relation 29: If the number of crew members and pilots remain the same, and the number of child passengers is doubled, the total number of meals in the MSR output should increase proportionally.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test29(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Get source output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, "n", 0, "n", 0, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Construct follow-up input with double the number of child passengers */
        int follow_numberofchildpassengers = numberofchildpassengers * 2;

        /* Get follow-up output */
        MSR follow_out = MOS.generateMSR(aircraftmodel, "n", 0, "n", 0, follow_numberofchildpassengers, numberofrequestedbundlesofflowers);

        int source_totalMeals = getTotalMeals(source_out);
        int follow_totalMeals = getTotalMeals(follow_out);

        /* Verification */
        assertTrue(follow_totalMeals == source_totalMeals * 2);
    }

    /**
     * Metamorphic Relation 30: If the number of child passengers is zero and the number of requested bundles of flowers is non-zero, then the total number of meals in the MSR output should be equal to the sum of crew meals, pilot meals, and the number of requested bundles of flowers.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test30(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        if (numberofchildpassengers == 0 && numberofrequestedbundlesofflowers > 0) {
            /* Get source output */
            MealOrderingSystem MOS = new MealOrderingSystem();
            MSR output = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                    changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            int totalMeals = getTotalMeals(output);

            /* Verification */
            assertEquals(totalMeals, output.numberOfMealsForCrewMembers + output.numberOfMealsForPilots + numberofrequestedbundlesofflowers);
        }
    }

    /**
     * Metamorphic Relation 31: The MSR output should remain unchanged regardless of the change in the aircraft model, if the number of crew members, pilots, child passengers, and requested bundles of flowers remain the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test31(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        /* Get output with regular input */
        MealOrderingSystem MOS1 = new MealOrderingSystem();
        MSR output1 = MOS1.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Get output with different aircraft model but the same regular input */
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR output2 = MOS2.generateMSR("DifferentAircraftModel", changeinthenumberofcrewmembers, newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Verification */
        assertTrue(MSREquals(output1, output2));
    }

    /**
     * Metamorphic Relation 32: If the number of crew members increases and the number of pilots remains unchanged, the total number of crew member meals in the MSR output should increase by the same amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test32(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        if (changeinthenumberofcrewmembers.equals("y")) {
            /* Get source output */
            MealOrderingSystem MOS = new MealOrderingSystem();
            MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            /* Get follow-up output */
            MSR follow_up = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers + 1,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            /* Verification */
            assertTrue(follow_up.numberOfMealsForCrewMembers == source_out.numberOfMealsForCrewMembers + 2);
        }
    }

    /**
     * Metamorphic Relation 33: If the aircraft model remains the same, and there is an increase in the number of child passengers and the number of requested bundles of flowers is doubled, the total number of meals in the MSR output should increase proportionally.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test33(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {
        /* Get source output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Construct follow-up input */
        int follow_numberofchildpassengers = numberofchildpassengers * 2;
        int follow_numberofrequestedbundlesofflowers = numberofrequestedbundlesofflowers * 2;

        /* Get follow-up output */
        MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots, follow_numberofchildpassengers, follow_numberofrequestedbundlesofflowers);

        int source_totalMeals = getTotalMeals(source_out);
        int follow_totalMeals = getTotalMeals(follow_out);

        /* Verification */
        assertTrue(follow_totalMeals == source_totalMeals * 2);
    }

    /**
     * Metamorphic Relation 34: If the number of child passengers doubles and the number of requested bundles of flowers is tripled, the total number of meals in the MSR output should increase proportionally.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test34(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        /* Get source output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Construct follow-up input */
        int follow_numberofchildpassengers = numberofchildpassengers * 2;
        int follow_numberofrequestedbundlesofflowers = numberofrequestedbundlesofflowers * 3;

        /* Get follow-up output */
        MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers, changeinthenumberofpilots, newnumberofpilots, follow_numberofchildpassengers, follow_numberofrequestedbundlesofflowers);

        int source_totalMeals = getTotalMeals(source_out);
        int follow_totalMeals = getTotalMeals(follow_out);

        /* Verification */
        assertTrue(follow_totalMeals == source_totalMeals * 3);
    }

    /**
     * Metamorphic Relation 35: If the number of crew members and number of pilots are both unchanged, the ratio of crew meals to pilot meals in the MSR output for the original input and the follow-up input should be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test35(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        if (changeinthenumberofcrewmembers.equals("n") && changeinthenumberofpilots.equals("n")) {
            /* Get source output */
            MealOrderingSystem MOS = new MealOrderingSystem();
            MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                    changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            int crewMealsRatio = source_out.numberOfMealsForCrewMembers / source_out.numberOfMealsForPilots;

            /* Get follow-up output */
            MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                    changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            int followCrewMealsRatio = follow_out.numberOfMealsForCrewMembers / follow_out.numberOfMealsForPilots;

            /* Verification */
            assertEquals(crewMealsRatio, followCrewMealsRatio);
        }
    }

    /**
     * Metamorphic Relation 36: If the number of crew members is decreased, and the number of child passengers and requested bundles of flowers remain unchanged, the total number of crew meals in the MSR output should decrease by the same amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test36(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        if (changeinthenumberofcrewmembers.equals("y") && newnumberofcrewmembers < 5) { // Assuming a decrease of 1 crew member
            /* Get source output */
            MealOrderingSystem MOS = new MealOrderingSystem();
            MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                    changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            /* Construct follow-up input */
            int follow_newnumberofcrewmembers = newnumberofcrewmembers - 1;

            /* Get follow-up output */
            MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, follow_newnumberofcrewmembers,
                    changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            /* Verification */
            assertTrue(follow_out.numberOfMealsForCrewMembers == source_out.numberOfMealsForCrewMembers - 2); // Assuming each crew meal per crew member decreases by 2
        }
    }

    /**
     * Metamorphic Relation 37: If the number of crew members is increased and the number of pilots remains unchanged, the total number of crew meals in the MSR output should increase proportionally.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test37(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        if (changeinthenumberofcrewmembers.equals("y")) {
            /* Get source output */
            MealOrderingSystem MOS = new MealOrderingSystem();
            MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                    changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            /* Construct follow-up input */
            int increasedCrewMembers = newnumberofcrewmembers + 1;

            /* Get follow-up output */
            MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, increasedCrewMembers,
                    changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

            /* Verification */
            assertTrue(follow_out.numberOfMealsForCrewMembers == source_out.numberOfMealsForCrewMembers + 2); // Assuming each crew meal per crew member increases by 2
        }
    }

    /**
     * Metamorphic Relation 38: If the number of child passengers and the number of requested bundles of flowers remain unchanged, the total number of meals in the MSR output should remain unchanged regardless of the changes in the number of crew members and pilots.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test38(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        // Get output with regular input
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR output1 = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        // Get output with reversed input order
        MealOrderingSystem MOS2 = new MealOrderingSystem();
        MSR output2 = MOS2.generateMSR(aircraftmodel, changeinthenumberofpilots, newnumberofpilots,
                changeinthenumberofcrewmembers, newnumberofcrewmembers, numberofchildpassengers, numberofrequestedbundlesofflowers);

        int totalMeals1 = getTotalMeals(output1);
        int totalMeals2 = getTotalMeals(output2);

        // Verification
        assertEquals(totalMeals1, totalMeals2);
    }

    /**
     * Metamorphic Relation 39: If the number of crew members and pilots are both unchanged, and the number of child passengers is increased, the total number of child meals in the MSR output should increase proportionally.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test39(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        /* Get source output with no change in crew members and pilots */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, "n", 0, "n", 0, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Construct follow-up input with double the number of child passengers */
        int follow_numberofchildpassengers = numberofchildpassengers * 2;

        /* Get follow-up output */
        MSR follow_out = MOS.generateMSR(aircraftmodel, "n", 0, "n", 0, follow_numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Verification */
        assertTrue(follow_out.numberOfChildMeals == source_out.numberOfChildMeals * 2);
    }

    /**
     * Metamorphic Relation 40: If the number of requested bundles of flowers is increased, the total number of meals in the MSR output should also increase proportionally.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider")
    public void test40(String aircraftmodel, String changeinthenumberofcrewmembers,
            int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
            int numberofchildpassengers, int numberofrequestedbundlesofflowers) {   // Fixed
        /* Get source output */
        MealOrderingSystem MOS = new MealOrderingSystem();
        MSR source_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
            changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, numberofrequestedbundlesofflowers);

        /* Construct follow-up input */
        int follow_numberofrequestedbundlesofflowers = numberofrequestedbundlesofflowers * 2;

        /* Get follow-up output */
        MSR follow_out = MOS.generateMSR(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
            changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers, follow_numberofrequestedbundlesofflowers);

        int source_totalMeals = getTotalMeals(source_out);
        int follow_totalMeals = getTotalMeals(follow_out);

        /* Verification */
        assertTrue(follow_totalMeals == source_totalMeals * 2);
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
