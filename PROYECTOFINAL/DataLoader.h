#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class DataLoader {
public:
    // Loads "item -> attributes" (WITHOUT base attributes) from a file.
    static std::unordered_map<std::string, std::vector<std::string>>
        LoadFromFile(const std::string& path);
};