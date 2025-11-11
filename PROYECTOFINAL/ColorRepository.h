#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "DataLoader.h"

class ColorRepository {
public:
    ColorRepository();
    int GetAvailableQuantity(const std::string& colorType) const;
    void UpdateQuantity(const std::string& colorType, int newQuantity);

private:
    mutable std::unordered_map<std::string, std::vector<std::string>> data_;
};