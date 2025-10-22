#ifndef USUARIO_H
#define USUARIO_H

#include <string>

using namespace std;

class Usuario {
private:
    string id;
    string nombre;
    string carrera;
    string correo;
    string telefono;
    int librosPrestados;

public:
    // Constructor
    Usuario(string id="", string nombre="", string carrera="", string correo="", string telefono="", int librosPrestados=0)
        : id(id), nombre(nombre), carrera(carrera), correo(correo), telefono(telefono), librosPrestados(librosPrestados) {}

    // Métodos
    bool puedePrestar() const;

    // Setters y getters
    // getters
    string getId() { return id; }
    string getNombre() { return nombre; }
    string getCarrera() { return carrera; }
    string getCorreo() { return correo; }
    string getTelefono() { return telefono; }
    int getLibrosPrestados() { return librosPrestados; }

    // setters
    void setNombre(string& n) { nombre = n; }
    void setCarrera(string& c) { carrera = c; }
    void setCorreo(string& co) { correo = co; }
    void setTelefono(string& t) { telefono = t; }
    void setLibrosPrestados(int l) { librosPrestados = l; }
    
};

#endif

