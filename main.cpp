#include <iostream>
#include "PaymentCard.h"
#include "Transaction.h"
#include "BankAccount.h"

int main() {

    BankAccount *account1 = new BankAccount();

    int operationChoice;

    do {
        // Chiedi all'utente di selezionare il tipo di operazione
        std::cout << "Select operation to perform:" << std::endl;
        std::cout << "1. New transaction" << std::endl;
        std::cout << "2. Visualize transaction history" << std::endl;
        std::cout << "3. Share transaction history" << std::endl;
        std::cout << "4. Card operations" << std::endl;
        std::cout << "5. exit " << std::endl;
        /*/std::cout << "5. - " << std::endl;
        std::cout << "6. - " << std::endl;
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
                    std::cout << Transaction::printTransactionTypes();
                    std::cin >> transactionTypeChoice;
                    if (transactionTypeChoice <= 0 || transactionTypeChoice >= 4)
                        std::cerr << "Invalid choice!" << std::endl;
                } while (transactionTypeChoice <= 0 || transactionTypeChoice >= 4);


                TransactionType transactionType;

                // Imposta il tipo di transazione in base alla scelta dell'utente
                switch (transactionTypeChoice) {
                    case 1:
                        transactionType = TransactionType::Deposit;
                        break;
                    case 2:
                        transactionType = TransactionType::Withdrawal;
                        break;
                    case 3:
                        transactionType = TransactionType::Transfer;
                        break;
                        /*/default:
                            std::cerr << "Invalid choice!" << std::endl;
                            break;*/
                }

                // Chiedi all'utente di inserire l'importo della transazione
                std::cout << "Enter transaction amount: ";
                std::cin >> amount;

                // Crea un nuovo shared_ptr transaction puntante la transazione creata con i valori inseriti/selezionati dall'utente
                auto transaction = std::make_shared<Transaction>(amount, transactionType);

                // Aggiungi lo shared_ptr transaction al vettore transactions del BankAccount
                account1->addTransaction(transaction);

                std::cout << "Done" << std::endl;

                // Stampa la transazione
                transaction->printTransaction();

                break;
            }
                //2. Visualize transaction history
            case 2:
                account1->printOperations();
                break;
                //3. Share transaction history
            case 3:
                account1->save(std::string("history.txt"));
                break;
                //4. Card operations
            case 4: {

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
                            transactionType = TransactionType::Deposit;
                            break; */
                }


                break;

            }
                //5. exit
            case 5:
                break;
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
