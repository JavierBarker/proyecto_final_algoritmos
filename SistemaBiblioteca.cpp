#include "SistemaBiblioteca.h"
#include "Utilidades.h"
#include "Usuario.h"
#include "Libro.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>


using namespace std;

//Variables Globales
Utilidades utilidades;
Usuario usuario;
Libro libro;

//vectores
vector<Usuario> usuarios;
vector<Libro> libros;


string usuariosTxt = "usuarios.txt";
string librosTxt = "libros.txt";
string prestamosTxt = "/output/prestamos.txt";

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
            /* code */
            break;
        case 4:
            /* code */
            break;
        
        case 5:
            utilidades.limpiarPantalla();
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

