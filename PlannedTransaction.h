//
// Created by ciullo on 27/05/24.
//

#ifndef ECONOVAULT_PLANNEDTRANSACTION_H
#define ECONOVAULT_PLANNEDTRANSACTION_H


#include "Operation.h"

enum class Frequency {
    One, Daily, Weekly, Monthly, Yearly
};

class PlannedTransaction : public Operation {
public:
    PlannedTransaction(float amount, OperationType type, Date nextExecutionDate, Frequency frequency)
            : Operation(amount, type), nextExecutionDate(nextExecutionDate), frequency(frequency) {}

    Date getNextExecutionDate() const {
        return nextExecutionDate;
    }


    Frequency getFrequency() const {
        return frequency;
    }

    std::string printFrequency() const;

    std::string printOperationString() const override;

    void updateNextExecutionDate();

private:
    Date nextExecutionDate;
    Frequency frequency;
};


#endif //ECONOVAULT_PLANNEDTRANSACTION_H
