#include "ClothingOrderBuilder.h"
#include <iostream>

int main() {
    try {
        ClothingOrderBuilder builder;
        builder.BuildOrder();
        builder.DisplayFinalOrder();
    }
    catch (const std::exception& ex) {
        std::cerr << "Fatal error: " << ex.what() << std::endl;
        return 1;
    }

    system("pause");
    return 0;
}
