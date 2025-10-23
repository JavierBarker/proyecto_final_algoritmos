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
    Libro(string isbn = "", string titulo = "", string autor = "", int anio = 0, string categoria = "", int cantidadDisponible = 0)
        : isbn(isbn), titulo(titulo), autor(autor), anio(anio), categoria(categoria), cantidadDisponible(cantidadDisponible) {}

    // Getters
    string getISBN() { return isbn; }
    string getTitulo() { return titulo; }
    string getAutor() { return autor; }
    int getAnio() { return anio; }
    string getCategoria() { return categoria; }
    int getCantidadDisponible() { return cantidadDisponible; }

    // Setters
    void setISBN(string& i) { isbn = i; }
    void setTitulo(string& t) { titulo = t; }
    void setAutor(string& a) { autor = a; }
    void setAnio(int an) { anio = an; }
    void setCategoria(string& c) { categoria = c; }
    void setCantidadDisponible(int cant) { cantidadDisponible = cant; }

    // Métodos funcionales
    bool estaDisponible() const;
    void mostrarInformacion() const;
};

#endif
