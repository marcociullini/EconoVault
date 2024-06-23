//
// Created by ciullo on 27/05/24.
//

#ifndef ECONOVAULT_OPERATION_H
#define ECONOVAULT_OPERATION_H


#include <string>
#include <ctime>
#include <iostream>
#include "Time.h"

enum class OperationType {
    Deposit, Withdrawal, Transfer
};

class Operation {
public:
    explicit Operation(float a, OperationType type);

    Operation(const Operation &other);

    ~Operation() = default;

    virtual Operation &operator=(const Operation &right);

    virtual void printOperation() const;

    std::string printOperationString() const;

    std::string printOperationType() const;

    static std::string printOperationTypes();

    std::string printDateTime() const;

    float getAmount() const {
        return amount;
    }

    Time getDateTime() const {
        return dateTime;
    }

    OperationType getType() const {
        return type;
    }

protected:
    float amount;
    Time dateTime;
    OperationType type;
};


#endif //ECONOVAULT_OPERATION_H
