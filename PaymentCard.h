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
    explicit PaymentCard(const std::string& name);

    ~PaymentCard() = default;

    std::string printCardString() const;

protected:
    std::string cardName;
    std::string cardNumber;
    int cvv;
    int pin;
    int maximum;
};


#endif //ECONOVAULT_PAYMENTCARD_H
