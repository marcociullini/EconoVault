//
// Created by ciullo on 27/05/24.
//

#ifndef ECONOVAULT_PLANNEDTRANSACTION_H
#define ECONOVAULT_PLANNEDTRANSACTION_H


#include "Transaction.h"

class PlannedTransaction : public Transaction {
public:
    explicit PlannedTransaction(float amount);

    virtual PlannedTransaction &operator=(const PlannedTransaction &right);

private:
    int date;

};


#endif //ECONOVAULT_PLANNEDTRANSACTION_H
