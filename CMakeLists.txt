cmake_minimum_required(VERSION 3.28)
project(EconoVault)

set(CMAKE_CXX_STANDARD 11)

add_executable(EconoVault main.cpp
        Transaction.cpp
        Transaction.h
        TransactionType.cpp
        TransactionType.h
        PlannedTransaction.cpp
        PlannedTransaction.h
        TransactionFlow.cpp
        TransactionFlow.h
        Time.cpp
        Time.h
)
