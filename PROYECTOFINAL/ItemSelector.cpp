#include "ItemSelector.h"
#include <iostream>

template<typename TRepository>
ItemSelector<TRepository>::ItemSelector(TRepository& repository, const std::vector<std::string>& availableItems, const std::string& itemType)
    : repository_(repository), availableItems_(availableItems), itemType_(itemType) {
}

template<typename TRepository>
void ItemSelector<TRepository>::DisplayAvailableItems() {
    std::cout << "\nAvailable " << itemType_ << ":" << std::endl;
    for (const auto& item : availableItems_) {
        try {
            int quantity = repository_.GetAvailableQuantity(item);
            std::cout << "- " << item << " (Available: " << quantity << ")" << std::endl;
        }
        catch (const std::invalid_argument&) {
            std::cout << "- " << item << " (Not available)" << std::endl;
        }
    }
}

template<typename TRepository>
bool ItemSelector<TRepository>::AddItemToOrder(const std::string& itemName, std::vector<std::string>& selectedItems) {
    try {
        int quantity = repository_.GetAvailableQuantity(itemName);
        if (quantity > 0) {
            selectedItems.push_back(itemName);
            repository_.UpdateQuantity(itemName, quantity - 1);
            std::cout << "Added " << itemName << " to your order!" << std::endl;
            return true;
        }
        else {
            std::cout << "Sorry, " << itemName << " is out of stock. Please choose another one." << std::endl;
            return false;
        }
    }
    catch (const std::invalid_argument&) {
        std::cout << "Sorry, " << itemName << " is not a valid " << itemType_ << ". Please choose from the available options." << std::endl;
        return false;
    }
}

// Template instantiations
#include "CategoryRepository.h"
template class ItemSelector<CategoryRepository>;

#include "SubcategoryRepository.h"
template class ItemSelector<SubcategoryRepository>;

#include "SizeRepository.h"
template class ItemSelector<SizeRepository>;



