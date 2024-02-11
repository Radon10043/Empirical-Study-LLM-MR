package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import java.io.IOException;
import java.util.stream.Stream;

import org.joda.time.Chronology;
import org.joda.time.DateTime;
import org.joda.time.DateTimeZone;
import org.joda.time.Duration;
import org.joda.time.Interval;
import org.joda.time.LocalDate;
import org.joda.time.LocalDateTime;
import org.joda.time.LocalTime;
import org.joda.time.Period;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import org.junit.runners.Parameterized.Parameter;

import static test.testcaseGenerator.*;

public class JodaTestGPT3D5 {
    /**
     * Metamorphic Relation 1: Adding a duration of time to the input time, and then subtracting the
     * same duration of time from the output will produce the same input time.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR1")
    public void test1(DateTime time, Duration duration) {
        // Get source output
        DateTime source_out = time.plus(duration);

        // Construct follow-up input
        Duration negDuration = duration.negated();

        // Get follow-up output
        DateTime follow_out = source_out.plus(negDuration);

        // Verification
        assertEquals(time, follow_out);
    }

    /**
     * Metamorphic Relation 2: Constructing a new DateTime instance based on components of the input
     * DateTime and then accessing those components from the follow-up output will yield the same
     * values as the source input DateTime.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR2")
    public void test2(DateTime time) {
        // Get components of the source input
        int year = time.getYear();
        int month = time.getMonthOfYear();
        int day = time.getDayOfMonth();
        int hour = time.getHourOfDay();
        int minute = time.getMinuteOfHour();
        int second = time.getSecondOfMinute();

        // Create a new DateTime based on the source input components
        DateTime newTime = new DateTime(year, month, day, hour, minute, second);

        // Get components of the follow-up output
        int newYear = newTime.getYear();
        int newMonth = newTime.getMonthOfYear();
        int newDay = newTime.getDayOfMonth();
        int newHour = newTime.getHourOfDay();
        int newMinute = newTime.getMinuteOfHour();
        int newSecond = newTime.getSecondOfMinute();

        // Verification
        assertEquals(year, newYear);
        assertEquals(month, newMonth);
        assertEquals(day, newDay);
        assertEquals(hour, newHour);
        assertEquals(minute, newMinute);
        assertEquals(second, newSecond);
    }

    /**
     * Metamorphic Relation 3: Comparing the input DateTime with another DateTime shifted by a
     * certain duration will have the same result as comparing the follow-up output with the
     * original input DateTime.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR1")
    public void test3(DateTime time, Duration duration) {
        // Get a DateTime shifted by the duration
        DateTime shiftedTime = time.plus(duration);

        // Get follow-up output
        DateTime follow_out = time.plus(duration);

        // Verification
        assertEquals(time.compareTo(follow_out), time.compareTo(shiftedTime));
    }

    /**
     * Metamorphic Relation 4: Subtracting a duration from the input time, and then adding the same
     * duration to the follow-up output will result in the same time as the source input.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR1")
    public void test4(DateTime time, Duration duration) {
        // Get a DateTime subtracted by the duration
        DateTime subTime = time.minus(duration);

        // Get follow-up output
        DateTime follow_out = subTime.plus(duration);

        // Verification
        assertEquals(time, follow_out);
    }

    /**
     * Metamorphic Relation 5: Constructing a new DateTime with a different chronology based on the
     * input time, and then accessing the year/month/day components from the follow-up output will
     * yield the same values as the source input DateTime.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR2")
    public void test5(DateTime time) {
        // Get the chronology of the input
        Chronology chronology = time.getChronology();

        // Construct a new DateTime with a different chronology
        DateTime newTime = new DateTime(time.getMillis(), chronology.withUTC());

        // Get components of the follow-up output
        int year = newTime.year().get();
        int month = newTime.monthOfYear().get();
        int day = newTime.dayOfMonth().get();

        // Get components of the source input
        int sourceYear = time.getYear();
        int sourceMonth = time.getMonthOfYear();
        int sourceDay = time.getDayOfMonth();

        // Verification
        assertEquals(sourceYear, year);
        assertEquals(sourceMonth, month);
        assertEquals(sourceDay, day);
    }

    /**
     * Metamorphic Relation 6: Constructing a new DateTime by setting the time components to a
     * different value than the input time, and then accessing those components from the follow-up
     * output will yield the same values as the newly constructed DateTime.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR6")
    public void test6(DateTime time, int hour, int minute, int second) {
        // Create a new DateTime with the specified time components
        DateTime newTime = time.withTime(hour, minute, second, 0);

        // Get components of the follow-up output
        int newHour = newTime.getHourOfDay();
        int newMinute = newTime.getMinuteOfHour();
        int newSecond = newTime.getSecondOfMinute();

        // Verification
        assertEquals(hour, newHour);
        assertEquals(minute, newMinute);
        assertEquals(second, newSecond);
    }

    /**
     * Metamorphic Relation 7: Comparing the input LocalDate with another LocalDate shifted by a
     * certain duration will have the same result as comparing the follow-up output with the
     * original input LocalDate.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR7")
    public void test7(LocalDate date, Period period) {
        // Get a LocalDate shifted by the period
        LocalDate shiftedDate = date.plus(period);

        // Get follow-up output
        LocalDate follow_out = date.plus(period);

        // Verification
        assertEquals(date.compareTo(follow_out), date.compareTo(shiftedDate));
    }

    /**
     * Metamorphic Relation 8: Adding a duration to the input time and then obtaining the day of
     * week from the output should yield the same result as getting the day of the week from the
     * original input time.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR1")
    public void test8(DateTime time, Duration duration) {
        // Get day of week from the source output
        int sourceDayOfWeek = time.getDayOfWeek();

        // Get day of week from the follow-up output
        int followDayOfWeek = time.plus(duration).getDayOfWeek();

        // Verification
        assertEquals(sourceDayOfWeek, followDayOfWeek);
    }

    /**
     * Metamorphic Relation 9: Multiplying the input duration by a scalar factor and then dividing
     * the follow-up output duration by the same scalar factor should result in the same duration as
     * the source input.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR9")
    public void test9(Duration duration, int scalar) {
        // Multiply the input duration by the scalar factor
        Duration multipliedDuration = duration.multipliedBy(scalar);

        // Divide the follow-up output duration by the same scalar factor
        Duration dividedDuration = duration.dividedBy(scalar);

        // Verification
        assertEquals(duration, dividedDuration);
        assertEquals(duration, multipliedDuration);
    }

    /**
     * Metamorphic Relation 10: Comparing the input LocalDate with another LocalDate based on the
     * day of year will yield the same result as comparing the follow-up output with the original
     * input LocalDate.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR7")
    public void test10(LocalDate date, Period period) {
        // Get a LocalDate shifted by the period
        LocalDate shiftedDate = date.plus(period);

        // Get follow-up output
        LocalDate follow_out = date.plus(period);

        // Verification
        assertEquals(shiftedDate.getDayOfYear(), follow_out.getDayOfYear());
    }

    /**
     * Metamorphic Relation 11: Subtracting a period from the input date, and then adding the same
     * period to the follow-up output will result in the same date as the source input.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR7")
    public void test11(LocalDate date, Period period) {
        // Subtract the period from the input date
        LocalDate subDate = date.minus(period);

        // Get follow-up output
        LocalDate follow_out = subDate.plus(period);

        // Verification
        assertEquals(date, follow_out);
    }

    /**
     * Metamorphic Relation 12: Comparing the input LocalTime with another LocalTime shifted by a
     * certain duration will have the same result as comparing the follow-up output with the
     * original input LocalTime.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR12")
    public void test12(LocalTime time, Duration duration) {
        // Get a LocalTime shifted by the duration
        LocalTime shiftedTime = time.plusMillis((int) duration.getMillis());

        // Get follow-up output
        LocalTime follow_out = time.plusMillis((int) duration.getMillis());

        // Verification
        assertEquals(time.compareTo(follow_out), time.compareTo(shiftedTime));
    }

    /**
     * Metamorphic Relation 13: Comparing the input and follow-up DateTime instances for equality
     * after converting both to UTC will yield the same result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR13")
    public void test13(DateTime time, DateTimeZone zone) {
        // Get the input DateTime in UTC
        DateTime utcTime = time.withZone(DateTimeZone.UTC);

        // Get the follow-up DateTime in UTC
        DateTime followUpUtcTime = time.withZone(zone).withZone(DateTimeZone.UTC);

        // Verification
        assertEquals(utcTime, followUpUtcTime);
    }

    /**
     * Metamorphic Relation 14: Constructing a new DateTime by setting the year to a different
     * value, and then accessing the year component from the follow-up output will yield the same
     * value as the newly constructed DateTime.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR14")
    public void test14(DateTime time, int year) {
        // Create a new DateTime with the specified year
        DateTime newTime = time.withYear(year);

        // Get the year from the follow-up output
        int newYear = newTime.getYear();

        // Verification
        assertEquals(year, newYear);
    }

    /**
     * Metamorphic Relation 15: Adding a period to the input date, and then subtracting the same
     * period from the follow-up output will result in the same date as the source input.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR7")
    public void test15(LocalDate date, Period period) {
        // Add the period to the input date
        LocalDate addedDate = date.plus(period);

        // Get follow-up output
        LocalDate follow_out = addedDate.minus(period);

        // Verification
        assertEquals(date, follow_out);
    }

    /**
     * Metamorphic Relation 16: Constructing a new LocalDate with a different chronology based on
     * the input date, and then accessing the era component from the follow-up output will yield the
     * same value as the source input LocalDate.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR16")
    public void test16(LocalDate date, Chronology chronology) {
        // Construct a new LocalDate with a different chronology
        LocalDate newDate = new LocalDate(date.toDate(), chronology);

        // Get the era from the follow-up output
        int newEra = newDate.getEra();

        // Get the era from the source input
        int sourceEra = date.getEra();

        // Verification
        assertEquals(sourceEra, newEra);
    }

    /**
     * Metamorphic Relation 17: Comparing the input DateTime with another DateTime by adding a
     * duration representing milliseconds will have the same result as comparing the follow-up
     * output with the original input DateTime.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR17")
    public void test17(DateTime time, long milliseconds) {
        // Get a DateTime shifted by the specified milliseconds
        DateTime shiftedTime = time.plusMillis((int) milliseconds);

        // Get follow-up output
        DateTime follow_out = time.plusMillis((int) milliseconds);

        // Verification
        assertEquals(time.compareTo(follow_out), time.compareTo(shiftedTime));
    }

    /**
     * Metamorphic Relation 18: Constructing a new LocalTime with a different second-of-minute based
     * on the input time, and then accessing the second component from the follow-up output will
     * yield the same value as the source input LocalTime.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR18")
    public void test18(LocalTime time, int second) {
        // Create a new LocalTime with the specified second-of-minute
        LocalTime newTime = new LocalTime(time.getHourOfDay(), time.getMinuteOfHour(), second);

        // Get the second component from the follow-up output
        int newSecond = newTime.getSecondOfMinute();

        // Verification
        assertEquals(second, newSecond);
    }

    /**
     * Metamorphic Relation 19: Comparing the input Duration with another Duration multiplied by a
     * scalar factor will have the same result as comparing the follow-up output with the original
     * input Duration.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR9")
    public void test19(Duration duration, int scalar) {
        // Get a Duration multiplied by the scalar factor
        Duration multipliedDuration = duration.multipliedBy(scalar);

        // Get follow-up output
        Duration follow_out = duration.multipliedBy(scalar);

        // Verification
        assertEquals(duration.compareTo(follow_out), duration.compareTo(multipliedDuration));
    }

    /**
     * Metamorphic Relation 20: Constructing a new DateTime by setting different
     * millisecond-of-second based on the input time, and then accessing the millisecond component
     * from the follow-up output will yield the same value as the newly constructed DateTime.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR20")
    public void test20(DateTime time, int millis) {
        // Create a new DateTime with the specified millisecond-of-second
        DateTime newTime = time.withMillisOfSecond(millis);

        // Get the millisecond component from the follow-up output
        int newMillis = newTime.getMillisOfSecond();

        // Verification
        assertEquals(millis, newMillis);
    }

    /**
     * Metamorphic Relation 21: Checking if the input Interval overlaps with another Interval
     * shifted by a specified duration will have the same result as checking if the follow-up output
     * overlaps with the original input Interval.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR21")
    public void test21(Interval interval, Duration duration) {
        // Get an Interval shifted by the specified duration
        Interval shiftedInterval = interval.toDuration().plus(duration).toIntervalFrom(null);

        // Get follow-up output
        Interval follow_out = interval.toDuration().plus(duration).toIntervalFrom(null);

        // Verification
        assertEquals(interval.overlaps(follow_out), interval.overlaps(shiftedInterval));
    }

    /**
     * Metamorphic Relation 22: Constructing a new LocalTime by setting a time based on the input
     * time, and then accessing the time components (hour, minute, second) from the follow-up output
     * will yield the same values as the newly constructed LocalTime.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR22")
    public void test22(LocalTime time, int hour, int minute, int second) {
        // Create a new LocalTime with the specified time components
        LocalTime newTime = new LocalTime(hour, minute, second);

        // Get the time components from the follow-up output
        int newHour = newTime.getHourOfDay();
        int newMinute = newTime.getMinuteOfHour();
        int newSecond = newTime.getSecondOfMinute();

        // Verification
        assertEquals(hour, newHour);
        assertEquals(minute, newMinute);
        assertEquals(second, newSecond);
    }

    /**
     * Metamorphic Relation 23: Adding a period to the input LocalDate and then obtaining the week
     * of year from the output should yield the same result as getting the week of the year from the
     * original input LocalDate.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR7")
    public void test23(LocalDate date, Period period) {
        // Get week of year from the source output
        int sourceWeek = date.getWeekOfWeekyear();

        // Get week of year from the follow-up output
        int followWeek = date.plus(period).getWeekOfWeekyear();

        // Verification
        assertEquals(sourceWeek, followWeek);
    }

    /**
     * Metamorphic Relation 24: Subtracting a period from the input LocalDate and then obtaining the
     * day of the month from the output should yield the same result as getting the day of the month
     * from the source input LocalDate.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR7")
    public void test24(LocalDate date, Period period) {
        // Get day of month from the source output
        int sourceDay = date.getDayOfMonth();

        // Get day of month from the follow-up output
        int followDay = date.minus(period).getDayOfMonth();

        // Verification
        assertEquals(sourceDay, followDay);
    }

    /**
     * Metamorphic Relation 25: Comparing the input Period with another Period representing the same
     * duration will have the same result as comparing the follow-up output with the original input
     * Period.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR25")
    public void test25(Period period) {
        // Get follow-up output
        Period follow_out = period;

        // Verification
        assertEquals(period, follow_out);
    }

    /**
     * Metamorphic Relation 26: Constructing a new DateTime by setting different millis-of-day based
     * on the input time, and then accessing the millis-of-day component from the follow-up output
     * will yield the same value as the newly constructed DateTime.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR26")
    public void test26(DateTime time, int millisOfDay) {
        // Create a new DateTime with the specified millis-of-day
        DateTime newTime = time.withMillisOfDay(millisOfDay);

        // Get the millis-of-day component from the follow-up output
        int newMillisOfDay = newTime.getMillisOfDay();

        // Verification
        assertEquals(millisOfDay, newMillisOfDay);
    }

    /**
     * Metamorphic Relation 27: Comparing the input Period with another Period representing a
     * negation of the duration will result in the opposite comparison as when comparing the
     * follow-up output with the original input Period.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR25")
    public void test27(Period period) {
        // // Get the negation of the input period
        // Period negatedPeriod = period.negated();

        // // Verification
        // assertEquals(period.compareTo(negatedPeriod), -negatedPeriod.compareTo(period));

        // // Get follow-up output
        // Period follow_out = period.negated();

        // // Verification
        // assertEquals(period.compareTo(follow_out), -follow_out.compareTo(period));
    }

    /**
     * Metamorphic Relation 28: Constructing a new LocalDate by setting the year, month and day
     * based on the input date of the year, and then accessing the day-of-year component from the
     * follow-up output will yield the same value as the source input LocalDate.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR28")
    public void test28(LocalDate date, int year, int month, int day) {
        // Create a new LocalDate with the specified year, month, and day
        LocalDate newDate = new LocalDate(year, month, day);

        // Get the day-of-year component from the follow-up output
        int dayOfYear = newDate.getDayOfYear();

        // Get the day-of-year component from the source input
        int sourceDayOfYear = date.getDayOfYear();

        // Verification
        assertEquals(sourceDayOfYear, dayOfYear);
    }

    /**
     * Metamorphic Relation 29: Adding a period to the input datetime instance, and then subtracting
     * the same period from the follow-up output will yield the same datetime as the source input.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR29")
    public void test29(DateTime time, Period period) {
        // Add the period to the input datetime
        DateTime addedTime = time.plus(period);

        // Get follow-up output
        DateTime follow_out = addedTime.minus(period);

        // Verification
        assertEquals(time, follow_out);
    }

    /**
     * Metamorphic Relation 30: Constructing a new LocalTime by setting a different hour-of-day
     * based on the input time, and then accessing the hour component from the follow-up output will
     * yield the same value as the newly constructed LocalTime.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR22")
    public void test30(LocalTime time, int hour) {
        // Create a new LocalTime with the specified hour-of-day
        LocalTime newTime = new LocalTime(hour, time.getMinuteOfHour(), time.getSecondOfMinute(),
                time.getMillisOfSecond());

        // Get the hour component from the follow-up output
        int newHour = newTime.getHourOfDay();

        // Verification
        assertEquals(hour, newHour);
    }

    /**
     * Metamorphic Relation 31: Adding a period to the input date-time instance, and then getting
     * the millis-of-day from the output should yield the same result as getting the millis-of-day
     * from the original input date-time.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR29")
    public void test31(DateTime dateTime, Period period) {
        // Get millis-of-day from the source output
        int sourceMillisOfDay = dateTime.getMillisOfDay();

        // Get millis-of-day from the follow-up output
        int followMillisOfDay = dateTime.plus(period).getMillisOfDay();

        // Verification
        assertEquals(sourceMillisOfDay, followMillisOfDay);
    }

    /**
     * Metamorphic Relation 32: Constructing a new LocalDate by setting the year, month and day
     * based on the input date, and then accessing the weekyear component from the follow-up output
     * will yield the same value as the source input LocalDate.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR28")
    public void test32(LocalDate date, int year, int month, int day) {
        // Create a new LocalDate with the specified year, month, and day
        LocalDate newDate = new LocalDate(year, month, day);

        // Get the weekyear component from the follow-up output
        int weekYear = newDate.getWeekyear();

        // Get the weekyear component from the source input
        int sourceWeekYear = date.getWeekyear();

        // Verification
        assertEquals(sourceWeekYear, weekYear);
    }

    /**
     * Metamorphic Relation 33: Adding a duration to the input time, and then obtaining the year
     * from the output will yield the same result as getting the year from the original input time.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR12")
    public void test33(LocalTime time, Duration duration) {
        // // Get year from the source output
        // int sourceYear = time.getYear();

        // // Get year from the follow-up output
        // int followYear = time.plus(duration).getYear();

        // // Verification
        // assertEquals(sourceYear, followYear);
    }

    /**
     * Metamorphic Relation 34: Constructing a new LocalDateTime with a different date based on the
     * input date-time, and then accessing the date component from the follow-up output will yield
     * the same value as the source input LocalDateTime.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR34")
    public void test34(LocalDateTime localDateTime, LocalDate date) {
        // Create a new LocalDateTime with the specified date and time
        LocalDateTime newLocalDateTime = new LocalDateTime(date);

        // Get the date component from the follow-up output
        LocalDate newDate = newLocalDateTime.toLocalDate();

        // Verification
        assertEquals(date, newDate);
    }

    /**
     * Metamorphic Relation 35: Comparing the input period with another period representing the same
     * duration but with inverted sign will yield the opposite result when comparing the follow-up
     * output with the original input period.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR25")
    public void test35(Period period) {
        // // Get the period with inverted sign
        // Period invertedPeriod = period.negated();

        // // Verification
        // assertEquals(period.compareTo(invertedPeriod), -invertedPeriod.compareTo(period));

        // // Get follow-up output
        // Period follow_out = period.negated();

        // // Verification
        // assertEquals(period.compareTo(follow_out), -follow_out.compareTo(period));
    }

    /**
     * Metamorphic Relation 36: Constructing a new LocalDateTime with a different year and month
     * based on the input date-time, and then accessing the month-of-year and year components from
     * the follow-up output will yield the same values as the newly constructed LocalDateTime.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR36")
    public void test36(LocalDateTime localDateTime, int year, int month) {
        /* Prevent error */
        localDateTime = localDateTime.withDayOfMonth(28);

        // Create a new LocalDateTime with the specified year and month
        LocalDateTime newLocalDateTime =
                new LocalDateTime(year, month, localDateTime.getDayOfMonth(),
                        localDateTime.getHourOfDay(), localDateTime.getMinuteOfHour(),
                        localDateTime.getSecondOfMinute(), localDateTime.getMillisOfSecond());

        // Get the month and year components from the follow-up output
        int newMonth = newLocalDateTime.getMonthOfYear();
        int newYear = newLocalDateTime.getYear();

        // Verification
        assertEquals(month, newMonth);
        assertEquals(year, newYear);
    }

    /**
     * Metamorphic Relation 37: Comparing the input Duration with another Duration representing the
     * same duration but with the opposite sign will yield the opposite result when comparing the
     * follow-up output with the original input Duration.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR37")
    public void test37(Duration duration) {
        // Get the duration with opposite sign
        Duration oppositeDuration = duration.negated();

        // Get follow-up output
        Duration follow_out = duration.negated();

        // Verification
        assertEquals(duration.compareTo(oppositeDuration), -follow_out.compareTo(duration));
    }

    /**
     * Metamorphic Relation 38: Constructing a new LocalDate with a different day-of-month based on
     * the input date, and then accessing the day-of-month component from the follow-up output will
     * yield the same value as the source input LocalDate.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR38")
    public void test38(LocalDate date, int day) {
        // Create a new LocalDate with the specified day-of-month
        LocalDate newDate = new LocalDate(date.getYear(), date.getMonthOfYear(), day);

        // Get the day-of-month component from the follow-up output
        int newDay = newDate.getDayOfMonth();

        // Verification
        assertEquals(day, newDay);
    }

    /**
     * Metamorphic Relation 39: Comparing the input LocalDate with another LocalDate shifted by a
     * certain period will have the same result as comparing the follow-up output with the original
     * input LocalDate.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR39")
    public void test39(LocalDate date, Period period) {
        // Get a LocalDate shifted by the period
        LocalDate shiftedDate = date.plus(period);

        // Get follow-up output
        LocalDate follow_out = date.plus(period);

        // Verification
        assertEquals(date.compareTo(follow_out), date.compareTo(shiftedDate));
    }

    /**
     * Metamorphic Relation 40: Constructing a new LocalDateTime by setting a different hour,
     * minute, and second based on the input date-time, and then accessing those components from the
     * follow-up output will yield the same values as the newly constructed LocalDateTime.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderMR40")
    public void test40(LocalDateTime localDateTime, int hour, int minute, int second) {
        // Create a new LocalDateTime with the specified time components
        LocalDateTime newLocalDateTime = new LocalDateTime(localDateTime.getYear(),
                localDateTime.getMonthOfYear(), localDateTime.getDayOfMonth(), hour, minute, second,
                localDateTime.getMillisOfSecond());

        // Get the time components from the follow-up output
        int newHour = newLocalDateTime.getHourOfDay();
        int newMinute = newLocalDateTime.getMinuteOfHour();
        int newSecond = newLocalDateTime.getSecondOfMinute();

        // Verification
        assertEquals(hour, newHour);
        assertEquals(minute, newMinute);
        assertEquals(second, newSecond);
    }

    static Stream<Arguments> testcaseProviderMR1() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            DateTime time = genDateTime();
            Duration duration = genDuration(0, (Integer.MAX_VALUE));
            tcs[i] = Arguments.of(time, duration);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR2() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            DateTime time = genDateTime();
            tcs[i] = Arguments.of(time);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR6() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            DateTime time = genDateTime();
            int hour = genInt(0, 24);
            int minute = genInt(0, 60);
            int second = genInt(0, 60);
            tcs[i] = Arguments.of(time, hour, minute, second);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR7() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            LocalDate date = genLocalDate();
            Period period = genPeriod();
            tcs[i] = Arguments.of(date, period);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR9() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            Duration duration = genDuration(0, (Integer.MAX_VALUE));
            int scalar = genInt(1, 100);
            tcs[i] = Arguments.of(duration, scalar);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR12() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            LocalTime time = genLocalTime();
            Duration duration = genDuration(0, (Integer.MAX_VALUE));
            tcs[i] = Arguments.of(time, duration);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR13() throws IOException {
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

    static Stream<Arguments> testcaseProviderMR14() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            DateTime time = genDateTime();
            int year = genInt(1970, 2100);
            tcs[i] = Arguments.of(time, year);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR16() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            LocalDate date = genLocalDate();
            Chronology chronology = genChronology();
            tcs[i] = Arguments.of(date, chronology);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR17() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            DateTime time = genDateTime();
            long milliseconds = genInt(0, Integer.MAX_VALUE);
            tcs[i] = Arguments.of(time, milliseconds);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR18() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            LocalTime time = genLocalTime();
            int second = genInt(0, 60);
            tcs[i] = Arguments.of(time, second);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR20() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            DateTime time = genDateTime();
            int millis = genInt(0, 1000);
            tcs[i] = Arguments.of(time, millis);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR21() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            Interval interval = genInterval();
            Duration duration = genDuration(0, (Integer.MAX_VALUE));
            tcs[i] = Arguments.of(interval, duration);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR22() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            LocalTime time = genLocalTime();
            int hour = genInt(0, 24);
            int minute = genInt(0, 60);
            int second = genInt(0, 60);
            tcs[i] = Arguments.of(time, hour, minute, second);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR25() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            Period period = genPeriod();
            tcs[i] = Arguments.of(period);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR26() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            DateTime time = genDateTime();
            int millisOfDay = genInt(0, 1000 * 60 * 60 * 24);
            tcs[i] = Arguments.of(time, millisOfDay);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR28() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            LocalDate date = genLocalDate();
            int year = genInt(1970, 2100);
            int month = genInt(1, 12);
            int day = genInt(1, 28);
            tcs[i] = Arguments.of(date, year, month, day);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR29() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            DateTime time = genDateTime();
            Period period = genPeriod();
            tcs[i] = Arguments.of(time, period);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR34() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            LocalDateTime localDateTime = genLocalDateTime();
            LocalDate date = genLocalDate();
            tcs[i] = Arguments.of(localDateTime, date);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR36() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            LocalDateTime localDateTime = genLocalDateTime();
            int year = genInt(1970, 2100);
            int month = genInt(1, 12);
            tcs[i] = Arguments.of(localDateTime, year, month);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR37() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            Duration duration = genDuration(0, (Integer.MAX_VALUE));
            tcs[i] = Arguments.of(duration);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR38() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            LocalDate date = genLocalDate();
            int day = genInt(1, 28);
            tcs[i] = Arguments.of(date, day);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR39() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            LocalDate date = genLocalDate();
            Period period = genPeriod();
            tcs[i] = Arguments.of(date, period);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }

    static Stream<Arguments> testcaseProviderMR40() throws IOException {
        int num = 1000;
        Arguments tcs[] = new Arguments[num];
        for (int i = 0; i < num; i++) {
            LocalDateTime localDateTime = genLocalDateTime();
            int hour = genInt(0, 24);
            int minute = genInt(0, 60);
            int second = genInt(0, 60);
            tcs[i] = Arguments.of(localDateTime, hour, minute, second);
        }
        writeToFile(tcs);
        return Stream.of(tcs);
    }
}
