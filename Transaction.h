//
// Created by ciullo on 27/05/24.
//

#ifndef ECONOVAULT_TRANSACTION_H
#define ECONOVAULT_TRANSACTION_H


#include <string>
#include <ctime>
#include "TransactionType.h"

class Transaction {
public:
    explicit Transaction(float amount);

    virtual Transaction& operator =(const Transaction &right);

    //FIXME destructor that deletes type that is a TransactionType pointer

protected:
    float amount;
    std::string dateTime;
    //FIXME TransactionType* type;
};


#endif //ECONOVAULT_TRANSACTION_H
