//
// Created by ciullo on 27/05/24.
//

#include "TransactionFlow.h"

TransactionFlow::TransactionFlow(bool credit, bool debit) {
    if (credit != debit) {
        this->credit = credit;
        this->debit = debit;
    }
}