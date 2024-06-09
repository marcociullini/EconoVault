//
// Created by ciullo on 28/05/24.
//

#ifndef ECONOVAULT_BANKACCOUNT_H
#define ECONOVAULT_BANKACCOUNT_H

#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include "Transaction.h"
#include "PaymentCard.h"

class BankAccount {
public:
    BankAccount();

    ~BankAccount();

    BankAccount &operator=(const BankAccount &right);

    void addTransaction(const std::shared_ptr<Transaction> &transaction);

    void save(std::string file) const;

    void addCard(std::string name);

    void printOperations() const;

    void printCards() const;

    void printIban() const;


private:
    std::vector<std::shared_ptr<Transaction>> operations; //shared_ptr altrimenti escono fuori di scopo nello switch e non riesco mai a salvarle nel main
    std::list<std::shared_ptr<PaymentCard>> paymentCards;
    std::string IBAN;
    float balance;
    //FIXME add overdraft?

};


#endif //ECONOVAULT_BANKACCOUNT_H
