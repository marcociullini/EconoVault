//
// Created by ciullo on 27/05/24.
//

#include <sstream>
#include "Transaction.h"

Transaction::Transaction(float a, TransactionType type) : amount(a), type(type) {

    dateTime.setTime();

}

void Transaction::printTransaction() const {
    std::cout
            << printTransactionType() /*/ << FIXME use usa printFlow() per flow */
            << ", amount:" << amount << ", time info:" << dateTime.getTime() << std::endl;
}

std::string Transaction::printTransactionString() {
    std::stringstream transaction;
    transaction << printTransactionType() /*/ << FIXME use usa printFlow() per flow */ << ", amount:" << amount
                << ", time info:" << dateTime.getTime();
    return transaction.str();
}

std::string Transaction::printTransactionType() const {
    switch (type) {
        case TransactionType::Deposit:
            return "Deposit";
        case TransactionType::Withdrawal:
            return "Withdrawal";
        case TransactionType::Transfer:
            return "Transfer";
        default:
            return "Unknown";
    }
}

std::string Transaction::printTransactionTypes() {
    std::stringstream transactionTypes;
    transactionTypes << "1. Deposit" << std::endl;
    transactionTypes << "2. Withdrawal" << std::endl;
    transactionTypes << "3. Transfer" << std::endl;
    return transactionTypes.str();
}

std::string Transaction::printDateTime() const {
    return dateTime.getTime();
}

Transaction &Transaction::operator=(const Transaction &right) {
    if (this != &right) {
        amount = right.amount;
        dateTime = right.dateTime;
        type = right.type;
    }
    return *this;
}