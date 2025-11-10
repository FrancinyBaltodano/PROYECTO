#pragma once
#include <vector>
#include <string>
#include "CategoryRepository.h"


class ClothingOrderBuilder {
public:
    ClothingOrderBuilder();
    void BuildOrder();
    void DisplayFinalOrder() const;

private:
    void SelectCategory();
    void SelectSize();         
    void SelectColor();
    void SelectSubcategory();

    CategoryRepository categoryRepo_;
    

    std::vector<std::string> selectedItems_;

    const std::vector<std::string> availableCategories_ = { "Ropa", "Calzado", "Accesorios" };
    const std::vector<std::string> availableSubcategories_ = { "Camiseta", "Pantalon", "Vestido", "Sudadera", "Shorts", "Zapatos", "Gorra", "Bufanda" };
    const std::vector<std::string> availableSizes_ = { "XS", "S", "M", "L", "XL", "XXL", "28", "30", "32", "34", "36" };
    const std::vector<std::string> availableColors_ = { "Rojo", "Azul", "Negro", "Blanco", "Verde", "Amarillo", "Gris", "Rosa" };
};