//
// Created by ciullo on 16/07/24.
//
#include "gtest/gtest.h"
#include "../PlannedTransaction.h"

TEST(PlannedTransaction, UpdateNextExecutionDate) {

    Date startDate(1, 1, 2025);

    PlannedTransaction daily(100, OperationType::Deposit, startDate, Frequency::Daily);
    daily.updateNextExecutionDate();
    ASSERT_EQ(daily.getNextExecutionDate().getDateTime(), Date(2, 1, 2025).getDateTime());

    PlannedTransaction weekly(100, OperationType::Deposit, startDate, Frequency::Weekly);
    weekly.updateNextExecutionDate();
    ASSERT_EQ(weekly.getNextExecutionDate().getDateTime(), Date(8, 1, 2025).getDateTime());

    PlannedTransaction monthly(100, OperationType::Deposit, startDate, Frequency::Monthly);
    monthly.updateNextExecutionDate();
    ASSERT_EQ(monthly.getNextExecutionDate().getDateTime(), Date(1, 2, 2025).getDateTime());

    PlannedTransaction yearly(100, OperationType::Deposit, startDate, Frequency::Yearly);
    yearly.updateNextExecutionDate();
    ASSERT_EQ(yearly.getNextExecutionDate().getDateTime(), Date(1, 1, 2026).getDateTime());
}