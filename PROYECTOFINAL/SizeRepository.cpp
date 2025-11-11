#include "SizeRepository.h"
#include <stdexcept>

SizeRepository::SizeRepository() {
    auto data = DataLoader::LoadFromFile("sizes.txt");
    data_ = std::move(data);
}

int SizeRepository::GetAvailableQuantity(const std::string& sizeType) const {
    auto it = data_.find(sizeType);
    if (it == data_.end()) {
        throw std::invalid_argument("Unknown size type: " + sizeType);
    }
    return std::stoi(it->second[0]);
}

void SizeRepository::UpdateQuantity(const std::string& sizeType, int newQuantity) {
    auto it = data_.find(sizeType);
    if (it == data_.end()) {
        throw std::invalid_argument("Unknown size type: " + sizeType);
    }
    it->second[0] = std::to_string(newQuantity);
}