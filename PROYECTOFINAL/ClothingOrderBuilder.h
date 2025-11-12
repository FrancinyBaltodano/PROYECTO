#pragma once
#include <vector>
#include <string>
#include <memory>
#include "CategoryRepository.h"
#include "SubcategoryRepository.h"
#include "SizeRepository.h"
#include "PriceRepository.h"
#include "ShoppingCart.h"
#include "PaymentMethod.h"

class ClothingOrderBuilder {
public:
    ClothingOrderBuilder();
    void Run();

private:
    void BuildOrder();
    void DisplayFinalOrder() const;
    void ProcessCheckout();
    void SelectPaymentMethod();


    void SelectCategory();
    void SelectSize();
    void SelectColor();
    void SelectSubcategory();

    CategoryRepository categoryRepo_;
    SubcategoryRepository subcategoryRepo_;
    SizeRepository sizeRepo_;
    PriceRepository priceRepo_;
    ShoppingCart cart_;

    std::unique_ptr<PaymentMethod> paymentMethod_;

    std::vector<std::string> selectedItems_;
    std::string currentCategory_;
    std::string currentSubcategory_;
    std::string currentSize_;
    std::string currentColor_;

    const std::vector<std::string> availableCategories_ = { "Ropa", "Calzado", "Accesorios" };
    const std::vector<std::string> availableSubcategories_ = { "Camiseta", "Pantalon", "Vestido", "Sudadera", "Shorts", "Zapatos", "Gorra", "Bufanda" };
    const std::vector<std::string> availableSizes_ = { "XS", "S", "M", "L", "XL", "XXL", "28", "30", "32", "34", "36" };
    const std::vector<std::string> availableColors_ = { "Rojo", "Azul", "Negro", "Blanco", "Verde", "Amarillo", "Gris", "Rosa" };
};