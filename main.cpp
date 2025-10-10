#include <windows.h>
#include "SistemaBiblioteca.h"
#include "Utilidades.h"
#include <string>
#include <iostream>



using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8); 
    // Crear una instancia del sistema de biblioteca he invocar el programa
    SistemaBiblioteca sistema;
    Utilidades utilidades;
    string usuario, contrasena;

    do
    {
        cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                 SISTEMA DE GESTIÓN DE BIBLIOTECA             ║" << endl;
        cout << "╠══════════════════════════════════════════════════════════════╣" << endl;

        cout << "║ Ingrese el Usuario: ";
        getline(cin, usuario);
        cout << "║ Ingrese su contraseña: ";
        getline(cin, contrasena);

        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;

        if (utilidades.autenticar(usuario, contrasena)){
            sistema.mostrarMenu();
        } else {
            cout << "\nUsuario o contraseña incorrectos.  🚨" << endl;
            utilidades.limpiarPantalla();
        }
    } while (utilidades.autenticar(usuario, contrasena) != true);
    


    return 0;
}