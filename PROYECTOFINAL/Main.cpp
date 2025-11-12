#include "ClothingOrderBuilder.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

// Función simple de login - TODO EN UNO
bool HacerLogin() {
    // Usuarios y contraseñas predefinidos
    map<string, string> usuarios;
    usuarios["admin"] = "admin123";
    usuarios["cliente1"] = "pass123";
    usuarios["usuario"] = "1234";
    usuarios["tienda"] = "ropa2024";

    cout << "========================================" << endl;
    cout << "   TIENDA DE ROPA - SISTEMA DE LOGIN" << endl;
    cout << "========================================" << endl;

    int intentos = 0;
    int maxIntentos = 3;

    while (intentos < maxIntentos) {
        string usuario, password;

        cout << "\nUsuario: ";
        getline(cin, usuario);
        cout << "Contraseña: ";
        getline(cin, password);

        // Verificar si el usuario existe y la contraseña es correcta
        if (usuarios.find(usuario) != usuarios.end() && usuarios[usuario] == password) {
            cout << "\n? Login exitoso! Bienvenido, " << usuario << "!" << endl;
            cout << "========================================\n" << endl;
            return true;
        }
        else {
            intentos++;
            cout << "\n? Credenciales incorrectas. ";

            if (intentos < maxIntentos) {
                cout << "Intentos restantes: " << (maxIntentos - intentos) << endl;
            }
            else {
                cout << "Maximo de intentos alcanzado. Acceso denegado." << endl;
            }
        }
    }

    return false;
}

int main() {
    try {
        // PASO 1: Hacer login
        if (!HacerLogin()) {
            cout << "\n*** Acceso denegado. El programa se cerrara. ***" << endl;
            system("pause");
            return 1;
        }

        // PASO 2: Si login exitoso, entrar a la tienda
        ClothingOrderBuilder builder;
        builder.BuildOrder();
        builder.DisplayFinalOrder();

    }
    catch (const exception& ex) {
        cerr << "Error fatal: " << ex.what() << endl;
        system("pause");
        return 1;
    }

    system("pause");
    return 0;
}