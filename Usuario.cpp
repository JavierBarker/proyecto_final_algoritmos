#include "Usuario.h"
#include <iostream>
#include <fstream>

using namespace std;

 Usuario::Usuario(std::string id, std::string nombre, std::string carrera, std::string correo, std::string telefono);
    id(id), nombre(nombre), carrera(carrera), correo(correo), telefono(telefono), librosPrestados(0) {}

bool Usuario::puedePrestar() const{
    return librosPrestados < 4;
}
        
void Usuario::mostrarInformacion() const{
    cout << "ID: " << id << "\nNombre: " << nombre << "\nCarrera: " << carrera
        << "\nCorreo: " << correo << "\nTelefono: " << telefono
        << "\nLibros prestados: " << librosPrestados << endl; 
}

void Usuario::getid() const{
    return id;
}

void Usuario::guardarEnArchivo() const{
    ofstream archivo("Usuario.txt", ios::app);

if(archivo.is_open()){
    archivo << "ID: " << id
            << "Nombre: " << nombre
            << "Carrera: " << carrera
            << "Correo: " << correo
            << "Telefono: " << telefono
            << "Libros Prestados: " << librosPrestados << endl;
    archivo.close();
} else {
    cerr << "Error al abrir el archivo Usuario.txt" << endl;
    }   

}

