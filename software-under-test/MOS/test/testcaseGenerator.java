package test;

import java.security.SecureRandom;
import java.util.stream.Stream;

import org.junit.jupiter.params.provider.Arguments;

public class testcaseGenerator {
    public static Stream<Arguments> generate(int num) {
        Arguments[] tcs = new Arguments[num];
        SecureRandom rand = new SecureRandom();
        String[] cand1 = { "747200", "747300", "747400", "000200", "000300" };
        String[] cand2 = { "y", "n" };
        int[] range1 = { 1, 100 };
        int[] range2 = { 1, 1000 };

        for (int i = 0; i < num; i++) {
            String aircraftmodel;
            String changeinthenumberofcrewmembers;
            int newnumberofcrewmembers;
            String changeinthenumberofpilots;
            int newnumberofpilots;
            int numberofchildpassengers;
            int numberofrequestedbundlesofflowers;

            aircraftmodel = cand1[rand.nextInt(cand1.length)];
            changeinthenumberofcrewmembers = cand2[rand.nextInt(cand2.length)];
            newnumberofcrewmembers = rand.nextInt(range1[1] - range1[0] + 1) + range1[0];
            changeinthenumberofpilots = cand2[rand.nextInt(cand2.length)];
            newnumberofpilots = rand.nextInt(range1[1] - range1[0] + 1) + range1[0];
            numberofchildpassengers = rand.nextInt(range1[1] - range1[0] + 1) + range1[0];
            numberofrequestedbundlesofflowers = rand.nextInt(range2[1] - range2[0] + 1) + range2[0];

            tcs[i] = Arguments.of(aircraftmodel, changeinthenumberofcrewmembers, newnumberofcrewmembers,
                    changeinthenumberofpilots, newnumberofpilots, numberofchildpassengers,
                    numberofrequestedbundlesofflowers);
        }

        return Stream.of(tcs);
    }
}
