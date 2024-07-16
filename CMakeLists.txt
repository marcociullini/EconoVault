cmake_minimum_required(VERSION 3.28)
project(EconoVault)

set(CMAKE_CXX_STANDARD 11)

#aggiunge una cartella nel processo di build
add_subdirectory(test)
#settaggio dei file sorgente
set(SOURCE_FILES Operation.cpp Operation.h PlannedTransaction.cpp PlannedTransaction.h
        BankAccount.cpp BankAccount.h PaymentCard.cpp PaymentCard.h CreditCard.cpp
        CreditCard.h DebitCard.cpp DebitCard.h Date.cpp Date.h
)
#il nome dell'eseguibile sarà quello del nome progetto e questo eseguibile avrà come file sorgente sarà solamente il main
add_executable(${CMAKE_PROJECT_NAME} main.cpp)
#aggiunta della libreria con i file sorgente settati a riga 9
add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCE_FILES})
#collego la libreria di riga 17 all'eseguibile di riga 13
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}_lib)