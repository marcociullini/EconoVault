//
// Created by ciullo on 27/05/24.
//

#ifndef ECONOVAULT_TRANSACTIONTYPE_H
#define ECONOVAULT_TRANSACTIONTYPE_H


class TransactionType {
public:
    //FIXME do a performTransaction() method that operates on the (still to implement) BankAccount class
    virtual void performTransaction() = 0;

//FIXME do a printTransactionType() method
    virtual void printTransactionType() const = 0;

protected:

};


#endif //ECONOVAULT_TRANSACTIONTYPE_H
