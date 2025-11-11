#include "ColorRepository.h"
#include <stdexcept>

ColorRepository::ColorRepository() {
    auto data = DataLoader::LoadFromFile("colors.txt");
    data_ = std::move(data);
}

int ColorRepository::GetAvailableQuantity(const std::string& colorType) const {
    auto it = data_.find(colorType);
    if (it == data_.end()) {
        throw std::invalid_argument("Unknown color type: " + colorType);
    }
    return std::stoi(it->second[0]);
}

void ColorRepository::UpdateQuantity(const std::string& colorType, int newQuantity) {
    auto it = data_.find(colorType);
    if (it == data_.end()) {
        throw std::invalid_argument("Unknown color type: " + colorType);
    }
    it->second[0] = std::to_string(newQuantity);
}