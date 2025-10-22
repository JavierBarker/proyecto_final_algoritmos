#ifndef LIBRO_H
#define LIBRO_H

#include <string>
using namespace std;

class Libro {
private:
    string isbn;
    string titulo;
    string autor;
    int anio;
    string categoria;
    int cantidadDisponible;

public:
    // Constructor por defecto
    Libro();

    // Constructor con parámetros
    Libro(string isbn, string titulo, string autor, int anio, string categoria, int cantidad);

    // Getters
    string getISBN() const;
    string getTitulo() const;
    string getAutor() const;
    int getAnio() const;
    string getCategoria() const;
    int getCantidadDisponible() const;

    // Setters
    void setISBN(const string& isbn);
    void setTitulo(const string& titulo);
    void setAutor(const string& autor);
    void setAnio(int anio);
    void setCategoria(const string& categoria);
    void setCantidadDisponible(int cantidad);

    // Métodos funcionales
    bool estaDisponible() const;
    void mostrarInformacion() const;

    // Métodos de archivo (para CRUD)
    static void registrarLibro();
    static void listarLibros();
    static void buscarLibro();
    static void eliminarLibro();
};

#endif
