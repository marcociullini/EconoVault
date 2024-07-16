//
// Created by ciullo on 28/05/24.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>

#include "BankAccount.h"

BankAccount::BankAccount() : operations(), plannedTransactions(), paymentCards(), balance(0.00f) {
    // Generates fake IBAN
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 9);
    std::uniform_int_distribution<int> letter_dis(0, 25);
    std::uniform_int_distribution<int> first_letter_dis(0, 1);

    std::stringstream ibanStream;
    ibanStream << "IT";
    ibanStream << dis(gen) << dis(gen);
    char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    ibanStream << letters[letter_dis(gen)];
    for (int i = 0; i < 22; ++i) {
        ibanStream << dis(gen);
    }
    IBAN = ibanStream.str();

}

void BankAccount::addTransaction(const std::shared_ptr<Operation> &transaction) {
    double newBalance = balance;
    if (transaction->getType() == OperationType::Deposit) {
        newBalance += transaction->getAmount();
    } else if (transaction->getType() == OperationType::Withdrawal ||
               transaction->getType() == OperationType::Transfer) {
        newBalance -= transaction->getAmount();
    }

    if (newBalance < 0) {
        throw std::runtime_error("The transaction exceeds the available balance!");
    } else {
        balance = newBalance;
        operations.push_back(transaction);
    }
}

void BankAccount::addPlannedTransaction(const std::shared_ptr<PlannedTransaction>& transaction) {
    plannedTransactions.push_back(transaction);
}

void BankAccount::cancelOperations(const std::vector<std::shared_ptr<Operation>> &transactionsToCancel) {
    double newBalance = balance;
    for (const auto &transaction: transactionsToCancel) {
        auto it = std::find(operations.begin(), operations.end(), transaction);
        if (it != operations.end()) {
            if (transaction->getType() == OperationType::Deposit) {
                newBalance -= transaction->getAmount();
            } else {
                newBalance += transaction->getAmount();
            }
        }
    }

    if (newBalance < 0) {
        throw std::runtime_error("The cancellation exceeds the available balance!");
    }

    balance = newBalance;
    for (const auto &transaction: transactionsToCancel) {
        auto it = std::find(operations.begin(), operations.end(), transaction);
        if (it != operations.end()) {
            operations.erase(it);
        }
    }
}

void
BankAccount::removePlannedTransaction(const std::vector<std::shared_ptr<PlannedTransaction>> transactionsToCancel) {
    for (const auto &transaction: transactionsToCancel) {
        auto it = std::find(plannedTransactions.begin(), plannedTransactions.end(), transaction);
        if (it != plannedTransactions.end()) {
            plannedTransactions.erase(it);
        }
    }
}

std::vector<std::shared_ptr<Operation>> BankAccount::searchOperationAmount(double amount) const {
    if(amount <= 0){
        throw std::invalid_argument("Amount not valid!");
    }
    std::vector<std::shared_ptr<Operation>> result;

    for (const auto &operation: operations) {
        if (std::fabs(operation->getAmount() - amount) < 1e-5) {
            result.push_back(operation);
        }
    }
    return result;
}

std::vector<std::shared_ptr<PlannedTransaction>> BankAccount::searchPlannedDate(double amount) const {
    if(amount <= 0){
       throw std::invalid_argument("Amount not valid!");
    }
    std::vector<std::shared_ptr<PlannedTransaction>> result;

    for (const auto &transaction: plannedTransactions) {
        if (std::fabs(transaction->getAmount() - amount) < 1e-5) {
            result.push_back(transaction);
        }
    }
    return result;
}

std::vector<std::shared_ptr<Operation>> BankAccount::searchOperationDate(Date date) const {
    std::vector<std::shared_ptr<Operation>> result;
    std::string formattedUserDate = date.formatDate(date);

    for (const auto &transaction: operations) {
        Date transactionDate = transaction->getDateTime();
        std::string formattedTransactionDate = transactionDate.formatDate(transactionDate);
        if (formattedTransactionDate == formattedUserDate) {
            result.push_back(transaction);
        }
    }
    return result;
}

std::vector<std::shared_ptr<PlannedTransaction>> BankAccount::searchPlannedDate(Date date) const {
    std::vector<std::shared_ptr<PlannedTransaction>> result;
    std::string formattedUserDate = date.formatDate(date);

    for (const auto &transaction: plannedTransactions) {
        Date transactionDate = transaction->getDateTime();
        std::string formattedTransactionDate = transactionDate.formatDate(transactionDate);
        if (formattedTransactionDate == formattedUserDate) {
            result.push_back(transaction);
        }
    }
    return result;
}

std::vector<std::shared_ptr<PlannedTransaction>> BankAccount::searchPlannedNextExecutionDate(Date date) const {
    std::vector<std::shared_ptr<PlannedTransaction>> result;
    std::string formattedUserDate = date.formatDate(date);

    for (const auto &transaction: plannedTransactions) {
        Date transactionNextExecutionDate = transaction->getNextExecutionDate();
        std::string formattedNextExecutionDate = transactionNextExecutionDate.formatDate(transactionNextExecutionDate);
        if (formattedNextExecutionDate == formattedUserDate) {
            result.push_back(transaction);
        }
    }
    return result;
}

std::vector<std::shared_ptr<Operation>> BankAccount::searchOperationType(OperationType type) const {
    std::vector<std::shared_ptr<Operation>> result;
    for (const auto &operation: operations) {
        if (operation->getType() == type) {
            result.push_back(operation);
        }
    }
    return result;
}

void BankAccount::executePlannedTransactions() {
    Date currentDate; // Current date
    auto it = plannedTransactions.begin();
    while (it != plannedTransactions.end()) {
        if ((*it)->getNextExecutionDate() <= currentDate) {
            try {
                addTransaction(std::make_shared<Operation>((*it)->getAmount(), (*it)->getType()));

                if ((*it)->getFrequency() == Frequency::One) {
                    // Remove the transaction after execution if it's one-time
                    it = plannedTransactions.erase(it);
                } else {
                    // Update the next execution date and move to the next transaction
                    (*it)->updateNextExecutionDate();
                    ++it;
                }
            } catch (const std::exception &e) {
                throw std::runtime_error(std::string("Failed to execute planned transaction: ") + e.what());
            }
        } else {
            ++it;
        }
    }
    std::cout << "Planned transactions executed." << std::endl;
}

void BankAccount::addCard(std::string name) {
    auto newCard = std::make_shared<PaymentCard>(name);
    paymentCards.push_back(newCard);
}

void BankAccount::printOperations(const std::vector<std::shared_ptr<Operation>> &operations) const {
    std::cout << "Transactions: " << std::endl;
    for (const auto operation: operations) {
        std::cout << operation->printOperationString() << std::endl;
    }
}

void BankAccount::printPlannedTransactions(const std::vector<std::shared_ptr<PlannedTransaction>> & plannedTransactions) const {
    std::cout << "Planned Transactions: " << std::endl;
    for (const auto plannedOperation: plannedTransactions) {
        std::cout << plannedOperation->printOperationString() << std::endl;
    }
}

void BankAccount::printCards() const {
    std::cout << "Payment Cards: " << std::endl;
    for (const auto paymentCard: paymentCards) {
        std::cout << paymentCard->printCardString() << std::endl;
    }
}

std::string BankAccount::printIban() const {
    return IBAN;
}

std::string BankAccount::printBalance() const {
    std::ostringstream balanceStream;
    balanceStream << balance;
    return balanceStream.str();
}

void BankAccount::save(std::string file) const {
    // Generates the output file with the BankAccount information
    std::ofstream outputFile(file); // Opens in write mode and gives a name to the file

    if (outputFile.is_open()) {
        for (const auto transaction: operations) {
            outputFile << "Operation: " << transaction->printOperationString();
        }

        outputFile << std::endl;
        for (const auto paymentCard: paymentCards) {
            outputFile << "Payment Cards: " << paymentCard->printCardString();
        }

        outputFile << "Current balance: " << balance << std::endl;

        outputFile.close();

        std::cout << "Data saved in: " << file << std::endl;
    } else {
        std::cerr << "Impossible to open " << file << " to save."
                  << std::endl;
    }
}