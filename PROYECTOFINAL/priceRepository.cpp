#include "PriceRepository.h"
#include <stdexcept>

PriceRepository::PriceRepository() {
    auto data = DataLoader::LoadFromFile("prices.txt");
    data_ = std::move(data);
}

double PriceRepository::GetPrice(const std::string& itemType) const {
    auto it = data_.find(itemType);
    if (it == data_.end()) {
        throw std::invalid_argument("Unknown item type: " + itemType);
    }
    return std::stod(it->second[0]);
}