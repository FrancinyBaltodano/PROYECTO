#pragma once
#include <string>

// Abstract base class for payment methods
class PaymentMethod {
public:
    virtual ~PaymentMethod() = default;
    virtual bool ProcessPayment(double amount) = 0;
    virtual std::string GetPaymentType() const = 0;
    virtual std::string GetPaymentDetails() const = 0;
};

// Cash payment
class CashPayment : public PaymentMethod {
public:
    CashPayment(double amountGiven);
    bool ProcessPayment(double amount) override;
    std::string GetPaymentType() const override;
    std::string GetPaymentDetails() const override;
    double GetChange() const;

private:
    double amountGiven_;
    double change_;
};

// Credit Card payment
class CreditCardPayment : public PaymentMethod {
public:
    CreditCardPayment(const std::string& cardNumber, const std::string& cardHolder);
    bool ProcessPayment(double amount) override;
    std::string GetPaymentType() const override;
    std::string GetPaymentDetails() const override;

private:
    std::string cardNumber_;
    std::string cardHolder_;
    std::string MaskCardNumber() const;
};

// Debit Card payment
class DebitCardPayment : public PaymentMethod {
public:
    DebitCardPayment(const std::string& cardNumber, const std::string& cardHolder);
    bool ProcessPayment(double amount) override;
    std::string GetPaymentType() const override;
    std::string GetPaymentDetails() const override;

private:
    std::string cardNumber_;
    std::string cardHolder_;
    std::string MaskCardNumber() const;
};
