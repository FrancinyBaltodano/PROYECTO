#include "CategoryRepository.h"
#include <stdexcept>

CategoryRepository::CategoryRepository() {
    auto data = DataLoader::LoadFromFile("categories.txt");
    data_ = std::move(data);
}

int CategoryRepository::GetAvailableQuantity(const std::string& categoryType) const {
    auto it = data_.find(categoryType);
    if (it == data_.end()) {
        throw std::invalid_argument("Unknown category type: " + categoryType);
    }
    return std::stoi(it->second[0]);
}

void CategoryRepository::UpdateQuantity(const std::string& categoryType, int newQuantity) {
    auto it = data_.find(categoryType);
    if (it == data_.end()) {
        throw std::invalid_argument("Unknown category type: " + categoryType);
    }
    it->second[0] = std::to_string(newQuantity);
}