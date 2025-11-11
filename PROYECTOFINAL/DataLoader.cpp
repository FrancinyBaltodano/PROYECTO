#include "DataLoader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

static inline std::string trim(const std::string& s) {
    auto start = s.find_first_not_of(" \t\r\n");
    auto end = s.find_last_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    return s.substr(start, end - start + 1);
}

std::unordered_map<std::string, std::vector<std::string>>
DataLoader::LoadFromFile(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("Cannot open file: " + path);
    }

    std::unordered_map<std::string, std::vector<std::string>> result;
    std::string line;
    int lineno = 0;

    while (std::getline(in, line)) {
        ++lineno;
        line = trim(line);
        if (line.empty()) continue;

        auto pos = line.find(':');
        if (pos == std::string::npos) {
            throw std::runtime_error("Invalid format at line " + std::to_string(lineno) + ": missing ':'");
        }

        std::string name = trim(line.substr(0, pos));
        std::string rest = trim(line.substr(pos + 1));

        std::vector<std::string> attributes;
        std::stringstream ss(rest);
        std::string item;

        while (std::getline(ss, item, ',')) {
            auto attr = trim(item);
            if (!attr.empty()) attributes.push_back(attr);
        }

        if (name.empty() || attributes.empty()) {
            throw std::runtime_error("Invalid entry at line " + std::to_string(lineno));
        }

        result[name] = std::move(attributes);
    }

    return result;
}