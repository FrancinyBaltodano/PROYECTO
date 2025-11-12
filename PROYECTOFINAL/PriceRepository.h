#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "DataLoader.h"

class PriceRepository {
public:
    PriceRepository();
    double GetPrice(const std::string& itemType) const;

private:
    mutable std::unordered_map<std::string, std::vector<std::string>> data_;
};
