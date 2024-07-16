//
// Created by ciullo on 27/05/24.
//

#ifndef ECONOVAULT_OPERATION_H
#define ECONOVAULT_OPERATION_H


#include <string>
#include <ctime>
#include <iostream>
#include "Date.h"

enum class OperationType {
    Deposit, Withdrawal, Transfer
};

class Operation {
public:
    explicit Operation(double a, OperationType type);

    ~Operation() = default;

    virtual void printOperation() const;

    virtual std::string printOperationString() const;

    std::string printOperationType() const;

    static std::string printOperationTypes();

    std::string printDateTime() const;

    double getAmount() const {
        return amount;
    }

    Date getDateTime() const {
        return date;
    }

    OperationType getType() const {
        return type;
    }

protected:
    double amount;
    Date date;
    OperationType type;
};


#endif //ECONOVAULT_OPERATION_H
