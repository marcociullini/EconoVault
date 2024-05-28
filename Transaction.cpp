//
// Created by ciullo on 27/05/24.
//

#include "Transaction.h"

Transaction::Transaction(float amount) : amount(amount) {

    dateTime = getdateTime();

    //FIXME initialize type
}


Transaction &Transaction::operator=(const Transaction &right) {
    if (this != &right) {
        amount = right.amount;
        dateTime = right.dateTime;
        //type = right.type; FIXME set the copy operator for the type variable
    }
    return *this;
}