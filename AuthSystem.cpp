#include "AuthSystem.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Definir el nombre del archivo donde se guardan los usuarios
const char* AuthSystem::ARCHIVO_USUARIOS = "users.txt";

// Constructor: se ejecuta automáticamente al crear un objeto AuthSystem
AuthSystem::AuthSystem() {
    CargarUsuariosDesdeArchivo();
}

// Función para cargar usuarios desde el archivo users.txt
void AuthSystem::CargarUsuariosDesdeArchivo() {
    ifstream archivo(ARCHIVO_USUARIOS);

    // Si el archivo no existe, crear usuarios por defecto
    if (!archivo.is_open()) {
        cout << "Archivo no encontrado. Creando usuarios por defecto..." << endl;
        usuarios["admin"] = "admin123";
        usuarios["cliente1"] = "pass123";
        usuarios["usuario"] = "1234";
        usuarios["tienda"] = "ropa2024";
        GuardarUsuariosEnArchivo();
        return;
    }

    // Leer el archivo línea por línea
    string linea;
    while (getline(archivo, linea)) {
        // Buscar el símbolo ':' que separa usuario y contraseña
        int posicionDosPuntos = linea.find(':');

        if (posicionDosPuntos != string::npos) {
            // Extraer usuario (antes de ':')
            string usuario = linea.substr(0, posicionDosPuntos);
            // Extraer contraseña (después de ':')
            string password = linea.substr(posicionDosPuntos + 1);

            // Guardar en el mapa
            usuarios[usuario] = password;
        }
    }

    archivo.close();
    cout << "Usuarios cargados correctamente." << endl;
}

// Función para guardar todos los usuarios en el archivo
void AuthSystem::GuardarUsuariosEnArchivo() {
    ofstream archivo(ARCHIVO_USUARIOS);

    // Recorrer todos los usuarios y escribirlos en el archivo
    for (const auto& par : usuarios) {
        archivo << par.first << ":" << par.second << endl;
    }

    archivo.close();
}

// Función principal de Login
bool AuthSystem::Login() {
    cout << "========================================" << endl;
    cout << "   TIENDA DE ROPA - SISTEMA DE LOGIN" << endl;
    cout << "========================================" << endl;
    cout << "1. Iniciar sesion" << endl;
    cout << "2. Registrar nuevo usuario" << endl;
    cout << "Elige una opcion: ";

    int opcion;
    cin >> opcion;
    cin.ignore(); // Limpiar el buffer

    // Si el usuario quiere registrarse
    if (opcion == 2) {
        string nuevoUsuario, nuevaPassword;

        cout << "\nNuevo usuario: ";
        getline(cin, nuevoUsuario);
        cout << "Nueva contraseña: ";
        getline(cin, nuevaPassword);

        if (RegisterUser(nuevoUsuario, nuevaPassword)) {
            cout << "\n? Usuario registrado exitosamente! Ahora puedes iniciar sesion.\n" << endl;
        }
        else {
            cout << "\n? El usuario ya existe!\n" << endl;
        }
    }

    // Proceso de login (máximo 3 intentos)
    int intentos = 0;

    while (intentos < MAX_INTENTOS) {
        string usuario, password;

        cout << "\nUsuario: ";
        getline(cin, usuario);
        cout << "Contraseña: ";
        getline(cin, password);

        // Validar las credenciales
        if (ValidarCredenciales(usuario, password)) {
            usuarioActual = usuario;
            cout << "\n? Login exitoso! Bienvenido, " << usuario << "!" << endl;
            cout << "========================================\n" << endl;
            return true;
        }
        else {
            intentos++;
            cout << "\n? Credenciales incorrectas. ";

            if (intentos < MAX_INTENTOS) {
                cout << "Intentos restantes: " << (MAX_INTENTOS - intentos) << endl;
            }
            else {
                cout << "Maximo de intentos alcanzado. Acceso denegado." << endl;
            }
        }
    }

    return false;
}

// Validar si el usuario y contraseña son correctos
bool AuthSystem::ValidarCredenciales(const string& username, const string& password) {
    // Buscar el usuario en el mapa
    auto busqueda = usuarios.find(username);

    // Si el usuario existe y la contraseña coincide
    if (busqueda != usuarios.end() && busqueda->second == password) {
        return true;
    }

    return false;
}

// Registrar un nuevo usuario
bool AuthSystem::RegisterUser(const string& username, const string& password) {
    // Verificar si el usuario ya existe
    if (usuarios.find(username) != usuarios.end()) {
        return false; // Usuario ya existe
    }

    // Agregar el nuevo usuario
    usuarios[username] = password;
    GuardarUsuariosEnArchivo();
    return true;
}

// Obtener el nombre del usuario actual
string AuthSystem::GetCurrentUser() const {
    return usuarioActual;
}