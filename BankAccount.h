//
// Created by ciullo on 28/05/24.
//

#ifndef ECONOVAULT_BANKACCOUNT_H
#define ECONOVAULT_BANKACCOUNT_H

#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include "Operation.h"
#include "PaymentCard.h"
#include "PlannedTransaction.h"

class BankAccount {
public:
    BankAccount();

    ~BankAccount() = default;

    const std::vector<std::shared_ptr<Operation>> &getOperations() const {
        return operations;
    }

    const std::vector<std::shared_ptr<PlannedTransaction>> &getPlannedTransactions() const {
        return plannedTransactions;
    }

    const std::list<std::shared_ptr<PaymentCard>> &getPaymentCards() const {
        return paymentCards;
    }

    const std::string &getIban() const {
        return IBAN;
    }

    double getBalance() const {
        return balance;
    }

    void addTransaction(const std::shared_ptr<Operation> &transaction);

    void addPlannedTransaction(const std::shared_ptr<PlannedTransaction>& transaction);

    void cancelOperations(const std::vector<std::shared_ptr<Operation>> &operationsToCancel);

    void removePlannedTransaction(const std::vector<std::shared_ptr<PlannedTransaction>> plannedTransactions);

    std::vector<std::shared_ptr<Operation>> searchOperationAmount(double amount) const;

    std::vector<std::shared_ptr<PlannedTransaction>> searchPlannedDate(double amount) const;

    std::vector<std::shared_ptr<Operation>> searchOperationDate(Date date) const;

    std::vector<std::shared_ptr<PlannedTransaction>> searchPlannedDate(Date date) const;

    std::vector<std::shared_ptr<PlannedTransaction>> searchPlannedNextExecutionDate(Date date) const;

    std::vector<std::shared_ptr<Operation>> searchOperationType(OperationType type) const;

    void executePlannedTransactions();

    void addCard(std::string name);

    void printOperations(const std::vector<std::shared_ptr<Operation>> &operations) const;

    void printPlannedTransactions(const std::vector<std::shared_ptr<PlannedTransaction>> &operations) const;

    void printCards() const;

    std::string printIban() const;

    std::string printBalance() const;

    void save(std::string file) const;

private:
    std::vector<std::shared_ptr<Operation>> operations; //shared_ptr because search functions uses the same elements of this vector
    std::vector<std::shared_ptr<PlannedTransaction>> plannedTransactions;
    std::list<std::shared_ptr<PaymentCard>> paymentCards;
    std::string IBAN;
    double balance;

};


#endif //ECONOVAULT_BANKACCOUNT_H
