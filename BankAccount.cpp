//
// Created by ciullo on 28/05/24.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>

#include "BankAccount.h"

BankAccount::BankAccount() : operations(), paymentCards(), balance(0.00f) {
    // Generazione IBAN fittizio
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

BankAccount &BankAccount::operator=(const BankAccount &right) {
    if (this != &right) {
        // Copia IBAN e balance
        IBAN = right.IBAN;
        balance = right.balance;

        // Copia le transazioni
        for (const auto &transaction: right.operations) {
            operations.push_back(std::make_shared<Operation>(*transaction));
        }

        // Copia le carte di pagamento
        for (const auto &card: right.paymentCards) {
            paymentCards.push_back(std::make_shared<PaymentCard>(*card));
        }
    }
    return *this;
}

void BankAccount::addTransaction(const std::shared_ptr<Operation> &transaction) {
    if ((transaction->getType() == OperationType::Deposit) & (transaction->getAmount() > 0)) {
        balance += transaction->getAmount();
    } else if ((transaction->getType() == OperationType::Withdrawal) & (transaction->getAmount() > 0)) {
        balance -= transaction->getAmount();
    } else if ((transaction->getType() == OperationType::Transfer) & (transaction->getAmount() > 0)) {
        balance -= transaction->getAmount();
    }
    operations.push_back(transaction);
}

bool BankAccount::sameAmount(float a, float b) const {
    if (std::fabs(a - b) < 1e-5) {
        return true;
    } else
        return false;
}

/*/auto BankAccount::searchOperations(float amount) const {
    int sameOperation = 0;
    for (const auto transaction: operations) {
        if (transaction->getAmount() == amount) {
            sameOperation++;
        }
        int n ++;
    }
    if (sameOperation == 0) {
        return false;
    } else if (sameOperation == 1) {
        for (const auto transaction: operations) {
            if (transaction->getAmount() == amount) {
                return Operation a (transaction);
            }
        }
    } else {
        std::vector<Operation> sameOperations;
        for (const auto transaction: operations) {
            const Operation transactionOutput = &transaction;
            if (transaction->getAmount() == amount) {
                sameOperations.push_back(transactionOutput);
            }
        }
        return sameOperations;
    }
}*/

std::vector<std::shared_ptr<Operation>> BankAccount::searchOperationAmount(float amount) const {
    std::vector<std::shared_ptr<Operation>> result;
    bool sameElements = false;

    for (const auto &operation: operations) {
        if (sameAmount(operation->getAmount(), amount)) {
            result.push_back(operation);
            sameElements = true;
        }
    }
    if (sameElements) {
        return result;
    }
    //return false;
    return result;
}

std::vector<std::shared_ptr<Operation>> BankAccount::searchOperationDate() const {
    Time time;
    std::string userDate = time.getUserInputDate();
    std::string formattedUserDate = time.formatDate(userDate);
    std::vector<std::shared_ptr<Operation>> result;
    bool sameDate = false;

    for (const auto &transaction: operations) {
        std::string transactionDate = transaction->printDateTime();
        std::string formattedTransactionDate = time.formatDate(transactionDate);
        if (formattedTransactionDate == formattedUserDate) {
            result.push_back(transaction);
            sameDate = true;
        }
    }
    if (sameDate) {
        return result;
    }
    //return false;
    return result;
}

void BankAccount::save(std::string file) const {
    std::ofstream outputFile(file); // Opens in write mode and gives a name to the file
    std::stringstream tString; // Creates a string output stream

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

        std::cout << "Dati salvati su file: " << file << std::endl;
    } else {
        std::cerr << "Impossibile aprire il file " << file << " per la scrittura."
                  << std::endl; //FIXME trasformare in errore
    }
}

void BankAccount::addCard(std::string name) {
    auto newCard = std::make_shared<PaymentCard>(name);
    paymentCards.push_back(newCard);
}

void BankAccount::printOperations(std::vector<std::shared_ptr<Operation>> operations) const {
    std::cout << "IBAN: " << IBAN << std::endl;
    std::cout << "Transactions: " << std::endl;
    for (const auto operation: operations) {
        std::cout << operation->printOperationString() << std::endl;
    }
}

void BankAccount::printCards() const {
    std::cout << "Payment Cards: " << std::endl;
    for (const auto paymentCard: paymentCards) {
        std::cout << paymentCard->printCardString() << std::endl;
    }
}

void BankAccount::printIban() const {
    std::cout << IBAN;
}

void BankAccount::printBalance() const {
    std::cout << balance;
}