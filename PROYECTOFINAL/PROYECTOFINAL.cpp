#include <iostream>
#include "Ropa.h"
#include "Carrito.h"

int main() {
    Ropa camisa("Camisa", "Camisa Polo", 25.99, 10, "M");
    Ropa shortt("Short", "Short Deportivo", 19.50, 8, "L");
    Ropa zapato("Zapato", "Tenis Nike", 59.99, 5, "42");

    Carrito carrito;

    int opcion;
    do {
        std::cout << "\n--- Tienda de Ropa ---\n";
        std::cout << "1. Ver productos\n";
        std::cout << "2. Agregar producto al carrito\n";
        std::cout << "3. Ver carrito\n";
        std::cout << "4. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
        case 1:
            camisa.MostrarInfo();
            shortt.MostrarInfo();
            zapato.MostrarInfo();
            break;
        case 2: {
            int eleccion;
            std::cout << "1. Camisa\n2. Short\n3. Zapato\n";
            std::cout << "Elija producto: ";
            std::cin >> eleccion;

            if (eleccion == 1) carrito.AgregarProducto(&camisa);
            else if (eleccion == 2) carrito.AgregarProducto(&shortt);
            else if (eleccion == 3) carrito.AgregarProducto(&zapato);
            break;
        }
        case 3:
            carrito.MostrarCarrito();
            break;
        }
    } while (opcion != 4);

    return 0;
}
