#pragma once
#include <string>
#include <vector>
#include <map>

class CategoryRepository {
public:
    CategoryRepository();

    int GetAvailableQuantity(const std::string& categoryType) const;
    void UpdateQuantity(const std::string& categoryType, int newQuantity);
    bool ReduceQuantity(const std::string& categoryType);
    std::vector<std::string> GetAllCategories() const;

    // Hacer público el mapa de datos para poder acceder desde ClothingOrderBuilder
    std::map<std::string, std::vector<std::string>> data_;

private:
    std::map<std::string, int> categoryStock_;
};