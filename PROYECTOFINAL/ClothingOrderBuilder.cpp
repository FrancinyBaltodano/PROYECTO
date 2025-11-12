#include "ClothingOrderBuilder.h"
#include "ItemSelector.h"
#include "Invoice.h"
#include <iostream>
#include <limits>

ClothingOrderBuilder::ClothingOrderBuilder() {
}

void ClothingOrderBuilder::Run() {
    std::cout << "=== Welcome to Clothing Store ===" << std::endl;

    char continueOrder = 'y';

    while (continueOrder == 'y' || continueOrder == 'Y') {
        BuildOrder();

        std::cout << "\nDo you want to add another item? (y/n): ";
        std::cin >> continueOrder;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (!cart_.IsEmpty()) {
        ProcessCheckout();
    }
    else {
        std::cout << "\nNo items in cart. Thank you for visiting!" << std::endl;
    }
}

void ClothingOrderBuilder::BuildOrder() {
    std::cout << "\n=== Add Item to Cart ===" << std::endl;

    SelectCategory();
    SelectSubcategory();
    SelectSize();
    SelectColor();

    // Get price and add to cart
    try {
        double price = priceRepo_.GetPrice(currentSubcategory_);
        cart_.AddItem(currentCategory_, currentSubcategory_, currentSize_, currentColor_, price);

        std::cout << "\nCurrent cart:" << std::endl;
        cart_.DisplayCart();
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void ClothingOrderBuilder::DisplayFinalOrder() const {
    cart_.DisplayCart();
}

void ClothingOrderBuilder::SelectCategory() {
    ItemSelector<CategoryRepository> selector(categoryRepo_, availableCategories_, "category");
    selector.DisplayAvailableItems();

    std::cout << "\nEnter the category you want: ";
    std::getline(std::cin, currentCategory_);

    selector.AddItemToOrder(currentCategory_, selectedItems_);
}

void ClothingOrderBuilder::SelectSubcategory() {
    ItemSelector<SubcategoryRepository> selector(subcategoryRepo_, availableSubcategories_, "subcategory");
    selector.DisplayAvailableItems();

    std::cout << "\nEnter the type of clothing you want: ";
    std::getline(std::cin, currentSubcategory_);

    selector.AddItemToOrder(currentSubcategory_, selectedItems_);
}

void ClothingOrderBuilder::SelectSize() {
    ItemSelector<SizeRepository> selector(sizeRepo_, availableSizes_, "size");
    selector.DisplayAvailableItems();

    std::cout << "\nEnter the size you want: ";
    std::getline(std::cin, currentSize_);

    selector.AddItemToOrder(currentSize_, selectedItems_);
}

void ClothingOrderBuilder::SelectColor() {
    std::cout << "\nAvailable colors:" << std::endl;
    for (const auto& color : availableColors_) {
        std::cout << "- " << color << std::endl;
    }

    std::cout << "\nEnter the color you want: ";
    std::getline(std::cin, currentColor_);

    std::cout << "Selected color: " << currentColor_ << std::endl;
}

void ClothingOrderBuilder::ProcessCheckout() {
    std::cout << "\n=== CHECKOUT ===" << std::endl;
    DisplayFinalOrder();

    SelectPaymentMethod();

    if (paymentMethod_) {
        double total = cart_.GetTotal();
        if (paymentMethod_->ProcessPayment(total)) {
            Invoice invoice(cart_, *paymentMethod_);
            invoice.GenerateInvoice();

            std::string filename = "invoice_" + invoice.GetInvoiceNumber() + ".txt";
            invoice.SaveToFile(filename);

            std::cout << "\nThank you for your purchase!" << std::endl;
        }
        else {
            std::cout << "\nPayment failed. Transaction cancelled." << std::endl;
        }
    }
}

void ClothingOrderBuilder::SelectPaymentMethod() {
    std::cout << "\nSelect payment method:" << std::endl;
    std::cout << "1. Cash" << std::endl;
    std::cout << "2. Credit Card" << std::endl;
    std::cout << "3. Debit Card" << std::endl;
    std::cout << "Enter your choice (1-3): ";

    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    double total = cart_.GetTotal();

    switch (choice) {
    case 1: {
        double amountGiven;
        std::cout << "Total to pay: $" << total << std::endl;
        std::cout << "Enter amount given: $";
        std::cin >> amountGiven;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        paymentMethod_ = std::make_unique<CashPayment>(amountGiven);
        break;
    }
    case 2: {
        std::string cardNumber, cardHolder;
        std::cout << "Enter card number: ";
        std::getline(std::cin, cardNumber);
        std::cout << "Enter cardholder name: ";
        std::getline(std::cin, cardHolder);
        paymentMethod_ = std::make_unique<CreditCardPayment>(cardNumber, cardHolder);
        break;
    }
    case 3: {
        std::string cardNumber, cardHolder;
        std::cout << "Enter card number: ";
        std::getline(std::cin, cardNumber);
        std::cout << "Enter cardholder name: ";
        std::getline(std::cin, cardHolder);
        paymentMethod_ = std::make_unique<DebitCardPayment>(cardNumber, cardHolder);
        break;
    }
    default:
        std::cout << "Invalid choice. Defaulting to cash." << std::endl;
        paymentMethod_ = std::make_unique<CashPayment>(total);
        break;
    }
}


