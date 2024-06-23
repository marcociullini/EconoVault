cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 11)

#aggiungo una sottocartella dove inserirò google test
add_subdirectory(./lib/googletest)
#definisco la cartella dove si trova google test (ovvero la sottocartella)
set(gtest_SOURCE_DIR, ./lib/googletest/)
#includo gli header della libreria di google test cercandoli nella sottocartella appena creata
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#le prossime righe spiego come si crea l'eseguibile di test

#setto gli elementi tester (i file cpp della cartella di test)
set(TEST_SOURCE_FILES runAllTests.cpp BankAccountTest.cpp TransactionTest.cpp #FIXME aggiungi i file eseguibili di test!!!
)
#crea l'eseguibile con i file cpp che contengono i test (riga 14)
add_executable(runEconoVaultTests ${TEST_SOURCE_FILES})
#collega l'eseguibile di test (riga 17) con la libreria creata nell'altro CMakeLists.txt che contiene i SOURCE_FILES da testare
target_link_libraries(runEconoVaultTests gtest gtest_main ${CMAKE_PROJECT_NAME}_lib)