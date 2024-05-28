//
// Created by ciullo on 27/05/24.
//

#ifndef ECONOVAULT_TRANSACTIONFLOW_H
#define ECONOVAULT_TRANSACTIONFLOW_H


class TransactionFlow {
public:
    //FIXME find a nicer way to do it
    TransactionFlow(bool credit, bool debit);

private:
    bool credit;
    bool debit;
};


#endif //ECONOVAULT_TRANSACTIONFLOW_H
