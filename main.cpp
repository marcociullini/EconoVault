#include <iostream>
#include <sstream>
#include <algorithm>
#include "Operation.h"
#include "BankAccount.h"

int main() {
    BankAccount *account1 = new BankAccount();
    int operationChoice;

    do {
        do {
            // Ask the user to select an operation to perform
            std::cout << "Select operation to perform:" << std::endl;
            std::cout << "1. New transaction" << std::endl;
            std::cout << "2. Visualize personal bank account data" << std::endl;
            std::cout << "3. Search/cancel transaction" << std::endl;
            std::cout << "4. Share transaction history" << std::endl;
            std::cout << "5. Card operations" << std::endl;
            std::cout << "6. Execute planned transactions" << std::endl;
            std::cout << "7. Exit" << std::endl;
            std::cin >> operationChoice;
            if (operationChoice <= 0 || operationChoice > 7)
                std::cerr << "Invalid choice!" << std::endl;
        } while (operationChoice <= 0 || operationChoice > 7);

        switch (operationChoice) {
            // 1. New transaction
            case 1: {

                int transactionTypeChoice = 0;

                do {
                    std::cout << "Select transaction type:" << std::endl;
                    std::cout << "1. Regular transaction" << std::endl;
                    std::cout << "2. Planned transaction" << std::endl;
                    std::cin >> transactionTypeChoice;
                    if (transactionTypeChoice <= 0 || transactionTypeChoice > 2)
                        std::cerr << "Invalid choice!" << std::endl;
                } while (transactionTypeChoice <= 0 || transactionTypeChoice > 2);

                switch (transactionTypeChoice) {
                    // Regular transaction
                    case 1: {
                        do {
                            // Ask the user to select a transaction type
                            std::cout << "Select transaction type:" << std::endl;
                            std::cout << Operation::printOperationTypes();
                            std::cin >> transactionTypeChoice;
                            if (transactionTypeChoice <= 0 || transactionTypeChoice >= 4)
                                std::cerr << "Invalid choice!" << std::endl;
                        } while (transactionTypeChoice <= 0 || transactionTypeChoice >= 4);

                        OperationType transactionType;

                        //Sets the transaction type based on user choice
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
                        }

                        float amount;

                        std::string amountStr;
                        std::cout << "Enter transaction amount: ";
                        std::cin >> amountStr;
                        std::replace(amountStr.begin(), amountStr.end(), ',', '.'); // Replace comma with dot
                        amount = std::stof(amountStr);

                        try {
                            //Creates a new transaction based on the user choice
                            auto transaction = std::make_shared<Operation>(amount, transactionType);

                            account1->addTransaction(transaction);

                            std::cout << "Done" << std::endl;

                            transaction->printOperation();

                        } catch (const std::out_of_range &e) {
                            std::cerr << "Error: " << e.what() << std::endl;
                        } catch (const std::runtime_error &e) {
                            std::cerr << "Transaction failed: " << e.what() << std::endl;
                        }
                        break;
                    }
                    // Planned transaction
                    case 2: {
                        float amount;
                        std::string amountStr;
                        std::cout << "Enter transaction amount: ";
                        std::cin >> amountStr;
                        std::replace(amountStr.begin(), amountStr.end(), ',', '.'); // Replace comma with dot
                        amount = std::stof(amountStr);

                        int year, month, day;
                        std::cout << "Enter year for next execution: ";
                        std::cin >> year;
                        std::cout << "Enter month for next execution (1-12): ";
                        std::cin >> month;
                        std::cout << "Enter day for next execution (1-31): ";
                        std::cin >> day;

                        try {
                            Date nextExecutionDate(day, month, year);

                            int frequencyChoice;
                            std::cout << "Do you want to make this a periodic transaction? (1: Yes, 0: No): ";
                            std::cin >> frequencyChoice;

                            Frequency frequency = Frequency::One; // Default value

                            if (frequencyChoice == 1) {
                                int freqChoice;
                                do {
                                    std::cout << "Select frequency:" << std::endl;
                                    std::cout << "1. Daily" << std::endl;
                                    std::cout << "2. Weekly" << std::endl;
                                    std::cout << "3. Monthly" << std::endl;
                                    std::cout << "4. Yearly" << std::endl;
                                    std::cin >> freqChoice;
                                    if (freqChoice <= 0 || freqChoice >= 6)
                                        std::cerr << "Invalid choice!" << std::endl;
                                } while (freqChoice <= 0 || freqChoice >= 6);

                                switch (freqChoice) {
                                    case 1:
                                        frequency = Frequency::Daily;
                                        break;
                                    case 2:
                                        frequency = Frequency::Weekly;
                                        break;
                                    case 3:
                                        frequency = Frequency::Monthly;
                                        break;
                                    case 4:
                                        frequency = Frequency::Yearly;
                                }
                            }

                            auto plannedTransaction = std::make_shared<PlannedTransaction>(amount,
                                                                                           OperationType::Withdrawal,
                                                                                           nextExecutionDate,
                                                                                           frequency);
                            account1->addPlannedTransaction(plannedTransaction);
                            std::cout << "Planned transaction added successfully." << std::endl;
                        } catch (const std::exception &e) {
                            std::cerr << "Error adding planned transaction: " << e.what() << std::endl;
                        }
                        break;
                    }
                }
                break;
            }
            // 2. Visualize BankAccount data
            case 2: {
                int dataVisualizationChoice;
                do {
                    std::cout << "Select bank account information:" << std::endl;
                    std::cout << "1. Visualize transaction history" << std::endl;
                    std::cout << "2. Visualize planned transactions" << std::endl;
                    std::cout << "2. Visualize IBAN" << std::endl;
                    std::cout << "3. Visualize balance" << std::endl;
                    std::cin >> dataVisualizationChoice;
                    if (dataVisualizationChoice <= 0 || dataVisualizationChoice >= 5)
                        std::cerr << "Invalid choice!" << std::endl;
                } while (dataVisualizationChoice <= 0 || dataVisualizationChoice >= 5);

                switch (dataVisualizationChoice) {
                    case 1:
                        account1->printOperations(account1->getOperations());
                        break;
                    case 2:
                        account1->printPlannedTransactions(account1->getPlannedTransactions());
                        break;
                    case 3:
                        std::cout << "IBAN: " << account1->printIban() << std::endl;
                        break;
                    case 4:
                        std::cout << "Balance: €" << account1->printBalance() << std::endl;
                        break;
                }
                break;
            }
            //3. Search/Cancel transaction
            case 3: {
                int searchOrCancelChoice;
                do {
                    std::cout << "Select action:" << std::endl;
                    std::cout << "1. Search transaction" << std::endl;
                    std::cout << "2. Cancel transaction" << std::endl;
                    std::cin >> searchOrCancelChoice;
                    if (searchOrCancelChoice <= 0 || searchOrCancelChoice >= 3)
                        std::cerr << "Invalid choice!" << std::endl;
                } while (searchOrCancelChoice <= 0 || searchOrCancelChoice >= 3);

                switch (searchOrCancelChoice) {
                    //Search transaction
                    case 1: {
                        int transactionTypeChoice;
                        do {
                            std::cout << "Select transaction type to search:" << std::endl;
                            std::cout << "1. Regular transaction" << std::endl;
                            std::cout << "2. Planned transaction" << std::endl;
                            std::cin >> transactionTypeChoice;
                            if (transactionTypeChoice <= 0 || transactionTypeChoice > 2)
                                std::cerr << "Invalid choice!" << std::endl;
                        } while (transactionTypeChoice <= 0 || transactionTypeChoice > 2);

                        switch (transactionTypeChoice) {
                            //Regular transaction
                            case 1: {
                                int searchMethodChoice;
                                do {
                                    std::cout << "Select search method:" << std::endl;
                                    std::cout << "1. Amount search" << std::endl;
                                    std::cout << "2. Type search" << std::endl;
                                    std::cout << "3. Date search" << std::endl;
                                    std::cin >> searchMethodChoice;
                                    if (searchMethodChoice <= 0 || searchMethodChoice >= 4)
                                        std::cerr << "Invalid choice!" << std::endl;
                                } while (searchMethodChoice <= 0 || searchMethodChoice >= 4);

                                switch (searchMethodChoice) {
                                    //Amount search
                                    case 1: {
                                        float amount;
                                        std::cout << "Insert amount:" << std::endl;
                                        std::cin >> amount;

                                        try {
                                            auto results = account1->searchOperationAmount(amount);
                                            if (!results.empty()) {
                                                std::cout << "Search result:" << std::endl;
                                                account1->printOperations(results);
                                            } else {
                                                std::cout << "Search result:" << std::endl;
                                                std::cout << "-none" << std::endl;
                                            }
                                        } catch (const std::invalid_argument &e) {
                                            std::cerr << "Error: " << e.what() << std::endl;
                                        }
                                        break;
                                    }
                                    // Type search
                                    case 2: {
                                        int typeChoice;
                                        do {
                                            std::cout << "Select operation type:" << std::endl;
                                            std::cout << Operation::printOperationTypes();
                                            std::cin >> typeChoice;
                                            if (typeChoice <= 0 || typeChoice >= 4)
                                                std::cerr << "Invalid choice!" << std::endl;
                                        } while (typeChoice <= 0 || typeChoice >= 4);

                                        OperationType searchType;
                                        switch (typeChoice) {
                                            case 1:
                                                searchType = OperationType::Deposit;
                                                break;
                                            case 2:
                                                searchType = OperationType::Withdrawal;
                                                break;
                                            case 3:
                                                searchType = OperationType::Transfer;
                                                break;
                                        }

                                        auto results = account1->searchOperationType(searchType);
                                        if (!results.empty()) {
                                            std::cout << "Search result:" << std::endl;
                                            account1->printOperations(results);
                                        } else {
                                            std::cout << "Search result:" << std::endl;
                                            std::cout << "-none" << std::endl;
                                        }
                                        break;
                                    }
                                    //Data search
                                    case 3: {
                                        int year, month, day;
                                        std::cout << "Enter year: ";
                                        std::cin >> year;
                                        std::cout << "Enter month (1-12): ";
                                        std::cin >> month;
                                        std::cout << "Enter day (1-31): ";
                                        std::cin >> day;
                                        try {
                                            Date date(day, month, year);
                                            auto results = account1->searchOperationDate(date);
                                            if (!results.empty()) {
                                                std::cout << "Search result:" << std::endl;
                                                account1->printOperations(results);
                                            } else {
                                                std::cout << "Search result:" << std::endl;
                                                std::cout << "-none" << std::endl;
                                            }
                                        } catch (const std::out_of_range &e) {
                                            std::cerr << "Error: " << e.what() << std::endl;
                                        }
                                        break;
                                    }
                                }
                                break;
                            }
                            // Planned transaction
                            case 2: {
                                int searchMethodChoice;
                                do {
                                    std::cout << "Select search method:" << std::endl;
                                    std::cout << "1. Execution date search" << std::endl;
                                    std::cout << "2. Next execution date search" << std::endl;
                                    std::cout << "3. Amount search" << std::endl;
                                    std::cin >> searchMethodChoice;
                                    if (searchMethodChoice <= 0 || searchMethodChoice > 3)
                                        std::cerr << "Invalid choice!" << std::endl;
                                } while (searchMethodChoice <= 0 || searchMethodChoice > 3);

                                switch (searchMethodChoice) {
                                    // Execution date search
                                    case 1: {
                                        int year, month, day;
                                        std::cout << "Enter year: ";
                                        std::cin >> year;
                                        std::cout << "Enter month (1-12): ";
                                        std::cin >> month;
                                        std::cout << "Enter day (1-31): ";
                                        std::cin >> day;
                                        try {
                                            Date date(day, month, year);
                                            auto results = account1->searchPlannedDate(date);
                                            if (!results.empty()) {
                                                account1->printPlannedTransactions(results);
                                            } else {
                                                std::cout << "Search result:" << std::endl;
                                                std::cout << "-none" << std::endl;
                                            }
                                        } catch (const std::out_of_range &e) {
                                            std::cerr << "Error: " << e.what() << std::endl;
                                        }
                                        break;
                                    }
                                    // Next execution date search
                                    case 2: {
                                        int year, month, day;
                                        std::cout << "Enter year: ";
                                        std::cin >> year;
                                        std::cout << "Enter month (1-12): ";
                                        std::cin >> month;
                                        std::cout << "Enter day (1-31): ";
                                        std::cin >> day;
                                        try {
                                            Date date(day, month, year);
                                            auto results = account1->searchPlannedNextExecutionDate(date);
                                            if (!results.empty()) {
                                                account1->printPlannedTransactions(results);
                                            } else {
                                                std::cout << "Search result:" << std::endl;
                                                std::cout << "-none" << std::endl;
                                            }
                                        } catch (const std::out_of_range &e) {
                                            std::cerr << "Error: " << e.what() << std::endl;
                                        }
                                        break;
                                    }
                                    // Amount search
                                    case 3: {
                                        float amount;
                                        std::cout << "Insert amount:" << std::endl;
                                        std::cin >> amount;

                                        try {
                                            auto results = account1->searchPlannedDate(amount);
                                            if (!results.empty()) {
                                                std::cout << "Search result:" << std::endl;
                                                account1->printPlannedTransactions(results);
                                            } else {
                                                std::cout << "Search result:" << std::endl;
                                                std::cout << "-none" << std::endl;
                                            }
                                        } catch (const std::invalid_argument &e) {
                                            std::cerr << "Error: " << e.what() << std::endl;
                                        }
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                        break;
                    }
                    // Cancel transaction
                    case 2: {
                        int transactionTypeChoice;
                        do {
                            std::cout << "Select transaction type to cancel:" << std::endl;
                            std::cout << "1. Regular transaction" << std::endl;
                            std::cout << "2. Planned transaction" << std::endl;
                            std::cin >> transactionTypeChoice;
                            if (transactionTypeChoice <= 0 || transactionTypeChoice > 2)
                                std::cerr << "Invalid choice!" << std::endl;
                        } while (transactionTypeChoice <= 0 || transactionTypeChoice > 2);

                        switch (transactionTypeChoice) {
                            // Regular transaction
                            case 1: {

                                int searchMethodChoice;
                                do {
                                    std::cout << "Select search method to find transactions to delete:"
                                              << std::endl;
                                    std::cout << "1. Amount search" << std::endl;
                                    std::cout << "2. Type search" << std::endl;
                                    std::cout << "3. Date search" << std::endl;
                                    std::cin >> searchMethodChoice;
                                    if (searchMethodChoice <= 0 || searchMethodChoice >= 4)
                                        std::cerr << "Invalid choice!" << std::endl;
                                } while (searchMethodChoice <= 0 || searchMethodChoice >= 4);

                                std::vector<std::shared_ptr<Operation>> selectedTransactions;

                                switch (searchMethodChoice) {
                                    //Amount search
                                    case 1: {
                                        float amount;
                                        std::cout << "Insert amount:" << std::endl;
                                        std::cin >> amount;
                                        selectedTransactions = account1->searchOperationAmount(amount);
                                        break;
                                    }
                                    //Type search
                                    case 2: {
                                        int typeChoice;
                                        do {
                                            std::cout << "Select operation type:" << std::endl;
                                            std::cout << Operation::printOperationTypes();
                                            std::cin >> typeChoice;
                                            if (typeChoice <= 0 || typeChoice >= 4)
                                                std::cerr << "Invalid choice!" << std::endl;

                                        } while (typeChoice <= 0 || typeChoice >= 4);

                                        OperationType searchType;
                                        switch (typeChoice) {
                                            case 1:
                                                searchType = OperationType::Deposit;
                                                break;
                                            case 2:
                                                searchType = OperationType::Withdrawal;
                                                break;
                                            case 3:
                                                searchType = OperationType::Transfer;
                                                break;
                                        }
                                        selectedTransactions = account1->searchOperationType(searchType);
                                        break;
                                    }
                                    //Data search
                                    case 3: {
                                        int year, month, day;
                                        std::cout << "Enter year: ";
                                        std::cin >> year;
                                        std::cout << "Enter month (1-12): ";
                                        std::cin >> month;
                                        std::cout << "Enter day (1-31): ";
                                        std::cin >> day;
                                        try {
                                            Date date(day, month, year);
                                            selectedTransactions = account1->searchOperationDate(date);
                                        } catch (const std::out_of_range &e) {
                                            std::cerr << "Error: " << e.what() << std::endl;
                                            break;
                                        }
                                        break;
                                    }
                                }

                                if (!selectedTransactions.empty()) {
                                    std::cout << "Transactions found:" << std::endl;
                                    account1->printOperations(selectedTransactions);
                                    int cancelChoice;
                                    do {
                                        std::cout << "Select deletion method:" << std::endl;
                                        std::cout << "1. Select transaction" << std::endl;
                                        std::cout << "2. Delete all" << std::endl;
                                        std::cin >> cancelChoice;
                                        if (cancelChoice <= 0 || cancelChoice >= 3)
                                            std::cerr << "Invalid choice!" << std::endl;
                                    } while (cancelChoice <= 0 || cancelChoice >= 3);

                                    switch (cancelChoice) {
                                        // Select transaction
                                        case 1: {
                                            std::cout
                                                    << "Select transactions to delete (enter indices separated by commas, e.g., 1,2,4): "
                                                    << std::endl;
                                            std::vector<std::shared_ptr<Operation>> transactionToCancel;
                                            std::string input;
                                            std::cin.ignore();
                                            std::getline(std::cin, input);
                                            std::stringstream ss(input);
                                            std::string token;
                                            while (std::getline(ss, token, ',')) {
                                                int transactionIndex = std::stoi(token);
                                                if (transactionIndex > 0 &&
                                                    transactionIndex <= selectedTransactions.size()) {
                                                    transactionToCancel.push_back(
                                                            selectedTransactions[transactionIndex - 1]);
                                                } else {
                                                    std::cerr << "Invalid index: " << transactionIndex << std::endl;
                                                }
                                            }
                                            if (!transactionToCancel.empty()) {
                                                try {
                                                    account1->cancelOperations(transactionToCancel);
                                                    std::cout << "Selected transactions cancelled." << std::endl;
                                                } catch (const std::runtime_error &e) {
                                                    std::cerr << "Cancellation failed: " << e.what() << std::endl;
                                                }
                                            } else {
                                                std::cout << "No transactions were selected for cancellation."
                                                          << std::endl;
                                            }
                                            break;
                                        }
                                        // Delete all
                                        case 2: {
                                            try {
                                                account1->cancelOperations(selectedTransactions);
                                                std::cout << "All transactions found cancelled." << std::endl;
                                            } catch (const std::runtime_error &e) {
                                                std::cerr << "Cancellation failed: " << e.what() << std::endl;
                                            }
                                            break;
                                        }
                                    }
                                } else {
                                    std::cerr << "No transactions found with the selected attributes" << std::endl;
                                }
                                break;
                            }
                            // Planned transaction
                            case 2: {
                                int searchMethodChoice;
                                do {
                                    std::cout << "Select search method to find transactions to delete:" << std::endl;
                                    std::cout << "1. Execution date search" << std::endl;
                                    std::cout << "2. Next execution date search" << std::endl;
                                    std::cout << "3. Amount search" << std::endl;
                                    std::cin >> searchMethodChoice;
                                    if (searchMethodChoice <= 0 || searchMethodChoice > 3)
                                        std::cerr << "Invalid choice!" << std::endl;
                                } while (searchMethodChoice <= 0 || searchMethodChoice > 3);

                                std::vector<std::shared_ptr<PlannedTransaction>> selectedTransactions;

                                switch (searchMethodChoice) {
                                    // Execution date search
                                    case 1: {
                                        int year, month, day;
                                        std::cout << "Enter year: ";
                                        std::cin >> year;
                                        std::cout << "Enter month (1-12): ";
                                        std::cin >> month;
                                        std::cout << "Enter day (1-31): ";
                                        std::cin >> day;
                                        try {
                                            Date date(day, month, year);
                                            selectedTransactions = account1->searchPlannedDate(date);
                                        } catch (const std::out_of_range &e) {
                                            std::cerr << "Error: " << e.what() << std::endl;
                                        }
                                        break;
                                    }
                                    // Next execution date search
                                    case 2: {
                                        int year, month, day;
                                        std::cout << "Enter year: ";
                                        std::cin >> year;
                                        std::cout << "Enter month (1-12): ";
                                        std::cin >> month;
                                        std::cout << "Enter day (1-31): ";
                                        std::cin >> day;
                                        try {
                                            Date date(day, month, year);
                                            selectedTransactions = account1->searchPlannedNextExecutionDate(date);
                                        } catch (const std::out_of_range &e) {
                                            std::cerr << "Error: " << e.what() << std::endl;
                                        }
                                        break;
                                    }
                                    // Amount search
                                    case 3: {
                                        float amount;
                                        std::cout << "Insert amount:" << std::endl;
                                        std::cin >> amount;
                                        selectedTransactions = account1->searchPlannedDate(amount);
                                        break;
                                    }
                                }

                                if (!selectedTransactions.empty()) {
                                    std::cout << "Transactions found:" << std::endl;
                                    account1->printPlannedTransactions(selectedTransactions);
                                    int cancelChoice;
                                    do {
                                        std::cout << "Select deletion method:" << std::endl;
                                        std::cout << "1. Select transaction" << std::endl;
                                        std::cout << "2. Delete all" << std::endl;
                                        std::cin >> cancelChoice;
                                        if (cancelChoice <= 0 || cancelChoice >= 3)
                                            std::cerr << "Invalid choice!" << std::endl;
                                    } while (cancelChoice <= 0 || cancelChoice >= 3);

                                    switch (cancelChoice) {
                                        // Select transaction
                                        case 1: {
                                            std::cout
                                                    << "Select transactions to delete (enter indices separated by commas, e.g., 1,2,4): "
                                                    << std::endl;
                                            std::vector<std::shared_ptr<PlannedTransaction>> transactionToCancel;
                                            std::string input;
                                            std::cin.ignore();
                                            std::getline(std::cin, input);
                                            std::stringstream ss(input);
                                            std::string token;
                                            while (std::getline(ss, token, ',')) {
                                                int transactionIndex = std::stoi(token);
                                                if (transactionIndex > 0 &&
                                                    transactionIndex <= selectedTransactions.size()) {
                                                    transactionToCancel.push_back(
                                                            selectedTransactions[transactionIndex - 1]);
                                                } else {
                                                    std::cerr << "Invalid index: " << transactionIndex << std::endl;
                                                }
                                            }
                                            if (!transactionToCancel.empty()) {
                                                account1->removePlannedTransaction(transactionToCancel);
                                                std::cout << "Selected transactions cancelled." << std::endl;
                                            } else {
                                                std::cout << "No transactions were selected for cancellation."
                                                          << std::endl;
                                            }
                                            break;
                                        }
                                        // Delete all
                                        case 2: {
                                            account1->removePlannedTransaction(selectedTransactions);
                                            std::cout << "All transactions found cancelled." << std::endl;
                                            break;
                                        }
                                    }
                                } else {
                                    std::cerr << "No transactions found with the selected attributes" << std::endl;
                                }
                                break;
                            }
                        }
                        break;
                    }
                }
                break;
            }
            //4. Share transaction history
            case 4: {
                account1->save(std::string("history.txt"));
                break;
            }
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
                    case 3: {
                        account1->printCards();
                        break;
                    }
                }
                break;
            }
            //6. Execute planned transactions
            case 6: {
                try {
                    account1->executePlannedTransactions();
                } catch (const std::runtime_error &e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                break;
            }
            //7. exit
            case 7:
                break;
        }
    } while (operationChoice != 7);

    account1->save("account.txt");
    delete account1;
    return 0;
}