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

class BankAccount {
public:
    BankAccount();

    ~BankAccount() = default;

    BankAccount &operator=(const BankAccount &right);

    const std::vector<std::shared_ptr<Operation>> &getOperations() const {
        return operations;
    }

    const std::list<std::shared_ptr<PaymentCard>> &getPaymentCards() const {
        return paymentCards;
    }

    const std::string &getIban() const {
        return IBAN;
    }

    float getBalance() const {
        return balance;
    }

    void addTransaction(const std::shared_ptr<Operation> &transaction);

    bool sameAmount(float a, float b) const;

    std::vector<std::shared_ptr<Operation>> searchOperationAmount(float amount) const;

    std::vector<std::shared_ptr<Operation>> searchOperationDate() const;

    void save(std::string file) const;

    void addCard(std::string name);

    void printOperations(std::vector<std::shared_ptr<Operation>> operations) const;

    void printCards() const;

    void printIban() const;

    void printBalance() const;


private:
    std::vector<std::shared_ptr<Operation>> operations; //shared_ptr altrimenti escono fuori di scopo nello switch e non riesco mai a salvarle nel main
    std::list<std::shared_ptr<PaymentCard>> paymentCards;
    std::string IBAN;
    float balance;
    //FIXME add overdraft?

};


#endif //ECONOVAULT_BANKACCOUNT_H
