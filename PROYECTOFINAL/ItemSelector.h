#pragma once
#include <string>
#include <vector>

template<typename TRepository>
class ItemSelector {
public:
    ItemSelector(TRepository& repository, const std::vector<std::string>& availableItems, const std::string& itemType);

    void DisplayAvailableItems();
    bool AddItemToOrder(const std::string& itemName, std::vector<std::string>& selectedItems);

private:
    TRepository& repository_;
    const std::vector<std::string>& availableItems_;
    const std::string itemType_;
};