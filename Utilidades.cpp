#include "Utilidades.h"
#include <iostream>
#include <string>

#ifdef _WIN32
#include <conio.h>
#endif

using namespace std;

bool Utilidades::autenticar(string& usuario, string& contrasena) {
    string usuarioAdmin = "admin";
    string passAdmin = "admin";

    return (usuario == passAdmin && contrasena == passAdmin);
}

void Utilidades::limpiarPantalla() {
    cout << "Presione cualquier tecla para continuar..." << endl;
    _getch();
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
