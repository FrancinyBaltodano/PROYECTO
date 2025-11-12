#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "DataLoader.h"

class CategoryRepository {
public:
    CategoryRepository();

    // Devuelve cuántas unidades hay disponibles de una categoría
    int GetAvailableQuantity(const std::string& categoryType) const;

    // Actualiza manualmente la cantidad de una categoría
    void UpdateQuantity(const std::string& categoryType, int newQuantity);

    // Reduce la cantidad en 1 (si hay disponibles)
    bool ReduceQuantity(const std::string& categoryType);

    // Devuelve todas las categorías
    std::vector<std::string> GetAllCategories() const;

private:
    // category -> stock disponible
    std::unordered_map<std::string, int> categoryStock_;

    // category -> lista de subcategorías (por si DataLoader carga relaciones)
    mutable std::unordered_map<std::string, std::vector<std::string>> data_;
};
