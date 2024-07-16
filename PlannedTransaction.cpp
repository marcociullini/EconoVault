//
// Created by ciullo on 27/05/24.
//

#include <sstream>
#include "PlannedTransaction.h"

void PlannedTransaction::updateNextExecutionDate() {
    switch (frequency) {
        case Frequency::One:
            // No date update, just one time
            break;
        case Frequency::Daily:
            nextExecutionDate = nextExecutionDate.addDays(1);
            break;
        case Frequency::Weekly:
            nextExecutionDate = nextExecutionDate.addDays(7);
            break;
        case Frequency::Monthly:
            nextExecutionDate = nextExecutionDate.addMonths(1);
            break;
        case Frequency::Yearly:
            nextExecutionDate = nextExecutionDate.addYears(1);
            break;
    }
}

std::string PlannedTransaction::printFrequency() const {
    switch (frequency) {
        case Frequency::One:
            return "One";
        case Frequency::Daily:
            return "Daily";
        case Frequency::Weekly:
            return "Weekly";
        case Frequency::Monthly:
            return "Monthly";
        case Frequency::Yearly:
            return "Yearly";
    }
}

std::string PlannedTransaction::printOperationString() const {
    std::stringstream transaction;
    transaction << printOperationType() << ", amount:" << amount << ", time info:" << date.getDateTime();
    transaction << "-Next execution date: " << nextExecutionDate.getDateTime();
    transaction << "-Frequency: " << printFrequency() << std::endl;
    return transaction.str();
}