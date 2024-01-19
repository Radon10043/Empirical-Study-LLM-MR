import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.IOException;
import java.util.stream.Stream;

import org.joda.time.Chronology;
import org.joda.time.DateTime;
import org.joda.time.DateTimeConstants;
import org.joda.time.DateTimeZone;
import org.joda.time.Days;
import org.joda.time.Duration;
import org.joda.time.Instant;
import org.joda.time.Period;
import org.joda.time.Weeks;
import org.joda.time.format.DateTimeFormatter;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

public class JodaTestGPT3D5 {
    /**
     * Metamorphic Relation 3: Subtracting the number of hours from the input time
     * and then adding the same number of hours should result in the same output.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderDI")
    public void test3(DateTime time, int hours) {
        /* Get source output */
        DateTime intermediate = time.minusHours(hours);
        DateTime source_out = intermediate.plusHours(hours);

        /* Get follow-up output */
        DateTime follow_out = time;

        /* Verification */
        assertTrue(source_out.equals(follow_out));
    }

    /**
     * Metamorphic Relation 4: Adding the number of weeks to the input time and then
     * adding the same number of days should result in the same output as adding the
     * total days directly.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderDII")
    public void test4(DateTime time, int weeks, int days) {
        /* Get source output for adding weeks first */
        DateTime source_out_weeks = time.plusWeeks(weeks);

        /* Get follow-up output for adding days directly */
        DateTime follow_out = time.plusDays(weeks * 7 + days);

        /* Verification */
        assertTrue(source_out_weeks.equals(follow_out));
    }

    /**
     * Metamorphic Relation 5: Adjusting the time by adding a duration in
     * milliseconds to the input time should result in the same output as adding the
     * equivalent seconds duration.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderDI")
    public void test5(DateTime time, long milliseconds) {
        /* Get source output for adding milliseconds */
        DateTime source_out_millis = time.plus(Duration.millis(milliseconds));

        /* Construct follow-up input for equivalent seconds */
        int seconds = (int) (milliseconds / 1000);

        /* Get follow-up output for adding seconds */
        DateTime follow_out_seconds = time.plusSeconds(seconds);

        /* Verification */
        assertTrue(source_out_millis.equals(follow_out_seconds));
    }

    /**
     * Metamorphic Relation 6: Adjusting the input time with a specific time zone
     * and then adjusting the output time to another time zone should preserve the
     * same time.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderDZZ")
    public void test6(DateTime time, DateTimeZone zone1, DateTimeZone zone2) {
        /* Adjust the time to zone1 */
        DateTime time_zone1 = time.withZone(zone1);

        /* Adjust the time from zone1 to zone2 */
        DateTime time_zone2 = time_zone1.withZone(zone2);

        /* Verification */
        assertTrue(time.equals(time_zone2));
    }

    /**
     * Metamorphic Relation 7: Constructing a time from a specific timestamp in
     * milliseconds, then obtaining the timestamp from the constructed time, and
     * finally constructing another time using the obtained timestamp should result
     * in the same time as the original time.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderL")
    public void test7(long timestamp) {
        /* Construct time from timestamp */
        DateTime originalTime = new DateTime(timestamp);

        /* Obtain timestamp from original time */
        long obtainedTimestamp = originalTime.getMillis();

        /* Construct time from obtained timestamp */
        DateTime obtainedTime = new DateTime(obtainedTimestamp);

        /* Verification */
        assertTrue(originalTime.equals(obtainedTime));
    }

    /**
     * Metamorphic Relation 8: Constructing a time using a specific date and time
     * components, then obtaining the individual date and time components from the
     * constructed time, and finally constructing another time using the obtained
     * components should result in the same time as the original time.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderIIIIIII")
    public void test8(int year, int month, int day, int hour, int minute, int second, int millis) {
        /* Construct time from date and time components */
        DateTime originalTime = new DateTime(year, month, day, hour, minute, second, millis);

        /* Obtain individual date and time components from original time */
        int obtainedYear = originalTime.getYear();
        int obtainedMonth = originalTime.getMonthOfYear();
        int obtainedDay = originalTime.getDayOfMonth();
        int obtainedHour = originalTime.getHourOfDay();
        int obtainedMinute = originalTime.getMinuteOfHour();
        int obtainedSecond = originalTime.getSecondOfMinute();
        int obtainedMillis = originalTime.getMillisOfSecond();

        /* Construct time using obtained components */
        DateTime obtainedTime = new DateTime(obtainedYear, obtainedMonth, obtainedDay, obtainedHour, obtainedMinute,
                obtainedSecond, obtainedMillis);

        /* Verification */
        assertTrue(originalTime.equals(obtainedTime));
    }

    /**
     * Metamorphic Relation 9: Constructing a time using a specific instant and then
     * adjusting the time zone to another time zone should preserve the same
     * instant.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderInsZZ")
    public void test9(Instant instant, DateTimeZone zone1, DateTimeZone zone2) {
        /* Construct time from specific instant */
        DateTime originalTime = new DateTime(instant);

        /* Adjust the time zone to zone1 */
        DateTime time_zone1 = originalTime.withZone(zone1);

        /* Adjust the time zone from zone1 to zone2 */
        DateTime time_zone2 = time_zone1.withZone(zone2);

        /* Verification */
        assertTrue(originalTime.equals(time_zone2));
    }

    /**
     * Metamorphic Relation 10: Constructing a time using a specific year, day of
     * year, and time components, then obtaining the year and day of year from the
     * constructed time, and finally constructing another time using the obtained
     * year, day of year, and time components should result in the same time as the
     * original time.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderIIIIIII")
    public void test10(int year, int dayOfYear, int hour, int minute, int second, int millis) {
        /* Construct time from year, day of year, and time components */
        DateTime originalTime = new DateTime().withYear(year).withDayOfYear(dayOfYear).withTime(hour, minute, second,
                millis);

        /* Obtain year and day of year from original time */
        int obtainedYear = originalTime.getYear();
        int obtainedDayOfYear = originalTime.getDayOfYear();

        /* Construct time using obtained year, day of year, and time components */
        DateTime obtainedTime = new DateTime().withYear(obtainedYear).withDayOfYear(obtainedDayOfYear).withTime(hour,
                minute, second, millis);

        /* Verification */
        assertTrue(originalTime.equals(obtainedTime));
    }

    /**
     * Metamorphic Relation 11: Constructing a time using a specific week year, week
     * of week year, and day of week components, then obtaining the week year, week
     * of week year, and day of week from the constructed time, and finally
     * constructing another time using the obtained components should result in the
     * same time as the original time.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderIIIIIII")
    public void test11(int weekYear, int weekOfWeekYear, int dayOfWeek, int hour, int minute, int second, int millis) {
        /*
         * Construct time from week year, week of week year, and day of week components
         */
        DateTime originalTime = new DateTime().withWeekyear(weekYear).withWeekOfWeekyear(weekOfWeekYear)
                .withDayOfWeek(dayOfWeek).withTime(hour, minute, second, millis);

        /* Obtain week year, week of week year, and day of week from original time */
        int obtainedWeekYear = originalTime.getWeekyear();
        int obtainedWeekOfWeek = originalTime.getWeekOfWeekyear();
        int obtainedDayOfWeek = originalTime.getDayOfWeek();

        /*
         * Construct time using obtained week year, week of week year, day of week, and
         * time components
         */
        DateTime obtainedTime = new DateTime().withWeekyear(obtainedWeekYear).withWeekOfWeekyear(obtainedWeekOfWeek)
                .withDayOfWeek(obtainedDayOfWeek).withTime(hour, minute, second, millis);

        /* Verification */
        assertTrue(originalTime.equals(obtainedTime));
    }

    /**
     * Metamorphic Relation 12: Adjusting the time to the start of the day, then
     * adjusting the time to the end of the day should result in the same date but
     * different times.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderDI")
    public void test12(DateTime time) {
        /* Adjust time to start of the day */
        DateTime startOfDayTime = time.withTimeAtStartOfDay();

        /* Adjust time to end of the day */
        DateTime endOfDayTime = time.millisOfDay().withMaximumValue();

        /* Verification */
        assertTrue(startOfDayTime.toLocalDate().equals(endOfDayTime.toLocalDate()));
        assertFalse(startOfDayTime.equals(endOfDayTime));
    }

    /**
     * Metamorphic Relation 13: Adjusting the time to the beginning of the hour,
     * then adding 1 hour to the time should result in the same hour but different
     * minutes.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderDI")
    public void test13(DateTime time) {
        /* Adjust time to the beginning of the hour */
        DateTime startOfHourTime = time.withTime(time.getHourOfDay(), 0, 0, 0);

        /* Add 1 hour to the time */
        DateTime nextHourTime = time.plusHours(1);

        /* Verification */
        assertEquals(startOfHourTime.getHourOfDay(), nextHourTime.getHourOfDay());
        assertNotEquals(startOfHourTime.getMinuteOfHour(), nextHourTime.getMinuteOfHour());
    }

    /**
     * Metamorphic Relation 14: Constructing a time with milliseconds precision and
     * another time with seconds precision should result in the same time when
     * compared at milliseconds precision.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderIIIIIII")
    public void test14(long timeInMilliseconds, long timeInSeconds) {
        /* Construct time with milliseconds precision */
        DateTime millisPrecisionTime = new DateTime(timeInMilliseconds);

        /* Construct time with seconds precision */
        DateTime secondsPrecisionTime = new DateTime(timeInSeconds * 1000L);

        /* Verification */
        assertEquals(millisPrecisionTime.getMillis(), secondsPrecisionTime.getMillis());
        assertEquals(millisPrecisionTime, secondsPrecisionTime);
    }

    /**
     * Metamorphic Relation 15: Constructing a time with a specific year, month, and
     * day, then adding a duration of 1 day should result in the same day of the
     * month but a different month and year.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderIIIIIII")
    public void test15(int year, int month, int day) {
        /* Construct time from year, month, and day */
        DateTime originalTime = new DateTime(year, month, day, 0, 0, 0, 0);

        /* Add 1 day to the time */
        DateTime nextDayTime = originalTime.plusDays(1);

        /* Verification */
        assertEquals(originalTime.getDayOfMonth(), nextDayTime.getDayOfMonth());
        assertNotEquals(originalTime.getMonthOfYear(), nextDayTime.getMonthOfYear());
        assertNotEquals(originalTime.getYear(), nextDayTime.getYear());
    }

    /**
     * Metamorphic Relation 16: Constructing a time with a specific year and week,
     * then adding a duration of 1 week should result in the same week but a
     * different year and day of week.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderIIIIIII")
    public void test16(int year, int week, int dayOfWeek) {
        /* Construct time from year, week, and day of week */
        DateTime originalTime = new DateTime().withWeekyear(year).withWeekOfWeekyear(week).withDayOfWeek(dayOfWeek);

        /* Add 1 week to the time */
        DateTime nextWeekTime = originalTime.plusWeeks(1);

        /* Verification */
        assertEquals(originalTime.getWeekOfWeekyear(), nextWeekTime.getWeekOfWeekyear());
        assertNotEquals(originalTime.getYear(), nextWeekTime.getYear());
        assertNotEquals(originalTime.getDayOfWeek(), nextWeekTime.getDayOfWeek());
    }

    /**
     * Metamorphic Relation 17: Adjusting the time to the end of the month, then
     * setting the time to the beginning of the month using the same year and month
     * should result in the same month and year but different day.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderDI")
    public void test17(DateTime time) {
        /* Adjust time to the end of the month */
        DateTime endOfMonthTime = time.dayOfMonth().withMaximumValue();

        /* Set the time to the beginning of the month */
        DateTime startOfMonthTime = endOfMonthTime.dayOfMonth().withMinimumValue();

        /* Verification */
        assertEquals(startOfMonthTime.getYear(), endOfMonthTime.getYear());
        assertEquals(startOfMonthTime.getMonthOfYear(), endOfMonthTime.getMonthOfYear());
        assertNotEquals(startOfMonthTime.getDayOfMonth(), endOfMonthTime.getDayOfMonth());
    }

    /**
     * Metamorphic Relation 18: Constructing times with different time zones and
     * adjusting them to UTC time zone should result in the same time.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderZZ")
    public void test18(DateTimeZone zone1, DateTimeZone zone2) {
        /* Construct time in different time zones */
        DateTime time_zone1 = new DateTime(zone1);
        DateTime time_zone2 = new DateTime(zone2);

        /* Adjust times to UTC time zone */
        DateTime utc_time_zone1 = time_zone1.withZone(DateTimeZone.UTC);
        DateTime utc_time_zone2 = time_zone2.withZone(DateTimeZone.UTC);

        /* Verification */
        assertTrue(utc_time_zone1.equals(utc_time_zone2));
    }

    /**
     * Metamorphic Relation 19: Calculating the difference between two dates and
     * adding the same duration to both dates should result in the same difference
     * between the modified dates.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderDDP")
    public void test19(DateTime date1, DateTime date2, Period period) {
        /* Get the difference between the original dates */
        Period originalDifference = new Period(date1, date2);

        /* Add the same duration to both dates */
        DateTime modifiedDate1 = date1.plus(period);
        DateTime modifiedDate2 = date2.plus(period);

        /* Get the difference between the modified dates */
        Period modifiedDifference = new Period(modifiedDate1, modifiedDate2);

        /* Verification */
        assertEquals(originalDifference, modifiedDifference);
    }

    /**
     * Metamorphic Relation 20: Constructing two times with the same date and time
     * components, but with different chronologies, and adjusting them to a common
     * chronology should result in the same time.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderIIIIIIICC")
    public void test20(int year, int month, int day, int hour, int minute, int second, int millis, Chronology chrono1,
            Chronology chrono2) {
        /* Construct times with different chronologies */
        DateTime dateTime1 = new DateTime(year, month, day, hour, minute, second, millis, chrono1);
        DateTime dateTime2 = new DateTime(year, month, day, hour, minute, second, millis, chrono2);

        /* Adjust both times to a common chronology */
        DateTime adjustedDateTime1 = dateTime1.withChronology(chrono1.withUTC());
        DateTime adjustedDateTime2 = dateTime2.withChronology(chrono1.withUTC());

        /* Verification */
        assertTrue(adjustedDateTime1.equals(adjustedDateTime2));
    }

    /**
     * Metamorphic Relation 21: Constructing two times using different time zones
     * and then adjusting them to a common time zone should result in the same time.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderZZ")
    public void test21(DateTimeZone zone1, DateTimeZone zone2) {
        /* Construct times in different time zones */
        DateTime timeInZone1 = new DateTime(zone1);
        DateTime timeInZone2 = new DateTime(zone2);

        /* Adjust both times to a common time zone */
        DateTime adjustedTimeInZone1 = timeInZone1.withZone(DateTimeZone.UTC);
        DateTime adjustedTimeInZone2 = timeInZone2.withZone(DateTimeZone.UTC);

        /* Verification */
        assertTrue(adjustedTimeInZone1.equals(adjustedTimeInZone2));
    }

    /**
     * Metamorphic Relation 22: Constructing a time based on a specific day and then
     * adding a duration of 1 week should result in a time representing the same day
     * of the week in the following week.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderIIIIIII")
    public void test22(int year, int month, int day) {
        /* Construct time from year, month, and day */
        DateTime originalTime = new DateTime(year, month, day, 0, 0, 0, 0);

        /* Add 1 week to the time */
        DateTime nextWeekTime = originalTime.plusWeeks(1);

        /* Verification */
        assertTrue(originalTime.dayOfWeek().equals(nextWeekTime.dayOfWeek()));
    }

    /**
     * Metamorphic Relation 23: Constructing two times with different time zones and
     * obtaining the millisecond difference should result in the same difference
     * when adjusting both times to a common time zone.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderZZ")
    public void test23(DateTimeZone zone1, DateTimeZone zone2) {
        /* Construct times in different time zones */
        DateTime timeInZone1 = new DateTime(zone1);
        DateTime timeInZone2 = new DateTime(zone2);

        /* Obtain the millisecond difference between the two times */
        long millisecondDifference = Math.abs(timeInZone1.getMillis() - timeInZone2.getMillis());

        /* Adjust both times to a common time zone */
        DateTime adjustedTimeInZone1 = timeInZone1.withZone(DateTimeZone.UTC);
        DateTime adjustedTimeInZone2 = timeInZone2.withZone(DateTimeZone.UTC);

        /* Obtain the millisecond difference after adjustment */
        long adjustedMillisecondDifference = Math
                .abs(adjustedTimeInZone1.getMillis() - adjustedTimeInZone2.getMillis());

        /* Verification */
        assertEquals(millisecondDifference, adjustedMillisecondDifference);
    }

    /**
     * Metamorphic Relation 24: Constructing two times with different formats
     * representing the same point in time should result in the same output when
     * formatting the times in a standard format.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderDFF")
    public void test24(DateTime time, DateTimeFormatter formatter1, DateTimeFormatter formatter2) {
        // TODO

        /* Format the time using the first formatter */
        String formattedTime1 = time.toString(formatter1);

        /* Format the time using the second formatter */
        String formattedTime2 = time.toString(formatter2);

        /* Verification */
        assertEquals(formattedTime1, formattedTime2);
    }

    /**
     * Metamorphic Relation 25: Constructing the date using the day of year and then
     * adding one year should result in the same day of the year in the following
     * year.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderIIIIIII")
    public void test25(int year, int dayOfYear) {
        /* Construct time from year and day of year */
        DateTime originalTime = new DateTime().withYear(year).withDayOfYear(dayOfYear);

        /* Add one year to the time */
        DateTime nextYearTime = originalTime.plusYears(1);

        /* Verification */
        assertEquals(originalTime.getDayOfYear(), nextYearTime.getDayOfYear());
    }

    /**
     * Metamorphic Relation 26: Adjusting the time to the end of the chronological
     * era, then setting the time to the beginning of the chronological era using
     * the same time should result in the same year but different era.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderDI")
    public void test26(DateTime time) {
        /* Adjust time to the end of the chronological era */
        DateTime endOfEraTime = time.withYear(9999);

        /* Set the time to the beginning of the chronological era */
        DateTime startOfEraTime = endOfEraTime.withYear(1);

        /* Verification */
        assertEquals(startOfEraTime.getYear(), endOfEraTime.getYear());
        assertNotEquals(startOfEraTime.getEra(), endOfEraTime.getEra());
    }

    /**
     * Metamorphic Relation 27: Calculating the age of a person based on their birth
     * date and the current date, and then adding one year to both dates should
     * result in the same difference in age.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderDDP")
    public void test27(DateTime birthDate, DateTime currentDate) {
        /* Calculate the age based on the birth date and current date */
        Period ageDifference = new Period(birthDate, currentDate);

        /* Add one year to both dates */
        DateTime nextBirthDate = birthDate.plusYears(1);
        DateTime nextCurrentDate = currentDate.plusYears(1);

        /* Calculate the age based on the modified dates */
        Period nextAgeDifference = new Period(nextBirthDate, nextCurrentDate);

        /* Verification */
        assertEquals(ageDifference, nextAgeDifference);
    }

    /**
     * Metamorphic Relation 28: Constructing a time using a specific date, then
     * adding a duration of 1 month should result in a time representing the same
     * day of the month in the following month.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderIIIIIII")
    public void test28(int year, int month, int day) {
        /* Construct time from year, month, and day */
        DateTime originalTime = new DateTime(year, month, day, 0, 0, 0, 0);

        /* Add 1 month to the time */
        DateTime nextMonthTime = originalTime.plusMonths(1);

        /* Verification */
        assertEquals(originalTime.getDayOfMonth(), nextMonthTime.getDayOfMonth());
    }

    /**
     * Metamorphic Relation 29: Constructing a time with a specific year, month, and
     * day, then adjusting the time to the beginning of the next day and then to the
     * beginning of the current day should result in the same day but different
     * times.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderIIIIIII")
    public void test29(int year, int month, int day) {
        /* Construct time from year, month, and day */
        DateTime originalTime = new DateTime(year, month, day, 0, 0, 0, 0);

        /* Adjust time to the beginning of the next day */
        DateTime startOfNextDayTime = originalTime.plusDays(1).withTimeAtStartOfDay();

        /* Adjust time to the beginning of the current day */
        DateTime startOfCurrentDayTime = originalTime.withTimeAtStartOfDay();

        /* Verification */
        assertEquals(startOfNextDayTime.toLocalDate(), startOfCurrentDayTime.toLocalDate());
        assertNotEquals(startOfNextDayTime, startOfCurrentDayTime);
    }

    /**
     * Metamorphic Relation 30: Constructing a time with a specific year, month, and
     * day, then adjusting the time to the beginning of the next week and then to
     * the beginning of the current week should result in the same week but
     * different times.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderIIIIIII")
    public void test30(int year, int month, int day) {
        /* Construct time from year, month, and day */
        DateTime originalTime = new DateTime(year, month, day, 0, 0, 0, 0);

        /* Adjust time to the beginning of the next week */
        DateTime startOfNextWeekTime = originalTime.plusWeeks(1).withDayOfWeek(1).withTimeAtStartOfDay();

        /* Adjust time to the beginning of the current week */
        DateTime startOfCurrentWeekTime = originalTime.withDayOfWeek(1).withTimeAtStartOfDay();

        /* Verification */
        assertEquals(startOfNextWeekTime.weekOfWeekyear().get(), startOfCurrentWeekTime.weekOfWeekyear().get());
        assertNotEquals(startOfNextWeekTime, startOfCurrentWeekTime);
    }

    /**
     * Metamorphic Relation 31: Constructing two times with identical dates but
     * different times and then accessing the time until midnight should have the
     * same result for both times.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderIIIIIIIII")
    public void test31(int year, int month, int day, int hour1, int minute1, int second1, int hour2, int minute2,
            int second2) {
        /* Construct times with identical dates but different times */
        DateTime time1 = new DateTime(year, month, day, hour1, minute1, second1, 0);
        DateTime time2 = new DateTime(year, month, day, hour2, minute2, second2, 0);

        /* Calculate the time until midnight for both times */
        Duration durationUntilMidnight1 = new Duration(time1, time1.toLocalDate().plusDays(1).toDateTimeAtStartOfDay());
        Duration durationUntilMidnight2 = new Duration(time2, time2.toLocalDate().plusDays(1).toDateTimeAtStartOfDay());

        /* Verification */
        assertEquals(durationUntilMidnight1, durationUntilMidnight2);
    }

    /**
     * Metamorphic Relation 32: Constructing a time with a specific year, month, and
     * day, then calculating the difference between that time and the current time,
     * and adding the difference to the current time should result in the same
     * original time.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderIIIIIII")
    public void test32(int year, int month, int day) {
        /* Construct time from year, month, and day */
        DateTime originalTime = new DateTime(year, month, day, 0, 0, 0, 0);

        /* Get the difference between the original time and the current time */
        Period timeDifference = new Period(originalTime, DateTime.now());

        /* Add the difference to the current time */
        DateTime calculatedTime = DateTime.now().plus(timeDifference);

        /* Verification */
        assertEquals(originalTime, calculatedTime);
    }

    /**
     * Metamorphic Relation 33: Checking the day of the week for the first day of a
     * month and the last day of the previous month should result in the same day of
     * the week.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderIIIIIII")
    public void test33(int year, int month) {
        /* Get the first day of the specified month */
        DateTime firstDayOfMonth = new DateTime(year, month, 1, 0, 0, 0, 0);

        /* Get the last day of the previous month */
        DateTime lastDayOfPreviousMonth = firstDayOfMonth.minusMonths(1).dayOfMonth().withMaximumValue();

        /* Verify the day of the week for both dates */
        assertEquals(firstDayOfMonth.getDayOfWeek(), lastDayOfPreviousMonth.getDayOfWeek());
    }

    /**
     * Metamorphic Relation 34: Adjusting the time to the beginning of a specific
     * day, then obtaining the time until the beginning of the next day should
     * result in exactly one day difference.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderDI")
    public void test34(DateTime time) {
        /* Adjust the time to the beginning of the day */
        DateTime startOfDayTime = time.withTimeAtStartOfDay();

        /* Obtain the time until the beginning of the next day */
        Duration timeUntilNextDay = new Duration(startOfDayTime, startOfDayTime.plusDays(1).withTimeAtStartOfDay());

        /* Verify the duration is exactly one day */
        assertEquals(86400000, timeUntilNextDay.getMillis());
    }

    /**
     * Metamorphic Relation 35: Adjusting the time to the beginning of a specific
     * hour, then obtaining the time until the beginning of the next hour should
     * result in an hour difference.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderDI")
    public void test35(DateTime time) {
        /* Adjust the time to the beginning of the hour */
        DateTime startOfHourTime = time.hourOfDay().roundFloorCopy();

        /* Obtain the time until the beginning of the next hour */
        Duration timeUntilNextHour = new Duration(startOfHourTime,
                startOfHourTime.plusHours(1).hourOfDay().roundFloorCopy());

        /* Verify the duration is exactly one hour */
        assertEquals(3600000, timeUntilNextHour.getMillis());
    }

    /**
     * Metamorphic Relation 36: Generating a time using a specific year, month, day,
     * hour, minute, and second, then obtaining the precise difference in
     * milliseconds between two instances of that time should result in zero
     * difference.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderIIIIIII")
    public void test36(int year, int month, int day, int hour, int minute, int second) {
        /* Generate two instances of the specified time */
        DateTime time1 = new DateTime(year, month, day, hour, minute, second, 0);
        DateTime time2 = new DateTime(year, month, day, hour, minute, second, 0);

        /* Obtain the difference in milliseconds between the two instances */
        long differenceInMilliseconds = Math.abs(time1.getMillis() - time2.getMillis());

        /* Verify the difference is zero */
        assertEquals(0, differenceInMilliseconds);
    }

    /**
     * Metamorphic Relation 37: Calculating the difference between the input time
     * and the start of the day, then obtaining the same difference in milliseconds
     * and adding it to the start of the day should result in the same time as the
     * input time.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderDI")
    public void test37(DateTime time) {
        /* Calculate the difference between the input time and the start of the day */
        Duration difference = new Duration(time.withTimeAtStartOfDay(), time);

        /* Obtain the same difference in milliseconds */
        long differenceInMilliseconds = difference.getMillis();

        /* Add the difference to the start of the day */
        DateTime calculatedTime = time.withTimeAtStartOfDay().plusMillis((int) differenceInMilliseconds);

        /* Verification */
        assertEquals(time, calculatedTime);
    }

    /**
     * Metamorphic Relation 38: Constructing two times and then using the isBefore
     * method, should return the opposite result when the positions of the two times
     * are reversed.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderDDP")
    public void test38(DateTime time1, DateTime time2) {
        /* Check if time1 is before time2 */
        boolean isTime1BeforeTime2 = time1.isBefore(time2);

        /* Check if time2 is before time1 */
        boolean isTime2BeforeTime1 = time2.isBefore(time1);

        /* Verification */
        assertEquals(isTime1BeforeTime2, !isTime2BeforeTime1);
    }

    /**
     * Metamorphic Relation 39: Constructing two times and calculating the
     * difference in days between them should yield the same result regardless of
     * their time zone adjustments.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderDDP")
    public void test39(DateTime time1, DateTime time2) {
        /* Calculate the difference in days between time1 and time2 */
        Days difference1 = Days.daysBetween(time1, time2);

        /* Calculate the difference in days after adjusting to a common time zone */
        Days difference2 = Days.daysBetween(time1.withZone(DateTimeZone.UTC), time2.withZone(DateTimeZone.UTC));

        /* Verification */
        assertEquals(difference1, difference2);
    }

    /**
     * Metamorphic Relation 40: Adding the duration of one week to a given time, and
     * then adding the duration of six days should result in the same time as adding
     * the duration of 13 days directly.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderDI")
    public void test40(DateTime time) {
        /* Add the duration of one week to the given time */
        DateTime timeAfterOneWeek = time.plusWeeks(1);

        /* Add the duration of six days to the time after one week */
        DateTime timeAfterThirteenDays = timeAfterOneWeek.plusDays(6);

        /* Add the duration of 13 days directly to the given time */
        DateTime timeAfterThirteenDaysDirect = time.plusDays(13);

        /* Verification */
        assertEquals(timeAfterThirteenDays, timeAfterThirteenDaysDirect);
    }

    /**
     * Metamorphic Relation 41: Constructing a time with a specific year, month, and
     * day, and then adjusting the time to the beginning of the year and to the end
     * of the year should result in the same year but different times.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderIIIIIII")
    public void test41(int year, int month, int day) {
        /* Construct time from year, month, and day */
        DateTime originalTime = new DateTime(year, month, day, 0, 0, 0, 0);

        /* Adjust time to the beginning of the year */
        DateTime startOfYearTime = originalTime.withDayOfYear(1).withTimeAtStartOfDay();

        /* Adjust time to the end of the year */
        DateTime endOfYearTime = originalTime.dayOfYear().withMaximumValue().withTime(23, 59, 59, 999);

        /* Verification */
        assertEquals(startOfYearTime.getYear(), endOfYearTime.getYear());
        assertNotEquals(startOfYearTime, endOfYearTime);
    }

    /**
     * Metamorphic Relation 42: Calculating the difference in days between two times
     * and then obtaining the same difference in weeks should result in a consistent
     * conversion.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderDDP")
    public void test42(DateTime time1, DateTime time2) {
        /* Calculate the difference in days between time1 and time2 */
        Days differenceInDays = Days.daysBetween(time1, time2);

        /* Obtain the difference in weeks using consistent conversion */
        Weeks differenceInWeeks = Weeks.weeks(differenceInDays.getDays() / 7);

        /* Verification */
        assertEquals(differenceInWeeks, Weeks.weeksBetween(time1, time2));
    }

    static Stream<Arguments> testcaseProviderDI() throws IOException {
        return testcaseGenerator.generate_di(1000);
    }

    static Stream<Arguments> testcaseProviderDII() throws IOException {
        return testcaseGenerator.generate_dii(1000);
    }

    static Stream<Arguments> testcaseProviderDZZ() throws IOException {
        return testcaseGenerator.generate_dzz(1000);
    }

    static Stream<Arguments> testcaseProviderL() throws IOException {
        return testcaseGenerator.generate_l(1000);
    }

    static Stream<Arguments> testcaseProviderIIIIIII() throws IOException {
        return testcaseGenerator.generate_iiiiiii(1000);
    }

    static Stream<Arguments> testcaseProviderInsZZ() throws IOException {
        return testcaseGenerator.generate_inszz(1000);
    }

    static Stream<Arguments> testcaseProviderZZ() throws IOException {
        return testcaseGenerator.generate_zz(1000);
    }

    static Stream<Arguments> testcaseProviderDDP() throws IOException {
        return testcaseGenerator.generate_ddp(1000);
    }

    static Stream<Arguments> testcaseProviderIIIIIIICC() throws IOException {
        return testcaseGenerator.generate_iiiiiiicc(1000);
    }

    static Stream<Arguments> testcaseProviderDFF() throws IOException {
        return testcaseGenerator.generate_dff(1000);
    }

    static Stream<Arguments> testcaseProviderIIIIIIIII() throws IOException {
        return testcaseGenerator.generate_iiiiiiiii(1000);
    }
}
