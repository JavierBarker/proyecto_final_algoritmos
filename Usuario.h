#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
private:
    std::string id;
    std::string nombre;
    std::string carrera;
    std::string correo;
    std::string telefono;
    int librosPrestados;

public:
    // Constructor
    Usuario(std::string id, std::string nombre, std::string carrera, std::string correo, std::string telefono);

    // Métodos
    bool puedePrestar() const;
    void mostrarInformacion() const;

    // Setters y getters
    void getid(const std::string& nuevoId);
    std::string getid() const;

    void guardarEnArchivo() const;
};

#endif

