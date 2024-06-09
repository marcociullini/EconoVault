//
// Created by ciullo on 28/05/24.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>

#include "BankAccount.h"

BankAccount::BankAccount() : balance(0.00f), paymentCards() {
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
            operations.push_back(std::make_shared<Transaction>(*transaction));
        }

        // Copia le carte di pagamento
        for (const auto &card: right.paymentCards) {
            paymentCards.push_back(std::make_shared<PaymentCard>(*card));
        }
    }
    return *this;
}

void BankAccount::addTransaction(const std::shared_ptr<Transaction> &transaction) {
    if (transaction->getType() == TransactionType::Deposit) {
        balance += transaction->getAmount();
    } else if (transaction->getType() == TransactionType::Withdrawal) {
        balance -= transaction->getAmount();
    } else if (transaction->getType() == TransactionType::Transfer) {
        balance -= transaction->getAmount();
    }
    operations.push_back(transaction);
}

void BankAccount::save(std::string file) const {
    std::ofstream outputFile(file); // Apre in modalità scrittura e da il nome al file
    std::stringstream tString; //crea un flusso di uscita di stringhe

    if (outputFile.is_open()) {
        for (const auto transaction: operations) {
            outputFile << "Transaction: " << transaction->printTransactionString();
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
    auto newCard = std::make_shared<PaymentCard>(name); // Crea una nuova carta di pagamento
    paymentCards.push_back(newCard); // Aggiungi la carta alla lista paymentCards
}

void BankAccount::printOperations() const {
    std::cout << "IBAN: " << IBAN << std::endl;
    std::cout << "Transactions: " << std::endl;
    for (const auto transaction: operations) {
        std::cout << transaction->printTransactionString() << std::endl;
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