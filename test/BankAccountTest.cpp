//
// Created by ciullo on 10/06/24.
//
#include "gtest/gtest.h"
#include "../BankAccount.h"

TEST(BankAccount, Constructor) {

    BankAccount test;
    ASSERT_TRUE(test.getOperations().empty());
    ASSERT_TRUE(test.getPaymentCards().empty());
    ASSERT_TRUE(test.getIban().data() != nullptr);
    ASSERT_FLOAT_EQ(test.getBalance(), 0.00);
}

TEST(BankAccount, AddTransaction) {

    BankAccount test;

    auto transaction1 = std::make_shared<Operation>(80, OperationType::Deposit);
    test.addTransaction(transaction1);
    ASSERT_EQ(test.getBalance(), 80);
    ASSERT_TRUE(test.getOperations().data() != nullptr);
    ASSERT_EQ(test.searchOperationAmount(80).size(), 1);
    ASSERT_EQ(test.getOperations().size(), 1);

    auto transaction2 = std::make_shared<Operation>(40.5, OperationType::Withdrawal);
    test.addTransaction(transaction2);
    ASSERT_NEAR(test.getBalance(), 39.5, 1e-5);
    ASSERT_EQ(test.searchOperationAmount(40.5).size(), 1);
    ASSERT_EQ(test.getOperations().size(), 2);

    auto transaction3 = std::make_shared<Operation>(20.2, OperationType::Transfer);
    test.addTransaction(transaction3);
    ASSERT_NEAR(test.getBalance(), 19.3, 1e-5);
    ASSERT_EQ(test.searchOperationAmount(20.2).size(), 1);
    ASSERT_EQ(test.getOperations().size(), 3);

}