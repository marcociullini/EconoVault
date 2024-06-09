cmake_minimum_required(VERSION 3.28)
project(EconoVault)

set(CMAKE_CXX_STANDARD 11)

add_executable(EconoVault main.cpp
        Transaction.cpp
        Transaction.h
        PlannedTransaction.cpp
        PlannedTransaction.h
        TransactionFlow.cpp
        TransactionFlow.h
        Time.cpp
        Time.h
        BankAccount.cpp
        BankAccount.h
        PaymentCard.cpp
        PaymentCard.h
        CreditCard.cpp
        CreditCard.h
        DebitCard.cpp
        DebitCard.h
)
