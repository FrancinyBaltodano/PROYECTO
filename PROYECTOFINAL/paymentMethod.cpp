#include "PaymentMethod.h"
#include <iostream>
#include <iomanip>

// ========== CashPayment ==========
CashPayment::CashPayment(double amountGiven)
    : amountGiven_(amountGiven), change_(0.0) {
}

bool CashPayment::ProcessPayment(double amount) {
    if (amountGiven_ >= amount) {
        change_ = amountGiven_ - amount;
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "\nPayment successful!" << std::endl;
        std::cout << "Amount given: $" << amountGiven_ << std::endl;
        std::cout << "Change: $" << change_ << std::endl;
        return true;
    }
    else {
        std::cout << "\nInsufficient cash. Payment failed." << std::endl;
        return false;
    }
}

std::string CashPayment::GetPaymentType() const {
    return "Cash";
}

std::string CashPayment::GetPaymentDetails() const {
    return "Cash Payment";
}

double CashPayment::GetChange() const {
    return change_;
}

// ========== CreditCardPayment ==========
CreditCardPayment::CreditCardPayment(const std::string& cardNumber, const std::string& cardHolder)
    : cardNumber_(cardNumber), cardHolder_(cardHolder) {
}

bool CreditCardPayment::ProcessPayment(double amount) {
    std::cout << "\nProcessing credit card payment..." << std::endl;
    std::cout << "Card: " << MaskCardNumber() << std::endl;
    std::cout << "Cardholder: " << cardHolder_ << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Amount: $" << amount << std::endl;
    std::cout << "Payment approved!" << std::endl;
    return true;
}

std::string CreditCardPayment::GetPaymentType() const {
    return "Credit Card";
}

std::string CreditCardPayment::GetPaymentDetails() const {
    return "Card: " + MaskCardNumber() + " (" + cardHolder_ + ")";
}

std::string CreditCardPayment::MaskCardNumber() const {
    if (cardNumber_.length() < 4) return "****";
    return "**** **** **** " + cardNumber_.substr(cardNumber_.length() - 4);
}

// ========== DebitCardPayment ==========
DebitCardPayment::DebitCardPayment(const std::string& cardNumber, const std::string& cardHolder)
    : cardNumber_(cardNumber), cardHolder_(cardHolder) {
}

bool DebitCardPayment::ProcessPayment(double amount) {
    std::cout << "\nProcessing debit card payment..." << std::endl;
    std::cout << "Card: " << MaskCardNumber() << std::endl;
    std::cout << "Cardholder: " << cardHolder_ << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Amount: $" << amount << std::endl;
    std::cout << "Payment approved!" << std::endl;
    return true;
}

std::string DebitCardPayment::GetPaymentType() const {
    return "Debit Card";
}

std::string DebitCardPayment::GetPaymentDetails() const {
    return "Card: " + MaskCardNumber() + " (" + cardHolder_ + ")";
}

std::string DebitCardPayment::MaskCardNumber() const {
    if (cardNumber_.length() < 4) return "****";
    return "**** **** **** " + cardNumber_.substr(cardNumber_.length() - 4);
}