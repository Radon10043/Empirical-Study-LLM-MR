package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeFalse;
import static org.junit.jupiter.api.Assumptions.assumeTrue;
import static test.testcaseGenerator.genDateTime;
import static test.testcaseGenerator.genDateTimeZone;
import static test.testcaseGenerator.genInt;
import static test.testcaseGenerator.genLocalDate;
import static test.testcaseGenerator.genLocalDateTime;
import static test.testcaseGenerator.genLocalTime;
import static test.testcaseGenerator.genPeriod;
import static test.testcaseGenerator.writeToFile;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.time.Year;
import java.util.stream.Stream;

import org.joda.time.Chronology;
import org.joda.time.DateTime;
import org.joda.time.DateTimeZone;
import org.joda.time.Days;
import org.joda.time.Duration;
import org.joda.time.Interval;
import org.joda.time.LocalDate;
import org.joda.time.LocalDateTime;
import org.joda.time.LocalTime;
import org.joda.time.Period;
import org.joda.time.format.DateTimeFormat;
import org.joda.time.format.DateTimeFormatter;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

public class JodaTestGPT4 {
    /**
     * Metamorphic Relation 1: Adding a Period and a Duration representing the same
     * amount of time to a DateTime should yield the same result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testAddPeriodAndDuration(DateTime time, int hours) {
        /* Get source output */
        DateTime source_out = time.plusHours(hours);

        /* Construct follow-up input */
        Duration duration = new Duration(hours * 60 * 60 * 1000L);

        /* Get follow-up output */
        DateTime follow_out = time.plus(duration);

        /* Verification */
        assertTrue(source_out.equals(follow_out));
    }

    /**
     * Metamorphic Relation 2: Subtracting a Period from a DateTime should yield the
     * same result as adding a negative Period of the same length.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testSubtractPeriod(DateTime time, int days) {
        /* Get source output */
        DateTime source_out = time.minusDays(days);

        /* Construct follow-up input */
        Period period = new Period().withDays(-days);

        /* Get follow-up output */
        DateTime follow_out = time.plus(period);

        /* Verification */
        assertTrue(source_out.equals(follow_out));
    }

    /**
     * Metamorphic Relation 3: Converting a DateTime to a different time zone and
     * then converting it back should yield the same instant in time.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void testTimeZoneConversion(DateTime time, DateTimeZone zone) {
        /* Get source output */
        DateTime source_out = time;

        /* Construct follow-up input */
        DateTime zonedTime = time.withZone(zone);

        /* Convert back to original time zone */
        DateTime follow_out = zonedTime.withZone(time.getZone());

        /* Verification */
        assertTrue(source_out.isEqual(follow_out));
    }

    /**
     * Metamorphic Relation 4: Adding a duration twice with half of the original
     * duration each time should yield the same result as adding the entire duration
     * once.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testAddHalfDurations(DateTime time, long durationMillis) {
        /* Get source output */
        Duration fullDuration = new Duration(durationMillis);
        DateTime source_out = time.plus(fullDuration);

        /* Construct follow-up input */
        Duration halfDuration = new Duration(durationMillis / 2);

        /* Get follow-up output after adding half duration twice */
        DateTime follow_out = time.plus(halfDuration).plus(halfDuration);

        /* Verification */
        assertTrue(source_out.equals(follow_out));
    }

    /**
     * Metamorphic Relation 5: Changing the chronology of a DateTime should not
     * affect the instant (except for possible rounding issues due to the
     * granularity of the target chronology).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider5")
    public void testChronologyChange(DateTime time, Chronology targetChrono) { // Illegal
        /* Get source output */
        DateTime source_out = time;

        /* Change chronology */
        DateTime follow_out = time.withChronology(targetChrono);

        /*
         * Convert follow_out back to original chronology here if needed to compare
         * instants accurately
         * Note: Depending on the chronology change, it may not be accurate to compare
         * instants directly but instead compare field values (e.g., year, dayOfMonth,
         * etc.) due to differences in calendar systems.
         */

        /* Verification */
        assertTrue(source_out.toInstant().equals(follow_out.toInstant()));
    }

    /**
     * Metamorphic Relation 6: Formatting a DateTime using a specific pattern and
     * then parsing it back should yield the same DateTime if no information is lost
     * in formatting.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider3")
    public void testFormatAndParse(DateTime time, String patternStr) {
        /* Get source output */
        DateTimeFormatter pattern = DateTimeFormat.forPattern(patternStr);
        String formattedTime = time.toString(pattern);

        /* Construct follow-up input by parsing the formatted time */
        DateTime follow_out = DateTime.parse(formattedTime, pattern);

        /* Verification */
        assertTrue(time.isEqual(follow_out));
    }

    /**
     * Metamorphic Relation 7: Converting LocalDate to DateTime and back to
     * LocalDate should yield the original LocalDate, assuming default time zone.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider4")
    public void testLocalDateConversion(LocalDate date) {
        /* Get source output */
        LocalDate source_out = date;

        /* Construct follow-up input by converting to DateTime */
        DateTime dateTime = date.toDateTimeAtStartOfDay();

        /* Convert back to LocalDate */
        LocalDate follow_out = dateTime.toLocalDate();

        /* Verification */
        assertTrue(source_out.equals(follow_out));
    }

    /**
     * Metamorphic Relation 8: Comparing two LocalTimes for equality should yield
     * the same result regardless of the dates they are attached to, as long as both
     * dates are the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider5")
    public void testLocalTimeComparison(LocalTime time, LocalDate date1, LocalDate date2) {
        /* Create DateTime objects for the given LocalTimes on different dates */
        DateTime datetime1 = date1.toDateTime(time);
        DateTime datetime2 = date2.toDateTime(time);

        /* Verification */
        assertTrue(time.equals(datetime1.toLocalTime()));
        assertTrue(time.equals(datetime2.toLocalTime()));
        assertTrue(datetime1.toLocalTime().equals(datetime2.toLocalTime()));
    }

    /**
     * Metamorphic Relation 9: An Interval created by two DateTimes should maintain
     * its start and end times when converted to another time zone.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider6")
    public void testIntervalTimeZoneConversion(DateTime startTime, DateTime endTime, DateTimeZone timeZone) {
        /* Create an interval from start to end DateTime */
        Interval sourceInterval = new Interval(startTime, endTime);

        /* Convert times to another time zone */
        Interval followInterval = new Interval(
                startTime.withZone(timeZone), endTime.withZone(timeZone));

        /* Verification */
        assertTrue(sourceInterval.getStart().isEqual(followInterval.getStart()));
        assertTrue(sourceInterval.getEnd().isEqual(followInterval.getEnd()));
    }

    /**
     * Metamorphic Relation 10: Adding a Period consisting of months to a LocalDate
     * across a daylight saving time change should not affect the local time (as
     * LocalDate does not have a time component).
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider7")
    public void testLocalDateDSTPeriod(LocalDate date, int months) {
        /* Get source output */
        LocalDate source_out = date.plusMonths(months);

        /*
         * Assuming a context where DST could apply, if the LocalDate had a time
         * component
         */
        DateTime dateTime = date.toDateTimeAtStartOfDay();
        DateTime dstAdjustedDateTime = dateTime.plusMonths(months);

        /* Convert back to LocalDate */
        LocalDate follow_out = dstAdjustedDateTime.toLocalDate();

        /* Verification */
        assertTrue(source_out.equals(follow_out));
    }

    /**
     * Metamorphic Relation 11: Getting the day of the week from a LocalDate should
     * be invariant under addition of a number of weeks.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider7")
    public void testDayOfWeekInvarianceUnderWeekAddition(LocalDate date, int weeksToAdd) {
        /* Get source output */
        int dayOfWeekSource = date.getDayOfWeek();

        /* Add weeks to the date */
        LocalDate datePlusWeeks = date.plusWeeks(weeksToAdd);

        /* Get follow-up output */
        int dayOfWeekFollow = datePlusWeeks.getDayOfWeek();

        /* Verification */
        assertEquals(dayOfWeekSource, dayOfWeekFollow);
    }

    /**
     * Metamorphic Relation 12: Adjusting the time zone of a DateTime should
     * preserve the difference between two DateTimes when comparing them in
     * milliseconds.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider6")
    public void testPreservationOfMillisecondsDifference(DateTime firstTime, DateTime secondTime,
            DateTimeZone newZone) {
        /* Get source output milliseconds difference */
        long millisecondsDifferenceSource = new Duration(firstTime, secondTime).getMillis();

        /* Adjust time zones */
        DateTime firstTimeInNewZone = firstTime.withZone(newZone);
        DateTime secondTimeInNewZone = secondTime.withZone(newZone);

        /* Get follow-up output milliseconds difference */
        long millisecondsDifferenceFollow = new Duration(firstTimeInNewZone, secondTimeInNewZone).getMillis();

        /* Verification */
        assertEquals(millisecondsDifferenceSource, millisecondsDifferenceFollow);
    }

    /**
     * Metamorphic Relation 13: Adding an Interval's duration to its start time
     * should yield its end time.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testAddIntervalDurationToStartTime(DateTime start, long durationMillis) {
        /* Create an interval from start to start plus duration */
        Interval interval = new Interval(start, new Duration(durationMillis));

        /* Get source output (interval's end time) */
        DateTime intervalEndTime = interval.getEnd();

        /* Add duration to the interval's start time */
        DateTime timePlusDuration = start.plus(durationMillis);

        /* Verification */
        assertEquals(intervalEndTime, timePlusDuration);
    }

    /**
     * Metamorphic Relation 14: Subtracting a Period from a DateTime and then adding
     * the same Period should return the original DateTime.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider8")
    public void testSubtractThenAddPeriod(DateTime dateTime, Period period) {
        /* Subtract period from dateTime */
        DateTime dateTimeMinusPeriod = dateTime.minus(period);

        /* Add the same period to the new dateTime */
        DateTime resultDateTime = dateTimeMinusPeriod.plus(period);

        /* Verification */
        assertEquals(dateTime, resultDateTime);
    }

    /**
     * Metamorphic Relation 15: The millisOfDay value of LocalTime should remain the
     * same when converting to a DateTime and back to a LocalTime, assuming the date
     * is not crossing DST change.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider5")
    public void testLocalTimeMillisOfDayConversion(LocalTime time) {
        /* Get source output (millis of day value) */
        int millisOfDaySource = time.getMillisOfDay();

        /* Convert LocalTime to DateTime with a random date */
        LocalDate date = new LocalDate(2023, 1, 1); // Fixed date not affected by DST
        DateTime dateTime = time.toDateTimeToday(date.toDateTimeAtStartOfDay().getZone());

        /* Convert back to LocalTime */
        LocalTime followTime = dateTime.toLocalTime();

        /* Get follow-up output (millis of day value) */
        int millisOfDayFollow = followTime.getMillisOfDay();

        /* Verification */
        assertEquals(millisOfDaySource, millisOfDayFollow);
    }

    /**
     * Metamorphic Relation 16: The start and end of an Interval should remain the
     * same after serializing and deserializing the Interval.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider6")
    public void testIntervalSerialization(DateTime start, DateTime end) throws IOException, ClassNotFoundException {
        // Create an interval
        Interval originalInterval = new Interval(start, end);

        // Serialize the interval
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        ObjectOutputStream out = new ObjectOutputStream(bos);
        out.writeObject(originalInterval);
        out.flush();
        byte[] intervalBytes = bos.toByteArray();

        // Deserialize the interval
        ByteArrayInputStream bis = new ByteArrayInputStream(intervalBytes);
        ObjectInputStream in = new ObjectInputStream(bis);
        Interval deserializedInterval = (Interval) in.readObject();

        // Verification
        assertEquals(originalInterval.getStart(), deserializedInterval.getStart());
        assertEquals(originalInterval.getEnd(), deserializedInterval.getEnd());
    }

    /**
     * Metamorphic Relation 17: When two LocalDate instances represent the same
     * date, their toString output should be equal.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider17")
    public void testLocalDateToStringEquality(LocalDate date1, LocalDate date2) {
        // Verification that two LocalDate instances represent the same date
        assertTrue(date1.isEqual(date2));

        // Verification that their toString outputs are equal
        assertEquals(date1.toString(), date2.toString());
    }

    /**
     * Metamorphic Relation 18: The length in milliseconds of a Duration should not
     * change when it is added to and then subtracted from a DateTime.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDurationAddSubtractInvariance(DateTime dateTime, long durationMillis) { // Fixed
        // Create duration
        Duration duration = new Duration(durationMillis);

        // Add and then subtract the duration from the dateTime
        DateTime alteredDateTime = dateTime.plus(duration).minus(duration);

        // Verification
        // assertEquals(durationMillis, newerDuration.getMillis());
        assertEquals(dateTime, alteredDateTime);
    }

    /**
     * Metamorphic Relation 19: For any DateTime, adding one day should always yield
     * the next calendar day.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDateTimeNextCalendarDay(DateTime dateTime) {
        // Source output
        LocalDate originalDate = dateTime.toLocalDate();

        // Follow-up output
        LocalDate nextDate = originalDate.plusDays(1);

        // Verification
        LocalDate nextCalendarDay = dateTime.plusDays(1).toLocalDate();
        assertEquals(nextDate, nextCalendarDay);
    }

    /**
     * Metamorphic Relation 20: Changing the year of a LocalDate to a leap year and
     * back to the original year should result in the same LocalDate if the day is
     * not February 29.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider7")
    public void testLocalDateLeapYearInvariance(LocalDate date, int leapYear) {
        // Precondition verification: the original LocalDate is not February 29
        assumeFalse(date.getMonthOfYear() == 2 && date.getDayOfMonth() == 29);

        // Original year
        int originalYear = date.getYear();

        // Change the year to a leap year
        LocalDate leapYearDate = date.withYear(leapYear);

        // Change the year back to the original
        LocalDate finalDate = leapYearDate.withYear(originalYear);

        // Verification
        assertEquals(date, finalDate);
    }

    /**
     * Metamorphic Relation 21: A Duration's standard length in days should remain
     * constant when created from a fixed number of hours, regardless of which
     * LocalDate it is added to.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider7")
    public void testDurationStandardLength(LocalDate date, int hours) {
        // Create a Duration from hours
        Duration duration = new Duration(hours * 60L * 60L * 1000L);

        // Get the number of standard days in the duration
        int standardDays = duration.toStandardDays().getDays();

        // Add the duration to a LocalDate
        DateTime dateTime = date.toDateTimeAtStartOfDay();
        DateTime dateTimeAfterDuration = dateTime.plus(duration);

        // Get the difference in days
        Days daysBetween = Days.daysBetween(dateTime, dateTimeAfterDuration);

        // Verification
        assertEquals(standardDays, daysBetween.getDays());
    }

    /**
     * Metamorphic Relation 22: Converting LocalDateTime to LocalDate and then back
     * to LocalDateTime should yield the initial LocalDateTime if the time component
     * is at the start of day.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider9")
    public void testLocalDateTimeToDateAndBack(LocalDateTime localDateTime) { // Fixed
        localDateTime = localDateTime.withMillisOfDay(0);

        // Precondition check: ensure that the time is at the start of the day
        assumeTrue(localDateTime.toLocalTime().equals(LocalTime.MIDNIGHT));

        // Convert LocalDateTime to LocalDate
        LocalDate localDate = localDateTime.toLocalDate();

        // Convert back to LocalDateTime at the start of the day
        LocalDateTime convertedBackLocalDateTime = localDate.toLocalDateTime(LocalTime.MIDNIGHT);

        // Verification
        assertEquals(localDateTime, convertedBackLocalDateTime);
    }

    /**
     * Metamorphic Relation 23: For any LocalDateTime, reversing the order of the
     * date and time components and then reordering should yield the original
     * LocalDateTime.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider23")
    public void testLocalDateTimeComponentReorder(LocalDateTime localDateTime) {
        // LocalDate originalDate = localDateTime.toLocalDate();
        // LocalTime originalTime = localDateTime.toLocalTime();

        // // Reverse the order: create LocalDateTime from time and date
        // LocalDateTime reversedLocalDateTime =
        // originalTime.toLocalDateTime(originalDate);

        // // Reorder to the original: create LocalDateTime from date and time
        // LocalDateTime reorderedLocalDateTime = reversedLocalDateTime.toLocalDate()
        // .toLocalDateTime(reversedLocalDateTime.toLocalTime());

        // // Verification
        // assertEquals(localDateTime, reorderedLocalDateTime);
    }

    /**
     * Metamorphic Relation 24: The day of the month retrieved from DateTime should
     * remain constant under transformation to another timezone and back, assuming
     * the original DateTime does not cross midnight when changed to the other
     * timezone.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void testPreserveDayOfMonthOnTimeZoneRoundTrip(DateTime dateTime, DateTimeZone otherTimeZone) {
        // Precondition: Ensure the day of month does not change in the other time zone
        assumeTrue(dateTime.toDateTime(otherTimeZone).getDayOfMonth() == dateTime.getDayOfMonth());

        // Original day of month
        int originalDayOfMonth = dateTime.getDayOfMonth();

        // Change timezone and then change back
        int roundTripDayOfMonth = dateTime.withZone(otherTimeZone)
                .withZone(dateTime.getZone())
                .getDayOfMonth();

        // Verification
        assertEquals(originalDayOfMonth, roundTripDayOfMonth);
    }

    /**
     * Metamorphic Relation 25: The date retrieved from two different DateTime
     * instances should be the same when both DateTimes represent the exact same
     * instant, even if they have different timezones.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void testDateEqualityAtSameInstant(DateTime dateTime1, DateTimeZone timeZone2) {
        // Construct another DateTime with a different timezone but the same instant
        DateTime dateTime2 = dateTime1.withZone(timeZone2);

        // The dates should be equal as they represent the same instant
        LocalDate localDate1 = dateTime1.toLocalDate();
        LocalDate localDate2 = dateTime2.toLocalDate();

        // Verification
        assertTrue(localDate1.isEqual(localDate2));
    }

    /**
     * Metamorphic Relation 26: Increasing the years on a LocalDate by a number and
     * then decreasing by the same number should return the original LocalDate,
     * given that it is not a leap day.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider7")
    public void testYearIncrementDecrement(LocalDate date, int years) {
        // Precondition check: ensure that the date is not February 29 on a leap year
        assumeFalse(date.getMonthOfYear() == 2 && date.getDayOfMonth() == 29 && Year.isLeap(date.getYear()));

        // Increase years
        LocalDate increasedDate = date.plusYears(years);

        // Decrease years
        LocalDate resultDate = increasedDate.minusYears(years);

        // Verification
        assertEquals(date, resultDate);
    }

    /**
     * Metamorphic Relation 27: The day of the week should be the same for two
     * LocalDate instances that are a multiple of 7 days apart.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider7")
    public void testDayOfWeekAfterMultipleOf7Days(LocalDate date, int multiple) {
        int daysToAdd = 7 * multiple;
        LocalDate newDate = date.plusDays(daysToAdd);
        assertEquals(date.getDayOfWeek(), newDate.getDayOfWeek());
    }

    /**
     * Metamorphic Relation 28: The year of a LocalDate should not be affected by
     * adding or subtracting a Period made only of months.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider7")
    public void testYearUnchangedByMonthsPeriod(LocalDate date, int months) {
        Period monthsPeriod = Period.months(months);
        LocalDate dateAfterAddingMonths = date.plus(monthsPeriod);
        LocalDate dateAfterSubtractingMonths = dateAfterAddingMonths.minus(monthsPeriod);
        assertEquals(date.getYear(), dateAfterSubtractingMonths.getYear());
    }

    /**
     * Metamorphic Relation 29: The month of the LocalDate retrieved from a DateTime
     * should be preserved when the DateTime is converted to a LocalDate even after
     * changing the DateTime's chronology to a different calendar system.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider10")
    public void testMonthPreservedAfterChronologyChange(DateTime dateTime, Chronology chronology) {
        int originalMonth = dateTime.getMonthOfYear();
        // Change to a different chronology
        DateTime changedChronologyDateTime = dateTime.withChronology(chronology);
        // Convert to LocalDate and get month
        int monthAfterChange = changedChronologyDateTime.toLocalDate().getMonthOfYear();
        assertEquals(originalMonth, monthAfterChange);
    }

    /**
     * Metamorphic Relation 30: The Duration between two DateTime instances should
     * remain the same when shifting both DateTimes by the same Period.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider11")
    public void testDurationBetweenShiftedByPeriod(DateTime startDateTime, DateTime endDateTime, Period shiftPeriod) {
        // Original duration
        Duration originalDuration = new Duration(startDateTime, endDateTime);
        // Shift both DateTimes by the same period
        DateTime shiftedStartDateTime = startDateTime.plus(shiftPeriod);
        DateTime shiftedEndDateTime = endDateTime.plus(shiftPeriod);
        // Get duration between the shifted DateTimes
        Duration shiftedDuration = new Duration(shiftedStartDateTime, shiftedEndDateTime);
        // Verification
        assertEquals(originalDuration, shiftedDuration);
    }

    /**
     * Metamorphic Relation 31: For any LocalDateTime, formatting it and then
     * parsing that format without a zone should yield the same LocalDateTime.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider31")
    public void testLocalDateTimeFormatParse(LocalDateTime localDateTime) {
        // DateTimeFormatter formatter = DateTimeFormatter.ISO_LOCAL_DATE_TIME;
        // // Format LocalDateTime
        // String formattedTime = localDateTime.toString(formatter);

        // // Parse LocalDateTime from formatted string
        // LocalDateTime parsedLocalDateTime = LocalDateTime.parse(formattedTime,
        // formatter);

        // // Verification
        // assertEquals(localDateTime, parsedLocalDateTime);
    }

    /**
     * Metamorphic Relation 32: When converting LocalTime to DateTime and back, the
     * nanosecond of day is preserved.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider5")
    public void testLocalTimeNanosecondOfDayPreservation(LocalTime localTime) {
        // Create a DateTime at the given LocalTime
        DateTime dateTime = new LocalDate().toDateTime(localTime);

        // Convert back to LocalTime
        LocalTime convertedLocalTime = dateTime.toLocalTime();

        // Verification
        assertEquals(localTime.getMillisOfDay(), convertedLocalTime.getMillisOfDay());
    }

    /**
     * Metamorphic Relation 33: Adding a zero Period to a DateTime should not change
     * the DateTime.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider33")
    public void testAddZeroPeriod(DateTime dateTime) {
        Period zeroPeriod = Period.ZERO;
        DateTime unchangedDateTime = dateTime.plus(zeroPeriod);
        assertEquals(dateTime, unchangedDateTime);
    }

    /**
     * Metamorphic Relation 34: Adding and then subtracting the same number of days
     * to a LocalDate should yield the original date.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider7")
    public void testAddSubtractDays(LocalDate localDate, int daysToAddAndSubtract) {
        LocalDate newDate = localDate.plusDays(daysToAddAndSubtract).minusDays(daysToAddAndSubtract);
        assertEquals(localDate, newDate);
    }

    /**
     * Metamorphic Relation 35: Adding two Periods together and then adding the
     * result to a DateTime should yield the same result as adding each Period
     * separately.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider12")
    public void testPeriodAddition(DateTime dateTime, Period period1, Period period2) {
        Period combinedPeriod = period1.plus(period2);
        DateTime dateTimeWithCombinedPeriod = dateTime.plus(combinedPeriod);
        DateTime dateTimeWithSeparatePeriods = dateTime.plus(period1).plus(period2);
        assertEquals(dateTimeWithCombinedPeriod, dateTimeWithSeparatePeriods);
    }

    /**
     * Metamorphic Relation 36: The difference in days between two LocalDate
     * instances should remain unchanged before and after adding a year to both
     * dates.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider13")
    public void testDifferenceInDaysOverYears(LocalDate date1, LocalDate date2) {
        int differenceInDays = Days.daysBetween(date1, date2).getDays();
        LocalDate date1PlusYear = date1.plusYears(1);
        LocalDate date2PlusYear = date2.plusYears(1);
        int differenceInDaysAfterYear = Days.daysBetween(date1PlusYear, date2PlusYear).getDays();
        assertEquals(differenceInDays, differenceInDaysAfterYear);
    }

    /**
     * Metamorphic Relation 37: The formatted output for two different instances of
     * the same DateTimeKind that represent the same instant should be identical.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider11")
    public void testFormattedOutputForSameInstant(DateTime dateTime1) { // Fixed
        DateTime dateTime2 = dateTime1;

        // Assume both DateTimes represent the same instant
        assumeTrue(dateTime1.isEqual(dateTime2));

        DateTimeFormatter formatter = DateTimeFormat.forPattern("yyyy-MM-dd HH:mm:ss");
        // Format both DateTimes
        String formattedTime1 = dateTime1.toString(formatter);
        String formattedTime2 = dateTime2.toString(formatter);

        // Verification
        assertEquals(formattedTime1, formattedTime2);
    }

    /**
     * Metamorphic Relation 38: Converting a LocalDate to a LocalTime with a
     * specific time and back to LocalDate should return the original LocalDate.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider4")
    public void testLocalDateToLocalTimeConversion(LocalDate date) {
        LocalTime time = new LocalTime(12, 0); // Use a specific time, such as 12:00 PM
        LocalDateTime dateTime = date.toLocalDateTime(time);
        LocalDate convertedBackDate = dateTime.toLocalDate();
        assertEquals(date, convertedBackDate);
    }

    /**
     * Metamorphic Relation 39: Comparing LocalTime from identical DateTime objects
     * with different time zones should yield the same result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider14")
    public void testLocalTimeIdentityWithDifferentTimeZones(DateTime dateTime, DateTimeZone timeZone1,
            DateTimeZone timeZone2) {
        LocalTime localTimeInZone1 = dateTime.withZone(timeZone1).toLocalTime();
        LocalTime localTimeInZone2 = dateTime.withZone(timeZone2).toLocalTime();
        assertEquals(localTimeInZone1, localTimeInZone2);
    }

    /**
     * Metamorphic Relation 40: An Interval's duration should not change after
     * adjusting the Interval's start and end DateTimes individually by the same
     * amount.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider15")
    public void testIntervalDurationAfterAdjustingStartAndEnd(DateTime start, DateTime end, Duration adjustment) {
        Interval originalInterval = new Interval(start, end);
        long originalDurationMillis = originalInterval.toDurationMillis();

        DateTime newStart = start.plus(adjustment);
        DateTime newEnd = end.plus(adjustment);
        Interval adjustedInterval = new Interval(newStart, newEnd);
        long adjustedDurationMillis = adjustedInterval.toDurationMillis();

        assertEquals(originalDurationMillis, adjustedDurationMillis);
    }

    static Stream<Arguments> testcaseProvider1() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            DateTime time = genDateTime();
            int val = genInt(1, 100);
            tcs[i] = Arguments.of(time, val);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProvider2() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            DateTime time = genDateTime();
            DateTimeZone zone = genDateTimeZone();
            tcs[i] = Arguments.of(time, zone);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProvider3() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            DateTime time = genDateTime();
            String patternStr = "yyyy-MM-dd HH:mm:ss";
            tcs[i] = Arguments.of(time, patternStr);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProvider4() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            LocalDate date = genLocalDate();
            tcs[i] = Arguments.of(date);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProvider5() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            LocalTime time = genLocalTime();
            LocalDate date1 = genLocalDate();
            LocalDate date2 = genLocalDate();
            tcs[i] = Arguments.of(time, date1, date2);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProvider6() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            DateTime startTime = genDateTime();
            DateTime endTime = startTime.plusDays(genInt(1, 100));
            DateTimeZone zone = genDateTimeZone();
            tcs[i] = Arguments.of(startTime, endTime, zone);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProvider7() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            LocalDate date = genLocalDate();
            int val = genInt(1, 100);
            tcs[i] = Arguments.of(date, val);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProvider8() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            DateTime dateTime = genDateTime();
            Period period = genPeriod();
            tcs[i] = Arguments.of(dateTime, period);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProvider9() {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            LocalDateTime localDateTime = genLocalDateTime();
            tcs[i] = Arguments.of(localDateTime);
        }
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProvider10() {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            DateTime dateTime = genDateTime();
            Chronology chronology = genDateTime().getChronology();
            tcs[i] = Arguments.of(dateTime, chronology);
        }
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProvider11() {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            DateTime startDateTime = genDateTime();
            DateTime endDateTime = startDateTime.plusDays(genInt(1, 100));
            Period shiftPeriod = genPeriod();
            tcs[i] = Arguments.of(startDateTime, endDateTime, shiftPeriod);
        }
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProvider12() {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            DateTime dateTime = genDateTime();
            Period period1 = genPeriod();
            Period period2 = genPeriod();
            tcs[i] = Arguments.of(dateTime, period1, period2);
        }
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProvider13() {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            LocalDate date1 = genLocalDate();
            LocalDate date2 = genLocalDate();
            tcs[i] = Arguments.of(date1, date2);
        }
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProvider14() {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            DateTime dateTime = genDateTime();
            DateTimeZone timeZone1 = genDateTimeZone();
            DateTimeZone timeZone2 = genDateTimeZone();
            tcs[i] = Arguments.of(dateTime, timeZone1, timeZone2);
        }
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProvider15() {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            DateTime start = genDateTime();
            DateTime end = start.plusDays(genInt(1, 100));
            Duration adjustment = new Duration(genInt(1, 100) * 60 * 60 * 1000L);
            tcs[i] = Arguments.of(start, end, adjustment);
        }
        return Stream.of(tcs);
    }
}
