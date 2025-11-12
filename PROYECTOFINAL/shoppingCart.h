#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct CartItem {
    std::string category;
    std::string subcategory;
    std::string size;
    std::string color;
    double price;
    int quantity;
};

class ShoppingCart {
public:
    ShoppingCart();

    void AddItem(const std::string& category, const std::string& subcategory,
        const std::string& size, const std::string& color, double price);
    void RemoveItem(int index);
    void ClearCart();

    double GetSubtotal() const;
    double GetTax() const;
    double GetTotal() const;

    const std::vector<CartItem>& GetItems() const;
    int GetItemCount() const;
    bool IsEmpty() const;

    void DisplayCart() const;

private:
    std::vector<CartItem> items_;
    const double TAX_RATE = 0.13; // 13% IVA en Costa Rica
};
