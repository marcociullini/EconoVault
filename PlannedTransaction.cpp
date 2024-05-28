//
// Created by ciullo on 27/05/24.
//

#include "PlannedTransaction.h"

PlannedTransaction::PlannedTransaction(float amount) : Transaction(amount) {
    this->date = 1; //FIXME watch for a valid date
}

PlannedTransaction &PlannedTransaction::operator=(const PlannedTransaction &right) {
    if (this != &right) {
        Transaction::operator=(right);
        date = right.date;
    }
    return *this;
}
