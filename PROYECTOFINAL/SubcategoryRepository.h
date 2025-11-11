#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "DataLoader.h"

class SubcategoryRepository {
public:
    SubcategoryRepository();
    int GetAvailableQuantity(const std::string& subcategoryType) const;
    void UpdateQuantity(const std::string& subcategoryType, int newQuantity);

private:
    mutable std::unordered_map<std::string, std::vector<std::string>> data_;
};