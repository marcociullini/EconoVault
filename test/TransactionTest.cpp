//
// Created by ciullo on 10/06/24.
//
#include "gtest/gtest.h"
#include "../Operation.h"

TEST(Operation, Constructor) {

    Operation transaction1(20.20, OperationType::Deposit);
    ASSERT_NEAR(transaction1.getAmount(), 20.20, 1e-5);
    ASSERT_EQ(transaction1.getType(), OperationType::Deposit);

    Operation transaction2(40.40, OperationType::Withdrawal);
    ASSERT_NEAR(transaction2.getAmount(), 40.40, 1e-5);
    ASSERT_EQ(transaction2.getType(), OperationType::Withdrawal);

    Operation transaction3(60.60, OperationType::Transfer);
    ASSERT_NEAR(transaction3.getAmount(), 60.60, 1e-5);
    ASSERT_EQ(transaction3.getType(), OperationType::Transfer);
}