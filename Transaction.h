//
// Created by ciullo on 27/05/24.
//

#ifndef ECONOVAULT_TRANSACTION_H
#define ECONOVAULT_TRANSACTION_H


#include <string>
#include <ctime>
#include <iostream>
#include "TransactionType.h"

class Transaction {
public:
    explicit Transaction(float amount);

    //FIXME destructor that deletes type that is a TransactionType pointer

    virtual Transaction &operator=(const Transaction &right);

    std::string getdateTime() const {
        return dateTime;
    }

    virtual void printTransaction() const {
        std::cout
                << "Transaction: "  /*/ << FIXME use printTransactionType() per transactionType */ /*/ << FIXME use usa printFlow() per flow */
                << ", amount: " << amount << ", time info: " << dateTime << std::endl;
    }

protected:
    float amount;
    std::string dateTime;
    //FIXME TransactionType* type;
    //FIXME transactionFlow flow;
};


#endif //ECONOVAULT_TRANSACTION_H
