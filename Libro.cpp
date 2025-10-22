#include "Libro.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;


Libro::Libro() {}

Libro::Libro(string isbn, string titulo, string autor, int anio, string categoria, int cantidad) {
    this->isbn = isbn;
    this->titulo = titulo;
    this->autor = autor;
    this->anio = anio;
    this->categoria = categoria;
    this->cantidadDisponible = cantidad;
}


string Libro::getISBN() const { return isbn; }
string Libro::getTitulo() const { return titulo; }
string Libro::getAutor() const { return autor; }
int Libro::getAnio() const { return anio; }
string Libro::getCategoria() const { return categoria; }
int Libro::getCantidadDisponible() const { return cantidadDisponible; }


void Libro::setISBN(const string& isbn) { this->isbn = isbn; }
void Libro::setTitulo(const string& titulo) { this->titulo = titulo; }
void Libro::setAutor(const string& autor) { this->autor = autor; }
void Libro::setAnio(int anio) { this->anio = anio; }
void Libro::setCategoria(const string& categoria) { this->categoria = categoria; }
void Libro::setCantidadDisponible(int cantidad) { this->cantidadDisponible = cantidad; }


bool Libro::estaDisponible() const {
    return cantidadDisponible > 0;
}

void Libro::mostrarInformacion() const {
    cout << "\nISBN: " << isbn
         << "\nTítulo: " << titulo
         << "\nAutor: " << autor
         << "\nAño: " << anio
         << "\nCategoría: " << categoria
         << "\nCantidad disponible: " << cantidadDisponible << endl;
}


static vector<Libro> cargarLibros() {
    vector<Libro> libros;
    ifstream archivo("libros.txt");
    if (!archivo.is_open()) return libros;

    string isbn, titulo, autor, categoria;
    int anio, cantidad;

    while (archivo >> ws && getline(archivo, isbn, '|')) {
        getline(archivo, titulo, '|');
        getline(archivo, autor, '|');
        archivo >> anio;
        archivo.ignore();
        getline(archivo, categoria, '|');
        archivo >> cantidad;
        archivo.ignore();

        libros.emplace_back(isbn, titulo, autor, anio, categoria, cantidad);
    }

    archivo.close();
    return libros;
}

static void guardarLibros(const vector<Libro>& libros) {
    ofstream archivo("libros.txt", ios::trunc);
    for (const auto& libro : libros) {
        archivo << libro.getISBN() << "|"
                << libro.getTitulo() << "|"
                << libro.getAutor() << "|"
                << libro.getAnio() << "|"
                << libro.getCategoria() << "|"
                << libro.getCantidadDisponible() << "\n";
    }
    archivo.close();
}

//Registrar, Listar, Buscar, Eliminar
void Libro::registrarLibro() {
    string isbn, titulo, autor, categoria;
    int anio, cantidad;

    cout << "\n=== Registrar nuevo libro ===\n";
    cout << "ISBN: ";
    getline(cin, isbn);
    cout << "Título: ";
    getline(cin, titulo);
    cout << "Autor: ";
    getline(cin, autor);
    cout << "Año: ";
    cin >> anio;
    cin.ignore();
    cout << "Categoría: ";
    getline(cin, categoria);
    cout << "Cantidad disponible: ";
    cin >> cantidad;
    cin.ignore();

    ofstream archivo("libros.txt", ios::app);
    archivo << isbn << "|" << titulo << "|" << autor << "|" << anio << "|" << categoria << "|" << cantidad << "\n";
    archivo.close();

    cout << "Libro registrado exitosamente.\n";
}

void Libro::listarLibros() {
    vector<Libro> libros = cargarLibros();
    if (libros.empty()) {
        cout << "No hay libros registrados.\n";
        return;
    }

    cout << "\n=== Lista de Libros ===\n";
    for (const auto& libro : libros) {
        libro.mostrarInformacion();
    }
}

void Libro::buscarLibro() {
    vector<Libro> libros = cargarLibros();
    if (libros.empty()) {
        cout << "No hay libros registrados.\n";
        return;
    }

    string busqueda;
    cout << "\nIngrese título, autor o ISBN a buscar: ";
    getline(cin, busqueda);

    bool encontrado = false;
    for (const auto& libro : libros) {
        if (libro.getISBN() == busqueda ||
            libro.getTitulo() == busqueda ||
            libro.getAutor() == busqueda) {
            libro.mostrarInformacion();
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontró ningún libro con ese dato.\n";
    }
}

void Libro::eliminarLibro() {
    vector<Libro> libros = cargarLibros();
    if (libros.empty()) {
        cout << "No hay libros registrados.\n";
        return;
    }

    string isbnEliminar;
    cout << "\nIngrese el ISBN del libro a eliminar: ";
    getline(cin, isbnEliminar);

    bool eliminado = false;
    vector<Libro> nuevos;

    for (const auto& libro : libros) {
        if (libro.getISBN() != isbnEliminar) {
            nuevos.push_back(libro);
        } else {
            eliminado = true;
        }
    }

    if (eliminado) {
        guardarLibros(nuevos);
        cout << "\nLibro eliminado correctamente.\n";
    } else {
        cout << "\nNo se encontró un libro con ese ISBN.\n";
    }
}
