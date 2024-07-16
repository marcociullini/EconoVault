//
// Created by ciullo on 10/06/24.
//
#include <fstream>
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

    //Valid transactions
    auto transaction1 = std::make_shared<Operation>(160, OperationType::Deposit);
    test.addTransaction(transaction1);
    ASSERT_EQ(test.getBalance(), 160);
    ASSERT_EQ(test.getOperations().size(), 1);

    auto transaction2 = std::make_shared<Operation>(40.5, OperationType::Withdrawal);
    test.addTransaction(transaction2);
    ASSERT_NEAR(test.getBalance(), 119.5, 1e-5);
    ASSERT_EQ(test.getOperations().size(), 2);

    auto transaction3 = std::make_shared<Operation>(20.2, OperationType::Transfer);
    test.addTransaction(transaction3);
    ASSERT_NEAR(test.getBalance(), 99.3, 1e-5);
    ASSERT_EQ(test.getOperations().size(), 3);

    // Invalid transactions (should throw exceptions)
    // Negative amount
    ASSERT_THROW({
                     auto invalidTransaction1 = std::make_shared<Operation>(-50, OperationType::Deposit);
                 }, std::out_of_range);

    // Zero amount
    ASSERT_THROW({
                     auto invalidTransaction2 = std::make_shared<Operation>(0, OperationType::Withdrawal);
                 }, std::out_of_range);

    // Withdrawal exceeding balance
    ASSERT_THROW({
                     BankAccount testE;

                     //Valid transactions
                     auto invalidTransaction1 = std::make_shared<Operation>(160, OperationType::Deposit);
                     testE.addTransaction(invalidTransaction1);

                     auto invalidTransaction2 = std::make_shared<Operation>(200, OperationType::Withdrawal);
                     testE.addTransaction(invalidTransaction2);
                 }, std::runtime_error);

    // Verify that invalid transactions were not added
    ASSERT_EQ(test.getOperations().size(), 3);
    ASSERT_NEAR(test.getBalance(), 99.3, 1e-5);
}

TEST(BankAccount, SearchTransactionAmount) {

    BankAccount test;

    //Valid search
    auto transaction1 = std::make_shared<Operation>(160, OperationType::Deposit);
    test.addTransaction(transaction1);
    ASSERT_EQ(test.searchOperationAmount(160).size(), 1);

    auto transaction2 = std::make_shared<Operation>(40.5, OperationType::Withdrawal);
    test.addTransaction(transaction2);
    ASSERT_EQ(test.searchOperationAmount(40.5).size(), 1);

    auto transaction3 = std::make_shared<Operation>(20.2, OperationType::Transfer);
    test.addTransaction(transaction3);
    ASSERT_EQ(test.searchOperationAmount(20.2).size(), 1);

    auto transaction4 = std::make_shared<Operation>(20.2, OperationType::Withdrawal);
    test.addTransaction(transaction3);
    ASSERT_EQ(test.searchOperationAmount(20.2).size(),
              2);

    // Invalid search (should throw exceptions)
    // Test searching for negative amount
    ASSERT_THROW({
                     test.searchOperationAmount(-50);
                 }, std::invalid_argument);

    // Test searching for zero amount (should throw an exception)
    ASSERT_THROW({
                     test.searchOperationAmount(0);
                 }, std::invalid_argument);
}

TEST(BankAccount, SearchTransactionDate) {

    BankAccount test;

    Date currentDate;  // Get current date

    // Valid search
    auto transaction1 = std::make_shared<Operation>(160, OperationType::Deposit);
    test.addTransaction(transaction1);
    ASSERT_EQ(test.searchOperationDate(currentDate).size(), 1);

    auto transaction2 = std::make_shared<Operation>(40.5, OperationType::Withdrawal);
    test.addTransaction(transaction2);
    ASSERT_EQ(test.searchOperationDate(currentDate).size(), 2);

    auto transaction3 = std::make_shared<Operation>(20.2, OperationType::Transfer);
    test.addTransaction(transaction3);
    ASSERT_EQ(test.searchOperationDate(currentDate).size(), 3);

    auto transaction4 = std::make_shared<Operation>(20.2, OperationType::Withdrawal);
    test.addTransaction(transaction4);
    ASSERT_EQ(test.searchOperationDate(currentDate).size(), 4);

    // Test searching for a future date (should return empty vector)
    Date futureDate(31, 12, 2098);
    ASSERT_EQ(test.searchOperationDate(futureDate).size(), 0);

    // Invalid search (should throw exceptions)
    // Test searching for an invalid date (should throw an exception)
    ASSERT_THROW({
                     Date invalidDate(31, 2, 2024);  // Invalid date: February 31st
                     test.searchOperationDate(invalidDate);
                 }, std::out_of_range);
}

TEST(BankAccount, SearchTransactionType) {

    BankAccount test;

    // Valid search
    auto transaction1 = std::make_shared<Operation>(160, OperationType::Deposit);
    test.addTransaction(transaction1);
    ASSERT_EQ(test.searchOperationType(OperationType::Deposit).size(), 1);

    auto transaction2 = std::make_shared<Operation>(40.5, OperationType::Withdrawal);
    test.addTransaction(transaction2);
    ASSERT_EQ(test.searchOperationType(OperationType::Withdrawal).size(), 1);

    auto transaction3 = std::make_shared<Operation>(20.2, OperationType::Transfer);
    test.addTransaction(transaction3);
    ASSERT_EQ(test.searchOperationType(OperationType::Transfer).size(), 1);

    auto transaction4 = std::make_shared<Operation>(20.2, OperationType::Withdrawal);
    test.addTransaction(transaction4);
    ASSERT_EQ(test.searchOperationType(OperationType::Withdrawal).size(),
              2);
}

TEST(BankAccount, CancelOperations) {

    BankAccount test;

    // Adding transactions
    auto transaction1 = std::make_shared<Operation>(200.10, OperationType::Deposit);
    test.addTransaction(transaction1);
    ASSERT_NEAR(test.getBalance(), 200.10, 1e-5);

    auto transaction2 = std::make_shared<Operation>(50.30, OperationType::Withdrawal);
    test.addTransaction(transaction2);
    ASSERT_NEAR(test.getBalance(), 149.80, 1e-5);

    auto transaction3 = std::make_shared<Operation>(47.10, OperationType::Transfer);
    test.addTransaction(transaction3);
    ASSERT_NEAR(test.getBalance(), 102.70, 1e-5);

    auto transaction4 = std::make_shared<Operation>(99.90, OperationType::Withdrawal);
    test.addTransaction(transaction4);
    ASSERT_NEAR(test.getBalance(), 2.80, 1e-5);

    // Deleting transactions
    std::vector<std::shared_ptr<Operation>> cancel1 = {transaction2};
    test.cancelOperations(cancel1);
    ASSERT_NEAR(test.getBalance(), 53.10, 1e-5);
    ASSERT_EQ(test.getOperations().size(), 3);

    std::vector<std::shared_ptr<Operation>> cancel2 = {transaction3, transaction4};
    test.cancelOperations(cancel2);
    ASSERT_NEAR(test.getBalance(), 200.1, 1e-5);
    ASSERT_EQ(test.getOperations().size(), 1);

    std::vector<std::shared_ptr<Operation>> cancel3 = {transaction1};
    test.cancelOperations(cancel3);
    ASSERT_NEAR(test.getBalance(), 0, 1e-5);
    ASSERT_EQ(test.getOperations().size(), 0);

    // Invalid delete (should throw exceptions)
    // Test cancelling transactions that would result in negative balance
    ASSERT_THROW({
                     BankAccount testNegative;
                     auto transactionDeposit = std::make_shared<Operation>(100, OperationType::Deposit);
                     auto transactionWithdraw = std::make_shared<Operation>(200, OperationType::Withdrawal);
                     testNegative.addTransaction(transactionDeposit);
                     testNegative.addTransaction(transactionWithdraw);
                     std::vector<std::shared_ptr<Operation>> invalidCancel = {transactionDeposit};
                     testNegative.cancelOperations(invalidCancel);
                 }, std::runtime_error);
}

TEST(BankAccount, AddPlannedTransaction) {

    BankAccount test;

    Date futureDate1(1, 1, 2099);

    // Valid planned transactions
    auto plannedTransaction1 = std::make_shared<PlannedTransaction>(100, OperationType::Deposit, futureDate1,
                                                                    Frequency::Monthly);
    test.addPlannedTransaction(plannedTransaction1);
    ASSERT_EQ(test.getPlannedTransactions().size(), 1);

    Date futureDate2(15, 6, 2099);
    auto plannedTransaction2 = std::make_shared<PlannedTransaction>(50.5, OperationType::Withdrawal, futureDate2,
                                                                    Frequency::Weekly);
    test.addPlannedTransaction(plannedTransaction2);
    ASSERT_EQ(test.getPlannedTransactions().size(), 2);

    Date futureDate3(31, 12, 2099);
    auto plannedTransaction3 = std::make_shared<PlannedTransaction>(1000, OperationType::Transfer, futureDate3,
                                                                    Frequency::Yearly);
    test.addPlannedTransaction(plannedTransaction3);
    ASSERT_EQ(test.getPlannedTransactions().size(), 3);

    // Invalid planned transactions (should throw exceptions)
    // Test adding a transaction with an invalid date
    ASSERT_THROW({
                     Date pastDate(1, 1, 2020);
                     auto invalidTransaction = std::make_shared<PlannedTransaction>(200, OperationType::Deposit,
                                                                                    pastDate,
                                                                                    Frequency::Daily);
                     test.addPlannedTransaction(invalidTransaction);
                 }, std::out_of_range);

    // Verify that the invalid transaction was not added
    ASSERT_EQ(test.getPlannedTransactions().size(), 3);

    // Test adding a transaction with an invalid amount
    ASSERT_THROW({
                     Date validDate(1, 1, 2100);
                     auto invalidAmountTransaction = std::make_shared<PlannedTransaction>(-100, OperationType::Deposit,
                                                                                          validDate,
                                                                                          Frequency::Monthly);
                     test.addPlannedTransaction(invalidAmountTransaction);
                 }, std::out_of_range);

    // Verify that the invalid transaction was not added
    ASSERT_EQ(test.getPlannedTransactions().size(), 3);
}

TEST(BankAccount, SearchPlannedAmount) {

    BankAccount test;

    Date futureDate1(1, 1, 2099);
    Date futureDate2(2, 2, 2099);

    // Valid search
    auto plannedTransaction1 = std::make_shared<PlannedTransaction>(100, OperationType::Withdrawal, futureDate1, Frequency::Daily);
    test.addPlannedTransaction(plannedTransaction1);
    ASSERT_EQ(test.searchPlannedDate(100).size(), 1);

    auto plannedTransaction2 = std::make_shared<PlannedTransaction>(200, OperationType::Withdrawal, futureDate1, Frequency::Weekly);
    test.addPlannedTransaction(plannedTransaction2);
    ASSERT_EQ(test.searchPlannedDate(200).size(), 1);

    auto plannedTransaction3 = std::make_shared<PlannedTransaction>(300, OperationType::Withdrawal, futureDate2, Frequency::Monthly);
    test.addPlannedTransaction(plannedTransaction3);
    ASSERT_EQ(test.searchPlannedDate(300).size(), 1);

    auto plannedTransaction4 = std::make_shared<PlannedTransaction>(400, OperationType::Withdrawal, futureDate2, Frequency::Yearly);
    test.addPlannedTransaction(plannedTransaction4);
    ASSERT_EQ(test.searchPlannedDate(400).size(), 1);

    auto plannedTransaction5 = std::make_shared<PlannedTransaction>(200, OperationType::Withdrawal, futureDate2, Frequency::Monthly);
    test.addPlannedTransaction(plannedTransaction5);
    ASSERT_EQ(test.searchPlannedDate(200).size(), 2);

    // Test searching for a wrong amount (should return empty vector)
    ASSERT_EQ(test.searchPlannedDate(500).size(), 0);

    // Invalid search (should throw exceptions)
    // Test searching for negative amount (should throw an exception)
    ASSERT_THROW({
                     test.searchPlannedDate(-100);
                 }, std::invalid_argument);

    // Test searching for zero amount (should throw an exception)
    ASSERT_THROW({
                     test.searchPlannedDate(0);
                 }, std::invalid_argument);
}

TEST(BankAccount, SearchPlannedDate) {

    BankAccount test;

    Date futureDate1(1, 1, 2099);
    Date futureDate2(2, 2, 2099);

    Date currentDate;

    // Valid search
    auto plannedTransaction1 = std::make_shared<PlannedTransaction>(100, OperationType::Withdrawal, futureDate1, Frequency::Daily);
    test.addPlannedTransaction(plannedTransaction1);
    ASSERT_EQ(test.searchPlannedDate(currentDate).size(), 1);

    auto plannedTransaction2 = std::make_shared<PlannedTransaction>(200, OperationType::Withdrawal, futureDate1, Frequency::Weekly);
    test.addPlannedTransaction(plannedTransaction2);
    ASSERT_EQ(test.searchPlannedDate(currentDate).size(), 2);

    auto plannedTransaction3 = std::make_shared<PlannedTransaction>(300, OperationType::Withdrawal, futureDate2, Frequency::Monthly);
    test.addPlannedTransaction(plannedTransaction3);
    ASSERT_EQ(test.searchPlannedDate(currentDate).size(), 3);

    auto plannedTransaction4 = std::make_shared<PlannedTransaction>(400, OperationType::Withdrawal, futureDate2, Frequency::Yearly);
    test.addPlannedTransaction(plannedTransaction4);
    ASSERT_EQ(test.searchPlannedDate(currentDate).size(), 4);

    auto plannedTransaction5 = std::make_shared<PlannedTransaction>(200, OperationType::Withdrawal, futureDate2, Frequency::Monthly);
    test.addPlannedTransaction(plannedTransaction5);
    ASSERT_EQ(test.searchPlannedDate(currentDate).size(), 5);

    ASSERT_EQ(test.searchPlannedDate(Date(12, 12, 2099)).size(), 0);

    // Invalid search (should throw exceptions)
    // Test searching for a past date
    ASSERT_THROW({
                     test.searchPlannedDate(Date(1, 1, 2000));
                 }, std::out_of_range);

    // Test searching for an invalid date (should throw an exception)
    ASSERT_THROW({
                     test.searchPlannedDate(Date(31, 2, 2099));  // Invalid date: February 31st
                 }, std::out_of_range);
}

TEST(BankAccount, SearchPlannedNextExecutionDate) {

    BankAccount test;

    Date futureDate1(1, 1, 2099);
    Date futureDate2(2, 2, 2099);

    // Valid search
    auto plannedTransaction1 = std::make_shared<PlannedTransaction>(100, OperationType::Withdrawal, futureDate1, Frequency::Daily);
    test.addPlannedTransaction(plannedTransaction1);
    ASSERT_EQ(test.searchPlannedNextExecutionDate(futureDate1).size(), 1);

    auto plannedTransaction2 = std::make_shared<PlannedTransaction>(200, OperationType::Withdrawal, futureDate1, Frequency::Weekly);
    test.addPlannedTransaction(plannedTransaction2);
    ASSERT_EQ(test.searchPlannedNextExecutionDate(futureDate1).size(), 2);

    auto plannedTransaction3 = std::make_shared<PlannedTransaction>(300, OperationType::Withdrawal, futureDate2, Frequency::Monthly);
    test.addPlannedTransaction(plannedTransaction3);
    ASSERT_EQ(test.searchPlannedNextExecutionDate(futureDate2).size(), 1);

    auto plannedTransaction4 = std::make_shared<PlannedTransaction>(400, OperationType::Withdrawal, futureDate2, Frequency::Yearly);
    test.addPlannedTransaction(plannedTransaction4);
    ASSERT_EQ(test.searchPlannedNextExecutionDate(futureDate2).size(), 2);

    auto plannedTransaction5 = std::make_shared<PlannedTransaction>(200, OperationType::Withdrawal, futureDate2, Frequency::Monthly);
    test.addPlannedTransaction(plannedTransaction5);
    ASSERT_EQ(test.searchPlannedNextExecutionDate(futureDate2).size(), 3);

    // Test searching for a wrong date (should return empty vector)
    ASSERT_EQ(test.searchPlannedNextExecutionDate(Date(3, 3, 2099)).size(), 0);

    // Invalid search (should throw exceptions)
    // Test searching for a past date
    ASSERT_THROW({
                     test.searchPlannedNextExecutionDate(Date(1, 1, 2000));
                 }, std::out_of_range);

    // Test searching for an invalid date
    ASSERT_THROW({
                     test.searchPlannedNextExecutionDate(Date(31, 2, 2099));  // Invalid date: February 31st
                 }, std::out_of_range);
}

TEST(BankAccount, RemovePlannedTransaction) {

    BankAccount test;

    Date futureDate1(1, 1, 2099);
    Date futureDate2(2, 2, 2099);

    // Adding planned transactions
    auto plannedTransaction1 = std::make_shared<PlannedTransaction>(100, OperationType::Withdrawal, futureDate1, Frequency::Daily);
    test.addPlannedTransaction(plannedTransaction1);

    auto plannedTransaction2 = std::make_shared<PlannedTransaction>(200, OperationType::Withdrawal, futureDate1, Frequency::Weekly);
    test.addPlannedTransaction(plannedTransaction2);

    auto plannedTransaction3 = std::make_shared<PlannedTransaction>(300, OperationType::Withdrawal, futureDate2, Frequency::Monthly);
    test.addPlannedTransaction(plannedTransaction3);

    auto plannedTransaction4 = std::make_shared<PlannedTransaction>(400, OperationType::Withdrawal, futureDate2, Frequency::Yearly);
    test.addPlannedTransaction(plannedTransaction4);

    auto plannedTransaction5 = std::make_shared<PlannedTransaction>(200, OperationType::Withdrawal, futureDate2, Frequency::Monthly);
    test.addPlannedTransaction(plannedTransaction5);

    ASSERT_EQ(test.getPlannedTransactions().size(), 5);

    // Deleting planned transactions
    std::vector<std::shared_ptr<PlannedTransaction>> cancel1 = {plannedTransaction1};
    test.removePlannedTransaction(cancel1);
    ASSERT_EQ(test.getPlannedTransactions().size(), 4);

    std::vector<std::shared_ptr<PlannedTransaction>> cancel2 = {plannedTransaction2, plannedTransaction3};
    test.removePlannedTransaction(cancel2);
    ASSERT_EQ(test.getPlannedTransactions().size(), 2);

    std::vector<std::shared_ptr<PlannedTransaction>> cancel3 = {plannedTransaction4, plannedTransaction5};
    test.removePlannedTransaction(cancel3);
    ASSERT_EQ(test.getPlannedTransactions().size(), 0);
}

TEST(BankAccount, ExecutePlannedTransactions) {

    BankAccount test;

    Date currentDate;

    // Adding transactions
    auto transaction1 = std::make_shared<Operation>(1500, OperationType::Deposit);
    test.addTransaction(transaction1);

    // Adding planned transactions and execute
    auto plannedTransaction1 = std::make_shared<PlannedTransaction>(100, OperationType::Withdrawal, currentDate, Frequency::One);
    ASSERT_EQ(test.getPlannedTransactions().size(), 0);
    test.addPlannedTransaction(plannedTransaction1);
    ASSERT_EQ(test.getPlannedTransactions().size(), 1);
    test.executePlannedTransactions();
    ASSERT_NEAR(test.getBalance(), 1400, 1e-5);
    ASSERT_EQ(test.getOperations().size(), 2);
    ASSERT_EQ(test.getPlannedTransactions().size(), 0);

    auto plannedTransaction2 = std::make_shared<PlannedTransaction>(100, OperationType::Withdrawal, currentDate, Frequency::Daily);
    test.addPlannedTransaction(plannedTransaction2);
    ASSERT_EQ(test.getPlannedTransactions().size(), 1);
    test.executePlannedTransactions();
    ASSERT_NEAR(test.getBalance(), 1300, 1e-5);
    ASSERT_EQ(test.getOperations().size(), 3);
    ASSERT_EQ(test.getPlannedTransactions().size(), 1);

    auto plannedTransaction3 = std::make_shared<PlannedTransaction>(200, OperationType::Withdrawal, currentDate, Frequency::Weekly);
    test.addPlannedTransaction(plannedTransaction3);
    ASSERT_EQ(test.getPlannedTransactions().size(), 2);
    test.executePlannedTransactions();
    ASSERT_NEAR(test.getBalance(), 1100, 1e-5);
    ASSERT_EQ(test.getOperations().size(), 4);
    ASSERT_EQ(test.getPlannedTransactions().size(), 2);

    auto plannedTransaction4 = std::make_shared<PlannedTransaction>(300, OperationType::Withdrawal, currentDate, Frequency::Monthly);
    test.addPlannedTransaction(plannedTransaction4);
    ASSERT_EQ(test.getPlannedTransactions().size(), 3);
    test.executePlannedTransactions();
    ASSERT_NEAR(test.getBalance(), 800, 1e-5);
    ASSERT_EQ(test.getOperations().size(), 5);
    ASSERT_EQ(test.getPlannedTransactions().size(), 3);

    auto plannedTransaction5 = std::make_shared<PlannedTransaction>(400, OperationType::Withdrawal, currentDate, Frequency::Yearly);
    test.addPlannedTransaction(plannedTransaction5);
    ASSERT_EQ(test.getPlannedTransactions().size(), 4);
    test.executePlannedTransactions();
    ASSERT_NEAR(test.getBalance(), 400, 1e-5);
    ASSERT_EQ(test.getOperations().size(), 6);
    ASSERT_EQ(test.getPlannedTransactions().size(), 4);

    auto plannedTransaction6 = std::make_shared<PlannedTransaction>(200, OperationType::Withdrawal, currentDate, Frequency::Monthly);
    test.addPlannedTransaction(plannedTransaction6);
    ASSERT_EQ(test.getPlannedTransactions().size(), 5);
    test.executePlannedTransactions();
    ASSERT_NEAR(test.getBalance(), 200, 1e-5);
    ASSERT_EQ(test.getOperations().size(), 7);
    ASSERT_EQ(test.getPlannedTransactions().size(), 5);
}

TEST(BankAccount, Save) {

BankAccount test;

auto transaction1 = std::make_shared<Operation>(100, OperationType::Deposit);
test.addTransaction(transaction1);
test.addCard("Test Card");

test.save("test_account.txt");

std::ifstream file("test_account.txt");
ASSERT_TRUE(file.good());
std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
ASSERT_TRUE(content.find("Operation: Deposit") != std::string::npos);
ASSERT_TRUE(content.find("Payment Cards: Card Name: Test Card") != std::string::npos);
ASSERT_TRUE(content.find("Current balance: 100") != std::string::npos);
}