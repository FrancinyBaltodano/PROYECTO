#include "ClothingOrderBuilder.h"
#include "ItemSelector.h"
#include "CategoryRepository.h";
#include "SubCategoryRepository.h";
#include <iostream>

ClothingOrderBuilder::ClothingOrderBuilder() {
}

void ClothingOrderBuilder::BuildOrder() {
    std::cout << "=== Clothing Store Order Builder ===" << std::endl;
    std::cout << "Let's build your order!" << std::endl;

    SelectCategory();
    SelectSubcategory();
    SelectSize();
    SelectColor();
}

    void ClothingOrderBuilder::DisplayFinalOrder() const {
        std::cout << "\n=== Your Order ===" << std::endl;

        if (selectedItems_.empty()) {
            std::cout << "No items selected." << std::endl;
        }
        else {
            std::cout << "Your order contains:" << std::endl;
            for (const auto& item : selectedItems_) {
                std::cout << "- " << item << std::endl;
            }
        }
    }


void ClothingOrderBuilder::SelectCategory() {
    ItemSelector<CategoryRepository> selector(categoryRepo_, availableCategories_, "category");

    selector.DisplayAvailableItems();

    std::cout << "\nEnter the category you want: ";
    std::string choice;
    std::getline(std::cin, choice);

    selector.AddItemToOrder(choice, selectedItems_);
}

void ClothingOrderBuilder::SelectSubcategory() {
    
        ItemSelector<SubcategoryRepository> selector(subcategoryRepo_, availableSubcategories_, "subcategory");
        selector.DisplayAvailableItems();

        std::cout << "\nEnter the type of clothing you want: ";
        std::string choice;
        std::getline(std::cin, choice);

        selector.AddItemToOrder(choice, selectedItems_);
    }

void ClothingOrderBuilder::SelectSize() {
 
}

void ClothingOrderBuilder::SelectColor() {
   
}


