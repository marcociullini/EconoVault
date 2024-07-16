//
// Created by ciullo on 16/07/24.
//
#include "gtest/gtest.h"
#include "../Date.h"

TEST(Date, Constructor) {
    EXPECT_NO_THROW(Date());
    EXPECT_NO_THROW(Date(1, 1, 2025));
    EXPECT_THROW(Date(32, 1, 2025), std::out_of_range);
    EXPECT_THROW(Date(1, 13, 2025), std::out_of_range);
    EXPECT_THROW(Date(1, 1, 1999), std::out_of_range);
    EXPECT_THROW(Date(31, 4, 2025), std::out_of_range); // April 31st doesn't exist
    EXPECT_THROW(Date(29, 2, 2025), std::out_of_range); // February 29th in a non-leap year
    EXPECT_THROW(Date(0, 1, 2025), std::out_of_range); // Day 0 doesn't exist
    EXPECT_THROW(Date(1, 0, 2025), std::out_of_range); // Month 0 doesn't exist
    EXPECT_THROW(Date(1, 1, 2101), std::out_of_range); // Year beyond upper limit
}

TEST(Date, IsLeapYear) {
    ASSERT_TRUE(Date::isLeapYear(2024));
    ASSERT_FALSE(Date::isLeapYear(2025));
    ASSERT_TRUE(Date::isLeapYear(2000));
    ASSERT_FALSE(Date::isLeapYear(1900));
    ASSERT_FALSE(Date::isLeapYear(2100)); // Non-leap century year
    ASSERT_TRUE(Date::isLeapYear(2400)); // Leap century year
}

TEST(Date, GetMaxDays) {
    ASSERT_EQ(Date::getMaxDays(2, 2024), 29);
    ASSERT_EQ(Date::getMaxDays(2, 2025), 28);
    ASSERT_EQ(Date::getMaxDays(4, 2025), 30);
    ASSERT_EQ(Date::getMaxDays(12, 2025), 31);
}

TEST(Date, CheckFutureDate) {

    Date currentDate;

    Date futureDate(1, 1, 2099);
    EXPECT_TRUE(Date::checkFutureDate(futureDate));
    EXPECT_THROW(Date::checkFutureDate(currentDate), std::out_of_range);
    EXPECT_THROW(Date::checkFutureDate(Date(1, 1, 2000)), std::out_of_range);
}

TEST(Date, FormatDate) {

    Date date(15, 7, 2025);

    ASSERT_EQ(Date::formatDate(date), "2025-07-15");
    EXPECT_THROW(Date::formatDate(Date(31, 2, 2025)), std::out_of_range); // Invalid date
}

TEST(Date, AddDays) {

    Date date(1, 1, 2025);

    Date newDate = date.addDays(31);

    ASSERT_EQ(newDate.getDateTime(), Date(1, 2, 2025).getDateTime());
    EXPECT_THROW(date.addDays(365 * 77), std::out_of_range); // Adding days beyond upper limit
}

TEST(Date, AddMonths) {

    Date date(1, 1, 2025);

    Date newDate = date.addMonths(12);

    ASSERT_EQ(newDate.getDateTime(), Date(1, 1, 2026).getDateTime());
    EXPECT_THROW(date.addMonths(12 * 77), std::out_of_range); // Adding months beyond upper limit
}

TEST(Date, AddYears) {

    Date date(1, 1, 2025);

    Date newDate = date.addYears(1);

    ASSERT_EQ(newDate.getDateTime(), Date(1, 1, 2026).getDateTime());
    EXPECT_THROW(date.addYears(77), std::out_of_range); // Adding years beyond upper limit
}