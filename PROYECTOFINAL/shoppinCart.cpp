#include "ShoppingCart.h"
#include <iostream>
#include <iomanip>

ShoppingCart::ShoppingCart() {
}

void ShoppingCart::AddItem(const std::string& category, const std::string& subcategory,
    const std::string& size, const std::string& color, double price) {
    CartItem item;
    item.category = category;
    item.subcategory = subcategory;
    item.size = size;
    item.color = color;
    item.price = price;
    item.quantity = 1;

    items_.push_back(item);
    std::cout << "Item added to cart!" << std::endl;
}

void ShoppingCart::RemoveItem(int index) {
    if (index >= 0 && index < static_cast<int>(items_.size())) {
        items_.erase(items_.begin() + index);
        std::cout << "Item removed from cart." << std::endl;
    }
    else {
        std::cout << "Invalid item index." << std::endl;
    }
}

void ShoppingCart::ClearCart() {
    items_.clear();
    std::cout << "Cart cleared." << std::endl;
}

double ShoppingCart::GetSubtotal() const {
    double subtotal = 0.0;
    for (const auto& item : items_) {
        subtotal += item.price * item.quantity;
    }
    return subtotal;
}

double ShoppingCart::GetTax() const {
    return GetSubtotal() * TAX_RATE;
}

double ShoppingCart::GetTotal() const {
    return GetSubtotal() + GetTax();
}

const std::vector<CartItem>& ShoppingCart::GetItems() const {
    return items_;
}

int ShoppingCart::GetItemCount() const {
    return static_cast<int>(items_.size());
}

bool ShoppingCart::IsEmpty() const {
    return items_.empty();
}

void ShoppingCart::DisplayCart() const {
    std::cout << "\n=== Shopping Cart ===" << std::endl;

    if (items_.empty()) {
        std::cout << "Your cart is empty." << std::endl;
        return;
    }

    std::cout << std::fixed << std::setprecision(2);

    for (size_t i = 0; i < items_.size(); ++i) {
        const auto& item = items_[i];
        std::cout << (i + 1) << ". " << item.subcategory
            << " - Size: " << item.size
            << " - Color: " << item.color
            << " - $" << item.price << std::endl;
    }

    std::cout << "\n--------------------------" << std::endl;
    std::cout << "Subtotal: $" << GetSubtotal() << std::endl;
    std::cout << "Tax (13%): $" << GetTax() << std::endl;
    std::cout << "Total: $" << GetTotal() << std::endl;
    std::cout << "--------------------------\n" << std::endl;
}