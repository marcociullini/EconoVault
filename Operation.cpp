//
// Created by ciullo on 27/05/24.
//

#include <sstream>
#include "Operation.h"

Operation::Operation(float a, OperationType type) : amount(a), type(type) {

    dateTime.setTime();

}

Operation::Operation(const Operation &other) : amount(other.amount) , dateTime(other.dateTime) , type(other.type) {}

void Operation::printOperation() const {
    std::cout
            << printOperationType() /*/ << FIXME use usa printFlow() per flow */
            << ", amount:" << amount << ", time info:" << dateTime.getTime() << std::endl;
}

std::string Operation::printOperationString() const {
    std::stringstream transaction;
    transaction << printOperationType() /*/ << FIXME use usa printFlow() per flow */ << ", amount:" << amount
                << ", time info:" << dateTime.getTime();
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
        default:
            return "Unknown";
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
    return dateTime.getTime();
}

Operation &Operation::operator=(const Operation &right) {
    if (this != &right) {
        amount = right.amount;
        dateTime = right.dateTime;
        type = right.type;
    }
    return *this;
}