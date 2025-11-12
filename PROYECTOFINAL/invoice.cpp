#include "Invoice.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <random>

Invoice::Invoice(const ShoppingCart& cart, const PaymentMethod& payment) {
    invoiceNumber_ = GenerateInvoiceNumber();
    date_ = GetCurrentDate();
    items_ = cart.GetItems();
    subtotal_ = cart.GetSubtotal();
    tax_ = cart.GetTax();
    total_ = cart.GetTotal();
    paymentType_ = payment.GetPaymentType();
    paymentDetails_ = payment.GetPaymentDetails();
}

void Invoice::GenerateInvoice() {
    Display();
}

void Invoice::SaveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not create invoice file." << std::endl;
        return;
    }

    file << FormatInvoiceText();
    file.close();

    std::cout << "\nInvoice saved to: " << filename << std::endl;
}

void Invoice::Display() const {
    std::cout << FormatInvoiceText();
}

std::string Invoice::GetInvoiceNumber() const {
    return invoiceNumber_;
}

std::string Invoice::GetDate() const {
    return date_;
}

std::string Invoice::GenerateInvoiceNumber() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(10000, 99999);

    return "INV-" + std::to_string(dis(gen));
}

std::string Invoice::GetCurrentDate() const {
    time_t now = time(0);
    tm ltm;

#ifdef _WIN32
    localtime_s(&ltm, &now);
#else
    localtime_r(&now, &ltm);
#endif

    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(2) << ltm.tm_mday << "/"
        << std::setw(2) << (1 + ltm.tm_mon) << "/"
        << (1900 + ltm.tm_year);

    return oss.str();
}

std::string Invoice::FormatInvoiceText() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);

    oss << "\n========================================\n";
    oss << "           CLOTHING STORE               \n";
    oss << "========================================\n";
    oss << "Invoice #: " << invoiceNumber_ << "\n";
    oss << "Date: " << date_ << "\n";
    oss << "========================================\n\n";

    oss << "ITEMS:\n";
    oss << "----------------------------------------\n";

    int itemNum = 1;
    for (const auto& item : items_) {
        oss << itemNum++ << ". " << item.subcategory << "\n";
        oss << "   Category: " << item.category << "\n";
        oss << "   Size: " << item.size << "\n";
        oss << "   Color: " << item.color << "\n";
        oss << "   Price: $" << item.price << "\n";
        oss << "   Qty: " << item.quantity << "\n\n";
    }

    oss << "----------------------------------------\n";
    oss << "Subtotal:        $" << std::setw(10) << subtotal_ << "\n";
    oss << "Tax (13%):       $" << std::setw(10) << tax_ << "\n";
    oss << "========================================\n";
    oss << "TOTAL:           $" << std::setw(10) << total_ << "\n";
    oss << "========================================\n\n";

    oss << "PAYMENT METHOD: " << paymentType_ << "\n";
    oss << paymentDetails_ << "\n\n";

    oss << "========================================\n";
    oss << "      Thank you for your purchase!      \n";
    oss << "========================================\n\n";

    return oss.str();
}