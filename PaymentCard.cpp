//
// Created by ciullo on 28/05/24.
//

#include <random>
#include <sstream>
#include <iostream>
#include "PaymentCard.h"


PaymentCard::PaymentCard(std::string name) : cardName(name) {
    // Initialization of random number generators
    std::random_device rd;
    std::mt19937 gen(rd());

    // Generation of the cardID (16 digits, spaced every 4)
    std::uniform_int_distribution<int> cardIDModuleGenerator(1000, 9999);
    std::stringstream cardIDStream;
    cardIDStream << cardIDModuleGenerator(gen) << " " << cardIDModuleGenerator(gen) << " " << cardIDModuleGenerator(gen)
                 << " " << cardIDModuleGenerator(gen);
    cardNumber = cardIDStream.str();

    // Generation of the cvv (3 digits)
    std::uniform_int_distribution<int> cvvGenerator(100, 999);
    cvv = cvvGenerator(gen);

    // Generation of the pin (5 digits)
    std::uniform_int_distribution<int> pinGenerator(10000, 99999);
    pin = pinGenerator(gen);

    maximum = 1000;
}

PaymentCard &PaymentCard::operator=(const PaymentCard &other) {
    if (this != &other) {
        cardNumber = other.cardNumber;
        cvv = other.cvv;
        pin = other.pin;
    }
    return *this;
}

void PaymentCard::printCvv() const {
    std::cout << cvv << std::endl;
}

void PaymentCard::printPin() const {
    std::cout << pin << std::endl;
}

void PaymentCard::printCardID() const {
    std::cout << cardNumber << std::endl;
}

void PaymentCard::printCard() const {
    std::cout << "Card number: " << cardNumber << ", cvv: " << cvv << ", pin: " << pin << std::endl;
}

std::string PaymentCard::printCardString() const {
    std::stringstream card;
    card << "Card Name: " << cardName << ", card number: " << cardNumber << ", cvv: " << cvv << ", pin: " << pin
         << std::endl;
    return card.str();
}