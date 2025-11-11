#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "DataLoader.h"

class SizeRepository {
public:
    SizeRepository();
    int GetAvailableQuantity(const std::string& sizeType) const;
    void UpdateQuantity(const std::string& sizeType, int newQuantity);

private:
    mutable std::unordered_map<std::string, std::vector<std::string>> data_;
};