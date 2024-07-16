cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 11)

#aggiungo una sottocartella dove inserirò google test
add_subdirectory(./lib/googletest)
#definisco la cartella dove si trova google test (ovvero la sottocartella)
set(gtest_SOURCE_DIR ./lib/googletest/)
#includo gli header della libreria di google test cercandoli nella sottocartella appena creata
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#le prossime righe spiego come si crea l'eseguibile di test

#setto gli elementi tester (i file cpp della cartella di test)
set(TEST_SOURCE_FILES runAllTests.cpp BankAccountTest.cpp TransactionTest.cpp
        PlannedTransactionTest.cpp
        DateTest.cpp
)
#crea l'eseguibile con i file cpp che contengono i test (riga 14)
add_executable(runAllTests ${TEST_SOURCE_FILES})
#crea l'eseguibile con il singolo file cpp di test di BankAccount
add_executable(runBankAccountTest BankAccountTest.cpp)
#crea l'eseguibile con il singolo file cpp di test di TransactionTest
add_executable(runTransactionTest TransactionTest.cpp)
#crea l'eseguibile con il singolo file cpp di test di PlannedTransactionTest
add_executable(runPlannedTransactionTest PlannedTransactionTest.cpp)
#crea l'eseguibile con il singolo file cpp di test di DateTest
add_executable(runDateTest DateTest.cpp)
#collega l'eseguibile di test (riga 19) con la libreria creata nell'altro CMakeLists.txt che contiene i SOURCE_FILES da testare
target_link_libraries(runAllTests gtest gtest_main ${CMAKE_PROJECT_NAME}_lib)
#collega l'eseguibile di test (riga 21) con la libreria creata nell'altro CMakeLists.txt che contiene i SOURCE_FILES da testare
target_link_libraries(runBankAccountTest gtest gtest_main ${CMAKE_PROJECT_NAME}_lib)
#collega l'eseguibile di test (riga 23) con la libreria creata nell'altro CMakeLists.txt che contiene i SOURCE_FILES da testare
target_link_libraries(runTransactionTest gtest gtest_main ${CMAKE_PROJECT_NAME}_lib)
#collega l'eseguibile di test (riga 25) con la libreria creata nell'altro CMakeLists.txt che contiene i SOURCE_FILES da testare
target_link_libraries(runPlannedTransactionTest gtest gtest_main ${CMAKE_PROJECT_NAME}_lib)
#collega l'eseguibile di test (riga 27) con la libreria creata nell'altro CMakeLists.txt che contiene i SOURCE_FILES da testare
target_link_libraries(runDateTest gtest gtest_main ${CMAKE_PROJECT_NAME}_lib)
