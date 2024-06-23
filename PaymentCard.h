//
// Created by ciullo on 28/05/24.
//

#ifndef ECONOVAULT_PAYMENTCARD_H
#define ECONOVAULT_PAYMENTCARD_H


enum class CardType {
    Debit, Credit, Virtual
};


class PaymentCard {
public:
    PaymentCard(std::string name);

    ~PaymentCard() = default;

    PaymentCard &operator=(const PaymentCard &right);

    std::string getCardName() const {
        return cardName;
    }

    void setCardName(const std::string &cardName) {
        PaymentCard::cardName = cardName;
    }

    std::string getCardNumber() const {
        return cardNumber;
    }

    void setCardNumber(const std::string &cardNumber) {
        PaymentCard::cardNumber = cardNumber;
    }

    int getCvv() const {
        return cvv;
    }

    void setCvv(int cvv) {
        PaymentCard::cvv = cvv;
    }

    int getPin() const {
        return pin;
    }

    void setPin(int pin) {
        PaymentCard::pin = pin;
    }

    int getMaximum() const {
        return maximum;
    }

    void setMaximum(int maximum) {
        PaymentCard::maximum = maximum;
    }

    void printCvv() const;

    void printPin() const;

    void printCardID() const;

    void printCard() const;

    std::string printCardString() const;

protected:
    std::string cardName;
    std::string cardNumber;
    int cvv;
    int pin;
    int maximum;
};


#endif //ECONOVAULT_PAYMENTCARD_H
