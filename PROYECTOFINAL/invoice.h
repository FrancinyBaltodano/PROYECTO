#pragma once
#include <string>
#include <vector>
#include "ShoppingCart.h"
#include "PaymentMethod.h"

class Invoice {
public:
    Invoice(const ShoppingCart& cart, const PaymentMethod& payment);

    void GenerateInvoice();
    void SaveToFile(const std::string& filename) const;
    void Display() const;

    std::string GetInvoiceNumber() const;
    std::string GetDate() const;

private:
    std::string invoiceNumber_;
    std::string date_;
    std::vector<CartItem> items_;
    double subtotal_;
    double tax_;
    double total_;
    std::string paymentType_;
    std::string paymentDetails_;

    std::string GenerateInvoiceNumber() const;
    std::string GetCurrentDate() const;
    std::string FormatInvoiceText() const;
};
