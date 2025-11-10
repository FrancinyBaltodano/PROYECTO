#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "DataLoader.h"

class CategoryRepository {
public:
    CategoryRepository();
    int GetAvailableQuantity(const std::string& categoryType) const;
    void UpdateQuantity(const std::string& categoryType, int newQuantity);

private:
    mutable std::unordered_map<std::string, std::vector<std::string>> data_;
};