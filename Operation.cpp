//
// Created by ciullo on 27/05/24.
//

#include <sstream>
#include "Operation.h"

Operation::Operation(double a, OperationType type) : type(type), date(Date()) {
    if(a <= 0)
        throw std::out_of_range("Amount not valid!");
    else
        amount = a;
}

void Operation::printOperation() const {
    std::cout
            << printOperationType() << ", amount:" << amount << ", time info:" << date.getDateTime() << std::endl;
}

std::string Operation::printOperationString() const {
    std::stringstream transaction;
    transaction << printOperationType() << ", amount:" << amount
                << ", time info:" << date.getDateTime();
    return transaction.str();
}

std::string Operation::printOperationType() const {
    switch (type) {
        case OperationType::Deposit:
            return "Deposit";
        case OperationType::Withdrawal:
            return "Withdrawal";
        case OperationType::Transfer:
            return "Transfer";
    }
}

std::string Operation::printOperationTypes() {
    std::stringstream transactionTypes;
    transactionTypes << "1. Deposit" << std::endl;
    transactionTypes << "2. Withdrawal" << std::endl;
    transactionTypes << "3. Transfer" << std::endl;
    return transactionTypes.str();
}

std::string Operation::printDateTime() const {
    return date.getDateTime();
}