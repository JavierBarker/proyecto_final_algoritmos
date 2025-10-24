#include "SistemaBiblioteca.h"
#include "Utilidades.h"
#include "Usuario.h"
#include "Libro.h"
#include "Prestamo.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>


using namespace std;

//Variables Globales
Utilidades utilidades;
Usuario usuario;
Libro libro;
Prestamo prestamo;

//vectores
vector<Usuario> usuarios;
vector<Libro> libros;
vector<Prestamo> prestamos;


string usuariosTxt = "usuarios.txt";
string librosTxt = "libros.txt";
string prestamosTxt = "prestamos.txt";

void SistemaBiblioteca::mostrarMenu() {
    utilidades.limpiarPantalla();
    int opcion;

    do
    {
        cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║              === SISTEMA DE BIBLIOTECA ===                   ║" << endl;
        cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
        cout << "║ 1. Gestión de Libros                                         ║" << endl;
        cout << "║ 2. Gestión de Usuarios                                       ║" << endl;
        cout << "║ 3. Gestión de Prestamos                                      ║" << endl;
        cout << "║ 4. Reportes y Estadísticas                                   ║" << endl;
        cout << "║ 5. Guardar y Salir                                           ║" << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;

        cout << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer de entrada
        cout << endl; 

        switch (opcion)
        {
        case 1:
            utilidades.limpiarPantalla();
            mostrarMenuGestionLibro();
            break;
        case 2:
            utilidades.limpiarPantalla();
            mostrarMenuGestionUsuario();
           break;
           
        case 3:
            utilidades.limpiarPantalla();
            mostrarMenuGestionPrestamo();
            break;
        case 4:
            utilidades.limpiarPantalla();
            mostrarMenuGestionReportes();
            break;
        
        case 5:
            utilidades.limpiarPantalla();
            cout << endl;
            generarReporteGeneralTxt();
            cout << endl;
            cout << "Saliendo del programa... 🫡" << endl;
            cout << endl;
            break;
        default:
            utilidades.limpiarPantalla();
            cout << endl;
            cout << "Opción inválida. Por favor, intente de nuevo. 🚨" << endl;
            cout << endl;
            break;
        }
    } while (opcion != 5);
}


//CRUD USUARIOS
void SistemaBiblioteca::cargarUsuarios(){
    ifstream archivo(usuariosTxt);
    string lineaTexto;

    while (getline(archivo, lineaTexto)){

        stringstream infoLineaTexto(lineaTexto);
        string id, nombre, carrera, correo, telefono, librosPrestados;

        getline(infoLineaTexto, id, ';');
        getline(infoLineaTexto, nombre, ';');
        getline(infoLineaTexto, carrera, ';');
        getline(infoLineaTexto, correo, ';');
        getline(infoLineaTexto, telefono, ';');
        getline(infoLineaTexto, librosPrestados, ';');

        if (id == "ID") continue;
        usuarios.push_back(Usuario(id, nombre, carrera, correo, telefono, stoi(librosPrestados)));
    }

    archivo.close();
}

void SistemaBiblioteca::guardarUsuarios(){
    ofstream archivo(usuariosTxt, ios::trunc);

    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo Usuario.txt" << endl;
    }else{
        archivo << "ID;Nombre;Carrera;Correo;Telefono;LibrosPrestados" << endl;
        for (size_t i = 0; i < usuarios.size(); i++)
        {
            archivo 
                << usuarios[i].getId() << ";"
                << usuarios[i].getNombre() << ";"
                << usuarios[i].getCarrera() << ";"
                << usuarios[i].getCorreo() << ";"
                << usuarios[i].getTelefono() << ";"
                << usuarios[i].getLibrosPrestados() << endl;
        }

        archivo.close();
    }
}

bool SistemaBiblioteca::agregarUsuario(){
    cargarUsuarios();

    string nombre, carrera, correo, telefono;
    int idUsuario = stoi(usuarios[usuarios.size() - 1].getId()) + 1;
    
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║              === Registrar Usuario No. " << idUsuario << " ===                 ║" << endl;
    cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
    cout << "║ Nombre: "; getline(cin, nombre);
    cout << "║ Carrera: "; getline(cin, carrera); 
    cout << "║ Correo: "; getline(cin, correo);
    cout << "║ Telefono: "; getline(cin, telefono);
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;


    cout << endl;
    cout << " Usuario registrado correctamente ✅ " << endl;

    usuarios.push_back(Usuario(to_string(idUsuario), nombre, carrera, correo, telefono, 0));
    guardarUsuarios();
    
    usuarios.clear();
    return true;
}

void SistemaBiblioteca::buscarUsuario(){
    cargarUsuarios();
    string buscar;
    int encontrado;

    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ === Buscar Usuario por ID o Nombre ===                       ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << "   Ingrese el Id o Nombre: ";
    getline(cin, buscar);
    cout << endl;

    for (size_t i = 0; i < usuarios.size(); i++)
    {
        if (usuarios[i].getId() == buscar || usuarios[i].getNombre() == buscar)
        {
            cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
            cout << "  Usuario No. " << usuarios[i].getId() << endl;
            cout << "  Nombre: " << usuarios[i].getNombre() << endl;
            cout << "  Carrera: " << usuarios[i].getCarrera() << endl;
            cout << "  Correo: " << usuarios[i].getCorreo() << endl;
            cout << "  Telefono: " << usuarios[i].getTelefono() << endl;
            cout << "  Libros Prestados: " << usuarios[i].getLibrosPrestados() << endl;
            cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
            cout << endl;
            cout << "Usuario Encontrado. ✅" << endl;
            encontrado = 1;
        } 
    }

    if (encontrado != 1) cout << "Usuario no Encontrado. 🚨" << endl;
    usuarios.clear();
}

void SistemaBiblioteca::listarUsuarios(){
    cargarUsuarios();

    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ === Lista de Usuarios ===                                    ║" << endl;

    for (size_t i = 0; i < usuarios.size(); i++)
    {
        cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
        cout << "  Usuario No. " << usuarios[i].getId() << endl;
        cout << "  Nombre: " << usuarios[i].getNombre() << endl;
        cout << "  Carrera: " << usuarios[i].getCarrera() << endl;
        cout << "  Correo: " << usuarios[i].getCorreo() << endl;
        cout << "  Telefono: " << usuarios[i].getTelefono() << endl;
        cout << "  Libros Prestados: " << usuarios[i].getLibrosPrestados() << endl;
    }
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;
    usuarios.clear();
}

void SistemaBiblioteca::actualizarUsuario(){
    cargarUsuarios();
    string buscar;
    int encontrado, posicion;

    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ === Actualizar Usuario ===                                   ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << "   Ingrese el Id o Nombre: ";
    getline(cin, buscar);
    cout << endl;

    for (size_t i = 0; i < usuarios.size(); i++)
    {
        if (usuarios[i].getId() == buscar || usuarios[i].getNombre() == buscar)
        {
            cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
            cout << "  Usuario No. " << usuarios[i].getId() << endl;
            cout << "  Nombre: " << usuarios[i].getNombre() << endl;
            cout << "  Carrera: " << usuarios[i].getCarrera() << endl;
            cout << "  Correo: " << usuarios[i].getCorreo() << endl;
            cout << "  Telefono: " << usuarios[i].getTelefono() << endl;
            cout << "  Libros Prestados: " << usuarios[i].getLibrosPrestados() << endl;
            cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
            cout << endl;
            cout << "Usuario Encontrado. ✅" << endl;
            encontrado = 1;
            posicion = i;
        } 
    }

    if (encontrado == 1){
        //actualizar usuario
        string nombre, carrera, correo, telefono, librosPrestados;
        
        cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║  === Ingrese los Nuevos Valores ===                          ║" << endl;
        cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
        cout << "║ Usuario No. " << usuarios[posicion].getId() << endl;
        cout << "║ Nombre: "; getline(cin, nombre);
        cout << "║ Carrera: "; getline(cin, carrera); 
        cout << "║ Correo: "; getline(cin, correo);
        cout << "║ Telefono: "; getline(cin, telefono);
        cout << "║ Libros Prestados: "; getline(cin, librosPrestados);
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;

        //actualizamos los datos
        usuarios[posicion].setNombre(nombre);
        usuarios[posicion].setCarrera(carrera);
        usuarios[posicion].setCorreo(correo);
        usuarios[posicion].setTelefono(telefono);
        usuarios[posicion].setLibrosPrestados(stoi(librosPrestados));
        guardarUsuarios();

        cout << "Usuario Actualizado. ✅" << endl;
    }else{
        cout << "Usuario no Encontrado. 🚨" << endl;
    }

    usuarios.clear();
}

void SistemaBiblioteca::eliminarUsuario(){
    cargarUsuarios();
    string buscar;
    int encontrado, posicion;

    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ === Eliminar Usuario ===                                     ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << "   Ingrese el Id o Nombre: ";
    getline(cin, buscar);
    cout << endl;

    for (size_t i = 0; i < usuarios.size(); i++)
    {
        if (usuarios[i].getId() == buscar || usuarios[i].getNombre() == buscar)
        {
            cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
            cout << "  Usuario No. " << usuarios[i].getId() << endl;
            cout << "  Nombre: " << usuarios[i].getNombre() << endl;
            cout << "  Carrera: " << usuarios[i].getCarrera() << endl;
            cout << "  Correo: " << usuarios[i].getCorreo() << endl;
            cout << "  Telefono: " << usuarios[i].getTelefono() << endl;
            cout << "  Libros Prestados: " << usuarios[i].getLibrosPrestados() << endl;
            cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
            cout << endl;
            cout << "Usuario Encontrado. ✅" << endl;
            encontrado = 1;
            posicion = i;
        } 
    }

    string respuesta;
    if (encontrado == 1){
        cout << "Desea Eliminar el Usuario? 🚧 (S/N): ";
        getline(cin, respuesta);

        if (respuesta == "S" || respuesta == "s")
        {
            usuarios.erase(usuarios.begin() + posicion);
        }
        guardarUsuarios();
        cout << "Usuario Eliminado. ✅" << endl;
    }else{
        cout << "Usuario no Encontrado. 🚨" << endl;
    }

    usuarios.clear();
}

void SistemaBiblioteca::mostrarMenuGestionUsuario()
{
    int opcion2;
    do
    {
        cout << endl;
        cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║              === GESTIÓN DE USUARIOS ===                     ║" << endl;
        cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
        cout << "║ 1. Registrar Usuario                                         ║" << endl;
        cout << "║ 2. Buscar Usuario                                            ║" << endl;
        cout << "║ 3. Listar Usuarios                                           ║" << endl;
        cout << "║ 4. Actualizar Usuario                                        ║" << endl;
        cout << "║ 5. Eliminar Usuario                                          ║" << endl;
        cout << "║ 6. Regresar                                                  ║" << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;

        cout << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion2;
        cin.ignore(); // Limpiar el buffer de entrada
        cout << endl;

        switch (opcion2)
        {
        case 1:
        {
            agregarUsuario();
            utilidades.limpiarPantallaValidar();
            cout << endl;
        }
        break;

        case 2:
            buscarUsuario();
            utilidades.limpiarPantallaValidar();
            cout << endl;
            break;

        case 3:
            listarUsuarios();
            utilidades.limpiarPantallaValidar();
            cout << endl;
            break;

        case 4:
            actualizarUsuario();
            utilidades.limpiarPantallaValidar();
            cout << endl;
            break;

        case 5:
            eliminarUsuario();
            utilidades.limpiarPantallaValidar();
            cout << endl;
            break;

        case 6:
            utilidades.limpiarPantalla();
            cout << endl;
            break;
        default:
            utilidades.limpiarPantalla();
            cout << endl;
            cout << "Opción inválida. Por favor, intente de nuevo. 🚨" << endl;
            cout << endl;
            break;
        }
    } while (opcion2 != 6);
}












//CRUD LIBROS
void SistemaBiblioteca::cargarLibros(){
    ifstream archivo(librosTxt);
    string lineaTexto;

    while (getline(archivo, lineaTexto)){

        stringstream infoLineaTexto(lineaTexto);
        string isbn, titulo, autor, anio, categoria, cantidadDisponible;

        getline(infoLineaTexto, isbn, ';');
        getline(infoLineaTexto, titulo, ';');
        getline(infoLineaTexto, autor, ';');
        getline(infoLineaTexto, anio, ';');
        getline(infoLineaTexto, categoria, ';');
        getline(infoLineaTexto, cantidadDisponible, ';');

        if (isbn == "ISBN") continue;
        libros.push_back(Libro(isbn, titulo, autor, stoi(anio), categoria, stoi(cantidadDisponible)));
    }

    archivo.close();
}

void SistemaBiblioteca::guardarLibros(){
    ofstream archivo(librosTxt, ios::trunc);

    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo libros.txt" << endl;
    }else{
        archivo << "ISBN;Titulo;Autor;Año;Categoria;Cantidad" << endl;
        for (size_t i = 0; i < libros.size(); i++)
        {
            archivo 
                << libros[i].getISBN() << ";"
                << libros[i].getTitulo() << ";"
                << libros[i].getAutor() << ";"
                << libros[i].getAnio() << ";"
                << libros[i].getCategoria() << ";"
                << libros[i].getCantidadDisponible() << endl;
        }

        archivo.close();
    }
}

bool SistemaBiblioteca::agregarLibro(){
    cargarLibros();

    string isbn, titulo, autor, anio, categoria, cantidadDisponible;
    
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║              === Registrar Libro ===                         ║" << endl;
    cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
    cout << "║ ISBN: "; getline(cin, isbn);
    cout << "║ Titulo: "; getline(cin, titulo); 
    cout << "║ Autor: "; getline(cin, autor);
    cout << "║ Año: "; getline(cin, anio);
    cout << "║ Categoria: "; getline(cin, categoria);
    cout << "║ Cantidad Disponible: "; getline(cin, cantidadDisponible);
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;


    cout << endl;
    cout << " Libro registrado correctamente ✅ " << endl;

    libros.push_back(Libro(isbn, titulo, autor, stoi(anio), categoria, stoi(cantidadDisponible)));
    guardarLibros();
    
    libros.clear();
    return true;
}

void SistemaBiblioteca::buscarLibro(){
    cargarLibros();
    string buscar;
    int encontrado;

    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ === Buscar Libro por Titulo, Autor o ISBN ===                 ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << "   Ingrese el Titulo, Autor o ISBN: ";
    getline(cin, buscar);
    cout << endl;

    for (size_t i = 0; i < libros.size(); i++)
    {
        if (libros[i].getTitulo() == buscar || libros[i].getAutor() == buscar || libros[i].getISBN() == buscar)
        {
            cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
            cout << "  ISBN " << libros[i].getISBN() << endl;
            cout << "  Titulo: " << libros[i].getTitulo() << endl;
            cout << "  Autor: " << libros[i].getAutor() << endl;
            cout << "  Año: " << libros[i].getAnio() << endl;
            cout << "  Categoria: " << libros[i].getCategoria() << endl;
            cout << "  Cantidad Disponible: " << libros[i].getCantidadDisponible() << endl;
            cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
            cout << endl;
            cout << "Libro Encontrado. ✅" << endl;
            encontrado = 1;
        } 
    }

    if (encontrado != 1) cout << "Libro no Encontrado. 🚨" << endl;
    libros.clear();
}

void SistemaBiblioteca::listarLibros(){
    cargarLibros();

    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ === Lista de libros ===                                      ║" << endl;

    for (size_t i = 0; i < libros.size(); i++)
    {
        cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
        cout << "  ISBN " << libros[i].getISBN() << endl;
        cout << "  Titulo: " << libros[i].getTitulo() << endl;
        cout << "  Autor: " << libros[i].getAutor() << endl;
        cout << "  Año: " << libros[i].getAnio() << endl;
        cout << "  Categoria: " << libros[i].getCategoria() << endl;
        cout << "  Cantidad Disponible: " << libros[i].getCantidadDisponible() << endl;
    }
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;
    libros.clear();
}

void SistemaBiblioteca::actualizarLibro(){
    cargarLibros();
    string buscar;
    int encontrado, posicion;

    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ === Actualizar Libro ===                                     ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << "   Ingrese el Titulo, Autor o ISBN: ";
    getline(cin, buscar);
    cout << endl;

    for (size_t i = 0; i < libros.size(); i++)
    {
        if (libros[i].getTitulo() == buscar || libros[i].getAutor() == buscar || libros[i].getISBN() == buscar)
        {
            cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
            cout << "  ISBN " << libros[i].getISBN() << endl;
            cout << "  Titulo: " << libros[i].getTitulo() << endl;
            cout << "  Autor: " << libros[i].getAutor() << endl;
            cout << "  Año: " << libros[i].getAnio() << endl;
            cout << "  Categoria: " << libros[i].getCategoria() << endl;
            cout << "  Cantidad Disponible: " << libros[i].getCantidadDisponible() << endl;
            cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
            cout << endl;
            cout << "Libro Encontrado. ✅" << endl;
            encontrado = 1;
            posicion = i;
        } 
    }

    if (encontrado == 1){
        //actualizar Libro
        string isbn, titulo, autor, anio, categoria, cantidadDisponible;
        
        cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║  === Ingrese los Nuevos Valores ===                          ║" << endl;
        cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
        cout << "║ ISBN: "; getline(cin, isbn);
        cout << "║ Titulo: "; getline(cin, titulo); 
        cout << "║ Autor: "; getline(cin, autor);
        cout << "║ Año: "; getline(cin, anio);
        cout << "║ Categoria: "; getline(cin, categoria);
        cout << "║ Cantidad Disponible: "; getline(cin, cantidadDisponible);
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;

        //actualizamos los datos
        libros[posicion].setISBN(isbn);
        libros[posicion].setTitulo(titulo);
        libros[posicion].setAutor(autor);
        libros[posicion].setAnio(stoi(anio));
        libros[posicion].setCategoria(categoria);
        libros[posicion].setCantidadDisponible(stoi(cantidadDisponible));
        guardarLibros();

        cout << "Libro Actualizado. ✅" << endl;
    }else{
        cout << "Libro no Encontrado. 🚨" << endl;
    }

    libros.clear();
}

void SistemaBiblioteca::eliminarLibro(){
    cargarLibros();
    string buscar;
    int encontrado, posicion;

    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ === Eliminar Libro ===                                       ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << "   Ingrese el Titulo, Autor o ISBN: ";
    getline(cin, buscar);
    cout << endl;

    for (size_t i = 0; i < libros.size(); i++)
    {
        if (libros[i].getTitulo() == buscar || libros[i].getAutor() == buscar || libros[i].getISBN() == buscar)
        {
            cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
            cout << "  ISBN " << libros[i].getISBN() << endl;
            cout << "  Titulo: " << libros[i].getTitulo() << endl;
            cout << "  Autor: " << libros[i].getAutor() << endl;
            cout << "  Año: " << libros[i].getAnio() << endl;
            cout << "  Categoria: " << libros[i].getCategoria() << endl;
            cout << "  Cantidad Disponible: " << libros[i].getCantidadDisponible() << endl;
            cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
            cout << endl;
            cout << "Libro Encontrado. ✅" << endl;
            encontrado = 1;
            posicion = i;
        } 
    }

    string respuesta;
    if (encontrado == 1){
        cout << "Desea Eliminar el Libro? 🚧 (S/N): ";
        getline(cin, respuesta);

        if (respuesta == "S" || respuesta == "s")
        {
            libros.erase(libros.begin() + posicion);
        }
        guardarLibros();
        cout << "Libro Eliminado. ✅" << endl;
    }else{
        cout << "Libro no Encontrado. 🚨" << endl;
    }

    libros.clear();
}

void SistemaBiblioteca::mostrarMenuGestionLibro()
{
    int opcion2;
    do
    {
        cout << endl;
        cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║              === GESTIÓN DE LIBROS ===                       ║" << endl;
        cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
        cout << "║ 1. Registrar Libro                                           ║" << endl;
        cout << "║ 2. Buscar Libro                                              ║" << endl;
        cout << "║ 3. Listar Libros                                             ║" << endl;
        cout << "║ 4. Actualizar Libro                                          ║" << endl;
        cout << "║ 5. Eliminar Libro                                            ║" << endl;
        cout << "║ 6. Regresar                                                  ║" << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;

        cout << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion2;
        cin.ignore(); // Limpiar el buffer de entrada
        cout << endl;

        switch (opcion2)
        {
        case 1:
        {
            agregarLibro();
            utilidades.limpiarPantallaValidar();
            cout << endl;
        }
        break;

        case 2:
            buscarLibro();
            utilidades.limpiarPantallaValidar();
            cout << endl;
            break;

        case 3:
            listarLibros();
            utilidades.limpiarPantallaValidar();
            cout << endl;
            break;

        case 4:
            actualizarLibro();
            utilidades.limpiarPantallaValidar();
            cout << endl;
            break;

        case 5:
            eliminarLibro();
            utilidades.limpiarPantallaValidar();
            cout << endl;
            break;

        case 6:
            utilidades.limpiarPantalla();
            cout << endl;
            break;
        default:
            utilidades.limpiarPantalla();
            cout << endl;
            cout << "Opción inválida. Por favor, intente de nuevo. 🚨" << endl;
            cout << endl;
            break;
        }
    } while (opcion2 != 6);
}












//PRESTAMOS
void SistemaBiblioteca::cargarPrestamos(){
    ifstream archivo(prestamosTxt);
    string lineaTexto;

    while (getline(archivo, lineaTexto)) {
        stringstream infoLineaTexto(lineaTexto);
        string idPrestamo, idUsuario, isbn, fechaPrestamo, fechaDevolucion, activo, multa;

        getline(infoLineaTexto, idPrestamo, ';');
        getline(infoLineaTexto, idUsuario, ';');
        getline(infoLineaTexto, isbn, ';');
        getline(infoLineaTexto, fechaPrestamo, ';');
        getline(infoLineaTexto, fechaDevolucion, ';');
        getline(infoLineaTexto, activo, ';');
        getline(infoLineaTexto, multa, ';');

        if (idPrestamo == "IdPrestamo") continue;

        bool activoBool = (activo == "1");
        double multaDouble = round(stod(multa) * 100.0) / 100.0;

        prestamos.push_back(Prestamo(idPrestamo, idUsuario, isbn, fechaPrestamo, fechaDevolucion, activoBool, multaDouble));
    }

    archivo.close();
}

void SistemaBiblioteca::guardarPrestamos(){
    ofstream archivo(prestamosTxt, ios::trunc);

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo prestamos.txt" << endl;
    } else {
        archivo << "IdPrestamo;IdUsuario;ISBN;FechaPrestamo;FechaDevolucion;Activo;Multa" << endl;
        for (size_t i = 0; i < prestamos.size(); i++) {
            archivo 
                << prestamos[i].getIdPrestamo() << ";"
                << prestamos[i].getIdUsuario() << ";"
                << prestamos[i].getISBN() << ";"
                << prestamos[i].getFechaPrestamo() << ";"
                << prestamos[i].getFechaDevolucion() << ";"
                << prestamos[i].getActivo() << ";"
                << prestamos[i].getMulta() << endl;
        }

        archivo.close();
    }
}

bool SistemaBiblioteca::realizarPrestamo() {
    cargarUsuarios();
    cargarLibros();
    cargarPrestamos();
    
    string idUsuario, isbn;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║              === Registrar Prestamo ===                      ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << " Ingrese ID de usuario: ";
    getline(cin, idUsuario);
    cout << " Ingrese ISBN del libro: ";
    getline(cin, isbn);

    // Buscar usuario
    int posUsuario = -1;
    for (int i = 0; i < usuarios.size(); i++) {
        if (usuarios[i].getId() == idUsuario) { posUsuario = i; break; }
    }
    if (posUsuario == -1) {
        cout << "Usuario no encontrado 🚨" << endl;
        return false;
    }
    if (!usuarios[posUsuario].puedePrestar()) {
        cout << "El usuario ya tiene 3 libros prestados 🚨" << endl;
        return false;
    }

    // Buscar libro
    int posLibro = -1;
    for (int i = 0; i < libros.size(); i++) {
        if (libros[i].getISBN() == isbn) { posLibro = i; break; }
    }
    if (posLibro == -1) {
        cout << "Libro no encontrado 🚨" << endl;
        return false;
    }
    if (libros[posLibro].getCantidadDisponible() <= 0) {
        cout << "Libro no disponible 🚨" << endl;
        return false;
    }

    // Crear préstamo
    string idPrestamo = to_string(prestamos.size() + 1);
    string fechaHoy = utilidades.obtenerFechaActual();
    prestamos.push_back(Prestamo(idPrestamo, idUsuario, isbn, fechaHoy, "", true, 0.0));

    // Actualizar libro y usuario
    libros[posLibro].setCantidadDisponible(libros[posLibro].getCantidadDisponible() - 1);
    usuarios[posUsuario].setLibrosPrestados(usuarios[posUsuario].getLibrosPrestados() + 1);

    guardarPrestamos();
    guardarLibros();
    guardarUsuarios();

    cout << " Préstamo realizado ✅" << endl;

    prestamos.clear();
    libros.clear();
    usuarios.clear();

    return true;
}

bool SistemaBiblioteca::registrarDevolucion() {
    cargarUsuarios();
    cargarLibros();
    cargarPrestamos();

    string idPrestamo;
    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ === Registrar Devolución de Préstamo ===                     ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << " Ingrese el ID del préstamo: ";
    getline(cin, idPrestamo);
    cout << endl;

    int posPrestamo = -1;
    for (int i = 0; i < prestamos.size(); i++) {
        if (prestamos[i].getIdPrestamo() == idPrestamo && prestamos[i].getActivo()) {
            posPrestamo = i;
            break;
        }
    }

    if (posPrestamo == -1) {
        cout << "Préstamo no encontrado o ya fue devuelto 🚨" << endl;
        prestamos.clear();
        usuarios.clear();
        libros.clear();
        return false;
    }

    // Obtener fecha de devolución
    string fechaHoy = utilidades.obtenerFechaActual();
    prestamos[posPrestamo].setFechaDevolucion(fechaHoy);

    // Calcular multa
    prestamos[posPrestamo].calcularMulta(prestamos[posPrestamo].getFechaPrestamo(), fechaHoy);
    // prestamos[posPrestamo].setMulta(multaCalculada);

    // Marcar como devuelto
    prestamos[posPrestamo].setActivo(false);

    // Actualizar usuario
    for (int i = 0; i < usuarios.size(); i++) {
        if (usuarios[i].getId() == prestamos[posPrestamo].getIdUsuario()) {
            usuarios[i].setLibrosPrestados(usuarios[i].getLibrosPrestados() - 1);
            break;
        }
    }

    // Actualizar disponibilidad del libro
    for (int i = 0; i < libros.size(); i++) {
        if (libros[i].getISBN() == prestamos[posPrestamo].getISBN()) {
            libros[i].setCantidadDisponible(libros[i].getCantidadDisponible() + 1);
            break;
        }
    }

    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ ✅ Devolución registrada exitosamente                         ║" << endl;
    cout << "║ Multa generada: Q" << fixed << setprecision(2) << prestamos[posPrestamo].getMulta() 
         << "                                      ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;

    // Guardar cambios
    guardarPrestamos();
    guardarLibros();
    guardarUsuarios();

    prestamos.clear();
    libros.clear();
    usuarios.clear();

    return true;
}

void SistemaBiblioteca::consultarHistorialPorUsuario() {
    cargarUsuarios();
    cargarLibros();
    cargarPrestamos();

    string idUsuario;
    bool encontrado = false;

    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ === Consultar Historial de Préstamos por Usuario ===         ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << " Ingrese el ID del usuario: ";
    getline(cin, idUsuario);
    cout << endl;

    // Validar que el usuario exista
    int posUsuario = -1;
    for (int i = 0; i < usuarios.size(); i++) {
        if (usuarios[i].getId() == idUsuario) {
            posUsuario = i;
            break;
        }
    }

    if (posUsuario == -1) {
        cout << "Usuario no encontrado 🚨" << endl;
        prestamos.clear();
        libros.clear();
        usuarios.clear();
        return;
    }

    cout << "Historial del usuario: " << usuarios[posUsuario].getNombre() << endl;
    cout << "--------------------------------------------------------------" << endl;

    // Recorrer préstamos y mostrar los que corresponden al usuario
    for (int i = 0; i < prestamos.size(); i++) {
        if (prestamos[i].getIdUsuario() == idUsuario) {
            encontrado = true;

            cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
            cout << "  ID Préstamo: " << prestamos[i].getIdPrestamo() << endl;
            cout << "  ISBN: " << prestamos[i].getISBN() << endl;
            cout << "  Fecha Préstamo: " << prestamos[i].getFechaPrestamo() << endl;
            cout << "  Fecha Devolución: " 
                 << (prestamos[i].getFechaDevolucion().empty() ? "No devuelto" : prestamos[i].getFechaDevolucion()) 
                 << endl;
            cout << "  Estado: " << (prestamos[i].getActivo() ? "Activo" : "Devuelto") << endl;
            cout << "  Multa: Q" << fixed << setprecision(2) << prestamos[i].getMulta() << endl;
            cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
            cout << endl;
        }
    }

    if (!encontrado) {
        cout << "📭 Este usuario no tiene historial." << endl;
    }

    prestamos.clear();
    libros.clear();
    usuarios.clear();
}

void SistemaBiblioteca::listarPrestamosActivos() {
    cargarPrestamos();
    cargarUsuarios();
    cargarLibros();

    bool encontrado = false;

    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ === Listado de Préstamos Activos ===                         ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;

    for (int i = 0; i < prestamos.size(); i++) {
        if (prestamos[i].getActivo()) {
            encontrado = true;

            // Buscar el nombre del usuario
            string nombreUsuario = "Desconocido";
            for (int j = 0; j < usuarios.size(); j++) {
                if (usuarios[j].getId() == prestamos[i].getIdUsuario()) {
                    nombreUsuario = usuarios[j].getNombre();
                    break;
                }
            }

            // Buscar el título del libro
            string tituloLibro = "Desconocido";
            for (int k = 0; k < libros.size(); k++) {
                if (libros[k].getISBN() == prestamos[i].getISBN()) {
                    tituloLibro = libros[k].getTitulo();
                    break;
                }
            }

            cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
            cout << "  ID Préstamo: " << prestamos[i].getIdPrestamo() << endl;
            cout << "  Usuario (ID): " << prestamos[i].getIdUsuario() << endl;
            cout << "  Nombre Usuario: " << nombreUsuario << endl;
            cout << "  ISBN: " << prestamos[i].getISBN() << endl;
            cout << "  Libro: " << tituloLibro << endl;
            cout << "  Fecha de Préstamo: " << prestamos[i].getFechaPrestamo() << endl;
            cout << "  Multa a Pagar: " << prestamos[i].getMulta() << endl;
            cout << "  Estado: ACTIVO" << endl;
            cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
            cout << endl;
        }
    }

    if (!encontrado) {
        cout << "📭 No hay préstamos activos actualmente." << endl;
    }

    prestamos.clear();
    usuarios.clear();
    libros.clear();
}

void SistemaBiblioteca::calcularMultasRetraso() {
    cargarPrestamos();
    cargarUsuarios();
    cargarLibros();

    bool hayRetrasados = false;
    string fechaHoy = utilidades.obtenerFechaActual();

    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ === Cálculo de Multas por Préstamos Retrasados ===           ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;

    for (int i = 0; i < prestamos.size(); i++) {
        if (prestamos[i].getActivo()) {
            string fechaPrestamo = prestamos[i].getFechaPrestamo();
            int diasPrestamo = prestamos[i].calcularDiasRetraso(fechaPrestamo, fechaHoy);

            if (diasPrestamo > 7) {
                double multa = (diasPrestamo - 7) * 5.0; // Q5 por día extra
                prestamos[i].setMulta(multa);

                hayRetrasados = true;

                // Buscar usuario
                string nombreUsuario = "Desconocido";
                for (int j = 0; j < usuarios.size(); j++) {
                    if (usuarios[j].getId() == prestamos[i].getIdUsuario()) {
                        nombreUsuario = usuarios[j].getNombre();
                        break;
                    }
                }

                // Buscar libro
                string tituloLibro = "Desconocido";
                for (int k = 0; k < libros.size(); k++) {
                    if (libros[k].getISBN() == prestamos[i].getISBN()) {
                        tituloLibro = libros[k].getTitulo();
                        break;
                    }
                }

                cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
                cout << "  ID Préstamo: " << prestamos[i].getIdPrestamo() << endl;
                cout << "  Usuario: " << nombreUsuario << " (ID: " << prestamos[i].getIdUsuario() << ")" << endl;
                cout << "  Libro: " << tituloLibro << " (ISBN: " << prestamos[i].getISBN() << ")" << endl;
                cout << "  Fecha Préstamo: " << prestamos[i].getFechaPrestamo() << endl;
                cout << "  Días Prestado: " << diasPrestamo << endl;
                cout << "  Multa aplicada: Q" << fixed << setprecision(2) << multa << endl;
                cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
                cout << endl;
            }
        }
    }

    if (!hayRetrasados) {
        cout << "✅ No hay préstamos con retraso mayor a 7 días." << endl;
    } else {
        guardarPrestamos();
        cout << "✅ Multas calculadas y actualizadas correctamente." << endl;
    }

    prestamos.clear();
    usuarios.clear();
    libros.clear();
}

void SistemaBiblioteca::mostrarMenuGestionPrestamo()
{
    int opcion3;
    do
    {
        cout << endl;
        cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║              === GESTIÓN DE PRESTAMOS ===                    ║" << endl;
        cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
        cout << "║ 1. Realizar Prestamo                                         ║" << endl;
        cout << "║ 2. Registrar Devoluciones                                    ║" << endl;
        cout << "║ 3. Historial por Usuario                                     ║" << endl;
        cout << "║ 4. Listar Prestamos Activos                                  ║" << endl;
        cout << "║ 5. Calcular Multas                                           ║" << endl;
        cout << "║ 6. Regresar                                                  ║" << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;

        cout << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion3;
        cin.ignore(); // Limpiar el buffer de entrada
        cout << endl;

        switch (opcion3)
        {
        case 1:
        {
            utilidades.limpiarPantalla();
            realizarPrestamo();
            utilidades.limpiarPantallaValidar();
            cout << endl;
        }
        break;

        case 2:
            utilidades.limpiarPantalla();
            registrarDevolucion();
            utilidades.limpiarPantallaValidar();
            cout << endl;
            break;

        case 3:
            utilidades.limpiarPantalla();
            consultarHistorialPorUsuario();
            utilidades.limpiarPantallaValidar();
            cout << endl;
            break;

        case 4:
            utilidades.limpiarPantalla();
            listarPrestamosActivos();
            utilidades.limpiarPantallaValidar();
            cout << endl;
            break;

        case 5:
            utilidades.limpiarPantalla();
            calcularMultasRetraso();
            utilidades.limpiarPantallaValidar();
            cout << endl;
            break;

        case 6:
            utilidades.limpiarPantalla();
            cout << endl;
            break;
        default:
            utilidades.limpiarPantalla();
            cout << endl;
            cout << "Opción inválida. Por favor, intente de nuevo. 🚨" << endl;
            cout << endl;
            break;
        }
    } while (opcion3 != 6);
}









void SistemaBiblioteca::reporteLibrosMasPrestados() {
    cargarLibros();
    cargarPrestamos();

    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ === Reporte: Libros Más Prestados ===                        ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;

    if (prestamos.empty()) {
        cout << "No existen préstamos registrados aún. 🚨" << endl;
        return;
    }

    // Contadores por ISBN
    map<string, int> conteoPrestamos;
    for (auto& p : prestamos) {
        conteoPrestamos[p.getISBN()]++;
    }

    // Mostrar resultados
    for (auto& libro : libros) {
        int cantidad = conteoPrestamos[libro.getISBN()];
        cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "  Título: " << libro.getTitulo() << endl;
        cout << "  Autor: " << libro.getAutor() << endl;
        cout << "  ISBN: " << libro.getISBN() << endl;
        cout << "  Veces Prestado: " << cantidad << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    }

    prestamos.clear();
    libros.clear();
}

void SistemaBiblioteca::reporteUsuariosConMasPrestamos() {
    cargarUsuarios();
    cargarPrestamos();

    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ === Reporte: Usuarios con Más Préstamos ===                  ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;

    if (prestamos.empty()) {
        cout << "No existen préstamos registrados. 🚨" << endl;
        return;
    }

    map<string, int> conteoUsuarios;
    for (auto& p : prestamos) {
        conteoUsuarios[p.getIdUsuario()]++;
    }

    for (auto& usuario : usuarios) {
        int cantidad = conteoUsuarios[usuario.getId()];
        cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "  ID Usuario: " << usuario.getId() << endl;
        cout << "  Nombre: " << usuario.getNombre() << endl;
        cout << "  Carrera: " << usuario.getCarrera() << endl;
        cout << "  Total de Préstamos: " << cantidad << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    }

    prestamos.clear();
    usuarios.clear();
}

void SistemaBiblioteca::reporteLibrosBajaDisponibilidad() {
    cargarLibros();

    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ === Reporte: Libros con Baja Disponibilidad ===              ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;

    bool encontrado = false;

    for (auto& libro : libros) {
        if (libro.getCantidadDisponible() <= 2) {
            encontrado = true;
            cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
            cout << "  Título: " << libro.getTitulo() << endl;
            cout << "  Autor: " << libro.getAutor() << endl;
            cout << "  ISBN: " << libro.getISBN() << endl;
            cout << "  Categoría: " << libro.getCategoria() << endl;
            cout << "  Disponibles: " << libro.getCantidadDisponible() << endl;
            cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
        }
    }

    if (!encontrado) {
        cout << "✅ No hay libros con baja disponibilidad." << endl;
    }

    libros.clear();
}

void SistemaBiblioteca::reporteMultasPendientes() {
    cargarPrestamos();
    cargarUsuarios();
    cargarLibros();

    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ === Reporte: Multas Pendientes ===                           ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;

    bool encontrado = false;

    for (auto& prestamo : prestamos) {
        if (prestamo.getMulta() > 0 && prestamo.getActivo() == 1) {
            encontrado = true;

            // Buscar usuario
            string nombreUsuario = "Desconocido";
            for (auto& usuario : usuarios) {
                if (usuario.getId() == prestamo.getIdUsuario()) {
                    nombreUsuario = usuario.getNombre();
                    break;
                }
            }

            // Buscar libro
            string tituloLibro = "Desconocido";
            for (auto& libro : libros) {
                if (libro.getISBN() == prestamo.getISBN()) {
                    tituloLibro = libro.getTitulo();
                    break;
                }
            }

            cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
            cout << "  ID Préstamo: " << prestamo.getIdPrestamo() << endl;
            cout << "  Usuario: " << nombreUsuario << " (ID: " << prestamo.getIdUsuario() << ")" << endl;
            cout << "  Libro: " << tituloLibro << " (ISBN: " << prestamo.getISBN() << ")" << endl;
            cout << "  Multa pendiente: Q" << fixed << setprecision(2) << prestamo.getMulta() << endl;
            cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
            cout << endl;
        }
    }

    if (!encontrado) {
        cout << "✅ No hay multas pendientes." << endl;
    }

    prestamos.clear();
    usuarios.clear();
    libros.clear();
}

// REPORTES Y ESTADÍSTICAS
void SistemaBiblioteca::mostrarMenuGestionReportes()
{
    int opcion4;
    do
    {
        cout << endl;
        cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║              === REPORTES Y ESTADÍSTICAS ===                 ║" << endl;
        cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
        cout << "║ 1. Libros más Prestados                                      ║" << endl;
        cout << "║ 2. Usuarios con más Préstamos                                ║" << endl;
        cout << "║ 3. Libros con baja Disponibilidad                            ║" << endl;
        cout << "║ 4. Reporte de multas pendientes                              ║" << endl;
        cout << "║ 5. Regresar                                                  ║" << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;

        cout << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion4;
        cin.ignore(); // Limpiar el buffer de entrada
        cout << endl;

        switch (opcion4)
        {
        case 1:
        {
            utilidades.limpiarPantalla();
            reporteLibrosMasPrestados();
            utilidades.limpiarPantallaValidar();
            cout << endl;
        }
        break;

        case 2:
            utilidades.limpiarPantalla();
            reporteUsuariosConMasPrestamos();
            utilidades.limpiarPantallaValidar();
            cout << endl;
            break;

        case 3:
            utilidades.limpiarPantalla();
            reporteLibrosBajaDisponibilidad();
            utilidades.limpiarPantallaValidar();
            cout << endl;
            break;

        case 4:
            utilidades.limpiarPantalla();
            reporteMultasPendientes();
            utilidades.limpiarPantallaValidar();
            cout << endl;
            break;

        case 5:
            utilidades.limpiarPantalla();
            cout << endl;
            break;
        default:
            utilidades.limpiarPantalla();
            cout << endl;
            cout << "Opción inválida. Por favor, intente de nuevo. 🚨" << endl;
            cout << endl;
            break;
        }
    } while (opcion4 != 5);
}



// REPORTE GENERAL TXT

void SistemaBiblioteca::generarReporteGeneralTxt() {
    cargarLibros();
    cargarUsuarios();
    cargarPrestamos();

    ofstream archivo("reporte_general_biblioteca.txt", ios::trunc);
    if (!archivo.is_open()) {
        cerr << "No se pudo crear el archivo de reportes. 🚨" << endl;
        return;
    }

    archivo << "╔══════════════════════════════════════════════════════════════╗" << endl;
    archivo << "║    REPORTE GENERAL DEL SISTEMA DE BIBLIOTECA                 ║" << endl;
    archivo << "╚══════════════════════════════════════════════════════════════╝" << endl;
    archivo << endl;

    // ================== LIBROS MÁS PRESTADOS ==================
    archivo << "=== Libros más prestados ===" << endl;
    map<string, int> conteoLibros;
    for (auto& p : prestamos) conteoLibros[p.getISBN()]++;
// ╣
    archivo << "╔══════════════════════════════════════════════════════════════╗" << endl;
    for (auto& libro : libros) {
        
        archivo << "  Título: " << libro.getTitulo() << endl;
        archivo << "  Prestamos: " << conteoLibros[libro.getISBN()] << endl;
        archivo << "╠══════════════════════════════════════════════════════════════╣" << endl;
    }
    archivo << "╚══════════════════════════════════════════════════════════════╝" << endl;
    archivo << endl;

    // ================== USUARIOS CON MÁS PRÉSTAMOS ==================
    archivo << "=== Usuarios con más préstamos ===" << endl;
    map<string, int> conteoUsuarios;
    for (auto& p : prestamos) conteoUsuarios[p.getIdUsuario()]++;

    
    archivo << "╔══════════════════════════════════════════════════════════════╗" << endl;
    for (auto& usuario : usuarios) {
        archivo << "  Usuario: " << usuario.getNombre() << " (ID: " << usuario.getId() << ")" << endl;
        archivo << "  Préstamos: " << conteoUsuarios[usuario.getId()] << endl;
        archivo << "╠══════════════════════════════════════════════════════════════╣" << endl;
    }
    archivo << "╚══════════════════════════════════════════════════════════════╝" << endl;
    archivo << endl;

    // ================== LIBROS BAJA DISPONIBILIDAD ==================
    archivo << "=== Libros con baja disponibilidad (≤ 2) === " << endl;
    
    archivo << "╔══════════════════════════════════════════════════════════════╗" << endl;
    for (auto& libro : libros) {
        if (libro.getCantidadDisponible() <= 2) {
            archivo << "  Título: " << libro.getTitulo() << endl;
            archivo << "  Disponibles: " << libro.getCantidadDisponible() << endl;
            archivo << "╠══════════════════════════════════════════════════════════════╣" << endl;
        }
    }
    archivo << "╚══════════════════════════════════════════════════════════════╝" << endl;
    archivo << endl;

    // ================== MULTAS PENDIENTES ==================
    archivo << "=== Multas Pendientes ===" << endl;
    archivo << "╔══════════════════════════════════════════════════════════════╗" << endl;
    for (auto& prestamo : prestamos) {
        if (prestamo.getMulta() > 0) {
            string nombreUsuario = "Desconocido";
            string tituloLibro = "Desconocido";

            for (auto& u : usuarios) if (u.getId() == prestamo.getIdUsuario()) nombreUsuario = u.getNombre();
            for (auto& l : libros) if (l.getISBN() == prestamo.getISBN()) tituloLibro = l.getTitulo();

            archivo << "  Usuario: " << nombreUsuario << endl;
            archivo << "  Libro: " << tituloLibro << endl;
            archivo << "  Multa: Q" << fixed << setprecision(2) << prestamo.getMulta() << endl;
            
            archivo << "╠══════════════════════════════════════════════════════════════╣" << endl;
        }
    }
    archivo << "╚══════════════════════════════════════════════════════════════╝" << endl;
    archivo << endl;

    archivo.close();

    prestamos.clear();
    usuarios.clear();
    libros.clear();

    cout << "✅ Reporte general generado correctamente en: reportes_biblioteca.txt" << endl;
}
