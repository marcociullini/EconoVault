//
// Created by ciullo on 27/05/24.
//

#ifndef ECONOVAULT_TRANSACTION_H
#define ECONOVAULT_TRANSACTION_H


#include <string>
#include <ctime>
#include <iostream>
#include "Time.h"

enum class TransactionType {
    Deposit, Withdrawal, Transfer
};

class Transaction {
public:
    explicit Transaction(float a, TransactionType type);

    ~Transaction();

    virtual Transaction &operator=(const Transaction &right);

    virtual void printTransaction() const;

    std::string printTransactionString();

    std::string printTransactionType() const;

    static std::string printTransactionTypes();

    std::string printDateTime() const;

    float getAmount() const {
        return amount;
    }

    void setAmount(float amount) {
        this->amount = amount;
    }

    const Time &getDateTime() const {
        return dateTime;
    }

    void setDateTime() {
        this->dateTime;
    }

    TransactionType getType() const {
        return type;
    }

    void setType(TransactionType type) {
        this->type = type;
    }

protected:
    float amount;
    Time dateTime;
    TransactionType type;
};


#endif //ECONOVAULT_TRANSACTION_H
