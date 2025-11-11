#include "SubcategoryRepository.h"
#include <stdexcept>

SubcategoryRepository::SubcategoryRepository() {
    auto data = DataLoader::LoadFromFile("subcategories.txt");
    data_ = std::move(data);
}

int SubcategoryRepository::GetAvailableQuantity(const std::string& subcategoryType) const {
    auto it = data_.find(subcategoryType);
    if (it == data_.end()) {
        throw std::invalid_argument("Unknown subcategory type: " + subcategoryType);
    }
    return std::stoi(it->second[0]);
}

void SubcategoryRepository::UpdateQuantity(const std::string& subcategoryType, int newQuantity) {
    auto it = data_.find(subcategoryType);
    if (it == data_.end()) {
        throw std::invalid_argument("Unknown subcategory type: " + subcategoryType);
    }
    it->second[0] = std::to_string(newQuantity);
}