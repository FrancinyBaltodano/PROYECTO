#include "CategoryRepository.h"
#include <iostream>

CategoryRepository::CategoryRepository() {
    // Inicializa las categorías con stock
    categoryStock_["Ropa"] = 150;
    categoryStock_["Calzado"] = 80;
    categoryStock_["Accesorios"] = 120;

    // Ejemplo de subcategorías si quieres vincularlas
    data_["Ropa"] = { "Camiseta", "Pantalon", "Vestido" };
    data_["Calzado"] = { "Zapatos", "Sandalias" };
    data_["Accesorios"] = { "Gorra", "Bufanda" };
}

int CategoryRepository::GetAvailableQuantity(const std::string& categoryType) const {
    auto it = categoryStock_.find(categoryType);
    if (it != categoryStock_.end()) {
        return it->second;
    }
    return 0; // No encontrada
}


void CategoryRepository::UpdateQuantity(const std::string& categoryType, int newQuantity) {
    categoryStock_[categoryType] = newQuantity;
}

bool CategoryRepository::ReduceQuantity(const std::string& categoryType) {
    auto it = categoryStock_.find(categoryType);
    if (it != categoryStock_.end() && it->second > 0) {
        it->second--; // 🔻 Reducir stock
        std::cout << "Added " << categoryType << " to your order! (Remaining: " << it->second << ")\n";
        return true;
    }
    std::cout << "❌ Category not found or out of stock.\n";
    return false;
}

std::vector<std::string> CategoryRepository::GetAllCategories() const {
    std::vector<std::string> result;
    for (const auto& entry : categoryStock_) {
        result.push_back(entry.first);
    }
    return result;
}
