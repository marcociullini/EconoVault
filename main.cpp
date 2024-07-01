#include <iostream>
#include "PaymentCard.h"
#include "Operation.h"
#include "BankAccount.h"

int main() {

    BankAccount *account1 = new BankAccount();

    int operationChoice;

    do {
        // Chiedi all'utente di selezionare il tipo di operazione
        std::cout << "Select operation to perform:" << std::endl;
        std::cout << "1. New transaction" << std::endl;
        std::cout << "2. Visualize transaction history" << std::endl;
        std::cout << "3. Search transaction" << std::endl;
        std::cout << "4. Share transaction history" << std::endl;
        std::cout << "5. Card operations" << std::endl;
        std::cout << "6. exit " << std::endl;
        /*/std::cout << "6. - " << std::endl;
        std::cout << "7. - " << std::endl;
        std::cout << "8. - " << std::endl;
        std::cout << "9. - " << std::endl;
        std::cout << "10. - " << std::endl;
        std::cout << "11. - " << std::endl;
        std::cout << "12. - " << std::endl;
        std::cout << "13. - " << std::endl;
        std::cout << "14. - " << std::endl;*/
        std::cin >> operationChoice;

        switch (operationChoice) {
            //1. New transaction
            case 1: {
                float amount;
                int transactionTypeChoice = 0;

                do {
                    // Chiedi all'utente di selezionare il tipo di transazione
                    std::cout << "Select transaction type:" << std::endl;
                    std::cout << Operation::printOperationTypes();
                    std::cin >> transactionTypeChoice;
                    if (transactionTypeChoice <= 0 || transactionTypeChoice >= 4)
                        std::cerr << "Invalid choice!" << std::endl;
                } while (transactionTypeChoice <= 0 || transactionTypeChoice >= 4);


                OperationType transactionType;

                // Imposta il tipo di transazione in base alla scelta dell'utente
                switch (transactionTypeChoice) {
                    case 1:
                        transactionType = OperationType::Deposit;
                        break;
                    case 2:
                        transactionType = OperationType::Withdrawal;
                        break;
                    case 3:
                        transactionType = OperationType::Transfer;
                        break;
                        /*/default:
                            std::cerr << "Invalid choice!" << std::endl;
                            break;*/
                }

                // Chiedi all'utente di inserire l'importo della transazione
                std::cout << "Enter transaction amount: ";
                std::cin >> amount;

                // Crea un nuovo shared_ptr transaction puntante la transazione creata con i valori inseriti/selezionati dall'utente
                auto transaction = std::make_shared<Operation>(amount, transactionType);

                // Aggiungi lo shared_ptr transaction al vettore transactions del BankAccount
                account1->addTransaction(transaction);

                std::cout << "Done" << std::endl;

                // Stampa la transazione
                transaction->printOperation();

                break;
            }
                //2. Visualize transaction history
            case 2:
                account1->printOperations(account1->getOperations());
                std::cout << std::endl;
                account1->printBalance();
                std::cout << std::endl;
                break;
                //3. Search transaction
            case 3:
                int searchMethodChoice;

                do {
                    std::cout << "Select search method:" << std::endl;
                    std::cout << "1. Date Search" << std::endl;
                    std::cout << "2. Amount search" << std::endl;
                    std::cin >> searchMethodChoice;
                } while (searchMethodChoice <= 0 || searchMethodChoice >= 3);

                switch (searchMethodChoice) {
                    case 1: {

                        Time date;

                        date.getUserInputDate();

                        if (account1->searchOperationDate(date.getTime()).size() > 0) {
                            std::cout << "Search result:" << std::endl;
                            account1->printOperations(account1->searchOperationDate(date.getTime()));
                        } else {
                            std::cout << "Search result:" << std::endl;
                            std::cout << "-none" << std::endl;
                        }
                        break;
                    }
                    case 2: {

                        float amount;

                        std::cout << "Insert amount:" << std::endl;
                        std::cin >> amount;

                        if (account1->searchOperationAmount(amount).size() > 0) {
                            std::cout << "Search result:" << std::endl;
                            account1->printOperations(account1->searchOperationAmount(amount));
                        } else {
                            std::cout << "Search result: -none" << std::endl;
                        }
                        break;
                    }
                }


                break;
                //4. Share transaction history
            case 4:
                account1->save(std::string("history.txt"));
                break;
                //5. Card operations
            case 5: {
                int cardOperationChoice;
                do {
                    std::cout << "Select operation to perform:" << std::endl;
                    std::cout << "1. Creation of a new Debit card" << std::endl;
                    std::cout << "2. Creation of a new Credit card" << std::endl;
                    std::cout << "3. Visualize personal cards info" << std::endl;
                    std::cin >> cardOperationChoice;
                } while (cardOperationChoice <= 0 || cardOperationChoice >= 4);

                switch (cardOperationChoice) {
                    case 1: {
                        std::string cardName;
                        std::cout << "Select a name for the card:" << std::endl;
                        std::cin >> cardName;
                        account1->addCard(cardName);
                        break;
                    }
                    case 2: {
                        std::string cardName;
                        std::cout << "Select a name for the card:" << std::endl;
                        std::cin >> cardName;
                        account1->addCard(cardName);
                        break;
                    }
                    case 3:
                        account1->printCards();
                        break;
                        /*/default:
                            std::cerr << "Invalid choice. Defaulting to Deposit." << std::endl;
                            transactionType = OperationType::Deposit;
                            break; */
                }


                break;

            }
                //6. exit
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                break;
            case 11:
                break;
            case 12:
                break;
            case 13:
                break;
            case 14:
                break;
        }
    } while (operationChoice != 5);

    account1->save("account.txt");
}
