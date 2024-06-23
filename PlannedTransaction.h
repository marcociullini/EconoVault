//
// Created by ciullo on 27/05/24.
//

#ifndef ECONOVAULT_PLANNEDTRANSACTION_H
#define ECONOVAULT_PLANNEDTRANSACTION_H


#include "Operation.h"

class PlannedTransaction : public Operation {
public:
    explicit PlannedTransaction(float amount, OperationType type);

    virtual PlannedTransaction &operator=(const PlannedTransaction &right);

private:
    int date;

};


#endif //ECONOVAULT_PLANNEDTRANSACTION_H
