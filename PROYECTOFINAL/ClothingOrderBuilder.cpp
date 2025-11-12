#include "ClothingOrderBuilder.h"
#include "ItemSelector.h"
#include "Invoice.h"
#include <iostream>
#include <limits>
#include <algorithm>

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
    // Definir el mapa de subcategorías por categoría
    std::map<std::string, std::vector<std::string>> subcategoriesByCategory = {
        {"Ropa", {"Camiseta", "Pantalon", "Vestido", "Sudadera", "Shorts"}},
        {"Calzado", {"Zapatos","Sandalias", "Botas"}},
        {"Accesorios", {"Gorra", "Bufanda"}}
    };

    // Obtener las subcategorías filtradas según la categoría actual
    std::vector<std::string> filteredSubcategories;

    auto it = subcategoriesByCategory.find(currentCategory_);
    if (it != subcategoriesByCategory.end()) {
        filteredSubcategories = it->second;
    }
    else {
        // Si no encuentra la categoría, usar todas (fallback)
        std::cout << "Warning: Category '" << currentCategory_ << "' not found. Showing all items." << std::endl;
        filteredSubcategories = availableSubcategories_;
    }

    // Mostrar las subcategorías manualmente (sin ItemSelector)
    std::cout << "\n=== Available subcategories for " << currentCategory_ << " ===" << std::endl;
    for (const auto& subcat : filteredSubcategories) {
        try {
            int quantity = subcategoryRepo_.GetAvailableQuantity(subcat);
            std::cout << "  - " << subcat << " (Stock: " << quantity << ")" << std::endl;
        }
        catch (const std::invalid_argument&) {
            std::cout << "  - " << subcat << " (Not available)" << std::endl;
        }
    }

    std::cout << "\nEnter the type of clothing you want: ";
    std::getline(std::cin, currentSubcategory_);

    // Validar que la subcategoría pertenece a las filtradas
    bool isValid = std::find(filteredSubcategories.begin(), filteredSubcategories.end(),
        currentSubcategory_) != filteredSubcategories.end();

    if (isValid) {
        try {
            int quantity = subcategoryRepo_.GetAvailableQuantity(currentSubcategory_);
            if (quantity > 0) {
                selectedItems_.push_back(currentSubcategory_);
                subcategoryRepo_.UpdateQuantity(currentSubcategory_, quantity - 1);
                std::cout << " Added " << currentSubcategory_ << " to your order!" << std::endl;
            }
            else {
                std::cout << " Sorry, " << currentSubcategory_ << " is out of stock." << std::endl;
            }
        }
        catch (const std::invalid_argument&) {
            std::cout << " Error processing " << currentSubcategory_ << std::endl;
        }
    }
    else {
        std::cout << " " << currentSubcategory_ << "' is not available for " << currentCategory_ << std::endl;
    }
}

void ClothingOrderBuilder::SelectSize() {
    // Obtener las tallas filtradas según la subcategoría actual
    std::vector<std::string> filteredSizes;

    // Ropa usa tallas de letras
    if (currentSubcategory_ == "Camiseta" || currentSubcategory_ == "Pantalon" ||
        currentSubcategory_ == "Vestido" || currentSubcategory_ == "Sudadera" ||
        currentSubcategory_ == "Shorts") {
        filteredSizes = { "XS", "S", "M", "L", "XL", "XXL" };
    }
    // Calzado usa tallas numéricas
    else if (currentSubcategory_ == "Zapatos" || currentSubcategory_ == "Sandalias" ||
        currentSubcategory_ == "Botas") {
        filteredSizes = { "28", "30", "32", "34", "36", "38", "40", "42" };
    }
    // Accesorios pueden usar tallas simples o única
    else if (currentSubcategory_ == "Gorra" || currentSubcategory_ == "Bufanda") {
        filteredSizes = { "Unica", "S", "M", "L" };
    }
    else {
        // Si no reconoce la subcategoría, mostrar todas
        filteredSizes = availableSizes_;
    }

    // Mostrar las tallas filtradas
    std::cout << "\n=== Available sizes for " << currentSubcategory_ << " ===" << std::endl;
    for (const auto& size : filteredSizes) {
        try {
            int quantity = sizeRepo_.GetAvailableQuantity(size);
            std::cout << "  - " << size << " (Stock: " << quantity << ")" << std::endl;
        }
        catch (const std::invalid_argument&) {
            std::cout << "  - " << size << " (Not available)" << std::endl;
        }
    }

    std::cout << "\nEnter the size you want: ";
    std::getline(std::cin, currentSize_);

    // Validar que la talla pertenece a las filtradas
    bool isValid = std::find(filteredSizes.begin(), filteredSizes.end(),
        currentSize_) != filteredSizes.end();

    if (isValid) {
        try {
            int quantity = sizeRepo_.GetAvailableQuantity(currentSize_);
            if (quantity > 0) {
                selectedItems_.push_back(currentSize_);
                sizeRepo_.UpdateQuantity(currentSize_, quantity - 1);
                std::cout << "Added size " << currentSize_ << " to your order!" << std::endl;
            }
            else {
                std::cout << "Sorry, size " << currentSize_ << " is out of stock." << std::endl;
            }
        }
        catch (const std::invalid_argument&) {
            std::cout << "Error processing size " << currentSize_ << std::endl;
        }
    }
    else {
        std::cout << "'" << currentSize_ << "' is not a valid size for " << currentSubcategory_ << std::endl;
    }
}

void ClothingOrderBuilder::SelectColor() {
    std::cout << "\nAvailable colors:" << std::endl;
    for (const auto& color : availableColors_) {
        std::cout << "  - " << color << std::endl;
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