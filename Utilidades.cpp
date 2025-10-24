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

void Utilidades::limpiarPantallaValidar() {
    cout << "Presione cualquier tecla para continuar..." << endl;
    _getch();
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Utilidades::limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

string Utilidades::obtenerFechaActual() {
    time_t t = time(nullptr);            // Obtiene el tiempo actual del sistema
    tm* fechaLocal = localtime(&t);      // Lo convierte a formato local (día, mes, año, etc.)

    int dia = fechaLocal->tm_mday;
    int mes = fechaLocal->tm_mon + 1;    // tm_mon va de 0 a 11, por eso se suma 1
    int anio = fechaLocal->tm_year + 1900; // tm_year es años desde 1900

    // Convertimos a cadena con formato DD/MM/YYYY
    return (to_string(dia < 10 ? 0 : dia)) + "/" +
           (to_string(mes < 10 ? 0 : mes)) + "/" +
           to_string(anio);
}